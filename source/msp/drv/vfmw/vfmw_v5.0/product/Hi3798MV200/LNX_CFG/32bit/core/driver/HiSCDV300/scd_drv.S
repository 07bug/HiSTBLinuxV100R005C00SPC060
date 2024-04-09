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
	.type	GetFreeSegBufSize.part.7, %function
GetFreeSegBufSize.part.7:
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
	add	r0, r0, #327680
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
	.size	GetFreeSegBufSize.part.7, .-GetFreeSegBufSize.part.7
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
	ldr	r5, .L30
	ldr	r0, [r5, #60]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L25
	cmp	r7, #1
	beq	.L26
	cmp	r7, #2
	beq	.L27
	mov	r0, r4
	ldr	r1, .L30+4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L27:
	ldr	r6, .L30+8
	mov	r2, #17920
	ldr	r1, .L30+12
	ldr	r3, [r6, #52]
	blx	r3
	mov	r1, r4
	ldr	r0, [r5, #64]
	bl	MEM_WritePhyWord
.L15:
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
	b	.L18
.L28:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L19
.L18:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	ldr	r0, [r5, #64]
	add	r0, r0, #260
	bl	MEM_ReadPhyWord
	tst	r0, #1
	beq	.L28
	cmp	r4, #1000
	bcs	.L19
	ldr	r2, .L30+16
	mov	r0, #0
	ldr	r1, .L30+20
	bl	dprint_vfmw
.L21:
	cmp	r7, #1
	beq	.L29
	cmp	r7, #2
	ldreq	r3, .L30+24
	moveq	r2, #1
	streq	r2, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L19:
	ldr	r2, .L30+16
	mov	r0, #0
	ldr	r1, .L30+28
	bl	dprint_vfmw
	b	.L21
.L26:
	ldr	r6, .L30+8
	mov	r2, #17920
	ldr	r1, .L30+32
	ldr	r3, [r6, #52]
	blx	r3
	mov	r1, r7
	ldr	r0, [r5, #64]
	bl	MEM_WritePhyWord
	b	.L15
.L29:
	ldr	r3, .L30+24
	mov	r2, #2
	str	r2, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L25:
	ldr	r2, [r5, #60]
	ldr	r1, .L30+36
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L31:
	.align	2
.L30:
	.word	.LANCHOR0
	.word	.LC3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+1552
	.word	.LANCHOR3
	.word	.LC5
	.word	g_DspDrvState
	.word	.LC4
	.word	.LANCHOR1
	.word	.LC2
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
	ldr	ip, .L42
	mov	r3, #0
	b	.L35
.L33:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L41
.L35:
	ldr	r2, [ip, r3, asl #3]
	cmp	r2, #0
	add	r1, r2, #80
	beq	.L33
	cmp	r0, r1
	bne	.L33
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L41:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L43:
	.align	2
.L42:
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
	ldreq	r3, .L48
	moveq	r2, #1
	streq	r2, [r3, #48]
	ldmfd	sp, {fp, sp, pc}
.L49:
	.align	2
.L48:
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	bne	.L57
	ldr	r5, .L65
	mov	r1, #3
	ldr	r6, .L65+4
	ldr	r0, [r5, #64]
	add	r0, r0, #2176
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #64]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_ReadPhyWord
	ldr	ip, [r6]
	ldr	r4, [ip, #120]
	ands	r2, r4, #1
	mov	r7, r0
	beq	.L62
	orr	r4, r4, #32
	str	r4, [ip, #120]
	ldr	r3, [ip, #372]
	tst	r3, #2
	bne	.L56
	movw	r2, #9999
	b	.L54
.L64:
	subs	r2, r2, #1
	beq	.L63
.L54:
	ldr	r3, [ip, #372]
	tst	r3, #2
	beq	.L64
.L56:
	ldr	r0, [r5, #64]
	and	r1, r7, #1
	bfc	r4, #5, #1
	str	r4, [ip, #120]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #64]
	mov	r1, #2
	add	r0, r0, #2176
	bl	MEM_WritePhyWord
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L62:
	ldr	r1, .L65+8
	mov	r0, #26
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L63:
	mov	r0, r2
	ldr	r1, .L65+12
	bl	dprint_vfmw
	ldr	ip, [r6]
	b	.L56
.L57:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L66:
	.align	2
.L65:
	.word	.LANCHOR0
	.word	g_pstRegCrg
	.word	.LC6
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
	ldr	r3, .L71
	ldr	r3, [r3, #44]
	cmp	r3, r0
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, .L71+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L69
	mov	r1, #0
	mov	r0, r1
	bl	VDH_Reset_Module
.L70:
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SCDDRV_SetStateIdle.part.0
.L69:
	mov	r0, #0
	bl	ResetSCD
	b	.L70
.L72:
	.align	2
.L71:
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
	ldr	r3, .L78
	ldr	r5, [r1, #4]
	add	r0, r3, r0, lsl #3
	ldr	r2, [r0, #68]
	cmp	r2, #0
	cmpne	r5, #0
	moveq	r5, #1
	movne	r5, #0
	beq	.L76
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
	beq	.L77
	ldr	ip, .L78+4
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
.L77:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L76:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L79:
	.align	2
.L78:
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
	bhi	.L83
	ldr	r3, .L85
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #68]
	cmp	r3, #0
	beq	.L83
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
.L83:
	mvn	r0, #3
	ldmfd	sp, {fp, sp, pc}
.L86:
	.align	2
.L85:
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
	bcs	.L90
	ldr	r2, [r4, #4]
	cmp	r3, r2
	beq	.L90
	ldr	lr, .L91
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
.L90:
	mvn	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L92:
	.align	2
.L91:
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
	beq	.L95
	add	r3, r0, #98304
	ldr	ip, [r3]
	ldr	r0, [r3, #4]
	cmp	ip, r0
	beq	.L96
	ldr	r3, [r3, #12]
	mov	r0, r2
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L95:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L96:
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
	beq	.L101
	add	r3, r0, #98304
	ldr	r2, [r3]
	ldr	r1, [r3, #4]
	cmp	r2, r1
	beq	.L100
	ldr	r5, [r3, #12]
	mov	r7, r5, asr #31
	mov	r6, r5
	mov	r8, r5
.L99:
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
.L100:
	mov	r8, #0
	mov	r6, #0
	mov	r7, #0
	mov	r5, r8
	b	.L99
.L101:
	mov	r3, #98304
	mov	r6, #0
	mov	r7, #0
	ldr	r2, [r3]
	mov	r8, r0
	mov	r5, r0
	b	.L99
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
	beq	.L106
	add	r3, r0, #98304
	ldmia	r3, {r2, ip}
	cmp	r2, ip
	beq	.L105
	mov	ip, r2, asl #7
	ldr	lr, [r3, #12]
	sub	r2, ip, r2, asl #5
	add	r0, r0, r2
	add	r1, r1, lr
	ldr	r2, [r0, #12]
	cmp	r1, r2
	bge	.L106
	str	r1, [r3, #12]
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L106:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L105:
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
	beq	.L123
	ldr	r0, .L135
	b	.L112
.L109:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L110
.L112:
	ldr	r2, [r0, r3, asl #3]
	mov	r7, r3, asl #3
	cmp	r2, #0
	add	r1, r2, #80
	beq	.L109
	cmp	r8, r1
	bne	.L109
	cmp	r3, #31
	bhi	.L110
	add	r3, r8, #98304
	str	r3, [fp, #-48]
	mov	r2, r3
	ldr	r3, [r3]
	ldr	r2, [r2, #4]
	cmp	r3, r2
	addgt	r2, r2, #1024
	rsb	r2, r3, r2
	cmp	r2, r9
	bcc	.L134
	cmp	r9, #0
	mov	r4, r3
	beq	.L116
	ldr	r10, .L135+4
	mov	r5, #0
.L117:
	mov	r3, r4, asl #7
	ldr	r2, .L135+8
	sub	r3, r3, r4, asl #5
	ldr	r1, .L135+12
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
	bne	.L117
	ldr	r2, [fp, #-48]
	ldr	r3, [r2]
	add	r5, r5, r3
	str	r5, [r2]
	cmp	r5, #1024
	bge	.L121
.L122:
	ldr	r3, [fp, #-48]
	mov	r0, #0
	str	r0, [r3, #12]
.L130:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L121:
	ldr	r3, [fp, #-48]
	sub	r5, r5, #1024
	str	r5, [r3]
	b	.L122
.L116:
	ldr	r2, [fp, #-48]
	cmp	r3, #1024
	str	r3, [r2]
	ldrge	r2, [fp, #-48]
	subge	r3, r3, #1024
	strge	r3, [r2]
.L120:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L123:
	mvn	r0, #0
	b	.L130
.L134:
	mov	r3, r9
	ldr	r1, .L135+16
	mov	r0, #26
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L130
.L110:
	mov	r2, #476
	ldr	r1, .L135+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L130
.L136:
	.align	2
.L135:
	.word	.LANCHOR0+68
	.word	.LANCHOR0
	.word	.LANCHOR3+20
	.word	.LC10
	.word	.LC9
	.word	.LC8
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
	bne	.L145
	cmp	r3, #0
	cmpne	r2, #0
	moveq	r6, #1
	movne	r6, #0
	cmp	r9, #0
	orreq	r6, r6, #1
	cmp	r6, #0
	bne	.L145
	add	r8, r0, #98304
	cmp	ip, #0
	ldr	r7, [r8]
	ldr	lr, [r8, #12]
	mov	ip, r7, asl #7
	sub	ip, ip, r7, asl #5
	add	ip, r0, ip
	ldr	r5, [ip, #12]
	rsb	r5, lr, r5
	bne	.L139
	ldr	r6, [r8, #4]
	subs	r6, r6, r7
	addmi	r6, r6, #1024
.L139:
	cmp	r1, r5
	add	r6, r7, r6
	mov	ip, r7
	movge	lr, #0
	movlt	lr, #1
	cmp	r6, r7
	orrls	lr, lr, #1
	cmp	lr, #0
	bne	.L140
	mov	r4, r7
.L141:
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
	beq	.L141
	cmp	r7, r4
	rsbne	r5, r10, r5
	rsbne	r5, r5, r1
	strne	r5, [r3]
	beq	.L140
.L143:
	str	ip, [r9]
	mov	r0, #0
	ldr	r3, [r8]
	rsb	r4, r3, r4
	str	r4, [r2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L140:
	str	r1, [r3]
	mov	r4, r7
	b	.L143
.L145:
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
	bne	.L152
	cmp	r3, #0
	str	ip, [fp, #-40]
	str	ip, [fp, #-36]
	bne	.L152
	add	r4, r0, #98304
	ldr	r3, [r4, #20]
	ldr	ip, [r4, #12]
	rsb	r3, ip, r3
	movs	r6, r3, asr #31
	bne	.L151
	cmp	r1, r3
	bgt	.L152
	sub	r2, fp, #32
	sub	r3, fp, #36
	str	r2, [sp]
	sub	r2, fp, #40
	bl	GetRawNumOffset
	ldr	r0, [r4]
	ldr	ip, [fp, #-40]
	movw	r2, #642
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
	ldr	r1, .L154
	bl	dprint_vfmw
	ldr	r1, [fp, #-40]
	mov	r0, r5
	bl	DeleteRawPacket
	ldr	r3, [r4]
	ldr	r1, [r4, #4]
	ldr	r2, [fp, #-36]
	cmp	r3, r1
	mvneq	r6, #2
	beq	.L151
	mov	r1, r3, asl #7
	ldr	r0, [r4, #12]
	sub	r3, r1, r3, asl #5
	add	r5, r5, r3
	add	r2, r2, r0
	ldr	r3, [r5, #12]
	cmp	r2, r3
	strlt	r2, [r4, #12]
	bge	.L152
.L151:
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L152:
	mvn	r6, #0
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L155:
	.align	2
.L154:
	.word	.LC11
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
	ldr	r3, .L160
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #68]
	cmp	r0, #0
	beq	.L159
	add	r4, r0, #425984
	ldr	r1, [r4, #160]
	cmp	r1, #0
	ldmlefd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #80
	bl	DeleteRawPacket
	mov	r3, #0
	str	r3, [r4, #160]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L159:
	movw	r2, #659
	ldr	r1, .L160+4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L161:
	.align	2
.L160:
	.word	.LANCHOR0
	.word	.LC12
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
	beq	.L168
	add	r2, r0, #98304
	ldmia	r2, {r2, r3}
	subs	r3, r3, r2
	strpl	r3, [r1]
	addmi	r3, r3, #1024
	strmi	r3, [r1]
	movpl	r0, ip
	movmi	r0, ip
	ldmfd	sp, {fp, sp, pc}
.L168:
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
	beq	.L172
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r4, #1
	movne	r4, #0
	cmp	r3, #262144
	orrcc	r4, r4, #1
	cmp	r4, #0
	bne	.L172
	ldr	r3, .L173
	mov	r2, #56
	movt	r2, 5
	mov	r1, r4
	ldr	r3, [r3, #48]
	blx	r3
	add	r2, r7, #327680
	mov	r0, r4
	str	r5, [r2, #24]
	str	r6, [r7]
	str	r5, [r2, #32]
	str	r5, [r2, #36]
	str	r8, [r2, #28]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L172:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L174:
	.align	2
.L173:
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
	ldr	r3, .L180
	mov	r2, #327680
	mov	r1, #0
	add	r0, r4, #8
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r4, #327680
	mov	r3, #0
	ldr	r2, [r0, #24]
	str	r3, [r0, #8]
	str	r3, [r0, #12]
	str	r2, [r0, #32]
	str	r2, [r0, #36]
	str	r3, [r0, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L181:
	.align	2
.L180:
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
	add	r0, r0, #327680
	ldr	r2, [r0, #36]
	ldr	r3, [r0, #32]
	cmp	r2, r3
	bhi	.L187
	ldrcs	r0, [r0, #28]
	subcc	r3, r3, #1
	rsbcc	r0, r2, r3
	subcs	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
.L187:
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
	addne	r2, r0, #475136
	ldrne	r3, [r2, #1296]
	addne	r3, r3, #1
	strne	r3, [r2, #1296]
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
	beq	.L197
.L192:
	add	r0, r0, #475136
	ldr	r3, [r0, #1300]
	add	r3, r3, #1
	str	r3, [r0, #1300]
	ldmfd	sp, {fp, sp, pc}
.L197:
	add	r1, r1, #73
	uxtb	r1, r1
	cmp	r1, #3
	ldmhifd	sp, {fp, sp, pc}
	b	.L192
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
	add	r0, r0, #475136
	ldr	r3, [r0, #1304]
	cmp	r3, #2
	ldmlefd	sp, {fp, sp, pc}
	tst	r1, #31
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #1316]
	ldr	r2, [r0, #1312]
	rsb	r1, r2, r3
	cmp	r1, #1
	beq	.L212
.L200:
	cmp	r3, r2
	ldmnefd	sp, {fp, sp, pc}
	ldr	r2, [r0, #1308]
	cmp	r3, r2
	ldmnefd	sp, {fp, sp, pc}
.L201:
	cmp	r3, #1
	cmpne	r3, #20
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #1296]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r0, #1296]
	ldr	r3, [r0, #1300]
	add	r3, r3, #1
	str	r3, [r0, #1300]
	ldmfd	sp, {fp, sp, pc}
.L212:
	ldr	r1, [r0, #1308]
	rsb	r1, r1, r2
	cmp	r1, #1
	bne	.L200
	b	.L201
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
	ldr	r3, .L233
	mov	r6, r1
	ldr	r4, [r3, r1, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #568]
	cmp	r3, #0
	cmpne	r3, #3
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r4, #475136
	ldr	r3, [r5, #1304]
	cmp	r3, #199
	ldmgtfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r2, [r0]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #0
	movne	r7, r2
	bne	.L217
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L231
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	cmp	r2, #1
	ldreqb	r7, [r0, #3]	@ zero_extendqisi2
	andeq	r2, r7, #31
	beq	.L217
	mov	r2, r1
.L231:
	mov	r7, r2
.L217:
	ldr	r0, [r5, #1312]
	add	r3, r3, #1
	ldr	ip, [r5, #1316]
	mov	r1, r7
	str	r3, [r5, #1304]
	str	r0, [r5, #1308]
	mov	r0, r4
	str	ip, [r5, #1312]
	str	r2, [r5, #1316]
	bl	CheckData
	mov	r1, r7
	mov	r0, r4
	bl	CheckStartCodeCnt
	ldr	r3, [r5, #1304]
	cmp	r3, #199
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, [r5, #1296]
	ldr	r3, [r5, #1300]
	rsb	r1, r3, r2
	cmp	r1, #49
	ble	.L218
	ldr	r1, [r4, #568]
	cmp	r1, #3
	beq	.L232
.L218:
	rsb	r3, r2, r3
	cmp	r3, #49
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #568]
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, .L233+4
	ldr	ip, [r2]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, r6
	mov	r2, r3
	mov	r1, #124
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L232:
	ldr	r3, .L233+4
	ldr	r7, [r3]
	cmp	r7, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r3, #0
	mov	r1, #124
	mov	r2, r3
	mov	r0, r6
	blx	r7
	ldr	r3, [r5, #1300]
	ldr	r2, [r5, #1296]
	b	.L218
.L234:
	.align	2
.L233:
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
	beq	.L244
	add	r4, r0, #327680
	ldr	r7, [r4, #12]
	ldr	r0, [r4, #8]
	add	r3, r7, #1
	mov	r1, r3, asr #31
	mov	r1, r1, lsr #20
	add	r3, r3, r1
	ubfx	r3, r3, #0, #12
	rsb	r3, r1, r3
	cmp	r3, r0
	beq	.L245
	ldr	r0, [r5]
	cmp	r0, #0
	beq	.L242
	cmp	r2, #31
	bls	.L252
.L242:
	ldr	ip, .L253
	mov	r3, r7, asl #6
	add	r7, r3, r7, lsl #4
	mov	r2, #80
	add	r0, r7, #8
	mov	r1, r5
	ldr	r3, [ip, #52]
	add	r0, r6, r0
	blx	r3
	ldr	r1, [r4, #12]
	mov	ip, #1
	add	r7, r6, r7
	add	r3, r1, ip
	mov	r0, r1, asl #6
	mov	r2, r3, asr #31
	add	r0, r0, r1, lsl #4
	add	r6, r6, r0
	mov	r2, r2, lsr #20
	add	r3, r3, r2
	strb	ip, [r6, #12]
	ubfx	r3, r3, #0, #12
	str	r1, [r7, #28]
	rsb	r3, r2, r3
	str	r3, [r4, #12]
	ldrsb	r3, [r5, #5]
	cmp	r3, #2
	beq	.L243
	ldr	r1, [r5, #12]
	ldr	r3, [r5, #16]
	ldr	r2, [r4, #40]
	add	r3, r3, r1
	str	r3, [r4, #36]
	ldr	r1, [r5, #16]
	ldr	r3, [r4, #44]
	add	r2, r2, r1
	str	r2, [r4, #40]
	ldr	r2, [r5, #16]
	add	r3, r3, r2
	str	r3, [r4, #44]
.L243:
	ldr	r3, [r4, #48]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #48]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L245:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L252:
	mov	r1, r2
	bl	CheckStream.part.3
	ldr	r7, [r4, #12]
	b	.L242
.L244:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L254:
	.align	2
.L253:
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r0, r1
	beq	.L266
	add	r4, r5, #327680
	ldr	r3, [r4, #8]
	cmp	r3, #0
	blt	.L266
	ldr	r1, [r4, #12]
	cmp	r1, #0
	blt	.L266
	cmp	r3, r1
	beq	.L268
	mov	r6, r3, asl #4
	mov	r7, r3, asl #6
	add	r2, r6, r7
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	bne	.L259
	b	.L257
.L273:
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	beq	.L257
.L259:
	add	r2, r3, #1
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #20
	add	r2, r2, r3
	ubfx	r2, r2, #0, #12
	rsb	r3, r3, r2
	cmp	r1, r3
	mov	r6, r3, asl #4
	mov	r7, r3, asl #6
	add	r2, r6, r7
	bne	.L273
.L268:
	mvn	r0, #2
.L256:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L257:
	add	r8, r6, r7
	add	r1, r8, #8
	adds	r1, r5, r1
	beq	.L268
	ldr	r3, .L274
	mov	r2, #80
	add	r6, r6, r7
	add	r6, r5, r6
	ldr	r3, [r3, #52]
	blx	r3
	add	r3, r5, r8
	mov	r0, #2
	ldrsb	r1, [r3, #13]
	strb	r0, [r3, #12]
	cmp	r1, r0
	ldr	r3, [r3, #24]
	ldr	r1, [r4, #44]
	mov	r0, #26
	ldr	r2, [r4, #48]
	rsbne	r1, r3, r1
	sub	r2, r2, #1
	bic	r1, r1, r1, asr #31
	str	r1, [r4, #44]
	bic	r2, r2, r2, asr #31
	str	r2, [r4, #48]
	ldrb	ip, [r6, #14]	@ zero_extendqisi2
	ldr	r2, [r6, #20]
	ldr	r1, .L274+4
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L266:
	mvn	r0, #0
	b	.L256
.L275:
	.align	2
.L274:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r6, r0, #0
	mov	r4, r1
	beq	.L294
	movw	r3, #61438
	sub	r2, r1, #4096
	movt	r3, 65535
	cmp	r2, r3
	bls	.L294
	cmn	r1, #1
	add	r5, r6, #327680
	beq	.L310
	ldr	r3, [r5, #8]
	ldr	r2, [r5, #12]
	cmp	r3, r2
	bne	.L305
	b	.L299
.L282:
	add	r3, r3, #1
	ubfx	r3, r3, #0, #12
	cmp	r3, r2
	beq	.L299
.L305:
	cmp	r4, r3
	bne	.L282
	mov	r2, r3, asl #6
	add	r3, r2, r3, lsl #4
	add	r2, r6, r3
	ldrsb	r2, [r2, #12]
	cmp	r2, #2
	addeq	r3, r3, #8
	addeq	r7, r6, r3
	beq	.L279
.L299:
	mvn	r0, #2
.L306:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L310:
	ldr	r7, [r5, #8]
	ldr	r3, [r5, #12]
	cmp	r7, r3
	beq	.L299
	mov	r3, r7, asl #6
	mov	r4, r7
	add	r7, r3, r7, lsl #4
	add	r7, r7, #8
	add	r7, r6, r7
.L279:
	cmp	r7, #0
	beq	.L299
	ldr	r3, [r7, #16]
	mov	r2, #0
	strb	r2, [r7, #4]
	mov	r0, #26
	ldr	r2, [r7, #12]
	str	r4, [sp, #4]
	ldrb	ip, [r7, #6]	@ zero_extendqisi2
	ldr	r1, .L312
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #8]
	cmp	r3, r4
	beq	.L289
.L284:
	ldrsb	r3, [r7, #5]
	cmp	r3, #2
	beq	.L309
.L290:
	ldr	r2, [r7, #16]
	ldr	r3, [r5, #40]
	rsb	r3, r2, r3
.L288:
	bic	r3, r3, r3, asr #31
	mov	r0, #0
	str	r3, [r5, #40]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L285:
	ldr	r2, [r5, #12]
	cmp	r2, r4
	beq	.L291
	ldrsb	r2, [r3, #12]
	cmp	r2, #0
	bne	.L311
.L300:
	add	r4, r4, #1
	ubfx	r4, r4, #0, #12
.L289:
	mov	r3, r4, asl #6
	cmp	r4, #4096
	add	r3, r3, r4, lsl #4
	add	r3, r6, r3
	bcc	.L285
	ldr	r2, .L312+4
	mov	r0, #1
	ldr	r1, .L312+8
	bl	dprint_vfmw
	ldr	r2, [r5, #12]
	cmp	r2, r4
	bne	.L300
.L291:
	ldr	r3, [r5, #36]
	str	r2, [r5, #8]
	str	r3, [r5, #32]
	ldrsb	r3, [r7, #5]
	cmp	r3, #2
	bne	.L290
.L309:
	ldr	r3, [r5, #40]
	b	.L288
.L311:
	str	r4, [r5, #8]
	ldrsb	r2, [r7, #5]
	cmp	r2, #2
	ldrne	r3, [r3, #20]
	strne	r3, [r5, #32]
	bne	.L284
	b	.L309
.L294:
	mvn	r0, #0
	b	.L306
.L313:
	.align	2
.L312:
	.word	.LC14
	.word	.LANCHOR3+36
	.word	.LC15
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
	addne	r2, r0, #327680
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
	addne	r0, r0, #327680
	ldrne	r3, [r0, #12]
	ldrne	r0, [r0, #8]
	rsbne	r0, r0, r3
	ubfxne	r0, r0, #0, #12
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
	addeq	r0, r0, #327680
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
	bne	.L326
	ldr	r3, .L327
	ldr	r2, [r3, #324]
	cmp	r2, #0
	bne	.L326
	ldr	r0, [r3, #48]
	cmp	r0, #0
	moveq	r2, #2
	movne	r0, r2
	movne	r2, #1
	str	r2, [r3, #324]
	ldmfd	sp, {fp, sp, pc}
.L326:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L328:
	.align	2
.L327:
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
	ldreq	r3, .L332
	ldreq	r0, [r3, #324]
	movne	r0, #3
	ldmfd	sp, {fp, sp, pc}
.L333:
	.align	2
.L332:
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
	ldr	r3, .L339
	ldr	r2, [r3, #324]
	cmp	r2, #2
	movne	r2, #2
	strne	r2, [r3, #324]
	ldmfd	sp, {fp, sp, pc}
.L340:
	.align	2
.L339:
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
	ldreq	r3, .L343
	streq	r0, [r3, #324]
	ldmfd	sp, {fp, sp, pc}
.L344:
	.align	2
.L343:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_ExitSleep, .-SCDDRV_ExitSleep
	.align	2
	.global	ResetLastUnfinishedSegInfo
	.type	ResetLastUnfinishedSegInfo, %function
ResetLastUnfinishedSegInfo:
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
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L347
	add	r3, r0, #425984
	add	r0, r3, #436
	add	r5, r3, #444
	mov	ip, #0
	mvn	r2, #0
	ldr	lr, [r1, #48]
	mov	r4, #1
	str	r2, [r3, #440]
	mov	r1, ip
	strh	r2, [r0]	@ movhi
	add	r0, r3, #480
	str	r2, [r3, #448]
	strh	r2, [r5]	@ movhi
	mov	r2, #80
	str	r4, [r3, #456]
	str	ip, [r3, #460]
	str	ip, [r3, #464]
	str	ip, [r3, #468]
	str	ip, [r3, #472]
	str	ip, [r3, #452]
	mov	r3, lr
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L348:
	.align	2
.L347:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ResetLastUnfinishedSegInfo, .-ResetLastUnfinishedSegInfo
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
	bhi	.L351
	ldr	r3, .L352
	movw	r2, #49712
	ldr	ip, .L352+4
	movt	r2, 6
	add	r4, r3, r0, lsl #3
	mov	r1, #0
	mvn	r5, #0
	ldr	r3, [ip, #48]
	ldr	r0, [r4, #68]
	blx	r3
	ldr	r0, [r4, #68]
	bl	ResetLastUnfinishedSegInfo
	ldr	r3, [r4, #68]
	mov	r0, #0
	mvn	r4, #0
	add	r3, r3, #425984
	strd	r4, [r3, #248]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L351:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L353:
	.align	2
.L352:
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
	ldr	r4, .L357
	ldr	r6, .L357+4
	add	r5, r4, #256
.L355:
	mov	r2, #8
	mov	r0, r4
	ldr	r3, [r6, #48]
	add	r4, r4, r2
	mov	r1, #0
	blx	r3
	cmp	r4, r5
	bne	.L355
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L358:
	.align	2
.L357:
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
	bne	.L367
	cmp	r2, #0
	beq	.L368
	cmp	r2, #1
	moveq	r1, #49152
	movteq	r1, 63941
	bne	.L376
.L362:
	mov	r6, r2, asl #2
	ldr	r8, .L378
	rsb	r9, r6, r2, lsl #6
	add	r5, r8, r9
	add	r6, r8, r6
	ldr	r2, [r5, #40]
	str	r1, [r6, #64]
	cmp	r2, #1
	beq	.L366
	ldr	ip, .L378+4
	mov	r2, #60
	mov	r1, #0
	mov	r0, r5
	ldr	r10, [ip, #48]
	blx	r10
	ldr	r2, .L378+8
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
	add	r4, r4, #45056
	add	r4, r4, #127
	add	r4, r4, r9
	bic	r4, r4, #127
	str	r0, [r5, #8]
	mov	r0, r1
	bl	MEM_Phy2Vir
	ldr	r2, [fp, #-48]
	mov	r1, #32768
	str	r4, [r8, #60]
	str	r1, [r2, #4]
	str	r0, [r10, #4]
	mov	r0, r4
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r8, #328]
	beq	.L377
	add	r9, r9, #62976
	ldr	r1, [r6, #64]
	ldr	r2, [r6, #336]
	cmp	r7, r9
	mov	r3, #17920
	str	r3, [r8, #332]
	str	r1, [r5, #32]
	str	r2, [r5, #36]
	blt	.L366
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L366
	ldr	r3, [r10, #4]
	cmp	r3, #0
	beq	.L366
	mov	r0, #0
	mov	r3, #1
	str	r3, [r5, #40]
.L360:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L376:
	mov	r0, r1
	ldr	r2, .L378+12
	ldr	r1, .L378+16
	bl	dprint_vfmw
	mvn	r0, #6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L368:
	mov	r1, #49152
	movt	r1, 63683
	b	.L362
.L366:
	mvn	r0, #6
	b	.L360
.L367:
	mvn	r0, #0
	b	.L360
.L377:
	ldr	r2, .L378+12
	ldr	r1, .L378+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L360
.L379:
	.align	2
.L378:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	.word	.LANCHOR3+56
	.word	.LC16
	.word	.LC17
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
	bne	.L384
	ldr	r1, .L392
	mov	ip, r0
.L383:
	cmp	r0, #31
	bhi	.L382
	ldr	r3, [r1, r0, asl #3]
	cmp	r3, #0
	add	r2, r3, #425984
	beq	.L382
	ldr	r3, [r2, #228]
	cmp	r3, #0
	beq	.L382
	ldr	r3, [r2, #216]
	cmp	r3, #0
	strle	ip, [r2, #228]
.L382:
	add	r0, r0, #1
	cmp	r0, #32
	bne	.L383
	ldr	ip, .L392+4
	mov	r4, #0
	ldr	r3, .L392+8
	mov	r1, r4
	mov	r2, #60
	ldr	r0, .L392+12
	str	r4, [ip, #56]
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L384:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L393:
	.align	2
.L392:
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
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	clz	r3, r1
	mov	r7, r0
	mov	r5, r1
	mov	r3, r3, lsr #5
	cmp	r0, #31
	orrhi	r3, r3, #1
	cmp	r3, #0
	bne	.L397
	ldr	r3, .L409
	add	r2, r3, r0, lsl #3
	ldr	r6, [r2, #68]
	clz	r8, r6
	mov	r8, r8, lsr #5
	cmp	r8, #0
	bne	.L397
	ldr	r2, [r1, #44]
	add	r4, r6, #425984
	str	r2, [r4, #296]
	ldr	r2, [r1, #12]
	ldr	r1, [r6, #20]
	cmp	r1, r2
	addeq	r9, r6, #8
	ldreq	r10, .L409+4
	beq	.L399
	cmp	r2, #0
	beq	.L397
	ldr	r2, [r5]
	cmp	r2, #0
	beq	.L397
	ldr	r1, [r3, #12]
	mov	r2, #4096
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
	blt	.L397
	ldr	r10, .L409+4
	add	r0, r6, #98304
	add	r9, r6, #8
	add	r0, r0, #104
	bl	ConfigStreamSegArray
	mov	r2, #72
	ldr	r3, [r10, #52]
	mov	r0, r9
	mov	r1, r5
	blx	r3
	str	r8, [r4, #216]
.L399:
	ldr	r3, [r10, #52]
	mov	r0, r9
	mov	r2, #72
	mov	r1, r5
	blx	r3
	mov	r3, #2
	str	r3, [r4, #284]
	ldr	r3, [r5, #8]
	cmp	r3, #2
	moveq	r3, #3
	streq	r3, [r4, #284]
	ldr	r3, .L409+8
	ldr	r3, [r3]
	cmp	r3, #1
	beq	.L408
.L401:
	mov	r0, #0
	str	r7, [r4, #212]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L408:
	ldr	r2, [r5, #8]
	cmp	r2, #17
	streq	r3, [r6, #4]
	b	.L401
.L397:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L410:
	.align	2
.L409:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_SegBypassEnable
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
	bhi	.L419
	cmp	r1, #0
	bne	.L420
	ldr	r2, .L421
	add	r0, r2, r0, lsl #3
	ldr	r3, [r0, #68]
	clz	r1, r3
	mov	r1, r1, lsr #5
	cmp	r1, #0
	bne	.L415
	add	r3, r3, #425984
	ldr	r0, [r3, #216]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r6, [r2, #12]
	mov	r0, r1
	ldr	r5, [r2, #8]
	mov	ip, #4096
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
.L415:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L419:
	mov	r3, r0
	movw	r2, #1403
	ldr	r1, .L421+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L420:
	mov	r3, r1
	movw	r2, #1410
	ldr	r1, .L421+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L422:
	.align	2
.L421:
	.word	.LANCHOR0
	.word	.LC18
	.word	.LC19
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
	bhi	.L425
	ldr	r3, .L429
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #68]
	cmp	r3, #0
	beq	.L428
	ldr	r2, [r3, #24]
	cmp	r2, #0
	beq	.L428
	add	r3, r3, #425984
	ldr	r0, [r3, #228]
	cmp	r0, #0
	bne	.L428
	mov	r2, #1
	str	r2, [r3, #228]
	ldmfd	sp, {fp, sp, pc}
.L428:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L425:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L430:
	.align	2
.L429:
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
	bhi	.L433
	ldr	r3, .L439
	add	r0, r3, r0, lsl #3
	ldr	r0, [r0, #68]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	add	r3, r0, #425984
	ldr	r0, [r3, #228]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r2, [r3, #216]
	cmp	r2, #0
	bgt	.L435
	mov	r0, #0
	str	r0, [r3, #228]
	ldmfd	sp, {fp, sp, pc}
.L435:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L433:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L440:
	.align	2
.L439:
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	clz	r3, r1
	mov	r4, r1
	mov	r5, r0
	mov	r3, r3, lsr #5
	cmp	r0, #31
	movls	r1, r3
	orrhi	r1, r3, #1
	cmp	r1, #0
	bne	.L456
	ldr	r3, .L459
	mov	r2, #24
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r0, .L459+4
	add	r0, r0, r5, lsl #3
	ldr	r3, [r0, #68]
	cmp	r3, #0
	beq	.L458
	add	ip, r3, #425984
	add	r1, r3, #98304
	adds	lr, r1, #104
	ldr	r2, [ip, #228]
	strb	r2, [r4]
	ldr	r2, [ip, #276]
	str	r2, [r4, #20]
	moveq	r2, lr
	ldrne	r0, [ip, #112]
	ldrne	r2, [ip, #116]
	rsbne	r2, r0, r2
	ubfxne	r2, r2, #0, #12
	cmn	r3, #80
	str	r2, [r4, #8]
	movne	r0, #0
	moveq	r0, #1
	cmn	r3, #80
	cmnne	r4, #4
	beq	.L456
	ldr	r3, [r1, #84]
	ldr	r2, [r1, #80]
	subs	r3, r3, r2
	addmi	r3, r3, #1024
	strmi	r3, [r4, #4]
	strpl	r3, [r4, #4]
.L448:
	cmn	r4, #12
	movne	r3, #0
	moveq	r3, #1
	orrs	r3, r0, r3
	bne	.L456
	ldr	r3, [r1, #100]
	str	r3, [r4, #12]
	ldr	r0, [r1, #92]
	rsb	r0, r0, r3
	str	r0, [r4, #12]
	movs	r0, r0, asr #31
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	cmn	r4, #16
	cmpne	lr, #0
	beq	.L456
	ldr	r3, [ip, #144]
	str	r3, [r4, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L458:
	cmp	r4, #0
	strneb	r3, [r4]
.L456:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L460:
	.align	2
.L459:
	.word	vfmw_Osal_Func_Ptr_S
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
	b	.L462
.L464:
	ldr	r4, [r1]
	add	r4, r4, #1
	str	r4, [r1]
	ldr	r4, [lr, #12]
	ldr	lr, [r2]
	add	lr, lr, r4
	str	lr, [r2]
	ldr	lr, [r6, #4]
	cmp	lr, r3
	beq	.L466
	ldr	lr, [r1]
	cmp	lr, #1024
	bhi	.L466
.L462:
	rsb	ip, ip, r5
	add	r3, r3, #1
	ubfx	r3, r3, #0, #10
	ldrb	r4, [r0, ip]	@ zero_extendqisi2
	mov	r5, r3, asl #7
	mov	ip, r3, asl #5
	cmp	r4, #0
	rsb	lr, ip, r5
	add	lr, r0, lr
	bne	.L464
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L466:
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
	beq	.L472
	mov	r7, ip, asl #5
	mov	r6, ip, asl #7
	rsb	lr, r7, r6
	add	lr, r0, lr
	ldr	r4, [lr, #12]
	cmp	r4, #2
	bgt	.L473
	mov	lr, r4
	mov	r8, #3
	mov	r5, #0
	b	.L470
.L471:
	add	lr, r0, lr
	ldr	lr, [lr, #12]
	add	r4, r4, lr
	cmp	r4, #2
	bgt	.L475
.L470:
	add	ip, ip, #1
	add	r5, r5, #1
	ubfx	ip, ip, #0, #10
	cmp	r5, r10
	rsb	r8, lr, r8
	mov	r7, ip, asl #5
	mov	r6, ip, asl #7
	rsb	lr, r7, r6
	bne	.L471
.L472:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L475:
	mov	r9, r8, asr #31
.L469:
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
.L473:
	mov	r8, #3
	mov	r9, #0
	mov	r5, #0
	b	.L469
	UNWIND(.fnend)
	.size	AdjustRawPacketVP6A, .-AdjustRawPacketVP6A
	.align	2
	.global	SM_LinkRawToSeg
	.type	SM_LinkRawToSeg, %function
SM_LinkRawToSeg:
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
	ldr	r3, .L495
	mov	r8, r0
	mov	r5, r1
	add	r3, r3, r0, lsl #3
	ldr	r6, [r3, #68]
	cmp	r6, #0
	beq	.L479
	add	r3, r6, #98304
	add	r2, r6, #80
	cmn	r3, #104
	cmnne	r6, #80
	str	r2, [fp, #-56]
	ldr	r4, [r3, #80]
	add	r10, r3, #104
	moveq	r2, #1
	movne	r2, #0
	cmp	r1, #0
	orreq	r2, r2, #1
	cmp	r2, #0
	str	r4, [fp, #-52]
	bne	.L479
	ldr	r3, [r3, #84]
	cmp	r4, r3
	beq	.L485
	mov	r9, r4, asl #5
	mov	r4, r4, asl #7
	rsb	ip, r9, r4
	add	r7, r6, ip
	ldrb	r3, [r7, #80]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L492
	ldrd	r0, [r7, #120]
	orrs	r3, r0, r1
	beq	.L493
	ldr	r3, [r6, #16]
	cmp	r3, #12
	beq	.L494
.L482:
	ldr	r3, .L495+4
	mov	r2, r8
	mov	r0, r10
	mov	r1, r5
	ldr	r3, [r3, r8, asl #2]
	add	r3, r3, #475136
	ldr	r3, [r3, #1320]
	cmp	r3, #1
	rsbne	r3, r9, r4
	rsb	r4, r9, r4
	addne	r3, r6, r3
	ldreq	r3, [r7, #84]
	add	r6, r6, r4
	ldrne	r3, [r3, #88]
	str	r3, [r5, #12]
	mov	r3, #1
	ldr	ip, [r6, #120]
	str	ip, [r5]
	ldr	ip, [r6, #92]
	str	ip, [r5, #16]
	ldrd	r8, [r6, #144]
	strd	r8, [r5, #24]
	ldrd	r8, [r6, #144]
	strd	r8, [r5, #32]
	ldrd	r8, [r6, #128]
	strd	r8, [r5, #40]
	ldrd	r8, [r6, #136]
	strd	r8, [r5, #48]
	ldr	ip, [r6, #104]
	str	ip, [r5, #56]
	ldr	ip, [r6, #108]
	str	ip, [r5, #60]
	ldr	ip, [r6, #112]
	str	ip, [r5, #64]
	ldr	ip, [r6, #116]
	str	ip, [r5, #68]
	ldrb	ip, [r7, #81]	@ zero_extendqisi2
	strb	r3, [r5, #6]
	strb	ip, [r5, #7]
	bl	InsertStreamSeg
	mov	r0, #0
.L478:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L494:
	add	r3, r7, #88
	str	r3, [fp, #-60]
	ldr	r3, [r7, #92]
	cmp	r3, #0
	beq	.L482
	ldr	lr, [fp, #-56]
	sub	r1, fp, #44
	add	r2, ip, #40
	mov	r0, #1
	add	r3, lr, ip
	str	r0, [r1, #-4]!
	add	r3, r3, #12
	sub	r0, fp, #52
	add	r2, lr, r2
	str	r0, [sp]
	mov	r0, lr
	bl	AdjustRawPacketVP6A
	cmp	r0, #0
	beq	.L482
	ldr	r3, [fp, #-60]
	ldr	r0, [fp, #-56]
	ldr	r1, [r3, #4]
	bl	DeleteRawLen
	mvn	r0, #3
	b	.L478
.L492:
	ldr	r1, [r7, #92]
	ldr	r0, [fp, #-56]
	str	r2, [fp, #-60]
	bl	DeleteRawLen
	ldr	r2, [fp, #-60]
	ldr	r1, .L495+8
	mov	r0, r2
	ldr	r2, .L495+12
	bl	dprint_vfmw
	mvn	r0, #3
	b	.L478
.L493:
	ldr	r1, [r7, #92]
	ldr	r0, [fp, #-56]
	bl	DeleteRawLen
	ldr	r2, .L495+12
	ldr	r1, .L495+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #3
	b	.L478
.L485:
	mvn	r0, #3
	b	.L478
.L479:
	mvn	r0, #0
	b	.L478
.L496:
	.align	2
.L495:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	.LC20
	.word	.LANCHOR3+72
	.word	.LC21
	UNWIND(.fnend)
	.size	SM_LinkRawToSeg, .-SM_LinkRawToSeg
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
	ldr	r3, .L536
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
	beq	.L516
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
	bne	.L516
	ldr	r10, [r8, #84]
	ldr	r3, [r8, #80]
	cmp	r10, r3
	beq	.L531
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
	b	.L500
.L502:
	add	ip, ip, #1
	ldr	r0, [r0, #92]
	cmp	ip, #1024
	add	r6, r6, r0
	movls	r1, #0
	movhi	r1, #1
	cmp	r3, r10
	orreq	r1, r1, #1
	cmp	r1, #0
	bne	.L531
.L500:
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
	bne	.L502
	cmp	r9, #0
	str	ip, [fp, #-56]
	addne	r3, r4, #425984
	bne	.L513
	ldr	r10, .L536+4
	mov	r2, #327680
	mov	r1, r9
	add	r0, r8, #112
	ldr	r3, [r10, #48]
	blx	r3
	add	r3, r4, #425984
	ldr	r2, [r3, #128]
	str	r9, [r3, #112]
	str	r9, [r3, #116]
	str	r9, [r3, #120]
	str	r2, [r3, #136]
	str	r2, [r3, #140]
.L513:
	ldr	r2, [r3, #132]
	cmp	r2, r6
	blt	.L534
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
	bne	.L505
.L508:
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
	strb	r1, [r5, #6]
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
	beq	.L507
	cmp	r8, #0
	beq	.L531
	ldrd	r2, [fp, #-52]
	orrs	r3, r2, r3
	ldrne	r10, .L536+4
	movne	r7, #0
	bne	.L510
	b	.L531
.L511:
	cmp	r8, #0
	beq	.L531
	orrs	r3, r0, r1
	beq	.L531
.L510:
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
	strb	r0, [r5, #7]
	add	r1, r2, r1
	str	r1, [r5, #16]
	ldrd	r0, [r3, #120]
	ldr	r3, [r3, #92]
	strd	r0, [fp, #-52]
	str	r3, [fp, #-64]
	bhi	.L511
	ldr	r0, [r5]
.L507:
	cmp	r0, #0
	beq	.L535
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
.L534:
	mov	r2, r6
	ldr	r1, .L536+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r1, r6
	ldr	r0, [fp, #-76]
	bl	DeleteRawLen
	cmp	r0, #0
	beq	.L531
	movw	r2, #1708
	ldr	r1, .L536+12
	mov	r0, #0
	bl	dprint_vfmw
.L531:
	mvn	r0, #3
.L528:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L505:
	sub	r2, fp, #60
	sub	r3, fp, #64
	str	r2, [sp]
	sub	r1, fp, #56
	sub	r2, fp, #52
	ldr	r0, [fp, #-76]
	bl	AdjustRawPacketVP6A
	cmp	r0, #0
	beq	.L508
	b	.L531
.L516:
	mvn	r0, #0
	b	.L528
.L535:
	movw	r3, #1769
	ldr	r2, .L536+16
	ldr	r1, .L536+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #3
	b	.L528
.L537:
	.align	2
.L536:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC22
	.word	.LC23
	.word	.LANCHOR3+88
	.word	.LC24
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
	beq	.L544
	sub	r3, r0, #2
	cmp	r3, #1
	bls	.L543
	cmp	r0, #18
	cmpne	r0, #6
	moveq	r3, #1
	movne	r3, #0
	beq	.L543
	cmp	r0, #1
	beq	.L545
.L540:
	subs	r0, r0, #15
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L543:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L545:
	ldr	r2, [r1]
	cmp	r2, #0
	beq	.L540
.L544:
	mov	r0, r3
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
	ldr	r5, .L554
	mov	r6, r0
	mov	r4, r1
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrsb	r3, [r1, #5]
	cmp	r3, #2
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r7, .L554+4
	mov	r0, #0
	ldr	r3, [r7, #16]
	blx	r3
	ldr	r3, [r7, #44]
	ldr	r2, [r5, r6, asl #2]
	ldr	r1, [r4, #16]
	ldr	r0, [r4]
	blx	r3
	ldr	r3, [r7, #12]
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L555:
	.align	2
.L554:
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
	bne	.L563
	ldr	r3, .L573
	add	r3, r3, r0, lsl #3
	ldr	r4, [r3, #68]
	cmp	r4, #0
	beq	.L563
	add	r1, r4, #32
	ldr	r0, [r4, #16]
	bl	SCDDRV_IsSCDByPass
	cmp	r0, #0
	beq	.L558
	ldr	r3, [r4, #4]
	mov	r1, r7
	mov	r0, r6
	cmp	r3, #1
	beq	.L570
	bl	SM_CopyRawToSeg
.L560:
	cmp	r0, #0
	bne	.L571
.L558:
	add	r0, r4, #98304
	mov	r1, r7
	add	r0, r0, #104
	add	r4, r4, #425984
	bl	SCDDRV_GetStreamSeg
	subs	r5, r0, #0
	beq	.L572
	ldr	r3, [r4, #276]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #276]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L572:
	mov	r0, r6
	mov	r1, r7
	str	r5, [r4, #276]
	bl	SCDDRV_SaveStreamSeg
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L570:
	bl	SM_LinkRawToSeg
	b	.L560
.L571:
	add	r4, r4, #425984
	mvn	r0, #6
	ldr	r3, [r4, #276]
	add	r3, r3, #1
	str	r3, [r4, #276]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L563:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L574:
	.align	2
.L573:
	.word	.LANCHOR0
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L578
	ldr	r3, .L581
	add	r0, r3, r0, lsl #3
	ldr	r4, [r0, #68]
	cmp	r4, #0
	beq	.L578
	add	r0, r4, #98304
	add	r0, r0, #104
	bl	ReleaseStreamSeg
	subs	r5, r0, #0
	bne	.L579
	ldr	r0, [r4, #4]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r4, #80
	mov	r1, #1
	bl	DeleteRawPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L578:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L579:
	mvn	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L582:
	.align	2
.L581:
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
	ldr	r3, .L584
	mov	r0, #0
	ldr	r3, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L585:
	.align	2
.L584:
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
	ldr	r3, .L591
	mov	r5, r1
	mov	r4, r0
	ldr	r3, [r3]
	blx	r3
	cmp	r5, #0
	add	r3, r4, #425984
	mov	r1, r0
	bne	.L590
	ldr	r2, [r3, #244]
	cmp	r0, r2
	strls	r5, [r3, #240]
	rsbhi	r0, r2, r0
	strls	r1, [r3, #244]
	strhi	r0, [r3, #240]
	movls	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L590:
	mov	r2, #0
	str	r1, [r3, #244]
	mov	r0, r2
	str	r2, [r3, #240]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L592:
	.align	2
.L591:
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
	ldr	r3, .L596
	ldr	r2, [r3, #48]
	cmp	r2, #1
	ldreq	r3, [r3, #44]
	rsbeq	r0, r0, r3
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L597:
	.align	2
.L596:
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
	beq	.L599
	add	lr, r0, #98304
	ldr	ip, [lr, #20]
	str	ip, [r1]
	ldr	lr, [lr, #12]
	rsb	ip, lr, ip
	str	ip, [r1]
.L599:
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
	b	GetFreeSegBufSize.part.7
	UNWIND(.fnend)
	.size	GetFreeSegBufSize, .-GetFreeSegBufSize
	.align	2
	.global	SCDDRV_GetSegStreamStatus
	.type	SCDDRV_GetSegStreamStatus, %function
SCDDRV_GetSegStreamStatus:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r7, [fp, #4]
	clz	r5, r0
	cmp	r0, #0
	cmpne	r2, #0
	mov	r4, r3
	mov	r6, r1
	mov	r3, #0
	mov	r8, r2
	mov	r5, r5, lsr #5
	str	r3, [r7]
	mov	r9, r0
	bne	.L614
.L608:
	ldr	r2, [r8]
	add	r3, r6, #79
	add	r0, r9, #327680
	cmp	r2, r3
	movwcs	r3, #65457
	movcc	r3, #0
	movtcs	r3, 65535
	rsbcs	r3, r6, r3
	addcs	r3, r3, r2
	str	r3, [r8]
	ldr	ip, [r0, #28]
	rsb	ip, ip, ip, lsl #3
	add	r2, ip, #7
	cmp	ip, #0
	movlt	ip, r2
	cmp	r6, ip, asr #3
	addcs	r6, r3, r6
	strcs	r6, [r8]
	movcs	r3, #1
	strcs	r3, [r7]
	cmp	r5, #0
	ldreq	r2, [r0, #12]
	movne	r2, #4096
	ldreq	r3, [r0, #8]
	rsbeq	r2, r3, r2
	ubfxeq	r2, r2, #0, #12
	rsbeq	r2, r2, #4096
	str	r2, [r4]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L614:
	mov	r1, r2
	bl	GetFreeSegBufSize.part.7
	b	.L608
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
	cmp	r0, #1024
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
	@ args = 12, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	sub	ip, fp, #28
	mov	r5, r3
	mov	r4, r1
	mov	r3, #0
	mov	r6, r2
	str	r3, [ip, #-4]!
	mov	r1, r5
	mov	r2, ip
	bl	SCDDRV_GetRawStreamStatus
	ldr	r2, [r5]
	ldr	r3, [fp, #-32]
	cmp	r3, #0
	cmpne	r2, #3
	bls	.L620
	ldr	r3, [fp, #12]
	mov	r1, r6
	mov	r0, r4
	str	r3, [sp]
	ldmib	fp, {r2, r3}
	bl	SCDDRV_GetSegStreamStatus
	ldr	r3, [fp, #8]
	ldr	r3, [r3]
	cmp	r3, #1024
	bls	.L621
	add	r4, r4, #327680
	ldr	r3, [fp, #4]
	ldr	r2, [r4, #28]
	ldr	r3, [r3]
	cmp	r3, r2, lsr #3
	mvnls	r0, #5
	movhi	r0, #0
.L619:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L620:
	mvn	r0, #4
	b	.L619
.L621:
	mvn	r0, #5
	b	.L619
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
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #16]
	cmp	r2, #18
	beq	.L629
	sub	lr, r2, #6
	cmp	r2, #1
	cmpne	r2, #15
	clz	lr, lr
	moveq	r5, #1
	movne	r5, #0
	mov	lr, lr, lsr #5
	mov	r4, lr
.L624:
	add	r3, r0, #425984
	mov	ip, #1
	strb	ip, [r1, #2]
	ldr	ip, [r3, #184]
	str	ip, [r1, #4]
	ldr	ip, [r3, #176]
	str	ip, [r1, #8]
	ldr	ip, [r3, #192]
	str	ip, [r1, #16]
	ldr	r6, [r3, #200]
	ldr	ip, [r3, #284]
	mul	ip, ip, r6
	str	ip, [r1, #20]
	ldr	ip, [r3, #128]
	str	ip, [r1, #24]
	ldr	ip, [r3, #132]
	ldr	r6, [r3, #128]
	add	ip, ip, r6
	str	ip, [r1, #28]
	ldr	ip, [r3, #456]
	cmp	ip, #1
	ldreq	ip, [r3, #140]
	ldrne	ip, [r3, #452]
	addeq	ip, ip, #3
	biceq	ip, ip, #3
	cmp	r5, #0
	str	ip, [r1, #32]
	mov	ip, #1
	strb	ip, [r1]
	ldr	r0, [r0, #44]
	str	r4, [r1, #60]
	str	r0, [r1, #44]
	bne	.L630
	sub	r0, r2, #2
	cmp	r0, ip
	orrls	lr, lr, #1
	cmp	lr, #0
	strneb	ip, [r1, #1]
	beq	.L627
.L628:
	str	r2, [r1, #36]
	mov	r2, #1
	str	r2, [r1, #40]
	str	r2, [r1, #48]
	str	r2, [r1, #52]
	ldr	r3, [r3, #432]
	str	r3, [r1, #56]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L630:
	mov	r2, #0
.L627:
	mov	r0, #0
	strb	r0, [r1, #1]
	b	.L628
.L629:
	mov	r4, #1
	mov	r5, #0
	mov	lr, r4
	mov	r2, #6
	b	.L624
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
	add	r4, r0, #425984
	cmp	r1, r2
	str	r1, [r4, #256]
	movls	r3, #1
	str	r2, [r4, #260]
	movhi	r3, #0
	strb	r3, [r0, #2]
	mov	r1, #1
	ldr	r3, .L637
	mov	r2, #0
	str	r1, [r4, #220]
	strb	r2, [r0, #3]
	ldr	r3, [r3]
	blx	r3
	str	r0, [r4, #280]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L638:
	.align	2
.L637:
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
	ldr	ip, .L646
	mov	r5, r0
	mov	r0, r3
	ldrb	r3, [ip]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L645
	cmp	r5, #4
	beq	.L644
	ldr	r6, .L646+4
	mov	r4, r2, asl #2
.L641:
	add	r2, r6, r4
	ldr	r0, [r2, #64]
	add	r0, r5, r0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MEM_WritePhyWord
.L645:
	mov	r3, r1
	mov	r2, r5
	mov	r1, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Record_RegData
.L644:
	ldr	r6, .L646+4
	mov	r4, r2, asl #2
	cmp	r1, #0
	add	r3, r6, r4
	ldr	r0, [r3, #64]
	add	r0, r0, #4
	bne	.L642
	bl	MEM_ReadPhyWord
	uxth	r1, r0
	b	.L641
.L642:
	bl	MEM_ReadPhyWord
	orr	r1, r0, #65536
	b	.L641
.L647:
	.align	2
.L646:
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #196)
	sub	sp, sp, #196
	ldr	r5, .L707
	mov	r9, r0
	mov	r4, r1
	mov	r7, r2
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L649
	ldr	r3, .L707+4
	sub	r0, fp, #232
	mov	r2, #188
	mov	r1, #0
	mov	r8, r0
	ldr	r3, [r3, #48]
	blx	r3
.L650:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #4]
	cmp	r2, #1
	bne	.L687
	ldr	r6, .L707+8
	add	r3, r6, r7, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2048
	add	r0, r0, #4
	bl	MEM_WritePhyWord
.L652:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #16]
	cmp	r2, #1
	bne	.L688
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #64]
	add	r0, r0, #2048
	add	r0, r0, #8
	bl	MEM_WritePhyWord
.L654:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #20]
	cmp	r2, #1
	bne	.L689
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #64]
	add	r0, r0, #2048
	add	r0, r0, #12
	bl	MEM_WritePhyWord
.L656:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #24]
	cmp	r2, #1
	bne	.L690
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #64]
	add	r0, r0, #2064
	bl	MEM_WritePhyWord
.L658:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #28]
	cmp	r2, #1
	bne	.L691
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #64]
	add	r0, r0, #2064
	add	r0, r0, #4
	bl	MEM_WritePhyWord
.L660:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #32]
	cmp	r2, #1
	bne	.L692
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #64]
	add	r0, r0, #2064
	add	r0, r0, #8
	bl	MEM_WritePhyWord
.L662:
	mov	r10, r9, asl #3
	ldr	r3, .L707+8
	add	r2, r6, r10
	ldr	r2, [r2, #68]
	add	r2, r2, #425984
	ldr	r1, [r2, #456]
	cmp	r1, #1
	beq	.L693
	ldr	r1, [r2, #440]
	mov	r0, #3
	movt	r0, 768
	cmp	r1, r0
	beq	.L694
.L668:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L695
	add	r3, r6, r7, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2096
	add	r0, r0, #12
	bl	MEM_WritePhyWord
.L673:
	add	r10, r6, r10
	ldrb	r1, [r5]	@ zero_extendqisi2
	ldr	r2, .L707+8
	ldr	r3, [r10, #68]
	cmp	r1, #1
	add	r3, r3, #425984
	add	r3, r3, #436
	ldrh	r1, [r3]
	bne	.L696
	add	r2, r2, r7, lsl #2
	ldr	r0, [r2, #64]
	add	r0, r0, #2112
	add	r0, r0, #4
	bl	MEM_WritePhyWord
.L667:
	ldr	r3, [r4, #52]
	ldr	r0, [r4, #44]
	ldr	r2, [r4, #36]
	mov	r3, r3, asl #9
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	orr	r3, r3, r0, asl #8
	and	r2, r2, #15
	orr	r2, r3, r2
	ldrb	r0, [r5]	@ zero_extendqisi2
	ldr	r3, [r4, #48]
	mov	r1, r1, asl #4
	cmp	r0, #1
	and	r1, r1, #16
	orr	r3, r2, r3, asl #13
	orr	r1, r3, r1
	bne	.L697
	add	r3, r6, r7, lsl #2
	ldr	r0, [r3, #64]
	add	r0, r0, #2080
	bl	MEM_WritePhyWord
	ldr	r3, [r4, #44]
	cmp	r3, #0
	bne	.L698
.L677:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L699
	add	r3, r6, r7, lsl #2
	mov	r1, #0
	ldr	r10, .L707
	ldr	r0, [r3, #64]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldrb	r5, [r5]	@ zero_extendqisi2
	cmp	r5, #1
	beq	.L681
.L702:
	ldr	r2, [r4, #44]
	sub	r0, fp, #232
	mov	r3, #0
	str	r9, [fp, #-224]
	strb	r7, [fp, #-232]
	strb	r2, [fp, #-231]
	str	r3, [fp, #-228]
	bl	VDH_PostTask
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L694:
	add	r2, r2, #436
	ldrh	r2, [r2]
	cmp	r2, #0
	bne	.L668
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L700
	add	r3, r3, r7, lsl #2
	mov	r1, #3
	ldr	r0, [r3, #64]
	add	r0, r0, #2096
	add	r0, r0, #12
	bl	MEM_WritePhyWord
.L670:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L701
	add	r3, r6, r7, lsl #2
	mov	r1, #0
	ldr	r0, [r3, #64]
	add	r0, r0, #2112
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	b	.L667
.L695:
	mov	r3, r1
	movw	r2, #2108
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L673
.L699:
	mov	r3, #0
	movw	r2, #2076
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	ldrb	r5, [r5]	@ zero_extendqisi2
	ldr	r10, .L707
	cmp	r5, #1
	bne	.L702
.L681:
	add	r6, r6, r7, lsl #2
	mov	r1, #0
	ldr	r0, [r6, #64]
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
	ldrb	r3, [r10]	@ zero_extendqisi2
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #1
	and	r1, r1, #1
	bne	.L703
	ldr	r0, [r6, #64]
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L697:
	mov	r3, r1
	mov	r2, #2080
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	ldr	r3, [r4, #44]
	cmp	r3, #0
	beq	.L677
.L698:
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, [r4, #60]
	cmp	r2, #1
	bne	.L704
	add	r2, r6, r7, lsl #2
	ldr	r0, [r2, #64]
	bl	MEM_WritePhyWord
	b	.L677
.L692:
	mov	r3, r1
	movw	r2, #2072
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L662
.L691:
	mov	r3, r1
	movw	r2, #2068
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L660
.L690:
	mov	r3, r1
	mov	r2, #2064
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L658
.L689:
	mov	r3, r1
	movw	r2, #2060
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L656
.L688:
	mov	r3, r1
	movw	r2, #2056
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L654
.L687:
	mov	r3, r1
	movw	r2, #2052
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	ldr	r6, .L707+8
	b	.L652
.L696:
	mov	r3, r1
	movw	r2, #2116
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L667
.L649:
	mov	r0, r2
	mov	r8, #0
	bl	ResetSCD
	b	.L650
.L704:
	mov	r3, r1
	mov	r2, #0
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L677
.L703:
	mov	r3, r1
	mov	r0, r8
	mov	r1, r5
	mov	r2, #2048
	bl	VDH_Record_RegData
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L693:
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L705
	add	r3, r3, r7, lsl #2
	mvn	r1, #0
	ldr	r0, [r3, #64]
	add	r0, r0, #2096
	add	r0, r0, #12
	bl	MEM_WritePhyWord
.L665:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L706
	add	r3, r6, r7, lsl #2
	mvn	r1, #0
	ldr	r0, [r3, #64]
	add	r0, r0, #2112
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	b	.L667
.L705:
	mvn	r3, #0
	movw	r2, #2108
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L665
.L706:
	mvn	r3, #0
	movw	r2, #2116
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L667
.L700:
	mov	r3, #3
	movw	r2, #2108
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L670
.L701:
	mov	r3, #0
	movw	r2, #2116
	mov	r1, #1
	mov	r0, r8
	bl	VDH_Record_RegData
	b	.L667
.L708:
	.align	2
.L707:
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
	@ args = 12, pretend = 0, frame = 136
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #140)
	sub	sp, sp, #140
	mov	r0, r0, asl #3
	mov	r10, r1
	str	r1, [fp, #-148]
	mov	r4, r0
	mov	r8, r2
	str	r2, [fp, #-164]
	mov	r1, #0
	str	r0, [fp, #-168]
	mov	r2, #96
	sub	r0, fp, #140
	mov	r7, r3
	str	r3, [fp, #-160]
	bl	memset
	ldr	r3, .L769
	mov	r2, #16384
	mov	r1, #0
	add	r3, r3, r4
	ldr	r3, [r3, #68]
	mov	r0, r3
	str	r3, [fp, #-172]
	ldr	r3, .L769+4
	add	r0, r0, #425984
	str	r0, [fp, #-176]
	mov	r5, r0
	add	r0, r0, #560
	ldr	r3, [r3, #48]
	add	r4, r5, #448
	str	r0, [fp, #-144]
	blx	r3
	sub	r1, fp, #140
	mov	r0, r7
	bl	GetFirstRawPacket
	ldr	r9, [fp, #-128]
	ldr	r3, [fp, #4]
	add	r6, r5, #444
	cmp	r9, r8
	mov	r5, #0
	str	r5, [r3]
	str	r5, [r3, #4]
	str	r5, [r3, #8]
	str	r5, [r10, #4]
	bgt	.L710
	add	r8, r7, #98304
	mov	r10, r5
	mov	r7, r5
	mov	r2, r9
	str	r6, [fp, #-152]
	str	r4, [fp, #-156]
.L713:
	ldr	r1, [fp, #4]
	mov	r3, r7, asl #2
	cmp	r2, #0
	mov	r0, r5, asl #4
	add	ip, r1, r3
	ldr	r1, [fp, #8]
	add	r3, r3, #12
	add	r10, r10, #1
	add	r3, r3, r1
	ldr	r1, [fp, #-144]
	add	lr, r1, r0
	ble	.L711
	ldr	r1, [fp, #-136]
	add	r5, r5, #1
	ldr	r6, [fp, #-136]
	ldr	r4, [fp, #4]
	sub	r1, r1, #1
	add	r1, r1, r2
	str	r6, [r4, r7, asl #2]
	add	r7, r7, #3
	str	r3, [ip, #8]
	str	r1, [ip, #4]
	ldrd	r2, [fp, #-100]
	ldr	r1, [fp, #-144]
	strd	r2, [r1, r0]
	ldrd	r2, [fp, #-100]
	ldr	r1, [fp, #-128]
	subs	r2, r2, #1
	sbc	r3, r3, #0
	adds	r2, r2, r1
	adc	r3, r3, r1, asr #31
	strd	r2, [lr, #8]
	mov	r3, #0
	str	r3, [fp, #-128]
.L711:
	ldr	r3, [fp, #-148]
	str	r9, [r3, #4]
	ldr	r3, [r8, #16]
	cmp	r3, #1024
	bcc	.L766
.L712:
	ldr	r3, [fp, #12]
	ldr	r6, [fp, #-152]
	cmp	r3, #0
	ldr	r4, [fp, #-156]
	bne	.L714
	ldr	r2, [fp, #-128]
	cmp	r2, #0
	bne	.L732
.L714:
	cmp	r10, #0
	beq	.L731
	cmp	r7, #0
	subgt	r7, r7, #-1073741823
	ldrgt	r2, [fp, #4]
	movgt	r3, #0
	strgt	r3, [r2, r7, asl #2]
	ldr	r2, [fp, #-168]
	ldr	r3, .L769
	add	r3, r3, r2
	ldr	r2, [fp, #-148]
	ldr	r3, [r3, #68]
	ldr	r2, [r2, #4]
	add	r3, r3, #425984
	add	r0, r3, #444
	cmp	r2, #6
	ldr	ip, [r3, #448]
	add	r1, r3, #436
	movge	r2, #6
	cmp	r2, #5
	str	ip, [r3, #440]
	ldrh	r3, [r0]
	strh	r3, [r1]	@ movhi
	bls	.L767
.L734:
	mov	r8, #2
	mov	r2, #4
.L718:
	cmp	r5, #0
	ldrgt	r3, [fp, #-144]
	addgt	r9, r3, r5, lsl #4
	ble	.L727
.L730:
	ldr	r1, [r9, #-8]
	ldr	r0, [r9, #-16]
	add	r3, r1, #1
	rsb	r0, r0, r3
	cmp	r0, r2
	movcc	lr, r0
	movcs	lr, r2
	cmp	r2, #0
	beq	.L723
	cmp	lr, #0
	beq	.L726
	add	ip, r4, lr
.L725:
	ldrb	r7, [r3, #-1]!	@ zero_extendqisi2
	strb	r7, [r4], #1
	cmp	r4, ip
	bne	.L725
	subs	r2, r2, lr
	beq	.L723
.L726:
	subs	r5, r5, #1
	sub	r9, r9, #16
	bne	.L730
.L727:
	ldr	r2, [fp, #-148]
	mov	r0, #0
	mov	r3, #1
	str	r10, [r2]
	str	r3, [r2, #8]
.L762:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L723:
	cmp	r8, #0
	beq	.L727
	rsb	r0, lr, r0
	rsb	r1, lr, r1
	cmp	r0, r8
	movcs	r0, r8
	cmp	r0, #0
	beq	.L728
	add	r1, r1, #1
	add	r2, r6, r0
.L729:
	ldrb	r3, [r1, #-1]!	@ zero_extendqisi2
	strb	r3, [r6], #1
	cmp	r6, r2
	bne	.L729
	subs	r8, r8, r0
	beq	.L727
	mov	r2, #0
	b	.L726
.L766:
	ldr	ip, [fp, #-160]
	mov	r1, r3, asl #7
	sub	r1, r1, r3, asl #5
	mov	r2, #96
	add	r1, ip, r1
	ldr	ip, [r8, #4]
	sub	r0, fp, #140
	cmp	r3, ip
	beq	.L712
	ldr	r3, .L769+4
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r8, #16]
	ldr	r2, [fp, #-128]
	ldr	r0, [fp, #-164]
	add	r3, r3, #1
	add	r9, r9, r2
	cmp	r0, r9
	mov	r1, r3, asr #31
	movge	r0, #1
	movlt	r0, #0
	cmp	r10, #1024
	mov	r1, r1, lsr #22
	add	r3, r3, r1
	movge	r0, #0
	cmp	r0, #0
	ubfx	r3, r3, #0, #10
	rsb	r3, r1, r3
	str	r3, [r8, #16]
	bne	.L713
	b	.L712
.L767:
	cmp	r2, #1
	beq	.L768
	rsbs	r0, r2, #6
	rsb	lr, r2, #5
	beq	.L734
	ldr	r3, [fp, #-172]
	movw	ip, #33214
	add	lr, r4, lr
	movt	ip, 6
	add	ip, r3, ip
	mov	r3, #2
.L720:
	subs	r0, r0, #1
	rsb	r7, r3, #3
	sub	r8, r3, #1
	ldrb	r1, [lr], #-1	@ zero_extendqisi2
	movne	r3, #1
	moveq	r3, #0
	cmp	r7, #1
	movhi	r3, #0
	andls	r3, r3, #1
	cmp	r3, #0
	strb	r1, [ip, #-1]!
	mov	r3, r8
	bne	.L720
	cmp	r8, #0
	bne	.L765
	cmp	r0, #0
	rsb	r2, r2, #3
	beq	.L736
	ldr	r3, [fp, #-176]
	rsb	ip, r0, r2
	add	ip, r4, ip
	add	r1, r3, #452
	add	r3, r4, r2
.L721:
	ldrb	r2, [r3], #-1	@ zero_extendqisi2
	cmp	r3, ip
	strb	r2, [r1, #-1]!
	bne	.L721
	rsb	r2, r0, #4
	b	.L718
.L710:
	ldr	r3, [fp, #12]
	cmp	r3, #0
	bne	.L731
	cmp	r9, #0
	beq	.L731
	ldr	r5, [fp, #12]
	mov	r2, r9
	mov	r7, r5
	mov	r10, r5
.L732:
	ldr	r3, [fp, #-148]
	ldr	r1, [fp, #-164]
	ldr	r3, [r3, #4]
	sub	r1, r1, #16
	cmp	r3, r1
	bge	.L714
	ldr	r1, [fp, #-164]
	cmp	r1, r9
	cmplt	r10, #1024
	bge	.L714
	rsb	r3, r3, r1
	cmp	r3, r2
	bgt	.L714
	ldr	r2, [fp, #-136]
	mov	r1, r7, asl #2
	ldr	lr, [fp, #4]
	add	r0, r1, #12
	ldr	ip, [fp, #4]
	add	r10, r10, #1
	str	r3, [fp, #-128]
	str	r2, [lr, r7, asl #2]
	add	r1, ip, r1
	sub	r2, r2, #1
	ldr	ip, [fp, #8]
	add	r2, r2, r3
	ldrd	r8, [fp, #-100]
	ldr	r3, [fp, #-144]
	add	r0, r0, ip
	mov	ip, r5, asl #4
	str	r0, [r1, #8]
	str	r2, [r1, #4]
	add	r0, r3, ip
	strd	r8, [r3, ip]
	mov	r1, #0
	ldrd	r2, [fp, #-100]
	add	r7, r7, #3
	ldr	ip, [fp, #-128]
	add	r5, r5, #1
	subs	r2, r2, #1
	sbc	r3, r3, #0
	adds	r2, r2, ip
	adc	r3, r3, ip, asr #31
	strd	r2, [r0, #8]
	ldr	r0, [fp, #-148]
	ldr	r2, [fp, #-128]
	str	r1, [fp, #-128]
	ldr	r3, [r0, #4]
	add	r3, r3, r2
	mov	r2, r0
	str	r3, [r0, #4]
	b	.L714
.L728:
	mov	r2, r0
	b	.L726
.L736:
.L765:
	mov	r2, #4
	b	.L718
.L768:
	ldr	ip, [fp, #-176]
	mov	r8, #0
	ldrb	r1, [ip, #444]	@ zero_extendqisi2
	ldrb	r3, [ip, #451]	@ zero_extendqisi2
	ldrb	r0, [ip, #450]	@ zero_extendqisi2
	strb	r1, [ip, #445]
	strb	r3, [ip, #444]
	ldrb	r1, [ip, #449]	@ zero_extendqisi2
	ldrb	r3, [ip, #448]	@ zero_extendqisi2
	strb	r0, [ip, #451]
	strb	r1, [ip, #450]
	strb	r3, [ip, #449]
	b	.L718
.L731:
	mvn	r0, #5
	b	.L762
.L770:
	.align	2
.L769:
	.word	.LANCHOR0
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
	add	r4, r1, #425984
	mov	r9, r3
	mov	r7, r0
	ldr	r3, [r4, #184]
	mov	r10, r2
	ldr	r0, [r4, #212]
	add	r5, r1, #80
	add	r6, r4, #160
	str	r3, [fp, #-48]
	ldr	r3, [r4, #176]
	str	r3, [fp, #-52]
	bl	VCTRL_IfEsBufEnable
	cmp	r0, #0
	beq	.L775
	ldr	r8, .L776
	mov	r2, #12
	mov	r1, #0
	mov	r0, r6
	ldr	r3, [r8, #48]
	blx	r3
	ldr	ip, [r7, #44]
	ldr	r2, [fp, #-48]
	mov	r3, r5
	ldr	r1, [fp, #-52]
	ldr	r0, [r4, #212]
	str	r2, [sp, #4]
	mov	r2, r10
	str	r1, [sp]
	mov	r1, r6
	str	ip, [sp, #8]
	bl	WriteScdMsg
	subs	r5, r0, #0
	movne	r0, r5
	bne	.L773
	ldr	r3, [r8]
	blx	r3
	ldr	ip, .L776+4
	mov	r3, r9, asl #6
	mov	r1, r7
	sub	r3, r3, r9, asl #2
	mov	r2, r9
	add	r3, ip, r3
	str	r0, [r3, #48]
	ldr	r0, [r4, #212]
	bl	WriteScdVtrlReg
	mov	r0, r5
.L773:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L775:
	ldr	r2, [r4, #212]
	mov	r0, #1
	ldr	r1, .L776+8
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L773
.L777:
	.align	2
.L776:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	.word	.LC25
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
	UNWIND(.pad #96)
	sub	sp, sp, #96
	add	r6, r0, #425984
	mov	r7, r1
	add	r1, r0, #98304
	ldr	r2, [r6, #464]
	sub	r3, fp, #96
	mov	r5, r0
	str	r3, [sp, #8]
	add	r1, r1, #104
	sub	r3, fp, #104
	add	r0, r0, #80
	str	r3, [sp, #4]
	sub	r3, fp, #100
	str	r3, [sp]
	sub	r3, fp, #108
	mov	ip, #0
	str	ip, [fp, #-108]
	str	ip, [fp, #-104]
	str	ip, [fp, #-100]
	str	ip, [fp, #-96]
	bl	SCDDRV_CheckConditionOfStartSCD
	subs	r4, r0, #0
	bne	.L789
	ldr	r3, [fp, #-96]
	cmp	r3, #0
	bne	.L790
.L781:
	mov	r1, r7
	ldr	r0, [r6, #212]
	bl	SM_CfgBuf
	subs	r4, r0, #0
	bne	.L791
	ldr	r2, [fp, #-104]
	mov	r0, r5
	ldr	r3, [r6, #284]
	sub	r1, fp, #92
	str	r2, [r6, #200]
	mul	r3, r3, r2
	mov	r3, r3, asl #2
	str	r3, [r6, #196]
	bl	SCDDRV_SetCtrlReg
	ldr	r2, [fp, #-100]
	mov	r3, r7
	sub	r0, fp, #92
	mov	r1, r5
	bl	SCDDRV_StartSCD
	cmp	r0, #0
	movne	r2, r0
	bne	.L780
	ldr	r3, [fp, #-100]
	mov	r2, #1
	ldr	r1, [fp, #-108]
	mov	r4, #0
	cmp	r1, r3
	str	r3, [r6, #260]
	str	r1, [r6, #256]
	movls	r3, #1
	strlsb	r3, [r5, #2]
	ldr	r3, .L792
	strhib	r0, [r5, #2]
	str	r2, [r6, #220]
	strb	r4, [r5, #3]
	ldr	r3, [r3]
	blx	r3
	mov	r2, r4
	str	r0, [r6, #280]
.L780:
	mov	r0, r2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L791:
	mov	r2, r4
	ldr	r1, .L792+4
	mov	r0, #26
	bl	dprint_vfmw
	mov	r2, r4
	mov	r0, r2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L790:
	mov	r0, r5
	bl	ResetLastUnfinishedSegInfo
	b	.L781
.L789:
	mov	r2, r4
	ldr	r1, .L792+8
	mov	r0, #26
	bl	dprint_vfmw
	mov	r2, r4
	mov	r0, r2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L793:
	.align	2
.L792:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	.LC26
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
	ldr	r4, .L795
	mov	r5, r0
	movw	r6, #2124
	add	r4, r4, r1, lsl #2
	ldr	r0, [r4, #64]
	add	r0, r0, #2112
	bl	MEM_ReadPhyWord
	and	r0, r0, #1
	str	r0, [r5]
	ldr	r0, [r4, #64]
	add	r0, r6, r0
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
	ldr	r3, [r4, #64]
	str	r0, [r5, #24]
	add	r0, r3, #2128
	add	r0, r0, #12
	bl	MEM_ReadPhyWord
	str	r0, [r5, #28]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L796:
	.align	2
.L795:
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
	ldr	r3, [r2, #4]
	ldrb	r0, [r1]	@ zero_extendqisi2
	mov	r3, r3, lsr #30
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
	beq	.L806
	ldr	r3, [r0, #12]
	cmp	r3, #0
	beq	.L808
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L808
	cmp	r1, #0
	beq	.L803
	add	r1, r1, #327680
	ldr	r2, [r1, #36]
	ldr	r3, [r1, #32]
	cmp	r2, r3
	bls	.L804
	ldr	r1, [r1, #28]
	sub	r3, r3, #1
	add	r3, r3, r1
	rsb	r1, r2, r3
.L803:
	ldr	r3, [r0, #16]
	cmp	r3, r1
	mvnhi	r0, #6
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L804:
	ldrcs	r1, [r1, #28]
	subcc	r3, r3, #1
	rsbcc	r1, r2, r3
	subcs	r1, r1, #1
	b	.L803
.L808:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L806:
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
	strb	r3, [r4, #8]
	ldrd	r2, [r5]
	cmp	r7, r3
	cmpeq	r6, r2
	beq	.L814
.L812:
	strd	r6, [r5]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L814:
	ldr	r3, .L815
	ldr	r2, [fp, #4]
	ldr	r3, [r3, r2, asl #2]
	add	r3, r3, #475136
	ldr	r3, [r3, #1332]
	cmp	r3, #0
	bne	.L812
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [r4, #24]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L816:
	.align	2
.L815:
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
	beq	.L822
	cmp	r0, #2
	movne	r0, #0
	beq	.L823
.L819:
	mov	r2, #0
	movt	r2, 65025
	cmp	r1, r2
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L822:
	mov	r3, #0
	movt	r3, 46593
	rsb	r0, r3, r1
	clz	r0, r0
	mov	r0, r0, lsr #5
	b	.L819
.L823:
	ubfx	r3, r1, #16, #8
	sub	r3, r3, #128
	cmp	r3, #3
	movhi	r0, #0
	movls	r0, #1
	b	.L819
	UNWIND(.fnend)
	.size	IsVopHeader, .-IsVopHeader
	.align	2
	.global	GetNextVop
	.type	GetNextVop, %function
GetNextVop:
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
	add	lr, r0, #98304
	cmn	lr, #104
	addne	ip, r0, #425984
	moveq	r8, #4096
	ldrne	r8, [ip, #112]
	ldrne	r3, [ip, #116]
	rsbne	r8, r8, r3
	sub	r3, r2, #1
	ubfxne	r8, r8, #0, #12
	rsbne	r8, r8, #4096
	cmp	r3, #0
	mov	ip, r3
	blt	.L834
	add	r0, r0, #425984
	mov	r4, #0
	mov	r9, r4
	ldr	r7, [lr, #104]
	ldr	r5, [r0, #284]
	movt	r4, 65025
	ldr	r6, [r0, #128]
	movt	r9, 46593
	ldr	lr, [r0, #232]
	mov	r5, r5, asl #2
	mla	r1, r5, r3, r1
	b	.L832
.L837:
	cmp	lr, #2
	beq	.L836
	cmp	r2, r4
	beq	.L830
.L831:
	sub	ip, ip, #1
	rsb	r1, r5, r1
	cmn	ip, #1
	mov	r2, r3
	beq	.L834
	sub	r3, r3, #1
.L832:
	ldr	r2, [r1]
	cmp	lr, #1
	rsb	r2, r6, r2
	ldr	r2, [r7, r2]
	rsbeq	r0, r9, r2
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	bne	.L837
.L828:
	cmp	r2, r4
	beq	.L830
	cmp	r0, #1
	bne	.L831
.L830:
	cmp	r3, r8
	mov	r2, r3
	bls	.L834
	sub	r3, r3, #1
	b	.L831
.L836:
	ubfx	r0, r2, #16, #8
	sub	r0, r0, #128
	cmp	r0, #3
	movhi	r0, #0
	movls	r0, #1
	b	.L828
.L834:
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetNextVop, .-GetNextVop
	.align	2
	.global	CorrectRollPhyAddr
	.type	CorrectRollPhyAddr, %function
CorrectRollPhyAddr:
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
	cmp	r1, r2
	rsbcc	r1, r2, r1
	addcc	r0, r1, r0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CorrectRollPhyAddr, .-CorrectRollPhyAddr
	.align	2
	.global	CorrectSegNextAddr
	.type	CorrectSegNextAddr, %function
CorrectSegNextAddr:
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
	cmp	r0, r1
	movcc	r0, r1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CorrectSegNextAddr, .-CorrectSegNextAddr
	.align	2
	.global	SetLastUnfinishedSegInfo
	.type	SetLastUnfinishedSegInfo, %function
SetLastUnfinishedSegInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	add	r4, r0, #425984
	mov	r5, r0
	mov	r9, r1
	ldr	r8, [r4, #284]
	mov	r7, r2
	mov	r1, #0
	mov	r2, #80
	sub	r0, fp, #124
	ldr	r6, [r4, #188]
	bl	memset
	mul	ip, r8, r9
	ldr	lr, [r4, #212]
	add	r8, r4, #480
	add	r2, r4, #248
	add	r0, r5, #80
	add	r9, r5, #98304
	add	ip, ip, #1
	mov	r3, r8
	ldr	r1, [r6, ip, asl #2]
	mov	r10, ip, asl #2
	str	lr, [sp]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r3, .L857
	mov	r1, r8
	mov	r2, #80
	sub	r0, fp, #124
	add	r8, r9, #104
	ldr	r3, [r3, #52]
	blx	r3
	add	ip, r6, r10
	ldr	r2, [r4, #128]
	ldr	ip, [ip, #-4]
	str	ip, [r4, #460]
	ldr	r3, [r7, #28]
	cmp	r2, r3
	movcs	r3, r2
	cmp	ip, r3
	str	r3, [r4, #452]
	bls	.L843
	mov	r1, #1
	str	r1, [r4, #468]
	ldr	r0, [r7, #28]
	rsb	r6, r2, r3
	ldr	r1, [r7, #16]
	cmp	r2, r0
	addhi	r1, r0, r1
	rsbhi	r1, r2, r1
	str	r1, [r4, #472]
	rsb	lr, ip, r1
	add	r1, lr, r6
	str	r1, [r4, #464]
	ldr	r3, [r5, #48]
	cmp	r3, #1
	beq	.L856
.L846:
	mov	r3, #0
	str	r3, [r4, #456]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L843:
	rsb	r3, ip, r3
	mov	r1, #0
	cmp	r3, #3
	str	r1, [r4, #468]
	str	r1, [r4, #472]
	str	r3, [r4, #464]
	movls	r1, #0
	ldr	r0, [r5, #48]
	movhi	r1, #1
	cmp	r0, #1
	movne	r1, #0
	cmp	r1, #0
	beq	.L846
	ldr	r5, [r9, #104]
	rsb	lr, r2, ip
	sub	r1, fp, #124
	mov	r0, r8
	ldr	r2, [r4, #212]
	add	lr, r5, lr
	str	ip, [fp, #-112]
	mov	r5, #1
	mov	ip, #2
	str	lr, [fp, #-124]
	str	r3, [fp, #-108]
	strb	r5, [fp, #-118]
	strb	ip, [fp, #-119]
	bl	InsertStreamSeg
	b	.L846
.L856:
	cmp	r8, #0
	beq	.L847
	ldr	r3, [r4, #116]
	ldr	r0, [r4, #112]
	rsb	r3, r0, r3
	ubfx	r3, r3, #0, #12
	rsb	r3, r3, #4096
	cmp	r3, #3
	movls	r3, #0
	movhi	r3, #1
.L847:
	cmp	r1, #3
	movls	r3, #0
	andhi	r3, r3, #1
	cmp	r3, #0
	beq	.L846
	ldr	r3, [r9, #104]
	rsb	r0, r2, ip
	sub	r1, fp, #124
	ldr	r2, [r4, #212]
	add	r3, r3, r0
	mov	r0, r8
	str	ip, [fp, #-112]
	mov	r5, #2
	str	lr, [fp, #-108]
	str	r3, [fp, #-124]
	mov	r3, #0
	strb	r5, [fp, #-119]
	strb	r3, [fp, #-118]
	bl	InsertStreamSeg
	ldr	lr, [r9, #104]
	sub	r1, fp, #124
	ldr	ip, [r4, #128]
	mov	r0, r8
	ldr	r2, [r4, #212]
	mov	r3, #1
	strb	r5, [fp, #-119]
	str	lr, [fp, #-124]
	str	r6, [fp, #-108]
	str	ip, [fp, #-112]
	strb	r3, [fp, #-118]
	bl	InsertStreamSeg
	b	.L846
.L858:
	.align	2
.L857:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SetLastUnfinishedSegInfo, .-SetLastUnfinishedSegInfo
	.align	2
	.global	ProcessSegRoll
	.type	ProcessSegRoll, %function
ProcessSegRoll:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
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
	add	r5, r0, #425984
	mov	r4, r1
	add	r6, r0, #98304
	ldr	r1, [r5, #188]
	adds	r8, r6, #104
	ldr	r9, [r5, #128]
	ldr	r0, [r5, #460]
	ldr	r7, [r1]
	ldrsb	r1, [fp, #4]
	rsb	r2, r0, r2
	rsb	r7, r9, r7
	add	ip, r2, r7
	str	r1, [fp, #-56]
	beq	.L860
	ldr	lr, [r5, #112]
	cmp	ip, #3
	ldr	r1, [r5, #116]
	str	r0, [r4, #12]
	ldr	r10, [r5, #128]
	rsb	r1, lr, r1
	ldr	lr, [r6, #104]
	ubfx	r1, r1, #0, #12
	rsb	r0, r10, r0
	rsb	r1, r1, #4096
	add	r0, lr, r0
	str	ip, [r4, #16]
	str	r0, [r4]
	bls	.L866
	cmp	r1, #2
	bls	.L864
.L863:
	mov	r1, r8
	mov	r0, r4
	str	r3, [fp, #-52]
	str	r2, [fp, #-48]
	bl	CheckSegValid
	subs	r10, r0, #0
	bne	.L864
	ldr	r2, [fp, #-48]
	cmp	r7, #0
	ldr	r3, [fp, #-52]
	str	r2, [r4, #16]
	beq	.L868
	strb	r3, [r4, #5]
	mov	r1, r4
	strb	r10, [r4, #6]
	mov	r0, r8
	ldr	r2, [r5, #212]
	bl	InsertStreamSeg
	str	r9, [r4, #12]
	ldr	r2, [r5, #128]
	mov	ip, #1
	ldr	r3, [r6, #104]
	mov	r0, r8
	rsb	r9, r2, r9
	str	r7, [r4, #16]
	add	r9, r3, r9
	ldrb	r3, [fp, #-56]	@ zero_extendqisi2
	str	r9, [r4]
	mov	r1, r4
	strb	ip, [r4, #6]
	strb	r3, [r4, #5]
	ldr	r2, [r5, #212]
	bl	InsertStreamSeg
.L867:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L868:
	strb	r3, [r4, #5]
	mov	r0, r8
	mov	r3, #1
	mov	r1, r4
	strb	r3, [r4, #6]
	ldr	r2, [r5, #212]
	bl	InsertStreamSeg
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L860:
	str	r0, [r4, #12]
	cmp	ip, #3
	ldr	lr, [r5, #128]
	ldr	r1, [r6, #104]
	rsb	r0, lr, r0
	str	ip, [r4, #16]
	add	r0, r1, r0
	str	r0, [r4]
	bhi	.L863
.L866:
	mov	r3, ip
	movw	r2, #2754
	ldr	r1, .L869
	mov	r0, #0
	bl	dprint_vfmw
	mov	r10, #0
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L864:
	mvn	r10, #3
	b	.L867
.L870:
	.align	2
.L869:
	.word	.LC28
	UNWIND(.fnend)
	.size	ProcessSegRoll, .-ProcessSegRoll
	.align	2
	.global	ProcessLastUnfinishedSeg
	.type	ProcessLastUnfinishedSeg, %function
ProcessLastUnfinishedSeg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	add	r4, r0, #425984
	mov	r6, r2
	mov	r8, r1
	mov	r2, #80
	mov	r5, r0
	mov	r1, #0
	sub	r0, fp, #116
	bl	memset
	ldr	r3, [r6, #28]
	ldr	r2, [r4, #128]
	ldr	r7, [r6, #16]
	cmp	r2, r3
	addhi	r3, r3, r7
	rsbhi	r7, r2, r3
	cmp	r8, #0
	bne	.L873
	ldr	r3, [r4, #256]
	ldr	r1, [r4, #260]
	cmp	r3, r1
	movle	r3, #0
	movgt	r3, #1
	strb	r3, [r5]
	ldr	r0, [r4, #460]
	cmp	r0, #0
	ldreq	r1, [r4, #164]
	beq	.L875
	ldr	ip, [r4, #468]
	ldr	r3, [r4, #464]
	ldr	r1, [r4, #164]
	cmp	ip, #0
	add	r3, r1, r3
	str	r3, [r4, #464]
	bne	.L876
	ldr	r3, [r6, #28]
	cmp	r0, r3
	strhi	r7, [r4, #472]
	movhi	r3, #1
	strhi	r3, [r4, #468]
.L876:
	mov	r3, #0
	str	r3, [r4, #456]
	ldr	r3, [r6, #28]
	cmp	r3, r2
	movcc	r3, r2
	str	r3, [r4, #452]
.L875:
	add	r0, r5, #80
	bl	DeleteRawLen
.L877:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L873:
	mov	r6, #0
	strb	r6, [r5]
	ldr	r0, [r4, #460]
	cmp	r0, r6
	beq	.L877
	ldr	r3, .L885
	add	r1, r4, #480
	mov	r2, #80
	sub	r0, fp, #116
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r1, [r4, #468]
	cmp	r1, #1
	beq	.L883
	ldr	r0, [r4, #188]
	ldr	r3, [r4, #460]
	ldr	r2, [r0]
	cmp	r2, r3
	bcc	.L879
	add	r5, r5, #98304
	ldr	r2, [r4, #128]
	str	r3, [fp, #-104]
	mov	ip, #1
	ldr	r1, [r5, #104]
	rsb	r2, r2, r3
	add	r2, r1, r2
	str	r2, [fp, #-116]
	ldr	r2, [r0]
	strb	ip, [fp, #-110]
	rsb	r3, r3, r2
	strb	ip, [fp, #-111]
	cmp	r3, #3
	str	r3, [fp, #-100]
	bls	.L884
	add	r5, r5, #104
	sub	r0, fp, #116
	mov	r1, r5
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L882
	ldr	r2, [r4, #212]
	sub	r1, fp, #116
	mov	r0, r5
	bl	InsertStreamSeg
	b	.L877
.L879:
	str	r6, [sp]
	mov	r2, r7
	sub	r1, fp, #116
	mov	r0, r5
	mov	r3, #1
	bl	ProcessSegRoll
	b	.L877
.L883:
	ldr	r2, [r4, #472]
	mov	r3, r1
	str	r1, [sp]
	mov	r0, r5
	sub	r1, fp, #116
	bl	ProcessSegRoll
	b	.L877
.L884:
	movw	r2, #2843
	ldr	r1, .L885+4
	mov	r0, r6
	bl	dprint_vfmw
	mov	r0, r6
	b	.L877
.L882:
	mvn	r0, #3
	b	.L877
.L886:
	.align	2
.L885:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	UNWIND(.fnend)
	.size	ProcessLastUnfinishedSeg, .-ProcessLastUnfinishedSeg
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
	movw	r2, #2882
	mov	r4, r0
	mov	r3, r1
	mov	r0, #0
	ldr	r1, .L891
	bl	dprint_vfmw
	add	r0, r4, #80
	mov	r1, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DeleteRawPacket
.L892:
	.align	2
.L891:
	.word	.LC29
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
	add	r5, r0, #425984
	str	r1, [fp, #-132]
	mov	r4, r0
	ldr	r1, [r5, #284]
	add	r9, r0, #98304
	str	r2, [fp, #-152]
	add	r10, r9, #104
	ldr	r2, [r5, #188]
	mov	r3, r1, asl #2
	str	r1, [fp, #-160]
	mov	r1, #0
	str	r0, [fp, #-156]
	mov	ip, r2
	mov	lr, r3
	str	r2, [fp, #-164]
	mov	r8, r1
	str	r3, [fp, #-140]
	sub	r0, fp, #124
	mov	r3, ip
	mov	r2, #80
	add	ip, r3, lr
	mov	r6, r3
	str	ip, [fp, #-136]
	mov	r7, r8
	bl	memset
	add	r3, r4, #80
	str	r3, [fp, #-144]
	b	.L895
.L917:
	rsb	r3, r1, r4
	ldr	r2, [r5, #128]
	ldr	r0, [r9, #104]
	cmp	r3, #3
	rsb	r2, r2, r1
	str	r1, [fp, #-112]
	add	r2, r0, r2
	mov	r1, #1
	str	r3, [fp, #-108]
	str	r2, [fp, #-124]
	strb	r1, [fp, #-118]
	bls	.L916
	mov	r1, r10
	sub	r0, fp, #124
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L902
	ldr	ip, [r5, #212]
	sub	r3, fp, #124
	strb	r0, [fp, #-119]
	add	r2, r5, #248
	ldr	r1, [r6, #4]
	ldr	r0, [fp, #-144]
	str	ip, [sp]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #212]
	sub	r1, fp, #124
	mov	r0, r10
	bl	InsertStreamSeg
	cmp	r0, #0
	bne	.L902
.L898:
	ldr	r3, [fp, #-140]
	ldr	r7, [fp, #-128]
	add	r6, r6, r3
	add	r8, r8, r3
.L895:
	ldr	r3, [fp, #-132]
	cmp	r7, r3
	beq	.L902
	add	r3, r7, #1
	str	r3, [fp, #-128]
	ldr	r3, [fp, #-136]
	ldr	r1, [r6]
	ldr	r4, [r3, r8]
	cmp	r1, r4
	bls	.L917
	ldr	r3, [fp, #-152]
	cmp	r10, #0
	ldr	ip, [r5, #128]
	ldr	r2, [r3, #16]
	rsb	r4, ip, r4
	rsb	r2, r1, r2
	add	r3, r2, r4
	beq	.L903
	ldr	r0, [r5, #116]
	rsb	ip, ip, r1
	ldr	lr, [r5, #112]
	cmp	r3, #3
	str	r1, [fp, #-112]
	rsb	r0, lr, r0
	ldr	r1, [r9, #104]
	ubfx	r0, r0, #0, #12
	str	r3, [fp, #-108]
	add	ip, r1, ip
	rsb	r0, r0, #4096
	str	ip, [fp, #-124]
	bls	.L910
	cmp	r0, #2
	bls	.L902
.L911:
	mov	r1, r10
	sub	r0, fp, #124
	str	r2, [fp, #-148]
	bl	CheckSegValid
	subs	r3, r0, #0
	mov	r1, r3
	bne	.L902
	cmp	r4, #0
	ldr	ip, [r5, #212]
	ldr	r2, [fp, #-148]
	bne	.L905
	str	r2, [fp, #-108]
	mov	r1, #1
	strb	r4, [fp, #-119]
	add	r2, r5, #248
	strb	r1, [fp, #-118]
	sub	r3, fp, #124
	ldr	r1, [r6, #4]
	ldr	r0, [fp, #-144]
	str	ip, [sp]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #212]
	sub	r1, fp, #124
	mov	r0, r10
	bl	InsertStreamSeg
	b	.L898
.L905:
	str	r2, [fp, #-108]
	mov	r7, r1
	strb	r1, [fp, #-118]
	sub	r3, fp, #124
	strb	r1, [fp, #-119]
	add	r2, r5, #248
	ldr	r1, [r6, #4]
	ldr	r0, [fp, #-144]
	str	ip, [sp]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #212]
	sub	r1, fp, #124
	mov	r0, r10
	bl	InsertStreamSeg
	ldr	lr, [r5, #128]
	ldr	ip, [r9, #104]
	sub	r1, fp, #124
	ldr	r2, [r5, #212]
	mov	r0, r10
	mov	r3, #1
	str	r4, [fp, #-108]
	strb	r7, [fp, #-119]
	str	lr, [fp, #-112]
	str	ip, [fp, #-124]
	strb	r3, [fp, #-118]
	bl	InsertStreamSeg
	b	.L898
.L903:
	ldr	r0, [r9, #104]
	cmp	r3, #3
	rsb	ip, ip, r1
	str	r1, [fp, #-112]
	add	ip, r0, ip
	str	r3, [fp, #-108]
	str	ip, [fp, #-124]
	bhi	.L911
.L910:
	movw	r2, #2956
	ldr	r1, .L921
	mov	r0, #0
	bl	dprint_vfmw
	b	.L898
.L916:
	movw	r2, #2924
	ldr	r1, .L921
	mov	r0, #0
	bl	dprint_vfmw
	b	.L898
.L902:
	cmp	r7, #0
	ble	.L918
	ldr	r3, [fp, #-152]
	ldr	r1, [r3, #12]
	sub	r1, r1, #1
	cmp	r1, r7
	bhi	.L919
.L907:
	cmp	r1, r7
	beq	.L920
.L909:
	ldr	r2, [fp, #-152]
	mov	r1, #0
	ldr	r0, [fp, #-156]
	bl	SetLastUnfinishedSegInfo
.L894:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L918:
	blt	.L909
	ldr	r3, [fp, #-152]
	ldr	r1, [r3, #12]
	sub	r1, r1, #1
	b	.L907
.L919:
	ldr	r3, [fp, #-160]
	ldr	r2, [fp, #-164]
	ldr	r0, [fp, #-156]
	mul	r3, r3, r7
	add	r3, r3, #1
	ldr	r4, [r2, r3, asl #2]
	bl	ResetLastUnfinishedSegInfo
	ldr	r0, [fp, #-144]
	bic	r4, r4, #-1073741824
	mov	r1, r4
	bl	DeleteRawLen
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L920:
	ldr	r4, [r5, #164]
	ldr	r0, [fp, #-156]
	ldr	r2, [fp, #-152]
	bl	SetLastUnfinishedSegInfo
	mov	r1, r4
	ldr	r0, [fp, #-144]
	bl	DeleteRawLen
	b	.L894
.L922:
	.align	2
.L921:
	.word	.LC28
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
	add	r6, r0, #425984
	subs	r8, r1, #0
	ldr	r7, [r6, #284]
	ldr	r4, [r6, #188]
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	mov	r7, r7, asl #2
	mov	r5, #0
	movw	r9, #438
	b	.L933
.L929:
	add	r5, r5, #1
	add	r4, r4, r7
	cmp	r5, r8
	beq	.L942
.L933:
	ldr	r0, [r4]
	bl	MEM_Phy2Vir
	mov	ip, #1
	mov	r1, #0
	cmp	r0, #0
	beq	.L943
	ldrb	lr, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r2, [r0, #3]	@ zero_extendqisi2
	mov	lr, lr, asl #16
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	orr	r3, lr, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, r0, asl #8
	bic	r2, r3, #1020
	cmp	r3, r9
	cmpne	r3, #288
	bic	r2, r2, #3
	streq	ip, [r6, #232]
	streq	r1, [r6, #236]
	cmp	r2, #32768
	bne	.L929
	ldr	r3, [r6, #232]
	cmp	r3, #1
	beq	.L930
.L932:
	add	r5, r5, #1
	mov	r3, #2
	cmp	r5, r8
	str	r3, [r6, #232]
	add	r4, r4, r7
	bne	.L933
.L942:
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L930:
	ldr	r3, [r6, #236]
	add	r3, r3, #1
	str	r3, [r6, #236]
	cmp	r3, #30
	bls	.L929
	ldr	r3, .L944
	mov	r1, #102
	ldr	r10, [r3]
	mov	r3, #0
	mov	r2, r3
	cmp	r10, r3
	beq	.L932
	ldr	r0, [r6, #212]
	blx	r10
	b	.L932
.L943:
	movw	r3, #3025
	ldr	r2, .L944+4
	ldr	r1, .L944+8
	mov	r0, ip
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L945:
	.align	2
.L944:
	.word	g_event_report
	.word	.LANCHOR3+104
	.word	.LC30
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
	add	r5, r0, #425984
	mov	r7, r0
	mov	r8, r1
	ldr	r3, [r5, #284]
	mov	r10, r2
	str	r0, [fp, #-236]
	sub	r0, fp, #204
	str	r1, [fp, #-240]
	mov	r1, #0
	mov	r9, r3
	str	r3, [fp, #-244]
	ldr	r3, [r5, #188]
	mov	r9, r9, asl #2
	str	r2, [fp, #-232]
	mov	r2, #80
	mov	r6, r3
	str	r3, [fp, #-248]
	bl	memset
	mov	r2, #80
	mov	r1, #0
	sub	r0, fp, #124
	bl	memset
	ldr	r0, [r5, #128]
	bl	MEM_Phy2Vir
	mov	r4, r0
	ldr	r0, [r10, #16]
	bl	MEM_Phy2Vir
	ldr	r3, .L991
	mov	r1, r4
	mov	r2, #4
	mov	r4, r6
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, r8
	mov	r0, r7
	bl	GetMpeg4ModeFlag
	add	r3, r7, #98304
	mov	r2, r8
	mov	r1, r6
	mov	r0, r7
	mov	r6, r3
	str	r3, [fp, #-220]
	add	r3, r4, r9
	str	r3, [fp, #-216]
	bl	GetNextVop
	mov	r8, #0
	add	r3, r7, #80
	add	r6, r6, #104
	str	r3, [fp, #-224]
	mov	r7, r8
	str	r0, [fp, #-212]
	b	.L947
.L985:
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L949
	ldr	r3, [fp, #-108]
	mov	r1, r6
	sub	r0, fp, #124
	add	r10, r3, r10
	str	r10, [fp, #-108]
	bl	CheckSegValid
	subs	r3, r0, #0
	bne	.L953
	ldr	r2, [r5, #212]
	sub	r1, fp, #124
	mov	r0, r6
	strb	r3, [fp, #-119]
	str	r3, [fp, #-228]
	bl	InsertStreamSeg
	ldr	r3, [fp, #-228]
	mov	r2, #80
	mov	r1, r3
	ldr	r3, .L991
	ldr	r3, [r3, #48]
	mov	r10, r0
	sub	r0, fp, #124
	blx	r3
	cmp	r10, #0
	bne	.L953
.L954:
	ldr	r7, [fp, #-208]
	add	r4, r4, r9
	add	r8, r8, r9
.L947:
	ldr	r3, [fp, #-212]
	cmp	r7, r3
	beq	.L953
	add	r3, r7, #1
	str	r3, [fp, #-208]
	ldr	r3, [fp, #-216]
	ldr	r2, [r4]
	ldr	r0, [r3, r8]
	rsb	r10, r2, r0
	cmp	r10, #3
	bgt	.L985
	sub	r3, r10, #1
	cmp	r3, #2
	bls	.L986
	ldr	r3, [fp, #-232]
	cmp	r6, #0
	ldr	ip, [r5, #128]
	ldr	r10, [r3, #16]
	rsb	r3, r2, r10
	rsb	r10, ip, r0
	str	r3, [fp, #-228]
	add	r3, r3, r10
	beq	.L963
	rsb	r0, ip, r2
	str	r2, [fp, #-192]
	ldr	r2, [fp, #-220]
	cmp	r3, #3
	ldr	r1, [r5, #116]
	ldr	lr, [r5, #112]
	ldr	ip, [r2, #104]
	rsb	r2, lr, r1
	str	r3, [fp, #-188]
	ubfx	r2, r2, #0, #12
	add	r0, ip, r0
	rsb	r2, r2, #4096
	str	r0, [fp, #-204]
	bls	.L974
	cmp	r2, #2
	bls	.L953
.L975:
	mov	r1, r6
	sub	r0, fp, #204
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L953
	cmp	r10, #0
	ldr	r3, [r5, #232]
	bne	.L965
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	ldr	lr, [r5, #212]
	mov	ip, #0
	bfieq	r3, r10, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	mov	r2, #1
	ldr	r3, [r4, #4]
	ldrb	r1, [fp, #-132]	@ zero_extendqisi2
	mov	r3, r3, lsr #30
	bfi	r1, r3, #1, #1
	strb	r1, [fp, #-132]
	ldrh	r0, [r4, #10]
	sub	r3, fp, #204
	uxtb	r1, r1
	bfi	r1, r0, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r4, #8]
	ldrb	r0, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	r0, r1, #3, #4
	strb	r0, [fp, #-132]
	ldr	r0, [fp, #-228]
	ldr	r1, [r4, #8]
	strb	r2, [fp, #-198]
	add	r2, r5, #248
	str	r0, [fp, #-188]
	and	r1, r1, #7
	ldrh	r0, [fp, #-132]
	strb	ip, [fp, #-199]
	bfi	r0, r1, #7, #4
	strh	r0, [fp, #-132]	@ movhi
	ldr	r1, [r4, #4]
	ldr	r0, [fp, #-224]
	str	lr, [sp]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #212]
	sub	r1, fp, #204
	mov	r0, r6
	bl	InsertStreamSeg
	b	.L954
.L949:
	ldr	r3, [r5, #128]
	mov	r1, r6
	str	r2, [fp, #-192]
	sub	r0, fp, #204
	rsb	r2, r3, r2
	ldr	r3, [fp, #-220]
	str	r10, [fp, #-188]
	ldr	r3, [r3, #104]
	add	r2, r3, r2
	mov	r3, #1
	str	r2, [fp, #-204]
	strb	r3, [fp, #-198]
	bl	CheckSegValid
	cmp	r0, #0
	bne	.L953
	ldr	r3, [r5, #232]
	add	r2, r5, #248
	ldr	lr, [r5, #212]
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	bfieq	r3, r0, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	sub	r3, fp, #204
	ldr	r1, [r4, #4]
	ldrb	r0, [fp, #-132]	@ zero_extendqisi2
	mov	r1, r1, lsr #30
	bfi	r0, r1, #1, #1
	strb	r0, [fp, #-132]
	ldrh	ip, [r4, #10]
	uxtb	r1, r0
	ldr	r0, [fp, #-224]
	bfi	r1, ip, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r4, #8]
	ldrb	ip, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	ip, r1, #3, #4
	strb	ip, [fp, #-132]
	ldr	r1, [r4, #8]
	ldrh	ip, [fp, #-132]
	and	r1, r1, #7
	bfi	ip, r1, #7, #4
	strh	ip, [fp, #-132]	@ movhi
	ldr	r1, [r4, #4]
	str	lr, [sp]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #212]
	sub	r1, fp, #204
	mov	r0, r6
	mov	r3, #0
	strb	r3, [fp, #-199]
	bl	InsertStreamSeg
	cmp	r0, #0
	beq	.L954
.L953:
	cmp	r7, #0
	ble	.L952
	ldr	r3, [fp, #-232]
	ldr	r3, [r3, #12]
	sub	r3, r3, #1
	cmp	r3, r7
	bhi	.L987
	beq	.L988
.L952:
	ldr	r3, [fp, #-212]
	ldr	r2, [fp, #-240]
	clz	r3, r3
	cmp	r2, #1024
	mov	r3, r3, lsr #5
	movls	r3, #0
	cmp	r3, #0
	bne	.L989
.L973:
	ldr	r0, [fp, #-236]
	bl	ResetLastUnfinishedSegInfo
.L946:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L986:
	str	r2, [fp, #-228]
	bl	MEM_Phy2Vir
	ldr	r2, [fp, #-228]
	subs	ip, r0, #0
	beq	.L990
	ldrb	r1, [ip, #1]	@ zero_extendqisi2
	ldrb	r3, [ip]	@ zero_extendqisi2
	ldrb	r0, [ip, #2]	@ zero_extendqisi2
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r0, asl #8
	cmp	r3, #256
	beq	.L954
	ldr	r3, [r5, #232]
	mov	ip, #1
	cmp	r3, #1
	ldrb	r3, [fp, #-52]	@ zero_extendqisi2
	bfceq	r3, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-52]
	sub	r3, fp, #124
	ldr	r1, [r4, #4]
	ldrb	r0, [fp, #-52]	@ zero_extendqisi2
	mov	r1, r1, lsr #30
	bfi	r0, r1, #1, #1
	strb	r0, [fp, #-52]
	uxtb	r1, r0
	ldrh	r0, [r4, #10]
	bfi	r1, r0, #2, #1
	strb	r1, [fp, #-52]
	ldr	r1, [r4, #8]
	ldrb	r0, [fp, #-52]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	r0, r1, #3, #4
	strb	r0, [fp, #-52]
	ldr	r0, [r4, #8]
	ldrh	lr, [fp, #-52]
	and	r0, r0, #7
	ldr	r1, [r5, #128]
	bfi	lr, r0, #7, #4
	ldr	r0, [fp, #-220]
	strb	ip, [fp, #-118]
	rsb	r1, r1, r2
	str	r2, [fp, #-112]
	add	r2, r5, #248
	ldr	ip, [r0, #104]
	strh	lr, [fp, #-52]	@ movhi
	add	r1, ip, r1
	ldr	ip, [r5, #212]
	str	r10, [fp, #-108]
	str	r1, [fp, #-124]
	ldr	r1, [r4, #4]
	ldr	r0, [fp, #-224]
	str	ip, [sp]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	b	.L954
.L965:
	cmp	r3, #1
	ldrb	r3, [fp, #-132]	@ zero_extendqisi2
	ldr	ip, [r5, #212]
	mov	r7, #0
	bfieq	r3, r0, #0, #1
	orrne	r3, r3, #1
	strb	r3, [fp, #-132]
	sub	r3, fp, #204
	ldr	r2, [r4, #4]
	ldrb	r1, [fp, #-132]	@ zero_extendqisi2
	mov	r2, r2, lsr #30
	bfi	r1, r2, #1, #1
	strb	r1, [fp, #-132]
	ldrh	r0, [r4, #10]
	add	r2, r5, #248
	uxtb	r1, r1
	bfi	r1, r0, #2, #1
	strb	r1, [fp, #-132]
	ldr	r1, [r4, #8]
	ldrb	r0, [fp, #-132]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #3
	bfi	r0, r1, #3, #4
	strb	r0, [fp, #-132]
	ldr	r0, [fp, #-228]
	ldr	r1, [r4, #8]
	strb	r7, [fp, #-198]
	str	r0, [fp, #-188]
	and	r1, r1, #7
	ldrh	r0, [fp, #-132]
	strb	r7, [fp, #-199]
	bfi	r0, r1, #7, #4
	strh	r0, [fp, #-132]	@ movhi
	ldr	r1, [r4, #4]
	ldr	r0, [fp, #-224]
	str	ip, [sp]
	bic	r1, r1, #-1073741824
	bl	GetSegPts
	ldr	r2, [r5, #212]
	sub	r1, fp, #204
	mov	r0, r6
	bl	InsertStreamSeg
	ldr	r3, [fp, #-220]
	ldr	lr, [r5, #128]
	sub	r1, fp, #204
	ldr	r2, [r5, #212]
	mov	r0, r6
	ldr	ip, [r3, #104]
	mov	r3, #1
	strb	r7, [fp, #-199]
	str	r10, [fp, #-188]
	str	lr, [fp, #-192]
	str	ip, [fp, #-204]
	strb	r3, [fp, #-198]
	bl	InsertStreamSeg
	b	.L954
.L963:
	ldr	r1, [fp, #-220]
	cmp	r3, #3
	rsb	r0, ip, r2
	str	r2, [fp, #-192]
	str	r3, [fp, #-188]
	ldr	r1, [r1, #104]
	add	r0, r1, r0
	str	r0, [fp, #-204]
	bhi	.L975
.L974:
	movw	r2, #3165
	ldr	r1, .L991+4
	mov	r0, #0
	bl	dprint_vfmw
	b	.L954
.L987:
	ldr	r3, [fp, #-244]
	ldr	r2, [fp, #-248]
	ldr	r0, [fp, #-236]
	mul	r3, r3, r7
	add	r3, r3, #1
	ldr	r4, [r2, r3, asl #2]
	bl	ResetLastUnfinishedSegInfo
	ldr	r0, [fp, #-224]
	bic	r4, r4, #-1073741824
	mov	r1, r4
	bl	DeleteRawLen
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L989:
	ldr	r1, .L991+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r0, [fp, #-224]
	mov	r1, #1
	bl	DeleteRawPacket
	b	.L973
.L988:
	ldr	r4, [r5, #164]
	mov	r1, r7
	ldr	r0, [fp, #-236]
	ldr	r2, [fp, #-232]
	bl	SetLastUnfinishedSegInfo
	mov	r1, r4
	ldr	r0, [fp, #-224]
	bl	DeleteRawLen
	b	.L946
.L990:
	movw	r2, #3135
	ldr	r1, .L991+12
	bl	dprint_vfmw
	b	.L946
.L992:
	.align	2
.L991:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	.word	.LC32
	.word	.LC31
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	add	r4, r0, #425984
	mov	r5, r0
	ldr	r3, [r4, #168]
	cmp	r3, #3
	mov	r3, #2
	streq	r3, [r4, #168]
	mvneq	r0, #6
	beq	.L995
	str	r3, [r4, #168]
	sub	r0, fp, #60
	bl	ReadScdStateReg
	ldr	r6, [fp, #-48]
	movw	r3, #34464
	movt	r3, 1
	cmp	r6, r3
	bls	.L996
	ldr	r3, [r5, #16]
	cmp	r3, #0
	beq	.L1001
.L996:
	ldr	r1, [r4, #284]
	ldr	r0, [fp, #-36]
	bl	__aeabi_uidiv
	cmp	r0, r6
	movcc	r7, r0
	movcs	r7, r6
	cmp	r6, r7
	bhi	.L1002
.L998:
	sub	r2, fp, #60
	mov	r1, r7
	mov	r0, r5
	bl	ProcessLastUnfinishedSeg
	clz	r3, r7
	mov	r3, r3, lsr #5
	cmp	r0, #0
	moveq	r4, r3
	orrne	r4, r3, #1
	cmp	r4, #0
	bne	.L995
	ldr	r3, [r5, #16]
	sub	r2, fp, #60
	sub	r1, r7, #1
	mov	r0, r5
	cmp	r3, #2
	beq	.L999
	bl	ProcessNotMpeg4ScdUpMsg
	mov	r0, r4
.L995:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1002:
	ldrsb	r3, [r5, #2]
	cmp	r3, #1
	moveq	r3, #0
	streqb	r3, [r5, #2]
	b	.L998
.L999:
	bl	ProcessMpeg4ScdUpMsg
	mov	r0, r4
	b	.L995
.L1001:
	mov	r0, r5
	mov	r1, r6
	bl	ProcessExceptionalStartCodeNum
	mvn	r0, #6
	b	.L995
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
	ldr	r6, .L1011
	mov	r7, r0
	mov	r8, r1
	mov	r5, r2
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r4, .L1011+4
	mov	r0, #0
	ldr	r9, [r1, #16]
	ldr	r3, [r4, #16]
	blx	r3
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1005
	add	r1, r8, #32
	mov	r0, r9
	bl	SCDDRV_IsSCDByPass
	cmp	r0, #0
	bne	.L1010
.L1006:
	ldr	r2, [r6, r7, asl #2]
	ldr	r3, [r4, #44]
	ldr	r1, [r5, #12]
	ldr	r0, [r5, #40]
	blx	r3
.L1005:
	ldr	r3, [r4, #12]
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L1010:
	ldr	r3, [r4, #44]
	mov	r1, #4
	ldr	r2, [r6, r7, asl #2]
	add	r0, r5, #12
	blx	r3
	b	.L1006
.L1012:
	.align	2
.L1011:
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
	bne	.L1014
	ldr	r3, [r1, #60]
	cmp	r3, #0
	beq	.L1016
.L1014:
	add	r1, r1, #425984
	ldr	r3, [r1, #152]
	cmp	r3, #8
	bgt	.L1017
	ldr	r2, .L1018
	cmp	r3, #0
	movgt	r3, #0
	movle	r3, #1
	ldr	r2, [r2, r0, asl #2]
	add	r2, r2, #475136
	ldr	r0, [r2, #1332]
	cmp	r0, #1
	moveq	r0, r3
	orrne	r0, r3, #1
	ldmfd	sp, {fp, sp, pc}
.L1017:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1016:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1019:
	.align	2
.L1018:
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
	ldr	r3, .L1034
	mov	r4, r1
	mov	r2, #100
	add	r3, r3, r0, lsl #3
	ldr	r1, .L1034+4
	sub	r0, fp, #128
	ldr	r5, [r3, #68]
	bl	memcpy
	cmp	r4, #0
	beq	.L1033
	ldr	r3, [r5, #16]
	cmp	r3, #18
	bhi	.L1023
	mov	r1, #1
	movw	r2, #65406
	mov	r1, r1, asl r3
	movt	r2, 4
	and	r2, r2, r1
	cmp	r2, #0
	bne	.L1024
	tst	r1, #65536
	bne	.L1028
	tst	r1, #1
	subne	r1, fp, #128
	movne	r5, #15
	beq	.L1023
.L1025:
	ldr	r3, [r4, #12]
	ldr	r2, [r4, #80]
	add	r0, r5, r3
	cmp	r0, r2
	bhi	.L1026
	ldr	ip, .L1034+8
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
.L1024:
	ldr	r3, [r4, #12]
	ldr	r2, [r4, #80]
	cmp	r3, r2
	bhi	.L1030
	mov	r0, #0
.L1031:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1028:
	mov	r5, #16
	sub	r1, fp, #48
	b	.L1025
.L1023:
	ldr	r2, .L1034+12
	mov	r0, #0
	ldr	r1, .L1034+16
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1031
.L1030:
	mov	r5, #0
.L1026:
	str	r2, [sp, #4]
	mov	r0, #0
	str	r5, [sp]
	ldr	r2, .L1034+12
	ldr	r1, .L1034+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1031
.L1033:
	mov	r0, r4
	ldr	r2, .L1034+12
	ldr	r1, .L1034+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1031
.L1035:
	.align	2
.L1034:
	.word	.LANCHOR0
	.word	.LANCHOR3+124
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+224
	.word	.LC34
	.word	.LC35
	.word	.LC33
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
	ldr	r3, .L1058
	mov	r4, r1
	mov	r2, #100
	add	r3, r3, r0, lsl #3
	ldr	r1, .L1058+4
	sub	r0, fp, #120
	ldr	r5, [r3, #68]
	bl	memcpy
	cmp	r4, #0
	beq	.L1056
	ldr	r3, [r5, #16]
	cmp	r3, #18
	ldrls	pc, [pc, r3, asl #2]
	b	.L1039
.L1041:
	.word	.L1040
	.word	.L1042
	.word	.L1043
	.word	.L1044
	.word	.L1054
	.word	.L1054
	.word	.L1050
	.word	.L1039
	.word	.L1054
	.word	.L1054
	.word	.L1054
	.word	.L1054
	.word	.L1054
	.word	.L1054
	.word	.L1054
	.word	.L1040
	.word	.L1046
	.word	.L1054
	.word	.L1050
.L1040:
	sub	r1, fp, #120
	mov	r5, #15
.L1045:
	ldr	r3, [r4, #12]
	cmp	r5, r3
	bhi	.L1057
	ldr	r3, .L1058+8
	mov	r2, r5
	ldr	r0, [r4, #40]
	ldr	r3, [r3, #52]
	blx	r3
	str	r5, [r4, #12]
.L1054:
	mov	r0, #0
.L1052:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1050:
	mov	r5, #15
	sub	r1, fp, #100
	b	.L1045
.L1042:
	ldr	r3, [r5, #32]
	cmp	r3, #1
	bne	.L1054
	sub	r1, fp, #100
	mov	r5, #15
	b	.L1045
.L1043:
	mov	r5, #19
	sub	r1, fp, #80
	b	.L1045
.L1044:
	mov	r5, #16
	sub	r1, fp, #60
	b	.L1045
.L1046:
	mov	r5, #16
	sub	r1, fp, #40
	b	.L1045
.L1039:
	ldr	r2, .L1058+12
	mov	r0, #0
	ldr	r1, .L1058+16
	bl	dprint_vfmw
	mvn	r0, #6
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1057:
	str	r3, [sp]
	mov	r0, #0
	mov	r3, r5
	ldr	r2, .L1058+12
	ldr	r1, .L1058+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1052
.L1056:
	mov	r0, r4
	ldr	r2, .L1058+12
	ldr	r1, .L1058+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1052
.L1059:
	.align	2
.L1058:
	.word	.LANCHOR0
	.word	.LANCHOR3+244
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+344
	.word	.LC34
	.word	.LC36
	.word	.LC33
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
	beq	.L1070
	ands	r5, r0, #128
	bne	.L1071
	add	r6, r6, #425984
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #80]
	ldr	r0, [r6, #300]
	add	r3, r2, r0
	cmp	r3, r1
	bhi	.L1072
.L1068:
	ldr	r7, .L1075
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
.L1064:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1071:
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
	bne	.L1073
	ldr	r7, .L1075
	add	r6, r6, #425984
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
.L1070:
	ands	r5, r0, #128
	beq	.L1062
	ldr	r3, [r4, #12]
	cmp	r3, #127
	bhi	.L1074
	ldr	r2, .L1075
	add	r6, r6, #425984
	add	r0, r6, #304
	str	r3, [r6, #300]
	ldr	r3, [r2, #52]
	ldr	r1, [r4, #40]
	ldr	r2, [r4, #12]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1062:
	ldrb	r0, [r4, #72]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1064
	add	r6, r6, #425984
	ldr	r2, [r4, #12]
	ldr	ip, [r4, #80]
	ldr	r0, [r6, #300]
	add	r3, r2, r0
	cmp	r3, ip
	bls	.L1068
	mov	r0, r1
	str	ip, [sp]
	ldr	r2, .L1075+4
	ldr	r1, .L1075+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1064
.L1073:
	str	r1, [sp]
	mov	r0, #1
	mov	r1, #128
	ldr	r2, .L1075+4
	str	r1, [sp, #4]
	ldr	r1, .L1075+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1064
.L1072:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L1075+4
	ldr	r1, .L1075+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1064
.L1074:
	mov	r0, r1
	ldr	r2, .L1075+4
	mov	r1, #128
	str	r1, [sp]
	ldr	r1, .L1075+16
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1064
.L1076:
	.align	2
.L1075:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+364
	.word	.LC38
	.word	.LC39
	.word	.LC37
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
	bhi	.L1080
	ldr	r5, .L1081
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
.L1079:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1080:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L1081+4
	ldr	r1, .L1081+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1079
.L1082:
	.align	2
.L1081:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+384
	.word	.LC40
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
	beq	.L1084
	ldr	r3, [r1, #12]
	cmp	r3, #127
	bhi	.L1088
	ldr	r2, .L1090
	add	r4, r0, #425984
	add	r0, r4, #304
	str	r3, [r4, #300]
	ldr	r3, [r2, #52]
	ldr	r2, [r1, #12]
	ldr	r1, [r1, #40]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1084:
	add	r4, r0, #425984
	ldr	r2, [r1, #12]
	ldr	r1, [r1, #80]
	ldr	r0, [r4, #300]
	add	r3, r2, r0
	cmp	r3, r1
	bhi	.L1089
	ldr	r7, .L1090
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
.L1086:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1089:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L1090+4
	ldr	r1, .L1090+8
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1086
.L1088:
	mov	r1, #128
	ldr	r2, .L1090+4
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L1090+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1086
.L1091:
	.align	2
.L1090:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+404
	.word	.LC41
	.word	.LC37
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
	bne	.L1098
	ldr	r2, [r1, #12]
	cmp	r2, #0
	ble	.L1101
	ldr	r2, .L1103
	add	r0, r2, r0, lsl #3
	ldr	r0, [r0, #68]
	ldr	r2, [r0, #16]
	cmp	r2, #5
	beq	.L1095
	cmp	r2, #8
	beq	.L1096
	cmp	r2, #1
	beq	.L1102
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1096:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillREAL8ExtraData
.L1095:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillDIVX3ExtraData
.L1102:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FillVC1ExtraData
.L1098:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1101:
	mov	r3, r2
	ldr	r1, .L1103+4
	ldr	r2, .L1103+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1104:
	.align	2
.L1103:
	.word	.LANCHOR0
	.word	.LC42
	.word	.LANCHOR3+424
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
	ldr	r5, .L1120
	mov	r2, #12
	mov	r1, #0
	ldr	r3, [r5, #48]
	mov	r4, r0
	sub	r0, fp, #144
	blx	r3
	cmp	r4, #0
	beq	.L1117
	mov	r1, r4
	ldr	r3, [r5, #52]
	mov	r2, #12
	sub	r0, fp, #144
	blx	r3
	mov	r1, r6
	ldr	r3, [r5, #52]
	sub	r0, fp, #132
	mov	r2, #96
	ldr	r6, .L1120+4
	blx	r3
	ldr	r3, [r4, #8]
	mov	r8, r7, asl #3
	cmp	r3, #0
	mvneq	r4, #6
	beq	.L1108
	add	r4, r6, r8
	ldr	r3, [r4, #68]
	ldr	r3, [r3, #56]
	cmp	r3, #1
	beq	.L1118
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
	beq	.L1111
	sub	r1, fp, #132
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	blx	r3
	mov	r4, r0
.L1111:
	ldr	r3, [r5, #28]
	mov	r0, #1
	mov	r1, r7
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
.L1110:
	cmp	r4, #0
	mvnne	r4, #6
.L1108:
	add	r6, r6, r8
	ldr	r0, [r6, #68]
	cmp	r0, #0
	movne	r0, r4
	beq	.L1119
.L1107:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1118:
	sub	r1, fp, #132
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	blx	r3
	mov	r4, r0
	b	.L1110
.L1117:
	mov	r2, r7
	mov	r0, r4
	ldr	r1, .L1120+8
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1107
.L1119:
	mov	r3, r7
	movw	r2, #4088
	ldr	r1, .L1120+12
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1107
.L1121:
	.align	2
.L1120:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC43
	.word	.LC44
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
	bhi	.L1134
	ldr	r9, .L1141
	mov	r10, r0, asl #3
	add	r3, r9, r10
	ldr	r7, [r3, #68]
	cmp	r7, #0
	beq	.L1134
	cmp	r1, #0
	beq	.L1138
.L1124:
	adds	r3, r7, #80
	str	r3, [fp, #-52]
	beq	.L1134
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
	beq	.L1134
	mov	r6, #0
	b	.L1128
.L1140:
	ldr	r2, [fp, #-48]
	cmp	r6, r2
	beq	.L1139
.L1128:
	mov	r5, r4, asl #7
	ldr	r2, .L1141+4
	sub	r5, r5, r4, asl #5
	ldr	r1, .L1141+8
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
	add	r3, r9, r10
	ldr	r2, [r3, #68]
	subs	r3, r7, r2
	movne	r3, #1
	cmp	r2, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	beq	.L1140
	mvn	r0, #6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1138:
	add	r3, r7, #425984
	ldr	r3, [r3, #228]
	cmp	r3, #0
	bne	.L1124
.L1134:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1139:
	ldr	r2, [fp, #-56]
	ldr	r4, [r2, #88]
	add	r4, r4, r6
	cmp	r4, #1024
	strlt	r4, [r2, #88]
	subge	r4, r4, #1024
	movge	r0, r3
	ldrge	r3, [fp, #-56]
	movlt	r0, r3
	strge	r4, [r3, #88]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1142:
	.align	2
.L1141:
	.word	.LANCHOR0
	.word	.LANCHOR3+440
	.word	.LC10
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
	mov	r6, r0
	bhi	.L1155
	ldr	r7, .L1167
	mov	r10, r0, asl #3
	add	r3, r7, r10
	ldr	r5, [r3, #68]
	cmp	r5, #0
	beq	.L1145
	ldr	r3, [r7, #44]
	cmp	r3, r0
	bne	.L1147
	mov	r0, #0
	bl	SCDDRV_SetStateIdle.part.0
	movw	r3, #1149
	ldr	r2, .L1167+4
	mov	r0, #22
	ldr	r1, .L1167+8
	bl	dprint_vfmw
.L1147:
	ldr	r8, .L1167+12
	add	r4, r5, #425984
	mov	r2, #72
	add	r1, r5, #8
	sub	r0, fp, #244
	add	r9, r4, #304
	ldr	r3, [r8, #52]
	add	r7, r7, r10
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
	ldr	r3, [r7, #68]
	cmp	r3, #0
	beq	.L1148
	add	r3, r3, #425984
	ldr	r2, [r3, #228]
	cmp	r2, #0
	bne	.L1165
.L1148:
	adds	r7, r5, #80
	beq	.L1149
.L1166:
	add	r2, r5, #98304
	ldr	r3, [r2, #84]
	ldr	r1, [r2, #80]
	subs	r1, r3, r1
	addmi	r1, r1, #1024
.L1154:
	mov	r0, r7
	bl	DeleteRawPacket
	mov	r1, #1
	mov	r0, r6
	bl	DeleteRawPacketInBuffer
	ldrb	r7, [r4, #212]	@ zero_extendqisi2
	movw	r2, #49712
	ldr	r3, [r8, #48]
	movt	r2, 6
	mov	r1, #0
	mov	r0, r5
	sxtb	r7, r7
	blx	r3
	mov	r0, r5
	bl	ResetLastUnfinishedSegInfo
	mvn	r2, #0
	mvn	r3, #0
	mov	ip, #2
	strd	r2, [r4, #248]
	sub	r1, fp, #244
	str	ip, [r4, #284]
	mov	r0, r6
	str	r7, [r4, #212]
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
.L1162:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1165:
	ldr	r2, [r3, #216]
	cmp	r2, #0
	movle	r2, #0
	strle	r2, [r3, #228]
	adds	r7, r5, #80
	bne	.L1166
.L1149:
	ldr	r1, .L1167+16
	movw	r3, #1165
	ldr	r2, .L1167+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r1, r7
	b	.L1154
.L1155:
	mvn	r0, #0
	b	.L1162
.L1145:
	mov	r0, r5
	movw	r2, #1139
	ldr	r1, .L1167+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1162
.L1168:
	.align	2
.L1167:
	.word	.LANCHOR0
	.word	.LANCHOR3+464
	.word	.LC46
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	.LC45
	UNWIND(.fnend)
	.size	SM_Reset, .-SM_Reset
	.align	2
	.global	ReadRawStreamData
	.type	ReadRawStreamData, %function
ReadRawStreamData:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r5, .L1207
	ldr	r6, .L1207+4
	mov	r7, r0
	add	r5, r5, r0, lsl #3
	mov	r9, r1
	sub	r0, fp, #48
	mov	r2, #12
	ldr	r4, [r5, #68]
	mov	r1, #0
	ldr	r3, [r6, #48]
	blx	r3
	cmp	r4, #0
	beq	.L1173
	mov	r0, r7
	bl	VCTRL_GetStreamInterface
	subs	r8, r0, #0
	beq	.L1200
	ldr	r3, [r6, #52]
	sub	r0, fp, #48
	mov	r2, #12
	mov	r1, r8
	blx	r3
	ldr	r3, [r8, #4]
	cmp	r3, #0
	beq	.L1173
	ldr	r3, [r4, #56]
	cmp	r3, #1
	beq	.L1201
	ldr	r3, [r6, #16]
	mov	r0, #0
	blx	r3
	ldr	r3, [fp, #-44]
	mov	r1, r9
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r6, #12]
	mov	r8, r0
	mov	r0, #0
	blx	r3
	ldr	r2, [r5, #68]
	subs	r3, r4, r2
	movne	r3, #1
	cmp	r2, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L1202
	cmp	r8, #0
	bne	.L1173
.L1176:
	ldrb	r5, [r9, #1]	@ zero_extendqisi2
	cmp	r5, #1
	beq	.L1203
	ldr	r3, [r4, #56]
	cmp	r3, #1
	beq	.L1204
.L1178:
	add	r4, r4, #98304
	ldr	r2, [r9, #12]
	mov	r0, #0
	ldr	r3, [r4, #100]
	add	r3, r3, r2
	str	r3, [r4, #100]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1173:
	mvn	r0, #6
.L1197:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1202:
	mov	r3, r7
	movw	r2, #3993
	ldr	r1, .L1207+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1197
.L1201:
	ldr	r3, [fp, #-44]
	mov	r1, r9
	ldr	r0, [fp, #-48]
	blx	r3
	mov	r8, r0
	cmp	r8, #0
	beq	.L1176
	b	.L1173
.L1203:
	mov	r1, r9
	mov	r0, r7
	bl	FillEosRawStream
	cmp	r0, #0
	bne	.L1205
	mov	r1, r5
	mov	r0, r7
	bl	VCTRL_SetLastFrameState
	b	.L1178
.L1204:
	mov	r1, r9
	mov	r0, r7
	bl	FillExtraData
	cmp	r0, #0
	bne	.L1206
	add	r3, r4, #425984
	ldr	r3, [r3, #296]
	cmp	r3, #0
	beq	.L1178
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1178
	mov	r0, r7
	mov	r1, r9
	bl	FillEopRawStream
	b	.L1178
.L1206:
	mov	r2, r7
	ldr	r1, .L1207+12
	mov	r0, r8
	bl	dprint_vfmw
	mov	r1, r9
	ldr	r0, [fp, #-48]
	bl	ReleaseRawStreamData
	cmp	r0, #0
	beq	.L1173
	mov	r0, r8
	ldr	r1, .L1207+16
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1197
.L1200:
	mov	r2, r7
	ldr	r1, .L1207+20
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1197
.L1205:
	mov	r2, r7
	mov	r0, r8
	ldr	r1, .L1207+24
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1197
.L1208:
	.align	2
.L1207:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC49
	.word	.LC51
	.word	.LC52
	.word	.LC48
	.word	.LC50
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
	ldr	r8, .L1251
	mov	r9, r0, asl #3
	ldr	r7, .L1251+4
	add	r3, r8, r9
	mov	r4, r0
	mov	r2, #96
	mov	r1, #0
	ldr	r5, [r3, #68]
	sub	r0, fp, #140
	ldr	r3, [r7, #48]
	blx	r3
	cmp	r5, #0
	beq	.L1209
	ldr	r3, [r5, #16]
	cmp	r3, #20
	beq	.L1209
	mov	r3, r4, asl #24
	ldr	r6, .L1251+8
	str	r3, [fp, #-152]
	b	.L1225
.L1250:
	ldr	r3, [r5, #60]
	cmp	r3, #0
	bne	.L1211
.L1212:
	cmp	r4, #31
	bhi	.L1216
	add	r3, r8, r9
	ldr	r3, [r3, #68]
	cmp	r3, #0
	beq	.L1216
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
	beq	.L1216
	sub	r1, fp, #140
	mov	r0, r4
	bl	ReadRawStreamData
	subs	r3, r0, #0
	str	r3, [fp, #-144]
	bne	.L1209
	add	r10, r5, #425984
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
	beq	.L1219
	rsb	r1, r1, r0
	cmp	r1, #2000
	bls	.L1219
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
.L1219:
	ldrd	r2, [fp, #-76]
	mov	r0, #29
	ldr	r1, .L1251+12
	bl	dprint_vfmw
	ldr	r3, [fp, #-128]
	ldr	r2, [fp, #-136]
	mov	r0, #26
	ldr	r1, .L1251+16
	bl	dprint_vfmw
	ldrd	r2, [fp, #-76]
	mov	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1247
.L1220:
	sub	r1, fp, #140
	mov	r0, r4
	bl	SCDDRV_InsertRawPacket
	cmp	r0, #0
	bne	.L1248
	mov	r3, #1
	strb	r3, [r5, #3]
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1249
.L1223:
	sub	r2, fp, #140
	mov	r1, r5
	mov	r0, r4
	bl	SCDDRV_SaveRawStream
	ldr	r3, [r6, r4, asl #2]
	add	r3, r3, #475136
	ldr	r3, [r3, #1332]
	cmp	r3, #1
	beq	.L1209
.L1225:
	ldr	r3, [r5, #56]
	cmp	r3, #0
	beq	.L1250
.L1211:
	add	r3, r5, #425984
	ldr	r3, [r3, #152]
	cmp	r3, #8
	bgt	.L1209
	ldr	r2, [r6, r4, asl #2]
	cmp	r3, #0
	add	r2, r2, #475136
	movgt	r3, #0
	movle	r3, #1
	ldr	r2, [r2, #1332]
	cmp	r2, #1
	orrne	r3, r3, #1
	cmp	r3, #0
	bne	.L1212
.L1209:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1216:
	mov	r2, r4
	ldr	r1, .L1251+20
	mov	r0, #23
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1249:
	ldr	r3, [r7]
	blx	r3
	add	ip, r8, r4, lsl #2
	ldr	r2, .L1251+24
	ldr	r3, [ip, #340]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	cmp	r3, r2
	bls	.L1223
	str	r0, [ip, #340]
	movw	r1, #3402
	ldr	r2, [fp, #-152]
	ldr	r0, .L1251+28
	bl	DBG_AddTrace
	b	.L1223
.L1247:
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [fp, #-76]
	b	.L1220
.L1248:
	ldr	r1, .L1251+32
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1209
.L1252:
	.align	2
.L1251:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LC53
	.word	.LC54
	.word	.LC56
	.word	g_TraceBsPeriod
	.word	.LANCHOR3+476
	.word	.LC55
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
	cmp	r1, #4096
	mov	r4, r1
	mov	r8, r0
	mov	r6, r2
	beq	.L1258
	cmp	r1, r2
	beq	.L1259
	add	r9, r0, #327680
	mov	r5, #0
	mov	r7, #2
.L1257:
	mov	r3, r4, asl #6
	mov	r1, r4
	add	r3, r3, r4, lsl #4
	mov	r0, r8
	add	r3, r8, r3
	strb	r7, [r3, #12]
	ldr	ip, [r3, #24]
	ldr	r2, [r9, #44]
	ldr	r3, [r9, #48]
	rsb	r2, ip, r2
	sub	r3, r3, #1
	bic	r2, r2, r2, asr #31
	str	r2, [r9, #44]
	bic	r3, r3, r3, asr #31
	str	r3, [r9, #48]
	bl	ReleaseStreamSeg
	add	r3, r4, #1
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #20
	add	r3, r3, r4
	ubfx	r3, r3, #0, #12
	rsb	r4, r4, r3
	cmp	r0, #0
	addeq	r5, r5, #1
	cmp	r6, r4
	bne	.L1257
.L1255:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1258:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1259:
	mov	r5, #0
	b	.L1255
	UNWIND(.fnend)
	.size	ReleaseSegArrayPackets, .-ReleaseSegArrayPackets
	.align	2
	.global	SM_SeekPtsInSegArray
	.type	SM_SeekPtsInSegArray, %function
SM_SeekPtsInSegArray:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
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
	add	r7, r0, #425984
	mov	r3, r1
	add	r5, r0, #98304
	mov	r2, #0
	mov	r6, r0
	str	r1, [fp, #-60]
	add	r10, r5, #104
	ldrd	r0, [r1]
	mvn	r8, #0
	ldr	r4, [r7, #112]
	mvn	r9, #0
	str	r2, [fp, #-56]
	ldr	ip, [r7, #116]
	ldrd	r2, [r3, #8]
	strd	r0, [fp, #-52]
	str	r4, [r7, #120]
	strd	r2, [fp, #-68]
.L1262:
	cmp	r4, ip
	beq	.L1288
.L1263:
	mov	r3, r4, asl #6
	add	r3, r3, r4, lsl #4
	add	r3, r5, r3
	ldrb	r2, [r3, #116]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1285
	cmp	r2, #2
	beq	.L1289
	ldrd	r2, [r3, #144]
	cmp	r3, r9
	cmpeq	r2, r8
	beq	.L1285
	ldrd	r0, [fp, #-52]
	cmp	r1, r3
	cmpeq	r0, r2
	strhi	r4, [r7, #120]
	addhi	r3, r4, #1
	bhi	.L1284
	beq	.L1290
	bcs	.L1262
	ldr	lr, [r7, #120]
	strd	r2, [fp, #-76]
	mvn	r3, #0
	mvn	r2, #0
	mov	ip, lr, asl #6
	add	ip, ip, lr, lsl #4
	add	r5, r5, ip
	ldrd	r8, [r5, #144]
	cmp	r9, r3
	cmpeq	r8, r2
	beq	.L1286
	ldrd	r0, [fp, #-52]
	cmp	r1, r9
	cmpeq	r0, r8
	bhi	.L1291
.L1279:
	mov	r4, lr
.L1275:
	ldr	r3, [fp, #-60]
	strd	r8, [r3]
.L1273:
	mov	r2, r4
	ldr	r1, [r7, #112]
	mov	r0, r10
	bl	ReleaseSegArrayPackets
	ldr	r3, [r6, #4]
	cmp	r3, #0
	bne	.L1292
.L1276:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1289:
	mov	r1, r4
	mov	r0, r10
	bl	ReleaseStreamSeg
	ldr	ip, [r7, #116]
	cmp	r0, #0
	ldreq	r3, [fp, #-56]
	addeq	r3, r3, #1
	streq	r3, [fp, #-56]
	add	r3, r4, #1
.L1284:
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #20
	add	r3, r3, r4
	ubfx	r3, r3, #0, #12
	rsb	r4, r4, r3
	cmp	r4, ip
	bne	.L1263
.L1288:
	mov	r2, r4
	ldr	r1, [r7, #112]
	mov	r0, r10
	bl	ReleaseSegArrayPackets
	ldr	r3, [r6, #4]
	cmp	r3, #0
	bne	.L1293
.L1287:
	mvn	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1285:
	add	r3, r4, #1
	b	.L1284
.L1293:
	ldr	r3, [fp, #-56]
	add	r1, r0, r3
	add	r0, r6, #80
	bl	DeleteRawPacket
	b	.L1287
.L1290:
	ldr	r1, [fp, #-60]
	ldrd	r2, [fp, #-52]
	strd	r2, [r1]
	b	.L1273
.L1292:
	ldr	r3, [fp, #-56]
	add	r1, r0, r3
	add	r0, r6, #80
	bl	DeleteRawPacket
	b	.L1276
.L1291:
	subs	r0, r0, r8
	ldrd	r2, [fp, #-68]
	sbc	r1, r1, r9
	cmp	r3, r1
	cmpeq	r2, r0
	bcs	.L1279
.L1286:
	str	r4, [r7, #120]
	ldrd	r8, [fp, #-76]
	b	.L1275
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
	ldr	ip, .L1333
	str	r2, [fp, #-64]
	mov	lr, r0
	add	ip, ip, r2, lsl #3
	mov	r0, r1
	str	r1, [fp, #-72]
	ldr	r2, [ip, #68]
	str	r3, [fp, #-76]
	cmp	r2, #0
	str	r2, [fp, #-68]
	beq	.L1315
	add	r8, lr, #98304
	ldr	r9, [r8]
	cmp	r9, #0
	blt	.L1315
	ldr	r1, [r8, #4]
	cmp	r1, #0
	blt	.L1315
	cmp	r3, #1
	ldrd	r4, [r0]
	ldrd	r2, [r0, #8]
	strd	r4, [fp, #-60]
	strd	r2, [fp, #-92]
	movne	r3, #0
	strne	r3, [fp, #-80]
	beq	.L1327
.L1296:
	mov	r3, r9
	mvn	r6, #0
	mvn	r7, #0
	str	r9, [r8, #8]
	strd	r6, [fp, #-52]
.L1297:
	mov	r10, r3, asl #5
	mov	ip, r3, asl #7
	add	r2, r3, #1
	cmp	r3, r1
	rsb	r0, r10, ip
	add	r0, lr, r0
	mov	r7, r2, asr #31
	beq	.L1328
	ldrd	r4, [r0, #64]
	mov	r0, r7, lsr #22
	ldrd	r6, [fp, #-52]
	add	r2, r2, r0
	ubfx	r2, r2, #0, #10
	cmp	r5, r7
	cmpeq	r4, r6
	beq	.L1329
	ldrd	r6, [fp, #-60]
	cmp	r7, r5
	cmpeq	r6, r4
	bls	.L1303
	str	r3, [r8, #8]
	rsb	r3, r0, r2
	b	.L1297
.L1329:
	add	r2, r3, #1
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #22
	add	r2, r2, r3
	ubfx	r2, r2, #0, #10
	rsb	r3, r3, r2
	b	.L1297
.L1328:
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
.L1295:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1303:
	beq	.L1330
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
	beq	.L1309
	ldrd	r4, [fp, #-60]
	cmp	r5, r1
	cmpeq	r4, r0
	bhi	.L1331
.L1309:
	cmp	r9, r2
	ldr	r3, [fp, #-76]
	addgt	r1, r2, #1024
	rsble	r1, r9, r2
	rsbgt	r1, r9, r1
	cmp	r3, #1
	beq	.L1332
.L1312:
	mov	r3, r2, asl #7
	mov	r0, lr
	sub	r2, r3, r2, asl #5
	add	lr, lr, r2
	ldrd	r2, [lr, #64]
.L1326:
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
.L1327:
	ldr	r3, [fp, #-68]
	add	r3, r3, #425984
	ldr	r2, [r3, #168]
	cmp	r2, #1
	str	r2, [fp, #-80]
	moveq	r2, #3
	streq	r2, [r3, #168]
	ldreq	r1, [r8, #4]
	ldreq	r9, [r8]
	b	.L1296
.L1331:
	subs	r4, r4, r0
	sbc	r5, r5, r1
	mov	r0, r4
	mov	r1, r5
	ldrd	r4, [fp, #-92]
	cmp	r5, r1
	cmpeq	r4, r0
	strcc	r3, [r8, #8]
	movcc	r2, r3
	b	.L1309
.L1330:
	cmp	r3, r9
	addlt	r3, r3, #1024
	rsb	r1, r9, r3
	ldr	r3, [fp, #-76]
	cmp	r3, #1
	bne	.L1307
	ldr	r3, [fp, #-68]
	ldr	r0, [fp, #-80]
	add	r3, r3, #425984
	ldr	r2, [r3, #160]
	cmp	r1, r2
	cmple	r0, #1
	moveq	r2, r0
	streq	r2, [r3, #168]
.L1307:
	rsb	ip, r10, ip
	mov	r0, lr
	add	r3, lr, ip
	ldrd	r2, [r3, #64]
	b	.L1326
.L1332:
	ldr	r3, [fp, #-68]
	ldr	ip, [fp, #-80]
	add	r3, r3, #425984
	ldr	r0, [r3, #160]
	cmp	r1, r0
	cmple	ip, #1
	moveq	r2, ip
	streq	r2, [r3, #168]
	ldreq	r2, [r8, #8]
	b	.L1312
.L1315:
	mvn	r0, #0
	b	.L1295
.L1334:
	.align	2
.L1333:
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	clz	r3, r1
	mov	r5, r0
	mov	r7, r1
	mov	r3, r3, lsr #5
	cmp	r0, #31
	movls	r4, r3
	orrhi	r4, r3, #1
	cmp	r4, #0
	bne	.L1349
	ldr	r3, .L1359
	add	r3, r3, r0, lsl #3
	ldr	r6, [r3, #68]
	cmp	r6, #0
	beq	.L1349
	mov	r0, r6
	bl	SM_SeekPtsInSegArray
	cmp	r0, #0
	bne	.L1338
.L1339:
	mov	r0, #0
.L1337:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1338:
	add	r8, r6, #80
	mov	r1, r4
	mov	r0, r5
	bl	DeleteRawPacketInBuffer
	mov	r0, r8
	mov	r3, #1
	mov	r2, r5
	mov	r1, r7
	bl	SM_SeekPtsInRawArray
	cmp	r0, #0
	beq	.L1339
	add	r6, r6, #98304
	ldr	r2, [r6, #80]
	ldr	r0, [r6, #84]
	cmp	r2, r0
	addgt	r0, r0, #1024
	rsb	r0, r2, r0
	ldrd	r2, [r7, #16]
	mov	r1, r0, asr #31
	cmp	r1, r3
	cmpeq	r0, r2
	bcs	.L1358
	subs	r2, r2, r0
	movw	r0, #1023
	sbc	r3, r3, r1
	and	r0, r0, r2
	mov	r1, #0
	mov	r6, r2, lsr #10
	and	r1, r1, r3
	orr	r6, r6, r3, asl #22
	orrs	r1, r0, r1
	addne	r6, r6, #1
	cmp	r6, #0
	movge	r4, #0
	blt	.L1347
.L1346:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r8
	add	r4, r4, #1
	bl	SM_SeekPtsAfterFillNewRaw
	cmp	r0, #0
	beq	.L1339
	cmp	r6, r4
	bge	.L1346
.L1347:
	mvn	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1349:
	mvn	r0, #0
	b	.L1337
.L1358:
	strd	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1359+4
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L1337
.L1360:
	.align	2
.L1359:
	.word	.LANCHOR0
	.word	.LC57
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
	bgt	.L1364
	ldr	r10, .L1366
	add	r5, r5, #425984
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
.L1365:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1364:
	str	r3, [sp]
	mov	r3, r2
	ldr	r1, .L1366+4
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #6
	b	.L1365
.L1367:
	.align	2
.L1366:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC58
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
	add	r4, r0, #425984
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
	bne	.L1370
	add	r5, r5, r5, lsr #31
	cmp	r9, r5, asr #1
	movlt	r3, #1
	movge	r3, #0
	cmp	r10, #127
	movgt	r3, #0
	andle	r3, r3, #1
	cmp	r3, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, .L1391
	mov	r2, #1
	strb	r2, [r0, #1]
	ldr	r3, [r3]
	blx	r3
	str	r7, [r4, #240]
	str	r0, [r4, #244]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1370:
	ldr	r3, .L1391
	ldr	r3, [r3]
	blx	r3
	ldr	r2, [r4, #244]
	cmp	r0, r2
	bls	.L1373
	rsb	r2, r2, r0
	str	r2, [r4, #240]
	cmp	r2, #1000
	ble	.L1389
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
	cmp	r9, #0
	bne	.L1376
	ldr	r3, [r4, #464]
	cmp	r3, #0
	beq	.L1376
	cmp	r8, #0
	beq	.L1379
	ldr	r1, [r4, #112]
	movw	r2, #43691
	ldr	r3, [r4, #116]
	movt	r2, 43690
	rsb	r3, r1, r3
	ubfx	r3, r3, #0, #12
	umull	r2, r3, r3, r2
	movs	r7, r3, lsr #1
	beq	.L1379
	mov	r5, r9
	b	.L1380
.L1390:
	ldr	r1, [r4, #112]
.L1380:
	add	r1, r5, r1
	mov	r0, r8
	add	r5, r5, #1
	bl	ReleaseStreamSeg
	cmp	r7, r5
	bne	.L1390
.L1379:
	ldr	r1, .L1391+4
	mov	r0, #0
	bl	dprint_vfmw
.L1378:
	mov	r3, #0
	strb	r3, [r6, #1]
	strb	r3, [r6]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1373:
	mov	r3, #0
	str	r0, [r4, #244]
	str	r3, [r4, #240]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1376:
	ldr	r1, .L1391+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r8
	mvn	r1, #0
	bl	ReleaseStreamSeg
	b	.L1378
.L1389:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1392:
	.align	2
.L1391:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC59
	.word	.LC60
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
	ldr	r3, .L1406
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #68]
	cmp	r3, #0
	beq	.L1396
	add	r2, r3, #425984
	ldr	r1, [r2, #228]
	cmp	r1, #0
	beq	.L1396
	ldr	r2, [r2, #220]
	cmp	r2, #1
	beq	.L1396
	add	r2, r3, #32
	ldr	ip, [r3, #16]
	sub	r3, fp, #24
	ldmia	r2, {r0, r1, r2}
	cmp	ip, #19
	stmia	r3, {r0, r1, r2}
	beq	.L1396
	mov	r1, r3
	mov	r0, ip
	bl	SCDDRV_IsSCDByPass
	adds	r0, r0, #0
	movne	r0, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1396:
	mov	r0, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1407:
	.align	2
.L1406:
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
	ldr	r2, .L1427
	mov	r3, r0, asl #2
	str	r1, [fp, #-48]
	add	r1, r2, r3
	mov	r6, r0
	ldr	r2, [r1, #324]
	cmp	r2, #0
	beq	.L1409
	cmp	r2, #1
	beq	.L1410
.L1419:
	mvn	r0, #2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1409:
	ldr	r2, .L1427
	rsb	r3, r3, r0, lsl #6
	ldr	r9, .L1427+4
	mov	r5, #32
	add	r3, r2, r3
	ldr	r4, [r3, #44]
	b	.L1418
.L1412:
	subs	r5, r5, #1
	beq	.L1419
.L1418:
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
	bne	.L1412
	ldr	r3, .L1427
	ldr	r2, [r9]
	add	r3, r3, r4, lsl #3
	ldr	r10, [r3, #68]
	blx	r2
	add	r8, r10, #425984
	ldr	r1, [r8, #280]
	subs	r1, r0, r1
	bmi	.L1424
	ldrsh	ip, [r10, #2]
	cmp	ip, #1
	beq	.L1425
.L1414:
	str	r0, [r8, #280]
	ldrsb	r1, [r10]
	cmp	r1, #1
	movne	r1, #0
	strneb	r1, [r10, #1]
	beq	.L1426
.L1417:
	ldr	r3, .L1427+8
	mov	r1, r6
	mov	r0, r10
	ldr	ip, [r3, r4, asl #2]
	add	ip, ip, #475136
	ldr	ip, [ip, #1320]
	str	ip, [r8, #432]
	bl	CutStreamWithSCD
	cmn	r0, #6
	mov	r7, r0
	movne	r1, #0
	moveq	r1, #1
	cmp	r0, #0
	strb	r1, [r10]
	bne	.L1412
	ldr	r2, [fp, #-48]
	mov	r3, #1
	ldr	r0, .L1427+12
	mov	r1, r3
	movw	ip, #4580
	str	r4, [r2]
	add	r2, r0, r4, lsl #2
	str	r3, [r8, #228]
	mov	r0, r4
	ldr	r3, .L1427+16
	str	ip, [sp]
	bl	RecordPOS
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1425:
	cmp	r1, #500
	bcc	.L1412
	b	.L1414
.L1424:
	str	r0, [r8, #280]
	ldrsh	r1, [r10, #2]
	cmp	r1, #1
	bne	.L1414
	b	.L1412
.L1426:
	mov	r0, r10
	bl	SCDDRV_ProcessSegFull
	b	.L1417
.L1410:
	mov	r3, #2
	mvn	r0, #2
	str	r3, [r1, #324]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1428:
	.align	2
.L1427:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LANCHOR0+468
	.word	.LANCHOR3+488
	UNWIND(.fnend)
	.size	SM_DoNextInstance, .-SM_DoNextInstance
	.align	2
	.type	SCDDRV_ActivateSCD.part.13, %function
SCDDRV_ActivateSCD.part.13:
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
	bne	.L1429
	ldr	r4, .L1432
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
	ldr	r3, .L1432+4
	ldr	r3, [r3]
	blx	r3
	movw	r3, #4799
	ldr	r2, .L1432+8
	ldr	r1, .L1432+12
	str	r0, [r4, #52]
	mov	r0, #26
	bl	dprint_vfmw
.L1429:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1433:
	.align	2
.L1432:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+508
	.word	.LC61
	UNWIND(.fnend)
	.size	SCDDRV_ActivateSCD.part.13, .-SCDDRV_ActivateSCD.part.13
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
	ldr	r3, .L1440
	mov	r4, r0
	ldr	r3, [r3]
	blx	r3
	mov	lr, r4, asl #2
	ldr	ip, .L1440+4
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
.L1441:
	.align	2
.L1440:
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
	ldr	r3, .L1452
	add	r0, r3, r0, lsl #3
	ldr	r4, [r0, #68]
	ldr	r0, [r4, #56]
	cmp	r0, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	adds	r5, r4, #80
	beq	.L1445
	add	r2, r4, #98304
	ldr	r3, [r2, #84]
	ldr	r2, [r2, #80]
	subs	r3, r3, r2
	addmi	r3, r3, #1024
.L1448:
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
	ldr	r1, .L1452+4
	bl	dprint_vfmw
	add	r4, r4, #425984
	ldr	r0, [r4, #212]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SM_Reset
.L1445:
	ldr	r1, .L1452+8
	bl	dprint_vfmw
	mov	r3, r5
	b	.L1448
.L1453:
	.align	2
.L1452:
	.word	.LANCHOR0
	.word	.LC62
	.word	.LC63
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
	subs	r6, r0, #0
	beq	.L1471
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1471:
	ldr	r5, .L1477
	ldr	r4, .L1477+4
	ldr	r3, [r5, #12]
	blx	r3
	ldr	r0, [r4, #64]
	add	r0, r0, #2112
	bl	MEM_ReadPhyWord
	tst	r0, #1
	bne	.L1472
.L1456:
	ldr	r3, .L1477+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1460
	mov	r1, #0
	mov	r0, r1
	bl	VDH_Notify_ModuleIdle
.L1460:
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1472:
	ldr	r0, [r4, #64]
	mov	r1, #1
	add	r0, r0, #2080
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldr	r9, [r4, #44]
	ldr	r0, [r4, #40]
	add	r3, r4, r9, lsl #3
	ldr	r8, [r3, #68]
	cmp	r8, #0
	cmpne	r0, #0
	moveq	r7, #1
	movne	r7, #0
	beq	.L1473
	ldr	r3, .L1477+12
	movw	r2, #4673
	mov	r1, #2
	str	r2, [sp]
	mov	r0, r9
	add	r2, r4, #596
	bl	RecordPOS
	mov	r0, r7
	bl	SCDDRV_RecordGlobalState
	ldr	r3, [r4, #48]
	cmp	r3, #1
	beq	.L1474
.L1458:
	ldr	r3, [r5, #128]
	mov	r0, #1
	blx	r3
	ldr	r3, [r5, #128]
	mov	r0, #0
	blx	r3
	b	.L1456
.L1474:
	add	r10, r8, #425984
	ldr	r3, [r10, #228]
	cmp	r3, #1
	beq	.L1475
.L1459:
	mov	r6, #0
	sub	r1, fp, #48
	str	r6, [r10, #220]
	mov	r0, r6
	bl	SM_DoNextInstance
	cmp	r0, r6
	bne	.L1476
	ldr	r2, [fp, #-48]
	mov	r1, #1
	ldr	r3, [r5]
	str	r1, [r4, #48]
	str	r2, [r4, #44]
	blx	r3
	str	r0, [r4, #52]
	b	.L1458
.L1473:
	mov	r0, r6
	bl	SCDDRV_SetStateIdle.part.0
	b	.L1456
.L1476:
	mov	r0, r6
	bl	SCDDRV_SetStateIdle.part.0
	b	.L1458
.L1475:
	mov	r1, r7
	mov	r0, r8
	bl	ProcessScdReturn
	mov	r0, r9
	bl	SCDDRV_MoveRawByOmxPath
	b	.L1459
.L1478:
	.align	2
.L1477:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	g_HalDisable
	.word	.LANCHOR3+528
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
	bne	.L1488
	ldr	r4, .L1491
	movw	r3, #4725
	str	r6, [sp]
	mov	r0, #26
	ldr	r2, .L1491+4
	ldr	ip, [r4, #48]
	ldr	r1, .L1491+8
	str	ip, [sp, #4]
	bl	dprint_vfmw
	ldr	r5, [r4, #48]
	cmp	r5, #0
	beq	.L1490
	movw	r3, #4734
	ldr	r2, .L1491+4
	ldr	r1, .L1491+8
	mov	r0, #26
	str	r5, [sp, #4]
	str	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, .L1491+12
	ldr	r3, [r3]
	blx	r3
	ldr	r3, [r4, #52]
	cmp	r0, r3
	strcc	r0, [r4, #52]
	bcc	.L1483
	rsb	r0, r3, r0
	cmp	r0, #2000
	bls	.L1483
	ldr	r2, [r4, #44]
	mov	r3, r6
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1491+16
	bl	dprint_vfmw
	ldr	r3, .L1491+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1484
	mov	r1, r6
	mov	r0, r6
	bl	VDH_Reset_Module
.L1485:
	mov	r0, #0
	mov	r5, #0
	bl	SCDDRV_SetStateIdle.part.0
	ldr	r0, [r4, #44]
	add	r4, r4, r0, lsl #3
	ldr	r3, [r4, #68]
	cmp	r3, #0
	addne	r3, r3, #425984
	movne	r2, #0
	strne	r2, [r3, #220]
	bl	DeleteLastSendRaw
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1483:
	mov	r2, #0
	movw	r3, #4780
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1491+4
	mov	r5, #1
	ldr	r1, .L1491+24
	bl	dprint_vfmw
.L1489:
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1490:
	str	r5, [sp]
	movw	r3, #4729
	ldr	r2, .L1491+4
	mov	r0, #26
	ldr	r1, .L1491+28
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1484:
	mov	r0, r6
	bl	ResetSCD
	b	.L1485
.L1488:
	mvn	r5, #0
	b	.L1489
.L1492:
	.align	2
.L1491:
	.word	.LANCHOR0
	.word	.LANCHOR3+548
	.word	.LC64
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC66
	.word	g_HalDisable
	.word	.LC67
	.word	.LC65
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
	b	SCDDRV_ActivateSCD.part.13
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
	ldr	r5, .L1506
	mov	r4, #0
	b	.L1497
.L1496:
	add	r4, r4, #1
	cmp	r4, #32
	beq	.L1505
.L1497:
	ldr	r3, [r5, r4, asl #3]
	cmp	r3, #0
	add	r2, r3, #425984
	beq	.L1496
	ldr	r3, [r2, #228]
	cmp	r3, #1
	bne	.L1496
	mov	r0, r4
	add	r4, r4, #1
	bl	FillRawData
	cmp	r4, #32
	bne	.L1497
.L1505:
	mov	r2, #1
	mov	r3, #0
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1506+4
	ldr	r1, .L1506+8
	bl	dprint_vfmw
	mov	r0, #0
	bl	SCDDRV_CheckDevice
	subs	r4, r0, #0
	beq	.L1498
	mov	r2, #0
	movw	r3, #4828
	str	r2, [sp]
	mov	r0, #26
	ldr	r2, .L1506+4
	ldr	r1, .L1506+12
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1498:
	str	r4, [sp]
	movw	r3, #4823
	ldr	r2, .L1506+4
	mov	r0, #26
	ldr	r1, .L1506+16
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SCDDRV_ActivateSCD.part.13
.L1507:
	.align	2
.L1506:
	.word	.LANCHOR0+68
	.word	.LANCHOR3+568
	.word	.LC68
	.word	.LC69
	.word	.LC70
	UNWIND(.fnend)
	.size	SM_Wakeup, .-SM_Wakeup
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
	ldr	r3, .L1522
	mov	r2, r5
	ldr	r1, .L1522+4
	mov	r0, #26
	add	r3, r3, r5, lsl #3
	ldr	r8, [r3, #68]
	bl	dprint_vfmw
	ldr	r1, .L1522+8
	mov	r0, #26
	add	r7, r8, #98304
	ldr	r2, [r7, #80]
	bl	dprint_vfmw
	ldr	r2, [r7, #84]
	ldr	r1, .L1522+12
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r7, #88]
	ldr	r1, .L1522+16
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r7, #92]
	ldr	r1, .L1522+20
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r7, #96]
	ldr	r1, .L1522+24
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r6, #1
	beq	.L1512
.L1516:
	mov	r2, r5
	ldr	r1, .L1522+28
	mov	r0, #26
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1512:
	cmn	r8, #80
	beq	.L1513
	ldr	r4, [r7, #80]
	ldr	r7, [r7, #84]
	subs	r7, r7, r4
	addmi	r7, r7, #1024
	cmp	r7, #0
	ble	.L1516
	mov	r3, r4, asl #7
	mov	r6, #0
	sub	r3, r3, r4, asl #5
	add	r4, r8, r3
.L1515:
	ldr	r2, [r4, #84]
	mov	r0, #26
	ldr	r1, .L1522+32
	add	r6, r6, #1
	bl	dprint_vfmw
	ldrd	r2, [r4, #120]
	ldr	r1, .L1522+36
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #92]
	ldr	r1, .L1522+40
	mov	r0, #26
	bl	dprint_vfmw
	ldrd	r2, [r4, #144]
	ldr	r1, .L1522+44
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r6, r7
	add	r4, r4, #96
	bne	.L1515
	b	.L1516
.L1513:
	movw	r3, #4857
	ldr	r2, .L1522+48
	ldr	r1, .L1522+52
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1516
.L1523:
	.align	2
.L1522:
	.word	.LANCHOR0
	.word	.LC71
	.word	.LC72
	.word	.LC73
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LANCHOR3+580
	.word	.LC82
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
	ldr	r3, .L1538
	mov	r2, r6
	ldr	r1, .L1538+4
	mov	r0, #26
	add	r3, r3, r6, lsl #3
	ldr	r5, [r3, #68]
	bl	dprint_vfmw
	ldr	r1, .L1538+8
	mov	r0, #26
	add	r4, r5, #425984
	add	r8, r5, #98304
	ldr	r2, [r4, #112]
	bl	dprint_vfmw
	ldr	r2, [r4, #116]
	ldr	r1, .L1538+12
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #124]
	ldr	r1, .L1538+16
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #128]
	ldr	r1, .L1538+20
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r8, #104]
	ldr	r1, .L1538+24
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #132]
	ldr	r1, .L1538+28
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #136]
	ldr	r1, .L1538+32
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #140]
	ldr	r1, .L1538+36
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r7, #1
	beq	.L1528
.L1529:
	mov	r2, r6
	ldr	r1, .L1538+40
	mov	r0, #26
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1528:
	cmn	r8, #104
	beq	.L1529
	ldr	r2, [r4, #112]
	ldr	r8, [r4, #116]
	rsb	r8, r2, r8
	ubfx	r8, r8, #0, #12
	cmp	r8, #0
	ble	.L1529
	mov	r3, r2, asl #6
	mov	r7, #0
	add	r4, r3, r2, lsl #4
	add	r4, r4, #98304
	add	r4, r4, #124
	add	r4, r5, r4
.L1530:
	ldr	r2, [r4]
	mov	r0, #26
	ldr	r1, .L1538+44
	add	r7, r7, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #-12]
	ldr	r1, .L1538+48
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #4]
	ldr	r1, .L1538+52
	mov	r0, #26
	bl	dprint_vfmw
	ldr	r2, [r4, #8]
	ldr	r1, .L1538+56
	mov	r0, #26
	bl	dprint_vfmw
	ldrsb	r2, [r4, #-8]
	ldr	r1, .L1538+60
	mov	r0, #26
	bl	dprint_vfmw
	ldrb	r2, [r4, #-6]	@ zero_extendqisi2
	ldr	r1, .L1538+64
	mov	r0, #26
	bl	dprint_vfmw
	ldrd	r2, [r4, #12]
	ldr	r1, .L1538+68
	mov	r0, #26
	bl	dprint_vfmw
	cmp	r8, r7
	add	r4, r4, #80
	bne	.L1530
	b	.L1529
.L1539:
	.align	2
.L1538:
	.word	.LANCHOR0
	.word	.LC83
	.word	.LC84
	.word	.LC85
	.word	.LC86
	.word	.LC87
	.word	.LC88
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
	UNWIND(.fnend)
	.size	PrintScdSegState, .-PrintScdSegState
	.global	g_pScdDrvParamBase
	.global	s_ScdRegResetOKPhyAddr
	.global	s_ScdRegResetPhyAddr
	.global	s_ScdRegPhyBaseAddr
	.global	g_ScdDrvParam
	.global	s_SmIIS
	.global	g_hex_flag
	.global	g_hex_len
	.global	g_hex_base_addr
	.global	g_hex_base_vir_addr
	.section	.rodata
	.align	2
.LANCHOR3 = . + 0
	.type	__func__.52477, %object
	.size	__func__.52477, 19
__func__.52477:
	.ascii	"SCDDRV_LoadDspCode\000"
	.space	1
	.type	__func__.52549, %object
	.size	__func__.52549, 16
__func__.52549:
	.ascii	"DeleteRawPacket\000"
	.type	__FUNCTION__.52655, %object
	.size	__FUNCTION__.52655, 17
__FUNCTION__.52655:
	.ascii	"ReleaseStreamSeg\000"
	.space	3
	.type	__func__.52723, %object
	.size	__func__.52723, 14
__func__.52723:
	.ascii	"SM_OpenSCDDrv\000"
	.space	2
	.type	__func__.52798, %object
	.size	__func__.52798, 16
__func__.52798:
	.ascii	"SM_LinkRawToSeg\000"
	.type	__func__.52818, %object
	.size	__func__.52818, 16
__func__.52818:
	.ascii	"SM_CopyRawToSeg\000"
	.type	__func__.53151, %object
	.size	__func__.53151, 17
__func__.53151:
	.ascii	"GetMpeg4ModeFlag\000"
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
	.type	__func__.53225, %object
	.size	__func__.53225, 17
__func__.53225:
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
	.type	__func__.53253, %object
	.size	__func__.53253, 17
__func__.53253:
	.ascii	"FillEosRawStream\000"
	.space	3
	.type	__func__.53278, %object
	.size	__func__.53278, 17
__func__.53278:
	.ascii	"FillVC1ExtraData\000"
	.space	3
	.type	__func__.53283, %object
	.size	__func__.53283, 19
__func__.53283:
	.ascii	"FillDIVX3ExtraData\000"
	.space	1
	.type	__func__.53288, %object
	.size	__func__.53288, 19
__func__.53288:
	.ascii	"FillREAL8ExtraData\000"
	.space	1
	.type	__func__.53296, %object
	.size	__func__.53296, 14
__func__.53296:
	.ascii	"FillExtraData\000"
	.space	2
	.type	__func__.52563, %object
	.size	__func__.52563, 24
__func__.52563:
	.ascii	"DeleteRawPacketInBuffer\000"
	.type	__FUNCTION__.52697, %object
	.size	__FUNCTION__.52697, 9
__FUNCTION__.52697:
	.ascii	"SM_Reset\000"
	.space	3
	.type	__FUNCTION__.53215, %object
	.size	__FUNCTION__.53215, 12
__FUNCTION__.53215:
	.ascii	"FillRawData\000"
	.type	__FUNCTION__.53421, %object
	.size	__FUNCTION__.53421, 18
__FUNCTION__.53421:
	.ascii	"SM_DoNextInstance\000"
	.space	2
	.type	__func__.53458, %object
	.size	__func__.53458, 19
__func__.53458:
	.ascii	"SCDDRV_ActivateSCD\000"
	.space	1
	.type	__FUNCTION__.53445, %object
	.size	__FUNCTION__.53445, 19
__FUNCTION__.53445:
	.ascii	"SM_SCDIntServeProc\000"
	.space	1
	.type	__func__.53452, %object
	.size	__func__.53452, 19
__func__.53452:
	.ascii	"SCDDRV_CheckDevice\000"
	.space	1
	.type	__func__.53467, %object
	.size	__func__.53467, 10
__func__.53467:
	.ascii	"SM_Wakeup\000"
	.space	2
	.type	__FUNCTION__.53479, %object
	.size	__FUNCTION__.53479, 17
__FUNCTION__.53479:
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
	ASCII(.ascii	"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC3:
	ASCII(.ascii	"Warn: eVidStd = %d have not DSP vfmw bin file!!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC4:
	ASCII(.ascii	"%s failed!\012\000" )
.LC5:
	ASCII(.ascii	"%s success!\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"Ignore the reset request when the SCD[%d] clock is " )
	ASCII(.ascii	"closed.\012\000" )
.LC7:
	ASCII(.ascii	"SCD[%d]   ResetSCD ERROR!!!\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"line: %d Get SmID fail!\000" )
.LC9:
	ASCII(.ascii	"DelRaw err PacketNum = %d, DelNum = %d\012\000" )
.LC10:
	ASCII(.ascii	"%s release RawPhyAddr = 0x%x, Len = %d\012\000" )
.LC11:
	ASCII(.ascii	"line: %d DelNum = %d,RawPacketOffSet = %d,DelNum = " )
	ASCII(.ascii	"%d,Next Length = %d,is_extern_eop_flag = %d\012\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC12:
	ASCII(.ascii	"line: %d pSmInstArray is NULL!\012\000" )
.LC13:
	ASCII(.ascii	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLast" )
	ASCII(.ascii	"Seg=%d\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg" )
	ASCII(.ascii	"=%d StreamID=%d\012\000" )
.LC15:
	ASCII(.ascii	"Array out of bound in function %s\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"ScdId is wrong! %s error\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"%s: g_hex_base_vir_addr = NULL\012\000" )
.LC18:
	ASCII(.ascii	"line: %d, SmID = %d is not expected!\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"line: %d, SmID = %d, ScdId = %d is not expected!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC20:
	ASCII(.ascii	"%s not support discontinue raw.\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"%s VirAddr is null!!\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"Raw packet TOO BIG! Can't copy to seg! Len: 0x%x\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC23:
	ASCII(.ascii	"line: %d, delet raw failed!\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"[%s %d] VirAddr is null!!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"InstID = %d EsRelease!\012\000" )
.LC26:
	ASCII(.ascii	"Cann't Start SCD, Ret = %d\012\000" )
.LC27:
	ASCII(.ascii	"SM_CfgBuf Err! ret =%d\012\000" )
.LC28:
	ASCII(.ascii	"Line: %d, The length of seg packet is invalid: %d\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC29:
	ASCII(.ascii	"Line: %d, start code num from scd state reg: %d, re" )
	ASCII(.ascii	"lease raw packet anyway!\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"[%s %d] pCurrentStartCodeVirAddr is null!!\012\000" )
.LC31:
	ASCII(.ascii	"Line: %d, pNextStartCodeVirAddr is null!\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"ValidSegNum = %d, FilteredSegNum = 0, release raw p" )
	ASCII(.ascii	"acket anyway!\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"%s: pRawPacket = NULL!\012\000" )
.LC34:
	ASCII(.ascii	"%s: unkown standard type = %d!\012\000" )
.LC35:
	ASCII(.ascii	"%s: Length(%d)+FlagLen(%d) > BufLen(%d)\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"%s: FlagLen(%d) > RawPacketLength(%d)\012\000" )
	.space	1
.LC37:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act: %d, head" )
	ASCII(.ascii	"er_buf: %d)\012\000" )
.LC38:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act: %d, str_" )
	ASCII(.ascii	"buf: %d)\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act:%d, str_b" )
	ASCII(.ascii	"uf: %d, header_buf: %d)\012\000" )
.LC40:
	ASCII(.ascii	"Func: %s, buffer has no enough space, (act: %d, str" )
	ASCII(.ascii	"_buf: %d)\012\000" )
	.space	2
.LC41:
	ASCII(.ascii	"Func: %s, buffer has no enough space,(act:%d, str_b" )
	ASCII(.ascii	"uf:%d)\012\000" )
	.space	1
.LC42:
	ASCII(.ascii	"%s: RawPacket Length %d <= 0\012\000" )
	.space	2
.LC43:
	ASCII(.ascii	"Chan %d has been destroyed or the function pointer " )
	ASCII(.ascii	"-- ReleaseRawStreamData pStreamIntf is NULL!\000" )
.LC44:
	ASCII(.ascii	"line: %d s_SmIIS[%d].pSmInstArray is NULL\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"line: %d, pScdInstance is NULL!\012\000" )
	.space	3
.LC46:
	ASCII(.ascii	"%s %d force to clear SCDState = 0\012\000" )
	.space	1
.LC47:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum !!\012\000" )
	.space	3
.LC48:
	ASCII(.ascii	"Chan %d has been destroyed or the function pointer " )
	ASCII(.ascii	"-- ReadRawStreamData pStreamIntf is NULL!\000" )
	.space	3
.LC49:
	ASCII(.ascii	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"Chan %d FillEosRawStream failed!\012\000" )
	.space	2
.LC51:
	ASCII(.ascii	"Chan %d FillExtraData failed!\012\000" )
	.space	1
.LC52:
	ASCII(.ascii	"Release this packet failed!\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"raw_pts: %lld\012\000" )
	.space	1
.LC54:
	ASCII(.ascii	"Get RawPhyAddr=0x%x,Len=%d\012\000" )
.LC55:
	ASCII(.ascii	"!!!push raw err!!!\012\000" )
.LC56:
	ASCII(.ascii	"Chan%d raw full\012\000" )
	.space	3
.LC57:
	ASCII(.ascii	"RawNum %lld <= RawNumInVfmw %lld\012\000" )
	.space	2
.LC58:
	ASCII(.ascii	"No space for raw move, total:%d+%d > max:%d!\012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"scd buffer is full, reset scd!\012\000" )
.LC60:
	ASCII(.ascii	"(%d ms) not release stream seg, release anyway!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC61:
	ASCII(.ascii	"%s,%d, active scd Success!\012\000" )
.LC62:
	ASCII(.ascii	"Move raw data failed, force to reset scd.\012\000" )
	.space	1
.LC63:
	ASCII(.ascii	"SCD GetRawStreamNum Fail.\012\000" )
	.space	1
.LC64:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) SCDState = %d\012\000" )
	.space	2
.LC65:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return Idle!\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"Chan %d SCD[%d] Time Out(%d ms), Reset it!\012\000" )
.LC67:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) really busy!\012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"%s prepare to check SCD(%d)/(MAX_SCD_NUM = %d)\012\000" )
.LC69:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return BUSY!!\012\000" )
	.space	2
.LC70:
	ASCII(.ascii	"%s,%d,find idle SCD(ID = %d)\012\000" )
	.space	2
.LC71:
	ASCII(.ascii	"********** SmID [%d] RawState begin **********\012\000" )
.LC72:
	ASCII(.ascii	"RawHead=%d\012\000" )
.LC73:
	ASCII(.ascii	"RawTail=%d\012\000" )
.LC74:
	ASCII(.ascii	"RawHistory=%d\012\000" )
	.space	1
.LC75:
	ASCII(.ascii	"RawFirstPacketOffset=%d\012\000" )
	.space	3
.LC76:
	ASCII(.ascii	"CurShowIndex=%d\012\000" )
	.space	3
.LC77:
	ASCII(.ascii	"********** SmID [%d] RawState end   **********\012\000" )
.LC78:
	ASCII(.ascii	"RawPhyAddr=0x%x\012\000" )
	.space	3
.LC79:
	ASCII(.ascii	"RawVirAddr=0x%x\012\000" )
	.space	3
.LC80:
	ASCII(.ascii	"RawLength=%d\012\000" )
	.space	2
.LC81:
	ASCII(.ascii	"RawPts=%ld\012\000" )
.LC82:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum!!\012\000" )
.LC83:
	ASCII(.ascii	"********** SmID [%d] SegState begin **********\012\000" )
.LC84:
	ASCII(.ascii	"SegHead=%d\012\000" )
.LC85:
	ASCII(.ascii	"SegTail=%d\012\000" )
.LC86:
	ASCII(.ascii	"SegCurrent=%d\012\000" )
	.space	1
.LC87:
	ASCII(.ascii	"SegBufPhyAddr=%p\012\000" )
	.space	2
.LC88:
	ASCII(.ascii	"SegBufVirAddr=%p\012\000" )
	.space	2
.LC89:
	ASCII(.ascii	"SegBufSize=%d\012\000" )
	.space	1
.LC90:
	ASCII(.ascii	"SegBufReadAddr=%p\012\000" )
	.space	1
.LC91:
	ASCII(.ascii	"SegBufWriteAddr=%pd\012\000" )
	.space	3
.LC92:
	ASCII(.ascii	"********** SmID [%d] SegState end   **********\012\000" )
.LC93:
	ASCII(.ascii	"SegPhyAddr=0x%x\012\000" )
	.space	3
.LC94:
	ASCII(.ascii	"SegVirAddr=0x%x\012\000" )
	.space	3
.LC95:
	ASCII(.ascii	"SegLength=%d\012\000" )
	.space	2
.LC96:
	ASCII(.ascii	"SegStreamID=%d\012\000" )
.LC97:
	ASCII(.ascii	"SegState=%d\012\000" )
	.space	3
.LC98:
	ASCII(.ascii	"SegIsLastSeg=%d\012\000" )
	.space	3
.LC99:
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
	.type	last_rec_pos_time.53210, %object
	.size	last_rec_pos_time.53210, 128
last_rec_pos_time.53210:
	.space	128
	.type	LastRecPosTime.53418, %object
	.size	LastRecPosTime.53418, 128
LastRecPosTime.53418:
	.space	128
	.type	last_rec_pos_time.53443, %object
	.size	last_rec_pos_time.53443, 128
last_rec_pos_time.53443:
	.space	128
	.type	s_ScdRegResetOKPhyAddr, %object
	.size	s_ScdRegResetOKPhyAddr, 4
s_ScdRegResetOKPhyAddr:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
