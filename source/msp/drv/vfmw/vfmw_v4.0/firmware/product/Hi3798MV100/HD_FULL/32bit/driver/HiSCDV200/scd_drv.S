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
	ldr	r3, .L5
	cmp	r0, #0
	beq	.L4
	mov	r2, #5120
	ldr	r1, .L5+4
	ldr	r3, [r3, #52]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L4:
	mov	r2, #92
	ldr	r1, .L5+8
	mov	r0, #22
	ldr	r3, [r3, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L6:
	.align	2
.L5:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_CabacMN
	.word	.LC2
	UNWIND(.fnend)
	.size	WriteCabacTabDsp, .-WriteCabacTabDsp
	.align	2
	.global	WriteHexFile
	.type	WriteHexFile, %function
WriteHexFile:
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
	subs	r6, r1, #0
	mov	r4, r0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r5, .L21
	ldr	r0, [r5]
	bl	MEM_Phy2Vir
	ldr	r3, .L21+4
	cmp	r0, #0
	beq	.L18
	cmp	r4, #6
	beq	.L19
	cmp	r4, #0
	bne	.L13
	mov	r2, #17920
	ldr	r1, .L21+8
	ldr	r3, [r3, #52]
	blx	r3
.L12:
	ldr	r0, [r5, #4]
	mov	r1, #4480
	add	r0, r0, #264
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #4]
	ldr	r1, [r5]
	add	r0, r0, #268
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #4]
	mov	r1, #0
	add	r0, r0, #256
	bl	MEM_WritePhyWord
	ldr	r0, [r5, #4]
	mov	r1, #1
	add	r0, r0, #256
	bl	MEM_WritePhyWord
.L14:
	movw	r0, #49412
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ands	r0, r0, #1
	beq	.L14
	cmp	r4, #6
	beq	.L20
	cmp	r4, #0
	ldreq	r3, .L21+12
	streq	r0, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L13:
	mov	r0, r6
	ldr	r1, .L21+16
	ldr	r3, [r3, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L19:
	mov	r2, #17920
	ldr	r1, .L21+20
	ldr	r3, [r3, #52]
	blx	r3
	b	.L12
.L20:
	ldr	r3, .L21+12
	mov	r2, #2
	str	r2, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L18:
	ldr	r2, [r5]
	ldr	r1, .L21+24
	ldr	r3, [r3, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L22:
	.align	2
.L21:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+1552
	.word	g_DspDrvState
	.word	.LC4
	.word	.LANCHOR1
	.word	.LC3
	UNWIND(.fnend)
	.size	WriteHexFile, .-WriteHexFile
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
	ldr	r2, .L32
	mov	r3, #0
.L26:
	ldr	r1, [r2, #40]
	add	r2, r2, #48
	cmp	r1, #0
	add	ip, r1, #104
	beq	.L24
	cmp	r0, ip
	beq	.L27
.L24:
	add	r3, r3, #1
	cmp	r3, #16
	bne	.L26
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L27:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L33:
	.align	2
.L32:
	.word	.LANCHOR0+8
	UNWIND(.fnend)
	.size	GetInstIDByRawArray, .-GetInstIDByRawArray
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
	movw	r0, #51228
	ldr	r5, .L48
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	r2, [r5]
	ldr	r4, [r2, #120]
	tst	r4, #1
	mov	r6, r0
	beq	.L45
	orr	r4, r4, #32
	str	r4, [r2, #120]
	ldr	r3, [r2, #372]
	tst	r3, #2
	bne	.L40
	movw	r0, #9999
	b	.L38
.L47:
	subs	r0, r0, #1
	beq	.L46
.L38:
	ldr	r3, [r2, #372]
	tst	r3, #2
	beq	.L47
.L40:
	ldr	r3, .L48+4
	bfc	r4, #5, #1
	and	r1, r6, #1
	str	r4, [r2, #120]
	ldr	r0, [r3, #4]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L45:
	ldr	r3, .L48+8
	mov	r0, #26
	ldr	r1, .L48+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L46:
	ldr	r3, .L48+8
	ldr	r1, .L48+16
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r2, [r5]
	b	.L40
.L49:
	.align	2
.L48:
	.word	g_pstRegCrg
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	.word	.LC6
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L52
	ldr	r3, [r4, #856]
	cmp	r3, r0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	mov	r0, #0
	bl	ResetSCD
	mov	r3, #0
	str	r3, [r4, #860]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L53:
	.align	2
.L52:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_ResetSCD, .-SCDDRV_ResetSCD
	.align	2
	.global	SCDDRV_MaskInt
	.type	SCDDRV_MaskInt, %function
SCDDRV_MaskInt:
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
	ldr	r3, .L55
	mov	r1, #1
	ldr	r0, [r3, #4]
	add	r0, r0, #2064
	add	r0, r0, #12
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MEM_WritePhyWord
.L56:
	.align	2
.L55:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_MaskInt, .-SCDDRV_MaskInt
	.align	2
	.global	SCDDRV_EnableInt
	.type	SCDDRV_EnableInt, %function
SCDDRV_EnableInt:
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
	ldr	r3, .L58
	mov	r1, #0
	ldr	r0, [r3, #4]
	add	r0, r0, #2064
	add	r0, r0, #12
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MEM_WritePhyWord
.L59:
	.align	2
.L58:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_EnableInt, .-SCDDRV_EnableInt
	.align	2
	.global	InsertRawPacket
	.type	InsertRawPacket, %function
InsertRawPacket:
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
	cmp	r1, #0
	cmpne	r0, #0
	moveq	r5, #1
	movne	r5, #0
	beq	.L62
	add	r4, r0, #98304
	ldmib	r4, {ip, lr}
	add	r3, ip, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	cmp	r3, lr
	beq	.L63
	ldr	lr, .L64
	mov	r3, ip, asl #7
	sub	ip, r3, ip, asl #5
	mov	r2, #96
	add	r0, r0, ip
	ldr	r3, [lr, #52]
	blx	r3
	ldr	r3, [r4, #4]
	mov	r0, r5
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	str	r3, [r4, #4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L62:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L63:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L65:
	.align	2
.L64:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	InsertRawPacket, .-InsertRawPacket
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
	cmp	r0, #15
	bhi	.L69
	ldr	r3, .L71
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #4
	add	r0, r3, r0
	ldr	r3, [r0, #48]
	cmp	r3, #0
	beq	.L69
	add	r2, r3, #98304
	ldr	r3, [r2, #108]
	ldr	r1, [r2, #112]
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
.L69:
	mvn	r0, #3
	ldmfd	sp, {fp, sp, pc}
.L72:
	.align	2
.L71:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	GetRawState, .-GetRawState
	.align	2
	.global	ShowFirstRawPacket
	.type	ShowFirstRawPacket, %function
ShowFirstRawPacket:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	lr, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L75
	add	r2, r0, #98304
	ldr	r3, [r2]
	ldr	r0, [r2, #4]
	cmp	r3, r0
	beq	.L76
	ldr	r5, .L77
	mov	ip, r3, asl #7
	sub	ip, ip, r3, asl #5
	str	r3, [r2, #16]
	mov	r0, r1
	mov	r2, #96
	add	r1, lr, ip
	ldr	r3, [r5, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L75:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L76:
	mvn	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L78:
	.align	2
.L77:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ShowFirstRawPacket, .-ShowFirstRawPacket
	.align	2
	.global	ShowNextRawPacket
	.type	ShowNextRawPacket, %function
ShowNextRawPacket:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	lr, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L81
	add	ip, r0, #98304
	ldr	r2, [ip, #16]
	ldr	r0, [ip, #4]
	add	r2, r2, #1
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #22
	add	r2, r2, r3
	ubfx	r2, r2, #0, #10
	rsb	r3, r3, r2
	cmp	r0, r3
	beq	.L82
	ldr	r5, .L83
	mov	r2, r3, asl #7
	sub	r2, r2, r3, asl #5
	str	r3, [ip, #16]
	mov	r0, r1
	add	r1, lr, r2
	ldr	r3, [r5, #52]
	mov	r2, #96
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L81:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L82:
	mvn	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L84:
	.align	2
.L83:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ShowNextRawPacket, .-ShowNextRawPacket
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
	beq	.L89
	add	r3, r0, #98304
	ldmia	r3, {r2, ip}
	cmp	r2, ip
	beq	.L88
	mov	ip, r2, asl #7
	ldr	lr, [r3, #12]
	sub	r2, ip, r2, asl #5
	add	r0, r0, r2
	add	r1, r1, lr
	ldr	r2, [r0, #8]
	cmp	r1, r2
	bge	.L89
	str	r1, [r3, #12]
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L89:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L88:
	mvn	r0, #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SetFirstOffset, .-SetFirstOffset
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
	beq	.L92
	add	r3, r0, #98304
	ldr	ip, [r3]
	ldr	r0, [r3, #4]
	cmp	ip, r0
	beq	.L93
	ldr	r3, [r3, #12]
	mov	r0, r2
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L92:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L93:
	mvn	r0, #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetFirstOffset, .-GetFirstOffset
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r0
	mov	r8, r1
	moveq	r3, #1
	movne	r3, #0
	beq	.L110
	ldr	r2, .L123
.L99:
	ldr	r1, [r2, #40]
	add	r2, r2, #48
	cmp	r1, #0
	add	r0, r1, #104
	beq	.L96
	cmp	r6, r0
	beq	.L121
.L96:
	add	r3, r3, #1
	cmp	r3, #16
	bne	.L99
.L97:
	ldr	r3, .L123+4
	movw	r2, #711
	ldr	r1, .L123+8
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L117
.L121:
	cmp	r3, #0
	blt	.L97
	add	r2, r6, #98304
	str	r2, [fp, #-52]
	ldmia	r2, {r1, r2}
	cmp	r1, r2
	addgt	r2, r2, #1024
	rsb	r2, r1, r2
	cmp	r2, r8
	bcc	.L122
	cmp	r8, #0
	mov	r4, r1
	beq	.L103
	ldr	r10, .L123+4
	mov	r5, #0
	mov	r9, r3, asl #4
	mov	r3, r3, asl #6
	str	r3, [fp, #-48]
.L104:
	mov	r3, r4, asl #7
	ldr	r1, .L123+12
	sub	r3, r3, r4, asl #5
	mov	r0, #26
	add	r7, r6, r3
	ldr	ip, [r10, #68]
	ldr	r2, [r6, r3]
	add	r5, r5, #1
	ldr	r3, [r7, #8]
	add	r4, r4, #1
	blx	ip
	ldr	r3, [fp, #-48]
	ldr	r1, [r7, #8]
	cmp	r5, r8
	rsb	r2, r9, r3
	ldr	r3, .L123+16
	ubfx	r4, r4, #0, #10
	add	r2, r3, r2
	ldr	r2, [r2, #48]
	add	r2, r2, #98304
	ldr	r3, [r2, #124]
	rsb	r3, r1, r3
	bic	r3, r3, r3, asr #31
	str	r3, [r2, #124]
	bne	.L104
	ldr	r2, [fp, #-52]
	ldr	r3, [r2]
	add	r5, r5, r3
	str	r5, [r2]
	cmp	r5, #1024
	ldrge	r3, [fp, #-52]
	subge	r5, r5, #1024
	strge	r5, [r3]
.L109:
	ldr	r3, [fp, #-52]
	mov	r0, #0
	str	r0, [r3, #12]
.L117:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L103:
	ldr	r3, [fp, #-52]
	cmp	r1, #1024
	str	r1, [r3]
	ldrge	r3, [fp, #-52]
	subge	r1, r1, #1024
	strge	r1, [r3]
.L107:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L110:
	mvn	r0, #0
	b	.L117
.L122:
	ldr	ip, .L123+4
	mov	r3, r8
	ldr	r1, .L123+20
	mov	r0, #26
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L117
.L124:
	.align	2
.L123:
	.word	.LANCHOR0+8
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC7
	.word	.LC9
	.word	.LANCHOR0
	.word	.LC8
	UNWIND(.fnend)
	.size	DeleteRawPacket, .-DeleteRawPacket
	.align	2
	.global	GetRawNumOffsert
	.type	GetRawNumOffsert, %function
GetRawNumOffsert:
	UNWIND(.fnstart)
	@ args = 32, pretend = 0, frame = 16
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
	clz	ip, r0
	mov	r7, r1
	str	r2, [fp, #-52]
	mov	ip, ip, lsr #5
	str	r3, [fp, #-56]
	orrs	r1, ip, r7, lsr #31
	mov	r5, r0
	ldr	r6, [fp, #4]
	ldr	r8, [fp, #28]
	ldr	r9, [fp, #32]
	bne	.L135
	cmp	r3, #0
	cmpne	r2, #0
	moveq	r10, #1
	movne	r10, #0
	beq	.L135
	add	r3, r0, #98304
	cmp	ip, #0
	str	r3, [fp, #-48]
	ldr	lr, [r3]
	mov	ip, r3
	ldr	r0, [r3, #12]
	mov	r1, lr, asl #5
	mov	r2, lr, asl #7
	rsb	r3, r1, r2
	add	r3, r5, r3
	ldr	r4, [r3, #8]
	rsb	r4, r0, r4
	bne	.L127
	ldr	r3, [ip, #4]
	subs	r3, r3, lr
	addmi	r3, r3, #1024
.L133:
	rsb	r1, r1, r2
	add	lr, r3, lr
	add	r1, r5, r1
	ldr	r0, [fp, #8]
	ldrd	r2, [r1, #16]
	strd	r2, [r6]
	ldrd	r2, [r1, #32]
	strd	r2, [r0]
	ldrd	r2, [r1, #16]
	ldr	r0, [fp, #12]
	strd	r2, [r9]
	ldrd	r2, [r1, #40]
	strd	r2, [r0]
	ldr	r2, [fp, #16]
	ldr	r3, [r1, #56]
	str	r3, [r2]
	ldr	r2, [fp, #20]
	ldr	r3, [r1, #60]
	str	r3, [r2]
	ldr	r2, [fp, #24]
	ldr	r3, [r1, #64]
	str	r3, [r2]
	ldr	r3, [r1, #68]
	str	r3, [r8]
	ldr	r3, [fp, #-48]
	ldr	ip, [r3]
	cmp	r7, r4
	cmpge	lr, ip
	strgt	r8, [fp, #28]
	strgt	r9, [fp, #32]
	ldrgt	r2, [fp, #24]
	bgt	.L131
	b	.L132
.L130:
	strd	r0, [r6]
	cmp	r7, r4
	cmpge	lr, ip
	ldrd	r0, [r10, #32]
	ldr	r3, [fp, #8]
	strd	r0, [r3]
	ldr	r3, [fp, #32]
	ldrd	r0, [r10, #16]
	strd	r0, [r3]
	ldr	r3, [fp, #12]
	ldrd	r0, [r10, #40]
	strd	r0, [r3]
	ldr	r1, [fp, #16]
	ldr	r3, [r10, #56]
	str	r3, [r1]
	ldr	r1, [fp, #20]
	ldr	r3, [r10, #60]
	str	r3, [r1]
	ldr	r3, [r10, #64]
	ldr	r1, [fp, #28]
	str	r3, [r2]
	ldr	r3, [r10, #68]
	str	r3, [r1]
	ble	.L139
.L131:
	add	ip, ip, #1
	mvn	r9, #0
	mvn	r8, #0
	mov	r3, ip, asr #31
	mov	r1, r3, lsr #22
	add	r3, ip, r1
	ubfx	r3, r3, #0, #10
	rsb	r3, r1, r3
	mov	r1, r3, asl #5
	mov	r3, r3, asl #7
	rsb	r10, r1, r3
	add	r10, r5, r10
	ldrd	r0, [r10, #16]
	ldr	r3, [r10, #8]
	cmp	r1, r9
	cmpeq	r0, r8
	add	r4, r4, r3
	ldreqd	r0, [r6]
	b	.L130
.L139:
	ldr	r3, [fp, #-48]
	ldr	r2, [r3]
	cmp	r2, ip
	beq	.L132
	ldr	r3, [r10, #8]
	rsb	ip, r2, ip
	ldr	r2, [fp, #-52]
	mov	r0, #0
	rsb	r4, r3, r4
	ldr	r3, [fp, #-56]
	rsb	r7, r4, r7
	str	ip, [r2]
	str	r7, [r3]
.L138:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L132:
	ldr	r3, [fp, #-52]
	mov	r0, #0
	str	r0, [r3]
	ldr	r3, [fp, #-56]
	str	r7, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L127:
	ldr	ip, .L140
	movw	r3, #847
	ldr	r2, .L140+4
	mov	r0, #22
	ldr	r1, .L140+8
	ldr	ip, [ip, #68]
	blx	ip
	ldr	r3, [fp, #-48]
	ldr	lr, [r3]
	mov	r3, r10
	mov	r1, lr, asl #5
	mov	r2, lr, asl #7
	b	.L133
.L135:
	mvn	r0, #0
	b	.L138
.L141:
	.align	2
.L140:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3
	.word	.LC10
	UNWIND(.fnend)
	.size	GetRawNumOffsert, .-GetRawNumOffsert
	.align	2
	.global	DeleteRawLen
	.type	DeleteRawLen, %function
DeleteRawLen:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
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
	clz	r3, r0
	mov	r6, r0
	mov	r3, r3, lsr #5
	orrs	ip, r3, r1, lsr #31
	bne	.L150
	cmp	r3, #0
	str	ip, [fp, #-100]
	str	ip, [fp, #-96]
	bne	.L150
	add	r4, r0, #98304
	ldr	r3, [r4, #20]
	ldr	ip, [r4, #12]
	rsb	r3, ip, r3
	movs	r7, r3, asr #31
	bne	.L152
	cmp	r1, r3
	bgt	.L150
	sub	r3, fp, #52
	sub	r2, fp, #80
	str	r3, [sp, #28]
	sub	r3, fp, #84
	str	r2, [sp, #24]
	sub	r2, fp, #88
	str	r3, [sp, #20]
	sub	r3, fp, #92
	str	r2, [sp, #16]
	sub	r2, fp, #60
	str	r3, [sp, #12]
	sub	r3, fp, #68
	str	r2, [sp, #8]
	sub	r2, fp, #76
	str	r3, [sp, #4]
	sub	r3, fp, #96
	str	r2, [sp]
	sub	r2, fp, #100
	bl	GetRawNumOffsert
	ldr	r5, [r4]
	ldr	ip, [fp, #-100]
	movw	r2, #963
	ldr	lr, [fp, #-96]
	mov	r0, #26
	add	r5, ip, r5
	ldr	r8, .L156
	mov	r3, ip
	mov	r1, r5, asr #31
	ldr	r9, [r8, #68]
	mov	r10, r1, lsr #22
	add	r5, r5, r10
	ubfx	r5, r5, #0, #10
	rsb	r1, r10, r5
	mov	r5, r1, asl #7
	sub	r1, r5, r1, asl #5
	add	r5, r6, r1
	ldrb	r1, [r5, #54]	@ zero_extendqisi2
	str	r1, [sp, #12]
	ldr	r1, [r5, #8]
	str	ip, [sp, #4]
	str	lr, [sp]
	str	r1, [sp, #8]
	ldr	r1, .L156+4
	blx	r9
	ldrb	r3, [r5, #54]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L146
	ldr	r1, [fp, #-100]
.L147:
	mov	r0, r6
	bl	DeleteRawPacket
	ldmia	r4, {r2, r3}
	ldr	r1, [fp, #-96]
	cmp	r2, r3
	beq	.L155
	mov	r3, r2, asl #7
	ldr	r0, [r4, #12]
	sub	r3, r3, r2, asl #5
	add	r6, r6, r3
	add	r1, r1, r0
	ldr	r3, [r6, #8]
	cmp	r1, r3
	strlt	r1, [r4, #12]
	bge	.L150
.L152:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L150:
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L146:
	ldr	ip, [r5, #8]
	mov	r2, #968
	ldr	r1, [fp, #-96]
	mov	r0, #26
	ldr	r3, [fp, #-100]
	str	ip, [sp, #4]
	str	r1, [sp]
	ldr	r5, [r8, #68]
	ldr	r1, .L156+8
	blx	r5
	ldr	r1, [fp, #-100]
	str	r7, [fp, #-96]
	add	r1, r1, #1
	str	r1, [fp, #-100]
	b	.L147
.L155:
	mvn	r7, #2
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L157:
	.align	2
.L156:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	.word	.LC12
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
	cmp	r0, #15
	ldmhifd	sp, {r4, r5, fp, sp, pc}
	mov	r2, r0, asl #6
	ldr	r3, .L162
	sub	r0, r2, r0, asl #4
	add	r0, r3, r0
	ldr	r0, [r0, #48]
	cmp	r0, #0
	beq	.L161
	add	r4, r0, #188416
	ldr	r1, [r4, #2232]
	cmp	r1, #0
	ldmlefd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #104
	bl	DeleteRawPacket
	mov	r3, #0
	str	r3, [r4, #2232]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L161:
	ldr	r3, .L162+4
	mov	r2, #1008
	ldr	r1, .L162+8
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L163:
	.align	2
.L162:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
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
	cmp	r0, #0
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
	cmp	r0, #0
	beq	.L170
	add	r0, r0, #98304
	ldmia	r0, {r2, r3}
	subs	r3, r3, r2
	strpl	r3, [r1]
	addmi	r3, r3, #1024
	strmi	r3, [r1]
	movpl	r0, #0
	movmi	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L170:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r2
	mov	r6, r3
	mov	r5, r1
	mov	r8, r0
	beq	.L174
	cmp	r3, #262144
	movcs	r4, #0
	movcc	r4, #1
	cmp	r2, #0
	orreq	r4, r4, #1
	cmp	r4, #0
	bne	.L174
	ldr	r3, .L175
	movw	r2, #26680
	movt	r2, 1
	mov	r1, r4
	ldr	r3, [r3, #48]
	blx	r3
	add	r2, r8, #90112
	mov	r0, r4
	str	r5, [r2, #2072]
	str	r7, [r8]
	str	r5, [r2, #2080]
	str	r5, [r2, #2084]
	str	r6, [r2, #2076]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L174:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L176:
	.align	2
.L175:
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
	ldr	r3, .L182
	mov	r2, #92160
	mov	r1, #0
	add	r0, r4, #8
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r4, #90112
	mov	r3, #0
	ldr	r2, [r0, #2072]
	str	r3, [r0, #2056]
	str	r3, [r0, #2060]
	str	r2, [r0, #2080]
	str	r2, [r0, #2084]
	str	r3, [r0, #2064]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L183:
	.align	2
.L182:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ResetStreamSegArray, .-ResetStreamSegArray
	.align	2
	.global	GetSegBuf
	.type	GetSegBuf, %function
GetSegBuf:
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
	addeq	r0, r0, #90112
	ldreq	r3, [r0, #2072]
	streq	r3, [r1]
	ldreq	r3, [r0, #2076]
	streq	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetSegBuf, .-GetSegBuf
	.align	2
	.global	GetFreeSegBuf
	.type	GetFreeSegBuf, %function
GetFreeSegBuf:
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
	ldmnefd	sp, {fp, sp, pc}
	add	r0, r0, #90112
	ldr	ip, [r0, #2084]
	str	ip, [r1]
	str	r3, [r2]
	ldr	r3, [r0, #2084]
	ldr	r1, [r0, #2080]
	cmp	r3, r1
	bhi	.L193
	ldrcs	r0, [r0, #2076]
	subcc	r1, r1, #1
	ldrcc	r0, [r0, #2076]
	rsbcc	r3, r3, r1
	subcs	r3, r0, #1
.L190:
	cmp	r3, r0
	strle	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
.L193:
	ldr	r0, [r0, #2076]
	sub	r1, r1, #1
	add	r1, r1, r0
	rsb	r3, r3, r1
	b	.L190
	UNWIND(.fnend)
	.size	GetFreeSegBuf, .-GetFreeSegBuf
	.align	2
	.global	CheckStream
	.type	CheckStream, %function
CheckStream:
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
	ldr	r3, .L239
	mov	r6, r1
	ldr	r5, [r3, r1, asl #2]
	ldr	r3, [r5, #528]
	sub	r1, r3, #3
	clz	r1, r1
	mov	r1, r1, lsr #5
	cmp	r3, #0
	movne	r3, r1
	orreq	r3, r1, #1
	cmp	r3, #0
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	add	r4, r5, #229376
	ldr	r2, [r4, #88]
	cmp	r2, #199
	ldmgtib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldrb	ip, [r0]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L235
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L235
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L201
.L235:
	ldr	lr, [r4, #100]
	mov	ip, #0
	ldr	r7, [r4, #96]
	mov	r0, ip
	mov	r8, ip
	mov	r9, ip
	add	r2, r2, #1
	str	ip, [r4, #100]
	str	r2, [r4, #88]
	str	lr, [r4, #96]
	str	r7, [r4, #92]
.L202:
	cmp	r3, #0
	beq	.L236
.L203:
	ldr	r3, [r4, #84]
	add	r3, r3, #1
	str	r3, [r4, #84]
.L204:
	cmp	r0, #0
	beq	.L205
	rsb	r3, lr, r8
	cmp	r3, #1
	beq	.L237
.L206:
	cmp	lr, r8
	cmpeq	r7, lr
	bne	.L205
.L207:
	cmp	r8, #1
	cmpne	r8, #20
	beq	.L205
	ldr	r3, [r4, #80]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r4, #80]
	ldr	r3, [r4, #84]
	add	r3, r3, #1
	str	r3, [r4, #84]
.L205:
	cmp	r2, #199
	ldmleib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r0, [r4, #80]
	ldr	r3, [r4, #84]
	rsb	r2, r3, r0
	cmp	r2, #49
	movle	r1, #0
	andgt	r1, r1, #1
	cmp	r1, #0
	bne	.L238
.L209:
	rsb	r3, r0, r3
	cmp	r3, #49
	ldmleib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, [r5, #528]
	cmp	r3, #0
	ldmneib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r2, .L239+4
	ldr	ip, [r2]
	cmp	ip, #0
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	mov	r0, r6
	mov	r2, r3
	mov	r1, #121
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L236:
	add	r9, r9, #73
	uxtb	r9, r9
	cmp	r9, #3
	bhi	.L204
	b	.L203
.L238:
	ldr	r2, .L239+4
	ldr	r7, [r2]
	cmp	r7, #0
	beq	.L209
	mov	r3, #0
	mov	r1, #121
	mov	r2, r3
	mov	r0, r6
	blx	r7
	ldr	r3, [r4, #84]
	ldr	r0, [r4, #80]
	b	.L209
.L237:
	rsb	r3, r7, lr
	cmp	r3, #1
	bne	.L206
	b	.L207
.L201:
	ldrb	r9, [r0, #3]	@ zero_extendqisi2
	add	r2, r2, #1
	ldr	lr, [r4, #100]
	and	r8, r9, #31
	sub	r0, r9, #1
	sub	ip, r8, #30
	add	r7, r9, #79
	cmp	r8, #19
	cmpne	ip, #1
	uxtb	r3, r0
	sub	r10, r8, #1
	str	r2, [r4, #88]
	movls	ip, #1
	movhi	ip, #0
	cmp	r10, #12
	orrls	ip, ip, #1
	cmp	r3, #183
	uxtb	r3, r7
	ldr	r7, [r4, #96]
	movls	r0, #0
	movhi	r0, #1
	cmp	r3, #4
	movhi	r3, r0
	orrls	r3, r0, #1
	cmp	r8, #0
	cmpne	r2, #2
	str	r8, [r4, #100]
	movgt	r0, #1
	movle	r0, #0
	cmp	ip, #0
	str	lr, [r4, #96]
	str	r7, [r4, #92]
	ldrne	ip, [r4, #80]
	addne	ip, ip, #1
	strne	ip, [r4, #80]
	b	.L202
.L240:
	.align	2
.L239:
	.word	s_pstVfmwChan
	.word	g_event_report
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
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r7, r1
	moveq	r8, #1
	movne	r8, #0
	beq	.L243
	add	r4, r0, #90112
	movw	r6, #36409
	movt	r6, 14563
	ldr	r3, [r4, #2060]
	ldr	ip, [r4, #2056]
	add	r3, r3, #1
	smull	r0, r1, r3, r6
	mov	r0, r3, asr #31
	rsb	r1, r0, r1, asr #8
	mov	r0, r1, asl #10
	add	r1, r0, r1, lsl #7
	rsb	r3, r1, r3
	cmp	r3, ip
	beq	.L244
	mov	r1, r2
	ldr	r0, [r7]
	bl	CheckStream
	ldr	r3, [r4, #2060]
	ldr	r0, .L245
	mov	r1, r7
	mov	r2, #80
	mov	r9, r3, asl #6
	add	r9, r9, r3, lsl #4
	ldr	r3, [r0, #52]
	add	r0, r9, #8
	add	r0, r5, r0
	blx	r3
	ldr	ip, [r4, #2060]
	mov	lr, #1
	add	r3, r5, r9
	add	r2, ip, lr
	mov	r0, r8
	mov	r10, ip, asl #6
	smull	r8, r9, r2, r6
	mov	r1, r2, asr #31
	add	r6, r10, ip, lsl #4
	add	r5, r5, r6
	strb	lr, [r5, #12]
	rsb	r1, r1, r9, asr #8
	str	ip, [r3, #24]
	ldr	lr, [r4, #2088]
	mov	ip, r1, asl #10
	ldr	r3, [r4, #2092]
	add	r1, ip, r1, lsl #7
	ldr	ip, [r4, #2096]
	rsb	r2, r1, r2
	str	r2, [r4, #2060]
	add	r2, ip, #1
	ldr	r1, [r7, #12]
	ldr	ip, [r7, #8]
	add	r1, r1, ip
	str	r1, [r4, #2084]
	ldr	r1, [r7, #12]
	add	r1, lr, r1
	str	r1, [r4, #2088]
	ldr	r1, [r7, #12]
	str	r2, [r4, #2096]
	add	r3, r3, r1
	str	r3, [r4, #2092]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L244:
	mvn	r0, #3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L243:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L246:
	.align	2
.L245:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	InsertStreamSeg, .-InsertStreamSeg
	.align	2
	.global	GetStreamSeg
	.type	GetStreamSeg, %function
GetStreamSeg:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r0, r1
	beq	.L254
	add	r4, r5, #90112
	ldr	r3, [r4, #2056]
	ldr	ip, [r4, #2060]
	cmp	ip, r3
	beq	.L256
	mov	r1, r3, asl #4
	mov	r6, r3, asl #6
	add	r2, r1, r6
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	movwne	lr, #36409
	movtne	lr, 14563
	bne	.L251
	b	.L249
.L262:
	add	r2, r5, r2
	ldrsb	r2, [r2, #12]
	cmp	r2, #1
	beq	.L249
.L251:
	add	r1, r3, #1
	smull	r2, r3, r1, lr
	mov	r2, r1, asr #31
	rsb	r3, r2, r3, asr #8
	mov	r2, r3, asl #10
	add	r3, r2, r3, lsl #7
	rsb	r3, r3, r1
	cmp	ip, r3
	mov	r1, r3, asl #4
	mov	r6, r3, asl #6
	add	r2, r1, r6
	bne	.L262
.L256:
	mvn	r0, #2
.L248:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L249:
	add	r6, r1, r6
	add	r1, r6, #8
	adds	r1, r5, r1
	beq	.L256
	ldr	r7, .L263
	add	r5, r5, r6
	mov	r2, #80
	ldr	r3, [r7, #52]
	blx	r3
	mov	r3, #2
	strb	r3, [r5, #12]
	mov	r0, #26
	ldr	r3, [r5, #20]
	ldr	ip, [r4, #2092]
	ldr	r2, [r4, #2096]
	rsb	ip, r3, ip
	ldr	r1, .L263+4
	sub	r2, r2, #1
	ldr	r6, [r7, #68]
	bic	ip, ip, ip, asr #31
	str	ip, [r4, #2092]
	bic	r2, r2, r2, asr #31
	str	r2, [r4, #2096]
	ldrb	ip, [r5, #13]	@ zero_extendqisi2
	ldr	r2, [r5, #16]
	str	ip, [sp]
	blx	r6
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L254:
	mvn	r0, #0
	b	.L248
.L264:
	.align	2
.L263:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	UNWIND(.fnend)
	.size	GetStreamSeg, .-GetStreamSeg
	.align	2
	.global	ReleaseStreamSeg
	.type	ReleaseStreamSeg, %function
ReleaseStreamSeg:
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
	subs	r6, r0, #0
	mov	r4, r1
	beq	.L285
	movw	r3, #64382
	sub	r2, r1, #1152
	movt	r3, 65535
	cmp	r2, r3
	bls	.L285
	cmn	r1, #1
	add	r5, r6, #90112
	beq	.L299
	ldr	r3, [r5, #2056]
	ldr	ip, [r5, #2060]
	cmp	r3, ip
	beq	.L273
	cmp	r1, r3
	movwne	lr, #36409
	movtne	lr, 14563
	bne	.L276
	b	.L274
.L297:
	cmp	r4, r3
	beq	.L274
.L276:
	add	r2, r3, #1
	umull	r0, r1, r2, lr
	mov	r3, r1, lsr #8
	mov	r1, r3, asl #10
	add	r3, r1, r3, lsl #7
	rsb	r3, r3, r2
	cmp	r3, ip
	bne	.L297
.L273:
	mvn	r0, #2
.L295:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L274:
	mov	r2, r3, asl #6
	add	r3, r2, r3, lsl #4
	add	r2, r6, r3
	ldrsb	r2, [r2, #12]
	cmp	r2, #2
	addeq	r3, r3, #8
	addeq	r7, r6, r3
	bne	.L273
.L270:
	cmp	r7, #0
	beq	.L273
	ldr	r3, [r7, #12]
	mov	r2, #0
	ldr	r8, .L302
	mov	r0, #26
	strb	r2, [r7, #4]
	ldr	r2, [r7, #8]
	str	r4, [sp, #4]
	ldrb	ip, [r7, #5]	@ zero_extendqisi2
	ldr	r9, [r8, #68]
	ldr	r1, .L302+4
	str	ip, [sp]
	blx	r9
	ldr	r3, [r5, #2056]
	cmp	r3, r4
	beq	.L300
.L278:
	ldr	r2, [r7, #12]
	mov	r0, #0
	ldr	r3, [r5, #2088]
	rsb	r3, r2, r3
	bic	r3, r3, r3, asr #31
	str	r3, [r5, #2088]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L299:
	ldr	r4, [r5, #2056]
	ldr	r3, [r5, #2060]
	cmp	r4, r3
	beq	.L273
	ldr	r8, .L302
	mov	r10, r4, asl #6
	add	r10, r10, r4, lsl #4
	mov	r2, r4
	add	r7, r10, #8
	add	r10, r6, r10
	ldr	r3, [r8, #68]
	mov	r0, #0
	ldr	r1, .L302+8
	add	r7, r6, r7
	blx	r3
	ldr	r3, [r10, #20]
	cmp	r3, #0
	movne	r9, #0
	beq	.L272
.L271:
	ldr	r2, [r10, #8]
	mov	r0, #0
	ldr	r3, [r8, #68]
	ldr	r1, .L302+12
	ldrb	r2, [r2, r9]	@ zero_extendqisi2
	add	r9, r9, #1
	blx	r3
	ldr	r3, [r10, #20]
	cmp	r3, r9
	movhi	r3, #1
	movls	r3, #0
	cmp	r9, #15
	movhi	r3, #0
	cmp	r3, #0
	bne	.L271
.L272:
	ldr	r3, [r8, #68]
	mov	r0, #0
	ldr	r1, .L302+16
	blx	r3
	b	.L270
.L300:
	movw	r9, #36409
	movt	r9, 14563
	b	.L281
.L279:
	ldr	r2, [r5, #2060]
	cmp	r2, r4
	beq	.L282
	ldrsb	r2, [r3, #12]
	cmp	r2, #0
	bne	.L301
.L286:
	add	r2, r4, #1
	umull	r0, r1, r2, r9
	mov	r4, r1, lsr #8
	mov	r3, r4, asl #10
	add	r4, r3, r4, lsl #7
	rsb	r4, r4, r2
.L281:
	mov	r3, r4, asl #6
	cmp	r4, #1152
	add	r3, r3, r4, lsl #4
	add	r3, r6, r3
	bcc	.L279
	ldr	r2, .L302+20
	mov	r0, #1
	ldr	r3, [r8, #68]
	ldr	r1, .L302+24
	blx	r3
	ldr	r2, [r5, #2060]
	cmp	r2, r4
	bne	.L286
.L282:
	ldr	r3, [r5, #2084]
	str	r2, [r5, #2056]
	str	r3, [r5, #2080]
	b	.L278
.L301:
	str	r4, [r5, #2056]
	ldr	r3, [r3, #16]
	str	r3, [r5, #2080]
	b	.L278
.L285:
	mvn	r0, #0
	b	.L295
.L303:
	.align	2
.L302:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC18
	.word	.LC15
	.word	.LC17
	.word	.LC16
	.word	.LANCHOR3+20
	.word	.LC19
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
	cmp	r0, #0
	addne	r3, r0, #90112
	movne	r0, #0
	mvneq	r0, #0
	ldrne	r3, [r3, #2088]
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
	beq	.L310
	add	r0, r0, #90112
	ldr	r3, [r0, #2060]
	ldr	r2, [r0, #2056]
	subs	r3, r3, r2
	strpl	r3, [r1]
	addmi	r3, r3, #1152
	strmi	r3, [r1]
	movpl	r0, #0
	movmi	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L310:
	mvn	r0, #0
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
	cmp	r0, #0
	addne	r0, r0, #90112
	ldrne	r3, [r0, #2096]
	strne	r3, [r1]
	ldrne	r3, [r0, #2092]
	strne	r3, [r2]
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
	ldr	r3, .L320
	add	ip, r3, r0, lsl #2
	ldr	r2, [ip, #872]
	cmp	r2, #0
	bne	.L319
	mov	r1, r0, asl #7
	sub	r0, r1, r0, asl #5
	add	r3, r3, r0
	ldr	r0, [r3, #860]
	cmp	r0, #0
	moveq	r3, #2
	movne	r3, #1
	movne	r0, r2
	str	r3, [ip, #872]
	ldmfd	sp, {fp, sp, pc}
.L319:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L321:
	.align	2
.L320:
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
	ldr	r3, .L323
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #872]
	ldmfd	sp, {fp, sp, pc}
.L324:
	.align	2
.L323:
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
	ldr	r3, .L330
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #872]
	cmp	r3, #2
	movne	r3, #2
	strne	r3, [r0, #872]
	ldmfd	sp, {fp, sp, pc}
.L331:
	.align	2
.L330:
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L335
	mov	r4, r0
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L333
	blx	r3
.L334:
	ldr	r0, .L335+4
	mov	r3, #0
	add	r0, r0, r4, lsl #2
	str	r3, [r0, #872]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L333:
	ldr	ip, .L335+8
	mov	r0, r3
	movw	r2, #1603
	ldr	r1, .L335+12
	ldr	r3, [ip, #68]
	blx	r3
	b	.L334
.L336:
	.align	2
.L335:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
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
	cmp	r0, #15
	bhi	.L339
	mov	r4, r0, asl #6
	ldr	r3, .L340
	ldr	ip, .L340+4
	sub	r0, r4, r0, asl #4
	add	r4, r3, r0
	mov	r2, #204800
	mov	r1, #0
	mvn	r5, #0
	ldr	r3, [ip, #48]
	ldr	r0, [r4, #48]
	blx	r3
	ldr	r3, [r4, #48]
	mov	r0, #0
	mvn	r4, #0
	add	r3, r3, #203776
	add	r3, r3, #848
	strd	r4, [r3, #-8]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L339:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L341:
	.align	2
.L340:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_ClearInst, .-SM_ClearInst
	.align	2
	.global	SM_AllocDSPCtxMem
	.type	SM_AllocDSPCtxMem, %function
SM_AllocDSPCtxMem:
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
	UNWIND(.pad #24)
	sub	sp, sp, #24
	cmp	r0, #15
	mov	r4, r0
	bhi	.L348
	ldr	r6, .L352
	mov	r1, #0
	mov	r2, #16
	sub	r0, fp, #52
	mov	r5, r1
	ldr	r3, [r6, #48]
	blx	r3
	mov	r0, #8
	bl	VFMW_GetString
	sub	r3, fp, #52
	str	r5, [sp]
	mov	r1, r5
	movw	r2, #9248
	bl	MEM_AllocMemBlock
	subs	r7, r0, #0
	bne	.L344
	ldr	r5, .L352+4
	ldr	r2, [fp, #-40]
	ldr	r1, [fp, #-48]
	ldr	r0, [fp, #-44]
	bl	MEM_AddMemRecord
	mov	r3, r4, asl #6
	sub	r3, r3, r4, asl #4
	add	r0, r5, #8
	sub	r1, fp, #52
	add	r0, r0, r3
	ldr	r8, [r6, #52]
	mov	r2, #16
	add	r4, r5, r3
	blx	r8
	ldr	r8, [fp, #-44]
	add	r0, r8, #3
	bic	r0, r0, #3
	str	r0, [r4, #24]
	rsb	r5, r8, r0
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r4, #28]
	beq	.L351
	mov	r2, #1024
	mov	r1, r7
	str	r2, [r4, #32]
	add	r4, r4, #40
	ldr	r3, [r6, #48]
	blx	r3
	add	r0, r5, #1024
	add	r0, r0, r8
	str	r0, [r4, #-4]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r4]
	mov	r3, r0
	movne	r2, #8192
	ldreq	r3, [r6, #68]
	ldreq	r2, .L352+8
	movne	r1, r7
	ldreq	r1, .L352+12
	mvneq	r7, #6
	ldrne	r3, [r6, #48]
	strne	r2, [r4, #4]
	blx	r3
.L343:
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L348:
	mvn	r7, #0
	b	.L343
.L344:
	ldr	r3, [r6, #68]
	mov	r0, r5
	ldr	r2, .L352+8
	mvn	r7, #6
	ldr	r1, .L352+16
	blx	r3
	b	.L343
.L351:
	ldr	r3, [r6, #68]
	mvn	r7, #6
	ldr	r2, .L352+8
	ldr	r1, .L352+20
	blx	r3
	b	.L343
.L353:
	.align	2
.L352:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LANCHOR3+40
	.word	.LC23
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	SM_AllocDSPCtxMem, .-SM_AllocDSPCtxMem
	.align	2
	.global	SM_DeletDSPCtxMem
	.type	SM_DeletDSPCtxMem, %function
SM_DeletDSPCtxMem:
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
	ldr	r0, [r4, #8]
	cmp	r0, #0
	bne	.L358
	ldr	r3, .L359
	ldr	r1, .L359+4
	ldr	r3, [r3, #68]
	blx	r3
.L357:
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MEM_DelMemRecord
.L358:
	ldr	r1, [r4, #4]
	bl	MEM_ReleaseMemBlock
	b	.L357
.L360:
	.align	2
.L359:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	UNWIND(.fnend)
	.size	SM_DeletDSPCtxMem, .-SM_DeletDSPCtxMem
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
	ldr	r4, .L364
	ldr	r6, .L364+4
	add	r5, r4, #768
.L362:
	mov	r2, #48
	mov	r0, r4
	ldr	r3, [r6, #48]
	add	r4, r4, r2
	mov	r1, #0
	blx	r3
	cmp	r4, r5
	bne	.L362
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L365:
	.align	2
.L364:
	.word	.LANCHOR0+8
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_InstInit, .-SM_InstInit
	.align	2
	.global	SM_OpenSCDDrv
	.type	SM_OpenSCDDrv, %function
SM_OpenSCDDrv:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r4, .L395
	cmp	r2, #1
	mov	r3, #49152
	movt	r3, 63683
	mov	r6, r2
	mov	r5, r0
	str	r1, [fp, #-48]
	str	r3, [r4, #4]
	str	r3, [r4, #876]
	bhi	.L388
	cmp	r2, #0
	bgt	.L389
	ldr	r3, .L395+4
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L371
	mov	r0, r2
	blx	r3
.L372:
	mov	r10, r6, asl #7
	ldr	r8, .L395
	sub	r7, r10, r6, asl #5
	add	r4, r4, r7
	add	r3, r4, #848
	str	r3, [fp, #-60]
	ldr	r3, [r4, #852]
	cmp	r3, #1
	beq	.L387
	ldr	r9, .L395+8
	add	r10, r8, #776
	add	r10, r10, r7
	mov	r0, r6
	bl	ResetSCD
	mov	r1, #0
	mov	r2, #96
	ldr	r3, [r9, #48]
	mov	r0, r10
	mov	r7, r1
	blx	r3
	ldr	r2, .L395+12
	mov	r1, #84
	add	r3, r8, r6, lsl #2
	cmp	r10, r7
	mla	r6, r1, r6, r2
	str	r7, [r3, #872]
	str	r7, [r6, #76]
	beq	.L390
	ldr	r3, [fp, #-48]
	add	r0, r5, #15
	bic	r0, r0, #15
	str	r5, [r4, #776]
	str	r0, [r4, #784]
	rsb	r6, r5, r0
	str	r3, [r4, #780]
	add	r3, r4, #784
	str	r3, [fp, #-52]
	bl	MEM_Phy2Vir
	mov	r2, #12288
	add	r3, r5, #12288
	str	r2, [r4, #792]
	add	r2, r4, #808
	str	r2, [fp, #-56]
	add	r3, r3, r6
	ldr	r2, [fp, #-52]
	add	r10, r6, #21504
	str	r3, [r4, #796]
	str	r0, [r2, #4]
	mov	r0, r3
	bl	MEM_Phy2Vir
	add	r3, r10, r5
	mov	r1, #9216
	str	r3, [r4, #808]
	str	r1, [r4, #804]
	str	r0, [r4, #800]
	mov	r0, r3
	bl	MEM_Phy2Vir
	ldr	r2, [fp, #-56]
	cmp	r0, #0
	str	r0, [r2, #4]
	beq	.L391
	ldr	r3, [r9, #48]
	mov	r2, #512
	mov	r1, r7
	blx	r3
	add	r0, r6, #22016
	mov	r3, #512
	add	r0, r0, r5
	str	r3, [r4, #816]
	str	r0, [r4, #820]
	bl	MEM_Phy2Vir
	add	r3, r4, #824
	cmp	r0, #0
	str	r0, [r4, #824]
	beq	.L392
	mov	r6, #278528
	mov	r1, r7
	str	r6, [r3, #4]
	mov	r2, r6
	add	r3, r4, #832
	str	r3, [fp, #-56]
	ldr	r3, [r9, #48]
	blx	r3
	add	r0, r10, r6
	add	r0, r0, #512
	add	r0, r0, r5
	str	r0, [r4, #832]
	bl	MEM_Phy2Vir
	ldr	r3, [fp, #-56]
	cmp	r0, #0
	str	r0, [r3, #4]
	beq	.L393
	mov	r2, r6
	ldr	r3, [r9, #48]
	mov	r1, r7
	add	r10, r10, #557056
	blx	r3
	ldr	r0, [r4, #832]
	str	r6, [r4, #840]
	add	r6, r4, #840
	bl	WriteCabacTabDsp
	add	r0, r5, r10
	add	r0, r0, #636
	add	r0, r0, #3
	bic	r0, r0, #127
	str	r0, [r8]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r8, #880]
	beq	.L394
	ldr	r2, [fp, #-48]
	add	r10, r10, #18432
	ldr	r3, [r8, #4]
	cmp	r2, r10
	str	r7, [r4, #848]
	mov	r2, #17920
	str	r2, [r8, #884]
	str	r3, [r6, #4]
	blt	.L387
	ldr	r3, [fp, #-52]
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L387
	ldr	r3, [r4, #800]
	cmp	r3, #0
	beq	.L387
	ldr	r2, [fp, #-60]
	mov	r0, r7
	mov	r3, #1
	str	r3, [r2, #4]
.L369:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L371:
	ldr	ip, .L395+8
	mov	r0, r3
	movw	r2, #1871
	ldr	r1, .L395+16
	ldr	r3, [ip, #68]
	blx	r3
	b	.L372
.L390:
	ldr	r4, [r9, #68]
	mov	r0, r10
	movw	r3, #1894
	ldr	r2, .L395+20
	ldr	r1, .L395+24
	blx	r4
.L387:
	mvn	r0, #6
	b	.L369
.L389:
	ldr	ip, .L395+8
	movw	r3, #1867
	ldr	r2, .L395+20
	mov	r0, #0
	ldr	r1, .L395+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #6
	b	.L369
.L388:
	ldr	r3, .L395+8
	mov	r0, #0
	ldr	r2, .L395+20
	ldr	r1, .L395+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #6
	b	.L369
.L391:
	ldr	r3, [r9, #68]
	ldr	r2, .L395+20
	ldr	r1, .L395+36
	blx	r3
	mvn	r0, #0
	b	.L369
.L392:
	ldr	r3, [r9, #68]
	ldr	r2, .L395+20
	ldr	r1, .L395+40
	blx	r3
	mvn	r0, #0
	b	.L369
.L393:
	ldr	r3, [r9, #68]
	ldr	r2, .L395+20
	ldr	r1, .L395+44
	blx	r3
	mvn	r0, #0
	b	.L369
.L394:
	ldr	r3, [r9, #68]
	ldr	r2, .L395+20
	ldr	r1, .L395+48
	blx	r3
	mvn	r0, #0
	b	.L369
.L396:
	.align	2
.L395:
	.word	.LANCHOR0
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	.word	.LC20
	.word	.LANCHOR3+60
	.word	.LC27
	.word	.LC26
	.word	.LC25
	.word	.LC28
	.word	.LC29
	.word	.LC30
	.word	.LC31
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L407
	mov	r4, r0
	mov	ip, #0
	add	r5, r3, #768
	mov	r0, r5
.L399:
	ldr	r2, [r3, #40]
	add	r3, r3, #48
	cmp	r2, #0
	add	r1, r2, #188416
	beq	.L398
	ldr	r2, [r1, #2360]
	cmp	r2, #0
	beq	.L398
	ldr	r2, [r1, #2348]
	cmp	r2, #0
	strle	ip, [r1, #2360]
.L398:
	cmp	r3, r0
	bne	.L399
	mov	r0, r4
	mov	r6, #0
	bl	ResetSCD
	ldr	ip, .L407+4
	mov	r3, #84
	ldr	r2, .L407+8
	mov	r0, r4, asl #7
	mov	r1, r6
	mla	r3, r3, r4, ip
	sub	r0, r0, r4, asl #5
	add	r0, r5, r0
	ldr	r4, [r2, #48]
	mov	r2, #96
	str	r6, [r3, #76]
	blx	r4
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L408:
	.align	2
.L407:
	.word	.LANCHOR0+8
	.word	g_VfmwGlobalStat
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SM_CloseSCDDrv, .-SM_CloseSCDDrv
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
	cmp	r0, #15
	bhi	.L417
	cmp	r1, #0
	bne	.L418
	mov	r2, r0, asl #6
	ldr	r1, .L419
	sub	r0, r2, r0, asl #4
	add	r0, r1, r0
	ldr	r3, [r0, #48]
	cmn	r1, #776
	cmpne	r3, #0
	moveq	r2, #1
	movne	r2, #0
	beq	.L413
	add	r3, r3, #188416
	ldr	r0, [r3, #2348]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r7, [r1, #784]
	mov	r0, r2
	ldr	r6, [r1, #788]
	mov	ip, #1152
	ldr	r5, [r1, #792]
	ldr	r4, [r1, #796]
	ldr	lr, [r1, #800]
	str	r2, [r3, #2348]
	ldr	r2, [r1, #804]
	str	r7, [r3, #2248]
	str	r6, [r3, #2252]
	ldr	r7, [r1, #808]
	str	r5, [r3, #2256]
	ldr	r6, [r1, #812]
	str	r4, [r3, #2260]
	ldr	r5, [r1, #816]
	str	lr, [r3, #2264]
	ldr	r4, [r1, #820]
	str	r2, [r3, #2268]
	ldr	lr, [r1, #824]
	ldr	r2, [r1, #828]
	str	r7, [r3, #2300]
	str	r6, [r3, #2304]
	str	r5, [r3, #2308]
	str	r4, [r3, #2312]
	str	lr, [r3, #2316]
	str	r2, [r3, #2320]
	str	ip, [r3, #2272]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L413:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L417:
	ldr	ip, .L419+4
	mov	r3, r0
	movw	r2, #2318
	ldr	r1, .L419+8
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L418:
	ldr	ip, .L419+4
	mov	r3, r1
	movw	r2, #2324
	ldr	r1, .L419+12
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L420:
	.align	2
.L419:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC32
	.word	.LC33
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
	ldr	r3, .L426
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #4
	add	r0, r3, r0
	ldr	r3, [r0, #48]
	cmp	r3, #0
	beq	.L425
	ldr	r2, [r3, #64]
	cmp	r2, #0
	beq	.L425
	add	r3, r3, #188416
	ldr	r0, [r3, #2360]
	cmp	r0, #0
	bne	.L425
	mov	r2, #1
	str	r2, [r3, #2360]
	ldmfd	sp, {fp, sp, pc}
.L425:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L427:
	.align	2
.L426:
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
	ldr	r3, .L435
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #4
	add	r0, r3, r0
	ldr	r0, [r0, #48]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	add	r3, r0, #188416
	ldr	r0, [r3, #2360]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r2, [r3, #2348]
	cmp	r2, #0
	movle	r0, #0
	strle	r0, [r3, #2360]
	mvngt	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L436:
	.align	2
.L435:
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
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L446
	mov	r2, r0, asl #6
	ldr	r3, .L455
	sub	r0, r2, r0, asl #4
	add	r0, r3, r0
	ldr	r0, [r0, #48]
	cmp	r0, #0
	beq	.L454
	add	r2, r0, #188416
	add	r3, r0, #200704
	cmn	r0, #104
	add	r0, r0, #98304
	ldr	ip, [r2, #2360]
	strb	ip, [r1]
	ldr	r3, [r3, #3940]
	str	r3, [r1, #20]
	beq	.L440
	ldr	r3, [r0, #108]
	ldr	ip, [r0, #104]
	subs	r3, r3, ip
	addmi	r3, r3, #1024
	strmi	r3, [r1, #4]
	strpl	r3, [r1, #4]
.L442:
	ldr	r3, [r0, #124]
	str	r3, [r1, #12]
	ldr	ip, [r0, #116]
	rsb	r3, ip, r3
	str	r3, [r1, #12]
.L440:
	adds	r0, r0, #128
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r2, #2188]
	ldr	r0, [r2, #2184]
	subs	r3, r3, r0
	addmi	r3, r3, #1152
	strmi	r3, [r1, #8]
	strpl	r3, [r1, #8]
.L444:
	ldr	r3, [r2, #2216]
	mov	r0, #0
	str	r3, [r1, #16]
	ldmfd	sp, {fp, sp, pc}
.L454:
	cmp	r1, #0
	beq	.L446
	strb	r0, [r1]
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L446:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L456:
	.align	2
.L455:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_GetInfo, .-SM_GetInfo
	.align	2
	.global	SM_PushRaw
	.type	SM_PushRaw, %function
SM_PushRaw:
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
	ldr	r3, .L462
	mov	r2, r0, asl #6
	ldr	lr, [r1]
	sub	r0, r2, r0, asl #4
	add	r0, r3, r0
	cmp	lr, #0
	ldr	r0, [r0, #48]
	beq	.L458
	ldr	r3, [r1, #4]
	cmp	r0, #0
	cmpne	r3, #0
	beq	.L458
	add	r0, r0, #104
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	InsertRawPacket
.L458:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L463:
	.align	2
.L462:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_PushRaw, .-SM_PushRaw
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldr	r3, .L495
	mov	r2, r0, asl #6
	str	r0, [fp, #-72]
	sub	r2, r2, r0, asl #4
	mov	r7, r1
	add	r3, r3, r2
	ldr	r5, [r3, #48]
	cmp	r5, #0
	beq	.L482
	cmn	r5, #104
	add	r8, r5, #98304
	add	r2, r8, #128
	str	r2, [fp, #-68]
	movne	r3, #0
	moveq	r3, #1
	cmn	r8, #128
	add	r2, r5, #104
	str	r2, [fp, #-64]
	movne	r10, #0
	moveq	r10, #1
	orr	r3, r10, r3
	cmp	r7, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L482
	ldr	lr, [r8, #108]
	ldr	r3, [r8, #104]
	cmp	lr, r3
	beq	.L468
	mov	r2, r3, asl #5
	mov	r9, r3, asl #7
	rsb	r1, r2, r9
	str	r2, [fp, #-48]
	add	r1, r5, r1
	mov	ip, r2
	mov	r4, #1
	mov	r2, r9
	ldr	r6, [r1, #112]
	b	.L467
.L469:
	add	r4, r4, #1
	ldr	r0, [r0, #112]
	cmp	r4, #1024
	add	r6, r6, r0
	movls	r1, #0
	movhi	r1, #1
	cmp	r3, lr
	orreq	r1, r1, #1
	cmp	r1, #0
	bne	.L468
.L467:
	rsb	r1, ip, r2
	add	r3, r3, #1
	add	r1, r5, r1
	ubfx	r3, r3, #0, #10
	ldrb	r1, [r1, #156]	@ zero_extendqisi2
	mov	ip, r3, asl #5
	mov	r2, r3, asl #7
	cmp	r1, #0
	rsb	r0, ip, r2
	add	r0, r5, r0
	bne	.L469
	cmp	r10, #0
	addne	r3, r5, #188416
	bne	.L470
	ldr	r3, .L495+4
	mov	r2, #92160
	mov	r1, r10
	add	r0, r8, #136
	ldr	r3, [r3, #48]
	blx	r3
	add	r3, r5, #188416
	ldr	r2, [r3, #2200]
	str	r10, [r3, #2184]
	str	r10, [r3, #2188]
	str	r10, [r3, #2192]
	str	r2, [r3, #2208]
	str	r2, [r3, #2212]
.L470:
	ldr	r2, [r3, #2204]
	add	r2, r2, #-67108863
	add	r2, r2, #66846720
	cmp	r2, r6
	ble	.L492
	ldr	r2, [r5, #56]
	ldr	r0, [r3, #2200]
	ldr	r1, [r8, #128]
	sub	r3, r2, #10
	bics	r3, r3, #2
	str	r1, [fp, #-56]
	bne	.L472
	ldr	r3, .L495+8
	ldr	r3, [r3]
	ands	r3, r3, #1
	moveq	r2, r1
	streqb	r3, [r2]
	addeq	r3, r2, #1
	ldreq	r2, [r5, #56]
	streq	r3, [fp, #-56]
.L472:
	ldr	r3, [fp, #-48]
	cmp	r2, #12
	ldr	r10, [r8, #104]
	rsb	r3, r3, r9
	add	r3, r5, r3
	ldr	r1, [r3, #108]
	ldr	r3, [r3, #112]
	str	r3, [fp, #-76]
	beq	.L493
.L473:
	str	r0, [r7, #8]
	str	r1, [fp, #-52]
	bl	MEM_Phy2Vir
	ldr	r3, [fp, #-48]
	cmp	r4, #0
	ldr	r1, [fp, #-52]
	rsb	r9, r3, r9
	ldr	r3, [fp, #-56]
	add	r9, r5, r9
	str	r0, [r7]
	rsb	r0, r0, r3
	str	r0, [r7, #12]
	mov	r0, #1
	ldrd	r2, [r9, #120]
	strd	r2, [r7, #24]
	ldrd	r2, [r9, #120]
	strd	r2, [r7, #32]
	ldrd	r2, [r9, #136]
	strb	r0, [r7, #5]
	strd	r2, [r7, #40]
	beq	.L480
	ldr	r3, [fp, #-56]
	cmp	r1, #0
	cmpne	r3, #0
	beq	.L468
	ldr	r3, .L495+4
	mov	r8, r10, asl #7
	str	r6, [fp, #-80]
	mov	ip, r1
	ldr	r6, [fp, #-56]
	str	r3, [fp, #-52]
	mov	r3, r10, asl #5
	str	r4, [fp, #-56]
	mov	r2, r3
	str	r5, [fp, #-60]
	mov	r3, #0
	ldr	r5, [fp, #-76]
	mov	r4, r2
	b	.L478
.L479:
	cmp	r6, #0
	cmpne	ip, #0
	beq	.L468
.L478:
	str	r3, [fp, #-48]
	mov	r1, ip
	ldr	r3, [fp, #-52]
	mov	r2, r5
	mov	r0, r6
	rsb	r4, r4, r8
	add	r10, r10, #1
	add	r6, r6, r5
	ldr	r3, [r3, #52]
	ubfx	r10, r10, #0, #10
	blx	r3
	ldr	r3, [fp, #-60]
	mov	r8, r10, asl #7
	ldr	r1, [r7, #12]
	add	r4, r3, r4
	add	r5, r1, r5
	ldrb	r2, [r4, #157]	@ zero_extendqisi2
	mov	r4, r10, asl #5
	rsb	r0, r4, r8
	str	r5, [r7, #12]
	add	r0, r3, r0
	ldr	r3, [fp, #-48]
	strb	r2, [r7, #6]
	ldr	ip, [r0, #108]
	add	r3, r3, #1
	ldr	r5, [r0, #112]
	ldrd	r0, [r9, #144]
	ldr	r2, [fp, #-56]
	strd	r0, [r7, #48]
	cmp	r3, r2
	ldr	r2, [r9, #160]
	str	r2, [r7, #56]
	ldr	r2, [r9, #164]
	str	r2, [r7, #60]
	ldr	r2, [r9, #168]
	str	r2, [r7, #64]
	ldr	r2, [r9, #172]
	str	r2, [r7, #68]
	bne	.L479
	ldr	r6, [fp, #-80]
.L480:
	ldr	r2, [fp, #-72]
	mov	r1, r7
	ldr	r0, [fp, #-68]
	bl	InsertStreamSeg
	mov	r1, r6
	ldr	r0, [fp, #-64]
	bl	DeleteRawLen
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L468:
	mvn	r0, #3
.L465:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L493:
	ldr	r3, .L495+8
	ldr	r2, [fp, #-76]
	ldr	r3, [r3]
	cmp	r2, #0
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	beq	.L473
	cmp	r2, #2
	bgt	.L494
	cmp	r4, #1
	add	r3, r10, #1
	ubfx	r10, r3, #0, #10
	bls	.L468
	mov	r8, r10, asl #7
	sub	r3, r8, r10, asl #5
	add	r3, r5, r3
	ldr	r2, [r3, #112]
	ldr	r1, [r3, #108]
	ldr	r3, [fp, #-76]
	add	r2, r3, r2
	cmp	r2, #2
	ble	.L475
	add	r3, r10, #1020
	sub	r2, r2, #3
	add	r3, r3, #3
	str	r2, [fp, #-76]
	ubfx	r3, r3, #0, #10
	sub	r4, r4, #1
	mov	r2, r3, asl #7
	sub	r3, r2, r3, asl #5
	add	r3, r5, r3
	ldr	lr, [r3, #112]
	rsb	lr, lr, #3
	add	r1, r1, lr
	b	.L473
.L492:
	ldr	r4, .L495+4
	mov	r2, r6
	ldr	r1, .L495+12
	mov	r0, #0
	ldr	r3, [r4, #68]
	blx	r3
	mov	r1, r6
	ldr	r0, [fp, #-64]
	bl	DeleteRawLen
	cmp	r0, #0
	beq	.L465
	ldr	r3, [r4, #68]
	movw	r2, #2587
	ldr	r1, .L495+16
	mov	r0, #0
	blx	r3
	mov	r0, #0
	b	.L465
.L494:
	sub	r3, r2, #3
	add	r1, r1, #3
	str	r3, [fp, #-76]
	b	.L473
.L482:
	mvn	r0, #0
	b	.L465
.L475:
	cmp	r4, #2
	add	r3, r10, #1
	ubfx	r10, r3, #0, #10
	bls	.L468
	mov	r8, r10, asl #7
	sub	r3, r8, r10, asl #5
	add	r3, r5, r3
	ldr	r1, [r3, #112]
	ldr	lr, [r3, #108]
	add	r1, r2, r1
	cmp	r1, #2
	ble	.L468
	add	r2, r10, #1020
	sub	r1, r1, #3
	str	r1, [fp, #-76]
	sub	r4, r4, #2
	mov	r3, r2
	add	r2, r2, #3
	ubfx	r2, r2, #0, #10
	add	r3, r3, #2
	ubfx	r3, r3, #0, #10
	mov	ip, r2, asl #7
	mov	r1, r3, asl #7
	sub	ip, ip, r2, asl #5
	sub	r3, r1, r3, asl #5
	add	ip, r5, ip
	add	r2, r5, r3
	ldr	r3, [ip, #112]
	ldr	r1, [r2, #112]
	rsb	r3, r3, #3
	rsb	r1, r1, r3
	add	r1, lr, r1
	b	.L473
.L496:
	.align	2
.L495:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VdmCharacter
	.word	.LC34
	.word	.LC35
	UNWIND(.fnend)
	.size	SM_CopyRawToSeg, .-SM_CopyRawToSeg
	.align	2
	.global	SM_CopyYuvToDnr
	.type	SM_CopyYuvToDnr, %function
SM_CopyYuvToDnr:
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
	ldr	r3, .L515
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #4
	add	r0, r3, r0
	ldr	r7, [r0, #48]
	cmp	r7, #0
	beq	.L507
	add	r0, r7, #98304
	add	r5, r7, #104
	cmn	r0, #128
	movne	r4, #0
	moveq	r4, #1
	cmn	r0, #128
	cmnne	r7, #104
	beq	.L507
	ldr	r6, [r0, #104]
	ldr	r3, [r0, #108]
	cmp	r3, r6
	beq	.L508
	cmp	r4, #0
	bne	.L499
	ldr	r3, .L515+4
	mov	r2, #92160
	add	r0, r0, #136
	mov	r1, r4
	ldr	r3, [r3, #48]
	blx	r3
	add	r2, r7, #188416
	ldr	r3, [r2, #2200]
	str	r4, [r2, #2184]
	str	r4, [r2, #2188]
	str	r4, [r2, #2192]
	str	r3, [r2, #2208]
	str	r3, [r2, #2212]
.L499:
	mov	r4, r6, asl #5
	mov	r6, r6, asl #7
	rsb	r2, r4, r6
	add	r2, r7, r2
	ldr	r0, [r2, #108]
	ldr	ip, [r0]
	ldr	r3, [r0, #4]
	sub	r1, ip, #32
	cmp	r1, #1888
	bhi	.L500
	sub	r1, r3, #32
	cmp	r1, #1056
	bls	.L513
.L500:
	ldr	r8, .L515+4
	mov	r0, #0
	ldr	r1, .L515+8
	rsb	r6, r4, r6
	ldr	r3, [r8, #68]
	blx	r3
	add	r3, r7, r6
	mov	r0, r5
	ldr	r1, [r3, #112]
	bl	DeleteRawLen
	cmp	r0, #0
	bne	.L514
.L512:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L513:
	ldr	r1, [r2, #112]
	mov	r2, #51712
	movt	r2, 47
	sub	lr, r1, #1552
	cmp	lr, r2
	bhi	.L500
	mul	r3, r3, ip
	add	r2, r7, #188416
	ldr	r2, [r2, #2204]
	add	r2, r2, #-67108863
	add	r3, r3, r3, lsl #1
	add	r2, r2, #66846720
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	cmp	r2, r3
	ble	.L500
	add	r3, r3, #15
	cmp	r1, r3
	ble	.L500
	ldr	r3, [r0, #8]
	movw	ip, #1916
	ldr	r2, [r0, #12]
	sub	r3, r3, #4
	cmp	r3, ip
	bhi	.L503
	sub	r2, r2, #4
	movw	r3, #1084
	cmp	r2, r3
	bls	.L504
.L503:
	ldr	r8, .L515+4
	mov	r0, #0
	ldr	r1, .L515+12
	rsb	r6, r4, r6
	ldr	r3, [r8, #68]
	blx	r3
	add	r3, r7, r6
	mov	r0, r5
	ldr	r1, [r3, #112]
	bl	DeleteRawLen
	cmp	r0, #0
	beq	.L512
	ldr	r3, [r8, #68]
	movw	r2, #2814
	ldr	r1, .L515+16
	mov	r0, #0
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L514:
	ldr	r3, [r8, #68]
	movw	r2, #2799
	ldr	r1, .L515+16
	mov	r0, #0
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L507:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L508:
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L504:
	mov	r0, r5
	bl	DeleteRawLen
	b	.L512
.L516:
	.align	2
.L515:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC36
	.word	.LC37
	.word	.LC35
	UNWIND(.fnend)
	.size	SM_CopyYuvToDnr, .-SM_CopyYuvToDnr
	.align	2
	.global	SM_ReadStreamSeg
	.type	SM_ReadStreamSeg, %function
SM_ReadStreamSeg:
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
	ldr	r3, .L532
	mov	r2, r0, asl #6
	sub	r2, r2, r0, asl #4
	mov	r5, r0
	add	r3, r3, r2
	mov	r6, r1
	ldr	r4, [r3, #48]
	cmp	r4, #0
	cmpne	r1, #0
	beq	.L523
	ldr	r2, [r4, #56]
	sub	r3, r2, #8
	sub	r1, r2, #4
	cmp	r1, #1
	cmphi	r3, #5
	movls	r3, #1
	movhi	r3, #0
	cmp	r2, #15
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L519
	cmp	r2, #1
	beq	.L531
.L520:
	add	r0, r4, #98304
	mov	r1, r6
	add	r0, r0, #128
	bl	GetStreamSeg
	subs	r7, r0, #0
	bne	.L521
	ldr	r9, .L532+4
	ldr	r3, [r9, r5, asl #2]
	cmp	r3, #0
	beq	.L522
	ldr	r8, .L532+8
	ldr	r3, [r8, #16]
	blx	r3
	ldr	r3, [r8, #44]
	ldr	r2, [r9, r5, asl #2]
	ldr	r1, [r6, #12]
	ldr	r0, [r6]
	blx	r3
	ldr	r3, [r8, #12]
	mov	r0, r7
	blx	r3
.L522:
	add	r4, r4, #200704
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #3940]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L531:
	ldr	r3, [r4, #72]
	cmp	r3, #0
	bne	.L520
.L519:
	mov	r1, r6
	mov	r0, r5
	bl	SM_CopyRawToSeg
	cmp	r0, #0
	beq	.L520
	ldr	r3, .L532+8
	mov	r0, #26
	ldr	r1, .L532+12
	mvn	r7, #6
	ldr	r3, [r3, #68]
	blx	r3
.L521:
	add	r4, r4, #200704
	mov	r0, r7
	ldr	r3, [r4, #3940]
	add	r3, r3, #1
	str	r3, [r4, #3940]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L523:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L533:
	.align	2
.L532:
	.word	.LANCHOR0
	.word	vfmw_save_seg_file
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC38
	UNWIND(.fnend)
	.size	SM_ReadStreamSeg, .-SM_ReadStreamSeg
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
	ldr	r3, .L536
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #4
	add	r0, r3, r0
	ldr	r0, [r0, #48]
	cmp	r0, #0
	beq	.L535
	add	r0, r0, #98304
	add	r0, r0, #128
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseStreamSeg
.L535:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L537:
	.align	2
.L536:
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
	ldr	r3, .L539
	mov	r0, #0
	ldr	r3, [r3, #132]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L540:
	.align	2
.L539:
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
	ldr	r3, .L547
	mov	r2, r0, asl #6
	sub	r2, r2, r0, asl #4
	mov	r5, r1
	add	r3, r3, r2
	ldr	r4, [r3, #48]
	cmp	r4, #0
	beq	.L546
	ldr	r3, .L547+4
	add	r4, r4, #200704
	ldr	r3, [r3]
	blx	r3
	cmp	r5, #0
	mov	r2, r0
	beq	.L543
	mov	r3, #0
	str	r2, [r4, #3904]
	mov	r0, r3
	str	r3, [r4, #3900]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L543:
	ldr	r3, [r4, #3904]
	cmp	r0, r3
	strls	r5, [r4, #3900]
	rsbhi	r0, r3, r0
	strls	r2, [r4, #3904]
	strhi	r0, [r4, #3900]
	movls	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L546:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L548:
	.align	2
.L547:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	CalcInstBlockTime, .-CalcInstBlockTime
	.align	2
	.global	SetInstMode
	.type	SetInstMode, %function
SetInstMode:
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
	ldr	r2, .L552
	mov	r3, r0, asl #6
	sub	ip, r3, r0, asl #4
	sub	r0, r1, #1
	add	r2, r2, ip
	ldr	r2, [r2, #48]
	clz	r3, r2
	mov	r3, r3, lsr #5
	cmp	r0, #1
	movls	r0, r3
	orrhi	r0, r3, #1
	cmp	r0, #0
	addeq	r2, r2, #188416
	mvnne	r0, #0
	streq	r1, [r2, #2360]
	ldmfd	sp, {fp, sp, pc}
.L553:
	.align	2
.L552:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SetInstMode, .-SetInstMode
	.align	2
	.global	CheckScdStateReg
	.type	CheckScdStateReg, %function
CheckScdStateReg:
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
	ldr	r3, [r0, #16]
	cmp	r3, #0
	mvneq	r0, #6
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CheckScdStateReg, .-CheckScdStateReg
	.align	2
	.global	ScdParseUpMsgInfo
	.type	ScdParseUpMsgInfo, %function
ScdParseUpMsgInfo:
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
	beq	.L561
	ldr	ip, [r0, #12]
	mul	r3, r3, r2
	cmp	ip, #1
	ldrb	ip, [r1, #72]	@ zero_extendqisi2
	bfceq	ip, #0, #1
	orrne	ip, ip, #1
	strb	ip, [r1, #72]
	mov	ip, #0
	ldr	r2, [r0, #4]
	ldrb	lr, [r1, #72]	@ zero_extendqisi2
	ldr	r2, [r2, r3, asl #2]
	mov	r3, r3, asl #2
	add	r3, r3, #8
	mov	r2, r2, lsr #31
	bfi	lr, r2, #1, #1
	strb	lr, [r1, #72]
	ldr	r2, [r0, #4]
	uxtb	lr, lr
	ldr	r2, [r2, r3]
	mov	r2, r2, asr #16
	bfi	lr, r2, #2, #1
	strb	lr, [r1, #72]
	ldr	r2, [r0, #4]
	uxtb	lr, lr
	ldr	r2, [r2, r3]
	ubfx	r2, r2, #4, #3
	bfi	lr, r2, #3, #4
	strb	lr, [r1, #72]
	ldr	r0, [r0, #4]
	ldrh	r2, [r1, #72]
	ldr	r3, [r0, r3]
	and	r3, r3, #7
	bfi	r2, r3, #7, #4
	strh	r2, [r1, #72]	@ movhi
.L558:
	mov	r0, ip
	ldmfd	sp, {fp, sp, pc}
.L561:
	mvn	ip, #0
	b	.L558
	UNWIND(.fnend)
	.size	ScdParseUpMsgInfo, .-ScdParseUpMsgInfo
	.align	2
	.global	ScdReturnSegFilter
	.type	ScdReturnSegFilter, %function
ScdReturnSegFilter:
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
	ldr	r10, .L602
	ldr	r8, [r0, #32]
	mov	r4, r0
	str	r3, [fp, #-48]
	mov	r7, r1
	mov	r6, #0
	ldr	r1, .L602+4
	str	r6, [r2]
	mov	r0, #24
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r4, #8]
	cmp	r3, #2
	beq	.L563
	cmp	r8, r6
	ldrgt	r3, [fp, #4]
	movgt	r5, r6
	movgt	r9, r3, asl #2
	ble	.L568
.L567:
	ldr	r3, [r4, #4]
	mov	ip, r7
	ldr	lr, [r4, #20]
	mov	r2, r5
	ldr	r1, .L602+8
	mov	r0, #24
	ldr	r3, [r3, r6]
	bic	r3, r3, #-2147483648
	cmp	r3, lr
	orrcc	r3, r3, #-2147483648
	str	r3, [ip, r6]!
	ldr	r3, [r4, #4]
	add	r3, r3, r6
	add	r6, r6, r9
	ldr	r3, [r3, #4]
	str	r3, [ip, #4]
	ldr	r3, [r4, #4]
	ldr	ip, [r10, #68]
	ldr	r3, [r3, r5, asl #2]
	add	r5, r5, #1
	blx	ip
	cmp	r5, r8
	bne	.L567
.L568:
	ldr	r3, [fp, #-48]
	mov	r0, #0
	str	r0, [r4, #12]
	str	r0, [r4, #16]
	str	r8, [r3]
.L598:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L563:
	ldr	r0, [r4, #20]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L570
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	ldrb	r1, [r0]	@ zero_extendqisi2
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	ldrb	r5, [r0, #2]	@ zero_extendqisi2
	mov	r2, r2, asl #16
	orr	r2, r2, r1, asl #24
	ldr	r0, [r4, #28]
	orr	r3, r2, r3
	orr	r5, r3, r5, asl #8
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L570
	cmp	r8, #0
	mov	r3, r5, lsr #24
	strb	r5, [r0, #3]
	strb	r3, [r0]
	mov	r3, r5, lsr #16
	mov	r5, r5, lsr #8
	strb	r3, [r0, #1]
	strb	r5, [r0, #2]
	ble	.L571
	add	r3, r8, #1
	str	r3, [fp, #-56]
	ldr	r3, [fp, #4]
	add	r9, r7, #4
	str	r7, [fp, #-52]
	mov	r6, #4
	mov	r8, #1
	mov	r3, r3, asl #2
	str	r3, [fp, #-60]
	mov	r7, r3
	b	.L579
.L600:
	mov	r3, #1
	str	r3, [r4, #12]
	mov	r3, #0
	str	r3, [r4, #16]
.L575:
	str	r5, [r9, #-4]
	mov	r5, r8
	ldr	r3, [r4, #4]
	add	r8, r8, #1
	ldr	r2, [fp, #-52]
	add	r9, r9, r7
	ldr	r3, [r3, r6]
	str	r3, [r2, r6]
	add	r6, r6, r7
	ldr	r3, [fp, #-56]
	cmp	r8, r3
	beq	.L599
.L579:
	ldr	r3, [r4, #4]
	ldr	r2, [r4, #20]
	add	r3, r3, r6
	ldr	r5, [r3, #-4]
	bic	r5, r5, #-2147483648
	cmp	r5, r2
	orrcc	r5, r5, #-2147483648
	cmp	r5, #0
	beq	.L570
	mov	r0, r5
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L570
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	ldrb	ip, [r0]	@ zero_extendqisi2
	ldrb	r1, [r0, #3]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	orr	r3, r3, ip, asl #24
	orr	r3, r3, r1
	orr	r2, r3, r2, asl #8
	movw	r3, #438
	cmp	r2, r3
	cmpne	r2, #288
	moveq	r3, #1
	movne	r3, #0
	beq	.L600
	bic	r2, r2, #1020
	bic	r2, r2, #3
	cmp	r2, #32768
	bne	.L575
	ldr	r2, [r4, #12]
	cmp	r2, #1
	beq	.L601
.L578:
	mov	r3, #2
	str	r3, [r4, #12]
	b	.L575
.L570:
	mvn	r0, #6
	b	.L598
.L601:
	ldr	r2, [r4, #16]
	add	r2, r2, #1
	str	r2, [r4, #16]
	cmp	r2, #12
	ble	.L575
	ldr	r2, .L602+12
	ldr	r2, [r2]
	subs	ip, r2, #0
	beq	.L578
	mov	r2, r3
	mov	r1, #102
	ldr	r0, [r4, #36]
	blx	ip
	b	.L578
.L599:
	ldr	r7, [fp, #-52]
	cmp	r5, #0
	ldr	r3, [fp, #-48]
	movgt	r6, #0
	ldrgt	r8, [fp, #-60]
	movgt	r4, r7
	str	r5, [r3]
	ble	.L582
.L581:
	mov	r2, r6
	ldr	r7, [r10, #68]
	ldr	r3, [r4], r8
	add	r6, r6, #1
	ldr	r1, .L602+8
	mov	r0, #24
	blx	r7
	cmp	r6, r5
	bne	.L581
.L582:
	mov	r0, #0
	b	.L598
.L571:
	ldr	r3, [fp, #-48]
	mov	r0, r6
	str	r6, [r3]
	b	.L598
.L603:
	.align	2
.L602:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC39
	.word	.LC40
	.word	g_event_report
	UNWIND(.fnend)
	.size	ScdReturnSegFilter, .-ScdReturnSegFilter
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
	beq	.L606
	ldr	r3, [r0, #8]
	cmp	r3, #0
	beq	.L608
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L608
	ldr	r3, [r0, #12]
	cmp	r3, r1
	mvngt	r0, #6
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L608:
	mvn	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L606:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CheckSegValid, .-CheckSegValid
	.align	2
	.global	GetSegPts
	.type	GetSegPts, %function
GetSegPts:
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
	UNWIND(.pad #40)
	sub	sp, sp, #40
	mov	r4, r3
	sub	r3, fp, #28
	mvn	r6, #0
	mvn	r7, #0
	mov	lr, #0
	mov	r5, r2
	add	ip, r4, #32
	add	r2, r4, #68
	str	ip, [sp, #28]
	str	r2, [sp, #24]
	add	ip, r4, #64
	add	r2, r4, #60
	str	ip, [sp, #20]
	str	r2, [sp, #16]
	add	ip, r4, #56
	add	r2, r4, #48
	str	ip, [sp, #12]
	str	r2, [sp, #8]
	add	ip, r4, #40
	add	r2, r4, #24
	stmia	sp, {r2, ip}
	mvn	ip, #0
	str	lr, [r3, #-4]!
	sub	r2, fp, #36
	strd	r6, [r4, #24]
	strd	r6, [r4, #40]
	strd	r6, [r4, #32]
	strd	r6, [r4, #48]
	str	ip, [r4, #56]
	str	ip, [r4, #60]
	str	ip, [r4, #64]
	str	ip, [r4, #68]
	str	lr, [fp, #-36]
	bl	GetRawNumOffsert
	ldrd	r0, [r4, #24]
	ldrd	r2, [r5]
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L613
	strd	r0, [r5]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L613:
	strd	r6, [r4, #24]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
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
	beq	.L619
	cmp	r0, #2
	movne	r0, #0
	beq	.L620
.L616:
	mov	r2, #0
	movt	r2, 65025
	cmp	r1, r2
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L619:
	mov	r3, #0
	movt	r3, 46593
	rsb	r0, r3, r1
	clz	r0, r0
	mov	r0, r0, lsr #5
	b	.L616
.L620:
	ubfx	r3, r1, #16, #8
	sub	r3, r3, #128
	cmp	r3, #3
	movhi	r0, #0
	movls	r0, #1
	b	.L616
	UNWIND(.fnend)
	.size	IsVopHeader, .-IsVopHeader
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
	ldr	r2, .L636
	mov	r3, r0, asl #6
	mov	r5, r1
	sub	r3, r3, r0, asl #4
	ldr	r1, .L636+4
	add	r3, r2, r3
	sub	r0, fp, #128
	mov	r2, #100
	ldr	r4, [r3, #48]
	bl	memcpy
	cmp	r5, #0
	beq	.L634
	ldr	r3, [r4, #56]
	cmp	r3, #17
	bhi	.L624
	mov	r2, #1
	movw	r4, #49022
	mov	r2, r2, asl r3
	movt	r4, 3
	and	r4, r4, r2
	cmp	r4, #0
	bne	.L625
	tst	r2, #1
	beq	.L624
	ldr	r3, [r5, #8]
	ldr	r2, [r5, #80]
	add	r1, r3, #15
	cmp	r1, r2
	bhi	.L635
	ldr	ip, .L636+8
	sub	r1, fp, #128
	ldr	r0, [r5, #4]
	mov	r2, #15
	ldr	r6, [ip, #52]
	add	r0, r0, r3
	blx	r6
	ldr	r3, [r5, #8]
	mov	r0, r4
	add	r3, r3, #15
	str	r3, [r5, #8]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L625:
	ldr	r3, [r5, #8]
	ldr	r2, [r5, #80]
	cmp	r3, r2
	bhi	.L630
	mov	r0, #0
.L631:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L624:
	ldr	ip, .L636+8
	mov	r0, #0
	ldr	r2, .L636+12
	ldr	r1, .L636+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #6
	b	.L631
.L630:
	mov	ip, #0
.L627:
	ldr	r1, .L636+8
	mov	r0, #0
	str	r2, [sp, #4]
	str	ip, [sp]
	ldr	r2, .L636+12
	ldr	r4, [r1, #68]
	ldr	r1, .L636+20
	blx	r4
	mvn	r0, #6
	b	.L631
.L635:
	mov	ip, #15
	b	.L627
.L634:
	ldr	r3, .L636+8
	mov	r0, r5
	ldr	r2, .L636+12
	ldr	r1, .L636+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #6
	b	.L631
.L637:
	.align	2
.L636:
	.word	.LANCHOR0
	.word	.LANCHOR3+76
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+176
	.word	.LC42
	.word	.LC43
	.word	.LC41
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
	ldr	r2, .L660
	mov	r3, r0, asl #6
	mov	r4, r1
	sub	r3, r3, r0, asl #4
	ldr	r1, .L660+4
	add	r3, r2, r3
	sub	r0, fp, #120
	mov	r2, #100
	ldr	r5, [r3, #48]
	bl	memcpy
	cmp	r4, #0
	beq	.L658
	ldr	r3, [r5, #56]
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L641
.L643:
	.word	.L642
	.word	.L644
	.word	.L645
	.word	.L646
	.word	.L656
	.word	.L656
	.word	.L652
	.word	.L641
	.word	.L656
	.word	.L656
	.word	.L656
	.word	.L656
	.word	.L656
	.word	.L656
	.word	.L641
	.word	.L656
	.word	.L642
	.word	.L648
.L642:
	sub	r1, fp, #120
	mov	r5, #15
.L647:
	ldr	r2, [r4, #8]
	cmp	r5, r2
	bhi	.L659
	ldr	r3, .L660+8
	mov	r2, r5
	ldr	r0, [r4, #4]
	ldr	r3, [r3, #52]
	blx	r3
	str	r5, [r4, #8]
.L656:
	mov	r0, #0
.L654:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L652:
	mov	r5, #15
	sub	r1, fp, #100
	b	.L647
.L644:
	ldr	r3, [r5, #72]
	cmp	r3, #1
	bne	.L656
	sub	r1, fp, #100
	mov	r5, #15
	b	.L647
.L645:
	mov	r5, #19
	sub	r1, fp, #80
	b	.L647
.L646:
	mov	r5, #16
	sub	r1, fp, #60
	b	.L647
.L648:
	mov	r5, #16
	sub	r1, fp, #40
	b	.L647
.L641:
	ldr	ip, .L660+8
	mov	r0, #0
	ldr	r2, .L660+12
	ldr	r1, .L660+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #6
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L659:
	ldr	r1, .L660+8
	mov	r3, r5
	str	r2, [sp]
	mov	r0, #0
	ldr	r2, .L660+12
	ldr	r4, [r1, #68]
	ldr	r1, .L660+20
	blx	r4
	mvn	r0, #6
	b	.L654
.L658:
	ldr	r3, .L660+8
	mov	r0, r4
	ldr	r2, .L660+12
	ldr	r1, .L660+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #6
	b	.L654
.L661:
	.align	2
.L660:
	.word	.LANCHOR0
	.word	.LANCHOR3+196
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+296
	.word	.LC42
	.word	.LC44
	.word	.LC41
	UNWIND(.fnend)
	.size	FillEosRawStream, .-FillEosRawStream
	.align	2
	.global	FillExtraData
	.type	FillExtraData, %function
FillExtraData:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	clz	r3, r1
	mov	r5, r1
	mov	r3, r3, lsr #5
	cmp	r0, #15
	movls	r4, r3
	orrhi	r4, r3, #1
	cmp	r4, #0
	bne	.L679
	ldr	r2, [r1, #8]
	cmp	r2, #0
	ble	.L685
	ldr	r3, .L693
	mov	r1, r0, asl #6
	sub	r0, r1, r0, asl #4
	add	r0, r3, r0
	ldr	r6, [r0, #48]
	ldr	r3, [r6, #56]
	cmp	r3, #5
	beq	.L665
	cmp	r3, #8
	beq	.L666
	cmp	r3, #1
	movne	r0, r4
	beq	.L686
.L663:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L666:
	ldr	r0, [r5, #76]
	ands	r7, r0, #128
	beq	.L676
	cmp	r2, #128
	bgt	.L687
.L677:
	ldr	r3, .L693+4
	add	r1, r6, #200704
	add	r0, r6, #203776
	str	r2, [r1, #3964]
	add	r0, r0, #896
	ldmib	r5, {r1, r2}
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L665:
	ldr	r0, [r5, #80]
	add	r1, r2, #8
	cmp	r1, r0
	bhi	.L688
	ldr	r6, .L693+4
	ldr	r1, [r5, #4]
	ldr	r3, [r6, #56]
	add	r0, r1, #8
	blx	r3
	ldr	r3, [r6, #52]
	add	r1, r5, #84
	mov	r2, #4
	ldr	r0, [r5, #4]
	blx	r3
	ldr	r0, [r5, #4]
	ldr	r3, [r6, #52]
	mov	r2, #4
	add	r1, r5, #88
	add	r0, r0, r2
	blx	r3
	ldr	r3, [r5, #8]
	mov	r0, r4
	add	r3, r3, #8
	str	r3, [r5, #8]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L686:
	ldr	r1, [r6, #72]
	ldr	r0, [r5, #76]
	cmp	r1, #1
	beq	.L689
	ands	r4, r0, #128
	beq	.L672
	cmp	r2, #116
	ldr	ip, [r5, #80]
	add	r1, r2, #12
	movle	r0, #0
	movgt	r0, #1
	cmp	r1, ip
	movls	r4, r0
	orrhi	r4, r0, #1
	cmp	r4, #0
	bne	.L690
	ldr	r7, .L693+4
	ldr	r1, [r5, #4]
	ldr	r3, [r7, #56]
	add	r0, r1, #8
	blx	r3
	ldr	r3, [r7, #52]
	mov	r2, #4
	add	r1, r5, #84
	ldr	r0, [r5, #4]
	blx	r3
	ldr	r0, [r5, #4]
	mov	r2, #4
	ldr	r3, [r7, #52]
	add	r0, r0, r2
	add	r1, r5, #88
	blx	r3
	ldr	r0, [r5, #4]
	ldr	r3, [r7, #48]
	mov	r2, #4
	mov	r1, r4
	add	r0, r0, #12
	blx	r3
	add	r2, r6, #200704
	add	r0, r6, #203776
	mov	r3, #16
	add	r0, r0, #896
	str	r3, [r5, #8]
	str	r3, [r2, #3964]
	ldr	r3, [r7, #52]
	ldmib	r5, {r1, r2}
	blx	r3
	mov	r0, r4
	b	.L663
.L676:
	add	r4, r6, #200704
	ldr	ip, [r5, #80]
	ldr	r0, [r4, #3964]
	add	r1, r2, r0
	cmp	r1, ip
	bhi	.L691
.L678:
	ldr	r8, .L693+4
	ldr	r1, [r5, #4]
	ldr	r3, [r8, #56]
	add	r0, r1, r0
	blx	r3
	add	r1, r6, #203776
	ldr	r3, [r8, #52]
	add	r1, r1, #896
	ldr	r2, [r4, #3964]
	ldr	r0, [r5, #4]
	blx	r3
	ldr	r2, [r4, #3964]
	ldr	r3, [r5, #8]
	mov	r0, r7
	add	r3, r3, r2
	str	r3, [r5, #8]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L689:
	ands	r7, r0, #128
	bne	.L692
	ldrb	r0, [r5, #72]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L663
	add	r4, r6, #200704
	ldr	lr, [r5, #80]
	ldr	r0, [r4, #3964]
	add	ip, r2, r0
	cmp	ip, lr
	bls	.L678
	ldr	r2, .L693+4
	mov	r3, r1
	mov	r0, r1
	str	lr, [sp, #4]
	str	ip, [sp]
.L684:
	ldr	r4, [r2, #68]
	ldr	r1, .L693+8
	ldr	r2, .L693+12
	blx	r4
	mvn	r0, #1
	b	.L663
.L672:
	add	r7, r6, #200704
	ldr	ip, [r5, #80]
	ldr	r0, [r7, #3964]
	add	r1, r2, r0
	cmp	r1, ip
	strhi	ip, [sp, #4]
	ldrhi	r2, .L693+4
	movhi	r0, r3
	bhi	.L683
	ldr	r8, .L693+4
	ldr	r1, [r5, #4]
	ldr	r3, [r8, #56]
	add	r0, r1, r0
	blx	r3
	add	r1, r6, #203776
	ldr	r3, [r8, #52]
	add	r1, r1, #896
	ldr	r2, [r7, #3964]
	ldr	r0, [r5, #4]
	blx	r3
	ldr	r2, [r7, #3964]
	ldr	r3, [r5, #8]
	mov	r0, r4
	add	r3, r3, r2
	str	r3, [r5, #8]
	b	.L663
.L692:
	cmp	r2, #128
	ble	.L677
	ldr	ip, .L693+4
	mov	r0, #128
	str	r2, [sp]
	mov	r3, r1
	str	r0, [sp, #4]
	mov	r0, r1
	ldr	r4, [ip, #68]
	ldr	r2, .L693+12
	ldr	r1, .L693+16
	blx	r4
	mvn	r0, #1
	b	.L663
.L688:
	ldr	r2, .L693+4
	str	r0, [sp, #4]
	mov	r0, #1
	str	r1, [sp]
	ldr	r1, .L693+20
	ldr	r4, [r2, #68]
	ldr	r2, .L693+12
	blx	r4
	mvn	r0, #1
	b	.L663
.L690:
	ldr	lr, .L693+4
	mov	r2, #128
	stmia	sp, {r1, ip}
	mov	r0, r3
	ldr	r1, .L693+24
	ldr	r4, [lr, #68]
	str	r2, [sp, #8]
	ldr	r2, .L693+12
	blx	r4
	mvn	r0, #1
	b	.L663
.L691:
	ldr	r2, .L693+4
	mov	r0, #1
	str	ip, [sp, #4]
.L683:
	str	r1, [sp]
	b	.L684
.L679:
	mvn	r0, #0
	b	.L663
.L685:
	ldr	ip, .L693+4
	mov	r3, r2
	mov	r0, #1
	ldr	r2, .L693+12
	ldr	r1, .L693+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L663
.L687:
	ldr	ip, .L693+4
	mov	r1, #128
	str	r2, [sp]
	mov	r0, #1
	ldr	r2, .L693+12
	ldr	r4, [ip, #68]
	str	r1, [sp, #4]
	ldr	r1, .L693+16
	blx	r4
	mvn	r0, #1
	b	.L663
.L694:
	.align	2
.L693:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	.LANCHOR3+316
	.word	.LC46
	.word	.LC49
	.word	.LC48
	.word	.LC45
	UNWIND(.fnend)
	.size	FillExtraData, .-FillExtraData
	.align	2
	.global	ReleaseRawStreamData
	.type	ReleaseRawStreamData, %function
ReleaseRawStreamData:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r9, r1
	mov	r8, r0
	bl	VCTRL_GetStreamInterface
	ldr	r7, .L708
	mov	r2, #12
	mov	r1, #0
	ldr	r3, [r7, #48]
	mov	r4, r0
	sub	r0, fp, #56
	blx	r3
	cmp	r4, #0
	beq	.L705
	ldr	r3, [r7, #52]
	sub	r0, fp, #56
	mov	r2, #12
	mov	r1, r4
	blx	r3
	ldr	r3, [r4, #8]
	cmp	r3, #0
	beq	.L701
	mov	r10, r8, asl #4
	mov	r6, r8, asl #6
	ldr	r5, .L708+4
	rsb	r3, r10, r6
	add	r3, r5, r3
	ldr	r3, [r3, #48]
	ldr	r3, [r3, #88]
	cmp	r3, #1
	beq	.L706
	ldr	r3, [r7, #16]
	mov	r0, #0
	blx	r3
	ldr	r3, [fp, #-48]
	mov	r1, r9
	ldr	r0, [fp, #-56]
	blx	r3
	ldr	r3, [r7, #12]
	mov	r4, r0
	mov	r0, #0
	blx	r3
.L700:
	cmp	r4, #0
	mvnne	r4, #6
.L698:
	rsb	r6, r10, r6
	add	r5, r5, r6
	ldr	r0, [r5, #48]
	cmp	r0, #0
	movne	r0, r4
	beq	.L707
.L697:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L706:
	mov	r1, r9
	ldr	r3, [fp, #-48]
	ldr	r0, [fp, #-56]
	blx	r3
	mov	r4, r0
	b	.L700
.L701:
	ldr	r5, .L708+4
	mov	r10, r8, asl #4
	mov	r6, r8, asl #6
	mvn	r4, #6
	b	.L698
.L705:
	ldr	r3, [r7, #68]
	mov	r2, r8
	mov	r0, r4
	ldr	r1, .L708+8
	blx	r3
	mvn	r0, #6
	b	.L697
.L707:
	ldr	r4, [r7, #68]
	mov	r3, r8
	movw	r2, #5276
	ldr	r1, .L708+12
	blx	r4
	mvn	r0, #6
	b	.L697
.L709:
	.align	2
.L708:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC50
	.word	.LC51
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	cmp	r0, #15
	mov	r8, r0
	bhi	.L726
	mov	r3, r0, asl #4
	mov	r9, r0, asl #6
	ldr	r2, .L730
	str	r3, [fp, #-52]
	rsb	r3, r3, r9
	add	r3, r2, r3
	ldr	r7, [r3, #48]
	cmp	r7, #0
	beq	.L722
	cmp	r1, #0
	beq	.L727
.L713:
	adds	r3, r7, #104
	str	r3, [fp, #-56]
	beq	.L722
	add	r3, r7, #98304
	str	r3, [fp, #-60]
	mov	r2, r3
	ldr	r3, [r3, #104]
	ldr	r4, [r2, #112]
	cmp	r3, r4
	addlt	r3, r3, #1024
	rsb	r3, r4, r3
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L722
	ldr	r10, .L730+4
	mov	r6, #0
	b	.L717
.L729:
	ldr	r3, [fp, #-48]
	cmp	r6, r3
	beq	.L728
.L717:
	mov	r5, r4, asl #7
	ldr	r1, .L730+8
	sub	r5, r5, r4, asl #5
	ldr	ip, [r10, #68]
	add	r2, r7, r5
	mov	r0, #26
	add	r4, r4, #1
	add	r6, r6, #1
	ldr	r3, [r2, #112]
	ubfx	r4, r4, #0, #10
	ldr	r2, [r2, #104]
	blx	ip
	ldr	r3, [fp, #-56]
	mov	r0, r8
	add	r1, r3, r5
	bl	ReleaseRawStreamData
	ldr	r3, [fp, #-52]
	ldr	r2, .L730
	rsb	r3, r3, r9
	add	r3, r2, r3
	ldr	r3, [r3, #48]
	cmp	r3, #0
	bne	.L729
	mvn	r0, #6
.L712:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L727:
	add	r3, r7, #188416
	ldr	r3, [r3, #2360]
	cmp	r3, #0
	bne	.L713
.L722:
	mvn	r0, #0
	b	.L712
.L728:
	ldr	r3, [fp, #-60]
	ldr	r4, [r3, #112]
	add	r4, r6, r4
	cmp	r4, #1024
	strlt	r4, [r3, #112]
	subge	r4, r4, #1024
	ldrge	r3, [fp, #-60]
	movlt	r0, #0
	movge	r0, #0
	strge	r4, [r3, #112]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L726:
	ldr	r3, .L730+4
	mov	r2, r0
	ldr	r1, .L730+12
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L712
.L731:
	.align	2
.L730:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC9
	.word	.LC52
	UNWIND(.fnend)
	.size	DeleteRawPacketInBuffer, .-DeleteRawPacketInBuffer
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
	ldr	r5, .L764
	mov	r3, r0, asl #6
	ldr	r7, .L764+4
	sub	r3, r3, r0, asl #4
	mov	r6, r0
	add	r5, r5, r3
	mov	r9, r1
	ldr	r3, [r7, #48]
	sub	r0, fp, #48
	ldr	r4, [r5, #48]
	mov	r2, #12
	mov	r1, #0
	blx	r3
	cmp	r4, #0
	beq	.L736
	mov	r0, r6
	bl	VCTRL_GetStreamInterface
	subs	r8, r0, #0
	beq	.L757
	ldr	r3, [r7, #52]
	sub	r0, fp, #48
	mov	r2, #12
	mov	r1, r8
	blx	r3
	ldr	r3, [r8, #4]
	cmp	r3, #0
	beq	.L736
	ldr	r3, [r4, #88]
	cmp	r3, #1
	beq	.L758
	ldr	r3, [r7, #16]
	mov	r0, #0
	blx	r3
	ldr	r3, [fp, #-44]
	mov	r1, r9
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r7, #12]
	mov	r8, r0
	mov	r0, #0
	blx	r3
	ldr	r0, [r5, #48]
	cmp	r0, #0
	beq	.L759
.L738:
	cmp	r8, #0
	bne	.L736
	ldrb	r5, [r9, #53]	@ zero_extendqisi2
	cmp	r5, #1
	beq	.L760
	ldr	r3, [r4, #88]
	cmp	r3, #1
	beq	.L761
.L741:
	add	r4, r4, #98304
	ldr	r2, [r9, #8]
	mov	r0, #0
	ldr	r3, [r4, #124]
	add	r3, r3, r2
	str	r3, [r4, #124]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L736:
	mvn	r0, #6
.L754:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L758:
	ldr	r3, [fp, #-44]
	mov	r1, r9
	ldr	r0, [fp, #-48]
	blx	r3
	mov	r8, r0
	b	.L738
.L760:
	mov	r1, r9
	mov	r0, r6
	bl	FillEosRawStream
	cmp	r0, #0
	bne	.L762
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_SetLastFrameState
	b	.L741
.L761:
	mov	r1, r9
	mov	r0, r6
	bl	FillExtraData
	cmp	r0, #0
	bne	.L763
	ldrb	r3, [r9, #52]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L741
	mov	r0, r6
	mov	r1, r9
	bl	FillEopRawStream
	b	.L741
.L763:
	ldr	r3, [r7, #68]
	mov	r2, r6
	ldr	r1, .L764+8
	mov	r0, r8
	blx	r3
	mov	r1, r9
	ldr	r0, [fp, #-48]
	bl	ReleaseRawStreamData
	ldr	r3, .L764+4
	cmp	r0, #0
	beq	.L736
	ldr	r3, [r3, #68]
	mov	r0, r8
	ldr	r1, .L764+12
	blx	r3
	mvn	r0, #6
	b	.L754
.L757:
	ldr	r3, [r7, #68]
	mov	r2, r6
	ldr	r1, .L764+16
	blx	r3
	mvn	r0, #6
	b	.L754
.L762:
	ldr	r3, [r7, #68]
	mov	r2, r6
	mov	r0, r8
	ldr	r1, .L764+20
	blx	r3
	mvn	r0, #6
	b	.L754
.L759:
	ldr	r4, [r7, #68]
	mov	r3, r6
	movw	r2, #5176
	ldr	r1, .L764+24
	blx	r4
	mvn	r0, #6
	b	.L754
.L765:
	.align	2
.L764:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC56
	.word	.LC57
	.word	.LC53
	.word	.LC55
	.word	.LC54
	UNWIND(.fnend)
	.size	ReadRawStreamData, .-ReadRawStreamData
	.align	2
	.global	SM_MoveRawData
	.type	SM_MoveRawData, %function
SM_MoveRawData:
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
	add	r7, r0, #98304
	ldr	ip, [r0, #96]
	mov	r5, r0
	ldr	r3, [r7, #108]
	subs	r6, r3, #1
	addmi	r6, r3, #1020
	addmi	r6, r6, #3
	subs	r8, r3, #2
	addmi	r8, r3, #1020
	addmi	r8, r8, #2
	mov	r1, r6, asl #7
	sub	r1, r1, r6, asl #5
	mov	r3, r8, asl #7
	add	r9, r0, r1
	sub	r8, r3, r8, asl #5
	add	r1, r1, #104
	add	r8, r0, r8
	ldr	r2, [r9, #112]
	add	r4, r0, r1
	ldr	r0, [r8, #112]
	add	r3, r0, r2
	cmp	r3, ip
	bgt	.L769
	ldr	r3, .L771
	add	r5, r5, #188416
	ldr	ip, [r8, #108]
	ldr	r1, [r9, #108]
	ldr	r3, [r3, #52]
	add	r0, ip, r0
	blx	r3
	ldr	r2, [r9, #112]
	ldr	r3, [r8, #112]
	mov	r1, r4
	add	r3, r3, r2
	str	r3, [r8, #112]
	ldr	r0, [r5, #2344]
	bl	ReleaseRawStreamData
	mov	r0, #0
	str	r6, [r7, #108]
.L770:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L769:
	ldr	lr, .L771
	mov	r3, r2
	str	ip, [sp]
	mov	r2, r0
	ldr	r1, .L771+4
	mov	r0, #1
	ldr	r4, [lr, #68]
	blx	r4
	mvn	r0, #6
	b	.L770
.L772:
	.align	2
.L771:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC58
	UNWIND(.fnend)
	.size	SM_MoveRawData, .-SM_MoveRawData
	.align	2
	.global	SM_AddMatchMode
	.type	SM_AddMatchMode, %function
SM_AddMatchMode:
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
	ldr	r4, .L789
	mov	r8, #0
	ldr	r7, .L789+4
	ldr	r9, .L789+8
	add	r6, r4, #768
	b	.L778
.L777:
	ldr	r10, [r9, #68]
	blx	r10
.L786:
	add	r5, r5, #188416
	str	r8, [r5, #2356]
.L774:
	add	r4, r4, #48
	cmp	r4, r6
	beq	.L788
.L778:
	ldr	r5, [r4, #40]
	cmp	r5, #0
	beq	.L774
	ldr	r3, [r5, #80]
	mov	r0, #0
	ldr	r1, .L789+12
	cmp	r3, r0
	beq	.L774
	ldr	ip, [r7]
	ldr	r3, [r7, #4]
	cmp	ip, #1
	mov	r2, ip
	bne	.L777
	cmp	r3, #1
	beq	.L786
	cmp	r3, #2
	addeq	r5, r5, #188416
	streq	ip, [r5, #2356]
	bne	.L777
	add	r4, r4, #48
	cmp	r4, r6
	bne	.L778
.L788:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L790:
	.align	2
.L789:
	.word	.LANCHOR0+8
	.word	g_DspDrvState
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC59
	UNWIND(.fnend)
	.size	SM_AddMatchMode, .-SM_AddMatchMode
	.align	2
	.global	SCDDRV_CheckDevice
	.type	SCDDRV_CheckDevice, %function
SCDDRV_CheckDevice:
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
	subs	r7, r0, #0
	bne	.L797
	ldr	r4, .L802
	movw	r3, #6233
	str	r7, [sp]
	mov	r0, #26
	ldr	r6, .L802+4
	ldr	r1, [r4, #860]
	ldr	r2, .L802+8
	ldr	r5, [r6, #68]
	str	r1, [sp, #4]
	ldr	r1, .L802+12
	blx	r5
	ldr	r5, [r4, #860]
	cmp	r5, #0
	beq	.L801
	str	r5, [sp, #4]
	movw	r3, #6243
	ldr	r2, .L802+8
	mov	r0, #26
	ldr	r1, .L802+12
	str	r7, [sp]
	ldr	r5, [r6, #68]
	blx	r5
	ldr	r3, [r6]
	blx	r3
	ldr	r3, [r4, #864]
	cmp	r0, r3
	strcc	r0, [r4, #864]
	bcc	.L795
	rsb	r3, r3, r0
	cmp	r3, #2000
	bls	.L795
	mov	r2, r7
	ldr	r1, .L802+16
	ldr	r5, [r6, #68]
	mov	r0, #1
	blx	r5
	mov	r0, r7
	bl	ResetSCD
	ldr	r0, [r4, #856]
	str	r7, [r4, #860]
	mov	r5, #0
	mov	r3, r0, asl #6
	sub	r3, r3, r0, asl #4
	add	r4, r4, r3
	ldr	r3, [r4, #48]
	cmp	r3, #0
	addne	r3, r3, #188416
	strne	r7, [r3, #2352]
	bl	DeleteLastSendRaw
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L795:
	mov	r2, #0
	ldr	r4, [r6, #68]
	str	r2, [sp]
	movw	r3, #6286
	ldr	r2, .L802+8
	mov	r0, #26
	ldr	r1, .L802+20
	mov	r5, #1
	blx	r4
.L792:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L801:
	str	r5, [sp]
	movw	r3, #6237
	ldr	r4, [r6, #68]
	mov	r0, #26
	ldr	r2, .L802+8
	ldr	r1, .L802+24
	blx	r4
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L797:
	mvn	r5, #0
	b	.L792
.L803:
	.align	2
.L802:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+332
	.word	.LC60
	.word	.LC62
	.word	.LC63
	.word	.LC61
	UNWIND(.fnend)
	.size	SCDDRV_CheckDevice, .-SCDDRV_CheckDevice
	.align	2
	.global	SCDDRV_MarkReloadDsp
	.type	SCDDRV_MarkReloadDsp, %function
SCDDRV_MarkReloadDsp:
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
	add	r3, r1, #1
	cmp	r3, #16
	ldmhifd	sp, {fp, sp, pc}
	ldr	r3, .L811
	cmn	r1, #1
	mov	r2, #1
	str	r2, [r3, #868]
	ldmeqfd	sp, {fp, sp, pc}
	mov	r2, r1, asl #6
	mvn	r0, #0
	sub	r1, r2, r1, asl #4
	add	r3, r3, r1
	ldr	r3, [r3, #48]
	add	r3, r3, #188416
	str	r0, [r3, #2356]
	ldmfd	sp, {fp, sp, pc}
.L812:
	.align	2
.L811:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SCDDRV_MarkReloadDsp, .-SCDDRV_MarkReloadDsp
	.align	2
	.global	SM_UpdateMatchMode
	.type	SM_UpdateMatchMode, %function
SM_UpdateMatchMode:
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
	cmp	r1, #15
	ldmhifd	sp, {fp, sp, pc}
	mov	r2, r1, asl #6
	ldr	r3, .L815
	sub	r1, r2, r1, asl #4
	mov	r2, #1
	add	r1, r3, r1
	ldr	r3, [r1, #48]
	add	r3, r3, #188416
	str	r2, [r3, #2356]
	ldmfd	sp, {fp, sp, pc}
.L816:
	.align	2
.L815:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	SM_UpdateMatchMode, .-SM_UpdateMatchMode
	.align	2
	.global	WaitSCDFinish
	.type	WaitSCDFinish, %function
WaitSCDFinish:
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
	ldr	r2, .L827
	mov	r3, r0, asl #7
	sub	r0, r3, r0, asl #5
	add	r0, r0, r2
	ldr	r3, [r0, #4]
	cmp	r3, #1
	beq	.L818
.L820:
	mov	r0, #0
.L819:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L818:
	ldr	r6, .L827+4
	movw	r5, #41248
	movt	r5, 7
	ldr	r3, [r6]
	blx	r3
	mov	r4, r0
	b	.L824
.L823:
	subs	r5, r5, #1
	beq	.L826
.L824:
	movw	r0, #51264
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	tst	r0, #1
	bne	.L820
	ldr	r3, [r6]
	blx	r3
	cmp	r4, r0
	rsb	r2, r0, r4
	rsb	r3, r4, r0
	mvnhi	r3, r2
	cmp	r3, #1000
	bls	.L823
	str	r3, [sp]
	mov	r2, r4
	mov	r3, r0
	ldr	r5, [r6, #68]
	ldr	r1, .L827+8
	mov	r0, #0
	blx	r5
	mvn	r0, #6
	b	.L819
.L826:
	mvn	r0, #6
	b	.L819
.L828:
	.align	2
.L827:
	.word	.LANCHOR0+856
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC64
	UNWIND(.fnend)
	.size	WaitSCDFinish, .-WaitSCDFinish
	.align	2
	.global	PrintScdVtrlReg
	.type	PrintScdVtrlReg, %function
PrintScdVtrlReg:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	str	r0, [fp, #-56]
	movw	r0, #51204
	ldr	r4, .L830
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	mov	r10, r0
	movw	r0, #51208
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	mov	r9, r0
	movw	r0, #51212
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	mov	r8, r0
	movw	r0, #51216
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	mov	r7, r0
	movw	r0, #51220
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	mov	r6, r0
	movw	r0, #51224
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	mov	r5, r0
	movw	r0, #51232
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	str	r0, [fp, #-48]
	mov	r0, #51200
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	r2, [fp, #-56]
	ldr	r3, [r4, #68]
	ldr	r1, .L830+4
	str	r0, [fp, #-52]
	mov	r0, #24
	blx	r3
	mov	r2, r10
	ldr	r3, [r4, #68]
	mov	r0, #24
	ldr	r1, .L830+8
	blx	r3
	mov	r2, r9
	ldr	r3, [r4, #68]
	mov	r0, #24
	ldr	r1, .L830+12
	blx	r3
	mov	r2, r8
	ldr	r3, [r4, #68]
	mov	r0, #24
	ldr	r1, .L830+16
	blx	r3
	mov	r2, r7
	ldr	r3, [r4, #68]
	mov	r0, #24
	ldr	r1, .L830+20
	blx	r3
	mov	r2, r6
	ldr	r3, [r4, #68]
	mov	r0, #24
	ldr	r1, .L830+24
	blx	r3
	mov	r2, r5
	ldr	r3, [r4, #68]
	mov	r0, #24
	ldr	r1, .L830+28
	blx	r3
	ldr	r2, [fp, #-48]
	ldr	r3, [r4, #68]
	mov	r0, #24
	ldr	r1, .L830+32
	blx	r3
	ldr	r3, [r4, #68]
	ldrsb	r2, [fp, #-52]
	mov	r0, #24
	ldr	r1, .L830+36
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L831:
	.align	2
.L830:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC65
	.word	.LC66
	.word	.LC67
	.word	.LC68
	.word	.LC69
	.word	.LC70
	.word	.LC71
	.word	.LC72
	.word	.LC73
	UNWIND(.fnend)
	.size	PrintScdVtrlReg, .-PrintScdVtrlReg
	.align	2
	.global	WriteScdVtrlReg
	.type	WriteScdVtrlReg, %function
WriteScdVtrlReg:
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
	ldr	r4, .L837
	mov	r5, r0
	mov	r6, r1
	ldr	r1, [r0, #4]
	ldr	r0, [r4, #4]
	add	r0, r0, #2048
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #12]
	add	r0, r0, #2048
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #20]
	add	r0, r0, #2048
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #24]
	add	r0, r0, #2064
	bl	MEM_WritePhyWord
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #28]
	add	r0, r0, #2064
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #32]
	add	r0, r0, #2064
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	ldrsb	r3, [r5, #1]
	ldr	r1, [r5, #36]
	ldr	r2, [r5, #104]
	ldr	r0, [r4, #4]
	mov	r3, r3, asl #4
	and	r1, r1, #15
	and	r3, r3, #16
	orr	r1, r1, r2, asl #8
	add	r0, r0, #2080
	orr	r1, r1, r3
	bl	MEM_WritePhyWord
	ldr	r3, [r5, #104]
	cmp	r3, #0
	beq	.L833
	ldr	r1, [r5, #108]
	ldr	r0, [r4, #4]
	bl	MEM_WritePhyWord
.L833:
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #44]
	add	r0, r0, #2080
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #56]
	add	r0, r0, #2080
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #68]
	add	r0, r0, #2096
	bl	MEM_WritePhyWord
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #80]
	add	r0, r0, #2096
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	mov	r3, r6, asl #7
	ldr	r0, [r4, #4]
	sub	r3, r3, r6, asl #5
	add	r3, r4, r3
	add	r0, r0, #2096
	ldr	r1, [r3, #832]
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	mov	r0, r6
	bl	PrintScdVtrlReg
	ldr	r0, [r4, #4]
	mov	r1, #0
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
	ldrb	r1, [r5, #2]	@ zero_extendqisi2
	ldr	r0, [r4, #4]
	and	r1, r1, #1
	add	r0, r0, #2048
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MEM_WritePhyWord
.L838:
	.align	2
.L837:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	WriteScdVtrlReg, .-WriteScdVtrlReg
	.align	2
	.global	PrintDownMsg
	.type	PrintDownMsg, %function
PrintDownMsg:
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
	ldr	r5, .L844
	mov	r4, r0
	mov	r9, r1
	mov	r8, r2
	ldr	r1, .L844+4
	mov	r2, r3
	mov	r0, #24
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r3, [r5, #68]
	mov	r2, r9
	ldr	r1, .L844+8
	mov	r0, #24
	blx	r3
	mov	r2, r4
	ldr	r3, [r5, #68]
	mov	r0, #24
	ldr	r1, .L844+12
	blx	r3
	cmp	r8, #0
	ldmlefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r8, r8, r8, lsl #1
	mov	r6, r9
	mov	r4, #0
.L841:
	mov	r2, r4
	ldr	r3, [r9, r4, asl #2]
	ldr	r7, [r5, #68]
	mov	r0, #24
	ldr	r1, .L844+16
	add	r6, r6, #12
	blx	r7
	ldr	r3, [r6, #-8]
	add	r2, r4, #1
	ldr	r7, [r5, #68]
	ldr	r1, .L844+16
	mov	r0, #24
	blx	r7
	ldr	r3, [r6, #-4]
	add	r2, r4, #2
	ldr	r1, .L844+16
	ldr	r7, [r5, #68]
	mov	r0, #24
	blx	r7
	add	r4, r4, #3
	ldr	r3, [r5, #68]
	mov	r0, #24
	ldr	r1, .L844+20
	blx	r3
	cmp	r4, r8
	bne	.L841
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L845:
	.align	2
.L844:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC77
	.word	.LC16
	UNWIND(.fnend)
	.size	PrintDownMsg, .-PrintDownMsg
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
	mov	r7, r2
	mov	r6, r0
	mov	r10, r1
	sub	r0, fp, #140
	mov	r2, #96
	mov	r1, #0
	mov	r5, r3
	bl	memset
	cmp	r7, #0
	beq	.L858
	add	r3, r7, #98304
	ldmia	r3, {r1, r2}
	cmp	r1, r2
	beq	.L859
	ldr	r4, [r3, #12]
	mov	r9, r4
.L847:
	sub	r1, fp, #140
	mov	r0, r7
	bl	ShowFirstRawPacket
	ldr	r3, [fp, #-132]
	ldr	r2, [fp, #-140]
	mov	r8, #0
	rsb	r4, r4, r3
	ldr	r3, [fp, #-136]
	cmp	r4, r10
	add	r2, r2, r9
	str	r8, [r5]
	add	r9, r3, r9
	str	r8, [r5, #4]
	str	r8, [r5, #8]
	str	r4, [fp, #-132]
	str	r2, [fp, #-140]
	str	r9, [fp, #-136]
	str	r8, [r6, #4]
	bgt	.L848
	mov	r9, r8
	mov	ip, r4
	str	r7, [fp, #-144]
	b	.L851
.L869:
	ldr	ip, [fp, #-132]
	movw	r2, #1023
	add	r4, r4, ip
	cmp	r10, r4
	movlt	r3, #0
	movge	r3, #1
	cmp	r9, r2
	movgt	r3, #0
	cmp	r3, #0
	beq	.L850
.L851:
	cmp	ip, #0
	mov	r3, r8, asl #2
	add	lr, r5, r3
	sub	r1, fp, #140
	ldr	r0, [fp, #-144]
	add	r3, r3, #12
	ble	.L849
	ldr	r2, [fp, #4]
	ldr	r7, [fp, #-140]
	add	r3, r3, r2
	mov	r2, #0
	str	r2, [fp, #-132]
	ldr	r2, [fp, #-140]
	str	r7, [r5, r8, asl #2]
	add	r8, r8, #3
	sub	r2, r2, #1
	str	r3, [lr, #8]
	add	ip, r2, ip
	str	ip, [lr, #4]
.L849:
	str	r4, [r6, #4]
	add	r9, r9, #1
	bl	ShowNextRawPacket
	cmp	r0, #0
	beq	.L869
.L850:
	ldr	r3, [fp, #8]
	cmp	r3, #0
	bne	.L852
	ldr	r3, [fp, #-132]
	cmp	r3, #0
	bne	.L857
.L852:
	cmp	r9, #0
	beq	.L856
	cmp	r8, #0
	ldr	r0, [fp, #4]
	subgt	r8, r8, #-1073741823
	mov	ip, #1
	movgt	r3, #0
	mov	r2, r9
	strgt	r3, [r5, r8, asl #2]
	mov	r1, r5
	str	r9, [r6]
	ldr	r3, [fp, #12]
	str	ip, [r6, #8]
	bl	PrintDownMsg
	mov	r0, #0
.L868:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L848:
	ldr	r3, [fp, #8]
	cmp	r3, #0
	bne	.L856
	cmp	r4, #0
	beq	.L856
	ldr	r8, [fp, #8]
	mov	r3, r4
	mov	r9, r8
.L857:
	ldr	r2, [r6, #4]
	sub	r1, r10, #16
	cmp	r2, r1
	bge	.L852
	cmp	r10, r4
	cmplt	r9, #1024
	bge	.L852
	rsb	r2, r2, r10
	cmp	r3, r2
	blt	.L852
	mov	r3, r8, asl #2
	ldr	ip, [fp, #-140]
	add	r0, r5, r3
	ldr	lr, [fp, #4]
	add	r3, r3, #12
	sub	r1, ip, #1
	str	ip, [r5, r8, asl #2]
	add	r1, r1, r2
	add	r3, r3, lr
	stmib	r0, {r1, r3}
	ldr	r3, [r6, #4]
	mov	r1, #0
	add	r9, r9, #1
	add	r8, r8, #3
	add	r2, r3, r2
	str	r1, [fp, #-132]
	str	r2, [r6, #4]
	b	.L852
.L859:
	mov	r9, #0
	mov	r4, r9
	b	.L847
.L858:
	mov	r9, r7
	mov	r4, r7
	b	.L847
.L856:
	mvn	r0, #5
	b	.L868
	UNWIND(.fnend)
	.size	WriteScdMsg, .-WriteScdMsg
	.align	2
	.global	ScdDriver
	.type	ScdDriver, %function
ScdDriver:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 0
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
	ldr	r4, [fp, #12]
	mov	r5, r0
	mov	r6, r1
	mov	r7, r2
	mov	r9, r3
	mov	r0, r4
	ldr	r8, [fp, #8]
	bl	ResetSCD
	ldr	ip, [r5, #104]
	mov	r0, r6
	str	r4, [sp, #8]
	mov	r2, r9
	str	r8, [sp]
	mov	r1, r7
	str	ip, [sp, #4]
	ldr	r3, [fp, #4]
	bl	WriteScdMsg
	subs	r6, r0, #0
	bne	.L871
	ldr	r3, .L872
	ldr	r3, [r3]
	blx	r3
	ldr	r3, .L872+4
	mov	r2, #84
	mov	r1, r4
	mla	r4, r2, r4, r3
	str	r0, [r4, #68]
	mov	r0, r5
	bl	WriteScdVtrlReg
.L871:
	mov	r0, r6
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L873:
	.align	2
.L872:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VfmwGlobalStat
	UNWIND(.fnend)
	.size	ScdDriver, .-ScdDriver
	.align	2
	.global	CutStreamWithSCD
	.type	CutStreamWithSCD, %function
CutStreamWithSCD:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #172)
	sub	sp, sp, #172
	add	r9, r0, #98304
	cmn	r9, #128
	add	r2, r9, #128
	str	r2, [fp, #-176]
	mov	r4, r0
	ldr	r2, [r0, #56]
	movne	r7, #0
	moveq	r7, #1
	cmn	r0, #104
	str	r1, [fp, #-168]
	str	r2, [fp, #-172]
	movne	r5, #0
	ldr	r2, [r0, #80]
	moveq	r5, #1
	orrs	r3, r5, r7
	str	r2, [fp, #-184]
	add	r2, r0, #104
	str	r2, [fp, #-180]
	mov	r2, #0
	str	r2, [fp, #-160]
	bne	.L877
	add	r6, r0, #190464
	ldr	r8, .L900
	add	r6, r6, #184
	str	r3, [fp, #-164]
	mov	r1, r3
	mov	r2, #12
	mov	r0, r6
	ldr	r3, [r8, #48]
	blx	r3
	cmp	r5, #0
	bne	.L877
	ldr	r3, [r9, #104]
	mov	r0, #26
	ldr	r5, [r9, #108]
	ldr	r1, .L900+4
	subs	r5, r5, r3
	ldr	r3, [r8, #68]
	addmi	r5, r5, #1024
	mov	r2, r5
	blx	r3
	ldr	r2, [r9, #124]
	ldr	r3, [r9, #116]
	ldr	r1, .L900
	rsb	r10, r3, r2
	movs	r9, r10, asr #31
	beq	.L897
.L894:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L877:
	mvn	r9, #0
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L897:
	ldr	r3, [r1, #68]
	mov	r2, r10
	ldr	r1, .L900+8
	mov	r0, #26
	blx	r3
	cmp	r10, #3
	cmpgt	r5, #0
	ble	.L891
	cmp	r7, #0
	bne	.L877
	add	r5, r4, #188416
	ldr	r1, .L900+12
	mov	r0, #26
	ldr	r3, [r5, #2188]
	ldr	r7, [r5, #2184]
	subs	r7, r3, r7
	ldr	r3, [r8, #68]
	addmi	r7, r7, #1152
	rsb	r7, r7, #1152
	mov	r2, r7
	blx	r3
	cmp	r7, #288
	ble	.L888
	ldr	r0, [fp, #-176]
	sub	r2, fp, #164
	sub	r1, fp, #160
	bl	GetFreeSegBuf
	ldr	r1, [fp, #-160]
	ldr	r3, .L900
	mov	r0, #26
	ldr	r2, [fp, #-164]
	add	r1, r1, #3
	bic	r1, r1, #3
	str	r1, [fp, #-160]
	sub	r2, r2, #79
	ldr	r3, [r3, #68]
	str	r2, [fp, #-164]
	ldr	r1, .L900+16
	blx	r3
	ldr	r3, [r5, #2204]
	ldr	r2, [fp, #-164]
	cmp	r2, r3, lsr #3
	bls	.L888
	str	r3, [fp, #-188]
	ldr	r3, [r5, #2200]
	ldr	r1, [fp, #-168]
	ldr	r0, [r5, #2344]
	str	r3, [fp, #-176]
	bl	SM_CfgBuf
	subs	r3, r0, #0
	str	r3, [fp, #-192]
	ldr	r3, [fp, #-188]
	bne	.L898
	add	r2, r4, #200704
	str	r7, [r5, #2272]
	str	r2, [fp, #-188]
	mov	r1, r2
	mov	r2, #1
	str	r2, [r5, #2352]
	ldr	r0, [r1, #3948]
	ldr	r1, [fp, #-176]
	ldr	ip, [r5, #2252]
	add	r3, r3, r1
	str	r3, [fp, #-128]
	str	r1, [fp, #-132]
	ldr	r1, [fp, #-172]
	mul	r7, r0, r7
	sub	r3, r1, #16
	cmp	r1, r2
	cmpne	r3, r2
	ldr	r3, [fp, #-184]
	ldr	r0, [r5, #2248]
	sub	lr, r1, #6
	ldr	r1, [fp, #-160]
	clz	lr, lr
	str	r3, [fp, #-52]
	ldr	r3, [r5, #2260]
	mov	lr, lr, lsr #5
	str	r7, [fp, #-136]
	mov	r7, r7, asl #2
	str	r7, [r5, #2268]
	str	r3, [fp, #-144]
	ldr	r3, [r5, #2276]
	ldr	r7, [r5, #2288]
	strb	r2, [fp, #-154]
	str	r3, [fp, #-112]
	ldr	r3, [r5, #2300]
	ldr	r5, [r5, #2312]
	strb	r2, [fp, #-156]
	str	r0, [fp, #-152]
	str	ip, [fp, #-148]
	str	r1, [fp, #-124]
	str	r7, [fp, #-100]
	str	r3, [fp, #-88]
	str	r5, [fp, #-76]
	str	lr, [fp, #-48]
	bls	.L892
	cmp	lr, #0
	strneb	r2, [fp, #-155]
	ldrne	lr, [fp, #-172]
	beq	.L899
.L885:
	ldr	r1, [fp, #-168]
	str	r0, [sp, #4]
	sub	r0, fp, #156
	str	ip, [sp]
	mov	ip, #1
	str	r1, [sp, #8]
	mov	r1, r6
	ldr	r2, [fp, #-164]
	ldr	r3, [fp, #-180]
	str	lr, [fp, #-120]
	str	ip, [fp, #-116]
	bl	ScdDriver
	subs	r5, r0, #0
	movne	r9, r5
	bne	.L894
	ldr	r3, [fp, #-164]
	ldr	r6, [fp, #-188]
	cmp	r3, r10
	mov	r2, r6
	str	r3, [r6, #3924]
	str	r10, [r6, #3920]
	movlt	r2, #0
	movge	r2, #1
	strb	r5, [r4, #4]
	strb	r2, [r4, #2]
	ldr	r3, [r8]
	blx	r3
	str	r0, [r6, #3944]
	strb	r5, [r4, #3]
	b	.L894
.L888:
	mvn	r9, #5
	b	.L894
.L892:
	ldr	lr, [fp, #-192]
.L882:
	mov	r3, #0
	strb	r3, [fp, #-155]
	b	.L885
.L898:
	ldr	r3, .L900
	mov	r2, r0
	ldr	r1, .L900+20
	mov	r0, #26
	mov	r9, r2
	ldr	r3, [r3, #68]
	blx	r3
	b	.L894
.L891:
	mvn	r9, #4
	b	.L894
.L899:
	ldr	lr, [fp, #-172]
	sub	r3, lr, #2
	cmp	r3, r2
	bhi	.L882
	strb	r2, [fp, #-155]
	b	.L885
.L901:
	.align	2
.L900:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC82
	.word	.LC78
	.word	.LC81
	.word	.LC79
	.word	.LC80
	UNWIND(.fnend)
	.size	CutStreamWithSCD, .-CutStreamWithSCD
	.align	2
	.global	PrintScdStateReg
	.type	PrintScdStateReg, %function
PrintScdStateReg:
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
	ldr	r4, .L903
	mov	r5, r0
	mov	r2, r1
	mov	r0, #24
	ldr	r1, .L903+4
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r3, [r4, #68]
	ldr	r2, [r5]
	mov	r0, #24
	ldr	r1, .L903+8
	blx	r3
	ldr	r3, [r4, #68]
	ldr	r2, [r5, #4]
	mov	r0, #24
	ldr	r1, .L903+12
	blx	r3
	ldr	r3, [r4, #68]
	ldr	r2, [r5, #8]
	mov	r0, #24
	ldr	r1, .L903+16
	blx	r3
	ldr	r3, [r4, #68]
	ldr	r2, [r5, #12]
	mov	r0, #24
	ldr	r1, .L903+20
	blx	r3
	ldr	r3, [r4, #68]
	ldr	r2, [r5, #16]
	mov	r0, #24
	ldr	r1, .L903+24
	blx	r3
	ldr	r3, [r4, #68]
	ldr	r2, [r5, #20]
	mov	r0, #24
	ldr	r1, .L903+28
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L904:
	.align	2
.L903:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC83
	.word	.LC84
	.word	.LC85
	.word	.LC86
	.word	.LC87
	.word	.LC88
	.word	.LC89
	UNWIND(.fnend)
	.size	PrintScdStateReg, .-PrintScdStateReg
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
	mov	r4, r0
	movw	r0, #51264
	movt	r0, 63683
	mov	r6, r1
	bl	MEM_ReadPhyWord
	movw	r5, #51276
	movt	r5, 63683
	and	r3, r0, #1
	movw	r0, #51268
	str	r3, [r4]
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	and	r3, r0, #1
	mov	r0, r5
	str	r3, [r4, #4]
	bl	MEM_ReadPhyWord
	mov	r3, r0, lsr #22
	mov	r0, r5
	str	r3, [r4, #8]
	bl	MEM_ReadPhyWord
	ubfx	r3, r0, #0, #22
	movw	r0, #51280
	str	r3, [r4, #12]
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	str	r0, [r4, #16]
	movw	r0, #51284
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	mov	r1, r6
	str	r0, [r4, #20]
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	PrintScdStateReg
	UNWIND(.fnend)
	.size	ReadScdStateReg, .-ReadScdStateReg
	.align	2
	.global	GetNextVop
	.type	GetNextVop, %function
GetNextVop:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 32
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
	mov	r5, r0
	movw	r0, #51232
	mov	r8, r2
	movt	r0, 63683
	mov	r6, r3
	mov	r4, r1
	bl	MEM_ReadPhyWord
	ldr	r1, [fp, #4]
	sub	r0, fp, #68
	bl	ReadScdStateReg
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	mvneq	r9, #6
	movne	r9, #0
	cmp	r8, #0
	beq	.L908
	add	r2, r8, #90112
	ldr	r3, [r2, #2060]
	ldr	r2, [r2, #2056]
	subs	r3, r3, r2
	addmi	r3, r3, #1152
	rsb	r3, r3, #1152
	str	r3, [fp, #-72]
.L919:
	cmp	r9, #0
	bne	.L923
	subs	r1, r6, #1
	bmi	.L921
	add	r2, r5, #200704
	add	r3, r8, #90112
	mov	r6, #0
	mov	r0, r9
	ldr	r7, [r2, #3948]
	mov	r10, r6
	ldr	r5, [r5, #20]
	movt	r6, 65025
	ldr	r9, [r3, #2072]
	movt	r10, 46593
	mov	r7, r7, asl #2
	ldr	r8, [r8]
	mla	r4, r7, r1, r4
	b	.L918
.L926:
	cmp	r5, #2
	beq	.L925
	cmp	r2, r6
	beq	.L915
.L917:
	sub	r3, r1, #1
	rsb	r4, r7, r4
	cmn	r3, #1
	beq	.L924
	mov	r1, r3
.L918:
	ldr	r3, [r4]
	cmp	r5, #1
	rsb	r3, r9, r3
	add	r2, r8, r3
	ldrb	r3, [r8, r3]	@ zero_extendqisi2
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	ldrb	ip, [r2, #2]	@ zero_extendqisi2
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	add	r3, r3, lr, lsl #8
	add	ip, r3, ip, lsl #16
	add	r2, ip, r2, lsl #24
	rsbeq	r3, r10, r2
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
	bne	.L926
.L913:
	cmp	r2, r6
	beq	.L915
	cmp	r3, #1
	bne	.L917
.L915:
	add	r0, r0, #1
	cmp	r0, #0
	ble	.L917
	ldr	r3, [fp, #-72]
	cmp	r1, r3
	bhi	.L917
.L924:
	mov	r9, r1
.L923:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L925:
	ubfx	r3, r2, #16, #8
	sub	r3, r3, #128
	cmp	r3, #3
	movhi	r3, #0
	movls	r3, #1
	b	.L913
.L908:
	ldr	ip, .L927
	movw	r3, #3913
	ldr	r2, .L927+4
	mov	r0, #22
	ldr	r1, .L927+8
	ldr	r7, [ip, #68]
	blx	r7
	mov	r3, #1152
	str	r3, [fp, #-72]
	b	.L919
.L921:
	mov	r9, r6
	b	.L923
.L928:
	.align	2
.L927:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+352
	.word	.LC90
	UNWIND(.fnend)
	.size	GetNextVop, .-GetNextVop
	.global	__aeabi_uidiv
	.align	2
	.global	ProcessScdReturn
	.type	ProcessScdReturn, %function
ProcessScdReturn:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 264
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #276)
	sub	sp, sp, #276
	add	r3, r0, #188416
	str	r3, [fp, #-268]
	mov	r4, #0
	ldr	r3, [r3, #2240]
	mov	r10, r0
	mov	r5, r1
	str	r4, [fp, #-240]
	cmp	r3, #3
	str	r4, [fp, #-236]
	beq	.L1031
	movw	r0, #51232
	ldr	r9, .L1044
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	ip, [fp, #-268]
	ldr	r3, [r9, #48]
	mov	r1, #2
	mov	r2, #80
	sub	r0, fp, #204
	str	r1, [ip, #2240]
	mov	r1, r4
	blx	r3
	mov	r1, r4
	ldr	r3, [r9, #48]
	mov	r2, #80
	sub	r0, fp, #124
	blx	r3
	mov	r1, r4
	add	r4, r10, #200704
	ldr	r3, [r9, #48]
	mov	r2, #24
	sub	r0, fp, #228
	blx	r3
	ldr	r3, [r4, #3948]
	sub	r0, fp, #228
	mov	r1, r5
	str	r3, [fp, #-280]
	bl	ReadScdStateReg
	ldr	r3, [fp, #-212]
	cmp	r3, #0
	beq	.L1026
	ldr	r2, [fp, #-216]
	movw	r3, #34464
	movt	r3, 1
	add	r1, r10, #104
	cmp	r2, r3
	str	r1, [fp, #-288]
	str	r2, [fp, #-304]
	str	r2, [fp, #-244]
	bls	.L933
	ldr	r0, [r10, #56]
	cmp	r0, #0
	beq	.L1032
.L933:
	add	r3, r10, #98304
	str	r3, [fp, #-276]
	adds	r3, r3, #128
	str	r3, [fp, #-272]
	movw	r0, #51232
	ldrne	r3, [fp, #-268]
	movt	r0, 63683
	ldreq	r3, [fp, #-272]
	ldrne	r2, [r3, #2200]
	ldrne	r6, [r3, #2204]
	moveq	r6, r3
	streq	r3, [fp, #-260]
	strne	r2, [fp, #-260]
	bl	MEM_ReadPhyWord
	ldr	r3, [fp, #-244]
	cmp	r3, #1152
	movlt	r7, r3
	movge	r7, #1152
	and	r3, r0, #15
	movw	r0, #51212
	str	r3, [r10, #16]
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	r1, [fp, #-280]
	bl	__aeabi_uidiv
	cmp	r7, r0
	bhi	.L1033
	ldr	r3, [fp, #-244]
	cmp	r3, #1152
	movlt	r0, r3
	movge	r0, #1152
.L936:
	cmp	r0, r3
	str	r0, [r10, #40]
	bge	.L937
	ldrsb	r3, [r10, #2]
	cmp	r3, #1
	moveq	r3, #0
	streqb	r3, [r10, #2]
.L937:
	ldr	ip, [fp, #-268]
	add	r2, r10, #190464
	ldr	lr, [fp, #-260]
	mov	r1, r2
	add	r2, r1, #316
	add	r1, r10, #8
	ldr	r3, [ip, #2264]
	str	r2, [fp, #-264]
	mov	r7, r1
	str	r1, [fp, #-296]
	mov	r1, r2
	ldr	r2, [fp, #-276]
	str	lr, [r10, #28]
	str	r3, [r10, #12]
	ldr	r0, [fp, #-212]
	ldr	r3, [ip, #2200]
	ldr	r2, [r2, #128]
	rsb	r3, r3, lr
	str	r0, [r10, #36]
	str	r6, [r10, #32]
	add	r3, r2, r3
	ldr	r2, [fp, #-280]
	mov	r0, r7
	str	r3, [r10, #8]
	sub	r3, fp, #244
	ldr	ip, [ip, #2344]
	str	r2, [sp]
	sub	r2, fp, #232
	str	ip, [r10, #44]
	bl	ScdReturnSegFilter
	subs	r7, r0, #0
	bne	.L1026
	ldr	r6, [fp, #-244]
	cmp	r6, #1
	ble	.L1034
	movw	r0, #51212
	strb	r7, [r10]
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	r4, [fp, #-280]
	mov	r1, r4
	bl	__aeabi_uidiv
	cmp	r6, r0
	bcs	.L944
	ldr	r3, [fp, #-244]
	ldr	r2, [fp, #-264]
	sub	r3, r3, #1
	str	r3, [fp, #-300]
	str	r3, [fp, #-244]
	mul	r3, r4, r3
	add	r3, r3, #1
	ldr	r3, [r2, r3, asl #2]
	bic	r3, r3, #-2147483648
	str	r3, [fp, #-284]
.L945:
	ldr	r3, [r10, #56]
	cmp	r3, #2
	beq	.L1035
.L948:
	ldr	r3, [fp, #-268]
	mov	r8, #0
	mov	r7, r8
	str	r8, [fp, #-292]
	ldr	r5, [fp, #-264]
	ldr	r3, [r3, #2188]
	ldr	r1, [fp, #-300]
	str	r10, [fp, #-256]
	str	r3, [fp, #-308]
	ldr	r3, [fp, #-280]
	mov	r3, r3, asl #2
	str	r3, [fp, #-248]
	b	.L949
.L1039:
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	bne	.L1036
	ldr	r3, [fp, #-256]
	ldr	r3, [r3, #56]
	cmp	r3, #2
	beq	.L1037
.L958:
	ldr	r3, [fp, #-268]
	sub	r2, fp, #240
	str	r6, [fp, #-196]
	sub	r1, fp, #236
	ldr	r0, [fp, #-272]
	ldr	r3, [r3, #2200]
	str	r4, [fp, #-192]
	rsb	r6, r3, r6
	ldr	r3, [fp, #-276]
	ldr	r3, [r3, #128]
	add	r6, r3, r6
	mov	r3, #1
	str	r6, [fp, #-204]
	strb	r3, [fp, #-199]
	bl	GetFreeSegBuf
	ldr	r3, [fp, #-196]
	ldr	r2, [fp, #-240]
	cmp	r3, #0
	beq	.L959
	ldr	r3, [fp, #-204]
	cmp	r3, #0
	beq	.L959
	ldr	r3, [fp, #-192]
	cmp	r2, r3
	blt	.L959
	ldr	r3, [fp, #-256]
	ldr	r1, [r5, #4]
	add	r2, r3, #203776
	ldr	r0, [fp, #-288]
	add	r2, r2, #840
	sub	r3, fp, #204
	bic	r1, r1, #-2147483648
	bl	GetSegPts
	ldr	r3, [fp, #-268]
	sub	r1, fp, #204
	ldr	r0, [fp, #-272]
	ldr	r2, [r3, #2344]
	bl	InsertStreamSeg
	cmp	r0, #0
	bne	.L1025
	ldrd	r6, [fp, #-180]
	mov	r0, #26
	ldr	r2, [r5, #4]
	ldr	r3, [r9, #68]
	bic	r2, r2, #-2147483648
	ldr	r1, .L1044+4
	strd	r6, [sp]
	blx	r3
	ldrb	ip, [fp, #-199]	@ zero_extendqisi2
	ldr	r1, .L1044+8
	mov	r0, #26
	ldr	r3, [fp, #-192]
	ldr	r2, [fp, #-196]
	ldr	r4, [r9, #68]
	str	ip, [sp]
	blx	r4
	ldr	r1, [fp, #-244]
.L957:
	ldr	r3, [fp, #-248]
	ldr	r7, [fp, #-252]
	add	r5, r5, r3
	add	r8, r8, r3
.L949:
	cmp	r7, r1
	bge	.L1038
	ldr	r3, [fp, #-264]
	add	r0, r7, #1
	ldr	r2, [fp, #-248]
	ldr	r6, [r5]
	add	r2, r3, r2
	ldr	r3, [r5, #4]
	str	r0, [fp, #-252]
	ldr	r10, [r2, r8]
	mov	r3, r3, lsr #31
	strb	r3, [fp, #-197]
	ldr	r3, [fp, #-260]
	cmp	r10, r3
	rsbne	r4, r6, r10
	ldreq	r4, [fp, #-212]
	rsbeq	r4, r6, r4
	cmp	r4, #3
	bgt	.L1039
	sub	r3, r4, #1
	cmp	r3, #2
	bhi	.L961
	ldr	r3, [fp, #-256]
	ldr	r3, [r3, #56]
	cmp	r3, #2
	bne	.L957
	mov	r0, r10
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L1026
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	mov	r2, r2, asl #16
	orr	r3, r2, r3, asl #24
	orr	r3, r3, r1, asl #8
	cmp	r3, #256
	beq	.L1023
	mov	r2, r7
	ldr	r3, [fp, #-280]
	sub	r1, fp, #124
	ldr	r0, [fp, #-296]
	bl	ScdParseUpMsgInfo
	ldr	r3, [fp, #-268]
	ldr	r2, [fp, #-276]
	sub	r1, fp, #236
	ldr	r0, [fp, #-272]
	ldr	r3, [r3, #2200]
	ldr	ip, [r2, #128]
	sub	r2, fp, #240
	rsb	r3, r3, r6
	str	r6, [fp, #-116]
	add	r3, ip, r3
	str	r4, [fp, #-112]
	mov	ip, #1
	str	r3, [fp, #-124]
	strb	ip, [fp, #-119]
	bl	GetFreeSegBuf
	ldr	r3, [fp, #-256]
	ldr	r1, [r5, #4]
	add	r2, r3, #203776
	ldr	r0, [fp, #-288]
	bic	r1, r1, #-2147483648
	add	r2, r2, #840
	sub	r3, fp, #124
	bl	GetSegPts
	ldr	r1, [fp, #-244]
	b	.L957
.L1032:
	ldr	r1, .L1044+12
	movw	r2, #4067
	ldr	r4, [r9, #68]
	ldr	r3, [fp, #-304]
	blx	r4
	ldr	r0, [fp, #-288]
	mov	r1, #1
	bl	DeleteRawPacket
.L1026:
	mvn	r0, #6
.L1016:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1036:
	ldr	r3, [fp, #-112]
	sub	r2, fp, #240
	sub	r1, fp, #236
	ldr	r0, [fp, #-272]
	add	r4, r3, r4
	str	r4, [fp, #-112]
	bl	GetFreeSegBuf
	ldr	r3, [fp, #-116]
	ldr	r2, [fp, #-240]
	cmp	r3, #0
	beq	.L954
	ldr	r3, [fp, #-124]
	cmp	r3, #0
	beq	.L954
	ldr	r3, [fp, #-112]
	cmp	r2, r3
	blt	.L954
	ldr	r3, [fp, #-268]
	sub	r1, fp, #124
	ldr	r0, [fp, #-272]
	ldr	r6, .L1044
	ldr	r2, [r3, #2344]
	bl	InsertStreamSeg
	ldr	r3, [r9, #48]
	mov	r2, #80
	mov	r1, #0
	mov	r4, r0
	sub	r0, fp, #124
	blx	r3
	cmp	r4, #0
	bne	.L1040
	ldrd	r6, [fp, #-100]
	mov	r0, #26
	ldr	r3, .L1044
	ldr	r2, [r5, #4]
	ldr	r1, .L1044+16
	ldr	r3, [r3, #68]
	bic	r2, r2, #-2147483648
	strd	r6, [sp]
	blx	r3
	ldr	r3, [fp, #-112]
	ldr	r2, [fp, #-116]
	mov	r0, #26
	ldrb	ip, [fp, #-119]	@ zero_extendqisi2
.L1022:
	ldr	r1, .L1044
	ldr	r4, [r1, #68]
	ldr	r1, .L1044+8
	str	ip, [sp]
	blx	r4
.L1023:
	ldr	r1, [fp, #-244]
	b	.L957
.L959:
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L1044+20
	mov	r4, #1
	ldr	r10, [fp, #-256]
	blx	r3
	ldr	r3, [fp, #-284]
	mov	r0, #0
	ldr	r5, [r9, #68]
	ldr	r2, [fp, #-240]
	ldr	r1, .L1044+24
	blx	r5
	ldrb	r1, [fp, #-199]	@ zero_extendqisi2
	ldr	r3, [fp, #-192]
	mov	r0, #0
	ldr	r2, [fp, #-196]
	str	r1, [sp]
	ldr	r5, [r9, #68]
	ldr	r1, .L1044+8
	blx	r5
.L956:
	ldr	r3, [fp, #-268]
	ldr	r2, [fp, #-308]
	ldr	r3, [r3, #2188]
	cmp	r3, r2
	movne	r3, #1
	moveq	r3, #0
	cmp	r7, #0
	strb	r3, [r10, #3]
	ble	.L975
	ldr	r3, [fp, #-280]
	ldr	r0, [fp, #-288]
	mul	r7, r3, r7
	ldr	r3, [fp, #-264]
	add	r7, r7, #1
	ldr	r1, [r3, r7, asl #2]
	bic	r1, r1, #-2147483648
	bl	DeleteRawLen
	cmp	r0, #0
	bne	.L1026
.L976:
	cmp	r4, #1
	beq	.L1026
.L978:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L961:
	cmp	r4, #0
	bge	.L957
	ldr	r3, [fp, #-256]
	ldr	r3, [r3, #56]
	cmp	r3, #2
	beq	.L1041
.L963:
	ldr	r2, [fp, #-260]
	ldr	r1, [fp, #-276]
	rsb	r10, r2, r10
	ldr	r2, [fp, #-268]
	ldr	r3, [fp, #-212]
	ldr	r1, [r1, #128]
	ldr	r0, [r2, #2200]
	add	r3, r10, r3
	str	r6, [fp, #-196]
	sub	r2, fp, #240
	rsb	r0, r0, r6
	rsb	r6, r6, r3
	add	r3, r1, r0
	sub	r1, fp, #236
	ldr	r0, [fp, #-272]
	str	r3, [fp, #-204]
	mov	r3, #0
	str	r6, [fp, #-192]
	strb	r3, [fp, #-199]
	bl	GetFreeSegBuf
	ldr	r3, [fp, #-192]
	cmp	r3, #3
	ble	.L1023
	ldr	r3, [fp, #-272]
	cmp	r3, #0
	beq	.L965
	ldr	r3, [fp, #-268]
	ldr	r2, [r3, #2188]
	ldr	r3, [r3, #2184]
	subs	r3, r2, r3
	str	r3, [fp, #-292]
	addmi	r3, r3, #1152
	strmi	r3, [fp, #-292]
.L984:
	ldr	r0, [fp, #-196]
	ldr	r3, [fp, #-292]
	cmp	r0, #0
	ldr	r2, [fp, #-240]
	rsb	r3, r3, #1152
	str	r3, [fp, #-292]
	beq	.L967
	ldr	r3, [fp, #-204]
	cmp	r3, #0
	beq	.L967
	ldr	r3, [fp, #-192]
	cmp	r2, r3
	blt	.L967
	ldr	r2, [fp, #-292]
	cmp	r2, #1
	ble	.L1021
	ldr	r3, [fp, #-256]
	ldr	r1, [r5, #4]
	ldr	ip, [fp, #-212]
	add	r2, r3, #203776
	add	r2, r2, #840
	bic	r1, r1, #-2147483648
	rsb	ip, r0, ip
	sub	r3, fp, #204
	ldr	r0, [fp, #-288]
	str	ip, [fp, #-192]
	bl	GetSegPts
	ldr	r3, [fp, #-268]
	sub	r1, fp, #204
	ldr	r0, [fp, #-272]
	ldr	r2, [r3, #2344]
	bl	InsertStreamSeg
	subs	r6, r0, #0
	bne	.L1025
	ldrd	r2, [fp, #-180]
	mov	r0, #26
	ldr	r1, [r5, #4]
	ldr	ip, [r9, #68]
	strd	r2, [sp]
	bic	r2, r1, #-2147483648
	ldr	r1, .L1044+4
	blx	ip
	ldrb	ip, [fp, #-199]	@ zero_extendqisi2
	ldr	r3, [fp, #-192]
	mov	r0, #26
	ldr	r2, [fp, #-196]
	ldr	r1, .L1044+8
	str	ip, [sp]
	ldr	r4, [r9, #68]
	blx	r4
	ldr	r2, [fp, #-268]
	ldr	r1, [fp, #-276]
	ldr	lr, [fp, #-260]
	ldr	r3, [r2, #2200]
	ldr	ip, [r1, #128]
	sub	r1, fp, #204
	rsb	r3, r3, lr
	ldr	r2, [r2, #2344]
	ldr	r0, [fp, #-272]
	add	r3, ip, r3
	str	lr, [fp, #-196]
	mov	ip, #1
	str	r10, [fp, #-192]
	str	r3, [fp, #-204]
	strb	ip, [fp, #-199]
	bl	InsertStreamSeg
	ldr	r1, .L1044
	cmp	r0, #0
	bne	.L1042
	ldr	r3, [fp, #-192]
	mov	r0, #26
	ldr	r2, [fp, #-196]
	ldrb	ip, [fp, #-199]	@ zero_extendqisi2
	b	.L1022
.L954:
	ldr	r3, [r9, #68]
	movw	r2, #4253
	ldr	r1, .L1044+28
	mov	r0, #1
	ldr	r10, [fp, #-256]
	blx	r3
	ldr	r2, [fp, #-284]
	mov	r0, #1
	ldr	r3, [fp, #-240]
	ldr	r4, [r9, #68]
	str	r2, [sp]
	movw	r2, #4254
	ldr	r1, .L1044+32
	blx	r4
	ldr	r3, [fp, #-116]
	ldrb	ip, [fp, #-119]	@ zero_extendqisi2
	movw	r2, #4255
.L1024:
	ldr	r1, [fp, #-112]
	mov	r0, #1
	ldr	r5, [r9, #68]
	mov	r4, r0
	str	ip, [sp, #4]
	str	r1, [sp]
	ldr	r1, .L1044+36
	blx	r5
	b	.L956
.L1037:
	ldr	r3, [fp, #-280]
	mov	r2, r7
	sub	r1, fp, #204
	ldr	r0, [fp, #-296]
	bl	ScdParseUpMsgInfo
	b	.L958
.L1034:
	ldr	r3, [r4, #3924]
	ldr	r2, [r4, #3920]
	cmp	r2, r3
	strleb	r7, [r10]
	movgt	r3, #1
	strgtb	r3, [r10]
	cmp	r6, #0
	bne	.L942
	ldr	r3, [fp, #-268]
	ldr	r1, [r3, #2236]
	cmp	r1, #3
	subgt	r1, r1, #3
	movle	r1, r6
	b	.L943
.L975:
	ldr	r3, [fp, #-300]
	ldr	r2, [fp, #-304]
	clz	r3, r3
	cmp	r2, #1152
	mov	r3, r3, lsr #5
	movls	r3, #0
	cmp	r3, #0
	beq	.L976
	ldr	r3, [r10, #56]
	cmp	r3, #2
	bne	.L976
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L1044+40
	blx	r3
	ldr	r0, [fp, #-288]
	mov	r1, #1
	bl	DeleteRawPacket
	b	.L976
.L942:
	cmp	r6, #1
	movne	r1, #0
	beq	.L1043
.L943:
	ldr	r0, [fp, #-288]
	bl	DeleteRawLen
	cmp	r0, #0
	beq	.L978
	b	.L1026
.L967:
	ldr	r3, [fp, #-292]
	ldr	r10, [fp, #-256]
	cmp	r3, #1
	ldrle	r3, [fp, #-192]
	ble	.L985
	ldr	r3, [r9, #68]
	movw	r2, #4409
	ldr	r1, .L1044+28
	mov	r0, #1
	blx	r3
	ldr	r2, [fp, #-284]
	ldr	r3, [fp, #-240]
	mov	r0, #1
	ldr	r4, [r9, #68]
	str	r2, [sp]
	movw	r2, #4410
	ldr	r1, .L1044+32
	blx	r4
	ldr	r3, [fp, #-116]
	ldrb	ip, [fp, #-119]	@ zero_extendqisi2
	movw	r2, #4411
	b	.L1024
.L1033:
	movw	r0, #51212
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	r1, [fp, #-280]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-244]
	b	.L936
.L1038:
	ldr	r10, [fp, #-256]
	mov	r4, #0
	b	.L956
.L944:
	movw	r0, #51212
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	r4, [fp, #-280]
	mov	r1, r4
	rsb	r0, r4, r0
	bl	__aeabi_uidiv
	subs	r3, r0, #1
	str	r3, [fp, #-300]
	strmi	r7, [fp, #-244]
	mov	r2, r3
	movpl	r3, r4
	mulpl	r3, r3, r2
	strpl	r2, [fp, #-244]
	ldr	r2, [r10, #12]
	movmi	r3, #4
	strmi	r7, [fp, #-300]
	addpl	r3, r3, #1
	movpl	r3, r3, asl #2
	ldr	r3, [r2, r3]
	bic	r3, r3, #-2147483648
	str	r3, [fp, #-284]
	b	.L945
.L1041:
	ldr	r3, [fp, #-280]
	mov	r2, r7
	sub	r1, fp, #204
	ldr	r0, [fp, #-296]
	bl	ScdParseUpMsgInfo
	b	.L963
.L965:
	ldr	r4, [r9, #68]
	movw	r3, #4360
	ldr	r2, .L1044+44
	mov	r0, #22
	ldr	r1, .L1044+48
	blx	r4
	b	.L984
.L1035:
	str	r5, [sp]
	mov	r0, r10
	ldr	r3, [fp, #-300]
	ldr	r2, [fp, #-272]
	ldr	r1, [fp, #-264]
	bl	GetNextVop
	str	r0, [fp, #-300]
	str	r0, [fp, #-244]
	b	.L948
.L1031:
	ldr	r2, [fp, #-268]
	mov	r3, #2
	mvn	r0, #6
	str	r3, [r2, #2240]
	b	.L1016
.L1043:
	ldr	r2, [fp, #-268]
	ldr	r3, [r2, #2204]
	ldr	r1, [r2, #2368]
	ldr	r2, [r2, #2236]
	add	r3, r3, r3, lsl #1
	cmp	r3, #0
	add	r0, r3, #3
	rsb	r2, r1, r2
	movlt	r3, r0
	cmp	r2, r3, asr #2
	ble	.L943
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L1044+52
	blx	r3
	ldr	r3, [fp, #-268]
	ldr	r1, [r3, #2236]
	b	.L943
.L1025:
	ldrb	r1, [fp, #-199]	@ zero_extendqisi2
	mov	r0, #26
	ldr	r3, [fp, #-192]
	mov	r4, #0
	ldr	r2, [fp, #-196]
	str	r1, [sp]
	ldr	r5, [r9, #68]
	ldr	r1, .L1044+56
	ldr	r10, [fp, #-256]
	blx	r5
	b	.L956
.L1040:
	ldrb	r1, [fp, #-119]	@ zero_extendqisi2
	mov	r0, #26
	ldr	r5, [r6, #68]
	mov	r4, #0
	ldr	r3, [fp, #-112]
	str	r1, [sp]
	ldr	r2, [fp, #-116]
	ldr	r1, .L1044+56
	ldr	r10, [fp, #-256]
	blx	r5
	b	.L956
.L1042:
	ldrb	ip, [fp, #-199]	@ zero_extendqisi2
	mov	r0, #26
	ldr	r5, [r1, #68]
	mov	r4, r6
	ldr	r3, [fp, #-192]
	ldr	r2, [fp, #-196]
	ldr	r1, .L1044+56
	str	ip, [sp]
	ldr	r10, [fp, #-256]
	blx	r5
	b	.L956
.L1021:
	ldr	r10, [fp, #-256]
.L985:
	ldrb	ip, [fp, #-199]	@ zero_extendqisi2
	mov	r2, r0
	ldr	r5, [r9, #68]
	mov	r0, #26
	ldr	r1, .L1044+60
	mov	r4, #0
	str	ip, [sp]
	blx	r5
	b	.L956
.L1045:
	.align	2
.L1044:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC96
	.word	.LC95
	.word	.LC91
	.word	.LC94
	.word	.LC102
	.word	.LC103
	.word	.LC98
	.word	.LC99
	.word	.LC100
	.word	.LC101
	.word	.LANCHOR3+364
	.word	.LC104
	.word	.LC92
	.word	.LC93
	.word	.LC97
	UNWIND(.fnend)
	.size	ProcessScdReturn, .-ProcessScdReturn
	.align	2
	.global	PrintScdRawState
	.type	PrintScdRawState, %function
PrintScdRawState:
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
	mov	r7, r0
	mov	r0, #26
	mov	r6, r1
	bl	IsDprintTypeEnable
	cmp	r0, #0
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r2, .L1055
	mov	r3, r7, asl #6
	sub	r3, r3, r7, asl #4
	ldr	r5, .L1055+4
	add	r3, r2, r3
	ldr	r1, .L1055+8
	mov	r2, r7
	mov	r0, #26
	ldr	r10, [r3, #48]
	ldr	r3, [r5, #68]
	add	r8, r10, #98304
	blx	r3
	ldr	r3, [r5, #68]
	mov	r0, #26
	ldr	r2, [r8, #104]
	ldr	r1, .L1055+12
	blx	r3
	ldr	r2, [r8, #108]
	ldr	r3, [r5, #68]
	mov	r0, #26
	ldr	r1, .L1055+16
	blx	r3
	ldr	r2, [r8, #112]
	ldr	r3, [r5, #68]
	mov	r0, #26
	ldr	r1, .L1055+20
	blx	r3
	ldr	r2, [r8, #116]
	ldr	r3, [r5, #68]
	mov	r0, #26
	ldr	r1, .L1055+24
	blx	r3
	ldr	r2, [r8, #120]
	ldr	r3, [r5, #68]
	mov	r0, #26
	ldr	r1, .L1055+28
	blx	r3
	cmp	r6, #1
	beq	.L1048
.L1052:
	ldr	r3, [r5, #68]
	mov	r2, r7
	ldr	r1, .L1055+32
	mov	r0, #26
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L1048:
	cmn	r10, #104
	beq	.L1049
	ldr	r6, [r8, #104]
	ldr	r9, [r8, #108]
	subs	r9, r9, r6
	addmi	r9, r9, #1024
	cmp	r9, #0
	ble	.L1052
	mov	r4, r6, asl #7
	add	r9, r6, r9
	sub	r4, r4, r6, asl #5
	add	r4, r10, r4
.L1051:
	ldr	r2, [r4, #104]
	mov	r0, #26
	ldr	r3, [r5, #68]
	add	r6, r6, #1
	ldr	r1, .L1055+36
	add	r4, r4, #96
	blx	r3
	ldr	r2, [r4, #12]
	ldr	r3, [r5, #68]
	mov	r0, #26
	ldr	r1, .L1055+40
	blx	r3
	ldr	r2, [r4, #16]
	ldr	r3, [r5, #68]
	mov	r0, #26
	ldr	r1, .L1055+44
	blx	r3
	ldrd	r2, [r4, #24]
	ldr	r8, [r5, #68]
	mov	r0, #26
	ldr	r1, .L1055+48
	blx	r8
	cmp	r6, r9
	bne	.L1051
	b	.L1052
.L1049:
	ldr	r4, [r5, #68]
	movw	r3, #6626
	ldr	r2, .L1055+52
	mov	r0, #22
	ldr	r1, .L1055+56
	blx	r4
	b	.L1052
.L1056:
	.align	2
.L1055:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC105
	.word	.LC106
	.word	.LC107
	.word	.LC108
	.word	.LC109
	.word	.LC110
	.word	.LC111
	.word	.LC112
	.word	.LC113
	.word	.LC114
	.word	.LC115
	.word	.LANCHOR3+384
	.word	.LC10
	UNWIND(.fnend)
	.size	PrintScdRawState, .-PrintScdRawState
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
	ldr	r9, .L1100
	mov	r2, r0, asl #6
	mov	r3, r0, asl #4
	str	r3, [fp, #-152]
	rsb	r3, r3, r2
	add	r3, r9, r3
	ldr	r6, .L1100+4
	str	r2, [fp, #-156]
	mov	r5, r0
	ldr	r4, [r3, #48]
	mov	r2, #96
	mov	r1, #0
	sub	r0, fp, #140
	ldr	r3, [r6, #48]
	blx	r3
	cmp	r4, #0
	beq	.L1057
	ldr	r3, [r4, #56]
	cmp	r3, #19
	beq	.L1057
	mov	r3, r5, asl #24
	str	r3, [fp, #-148]
.L1074:
	ldr	r3, [fp, #-156]
	ldr	r2, [fp, #-152]
	rsb	r8, r2, r3
	add	r8, r9, r8
	b	.L1070
.L1099:
	ldr	r3, [r8, #48]
	cmp	r3, #0
	beq	.L1060
	add	r2, r3, #98304
	ldr	r3, [r2, #108]
	ldr	r1, [r2, #112]
	add	r3, r3, #1
	mov	r2, r3, asr #31
	mov	r2, r2, lsr #22
	add	r3, r3, r2
	ubfx	r3, r3, #0, #10
	rsb	r3, r2, r3
	cmp	r3, r1
	beq	.L1060
	sub	r1, fp, #140
	mov	r0, r5
	bl	ReadRawStreamData
	subs	r7, r0, #0
	bne	.L1057
	add	r10, r4, #200704
	ldr	r2, [fp, #-132]
	ldr	r1, [r6]
	ldr	r0, [r10, #3928]
	ldr	ip, [r10, #3952]
	add	r0, r0, r2
	str	r0, [r10, #3928]
	ldr	r0, [r10, #3956]
	add	r2, r2, ip
	str	r2, [r10, #3952]
	add	r2, r0, #1
	str	r2, [r10, #3956]
	blx	r1
	ldr	r1, [r10, #3932]
	cmp	r1, #0
	streq	r0, [r10, #3932]
	beq	.L1063
	rsb	r1, r1, r0
	cmp	r1, #2000
	bls	.L1063
	str	r0, [fp, #-144]
	ldr	r0, [r10, #3928]
	mov	r0, r0, asl #3
	bl	__aeabi_uidiv
	mov	r1, #1000
	ldr	r2, [fp, #-144]
	str	r7, [r10, #3928]
	str	r2, [r10, #3932]
	mul	r0, r1, r0
	mov	r0, r0, lsr #10
	str	r0, [r10, #3936]
.L1063:
	ldrd	r2, [fp, #-124]
	mov	r0, #29
	ldr	r7, [r6, #68]
	ldr	r1, .L1100+8
	blx	r7
	ldr	r3, [fp, #-132]
	ldr	r2, [fp, #-140]
	mov	r0, #26
	ldr	r1, .L1100+12
	ldr	r7, [r6, #68]
	blx	r7
	ldrd	r2, [fp, #-124]
	mov	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1094
.L1064:
	sub	r1, fp, #140
	mov	r0, r5
	bl	SM_PushRaw
	subs	r7, r0, #0
	bne	.L1095
	mov	r3, #1
	mov	r2, r7
	strb	r3, [r4, #4]
	mov	r1, r7
	mov	r0, r5
	bl	DBG_CountTimeInfo
	mov	r0, r7
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1096
.L1068:
	ldr	r7, .L1100+16
	ldr	r3, [r7, r5, asl #2]
	cmp	r3, #0
	bne	.L1097
.L1070:
	ldr	r3, [r4, #88]
	cmp	r3, #1
	beq	.L1098
.L1059:
	cmp	r5, #15
	bls	.L1099
.L1060:
	add	r4, r4, #188416
	ldr	r1, .L1100+20
	ldr	r3, [r6, #68]
	mov	r2, r5
	mov	r0, #23
	blx	r3
	mov	r1, #0
	ldr	r0, [r4, #2344]
	bl	PrintScdRawState
.L1057:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1098:
	add	r3, r4, #188416
	ldr	r3, [r3, #2224]
	cmp	r3, #8
	ble	.L1059
	b	.L1057
.L1096:
	ldr	r3, [r6]
	blx	r3
	add	ip, r9, r5, lsl #2
	ldr	r2, .L1100+24
	ldr	r3, [ip, #888]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	cmp	r3, r2
	bls	.L1068
	ldr	r7, .L1100+16
	movw	r1, #4649
	str	r0, [ip, #888]
	ldr	r2, [fp, #-148]
	ldr	r0, .L1100+28
	bl	DBG_AddTrace
	ldr	r3, [r7, r5, asl #2]
	cmp	r3, #0
	beq	.L1070
.L1097:
	ldr	r3, [r6, #16]
	mov	r0, #0
	ldr	r8, [r4, #56]
	blx	r3
	ldrb	r3, [fp, #-86]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1071
	sub	r3, r8, #4
	cmp	r3, #1
	bls	.L1072
	cmp	r8, #18
	cmpne	r8, #15
	beq	.L1072
	sub	r3, r8, #8
	cmp	r3, #5
	bls	.L1072
	cmp	r8, #1
	bne	.L1073
	ldr	r3, [r4, #72]
	cmp	r3, #1
	beq	.L1073
.L1072:
	ldr	r3, [r6, #44]
	mov	r1, #4
	ldr	r2, [r7, r5, asl #2]
	sub	r0, fp, #132
	blx	r3
.L1073:
	ldr	r2, [r7, r5, asl #2]
	ldr	r3, [r6, #44]
	ldr	r1, [fp, #-132]
	ldr	r0, [fp, #-136]
	blx	r3
.L1071:
	ldr	r3, [r6, #12]
	mov	r0, #0
	blx	r3
	b	.L1074
.L1094:
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [fp, #-124]
	b	.L1064
.L1095:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L1100+32
	blx	r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1101:
	.align	2
.L1100:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC116
	.word	.LC117
	.word	vfmw_save_str_file
	.word	.LC119
	.word	g_TraceBsPeriod
	.word	.LANCHOR3+404
	.word	.LC118
	UNWIND(.fnend)
	.size	FillRawData, .-FillRawData
	.align	2
	.global	SM_SeekPts
	.type	SM_SeekPts, %function
SM_SeekPts:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	ldr	r3, .L1211
	mov	r2, r0, asl #6
	str	r0, [fp, #-68]
	sub	r2, r2, r0, asl #4
	str	r1, [fp, #-80]
	add	r3, r3, r2
	ldr	r3, [r3, #48]
	cmp	r3, #0
	str	r3, [fp, #-64]
	beq	.L1105
	ldr	r3, [fp, #-64]
	add	r10, r3, #98304
	adds	r9, r10, #128
	beq	.L1105
	add	r5, r3, #188416
	ldr	r3, [fp, #-80]
	movw	r8, #36409
	ldr	r2, [r5, #2240]
	movt	r8, 14563
	ldrd	r0, [r3]
	ldr	r4, [r5, #2184]
	cmp	r2, #1
	ldr	ip, [r5, #2188]
	strd	r0, [fp, #-52]
	ldrd	r0, [r3, #8]
	str	r2, [fp, #-84]
	strd	r0, [fp, #-100]
	ldrd	r0, [r3, #16]
	moveq	r3, #3
	str	r4, [r5, #2192]
	streq	r3, [r5, #2240]
	strd	r0, [fp, #-76]
.L1107:
	mov	r6, r4, asl #4
	mov	r7, r4, asl #6
	cmp	r4, ip
	add	r3, r6, r7
	mov	r1, r4
	mov	r0, r9
	add	r3, r10, r3
	beq	.L1195
	ldrsb	r2, [r3, #140]
	cmp	r2, #1
	bne	.L1111
	ldrd	r2, [r3, #168]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	addeq	r1, r4, #1
	beq	.L1185
	ldrd	r0, [fp, #-52]
	add	lr, r4, #1
	cmp	r1, r3
	cmpeq	r0, r2
	smull	r0, r1, lr, r8
	strd	r0, [fp, #-60]
	mov	r1, lr, asr #31
	bls	.L1114
	ldr	r2, [fp, #-56]
	str	r4, [r5, #2192]
	rsb	r4, r1, r2, asr #8
	mov	r3, r4, asl #10
	add	r4, r3, r4, lsl #7
	rsb	r4, r4, lr
	b	.L1107
.L1111:
	bl	ReleaseStreamSeg
	ldr	ip, [r5, #2188]
	add	r1, r4, #1
.L1185:
	smull	r2, r3, r1, r8
	mov	r4, r1, asr #31
	rsb	r4, r4, r3, asr #8
	mov	r3, r4, asl #10
	add	r4, r3, r4, lsl #7
	rsb	r4, r4, r1
	b	.L1107
.L1114:
	beq	.L1196
	bcs	.L1107
	ldr	lr, [r5, #2192]
	mvn	r1, #0
	mvn	r0, #0
	mov	r3, lr, asl #6
	add	r3, r3, lr, lsl #4
	add	r3, r10, r3
	ldrd	r2, [r3, #168]
	cmp	r3, r1
	cmpeq	r2, r0
	streq	r4, [r5, #2192]
	moveq	lr, r4
	beq	.L1119
	ldrd	r0, [fp, #-52]
	cmp	r1, r3
	cmpeq	r0, r2
	bhi	.L1197
.L1119:
	ldr	r7, [r5, #2184]
	cmp	r7, lr
	beq	.L1120
	movw	r4, #36409
	mov	r6, #2
	movt	r4, 14563
.L1121:
	mov	r3, r7, asl #6
	mov	r1, r7
	add	r3, r3, r7, lsl #4
	mov	r0, r9
	add	r3, r10, r3
	strb	r6, [r3, #140]
	ldr	ip, [r3, #148]
	ldr	r2, [r5, #2220]
	ldr	r3, [r5, #2224]
	rsb	r2, ip, r2
	sub	r3, r3, #1
	bic	r2, r2, r2, asr #31
	str	r2, [r5, #2220]
	bic	r3, r3, r3, asr #31
	str	r3, [r5, #2224]
	bl	ReleaseStreamSeg
	add	r1, r7, #1
	ldr	lr, [r5, #2192]
	smull	r2, r3, r1, r4
	mov	r7, r1, asr #31
	rsb	r7, r7, r3, asr #8
	mov	r3, r7, asl #10
	add	r7, r3, r7, lsl #7
	rsb	r7, r7, r1
	cmp	lr, r7
	bne	.L1121
.L1120:
	mov	r3, lr, asl #6
	ldr	r1, [fp, #-80]
	add	r3, r3, lr, lsl #4
	mov	r0, #0
	add	r3, r10, r3
	ldrd	r2, [r3, #168]
	strd	r2, [r1]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1195:
	ldr	r6, [r5, #2184]
	cmp	r4, r6
	beq	.L1109
	movw	r4, #36409
	mov	r7, #2
	movt	r4, 14563
.L1110:
	mov	r3, r6, asl #6
	mov	r1, r6
	add	r3, r3, r6, lsl #4
	mov	r0, r9
	add	r3, r10, r3
	strb	r7, [r3, #140]
	ldr	ip, [r3, #148]
	ldr	r2, [r5, #2220]
	ldr	r3, [r5, #2224]
	rsb	r2, ip, r2
	sub	r3, r3, #1
	bic	r2, r2, r2, asr #31
	str	r2, [r5, #2220]
	bic	r3, r3, r3, asr #31
	str	r3, [r5, #2224]
	bl	ReleaseStreamSeg
	add	r1, r6, #1
	ldr	r0, [r5, #2188]
	smull	r2, r3, r1, r4
	mov	r6, r1, asr #31
	rsb	r6, r6, r3, asr #8
	mov	r3, r6, asl #10
	add	r6, r3, r6, lsl #7
	rsb	r6, r6, r1
	cmp	r0, r6
	bne	.L1110
.L1109:
	mov	r1, #0
	ldr	r0, [fp, #-68]
	bl	DeleteRawPacketInBuffer
	ldr	r3, [fp, #-64]
	adds	r3, r3, #104
	str	r3, [fp, #-92]
	beq	.L1105
	ldr	r9, [r10, #104]
	ldr	r8, [r10, #108]
	cmp	r9, r8
	str	r9, [r10, #112]
	addgt	r3, r8, #1024
	rsble	r3, r9, r8
	rsbgt	r3, r9, r3
	cmp	r9, r8
	str	r3, [fp, #-60]
	beq	.L1186
	mvn	r6, #0
	mvn	r7, #0
	mov	ip, r9
	ldr	lr, [fp, #-64]
	str	r5, [fp, #-88]
	b	.L1126
.L1200:
	str	ip, [r10, #112]
	mov	ip, r2, lsr #22
	add	r3, r3, ip
	ubfx	r3, r3, #0, #10
	rsb	ip, ip, r3
.L1131:
	cmp	r8, ip
	beq	.L1198
.L1126:
	mov	r3, ip, asl #7
	sub	r3, r3, ip, asl #5
	add	r3, lr, r3
	ldrd	r4, [r3, #120]
	add	r3, ip, #1
	cmp	r5, r7
	cmpeq	r4, r6
	beq	.L1199
	ldrd	r0, [fp, #-52]
	mov	r2, r3, asr #31
	cmp	r1, r5
	cmpeq	r0, r4
	bhi	.L1200
	beq	.L1201
	bcs	.L1131
	ldr	lr, [r10, #112]
	mvn	r2, #0
	strd	r4, [fp, #-60]
	ldr	r3, [fp, #-64]
	mov	r4, lr, asl #7
	ldr	r5, [fp, #-88]
	sub	r4, r4, lr, asl #5
	add	r4, r3, r4
	mvn	r3, #0
	ldrd	r6, [r4, #120]
	cmp	r7, r3
	cmpeq	r6, r2
	beq	.L1202
	ldrd	r0, [fp, #-52]
	cmp	r1, r7
	cmpeq	r0, r6
	bls	.L1139
	subs	r0, r0, r6
	ldrd	r2, [fp, #-100]
	sbc	r1, r1, r7
	cmp	r3, r1
	cmpeq	r2, r0
	bcc	.L1203
.L1139:
	cmp	r9, lr
	addgt	lr, lr, #1024
	rsb	r1, r9, lr
	cmp	r1, #0
	beq	.L1142
	ldr	r4, [r5, #2232]
	ldr	r3, [fp, #-84]
	cmp	r1, r4
	cmple	r3, #1
	moveq	r4, #1
	movne	r4, #0
	beq	.L1142
	ldr	r3, [fp, #-80]
	strd	r6, [r3]
.L1194:
	ldr	r3, [r10, #104]
	ldr	r0, [fp, #-92]
	str	r3, [r10, #112]
	bl	DeleteRawPacket
	mov	r1, r4
	ldr	r0, [fp, #-68]
	bl	DeleteRawPacketInBuffer
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1199:
	mov	ip, r3, asr #31
	mov	ip, ip, lsr #22
	add	r3, r3, ip
	ubfx	r3, r3, #0, #10
	rsb	ip, ip, r3
	cmp	r8, ip
	bne	.L1126
.L1198:
	cmp	r9, r8
	addgt	r8, r8, #1024
.L1186:
	rsb	r1, r9, r8
	str	r9, [r10, #112]
	cmp	r1, #0
	bne	.L1204
.L1129:
	ldr	r0, [fp, #-60]
	ldrd	r2, [fp, #-76]
	mov	r1, r0, asr #31
	cmp	r3, r1
	cmpeq	r2, r0
	bls	.L1205
	ldrd	r2, [fp, #-76]
	subs	r2, r2, r0
	movw	r0, #1023
	sbc	r3, r3, r1
	and	r0, r0, r2
	mov	r1, #0
	and	r1, r1, r3
	orrs	r1, r0, r1
	mov	r2, r2, lsr #10
	orrne	r2, r2, r3, asl #22
	orreq	r3, r2, r3, asl #22
	addne	r3, r2, #1
	str	r3, [fp, #-88]
	ldr	r3, [fp, #-88]
	cmp	r3, #0
	blt	.L1167
	ldr	r4, [fp, #-68]
	mov	r1, #0
	mov	r9, #0
	mvn	r5, #0
	mov	r0, r4
	bl	DeleteRawPacketInBuffer
	mov	r0, r4
	bl	FillRawData
	str	r9, [fp, #-84]
	ldrd	r6, [fp, #-52]
	mvn	r4, #0
	ldr	r9, [fp, #-64]
	str	r10, [fp, #-60]
.L1168:
	ldr	r3, [fp, #-60]
	ldr	r2, [r3, #104]
	ldr	r10, [r3, #108]
	mov	ip, r2
	str	r2, [fp, #-76]
	str	r2, [r3, #112]
.L1148:
	mov	r3, ip, asl #7
	cmp	ip, r10
	sub	r3, r3, ip, asl #5
	mvn	r0, #0
	mvn	r1, #0
	add	r3, r9, r3
	beq	.L1206
	ldrd	r2, [r3, #120]
	cmp	r3, r5
	cmpeq	r2, r4
	beq	.L1207
	cmp	r7, r3
	add	lr, ip, #1
	cmpeq	r6, r2
	mov	r8, lr, asr #31
	bls	.L1156
	ldr	r3, [fp, #-60]
	str	ip, [r3, #112]
	mov	ip, r8, lsr #22
	add	lr, lr, ip
	ubfx	lr, lr, #0, #10
	rsb	ip, ip, lr
	b	.L1148
.L1156:
	beq	.L1208
	bcs	.L1148
	ldr	r10, [fp, #-60]
	ldr	r5, [fp, #-64]
	ldr	r8, [fp, #-76]
	ldr	lr, [r10, #112]
	mov	r4, lr, asl #7
	sub	r4, r4, lr, asl #5
	add	r4, r5, r4
	ldrd	r4, [r4, #120]
	cmp	r5, r1
	cmpeq	r4, r0
	beq	.L1209
	ldrd	r0, [fp, #-52]
	cmp	r1, r5
	cmpeq	r0, r4
	bls	.L1162
	subs	r0, r0, r4
	ldrd	r6, [fp, #-100]
	sbc	r1, r1, r5
	cmp	r7, r1
	cmpeq	r6, r0
	strcc	ip, [r10, #112]
	movcc	r4, r2
	movcc	r5, r3
	movcc	lr, ip
.L1162:
	cmp	r8, lr
	ldr	r3, [fp, #-80]
	addgt	lr, lr, #1024
	rsb	r1, r8, lr
	cmp	r1, #0
	strd	r4, [r3]
	bne	.L1165
.L1193:
	ldr	r3, [r10, #104]
	mov	r0, r1
	str	r3, [r10, #112]
.L1184:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1207:
	add	r3, ip, #1
	mov	ip, r3, asr #31
	mov	ip, ip, lsr #22
	add	r3, r3, ip
	ubfx	r3, r3, #0, #10
	rsb	ip, ip, r3
	b	.L1148
.L1206:
	ldr	r3, [fp, #-76]
	ldr	r2, [fp, #-76]
	cmp	r3, ip
	addgt	ip, ip, #1024
	ldrgt	r3, [fp, #-76]
	rsb	r1, r3, ip
	ldr	r3, [fp, #-60]
	cmp	r1, #0
	str	r2, [r3, #112]
	bne	.L1210
.L1153:
	ldr	r3, [fp, #-84]
	ldr	r2, [fp, #-88]
	add	r3, r3, #1
	str	r3, [fp, #-84]
	cmp	r2, r3
	blt	.L1167
	ldr	r8, [fp, #-68]
	mov	r1, #0
	mov	r0, r8
	bl	DeleteRawPacketInBuffer
	mov	r0, r8
	bl	FillRawData
	b	.L1168
.L1208:
	ldr	r8, [fp, #-76]
	ldr	r0, [fp, #-80]
	cmp	r8, ip
	ldrd	r2, [fp, #-52]
	addgt	ip, ip, #1024
	ldr	r10, [fp, #-60]
	rsb	r1, r8, ip
	cmp	r1, #0
	strd	r2, [r0]
	beq	.L1193
.L1165:
	ldr	r3, [r10, #104]
	ldr	r0, [fp, #-92]
	str	r3, [r10, #112]
	bl	DeleteRawPacket
	ldr	r0, [fp, #-68]
	mov	r1, #0
	bl	DeleteRawPacketInBuffer
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1210:
	ldr	r0, [fp, #-92]
	bl	DeleteRawPacket
	mov	r1, #0
	ldr	r0, [fp, #-68]
	bl	DeleteRawPacketInBuffer
	b	.L1153
.L1201:
	cmp	r9, ip
	ldr	r5, [fp, #-88]
	addgt	ip, ip, #1024
	rsb	r1, r9, ip
	cmp	r1, #0
	beq	.L1136
	ldr	r4, [r5, #2232]
	ldr	r3, [fp, #-84]
	cmp	r1, r4
	cmple	r3, #1
	moveq	r4, #1
	movne	r4, #0
	beq	.L1136
	ldr	r0, [fp, #-80]
	ldrd	r2, [fp, #-52]
	strd	r2, [r0]
	b	.L1194
.L1204:
	ldr	r0, [fp, #-92]
	bl	DeleteRawPacket
	mov	r1, #0
	ldr	r0, [fp, #-68]
	bl	DeleteRawPacketInBuffer
	b	.L1129
.L1196:
	ldr	r8, [r5, #2184]
	cmp	r4, r8
	beq	.L1116
	movw	r3, #36409
	str	r6, [fp, #-52]
	movt	r3, 14563
	mov	r6, r5
	mov	r5, r3
.L1117:
	mov	r3, r8, asl #6
	mov	r2, #2
	add	r3, r3, r8, lsl #4
	mov	r1, r8
	add	r3, r10, r3
	mov	r0, r9
	strb	r2, [r3, #140]
	ldr	lr, [r3, #148]
	ldr	ip, [r6, #2220]
	ldr	r3, [r6, #2224]
	rsb	ip, lr, ip
	sub	r3, r3, #1
	bic	ip, ip, ip, asr #31
	str	ip, [r6, #2220]
	bic	r3, r3, r3, asr #31
	str	r3, [r6, #2224]
	bl	ReleaseStreamSeg
	add	ip, r8, #1
	smull	r0, r1, ip, r5
	mov	r8, ip, asr #31
	rsb	r8, r8, r1, asr #8
	mov	r3, r8, asl #10
	add	r8, r3, r8, lsl #7
	rsb	r8, r8, ip
	cmp	r4, r8
	bne	.L1117
	ldr	r6, [fp, #-52]
	add	r3, r6, r7
	add	r3, r10, r3
	ldrd	r2, [r3, #168]
.L1116:
	ldr	r1, [fp, #-80]
	mov	r0, #0
	strd	r2, [r1]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1136:
	ldr	r1, [fp, #-80]
	ldrd	r2, [fp, #-52]
	strd	r2, [r1]
.L1192:
	ldr	r3, [r10, #104]
	mov	r0, #0
	str	r3, [r10, #112]
	ldr	r3, [fp, #-84]
	str	r3, [r5, #2240]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1142:
	ldr	r3, [fp, #-80]
	strd	r6, [r3]
	b	.L1192
.L1209:
	str	ip, [r10, #112]
	mov	r4, r2
	mov	r5, r3
	mov	lr, ip
	b	.L1162
.L1197:
	subs	r0, r0, r2
	sbc	r1, r1, r3
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #-100]
	cmp	r1, r3
	cmpeq	r0, r2
	strcc	r4, [r5, #2192]
	movcc	lr, r4
	b	.L1119
.L1203:
	ldrd	r6, [fp, #-60]
	mov	lr, ip
	str	ip, [r10, #112]
	b	.L1139
.L1202:
	str	ip, [r10, #112]
	mov	lr, ip
	ldrd	r6, [fp, #-60]
	b	.L1139
.L1167:
	mvn	r0, #1
	b	.L1184
.L1105:
	mvn	r0, #0
	b	.L1184
.L1205:
	ldr	ip, .L1211+4
	strd	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1211+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #1
	b	.L1184
.L1212:
	.align	2
.L1211:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC120
	UNWIND(.fnend)
	.size	SM_SeekPts, .-SM_SeekPts
	.align	2
	.global	PrintScdSegState
	.type	PrintScdSegState, %function
PrintScdSegState:
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
	mov	r8, r0
	mov	r0, #26
	mov	r6, r1
	bl	IsDprintTypeEnable
	cmp	r0, #0
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r2, .L1222
	mov	r3, r8, asl #6
	sub	r3, r3, r8, asl #4
	ldr	r4, .L1222+4
	add	r3, r2, r3
	ldr	r1, .L1222+8
	mov	r2, r8
	mov	r0, #26
	ldr	r10, [r3, #48]
	ldr	r3, [r4, #68]
	add	r7, r10, #188416
	blx	r3
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r2, [r7, #2184]
	add	r5, r10, #98304
	ldr	r1, .L1222+12
	blx	r3
	ldr	r2, [r7, #2188]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+16
	blx	r3
	ldr	r2, [r7, #2196]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+20
	blx	r3
	ldr	r2, [r7, #2200]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+24
	blx	r3
	ldr	r2, [r5, #128]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+28
	blx	r3
	ldr	r2, [r7, #2204]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+32
	blx	r3
	ldr	r2, [r7, #2208]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+36
	blx	r3
	ldr	r2, [r7, #2212]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+40
	blx	r3
	cmp	r6, #1
	beq	.L1215
.L1219:
	ldr	r3, [r4, #68]
	mov	r2, r8
	ldr	r1, .L1222+44
	mov	r0, #26
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L1215:
	cmn	r5, #128
	beq	.L1216
	ldr	r6, [r7, #2184]
	ldr	r9, [r7, #2188]
	subs	r9, r9, r6
	addmi	r9, r9, #1152
	cmp	r9, #0
	ble	.L1219
	mov	r5, r6, asl #6
	add	r9, r6, r9
	add	r5, r5, r6, lsl #4
	add	r5, r5, #98304
	add	r5, r5, #144
	add	r5, r10, r5
.L1218:
	ldr	r2, [r5]
	mov	r0, #26
	ldr	r3, [r4, #68]
	add	r6, r6, #1
	ldr	r1, .L1222+48
	add	r5, r5, #80
	blx	r3
	ldr	r2, [r5, #-88]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+52
	blx	r3
	ldr	r2, [r5, #-76]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+56
	blx	r3
	ldr	r2, [r5, #-72]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+60
	blx	r3
	ldrsb	r2, [r5, #-84]
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+64
	blx	r3
	ldrb	r2, [r5, #-83]	@ zero_extendqisi2
	ldr	r3, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+68
	blx	r3
	ldrd	r2, [r5, #-64]
	ldr	r7, [r4, #68]
	mov	r0, #26
	ldr	r1, .L1222+72
	blx	r7
	cmp	r6, r9
	bne	.L1218
	b	.L1219
.L1216:
	ldr	r5, [r4, #68]
	movw	r3, #6676
	ldr	r2, .L1222+76
	mov	r0, #22
	ldr	r1, .L1222+80
	blx	r5
	b	.L1219
.L1223:
	.align	2
.L1222:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC121
	.word	.LC122
	.word	.LC123
	.word	.LC124
	.word	.LC125
	.word	.LC126
	.word	.LC127
	.word	.LC128
	.word	.LC129
	.word	.LC130
	.word	.LC131
	.word	.LC132
	.word	.LC133
	.word	.LC134
	.word	.LC135
	.word	.LC136
	.word	.LC137
	.word	.LANCHOR3+416
	.word	.LC138
	UNWIND(.fnend)
	.size	PrintScdSegState, .-PrintScdSegState
	.align	2
	.global	SetMaxSegSize
	.type	SetMaxSegSize, %function
SetMaxSegSize:
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
	mov	r4, r1
	mov	r5, r0
	bl	VCTRL_GetChanCapLevel
	cmp	r0, #32
	bhi	.L1233
	cmp	r0, #25
	beq	.L1234
	ldr	r3, [r4, #8]
	cmp	r3, #17
	cmpne	r3, #0
	bne	.L1229
	sub	r0, r0, #13
	cmp	r0, #19
	bhi	.L1229
	mov	r2, #1
	mov	r3, #2016
	mov	r0, r2, asl r0
	movt	r3, 8
	and	r3, r3, r0
	cmp	r3, #0
	bne	.L1231
	tst	r0, #31
	movne	r0, #4194304
	moveq	r0, #3145728
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1234:
	mov	r0, r5
	bl	VCTRL_GetChanWidth
	mov	r4, r0
	mov	r0, r5
	bl	VCTRL_GetChanHeight
	cmn	r0, #1
	cmnne	r4, #1
	beq	.L1235
	mul	r0, r0, r4
	mov	r3, #57344
	movt	r3, 31
	cmp	r0, r3
	bgt	.L1231
.L1229:
	mov	r0, #3145728
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1231:
	mov	r0, #20971520
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1233:
	ldr	r3, .L1236
	mov	r0, #0
	ldr	r1, .L1236+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1235:
	ldr	r3, .L1236
	mov	r0, #0
	ldr	r1, .L1236+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1237:
	.align	2
.L1236:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC139
	.word	.LC140
	UNWIND(.fnend)
	.size	SetMaxSegSize, .-SetMaxSegSize
	.align	2
	.global	SM_Config
	.type	SM_Config, %function
SM_Config:
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
	clz	r3, r1
	mov	r6, r0
	mov	r5, r1
	mov	r3, r3, lsr #5
	cmp	r0, #15
	orrhi	r3, r3, #1
	cmp	r3, #0
	bne	.L1257
	ldr	r2, .L1260
	mov	r3, r0, asl #6
	sub	r3, r3, r0, asl #4
	add	r3, r2, r3
	ldr	r10, [r3, #48]
	cmn	r2, #776
	cmpne	r10, #0
	beq	.L1244
	ldr	r1, [r1, #36]
	add	r7, r10, #200704
	str	r1, [r7, #3960]
	ldr	r1, [r5, #12]
	ldr	r0, [r10, #60]
	cmp	r0, r1
	beq	.L1258
	cmp	r1, #0
	beq	.L1244
	ldr	r1, [r5]
	cmp	r1, #0
	beq	.L1244
	ldr	r0, [r2, #784]
	add	r4, r10, #188416
	ldr	r1, [r2, #788]
	mov	ip, #1152
	str	ip, [r4, #2272]
	str	r0, [r4, #2248]
	ldr	ip, [r2, #792]
	ldr	r0, [r2, #796]
	str	r1, [r4, #2252]
	ldr	r1, [r2, #800]
	str	ip, [r4, #2256]
	str	r0, [r4, #2260]
	ldr	ip, [r2, #804]
	ldr	r0, [r2, #808]
	str	r1, [r4, #2264]
	ldr	r1, [r2, #812]
	str	ip, [r4, #2268]
	str	r0, [r4, #2300]
	ldr	ip, [r2, #816]
	ldr	r0, [r2, #820]
	str	r1, [r4, #2304]
	ldr	r1, [r2, #824]
	ldr	r2, [r2, #828]
	str	ip, [r4, #2308]
	str	r0, [r4, #2312]
	ldr	ip, [r3, #24]
	ldr	r0, [r3, #28]
	str	r1, [r4, #2316]
	str	r2, [r4, #2320]
	ldr	r1, [r3, #32]
	ldr	r2, [r3, #36]
	str	ip, [r4, #2276]
	str	r0, [r4, #2280]
	str	r1, [r4, #2284]
	mov	r1, r5
	str	r2, [r4, #2288]
	ldr	r2, [r3, #40]
	ldr	r3, [r3, #44]
	str	r2, [r4, #2292]
	str	r3, [r4, #2296]
	ldr	r2, [r5, #12]
	ldr	r3, [r5, #8]
	add	r0, r2, #3
	ldr	lr, [r5]
	cmp	r3, #6
	bic	r0, r0, #3
	rsb	r9, r2, r0
	movne	ip, #131072
	moveq	ip, #1048576
	mov	r8, ip
	add	r0, ip, r0
	add	ip, ip, r9
	str	r0, [r4, #2336]
	add	ip, lr, ip
	mov	r0, r6
	str	ip, [r4, #2244]
	bl	SetMaxSegSize
	ldr	r3, [r5, #16]
	rsb	r2, r9, r3
	cmn	r0, #1
	moveq	r0, #2097152
	cmp	r0, r2
	blt	.L1259
	rsb	r3, r8, r2
	sub	r3, r3, #1024
	str	r3, [r4, #2340]
	cmp	r3, #262144
	blt	.L1244
.L1248:
	ldr	r9, .L1260+4
	add	r0, r10, #98304
	add	r8, r10, #48
	ldr	r2, [r4, #2244]
	ldr	r1, [r4, #2336]
	add	r0, r0, #128
	bl	ConfigStreamSegArray
	ldr	r3, [r9, #52]
	mov	r0, r8
	mov	r2, #52
	mov	r1, r5
	blx	r3
	mov	r3, #0
	str	r3, [r4, #2348]
.L1243:
	ldr	r3, [r9, #52]
	mov	r0, r8
	mov	r2, #52
	mov	r1, r5
	blx	r3
	mov	r3, #2
	str	r3, [r7, #3948]
	mov	r0, #0
	ldr	r3, [r5, #8]
	cmp	r3, #2
	moveq	r3, #3
	streq	r3, [r7, #3948]
	str	r6, [r4, #2344]
.L1240:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1259:
	rsb	r3, r8, r0
	sub	r3, r3, #1024
	str	r3, [r4, #2340]
	b	.L1248
.L1258:
	add	r8, r10, #48
	add	r4, r10, #188416
	ldr	r9, .L1260+4
	b	.L1243
.L1244:
	mvn	r0, #0
	b	.L1240
.L1257:
	ldr	ip, .L1260+4
	mov	r3, r0
	str	r1, [sp]
	movw	r2, #2185
	ldr	r1, .L1260+8
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1240
.L1261:
	.align	2
.L1260:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC141
	UNWIND(.fnend)
	.size	SM_Config, .-SM_Config
	.align	2
	.global	SM_Reset
	.type	SM_Reset, %function
SM_Reset:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #204)
	sub	sp, sp, #204
	cmp	r0, #15
	mov	r5, r0
	bhi	.L1271
	mov	r3, r0, asl #6
	ldr	r9, .L1282
	sub	r3, r3, r0, asl #4
	add	r9, r9, r3
	ldr	r4, [r9, #48]
	cmp	r4, #0
	beq	.L1279
	ldr	r6, .L1282+4
	mov	r2, #52
	add	r1, r4, #48
	sub	r0, fp, #224
	add	ip, r4, #188416
	str	ip, [fp, #-232]
	ldr	r3, [r6, #52]
	add	r7, r4, #200704
	blx	r3
	ldr	ip, [fp, #-232]
	add	r10, r4, #203776
	ldr	r3, [r6, #52]
	add	r8, r10, #896
	sub	r0, fp, #172
	ldr	ip, [ip, #2360]
	mov	r2, #128
	mov	r1, r8
	str	ip, [fp, #-236]
	ldr	ip, [r7, #3964]
	str	ip, [fp, #-240]
	blx	r3
	ldr	r3, [r9, #48]
	cmp	r3, #0
	beq	.L1265
	add	r3, r3, #188416
	ldr	r2, [r3, #2360]
	cmp	r2, #0
	bne	.L1280
.L1265:
	adds	r9, r4, #104
	beq	.L1266
.L1281:
	add	r2, r4, #98304
	ldr	r3, [r2, #108]
	ldr	r1, [r2, #104]
	subs	r1, r3, r1
	addmi	r1, r1, #1024
.L1270:
	mov	r0, r9
	bl	DeleteRawPacket
	mov	r1, #1
	mov	r0, r5
	bl	DeleteRawPacketInBuffer
	ldr	r3, [r6, #48]
	mov	r2, #204800
	mov	r1, #0
	mov	r0, r4
	blx	r3
	add	lr, r10, #848
	mvn	r2, #0
	mvn	r3, #0
	mov	ip, #2
	strd	r2, [lr, #-8]
	sub	r1, fp, #224
	str	ip, [r7, #3948]
	mov	r0, r5
	bl	SM_Config
	ldr	r3, [fp, #-236]
	ldr	r2, [fp, #-232]
	sub	r1, fp, #172
	sub	r3, r3, #1
	mov	r0, r8
	cmp	r3, #1
	movls	r3, #1
	movhi	r3, #0
	str	r3, [r2, #2360]
	mov	r2, #128
	ldr	r3, [fp, #-240]
	str	r3, [r7, #3964]
	ldr	r3, [r6, #52]
	blx	r3
	mov	r0, #0
.L1278:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1280:
	ldr	r2, [r3, #2348]
	cmp	r2, #0
	movle	r2, #0
	strle	r2, [r3, #2360]
	adds	r9, r4, #104
	bne	.L1281
.L1266:
	ldr	r1, .L1282+8
	movw	r3, #1665
	ldr	r2, .L1282+12
	mov	r0, #22
	ldr	ip, [r6, #68]
	blx	ip
	mov	r1, r9
	b	.L1270
.L1271:
	mvn	r0, #0
	b	.L1278
.L1279:
	ldr	r3, .L1282+4
	mov	r0, r4
	mov	r2, #1632
	ldr	r1, .L1282+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1278
.L1283:
	.align	2
.L1282:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC143
	.word	.LANCHOR3+436
	.word	.LC142
	UNWIND(.fnend)
	.size	SM_Reset, .-SM_Reset
	.align	2
	.global	SM_DoNextInstance
	.type	SM_DoNextInstance, %function
SM_DoNextInstance:
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
	cmp	r0, #0
	str	r1, [fp, #-72]
	bne	.L1333
	ldr	r9, .L1341
	ldr	r3, [r9, #872]
	cmp	r3, #0
	bne	.L1334
	ldr	r4, [r9, #856]
	mov	r10, r3
	mov	r5, #16
	str	r3, [fp, #-80]
	str	r3, [fp, #-76]
.L1304:
	add	r3, r4, #1
	sub	r1, fp, #68
	mov	r4, r3, asr #31
	mov	r4, r4, lsr #28
	add	r3, r3, r4
	and	r3, r3, #15
	rsb	r4, r4, r3
	mov	r7, r4, asl #4
	mov	r6, r4, asl #6
	rsb	r3, r7, r6
	mov	r0, r4
	add	r3, r9, r3
	ldr	r8, [r3, #48]
	bl	SM_GetInfo
	ldrsb	r3, [fp, #-68]
	cmp	r3, #0
	beq	.L1289
	add	r3, r8, #188416
	ldr	r2, [r3, #2352]
	cmp	r2, #1
	beq	.L1289
	ldr	r2, [r8, #56]
	sub	r1, r2, #8
	cmp	r2, #5
	cmpne	r1, #1
	bls	.L1289
	cmp	r2, #1
	beq	.L1335
	sub	r1, r2, #10
	sub	r0, r2, #15
	cmp	r2, #4
	cmpne	r1, #3
	movls	r1, #1
	movhi	r1, #0
	bics	r0, r0, #4
	orreq	r1, r1, #1
	cmp	r1, #0
	bne	.L1289
	cmp	r2, #18
	beq	.L1336
.L1291:
	mov	r1, #0
	mov	r0, r4
	str	r3, [fp, #-84]
	bl	PrintScdRawState
	mov	r1, #0
	mov	r0, r4
	bl	PrintScdSegState
	ldr	r3, .L1341+4
	ldr	r2, [r3]
	blx	r2
	add	r1, r8, #200704
	ldr	r3, [fp, #-84]
	ldr	r2, [r1, #3944]
	subs	r2, r0, r2
	strmi	r0, [r1, #3944]
	ldrsb	ip, [r8, #2]
	movmi	r2, #200
	cmp	ip, #1
	beq	.L1337
.L1293:
	str	r0, [r1, #3944]
	ldrsb	r2, [r8]
	cmp	r2, #1
	movne	r3, #0
	strneb	r3, [r8, #1]
	beq	.L1338
.L1297:
	mov	r1, #0
	mov	r0, r8
	bl	CutStreamWithSCD
	cmn	r0, #6
	moveq	r3, #1
	streqb	r3, [r8]
	beq	.L1289
	cmp	r0, #0
	mov	r3, #0
	strb	r3, [r8]
	beq	.L1339
.L1289:
	subs	r5, r5, #1
	bne	.L1304
	b	.L1305
.L1334:
	cmp	r3, #1
	beq	.L1288
.L1305:
	mvn	r0, #2
.L1286:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1335:
	ldr	r2, [r8, #72]
	cmp	r2, #0
	bne	.L1291
	subs	r5, r5, #1
	bne	.L1304
	b	.L1305
.L1288:
	mov	r3, #2
	mvn	r0, #2
	str	r3, [r9, #872]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1336:
	mov	r0, r4
	bl	SM_CopyYuvToDnr
	cmp	r0, #0
	beq	.L1289
	ldr	r3, .L1341+4
	mov	r0, #26
	ldr	r1, .L1341+8
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1289
.L1339:
	ldr	r2, [fp, #-72]
	rsb	r3, r7, r6
	add	r3, r9, r3
	mov	r1, #1
	mov	r0, r4
	str	r4, [r2]
	ldr	r3, [r3, #48]
	cmp	r3, #0
	addne	r3, r3, #188416
	movne	r2, #1
	strne	r2, [r3, #2360]
	ldr	r2, [r8, #80]
	bl	DBG_CountTimeInfo
	mov	r0, #1
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1340
.L1331:
	mov	r0, #0
	b	.L1286
.L1337:
	cmp	r2, #500
	ldrsb	ip, [r8, #4]
	movge	r2, #0
	movlt	r2, #1
	cmp	ip, #0
	movne	r2, #0
	cmp	r2, #0
	bne	.L1289
	b	.L1293
.L1333:
	ldr	r3, .L1341+4
	mov	r2, r0
	ldr	r1, .L1341+12
	mov	r0, #26
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1286
.L1338:
	mov	r1, #0
	mov	r0, r4
	str	r3, [fp, #-92]
	add	r3, r8, #98304
	str	r2, [fp, #-88]
	str	r3, [fp, #-84]
	bl	PrintScdRawState
	ldr	r2, [fp, #-88]
	mov	r0, r4
	ldr	r3, [fp, #-84]
	mov	r1, r2
	add	r3, r3, #128
	str	r3, [fp, #-84]
	bl	PrintScdSegState
	ldr	r3, [fp, #-84]
	cmp	r3, #0
	ldr	r3, [fp, #-92]
	ldrne	r2, [r3, #2224]
	ldrne	r10, [r3, #2220]
	strne	r2, [fp, #-76]
	ldrne	r2, [r3, #2204]
	strne	r2, [fp, #-80]
	ldrsb	r2, [r8, #1]
	cmp	r2, #0
	bne	.L1296
	ldr	r3, [fp, #-80]
	ldr	r2, [fp, #-76]
	add	r3, r3, r3, lsr #31
	cmp	r10, r3, asr #1
	movlt	r3, #1
	movge	r3, #0
	cmp	r2, #127
	movgt	r3, #0
	andle	r3, r3, #1
	cmp	r3, #0
	beq	.L1297
	mov	r1, #1
	mov	r0, r4
	strb	r1, [r8, #1]
	bl	CalcInstBlockTime
	b	.L1297
.L1296:
	mov	r1, #0
	mov	r0, r4
	str	r3, [fp, #-88]
	bl	CalcInstBlockTime
	ldr	r3, [fp, #-88]
	cmp	r0, #1000
	mov	r2, r0
	ble	.L1297
	ldr	r0, [fp, #-80]
	cmp	r0, #0
	add	r1, r0, #3
	movge	r1, r0
	ldr	r0, [fp, #-76]
	cmp	r10, r1, asr #2
	movlt	r1, #1
	movge	r1, #0
	cmp	r0, #63
	movgt	r1, #0
	andle	r1, r1, #1
	cmp	r1, #0
	beq	.L1297
	orrs	r0, r0, r10
	bne	.L1298
	ldr	ip, [r3, #2184]
	ldr	r1, [r3, #2188]
	cmp	ip, r1
	beq	.L1298
	ldr	r3, .L1341+4
	ldr	r1, .L1341+16
	ldr	r2, [r3, #68]
	blx	r2
	ldr	r3, [fp, #-88]
	ldr	r0, [r3, #2344]
	bl	SM_Reset
.L1299:
	mov	r3, #0
	strb	r3, [r8, #1]
	strb	r3, [r8]
	b	.L1297
.L1340:
	ldr	r3, .L1341+4
	add	r9, r9, r4, lsl #2
	ldr	r3, [r3]
	blx	r3
	ldr	r2, .L1341+20
	ldr	r3, [r9, #952]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	mov	ip, r0
	cmp	r3, r2
	bls	.L1331
	mov	r2, r4, asl #24
	movw	r1, #5908
	add	r2, r2, #65536
	ldr	r0, .L1341+24
	str	ip, [r9, #952]
	bl	DBG_AddTrace
	b	.L1331
.L1298:
	ldr	r3, .L1341+4
	mov	r0, #0
	ldr	r1, .L1341+28
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r0, [fp, #-84]
	mvn	r1, #0
	bl	ReleaseStreamSeg
	b	.L1299
.L1342:
	.align	2
.L1341:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC145
	.word	.LC144
	.word	.LC146
	.word	g_TraceBsPeriod
	.word	.LANCHOR3+448
	.word	.LC147
	UNWIND(.fnend)
	.size	SM_DoNextInstance, .-SM_DoNextInstance
	.align	2
	.type	SCDDRV_ActivateSCD.part.7, %function
SCDDRV_ActivateSCD.part.7:
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
	sub	r1, fp, #24
	mov	r4, r0
	bl	SM_DoNextInstance
	cmp	r0, #0
	bne	.L1343
	mov	r2, r4, asl #7
	ldr	r3, .L1345
	sub	r4, r2, r4, asl #5
	ldr	r5, .L1345+4
	ldr	r2, [fp, #-24]
	add	r4, r3, r4
	mov	r3, #1
	str	r3, [r4, #860]
	str	r2, [r4, #856]
	ldr	r3, [r5]
	blx	r3
	ldr	r5, [r5, #68]
	movw	r3, #6308
	ldr	r2, .L1345+8
	ldr	r1, .L1345+12
	str	r0, [r4, #864]
	mov	r0, #26
	blx	r5
.L1343:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1346:
	.align	2
.L1345:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+468
	.word	.LC148
	UNWIND(.fnend)
	.size	SCDDRV_ActivateSCD.part.7, .-SCDDRV_ActivateSCD.part.7
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
	b	SCDDRV_ActivateSCD.part.7
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
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r5, .L1360
	mov	r4, #0
	b	.L1351
.L1350:
	add	r4, r4, #1
	cmp	r4, #16
	beq	.L1359
.L1351:
	ldr	r3, [r5, #40]
	add	r5, r5, #48
	cmp	r3, #0
	add	r2, r3, #188416
	beq	.L1350
	ldr	r3, [r2, #2360]
	cmp	r3, #1
	bne	.L1350
	mov	r0, r4
	add	r4, r4, #1
	bl	FillRawData
	cmp	r4, #16
	bne	.L1351
.L1359:
	ldr	r5, .L1360+4
	mov	r3, #1
	mov	r4, #0
	str	r3, [sp, #4]
	str	r4, [sp]
	movw	r3, #6368
	ldr	r6, [r5, #68]
	mov	r0, #26
	ldr	r2, .L1360+8
	ldr	r1, .L1360+12
	blx	r6
	mov	r0, r4
	bl	SCDDRV_CheckDevice
	subs	r6, r0, #0
	beq	.L1352
	str	r4, [sp]
	movw	r3, #6377
	ldr	r4, [r5, #68]
	mov	r0, #26
	ldr	r2, .L1360+8
	ldr	r1, .L1360+16
	blx	r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1352:
	str	r6, [sp]
	movw	r3, #6372
	ldr	r4, [r5, #68]
	mov	r0, #26
	ldr	r2, .L1360+8
	ldr	r1, .L1360+20
	blx	r4
	mov	r0, r6
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	SCDDRV_ActivateSCD.part.7
.L1361:
	.align	2
.L1360:
	.word	.LANCHOR0+8
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3+488
	.word	.LC149
	.word	.LC150
	.word	.LC151
	UNWIND(.fnend)
	.size	SM_Wakeup, .-SM_Wakeup
	.align	2
	.global	SM_SCDIntServeProc
	.type	SM_SCDIntServeProc, %function
SM_SCDIntServeProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r3, r0, #0
	bne	.L1390
	ldr	r5, .L1398
	ldr	r3, [r5, #12]
	blx	r3
	movw	r0, #51264
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ands	r0, r0, #1
	beq	.L1391
	ldr	r4, .L1398+4
	mov	r1, #1
	ldr	r0, [r4, #4]
	add	r0, r0, #2080
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	mov	r0, #2
	mov	r3, #1
	str	r3, [r4, #1016]
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1392
.L1388:
	ldr	r2, [r4, #856]
.L1367:
	mov	r3, r2, asl #6
	ldr	r0, [r4, #852]
	sub	r2, r3, r2, asl #4
	ldr	r3, .L1398+4
	add	r2, r4, r2
	ldr	r6, [r2, #48]
	cmp	r6, #0
	cmpne	r0, #0
	moveq	r7, #1
	movne	r7, #0
	beq	.L1393
	ldr	r8, .L1398+8
	ldr	r3, [r8, #68]
	cmp	r3, #0
	bne	.L1394
.L1370:
	ldr	r3, [r4, #860]
	ldr	r7, .L1398+4
	cmp	r3, #1
	beq	.L1395
.L1374:
	add	r6, r6, #200704
	mov	r0, #0
	str	r0, [r4, #1016]
	ldr	r3, [r6, #3960]
	cmp	r3, r0
	moveq	r0, r3
	ldr	r3, [r5, #132]
	blx	r3
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1391:
	ldr	r3, [r5, #16]
	blx	r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1390:
	ldr	r1, .L1398
	mov	r0, #0
	ldr	r2, .L1398+12
	str	r0, [sp]
	ldr	r4, [r1, #68]
	ldr	r1, .L1398+16
	blx	r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1394:
	ldr	r3, [r5]
	blx	r3
	ldr	r1, [r8, #64]
	ldr	r3, [r8, #68]
	add	r2, r1, #49920
	add	r2, r2, #80
	cmp	r2, r3
	strcc	r3, [r8, #64]
	movcc	r1, r3
	ldrcs	r7, [r8, #72]
	rsb	r1, r1, r0
	rsb	r3, r3, r0
	cmp	r1, #1000
	add	r0, r3, r7
	mov	r7, #0
	str	r0, [r8, #72]
	str	r7, [r8, #68]
	ldr	r8, .L1398+8
	bcc	.L1370
	mov	r3, #1000
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	str	r7, [r8, #64]
	str	r0, [r8, #76]
	b	.L1370
.L1395:
	add	r8, r6, #188416
	ldr	r3, [r8, #2360]
	cmp	r3, #1
	beq	.L1396
.L1375:
	mov	r7, #0
	sub	r1, fp, #40
	str	r7, [r8, #2352]
	mov	r0, r7
	bl	SM_DoNextInstance
	cmp	r0, r7
	strne	r7, [r4, #860]
	bne	.L1374
	ldr	r2, [fp, #-40]
	mov	r1, #1
	ldr	r3, [r5]
	str	r1, [r4, #860]
	str	r2, [r4, #856]
	blx	r3
	str	r0, [r4, #864]
	b	.L1374
.L1392:
	ldr	r3, [r5]
	blx	r3
	ldr	r2, [r4, #856]
	ldr	r3, .L1398+20
	add	ip, r4, r2, lsl #2
	ldr	r1, [r3]
	ldr	r3, [ip, #1020]
	rsb	r3, r3, r0
	mov	lr, r0
	cmp	r3, r1
	bls	.L1367
	mov	r2, r2, asl #24
	movw	r1, #6026
	add	r2, r2, #131072
	ldr	r0, .L1398+24
	str	lr, [ip, #1020]
	bl	DBG_AddTrace
	b	.L1388
.L1393:
	mov	r2, #0
	ldr	r1, [r5, #16]
	str	r2, [r3, #860]
	mov	r0, r2
	str	r2, [r3, #1016]
	blx	r1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1396:
	mov	r1, #0
	ldr	r0, [r7, #856]
	bl	PrintScdRawState
	mov	r1, #0
	ldr	r0, [r7, #856]
	bl	PrintScdSegState
	ldr	r0, [r7, #856]
	mov	r2, #0
	mov	r1, #2
	bl	DBG_CountTimeInfo
	mov	r1, #0
	mov	r0, r6
	bl	ProcessScdReturn
	ldr	r0, [r6, #88]
	cmp	r0, #1
	beq	.L1397
.L1377:
	ldr	r0, [r4, #856]
	mov	r1, #0
	bl	PrintScdRawState
	mov	r1, #0
	ldr	r0, [r4, #856]
	bl	PrintScdSegState
	b	.L1375
.L1397:
	adds	r7, r6, #104
	beq	.L1378
	add	r2, r6, #98304
	ldr	r3, [r2, #108]
	ldr	r2, [r2, #104]
	subs	r3, r3, r2
	addmi	r3, r3, #1024
.L1384:
	ldrsb	r7, [r6, #2]
	cmp	r7, #1
	bne	.L1377
	ldr	r2, [r6, #92]
	cmp	r2, r3
	bne	.L1377
	mov	r0, r6
	bl	SM_MoveRawData
	cmp	r0, #0
	beq	.L1377
	mov	r0, r7
	ldr	r3, [r5, #68]
	ldr	r1, .L1398+28
	blx	r3
	ldr	r0, [r8, #2344]
	bl	SM_Reset
	b	.L1377
.L1378:
	ldr	r3, [r5, #68]
	ldr	r1, .L1398+32
	blx	r3
	mov	r3, r7
	b	.L1384
.L1399:
	.align	2
.L1398:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	g_VfmwGlobalStat
	.word	.LANCHOR3+500
	.word	.LC152
	.word	g_TraceBsPeriod
	.word	.LANCHOR3+520
	.word	.LC153
	.word	.LC154
	UNWIND(.fnend)
	.size	SM_SCDIntServeProc, .-SM_SCDIntServeProc
	.align	2
	.global	get_scd_msg_size
	.type	get_scd_msg_size, %function
get_scd_msg_size:
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
	mov	r0, #716800
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	get_scd_msg_size, .-get_scd_msg_size
	.global	g_pSmIISBase
	.global	g_pScdDrvParamBase
	.global	s_RegPhyBaseAddr_1
	.global	s_RegPhyBaseAddr
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
	.type	__FUNCTION__.25352, %object
	.size	__FUNCTION__.25352, 17
__FUNCTION__.25352:
	.ascii	"GetRawNumOffsert\000"
	.space	3
	.type	__FUNCTION__.25440, %object
	.size	__FUNCTION__.25440, 17
__FUNCTION__.25440:
	.ascii	"ReleaseStreamSeg\000"
	.space	3
	.type	__func__.25491, %object
	.size	__func__.25491, 18
__func__.25491:
	.ascii	"SM_AllocDSPCtxMem\000"
	.space	2
	.type	__func__.25514, %object
	.size	__func__.25514, 14
__func__.25514:
	.ascii	"SM_OpenSCDDrv\000"
	.space	2
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
	.type	__func__.25814, %object
	.size	__func__.25814, 17
__func__.25814:
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
	.type	__func__.25841, %object
	.size	__func__.25841, 17
__func__.25841:
	.ascii	"FillEosRawStream\000"
	.space	3
	.type	__func__.25866, %object
	.size	__func__.25866, 14
__func__.25866:
	.ascii	"FillExtraData\000"
	.space	2
	.type	__func__.25982, %object
	.size	__func__.25982, 19
__func__.25982:
	.ascii	"SCDDRV_CheckDevice\000"
	.space	1
	.type	__FUNCTION__.25750, %object
	.size	__FUNCTION__.25750, 11
__FUNCTION__.25750:
	.ascii	"GetNextVop\000"
	.space	1
	.type	__FUNCTION__.25789, %object
	.size	__FUNCTION__.25789, 17
__FUNCTION__.25789:
	.ascii	"ProcessScdReturn\000"
	.space	3
	.type	__FUNCTION__.26049, %object
	.size	__FUNCTION__.26049, 17
__FUNCTION__.26049:
	.ascii	"PrintScdRawState\000"
	.space	3
	.type	__FUNCTION__.25803, %object
	.size	__FUNCTION__.25803, 12
__FUNCTION__.25803:
	.ascii	"FillRawData\000"
	.type	__FUNCTION__.26061, %object
	.size	__FUNCTION__.26061, 17
__FUNCTION__.26061:
	.ascii	"PrintScdSegState\000"
	.space	3
	.type	__FUNCTION__.25478, %object
	.size	__FUNCTION__.25478, 9
__FUNCTION__.25478:
	.ascii	"SM_Reset\000"
	.space	3
	.type	__FUNCTION__.25947, %object
	.size	__FUNCTION__.25947, 18
__FUNCTION__.25947:
	.ascii	"SM_DoNextInstance\000"
	.space	2
	.type	__func__.25988, %object
	.size	__func__.25988, 19
__func__.25988:
	.ascii	"SCDDRV_ActivateSCD\000"
	.space	1
	.type	__func__.26008, %object
	.size	__func__.26008, 10
__func__.26008:
	.ascii	"SM_Wakeup\000"
	.space	2
	.type	__func__.25972, %object
	.size	__func__.25972, 19
__func__.25972:
	.ascii	"SM_SCDIntServeProc\000"
	.space	1
	.type	__FUNCTION__.25973, %object
	.size	__FUNCTION__.25973, 19
__FUNCTION__.25973:
	.ascii	"SM_SCDIntServeProc\000"
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
	.word	908752
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
	.word	336598617
	.word	336598617
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
	.type	g_pSmIISBase, %object
	.size	g_pSmIISBase, 4
g_pSmIISBase:
	.word	s_SmIIS
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
	ASCII(.ascii	"Ignore the reset request when the SCD clock is clos" )
	ASCII(.ascii	"ed.\012\000" )
.LC6:
	ASCII(.ascii	"ResetSCD ERROR!!!\012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"line: %d Get SmID fail!\000" )
.LC8:
	ASCII(.ascii	"DelRaw err PacketNum=%d,DelNum=%d\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"Release RawPhyAddr=0x%x,Len=%d\012\000" )
.LC10:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum!!\012\000" )
.LC11:
	ASCII(.ascii	"line: %d DelNum = %d,RawPacketOffSet = %d,DelNum = " )
	ASCII(.ascii	"%d,Next Length = %d,is_extern_eop_flag = %d\012\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC12:
	ASCII(.ascii	"line: %d DelNum = %d,RawPacketOffSet = %d,Next Leng" )
	ASCII(.ascii	"th = %d\012\012\000" )
	.space	3
.LC13:
	ASCII(.ascii	"line: %d pSmInstArray is NULL!\012\000" )
.LC14:
	ASCII(.ascii	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLast" )
	ASCII(.ascii	"Seg=%d\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"-------- forece release seg[%d] -----------\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"0x%02x,\000" )
.LC18:
	ASCII(.ascii	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg" )
	ASCII(.ascii	"=%d StreamID=%d\012\000" )
.LC19:
	ASCII(.ascii	"Array out of bound in function %s\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"%s Alloc mem for DSP (SPS PPS) failed!\012\000" )
.LC22:
	ASCII(.ascii	"%s pDspSpsMsgMemVirAddr is NULL!\012\000" )
	.space	2
.LC23:
	ASCII(.ascii	"%s pDspPpsMsgMemVirAddr is NULL!\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"pstDSPMem->PhyAddr = 0 is not right address\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"ScdId is wrong! %s error\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"%s,line: %d\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"%s,line: %d,prt = NULL!\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"%s: pScdDrvParam->ScdDrvMem.pDvmMemVirAddr = NULL\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC29:
	ASCII(.ascii	"%s: pScdDrvParam->ScdDrvMem.pDspSedTopMemVirAddr = " )
	ASCII(.ascii	"NULL\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"%s: pScdDrvParam->ScdDrvMem.pDspCaMnMemVirAddr = NU" )
	ASCII(.ascii	"LL\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"%s: g_hex_base_vir_addr = NULL\012\000" )
.LC32:
	ASCII(.ascii	"line: %d, SmID = %d is not expected!\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"line: %d, SmID = %d, ScdId = %d is not expected!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC34:
	ASCII(.ascii	"Raw packet TOO BIG! can't copy to seg! Len: %#x\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC35:
	ASCII(.ascii	"line: %d, delet raw failed!\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"Raw packet(VFMW_RAW YUV) TOO BIG(maybe caused by w/" )
	ASCII(.ascii	"h... err)! can't copy to seg!\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"VFMW_RAW YUV disp w/h err)! discard raw packet!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC38:
	ASCII(.ascii	"copy raw to seg fail\012\000" )
	.space	2
.LC39:
	ASCII(.ascii	"***Print Up Msg Now\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"ScdUpMsg[%d] = 0x%x\012\000" )
	.space	3
.LC41:
	ASCII(.ascii	"%s: pRawPacket = NULL!\012\000" )
.LC42:
	ASCII(.ascii	"%s: unkown standard type = %d!\012\000" )
.LC43:
	ASCII(.ascii	"%s: Length(%d)+FlagLen(%d) > BufLen(%d)\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"%s: FlagLen(%d) > RawPacketLength(%d)\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"%s: RawPacket Length %d <= 0\012\000" )
	.space	2
.LC46:
	ASCII(.ascii	"%s(): Std(%d) buffer has no enough space,(act:%d, h" )
	ASCII(.ascii	"eader_buf:%d)\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"%s(): Std(%d) buffer has no enough space,(act:%d, s" )
	ASCII(.ascii	"tr_buf:%d)\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"%s(): Std(%d) buffer has no enough space,(act:%d, s" )
	ASCII(.ascii	"tr_buf:%d, header_buf:%d)\012\000" )
	.space	2
.LC49:
	ASCII(.ascii	"%s(): Std(%d) buffer has no enough space, (act:%d, " )
	ASCII(.ascii	"str_buf:%d)\012\000" )
.LC50:
	ASCII(.ascii	"Chan %d has been destroyed or the function pointer " )
	ASCII(.ascii	"-- ReleaseRawStreamData pStreamIntf is NULL!\000" )
.LC51:
	ASCII(.ascii	"line: %d s_SmIIS[%d].pSmInstArray is NULL\012\000" )
	.space	1
.LC52:
	ASCII(.ascii	"SmID = %d is not expected!\012\000" )
.LC53:
	ASCII(.ascii	"Chan %d has been destroyed or the function pointer " )
	ASCII(.ascii	"-- ReadRawStreamData pStreamIntf is NULL!\000" )
	.space	3
.LC54:
	ASCII(.ascii	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"Chan %d FillEosRawStream failed!\012\000" )
	.space	2
.LC56:
	ASCII(.ascii	"Chan %d FillExtraData failed!\012\000" )
	.space	1
.LC57:
	ASCII(.ascii	"Release this packet failed!\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"No space for raw move, total:%d+%d > max:%d!\012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"Error:now DspState[0]= %d,[1]= %d not except!!\012\000" )
.LC60:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) SCDState = %d\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return Idle!\012\000" )
	.space	3
.LC62:
	ASCII(.ascii	"SCD[%d] Time Out(%d ms), Reset SCD!\012\000" )
	.space	3
.LC63:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) really busy!\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"scd time out: t_start,t_now,t_wait = %d,%d,%d\012\000" )
	.space	1
.LC65:
	ASCII(.ascii	"***Print Scd[%d] Vtrl Reg Now\012\000" )
	.space	1
.LC66:
	ASCII(.ascii	"DownMsgPhyAddr = %x\012\000" )
	.space	3
.LC67:
	ASCII(.ascii	"UpMsgPhyAddr = %x\012\000" )
	.space	1
.LC68:
	ASCII(.ascii	"UpLen = %x\012\000" )
.LC69:
	ASCII(.ascii	"BufferFirst = %x\012\000" )
	.space	2
.LC70:
	ASCII(.ascii	"BufferLast = %x\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"BufferIni = %x\012\000" )
.LC72:
	ASCII(.ascii	"ScdProtocol = %x\012\000" )
	.space	2
.LC73:
	ASCII(.ascii	"ScdStart = %x\012\000" )
	.space	1
.LC74:
	ASCII(.ascii	"***Print SCD[%d] Down Msg Now\012\000" )
	.space	1
.LC75:
	ASCII(.ascii	"DownMsgVirAddr = %x   \012\000" )
.LC76:
	ASCII(.ascii	"DownMsgPhyAddr = %x   \012\000" )
.LC77:
	ASCII(.ascii	"DownMsg[%d] = %x   \000" )
.LC78:
	ASCII(.ascii	"RawStreamSize=%d\012\000" )
	.space	2
.LC79:
	ASCII(.ascii	"SegStreamSize=%d\012\000" )
	.space	2
.LC80:
	ASCII(.ascii	"SM_CfgBuf Err! ret =%d\012\000" )
.LC81:
	ASCII(.ascii	"SegStreamNum=%d\012\000" )
	.space	3
.LC82:
	ASCII(.ascii	"RawStreamNum=%d\012\000" )
	.space	3
.LC83:
	ASCII(.ascii	"***Print Scd[%d] State Reg\012\000" )
.LC84:
	ASCII(.ascii	"Scdover = %d \012\000" )
	.space	1
.LC85:
	ASCII(.ascii	"ScdInt = %d \012\000" )
	.space	2
.LC86:
	ASCII(.ascii	"ShortScdNum = %d \012\000" )
	.space	1
.LC87:
	ASCII(.ascii	"ScdNum = %d \012\000" )
	.space	2
.LC88:
	ASCII(.ascii	"ScdRollAddr = %0x \012\000" )
.LC89:
	ASCII(.ascii	"SrcEaten = %d \012\000" )
.LC90:
	ASCII(.ascii	"%s %d FMW_OK !=  GetSegStreamNum!!\012\000" )
.LC91:
	ASCII(.ascii	"line:%d ReadScdSegNum = %d, FilterScdSegNum = 0 rel" )
	ASCII(.ascii	"ease raw packet anyway!\012\000" )
.LC92:
	ASCII(.ascii	"Error! (PushRawTotalLen - SrcEaten) > SM_RAW_DISCAR" )
	ASCII(.ascii	"D_SIZE, packet discard...\012\000" )
	.space	2
.LC93:
	ASCII(.ascii	"Insert err Scd SegPacket.PhyAddr=0x%x,LenByte=%d,Is" )
	ASCII(.ascii	"LastSeg=%d\012\000" )
	.space	1
.LC94:
	ASCII(.ascii	"RawLen = %d, Pts = %ld, \012\000" )
	.space	2
.LC95:
	ASCII(.ascii	"Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d\012" )
	ASCII(.ascii	"\000" )
.LC96:
	ASCII(.ascii	"RawLen = %d, Pts =  %lld, \012\000" )
.LC97:
	ASCII(.ascii	"Insert 2 err Scd SegPacket.PhyAddr=0x%x,LenByte=%d," )
	ASCII(.ascii	"IsLastSeg=%d\012\000" )
	.space	3
.LC98:
	ASCII(.ascii	"line %d CheckSeg err\012\000" )
	.space	2
.LC99:
	ASCII(.ascii	"line %d SegFreeBufLen=%d,SrcEaten=%d\000" )
	.space	3
.LC100:
	ASCII(.ascii	"line %d Scd SegPacket.PhyAddr=0x%x,LenByte=%d,IsLas" )
	ASCII(.ascii	"tSeg=%d\012\000" )
.LC101:
	ASCII(.ascii	"ReadScdSegNum = %d, FilterScdSegNum = 0 release raw" )
	ASCII(.ascii	" packet anyway!\012\000" )
.LC102:
	ASCII(.ascii	"CheckSeg err\012\000" )
	.space	2
.LC103:
	ASCII(.ascii	"SegFreeBufLen=%d,SrcEaten=%d\000" )
	.space	3
.LC104:
	ASCII(.ascii	"%s %d FMW_OK != GetSegStreamNum!!\012\000" )
	.space	1
.LC105:
	ASCII(.ascii	"********** SmID [%d] RawState begin **********\012\000" )
.LC106:
	ASCII(.ascii	"RawHead=%d\012\000" )
.LC107:
	ASCII(.ascii	"RawTail=%d\012\000" )
.LC108:
	ASCII(.ascii	"RawHistory=%d\012\000" )
	.space	1
.LC109:
	ASCII(.ascii	"RawFirstPacketOffset=%d\012\000" )
	.space	3
.LC110:
	ASCII(.ascii	"CurShowIndex=%d\012\000" )
	.space	3
.LC111:
	ASCII(.ascii	"********** SmID [%d] RawState end   **********\012\000" )
.LC112:
	ASCII(.ascii	"RawPhyAddr=0x%x\012\000" )
	.space	3
.LC113:
	ASCII(.ascii	"RawVirAddr=0x%x\012\000" )
	.space	3
.LC114:
	ASCII(.ascii	"RawLength=%d\012\000" )
	.space	2
.LC115:
	ASCII(.ascii	"RawPts=%ld\012\000" )
.LC116:
	ASCII(.ascii	"raw_pts: %lld\012\000" )
	.space	1
.LC117:
	ASCII(.ascii	"Get RawPhyAddr=0x%x,Len=%d\012\000" )
.LC118:
	ASCII(.ascii	"!!!push raw err!!!\012\000" )
.LC119:
	ASCII(.ascii	"Chan%d raw full\012\000" )
	.space	3
.LC120:
	ASCII(.ascii	"RawNum %lld <= RawNumInVfmw %lld\012\000" )
	.space	2
.LC121:
	ASCII(.ascii	"********** SmID [%d] SegState begin **********\012\000" )
.LC122:
	ASCII(.ascii	"SegHead=%d\012\000" )
.LC123:
	ASCII(.ascii	"SegTail=%d\012\000" )
.LC124:
	ASCII(.ascii	"SegCurrent=%d\012\000" )
	.space	1
.LC125:
	ASCII(.ascii	"SegBufPhyAddr=%p\012\000" )
	.space	2
.LC126:
	ASCII(.ascii	"SegBufVirAddr=%p\012\000" )
	.space	2
.LC127:
	ASCII(.ascii	"SegBufSize=%d\012\000" )
	.space	1
.LC128:
	ASCII(.ascii	"SegBufReadAddr=%p\012\000" )
	.space	1
.LC129:
	ASCII(.ascii	"SegBufWriteAddr=%pd\012\000" )
	.space	3
.LC130:
	ASCII(.ascii	"********** SmID [%d] SegState end   **********\012\000" )
.LC131:
	ASCII(.ascii	"SegPhyAddr=0x%x\012\000" )
	.space	3
.LC132:
	ASCII(.ascii	"SegVirAddr=0x%x\012\000" )
	.space	3
.LC133:
	ASCII(.ascii	"SegLength=%d\012\000" )
	.space	2
.LC134:
	ASCII(.ascii	"SegStreamID=%d\012\000" )
.LC135:
	ASCII(.ascii	"SegState=%d\012\000" )
	.space	3
.LC136:
	ASCII(.ascii	"SegIsLastSeg=%d\012\000" )
	.space	3
.LC137:
	ASCII(.ascii	"SegPts=%lld\012\000" )
	.space	3
.LC138:
	ASCII(.ascii	"%s %d FMW_OK !=  GetSegStreamNum\012\000" )
	.space	2
.LC139:
	ASCII(.ascii	"SetMaxSegSize get eCapLevel failed!\012\000" )
	.space	3
.LC140:
	ASCII(.ascii	"SetMaxSegSize get ChanWidth/ChanHeight failed!\012\000" )
.LC141:
	ASCII(.ascii	"line: %d, SmID = %d, pSmCfg = %p is not expected!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC142:
	ASCII(.ascii	"line: %d, pSmInstArray is NULL!\012\000" )
	.space	3
.LC143:
	ASCII(.ascii	"%s %d FMW_OK !=  GetRawStreamNum !!\012\000" )
	.space	3
.LC144:
	ASCII(.ascii	"SM_DoNextInstance parm 1:scdId(%d) Error!\012\000" )
	.space	1
.LC145:
	ASCII(.ascii	"VFMW_RAW SM_CopyYuvToDnr fail\012\000" )
	.space	1
.LC146:
	ASCII(.ascii	"scd buffer is full, reset scd!\012\000" )
.LC147:
	ASCII(.ascii	"(%d ms) not release stream seg, release anyway!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC148:
	ASCII(.ascii	"%s,%d, active scd Success!\012\000" )
.LC149:
	ASCII(.ascii	"%s,%d, prepare to check SCD(%d) !(MAX_SCD_NUM = %d)" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC150:
	ASCII(.ascii	"%s,%d,SCD(ID = %d) return BUSY!!\012\000" )
	.space	2
.LC151:
	ASCII(.ascii	"%s,%d,find idle SCD(ID = %d)\012\000" )
	.space	2
.LC152:
	ASCII(.ascii	"%s: ScdId(%d) > %d\012\000" )
.LC153:
	ASCII(.ascii	"Move raw data failed, force to reset scd.\012\000" )
	.space	1
.LC154:
	ASCII(.ascii	"SCD GetRawStreamNum Fail.\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_hex_base_addr, %object
	.size	g_hex_base_addr, 4
g_hex_base_addr:
	.space	4
	.type	s_RegPhyBaseAddr, %object
	.size	s_RegPhyBaseAddr, 4
s_RegPhyBaseAddr:
	.space	4
	.type	s_SmIIS, %object
	.size	s_SmIIS, 768
s_SmIIS:
	.space	768
	.type	g_ScdDrvParam, %object
	.size	g_ScdDrvParam, 96
g_ScdDrvParam:
	.space	96
	.type	s_eScdDrvSleepStage, %object
	.size	s_eScdDrvSleepStage, 4
s_eScdDrvSleepStage:
	.space	4
	.type	s_RegPhyBaseAddr_1, %object
	.size	s_RegPhyBaseAddr_1, 4
s_RegPhyBaseAddr_1:
	.space	4
	.type	g_hex_base_vir_addr, %object
	.size	g_hex_base_vir_addr, 4
g_hex_base_vir_addr:
	.space	4
	.type	g_hex_len, %object
	.size	g_hex_len, 4
g_hex_len:
	.space	4
	.type	last_rec_pos_time.25798, %object
	.size	last_rec_pos_time.25798, 64
last_rec_pos_time.25798:
	.space	64
	.type	last_rec_pos_time.25943, %object
	.size	last_rec_pos_time.25943, 64
last_rec_pos_time.25943:
	.space	64
	.type	s_SCDInISR, %object
	.size	s_SCDInISR, 4
s_SCDInISR:
	.space	4
	.type	last_rec_pos_time.25971, %object
	.size	last_rec_pos_time.25971, 64
last_rec_pos_time.25971:
	.space	64
	.type	ForceRelease, %object
	.size	ForceRelease, 4
ForceRelease:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
