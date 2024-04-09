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
	.file	"mem_manage.c"
	.text
	.align	2
	.global	MEM_InitMemManager
	.type	MEM_InitMemManager, %function
MEM_InitMemManager:
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
	subs	r5, r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r4, .L4
	mov	r0, #1
	ldr	r3, [r4, #12]
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #24576
	mov	r1, #0
	ldr	r0, .L4+4
	blx	r3
	ldr	r3, .L4+8
	ldr	lr, [r5]
	mov	r1, #0
	ldr	ip, [r5, #4]
	mov	r0, #1
	ldr	r2, [r4, #16]
	str	lr, [r3, #24]
	str	ip, [r3, #28]
	str	r1, [r3, #32]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r2
.L5:
	.align	2
.L4:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	MEM_InitMemManager, .-MEM_InitMemManager
	.align	2
	.global	MEM_ManagerWithOperation
	.type	MEM_ManagerWithOperation, %function
MEM_ManagerWithOperation:
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
	ldrne	r3, .L11
	ldrne	r1, [r0, #52]
	ldrne	r2, [r0, #56]
	strne	r1, [r3, #36]
	strne	r2, [r3, #40]
	ldmfd	sp, {fp, sp, pc}
.L12:
	.align	2
.L11:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	MEM_ManagerWithOperation, .-MEM_ManagerWithOperation
	.align	2
	.global	MEM_ManagerClearOperation
	.type	MEM_ManagerClearOperation, %function
MEM_ManagerClearOperation:
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
	ldr	r3, .L14
	mov	r2, #0
	str	r2, [r3, #36]
	str	r2, [r3, #40]
	ldmfd	sp, {fp, sp, pc}
.L15:
	.align	2
.L14:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	MEM_ManagerClearOperation, .-MEM_ManagerClearOperation
	.align	2
	.global	MEM_AddMemRecord
	.type	MEM_AddMemRecord, %function
MEM_AddMemRecord:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r4, r1
	mov	r5, r2
	mov	r6, r0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	beq	.L30
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L30:
	ldr	r7, .L33
	mov	r0, #1
	ldr	r3, [r7, #12]
	blx	r3
	ldr	lr, .L33+4
	ldr	r3, [lr, #16]
	cmp	r3, #0
	beq	.L18
	mov	r0, lr
	mov	r3, #1
	b	.L19
.L32:
	add	r3, r3, #1
	cmp	r3, #1024
	beq	.L31
.L19:
	ldr	ip, [r0, #40]
	add	r0, r0, #24
	cmp	ip, #0
	bne	.L32
.L18:
	mov	r2, r3, asl #5
	ldr	r1, [r7, #16]
	sub	r3, r2, r3, asl #3
	mov	r0, #1
	add	lr, lr, r3
	stmib	lr, {r4, r6}
	str	r5, [lr, #16]
	blx	r1
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L31:
	ldr	r3, [r7, #16]
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L34:
	.align	2
.L33:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MEM_AddMemRecord, .-MEM_AddMemRecord
	.align	2
	.global	MEM_DelMemRecord
	.type	MEM_DelMemRecord, %function
MEM_DelMemRecord:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r6, r1
	mov	r7, r2
	mov	r5, r0
	moveq	r4, #1
	movne	r4, #0
	cmp	r0, #0
	orreq	r4, r4, #1
	cmp	r4, #0
	beq	.L47
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L47:
	ldr	r8, .L49
	mov	r0, #1
	ldr	r3, [r8, #12]
	blx	r3
	ldr	r2, .L49+4
	mov	r0, r4
	mov	r3, r2
	b	.L38
.L37:
	add	r0, r0, #1
	add	r3, r3, #24
	cmp	r0, #1024
	beq	.L48
.L38:
	ldr	ip, [r3, #16]
	cmp	ip, #0
	beq	.L37
	ldr	lr, [r3, #8]
	cmp	lr, r5
	bne	.L37
	ldr	lr, [r3, #4]
	cmp	r6, lr
	cmpeq	r7, ip
	bne	.L37
	mov	r3, r0, asl #5
	mov	r4, #0
	sub	r0, r3, r0, asl #3
	ldr	r1, [r8, #16]
	add	r2, r2, r0
	mov	r0, #1
	str	r4, [r2, #16]
	str	r4, [r2, #8]
	str	r4, [r2, #4]
	blx	r1
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L48:
	ldr	r3, [r8, #16]
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L50:
	.align	2
.L49:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MEM_DelMemRecord, .-MEM_DelMemRecord
	.align	2
	.global	MEM_Phy2Vir
	.type	MEM_Phy2Vir, %function
MEM_Phy2Vir:
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
	ldr	lr, .L60
	mov	r1, #0
	mov	r3, lr
	b	.L54
.L52:
	add	r1, r1, #1
	add	r3, r3, #24
	cmp	r1, #1024
	beq	.L59
.L54:
	ldr	r2, [r3, #16]
	cmp	r2, #0
	beq	.L52
	ldr	ip, [r3, #8]
	cmp	ip, r0
	add	r2, ip, r2
	bhi	.L52
	cmp	r0, r2
	bcs	.L52
	mov	r3, r1, asl #5
	rsb	r0, ip, r0
	sub	r1, r3, r1, asl #3
	add	lr, lr, r1
	ldr	r3, [lr, #4]
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L59:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L61:
	.align	2
.L60:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MEM_Phy2Vir, .-MEM_Phy2Vir
	.align	2
	.global	MEM_Vir2Phy
	.type	MEM_Vir2Phy, %function
MEM_Vir2Phy:
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
	ldr	lr, .L71
	mov	r1, #0
	mov	r3, lr
	b	.L65
.L63:
	add	r1, r1, #1
	add	r3, r3, #24
	cmp	r1, #1024
	beq	.L70
.L65:
	ldr	r2, [r3, #16]
	cmp	r2, #0
	beq	.L63
	ldr	ip, [r3, #4]
	cmp	ip, r0
	add	r2, ip, r2
	bhi	.L63
	cmp	r0, r2
	bcs	.L63
	mov	r3, r1, asl #5
	rsb	r0, ip, r0
	sub	r1, r3, r1, asl #3
	add	lr, lr, r1
	ldr	r3, [lr, #8]
	add	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
.L70:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L72:
	.align	2
.L71:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MEM_Vir2Phy, .-MEM_Vir2Phy
	.align	2
	.global	MEM_WritePhyWord
	.type	MEM_WritePhyWord, %function
MEM_WritePhyWord:
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
	bl	MEM_Phy2Vir
	cmp	r0, #0
	strne	r4, [r0]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MEM_WritePhyWord, .-MEM_WritePhyWord
	.align	2
	.global	MEM_ReadPhyWord
	.type	MEM_ReadPhyWord, %function
MEM_ReadPhyWord:
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
	ldrne	r0, [r0]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MEM_ReadPhyWord, .-MEM_ReadPhyWord
	.align	2
	.global	MEM_AllocMemBlock
	.type	MEM_AllocMemBlock, %function
MEM_AllocMemBlock:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 24
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
	cmp	r2, #0
	cmpne	r3, #0
	mov	r5, r3
	mov	r9, r2
	moveq	r4, #1
	movne	r4, #0
	cmp	r0, #0
	orreq	r4, r4, #1
	mov	r8, r0
	cmp	r4, #0
	bne	.L90
	ldr	r6, .L94
	sub	r7, fp, #68
	ldr	r10, [r3, #20]
	mov	r1, r4
	mov	r2, #24
	mov	r0, r3
	ldr	r3, [r6, #48]
	blx	r3
	mov	r1, r4
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r0, r7
	blx	r3
	mov	r1, r9
	ldr	r3, [fp, #4]
	mov	r2, #4
	str	r10, [fp, #-48]
	mov	r0, r8
	str	r7, [sp]
	ldr	r4, [r6, #144]
	blx	r4
	ldrd	r2, [fp, #-60]
	orrs	r1, r2, r3
	beq	.L90
	ldr	r1, [fp, #-48]
	ldr	r0, [fp, #-68]
	ldr	ip, [fp, #-64]
	ldr	lr, [fp, #-52]
	cmp	r1, #3
	ldrls	pc, [pc, r1, asl #2]
	b	.L90
.L86:
	.word	.L85
	.word	.L87
	.word	.L87
	.word	.L88
.L88:
	cmp	ip, #0
	cmpne	r2, #0
	beq	.L90
.L89:
	ldr	r1, .L94+4
	mov	r0, #0
	stmib	r5, {r2, ip}
	str	lr, [r5, #16]
	ldr	r3, [r1, #32]
	add	r3, r3, #3
	add	r3, r3, lr
	bic	r3, r3, #3
	str	r3, [r1, #32]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L87:
	cmp	r0, #0
	cmpne	ip, #0
	moveq	r0, #1
	movne	r0, #0
	cmp	r2, #0
	orreq	r0, r0, #1
	cmp	r0, #0
	beq	.L89
.L90:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L85:
	cmp	r0, #0
	cmpne	r2, #0
	beq	.L90
	mov	ip, r0
	b	.L89
.L95:
	.align	2
.L94:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	MEM_AllocMemBlock, .-MEM_AllocMemBlock
	.align	2
	.global	MEM_MapRegisterAddr
	.type	MEM_MapRegisterAddr, %function
MEM_MapRegisterAddr:
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
	mov	r7, r0
	mov	r6, r1
	mov	r5, r2
	moveq	r4, #1
	movne	r4, #0
	cmp	r2, #0
	orreq	r4, r4, #1
	cmp	r4, #0
	bne	.L99
	ldr	r8, .L103
	mov	r2, #24
	mov	r1, r4
	mov	r0, r5
	ldr	r3, [r8, #48]
	blx	r3
	ldr	r3, [r8, #152]
	mov	r1, r6
	mov	r0, r7
	blx	r3
	subs	r3, r0, #0
	beq	.L99
	mov	r0, r4
	stmib	r5, {r3, r7}
	str	r6, [r5, #16]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L99:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L104:
	.align	2
.L103:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MEM_MapRegisterAddr, .-MEM_MapRegisterAddr
	.align	2
	.global	MEM_UnmapRegisterAddr
	.type	MEM_UnmapRegisterAddr, %function
MEM_UnmapRegisterAddr:
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
	ldr	r3, .L107
	mov	r0, r1
	ldr	r3, [r3, #156]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L108:
	.align	2
.L107:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MEM_UnmapRegisterAddr, .-MEM_UnmapRegisterAddr
	.align	2
	.global	MEM_ReleaseMemBlock
	.type	MEM_ReleaseMemBlock, %function
MEM_ReleaseMemBlock:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r7, r1
	moveq	r5, #1
	movne	r5, #0
	bne	.L118
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L118:
	ldr	r6, .L119
	mov	r2, #24
	mov	r1, r5
	sub	r0, fp, #52
	ldr	r3, [r6, #48]
	blx	r3
	ldr	r3, .L119+4
	str	r4, [fp, #-52]
	add	r0, r3, #24576
	str	r7, [fp, #-44]
	str	r5, [fp, #-40]
	b	.L113
.L111:
	add	r3, r3, #24
	cmp	r3, r0
	beq	.L112
.L113:
	ldr	r2, [r3, #16]
	cmp	r2, #0
	beq	.L111
	ldr	r1, [r3, #8]
	cmp	r4, r1
	add	ip, r1, r2
	bcc	.L111
	cmp	r4, ip
	bcs	.L111
	str	r2, [fp, #-36]
.L112:
	ldr	r3, [r6, #148]
	sub	r0, fp, #52
	blx	r3
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L120:
	.align	2
.L119:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MEM_ReleaseMemBlock, .-MEM_ReleaseMemBlock
	.global	mem_free
	.global	mem_malloc
	.global	s_MemRecord
	.bss
	.align	2
.LANCHOR0 = . + 0
.LANCHOR1 = . + 24552
	.type	s_MemRecord, %object
	.size	s_MemRecord, 24576
s_MemRecord:
	.space	24576
	.type	s_MemBaseAddr, %object
	.size	s_MemBaseAddr, 4
s_MemBaseAddr:
	.space	4
	.type	s_MemSize, %object
	.size	s_MemSize, 4
s_MemSize:
	.space	4
	.type	s_MemOffset, %object
	.size	s_MemOffset, 4
s_MemOffset:
	.space	4
	.type	mem_malloc, %object
	.size	mem_malloc, 4
mem_malloc:
	.space	4
	.type	mem_free, %object
	.size	mem_free, 4
mem_free:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
