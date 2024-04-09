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
	.file	"dsp_ringbuf.c"
	.text
	.align	2
	.global	RBUF_Create
	.type	RBUF_Create, %function
RBUF_Create:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r7, r0
	mov	r5, r1
	mov	r0, #26
	mov	r1, #84
	bl	HI_ADSP_MALLOC
	subs	r4, r0, #0
	beq	.L7
	ldr	r6, .L10
	mov	r2, #84
	mov	r1, #0
	ldr	r3, [r6, #20]
	blx	r3
	ldr	r3, [r6, #24]
	mov	r2, #36
	mov	r1, r5
	mov	r0, r4
	blx	r3
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L4
	ldmib	r4, {r0, r1}
.L5:
	ldr	r2, [r4, #12]
	mov	r3, #0
	ldr	ip, [r4, #16]
	str	r0, [r4, #44]
	str	r2, [r4, #36]
	str	ip, [r4, #40]
	str	r1, [r4, #48]
	str	r3, [r2]
	ldr	r2, [r4, #40]
	str	r3, [r2]
.L7:
	str	r4, [r7]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4:
	ldr	r2, [r5, #24]
	mov	r0, #26
	ldr	r1, [r5, #8]
	bl	HI_ADSP_VMALLOC_Aligned
	subs	r6, r0, #0
	beq	.L9
	str	r6, [r4, #4]
	mov	r0, r6
	ldr	r1, [r5, #8]
	str	r1, [r4, #8]
	b	.L5
.L9:
	mov	r1, r4
	mov	r0, #26
	bl	HI_ADSP_FREE
	str	r6, [r7]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L11:
	.align	2
.L10:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	RBUF_Create, .-RBUF_Create
	.align	2
	.global	RBUF_Create_EXT
	.type	RBUF_Create_EXT, %function
RBUF_Create_EXT:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r7, r0
	mov	r5, r1
	mov	r0, #26
	mov	r1, #84
	bl	HI_ADSP_MALLOC
	subs	r4, r0, #0
	beq	.L18
	ldr	r6, .L20
	mov	r2, #84
	mov	r1, #0
	ldr	r3, [r6, #20]
	blx	r3
	ldr	r3, [r6, #24]
	mov	r2, #36
	mov	r1, r5
	mov	r0, r4
	blx	r3
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L15
	ldmib	r4, {r0, r3}
.L16:
	ldr	r1, [r4, #16]
	ldr	r2, [r4, #12]
	str	r0, [r4, #44]
	str	r3, [r4, #48]
	str	r1, [r4, #40]
	str	r2, [r4, #36]
.L18:
	str	r4, [r7]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L15:
	ldr	r2, [r5, #24]
	mov	r0, #26
	ldr	r1, [r5, #8]
	bl	HI_ADSP_VMALLOC_Aligned
	subs	r6, r0, #0
	beq	.L19
	str	r6, [r4, #4]
	mov	r0, r6
	ldr	r3, [r5, #8]
	str	r3, [r4, #8]
	b	.L16
.L19:
	mov	r1, r4
	mov	r0, #26
	bl	HI_ADSP_FREE
	str	r6, [r7]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L21:
	.align	2
.L20:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	RBUF_Create_EXT, .-RBUF_Create_EXT
	.align	2
	.global	RBUF_Destroy
	.type	RBUF_Destroy, %function
RBUF_Destroy:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4]
	cmp	r3, #0
	beq	.L25
.L24:
	mov	r1, r4
	mov	r0, #26
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HI_ADSP_FREE
.L25:
	ldr	r1, [r4, #4]
	mov	r0, #26
	bl	HI_ADSP_VFREE_Aligned
	b	.L24
	UNWIND(.fnend)
	.size	RBUF_Destroy, .-RBUF_Destroy
	.align	2
	.global	RBUF_ReadData
	.type	RBUF_ReadData, %function
RBUF_ReadData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r5, r0, #0
	mov	r7, r1
	moveq	r0, r5
	beq	.L48
	ldr	r1, [r5, #40]
	mov	r0, #0
	ldr	ip, [r5, #36]
	ldr	r3, [r5, #56]
	str	r0, [fp, #-60]
	add	r3, r3, #1
	str	r3, [r5, #56]
	ldr	r4, [r1]
	ldr	r3, [ip]
	str	r0, [fp, #-56]
	cmp	r4, r3
	str	r4, [fp, #-52]
	str	r0, [fp, #-48]
	bhi	.L28
	add	ip, r2, r4
	cmp	r3, ip
	bcc	.L29
.L31:
	mov	r8, r2
	mov	r3, #0
	str	r2, [fp, #-60]
	str	r3, [fp, #-68]
.L30:
	cmp	r8, #0
	beq	.L34
	ldr	r3, .L51
	sub	r10, fp, #52
	sub	r9, fp, #60
	mov	r6, r8
.L35:
	subs	r0, r7, #0
	mov	r2, r6
	ldr	r1, [r5, #44]
	ldr	r4, [r10], #4
	beq	.L33
	ldr	ip, [r3, #24]
	add	r1, r1, r4
	str	r3, [fp, #-64]
	blx	ip
	ldr	r3, [fp, #-64]
	add	r7, r7, r6
.L33:
	sub	r2, fp, #56
	add	r4, r4, r6
	cmp	r9, r2
	beq	.L49
	ldr	r6, [r9, #4]!
	cmp	r6, #0
	bne	.L35
.L49:
	ldr	r1, [r5, #40]
.L34:
	ldr	r3, [r5, #48]
	cmp	r3, r4
	ldr	r3, [fp, #-68]
	moveq	r4, #0
	adds	r0, r3, r8
	str	r4, [r1]
	ldreq	r3, [r5, #60]
	addeq	r3, r3, #1
	streq	r3, [r5, #60]
	ldr	r3, [r5, #52]
	add	r3, r3, r0
	str	r3, [r5, #52]
.L48:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L28:
	ldr	r8, [r5, #48]
	add	r0, r2, r4
	cmp	r0, r8
	bls	.L31
	rsb	r8, r4, r8
	str	r8, [fp, #-60]
	rsb	r2, r8, r2
	str	r2, [fp, #-68]
	cmp	r3, r2
	strcc	r3, [fp, #-56]
	strcc	r3, [fp, #-68]
	ldrcs	r3, [fp, #-68]
	strcs	r3, [fp, #-56]
	b	.L30
.L29:
	rsb	r8, r4, r3
	str	r0, [fp, #-68]
	str	r8, [fp, #-60]
	b	.L30
.L52:
	.align	2
.L51:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	RBUF_ReadData, .-RBUF_ReadData
	.align	2
	.global	RBUF_WriteData
	.type	RBUF_WriteData, %function
RBUF_WriteData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	subs	r5, r0, #0
	mov	r8, r1
	moveq	r0, r2
	beq	.L71
	ldr	ip, [r5, #40]
	mov	r0, #0
	ldr	r1, [r5, #36]
	ldr	r3, [r5, #72]
	str	r0, [fp, #-60]
	add	r3, r3, #1
	str	r3, [r5, #72]
	ldr	r6, [ip]
	ldr	r4, [r1]
	str	r0, [fp, #-56]
	cmp	r6, r4
	str	r0, [fp, #-48]
	str	r4, [fp, #-52]
	bhi	.L55
	ldr	r6, [r5, #48]
	add	r3, r2, r4
	cmp	r6, r3
	bcc	.L56
.L58:
	mov	r6, r2
	mov	r3, #0
	str	r2, [fp, #-60]
	str	r3, [fp, #-72]
.L57:
	cmp	r6, #0
	beq	.L62
	ldr	r10, .L73
	mov	r7, r6
	mov	r9, #0
	sub	r3, fp, #52
	str	r3, [fp, #-68]
	sub	r3, fp, #60
	str	r3, [fp, #-64]
.L66:
	subs	r1, r8, #0
	ldr	r0, [r5, #44]
	mov	r2, r7
	add	r9, r9, #1
	add	r0, r0, r4
	ldreq	r3, [r10, #20]
	ldrne	r3, [r10, #24]
	addne	r8, r8, r7
	blx	r3
	cmp	r9, #2
	add	r4, r7, r4
	beq	.L72
	ldr	r3, [fp, #-64]
	ldr	r7, [r3, #4]!
	cmp	r7, #0
	str	r3, [fp, #-64]
	ldrne	r3, [fp, #-68]
	ldrne	r4, [r3, #4]!
	strne	r3, [fp, #-68]
	bne	.L66
.L72:
	ldr	r1, [r5, #36]
.L62:
	ldr	r3, [r5, #48]
	cmp	r3, r4
	ldr	r3, [fp, #-72]
	movls	r4, #0
	adds	r0, r6, r3
	str	r4, [r1]
	ldreq	r3, [r5, #76]
	addeq	r3, r3, #1
	streq	r3, [r5, #76]
	ldr	r3, [r5, #68]
	add	r3, r3, r0
	str	r3, [r5, #68]
.L71:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L55:
	add	r3, r2, r4
	cmp	r6, r3
	bhi	.L58
	rsb	r6, r4, r6
	str	r0, [fp, #-72]
	str	r6, [fp, #-60]
	b	.L57
.L56:
	rsb	r6, r4, r6
	str	r6, [fp, #-60]
	rsb	r3, r6, r2
	str	r3, [fp, #-72]
	str	r3, [fp, #-56]
	b	.L57
.L74:
	.align	2
.L73:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	RBUF_WriteData, .-RBUF_WriteData
	.align	2
	.global	RBUF_ReadDataComplete
	.type	RBUF_ReadDataComplete, %function
RBUF_ReadDataComplete:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	lr, [r0, #40]
	ldr	r3, [r0, #36]
	ldr	r2, [lr]
	ldr	ip, [r3]
	cmp	r2, ip
	bhi	.L77
	add	r3, r1, r2
	cmp	ip, r3
	rsbcc	r5, r2, ip
	ldrcs	r4, [r0, #48]
	movcs	r5, r1
	ldrcc	r4, [r0, #48]
.L79:
	cmp	r5, #0
	beq	.L90
.L84:
	add	r3, r5, r2
.L81:
	cmp	r4, r3
	moveq	r3, #0
	str	r3, [lr]
	ldr	r3, [r0, #52]
	add	r1, r3, r1
	str	r1, [r0, #52]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L77:
	ldr	r4, [r0, #48]
	add	r3, r1, r2
	cmp	r3, r4
	bls	.L85
	rsb	r5, r2, r4
	rsb	r3, r5, r1
	cmp	r3, ip
	movcs	r3, ip
	cmp	r5, #0
	beq	.L90
	cmp	r3, #0
	bne	.L81
	b	.L84
.L85:
	mov	r5, r1
	b	.L79
.L90:
	mov	r3, r2
	b	.L81
	UNWIND(.fnend)
	.size	RBUF_ReadDataComplete, .-RBUF_ReadDataComplete
	.align	2
	.global	RBUF_WriteDataComplete
	.type	RBUF_WriteDataComplete, %function
RBUF_WriteDataComplete:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	ldmeqfd	sp, {r4, fp, sp, pc}
	ldr	r3, [r0, #40]
	ldr	r2, [r0, #36]
	ldr	lr, [r0, #48]
	ldr	r3, [r3]
	ldr	ip, [r2]
	cmp	r3, ip
	bls	.L104
.L95:
	cmp	r1, #0
	movne	r4, r1
	beq	.L99
.L98:
	add	r3, r4, ip
.L96:
	cmp	lr, r3
	moveq	r3, #0
	str	r3, [r2]
	ldr	r3, [r0, #68]
	add	r1, r3, r1
	str	r1, [r0, #68]
	ldmfd	sp, {r4, fp, sp, pc}
.L104:
	add	r3, r1, ip
	cmp	lr, r3
	bcs	.L95
	rsb	r4, ip, lr
	cmp	r4, #0
	rsb	r3, r4, r1
	beq	.L99
	cmp	r3, #0
	bne	.L96
	b	.L98
.L99:
	mov	r3, ip
	b	.L96
	UNWIND(.fnend)
	.size	RBUF_WriteDataComplete, .-RBUF_WriteDataComplete
	.align	2
	.global	RBUF_QueryInfo
	.type	RBUF_QueryInfo, %function
RBUF_QueryInfo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	mov	r3, r1
	beq	.L114
	ldr	r2, [r0, #28]
	ldr	lr, [r0, #24]
	str	r2, [r1, #32]
	ldr	r2, [r0, #44]
	str	r2, [r1]
	ldr	r2, [r0, #48]
	str	r2, [r1, #12]
	ldr	r2, [r0, #36]
	ldr	r2, [r2]
	str	r2, [r1, #8]
	ldr	r2, [r0, #40]
	ldr	r2, [r2]
	str	r2, [r1, #4]
	ldr	r1, [r0, #40]
	ldr	r2, [r0, #36]
	ldr	ip, [r1]
	ldr	r2, [r2]
	cmp	ip, r2
	rsbls	r2, ip, r2
	strls	r2, [r3, #16]
	ldrhi	r4, [r0, #48]
	addhi	r1, r2, r4
	rsbhi	r4, ip, r4
	rsbhi	r2, ip, r1
	strhi	r4, [r3, #16]
	str	r2, [r3, #20]
	ldr	r2, [r0, #40]
	ldr	r1, [r0, #36]
	ldr	r2, [r2]
	ldr	r1, [r1]
	cmp	r2, r1
	rsbhi	r2, r1, r2
	strhi	r2, [r3, #24]
	ldrls	r0, [r0, #48]
	addls	r2, r2, r0
	rsbls	r0, r1, r0
	rsbls	r2, r1, r2
	strls	r0, [r3, #24]
	cmp	lr, r2
	str	r2, [r3, #28]
	bcs	.L115
	ldr	r1, [r3, #28]
	rsb	r2, lr, r2
	ldr	r0, [r3, #24]
	str	r2, [r3, #28]
	rsb	r1, r0, r1
	cmp	lr, r1
	strhi	r2, [r3, #24]
	ldmfd	sp, {r4, fp, sp, pc}
.L115:
	mov	r2, #0
	str	r2, [r3, #24]
	str	r2, [r3, #28]
	ldmfd	sp, {r4, fp, sp, pc}
.L114:
	ldr	ip, .L116
	mov	r1, r0
	mov	r2, #36
	mov	r0, r3
	ldr	r3, [ip, #20]
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	bx	r3
.L117:
	.align	2
.L116:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	RBUF_QueryInfo, .-RBUF_QueryInfo
	.align	2
	.global	RBUF_QueryBusy_ProvideRptr
	.type	RBUF_QueryBusy_ProvideRptr, %function
RBUF_QueryBusy_ProvideRptr:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	ip, [r0, #40]
	ldr	r2, [r0, #36]
	ldr	r3, [r1]
	ldr	r1, [ip]
	ldr	r2, [r2]
	cmp	r3, r2
	rsbls	r0, r3, r2
	ldrhi	r0, [r0, #48]
	addhi	r0, r2, r0
	rsbhi	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	RBUF_QueryBusy_ProvideRptr, .-RBUF_QueryBusy_ProvideRptr
	.align	2
	.global	RBUF_QueryBusy
	.type	RBUF_QueryBusy, %function
RBUF_QueryBusy:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #40]
	ldr	r2, [r0, #36]
	ldr	r3, [r3]
	ldr	r2, [r2]
	cmp	r3, r2
	rsbls	r0, r3, r2
	ldrhi	r0, [r0, #48]
	addhi	r0, r2, r0
	rsbhi	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	RBUF_QueryBusy, .-RBUF_QueryBusy
	.align	2
	.global	RBUF_MuteRawData
	.type	RBUF_MuteRawData, %function
RBUF_MuteRawData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r4, r0, #0
	moveq	r0, r4
	beq	.L137
	ldr	r3, [r4, #40]
	mov	r0, #0
	ldr	r2, [r4, #36]
	str	r0, [fp, #-40]
	ldr	r3, [r3]
	ldr	r2, [r2]
	cmp	r3, r2
	bhi	.L128
	add	ip, r1, r3
	cmp	r2, ip
	rsbcc	r6, r3, r2
	movcc	r5, r0
	bcs	.L136
.L129:
	cmp	r6, #0
	beq	.L131
	ldr	r7, .L139
	mov	r2, r6
	ldr	r0, [r4, #44]
	mov	r1, #0
	ldr	r8, [r7, #20]
	add	r0, r0, r3
	blx	r8
	cmp	r5, #0
	beq	.L131
	ldr	ip, [r4, #44]
	mov	r2, r5
	ldr	r0, [fp, #-40]
	mov	r1, #0
	ldr	r3, [r7, #20]
	add	r0, ip, r0
	blx	r3
.L131:
	add	r0, r5, r6
.L137:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L128:
	ldr	r6, [r4, #48]
	add	ip, r1, r3
	cmp	ip, r6
	bhi	.L138
.L136:
	mov	r6, r1
	mov	r5, r0
	b	.L129
.L138:
	rsb	r6, r3, r6
	rsb	r0, r6, r1
	cmp	r0, r2
	movcc	r5, r0
	movcs	r5, r2
	b	.L129
.L140:
	.align	2
.L139:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	RBUF_MuteRawData, .-RBUF_MuteRawData
	.align	2
	.global	RBUF_QueryFree
	.type	RBUF_QueryFree, %function
RBUF_QueryFree:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r2, [r0, #40]
	ldr	r3, [r0, #36]
	ldr	r1, [r0, #24]
	ldr	r2, [r2]
	ldr	r3, [r3]
	cmp	r2, r3
	ldrls	r0, [r0, #48]
	addls	r2, r2, r0
	rsb	r3, r3, r2
	cmp	r1, r3
	rsbcc	r0, r1, r3
	movcs	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	RBUF_QueryFree, .-RBUF_QueryFree
	.align	2
	.global	RBUF_CheckFree
	.type	RBUF_CheckFree, %function
RBUF_CheckFree:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r3, r0, #0
	beq	.L153
	ldr	r0, [r3, #36]
	ldr	r2, [r3, #40]
	ldr	r4, [r3, #24]
	ldr	r2, [r2]
	ldr	ip, [r0]
	cmp	r2, ip
	rsbls	r0, r2, ip
	rsbhi	lr, ip, r2
	ldrls	lr, [r3, #48]
	ldrhi	r0, [r3, #48]
	addls	r2, r2, lr
	addhi	ip, ip, r0
	rsbls	lr, ip, r2
	rsbhi	r0, r2, ip
	cmp	r4, lr
	addcs	ip, r0, r1
	movcs	r1, #1
	bcc	.L154
.L152:
	ldr	r0, [r3, #28]
	cmp	r0, ip
	movcs	r0, r1
	orrcc	r0, r1, #1
	eor	r0, r0, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L154:
	rsb	r2, r4, lr
	add	ip, r0, r1
	cmp	r1, r2
	movcc	r1, #0
	movcs	r1, #1
	b	.L152
.L153:
	mov	r0, r3
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	RBUF_CheckFree, .-RBUF_CheckFree
	.align	2
	.global	RBUF_Flush
	.type	RBUF_Flush, %function
RBUF_Flush:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	ldrne	r2, [r0, #36]
	ldrne	r3, [r0, #40]
	ldrne	r2, [r2]
	strne	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	RBUF_Flush, .-RBUF_Flush
	.align	2
	.global	RBUF_ReadDataDma
	.type	RBUF_ReadDataDma, %function
RBUF_ReadDataDma:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r6, r0, #0
	mov	r7, r1
	mov	r9, r3
	beq	.L176
	cmp	r3, #0
	ldr	r0, [r6, #40]
	beq	.L187
	ldr	r1, [r6, #36]
	mov	r3, #0
	ldr	r0, [r0]
	ldr	r4, [r9]
	ldr	r1, [r1]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-48]
.L175:
	cmp	r4, r1
	str	r4, [fp, #-52]
	bhi	.L163
	add	r3, r4, r2
	cmp	r3, r1
	bls	.L166
	ldr	r3, [fp, #-56]
	rsb	r8, r4, r1
	str	r8, [fp, #-60]
	str	r3, [fp, #-64]
.L165:
	cmp	r8, #0
	beq	.L169
	sub	r3, fp, #52
	sub	r10, fp, #60
	mov	r5, r8
	str	r8, [fp, #-68]
	mov	r8, r3
.L170:
	subs	r0, r7, #0
	mov	r2, r5
	ldr	r1, [r6, #44]
	ldr	r4, [r8], #4
	beq	.L168
	ldr	r3, .L189
	add	r1, r1, r4
	add	r7, r7, r5
	ldr	r3, [r3, #24]
	blx	r3
.L168:
	sub	r3, fp, #56
	add	r4, r4, r5
	cmp	r10, r3
	beq	.L185
	ldr	r5, [r10, #4]!
	cmp	r5, #0
	bne	.L170
.L185:
	ldr	r8, [fp, #-68]
.L169:
	ldr	r3, [r6, #48]
	cmp	r3, r4
	moveq	r4, #0
	cmp	r9, #0
	strne	r4, [r9]
	ldrne	r3, [fp, #-64]
	addne	r0, r3, r8
	beq	.L188
.L184:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L163:
	ldr	r8, [r6, #48]
	add	r3, r4, r2
	cmp	r3, r8
	bls	.L166
	rsb	r8, r4, r8
	str	r8, [fp, #-60]
	rsb	r3, r8, r2
	str	r3, [fp, #-64]
	cmp	r3, r1
	strhi	r1, [fp, #-56]
	strhi	r1, [fp, #-64]
	ldrls	r3, [fp, #-64]
	strls	r3, [fp, #-56]
	b	.L165
.L166:
	ldr	r3, [fp, #-56]
	mov	r8, r2
	str	r2, [fp, #-60]
	str	r3, [fp, #-64]
	b	.L165
.L187:
	ldr	r1, [r6, #36]
	ldr	r3, [r6, #56]
	str	r9, [fp, #-60]
	add	r3, r3, #1
	str	r9, [fp, #-56]
	str	r3, [r6, #56]
	str	r9, [fp, #-48]
	ldr	r4, [r0]
	ldr	r1, [r1]
	b	.L175
.L176:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L188:
	ldr	r2, [fp, #-64]
	ldr	r3, [r6, #40]
	adds	r0, r2, r8
	str	r4, [r3]
	ldreq	r3, [r6, #60]
	addeq	r3, r3, #1
	streq	r3, [r6, #60]
	ldr	r3, [r6, #52]
	add	r3, r3, r0
	str	r3, [r6, #52]
	b	.L184
.L190:
	.align	2
.L189:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	RBUF_ReadDataDma, .-RBUF_ReadDataDma
	.align	2
	.global	RBUF_WriteDataDma
	.type	RBUF_WriteDataDma, %function
RBUF_WriteDataDma:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	subs	r5, r0, #0
	mov	r8, r1
	moveq	r0, r2
	beq	.L209
	ldr	ip, [r5, #40]
	mov	r0, #0
	ldr	r1, [r5, #36]
	ldr	r3, [r5, #72]
	str	r0, [fp, #-60]
	add	r3, r3, #1
	str	r3, [r5, #72]
	ldr	r6, [ip]
	ldr	r4, [r1]
	str	r0, [fp, #-56]
	cmp	r6, r4
	str	r0, [fp, #-48]
	str	r4, [fp, #-52]
	bhi	.L193
	ldr	r6, [r5, #48]
	add	r3, r2, r4
	cmp	r6, r3
	bcc	.L194
.L196:
	mov	r6, r2
	mov	r3, #0
	str	r2, [fp, #-60]
	str	r3, [fp, #-72]
.L195:
	cmp	r6, #0
	beq	.L200
	ldr	r10, .L211
	mov	r7, r6
	mov	r9, #0
	sub	r3, fp, #52
	str	r3, [fp, #-68]
	sub	r3, fp, #60
	str	r3, [fp, #-64]
.L204:
	subs	r1, r8, #0
	ldr	r0, [r5, #44]
	mov	r2, r7
	add	r9, r9, #1
	add	r0, r0, r4
	ldreq	r3, [r10, #20]
	ldrne	r3, [r10, #24]
	addne	r8, r8, r7
	blx	r3
	cmp	r9, #2
	add	r4, r7, r4
	beq	.L210
	ldr	r3, [fp, #-64]
	ldr	r7, [r3, #4]!
	cmp	r7, #0
	str	r3, [fp, #-64]
	ldrne	r3, [fp, #-68]
	ldrne	r4, [r3, #4]!
	strne	r3, [fp, #-68]
	bne	.L204
.L210:
	ldr	r1, [r5, #36]
.L200:
	ldr	r3, [r5, #48]
	cmp	r3, r4
	ldr	r3, [fp, #-72]
	movls	r4, #0
	adds	r0, r6, r3
	str	r4, [r1]
	ldreq	r3, [r5, #76]
	addeq	r3, r3, #1
	streq	r3, [r5, #76]
	ldr	r3, [r5, #68]
	add	r3, r3, r0
	str	r3, [r5, #68]
.L209:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L193:
	add	r3, r2, r4
	cmp	r6, r3
	bhi	.L196
	rsb	r6, r4, r6
	str	r0, [fp, #-72]
	str	r6, [fp, #-60]
	b	.L195
.L194:
	rsb	r6, r4, r6
	str	r6, [fp, #-60]
	rsb	r3, r6, r2
	str	r3, [fp, #-72]
	str	r3, [fp, #-56]
	b	.L195
.L212:
	.align	2
.L211:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	RBUF_WriteDataDma, .-RBUF_WriteDataDma
	.align	2
	.global	RBUF_CopyData
	.type	RBUF_CopyData, %function
RBUF_CopyData:
	UNWIND(.fnstart)


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
	mov	r6, r0
	mov	r4, r2
	moveq	ip, #1
	movne	ip, #0
	mov	r5, r1
	moveq	r0, #0
	bne	.L234
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L234:
	ldr	r3, [r6, #40]
	ldr	lr, [r1, #36]
	ldr	r2, [r6, #36]
	ldr	r1, [r3]
	ldr	r10, [lr]
	ldr	r3, [r3]
	str	r1, [fp, #-56]
	ldr	r1, [r6, #44]
	ldr	r2, [r2]
	str	r1, [fp, #-48]
	cmp	r3, r2
	ldr	r1, [r5, #44]
	str	r1, [fp, #-52]
	bls	.L235
	ldr	r0, [r6, #48]
	add	r1, r4, r3
	cmp	r1, r0
	bls	.L229
	rsb	r3, r3, r0
	mov	r0, #2
	rsb	r7, r3, r4
	cmp	r7, r2
	movcs	r7, r2
.L216:
	ldr	r2, [r5, #40]
	ldr	r8, [r2]
	ldr	r2, [lr]
	cmp	r8, r2
	bhi	.L217
	ldr	r8, [r5, #48]
	add	r1, r4, r2
	cmp	r8, r1
	bcs	.L231
	rsb	r8, r2, r8
	mov	r2, #2
	rsb	r9, r8, r4
.L219:
	cmp	r2, #2
	movne	ip, #0
	andeq	ip, ip, #1
	cmp	ip, #0
	bne	.L236
	cmp	r8, r3
	beq	.L237
	bcs	.L224
	ldr	r2, [fp, #-52]
	ldr	ip, .L239
	add	r0, r2, r10
	ldr	r1, [fp, #-56]
	rsb	r10, r8, r3
	ldr	r3, [fp, #-48]
	mov	r2, r8
	add	r9, r10, r7
	add	r1, r3, r1
	ldr	r3, [ip, #24]
	blx	r3
	ldr	r1, [fp, #-56]
	ldr	r0, .L239
	mov	r2, r10
	add	r1, r8, r1
	ldr	r8, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r1, r3, r1
	ldr	r3, [r0, #24]
	mov	r0, r8
	blx	r3
	ldr	r2, .L239
	add	r0, r8, r10
	ldr	r1, [fp, #-48]
	ldr	r3, [r2, #24]
	mov	r2, r7
	blx	r3
.L221:
	ldr	r1, [r6, #48]
	mov	r0, r4
	ldr	r3, [r6, #40]
	cmp	r1, r7
	ldr	r2, [r5, #48]
	moveq	r7, #0
	str	r7, [r3]
	ldr	r3, [r5, #36]
	cmp	r2, r9
	moveq	r9, #0
	str	r9, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L235:
	add	r1, r4, r3
	mov	ip, #1
	cmp	r2, r1
	bcs	.L233
	rsb	r3, r3, r2
	mov	r0, ip
	mov	r7, #0
	b	.L216
.L217:
	add	r1, r4, r2
	cmp	r8, r1
	rsbls	r8, r2, r8
	bhi	.L231
	cmp	ip, #0
	bne	.L238
.L220:
	cmp	r0, #2
	bne	.L232
	ldr	r0, [fp, #-56]
	ldr	r2, [fp, #-48]
	ldr	r8, .L239
	add	r1, r2, r0
	ldr	r0, [fp, #-52]
	mov	r2, r3
	add	r3, r3, r10
	add	r0, r0, r10
	ldr	r10, [r8, #24]
	add	r9, r3, r7
	str	r3, [fp, #-56]
	blx	r10
	ldr	r0, [fp, #-52]
	ldr	r3, [fp, #-56]
	mov	r2, r7
	ldr	r8, [r8, #24]
	add	r0, r0, r3
	ldr	r1, [fp, #-48]
	blx	r8
	b	.L221
.L229:
	mov	ip, #1
.L233:
	mov	r3, r4
	mov	r0, ip
	mov	r7, #0
	b	.L216
.L231:
	cmp	ip, #0
	mov	r8, r4
	beq	.L220
.L238:
	ldr	r3, .L239
	add	r9, r4, r10
	ldr	ip, [fp, #-56]
	ldr	r2, [fp, #-52]
	ldr	r1, [fp, #-48]
	add	r7, r4, ip
	add	r0, r2, r10
	ldr	r3, [r3, #24]
	add	r1, r1, ip
	mov	r2, r4
	blx	r3
	b	.L221
.L232:
	mov	r9, ip
	mov	r2, #1
	b	.L219
.L224:
	ldr	r2, [fp, #-48]
	rsb	r8, r3, r8
	ldr	r1, [fp, #-56]
	add	r7, r8, r9
	ldr	ip, .L239
	add	r1, r2, r1
	str	r3, [fp, #-56]
	mov	r2, r3
	ldr	r3, [fp, #-52]
	ldr	ip, [ip, #24]
	add	r0, r3, r10
	blx	ip
	ldr	r3, [fp, #-56]
	ldr	r1, .L239
	mov	r2, r8
	add	r0, r3, r10
	ldr	r10, [fp, #-48]
	ldr	r3, [fp, #-52]
	add	r0, r3, r0
	ldr	r3, [r1, #24]
	mov	r1, r10
	blx	r3
	ldr	r2, .L239
	add	r1, r10, r8
	ldr	r0, [fp, #-52]
	ldr	r3, [r2, #24]
	mov	r2, r9
	blx	r3
	b	.L221
.L236:
	ldr	r3, .L239
	ldr	r1, [fp, #-56]
	ldr	r2, [fp, #-52]
	ldr	ip, [fp, #-48]
	add	r0, r2, r10
	mov	r2, r8
	ldr	r10, [r3, #24]
	add	r8, r8, r1
	add	r1, ip, r1
	str	r3, [fp, #-56]
	blx	r10
	ldr	r3, [fp, #-56]
	ldr	ip, [fp, #-48]
	mov	r2, r9
	ldr	r0, [fp, #-52]
	add	r7, r8, r9
	ldr	r3, [r3, #24]
	add	r1, ip, r8
	blx	r3
	b	.L221
.L237:
	ldr	r0, [fp, #-56]
	mov	r2, r8
	ldr	r1, [fp, #-48]
	mov	r7, r9
	ldr	r3, .L239
	add	r1, r1, r0
	ldr	r0, [fp, #-52]
	ldr	r8, [r3, #24]
	add	r0, r0, r10
	str	r3, [fp, #-56]
	blx	r8
	ldr	r3, [fp, #-56]
	mov	r2, r9
	ldr	r1, [fp, #-48]
	ldr	r0, [fp, #-52]
	ldr	r3, [r3, #24]
	blx	r3
	b	.L221
.L240:
	.align	2
.L239:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	RBUF_CopyData, .-RBUF_CopyData
	.align	2
	.global	RBUF_UpdateAttr
	.type	RBUF_UpdateAttr, %function
RBUF_UpdateAttr:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	ldrne	r3, [r1, #32]
	strne	r3, [r0, #32]
	ldrne	r3, [r1, #28]
	strne	r3, [r0, #28]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	RBUF_UpdateAttr, .-RBUF_UpdateAttr
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
