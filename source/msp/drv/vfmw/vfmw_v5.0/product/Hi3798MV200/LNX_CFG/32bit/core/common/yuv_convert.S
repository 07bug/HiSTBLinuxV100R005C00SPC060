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
	.file	"yuv_convert.c"
	.text
	.align	2
	.global	IMAGE_TileTo2D
	.type	IMAGE_TileTo2D, %function
IMAGE_TileTo2D:
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
	mov	r9, r3
	ldr	r3, [r0, #28]
	cmp	r2, #0
	mov	r5, r0
	str	r2, [fp, #-80]
	str	r1, [fp, #-48]
	str	r3, [fp, #-84]
	ldr	r3, [r0, #32]
	str	r3, [fp, #-88]
	beq	.L1
	ldr	r10, .L31
	mov	r3, #0
	mov	r2, r1, lsr #2
	str	r3, [fp, #-64]
	str	r2, [fp, #-76]
	str	r3, [fp, #-56]
	str	r3, [fp, #-68]
.L3:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L8
	ldr	r3, [fp, #-68]
	mov	r7, #0
	mov	r2, r3, lsr #4
	and	r3, r3, #15
	str	r3, [fp, #-52]
	and	r8, r2, #1
	ldr	r3, [fp, #-84]
	mov	r8, r8, asl #2
	mul	r3, r3, r2
	str	r3, [fp, #-60]
	ldr	r3, [fp, #-88]
	mul	r3, r3, r2
	str	r3, [fp, #-72]
	mov	r3, r8
	mov	r8, r9
	mov	r9, r3
	b	.L6
.L5:
	ldr	r3, [fp, #-56]
	add	r4, r9, r4
	ldr	ip, [r5]
	add	r2, r3, r7
	ldr	r3, [fp, #-52]
	ldr	r0, [r8]
	add	r7, r7, #64
	add	r4, r3, r4, lsl #4
	ldr	r3, .L31+4
	add	r0, r0, r2
	mov	r2, #64
	add	r4, r3, r4, lsl #2
	ldr	r3, [fp, #-60]
	ldr	r1, [r4, #256]
	add	r1, r3, r1, lsl #6
	ldr	r3, [r10, #52]
	add	r1, r1, r6, lsl #10
	add	r1, ip, r1
	blx	r3
	ldr	r3, [fp, #-48]
	cmp	r3, r7
	bls	.L29
.L6:
	ldr	r2, [r5, #16]
	mov	r6, r7, lsr #6
	and	r4, r6, #3
	cmp	r2, #10
	bne	.L5
	ldr	r3, [fp, #-64]
	ldr	r2, [r8, #4]
	add	r0, r3, r7, lsr #2
	ldr	r3, [fp, #-52]
	ldr	ip, [r5, #4]
	add	r0, r2, r0
	add	r1, r3, r4, lsl #4
	ldr	r3, .L31+4
	mov	r2, #16
	ldr	r1, [r3, r1, asl #2]
	ldr	r3, [fp, #-72]
	add	r1, r1, r6, lsl #4
	mov	r1, r1, asl #6
	add	r1, r3, r1, lsr #2
	ldr	r3, [r10, #52]
	add	r1, ip, r1
	blx	r3
	b	.L5
.L29:
	mov	r9, r8
.L8:
	ldr	r2, [fp, #-56]
	ldr	r1, [fp, #-48]
	ldr	r3, [fp, #-68]
	add	r2, r2, r1
	str	r2, [fp, #-56]
	ldr	r2, [fp, #-80]
	add	r3, r3, #1
	str	r3, [fp, #-68]
	cmp	r3, r2
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-76]
	add	r3, r3, r2
	str	r3, [fp, #-64]
	bne	.L3
	ldr	r3, [fp, #-68]
	movs	r3, r3, lsr #1
	str	r3, [fp, #-80]
	beq	.L1
	ldr	r2, [fp, #-84]
	mov	r3, #0
	ldr	r10, .L31
	mov	r8, r3
	str	r3, [fp, #-60]
	mov	r2, r2, lsr #1
	str	r2, [fp, #-92]
	ldr	r2, [fp, #-88]
	str	r3, [fp, #-64]
	mov	r2, r2, lsr #1
	str	r2, [fp, #-84]
.L9:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L13
	ldr	r3, [fp, #-64]
	mov	r6, #0
	ldr	r1, [fp, #-92]
	mov	r2, r3, lsr #3
	and	r3, r3, #7
	and	r7, r2, #1
	str	r3, [fp, #-52]
	mul	r1, r1, r2
	mov	r7, r7, asl #2
	str	r1, [fp, #-56]
	ldr	r1, [fp, #-84]
	mul	r2, r1, r2
	str	r2, [fp, #-68]
	ldr	r2, .L31+4
	add	r3, r2, r3, lsl #2
	str	r3, [fp, #-72]
	mov	r3, r7
	mov	r7, r9
	mov	r9, r3
	b	.L12
.L11:
	and	ip, r4, #3
	ldr	r3, [fp, #-52]
	add	ip, r9, ip
	ldr	lr, [r5, #8]
	ldr	r0, [r7, #8]
	add	r2, r8, r6
	add	ip, r3, ip, lsl #3
	ldr	r3, .L31+4
	add	r0, r0, r2
	mov	r2, #64
	add	ip, r3, ip, lsl #2
	ldr	r3, [fp, #-56]
	add	r6, r6, #64
	ldr	r1, [ip, #800]
	add	r1, r3, r1, lsl #6
	ldr	r3, [r10, #52]
	add	r1, r1, r4, lsl #9
	add	r1, lr, r1
	blx	r3
	ldr	r3, [fp, #-48]
	cmp	r3, r6
	bls	.L30
.L12:
	ldr	r2, [r5, #16]
	mov	r4, r6, lsr #6
	cmp	r2, #10
	bne	.L11
	ldr	r3, [fp, #-72]
	ldr	r2, [r7, #12]
	ldr	ip, [r5, #12]
	ldr	r1, [r3, #768]
	ldr	r3, [fp, #-60]
	add	r1, r1, r4, lsl #3
	add	r0, r3, r6, lsr #2
	ldr	r3, [fp, #-68]
	mov	r1, r1, asl #6
	add	r0, r2, r0
	mov	r2, #16
	add	r1, r3, r1, lsr #2
	ldr	r3, [r10, #52]
	add	r1, ip, r1
	blx	r3
	b	.L11
.L30:
	mov	r9, r7
.L13:
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-64]
	add	r8, r8, r2
	ldr	r2, [fp, #-80]
	add	r3, r3, #1
	str	r3, [fp, #-64]
	cmp	r3, r2
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-76]
	add	r3, r3, r2
	str	r3, [fp, #-60]
	bne	.L9
.L1:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L32:
	.align	2
.L31:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	IMAGE_TileTo2D, .-IMAGE_TileTo2D
	.align	2
	.global	IMAGE_LinearTo2D
	.type	IMAGE_LinearTo2D, %function
IMAGE_LinearTo2D:
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
	mov	r7, r3
	ldr	r3, [r0, #32]
	cmp	r2, #0
	mov	r5, r0
	str	r2, [fp, #-56]
	mov	r6, r1
	str	r3, [fp, #-68]
	beq	.L33
	mov	r8, #0
	mov	r3, r1, lsr #2
	ldr	r9, .L61
	mov	r10, r8
	str	r3, [fp, #-60]
	str	r8, [fp, #-52]
	b	.L36
.L38:
	ldr	r1, [r5, #28]
	mov	r2, r6
	ldr	r3, [fp, #-60]
	ldr	ip, [r5]
	ldr	r0, [r7]
	add	r8, r8, r3
	mov	r1, r1, lsr #4
	ldr	r3, [fp, #-52]
	ldr	r4, [r9, #52]
	add	r0, r0, r3
	add	r3, r3, r6
	mla	r1, r1, r10, ip
	str	r3, [fp, #-52]
	blx	r4
	ldr	r3, [fp, #-56]
	add	r10, r10, #1
	cmp	r10, r3
	beq	.L60
.L36:
	ldr	r2, [r5, #16]
	cmp	r2, #10
	bne	.L38
	cmp	r6, #0
	beq	.L38
	ldr	r1, [fp, #-68]
	mov	r3, r10, lsr #4
	and	r2, r10, #15
	str	r10, [fp, #-64]
	mov	r4, #0
	mul	r3, r1, r3
	mov	r10, r2
	str	r3, [fp, #-48]
	mov	r3, r7
	mov	r7, r6
	mov	r6, r5
	mov	r5, r3
.L39:
	mov	lr, r4, lsr #6
	ldr	r3, .L61+4
	and	r2, lr, #3
	ldr	r0, [r5, #4]
	add	r1, r8, r4, lsr #2
	ldr	ip, [r6, #4]
	add	r2, r10, r2, lsl #4
	add	r0, r0, r1
	add	r4, r4, #64
	ldr	r1, [r3, r2, asl #2]
	mov	r2, #16
	ldr	r3, [fp, #-48]
	add	r1, r1, lr, lsl #4
	mov	r1, r1, asl #6
	add	r1, r3, r1, lsr #2
	ldr	r3, [r9, #52]
	add	r1, ip, r1
	blx	r3
	cmp	r7, r4
	bhi	.L39
	mov	r3, r5
	ldr	r10, [fp, #-64]
	mov	r5, r6
	mov	r6, r7
	mov	r7, r3
	b	.L38
.L33:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L60:
	movs	r3, r10, lsr #1
	str	r3, [fp, #-64]
	beq	.L33
	ldr	r3, [fp, #-68]
	mov	r8, #0
	str	r8, [fp, #-56]
	str	r8, [fp, #-52]
	mov	r3, r3, lsr #1
	str	r3, [fp, #-68]
	b	.L42
.L43:
	ldr	r3, [fp, #-60]
	mov	r2, r6
	ldr	r1, [r5, #28]
	ldr	r0, [r7, #8]
	add	r8, r8, r3
	ldr	r3, [fp, #-56]
	ldr	ip, [r5, #8]
	mov	r1, r1, lsr #4
	add	r0, r0, r3
	add	r3, r3, r6
	str	r3, [fp, #-56]
	ldr	r3, [fp, #-52]
	ldr	r4, [r9, #52]
	mla	r1, r1, r3, ip
	add	r3, r3, #1
	str	r3, [fp, #-52]
	mov	r10, r3
	blx	r4
	ldr	r2, [fp, #-64]
	cmp	r10, r2
	beq	.L33
.L42:
	ldr	r2, [r5, #16]
	cmp	r2, #10
	bne	.L43
	cmp	r6, #0
	beq	.L43
	ldr	r2, [fp, #-52]
	mov	r4, #0
	and	r10, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-68]
	mul	r3, r2, r3
	str	r3, [fp, #-48]
	ldr	r3, .L61+4
	add	r10, r3, r10, lsl #2
.L44:
	ldr	r2, [r10, #768]
	mov	r1, r4, lsr #6
	ldr	r3, [fp, #-48]
	add	r0, r8, r4, lsr #2
	add	r1, r2, r1, lsl #3
	ldr	ip, [r5, #12]
	ldr	r2, [r7, #12]
	add	r4, r4, #64
	mov	r1, r1, asl #6
	add	r0, r2, r0
	mov	r2, #16
	add	r1, r3, r1, lsr #2
	ldr	r3, [r9, #52]
	add	r1, ip, r1
	blx	r3
	cmp	r6, r4
	bhi	.L44
	b	.L43
.L62:
	.align	2
.L61:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	IMAGE_LinearTo2D, .-IMAGE_LinearTo2D
	.align	2
	.global	IMAGE_ConvertTo2D
	.type	IMAGE_ConvertTo2D, %function
IMAGE_ConvertTo2D:
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
	ldr	ip, [r0, #24]
	cmp	ip, #1
	beq	.L65
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	IMAGE_LinearTo2D
.L65:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	IMAGE_TileTo2D
	UNWIND(.fnend)
	.size	IMAGE_ConvertTo2D, .-IMAGE_ConvertTo2D
	.global	g_RowMapTable_UV_2b
	.global	g_RowMapTable_Y_2b
	.global	g_RowMapTable_UV
	.global	g_RowMapTable_Y
	.data
	.align	2
.LANCHOR0 = . + 0
	.type	g_RowMapTable_Y_2b, %object
	.size	g_RowMapTable_Y_2b, 256
g_RowMapTable_Y_2b:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.type	g_RowMapTable_Y, %object
	.size	g_RowMapTable_Y, 512
g_RowMapTable_Y:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	8
	.word	9
	.word	10
	.word	11
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.type	g_RowMapTable_UV_2b, %object
	.size	g_RowMapTable_UV_2b, 32
g_RowMapTable_UV_2b:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.type	g_RowMapTable_UV, %object
	.size	g_RowMapTable_UV, 256
g_RowMapTable_UV:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	4
	.word	5
	.word	6
	.word	7
	.word	0
	.word	1
	.word	2
	.word	3
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
