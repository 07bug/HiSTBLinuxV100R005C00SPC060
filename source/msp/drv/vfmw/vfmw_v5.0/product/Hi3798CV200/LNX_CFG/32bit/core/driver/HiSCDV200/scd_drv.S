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
	.file	"scd_drv.c"
	.text
	.align	2
	.type	SCDDRV_SetStateIdle.part.0, %function
SCDDRV_SetStateIdle.part.0:
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
	ldr	r2, .L2
	mov	r3, r0, asl #6
	ldr	ip, .L2+4
	sub	r3, r3, r0, asl #2
	add	r3, r2, r3
	mov	r1, #0
	mov	r0, #1
	ldr	r2, [ip, #128]
	str	r1, [r3, #48]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r2
.L3:
	.align	2
.L2:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_SetStateIdle.part.0, .-SCDDRV_SetStateIdle.part.0
	.align	2
	.type	GetFreeSegBufSize.part.6, %function
GetFreeSegBufSize.part.6:
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
	add	r0, r0, #163840
	mov	r3, #0
	str	r3, [r1]
	ldr	r3, [r0, #36]
	ldr	r2, [r0, #32]
	cmp	r3, r2
	bls	.L5
	ldr	r0, [r0, #28]
	sub	r2, r2, #1
	add	r2, r2, r0
	rsb	r3, r3, r2
.L6:
	cmp	r3, r0
	strle	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L5:
	ldrcs	r0, [r0, #28]
	subcc	r2, r2, #1
	ldrcc	r0, [r0, #28]
	rsbcc	r3, r3, r2
	subcs	r3, r0, #1
	b	.L6
	UNWIND(.fnend)
	.size	GetFreeSegBufSize.part.6, .-GetFreeSegBufSize.part.6
	.align	2
	.global	WriteCabacTabDsp
	.type	WriteCabacTabDsp, %function
WriteCabacTabDsp:
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
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L12
	ldr	r3, .L13
	mov	r2, #5120
	ldr	r1, .L13+4
	ldr	r3, [r3, #52]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L12:
	mov	r2, #56
	ldr	r1, .L13+8
	mov	r0, #22
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L14:
	.align	2
.L13:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_CabacMN
	.word	.LC2
	UNWIND(.fnend)
	.size	WriteCabacTabDsp, .-WriteCabacTabDsp
	.align	2
	.global	SCDDRV_LoadDspCode
	.type	SCDDRV_LoadDspCode, %function
SCDDRV_LoadDspCode:
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
	mov	r7, r1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r5, .L35
	ldr	r0, [r5, #60]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L30
	cmp	r7, #1
	beq	.L31
	cmp	r7, #2
	beq	.L32
	mov	r0, r4
	ldr	r1, .L35+4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L32:
	ldr	r6, .L35+8
	mov	r2, #17920
	ldr	r1, .L35+12
	ldr	r3, [r6, #52]
	blx	r3
	mov	r1, r4
	ldr	r0, [r5, #64]
	bl	MEM_WritePhyWord
.L20:
	ldr	r0, [r5, #64]
	mov	r1, #4480
	mov	r4, #0
	add	r0, r0, #264
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #64]
	ldr	r1, [r5, #60]
	add	r0, r0, #268
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #64]
	mov	r1, r4
	add	r0, r0, #256
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #64]
	mov	r1, #5
	add	r0, r0, #256
	bl	MEM_WritePhyWord
	b	.L23
.L33:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L24
.L23:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	ldr	r0, [r5, #64]
	add	r0, r0, #260
	bl	MEM_ReadPhyWord
	tst	r0, #1
	beq	.L33
	cmp	r4, #1000
	bcs	.L24
	ldr	r2, .L35+16
	mov	r0, #0
	ldr	r1, .L35+20
	bl	dprint_vfmw
.L26:
	cmp	r7, #1
	beq	.L34
	cmp	r7, #2
	ldreq	r3, .L35+24
	moveq	r2, #1
	streq	r2, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L24:
	ldr	r2, .L35+16
	mov	r0, #0
	ldr	r1, .L35+28
	bl	dprint_vfmw
	b	.L26
.L31:
	ldr	r6, .L35+8
	mov	r2, #17920
	ldr	r1, .L35+32
	ldr	r3, [r6, #52]
	blx	r3
	mov	r1, r7
	ldr	r0, [r5, #64]
	bl	MEM_WritePhyWord
	b	.L20
.L34:
	ldr	r3, .L35+24
	mov	r2, #2
	str	r2, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L30:
	ldr	r2, [r5, #60]
	ldr	r1, .L35+36
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L36:
	.align	2
.L35:
	.word	.LANCHOR0
	.word	.LC4
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+1552
	.word	.LANCHOR3
	.word	.LC6
	.word	g_DspDrvState
	.word	.LC5
	.word	.LANCHOR1
	.word	.LC3
	UNWIND(.fnend)
	.size	SCDDRV_LoadDspCode, .-SCDDRV_LoadDspCode
	.align	2
	.global	GetInstIDByRawArray
	.type	GetInstIDByRawArray, %function
GetInstIDByRawArray:
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
	ldr	ip, .L47
	mov	r3, #0
	b	.L40
.L38:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L46
.L40:
	ldr	r2, [ip, r3, asl #3]
	cmp	r2, #0
	add	r1, r2, #80
	beq	.L38
	cmp	r0, r1
	bne	.L38
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L46:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L48:
	.align	2
.L47:
	.word	.LANCHOR0+68
	UNWIND(.fnend)
	.size	GetInstIDByRawArray, .-GetInstIDByRawArray
	.align	2
	.global	SCDDRV_SetStateIdle
	.type	SCDDRV_SetStateIdle, %function
SCDDRV_SetStateIdle:
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
	cmp	r0, #0
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SCDDRV_SetStateIdle.part.0
	UNWIND(.fnend)
	.size	SCDDRV_SetStateIdle, .-SCDDRV_SetStateIdle
	.align	2
	.global	SCDDRV_SetStateWork
	.type	SCDDRV_SetStateWork, %function
SCDDRV_SetStateWork:
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
	cmp	r0, #0
	ldreq	r3, .L53
	moveq	r2, #1
	streq	r2, [r3, #48]
	ldmfd	sp, {fp, sp, pc}
.L54:
	.align	2
.L53:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_SetStateWork, .-SCDDRV_SetStateWork
	.align	2
	.global	ResetSCD
	.type	ResetSCD, %function
ResetSCD:
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
	subs	r4, r0, #0
	bne	.L62
	ldr	r6, .L67
	mov	r1, #3
	ldr	r7, .L67+4
	ldr	r0, [r6, #64]
	add	r0, r0, #2176
	bl	MEM_WritePhyWord
	ldr	r0, [r6, #64]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_ReadPhyWord
	ldr	ip, [r7]
	ldr	r5, [ip, #120]
	ands	r2, r5, #1
	mov	r8, r0
	beq	.L65
	orr	r5, r5, #32
	str	r5, [ip, #120]
	ldr	r2, [ip, #372]
	mov	r3, r4
	movw	r1, #10000
	tst	r2, #2
	bne	.L58
.L66:
	add	r3, r3, #1
	cmp	r3, r1
	beq	.L60
	ldr	r2, [ip, #372]
	tst	r2, #2
	beq	.L66
.L58:
	movw	r2, #9999
	cmp	r3, r2
	bhi	.L60
.L61:
	ldr	r0, [r6, #64]
	and	r1, r8, #1
	bfc	r5, #5, #1
	str	r5, [ip, #120]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r0, [r6, #64]
	mov	r1, #2
	add	r0, r0, #2176
	bl	MEM_WritePhyWord
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L60:
	mov	r2, #0
	ldr	r1, .L67+8
	mov	r0, r2
	bl	dprint_vfmw
	ldr	ip, [r7]
	b	.L61
.L65:
	ldr	r1, .L67+12
	mov	r0, #26
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L62:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L68:
	.align	2
.L67:
	.word	.LANCHOR0
	.word	g_pstRegCrg
	.word	.LC8
	.word	.LC7
	UNWIND(.fnend)
	.size	ResetSCD, .-ResetSCD
	.align	2
	.global	SCDDRV_ResetSCD
	.type	SCDDRV_ResetSCD, %function
SCDDRV_ResetSCD:
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
	ldr	r3, .L73
	ldr	r3, [r3, #44]
	cmp	r3, r0
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, .L73+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L71
	mov	r1, #0
	mov	r0, r1
	bl	VDH_Reset_Module
.L72:
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SCDDRV_SetStateIdle.part.0
.L71:
	mov	r0, #0
	bl	ResetSCD
	b	.L72
.L74:
	.align	2
.L73:
	.word	.LANCHOR0
	.word	g_HalDisable
	UNWIND(.fnend)
	.size	SCDDRV_ResetSCD, .-SCDDRV_ResetSCD
	.align	2
	.global	SCDDRV_IsRawArrayFull
	.type	SCDDRV_IsRawArrayFull, %function
SCDDRV_IsRawArrayFull:
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
	add	r0, r0, #98304
	ldr	r3, [r0, #4]
	ldr	r0, [r0, #8]
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	rsb	r0, r0, r3
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsRawArrayFull, .-SCDDRV_IsRawArrayFull
	.align	2
	.global	SCDDRV_InsertRawPacket
	.type	SCDDRV_InsertRawPacket, %function
SCDDRV_InsertRawPacket:
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
	ldr	r3, .L80
	ldr	r5, [r1, #4]
	add	r0, r3, r0, lsl #3
	ldr	r2, [r0, #68]
	cmp	r2, #0
	cmpne	r5, #0
	moveq	r5, #1
	movne	r5, #0
	beq	.L78
	add	r4, r2, #98304
	ldr	r0, [r4, #84]
	ldr	lr, [r4, #88]
	add	r3, r0, #1
	mov	ip, r3, asr #31
	mov	ip, ip, lsr #22
	add	r3, r3, ip
	ubfx	r3, r3, #0, #10
	rsb	r3, ip, r3
	cmp	r3, lr
	beq	.L79
	ldr	ip, .L80+4
	mov	r3, r0, asl #7
	add	r2, r2, #80
	sub	r0, r3, r0, asl #5
	add	r0, r2, r0
	mov	r2, #96
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #84]
	mov	r0, r5
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	str	r3, [r4, #84]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L79:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L78:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L81:
	.align	2
.L80:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_InsertRawPacket, .-SCDDRV_InsertRawPacket
	.align	2
	.global	GetRawState
	.type	GetRawState, %function
GetRawState:
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
	cmp	r0, #31
	bhi	.L85
	ldr	r3, .L87
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #68]
	cmp	r3, #0
	beq	.L85
	add	r2, r3, #98304
	ldr	r3, [r2, #84]
	ldr	r1, [r2, #88]
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	cmp	r3, r1
	mvneq	r0, #3
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L85:
	mvn	r0, #3
	ldmfd	sp, {fp, sp, pc}
.L88:
	.align	2
.L87:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	GetRawState, .-GetRawState
	.align	2
	.global	ShowRawPacket
	.type	ShowRawPacket, %function
ShowRawPacket:
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
	add	r4, r0, #98304
	mov	ip, r0
	ldr	r3, [r4, #16]
	cmp	r3, #1024
	bcs	.L92
	ldr	r2, [r4, #4]
	cmp	r3, r2
	beq	.L92
	ldr	lr, .L93
	mov	r2, r3, asl #7
	sub	r3, r2, r3, asl #5
	mov	r0, r1
	mov	r2, #96
	add	r1, ip, r3
	ldr	r3, [lr, #52]
	blx	r3
	ldr	r3, [r4, #16]
	mov	r0, #0
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	str	r3, [r4, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L92:
	mvn	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L94:
	.align	2
.L93:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ShowRawPacket, .-ShowRawPacket
	.align	2
	.global	GetFirstOffset
	.type	GetFirstOffset, %function
GetFirstOffset:
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
	cmpne	r0, #0
	moveq	r2, #1
	movne	r2, #0
	beq	.L97
	add	r3, r0, #98304
	ldr	ip, [r3]
	ldr	r0, [r3, #4]
	cmp	ip, r0
	beq	.L98
	ldr	r3, [r3, #12]
	mov	r0, r2
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L97:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L98:
	mvn	r0, #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetFirstOffset, .-GetFirstOffset
	.align	2
	.global	GetFirstRawPacket
	.type	GetFirstRawPacket, %function
GetFirstRawPacket:
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
	cmp	r0, #0
	mov	r4, r1
	beq	.L103
	add	r3, r0, #98304
	ldr	r2, [r3]
	ldr	r1, [r3, #4]
	cmp	r2, r1
	beq	.L102
	ldr	r5, [r3, #12]
	mov	r7, r5, asr #31
	mov	r6, r5
	mov	r8, r5
.L101:
	str	r2, [r3, #16]
	mov	r1, r4
	bl	ShowRawPacket
	ldrd	r2, [r4, #40]
	ldr	r0, [r4, #4]
	ldr	r1, [r4, #12]
	adds	r6, r6, r2
	adc	r7, r7, r3
	add	r0, r0, r8
	rsb	r3, r5, r1
	str	r0, [r4, #4]
	strd	r6, [r4, #40]
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L102:
	mov	r8, #0
	mov	r6, #0
	mov	r7, #0
	mov	r5, r8
	b	.L101
.L103:
	mov	r3, #98304
	mov	r6, #0
	mov	r7, #0
	ldr	r2, [r3]
	mov	r8, r0
	mov	r5, r0
	b	.L101
	UNWIND(.fnend)
	.size	GetFirstRawPacket, .-GetFirstRawPacket
	.align	2
	.global	SetFirstOffset
	.type	SetFirstOffset, %function
SetFirstOffset:
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
	cmp	r0, #0
	beq	.L108
	add	r3, r0, #98304
	ldmia	r3, {r2, ip}
	cmp	r2, ip
	beq	.L107
	mov	ip, r2, asl #7
	ldr	lr, [r3, #12]
	sub	r2, ip, r2, asl #5
	add	r0, r0, r2
	add	r1, r1, lr
	ldr	r2, [r0, #12]
	cmp	r1, r2
	bge	.L108
	str	r1, [r3, #12]
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L108:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L107:
	mvn	r0, #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SetFirstOffset, .-SetFirstOffset
	.align	2
	.global	DeleteRawPacket
	.type	DeleteRawPacket, %function
DeleteRawPacket:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r8, r0
	mov	r9, r1
	moveq	r3, #1
	movne	r3, #0
	beq	.L125
	ldr	r0, .L137
	b	.L114
.L111:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L112
.L114:
	ldr	r2, [r0, r3, asl #3]
	mov	r7, r3, asl #3
	cmp	r2, #0
	add	r1, r2, #80
	beq	.L111
	cmp	r8, r1
	bne	.L111
	cmp	r3, #31
	bhi	.L112
	add	r3, r8, #98304
	str	r3, [fp, #-48]
	mov	r2, r3
	ldr	r3, [r3]
	ldr	r2, [r2, #4]
	cmp	r3, r2
	addgt	r2, r2, #1024
	rsb	r2, r3, r2
	cmp	r2, r9
	bcc	.L136
	cmp	r9, #0
	mov	r4, r3
	beq	.L118
	ldr	r10, .L137+4
	mov	r5, #0
.L119:
	mov	r3, r4, asl #7
	ldr	r2, .L137+8
	sub	r3, r3, r4, asl #5
	ldr	r1, .L137+12
	add	r3, r8, r3
	mov	r0, #26
	add	r6, r3, #8
	add	r5, r5, #1
	ldr	ip, [r6, #4]
	add	r4, r4, #1
	ldr	r3, [r3, #4]
	ubfx	r4, r4, #0, #10
	str	ip, [sp]
	bl	dprint_vfmw
	add	r2, r10, r7
	ldr	r1, [r6, #4]
	cmp	r5, r9
	ldr	r2, [r2, #68]
	add	r2, r2, #98304
	ldr	r3, [r2, #100]
	rsb	r3, r1, r3
	bic	r3, r3, r3, asr #31
	str	r3, [r2, #100]
	bne	.L119
	ldr	r2, [fp, #-48]
	ldr	r3, [r2]
	add	r5, r5, r3
	str	r5, [r2]
	cmp	r5, #1024
	bge	.L123
.L124:
	ldr	r3, [fp, #-48]
	mov	r0, #0
	str	r0, [r3, #12]
.L132:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L123:
	ldr	r3, [fp, #-48]
	sub	r5, r5, #1024
	str	r5, [r3]
	b	.L124
.L118:
	ldr	r2, [fp, #-48]
	cmp	r3, #1024
	str	r3, [r2]
	ldrge	r2, [fp, #-48]
	subge	r3, r3, #1024
	strge	r3, [r2]
.L122:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L125:
	mvn	r0, #0
	b	.L132
.L136:
	mov	r3, r9
	ldr	r1, .L137+16
	mov	r0, #26
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L132
.L112:
	movw	r2, #435
	ldr	r1, .L137+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L132
.L138:
	.align	2
.L137:
	.word	.LANCHOR0+68
	.word	.LANCHOR0
	.word	.LANCHOR3+20
	.word	.LC11
	.word	.LC10
	.word	.LC9
	UNWIND(.fnend)
	.size	DeleteRawPacket, .-DeleteRawPacket
	.align	2
	.global	GetRawNumOffset
	.type	GetRawNumOffset, %function
GetRawNumOffset:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	clz	ip, r0
	ldr	r9, [fp, #4]
	mov	ip, ip, lsr #5
	orrs	lr, ip, r1, lsr #31
	bne	.L147
	cmp	r3, #0
	cmpne	r2, #0
	moveq	r6, #1
	movne	r6, #0
	cmp	r9, #0
	orreq	r6, r6, #1
	cmp	r6, #0
	bne	.L147
	add	r8, r0, #98304
	cmp	ip, #0
	ldr	r7, [r8]
	ldr	lr, [r8, #12]
	mov	ip, r7, asl #7
	sub	ip, ip, r7, asl #5
	add	ip, r0, ip
	ldr	r5, [ip, #12]
	rsb	r5, lr, r5
	bne	.L141
	ldr	r6, [r8, #4]
	subs	r6, r6, r7
	addmi	r6, r6, #1024
.L141:
	cmp	r1, r5
	add	r6, r7, r6
	mov	ip, r7
	movge	lr, #0
	movlt	lr, #1
	cmp	r6, r7
	orrls	lr, lr, #1
	cmp	lr, #0
	bne	.L142
	mov	r4, r7
.L143:
	add	r4, r4, #1
	mov	ip, r4, asr #31
	mov	lr, ip, lsr #22
	add	ip, r4, lr
	ubfx	ip, ip, #0, #10
	rsb	ip, lr, ip
	mov	lr, ip, asl #7
	sub	lr, lr, ip, asl #5
	add	lr, r0, lr
	ldr	r10, [lr, #12]
	add	r5, r5, r10
	cmp	r1, r5
	movge	lr, #0
	movlt	lr, #1
	cmp	r6, r4
	orrls	lr, lr, #1
	cmp	lr, #0
	beq	.L143
	cmp	r7, r4
	rsbne	r5, r10, r5
	rsbne	r5, r5, r1
	strne	r5, [r3]
	beq	.L142
.L145:
	str	ip, [r9]
	mov	r0, #0
	ldr	r3, [r8]
	rsb	r4, r3, r4
	str	r4, [r2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L142:
	str	r1, [r3]
	mov	r4, r7
	b	.L145
.L147:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetRawNumOffset, .-GetRawNumOffset
	.align	2
	.global	DeleteRawLen
	.type	DeleteRawLen, %function
DeleteRawLen:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	clz	r3, r0
	mov	r5, r0
	mov	r3, r3, lsr #5
	orrs	ip, r3, r1, lsr #31
	bne	.L154
	cmp	r3, #0
	str	ip, [fp, #-40]
	str	ip, [fp, #-36]
	bne	.L154
	add	r4, r0, #98304
	ldr	r3, [r4, #20]
	ldr	ip, [r4, #12]
	rsb	r3, ip, r3
	movs	r6, r3, asr #31
	bne	.L159
	cmp	r1, r3
	bgt	.L154
	sub	r2, fp, #32
	sub	r3, fp, #36
	str	r2, [sp]
	sub	r2, fp, #40
	bl	GetRawNumOffset
	ldr	r0, [r4]
	ldr	ip, [fp, #-40]
	movw	r2, #601
	ldr	lr, [fp, #-36]
	add	r0, ip, r0
	mov	r3, ip
	mov	r1, r0, asr #31
	mov	r1, r1, lsr #22
	add	r0, r0, r1
	ubfx	r0, r0, #0, #10
	rsb	r1, r1, r0
	str	r1, [fp, #-32]
	mov	r0, r1, asl #7
	sub	r1, r0, r1, asl #5
	mov	r0, #26
	add	r1, r5, r1
	ldrb	r7, [r1, #2]	@ zero_extendqisi2
	str	r7, [sp, #12]
	ldr	r1, [r1, #12]
	str	ip, [sp, #4]
	str	lr, [sp]
	str	r1, [sp, #8]
	ldr	r1, .L163
	bl	dprint_vfmw
	ldr	r2, [fp, #-32]
	mov	r3, r2, asl #7
	sub	r3, r3, r2, asl #5
	add	r3, r5, r3
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L155
	ldr	r1, [fp, #-40]
.L156:
	mov	r0, r5
	bl	DeleteRawPacket
	ldmia	r4, {r2, r3}
	ldr	r1, [fp, #-36]
	cmp	r2, r3
	beq	.L162
	mov	r3, r2, asl #7
	ldr	r0, [r4, #12]
	sub	r3, r3, r2, asl #5
	add	r5, r5, r3
	add	r1, r1, r0
	ldr	r3, [r5, #12]
	cmp	r1, r3
	strlt	r1, [r4, #12]
	bge	.L154
.L159:
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L154:
	mvn	r6, #0
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L155:
	ldr	r1, [r3, #12]
	movw	r2, #606
	ldr	ip, [fp, #-36]
	mov	r0, #26
	ldr	r3, [fp, #-40]
	str	r1, [sp, #4]
	str	ip, [sp]
	ldr	r1, .L163+4
	bl	dprint_vfmw
	ldr	r1, [fp, #-40]
	str	r6, [fp, #-36]
	add	r1, r1, #1
	str	r1, [fp, #-40]
	b	.L156
.L162:
	mvn	r6, #2
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L164:
	.align	2
.L163:
	.word	.LC12
	.word	.LC13
	UNWIND(.fnend)
	.size	DeleteRawLen, .-DeleteRawLen
	.align	2
	.global	DeleteLastSendRaw
	.type	DeleteLastSendRaw, %function
DeleteLastSendRaw:
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
	cmp	r0, #31
	ldmhifd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L169
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #68]
	cmp	r0, #0
	beq	.L168
	add	r4, r0, #262144
	ldr	r1, [r4, #160]
	cmp	r1, #0
	ldmlefd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #80
	bl	DeleteRawPacket
	mov	r3, #0
	str	r3, [r4, #160]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L168:
	movw	r2, #626
	ldr	r1, .L169+4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L170:
	.align	2
.L169:
	.word	.LANCHOR0
	.word	.LC14
	UNWIND(.fnend)
	.size	DeleteLastSendRaw, .-DeleteLastSendRaw
	.align	2
	.global	GetRawStreamSize
	.type	GetRawStreamSize, %function
GetRawStreamSize:
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
	cmpne	r0, #0
	addne	r0, r0, #98304
	ldrne	r3, [r0, #20]
	strne	r3, [r1]
	ldrne	r0, [r0, #12]
	rsbne	r0, r0, r3
	strne	r0, [r1]
	movne	r0, r0, asr #31
	mvneq	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetRawStreamSize, .-GetRawStreamSize
	.align	2
	.global	GetRawStreamNum
	.type	GetRawStreamNum, %function
GetRawStreamNum:
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
	cmpne	r0, #0
	moveq	ip, #1
	movne	ip, #0
	beq	.L177
	add	r2, r0, #98304
	ldmia	r2, {r2, r3}
	subs	r3, r3, r2
	strpl	r3, [r1]
	addmi	r3, r3, #1024
	strmi	r3, [r1]
	movpl	r0, ip
	movmi	r0, ip
	ldmfd	sp, {fp, sp, pc}
.L177:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetRawStreamNum, .-GetRawStreamNum
	.align	2
	.global	ConfigStreamSegArray
	.type	ConfigStreamSegArray, %function
ConfigStreamSegArray:
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
	subs	r7, r0, #0
	mov	r5, r1
	mov	r6, r2
	mov	r8, r3
	beq	.L181
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r4, #1
	movne	r4, #0
	cmp	r3, #262144
	orrcc	r4, r4, #1
	cmp	r4, #0
	bne	.L181
	ldr	r3, .L182
	movw	r2, #32824
	movt	r2, 2
	mov	r1, r4
	ldr	r3, [r3, #48]
	blx	r3
	add	r2, r7, #163840
	mov	r0, r4
	str	r5, [r2, #24]
	str	r6, [r7]
	str	r5, [r2, #32]
	str	r5, [r2, #36]
	str	r8, [r2, #28]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L181:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L183:
	.align	2
.L182:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ConfigStreamSegArray, .-ConfigStreamSegArray
	.align	2
	.global	ResetStreamSegArray
	.type	ResetStreamSegArray, %function
ResetStreamSegArray:
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
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L189
	mov	r2, #163840
	mov	r1, #0
	add	r0, r4, #8
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r4, #163840
	mov	r3, #0
	ldr	r2, [r0, #24]
	str	r3, [r0, #8]
	str	r3, [r0, #12]
	str	r2, [r0, #32]
	str	r2, [r0, #36]
	str	r3, [r0, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L190:
	.align	2
.L189:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ResetStreamSegArray, .-ResetStreamSegArray
	.align	2
	.global	GetSegBufFreeSize
	.type	GetSegBufFreeSize, %function
GetSegBufFreeSize:
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
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	add	r0, r0, #163840
	ldr	r2, [r0, #36]
	ldr	r3, [r0, #32]
	cmp	r2, r3
	bhi	.L196
	ldrcs	r0, [r0, #28]
	subcc	r3, r3, #1
	rsbcc	r0, r2, r3
	subcs	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
.L196:
	ldr	r0, [r0, #28]
	sub	r3, r3, #1
	add	r3, r3, r0
	rsb	r0, r2, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetSegBufFreeSize, .-GetSegBufFreeSize
	.align	2
	.global	CheckData
	.type	CheckData, %function
CheckData:
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
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	and	r3, r1, #31
	sub	r2, r3, #30
	sub	ip, r3, #1
	cmp	r3, #19
	cmpne	r2, #1
	movls	r3, #1
	movhi	r3, #0
	cmp	ip, #12
	orrls	r3, r3, #1
	cmp	r3, #0
	addne	r2, r0, #294912
	ldrne	r3, [r2, #1176]
	addne	r3, r3, #1
	strne	r3, [r2, #1176]
	add	r3, r1, #79
	sub	r2, r1, #1
	uxtb	r3, r3
	cmp	r3, #4
	uxtb	r2, r2
	movhi	r3, #0
	movls	r3, #1
	cmp	r2, #183
	orrhi	r3, r3, #1
	cmp	r3, #0
	beq	.L206
.L201:
	add	r0, r0, #294912
	ldr	r3, [r0, #1180]
	add	r3, r3, #1
	str	r3, [r0, #1180]
	ldmfd	sp, {fp, sp, pc}
.L206:
	add	r1, r1, #73
	uxtb	r1, r1
	cmp	r1, #3
	ldmhifd	sp, {fp, sp, pc}
	b	.L201
	UNWIND(.fnend)
	.size	CheckData, .-CheckData
	.align	2
	.global	CheckStartCodeCnt
	.type	CheckStartCodeCnt, %function
CheckStartCodeCnt:
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
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	add	r0, r0, #294912
	ldr	r3, [r0, #1184]
	cmp	r3, #2
	ldmlefd	sp, {fp, sp, pc}
	tst	r1, #31
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #1196]
	ldr	r2, [r0, #1192]
	rsb	r1, r2, r3
	cmp	r1, #1
	beq	.L221
.L209:
	cmp	r3, r2
	ldmnefd	sp, {fp, sp, pc}
	ldr	r2, [r0, #1188]
	cmp	r3, r2
	ldmnefd	sp, {fp, sp, pc}
.L210:
	cmp	r3, #1
	cmpne	r3, #20
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #1176]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r0, #1176]
	ldr	r3, [r0, #1180]
	add	r3, r3, #1
	str	r3, [r0, #1180]
	ldmfd	sp, {fp, sp, pc}
.L221:
	ldr	r1, [r0, #1188]
	rsb	r1, r1, r2
	cmp	r1, #1
	bne	.L209
	b	.L210
	UNWIND(.fnend)
	.size	CheckStartCodeCnt, .-CheckStartCodeCnt
	.align	2
	.type	CheckStream.part.3, %function
CheckStream.part.3:
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
	ldr	r3, .L242
	mov	r6, r1
	ldr	r4, [r3, r1, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #568]
	cmp	r3, #0
	cmpne	r3, #3
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r4, #294912
	ldr	r3, [r5, #1184]
	cmp	r3, #199
	ldmgtfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r2, [r0]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #0
	movne	r7, r2
	bne	.L226
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L240
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	cmp	r2, #1
	ldreqb	r7, [r0, #3]	@ zero_extendqisi2
	andeq	r2, r7, #31
	beq	.L226
	mov	r2, r1
.L240:
	mov	r7, r2
.L226:
	ldr	r0, [r5, #1192]
	add	r3, r3, #1
	ldr	ip, [r5, #1196]
	mov	r1, r7
	str	r3, [r5, #1184]
	str	r0, [r5, #1188]
	mov	r0, r4
	str	ip, [r5, #1192]
	str	r2, [r5, #1196]
	bl	CheckData
	mov	r1, r7
	mov	r0, r4
	bl	CheckStartCodeCnt
	ldr	r3, [r5, #1184]
	cmp	r3, #199
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, [r5, #1176]
	ldr	r3, [r5, #1180]
	rsb	r1, r3, r2
	cmp	r1, #49
	ble	.L227
	ldr	r1, [r4, #568]
	cmp	r1, #3
	beq	.L241
.L227:
	rsb	r3, r2, r3
	cmp	r3, #49
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #568]
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, .L242+4
	ldr	ip, [r2]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, r6
	mov	r2, r3
	mov	r1, #124
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L241:
	ldr	r3, .L242+4
	ldr	r7, [r3]
	cmp	r7, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r3, #0
	mov	r1, #124
	mov	r2, r3
	mov	r0, r6
	blx	r7
	ldr	r3, [r5, #1180]
	ldr	r2, [r5, #1176]
	b	.L227
.L243:
	.align	2
.L242:
	.word	s_pstVfmwChan
	.word	g_event_report
	UNWIND(.fnend)
	.size	CheckStream.part.3, .-CheckStream.part.3
	.align	2
	.global	CheckStream
	.type	CheckStream, %function
CheckStream:
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
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	cmp	r1, #31
	ldmhifd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckStream.part.3
	UNWIND(.fnend)
	.size	CheckStream, .-CheckStream
	.align	2
	.global	InsertStreamSeg
	.type	InsertStreamSeg, %function
InsertStreamSeg:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r0
	mov	r5, r1
	beq	.L252
	add	r4, r0, #163840
	ldr	ip, [r4, #12]
	ldr	r0, [r4, #8]
	add	r3, ip, #1
	mov	r1, r3, asr #31
	mov	r1, r1, lsr #21
	add	r3, r3, r1
	ubfx	r3, r3, #0, #11
	rsb	r3, r1, r3
	cmp	r3, r0
	beq	.L253
	ldr	r0, [r5]
	cmp	r0, #0
	beq	.L251
	cmp	r2, #31
	bls	.L257
.L251:
	mov	r7, ip, asl #6
	ldr	r3, .L258
	add	r7, r7, ip, lsl #4
	mov	r1, r5
	add	r0, r7, #8
	mov	r2, #80
	add	r0, r6, r0
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r1, [r4, #12]
	add	ip, r6, r7
	mov	r7, #1
	add	r3, r1, r7
	mov	r0, #0
	mov	lr, r1, asl #6
	mov	r2, r3, asr #31
	add	lr, lr, r1, lsl #4
	add	r6, r6, lr
	mov	r2, r2, lsr #21
	add	r3, r3, r2
	strb	r7, [r6, #12]
	ubfx	r3, r3, #0, #11
	str	r1, [ip, #28]
	rsb	r3, r2, r3
	str	r3, [r4, #12]
	ldr	r1, [r5, #12]
	ldr	r3, [r5, #16]
	ldr	r2, [r4, #40]
	add	r3, r3, r1
	str	r3, [r4, #36]
	ldr	r1, [r5, #16]
	ldr	r3, [r4, #44]
	add	r1, r2, r1
	ldr	r2, [r4, #48]
	str	r1, [r4, #40]
	ldr	r1, [r5, #16]
	add	r2, r2, r7
	str	r2, [r4, #48]
	add	r3, r3, r1
	str	r3, [r4, #44]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L253:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L257:
	mov	r1, r2
	bl	CheckStream.part.3
	ldr	ip, [r4, #12]
	b	.L251
.L252:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L259:
	.align	2
.L258:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	InsertStreamSeg, .-InsertStreamSeg
	.align	2
	.global	SCDDRV_GetStreamSeg
	.type	SCDDRV_GetStreamSeg, %function
SCDDRV_GetStreamSeg:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r0, r1
	beq	.L267
	add	r4, r5, #163840
	ldr	r3, [r4, #8]
	ldr	ip, [r4, #12]
	cmp	ip, r3
	beq	.L269
	mov	r1, r3, asl #4
	mov	r6, r3, asl #6
	add	r2, r1, r6
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	bne	.L264
	b	.L262
.L274:
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	beq	.L262
.L264:
	add	r2, r3, #1
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #21
	add	r2, r2, r3
	ubfx	r2, r2, #0, #11
	rsb	r3, r3, r2
	cmp	ip, r3
	mov	r1, r3, asl #4
	mov	r6, r3, asl #6
	add	r2, r1, r6
	bne	.L274
.L269:
	mvn	r0, #2
.L261:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L262:
	add	r6, r1, r6
	add	r1, r6, #8
	adds	r1, r5, r1
	beq	.L269
	ldr	r3, .L275
	add	r5, r5, r6
	mov	r2, #80
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #2
	strb	r3, [r5, #12]
	mov	r0, #26
	ldr	r3, [r5, #24]
	ldr	ip, [r4, #44]
	ldr	r2, [r4, #48]
	rsb	ip, r3, ip
	ldr	r1, .L275+4
	sub	r2, r2, #1
	bic	ip, ip, ip, asr #31
	str	ip, [r4, #44]
	bic	r2, r2, r2, asr #31
	str	r2, [r4, #48]
	ldrb	ip, [r5, #13]	@ zero_extendqisi2
	ldr	r2, [r5, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L267:
	mvn	r0, #0
	b	.L261
.L276:
	.align	2
.L275:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC15
	UNWIND(.fnend)
	.size	SCDDRV_GetStreamSeg, .-SCDDRV_GetStreamSeg
	.align	2
	.global	ReleaseStreamSeg
	.type	ReleaseStreamSeg, %function
ReleaseStreamSeg:
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
	subs	r6, r0, #0
	mov	r4, r1
	beq	.L297
	movw	r3, #63486
	sub	r2, r1, #2048
	movt	r3, 65535
	cmp	r2, r3
	bls	.L297
	cmn	r1, #1
	add	r5, r6, #163840
	beq	.L311
	ldr	r3, [r5, #8]
	ldr	r2, [r5, #12]
	cmp	r3, r2
	bne	.L308
	b	.L285
.L288:
	add	r3, r3, #1
	ubfx	r3, r3, #0, #11
	cmp	r3, r2
	beq	.L285
.L308:
	cmp	r4, r3
	bne	.L288
	mov	r2, r3, asl #6
	add	r3, r2, r3, lsl #4
	add	r2, r6, r3
	ldrsb	r2, [r2, #12]
	cmp	r2, #2
	addeq	r3, r3, #8
	addeq	r7, r6, r3
	beq	.L282
.L285:
	mvn	r0, #2
.L307:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L311:
	ldr	r9, [r5, #8]
	ldr	r3, [r5, #12]
	cmp	r9, r3
	beq	.L285
	mov	r3, r9, asl #6
	mov	r4, r9
	add	r9, r3, r9, lsl #4
	mov	r2, r4
	add	r7, r9, #8
	add	r9, r6, r9
	ldr	r1, .L313
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r9, #24]
	add	r7, r6, r7
	cmp	r3, #0
	movne	r8, #0
	beq	.L284
.L283:
	ldr	r3, [r9, #8]
	mov	r0, #0
	ldr	r1, .L313+4
	ldrb	r2, [r3, r8]	@ zero_extendqisi2
	add	r8, r8, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #24]
	cmp	r3, r8
	movhi	r3, #1
	movls	r3, #0
	cmp	r8, #15
	movhi	r3, #0
	cmp	r3, #0
	bne	.L283
.L284:
	ldr	r1, .L313+8
	mov	r0, #0
	bl	dprint_vfmw
.L282:
	cmp	r7, #0
	beq	.L285
	ldr	r3, [r7, #16]
	mov	r2, #0
	strb	r2, [r7, #4]
	mov	r0, #26
	ldr	r2, [r7, #12]
	str	r4, [sp, #4]
	ldrb	ip, [r7, #5]	@ zero_extendqisi2
	ldr	r1, .L313+12
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #8]
	cmp	r3, r4
	beq	.L293
.L290:
	ldr	r2, [r7, #16]
	mov	r0, #0
	ldr	r3, [r5, #40]
	rsb	r3, r2, r3
	bic	r3, r3, r3, asr #31
	str	r3, [r5, #40]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L291:
	ldr	r2, [r5, #12]
	cmp	r2, r4
	beq	.L294
	ldrsb	r2, [r3, #12]
	cmp	r2, #0
	bne	.L312
.L298:
	add	r4, r4, #1
	ubfx	r4, r4, #0, #11
.L293:
	mov	r3, r4, asl #6
	cmp	r4, #2048
	add	r3, r3, r4, lsl #4
	add	r3, r6, r3
	bcc	.L291
	ldr	r2, .L313+16
	mov	r0, #1
	ldr	r1, .L313+20
	bl	dprint_vfmw
	ldr	r2, [r5, #12]
	cmp	r2, r4
	bne	.L298
.L294:
	ldr	r3, [r5, #36]
	str	r2, [r5, #8]
	str	r3, [r5, #32]
	b	.L290
.L312:
	str	r4, [r5, #8]
	ldr	r3, [r3, #20]
	str	r3, [r5, #32]
	b	.L290
.L297:
	mvn	r0, #0
	b	.L307
.L314:
	.align	2
.L313:
	.word	.LC16
	.word	.LC18
	.word	.LC17
	.word	.LC19
	.word	.LANCHOR3+36
	.word	.LC20
	UNWIND(.fnend)
	.size	ReleaseStreamSeg, .-ReleaseStreamSeg
	.align	2
	.global	GetSegStreamSize
	.type	GetSegStreamSize, %function
GetSegStreamSize:
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
	cmpne	r0, #0
	addne	r2, r0, #163840
	movne	r3, #0
	moveq	r3, #1
	movne	r0, r3
	ldrne	r3, [r2, #40]
	mvneq	r0, #0
	strne	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetSegStreamSize, .-GetSegStreamSize
	.align	2
	.global	GetSegStreamNum
	.type	GetSegStreamNum, %function
GetSegStreamNum:
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
	cmp	r0, #0
	addne	r0, r0, #163840
	ldrne	r3, [r0, #12]
	ldrne	r0, [r0, #8]
	rsbne	r0, r0, r3
	ubfxne	r0, r0, #0, #11
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetSegStreamNum, .-GetSegStreamNum
	.align	2
	.global	GetFreshSegStream
	.type	GetFreshSegStream, %function
GetFreshSegStream:
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
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	addeq	r0, r0, #163840
	ldreq	r3, [r0, #48]
	streq	r3, [r1]
	ldreq	r3, [r0, #44]
	streq	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetFreshSegStream, .-GetFreshSegStream
	.align	2
	.global	SCDDRV_PrepareSleep
	.type	SCDDRV_PrepareSleep, %function
SCDDRV_PrepareSleep:
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
	cmp	r0, #0
	bne	.L327
	ldr	r3, .L328
	ldr	r2, [r3, #324]
	cmp	r2, #0
	bne	.L327
	ldr	r0, [r3, #48]
	cmp	r0, #0
	moveq	r2, #2
	movne	r0, r2
	movne	r2, #1
	str	r2, [r3, #324]
	ldmfd	sp, {fp, sp, pc}
.L327:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L329:
	.align	2
.L328:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_PrepareSleep, .-SCDDRV_PrepareSleep
	.align	2
	.global	SCDDRV_GetSleepStage
	.type	SCDDRV_GetSleepStage, %function
SCDDRV_GetSleepStage:
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
	cmp	r0, #0
	ldreq	r3, .L333
	ldreq	r0, [r3, #324]
	movne	r0, #3
	ldmfd	sp, {fp, sp, pc}
.L334:
	.align	2
.L333:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_GetSleepStage, .-SCDDRV_GetSleepStage
	.align	2
	.global	SCDDRV_ForceSleep
	.type	SCDDRV_ForceSleep, %function
SCDDRV_ForceSleep:
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
	cmp	r0, #0
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, .L340
	ldr	r2, [r3, #324]
	cmp	r2, #2
	movne	r2, #2
	strne	r2, [r3, #324]
	ldmfd	sp, {fp, sp, pc}
.L341:
	.align	2
.L340:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_ForceSleep, .-SCDDRV_ForceSleep
	.align	2
	.global	SCDDRV_ExitSleep
	.type	SCDDRV_ExitSleep, %function
SCDDRV_ExitSleep:
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
	cmp	r0, #0
	ldreq	r3, .L344
	streq	r0, [r3, #324]
	ldmfd	sp, {fp, sp, pc}
.L345:
	.align	2
.L344:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_ExitSleep, .-SCDDRV_ExitSleep
	.align	2
	.global	SM_ClearInst
	.type	SM_ClearInst, %function
SM_ClearInst:
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
	cmp	r0, #31
	bhi	.L348
	ldr	r3, .L349
	mov	r2, #440
	ldr	ip, .L349+4
	movt	r2, 4
	add	r4, r3, r0, lsl #3
	mov	r1, #0
	mvn	r5, #0
	ldr	r3, [ip, #48]
	ldr	r0, [r4, #68]
	blx	r3
	ldr	r3, [r4, #68]
	mov	r0, #0
	mvn	r4, #0
	add	r3, r3, #262144
	strd	r4, [r3, #248]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L348:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L350:
	.align	2
.L349:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_ClearInst, .-SM_ClearInst
	.align	2
	.global	SM_InstInit
	.type	SM_InstInit, %function
SM_InstInit:
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
	ldr	r4, .L354
	ldr	r6, .L354+4
	add	r5, r4, #256
.L352:
	mov	r2, #8
	mov	r0, r4
	ldr	r3, [r6, #48]
	add	r4, r4, r2
	mov	r1, #0
	blx	r3
	cmp	r4, r5
	bne	.L352
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L355:
	.align	2
.L354:
	.word	.LANCHOR0+68
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_InstInit, .-SM_InstInit
	.align	2
	.global	SM_OpenSCDDrv
	.type	SM_OpenSCDDrv, %function
SM_OpenSCDDrv:
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
	adds	ip, r2, #0
	mov	r7, r1
	mov	r4, r0
	movne	ip, #1
	cmp	r1, #0
	movgt	r1, ip
	orrle	r1, ip, #1
	cmp	r0, #0
	orreq	r1, r1, #1
	cmp	r1, #0
	bne	.L364
	cmp	r2, #0
	beq	.L365
	cmp	r2, #1
	moveq	r1, #49152
	movteq	r1, 63941
	bne	.L373
.L359:
	mov	r6, r2, asl #2
	ldr	r8, .L375
	rsb	r9, r6, r2, lsl #6
	add	r5, r8, r9
	add	r6, r8, r6
	ldr	r2, [r5, #40]
	str	r1, [r6, #64]
	cmp	r2, #1
	beq	.L363
	ldr	ip, .L375+4
	mov	r2, #60
	mov	r1, #0
	mov	r0, r5
	ldr	r10, [ip, #48]
	blx	r10
	ldr	r2, .L375+8
	add	r1, r4, #15
	mov	r3, #0
	bic	r1, r1, #15
	add	r2, r2, r9
	str	r1, [r5, #12]
	add	r10, r5, #16
	str	r3, [r2, #56]
	mov	r0, r1
	str	r7, [r5, #4]
	str	r4, [r8, r9]
	rsb	r9, r4, r1
	str	r3, [r6, #324]
	bl	MEM_Phy2Vir
	add	r1, r4, #12288
	mov	r2, #12288
	add	r1, r1, r9
	str	r2, [r5, #16]
	str	r1, [r5, #24]
	add	r2, r5, #24
	str	r2, [fp, #-48]
	add	r4, r4, #28672
	add	r4, r4, #127
	add	r4, r4, r9
	bic	r4, r4, #127
	str	r0, [r5, #8]
	mov	r0, r1
	bl	MEM_Phy2Vir
	ldr	r2, [fp, #-48]
	mov	r1, #16384
	str	r4, [r8, #60]
	str	r1, [r2, #4]
	str	r0, [r10, #4]
	mov	r0, r4
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r8, #328]
	beq	.L374
	add	r9, r9, #46592
	ldr	r1, [r6, #64]
	ldr	r2, [r6, #336]
	cmp	r7, r9
	mov	r3, #17920
	str	r3, [r8, #332]
	str	r1, [r5, #32]
	str	r2, [r5, #36]
	blt	.L363
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L363
	ldr	r3, [r10, #4]
	cmp	r3, #0
	beq	.L363
	mov	r0, #0
	mov	r3, #1
	str	r3, [r5, #40]
.L357:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L373:
	mov	r0, r1
	ldr	r2, .L375+12
	ldr	r1, .L375+16
	bl	dprint_vfmw
	mvn	r0, #6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L365:
	mov	r1, #49152
	movt	r1, 63683
	b	.L359
.L363:
	mvn	r0, #6
	b	.L357
.L364:
	mvn	r0, #0
	b	.L357
.L374:
	ldr	r2, .L375+12
	ldr	r1, .L375+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L357
.L376:
	.align	2
.L375:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	.word	.LANCHOR3+56
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	SM_OpenSCDDrv, .-SM_OpenSCDDrv
	.align	2
	.global	SM_CloseSCDDrv
	.type	SM_CloseSCDDrv, %function
SM_CloseSCDDrv:
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
	cmp	r0, #0
	bne	.L381
	ldr	r1, .L389
	mov	ip, r0
.L380:
	cmp	r0, #31
	bhi	.L379
	ldr	r3, [r1, r0, asl #3]
	cmp	r3, #0
	add	r2, r3, #262144
	beq	.L379
	ldr	r3, [r2, #228]
	cmp	r3, #0
	beq	.L379
	ldr	r3, [r2, #216]
	cmp	r3, #0
	strle	ip, [r2, #228]
.L379:
	add	r0, r0, #1
	cmp	r0, #32
	bne	.L380
	ldr	ip, .L389+4
	mov	r4, #0
	ldr	r3, .L389+8
	mov	r1, r4
	mov	r2, #60
	ldr	r0, .L389+12
	str	r4, [ip, #56]
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L381:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L390:
	.align	2
.L389:
	.word	.LANCHOR0+68
	.word	g_VfmwGlobalStat
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_CloseSCDDrv, .-SM_CloseSCDDrv
	.align	2
	.global	SM_Config
	.type	SM_Config, %function
SM_Config:
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
	clz	r3, r1
	mov	r7, r0
	mov	r5, r1
	mov	r3, r3, lsr #5
	cmp	r0, #31
	orrhi	r3, r3, #1
	cmp	r3, #0
	bne	.L394
	ldr	r3, .L404
	add	r2, r3, r0, lsl #3
	ldr	r6, [r2, #68]
	clz	r8, r6
	mov	r8, r8, lsr #5
	cmp	r8, #0
	bne	.L394
	ldr	r2, [r1, #44]
	add	r4, r6, #262144
	str	r2, [r4, #296]
	ldr	r2, [r1, #12]
	ldr	r1, [r6, #20]
	cmp	r1, r2
	addeq	r6, r6, #8
	ldreq	r9, .L404+4
	beq	.L396
	cmp	r2, #0
	beq	.L394
	ldr	r2, [r5]
	cmp	r2, #0
	beq	.L394
	ldr	r1, [r3, #12]
	mov	r2, #2048
	ldr	r0, [r3, #24]
	ldr	lr, [r3, #8]
	str	r1, [r4, #184]
	ldr	ip, [r3, #16]
	ldr	r1, [r3, #20]
	ldr	r3, [r3, #28]
	str	r2, [r4, #200]
	str	r1, [r4, #188]
	str	lr, [r4, #176]
	str	ip, [r4, #180]
	str	r0, [r4, #192]
	str	r3, [r4, #196]
	ldr	r3, [r5, #12]
	ldr	r0, [r5]
	add	r1, r3, #3
	bic	r1, r1, #3
	rsb	r3, r3, r1
	add	r1, r1, #131072
	add	r2, r3, #131072
	str	r1, [r4, #204]
	add	r2, r0, r2
	str	r2, [r4, #172]
	ldr	r0, [r5, #16]
	rsb	r3, r3, r0
	sub	r3, r3, #132096
	str	r3, [r4, #208]
	cmp	r3, #262144
	blt	.L394
	ldr	r9, .L404+4
	add	r0, r6, #98304
	add	r6, r6, #8
	add	r0, r0, #104
	bl	ConfigStreamSegArray
	mov	r2, #72
	mov	r0, r6
	ldr	r3, [r9, #52]
	mov	r1, r5
	blx	r3
	str	r8, [r4, #216]
.L396:
	ldr	r3, [r9, #52]
	mov	r0, r6
	mov	r2, #72
	mov	r1, r5
	blx	r3
	mov	r3, #2
	str	r3, [r4, #284]
	mov	r0, #0
	ldr	r3, [r5, #8]
	str	r7, [r4, #212]
	cmp	r3, #2
	moveq	r3, #3
	streq	r3, [r4, #284]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L394:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L405:
	.align	2
.L404:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_Config, .-SM_Config
	.align	2
	.global	SM_CfgBuf
	.type	SM_CfgBuf, %function
SM_CfgBuf:
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
	cmp	r0, #31
	bhi	.L414
	cmp	r1, #0
	bne	.L415
	ldr	r2, .L416
	add	r0, r2, r0, lsl #3
	ldr	r3, [r0, #68]
	clz	r1, r3
	mov	r1, r1, lsr #5
	cmp	r1, #0
	bne	.L410
	add	r3, r3, #262144
	ldr	r0, [r3, #216]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r6, [r2, #12]
	mov	r0, r1
	ldr	r5, [r2, #8]
	mov	ip, #2048
	ldr	r4, [r2, #16]
	ldr	lr, [r2, #24]
	str	r1, [r3, #216]
	ldr	r1, [r2, #20]
	ldr	r2, [r2, #28]
	str	r6, [r3, #184]
	str	r5, [r3, #176]
	str	r4, [r3, #180]
	str	lr, [r3, #192]
	str	r1, [r3, #188]
	str	r2, [r3, #196]
	str	ip, [r3, #200]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L410:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L414:
	mov	r3, r0
	movw	r2, #1338
	ldr	r1, .L416+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L415:
	mov	r3, r1
	movw	r2, #1345
	ldr	r1, .L416+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L417:
	.align	2
.L416:
	.word	.LANCHOR0
	.word	.LC23
	.word	.LC24
	UNWIND(.fnend)
	.size	SM_CfgBuf, .-SM_CfgBuf
	.align	2
	.global	SM_Start
	.type	SM_Start, %function
SM_Start:
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
	cmp	r0, #31
	bhi	.L420
	ldr	r3, .L424
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #68]
	cmp	r3, #0
	beq	.L423
	ldr	r2, [r3, #24]
	cmp	r2, #0
	beq	.L423
	add	r3, r3, #262144
	ldr	r0, [r3, #228]
	cmp	r0, #0
	bne	.L423
	mov	r2, #1
	str	r2, [r3, #228]
	ldmfd	sp, {fp, sp, pc}
.L423:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L420:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L425:
	.align	2
.L424:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_Start, .-SM_Start
	.align	2
	.global	SM_Stop
	.type	SM_Stop, %function
SM_Stop:
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
	cmp	r0, #31
	bhi	.L428
	ldr	r3, .L434
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #68]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	add	r3, r0, #262144
	ldr	r0, [r3, #228]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r2, [r3, #216]
	cmp	r2, #0
	bgt	.L430
	mov	r0, #0
	str	r0, [r3, #228]
	ldmfd	sp, {fp, sp, pc}
.L430:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L428:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L435:
	.align	2
.L434:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_Stop, .-SM_Stop
	.align	2
	.global	SM_GetInfo
	.type	SM_GetInfo, %function
SM_GetInfo:
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
	clz	r3, r1
	mov	r3, r3, lsr #5
	cmp	r0, #31
	orrhi	r3, r3, #1
	cmp	r3, #0
	bne	.L446
	ldr	r3, .L451
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #68]
	cmp	r3, #0
	beq	.L450
	add	ip, r3, #262144
	add	r2, r3, #98304
	adds	r0, r2, #104
	ldr	lr, [ip, #228]
	strb	lr, [r1]
	ldr	lr, [ip, #276]
	str	lr, [r1, #20]
	moveq	lr, r0
	ldrne	r4, [ip, #112]
	ldrne	lr, [ip, #116]
	rsbne	lr, r4, lr
	ubfxne	lr, lr, #0, #11
	cmn	r3, #80
	str	lr, [r1, #8]
	movne	r4, #0
	moveq	r4, #1
	cmn	r3, #80
	cmnne	r1, #4
	beq	.L441
	ldr	r3, [r2, #84]
	ldr	lr, [r2, #80]
	subs	r3, r3, lr
	addmi	r3, r3, #1024
	str	r3, [r1, #4]
.L441:
	cmn	r1, #12
	movne	r3, #0
	moveq	r3, #1
	orrs	r3, r4, r3
	ldreq	r3, [r2, #100]
	streq	r3, [r1, #12]
	ldreq	r2, [r2, #92]
	rsbeq	r3, r2, r3
	streq	r3, [r1, #12]
	cmn	r1, #16
	cmpne	r0, #0
	moveq	r0, #1
	movne	r0, #0
	beq	.L448
	ldr	r3, [ip, #144]
	str	r3, [r1, #16]
	ldmfd	sp, {r4, fp, sp, pc}
.L450:
	cmp	r1, #0
	beq	.L446
	strb	r3, [r1]
	mvn	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L448:
	mov	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L446:
	mvn	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L452:
	.align	2
.L451:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_GetInfo, .-SM_GetInfo
	.align	2
	.global	GetRawNumInFrame
	.type	GetRawNumInFrame, %function
GetRawNumInFrame:
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
	add	r6, r0, #98304
	mov	r4, #1
	ldr	r3, [r6]
	mov	ip, r3, asl #5
	mov	r5, r3, asl #7
	rsb	lr, ip, r5
	add	lr, r0, lr
	ldr	lr, [lr, #12]
	str	lr, [r2]
	str	r4, [r1]
	b	.L454
.L456:
	ldr	r4, [r1]
	add	r4, r4, #1
	str	r4, [r1]
	ldr	r4, [lr, #12]
	ldr	lr, [r2]
	add	lr, lr, r4
	str	lr, [r2]
	ldr	lr, [r6, #4]
	cmp	lr, r3
	beq	.L458
	ldr	lr, [r1]
	cmp	lr, #1024
	bhi	.L458
.L454:
	rsb	ip, ip, r5
	add	r3, r3, #1
	ubfx	r3, r3, #0, #10
	ldrb	r4, [r0, ip]	@ zero_extendqisi2
	mov	r5, r3, asl #7
	mov	ip, r3, asl #5
	cmp	r4, #0
	rsb	lr, ip, r5
	add	lr, r0, lr
	bne	.L456
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L458:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetRawNumInFrame, .-GetRawNumInFrame
	.align	2
	.global	AdjustRawPacketVP6A
	.type	AdjustRawPacketVP6A, %function
AdjustRawPacketVP6A:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r10, [r1]
	add	ip, r0, #98304
	cmp	r10, #0
	ldr	ip, [ip]
	beq	.L464
	mov	r7, ip, asl #5
	mov	r6, ip, asl #7
	rsb	lr, r7, r6
	add	lr, r0, lr
	ldr	r4, [lr, #12]
	cmp	r4, #2
	bgt	.L465
	mov	lr, r4
	mov	r8, #3
	mov	r5, #0
	b	.L462
.L463:
	add	lr, r0, lr
	ldr	lr, [lr, #12]
	add	r4, r4, lr
	cmp	r4, #2
	bgt	.L467
.L462:
	add	ip, ip, #1
	add	r5, r5, #1
	ubfx	ip, ip, #0, #10
	cmp	r5, r10
	rsb	r8, lr, r8
	mov	r7, ip, asl #5
	mov	r6, ip, asl #7
	rsb	lr, r7, r6
	bne	.L463
.L464:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L467:
	mov	r9, r8, asr #31
.L461:
	rsb	r6, r7, r6
	rsb	r5, r5, r10
	add	r6, r0, r6
	str	r5, [r1]
	sub	r4, r4, #3
	mov	r0, #0
	ldrd	r6, [r6, #40]
	adds	r8, r8, r6
	adc	r9, r9, r7
	strd	r8, [r2]
	str	r4, [r3]
	ldr	r3, [fp, #4]
	str	ip, [r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L465:
	mov	r8, #3
	mov	r9, #0
	mov	r5, #0
	b	.L461
	UNWIND(.fnend)
	.size	AdjustRawPacketVP6A, .-AdjustRawPacketVP6A
	.align	2
	.global	SM_CopyRawToSeg
	.type	SM_CopyRawToSeg, %function
SM_CopyRawToSeg:
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
	ldr	r3, .L507
	mov	r2, r0
	str	r0, [fp, #-84]
	add	r3, r3, r2, lsl #3
	mov	r2, #0
	mov	r5, r1
	mov	r0, #0
	ldr	r4, [r3, #68]
	mov	r1, #0
	str	r2, [fp, #-64]
	cmp	r4, r2
	strd	r0, [fp, #-52]
	beq	.L487
	cmn	r4, #80
	add	r8, r4, #98304
	add	r2, r8, #104
	str	r2, [fp, #-80]
	movne	r3, #0
	moveq	r3, #1
	cmn	r8, #104
	add	r2, r4, #80
	str	r2, [fp, #-76]
	movne	r9, #0
	moveq	r9, #1
	orr	r3, r9, r3
	cmp	r5, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L487
	ldr	r10, [r8, #84]
	ldr	r3, [r8, #80]
	cmp	r10, r3
	beq	.L502
	mov	r2, r3, asl #5
	mov	r7, r3, asl #7
	rsb	r1, r2, r7
	mov	ip, #1
	add	r1, r4, r1
	str	r2, [fp, #-72]
	mov	lr, r2
	str	ip, [fp, #-56]
	mov	r2, r7
	ldr	r6, [r1, #92]
	b	.L471
.L473:
	add	ip, ip, #1
	ldr	r0, [r0, #92]
	cmp	ip, #1024
	add	r6, r6, r0
	movls	r1, #0
	movhi	r1, #1
	cmp	r3, r10
	orreq	r1, r1, #1
	cmp	r1, #0
	bne	.L502
.L471:
	rsb	r1, lr, r2
	add	r3, r3, #1
	add	r1, r4, r1
	ubfx	r3, r3, #0, #10
	ldrb	r1, [r1, #80]	@ zero_extendqisi2
	mov	lr, r3, asl #5
	mov	r2, r3, asl #7
	cmp	r1, #0
	rsb	r0, lr, r2
	add	r0, r4, r0
	bne	.L473
	cmp	r9, #0
	str	ip, [fp, #-56]
	addne	r3, r4, #262144
	bne	.L484
	ldr	r10, .L507+4
	mov	r2, #163840
	mov	r1, r9
	add	r0, r8, #112
	ldr	r3, [r10, #48]
	blx	r3
	add	r3, r4, #262144
	ldr	r2, [r3, #128]
	str	r9, [r3, #112]
	str	r9, [r3, #116]
	str	r9, [r3, #120]
	str	r2, [r3, #136]
	str	r2, [r3, #140]
.L484:
	ldr	r2, [r3, #132]
	cmp	r2, r6
	blt	.L505
	ldr	r2, [fp, #-72]
	ldr	r1, [r4, #16]
	rsb	r2, r2, r7
	ldr	r9, [r3, #128]
	add	r2, r4, r2
	ldr	r3, [r8, #80]
	sub	r1, r1, #12
	ldr	r8, [r8, #104]
	ldr	r0, [r2, #92]
	clz	r1, r1
	str	r3, [fp, #-60]
	cmp	r0, #0
	mov	r1, r1, lsr #5
	ldrd	r2, [r2, #120]
	moveq	r1, #0
	cmp	r1, #0
	str	r0, [fp, #-64]
	strd	r2, [fp, #-52]
	bne	.L476
.L479:
	str	r9, [r5, #12]
	mov	r0, r9
	bl	MEM_Phy2Vir
	ldr	r3, [fp, #-72]
	mov	r1, #1
	ldr	ip, [fp, #-56]
	rsb	r7, r3, r7
	add	r7, r4, r7
	cmp	ip, #0
	str	r0, [r5]
	rsb	r3, r0, r8
	str	r3, [r5, #16]
	ldrd	r2, [r7, #144]
	strd	r2, [r5, #24]
	ldrd	r2, [r7, #144]
	strd	r2, [r5, #32]
	ldrd	r2, [r7, #128]
	strb	r1, [r5, #5]
	strd	r2, [r5, #40]
	ldrd	r2, [r7, #136]
	strd	r2, [r5, #48]
	ldr	r3, [r7, #104]
	str	r3, [r5, #56]
	ldr	r3, [r7, #108]
	str	r3, [r5, #60]
	ldr	r3, [r7, #112]
	str	r3, [r5, #64]
	ldr	r3, [r7, #116]
	str	r3, [r5, #68]
	beq	.L478
	cmp	r8, #0
	beq	.L502
	ldrd	r2, [fp, #-52]
	orrs	r3, r2, r3
	ldrne	r10, .L507+4
	movne	r7, #0
	bne	.L481
	b	.L502
.L482:
	cmp	r8, #0
	beq	.L502
	orrs	r3, r0, r1
	beq	.L502
.L481:
	mov	r0, #2
	add	r7, r7, #1
	bl	VCTRL_RecordPosTime
	ldr	r3, [r10, #52]
	ldr	r2, [fp, #-64]
	mov	r0, r8
	ldr	r1, [fp, #-52]
	blx	r3
	mov	r0, #3
	bl	VCTRL_RecordPosTime
	ldr	r1, [fp, #-64]
	mov	r0, #0
	bl	VCTRL_RecordData
	ldr	r2, [fp, #-60]
	ldr	r1, [fp, #-64]
	add	r0, r2, #1
	ldr	ip, [fp, #-56]
	mov	r3, r2, asl #7
	ubfx	r0, r0, #0, #10
	sub	r2, r3, r2, asl #5
	str	r0, [fp, #-60]
	add	r2, r4, r2
	mov	r3, r0, asl #7
	sub	r3, r3, r0, asl #5
	add	r8, r8, r1
	ldrb	r0, [r2, #81]	@ zero_extendqisi2
	add	r3, r4, r3
	ldr	r2, [r5, #16]
	cmp	ip, r7
	strb	r0, [r5, #6]
	add	r1, r2, r1
	str	r1, [r5, #16]
	ldrd	r0, [r3, #120]
	ldr	r3, [r3, #92]
	strd	r0, [fp, #-52]
	str	r3, [fp, #-64]
	bhi	.L482
	ldr	r0, [r5]
.L478:
	cmp	r0, #0
	beq	.L506
	ldr	r2, [fp, #-84]
	mov	r1, r5
	ldr	r0, [fp, #-80]
	bl	InsertStreamSeg
	mov	r1, r6
	ldr	r0, [fp, #-76]
	bl	DeleteRawLen
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L505:
	mov	r2, r6
	ldr	r1, .L507+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r1, r6
	ldr	r0, [fp, #-76]
	bl	DeleteRawLen
	cmp	r0, #0
	beq	.L502
	movw	r2, #1561
	ldr	r1, .L507+12
	mov	r0, #0
	bl	dprint_vfmw
.L502:
	mvn	r0, #3
.L499:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L476:
	sub	r2, fp, #60
	sub	r3, fp, #64
	str	r2, [sp]
	sub	r1, fp, #56
	sub	r2, fp, #52
	ldr	r0, [fp, #-76]
	bl	AdjustRawPacketVP6A
	cmp	r0, #0
	beq	.L479
	b	.L502
.L487:
	mvn	r0, #0
	b	.L499
.L506:
	movw	r3, #1622
	ldr	r2, .L507+16
	ldr	r1, .L507+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #3
	b	.L499
.L508:
	.align	2
.L507:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC25
	.word	.LC26
	.word	.LANCHOR3+72
	.word	.LC27
	UNWIND(.fnend)
	.size	SM_CopyRawToSeg, .-SM_CopyRawToSeg
	.align	2
	.global	SCDDRV_IsSCDByPass
	.type	SCDDRV_IsSCDByPass, %function
SCDDRV_IsSCDByPass:
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
	beq	.L514
	sub	r3, r0, #2
	cmp	r0, #6
	cmpne	r3, #1
	movls	r3, #1
	movhi	r3, #0
	bls	.L513
	cmp	r0, #1
	beq	.L515
.L511:
	subs	r0, r0, #15
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L515:
	ldr	r2, [r1]
	cmp	r2, #0
	beq	.L511
.L514:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L513:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsSCDByPass, .-SCDDRV_IsSCDByPass
	.align	2
	.global	SCDDRV_SaveStreamSeg
	.type	SCDDRV_SaveStreamSeg, %function
SCDDRV_SaveStreamSeg:
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
	ldr	r5, .L518
	mov	r6, r0
	mov	r7, r1
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r4, .L518+4
	mov	r0, #0
	ldr	r3, [r4, #16]
	blx	r3
	ldr	r3, [r4, #44]
	ldr	r2, [r5, r6, asl #2]
	ldr	r1, [r7, #16]
	ldr	r0, [r7]
	blx	r3
	ldr	r3, [r4, #12]
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L519:
	.align	2
.L518:
	.word	vfmw_save_seg_file
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_SaveStreamSeg, .-SCDDRV_SaveStreamSeg
	.align	2
	.global	SM_ReadSegStream
	.type	SM_ReadSegStream, %function
SM_ReadSegStream:
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
	clz	r3, r1
	mov	r6, r0
	mov	r7, r1
	mov	r3, r3, lsr #5
	cmp	r0, #31
	orrhi	r3, r3, #1
	cmp	r3, #0
	bne	.L525
	ldr	r3, .L534
	add	r3, r3, r0, lsl #3
	ldr	r4, [r3, #68]
	cmp	r4, #0
	beq	.L525
	add	r1, r4, #32
	ldr	r0, [r4, #16]
	bl	SCDDRV_IsSCDByPass
	cmp	r0, #0
	bne	.L532
.L522:
	add	r0, r4, #98304
	mov	r1, r7
	add	r0, r0, #104
	add	r4, r4, #262144
	bl	SCDDRV_GetStreamSeg
	subs	r5, r0, #0
	beq	.L533
	ldr	r3, [r4, #276]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #276]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L532:
	mov	r1, r7
	mov	r0, r6
	bl	SM_CopyRawToSeg
	cmp	r0, #0
	beq	.L522
	add	r4, r4, #262144
	ldr	r1, .L534+4
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r3, [r4, #276]
	mvn	r0, #6
	add	r3, r3, #1
	str	r3, [r4, #276]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L533:
	mov	r0, r6
	mov	r1, r7
	str	r5, [r4, #276]
	bl	SCDDRV_SaveStreamSeg
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L525:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L535:
	.align	2
.L534:
	.word	.LANCHOR0
	.word	.LC28
	UNWIND(.fnend)
	.size	SM_ReadSegStream, .-SM_ReadSegStream
	.align	2
	.global	SM_ReleaseStreamSeg
	.type	SM_ReleaseStreamSeg, %function
SM_ReleaseStreamSeg:
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
	cmp	r0, #31
	bhi	.L537
	ldr	r3, .L541
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #68]
	cmp	r0, #0
	beq	.L537
	add	r0, r0, #98304
	add	r0, r0, #104
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseStreamSeg
.L537:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L542:
	.align	2
.L541:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_ReleaseStreamSeg, .-SM_ReleaseStreamSeg
	.align	2
	.global	SM_GiveThreadEvent
	.type	SM_GiveThreadEvent, %function
SM_GiveThreadEvent:
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
	ldr	r3, .L544
	mov	r0, #0
	ldr	r3, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L545:
	.align	2
.L544:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_GiveThreadEvent, .-SM_GiveThreadEvent
	.align	2
	.global	CalcInstBlockTime
	.type	CalcInstBlockTime, %function
CalcInstBlockTime:
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
	ldr	r3, .L551
	mov	r5, r1
	mov	r4, r0
	ldr	r3, [r3]
	blx	r3
	cmp	r5, #0
	add	r3, r4, #262144
	mov	r1, r0
	bne	.L550
	ldr	r2, [r3, #244]
	cmp	r0, r2
	strls	r5, [r3, #240]
	rsbhi	r0, r2, r0
	strls	r1, [r3, #244]
	strhi	r0, [r3, #240]
	movls	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L550:
	mov	r2, #0
	str	r1, [r3, #244]
	mov	r0, r2
	str	r2, [r3, #240]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L552:
	.align	2
.L551:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	CalcInstBlockTime, .-CalcInstBlockTime
	.align	2
	.global	SCDDRV_IsChanDec
	.type	SCDDRV_IsChanDec, %function
SCDDRV_IsChanDec:
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
	ldr	r3, .L556
	ldr	r2, [r3, #48]
	cmp	r2, #1
	ldreq	r3, [r3, #44]
	rsbeq	r0, r0, r3
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L557:
	.align	2
.L556:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_IsChanDec, .-SCDDRV_IsChanDec
	.align	2
	.global	SCDDRV_GetRawStreamStatus
	.type	SCDDRV_GetRawStreamStatus, %function
SCDDRV_GetRawStreamStatus:
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
	clz	r3, r0
	cmp	r0, #0
	cmpne	r1, #0
	mov	r3, r3, lsr #5
	beq	.L559
	add	lr, r0, #98304
	ldr	ip, [lr, #20]
	str	ip, [r1]
	ldr	lr, [lr, #12]
	rsb	ip, lr, ip
	str	ip, [r1]
.L559:
	cmp	r2, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	ldmnefd	sp, {fp, sp, pc}
	add	r0, r0, #98304
	ldmia	r0, {r1, r3}
	subs	r3, r3, r1
	addmi	r3, r3, #1024
	str	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_GetRawStreamStatus, .-SCDDRV_GetRawStreamStatus
	.align	2
	.global	GetFreeSegBufSize
	.type	GetFreeSegBufSize, %function
GetFreeSegBufSize:
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
	cmpne	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	GetFreeSegBufSize.part.6
	UNWIND(.fnend)
	.size	GetFreeSegBufSize, .-GetFreeSegBufSize
	.align	2
	.global	SCDDRV_GetSegStreamStatus
	.type	SCDDRV_GetSegStreamStatus, %function
SCDDRV_GetSegStreamStatus:
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
	clz	r5, r0
	cmp	r0, #0
	cmpne	r1, #0
	mov	r6, r2
	mov	r4, r0
	mov	r5, r5, lsr #5
	mov	r7, r1
	bne	.L573
.L568:
	ldr	r3, [r7]
	cmp	r3, #78
	subhi	r3, r3, #79
	movls	r3, #0
	cmp	r5, #0
	addeq	r0, r4, #163840
	str	r3, [r7]
	movne	r3, #2048
	ldreq	r3, [r0, #12]
	ldreq	r2, [r0, #8]
	rsbeq	r3, r2, r3
	ubfxeq	r3, r3, #0, #11
	rsbeq	r3, r3, #2048
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L573:
	bl	GetFreeSegBufSize.part.6
	b	.L568
	UNWIND(.fnend)
	.size	SCDDRV_GetSegStreamStatus, .-SCDDRV_GetSegStreamStatus
	.align	2
	.global	SCDDRV_IsRawStreamNotEnough
	.type	SCDDRV_IsRawStreamNotEnough, %function
SCDDRV_IsRawStreamNotEnough:
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
	cmpne	r0, #3
	movls	r0, #1
	movhi	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsRawStreamNotEnough, .-SCDDRV_IsRawStreamNotEnough
	.align	2
	.global	SCDDRV_IsFreeSegSlotNotEnough
	.type	SCDDRV_IsFreeSegSlotNotEnough, %function
SCDDRV_IsFreeSegSlotNotEnough:
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
	cmp	r0, #512
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsFreeSegSlotNotEnough, .-SCDDRV_IsFreeSegSlotNotEnough
	.align	2
	.global	SCDDRV_IsFreeSegBufNotEnough
	.type	SCDDRV_IsFreeSegBufNotEnough, %function
SCDDRV_IsFreeSegBufNotEnough:
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
	cmp	r0, r1, lsr #3
	movls	r0, #1
	movhi	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_IsFreeSegBufNotEnough, .-SCDDRV_IsFreeSegBufNotEnough
	.align	2
	.global	SCDDRV_CheckConditionOfStartSCD
	.type	SCDDRV_CheckConditionOfStartSCD, %function
SCDDRV_CheckConditionOfStartSCD:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
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
	mov	r5, r2
	sub	r2, fp, #28
	mov	ip, #0
	mov	r4, r1
	mov	r1, r5
	str	ip, [r2, #-4]!
	mov	r6, r3
	bl	SCDDRV_GetRawStreamStatus
	ldr	r2, [r5]
	ldr	r3, [fp, #-32]
	cmp	r3, #0
	cmpne	r2, #3
	bls	.L579
	ldr	r2, [fp, #4]
	mov	r1, r6
	mov	r0, r4
	bl	SCDDRV_GetSegStreamStatus
	ldr	r3, [fp, #4]
	ldr	r3, [r3]
	cmp	r3, #512
	bls	.L580
	add	r4, r4, #163840
	ldr	r3, [r6]
	ldr	r2, [r4, #28]
	cmp	r3, r2, lsr #3
	mvnls	r0, #5
	movhi	r0, #0
.L578:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L579:
	mvn	r0, #4
	b	.L578
.L580:
	mvn	r0, #5
	b	.L578
	UNWIND(.fnend)
	.size	SCDDRV_CheckConditionOfStartSCD, .-SCDDRV_CheckConditionOfStartSCD
	.align	2
	.global	SCDDRV_SetCtrlReg
	.type	SCDDRV_SetCtrlReg, %function
SCDDRV_SetCtrlReg:
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
	add	r3, r0, #262144
	ldr	ip, [r0, #16]
	mov	lr, #1
	strb	lr, [r1, #2]
	ldr	r2, [r3, #184]
	sub	r4, ip, #6
	clz	r4, r4
	cmp	ip, lr
	cmpne	ip, #15
	str	r2, [r1, #4]
	mov	r4, r4, lsr #5
	ldr	r2, [r3, #176]
	str	r2, [r1, #8]
	ldr	r2, [r3, #192]
	str	r2, [r1, #16]
	ldr	r5, [r3, #200]
	ldr	r2, [r3, #284]
	mul	r2, r2, r5
	str	r2, [r1, #20]
	ldr	r2, [r3, #128]
	str	r2, [r1, #24]
	ldr	r2, [r3, #132]
	ldr	r5, [r3, #128]
	add	r2, r2, r5
	str	r2, [r1, #28]
	ldr	r2, [r3, #140]
	strb	lr, [r1]
	add	r2, r2, #3
	bic	r2, r2, #3
	str	r2, [r1, #32]
	ldr	r2, [r0, #44]
	str	r4, [r1, #60]
	str	r2, [r1, #44]
	beq	.L587
	cmp	r4, #0
	bne	.L585
	sub	r2, ip, #2
	cmp	r2, lr
	bhi	.L583
.L585:
	strb	lr, [r1, #1]
	b	.L586
.L587:
	mov	ip, #0
.L583:
	mov	r2, #0
	strb	r2, [r1, #1]
.L586:
	mov	r2, #1
	str	ip, [r1, #36]
	str	r2, [r1, #40]
	str	r2, [r1, #48]
	str	r2, [r1, #52]
	ldr	r3, [r3, #432]
	str	r3, [r1, #56]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	SCDDRV_SetCtrlReg, .-SCDDRV_SetCtrlReg
	.align	2
	.global	SCDDRV_RecordStartState
	.type	SCDDRV_RecordStartState, %function
SCDDRV_RecordStartState:
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
	add	r4, r0, #262144
	cmp	r1, r2
	str	r1, [r4, #256]
	movls	r3, #1
	str	r2, [r4, #260]
	movhi	r3, #0
	strb	r3, [r0, #2]
	mov	r1, #1
	ldr	r3, .L591
	mov	r2, #0
	str	r1, [r4, #220]
	strb	r2, [r0, #3]
	ldr	r3, [r3]
	blx	r3
	str	r0, [r4, #280]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L592:
	.align	2
.L591:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_RecordStartState, .-SCDDRV_RecordStartState
	.align	2
	.global	SCD_ConfigReg
	.type	SCD_ConfigReg, %function
SCD_ConfigReg:
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
	ldr	ip, .L600
	mov	r5, r0
	mov	r0, r3
	ldrb	r3, [ip]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L599
	cmp	r5, #4
	beq	.L598
	ldr	r6, .L600+4
	mov	r4, r2, asl #2
.L595:
	add	r2, r6, r4
	ldr	r0, [r2, #64]
	add	r0, r5, r0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MEM_WritePhyWord
.L599:
	mov	r3, r1
	mov	r2, r5
	mov	r1, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Record_RegData
.L598:
	ldr	r6, .L600+4
	mov	r4, r2, asl #2
	cmp	r1, #0
	add	r3, r6, r4
	ldr	r0, [r3, #64]
	add	r0, r0, #4
	bne	.L596
	bl	MEM_ReadPhyWord
	uxth	r1, r0
	b	.L595
.L596:
	bl	MEM_ReadPhyWord
	orr	r1, r0, #65536
	b	.L595
.L601:
	.align	2
.L600:
	.word	g_HalDisable
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCD_ConfigReg, .-SCD_ConfigReg
	.align	2
	.global	WriteScdVtrlReg
	.type	WriteScdVtrlReg, %function
WriteScdVtrlReg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 192
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #192)
	sub	sp, sp, #192
	ldr	r5, .L641
	mov	r8, r0
	mov	r4, r1
	mov	r6, r2
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L603
	ldr	r3, .L641+4
	sub	r0, fp, #224
	mov	r2, #188
	mov	r1, #0
	mov	r7, r0
	ldr	r3, [r3, #48]
	blx	r3
.L604:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #4]
	cmp	r2, #1
	bne	.L629
	ldr	r2, .L641+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2048
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #16]
	cmp	r2, #1
	bne	.L630
.L607:
	ldr	r2, .L641+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2048
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #20]
	cmp	r2, #1
	bne	.L631
.L609:
	ldr	r2, .L641+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2048
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #24]
	cmp	r2, #1
	bne	.L632
.L611:
	ldr	r2, .L641+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2064
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #28]
	cmp	r2, #1
	bne	.L633
.L613:
	ldr	r2, .L641+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2064
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #32]
	cmp	r2, #1
	bne	.L634
.L615:
	ldr	r2, .L641+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2064
	add	r0, r0, #8
	bl	MEM_WritePhyWord
.L616:
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #44]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	mov	r1, r1, asl #9
	ldr	r2, [r4, #36]
	orr	r1, r1, r0, asl #8
	ldrb	r0, [r5]	@ zero_extendqisi2
	and	r2, r2, #15
	mov	r3, r3, asl #4
	cmp	r0, #1
	orr	r1, r1, r2
	and	r3, r3, #16
	orr	r1, r1, r3
	bne	.L635
	ldr	r3, .L641+8
	add	r3, r3, r6, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2080
	bl	MEM_WritePhyWord
	ldr	r3, [r4, #44]
	cmp	r3, #0
	bne	.L636
.L619:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L637
	ldr	r3, .L641+8
	mov	r1, #0
	ldr	r9, .L641
	add	r3, r3, r6, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldrb	r5, [r5]	@ zero_extendqisi2
	cmp	r5, #1
	beq	.L623
.L638:
	ldr	r2, [r4, #44]
	sub	r0, fp, #224
	mov	r3, #0
	str	r8, [fp, #-216]
	strb	r6, [fp, #-224]
	strb	r2, [fp, #-223]
	str	r3, [fp, #-220]
	bl	VDH_PostTask
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L629:
	mov	r3, r1
	movw	r2, #2052
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #16]
	cmp	r2, #1
	beq	.L607
.L630:
	mov	r3, r1
	movw	r2, #2056
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #20]
	cmp	r2, #1
	beq	.L609
.L631:
	mov	r3, r1
	movw	r2, #2060
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #24]
	cmp	r2, #1
	beq	.L611
.L632:
	mov	r3, r1
	mov	r2, #2064
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #28]
	cmp	r2, #1
	beq	.L613
.L633:
	mov	r3, r1
	movw	r2, #2068
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #32]
	cmp	r2, #1
	beq	.L615
.L634:
	mov	r3, r1
	movw	r2, #2072
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	b	.L616
.L637:
	mov	r3, #0
	movw	r2, #2076
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldrb	r5, [r5]	@ zero_extendqisi2
	ldr	r9, .L641
	cmp	r5, #1
	bne	.L638
.L623:
	ldr	r3, .L641+8
	mov	r1, #0
	add	r6, r3, r6, lsl #2
	ldr	r0, [r6, #64]
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
	ldrb	r3, [r9]	@ zero_extendqisi2
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #1
	and	r1, r1, #1
	bne	.L639
	ldr	r0, [r6, #64]
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L635:
	mov	r3, r1
	mov	r2, #2080
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	ldr	r3, [r4, #44]
	cmp	r3, #0
	beq	.L619
.L636:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #60]
	cmp	r2, #1
	bne	.L640
	ldr	r2, .L641+8
	add	r3, r2, r6, lsl #2
	ldr	r0, [r3, #64]
	bl	MEM_WritePhyWord
	b	.L619
.L603:
	mov	r0, r2
	mov	r7, #0
	bl	ResetSCD
	b	.L604
.L640:
	mov	r3, r1
	mov	r2, #0
	mov	r1, #1
	mov	r0, r7
	bl	VDH_Record_RegData
	b	.L619
.L639:
	mov	r3, r1
	mov	r0, r7
	mov	r1, r5
	mov	r2, #2048
	bl	VDH_Record_RegData
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L642:
	.align	2
.L641:
	.word	g_HalDisable
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	WriteScdVtrlReg, .-WriteScdVtrlReg
	.align	2
	.global	WriteScdMsg
	.type	WriteScdMsg, %function
WriteScdMsg:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 104
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #108)
	sub	sp, sp, #108
	mov	r4, r1
	str	r1, [fp, #-144]
	mov	r8, r2
	mov	r1, #0
	mov	r2, #96
	mov	r9, r0
	sub	r0, fp, #140
	mov	r7, r3
	bl	memset
	sub	r1, fp, #140
	mov	r0, r8
	bl	GetFirstRawPacket
	ldr	r3, [fp, #-128]
	cmp	r3, r4
	mov	r10, r3
	bgt	.L644
	mov	r4, #0
	add	r6, r8, #98304
	mov	r5, r4
.L647:
	cmp	r3, #0
	mov	r2, r4, asl #2
	add	r1, r7, r2
	add	r2, r2, #12
	ble	.L645
	ldr	ip, [fp, #-136]
	ldr	r0, [fp, #4]
	str	ip, [r7, r4, asl #2]
	add	r4, r4, #3
	add	r2, r2, r0
	sub	r0, ip, #1
	str	r2, [r1, #8]
	add	r2, r0, r3
	str	r2, [r1, #4]
.L645:
	str	r10, [r9, #4]
	add	r5, r5, #1
	ldr	ip, [r6, #16]
	cmp	ip, #1024
	bcc	.L660
.L646:
	ldr	r2, [fp, #8]
	cmp	r2, #0
	bne	.L648
	ldr	r1, [fp, #-144]
	ldr	r2, [r9, #4]
	sub	r1, r1, #16
	cmp	r2, r1
	blt	.L653
.L648:
	cmp	r5, #0
	beq	.L652
	cmp	r4, #0
	mov	r0, #0
	subgt	r4, r4, #-1073741823
	movgt	r3, #0
	strgt	r3, [r7, r4, asl #2]
	mov	r3, #1
	str	r5, [r9]
	str	r3, [r9, #8]
.L659:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L660:
	ldr	lr, [r6, #4]
	mov	r1, ip, asl #7
	sub	r1, r1, ip, asl #5
	mov	r2, #96
	cmp	ip, lr
	sub	r0, fp, #140
	add	r1, r8, r1
	beq	.L646
	ldr	r3, .L661
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r2, [r6, #16]
	ldr	r3, [fp, #-128]
	ldr	r0, [fp, #-144]
	add	r2, r2, #1
	add	r10, r10, r3
	cmp	r0, r10
	mov	r1, r2, asr #31
	movge	r0, #1
	movlt	r0, #0
	cmp	r5, #1024
	mov	r1, r1, lsr #22
	add	r2, r2, r1
	movge	r0, #0
	cmp	r0, #0
	ubfx	r2, r2, #0, #10
	rsb	r2, r1, r2
	str	r2, [r6, #16]
	bne	.L647
	b	.L646
.L644:
	ldr	r2, [fp, #8]
	cmp	r2, #0
	bne	.L652
	ldr	r1, [fp, #-144]
	ldr	r2, [r9, #4]
	sub	r1, r1, #16
	cmp	r2, r1
	bge	.L652
	ldr	r4, [fp, #8]
	mov	r5, r4
.L653:
	ldr	r1, [fp, #-144]
	cmp	r1, r10
	cmplt	r5, #1024
	bge	.L648
	rsb	r2, r2, r1
	cmp	r3, r2
	blt	.L648
	mov	r3, r4, asl #2
	ldr	ip, [fp, #-136]
	ldr	r1, [fp, #4]
	add	r0, r3, #12
	add	r3, r7, r3
	add	r5, r5, #1
	add	r0, r0, r1
	sub	r1, ip, #1
	str	ip, [r7, r4, asl #2]
	add	r1, r1, r2
	str	r0, [r3, #8]
	add	r4, r4, #3
	str	r1, [r3, #4]
	ldr	r3, [r9, #4]
	add	r2, r3, r2
	str	r2, [r9, #4]
	b	.L648
.L652:
	mvn	r0, #5
	b	.L659
.L662:
	.align	2
.L661:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	WriteScdMsg, .-WriteScdMsg
	.align	2
	.global	SCDDRV_StartSCD
	.type	SCDDRV_StartSCD, %function
SCDDRV_StartSCD:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	add	r4, r1, #262144
	mov	r5, r3
	ldr	r9, .L665
	ldr	r3, [r4, #184]
	add	r7, r4, #160
	mov	r6, r1
	mov	r8, r0
	mov	r10, r2
	mov	r1, #0
	str	r3, [fp, #-48]
	mov	r2, #12
	ldr	r3, [r4, #176]
	mov	r0, r7
	ldr	ip, [r9, #48]
	str	r3, [fp, #-52]
	blx	ip
	ldr	ip, [r8, #44]
	add	r2, r6, #80
	ldr	r3, [fp, #-48]
	mov	r0, r7
	str	r5, [sp, #8]
	mov	r1, r10
	str	ip, [sp, #4]
	str	r3, [sp]
	ldr	r3, [fp, #-52]
	bl	WriteScdMsg
	subs	r6, r0, #0
	bne	.L664
	ldr	r3, [r9]
	blx	r3
	mov	r3, r5, asl #6
	ldr	ip, .L665+4
	sub	r3, r3, r5, asl #2
	mov	r1, r8
	mov	r2, r5
	add	r3, ip, r3
	str	r0, [r3, #48]
	ldr	r0, [r4, #212]
	bl	WriteScdVtrlReg
.L664:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L666:
	.align	2
.L665:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	UNWIND(.fnend)
	.size	SCDDRV_StartSCD, .-SCDDRV_StartSCD
	.align	2
	.global	CutStreamWithSCD
	.type	CutStreamWithSCD, %function
CutStreamWithSCD:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #88)
	sub	sp, sp, #88
	sub	r3, fp, #28
	mov	r7, r1
	add	r1, r0, #98304
	mov	ip, #0
	sub	r2, fp, #100
	str	ip, [r3, #-68]!
	mov	r5, r0
	str	r2, [sp]
	add	r1, r1, #104
	add	r0, r0, #80
	sub	r2, fp, #104
	str	ip, [fp, #-104]
	str	ip, [fp, #-100]
	bl	SCDDRV_CheckConditionOfStartSCD
	subs	r4, r0, #0
	bne	.L674
	add	r6, r5, #262144
	mov	r1, r7
	ldr	r0, [r6, #212]
	bl	SM_CfgBuf
	subs	r4, r0, #0
	bne	.L675
	ldr	r2, [fp, #-100]
	mov	r0, r5
	ldr	r3, [r6, #284]
	sub	r1, fp, #92
	str	r2, [r6, #200]
	mul	r3, r3, r2
	mov	r3, r3, asl #2
	str	r3, [r6, #196]
	bl	SCDDRV_SetCtrlReg
	ldr	r2, [fp, #-96]
	mov	r3, r7
	sub	r0, fp, #92
	mov	r1, r5
	bl	SCDDRV_StartSCD
	cmp	r0, #0
	movne	r2, r0
	bne	.L669
	ldr	r3, [fp, #-96]
	mov	r2, #1
	ldr	r1, [fp, #-104]
	mov	r4, #0
	cmp	r1, r3
	str	r3, [r6, #260]
	str	r1, [r6, #256]
	movls	r3, #1
	strlsb	r3, [r5, #2]
	ldr	r3, .L676
	strhib	r0, [r5, #2]
	str	r2, [r6, #220]
	strb	r4, [r5, #3]
	ldr	r3, [r3]
	blx	r3
	mov	r2, r4
	str	r0, [r6, #280]
.L669:
	mov	r0, r2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L675:
	mov	r2, r4
	ldr	r1, .L676+4
	mov	r0, #26
	bl	dprint_vfmw
	mov	r2, r4
	mov	r0, r2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L674:
	mov	r2, r4
	ldr	r1, .L676+8
	mov	r0, #26
	bl	dprint_vfmw
	mov	r2, r4
	mov	r0, r2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L677:
	.align	2
.L676:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	CutStreamWithSCD, .-CutStreamWithSCD
	.align	2
	.global	ReadScdStateReg
	.type	ReadScdStateReg, %function
ReadScdStateReg:
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
	ldr	r4, .L679
	mov	r5, r0
	movw	r6, #2124
	add	r4, r4, r1, lsl #2
	ldr	r0, [r4, #64]
	add	r0, r0, #2112
	bl	MEM_ReadPhyWord
	and	r0, r0, #1
	str	r0, [r5]
	ldr	r0, [r4, #64]
	add	r0, r0, #2112
	add	r0, r0, #4
	bl	MEM_ReadPhyWord
	ldr	r2, [r4, #64]
	and	r3, r0, #1
	add	r0, r6, r2
	str	r3, [r5, #4]
	bl	MEM_ReadPhyWord
	ldr	r2, [r4, #64]
	mov	r3, r0, lsr #22
	add	r0, r6, r2
	str	r3, [r5, #8]
	bl	MEM_ReadPhyWord
	ldr	r2, [r4, #64]
	ubfx	r3, r0, #0, #22
	add	r0, r2, #2128
	str	r3, [r5, #12]
	bl	MEM_ReadPhyWord
	ldr	r3, [r4, #64]
	str	r0, [r5, #16]
	add	r0, r3, #2128
	add	r0, r0, #4
	bl	MEM_ReadPhyWord
	ldr	r3, [r4, #64]
	str	r0, [r5, #20]
	add	r0, r3, #2048
	add	r0, r0, #12
	bl	MEM_ReadPhyWord
	str	r0, [r5, #24]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L680:
	.align	2
.L679:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	ReadScdStateReg, .-ReadScdStateReg
	.align	2
	.global	ParseMpeg4UniqueUpMsg
	.type	ParseMpeg4UniqueUpMsg, %function
ParseMpeg4UniqueUpMsg:
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
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r0, #1
	bfceq	r3, #0, #1
	orrne	r3, r3, #1
	strb	r3, [r1]
	ldr	r3, [r2]
	ldrb	r0, [r1]	@ zero_extendqisi2
	mov	r3, r3, lsr #31
	bfi	r0, r3, #1, #1
	strb	r0, [r1]
	ldrh	r0, [r2, #10]
	ldrb	r3, [r1]	@ zero_extendqisi2
	bfi	r3, r0, #2, #1
	strb	r3, [r1]
	ldr	r3, [r2, #8]
	ldrb	r0, [r1]	@ zero_extendqisi2
	ubfx	r3, r3, #4, #3
	bfi	r0, r3, #3, #4
	strb	r0, [r1]
	ldr	r3, [r2, #8]
	ldrh	r2, [r1]
	and	r3, r3, #7
	bfi	r2, r3, #7, #4
	strh	r2, [r1]	@ movhi
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	ParseMpeg4UniqueUpMsg, .-ParseMpeg4UniqueUpMsg
	.align	2
	.global	ConvertByteOrder
	.type	ConvertByteOrder, %function
ConvertByteOrder:
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
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r1, [r0, #3]	@ zero_extendqisi2
	mov	r2, r2, asl #16
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	orr	r3, r2, r3, asl #24
	orr	r3, r3, r1
	orr	r0, r3, r0, asl #8
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	ConvertByteOrder, .-ConvertByteOrder
	.align	2
	.global	CheckSegValid
	.type	CheckSegValid, %function
CheckSegValid:
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
	cmp	r0, #0
	beq	.L690
	ldr	r3, [r0, #12]
	cmp	r3, #0
	beq	.L692
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L692
	cmp	r1, #0
	beq	.L687
	add	r1, r1, #163840
	ldr	r2, [r1, #36]
	ldr	r3, [r1, #32]
	cmp	r2, r3
	bls	.L688
	ldr	r1, [r1, #28]
	sub	r3, r3, #1
	add	r3, r3, r1
	rsb	r1, r2, r3
.L687:
	ldr	r3, [r0, #16]
	cmp	r3, r1
	mvnhi	r0, #6
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L688:
	ldrcs	r1, [r1, #28]
	subcc	r3, r3, #1
	rsbcc	r1, r2, r3
	subcs	r1, r1, #1
	b	.L687
.L692:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L690:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CheckSegValid, .-CheckSegValid
	.align	2
	.global	GetSegPts
	.type	GetSegPts, %function
GetSegPts:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	mov	r4, r3
	mov	r5, r2
	sub	r3, fp, #36
	sub	r2, fp, #32
	str	r2, [sp]
	sub	r2, fp, #40
	mov	ip, #0
	mov	r6, r0
	str	ip, [fp, #-40]
	str	ip, [fp, #-36]
	str	ip, [fp, #-32]
	bl	GetRawNumOffset
	ldr	r0, [fp, #-32]
	mov	r3, r0, asl #7
	sub	r0, r3, r0, asl #5
	add	r0, r6, r0
	ldrd	r6, [r0, #64]
	strd	r6, [r4, #24]
	ldrd	r2, [r0, #48]
	strd	r2, [r4, #40]
	ldrd	r2, [r0, #64]
	strd	r2, [r4, #32]
	ldrd	r2, [r0, #56]
	strd	r2, [r4, #48]
	ldr	r3, [r0, #24]
	str	r3, [r4, #56]
	ldr	r3, [r0, #28]
	str	r3, [r4, #60]
	ldr	r3, [r0, #32]
	str	r3, [r4, #64]
	ldr	r3, [r0, #36]
	str	r3, [r4, #68]
	ldrb	r3, [r0, #92]	@ zero_extendqisi2
	strb	r3, [r4, #7]
	ldrd	r2, [r5]
	cmp	r7, r3
	cmpeq	r6, r2
	beq	.L698
.L696:
	strd	r6, [r5]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L698:
	ldr	r3, .L699
	ldr	r2, [fp, #4]
	ldr	r3, [r3, r2, asl #2]
	add	r3, r3, #294912
	ldr	r3, [r3, #1212]
	cmp	r3, #0
	bne	.L696
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [r4, #24]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L700:
	.align	2
.L699:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	GetSegPts, .-GetSegPts
	.align	2
	.global	IsVopHeader
	.type	IsVopHeader, %function
IsVopHeader:
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
	cmp	r0, #1
	beq	.L706
	cmp	r0, #2
	movne	r0, #0
	beq	.L707
.L703:
	mov	r2, #0
	movt	r2, 65025
	cmp	r1, r2
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L706:
	mov	r3, #0
	movt	r3, 46593
	rsb	r0, r3, r1
	clz	r0, r0
	mov	r0, r0, lsr #5
	b	.L703
.L707:
	ubfx	r3, r1, #16, #8
	sub	r3, r3, #128
	cmp	r3, #3
	movhi	r0, #0
	movls	r0, #1
	b	.L703
	UNWIND(.fnend)
	.size	IsVopHeader, .-IsVopHeader
	.align	2
	.global	CorrectSegPhyAddr
	.type	CorrectSegPhyAddr, %function
CorrectSegPhyAddr:
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
	cmp	r1, r0
	orrcc	r0, r1, #-2147483648
	movcs	r0, r1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CorrectSegPhyAddr, .-CorrectSegPhyAddr
	.align	2
	.global	GetNextVop
	.type	GetNextVop, %function
GetNextVop:
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
	add	r4, r0, #98304
	cmn	r4, #104
	addne	ip, r0, #262144
	moveq	r9, #2048
	ldrne	r9, [ip, #112]
	ldrne	r3, [ip, #116]
	sub	ip, r2, #1
	rsbne	r9, r9, r3
	mov	lr, ip
	ubfxne	r9, r9, #0, #11
	rsbne	r9, r9, #2048
	cmp	ip, #0
	blt	.L722
	add	r0, r0, #262144
	mov	r6, #0
	mov	r10, r6
	ldr	r8, [r4, #104]
	ldr	r7, [r0, #284]
	movt	r6, 65025
	ldr	r4, [r0, #128]
	movt	r10, 46593
	ldr	r5, [r0, #232]
	mov	r7, r7, asl #2
	mla	r1, r7, ip, r1
	b	.L720
.L725:
	cmp	r5, #2
	beq	.L724
	cmp	r3, r6
	beq	.L718
.L719:
	sub	lr, lr, #1
	rsb	r1, r7, r1
	cmn	lr, #1
	mov	r2, ip
	beq	.L722
	sub	ip, ip, #1
.L720:
	ldr	r3, [r1]
	bic	r3, r3, #-2147483648
	cmp	r3, r4
	orrcc	r3, r3, #-2147483648
	cmp	r5, #1
	rsb	r3, r4, r3
	ldr	r3, [r8, r3]
	rsbeq	r2, r10, r3
	clzeq	r2, r2
	moveq	r2, r2, lsr #5
	bne	.L725
.L716:
	cmp	r3, r6
	beq	.L718
	cmp	r2, #1
	bne	.L719
.L718:
	cmp	ip, r9
	mov	r2, ip
	bls	.L722
	sub	ip, ip, #1
	b	.L719
.L724:
	ubfx	r2, r3, #16, #8
	sub	r2, r2, #128
	cmp	r2, #3
	movhi	r2, #0
	movls	r2, #1
	b	.L716
.L722:
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetNextVop, .-GetNextVop
	.align	2
	.global	SetPushRawOverState
	.type	SetPushRawOverState, %function
SetPushRawOverState:
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
	ldr	r3, [r0, #8]
	str	r1, [r0, #8]
	cmp	r1, #2
	cmpeq	r3, #3
	moveq	r3, #1
	movne	r3, #0
	mvneq	r3, #6
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SetPushRawOverState, .-SetPushRawOverState
	.align	2
	.global	ProcessExceptionalStartCodeNum
	.type	ProcessExceptionalStartCodeNum, %function
ProcessExceptionalStartCodeNum:
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
	mov	r2, #2352
	mov	r4, r0
	mov	r3, r1
	mov	r0, #0
	ldr	r1, .L730
	bl	dprint_vfmw
	add	r0, r4, #80
	mov	r1, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DeleteRawPacket
.L731:
	.align	2
.L730:
	.word	.LC31
	UNWIND(.fnend)
	.size	ProcessExceptionalStartCodeNum, .-ProcessExceptionalStartCodeNum
	.global	__aeabi_uidiv
	.align	2
	.global	GetValidStartCodeNum
	.type	GetValidStartCodeNum, %function
GetValidStartCodeNum:
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
	ldr	r0, [r0, #24]
	bl	__aeabi_uidiv
	ldr	r3, [r4, #12]
	cmp	r0, r3
	movcs	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetValidStartCodeNum, .-GetValidStartCodeNum
	.align	2
	.global	ProcessNoSeg
	.type	ProcessNoSeg, %function
ProcessNoSeg:
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
	add	r3, r0, #262144
	mov	r4, r0
	ldr	r2, [r3, #256]
	ldr	r0, [r3, #260]
	ldr	r5, [r3, #164]
	cmp	r2, r0
	movle	r2, #0
	movgt	r2, #1
	cmp	r1, #0
	strb	r2, [r4]
	bne	.L734
	cmp	r5, #3
	subhi	r1, r5, #3
.L735:
	add	r0, r4, #80
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DeleteRawLen
.L734:
	ldr	r2, [r3, #188]
	ldr	r3, [r3, #132]
	ldr	r1, [r2, #4]
	add	r3, r3, r3, lsl #1
	add	r2, r3, #3
	cmp	r3, #0
	bic	r1, r1, #-2147483648
	movlt	r3, r2
	rsb	r2, r1, r5
	cmp	r2, r3, asr #2
	bls	.L735
	ldr	r1, .L737
	mov	r0, #0
	bl	dprint_vfmw
	mov	r1, r5
	add	r0, r4, #80
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DeleteRawLen
.L738:
	.align	2
.L737:
	.word	.LC32
	UNWIND(.fnend)
	.size	ProcessNoSeg, .-ProcessNoSeg
	.align	2
	.global	ProcessNotMpeg4ScdUpMsg
	.type	ProcessNotMpeg4ScdUpMsg, %function
ProcessNotMpeg4ScdUpMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 120
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	add	r5, r0, #262144
	str	r1, [fp, #-132]
	mov	r3, r0
	ldr	r1, [r5, #284]
	add	r10, r0, #98304
	str	r2, [fp, #-152]
	sub	r0, fp, #124
	ldr	r2, [r5, #188]
	add	r9, r10, #104
	str	r1, [fp, #-156]
	mov	r1, r1, asl #2
	str	r1, [fp, #-140]
	mov	lr, r1
	mov	r1, #0
	mov	ip, r2
	str	r2, [fp, #-160]
	mov	r8, r1
	mov	r2, #80
	add	lr, ip, lr
	add	r3, r3, r2
	str	lr, [fp, #-136]
	mov	r6, ip
	str	r3, [fp, #-144]
	mov	r7, r8
	bl	memset
	b	.L740
.L759:
	rsb	r3, r1, r4
	ldr	r2, [r10, #104]
	cmp	r3, #3
	rsb	r0, r0, r1
	add	r0, r2, r0
	str	r3, [fp, #-108]
	mov	r2, #1
	str	r1, [fp, #-112]
	str	r0, [fp, #-124]
	strb	r2, [fp, #-119]
	ble	.L758
	mov	r1, r9
	sub	r0, fp, #124
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L749
	ldr	ip, [r5, #212]
	sub	r3, fp, #124
	ldr	r1, [r6, #4]
	add	r2, r5, #248
	ldr	r0, [fp, #-144]
	str	ip, [sp]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r5, #212]
	sub	r1, fp, #124
	mov	r0, r9
	bl	InsertStreamSeg
	cmp	r0, #0
	bne	.L749
.L745:
	ldr	r3, [fp, #-140]
	ldr	r7, [fp, #-128]
	add	r6, r6, r3
	add	r8, r8, r3
.L740:
	ldr	r3, [fp, #-132]
	cmp	r7, r3
	beq	.L749
	ldr	r3, [fp, #-136]
	ldr	r1, [r6]
	ldr	r0, [r5, #128]
	ldr	r4, [r3, r8]
	bic	r1, r1, #-2147483648
	cmp	r0, r1
	add	r3, r7, #1
	bic	r4, r4, #-2147483648
	orrhi	r1, r1, #-2147483648
	cmp	r0, r4
	str	r3, [fp, #-128]
	orrhi	r4, r4, #-2147483648
	cmp	r1, r4
	bls	.L759
	ldr	r3, [fp, #-152]
	cmp	r9, #0
	rsb	r4, r0, r4
	rsb	r2, r1, r3
	add	r3, r4, r2
	beq	.L750
	ldr	ip, [r5, #112]
	cmp	r3, #3
	ldr	r0, [r5, #116]
	ldr	lr, [r5, #128]
	rsb	r0, ip, r0
	ldr	ip, [r10, #104]
	ubfx	r0, r0, #0, #11
	rsb	lr, lr, r1
	str	r1, [fp, #-112]
	rsb	r0, r0, #2048
	add	r1, ip, lr
	str	r3, [fp, #-108]
	str	r1, [fp, #-124]
	ble	.L754
	cmp	r0, #2
	bls	.L749
.L755:
	mov	r1, r9
	sub	r0, fp, #124
	str	r2, [fp, #-148]
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L749
	cmp	r4, #0
	ldr	ip, [r5, #212]
	ldr	r2, [fp, #-148]
	bne	.L752
	str	r2, [fp, #-108]
	mov	r1, #1
	strb	r1, [fp, #-119]
	add	r2, r5, #248
	ldr	r1, [r6, #4]
	sub	r3, fp, #124
	ldr	r0, [fp, #-144]
	str	ip, [sp]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r5, #212]
	sub	r1, fp, #124
	mov	r0, r9
	bl	InsertStreamSeg
	b	.L745
.L752:
	str	r2, [fp, #-108]
	sub	r3, fp, #124
	strb	r0, [fp, #-119]
	add	r2, r5, #248
	ldr	r1, [r6, #4]
	ldr	r0, [fp, #-144]
	str	ip, [sp]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r5, #212]
	sub	r1, fp, #124
	mov	r0, r9
	bl	InsertStreamSeg
	ldr	lr, [r5, #128]
	ldr	ip, [r10, #104]
	sub	r1, fp, #124
	ldr	r2, [r5, #212]
	mov	r0, r9
	mov	r3, #1
	str	r4, [fp, #-108]
	str	lr, [fp, #-112]
	str	ip, [fp, #-124]
	strb	r3, [fp, #-119]
	bl	InsertStreamSeg
	b	.L745
.L750:
	ldr	ip, [r10, #104]
	cmp	r3, #3
	rsb	r0, r0, r1
	str	r1, [fp, #-112]
	add	r0, ip, r0
	str	r3, [fp, #-108]
	str	r0, [fp, #-124]
	bgt	.L755
.L754:
	movw	r2, #2452
	ldr	r1, .L760
	mov	r0, #0
	bl	dprint_vfmw
	b	.L745
.L758:
	movw	r2, #2421
	ldr	r1, .L760
	mov	r0, #0
	bl	dprint_vfmw
	b	.L745
.L749:
	cmp	r7, #0
	ble	.L739
	ldr	r3, [fp, #-156]
	ldr	r0, [fp, #-144]
	mul	r7, r3, r7
	ldr	r3, [fp, #-160]
	add	r7, r7, #1
	ldr	r1, [r3, r7, asl #2]
	bic	r1, r1, #-2147483648
	bl	DeleteRawLen
.L739:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L761:
	.align	2
.L760:
	.word	.LC33
	UNWIND(.fnend)
	.size	ProcessNotMpeg4ScdUpMsg, .-ProcessNotMpeg4ScdUpMsg
	.align	2
	.global	GetMpeg4ModeFlag
	.type	GetMpeg4ModeFlag, %function
GetMpeg4ModeFlag:
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
	add	r6, r0, #262144
	subs	r8, r1, #0
	ldr	r7, [r6, #284]
	ldr	r4, [r6, #188]
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r10, .L784
	mov	r7, r7, asl #2
	mov	r5, #0
	movw	r9, #438
	b	.L773
.L769:
	add	r5, r5, #1
	add	r4, r4, r7
	cmp	r5, r8
	beq	.L782
.L773:
	ldr	r0, [r4]
	ldr	r3, [r6, #128]
	bic	r0, r0, #-2147483648
	cmp	r3, r0
	orrhi	r0, r0, #-2147483648
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L783
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r2, [r0, #3]	@ zero_extendqisi2
	mov	r1, r1, asl #16
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, r0, asl #8
	cmp	r3, r9
	cmpne	r3, #288
	bic	r3, r3, #1020
	bic	r3, r3, #3
	moveq	r1, #1
	moveq	r2, #0
	streq	r1, [r6, #232]
	streq	r2, [r6, #236]
	cmp	r3, #32768
	bne	.L769
	ldr	r3, [r6, #232]
	cmp	r3, #1
	beq	.L770
.L772:
	add	r5, r5, #1
	mov	r3, #2
	cmp	r5, r8
	str	r3, [r6, #232]
	add	r4, r4, r7
	bne	.L773
.L782:
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L770:
	ldr	r3, [r6, #236]
	add	r3, r3, #1
	str	r3, [r6, #236]
	cmp	r3, #30
	bls	.L769
	ldr	r3, [r10]
	subs	ip, r3, #0
	beq	.L772
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r6, #212]
	blx	ip
	b	.L772
.L783:
	movw	r3, #2507
	ldr	r2, .L784+4
	ldr	r1, .L784+8
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L785:
	.align	2
.L784:
	.word	g_event_report
	.word	.LANCHOR3+88
	.word	.LC34
	UNWIND(.fnend)
	.size	GetMpeg4ModeFlag, .-GetMpeg4ModeFlag
	.align	2
	.global	ProcessMpeg4ScdUpMsg
	.type	ProcessMpeg4ScdUpMsg, %function
ProcessMpeg4ScdUpMsg:
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
	add	r6, r0, #262144
	mov	r7, r0
	mov	r8, r1
	ldr	r3, [r6, #284]
	mov	r10, r2
	str	r1, [fp, #-240]
	sub	r0, fp, #204
	str	r2, [fp, #-236]
	mov	r1, #0
	mov	r9, r3
	str	r3, [fp, #-244]
	ldr	r3, [r6, #188]
	mov	r2, #80
	mov	r4, r3
	str	r3, [fp, #-248]
	bl	memset
	mov	r2, #80
	mov	r1, #0
	sub	r0, fp, #124
	bl	memset
	ldr	r0, [r6, #128]
	bl	MEM_Phy2Vir
	mov	r5, r0
	mov	r0, r10
	bl	MEM_Phy2Vir
	ldr	r3, .L831
	mov	r1, r5
	mov	r2, #4
	mov	r5, r4
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, r8
	mov	r0, r7
	bl	GetMpeg4ModeFlag
	add	ip, r7, #98304
	mov	r2, r8
	mov	r1, r4
	mov	r0, r7
	mov	r4, r9, asl #2
	add	r3, r5, r4
	mov	r10, ip
	str	r3, [fp, #-220]
	mov	r8, #0
	str	ip, [fp, #-224]
	bl	GetNextVop
	mov	r9, r5
	add	r3, r7, #80
	add	r5, r5, #4
	str	r3, [fp, #-228]
	mov	r7, r8
	add	r3, r10, #104
	str	r3, [fp, #-212]
	str	r0, [fp, #-216]
	b	.L787
.L827:
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L791
	ldr	r3, [fp, #-108]
	sub	r0, fp, #124
	ldr	r1, [fp, #-212]
	add	r10, r3, r10
	str	r10, [fp, #-108]
	bl	CheckSegValid
	subs	r3, r0, #0
	bne	.L795
	ldr	r2, [r6, #212]
	sub	r1, fp, #124
	ldr	r0, [fp, #-212]
	str	r3, [fp, #-232]
	bl	InsertStreamSeg
	ldr	r3, [fp, #-232]
	mov	r2, #80
	mov	r1, r3
	ldr	r3, .L831
	ldr	r3, [r3, #48]
	mov	r10, r0
	sub	r0, fp, #124
	blx	r3
	cmp	r10, #0
	bne	.L795
.L796:
	ldr	r7, [fp, #-208]
	add	r9, r9, r4
	add	r5, r5, r4
	add	r8, r8, r4
.L787:
	ldr	r3, [fp, #-216]
	cmp	r7, r3
	beq	.L795
	ldr	r3, [fp, #-220]
	ldr	r2, [r5, #-4]
	ldr	r1, [r6, #128]
	ldr	r0, [r3, r8]
	bic	r2, r2, #-2147483648
	cmp	r1, r2
	add	r3, r7, #1
	bic	r0, r0, #-2147483648
	orrhi	r2, r2, #-2147483648
	cmp	r1, r0
	str	r3, [fp, #-208]
	orrhi	r0, r0, #-2147483648
	rsb	r10, r2, r0
	cmp	r10, #3
	bgt	.L827
	sub	r3, r10, #1
	cmp	r3, #2
	bls	.L828
	ldr	r3, [fp, #-212]
	rsb	r10, r1, r0
	cmp	r3, #0
	ldr	r3, [fp, #-236]
	rsb	r3, r2, r3
	str	r3, [fp, #-232]
	add	r3, r10, r3
	beq	.L805
	rsb	r1, r1, r2
	str	r2, [fp, #-192]
	ldr	r2, [fp, #-224]
	cmp	r3, #3
	ldr	r0, [r6, #116]
	ldr	ip, [r6, #112]
	ldr	lr, [r2, #104]
	rsb	r2, ip, r0
	str	r3, [fp, #-188]
	ubfx	r2, r2, #0, #11
	add	r1, lr, r1
	rsb	r2, r2, #2048
	str	r1, [fp, #-204]
	ble	.L814
	cmp	r2, #2
	bls	.L795
.L815:
	ldr	r1, [fp, #-212]
	sub	r0, fp, #204
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L795
	cmp	r10, #0
	ldr	r3, [r6, #232]
	bne	.L807
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	ldr	lr, [r6, #212]
	mov	r0, #1
	bfieq	r3, r10, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	sub	r3, fp, #204
	ldr	r2, [r5, #-4]
	ldrb	r1, [fp, #-132]	@ zero_extendqisi2
	mov	r2, r2, lsr #31
	bfi	r1, r2, #1, #1
	strb	r1, [fp, #-132]
	ldrh	ip, [r5, #6]
	add	r2, r6, #248
	uxtb	r1, r1
	bfi	r1, ip, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r5, #4]
	ldrb	ip, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	ip, r1, #3, #4
	strb	ip, [fp, #-132]
	ldr	ip, [fp, #-232]
	ldr	r1, [r5, #4]
	strb	r0, [fp, #-199]
	str	ip, [fp, #-188]
	and	r1, r1, #7
	ldrh	ip, [fp, #-132]
	ldr	r0, [fp, #-228]
	bfi	ip, r1, #7, #4
	strh	ip, [fp, #-132]	@ movhi
	ldr	r1, [r9, #4]
	str	lr, [sp]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r6, #212]
	sub	r1, fp, #204
	ldr	r0, [fp, #-212]
	bl	InsertStreamSeg
	b	.L796
.L791:
	ldr	r3, [fp, #-224]
	rsb	ip, r1, r2
	sub	r0, fp, #204
	ldr	r1, [fp, #-212]
	str	r2, [fp, #-192]
	ldr	r3, [r3, #104]
	str	r10, [fp, #-188]
	add	r3, r3, ip
	str	r3, [fp, #-204]
	mov	r3, #1
	strb	r3, [fp, #-199]
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L795
	ldr	r3, [r6, #232]
	add	r2, r6, #248
	ldr	lr, [r6, #212]
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	bfieq	r3, r0, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	sub	r3, fp, #204
	ldr	r1, [r5, #-4]
	ldrb	r0, [fp, #-132]	@ zero_extendqisi2
	mov	r1, r1, lsr #31
	bfi	r0, r1, #1, #1
	strb	r0, [fp, #-132]
	ldrh	ip, [r5, #6]
	uxtb	r1, r0
	ldr	r0, [fp, #-228]
	bfi	r1, ip, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r5, #4]
	ldrb	ip, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	ip, r1, #3, #4
	strb	ip, [fp, #-132]
	ldr	r1, [r5, #4]
	ldrh	ip, [fp, #-132]
	and	r1, r1, #7
	bfi	ip, r1, #7, #4
	strh	ip, [fp, #-132]	@ movhi
	ldr	r1, [r9, #4]
	str	lr, [sp]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r2, [r6, #212]
	sub	r1, fp, #204
	ldr	r0, [fp, #-212]
	bl	InsertStreamSeg
	cmp	r0, #0
	beq	.L796
.L795:
	cmp	r7, #0
	ble	.L829
	ldr	r3, [fp, #-244]
	ldr	r0, [fp, #-228]
	mul	r7, r3, r7
	ldr	r3, [fp, #-248]
	add	r7, r7, #1
	ldr	r1, [r3, r7, asl #2]
	bic	r1, r1, #-2147483648
	bl	DeleteRawLen
.L786:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L828:
	str	r2, [fp, #-232]
	bl	MEM_Phy2Vir
	ldr	r2, [fp, #-232]
	cmp	r0, #0
	beq	.L830
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r0, asl #8
	cmp	r3, #256
	beq	.L796
	ldr	r3, [r6, #232]
	mov	ip, #1
	cmp	r3, #1
	ldrb	r3, [fp, #-52]	@ zero_extendqisi2
	bfceq	r3, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-52]
	sub	r3, fp, #124
	ldr	r1, [r5, #-4]
	ldrb	r0, [fp, #-52]	@ zero_extendqisi2
	mov	r1, r1, lsr #31
	bfi	r0, r1, #1, #1
	strb	r0, [fp, #-52]
	uxtb	r1, r0
	ldrh	r0, [r5, #6]
	bfi	r1, r0, #2, #1
	strb	r1, [fp, #-52]
	ldr	r1, [r5, #4]
	ldrb	r0, [fp, #-52]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	r0, r1, #3, #4
	strb	r0, [fp, #-52]
	ldr	r0, [r5, #4]
	ldrh	lr, [fp, #-52]
	and	r0, r0, #7
	ldr	r1, [r6, #128]
	bfi	lr, r0, #7, #4
	ldr	r0, [fp, #-224]
	strb	ip, [fp, #-119]
	rsb	r1, r1, r2
	str	r2, [fp, #-112]
	add	r2, r6, #248
	ldr	ip, [r0, #104]
	strh	lr, [fp, #-52]	@ movhi
	add	r1, ip, r1
	ldr	ip, [r6, #212]
	str	r10, [fp, #-108]
	str	r1, [fp, #-124]
	ldr	r1, [r9, #4]
	ldr	r0, [fp, #-228]
	str	ip, [sp]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	b	.L796
.L807:
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	ldr	lr, [r6, #212]
	bfieq	r3, r0, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	mov	r0, #0
	ldr	r2, [r5, #-4]
	sub	r3, fp, #204
	ldrb	r1, [fp, #-132]	@ zero_extendqisi2
	mov	r2, r2, lsr #31
	bfi	r1, r2, #1, #1
	strb	r1, [fp, #-132]
	ldrh	ip, [r5, #6]
	add	r2, r6, #248
	uxtb	r1, r1
	bfi	r1, ip, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r5, #4]
	ldrb	ip, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	ip, r1, #3, #4
	strb	ip, [fp, #-132]
	ldr	ip, [fp, #-232]
	ldr	r1, [r5, #4]
	strb	r0, [fp, #-199]
	str	ip, [fp, #-188]
	and	r1, r1, #7
	ldrh	ip, [fp, #-132]
	ldr	r0, [fp, #-228]
	bfi	ip, r1, #7, #4
	strh	ip, [fp, #-132]	@ movhi
	ldr	r1, [r9, #4]
	str	lr, [sp]
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r7, [fp, #-212]
	ldr	r2, [r6, #212]
	sub	r1, fp, #204
	mov	r0, r7
	bl	InsertStreamSeg
	ldr	r3, [fp, #-224]
	ldr	lr, [r6, #128]
	sub	r1, fp, #204
	ldr	r2, [r6, #212]
	mov	r0, r7
	ldr	ip, [r3, #104]
	mov	r3, #1
	str	r10, [fp, #-188]
	str	lr, [fp, #-192]
	str	ip, [fp, #-204]
	strb	r3, [fp, #-199]
	bl	InsertStreamSeg
	b	.L796
.L805:
	ldr	r0, [fp, #-224]
	cmp	r3, #3
	rsb	r1, r1, r2
	str	r2, [fp, #-192]
	str	r3, [fp, #-188]
	ldr	r0, [r0, #104]
	add	r1, r0, r1
	str	r1, [fp, #-204]
	bgt	.L815
.L814:
	movw	r2, #2643
	ldr	r1, .L831+4
	mov	r0, #0
	bl	dprint_vfmw
	b	.L796
.L829:
	ldr	r3, [fp, #-216]
	ldr	r2, [fp, #-240]
	clz	r3, r3
	cmp	r2, #2048
	mov	r3, r3, lsr #5
	movls	r3, #0
	cmp	r3, #0
	beq	.L786
	ldr	r1, .L831+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r0, [fp, #-228]
	mov	r1, #1
	bl	DeleteRawPacket
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L830:
	movw	r3, #2615
	ldr	r2, .L831+12
	ldr	r1, .L831+16
	mov	r0, #1
	bl	dprint_vfmw
	b	.L786
.L832:
	.align	2
.L831:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
	.word	.LC36
	.word	.LANCHOR3+108
	.word	.LC35
	UNWIND(.fnend)
	.size	ProcessMpeg4ScdUpMsg, .-ProcessMpeg4ScdUpMsg
	.align	2
	.global	ProcessScdReturn
	.type	ProcessScdReturn, %function
ProcessScdReturn:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r4, r0, #262144
	mov	r5, r0
	ldr	r3, [r4, #168]
	cmp	r3, #3
	mov	r3, #2
	streq	r3, [r4, #168]
	mvneq	r0, #6
	beq	.L835
	str	r3, [r4, #168]
	sub	r0, fp, #56
	bl	ReadScdStateReg
	ldr	r6, [fp, #-44]
	movw	r3, #34464
	movt	r3, 1
	cmp	r6, r3
	bhi	.L840
.L836:
	ldr	r1, [r4, #284]
	ldr	r0, [fp, #-32]
	bl	__aeabi_uidiv
	cmp	r0, r6
	movcs	r0, r6
	cmp	r0, #1
	bls	.L841
	ldr	r3, [r5, #16]
	mov	r4, #0
	sub	r1, r0, #1
	strb	r4, [r5]
	cmp	r3, #2
	mov	r0, r5
	ldr	r2, [fp, #-40]
	beq	.L839
	bl	ProcessNotMpeg4ScdUpMsg
	mov	r0, r4
.L835:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L840:
	ldr	r3, [r5, #16]
	cmp	r3, #0
	bne	.L836
	mov	r0, r5
	mov	r1, r6
	bl	ProcessExceptionalStartCodeNum
	mvn	r0, #6
	b	.L835
.L839:
	bl	ProcessMpeg4ScdUpMsg
	mov	r0, r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L841:
	mov	r1, r0
	mov	r0, r5
	bl	ProcessNoSeg
	b	.L835
	UNWIND(.fnend)
	.size	ProcessScdReturn, .-ProcessScdReturn
	.align	2
	.global	SCDDRV_SaveRawStream
	.type	SCDDRV_SaveRawStream, %function
SCDDRV_SaveRawStream:
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
	ldr	r6, .L850
	mov	r7, r0
	mov	r8, r1
	mov	r5, r2
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r4, .L850+4
	mov	r0, #0
	ldr	r9, [r1, #16]
	ldr	r3, [r4, #16]
	blx	r3
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L844
	add	r1, r8, #32
	mov	r0, r9
	bl	SCDDRV_IsSCDByPass
	cmp	r0, #0
	bne	.L849
.L845:
	ldr	r2, [r6, r7, asl #2]
	ldr	r3, [r4, #44]
	ldr	r1, [r5, #12]
	ldr	r0, [r5, #40]
	blx	r3
.L844:
	ldr	r3, [r4, #12]
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L849:
	ldr	r3, [r4, #44]
	mov	r1, #4
	ldr	r2, [r6, r7, asl #2]
	add	r0, r5, #12
	blx	r3
	b	.L845
.L851:
	.align	2
.L850:
	.word	vfmw_save_str_file
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SCDDRV_SaveRawStream, .-SCDDRV_SaveRawStream
	.align	2
	.global	NeedReadStream
	.type	NeedReadStream, %function
NeedReadStream:
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
	ldr	r3, [r1, #56]
	cmp	r3, #0
	bne	.L853
	ldr	r3, [r1, #60]
	cmp	r3, #0
	beq	.L855
.L853:
	add	r1, r1, #262144
	ldr	r3, [r1, #152]
	cmp	r3, #8
	bgt	.L856
	ldr	r2, .L857
	cmp	r3, #0
	movgt	r3, #0
	movle	r3, #1
	ldr	r2, [r2, r0, asl #2]
	add	r2, r2, #294912
	ldr	r0, [r2, #1212]
	cmp	r0, #1
	moveq	r0, r3
	orrne	r0, r3, #1
	ldmfd	sp, {fp, sp, pc}
.L856:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L855:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L858:
	.align	2
.L857:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	NeedReadStream, .-NeedReadStream
	.align	2
	.global	FillEopRawStream
	.type	FillEopRawStream, %function
FillEopRawStream:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #116)
	sub	sp, sp, #116
	ldr	r3, .L873
	mov	r4, r1
	mov	r2, #100
	add	r3, r3, r0, lsl #3
	ldr	r1, .L873+4
	sub	r0, fp, #128
	ldr	r5, [r3, #68]
	bl	memcpy
	cmp	r4, #0
	beq	.L872
	ldr	r3, [r5, #16]
	cmp	r3, #16
	bhi	.L862
	mov	r2, #1
	movw	r1, #65406
	mov	r2, r2, asl r3
	and	r1, r1, r2
	cmp	r1, #0
	bne	.L863
	tst	r2, #65536
	bne	.L867
	tst	r2, #1
	subne	r1, fp, #128
	movne	r5, #15
	beq	.L862
.L864:
	ldr	r3, [r4, #12]
	ldr	r2, [r4, #80]
	add	r0, r5, r3
	cmp	r0, r2
	bhi	.L865
	ldr	ip, .L873+8
	mov	r2, r5
	ldr	r0, [r4, #40]
	ldr	r6, [ip, #52]
	add	r0, r3, r0
	blx	r6
	ldr	r3, [r4, #12]
	mov	r0, #0
	add	r5, r3, r5
	str	r5, [r4, #12]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L863:
	ldr	r3, [r4, #12]
	ldr	r2, [r4, #80]
	cmp	r3, r2
	bhi	.L869
	mov	r0, #0
.L870:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L867:
	mov	r5, #16
	sub	r1, fp, #48
	b	.L864
.L862:
	ldr	r2, .L873+12
	mov	r0, #0
	ldr	r1, .L873+16
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L870
.L869:
	mov	r5, #0
.L865:
	str	r2, [sp, #4]
	mov	r0, #0
	str	r5, [sp]
	ldr	r2, .L873+12
	ldr	r1, .L873+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L870
.L872:
	mov	r0, r4
	ldr	r2, .L873+12
	ldr	r1, .L873+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L870
.L874:
	.align	2
.L873:
	.word	.LANCHOR0
	.word	.LANCHOR3+132
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+232
	.word	.LC38
	.word	.LC39
	.word	.LC37
	UNWIND(.fnend)
	.size	FillEopRawStream, .-FillEopRawStream
	.align	2
	.global	FillEosRawStream
	.type	FillEosRawStream, %function
FillEosRawStream:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #112)
	sub	sp, sp, #112
	ldr	r3, .L897
	mov	r4, r1
	mov	r2, #100
	add	r3, r3, r0, lsl #3
	ldr	r1, .L897+4
	sub	r0, fp, #120
	ldr	r5, [r3, #68]
	bl	memcpy
	cmp	r4, #0
	beq	.L895
	ldr	r3, [r5, #16]
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L878
.L880:
	.word	.L879
	.word	.L881
	.word	.L882
	.word	.L883
	.word	.L893
	.word	.L893
	.word	.L889
	.word	.L878
	.word	.L893
	.word	.L893
	.word	.L893
	.word	.L893
	.word	.L893
	.word	.L893
	.word	.L893
	.word	.L879
	.word	.L885
	.word	.L893
.L879:
	sub	r1, fp, #120
	mov	r5, #15
.L884:
	ldr	r3, [r4, #12]
	cmp	r5, r3
	bhi	.L896
	ldr	r3, .L897+8
	mov	r2, r5
	ldr	r0, [r4, #40]
	ldr	r3, [r3, #52]
	blx	r3
	str	r5, [r4, #12]
.L893:
	mov	r0, #0
.L891:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L889:
	mov	r5, #15
	sub	r1, fp, #100
	b	.L884
.L881:
	ldr	r3, [r5, #32]
	cmp	r3, #1
	bne	.L893
	sub	r1, fp, #100
	mov	r5, #15
	b	.L884
.L882:
	mov	r5, #19
	sub	r1, fp, #80
	b	.L884
.L883:
	mov	r5, #16
	sub	r1, fp, #60
	b	.L884
.L885:
	mov	r5, #16
	sub	r1, fp, #40
	b	.L884
.L878:
	ldr	r2, .L897+12
	mov	r0, #0
	ldr	r1, .L897+16
	bl	dprint_vfmw
	mvn	r0, #6
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L896:
	str	r3, [sp]
	mov	r0, #0
	mov	r3, r5
	ldr	r2, .L897+12
	ldr	r1, .L897+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L891
.L895:
	mov	r0, r4
	ldr	r2, .L897+12
	ldr	r1, .L897+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L891
.L898:
	.align	2
.L897:
	.word	.LANCHOR0
	.word	.LANCHOR3+252
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+352
	.word	.LC38
	.word	.LC40
	.word	.LC37
	UNWIND(.fnend)
	.size	FillEosRawStream, .-FillEosRawStream
	.align	2
	.global	FillVC1ExtraData
	.type	FillVC1ExtraData, %function
FillVC1ExtraData:
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
	mov	r4, r1
	ldr	r1, [r0, #32]
	mov	r6, r0
	ldr	r0, [r4, #76]
	cmp	r1, #1
	beq	.L909
	ands	r5, r0, #128
	bne	.L910
	add	r6, r6, #262144
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #80]
	ldr	r0, [r6, #300]
	add	r3, r2, r0
	cmp	r3, r1
	bhi	.L911
.L907:
	ldr	r7, .L914
	ldr	r1, [r4, #40]
	ldr	r3, [r7, #56]
	add	r0, r1, r0
	blx	r3
	ldr	r3, [r7, #52]
	ldr	r2, [r6, #300]
	add	r1, r6, #304
	ldr	r0, [r4, #40]
	blx	r3
	ldr	r2, [r6, #300]
	ldr	r3, [r4, #12]
	mov	r0, r5
	add	r3, r3, r2
	str	r3, [r4, #12]
.L903:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L910:
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #80]
	cmp	r2, #116
	add	r3, r2, #12
	movle	r0, #0
	movgt	r0, #1
	cmp	r3, r1
	movls	r5, r0
	orrhi	r5, r0, #1
	cmp	r5, #0
	bne	.L912
	ldr	r7, .L914
	add	r6, r6, #262144
	ldr	r1, [r4, #40]
	ldr	r3, [r7, #56]
	add	r0, r1, #8
	blx	r3
	ldr	r3, [r7, #52]
	add	r1, r4, #84
	mov	r2, #4
	ldr	r0, [r4, #40]
	blx	r3
	ldr	r0, [r4, #40]
	ldr	r3, [r7, #52]
	mov	r2, #4
	add	r1, r4, #88
	add	r0, r0, r2
	blx	r3
	ldr	r0, [r4, #40]
	ldr	r3, [r7, #48]
	mov	r1, r5
	mov	r2, #4
	add	r0, r0, #12
	blx	r3
	mov	r3, #16
	add	r0, r6, #304
	str	r3, [r4, #12]
	str	r3, [r6, #300]
	ldr	r3, [r7, #52]
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #40]
	blx	r3
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L909:
	ands	r5, r0, #128
	beq	.L901
	ldr	r3, [r4, #12]
	cmp	r3, #128
	bgt	.L913
	ldr	r2, .L914
	add	r6, r6, #262144
	add	r0, r6, #304
	str	r3, [r6, #300]
	ldr	r3, [r2, #52]
	ldr	r1, [r4, #40]
	ldr	r2, [r4, #12]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L901:
	ldrb	r0, [r4, #72]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L903
	add	r6, r6, #262144
	ldr	r2, [r4, #12]
	ldr	ip, [r4, #80]
	ldr	r0, [r6, #300]
	add	r3, r2, r0
	cmp	r3, ip
	bls	.L907
	mov	r0, r1
	str	ip, [sp]
	ldr	r2, .L914+4
	ldr	r1, .L914+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L903
.L912:
	str	r1, [sp]
	mov	r0, #1
	mov	r1, #128
	ldr	r2, .L914+4
	str	r1, [sp, #4]
	ldr	r1, .L914+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L903
.L911:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L914+4
	ldr	r1, .L914+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L903
.L913:
	mov	r0, r1
	ldr	r2, .L914+4
	mov	r1, #128
	str	r1, [sp]
	ldr	r1, .L914+16
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L903
.L915:
	.align	2
.L914:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+372
	.word	.LC42
	.word	.LC43
	.word	.LC41
	UNWIND(.fnend)
	.size	FillVC1ExtraData, .-FillVC1ExtraData
	.align	2
	.global	FillDIVX3ExtraData
	.type	FillDIVX3ExtraData, %function
FillDIVX3ExtraData:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r2, [r1, #12]
	mov	r4, r1
	ldr	r1, [r1, #80]
	add	r3, r2, #8
	cmp	r3, r1
	bhi	.L919
	ldr	r5, .L920
	ldr	r1, [r4, #40]
	ldr	r3, [r5, #56]
	add	r0, r1, #8
	blx	r3
	ldr	r3, [r5, #52]
	mov	r2, #4
	add	r1, r4, #84
	ldr	r0, [r4, #40]
	blx	r3
	ldr	r0, [r4, #40]
	ldr	r3, [r5, #52]
	mov	r2, #4
	add	r1, r4, #88
	add	r0, r0, r2
	blx	r3
	ldr	r3, [r4, #12]
	mov	r0, #0
	add	r3, r3, #8
	str	r3, [r4, #12]
.L918:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L919:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L920+4
	ldr	r1, .L920+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L918
.L921:
	.align	2
.L920:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+392
	.word	.LC44
	UNWIND(.fnend)
	.size	FillDIVX3ExtraData, .-FillDIVX3ExtraData
	.align	2
	.global	FillREAL8ExtraData
	.type	FillREAL8ExtraData, %function
FillREAL8ExtraData:
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
	ldr	r3, [r1, #76]
	mov	r6, r1
	ands	r5, r3, #128
	beq	.L923
	ldr	r3, [r1, #12]
	cmp	r3, #128
	bgt	.L927
	ldr	r2, .L929
	add	r4, r0, #262144
	add	r0, r4, #304
	str	r3, [r4, #300]
	ldr	r3, [r2, #52]
	ldr	r2, [r1, #12]
	ldr	r1, [r1, #40]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L923:
	add	r4, r0, #262144
	ldr	r2, [r1, #12]
	ldr	r1, [r1, #80]
	ldr	r0, [r4, #300]
	add	r3, r2, r0
	cmp	r3, r1
	bhi	.L928
	ldr	r7, .L929
	ldr	r1, [r6, #40]
	ldr	r3, [r7, #56]
	add	r0, r1, r0
	blx	r3
	ldr	r3, [r7, #52]
	ldr	r2, [r4, #300]
	add	r1, r4, #304
	ldr	r0, [r6, #40]
	blx	r3
	ldr	r2, [r4, #300]
	ldr	r3, [r6, #12]
	mov	r0, r5
	add	r3, r3, r2
	str	r3, [r6, #12]
.L925:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L928:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L929+4
	ldr	r1, .L929+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L925
.L927:
	mov	r1, #128
	ldr	r2, .L929+4
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L929+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L925
.L930:
	.align	2
.L929:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+412
	.word	.LC45
	.word	.LC41
	UNWIND(.fnend)
	.size	FillREAL8ExtraData, .-FillREAL8ExtraData
	.align	2
	.global	FillExtraData
	.type	FillExtraData, %function
FillExtraData:
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
	clz	r3, r1
	mov	r3, r3, lsr #5
	cmp	r0, #31
	orrhi	r3, r3, #1
	cmp	r3, #0
	bne	.L937
	ldr	r2, [r1, #12]
	cmp	r2, #0
	ble	.L940
	ldr	r2, .L942
	add	r0, r2, r0, lsl #3
	ldr	r0, [r0, #68]
	ldr	r2, [r0, #16]
	cmp	r2, #5
	beq	.L934
	cmp	r2, #8
	beq	.L935
	cmp	r2, #1
	beq	.L941
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L935:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillREAL8ExtraData
.L934:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillDIVX3ExtraData
.L941:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillVC1ExtraData
.L937:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L940:
	mov	r3, r2
	ldr	r1, .L942+4
	ldr	r2, .L942+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L943:
	.align	2
.L942:
	.word	.LANCHOR0
	.word	.LC46
	.word	.LANCHOR3+432
	UNWIND(.fnend)
	.size	FillExtraData, .-FillExtraData
	.align	2
	.global	ReleaseRawStreamData
	.type	ReleaseRawStreamData, %function
ReleaseRawStreamData:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 112
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #116)
	sub	sp, sp, #116
	mov	r6, r1
	mov	r7, r0
	bl	VCTRL_GetStreamInterface
	ldr	r5, .L959
	mov	r2, #12
	mov	r1, #0
	ldr	r3, [r5, #48]
	mov	r4, r0
	sub	r0, fp, #144
	blx	r3
	cmp	r4, #0
	beq	.L956
	mov	r1, r4
	ldr	r3, [r5, #52]
	mov	r2, #12
	sub	r0, fp, #144
	blx	r3
	mov	r1, r6
	ldr	r3, [r5, #52]
	sub	r0, fp, #132
	mov	r2, #96
	ldr	r6, .L959+4
	blx	r3
	ldr	r3, [r4, #8]
	mov	r8, r7, asl #3
	cmp	r3, #0
	mvneq	r4, #6
	beq	.L947
	add	r4, r6, r8
	ldr	r3, [r4, #68]
	ldr	r3, [r3, #56]
	cmp	r3, #1
	beq	.L957
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r3, [r5, #24]
	mov	r1, r7
	mov	r0, #1
	blx	r3
	ldr	r3, [r4, #68]
	cmp	r3, #0
	mvneq	r4, #6
	beq	.L950
	sub	r1, fp, #132
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	blx	r3
	mov	r4, r0
.L950:
	ldr	r3, [r5, #28]
	mov	r0, #1
	mov	r1, r7
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
.L949:
	cmp	r4, #0
	mvnne	r4, #6
.L947:
	add	r6, r6, r8
	ldr	r0, [r6, #68]
	cmp	r0, #0
	movne	r0, r4
	beq	.L958
.L946:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L957:
	sub	r1, fp, #132
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	blx	r3
	mov	r4, r0
	b	.L949
.L956:
	mov	r2, r7
	mov	r0, r4
	ldr	r1, .L959+8
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L946
.L958:
	mov	r3, r7
	movw	r2, #3596
	ldr	r1, .L959+12
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L946
.L960:
	.align	2
.L959:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC47
	.word	.LC48
	UNWIND(.fnend)
	.size	ReleaseRawStreamData, .-ReleaseRawStreamData
	.align	2
	.global	DeleteRawPacketInBuffer
	.type	DeleteRawPacketInBuffer, %function
DeleteRawPacketInBuffer:
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
	cmp	r0, #31
	mov	r8, r0
	bhi	.L973
	ldr	r10, .L980
	mov	r9, r0, asl #3
	add	r3, r10, r9
	ldr	r7, [r3, #68]
	cmp	r7, #0
	beq	.L973
	cmp	r1, #0
	beq	.L977
.L963:
	adds	r3, r7, #80
	str	r3, [fp, #-52]
	beq	.L973
	add	r3, r7, #98304
	str	r3, [fp, #-56]
	mov	r2, r3
	ldr	r3, [r3, #80]
	ldr	r4, [r2, #88]
	cmp	r3, r4
	addlt	r3, r3, #1024
	rsb	r3, r4, r3
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L973
	mov	r6, #0
	b	.L967
.L979:
	ldr	r3, [fp, #-48]
	cmp	r6, r3
	beq	.L978
.L967:
	mov	r5, r4, asl #7
	ldr	r2, .L980+4
	sub	r5, r5, r4, asl #5
	ldr	r1, .L980+8
	add	ip, r7, r5
	mov	r0, #26
	add	r4, r4, #1
	add	r6, r6, #1
	ldr	r3, [ip, #84]
	ubfx	r4, r4, #0, #10
	ldr	ip, [ip, #92]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [fp, #-52]
	mov	r0, r8
	add	r1, r3, r5
	bl	ReleaseRawStreamData
	add	r3, r10, r9
	ldr	r3, [r3, #68]
	cmp	r3, #0
	bne	.L979
	mvn	r0, #6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L977:
	add	r3, r7, #262144
	ldr	r3, [r3, #228]
	cmp	r3, #0
	bne	.L963
.L973:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L978:
	ldr	r3, [fp, #-56]
	ldr	r4, [r3, #88]
	add	r4, r4, r6
	cmp	r4, #1024
	strlt	r4, [r3, #88]
	subge	r4, r4, #1024
	ldrge	r3, [fp, #-56]
	movlt	r0, #0
	movge	r0, #0
	strge	r4, [r3, #88]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L981:
	.align	2
.L980:
	.word	.LANCHOR0
	.word	.LANCHOR3+448
	.word	.LC11
	UNWIND(.fnend)
	.size	DeleteRawPacketInBuffer, .-DeleteRawPacketInBuffer
	.align	2
	.global	SM_Reset
	.type	SM_Reset, %function
SM_Reset:
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
	UNWIND(.pad #212)
	sub	sp, sp, #212
	cmp	r0, #31
	mov	r7, r0
	bhi	.L994
	ldr	r6, .L1006
	mov	r10, r0, asl #3
	add	r3, r6, r10
	ldr	r5, [r3, #68]
	cmp	r5, #0
	beq	.L984
	ldr	r3, [r6, #44]
	cmp	r3, r0
	bne	.L986
	mov	ip, #0
	movw	r3, #1095
	ldr	r2, .L1006+4
	mov	r0, #22
	ldr	r1, .L1006+8
	str	ip, [r6, #48]
	bl	dprint_vfmw
.L986:
	ldr	r8, .L1006+12
	add	r4, r5, #262144
	mov	r2, #72
	add	r1, r5, #8
	sub	r0, fp, #244
	add	r9, r4, #304
	ldr	r3, [r8, #52]
	add	r6, r6, r10
	blx	r3
	ldr	ip, [r4, #228]
	ldr	r3, [r8, #52]
	mov	r1, r9
	sub	r0, fp, #172
	mov	r2, #128
	str	ip, [fp, #-248]
	ldr	ip, [r4, #300]
	str	ip, [fp, #-252]
	blx	r3
	ldr	r3, [r6, #68]
	cmp	r3, #0
	beq	.L987
	add	r3, r3, #262144
	ldr	r2, [r3, #228]
	cmp	r2, #0
	bne	.L1004
.L987:
	adds	r6, r5, #80
	beq	.L988
.L1005:
	add	r2, r5, #98304
	ldr	r3, [r2, #84]
	ldr	r1, [r2, #80]
	subs	r1, r3, r1
	addmi	r1, r1, #1024
.L993:
	mov	r0, r6
	bl	DeleteRawPacket
	mov	r1, #1
	mov	r0, r7
	bl	DeleteRawPacketInBuffer
	mov	r2, #440
	movt	r2, 4
	ldr	r3, [r8, #48]
	mov	r1, #0
	mov	r0, r5
	blx	r3
	mvn	r2, #0
	mvn	r3, #0
	mov	ip, #2
	strd	r2, [r4, #248]
	sub	r1, fp, #244
	str	ip, [r4, #284]
	mov	r0, r7
	bl	SM_Config
	ldr	r3, [fp, #-248]
	sub	r1, fp, #172
	mov	r0, r9
	sub	r3, r3, #1
	mov	r2, #128
	cmp	r3, #1
	movls	r3, #1
	movhi	r3, #0
	str	r3, [r4, #228]
	ldr	r3, [fp, #-252]
	str	r3, [r4, #300]
	ldr	r3, [r8, #52]
	blx	r3
	mov	r0, #0
.L1001:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1004:
	ldr	r2, [r3, #216]
	cmp	r2, #0
	movle	r2, #0
	strle	r2, [r3, #228]
	adds	r6, r5, #80
	bne	.L1005
.L988:
	ldr	r1, .L1006+16
	movw	r3, #1110
	ldr	r2, .L1006+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r1, r6
	b	.L993
.L994:
	mvn	r0, #0
	b	.L1001
.L984:
	mov	r0, r5
	movw	r2, #1085
	ldr	r1, .L1006+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1001
.L1007:
	.align	2
.L1006:
	.word	.LANCHOR0
	.word	.LANCHOR3+472
	.word	.LC50
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC51
	.word	.LC49
	UNWIND(.fnend)
	.size	SM_Reset, .-SM_Reset
	.align	2
	.global	ReadRawStreamData
	.type	ReadRawStreamData, %function
ReadRawStreamData:
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
	ldr	r8, .L1050
	mov	r10, r0, asl #3
	ldr	r6, .L1050+4
	add	r3, r8, r10
	mov	r5, r0
	mov	r9, r1
	mov	r2, #12
	ldr	r4, [r3, #68]
	sub	r0, fp, #56
	ldr	r3, [r6, #48]
	mov	r1, #0
	blx	r3
	cmp	r4, #0
	beq	.L1041
	mov	r0, r5
	bl	VCTRL_GetStreamInterface
	subs	r7, r0, #0
	beq	.L1043
	ldr	r3, [r6, #52]
	sub	r0, fp, #56
	mov	r2, #12
	mov	r1, r7
	blx	r3
	ldr	r3, [r7, #4]
	cmp	r3, #0
	beq	.L1041
	ldr	r3, [r4, #56]
	cmp	r3, #1
	beq	.L1044
	ldr	r3, .L1050+8
	mov	r0, #0
	ldr	r2, [r6, #16]
	ldr	r7, [r3, r5, asl #2]
	str	r3, [fp, #-64]
	cmp	r7, #0
	addne	r7, r7, #294912
	ldrne	r7, [r7, #1172]
	blx	r2
	ldr	r3, [fp, #-64]
	ldr	r2, .L1050+4
	ldr	r3, [r3, r5, asl #2]
	cmp	r3, #0
	beq	.L1016
	add	r3, r3, #294912
	ldr	r3, [r3, #1172]
	cmp	r3, r7
	bne	.L1045
.L1016:
	ldr	r3, [fp, #-52]
	mov	r1, r9
	ldr	r0, [fp, #-56]
	add	r8, r8, r10
	blx	r3
	ldr	r3, [r6, #12]
	mov	r7, r0
	mov	r0, #0
	blx	r3
	ldr	r0, [r8, #68]
	cmp	r0, #0
	beq	.L1046
.L1014:
	cmp	r7, #0
	bne	.L1041
	ldrb	r6, [r9, #1]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L1047
	ldr	r3, [r4, #56]
	cmp	r3, #1
	beq	.L1048
.L1019:
	add	r4, r4, #98304
	ldr	r2, [r9, #12]
	mov	r0, #0
	ldr	r3, [r4, #100]
	add	r3, r3, r2
	str	r3, [r4, #100]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1048:
	mov	r1, r9
	mov	r0, r5
	bl	FillExtraData
	cmp	r0, #0
	beq	.L1021
	mov	r2, r5
	ldr	r1, .L1050+12
	mov	r0, r7
	bl	dprint_vfmw
	mov	r1, r9
	ldr	r0, [fp, #-56]
	bl	ReleaseRawStreamData
	cmp	r0, #0
	beq	.L1041
	mov	r0, r7
	ldr	r1, .L1050+16
	bl	dprint_vfmw
.L1041:
	mvn	r0, #6
.L1039:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1044:
	ldr	r3, [fp, #-52]
	mov	r1, r9
	ldr	r0, [fp, #-56]
	blx	r3
	mov	r7, r0
	b	.L1014
.L1047:
	mov	r1, r9
	mov	r0, r5
	bl	FillEosRawStream
	cmp	r0, #0
	bne	.L1049
	mov	r1, r6
	mov	r0, r5
	bl	VCTRL_SetLastFrameState
	b	.L1019
.L1021:
	add	r3, r4, #262144
	ldr	r3, [r3, #296]
	cmp	r3, #0
	beq	.L1019
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1019
	mov	r0, r5
	mov	r1, r9
	bl	FillEopRawStream
	b	.L1019
.L1045:
	ldr	r3, [r2, #12]
	mov	r0, #0
	blx	r3
	mvn	r0, #6
	b	.L1039
.L1043:
	mov	r2, r5
	ldr	r1, .L1050+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1039
.L1049:
	mov	r2, r5
	mov	r0, r7
	ldr	r1, .L1050+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1039
.L1046:
	mov	r3, r5
	movw	r2, #3501
	ldr	r1, .L1050+28
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1039
.L1051:
	.align	2
.L1050:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LC55
	.word	.LC56
	.word	.LC52
	.word	.LC54
	.word	.LC53
	UNWIND(.fnend)
	.size	ReadRawStreamData, .-ReadRawStreamData
	.align	2
	.global	FillRawData
	.type	FillRawData, %function
FillRawData:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 112
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
	ldr	r8, .L1097
	mov	r9, r0, asl #3
	ldr	r7, .L1097+4
	add	r3, r8, r9
	mov	r4, r0
	mov	r2, #96
	mov	r1, #0
	ldr	r5, [r3, #68]
	sub	r0, fp, #140
	ldr	r3, [r7, #48]
	blx	r3
	cmp	r5, #0
	beq	.L1052
	ldr	r3, [r5, #16]
	cmp	r3, #20
	beq	.L1052
	mov	r3, r4, asl #24
	ldr	r6, .L1097+8
	str	r3, [fp, #-152]
	b	.L1068
.L1096:
	ldr	r3, [r5, #60]
	cmp	r3, #0
	bne	.L1054
.L1055:
	cmp	r4, #31
	bhi	.L1059
	add	r3, r8, r9
	ldr	r3, [r3, #68]
	cmp	r3, #0
	beq	.L1059
	add	r2, r3, #98304
	ldr	r3, [r2, #84]
	ldr	r2, [r2, #88]
	add	r3, r3, #1
	mov	r1, r3, asr #31
	mov	r1, r1, lsr #22
	add	r3, r3, r1
	ubfx	r3, r3, #0, #10
	rsb	r3, r1, r3
	cmp	r3, r2
	beq	.L1059
	sub	r1, fp, #140
	mov	r0, r4
	bl	ReadRawStreamData
	subs	r3, r0, #0
	str	r3, [fp, #-144]
	bne	.L1052
	add	r10, r5, #262144
	ldr	r2, [fp, #-128]
	ldr	r1, [r7]
	ldr	r0, [r10, #264]
	ldr	ip, [r10, #288]
	add	r0, r0, r2
	str	r0, [r10, #264]
	ldr	r0, [r10, #292]
	add	r2, r2, ip
	str	r2, [r10, #288]
	add	r2, r0, #1
	str	r2, [r10, #292]
	blx	r1
	ldr	r1, [r10, #268]
	cmp	r1, #0
	streq	r0, [r10, #268]
	beq	.L1062
	rsb	r1, r1, r0
	cmp	r1, #2000
	bls	.L1062
	str	r0, [fp, #-148]
	ldr	r0, [r10, #264]
	mov	r0, r0, asl #3
	bl	__aeabi_uidiv
	mov	r1, #1000
	ldr	r3, [fp, #-144]
	ldr	r2, [fp, #-148]
	str	r3, [r10, #264]
	str	r2, [r10, #268]
	mul	r0, r1, r0
	mov	r0, r0, lsr #10
	str	r0, [r10, #272]
.L1062:
	ldrd	r2, [fp, #-76]
	mov	r0, #29
	ldr	r1, .L1097+12
	bl	dprint_vfmw
	ldr	r3, [fp, #-128]
	ldr	r2, [fp, #-136]
	mov	r0, #26
	ldr	r1, .L1097+16
	bl	dprint_vfmw
	ldrd	r2, [fp, #-76]
	mov	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1093
.L1063:
	sub	r1, fp, #140
	mov	r0, r4
	bl	SCDDRV_InsertRawPacket
	cmp	r0, #0
	bne	.L1094
	mov	r3, #1
	strb	r3, [r5, #3]
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1095
.L1066:
	sub	r2, fp, #140
	mov	r1, r5
	mov	r0, r4
	bl	SCDDRV_SaveRawStream
	ldr	r3, [r6, r4, asl #2]
	add	r3, r3, #294912
	ldr	r3, [r3, #1212]
	cmp	r3, #1
	beq	.L1052
.L1068:
	ldr	r3, [r5, #56]
	cmp	r3, #0
	beq	.L1096
.L1054:
	add	r3, r5, #262144
	ldr	r3, [r3, #152]
	cmp	r3, #8
	bgt	.L1052
	ldr	r2, [r6, r4, asl #2]
	cmp	r3, #0
	add	r2, r2, #294912
	movgt	r3, #0
	movle	r3, #1
	ldr	r2, [r2, #1212]
	cmp	r2, #1
	orrne	r3, r3, #1
	cmp	r3, #0
	bne	.L1055
.L1052:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1059:
	mov	r2, r4
	ldr	r1, .L1097+20
	mov	r0, #23
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1095:
	ldr	r3, [r7]
	blx	r3
	add	ip, r8, r4, lsl #2
	ldr	r2, .L1097+24
	ldr	r3, [ip, #340]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	cmp	r3, r2
	bls	.L1066
	str	r0, [ip, #340]
	movw	r1, #2863
	ldr	r2, [fp, #-152]
	ldr	r0, .L1097+28
	bl	DBG_AddTrace
	b	.L1066
.L1093:
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [fp, #-76]
	b	.L1063
.L1094:
	ldr	r1, .L1097+32
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1052
.L1098:
	.align	2
.L1097:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LC57
	.word	.LC58
	.word	.LC60
	.word	g_TraceBsPeriod
	.word	.LANCHOR3+484
	.word	.LC59
	UNWIND(.fnend)
	.size	FillRawData, .-FillRawData
	.align	2
	.global	ReleaseSegArrayPackets
	.type	ReleaseSegArrayPackets, %function
ReleaseSegArrayPackets:
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
	cmp	r1, #2048
	mov	r4, r1
	mov	r7, r0
	mov	r5, r2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r1, r2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r8, r0, #163840
	mov	r6, #2
.L1102:
	mov	r3, r4, asl #6
	mov	r1, r4
	add	r3, r3, r4, lsl #4
	mov	r0, r7
	add	r3, r7, r3
	strb	r6, [r3, #12]
	ldr	ip, [r3, #24]
	ldr	r2, [r8, #44]
	ldr	r3, [r8, #48]
	rsb	r2, ip, r2
	sub	r3, r3, #1
	bic	r2, r2, r2, asr #31
	str	r2, [r8, #44]
	bic	r3, r3, r3, asr #31
	str	r3, [r8, #48]
	bl	ReleaseStreamSeg
	add	r3, r4, #1
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #21
	add	r3, r3, r4
	ubfx	r3, r3, #0, #11
	rsb	r4, r4, r3
	cmp	r5, r4
	bne	.L1102
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	ReleaseSegArrayPackets, .-ReleaseSegArrayPackets
	.align	2
	.global	SM_SeekPtsInSegArray
	.type	SM_SeekPtsInSegArray, %function
SM_SeekPtsInSegArray:
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
	ldrd	r2, [r1]
	add	r8, r0, #163840
	mov	r5, r0
	mov	r9, r1
	ldr	r4, [r8, #8]
	mov	r6, r2
	mov	r7, r3
	ldr	ip, [r8, #12]
	ldrd	r2, [r1, #8]
	str	r4, [r8, #16]
	strd	r2, [fp, #-52]
.L1105:
	mov	r3, r4, asl #6
	cmp	r4, ip
	add	r3, r3, r4, lsl #4
	mov	r1, r4
	add	r3, r5, r3
	mov	r0, r5
	add	r10, r3, #40
	beq	.L1116
	ldrsb	r2, [r3, #12]
	cmp	r2, #1
	bne	.L1108
	ldrd	r2, [r3, #40]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	addeq	r3, r4, #1
	beq	.L1115
	cmp	r7, r3
	add	r1, r4, #1
	cmpeq	r6, r2
	mov	r3, r1, asr #31
	bls	.L1111
	str	r4, [r8, #16]
	mov	r4, r3, lsr #21
	add	r1, r1, r4
	ubfx	r1, r1, #0, #11
	rsb	r4, r4, r1
	b	.L1105
.L1108:
	bl	ReleaseStreamSeg
	ldr	ip, [r8, #12]
	add	r3, r4, #1
.L1115:
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #21
	add	r3, r3, r4
	ubfx	r3, r3, #0, #11
	rsb	r4, r4, r3
	b	.L1105
.L1111:
	beq	.L1117
	bcs	.L1105
	ldr	ip, [r8, #16]
	mvn	r2, #0
	mov	r3, ip, asl #6
	add	r3, r3, ip, lsl #4
	add	r3, r5, r3
	ldrd	r0, [r3, #40]
	mvn	r3, #0
	cmp	r1, r3
	cmpeq	r0, r2
	streq	r4, [r8, #16]
	moveq	ip, r4
	beq	.L1114
	cmp	r7, r1
	cmpeq	r6, r0
	bls	.L1114
	subs	r6, r6, r0
	sbc	r7, r7, r1
	mov	r0, r6
	mov	r1, r7
	ldrd	r6, [fp, #-52]
	cmp	r7, r1
	cmpeq	r6, r0
	strcc	r4, [r8, #16]
	movcc	ip, r4
.L1114:
	mov	r2, ip
	mov	r0, r5
	ldr	r1, [r8, #8]
	bl	ReleaseSegArrayPackets
	ldr	r2, [r8, #16]
	mov	r0, #0
	mov	r3, r2, asl #6
	add	r3, r3, r2, lsl #4
	add	r5, r5, r3
	ldrd	r2, [r5, #40]
	strd	r2, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1116:
	mov	r2, r4
	ldr	r1, [r8, #8]
	bl	ReleaseSegArrayPackets
	mvn	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1117:
	mov	r2, r4
	mov	r0, r5
	ldr	r1, [r8, #8]
	bl	ReleaseSegArrayPackets
	ldrd	r2, [r10]
	mov	r0, #0
	strd	r2, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	SM_SeekPtsInSegArray, .-SM_SeekPtsInSegArray
	.align	2
	.global	SM_SeekPtsInRawArray
	.type	SM_SeekPtsInRawArray, %function
SM_SeekPtsInRawArray:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 48
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
	ldr	ip, .L1154
	str	r2, [fp, #-64]
	mov	lr, r0
	add	ip, ip, r2, lsl #3
	str	r1, [fp, #-72]
	str	r3, [fp, #-76]
	ldr	r2, [ip, #68]
	cmp	r2, #0
	str	r2, [fp, #-68]
	beq	.L1137
	cmp	r3, #1
	mov	r3, r1
	ldrd	r2, [r3, #8]
	ldrd	r0, [r1]
	strd	r2, [fp, #-92]
	movne	r3, #0
	strd	r0, [fp, #-60]
	strne	r3, [fp, #-80]
	beq	.L1148
.L1120:
	add	r8, lr, #98304
	mvn	r6, #0
	mvn	r7, #0
	strd	r6, [fp, #-52]
	ldr	r9, [r8]
	ldr	r1, [r8, #4]
	mov	r3, r9
	str	r9, [r8, #8]
.L1121:
	mov	r10, r3, asl #5
	mov	ip, r3, asl #7
	add	r2, r3, #1
	cmp	r3, r1
	rsb	r0, r10, ip
	add	r0, lr, r0
	mov	r7, r2, asr #31
	beq	.L1149
	ldrd	r4, [r0, #64]
	mov	r0, r7, lsr #22
	ldrd	r6, [fp, #-52]
	add	r2, r2, r0
	ubfx	r2, r2, #0, #10
	cmp	r5, r7
	cmpeq	r4, r6
	beq	.L1150
	ldrd	r6, [fp, #-60]
	cmp	r7, r5
	cmpeq	r6, r4
	bls	.L1127
	str	r3, [r8, #8]
	rsb	r3, r0, r2
	b	.L1121
.L1150:
	add	r2, r3, #1
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #22
	add	r2, r2, r3
	ubfx	r2, r2, #0, #10
	rsb	r3, r3, r2
	b	.L1121
.L1149:
	cmp	r9, r3
	mov	r0, lr
	addgt	r3, r3, #1024
	str	r9, [r8, #8]
	rsb	r1, r9, r3
	bl	DeleteRawPacket
	ldr	r0, [fp, #-64]
	mov	r1, #0
	bl	DeleteRawPacketInBuffer
	mvn	r0, #1
.L1119:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1127:
	beq	.L1151
	ldr	r2, [r8, #8]
	mvn	r5, #0
	mvn	r4, #0
	mov	r1, r2, asl #7
	sub	r1, r1, r2, asl #5
	add	r1, lr, r1
	ldrd	r0, [r1, #64]
	cmp	r1, r5
	cmpeq	r0, r4
	streq	r3, [r8, #8]
	moveq	r2, r3
	beq	.L1133
	ldrd	r4, [fp, #-60]
	cmp	r5, r1
	cmpeq	r4, r0
	bhi	.L1152
.L1133:
	cmp	r9, r2
	ldr	r3, [fp, #-76]
	addgt	r1, r2, #1024
	rsble	r1, r9, r2
	rsbgt	r1, r9, r1
	cmp	r3, #1
	beq	.L1153
.L1136:
	mov	r3, r2, asl #7
	mov	r0, lr
	sub	r2, r3, r2, asl #5
	add	lr, lr, r2
	ldrd	r2, [lr, #64]
.L1147:
	ldr	ip, [fp, #-72]
	strd	r2, [ip]
	ldr	r3, [r8]
	str	r3, [r8, #8]
	bl	DeleteRawPacket
	ldr	r0, [fp, #-64]
	mov	r1, #0
	bl	DeleteRawPacketInBuffer
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1148:
	ldr	r3, [fp, #-68]
	add	r3, r3, #262144
	ldr	r2, [r3, #168]
	cmp	r2, #1
	str	r2, [fp, #-80]
	moveq	r2, #3
	streq	r2, [r3, #168]
	b	.L1120
.L1152:
	subs	r4, r4, r0
	sbc	r5, r5, r1
	mov	r0, r4
	mov	r1, r5
	ldrd	r4, [fp, #-92]
	cmp	r5, r1
	cmpeq	r4, r0
	strcc	r3, [r8, #8]
	movcc	r2, r3
	b	.L1133
.L1151:
	cmp	r9, r3
	addgt	r3, r3, #1024
	rsb	r1, r9, r3
	ldr	r3, [fp, #-76]
	cmp	r3, #1
	bne	.L1131
	ldr	r3, [fp, #-68]
	ldr	r0, [fp, #-80]
	add	r3, r3, #262144
	ldr	r2, [r3, #160]
	cmp	r1, r2
	cmple	r0, #1
	moveq	r2, r0
	streq	r2, [r3, #168]
.L1131:
	rsb	ip, r10, ip
	mov	r0, lr
	add	r3, lr, ip
	ldrd	r2, [r3, #64]
	b	.L1147
.L1153:
	ldr	r3, [fp, #-68]
	ldr	ip, [fp, #-80]
	add	r3, r3, #262144
	ldr	r0, [r3, #160]
	cmp	r1, r0
	cmple	ip, #1
	moveq	r2, ip
	streq	r2, [r3, #168]
	ldreq	r2, [r8, #8]
	b	.L1136
.L1137:
	mvn	r0, #0
	b	.L1119
.L1155:
	.align	2
.L1154:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_SeekPtsInRawArray, .-SM_SeekPtsInRawArray
	.align	2
	.global	SM_SeekPtsAfterFillNewRaw
	.type	SM_SeekPtsAfterFillNewRaw, %function
SM_SeekPtsAfterFillNewRaw:
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
	mov	r4, r2
	mov	r5, r0
	mov	r6, r1
	mov	r0, r2
	mov	r1, #0
	bl	DeleteRawPacketInBuffer
	mov	r0, r4
	bl	FillRawData
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	mov	r3, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	SM_SeekPtsInRawArray
	UNWIND(.fnend)
	.size	SM_SeekPtsAfterFillNewRaw, .-SM_SeekPtsAfterFillNewRaw
	.align	2
	.global	SM_SeekPts
	.type	SM_SeekPts, %function
SM_SeekPts:
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
	clz	r3, r1
	mov	r6, r0
	mov	r7, r1
	mov	r3, r3, lsr #5
	cmp	r0, #31
	movls	r4, r3
	orrhi	r4, r3, #1
	cmp	r4, #0
	bne	.L1170
	ldr	r3, .L1180
	add	r3, r3, r0, lsl #3
	ldr	r5, [r3, #68]
	cmp	r5, #0
	beq	.L1170
	add	r8, r5, #98304
	add	r0, r8, #104
	bl	SM_SeekPtsInSegArray
	cmp	r0, #0
	bne	.L1159
.L1160:
	mov	r0, #0
.L1158:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1159:
	add	r5, r5, #80
	mov	r1, r4
	mov	r0, r6
	bl	DeleteRawPacketInBuffer
	mov	r0, r5
	mov	r3, #1
	mov	r2, r6
	mov	r1, r7
	bl	SM_SeekPtsInRawArray
	cmp	r0, #0
	beq	.L1160
	ldr	r0, [r8, #84]
	ldr	r2, [r8, #80]
	ldrd	r8, [r7, #16]
	cmp	r2, r0
	addgt	r0, r0, #1024
	rsb	r2, r2, r0
	mov	r1, r2, asr #31
	mov	r0, r2
	cmp	r1, r9
	cmpeq	r2, r8
	bcs	.L1179
	subs	r2, r8, r0
	movw	r0, #1023
	sbc	r3, r9, r1
	and	r0, r0, r2
	mov	r1, #0
	mov	r8, r2, lsr #10
	and	r1, r1, r3
	orr	r8, r8, r3, asl #22
	orrs	r1, r0, r1
	addne	r8, r8, #1
	cmp	r8, #0
	movge	r4, #0
	blt	.L1168
.L1167:
	mov	r2, r6
	mov	r1, r7
	mov	r0, r5
	add	r4, r4, #1
	bl	SM_SeekPtsAfterFillNewRaw
	cmp	r0, #0
	beq	.L1160
	cmp	r8, r4
	bge	.L1167
.L1168:
	mvn	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1170:
	mvn	r0, #0
	b	.L1158
.L1179:
	strd	r0, [sp]
	mov	r2, r8
	mov	r3, r9
	ldr	r1, .L1180+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1158
.L1181:
	.align	2
.L1180:
	.word	.LANCHOR0
	.word	.LC61
	UNWIND(.fnend)
	.size	SM_SeekPts, .-SM_SeekPts
	.align	2
	.global	SM_MoveRawData
	.type	SM_MoveRawData, %function
SM_MoveRawData:
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
	add	r7, r0, #98304
	mov	r5, r0
	ldr	r3, [r7, #84]
	subs	r6, r3, #1
	addmi	r6, r3, #1020
	addmi	r6, r6, #3
	subs	ip, r3, #2
	addmi	ip, r3, #1020
	addmi	ip, ip, #2
	mov	r1, r6, asl #7
	sub	r1, r1, r6, asl #5
	mov	r3, ip, asl #7
	add	lr, r0, r1
	sub	ip, r3, ip, asl #5
	add	r1, r1, #80
	add	ip, r0, ip
	ldr	r3, [r0, #68]
	add	r4, r0, r1
	ldr	r2, [lr, #92]
	ldr	r0, [ip, #92]
	add	r9, lr, #88
	add	r8, ip, #88
	add	r1, r0, r2
	cmp	r1, r3
	bgt	.L1185
	ldr	r10, .L1187
	add	r5, r5, #262144
	ldr	r3, [ip, #120]
	ldr	r1, [lr, #120]
	add	r0, r0, r3
	ldr	r3, [r10, #52]
	blx	r3
	ldr	r2, [r9, #4]
	ldr	r3, [r8, #4]
	mov	r1, r4
	add	r3, r3, r2
	str	r3, [r8, #4]
	ldr	r0, [r5, #212]
	bl	ReleaseRawStreamData
	mov	r0, #0
	str	r6, [r7, #84]
.L1186:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1185:
	str	r3, [sp]
	mov	r3, r2
	ldr	r1, .L1187+4
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1186
.L1188:
	.align	2
.L1187:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC62
	UNWIND(.fnend)
	.size	SM_MoveRawData, .-SM_MoveRawData
	.align	2
	.global	SCDDRV_ProcessSegFull
	.type	SCDDRV_ProcessSegFull, %function
SCDDRV_ProcessSegFull:
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
	add	r8, r0, #98304
	add	r4, r0, #262144
	add	r8, r8, #104
	ldrsb	r7, [r0, #1]
	cmp	r8, #0
	mov	r6, r0
	ldr	r5, [r4, #132]
	ldrne	r10, [r4, #152]
	moveq	r9, r8
	ldrne	r9, [r4, #148]
	moveq	r10, r8
	cmp	r7, #0
	bne	.L1191
	add	r5, r5, r5, lsr #31
	cmp	r9, r5, asr #1
	movlt	r0, #1
	movge	r0, #0
	cmp	r10, #127
	movgt	r0, #0
	andle	r0, r0, #1
	cmp	r0, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, .L1205
	mov	r2, #1
	strb	r2, [r6, #1]
	ldr	r3, [r3]
	blx	r3
	str	r7, [r4, #240]
	str	r0, [r4, #244]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1191:
	ldr	r3, .L1205
	ldr	r3, [r3]
	blx	r3
	ldr	r2, [r4, #244]
	cmp	r0, r2
	bls	.L1194
	rsb	r2, r2, r0
	str	r2, [r4, #240]
	cmp	r2, #1000
	ble	.L1204
	add	r3, r5, #3
	cmp	r5, #0
	movlt	r5, r3
	cmp	r9, r5, asr #2
	movlt	r3, #1
	movge	r3, #0
	cmp	r10, #63
	movgt	r3, #0
	andle	r3, r3, #1
	cmp	r3, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	orrs	r0, r10, r9
	bne	.L1197
	ldr	r1, [r4, #112]
	ldr	r3, [r4, #116]
	cmp	r1, r3
	beq	.L1197
	ldr	r1, .L1205+4
	bl	dprint_vfmw
	ldr	r0, [r4, #212]
	bl	SM_Reset
	b	.L1198
.L1194:
	mov	r3, #0
	str	r0, [r4, #244]
	str	r3, [r4, #240]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1197:
	ldr	r1, .L1205+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r8
	mvn	r1, #0
	bl	ReleaseStreamSeg
.L1198:
	mov	r3, #0
	strb	r3, [r6, #1]
	strb	r3, [r6]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1204:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1206:
	.align	2
.L1205:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC63
	.word	.LC64
	UNWIND(.fnend)
	.size	SCDDRV_ProcessSegFull, .-SCDDRV_ProcessSegFull
	.align	2
	.global	SCDDRV_CanNotSelectInst
	.type	SCDDRV_CanNotSelectInst, %function
SCDDRV_CanNotSelectInst:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r3, .L1220
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #68]
	cmp	r3, #0
	beq	.L1210
	add	r2, r3, #262144
	ldr	r1, [r2, #228]
	cmp	r1, #0
	beq	.L1210
	ldr	r2, [r2, #220]
	cmp	r2, #1
	beq	.L1210
	add	r2, r3, #32
	ldr	ip, [r3, #16]
	sub	r3, fp, #24
	ldmia	r2, {r0, r1, r2}
	cmp	ip, #19
	stmia	r3, {r0, r1, r2}
	beq	.L1210
	mov	r1, r3
	mov	r0, ip
	bl	SCDDRV_IsSCDByPass
	adds	r0, r0, #0
	movne	r0, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1210:
	mov	r0, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1221:
	.align	2
.L1220:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_CanNotSelectInst, .-SCDDRV_CanNotSelectInst
	.align	2
	.global	SM_DoNextInstance
	.type	SM_DoNextInstance, %function
SM_DoNextInstance:
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
	ldr	r2, .L1235
	mov	r3, r0, asl #2
	str	r1, [fp, #-48]
	add	r1, r2, r3
	mov	r6, r0
	ldr	r2, [r1, #324]
	cmp	r2, #0
	beq	.L1223
	cmp	r2, #1
	beq	.L1224
.L1231:
	mvn	r0, #2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1223:
	ldr	r2, .L1235
	rsb	r3, r3, r0, lsl #6
	ldr	r9, .L1235+4
	mov	r5, #32
	add	r3, r2, r3
	ldr	r4, [r3, #44]
	b	.L1230
.L1226:
	subs	r5, r5, #1
	beq	.L1231
.L1230:
	add	r3, r4, #1
	mov	r1, r6
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #27
	add	r3, r3, r4
	and	r3, r3, #31
	rsb	r4, r4, r3
	mov	r0, r4
	bl	SCDDRV_CanNotSelectInst
	cmp	r0, #0
	bne	.L1226
	ldr	r3, .L1235
	ldr	r2, [r9]
	add	r3, r3, r4, lsl #3
	ldr	r10, [r3, #68]
	blx	r2
	mov	ip, #0
	add	r8, r10, #262144
	ldr	r1, [r8, #280]
	subs	r1, r0, r1
	bmi	.L1227
	ldrsh	lr, [r10, #2]
	cmp	lr, #1
	beq	.L1233
.L1227:
	str	r0, [r8, #280]
	ldrsb	r1, [r10]
	cmp	r1, #1
	strneb	ip, [r10, #1]
	beq	.L1234
.L1229:
	ldr	r3, .L1235+8
	mov	r1, r6
	mov	r0, r10
	ldr	ip, [r3, r4, asl #2]
	add	ip, ip, #294912
	ldr	ip, [ip, #1200]
	str	ip, [r8, #432]
	bl	CutStreamWithSCD
	cmn	r0, #6
	mov	r7, r0
	movne	r1, #0
	moveq	r1, #1
	cmp	r0, #0
	strb	r1, [r10]
	bne	.L1226
	ldr	r2, [fp, #-48]
	mov	r3, #1
	ldr	r0, .L1235+12
	mov	r1, r3
	movw	ip, #4053
	str	r4, [r2]
	add	r2, r0, r4, lsl #2
	str	r3, [r8, #228]
	mov	r0, r4
	ldr	r3, .L1235+16
	str	ip, [sp]
	bl	RecordPOS
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1233:
	cmp	r1, #199
	bls	.L1226
	b	.L1227
.L1234:
	mov	r0, r10
	bl	SCDDRV_ProcessSegFull
	b	.L1229
.L1224:
	mov	r3, #2
	mvn	r0, #2
	str	r3, [r1, #324]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1236:
	.align	2
.L1235:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LANCHOR0+468
	.word	.LANCHOR3+496
	UNWIND(.fnend)
	.size	SM_DoNextInstance, .-SM_DoNextInstance
	.align	2
	.type	SCDDRV_ActivateSCD.part.12, %function
SCDDRV_ActivateSCD.part.12:
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
	sub	r1, fp, #32
	mov	r6, r0
	bl	SM_DoNextInstance
	cmp	r0, #0
	bne	.L1237
	ldr	r4, .L1240
	mov	r7, r6, asl #2
	mov	r5, r6, asl #6
	ldr	r2, [fp, #-32]
	rsb	r3, r7, r5
	cmp	r6, #0
	add	r3, r4, r3
	rsb	r5, r7, r5
	str	r2, [r3, #44]
	moveq	r3, #1
	streq	r3, [r4, #48]
	add	r4, r4, r5
	ldr	r3, .L1240+4
	ldr	r3, [r3]
	blx	r3
	movw	r3, #4296
	ldr	r2, .L1240+8
	ldr	r1, .L1240+12
	str	r0, [r4, #52]
	mov	r0, #26
	bl	dprint_vfmw
.L1237:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1241:
	.align	2
.L1240:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+516
	.word	.LC65
	UNWIND(.fnend)
	.size	SCDDRV_ActivateSCD.part.12, .-SCDDRV_ActivateSCD.part.12
	.align	2
	.global	SM_AddMatchMode
	.type	SM_AddMatchMode, %function
SM_AddMatchMode:
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
	ldr	r6, .L1258
	mov	r5, #0
	ldr	r7, .L1258+4
	b	.L1247
.L1246:
	bl	dprint_vfmw
.L1255:
	add	r4, r4, #262144
	mov	r3, #0
	str	r3, [r4, #224]
.L1243:
	add	r5, r5, #1
	cmp	r5, #32
	beq	.L1257
.L1247:
	ldr	r4, [r6, r5, asl #3]
	cmp	r4, #0
	beq	.L1243
	ldr	r3, [r4, #44]
	mov	r0, #0
	ldr	r1, .L1258+8
	cmp	r3, r0
	beq	.L1243
	ldr	ip, [r7]
	ldr	r3, [r7, #4]
	cmp	ip, #1
	mov	r2, ip
	bne	.L1246
	cmp	r3, #1
	beq	.L1255
	cmp	r3, #2
	addeq	r4, r4, #262144
	streq	ip, [r4, #224]
	bne	.L1246
	add	r5, r5, #1
	cmp	r5, #32
	bne	.L1247
.L1257:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1259:
	.align	2
.L1258:
	.word	.LANCHOR0+68
	.word	g_DspDrvState
	.word	.LC66
	UNWIND(.fnend)
	.size	SM_AddMatchMode, .-SM_AddMatchMode
	.align	2
	.global	SCDDRV_RecordGlobalState
	.type	SCDDRV_RecordGlobalState, %function
SCDDRV_RecordGlobalState:
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
	ldr	r3, .L1266
	mov	r4, r0
	ldr	r3, [r3]
	blx	r3
	mov	lr, r4, asl #2
	ldr	ip, .L1266+4
	mov	r4, r4, asl #6
	rsb	r3, lr, r4
	add	r3, ip, r3
	add	r6, r3, #48
	ldr	r2, [r3, #48]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r3, r3, #40
	ldr	r1, [r3, #4]
	rsb	r4, lr, r4
	add	r5, r1, #49920
	add	r4, ip, r4
	add	r5, r5, #80
	cmp	r2, r5
	strhi	r2, [r3, #4]
	mov	r5, #0
	str	r5, [r4, #48]
	movhi	r1, r2
	rsb	r1, r1, r0
	ldrls	r6, [r6, #4]
	movhi	r6, #0
	cmp	r1, #1000
	rsb	r0, r2, r0
	add	r0, r0, r6
	str	r0, [r4, #52]
	ldmccfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r3, #1000
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	str	r5, [r4, #44]
	str	r0, [r4, #56]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1267:
	.align	2
.L1266:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	UNWIND(.fnend)
	.size	SCDDRV_RecordGlobalState, .-SCDDRV_RecordGlobalState
	.align	2
	.global	SCDDRV_MoveRawByOmxPath
	.type	SCDDRV_MoveRawByOmxPath, %function
SCDDRV_MoveRawByOmxPath:
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
	ldr	r3, .L1278
	add	r0, r3, r0, lsl #3
	ldr	r4, [r0, #68]
	ldr	r0, [r4, #56]
	cmp	r0, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	adds	r5, r4, #80
	beq	.L1271
	add	r2, r4, #98304
	ldr	r3, [r2, #84]
	ldr	r2, [r2, #80]
	subs	r3, r3, r2
	addmi	r3, r3, #1024
.L1274:
	ldrsb	r5, [r4, #2]
	cmp	r5, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r2, [r4, #64]
	cmp	r2, r3
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	mov	r0, r4
	bl	SM_MoveRawData
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r0, r5
	ldr	r1, .L1278+4
	bl	dprint_vfmw
	add	r4, r4, #262144
	ldr	r0, [r4, #212]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SM_Reset
.L1271:
	ldr	r1, .L1278+8
	bl	dprint_vfmw
	mov	r3, r5
	b	.L1274
.L1279:
	.align	2
.L1278:
	.word	.LANCHOR0
	.word	.LC67
	.word	.LC68
	UNWIND(.fnend)
	.size	SCDDRV_MoveRawByOmxPath, .-SCDDRV_MoveRawByOmxPath
	.align	2
	.global	SM_SCDIntServeProc
	.type	SM_SCDIntServeProc, %function
SM_SCDIntServeProc:
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
	subs	r4, r0, #0
	beq	.L1298
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1298:
	ldr	r6, .L1304
	ldr	r5, .L1304+4
	ldr	r3, [r6, #12]
	blx	r3
	ldr	r0, [r5, #64]
	add	r0, r0, #2112
	bl	MEM_ReadPhyWord
	tst	r0, #1
	bne	.L1299
.L1282:
	ldr	r3, .L1304+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1286
	mov	r1, #0
	mov	r0, r1
	bl	VDH_Notify_ModuleIdle
.L1286:
	ldr	r3, [r6, #16]
	mov	r0, #0
	blx	r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1299:
	ldr	r0, [r5, #64]
	mov	r1, #1
	add	r0, r0, #2080
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldr	r9, [r5, #44]
	ldr	r0, [r5, #40]
	add	r3, r5, r9, lsl #3
	ldr	r8, [r3, #68]
	cmp	r8, #0
	cmpne	r0, #0
	moveq	r7, #1
	movne	r7, #0
	beq	.L1300
	ldr	r3, .L1304+12
	movw	r2, #4179
	mov	r1, #2
	str	r2, [sp]
	mov	r0, r9
	add	r2, r5, #596
	bl	RecordPOS
	mov	r0, r7
	bl	SCDDRV_RecordGlobalState
	ldr	r3, [r5, #48]
	cmp	r3, #1
	beq	.L1301
.L1284:
	ldr	r3, [r6, #128]
	mov	r0, #1
	blx	r3
	ldr	r3, [r6, #128]
	mov	r0, #0
	blx	r3
	b	.L1282
.L1301:
	add	r10, r8, #262144
	ldr	r3, [r10, #228]
	cmp	r3, #1
	beq	.L1302
.L1285:
	mov	r4, #0
	sub	r1, fp, #48
	str	r4, [r10, #220]
	mov	r0, r4
	bl	SM_DoNextInstance
	cmp	r0, r4
	bne	.L1303
	ldr	r2, [fp, #-48]
	mov	r1, #1
	ldr	r3, [r6]
	str	r1, [r5, #48]
	str	r2, [r5, #44]
	blx	r3
	str	r0, [r5, #52]
	b	.L1284
.L1300:
	mov	r0, r4
	bl	SCDDRV_SetStateIdle.part.0
	b	.L1282
.L1303:
	mov	r0, r4
	bl	SCDDRV_SetStateIdle.part.0
	b	.L1284
.L1302:
	mov	r1, r7
	mov	r0, r8
	bl	ProcessScdReturn
	mov	r0, r9
	bl	SCDDRV_MoveRawByOmxPath
	b	.L1285
.L1305:
	.align	2
.L1304:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	g_HalDisable
	.word	.LANCHOR3+536
	UNWIND(.fnend)
	.size	SM_SCDIntServeProc, .-SM_SCDIntServeProc
	.align	2
	.global	SCDDRV_CheckDevice
	.type	SCDDRV_CheckDevice, %function
SCDDRV_CheckDevice:
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
	subs	r6, r0, #0
	bne	.L1315
	ldr	r4, .L1318
	movw	r3, #4229
	str	r6, [sp]
	mov	r0, #26
	ldr	r2, .L1318+4
	ldr	ip, [r4, #48]
	ldr	r1, .L1318+8
	str	ip, [sp, #4]
	bl	dprint_vfmw
	ldr	r5, [r4, #48]
	cmp	r5, #0
	beq	.L1317
	movw	r3, #4239
	ldr	r2, .L1318+4
	ldr	r1, .L1318+8
	mov	r0, #26
	str	r5, [sp, #4]
	str	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, .L1318+12
	ldr	r3, [r3]
	blx	r3
	ldr	r3, [r4, #52]
	cmp	r0, r3
	strcc	r0, [r4, #52]
	bcc	.L1310
	rsb	r0, r3, r0
	cmp	r0, #2000
	bls	.L1310
	ldr	r2, [r4, #44]
	mov	r3, r6
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1318+16
	bl	dprint_vfmw
	ldr	r3, .L1318+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1311
	mov	r1, r6
	mov	r0, r6
	bl	VDH_Reset_Module
.L1312:
	mov	r0, #0
	mov	r5, #0
	bl	SCDDRV_SetStateIdle.part.0
	ldr	r0, [r4, #44]
	add	r4, r4, r0, lsl #3
	ldr	r3, [r4, #68]
	cmp	r3, #0
	addne	r3, r3, #262144
	movne	r2, #0
	strne	r2, [r3, #220]
	bl	DeleteLastSendRaw
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1310:
	mov	r2, #0
	movw	r3, #4276
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1318+4
	mov	r5, #1
	ldr	r1, .L1318+24
	bl	dprint_vfmw
.L1316:
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1317:
	str	r5, [sp]
	movw	r3, #4233
	ldr	r2, .L1318+4
	mov	r0, #26
	ldr	r1, .L1318+28
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1311:
	mov	r0, r6
	bl	ResetSCD
	b	.L1312
.L1315:
	mvn	r5, #0
	b	.L1316
.L1319:
	.align	2
.L1318:
	.word	.LANCHOR0
	.word	.LANCHOR3+556
	.word	.LC69
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC71
	.word	g_HalDisable
	.word	.LC72
	.word	.LC70
	UNWIND(.fnend)
	.size	SCDDRV_CheckDevice, .-SCDDRV_CheckDevice
	.align	2
	.global	SCDDRV_ActivateSCD
	.type	SCDDRV_ActivateSCD, %function
SCDDRV_ActivateSCD:
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
	cmp	r0, #0
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SCDDRV_ActivateSCD.part.12
	UNWIND(.fnend)
	.size	SCDDRV_ActivateSCD, .-SCDDRV_ActivateSCD
	.align	2
	.global	SM_Wakeup
	.type	SM_Wakeup, %function
SM_Wakeup:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r5, .L1333
	mov	r4, #0
	b	.L1324
.L1323:
	add	r4, r4, #1
	cmp	r4, #32
	beq	.L1332
.L1324:
	ldr	r3, [r5, r4, asl #3]
	cmp	r3, #0
	add	r2, r3, #262144
	beq	.L1323
	ldr	r3, [r2, #228]
	cmp	r3, #1
	bne	.L1323
	mov	r0, r4
	add	r4, r4, #1
	bl	FillRawData
	cmp	r4, #32
	bne	.L1324
.L1332:
	mov	r2, #1
	mov	r3, #0
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1333+4
	ldr	r1, .L1333+8
	bl	dprint_vfmw
	mov	r0, #0
	bl	SCDDRV_CheckDevice
	subs	r4, r0, #0
	beq	.L1325
	mov	r2, #0
	movw	r3, #4325
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1333+4
	ldr	r1, .L1333+12
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1325:
	str	r4, [sp]
	movw	r3, #4320
	ldr	r2, .L1333+4
	mov	r0, #26
	ldr	r1, .L1333+16
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SCDDRV_ActivateSCD.part.12
.L1334:
	.align	2
.L1333:
	.word	.LANCHOR0+68
	.word	.LANCHOR3+576
	.word	.LC73
	.word	.LC74
	.word	.LC75
	UNWIND(.fnend)
	.size	SM_Wakeup, .-SM_Wakeup
	.align	2
	.global	WaitSCDFinish
	.type	WaitSCDFinish, %function
WaitSCDFinish:
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
	ldr	r6, .L1345
	mov	r3, r0, asl #2
	rsb	r0, r3, r0, lsl #6
	add	r0, r6, r0
	ldr	r2, [r0, #48]
	cmp	r2, #1
	beq	.L1336
.L1338:
	mov	r0, #0
.L1337:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1336:
	ldr	r7, .L1345+4
	add	r6, r6, r3
	movw	r5, #41248
	movt	r5, 7
	ldr	r3, [r7]
	blx	r3
	mov	r4, r0
	b	.L1342
.L1341:
	subs	r5, r5, #1
	beq	.L1344
.L1342:
	ldr	r0, [r6, #64]
	add	r0, r0, #2112
	bl	MEM_ReadPhyWord
	tst	r0, #1
	bne	.L1338
	ldr	r3, [r7]
	blx	r3
	cmp	r4, r0
	rsb	r2, r0, r4
	rsb	r3, r4, r0
	mvnhi	r3, r2
	cmp	r3, #1000
	bls	.L1341
	str	r3, [sp]
	mov	r2, r4
	mov	r3, r0
	ldr	r1, .L1345+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1337
.L1344:
	mvn	r0, #6
	b	.L1337
.L1346:
	.align	2
.L1345:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC76
	UNWIND(.fnend)
	.size	WaitSCDFinish, .-WaitSCDFinish
	.align	2
	.global	PrintScdRawState
	.type	PrintScdRawState, %function
PrintScdRawState:
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
	cmp	r0, #31
	mov	r5, r0
	mov	r6, r1
	ldmhifd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r0, #26
	bl	IsDprintTypeEnable
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, .L1361
	mov	r2, r5
	ldr	r1, .L1361+4
	mov	r0, #26
	add	r3, r3, r5, lsl #3
	ldr	r8, [r3, #68]
	bl	dprint_vfmw
	ldr	r1, .L1361+8
	mov	r0, #26
	add	r7, r8, #98304
	ldr	r2, [r7, #80]
	bl	dprint_vfmw
	ldr	r2, [r7, #84]
	ldr	r1, .L1361+12
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r7, #88]
	ldr	r1, .L1361+16
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r7, #92]
	ldr	r1, .L1361+20
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r7, #96]
	ldr	r1, .L1361+24
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r6, #1
	beq	.L1351
.L1355:
	mov	r2, r5
	ldr	r1, .L1361+28
	mov	r0, #26
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1351:
	cmn	r8, #80
	beq	.L1352
	ldr	r4, [r7, #80]
	ldr	r7, [r7, #84]
	subs	r7, r7, r4
	addmi	r7, r7, #1024
	cmp	r7, #0
	ble	.L1355
	mov	r3, r4, asl #7
	mov	r6, #0
	sub	r3, r3, r4, asl #5
	add	r4, r8, r3
.L1354:
	ldr	r2, [r4, #84]
	mov	r0, #26
	ldr	r1, .L1361+32
	add	r6, r6, #1
	bl	dprint_vfmw
	ldrd	r2, [r4, #120]
	ldr	r1, .L1361+36
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #92]
	ldr	r1, .L1361+40
	mov	r0, #26
	bl	dprint_vfmw
	ldrd	r2, [r4, #144]
	ldr	r1, .L1361+44
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r6, r7
	add	r4, r4, #96
	bne	.L1354
	b	.L1355
.L1352:
	movw	r3, #4392
	ldr	r2, .L1361+48
	ldr	r1, .L1361+52
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1355
.L1362:
	.align	2
.L1361:
	.word	.LANCHOR0
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC84
	.word	.LC85
	.word	.LC86
	.word	.LC87
	.word	.LANCHOR3+588
	.word	.LC88
	UNWIND(.fnend)
	.size	PrintScdRawState, .-PrintScdRawState
	.align	2
	.global	PrintScdSegState
	.type	PrintScdSegState, %function
PrintScdSegState:
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
	cmp	r0, #31
	mov	r6, r0
	mov	r7, r1
	ldmhifd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r0, #26
	bl	IsDprintTypeEnable
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, .L1377
	mov	r2, r6
	ldr	r1, .L1377+4
	mov	r0, #26
	add	r3, r3, r6, lsl #3
	ldr	r5, [r3, #68]
	bl	dprint_vfmw
	ldr	r1, .L1377+8
	mov	r0, #26
	add	r4, r5, #262144
	add	r8, r5, #98304
	ldr	r2, [r4, #112]
	bl	dprint_vfmw
	ldr	r2, [r4, #116]
	ldr	r1, .L1377+12
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #124]
	ldr	r1, .L1377+16
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #128]
	ldr	r1, .L1377+20
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r8, #104]
	ldr	r1, .L1377+24
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #132]
	ldr	r1, .L1377+28
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #136]
	ldr	r1, .L1377+32
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #140]
	ldr	r1, .L1377+36
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r7, #1
	beq	.L1367
.L1368:
	mov	r2, r6
	ldr	r1, .L1377+40
	mov	r0, #26
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1367:
	cmn	r8, #104
	beq	.L1368
	ldr	r2, [r4, #112]
	ldr	r8, [r4, #116]
	rsb	r8, r2, r8
	ubfx	r8, r8, #0, #11
	cmp	r8, #0
	ble	.L1368
	mov	r3, r2, asl #6
	mov	r7, #0
	add	r4, r3, r2, lsl #4
	add	r4, r4, #98304
	add	r4, r4, #124
	add	r4, r5, r4
.L1369:
	ldr	r2, [r4]
	mov	r0, #26
	ldr	r1, .L1377+44
	add	r7, r7, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #-12]
	ldr	r1, .L1377+48
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #4]
	ldr	r1, .L1377+52
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #8]
	ldr	r1, .L1377+56
	mov	r0, #26
	bl	dprint_vfmw
	ldrsb	r2, [r4, #-8]
	ldr	r1, .L1377+60
	mov	r0, #26
	bl	dprint_vfmw
	ldrb	r2, [r4, #-7]	@ zero_extendqisi2
	ldr	r1, .L1377+64
	mov	r0, #26
	bl	dprint_vfmw
	ldrd	r2, [r4, #12]
	ldr	r1, .L1377+68
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r8, r7
	add	r4, r4, #80
	bne	.L1369
	b	.L1368
.L1378:
	.align	2
.L1377:
	.word	.LANCHOR0
	.word	.LC89
	.word	.LC90
	.word	.LC91
	.word	.LC92
	.word	.LC93
	.word	.LC94
	.word	.LC95
	.word	.LC96
	.word	.LC97
	.word	.LC98
	.word	.LC99
	.word	.LC100
	.word	.LC101
	.word	.LC102
	.word	.LC103
	.word	.LC104
	.word	.LC105
	UNWIND(.fnend)
	.size	PrintScdSegState, .-PrintScdSegState
	.global	g_pScdDrvParamBase
	.global	s_ScdRegResetOKPhyAddr
	.global	s_ScdRegResetPhyAddr
	.global	s_ScdRegPhyBaseAddr
	.global	g_ScdDrvParam
	.global	s_SmIIS
	.global	ForceRelease
	.global	g_hex_flag
	.global	g_hex_len
	.global	g_hex_base_addr
	.global	g_hex_base_vir_addr
	.section	.rodata
	.align	2
.LANCHOR3 = . + 0
	.type	__func__.53821, %object
	.size	__func__.53821, 19
__func__.53821:
	.ascii	"SCDDRV_LoadDspCode\000"
	.space	1
	.type	__func__.53893, %object
	.size	__func__.53893, 16
__func__.53893:
	.ascii	"DeleteRawPacket\000"
	.type	__FUNCTION__.54003, %object
	.size	__FUNCTION__.54003, 17
__FUNCTION__.54003:
	.ascii	"ReleaseStreamSeg\000"
	.space	3
	.type	__func__.54067, %object
	.size	__func__.54067, 14
__func__.54067:
	.ascii	"SM_OpenSCDDrv\000"
	.space	2
	.type	__func__.54151, %object
	.size	__func__.54151, 16
__func__.54151:
	.ascii	"SM_CopyRawToSeg\000"
	.type	__func__.54402, %object
	.size	__func__.54402, 17
__func__.54402:
	.ascii	"GetMpeg4ModeFlag\000"
	.space	3
	.type	__func__.54429, %object
	.size	__func__.54429, 21
__func__.54429:
	.ascii	"ProcessMpeg4ScdUpMsg\000"
	.space	3
.LC0:
	.byte	0
	.byte	0
	.byte	1
	.byte	30
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	30
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-70
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-70
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	96
	.byte	0
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-1
	.byte	0
	.byte	0
	.byte	0
	.type	__func__.54477, %object
	.size	__func__.54477, 17
__func__.54477:
	.ascii	"FillEopRawStream\000"
	.space	3
.LC1:
	.byte	0
	.byte	0
	.byte	1
	.byte	11
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-73
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	-73
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	98
	.byte	0
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	__func__.54504, %object
	.size	__func__.54504, 17
__func__.54504:
	.ascii	"FillEosRawStream\000"
	.space	3
	.type	__func__.54528, %object
	.size	__func__.54528, 17
__func__.54528:
	.ascii	"FillVC1ExtraData\000"
	.space	3
	.type	__func__.54533, %object
	.size	__func__.54533, 19
__func__.54533:
	.ascii	"FillDIVX3ExtraData\000"
	.space	1
	.type	__func__.54538, %object
	.size	__func__.54538, 19
__func__.54538:
	.ascii	"FillREAL8ExtraData\000"
	.space	1
	.type	__func__.54546, %object
	.size	__func__.54546, 14
__func__.54546:
	.ascii	"FillExtraData\000"
	.space	2
	.type	__func__.53907, %object
	.size	__func__.53907, 24
__func__.53907:
	.ascii	"DeleteRawPacketInBuffer\000"
	.type	__FUNCTION__.54041, %object
	.size	__FUNCTION__.54041, 9
__FUNCTION__.54041:
	.ascii	"SM_Reset\000"
	.space	3
	.type	__FUNCTION__.54467, %object
	.size	__FUNCTION__.54467, 12
__FUNCTION__.54467:
	.ascii	"FillRawData\000"
	.type	__FUNCTION__.54659, %object
	.size	__FUNCTION__.54659, 18
__FUNCTION__.54659:
	.ascii	"SM_DoNextInstance\000"
	.space	2
	.type	__func__.54705, %object
	.size	__func__.54705, 19
__func__.54705:
	.ascii	"SCDDRV_ActivateSCD\000"
	.space	1
	.type	__FUNCTION__.54692, %object
	.size	__FUNCTION__.54692, 19
__FUNCTION__.54692:
	.ascii	"SM_SCDIntServeProc\000"
	.space	1
	.type	__func__.54699, %object
	.size	__func__.54699, 19
__func__.54699:
	.ascii	"SCDDRV_CheckDevice\000"
	.space	1
	.type	__func__.54714, %object
	.size	__func__.54714, 10
__func__.54714:
	.ascii	"SM_Wakeup\000"
	.space	2
	.type	__FUNCTION__.54736, %object
	.size	__FUNCTION__.54736, 17
__FUNCTION__.54736:
	.ascii	"PrintScdRawState\000"
	.data
	.align	2
.LANCHOR1 = . + 0
.LANCHOR2 = . + 16368
	.type	g_avsp_firmware, %object
	.size	g_avsp_firmware, 17920
g_avsp_firmware:
	.word	0
	.word	16283648
	.word	16349954
	.word	9468936
	.word	-252085482
	.word	9468688
	.word	9468692
	.word	16284426
	.word	9468680
	.word	18807566
	.word	-258442240
	.word	10517258
	.word	18807566
	.word	-258442239
	.word	10517258
	.word	18807566
	.word	-258442238
	.word	10517258
	.word	18807566
	.word	-258442237
	.word	10517258
	.word	18807566
	.word	-258442236
	.word	10517258
	.word	18807566
	.word	-258442235
	.word	10517258
	.word	18807566
	.word	-258442234
	.word	10517258
	.word	18807566
	.word	-258442233
	.word	10517258
	.word	-251200754
	.word	10517258
	.word	17758990
	.word	33128448
	.word	24738824
	.word	-1879048192
	.word	16349954
	.word	0
	.word	18512896
	.word	33390592
	.word	24738817
	.word	-250447311
	.word	9468672
	.word	17988136
	.word	-795837688
	.word	12090128
	.word	18807566
	.word	24967950
	.word	-249398743
	.word	33259520
	.word	554859056
	.word	-258966784
	.word	19561007
	.word	-235307008
	.word	-1063027960
	.word	16349968
	.word	0
	.word	11041536
	.word	0
	.word	1073741824
	.word	33259520
	.word	554859057
	.word	9468672
	.word	0
	.word	-1342177280
	.word	0
	.word	33128448
	.word	-1592624595
	.word	-258966776
	.word	12090128
	.word	0
	.word	17988137
	.word	9468680
	.word	16349968
	.word	17988143
	.word	-258966784
	.word	0
	.word	33521664
	.word	-1879048192
	.word	0
	.word	-1610612736
	.word	-248874449
	.word	9468688
	.word	9468692
	.word	11041536
	.word	0
	.word	0
	.word	0
	.word	286948352
	.word	9467906
	.word	33128448
	.word	-1320519377
	.word	1630697896
	.word	33128448
	.word	-786269183
	.word	17988140
	.word	9468680
	.word	12090128
	.word	21953294
	.word	19400197
	.word	33128448
	.word	-1059883006
	.word	33062912
	.word	-1073741824
	.word	1358526466
	.word	-1342177280
	.word	-1879048192
	.word	17988009
	.word	1620081416
	.word	1354267408
	.word	21953294
	.word	19400216
	.word	33128448
	.word	-2133624830
	.word	33062912
	.word	-2147483648
	.word	-2131134462
	.word	19400222
	.word	33128448
	.word	0
	.word	19036462
	.word	33390592
	.word	33398784
	.word	1092253959
	.word	33128448
	.word	1362626056
	.word	17988013
	.word	9468680
	.word	12090128
	.word	21429006
	.word	1092253999
	.word	33128448
	.word	-250447444
	.word	9468680
	.word	12090128
	.word	24673282
	.word	-250447445
	.word	814775048
	.word	12090128
	.word	0
	.word	-785744896
	.word	556956675
	.word	33128448
	.word	-235298816
	.word	-235290624
	.word	25000964
	.word	-2147483648
	.word	33128448
	.word	-1050147328
	.word	18351619
	.word	18875907
	.word	554858927
	.word	33128448
	.word	-235290624
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	-1845493760
	.word	23594500
	.word	18875906
	.word	554858927
	.word	33128448
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	872415232
	.word	-2147483648
	.word	18351646
	.word	24926480
	.word	-2124785392
	.word	-2147483648
	.word	0
	.word	19028272
	.word	20601264
	.word	554858927
	.word	10517258
	.word	546339592
	.word	0
	.word	-268435456
	.word	-1592100601
	.word	12090128
	.word	33128448
	.word	1634207232
	.word	18351619
	.word	18875907
	.word	554859050
	.word	33128448
	.word	-235290624
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	17988139
	.word	9468680
	.word	0
	.word	-771751936
	.word	23594500
	.word	18875906
	.word	554859050
	.word	33128448
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	17988139
	.word	9468680
	.word	0
	.word	-1543503872
	.word	1073741824
	.word	18351646
	.word	24926480
	.word	1096440080
	.word	-2147483648
	.word	17988138
	.word	19028272
	.word	20601264
	.word	536870912
	.word	10517258
	.word	9468680
	.word	17988139
	.word	9468680
	.word	0
	.word	-1879048192
	.word	1366850566
	.word	33398784
	.word	17987886
	.word	33398784
	.word	33398784
	.word	-518882770
	.word	9468680
	.word	16349968
	.word	0
	.word	-536870912
	.word	1903720450
	.word	1092093440
	.word	17988010
	.word	9468680
	.word	12090128
	.word	18807566
	.word	33259520
	.word	293436421
	.word	25000967
	.word	-1055753810
	.word	9468680
	.word	12090128
	.word	0
	.word	33460224
	.word	33460224
	.word	33198080
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1011712
	.word	0
	.word	0
	.word	1013760
	.word	18687
	.word	0
	.word	0
	.word	18688
	.word	0
	.word	0
	.word	103084
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	102700
	.word	0
	.word	18432
	.word	916608
	.word	0
	.word	1027074
	.word	0
	.word	1013760
	.word	18432
	.word	916620
	.word	908352
	.word	1027075
	.word	0
	.word	1013760
	.word	105964
	.word	0
	.word	1013760
	.word	0
	.word	1031171
	.word	916484
	.word	1031173
	.word	98348
	.word	1013760
	.word	904428
	.word	1027075
	.word	0
	.word	1013760
	.word	0
	.word	1013760
	.word	1027075
	.word	916484
	.word	1031173
	.word	0
	.word	1013760
	.word	1035269
	.word	1031168
	.word	916712
	.word	1031172
	.word	23807
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	98348
	.word	1013760
	.word	916484
	.word	1031170
	.word	1007616
	.word	1018885
	.word	18687
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	1018880
	.word	1007616
	.word	18432
	.word	20480
	.word	916688
	.word	1031175
	.word	23552
	.word	916696
	.word	1027078
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	108112
	.word	917096
	.word	1031174
	.word	917076
	.word	1027078
	.word	25600
	.word	1018887
	.word	23553
	.word	908752
	.word	19456
	.word	22528
	.word	1013760
	.word	108112
	.word	917096
	.word	1031175
	.word	917076
	.word	1027079
	.word	25601
	.word	108108
	.word	917076
	.word	222628
	.word	19456
	.word	917068
	.word	917072
	.word	1027086
	.word	917068
	.word	1027080
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	23552
	.word	917068
	.word	1027080
	.word	0
	.word	0
	.word	1013760
	.word	1027080
	.word	23552
	.word	0
	.word	1013760
	.word	19457
	.word	20480
	.word	916756
	.word	916908
	.word	916844
	.word	0
	.word	1027083
	.word	917068
	.word	1027082
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	916844
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	989193
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	989194
	.word	1018891
	.word	113316
	.word	112296
	.word	1031179
	.word	310092
	.word	113572
	.word	0
	.word	0
	.word	69916
	.word	0
	.word	23552
	.word	1013760
	.word	988170
	.word	23553
	.word	0
	.word	917068
	.word	1027085
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	916844
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	1013760
	.word	989195
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	1013760
	.word	989196
	.word	1018894
	.word	113316
	.word	112296
	.word	1031182
	.word	310092
	.word	113572
	.word	0
	.word	0
	.word	69916
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	1013760
	.word	988173
	.word	19456
	.word	917068
	.word	19456
	.word	917068
	.word	917064
	.word	1027086
	.word	0
	.word	0
	.word	1013760
	.word	1018894
	.word	23552
	.word	1027087
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	916712
	.word	23556
	.word	0
	.word	1027087
	.word	0
	.word	0
	.word	1013760
	.word	999424
	.word	999424
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65537
	.word	1900544
	.word	513
	.word	1537
	.word	352782197
	.word	352782197
	.word	65536
	.word	131074
	.word	4
	.word	0
	.word	65537
	.word	131073
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	2
	.word	327686
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	131072
	.word	1
	.word	131072
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65538
	.word	1
	.word	0
	.word	0
	.word	131072
	.word	131073
	.word	131073
	.word	1
	.word	131072
	.word	1
	.word	131072
	.word	131073
	.word	131073
	.word	1
	.word	0
	.word	0
	.word	2
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	3
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	524289
	.word	4196352
	.word	1048608
	.word	8396800
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65536
	.word	0
	.word	65536
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65536
	.word	65537
	.word	65537
	.word	1
	.word	65536
	.word	1
	.word	65536
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	131073
	.word	33554688
	.word	1073741828
	.word	132096
	.word	65540
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	g_h264_firmware, %object
	.size	g_h264_firmware, 17920
g_h264_firmware:
	.word	0
	.word	823064910
	.word	8419328
	.word	9239400
	.word	16349184
	.word	285670144
	.word	33128448
	.word	-1879048192
	.word	1342177280
	.word	0
	.word	8420384
	.word	8420386
	.word	8420387
	.word	8420388
	.word	8420389
	.word	8420390
	.word	8420391
	.word	8420393
	.word	8420394
	.word	8420395
	.word	8420392
	.word	8420396
	.word	8715424
	.word	8715428
	.word	8682668
	.word	8682542
	.word	8682671
	.word	268435456
	.word	8420385
	.word	-1342177280
	.word	24673452
	.word	-268435456
	.word	24673326
	.word	1610612736
	.word	17234198
	.word	0
	.word	-2130020076
	.word	33259520
	.word	1610612736
	.word	1091206148
	.word	33259520
	.word	1610612736
	.word	17234274
	.word	822770726
	.word	33259520
	.word	1610612736
	.word	33325056
	.word	1610612736
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-2147483648
	.word	268435456
	.word	16349184
	.word	277150492
	.word	9239324
	.word	805306368
	.word	8419328
	.word	0
	.word	805306368
	.word	8419328
	.word	17234796
	.word	17758530
	.word	0
	.word	-268435456
	.word	1342177280
	.word	-235044864
	.word	1628371250
	.word	0
	.word	17464358
	.word	0
	.word	-235044864
	.word	1610612736
	.word	0
	.word	536870912
	.word	1610612736
	.word	24673326
	.word	-536870912
	.word	17234200
	.word	0
	.word	-2130020076
	.word	33259520
	.word	1610612736
	.word	1091206148
	.word	33259520
	.word	1610612736
	.word	17234274
	.word	822770726
	.word	33259520
	.word	1610612736
	.word	33325056
	.word	1610612736
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	1879048192
	.word	0
	.word	16349184
	.word	277150492
	.word	9239324
	.word	805306368
	.word	8419328
	.word	0
	.word	805306368
	.word	8419328
	.word	17234796
	.word	17758530
	.word	0
	.word	-268435456
	.word	1342177280
	.word	-235044864
	.word	1628371250
	.word	0
	.word	17464358
	.word	0
	.word	-235044864
	.word	-536870912
	.word	268435456
	.word	536870912
	.word	1610612736
	.word	24673455
	.word	1610612736
	.word	24935457
	.word	1610612736
	.word	24706208
	.word	1610612736
	.word	0
	.word	536870912
	.word	16349184
	.word	17758488
	.word	8715034
	.word	9239322
	.word	0
	.word	17234228
	.word	17758984
	.word	17758980
	.word	268435456
	.word	0
	.word	-234913792
	.word	1342177280
	.word	21428994
	.word	23525654
	.word	21952790
	.word	20904718
	.word	17758520
	.word	0
	.word	17234288
	.word	18282794
	.word	18807142
	.word	-2147483648
	.word	19331382
	.word	17235072
	.word	18283652
	.word	0
	.word	8715418
	.word	0
	.word	9763996
	.word	33325056
	.word	-1610612736
	.word	18282774
	.word	824113430
	.word	9239710
	.word	17235098
	.word	1610612736
	.word	16349184
	.word	9239710
	.word	17235098
	.word	17758988
	.word	0
	.word	805306368
	.word	17235098
	.word	18283278
	.word	18807964
	.word	0
	.word	805306368
	.word	18283278
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33128448
	.word	-1879048192
	.word	33128448
	.word	-1861813906
	.word	33128448
	.word	822540652
	.word	33128448
	.word	-536870912
	.word	0
	.word	-1073741824
	.word	24673280
	.word	805306368
	.word	16349184
	.word	17234704
	.word	19037185
	.word	-2129725162
	.word	18282848
	.word	18807144
	.word	-2147483648
	.word	805306368
	.word	805306368
	.word	24673296
	.word	805306368
	.word	16349184
	.word	17234706
	.word	19037201
	.word	-2129725088
	.word	18282848
	.word	18807144
	.word	-2147483648
	.word	805306368
	.word	17235098
	.word	17759388
	.word	18283678
	.word	8715424
	.word	9239714
	.word	9764004
	.word	14711981
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	21952864
	.word	-2147483648
	.word	16349184
	.word	17234228
	.word	17758984
	.word	0
	.word	17758980
	.word	268435456
	.word	33062912
	.word	-2147483648
	.word	-235175936
	.word	0
	.word	-235110400
	.word	-2147483648
	.word	16349184
	.word	17234288
	.word	17758978
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	16349184
	.word	20904718
	.word	17758520
	.word	0
	.word	19331382
	.word	17235072
	.word	0
	.word	0
	.word	8715420
	.word	16349184
	.word	17235100
	.word	17758982
	.word	0
	.word	17758988
	.word	33259520
	.word	-805306368
	.word	17235100
	.word	17758982
	.word	805306368
	.word	18282774
	.word	18807062
	.word	1879048192
	.word	17235100
	.word	17758988
	.word	0
	.word	0
	.word	805306368
	.word	17235100
	.word	18283278
	.word	18807558
	.word	0
	.word	805306368
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33128448
	.word	1073741824
	.word	33128448
	.word	1073741824
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420524
	.word	24706208
	.word	-2147483648
	.word	17759396
	.word	33521664
	.word	-536870912
	.word	17235104
	.word	17759396
	.word	18282774
	.word	18807062
	.word	-1879048192
	.word	16349184
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	17235104
	.word	18283278
	.word	18807970
	.word	0
	.word	805306368
	.word	18283278
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33390592
	.word	0
	.word	536870912
	.word	33390592
	.word	-2147483648
	.word	268435456
	.word	1879048192
	.word	268435456
	.word	268435456
	.word	8420524
	.word	0
	.word	0
	.word	8420398
	.word	0
	.word	16349184
	.word	17234708
	.word	8715430
	.word	17758498
	.word	0
	.word	8715432
	.word	17758488
	.word	18807562
	.word	1073741824
	.word	0
	.word	805306368
	.word	8419328
	.word	16940070
	.word	17758514
	.word	0
	.word	-250676968
	.word	-268435456
	.word	1342177280
	.word	17758488
	.word	-268435456
	.word	1610612736
	.word	0
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715104
	.word	268435456
	.word	-536870912
	.word	8715106
	.word	16349184
	.word	17234708
	.word	805306368
	.word	10516480
	.word	8715108
	.word	17235088
	.word	8715110
	.word	17234214
	.word	8715120
	.word	17234244
	.word	8715118
	.word	16940060
	.word	-268435456
	.word	-805306368
	.word	17464339
	.word	-268435456
	.word	-1073741824
	.word	17464340
	.word	-268435456
	.word	-1323894504
	.word	17464322
	.word	0
	.word	-268435456
	.word	-1610612736
	.word	17464324
	.word	-268435456
	.word	268435456
	.word	24673285
	.word	-2147483648
	.word	17758486
	.word	805306368
	.word	24673316
	.word	-512197595
	.word	-1055983330
	.word	805306368
	.word	17758488
	.word	805306368
	.word	24673286
	.word	286193958
	.word	805306368
	.word	17758486
	.word	805306368
	.word	-536870912
	.word	17464323
	.word	0
	.word	8715328
	.word	17235110
	.word	18282776
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	17234710
	.word	8715330
	.word	1090976934
	.word	0
	.word	286718232
	.word	18807144
	.word	-2147483648
	.word	17235112
	.word	8715332
	.word	1090976934
	.word	0
	.word	555153688
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	17234712
	.word	8715334
	.word	-2130248538
	.word	0
	.word	823589144
	.word	18807144
	.word	-2147483648
	.word	17235090
	.word	8715336
	.word	16940202
	.word	8715338
	.word	17235092
	.word	33259520
	.word	-1610612736
	.word	0
	.word	8715340
	.word	17235094
	.word	8715342
	.word	16940203
	.word	8715344
	.word	17235096
	.word	33259520
	.word	805306368
	.word	0
	.word	8715346
	.word	-1593672675
	.word	17464365
	.word	0
	.word	-268435456
	.word	-1342177280
	.word	822770723
	.word	0
	.word	-268435456
	.word	-1879048192
	.word	17464353
	.word	0
	.word	8715348
	.word	-251495381
	.word	0
	.word	-268435456
	.word	1628077098
	.word	0
	.word	-268435456
	.word	268435456
	.word	17464327
	.word	-536870912
	.word	17464354
	.word	18807064
	.word	33128448
	.word	0
	.word	33128448
	.word	536870912
	.word	1091500310
	.word	268435456
	.word	1073741824
	.word	536870912
	.word	1073741824
	.word	0
	.word	8715350
	.word	17235112
	.word	1092024672
	.word	18807144
	.word	-2147483648
	.word	16940070
	.word	17758514
	.word	0
	.word	-268435456
	.word	8715352
	.word	17235112
	.word	0
	.word	-1055459048
	.word	18807144
	.word	-2147483648
	.word	0
	.word	8715354
	.word	-1056506712
	.word	0
	.word	-787023592
	.word	18807144
	.word	-2147483648
	.word	0
	.word	554173952
	.word	17827336
	.word	1879048192
	.word	-251200684
	.word	0
	.word	8420526
	.word	822609408
	.word	17827352
	.word	1879048192
	.word	-1073741824
	.word	11566081
	.word	-250446847
	.word	33325056
	.word	-805306368
	.word	17988609
	.word	33325056
	.word	-805306368
	.word	20085934
	.word	554203411
	.word	33128448
	.word	0
	.word	33128448
	.word	0
	.word	-2130151150
	.word	33128448
	.word	0
	.word	33128448
	.word	0
	.word	-519538416
	.word	33128448
	.word	0
	.word	33128448
	.word	16808209
	.word	33128448
	.word	0
	.word	-805306368
	.word	1091074311
	.word	33128448
	.word	-1342177280
	.word	33128448
	.word	-1342177280
	.word	-1593280239
	.word	33128448
	.word	-1342177280
	.word	33128448
	.word	-1342177280
	.word	-805306368
	.word	-1073741824
	.word	11566082
	.word	17827329
	.word	0
	.word	0
	.word	33390592
	.word	-805306368
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-805306368
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	0
	.word	33390592
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	268435456
	.word	33390592
	.word	-268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1073741824
	.word	-2128083448
	.word	0
	.word	0
	.word	33128448
	.word	805306368
	.word	-805306368
	.word	18282786
	.word	0
	.word	17758564
	.word	0
	.word	0
	.word	33128448
	.word	1879048192
	.word	0
	.word	286193948
	.word	0
	.word	33062912
	.word	-1073741824
	.word	-1342177280
	.word	-234881024
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-2128083448
	.word	0
	.word	0
	.word	33128448
	.word	536870912
	.word	-805306368
	.word	18282786
	.word	0
	.word	17758564
	.word	0
	.word	0
	.word	33128448
	.word	1610612736
	.word	0
	.word	286193964
	.word	0
	.word	33062912
	.word	-1342177280
	.word	-1610612736
	.word	-536870912
	.word	-268435456
	.word	268435456
	.word	8420354
	.word	-1073741824
	.word	11566088
	.word	-1073741824
	.word	33259520
	.word	1342177280
	.word	-805306368
	.word	-1073741824
	.word	11566089
	.word	0
	.word	33128448
	.word	268435456
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	-805306368
	.word	-805306368
	.word	-1073741824
	.word	11566091
	.word	-1073741824
	.word	33521664
	.word	-805306368
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	17234772
	.word	8420362
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	1879048192
	.word	1879048192
	.word	-1073741824
	.word	11566254
	.word	-268435456
	.word	33259520
	.word	-805306368
	.word	0
	.word	33521664
	.word	-805306368
	.word	16940206
	.word	0
	.word	1879048192
	.word	-1342177280
	.word	-1073741824
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	-1073741824
	.word	11566083
	.word	286193960
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	-1073741824
	.word	11566084
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566085
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	0
	.word	33128448
	.word	1610612736
	.word	-2147483648
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566086
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	286193946
	.word	20085764
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	825392131
	.word	33325056
	.word	-805306368
	.word	0
	.word	0
	.word	8420358
	.word	286193956
	.word	20085764
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566087
	.word	24673455
	.word	-805306368
	.word	822609409
	.word	17827329
	.word	1879048192
	.word	268435456
	.word	8420352
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420352
	.word	0
	.word	-1073741824
	.word	11566097
	.word	17827583
	.word	33325056
	.word	-1342177280
	.word	33259520
	.word	-1342177280
	.word	-1073741824
	.word	11566098
	.word	17827359
	.word	33325056
	.word	-1342177280
	.word	33259520
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-2147483648
	.word	268435456
	.word	16349184
	.word	17758992
	.word	19037202
	.word	-2130249450
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935424
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566099
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566101
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-1342177280
	.word	-1073741824
	.word	11566103
	.word	-268435456
	.word	33259520
	.word	-1342177280
	.word	-1073741824
	.word	11566104
	.word	-268435456
	.word	33259520
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566106
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827330
	.word	1879048192
	.word	20380500
	.word	11566107
	.word	822609408
	.word	17827330
	.word	1879048192
	.word	805306368
	.word	33062912
	.word	-1342177280
	.word	-805306368
	.word	11566109
	.word	-805306368
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566105
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566100
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566102
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	17234198
	.word	8420380
	.word	822541470
	.word	17759062
	.word	0
	.word	33521664
	.word	805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566108
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935452
	.word	805306368
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	33390592
	.word	268435456
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	17235102
	.word	17759062
	.word	33521664
	.word	-536870912
	.word	-268435456
	.word	0
	.word	8420380
	.word	805306368
	.word	268435456
	.word	8420380
	.word	24673455
	.word	-1342177280
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	268435456
	.word	8420368
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420368
	.word	0
	.word	-1073741824
	.word	11566113
	.word	17758528
	.word	33062912
	.word	268435456
	.word	-1073741824
	.word	536870912
	.word	33128448
	.word	1610612736
	.word	1073741824
	.word	33128448
	.word	1610612736
	.word	1879048192
	.word	33128448
	.word	1610612736
	.word	-1879048192
	.word	33128448
	.word	1610612736
	.word	0
	.word	33128448
	.word	-1879048192
	.word	805306368
	.word	33128448
	.word	-1879048192
	.word	1342177280
	.word	33128448
	.word	-1879048192
	.word	-2147483648
	.word	33128448
	.word	-1879048192
	.word	268435456
	.word	33128448
	.word	-1073741824
	.word	1610612736
	.word	33128448
	.word	-1073741824
	.word	268435456
	.word	536870912
	.word	8944674
	.word	-536870912
	.word	0
	.word	8944674
	.word	-536870912
	.word	268435456
	.word	8944674
	.word	-1073741824
	.word	11566112
	.word	-268435456
	.word	33259520
	.word	268435456
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-1610612736
	.word	805306368
	.word	16349184
	.word	17758994
	.word	19037216
	.word	-2130249376
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935440
	.word	268435456
	.word	16349184
	.word	17758992
	.word	19037202
	.word	-2130249450
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935424
	.word	268435456
	.word	822609408
	.word	1092254728
	.word	0
	.word	1879048192
	.word	0
	.word	8420388
	.word	8420389
	.word	24673285
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566116
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673316
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566117
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	16940035
	.word	17464324
	.word	-268435456
	.word	-268435456
	.word	-2147483648
	.word	8420390
	.word	24673285
	.word	-1610612736
	.word	24673316
	.word	-1610612736
	.word	554335270
	.word	-2147483648
	.word	8420390
	.word	554335236
	.word	-268435456
	.word	-2147483648
	.word	268435456
	.word	0
	.word	8420356
	.word	285375524
	.word	17464326
	.word	0
	.word	8420391
	.word	1359641640
	.word	33390592
	.word	1342177280
	.word	-1073741824
	.word	17758528
	.word	33259520
	.word	268435456
	.word	17464329
	.word	33390592
	.word	536870912
	.word	822609408
	.word	1092254731
	.word	0
	.word	1879048192
	.word	16940053
	.word	285899812
	.word	0
	.word	33521664
	.word	536870912
	.word	1879048192
	.word	16940041
	.word	285899786
	.word	0
	.word	33521664
	.word	-536870912
	.word	1879048192
	.word	16940053
	.word	285899812
	.word	0
	.word	33521664
	.word	-536870912
	.word	1879048192
	.word	24935446
	.word	1073741824
	.word	-1073741824
	.word	0
	.word	33259520
	.word	268435456
	.word	285899810
	.word	33390592
	.word	-536870912
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	17234772
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	16940055
	.word	17464344
	.word	8420394
	.word	8944683
	.word	554335266
	.word	33128448
	.word	1610612736
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566121
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935465
	.word	1610612736
	.word	-1073741824
	.word	11566122
	.word	285899810
	.word	33390592
	.word	1610612736
	.word	-1073741824
	.word	11566123
	.word	554335266
	.word	33390592
	.word	-1342177280
	.word	0
	.word	8420394
	.word	285899810
	.word	33128448
	.word	0
	.word	0
	.word	8420395
	.word	554335266
	.word	33390592
	.word	1073741824
	.word	1610612736
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935598
	.word	1610612736
	.word	0
	.word	554335274
	.word	0
	.word	-1073741824
	.word	805306368
	.word	33259520
	.word	268435456
	.word	805306368
	.word	33128448
	.word	1610612736
	.word	0
	.word	33128448
	.word	536870912
	.word	268435456
	.word	33128448
	.word	536870912
	.word	536870912
	.word	33128448
	.word	1073741824
	.word	1342177280
	.word	1879048192
	.word	1342177280
	.word	1879048192
	.word	268435456
	.word	285899810
	.word	33390592
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935598
	.word	-1342177280
	.word	0
	.word	554335275
	.word	0
	.word	-1073741824
	.word	805306368
	.word	33259520
	.word	268435456
	.word	805306368
	.word	33128448
	.word	-1342177280
	.word	0
	.word	33128448
	.word	1879048192
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	-1879048192
	.word	-1610612736
	.word	1879048192
	.word	-1610612736
	.word	1879048192
	.word	1610612736
	.word	17464354
	.word	286948379
	.word	33390592
	.word	293108762
	.word	-2147483648
	.word	1879048192
	.word	17464354
	.word	33390592
	.word	1879048192
	.word	-235044864
	.word	1879048192
	.word	-2147483648
	.word	536870912
	.word	-1073741824
	.word	24673282
	.word	-1073741824
	.word	-1073741824
	.word	17464362
	.word	268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-805306368
	.word	-805306368
	.word	24673282
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-268435456
	.word	285899810
	.word	17988635
	.word	33390592
	.word	536870912
	.word	-235044864
	.word	536870912
	.word	17464363
	.word	268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	268435456
	.word	-805306368
	.word	-805306368
	.word	24673282
	.word	268435456
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	268435456
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	1342177280
	.word	24673324
	.word	-536870912
	.word	1359641640
	.word	33390592
	.word	-1342177280
	.word	822609408
	.word	17827330
	.word	1879048192
	.word	-536870912
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-536870912
	.word	-1073741824
	.word	11566254
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	1879048192
	.word	1073741824
	.word	33128448
	.word	1879048192
	.word	1610612736
	.word	33128448
	.word	1879048192
	.word	805306368
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	-1073741824
	.word	-1342177280
	.word	-1073741824
	.word	-1073741824
	.word	16940206
	.word	33259520
	.word	1342177280
	.word	24673299
	.word	-1073741824
	.word	16940066
	.word	33128448
	.word	1879048192
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	-1073741824
	.word	-1073741824
	.word	11566115
	.word	805306368
	.word	33062912
	.word	268435456
	.word	-805306368
	.word	11566125
	.word	24935449
	.word	-1879048192
	.word	-1073741824
	.word	536870912
	.word	33259520
	.word	268435456
	.word	17827329
	.word	33128448
	.word	-1879048192
	.word	-805306368
	.word	-805306368
	.word	24673455
	.word	268435456
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	268435456
	.word	8420398
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420398
	.word	0
	.word	1073741824
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	268435456
	.word	8420527
	.word	0
	.word	1073741824
	.word	11565056
	.word	19331386
	.word	20379926
	.word	33390592
	.word	-536870912
	.word	20379926
	.word	11336516
	.word	11860806
	.word	19855676
	.word	0
	.word	805306368
	.word	11336520
	.word	9239370
	.word	9763660
	.word	11860814
	.word	10287952
	.word	-536870912
	.word	20379926
	.word	11336516
	.word	0
	.word	0
	.word	11336518
	.word	19855676
	.word	0
	.word	805306368
	.word	11336520
	.word	9239370
	.word	11860812
	.word	19855676
	.word	0
	.word	805306368
	.word	11336526
	.word	10287952
	.word	268435456
	.word	8715074
	.word	0
	.word	1073741824
	.word	11565056
	.word	823064854
	.word	18282784
	.word	1879048192
	.word	554629398
	.word	18282848
	.word	1879048192
	.word	-251200684
	.word	17758502
	.word	1342177280
	.word	9468968
	.word	9993260
	.word	823064854
	.word	18282848
	.word	1879048192
	.word	0
	.word	0
	.word	33390592
	.word	-1342177280
	.word	16349184
	.word	-2129724670
	.word	18906285
	.word	-2130249360
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	17235074
	.word	17758488
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715394
	.word	16349184
	.word	-2130248958
	.word	18906285
	.word	-2129725072
	.word	18282782
	.word	18807144
	.word	-2147483648
	.word	1879048192
	.word	16349184
	.word	-2129724670
	.word	19331848
	.word	-268435456
	.word	-2130249360
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	16349184
	.word	17234694
	.word	17759362
	.word	0
	.word	9239686
	.word	17234694
	.word	17759360
	.word	18283276
	.word	33259520
	.word	-536870912
	.word	805306368
	.word	17235072
	.word	17758988
	.word	18283270
	.word	18283278
	.word	0
	.word	9239684
	.word	17235074
	.word	17758488
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715394
	.word	16349184
	.word	-2130248958
	.word	19331848
	.word	-268435456
	.word	-2129725072
	.word	18282794
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	287767304
	.word	0
	.word	8715016
	.word	0
	.word	536870912
	.word	10516480
	.word	8715042
	.word	277674784
	.word	546634532
	.word	33128448
	.word	1073741824
	.word	33128448
	.word	-2147483648
	.word	33128448
	.word	-1073741824
	.word	-268435456
	.word	268435456
	.word	8715046
	.word	0
	.word	-268435456
	.word	268435456
	.word	8715048
	.word	0
	.word	-268435456
	.word	268435456
	.word	8715050
	.word	0
	.word	0
	.word	1073741824
	.word	11565056
	.word	20380502
	.word	24935443
	.word	-1879048192
	.word	1898379590
	.word	0
	.word	0
	.word	0
	.word	16349184
	.word	0
	.word	33390592
	.word	-1879048192
	.word	17235104
	.word	17759394
	.word	33259520
	.word	1610612736
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	33259520
	.word	1610612736
	.word	9763988
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235104
	.word	19331386
	.word	0
	.word	19855676
	.word	0
	.word	0
	.word	825162046
	.word	0
	.word	0
	.word	805306368
	.word	11336850
	.word	19855662
	.word	0
	.word	11041962
	.word	0
	.word	10288278
	.word	19331388
	.word	18283278
	.word	0
	.word	805306368
	.word	9993387
	.word	17759394
	.word	0
	.word	805306368
	.word	10288280
	.word	1342177280
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	0
	.word	17234236
	.word	17758990
	.word	0
	.word	805306368
	.word	0
	.word	19855678
	.word	0
	.word	805306368
	.word	10288274
	.word	19855662
	.word	0
	.word	9993386
	.word	17234702
	.word	17759394
	.word	0
	.word	805306368
	.word	0
	.word	10288276
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	-1073741824
	.word	17235104
	.word	17759396
	.word	-1879048192
	.word	17235100
	.word	17758982
	.word	18283276
	.word	33259520
	.word	1342177280
	.word	17235100
	.word	17758988
	.word	0
	.word	805306368
	.word	33259520
	.word	805306368
	.word	9763988
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235100
	.word	19331386
	.word	0
	.word	19855676
	.word	0
	.word	0
	.word	825162046
	.word	0
	.word	0
	.word	805306368
	.word	11336850
	.word	19855662
	.word	0
	.word	11041962
	.word	0
	.word	10288278
	.word	19331388
	.word	18283278
	.word	0
	.word	805306368
	.word	9993387
	.word	17758982
	.word	823590036
	.word	0
	.word	10288280
	.word	1073741824
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235100
	.word	17758988
	.word	0
	.word	805306368
	.word	0
	.word	17234236
	.word	17758990
	.word	0
	.word	805306368
	.word	0
	.word	19855678
	.word	0
	.word	805306368
	.word	10288274
	.word	19855662
	.word	0
	.word	9993386
	.word	17234694
	.word	17759388
	.word	18283276
	.word	0
	.word	0
	.word	805306368
	.word	0
	.word	10288276
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	-1073741824
	.word	17235100
	.word	17758982
	.word	805306368
	.word	-1879048192
	.word	19331386
	.word	0
	.word	10288272
	.word	19331388
	.word	0
	.word	805306368
	.word	19331374
	.word	0
	.word	11041962
	.word	0
	.word	9239700
	.word	19331390
	.word	0
	.word	805306368
	.word	11336850
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	0
	.word	1090520577
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17758538
	.word	20380498
	.word	18807090
	.word	0
	.word	33128448
	.word	-1055983284
	.word	0
	.word	286194514
	.word	-268435456
	.word	-805306368
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	268435456
	.word	8420527
	.word	0
	.word	1090520576
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17234226
	.word	20380498
	.word	0
	.word	286194514
	.word	-268435456
	.word	-805306368
	.word	18282776
	.word	33128448
	.word	1073741824
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	1073741824
	.word	1610612736
	.word	268435456
	.word	8420527
	.word	0
	.word	18875904
	.word	0
	.word	1091044864
	.word	546863104
	.word	17827332
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17234772
	.word	0
	.word	17455440
	.word	16778756
	.word	33390592
	.word	-1342177280
	.word	1091044864
	.word	815298560
	.word	17827332
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17303041
	.word	17827336
	.word	33325056
	.word	-1879048192
	.word	17303072
	.word	33062912
	.word	268435456
	.word	285738497
	.word	18351620
	.word	-2147483648
	.word	0
	.word	17827352
	.word	33062912
	.word	1073741824
	.word	17303064
	.word	0
	.word	1091044864
	.word	815298560
	.word	17827352
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	536870912
	.word	1091044864
	.word	815298560
	.word	0
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	-536870912
	.word	1091044864
	.word	815298560
	.word	-2147483648
	.word	0
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	1342177280
	.word	1879048192
	.word	268435456
	.word	8420527
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1011712
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	916484
	.word	1031168
	.word	1018880
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035272
	.word	0
	.word	1031172
	.word	0
	.word	1027080
	.word	0
	.word	1035361
	.word	16391
	.word	916544
	.word	1031176
	.word	16388
	.word	916544
	.word	1031176
	.word	0
	.word	18432
	.word	916544
	.word	1031176
	.word	916552
	.word	1031176
	.word	1035284
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031171
	.word	1018883
	.word	16384
	.word	17408
	.word	0
	.word	16384
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	593924
	.word	103056
	.word	103056
	.word	905516
	.word	1031176
	.word	589828
	.word	0
	.word	902208
	.word	916588
	.word	1031176
	.word	16384
	.word	1035355
	.word	1018888
	.word	0
	.word	1027079
	.word	0
	.word	1035361
	.word	16391
	.word	916544
	.word	1031176
	.word	16388
	.word	916544
	.word	1031176
	.word	0
	.word	18432
	.word	916544
	.word	1031176
	.word	916552
	.word	1031176
	.word	1035284
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031174
	.word	1018886
	.word	16384
	.word	17408
	.word	0
	.word	16384
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	593924
	.word	103056
	.word	103056
	.word	905516
	.word	1031176
	.word	589828
	.word	0
	.word	902208
	.word	916588
	.word	1031175
	.word	16384
	.word	1035355
	.word	1018888
	.word	0
	.word	1031176
	.word	0
	.word	1027080
	.word	0
	.word	1027080
	.word	16384
	.word	1035355
	.word	0
	.word	16384
	.word	0
	.word	0
	.word	1007616
	.word	0
	.word	0
	.word	589828
	.word	99972
	.word	622596
	.word	901164
	.word	1031182
	.word	0
	.word	109184
	.word	0
	.word	0
	.word	0
	.word	597444
	.word	107044
	.word	100000
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	589840
	.word	98332
	.word	592016
	.word	100508
	.word	0
	.word	902272
	.word	1031178
	.word	0
	.word	67204
	.word	0
	.word	0
	.word	1018891
	.word	17408
	.word	0
	.word	0
	.word	0
	.word	902208
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904392
	.word	69260
	.word	0
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031181
	.word	916612
	.word	1031181
	.word	916608
	.word	1031180
	.word	916608
	.word	1031180
	.word	1018894
	.word	1035295
	.word	0
	.word	1027086
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	98324
	.word	0
	.word	1035359
	.word	1018894
	.word	1035312
	.word	0
	.word	1027086
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	98324
	.word	0
	.word	1035359
	.word	1018894
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	983049
	.word	0
	.word	0
	.word	0
	.word	589828
	.word	0
	.word	99972
	.word	916484
	.word	1031188
	.word	916524
	.word	1031184
	.word	916524
	.word	1031188
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	597444
	.word	0
	.word	0
	.word	589840
	.word	98332
	.word	0
	.word	0
	.word	0
	.word	0
	.word	98308
	.word	0
	.word	916484
	.word	1031184
	.word	0
	.word	0
	.word	67204
	.word	0
	.word	0
	.word	1018897
	.word	0
	.word	0
	.word	902208
	.word	103044
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904400
	.word	69260
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031188
	.word	916612
	.word	1031188
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	0
	.word	1027092
	.word	16384
	.word	916544
	.word	1031186
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1018899
	.word	0
	.word	0
	.word	0
	.word	902208
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904392
	.word	69260
	.word	0
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031188
	.word	1018900
	.word	916612
	.word	1031188
	.word	1035322
	.word	1018900
	.word	1035322
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	98308
	.word	0
	.word	0
	.word	0
	.word	102028
	.word	592972
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	589828
	.word	901164
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	69260
	.word	69260
	.word	69260
	.word	606220
	.word	0
	.word	16384
	.word	66176
	.word	0
	.word	0
	.word	0
	.word	20480
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	66176
	.word	66176
	.word	0
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	590920
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	1027096
	.word	0
	.word	1018905
	.word	0
	.word	1027096
	.word	1027096
	.word	1018905
	.word	0
	.word	1018905
	.word	0
	.word	1027097
	.word	1018905
	.word	0
	.word	1018905
	.word	67204
	.word	606212
	.word	606212
	.word	0
	.word	0
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	17409
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	17410
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	17414
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	901124
	.word	1031195
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	901124
	.word	1031196
	.word	16384
	.word	0
	.word	17409
	.word	98308
	.word	98308
	.word	66176
	.word	66176
	.word	18432
	.word	590980
	.word	67204
	.word	67204
	.word	606212
	.word	606212
	.word	0
	.word	18433
	.word	589832
	.word	66176
	.word	66176
	.word	590920
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	606212
	.word	18432
	.word	916552
	.word	1031198
	.word	916556
	.word	1031198
	.word	1018910
	.word	17408
	.word	1018910
	.word	17408
	.word	1018910
	.word	606212
	.word	0
	.word	0
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	589828
	.word	901164
	.word	0
	.word	17419
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	16384
	.word	0
	.word	17423
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	17423
	.word	589828
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	0
	.word	16385
	.word	916488
	.word	1031215
	.word	16384
	.word	916608
	.word	1031215
	.word	0
	.word	16388
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16389
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16390
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	916864
	.word	1031202
	.word	1031215
	.word	16390
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16391
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	1018920
	.word	1035374
	.word	0
	.word	17408
	.word	902532
	.word	903560
	.word	605256
	.word	1031215
	.word	1035374
	.word	17408
	.word	902532
	.word	1031215
	.word	1035374
	.word	17408
	.word	902532
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	902532
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	902532
	.word	1031208
	.word	29696
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027110
	.word	20480
	.word	30720
	.word	16384
	.word	916800
	.word	1031206
	.word	1035372
	.word	0
	.word	104840
	.word	104848
	.word	595332
	.word	16384
	.word	906560
	.word	1031206
	.word	103060
	.word	16384
	.word	112696
	.word	917380
	.word	1031206
	.word	1018917
	.word	990244
	.word	29696
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027112
	.word	20480
	.word	30720
	.word	16384
	.word	916800
	.word	1031208
	.word	1035372
	.word	0
	.word	104840
	.word	104848
	.word	595332
	.word	16384
	.word	906560
	.word	1031208
	.word	103060
	.word	16384
	.word	112696
	.word	917380
	.word	1031208
	.word	1018919
	.word	990246
	.word	1018920
	.word	16384
	.word	0
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1027113
	.word	1018927
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031210
	.word	17408
	.word	916868
	.word	1031210
	.word	17408
	.word	916868
	.word	1031211
	.word	1018927
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031211
	.word	1018927
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035376
	.word	1035376
	.word	1035374
	.word	0
	.word	17423
	.word	916868
	.word	1031215
	.word	17408
	.word	916868
	.word	1031211
	.word	29696
	.word	110208
	.word	1035376
	.word	988203
	.word	1035374
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	0
	.word	16384
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	1035374
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	916868
	.word	1031213
	.word	1018926
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	16384
	.word	916864
	.word	1031215
	.word	1018927
	.word	16384
	.word	0
	.word	16384
	.word	0
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	0
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031225
	.word	916872
	.word	1031225
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031225
	.word	916872
	.word	1031225
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031217
	.word	1018929
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	17408
	.word	916868
	.word	1031225
	.word	1035374
	.word	0
	.word	17409
	.word	916868
	.word	1031225
	.word	1035374
	.word	0
	.word	17409
	.word	916868
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	916868
	.word	1031225
	.word	1035372
	.word	0
	.word	1035372
	.word	1035372
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	18432
	.word	0
	.word	901124
	.word	901128
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031225
	.word	20480
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	916880
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	916484
	.word	1031224
	.word	1018935
	.word	16384
	.word	0
	.word	1018937
	.word	16384
	.word	0
	.word	0
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	1035374
	.word	0
	.word	0
	.word	916868
	.word	1031254
	.word	1035374
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	1018966
	.word	17408
	.word	0
	.word	1018940
	.word	17408
	.word	0
	.word	1018940
	.word	17408
	.word	0
	.word	1035374
	.word	0
	.word	17423
	.word	916868
	.word	1031254
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031229
	.word	1018941
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031254
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031254
	.word	16384
	.word	18432
	.word	100492
	.word	1035350
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	1031232
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027136
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	98348
	.word	99436
	.word	294916
	.word	0
	.word	0
	.word	1031233
	.word	0
	.word	1031233
	.word	16384
	.word	294916
	.word	0
	.word	16384
	.word	99436
	.word	294916
	.word	17408
	.word	901124
	.word	0
	.word	18432
	.word	49160
	.word	589828
	.word	0
	.word	16384
	.word	916544
	.word	1031234
	.word	1035374
	.word	0
	.word	916868
	.word	1031254
	.word	16384
	.word	916544
	.word	1031235
	.word	16384
	.word	18432
	.word	100492
	.word	1035350
	.word	0
	.word	18432
	.word	50248
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	18432
	.word	50308
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	18432
	.word	50308
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	1031236
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	16384
	.word	916484
	.word	1031236
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	916544
	.word	1031238
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031238
	.word	1035374
	.word	0
	.word	16384
	.word	916484
	.word	1031238
	.word	1035374
	.word	0
	.word	16384
	.word	916484
	.word	1031238
	.word	16386
	.word	0
	.word	16384
	.word	916484
	.word	1031239
	.word	16386
	.word	0
	.word	16384
	.word	916484
	.word	1031239
	.word	1018953
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031241
	.word	28672
	.word	16384
	.word	108548
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	17408
	.word	916868
	.word	1031241
	.word	17408
	.word	916868
	.word	1031241
	.word	18432
	.word	916872
	.word	1031241
	.word	17408
	.word	916868
	.word	1031241
	.word	1018953
	.word	1035376
	.word	1018953
	.word	1035376
	.word	983112
	.word	16384
	.word	902148
	.word	1031243
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031243
	.word	28672
	.word	16384
	.word	108548
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	17408
	.word	916868
	.word	1031243
	.word	17408
	.word	916868
	.word	1031243
	.word	18432
	.word	916872
	.word	1031243
	.word	17408
	.word	916868
	.word	1031243
	.word	1018955
	.word	1035376
	.word	1018955
	.word	1035376
	.word	983114
	.word	16384
	.word	18432
	.word	901124
	.word	1031244
	.word	1031244
	.word	1018956
	.word	0
	.word	916612
	.word	1031244
	.word	130284
	.word	1031244
	.word	1018956
	.word	1018961
	.word	1035374
	.word	0
	.word	1027148
	.word	1035374
	.word	28672
	.word	16384
	.word	108548
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027149
	.word	1035372
	.word	1035372
	.word	0
	.word	1027150
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027150
	.word	1035372
	.word	1035372
	.word	1035372
	.word	1035372
	.word	983116
	.word	16384
	.word	0
	.word	916484
	.word	1031249
	.word	916652
	.word	1031249
	.word	28672
	.word	16384
	.word	108548
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027152
	.word	1035372
	.word	1035372
	.word	0
	.word	1027153
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027153
	.word	1035372
	.word	1035372
	.word	1035372
	.word	1035372
	.word	983119
	.word	0
	.word	1027155
	.word	16384
	.word	916544
	.word	1031249
	.word	16384
	.word	0
	.word	1035350
	.word	1018963
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027155
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	1018963
	.word	1035374
	.word	1018963
	.word	1035374
	.word	1035374
	.word	17408
	.word	916484
	.word	1031250
	.word	0
	.word	1027156
	.word	17408
	.word	916484
	.word	1031252
	.word	18432
	.word	916488
	.word	1031252
	.word	1018964
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031254
	.word	1035372
	.word	0
	.word	0
	.word	1031253
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	0
	.word	916872
	.word	1031253
	.word	1035372
	.word	1035372
	.word	0
	.word	1031254
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	19456
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031255
	.word	1018967
	.word	16384
	.word	0
	.word	999424
	.word	22528
	.word	0
	.word	0
	.word	0
	.word	916632
	.word	1031256
	.word	594960
	.word	0
	.word	0
	.word	0
	.word	594964
	.word	71316
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1018969
	.word	595088
	.word	0
	.word	593936
	.word	906516
	.word	0
	.word	0
	.word	594964
	.word	71316
	.word	0
	.word	0
	.word	0
	.word	0
	.word	595092
	.word	71316
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	999424
	.word	22528
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	17409
	.word	591876
	.word	98944
	.word	592900
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	999424
	.word	17408
	.word	916484
	.word	1031260
	.word	0
	.word	21504
	.word	0
	.word	300368
	.word	99652
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	67204
	.word	67204
	.word	67204
	.word	606212
	.word	0
	.word	0
	.word	21504
	.word	0
	.word	300368
	.word	98624
	.word	0
	.word	1035359
	.word	1018975
	.word	0
	.word	21504
	.word	0
	.word	905516
	.word	300368
	.word	99652
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	99392
	.word	0
	.word	0
	.word	0
	.word	99392
	.word	916552
	.word	1031261
	.word	1018974
	.word	0
	.word	0
	.word	902208
	.word	902276
	.word	99460
	.word	0
	.word	0
	.word	0
	.word	67204
	.word	67204
	.word	67204
	.word	606212
	.word	0
	.word	0
	.word	21504
	.word	0
	.word	905516
	.word	300368
	.word	98624
	.word	0
	.word	1035359
	.word	0
	.word	16384
	.word	98560
	.word	0
	.word	999424
	.word	20480
	.word	0
	.word	20480
	.word	21504
	.word	22528
	.word	916688
	.word	1031264
	.word	916692
	.word	1031264
	.word	916696
	.word	1031264
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	999424
	.word	22528
	.word	0
	.word	0
	.word	108184
	.word	1031265
	.word	19456
	.word	104664
	.word	596248
	.word	108184
	.word	0
	.word	17408
	.word	916484
	.word	1031270
	.word	0
	.word	0
	.word	916544
	.word	1031270
	.word	104088
	.word	0
	.word	903232
	.word	68232
	.word	903316
	.word	1027172
	.word	0
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	594176
	.word	905480
	.word	595264
	.word	102676
	.word	70288
	.word	102680
	.word	595220
	.word	104084
	.word	0
	.word	0
	.word	595220
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	593040
	.word	69260
	.word	0
	.word	0
	.word	904264
	.word	69260
	.word	0
	.word	1018982
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	903232
	.word	68232
	.word	903560
	.word	108168
	.word	0
	.word	589828
	.word	66176
	.word	100480
	.word	0
	.word	593044
	.word	102028
	.word	0
	.word	0
	.word	593044
	.word	0
	.word	0
	.word	0
	.word	904256
	.word	69260
	.word	904420
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	1018988
	.word	0
	.word	0
	.word	1018987
	.word	0
	.word	0
	.word	98308
	.word	916608
	.word	1031275
	.word	104088
	.word	0
	.word	903232
	.word	68232
	.word	903316
	.word	1027177
	.word	0
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	594176
	.word	905480
	.word	595264
	.word	102676
	.word	70288
	.word	102680
	.word	595220
	.word	104084
	.word	0
	.word	0
	.word	595220
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	593040
	.word	69260
	.word	0
	.word	0
	.word	67204
	.word	904264
	.word	0
	.word	1018987
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	903232
	.word	68232
	.word	903560
	.word	108168
	.word	0
	.word	589828
	.word	66176
	.word	100480
	.word	0
	.word	593044
	.word	102028
	.word	0
	.word	0
	.word	593044
	.word	0
	.word	0
	.word	0
	.word	0
	.word	903300
	.word	904200
	.word	69260
	.word	904420
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	1018988
	.word	0
	.word	0
	.word	67204
	.word	1018987
	.word	0
	.word	592912
	.word	0
	.word	0
	.word	592912
	.word	69260
	.word	101592
	.word	595152
	.word	0
	.word	902244
	.word	0
	.word	0
	.word	595152
	.word	104084
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	999424
	.word	19456
	.word	17408
	.word	66176
	.word	67204
	.word	606212
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	590936
	.word	596184
	.word	916544
	.word	1031277
	.word	612440
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031278
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031278
	.word	1018990
	.word	16384
	.word	0
	.word	999424
	.word	19456
	.word	17408
	.word	66176
	.word	67204
	.word	606212
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	595992
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031280
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031280
	.word	1018992
	.word	16384
	.word	0
	.word	999424
	.word	21504
	.word	22528
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	113280
	.word	0
	.word	102660
	.word	916544
	.word	1031282
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	104836
	.word	916872
	.word	1031280
	.word	104080
	.word	916804
	.word	1031285
	.word	70288
	.word	102660
	.word	295128
	.word	905472
	.word	104080
	.word	916628
	.word	1031284
	.word	0
	.word	905476
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	1018995
	.word	19456
	.word	16384
	.word	101008
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	1018997
	.word	19456
	.word	16384
	.word	299224
	.word	903504
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031286
	.word	1018998
	.word	16384
	.word	0
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65537
	.word	7208960
	.word	513
	.word	1537
	.word	319365736
	.word	319365736
	.word	9437306
	.word	5046372
	.word	0
	.word	0
	.word	1
	.word	131
	.word	16
	.word	2
	.word	24
	.word	256
	.word	263
	.word	3
	.word	351
	.word	4
	.word	64
	.word	127
	.word	262143
	.word	1048575
	.word	4194303
	.word	2147483647
	.word	-2147483648
	.word	-16
	.word	15
	.word	-128
	.word	8192
	.word	1048576
	.word	96000
	.word	-8
	.word	-1
	.word	262144
	.word	-524288
	.word	65280000
	.word	196612
	.word	131074
	.word	65537
	.word	65537
	.word	0
	.word	0
	.word	0
	.word	0
	.word	8
	.word	8160
	.word	255
	.word	0
	.word	1
	.word	5
	.word	8
	.word	7
	.word	64
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	g_pScdDrvParamBase, %object
	.size	g_pScdDrvParamBase, 4
g_pScdDrvParamBase:
	.word	g_ScdDrvParam
	.type	g_hex_flag, %object
	.size	g_hex_flag, 4
g_hex_flag:
	.word	1
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC2:
	ASCII(.ascii	"line: %d, p = NULL is not expected value!\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC4:
	ASCII(.ascii	"Warn: eVidStd = %d have not DSP vfmw bin file!!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC5:
	ASCII(.ascii	"%s failed!\012\000" )
.LC6:
	ASCII(.ascii	"%s success!\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"Ignore the reset request when the SCD[%d] clock is " )
	ASCII(.ascii	"closed.\012\000" )
.LC8:
	ASCII(.ascii	"SCD[%d]   ResetSCD ERROR!!!\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"line: %d Get SmID fail!\000" )
.LC10:
	ASCII(.ascii	"DelRaw err PacketNum = %d, DelNum = %d\012\000" )
.LC11:
	ASCII(.ascii	"%s release RawPhyAddr = 0x%x, Len = %d\012\000" )
.LC12:
	ASCII(.ascii	"line: %d DelNum = %d,RawPacketOffSet = %d,DelNum = " )
	ASCII(.ascii	"%d,Next Length = %d,is_extern_eop_flag = %d\012\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC13:
	ASCII(.ascii	"line: %d DelNum = %d,RawPacketOffSet = %d,Next Leng" )
	ASCII(.ascii	"th = %d\012\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"line: %d pSmInstArray is NULL!\012\000" )
.LC15:
	ASCII(.ascii	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLast" )
	ASCII(.ascii	"Seg=%d\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"-------- forece release seg[%d] -----------\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"0x%02x,\000" )
.LC19:
	ASCII(.ascii	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg" )
	ASCII(.ascii	"=%d StreamID=%d\012\000" )
.LC20:
	ASCII(.ascii	"Array out of bound in function %s\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"ScdId is wrong! %s error\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"%s: g_hex_base_vir_addr = NULL\012\000" )
.LC23:
	ASCII(.ascii	"line: %d, SmID = %d is not expected!\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"line: %d, SmID = %d, ScdId = %d is not expected!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC25:
	ASCII(.ascii	"Raw packet TOO BIG! Can't copy to seg! Len: 0x%x\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC26:
	ASCII(.ascii	"line: %d, delet raw failed!\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"[%s %d] VirAddr is null!!\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"copy raw to seg fail\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"Cann't Start SCD, Ret = %d\012\000" )
.LC30:
	ASCII(.ascii	"SM_CfgBuf Err! ret =%d\012\000" )
.LC31:
	ASCII(.ascii	"Line: %d, start code num from scd state reg: %d, re" )
	ASCII(.ascii	"lease raw packet anyway!\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"Error, discard raw packet!\012\000" )
.LC33:
	ASCII(.ascii	"Line: %d, The length of seg packet is invalid: %d\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC34:
	ASCII(.ascii	"[%s %d] pCurrentStartCodeVirAddr is null!!\012\000" )
.LC35:
	ASCII(.ascii	"[%s %d] pNextStartCodeVirAddr is null!!\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"ValidSegNum = %d, FilteredSegNum = 0, release raw p" )
	ASCII(.ascii	"acket anyway!\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"%s: pRawPacket = NULL!\012\000" )
.LC38:
	ASCII(.ascii	"%s: unkown standard type = %d!\012\000" )
.LC39:
	ASCII(.ascii	"%s: Length(%d)+FlagLen(%d) > BufLen(%d)\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"%s: FlagLen(%d) > RawPacketLength(%d)\012\000" )
	.space	1
.LC41:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act: %d, head" )
	ASCII(.ascii	"er_buf: %d)\012\000" )
.LC42:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act: %d, str_" )
	ASCII(.ascii	"buf: %d)\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act:%d, str_b" )
	ASCII(.ascii	"uf: %d, header_buf: %d)\012\000" )
.LC44:
	ASCII(.ascii	"Func: %s, buffer has no enough space, (act: %d, str" )
	ASCII(.ascii	"_buf: %d)\012\000" )
	.space	2
.LC45:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act:%d, str_b" )
	ASCII(.ascii	"uf:%d)\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"%s: RawPacket Length %d <= 0\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"Chan %d has been destroyed or the function pointer " )
	ASCII(.ascii	"-- ReleaseRawStreamData pStreamIntf is NULL!\000" )
.LC48:
	ASCII(.ascii	"line: %d s_SmIIS[%d].pSmInstArray is NULL\012\000" )
	.space	1
.LC49:
	ASCII(.ascii	"line: %d, pSmInstArray is NULL!\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"%s %d force to clear SCDState = 0\012\000" )
	.space	1
.LC51:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum !!\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"Chan %d has been destroyed or the function pointer " )
	ASCII(.ascii	"-- ReadRawStreamData pStreamIntf is NULL!\000" )
	.space	3
.LC53:
	ASCII(.ascii	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\012\000" )
	.space	1
.LC54:
	ASCII(.ascii	"Chan %d FillEosRawStream failed!\012\000" )
	.space	2
.LC55:
	ASCII(.ascii	"Chan %d FillExtraData failed!\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"Release this packet failed!\012\000" )
	.space	3
.LC57:
	ASCII(.ascii	"raw_pts: %lld\012\000" )
	.space	1
.LC58:
	ASCII(.ascii	"Get RawPhyAddr=0x%x,Len=%d\012\000" )
.LC59:
	ASCII(.ascii	"!!!push raw err!!!\012\000" )
.LC60:
	ASCII(.ascii	"Chan%d raw full\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"RawNum %lld <= RawNumInVfmw %lld\012\000" )
	.space	2
.LC62:
	ASCII(.ascii	"No space for raw move, total:%d+%d > max:%d!\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"scd buffer is full, reset scd!\012\000" )
.LC64:
	ASCII(.ascii	"(%d ms) not release stream seg, release anyway!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC65:
	ASCII(.ascii	"%s,%d, active scd Success!\012\000" )
.LC66:
	ASCII(.ascii	"Error:now DspState[0]= %d,[1]= %d not except!!\012\000" )
.LC67:
	ASCII(.ascii	"Move raw data failed, force to reset scd.\012\000" )
	.space	1
.LC68:
	ASCII(.ascii	"SCD GetRawStreamNum Fail.\012\000" )
	.space	1
.LC69:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) SCDState = %d\012\000" )
	.space	2
.LC70:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return Idle!\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"Chan %d SCD[%d] Time Out(%d ms), Reset it!\012\000" )
.LC72:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) really busy!\012\000" )
	.space	3
.LC73:
	ASCII(.ascii	"%s prepare to check SCD(%d)/(MAX_SCD_NUM = %d)\012\000" )
.LC74:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return BUSY!!\012\000" )
	.space	2
.LC75:
	ASCII(.ascii	"%s,%d,find idle SCD(ID = %d)\012\000" )
	.space	2
.LC76:
	ASCII(.ascii	"scd time out: t_start,t_now,t_wait = %d,%d,%d\012\000" )
	.space	1
.LC77:
	ASCII(.ascii	"********** SmID [%d] RawState begin **********\012\000" )
.LC78:
	ASCII(.ascii	"RawHead=%d\012\000" )
.LC79:
	ASCII(.ascii	"RawTail=%d\012\000" )
.LC80:
	ASCII(.ascii	"RawHistory=%d\012\000" )
	.space	1
.LC81:
	ASCII(.ascii	"RawFirstPacketOffset=%d\012\000" )
	.space	3
.LC82:
	ASCII(.ascii	"CurShowIndex=%d\012\000" )
	.space	3
.LC83:
	ASCII(.ascii	"********** SmID [%d] RawState end   **********\012\000" )
.LC84:
	ASCII(.ascii	"RawPhyAddr=0x%x\012\000" )
	.space	3
.LC85:
	ASCII(.ascii	"RawVirAddr=0x%x\012\000" )
	.space	3
.LC86:
	ASCII(.ascii	"RawLength=%d\012\000" )
	.space	2
.LC87:
	ASCII(.ascii	"RawPts=%ld\012\000" )
.LC88:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum!!\012\000" )
.LC89:
	ASCII(.ascii	"********** SmID [%d] SegState begin **********\012\000" )
.LC90:
	ASCII(.ascii	"SegHead=%d\012\000" )
.LC91:
	ASCII(.ascii	"SegTail=%d\012\000" )
.LC92:
	ASCII(.ascii	"SegCurrent=%d\012\000" )
	.space	1
.LC93:
	ASCII(.ascii	"SegBufPhyAddr=%p\012\000" )
	.space	2
.LC94:
	ASCII(.ascii	"SegBufVirAddr=%p\012\000" )
	.space	2
.LC95:
	ASCII(.ascii	"SegBufSize=%d\012\000" )
	.space	1
.LC96:
	ASCII(.ascii	"SegBufReadAddr=%p\012\000" )
	.space	1
.LC97:
	ASCII(.ascii	"SegBufWriteAddr=%pd\012\000" )
	.space	3
.LC98:
	ASCII(.ascii	"********** SmID [%d] SegState end   **********\012\000" )
.LC99:
	ASCII(.ascii	"SegPhyAddr=0x%x\012\000" )
	.space	3
.LC100:
	ASCII(.ascii	"SegVirAddr=0x%x\012\000" )
	.space	3
.LC101:
	ASCII(.ascii	"SegLength=%d\012\000" )
	.space	2
.LC102:
	ASCII(.ascii	"SegStreamID=%d\012\000" )
.LC103:
	ASCII(.ascii	"SegState=%d\012\000" )
	.space	3
.LC104:
	ASCII(.ascii	"SegIsLastSeg=%d\012\000" )
	.space	3
.LC105:
	ASCII(.ascii	"SegPts=%lld\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_ScdDrvParam, %object
	.size	g_ScdDrvParam, 60
g_ScdDrvParam:
	.space	60
	.type	g_hex_base_addr, %object
	.size	g_hex_base_addr, 4
g_hex_base_addr:
	.space	4
	.type	s_ScdRegPhyBaseAddr, %object
	.size	s_ScdRegPhyBaseAddr, 4
s_ScdRegPhyBaseAddr:
	.space	4
	.type	s_SmIIS, %object
	.size	s_SmIIS, 256
s_SmIIS:
	.space	256
	.type	s_eScdDrvSleepStage, %object
	.size	s_eScdDrvSleepStage, 4
s_eScdDrvSleepStage:
	.space	4
	.type	g_hex_base_vir_addr, %object
	.size	g_hex_base_vir_addr, 4
g_hex_base_vir_addr:
	.space	4
	.type	g_hex_len, %object
	.size	g_hex_len, 4
g_hex_len:
	.space	4
	.type	s_ScdRegResetPhyAddr, %object
	.size	s_ScdRegResetPhyAddr, 4
s_ScdRegResetPhyAddr:
	.space	4
	.type	last_rec_pos_time.54462, %object
	.size	last_rec_pos_time.54462, 128
last_rec_pos_time.54462:
	.space	128
	.type	LastRecPosTime.54656, %object
	.size	LastRecPosTime.54656, 128
LastRecPosTime.54656:
	.space	128
	.type	last_rec_pos_time.54690, %object
	.size	last_rec_pos_time.54690, 128
last_rec_pos_time.54690:
	.space	128
	.type	s_ScdRegResetOKPhyAddr, %object
	.size	s_ScdRegResetOKPhyAddr, 4
s_ScdRegResetOKPhyAddr:
	.space	4
	.type	ForceRelease, %object
	.size	ForceRelease, 4
ForceRelease:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
