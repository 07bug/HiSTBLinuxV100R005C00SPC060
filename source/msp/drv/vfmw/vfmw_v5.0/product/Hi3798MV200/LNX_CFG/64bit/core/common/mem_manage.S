#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"mem_manage.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	MEM_InitMemManager
	.type	MEM_InitMemManager, %function
MEM_InitMemManager:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1
	ldr	x19, .LC0
	mov	w0, 1
	ldr	x1, [x19, 24]
	blr	x1
	ldr	x0, .LC1
	mov	x2, 32768
	ldr	x3, [x19, 96]
	mov	w1, 0
	blr	x3
	ldr	x2, .LC2
	mov	w0, 1
	ldr	x1, [x19, 32]
	str	wzr, [x2, 2304]
	blr	x1
.L1:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MEM_InitMemManager, .-MEM_InitMemManager
	.align	3
.LC0:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_ManagerWithOperation
	.type	MEM_ManagerWithOperation, %function
MEM_ManagerWithOperation:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L7
	ldr	x0, .LC3
	ldp	x2, x1, [x19, 56]
	str	x2, [x0, 2312]
	str	x1, [x0, 2320]
.L7:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MEM_ManagerWithOperation, .-MEM_ManagerWithOperation
	.align	3
.LC3:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_ManagerClearOperation
	.type	MEM_ManagerClearOperation, %function
MEM_ManagerClearOperation:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC4
	str	xzr, [x0, 2312]
	str	xzr, [x0, 2320]
	ldp	x29, x30, [sp], 16
	ret
	.size	MEM_ManagerClearOperation, .-MEM_ManagerClearOperation
	.align	3
.LC4:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_AddMemRecord
	.type	MEM_AddMemRecord, %function
MEM_AddMemRecord:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x20, x1
	mov	w19, w2
	bl	_mcount
	cmp	x20, xzr
	ccmp	w19, wzr, 4, ne
	ccmp	w21, wzr, 4, ne
	bne	.L27
.L26:
	mov	w0, 0
.L25:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L27:
	ldr	x22, .LC7
	mov	w0, 1
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x3, .LC8
	ldr	w0, [x3, 24]
	cbz	w0, .L19
	add	x4, x3, 56
	mov	w0, 1
	b	.L16
	.p2align 3
.L29:
	add	w0, w0, 1
	cmp	w0, 1024
	beq	.L28
.L16:
	ldr	w5, [x4]
	add	x4, x4, 32
	cbnz	w5, .L29
.L15:
	sbfiz	x0, x0, 5, 32
	ldr	x1, [x22, 32]
	add	x3, x3, x0
	mov	w0, 1
	str	x20, [x3, 8]
	str	w21, [x3, 16]
	str	w19, [x3, 24]
	blr	x1
	b	.L26
	.p2align 3
.L28:
	ldr	x1, [x22, 32]
	mov	w0, 1
	blr	x1
	mov	w0, -1
	b	.L25
.L19:
	mov	w0, 0
	b	.L15
	.size	MEM_AddMemRecord, .-MEM_AddMemRecord
	.align	3
.LC7:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC8:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_DelMemRecord
	.type	MEM_DelMemRecord, %function
MEM_DelMemRecord:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	cmp	x20, xzr
	mov	w0, 0
	ccmp	w21, wzr, 4, ne
	ccmp	w19, wzr, 4, ne
	bne	.L42
.L31:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L42:
	ldr	x22, .LC11
	mov	w0, 1
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x1, .LC12
	mov	w3, 0
	add	x0, x1, 24
	b	.L33
	.p2align 3
.L32:
	add	w3, w3, 1
	add	x0, x0, 32
	cmp	w3, 1024
	beq	.L43
.L33:
	ldr	w4, [x0]
	cbz	w4, .L32
	ldr	w5, [x0, -8]
	cmp	w19, w5
	bne	.L32
	ldr	x5, [x0, -16]
	cmp	x5, x20
	ccmp	w21, w4, 0, eq
	bne	.L32
	sbfiz	x3, x3, 5, 32
	ldr	x2, [x22, 32]
	add	x1, x1, x3
	mov	w0, 1
	str	xzr, [x1, 8]
	str	wzr, [x1, 16]
	str	wzr, [x1, 24]
	blr	x2
	mov	w0, 0
	b	.L31
	.p2align 3
.L43:
	ldr	x1, [x22, 32]
	mov	w0, 1
	blr	x1
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MEM_DelMemRecord, .-MEM_DelMemRecord
	.align	3
.LC11:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC12:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_Phy2Vir
	.type	MEM_Phy2Vir, %function
MEM_Phy2Vir:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x4, .LC13
	mov	w2, 0
	add	x0, x4, 24
	b	.L47
	.p2align 3
.L45:
	add	w2, w2, 1
	add	x0, x0, 32
	cmp	w2, 1024
	beq	.L52
.L47:
	ldr	w1, [x0]
	cbz	w1, .L45
	ldr	w3, [x0, -8]
	cmp	w3, w19
	add	w1, w1, w3
	bhi	.L45
	cmp	w19, w1
	bcs	.L45
	ubfiz	x2, x2, 5, 32
	sub	w3, w19, w3
	add	x0, x4, x2
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	x0, [x0, 8]
	add	x0, x0, x3
	ret
.L52:
	mov	x0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MEM_Phy2Vir, .-MEM_Phy2Vir
	.align	3
.LC13:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_Vir2Phy
	.type	MEM_Vir2Phy, %function
MEM_Vir2Phy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x4, .LC14
	mov	w2, 0
	add	x0, x4, 24
	b	.L56
	.p2align 3
.L54:
	add	w2, w2, 1
	add	x0, x0, 32
	cmp	w2, 1024
	beq	.L61
.L56:
	ldr	w1, [x0]
	cbz	w1, .L54
	ldr	x3, [x0, -16]
	cmp	x3, x19
	add	x1, x3, x1, uxtw
	bhi	.L54
	cmp	x19, x1
	bcs	.L54
	ubfiz	x2, x2, 5, 32
	sub	x3, x19, x3
	add	x0, x4, x2
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 16]
	add	w0, w0, w3
	ret
.L61:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MEM_Vir2Phy, .-MEM_Vir2Phy
	.align	3
.LC14:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_WritePhyWord
	.type	MEM_WritePhyWord, %function
MEM_WritePhyWord:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x5, .LC15
	mov	w3, 0
	add	x0, x5, 24
	b	.L66
	.p2align 3
.L63:
	add	w3, w3, 1
	add	x0, x0, 32
	cmp	w3, 1024
	beq	.L62
.L66:
	ldr	w2, [x0]
	cbz	w2, .L63
	ldr	w4, [x0, -8]
	cmp	w19, w4
	add	w2, w2, w4
	bcc	.L63
	cmp	w19, w2
	bcs	.L63
	ubfiz	x3, x3, 5, 32
	sub	w4, w19, w4
	add	x0, x5, x3
	ldr	x0, [x0, 8]
	cmn	x0, x4
	beq	.L62
	str	w20, [x0, x4]
.L62:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MEM_WritePhyWord, .-MEM_WritePhyWord
	.align	3
.LC15:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_ReadPhyWord
	.type	MEM_ReadPhyWord, %function
MEM_ReadPhyWord:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x4, .LC16
	mov	w2, 0
	add	x0, x4, 24
	b	.L75
	.p2align 3
.L72:
	add	w2, w2, 1
	add	x0, x0, 32
	cmp	w2, 1024
	beq	.L83
.L75:
	ldr	w1, [x0]
	cbz	w1, .L72
	ldr	w3, [x0, -8]
	cmp	w19, w3
	add	w1, w1, w3
	bcc	.L72
	cmp	w19, w1
	bcs	.L72
	ubfiz	x2, x2, 5, 32
	sub	w3, w19, w3
	add	x1, x4, x2
	mov	w0, 0
	ldr	x1, [x1, 8]
	cmn	x1, x3
	beq	.L73
	ldr	w0, [x1, x3]
.L73:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L83:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MEM_ReadPhyWord, .-MEM_ReadPhyWord
	.align	3
.LC16:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_AllocMemBlock
	.type	MEM_AllocMemBlock, %function
MEM_AllocMemBlock:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w2
	mov	x19, x3
	mov	w23, w4
	bl	_mcount
	cmp	x19, xzr
	ccmp	w22, wzr, 4, ne
	ccmp	x21, xzr, 4, ne
	beq	.L87
	ldr	x20, .LC17
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	ldr	w24, [x19, 28]
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 72
	blr	x3
	str	w24, [x29, 92]
	ldr	x5, [x20, 288]
	mov	w2, 4
	add	x4, x29, 72
	mov	w3, w23
	mov	w1, w22
	mov	x0, x21
	blr	x5
	ldr	x2, [x29, 80]
	cbz	x2, .L87
	ldr	w1, [x29, 92]
	mov	w0, -1
	ldp	w4, w3, [x29, 72]
	cmp	w1, 3
	bls	.L97
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L97:
	ldr	x0, .LC18
	ldrb	w0, [x0,w1,uxtw]
	adr	x1, .Lrtx89
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx89:
	.section	.rodata
	.align	0
	.align	2
.L89:
	.byte	(.L88 - .Lrtx89) / 4
	.byte	(.L90 - .Lrtx89) / 4
	.byte	(.L90 - .Lrtx89) / 4
	.byte	(.L91 - .Lrtx89) / 4
	.text
	.p2align 3
.L90:
	cmp	w4, wzr
	ccmp	w3, wzr, 4, ne
	ccmp	x2, xzr, 4, ne
	beq	.L87
.L92:
	ldr	x4, .LC19
	mov	w0, 0
	str	x2, [x19, 8]
	ldr	w1, [x29, 88]
	ldr	w2, [x4, 2304]
	str	w1, [x19, 24]
	add	w2, w2, 3
	str	w3, [x19, 16]
	add	w1, w2, w1
	and	w1, w1, -4
	str	w1, [x4, 2304]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L88:
	cmp	w4, wzr
	ccmp	x2, xzr, 4, ne
	beq	.L87
	mov	w3, w4
	b	.L92
	.p2align 3
.L91:
	cmp	w3, wzr
	ccmp	x2, xzr, 4, ne
	bne	.L92
.L87:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 96
	ret
	.size	MEM_AllocMemBlock, .-MEM_AllocMemBlock
	.align	3
.LC17:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC18:
	.xword	.L89
	.align	3
.LC19:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_MapRegisterAddr
	.type	MEM_MapRegisterAddr, %function
MEM_MapRegisterAddr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w1
	mov	x19, x2
	bl	_mcount
	cmp	w21, wzr
	ccmp	w20, wzr, 4, ne
	ccmp	x19, xzr, 4, ne
	beq	.L101
	ldr	x22, .LC20
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x22, 96]
	blr	x3
	ldr	x2, [x22, 304]
	mov	w1, w20
	mov	w0, w21
	blr	x2
	cbz	x0, .L101
	str	x0, [x19, 8]
	mov	w0, 0
	str	w21, [x19, 16]
	str	w20, [x19, 24]
.L100:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L101:
	mov	w0, -1
	b	.L100
	.size	MEM_MapRegisterAddr, .-MEM_MapRegisterAddr
	.align	3
.LC20:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_UnmapRegisterAddr
	.type	MEM_UnmapRegisterAddr, %function
MEM_UnmapRegisterAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, wzr
	ccmp	x19, xzr, 4, ne
	beq	.L105
	ldr	x1, .LC21
	mov	x0, x19
	ldr	x1, [x1, 312]
	blr	x1
.L105:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MEM_UnmapRegisterAddr, .-MEM_UnmapRegisterAddr
	.align	3
.LC21:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MEM_ReleaseMemBlock
	.type	MEM_ReleaseMemBlock, %function
MEM_ReleaseMemBlock:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, wzr
	ccmp	x20, xzr, 4, ne
	bne	.L116
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L116:
	ldr	x21, .LC22
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x21, 96]
	blr	x3
	str	w19, [x29, 56]
	ldr	x0, .LC23
	str	x20, [x29, 64]
	add	x3, x0, 32768
	add	x0, x0, 24
	add	x3, x3, 24
	b	.L111
	.p2align 3
.L109:
	add	x0, x0, 32
	cmp	x0, x3
	beq	.L110
.L111:
	ldr	w1, [x0]
	cbz	w1, .L109
	ldr	w2, [x0, -8]
	cmp	w19, w2
	add	w4, w1, w2
	bcc	.L109
	cmp	w19, w4
	bcs	.L109
	str	w1, [x29, 72]
.L110:
	ldr	x1, [x21, 296]
	add	x0, x29, 56
	blr	x1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.size	MEM_ReleaseMemBlock, .-MEM_ReleaseMemBlock
	.align	3
.LC22:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC23:
	.xword	.LANCHOR0
	.global	mem_free
	.global	mem_malloc
	.global	s_MemRecord
	.bss
	.align	3
.LANCHOR0 = . + 0
.LANCHOR1 = . + 30464
	.type	s_MemRecord, %object
	.size	s_MemRecord, 32768
s_MemRecord:
	.zero	32768
	.type	s_MemOffset, %object
	.size	s_MemOffset, 4
s_MemOffset:
	.zero	4
	.zero	4
	.type	mem_malloc, %object
	.size	mem_malloc, 8
mem_malloc:
	.zero	8
	.type	mem_free, %object
	.size	mem_free, 8
mem_free:
	.zero	8
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
