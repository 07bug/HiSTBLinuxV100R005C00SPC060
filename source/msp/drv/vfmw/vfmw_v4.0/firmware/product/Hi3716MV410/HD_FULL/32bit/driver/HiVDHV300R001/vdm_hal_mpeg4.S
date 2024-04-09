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
	.file	"vdm_hal_mpeg4.c"
	.text
	.align	2
	.global	MP4HAL_V300R001_Log2bin
	.type	MP4HAL_V300R001_Log2bin, %function
MP4HAL_V300R001_Log2bin:
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
	mov	r3, #0
.L3:
	add	r3, r3, #1
	movs	r0, r0, lsr #1
	uxth	r3, r3
	bne	.L3
	sxth	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP4HAL_V300R001_Log2bin, .-MP4HAL_V300R001_Log2bin
	.align	2
	.global	MP4HAL_V300R001_CfgReg
	.type	MP4HAL_V300R001_CfgReg, %function
MP4HAL_V300R001_CfgReg:
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
	add	r3, r0, #12288
	mov	r9, r0
	str	r3, [fp, #-48]
	ldr	ip, [r3, #2288]
	mov	r8, r1
	cmp	ip, #0
	beq	.L8
	mov	r3, r0
	mvn	r4, #0
	mov	r0, #0
.L9:
	ldr	r1, [r3, #256]
	cmp	r1, #0
	beq	.L12
	ldr	lr, [r3, #248]
	bic	r1, r1, #15
	cmp	lr, #0
	beq	.L12
	cmp	r4, r1
	movcs	r4, r1
.L12:
	ldr	r1, [r3, #260]
	cmp	r1, #0
	beq	.L10
	ldr	lr, [r3, #252]
	bic	r1, r1, #15
	cmp	lr, #0
	beq	.L10
	cmp	r4, r1
	movcs	r4, r1
.L10:
	add	r0, r0, #1
	add	r3, r3, #28
	cmp	r0, ip
	bne	.L9
	cmn	r4, #1
	beq	.L8
	str	r4, [r2]
	cmp	r8, #0
	ldrh	r7, [r9, #164]
	ldrh	r3, [r9, #166]
	mul	r7, r3, r7
	sub	r7, r7, #1
	ubfx	r7, r7, #0, #20
	orr	r7, r7, #1107296256
	orr	r7, r7, #4194304
	ble	.L54
	ldr	r6, .L57
	mov	r3, r8
	mov	r2, #1
	ldr	r1, .L57+4
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L57+8
	ldr	r5, [r6, #68]
	blx	r5
	mov	r2, r7
	ldr	r3, [r6, #68]
	mov	r0, #3
	ldr	r1, .L57+12
	blx	r3
	ldr	r3, [fp, #-48]
	ldr	r5, .L57+16
	mov	r0, #32
	ldr	r10, [r6, #68]
	ldr	r7, [r3, #2372]
	mov	r3, #1
	ldr	r2, .L57+8
	str	r3, [sp]
	mov	r3, r8
	ldr	r1, .L57+4
	and	r7, r7, #1
	blx	r10
	movw	r10, #1208
	mla	r10, r10, r8, r5
	mov	r7, r7, asl #30
	orr	r7, r7, #114688
	ldr	r3, [r6, #68]
	orr	r7, r7, #2
	ldr	r1, .L57+20
	mov	r0, #3
	mov	r2, r7
	blx	r3
	mov	r3, #1
	str	r3, [sp]
	mov	r0, #32
	ldr	r7, [r10, #48]
	mov	r3, r8
	ldr	ip, [r6, #68]
	bic	r7, r7, #15
	ldr	r2, .L57+8
	ldr	r1, .L57+4
	blx	ip
	mov	r2, r7
	ldr	r3, [r6, #68]
	mov	r0, #3
	ldr	r1, .L57+24
	blx	r3
	ldr	r7, [r10, #32]
	mov	r3, #1
	ldr	r2, .L57+8
	bic	r7, r7, #15
	str	r3, [sp]
	ldr	r1, .L57+4
	mov	r3, r8
	ldr	r10, [r6, #68]
	mov	r0, #32
	blx	r10
	mov	r2, r7
	ldr	r3, [r6, #68]
	mov	r0, #3
	ldr	r1, .L57+28
	blx	r3
	mov	r3, #1
	ldr	r7, [r6, #68]
	mov	r0, #32
	str	r3, [sp]
	mov	r3, r8
	ldr	r2, .L57+8
	ldr	r1, .L57+4
	blx	r7
.L17:
	ldr	r3, [r6, #68]
	mov	r2, r4
	ldr	r1, .L57+32
	mov	r0, #3
	blx	r3
	ldrh	r3, [r9, #164]
	cmp	r3, #120
	bls	.L55
	cmp	r8, #0
	beq	.L29
	cmp	r8, #1
	beq	.L36
.L25:
	cmp	r8, #0
	bgt	.L24
.L20:
	movw	r4, #1208
	movw	r3, #3075
	mul	r4, r4, r8
	movt	r3, 48
	ldr	r1, .L57+36
	mov	r0, #3
	ldr	r2, [r5, r4]
	str	r3, [r2, #60]
	ldr	r2, [r5, r4]
	str	r3, [r2, #64]
	ldr	r2, [r5, r4]
	str	r3, [r2, #68]
	ldr	r2, [r5, r4]
	str	r3, [r2, #72]
	ldr	r2, [r5, r4]
	str	r3, [r2, #76]
	ldr	r2, [r5, r4]
	str	r3, [r2, #80]
	ldr	r2, [r5, r4]
	str	r3, [r2, #84]
	ldr	r3, [r5, r4]
	ldr	r2, [r9, #212]
	bic	r2, r2, #15
	str	r2, [r3, #96]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r2, [fp, #-48]
	ldr	r3, [r5, r4]
	mov	r0, #3
	ldrh	r7, [r9, #166]
	ldr	r2, [r2, #2316]
	ldr	r1, .L57+40
	str	r2, [r3, #100]
	ldr	r3, [r6, #68]
	blx	r3
	ldrh	r3, [r9, #164]
	cmp	r3, #0
	mov	r3, r3, asl #4
	ble	.L27
	cmp	r3, #2048
	movle	r4, #16
	ble	.L28
.L27:
	sub	r2, r3, #2048
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r4, #32
	bcc	.L28
	sub	r2, r3, #4096
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r4, #48
	bcs	.L56
.L28:
	mov	ip, r7, asl #4
	ldr	r3, [fp, #-48]
	add	ip, ip, #31
	add	r2, r7, #1
	movw	r0, #1208
	ldr	r1, .L57+44
	mov	ip, ip, lsr #5
	ldr	r3, [r3, #2316]
	mul	r8, r0, r8
	mov	r2, r2, lsr #1
	mul	r4, ip, r4
	mov	r0, #3
	mul	r2, r3, r2
	mov	r7, #0
	ldr	r3, [r5, r8]
	add	r9, r5, r8
	add	r2, r2, r4, lsl #4
	mov	r4, r4, asl #5
	mov	r2, r2, asl #1
	str	r2, [r3, #104]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r5, r8]
	mov	r2, r7
	ldr	r1, .L57+48
	mov	r0, #3
	str	r4, [r3, #108]
	ldr	r3, [r5, r8]
	str	r7, [r3, #152]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r9, #1184]
	ldr	ip, [r5, r8]
	mov	r0, #3
	ldr	r1, .L57+52
	mov	r2, r3
	str	r3, [ip, #144]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r5, r8]
	mov	r0, r7
	mvn	r2, #0
	str	r2, [r3, #32]
.L51:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L55:
	cmp	r8, #0
	beq	.L31
	cmp	r8, #1
	bne	.L25
	mov	r4, #65536
	b	.L21
.L54:
	movw	r10, #1208
	ldr	r5, .L57+16
	mul	r10, r10, r8
	ldr	r6, .L57
	mov	r2, r7
	ldr	r1, .L57+12
	mov	r0, #3
	add	r3, r5, r10
	str	r3, [fp, #-52]
	ldr	ip, [r5, r10]
	str	r7, [ip, #8]
	ldr	r7, [r6, #68]
	blx	r7
	ldr	r3, [fp, #-48]
	ldr	ip, [r5, r10]
	mov	r0, #3
	ldr	r1, .L57+20
	ldr	r2, [r3, #2372]
	and	r2, r2, #1
	mov	r2, r2, asl #30
	orr	r2, r2, #114688
	orr	r2, r2, #2
	str	r2, [ip, #12]
	ldr	r7, [r6, #68]
	blx	r7
	ldr	r3, [fp, #-52]
	ldr	ip, [r5, r10]
	mov	r0, #3
	ldr	r1, .L57+24
	ldr	r2, [r3, #48]
	bic	r2, r2, #15
	str	r2, [ip, #16]
	ldr	r7, [r6, #68]
	blx	r7
	ldr	r3, [fp, #-52]
	mov	r0, #3
	ldr	r1, .L57+28
	ldr	r2, [r3, #32]
	ldr	r3, [r5, r10]
	bic	r2, r2, #15
	str	r2, [r3, #20]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r5, r10]
	str	r4, [r3, #24]
	b	.L17
.L36:
	mov	r4, #0
.L21:
	movw	r0, #49156
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	r3, .L57+56
	cmp	r4, #0
	biceq	r1, r0, #65536
	orrne	r1, r0, #65536
	ldr	r0, [r3]
	add	r0, r0, #4
	bl	MEM_WritePhyWord
.L24:
	mov	r0, #0
	ldr	r4, [r6, #68]
	mov	r3, r8
	str	r0, [sp]
	ldr	r2, .L57+8
	ldr	r1, .L57+60
	blx	r4
	mvn	r0, #0
	b	.L51
.L56:
	sub	r3, r3, #6144
	sub	r3, r3, #1
	cmp	r3, #2048
	movcs	r4, #16
	movcc	r4, #64
	b	.L28
.L8:
	ldr	r3, .L57
	mvn	r2, #0
	ldr	r1, .L57+64
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L51
.L31:
	movw	r0, #49156
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	orr	r1, r0, #65536
.L30:
	ldr	r3, .L57+68
	ldr	r0, [r3]
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	b	.L20
.L29:
	movw	r0, #49156
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	bic	r1, r0, #65536
	b	.L30
.L58:
	.align	2
.L57:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	.word	.LANCHOR0
	.word	.LC1
	.word	g_HwMem
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC6
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC12
	.word	s_RegPhyBaseAddr_1
	.word	.LC7
	.word	.LC0
	.word	s_RegPhyBaseAddr
	UNWIND(.fnend)
	.size	MP4HAL_V300R001_CfgReg, .-MP4HAL_V300R001_CfgReg
	.global	__aeabi_idiv
	.align	2
	.global	MP4HAL_V300R001_CfgDnMsg
	.type	MP4HAL_V300R001_CfgDnMsg, %function
MP4HAL_V300R001_CfgDnMsg:
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
	ldrh	r2, [r0, #166]
	ldrh	r3, [r0, #164]
	mov	r7, r0
	str	r1, [fp, #-48]
	mul	r3, r3, r2
	cmp	r3, #0
	beq	.L82
	mov	r6, #0
.L61:
	add	r6, r6, #1
	movs	r3, r3, lsr #1
	uxth	r6, r6
	bne	.L61
.L60:
	ldr	r2, [fp, #-48]
	movw	r3, #1208
	ldr	r10, .L101
	mla	r3, r3, r2, r10
	ldr	r0, [r3, #48]
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L93
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	ldr	r4, .L101+4
	cmp	r3, #1
	beq	.L94
	mov	r8, #0
	ldr	r1, .L101+8
	mov	r2, r8
	str	r8, [r5]
	mov	r0, #4
	ldr	r3, [r4, #68]
	blx	r3
	ldrb	r2, [r7, #3]	@ zero_extendqisi2
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	mov	r0, #4
	and	r2, r2, #31
	ldr	r1, .L101+12
	and	r6, r6, #15
	mov	r3, r3, asl #31
	orr	r2, r3, r2, asl #26
	str	r2, [r5, #4]
	ldr	r3, [r4, #68]
	blx	r3
	ldrb	r0, [r7]	@ zero_extendqisi2
	ldrb	lr, [r7, #15]	@ zero_extendqisi2
	cmp	r0, #2
	streqb	r8, [r7, #12]
	and	lr, lr, #1
	ldrb	r9, [r7, #13]	@ zero_extendqisi2
	moveq	ip, r8
	add	r8, r7, #12288
	and	r9, r9, #1
	and	r0, r0, #3
	ldr	r3, [r8, #2328]
	ldr	r1, [r8, #2332]
	and	r3, r3, #3
	ldr	r2, [r8, #2336]
	ldrneb	ip, [r7, #12]	@ zero_extendqisi2
	orr	r3, lr, r3, asl #26
	and	lr, r2, #3
	orr	r3, r3, r1, asl #30
	ldrb	r1, [r7, #14]	@ zero_extendqisi2
	orr	r2, r3, lr, asl #28
	ldrb	lr, [r7, #11]	@ zero_extendqisi2
	and	r1, r1, #1
	ldrb	r3, [r7, #10]	@ zero_extendqisi2
	and	lr, lr, #1
	orr	r1, r2, r1, asl #1
	ldrb	r2, [r7, #9]	@ zero_extendqisi2
	orr	r1, r1, r9, asl #2
	mov	r3, r3, asl #7
	orr	r1, r1, lr, asl #4
	ldrb	r9, [r7, #8]	@ zero_extendqisi2
	orr	r0, r1, r0, asl #5
	ldrb	r1, [r7, #7]	@ zero_extendqisi2
	uxtb	r3, r3
	and	r2, r2, #7
	ldrb	lr, [r7, #6]	@ zero_extendqisi2
	orr	r0, r0, r3
	and	r1, r1, #7
	orr	r0, r0, r2, asl #8
	and	r9, r9, #7
	and	lr, lr, #31
	orr	r3, r0, r1, asl #11
	ldr	r1, .L101+16
	orr	r3, r3, r9, asl #14
	mov	r0, #4
	orr	r2, r3, lr, asl #17
	ldr	r9, .L101+4
	orr	r6, r2, r6, asl #22
	andne	ip, ip, #1
	movne	ip, ip, asl #3
	orr	r2, r6, ip
	str	r2, [r5, #8]
	ldr	r3, [r4, #68]
	blx	r3
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L95
.L65:
	ldrh	r3, [r7, #164]
	mov	r0, #4
	ldrh	r2, [r7, #166]
	sub	r3, r3, #1
	ldr	r1, .L101+20
	sub	r2, r2, #1
	ldr	r6, .L101+4
	uxth	r3, r3
	orr	r2, r3, r2, asl #16
	str	r2, [r5, #16]
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r2, [r8, #2320]
	ldr	r3, [r8, #2324]
	mov	r0, #4
	ldr	r1, .L101+24
	orr	r2, r3, r2, asl #16
	str	r2, [r5, #20]
	ldr	r3, [r4, #68]
	blx	r3
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L96
.L68:
	mov	r6, #0
	ldr	r1, .L101+28
	str	r6, [r5, #32]
	mov	r2, r6
	ldr	r3, [r4, #68]
	mov	r0, #4
	blx	r3
	str	r6, [r5, #36]
	mov	r2, r6
	ldr	r3, [r4, #68]
	ldr	r1, .L101+32
	mov	r0, #4
	blx	r3
	str	r6, [r5, #40]
	mov	r2, r6
	ldr	r3, [r4, #68]
	ldr	r1, .L101+36
	mov	r0, #4
	blx	r3
	str	r6, [r5, #44]
	mov	r2, r6
	ldr	r3, [r4, #68]
	ldr	r1, .L101+40
	mov	r0, #4
	blx	r3
	ldr	r2, [r8, #2304]
	ldr	r1, .L101+44
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r5, #48]
	ldr	r3, [r4, #68]
	movw	r9, #1208
	blx	r3
	ldr	r2, [r7, #220]
	ldr	r1, .L101+48
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r5, #52]
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r2, [r7, #224]
	ldr	r1, .L101+52
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r5, #56]
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r2, [r7, #228]
	ldr	r1, .L101+56
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r5, #60]
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r2, [r7, #232]
	ldr	r1, .L101+60
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r5, #64]
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r3, [fp, #-48]
	ldr	r1, .L101+64
	mov	r0, #4
	mla	r9, r9, r3, r10
	ldr	r2, [r9, #1148]
	bic	r2, r2, #15
	str	r2, [r5, #68]
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r2, [r9, #1140]
	ldr	r3, [r4, #68]
	mov	r0, #4
	bic	r2, r2, #15
	ldr	r1, .L101+68
	str	r2, [r5, #72]
	blx	r3
	ldrb	r3, [r7]	@ zero_extendqisi2
	strb	r6, [r7, #157]
	cmp	r3, #3
	beq	.L97
.L74:
	ldrb	r3, [r7, #153]	@ zero_extendqisi2
	and	ip, r3, #1
	strb	r3, [r7, #152]
	mov	r1, ip, asl #3
.L76:
	ldrb	r2, [r7, #156]	@ zero_extendqisi2
	mov	r0, #4
	ldrb	r3, [r7, #155]	@ zero_extendqisi2
	and	r2, r2, #1
	and	r3, r3, #1
	orr	r2, r3, r2, asl #1
	ldr	r3, [r4, #68]
	orr	r2, r2, r1
	ldr	r1, .L101+72
	orr	r2, r2, ip, asl #2
	str	r2, [r5, #76]
	blx	r3
	ldr	r2, [r8, #2340]
	ldr	r3, [r4, #68]
	mov	r0, #4
	ldr	r1, .L101+76
	str	r2, [r5, #80]
	blx	r3
	ldr	r2, [r8, #2344]
	ldr	r3, [r4, #68]
	mov	r0, #4
	ldr	r1, .L101+80
	str	r2, [r5, #84]
	blx	r3
	ldr	r2, [r8, #2348]
	ldr	r3, [r4, #68]
	mov	r0, #4
	ldr	r1, .L101+84
	str	r2, [r5, #88]
	blx	r3
	ldr	r2, [r8, #2352]
	ldr	r3, [r4, #68]
	mov	r0, #4
	ldr	r1, .L101+88
	str	r2, [r5, #92]
	blx	r3
	ldr	r2, [r8, #2356]
	ldr	r3, [r4, #68]
	mov	r0, #4
	ldr	r1, .L101+92
	str	r2, [r5, #96]
	blx	r3
	ldr	r2, [r8, #2360]
	ldr	r3, [r4, #68]
	mov	r0, #4
	ldr	r1, .L101+96
	str	r2, [r5, #100]
	blx	r3
	ldr	r2, [r8, #2364]
	ldr	r3, [r4, #68]
	mov	r0, #4
	ldr	r1, .L101+100
	str	r2, [r5, #104]
	blx	r3
	ldr	r2, [r8, #2368]
	ldr	r3, [r4, #68]
	mov	r0, #4
	ldr	r1, .L101+104
	str	r2, [r5, #108]
	blx	r3
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L98
.L77:
	ldr	r2, [fp, #-48]
	movw	r3, #1208
	ldr	r4, [r4, #68]
	mov	r0, #4
	ldr	r1, .L101+108
	mla	r3, r3, r2, r10
	ldr	r2, [r3, #1136]
	bic	r2, r2, #15
	str	r2, [r5, #240]
	ldr	r2, [r3, #48]
	add	r2, r2, #256
	str	r2, [r5, #252]
	blx	r4
	mov	r0, #0
.L63:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L94:
	mov	r9, #4
	ldr	r1, .L101+8
	mov	r2, r9
	str	r9, [r5]
	mov	r0, r9
	ldr	r3, [r4, #68]
	blx	r3
	ldrb	r2, [r7, #4]	@ zero_extendqisi2
	ldrb	r1, [r7, #3]	@ zero_extendqisi2
	mov	r0, r9
	ldrb	r3, [r7, #5]	@ zero_extendqisi2
	and	r2, r2, #127
	and	r1, r1, #31
	add	r8, r7, #12288
	mov	r2, r2, asl #5
	sub	r3, r3, #1
	orr	r2, r2, r1, asl #26
	and	r3, r3, #31
	orr	r2, r2, r3
	ldr	r1, .L101+12
	str	r2, [r5, #4]
	ldr	r3, [r4, #68]
	blx	r3
	ldrb	r3, [r7]	@ zero_extendqisi2
	and	r2, r6, #15
	mov	r0, r9
	and	r3, r3, #3
	ldr	r1, .L101+16
	mov	r3, r3, asl #5
	orr	r2, r3, r2, asl #22
	str	r2, [r5, #8]
	ldr	r3, [r4, #68]
	blx	r3
	b	.L65
.L98:
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L77
	mov	r9, #0
	mov	r8, r7
	str	r7, [fp, #-56]
	str	r5, [fp, #-52]
.L78:
	ldr	r3, [fp, #-52]
	add	r7, r9, #112
	mov	r5, r8
	mov	r6, #0
	add	r7, r3, r7
.L79:
	ldrb	r3, [r5, #56]	@ zero_extendqisi2
	add	r2, r6, r6, lsr #31
	ldrb	ip, [r5, #40]	@ zero_extendqisi2
	add	r6, r6, #1
	ldrb	r1, [r5, #24]	@ zero_extendqisi2
	add	r2, r9, r2, asr #1
	ldrb	r0, [r5, #72]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	orr	r3, r3, ip, asl #8
	add	r2, r2, #24
	orr	r3, r3, r1
	ldr	r1, .L101+112
	orr	r3, r3, r0, asl #24
	mov	r0, #4
	str	r3, [r7], #4
	add	r5, r5, #8
	ldr	ip, [r4, #68]
	blx	ip
	cmp	r6, #2
	bne	.L79
	add	r9, r9, #8
	add	r8, r8, #1
	cmp	r9, #64
	bne	.L78
	ldr	r8, [fp, #-56]
	mov	r9, #0
.L80:
	ldr	r3, [fp, #-52]
	add	r7, r9, #176
	mov	r5, r8
	mov	r6, #0
	add	r7, r3, r7
.L81:
	ldrb	r3, [r5, #120]	@ zero_extendqisi2
	add	r2, r6, r6, lsr #31
	ldrb	ip, [r5, #104]	@ zero_extendqisi2
	add	r6, r6, #1
	ldrb	r1, [r5, #88]	@ zero_extendqisi2
	add	r2, r9, r2, asr #1
	ldrb	r0, [r5, #136]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	orr	r3, r3, ip, asl #8
	add	r2, r2, #24
	orr	r3, r3, r1
	ldr	r1, .L101+112
	orr	r3, r3, r0, asl #24
	mov	r0, #4
	str	r3, [r7], #4
	add	r5, r5, #8
	ldr	ip, [r4, #68]
	blx	ip
	cmp	r6, #2
	bne	.L81
	add	r9, r9, #8
	add	r8, r8, #1
	cmp	r9, #64
	bne	.L80
	ldr	r5, [fp, #-52]
	b	.L77
.L97:
	ldr	r3, [r8, #2332]
	cmp	r3, #1
	beq	.L99
	bhi	.L74
	ldrb	r1, [r7, #152]	@ zero_extendqisi2
	ldrb	r2, [r7, #153]	@ zero_extendqisi2
	and	r1, r1, #1
	and	ip, r2, #1
	mov	r1, r1, asl #3
	b	.L76
.L96:
	ldr	r3, [r8, #2332]
	cmp	r3, #1
	bne	.L68
	ldrb	r9, [r7, #154]	@ zero_extendqisi2
	cmp	r9, #1
	beq	.L100
	ldr	r2, [r8, #2356]
	mov	r0, #4
	ldrb	r1, [r7, #11]	@ zero_extendqisi2
	movs	r2, r2, asl r1
	ldreq	r2, [r8, #2336]
	ldrne	r1, [r8, #2336]
	moveq	r3, r3, asl r2
	movne	r3, r3, asl r1
	moveq	r3, r3, asr #1
	addne	r2, r2, r3, asr #1
	subeq	r3, r3, #1
	movne	r2, r2, lsr r1
	moveq	r2, r3, lsr r2
	ldr	r1, .L101+116
	str	r2, [r5, #24]
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r3, [r8, #2360]
	ldrb	r2, [r7, #11]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	cmp	r3, #0
	ble	.L72
	ldr	r1, [r8, #2336]
	mov	r2, #1
	mov	r2, r2, asl r1
	add	r3, r3, r2, asr #1
	mov	r2, r3, asr r1
.L73:
	str	r2, [r5, #28]
	mov	r0, #4
	ldr	r3, [r4, #68]
	ldr	r1, .L101+120
	blx	r3
	b	.L68
.L95:
	ldr	r3, [r7, #204]
	mov	r0, #4
	ldr	r2, [r7, #208]
	ldr	r1, .L101+124
	mov	r3, r3, asl #1
	uxth	r3, r3
	orr	r2, r3, r2, asl #17
	str	r2, [r5, #12]
	ldr	r3, [r9, #68]
	blx	r3
	b	.L65
.L82:
	mov	r6, r3
	b	.L60
.L99:
	ldrb	r2, [r7, #153]	@ zero_extendqisi2
	mov	r1, #8
	strb	r3, [r7, #152]
	and	ip, r2, #1
	b	.L76
.L72:
	ldr	r2, [r8, #2336]
	mov	r1, #1
	mov	r1, r1, asl r2
	add	r3, r3, r1, asr #1
	sub	r3, r3, #1
	mov	r2, r3, asr r2
	b	.L73
.L100:
	ldr	r3, [r8, #2336]
	ldrb	r1, [r7, #11]	@ zero_extendqisi2
	ldr	r0, [r8, #2356]
	rsb	r1, r1, r3
	mov	r1, r9, asl r1
	bl	__aeabi_idiv
	ldr	r1, .L101+116
	mov	r2, r0
	str	r0, [r5, #24]
	mov	r0, #4
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r8, #2336]
	ldrb	r1, [r7, #11]	@ zero_extendqisi2
	ldr	r0, [r8, #2360]
	rsb	r1, r1, r3
	mov	r1, r9, asl r1
	bl	__aeabi_idiv
	ldr	r1, .L101+120
	str	r0, [r5, #28]
	mov	r2, r0
	ldr	r3, [r6, #68]
	mov	r0, #4
	blx	r3
	b	.L68
.L93:
	ldr	r3, .L101+4
	movw	r2, #949
	ldr	r1, .L101+128
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L63
.L102:
	.align	2
.L101:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC18
	.word	.LC19
	.word	.LC22
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC30
	.word	.LC31
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC35
	.word	.LC36
	.word	.LC37
	.word	.LC38
	.word	.LC39
	.word	.LC40
	.word	.LC41
	.word	.LC43
	.word	.LC42
	.word	.LC20
	.word	.LC21
	.word	.LC17
	.word	.LC13
	UNWIND(.fnend)
	.size	MP4HAL_V300R001_CfgDnMsg, .-MP4HAL_V300R001_CfgDnMsg
	.align	2
	.global	MP4HAL_V300R001_WriteSlicMsg
	.type	MP4HAL_V300R001_WriteSlicMsg, %function
MP4HAL_V300R001_WriteSlicMsg:
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
	ldr	ip, .L130
	movw	r3, #1208
	mov	lr, r0
	str	r0, [fp, #-76]
	add	r0, r0, #12288
	mla	r1, r3, r1, ip
	ldr	r7, [r0, #2288]
	add	r3, lr, #240
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	mov	r4, #0
	str	r4, [fp, #-48]
	ldr	r9, [r1, #48]
	add	r5, r9, #256
	mov	r0, r5
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-56]
	beq	.L128
	ldr	r3, [fp, #-76]
	ldr	r3, [r3, #264]
	cmp	r3, #0
	bne	.L129
.L106:
	cmp	r7, #0
	ble	.L123
	ldr	r8, .L130+4
	mov	r3, r3, asl #5
	mov	r4, #0
	str	r3, [fp, #-68]
	add	r3, r3, r5
	str	r3, [fp, #-72]
.L122:
	mov	r5, r4, asl #5
	ldr	r3, [fp, #-60]
	cmp	r4, #0
	sub	r5, r5, r4, asl #2
	add	r5, r3, r5
	ble	.L111
	ldr	r2, [r5, #24]
	ldr	r3, [r5, #-4]
	cmp	r2, r3
	bls	.L112
.L111:
	ldr	r10, [r5, #16]
	mov	r9, #0
	ldrb	r3, [r5, #6]	@ zero_extendqisi2
	mov	r1, r9
	and	r0, r10, #15
	ldr	ip, [r5, #8]
	ldr	lr, [fp, #-68]
	mov	r2, #0
	add	r3, r3, r0, lsl #3
	bfi	r1, ip, #0, #24
	bfi	r2, r3, #0, #7
	str	r1, [fp, #-48]
	strb	r2, [fp, #-45]
	add	r6, lr, r4, lsl #3
	ldr	r2, [fp, #-48]
	mov	r0, #4
	ldr	r3, [fp, #-56]
	bic	r10, r10, #15
	ldr	r1, .L130+8
	add	r4, r4, #1
	str	r2, [r3, r6, asl #2]
	add	r6, r6, #1
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r2, [fp, #-64]
	ldr	ip, [fp, #-56]
	mov	r3, r9
	rsb	r10, r2, r10
	ldr	r1, .L130+12
	bfi	r3, r10, #0, #24
	mov	r0, #4
	str	r3, [fp, #-48]
	mov	r2, r3
	str	r3, [ip, r6, asl #2]
	ldr	r3, [r8, #68]
	mov	r6, r6, asl #2
	blx	r3
	ldr	r10, [r5, #20]
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	mov	r1, r9
	and	ip, r10, #15
	ldr	r0, [r5, #12]
	mov	r2, #0
	add	r3, r3, ip, lsl #3
	bfi	r1, r0, #0, #24
	bfi	r2, r3, #0, #7
	str	r1, [fp, #-48]
	strb	r2, [fp, #-45]
	add	r3, r6, #4
	ldr	ip, [fp, #-56]
	mov	r0, #4
	ldr	r2, [fp, #-48]
	ldr	r1, .L130+16
	str	r2, [ip, r3]
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r3, [r5, #20]
	ldr	r1, .L130+20
	mov	r0, #4
	cmp	r3, r9
	bicne	r10, r10, #15
	streq	r3, [fp, #-48]
	ldrne	r3, [fp, #-64]
	rsbne	r10, r3, r10
	add	r3, r6, #8
	bfine	r9, r10, #0, #24
	ldr	r10, [fp, #-56]
	strne	r9, [fp, #-48]
	mov	r9, #0
	ldr	r2, [fp, #-48]
	str	r2, [r10, r3]
	ldr	r3, [r8, #68]
	blx	r3
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	ldrb	r2, [r5, #4]	@ zero_extendqisi2
	add	ip, r6, #12
	and	r3, r3, #31
	str	r9, [fp, #-48]
	bfi	r3, r2, #5, #2
	ldrb	r2, [r5, #3]	@ zero_extendqisi2
	strb	r3, [fp, #-48]
	mov	r0, #4
	ldrh	r3, [fp, #-48]
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	bfi	r3, r2, #7, #3
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	strh	r3, [fp, #-48]	@ movhi
	mov	r3, r3, lsr #8
	bfi	r3, r1, #2, #3
	ldr	r1, .L130+24
	bfi	r3, r2, #5, #3
	strb	r3, [fp, #-47]
	ldr	r2, [fp, #-48]
	str	r2, [r10, ip]
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r1, [r5, #24]
	add	r3, r6, #16
	mov	r2, r9
	mov	r0, #4
	bfi	r2, r1, #0, #20
	ldr	r1, .L130+28
	str	r2, [fp, #-48]
	str	r2, [r10, r3]
	ldr	r3, [r8, #68]
	blx	r3
	cmp	r7, r4
	ble	.L115
	mov	r3, r4, asl #5
	ldr	r0, [fp, #-60]
	sub	r3, r3, r4, asl #2
	ldr	r2, [r5, #24]
	add	r1, r0, r3
	ldr	r1, [r1, #24]
	cmp	r2, r1
	bcc	.L115
	sub	r3, r3, #28
	add	r3, r0, r3
	b	.L116
.L118:
	ldr	r1, [r3, #52]
	cmp	r1, r2
	bhi	.L120
.L116:
	add	r4, r4, #1
	add	r3, r3, #28
	cmp	r7, r4
	bne	.L118
.L124:
	ldr	r3, [fp, #-76]
	mov	r9, #0
	mov	r5, r9
	ldrh	r2, [r3, #164]
	ldrh	r3, [r3, #166]
	mul	r3, r3, r2
	sub	r3, r3, #1
.L121:
	ldr	r10, [fp, #-56]
	add	ip, r6, #20
	add	r6, r6, #24
	ldr	r1, .L130+32
	mov	r2, #0
	mov	r0, #4
	bfi	r2, r3, #0, #20
	str	r2, [fp, #-48]
	str	r2, [r10, ip]
	sub	r4, r4, #1
	ldr	r3, [r8, #68]
	blx	r3
	str	r9, [r10, r6]
	mov	r2, r5
	ldr	r1, .L130+36
	mov	r0, #4
	ldr	r3, [r8, #68]
	str	r5, [fp, #-48]
	blx	r3
.L112:
	add	r4, r4, #1
	cmp	r7, r4
	bgt	.L122
.L123:
	mov	r0, #0
.L105:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L115:
	cmp	r7, r4
	beq	.L124
.L120:
	ldr	r2, [fp, #-72]
	mov	r5, r4, asl #5
	sub	r3, r5, r4, asl #2
	add	r5, r5, r2
	ldr	r2, [fp, #-60]
	add	r3, r2, r3
	mov	r9, r5
	ldr	r3, [r3, #24]
	sub	r3, r3, #1
	b	.L121
.L129:
	ldr	r10, [fp, #-76]
	mov	r0, #4
	ldr	r3, [fp, #-48]
	add	r9, r9, #288
	ldr	r6, .L130+4
	ldr	r8, [r10, #256]
	bfi	r3, r4, #0, #24
	ldrb	r2, [r10, #246]	@ zero_extendqisi2
	and	r1, r8, #15
	str	r3, [fp, #-48]
	mov	r3, r3, lsr #24
	add	r2, r2, r1, lsl #3
	ldr	r1, .L130+8
	bfi	r3, r2, #0, #7
	strb	r3, [fp, #-45]
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-56]
	str	r2, [r3]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r2, [fp, #-64]
	bic	r3, r8, #15
	ldr	r1, .L130+12
	rsb	r3, r2, r3
	mov	r2, r4
	bfi	r2, r3, #0, #24
	ldr	r3, [fp, #-56]
	str	r2, [fp, #-48]
	mov	r0, #4
	str	r2, [r3, #4]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r8, [r10, #260]
	ldrb	r3, [r10, #247]	@ zero_extendqisi2
	mov	r2, #0
	and	ip, r8, #15
	str	r4, [fp, #-48]
	ldr	r1, .L130+16
	mov	r0, #4
	add	r3, r3, ip, lsl #3
	bfi	r2, r3, #0, #7
	strb	r2, [fp, #-45]
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-56]
	str	r2, [r3, #8]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r10, #260]
	ldr	r10, [fp, #-56]
	mov	r0, #4
	cmp	r3, #0
	ldr	r1, .L130+20
	bicne	r3, r8, #15
	streq	r3, [fp, #-48]
	ldrne	r2, [fp, #-64]
	rsbne	r3, r2, r3
	bfine	r4, r3, #0, #24
	strne	r4, [fp, #-48]
	ldr	r2, [fp, #-48]
	mov	r4, #0
	str	r2, [r10, #12]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r8, [fp, #-76]
	str	r4, [fp, #-48]
	mov	r0, #4
	ldr	r1, .L130+24
	ldrb	r3, [r8, #245]	@ zero_extendqisi2
	ldrb	r2, [r8, #244]	@ zero_extendqisi2
	and	r3, r3, #31
	ldrb	ip, [r8, #241]	@ zero_extendqisi2
	bfi	r3, r2, #5, #2
	ldrb	r2, [r8, #243]	@ zero_extendqisi2
	strb	r3, [fp, #-48]
	ldrh	r3, [fp, #-48]
	bfi	r3, r2, #7, #3
	ldrb	r2, [r8, #242]	@ zero_extendqisi2
	strh	r3, [fp, #-48]	@ movhi
	mov	r3, r3, lsr #8
	bfi	r3, ip, #2, #3
	bfi	r3, r2, #5, #3
	strb	r3, [fp, #-47]
	ldr	r2, [fp, #-48]
	str	r2, [r10, #16]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r1, .L130+28
	mov	r2, r4
	mov	r0, #4
	bfi	r2, r4, #0, #20
	str	r2, [fp, #-48]
	str	r2, [r10, #20]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r8, #264]
	ldr	r1, .L130+32
	mov	r2, r4
	sub	r3, r3, #1
	mov	r0, #4
	bfi	r2, r3, #0, #20
	str	r2, [fp, #-48]
	str	r2, [r10, #24]
	ldr	r3, [r6, #68]
	blx	r3
	str	r9, [r10, #28]
	ldr	r1, .L130+36
	mov	r0, #4
	ldr	r3, [r6, #68]
	mov	r2, r9
	str	r9, [fp, #-48]
	blx	r3
	mov	r3, #1
	b	.L106
.L128:
	ldr	r3, .L130+4
	ldr	r2, .L130+40
	ldr	r1, .L130+44
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L105
.L131:
	.align	2
.L130:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC45
	.word	.LC46
	.word	.LC47
	.word	.LC48
	.word	.LC49
	.word	.LC50
	.word	.LC51
	.word	.LC52
	.word	.LANCHOR0+24
	.word	.LC44
	UNWIND(.fnend)
	.size	MP4HAL_V300R001_WriteSlicMsg, .-MP4HAL_V300R001_WriteSlicMsg
	.align	2
	.global	MP4HAL_V300R001_StartDec
	.type	MP4HAL_V300R001_StartDec, %function
MP4HAL_V300R001_StartDec:
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
	ldrh	r3, [r0, #164]
	mov	r6, #0
	mov	r4, r0
	cmp	r3, #512
	mov	r5, r1
	str	r6, [fp, #-32]
	bhi	.L139
	ldrh	r3, [r0, #166]
	cmp	r3, #512
	bhi	.L139
	sub	r2, fp, #32
	bl	MP4HAL_V300R001_CfgReg
	subs	r7, r0, #0
	bne	.L140
	mov	r1, r5
	mov	r0, r4
	bl	MP4HAL_V300R001_CfgDnMsg
	subs	r6, r0, #0
	bne	.L141
	mov	r1, r5
	mov	r0, r4
	ldr	r2, [fp, #-32]
	bl	MP4HAL_V300R001_WriteSlicMsg
	cmp	r0, #0
	bne	.L142
.L134:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L139:
	ldr	r1, .L143
	mov	r0, r6
	ldr	r3, .L143+4
	ldr	r2, .L143+8
	ldr	r4, [r1, #68]
	ldr	r1, .L143+12
	blx	r4
	mvn	r0, #0
	b	.L134
.L140:
	ldr	r3, .L143
	mov	r0, r6
	ldr	r1, .L143+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L134
.L141:
	ldr	r3, .L143
	mov	r0, r7
	ldr	r1, .L143+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L134
.L142:
	ldr	r3, .L143
	mov	r0, r6
	ldr	r1, .L143+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L134
.L144:
	.align	2
.L143:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC53
	.word	.LANCHOR0+56
	.word	.LC54
	.word	.LC55
	.word	.LC56
	.word	.LC57
	UNWIND(.fnend)
	.size	MP4HAL_V300R001_StartDec, .-MP4HAL_V300R001_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13565, %object
	.size	__func__.13565, 23
__func__.13565:
	.ascii	"MP4HAL_V300R001_CfgReg\000"
	.space	1
	.type	__func__.13614, %object
	.size	__func__.13614, 29
__func__.13614:
	.ascii	"MP4HAL_V300R001_WriteSlicMsg\000"
	.space	3
	.type	__func__.13545, %object
	.size	__func__.13545, 25
__func__.13545:
	.ascii	"MP4HAL_V300R001_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"stream_base_addr = %#x\012\000" )
.LC1:
	ASCII(.ascii	"BASIC_V300R001_CFG0=0x%x\012\000" )
	.space	2
.LC2:
	ASCII(.ascii	"BASIC_V300R001_CFG1=0x%x\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"AVM_V300R001_ADDR=0x%x\012\000" )
.LC4:
	ASCII(.ascii	"VAM_V300R001_ADDR=0x%x\012\000" )
.LC5:
	ASCII(.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"STREAM_V300R001_BASE_ADDR=0x%x\012\000" )
.LC7:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC8:
	ASCII(.ascii	"YSTADDR_V200R003_1D=0x%x\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"YSTRIDE_V200R003_1D=0x%x\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"UVOFFSET_V200R003_1D=0x%x\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"PRCMEM2_1D_CNT=0x%x\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"DNR_MBINFO_STADDR=0x%x\012\000" )
.LC13:
	ASCII(.ascii	"line: %d ,pMsgBlock = NULL is not expected value!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC14:
	ASCII(.ascii	"D0=0x%x\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"D1=0x%x\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"D2=0x%x\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"D3=0x%x\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"D4=0x%x\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"D5=0x%x\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"D6=0x%x\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"D7=0x%x\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"D8=0x%x\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"D9=0x%x\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"D10=0x%x\012\000" )
	.space	2
.LC25:
	ASCII(.ascii	"D11=0x%x\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"D12= 0x%x\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"D13= 0x%x\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"D14= 0x%x\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"D15= 0x%x\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"D16= 0x%x\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"D17= 0x%x\012\000" )
	.space	1
.LC32:
	ASCII(.ascii	"D18= 0x%x\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"D19= 0x%x\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"D20= 0x%x\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"D21= 0x%x\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	"D22= 0x%x\012\000" )
	.space	1
.LC37:
	ASCII(.ascii	"D23= 0x%x\012\000" )
	.space	1
.LC38:
	ASCII(.ascii	"D24= 0x%x\012\000" )
	.space	1
.LC39:
	ASCII(.ascii	"D25= 0x%x\012\000" )
	.space	1
.LC40:
	ASCII(.ascii	"D26= 0x%x\012\000" )
	.space	1
.LC41:
	ASCII(.ascii	"D27= 0x%x\012\000" )
	.space	1
.LC42:
	ASCII(.ascii	"D%d= 0x%x\012\000" )
	.space	1
.LC43:
	ASCII(.ascii	"D63= 0x%x\012\000" )
	.space	1
.LC44:
	ASCII(.ascii	"%s: SlcDnMsgVirAddr = NULL\012\000" )
.LC45:
	ASCII(.ascii	"D0 = %#x \012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"D1 = %#x \012\000" )
	.space	1
.LC47:
	ASCII(.ascii	"D2 = %#x \012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"D3 = %#x \012\000" )
	.space	1
.LC49:
	ASCII(.ascii	"D4 = %#x \012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"D5 = %#x \012\000" )
	.space	1
.LC51:
	ASCII(.ascii	"D6 = %#x \012\000" )
	.space	1
.LC52:
	ASCII(.ascii	"D7 = %#x \012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC54:
	ASCII(.ascii	"%s: %s\012\000" )
.LC55:
	ASCII(.ascii	"MP4HAL_V200R003_CfgReg failed!\012\000" )
.LC56:
	ASCII(.ascii	"MP4HAL_V200R003_CfgDnMsg failed!\012\000" )
	.space	2
.LC57:
	ASCII(.ascii	"MP4HAL_V200R003_WriteSlicMsg failed!\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
