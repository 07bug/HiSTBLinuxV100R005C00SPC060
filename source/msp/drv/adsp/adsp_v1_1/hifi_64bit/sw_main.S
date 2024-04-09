#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"sw_main.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	AoEngineTask, %function
AoEngineTask:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x0, x30
	mov	w22, 4999
	mov	w23, 41999
	bl	_mcount
	ldr	x19, .LC0
	mov	x20, x19
	ldr	x0, [x20], 8
	bl	AOE_Init
	ldr	x0, [x20, 128]
	blr	x0
	strh	wzr, [x19, 240]
	strh	wzr, [x19, 242]
	str	xzr, [x19, 232]
	bl	AOE_SchedStatisticsInit
	mov	w0, 42405
	movk	w0, 0xa5a5, lsl 16
	str	w0, [x19, 244]
	.p2align 2
.L2:
	add	x21, x19, 8
	ldr	x0, [x21, 160]
	mov	x20, x21
	blr	x0
	cbnz	w0, .L9
.L7:
	ldr	x0, [x20, 112]
	blr	x0
	str	x0, [x19, 232]
	bl	AOE_ProcThread_Sw
	ldr	x0, [x20, 112]
	blr	x0
	ldr	x1, [x19, 232]
	sub	w0, w0, w1
	cmp	w0, w22
	bhi	.L10
.L3:
	bl	AOE_GetThreadStatus
	cmp	w0, 1
	beq	.L2
	ldr	x0, [x21, 112]
	blr	x0
	str	x0, [x19, 232]
	ldr	x1, [x21, 120]
	mov	w0, 19264
	movk	w0, 0x4c, lsl 16
	blr	x1
	ldr	x0, [x21, 112]
	blr	x0
	ldr	x1, [x19, 232]
	sub	w0, w0, w1
	cmp	w0, w23
	bls	.L2
	ldrh	w1, [x19, 240]
	mov	w0, 1
	add	x21, x19, 8
	add	w1, w1, w0
	mov	x20, x21
	uxth	w1, w1
	strh	w1, [x19, 240]
	bl	AOE_SchedStatisticsShow
	ldr	x0, [x21, 160]
	blr	x0
	cbz	w0, .L7
.L9:
	ldr	x0, [x21, 136]
	blr	x0
	bl	AOE_DeInit
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L10:
	ldrh	w1, [x19, 242]
	mov	w0, 0
	add	w1, w1, 1
	uxth	w1, w1
	strh	w1, [x19, 242]
	bl	AOE_SchedStatisticsShow
	b	.L3
	.size	AoEngineTask, .-AoEngineTask
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOE_SwEngineCreate
	.type	AOE_SwEngineCreate, %function
AOE_SwEngineCreate:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L18
	ldr	x21, .LC2
	add	x20, x21, 8
	mov	x0, x20
	str	wzr, [x21, 244]
	bl	ASDP_OSAL_InterfaceInit
	mov	x0, x21
	ldr	x2, .LC3
	ldr	x1, .LC5
	ldr	x3, [x20, 144]
	str	x19, [x0], 248
	blr	x3
	mov	w19, w0
	cbnz	w0, .L24
	bl	TIMER_Init
	mov	w22, 42405
	bl	TIMER_SetEnable
	movk	w22, 0xa5a5, lsl 16
	ldr	w0, [x21, 244]
	cmp	w0, w22
	beq	.L14
	ldr	x1, [x20, 32]
	mov	w0, 1
	mov	w19, 511
	mov	x23, x21
	blr	x1
	b	.L16
	.p2align 3
.L26:
	ldr	x1, [x20, 32]
	blr	x1
	subs	w19, w19, #1
	beq	.L25
.L16:
	ldr	w1, [x21, 244]
	add	x20, x23, 8
	mov	w0, 1
	cmp	w1, w22
	bne	.L26
.L14:
	mov	w0, 0
.L20:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L24:
	ldr	x1, [x20, 8]
	ldr	x0, .LC7
	blr	x1
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L25:
	ldr	x1, [x20, 8]
	ldr	x0, .LC9
	blr	x1
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L18:
	mov	w0, -1
	b	.L20
	.size	AOE_SwEngineCreate, .-AOE_SwEngineCreate
	.align	3
.LC2:
	.xword	.LANCHOR0
	.align	3
.LC3:
	.xword	AoEngineTask
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC9:
	.xword	.LC8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AOE_SwEngineDestory
	.type	AOE_SwEngineDestory, %function
AOE_SwEngineDestory:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x0, x30
	bl	_mcount
	bl	TIMER_SetDisable
	bl	TIMER_DeInit
	ldr	x19, .LC11
	ldr	x1, [x19, 160]
	ldr	x0, [x19, 248]
	blr	x1
	str	xzr, [x19]
	str	xzr, [x19, 248]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AOE_SwEngineDestory, .-AOE_SwEngineDestory
	.align	3
.LC11:
	.xword	.LANCHOR0
	.global	g_AdspOsalFunc
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC4:
	ASCII(.string	"AoEngineTask" )
	.zero	3
.LC6:
	ASCII(.string	"create sw AOE task failed\n" )
	.zero	5
.LC8:
	ASCII(.string	"sw AOE running delay more than 512ms\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_pDspReg, %object
	.size	g_pDspReg, 8
g_pDspReg:
	.zero	8
	.type	g_AdspOsalFunc, %object
	.size	g_AdspOsalFunc, 224
g_AdspOsalFunc:
	.zero	224
	.type	g_u64BeginPts, %object
	.size	g_u64BeginPts, 8
g_u64BeginPts:
	.zero	8
	.type	g_u16SchTimeoutCnt, %object
	.size	g_u16SchTimeoutCnt, 2
g_u16SchTimeoutCnt:
	.zero	2
	.type	g_u16ExcuteTimeoutCnt, %object
	.size	g_u16ExcuteTimeoutCnt, 2
g_u16ExcuteTimeoutCnt:
	.zero	2
	.type	g_AoeRunningFlag, %object
	.size	g_AoeRunningFlag, 4
g_AoeRunningFlag:
	.zero	4
	.type	g_pAOEThread, %object
	.size	g_pAOEThread, 8
g_pAOEThread:
	.zero	8
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
