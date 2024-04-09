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
	.file	"vdm_hal_hevc.c"
	.text
	.align	2
	.global	HEVCWriteCabacTab
	.type	HEVCWriteCabacTab, %function
HEVCWriteCabacTab:
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
	ldr	r6, .L19
	mov	r9, #0
	ldr	r10, .L19+4
	mov	r1, r9
	mov	r8, r9
	mov	r7, r9
	mov	r5, #16
.L2:
	add	lr, r5, r9
	mov	r4, r1, asl #1
	rsb	r5, r1, r5
	add	ip, r6, r4
	add	lr, r10, lr, lsl #2
.L6:
	ldr	r3, [lr], #4
	add	r1, r1, #1
	add	ip, ip, #2
	cmn	r3, #1
	and	r2, r3, #15
	mov	r3, r3, asr #4
	streqb	r7, [r6, r4]
	mov	r2, r2, asl #3
	streqb	r7, [ip, #-1]
	addne	r3, r3, r3, lsl #2
	subne	r2, r2, #16
	subne	r3, r3, #45
	strneb	r3, [r6, r4]
	add	r3, r5, r1
	strneb	r2, [ip, #-1]
	cmp	r3, #159
	mov	r4, r1, asl #1
	ble	.L6
	add	r8, r8, #1
	cmp	r8, #3
	beq	.L17
	cmp	r8, #0
	add	r9, r9, #160
	moveq	r5, #16
	movne	r5, #0
	b	.L2
.L17:
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	addne	r3, r3, #2
	ldrne	r2, .L19+8
	addne	r0, r2, #928
	beq	.L18
.L10:
	ldrb	r1, [r2, #-1]	@ zero_extendqisi2
	add	r3, r3, #2
	strb	r1, [r3, #-3]
	ldrb	r1, [r2], #2	@ zero_extendqisi2
	cmp	r2, r0
	strb	r1, [r3, #-4]
	bne	.L10
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L18:
	ldr	r3, .L19+12
	ldr	r2, .L19+16
	ldr	r1, .L19+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L20:
	.align	2
.L19:
	.word	.LANCHOR0
	.word	.LANCHOR1+20
	.word	.LANCHOR0+1
	.word	.LC0
	.word	.LANCHOR1
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCWriteCabacTab, .-HEVCWriteCabacTab
	.align	2
	.global	HEVCHAL_V5R2C1_InitHal
	.type	HEVCHAL_V5R2C1_InitHal, %function
HEVCHAL_V5R2C1_InitHal:
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
	beq	.L27
	ldr	r0, [r3, #1108]
	bl	HEVCWriteCabacTab
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r1, .L28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L27:
	ldr	r3, .L28+4
	ldr	r2, .L28+8
	ldr	r1, .L28+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L29:
	.align	2
.L28:
	.word	.LC3
	.word	.LC2
	.word	.LANCHOR1+1940
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_InitHal, .-HEVCHAL_V5R2C1_InitHal
	.align	2
	.global	HEVCGet_V5R2C1_VirAddr
	.type	HEVCGet_V5R2C1_VirAddr, %function
HEVCGet_V5R2C1_VirAddr:
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
	add	r0, r1, r0, lsl #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCGet_V5R2C1_VirAddr, .-HEVCGet_V5R2C1_VirAddr
	.align	2
	.global	HEVCGet_V5R2C1_PhyAddr
	.type	HEVCGet_V5R2C1_PhyAddr, %function
HEVCGet_V5R2C1_PhyAddr:
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
	add	r0, r1, r0, lsl #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCGet_V5R2C1_PhyAddr, .-HEVCGet_V5R2C1_PhyAddr
	.align	2
	.global	HEVCHAL_V5R2C1_CutSliceChain
	.type	HEVCHAL_V5R2C1_CutSliceChain, %function
HEVCHAL_V5R2C1_CutSliceChain:
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
	subs	r3, r0, #0
	beq	.L35
	mov	r0, #0
	str	r0, [r3, #252]
	ldmfd	sp, {fp, sp, pc}
.L35:
	ldr	r3, .L36
	ldr	r2, .L36+4
	ldr	r1, .L36+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L37:
	.align	2
.L36:
	.word	.LC4
	.word	.LANCHOR1+1964
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_CutSliceChain, .-HEVCHAL_V5R2C1_CutSliceChain
	.align	2
	.global	HEVC_WriteQmatrix
	.type	HEVC_WriteQmatrix, %function
HEVC_WriteQmatrix:
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
	subs	r9, r1, #0
	mov	r8, r0
	mov	r10, r2
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	sub	r6, r3, #4
	sub	r7, r0, #4
	mov	r4, #0
.L40:
	ldr	r3, [r7, #4]!
	mov	r2, r4
	ldr	r1, .L43
	mov	r0, #4
	add	r4, r4, #1
	mov	r5, r7
	str	r3, [r6, #4]!
	ldr	r3, [r5], r10
	bl	dprint_vfmw
	ldr	r3, [r6]
	rsb	r2, r8, r5
	ldr	r1, .L43+4
	mov	r0, #4
	bl	dprint_vfmw
	cmp	r4, r9
	bne	.L40
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L44:
	.align	2
.L43:
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix, .-HEVC_WriteQmatrix
	.align	2
	.global	HEVC_WriteTileInfo
	.type	HEVC_WriteTileInfo, %function
HEVC_WriteTileInfo:
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
	str	r0, [fp, #-52]
	mov	r4, r0
	ldr	r0, [r1, #1112]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-48]
	beq	.L46
	add	r8, r3, #1024
	add	r9, r3, #4
	add	r8, r8, #4
	mov	r6, #0
	mov	r10, r4
	str	r4, [fp, #-56]
.L47:
	mov	r5, r10
	mov	r7, r9
	mov	r4, #0
	b	.L51
.L67:
	ldrb	r3, [r5, #1742]	@ zero_extendqisi2
	ldrb	ip, [r5, #1743]	@ zero_extendqisi2
	ldrb	r1, [r5, #1740]	@ zero_extendqisi2
	ldrb	r2, [r5, #1741]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	orr	r3, r3, ip, asl #24
	orr	r3, r3, r1
	ldr	r1, .L68
	orr	r2, r3, r2, asl #8
	str	r2, [r7, #-4]
	bl	dprint_vfmw
.L50:
	add	r4, r4, #4
	add	r7, r7, #4
	cmp	r4, #512
	add	r5, r5, #4
	beq	.L66
.L51:
	cmp	r4, #252
	mov	r2, #0
	ldr	r1, .L68
	mov	r0, #4
	ble	.L67
	str	r6, [r7, #-4]
	bl	dprint_vfmw
	b	.L50
.L66:
	add	r9, r9, #512
	add	r10, r10, #256
	cmp	r9, r8
	bne	.L47
	ldr	r7, [fp, #-56]
	mov	r3, #0
	ldr	r2, [fp, #-52]
	mov	ip, r3
.L52:
	cmp	r3, #9
	add	r3, r3, #1
	strgt	ip, [r8, #-4]
	add	r2, r2, #8
	ldrle	r0, [r2, #2248]
	add	r8, r8, #4
	ldrle	r1, [r2, #2244]
	orrle	r1, r1, r0, asl #16
	strle	r1, [r8, #-8]
	cmp	r3, #20
	bne	.L52
	ldr	r3, [fp, #-48]
	add	r2, r3, #1104
	mov	r3, #0
	add	r2, r2, #4
	mov	ip, r3
.L58:
	cmp	r3, #10
	add	r3, r3, #1
	strgt	ip, [r2, #-4]
	add	r7, r7, #8
	ldrle	r0, [r7, #2328]
	add	r2, r2, #4
	ldrle	r1, [r7, #2324]
	orrle	r1, r1, r0, asl #16
	strle	r1, [r2, #-8]
	cmp	r3, #22
	bne	.L58
	mov	r0, #0
.L63:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L46:
	ldr	r3, .L68+4
	ldr	r2, .L68+8
	ldr	r1, .L68+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L63
.L69:
	.align	2
.L68:
	.word	.LC8
	.word	.LC7
	.word	.LANCHOR1+1996
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVC_WriteTileInfo, .-HEVC_WriteTileInfo
	.align	2
	.global	HEVCHAL_V5R2C1_SetPicMsg
	.type	HEVCHAL_V5R2C1_SetPicMsg, %function
HEVCHAL_V5R2C1_SetPicMsg:
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
	mov	r4, r0
	mov	r0, r2
	mov	r7, r2
	mov	r6, r1
	mov	r8, r3
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L85
	ldr	r3, .L87
	mov	r2, #1280
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r1, .L87+4
	mov	r0, #4
	bl	dprint_vfmw
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	ldrb	lr, [r4, #7]	@ zero_extendqisi2
	mov	r2, r7
	ldr	r9, [r4, #20]
	mov	r0, #4
	mov	r3, r3, asl #25
	ldrb	r1, [r4, #8]	@ zero_extendqisi2
	orr	lr, r3, lr, asl #24
	ldr	r3, [r4, #12]
	ldrb	ip, [r4, #9]	@ zero_extendqisi2
	mov	r9, r9, asl #9
	ldrb	r10, [r4, #10]	@ zero_extendqisi2
	orr	r1, lr, r1, asl #23
	orr	r3, r9, r3, asl #19
	ldr	lr, [r4, #24]
	ldrb	r9, [r4, #16]	@ zero_extendqisi2
	orr	r1, r1, ip, asl #22
	orr	lr, r3, lr
	orr	ip, r1, r10, asl #21
	ldr	r1, .L87+8
	orr	r3, lr, r9, asl #18
	orr	r3, r3, ip
	str	r3, [r5]
	ldr	r3, [r5]
	bl	dprint_vfmw
	ldr	r3, [r4, #28]
	str	r3, [r5, #4]
	ldr	r2, [r4, #44]
	ldr	r1, [r4, #36]
	ldr	ip, [r4, #76]
	ldr	r3, [r4, #48]
	mov	r2, r2, asl #24
	ldr	r0, [r4, #52]
	orr	r2, r2, r1, asl #29
	ldr	lr, [r4, #56]
	orr	r2, r2, ip
	ldr	r1, [r4, #60]
	orr	r3, r2, r3, asl #21
	ldr	ip, [r4, #64]
	orr	r3, r3, r0, asl #18
	ldr	r2, [r4, #68]
	orr	r0, r3, lr, asl #15
	orr	r1, r0, r1, asl #12
	ldr	r0, [r4, #72]
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	orr	r1, r1, ip, asl #9
	orr	r2, r1, r2, asl #6
	ldrb	r1, [r4, #41]	@ zero_extendqisi2
	orr	r2, r2, r0, asl #3
	orr	r3, r2, r3, asl #28
	orr	r3, r3, r1, asl #27
	str	r3, [r5, #8]
	ldr	r0, [r4, #84]
	ldr	r2, [r4, #80]
	ldr	r1, [r4, #100]
	ldr	ip, [r4, #88]
	mov	r0, r0, asl #16
	ldr	r3, [r4, #92]
	orr	r2, r0, r2, asl #22
	orr	r2, r2, r1
	ldr	r1, [r4, #96]
	orr	r2, r2, ip, asl #12
	orr	r3, r2, r3, asl #8
	orr	r3, r3, r1, asl #4
	str	r3, [r5, #12]
	ldr	r3, [r6, #1092]
	str	r3, [r5, #16]
	ldr	r3, [r6, #1096]
	str	r3, [r5, #20]
	ldr	r3, [r4, #1292]
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #1476]
	str	r3, [r5, #24]
	ldr	r3, [r6, #1104]
	str	r3, [r5, #28]
	ldr	r3, [r4, #2484]
	cmp	r3, #0
	beq	.L73
	add	r0, r4, #2416
	add	r1, r5, #32
	mov	r2, #0
.L74:
	ldr	r3, [r0, #4]!
	add	r2, r2, #1
	add	r3, r3, #336
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r1], #4
	ldr	r3, [r4, #2484]
	cmp	r3, r2
	bhi	.L74
	cmp	r3, #15
	bhi	.L77
.L73:
	add	r1, r3, #8
	add	r1, r5, r1, lsl #2
.L76:
	ldr	r2, [r4, #2420]
	add	r3, r3, #1
	cmp	r3, #15
	add	r2, r2, #336
	ldr	r2, [r4, r2, asl #2]
	str	r2, [r1], #4
	bls	.L76
.L77:
	ldr	r1, [r6, #1108]
	add	r3, r4, #124
	add	r2, r5, #104
	add	r0, r4, #188
	str	r1, [r5, #100]
.L75:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2], #4
	bne	.L75
	ldr	r3, [r6, #1100]
	mov	r1, r6
	mov	r0, r4
	str	r3, [r5, #172]
	ldr	r2, [r4, #192]
	ldr	r3, [r4, #196]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #216]
	bl	HEVC_WriteTileInfo
	subs	r9, r0, #0
	bne	.L86
	ldr	r3, [r6, #1112]
	mov	r1, r5
	mov	r0, #64
	str	r3, [r5, #220]
	ldr	r3, [r6, #1124]
	str	r3, [r5, #224]
	ldr	r3, [r6, #1116]
	str	r3, [r5, #228]
	ldr	r3, [r6, #1128]
	str	r3, [r5, #232]
	ldr	r3, [r6, #1120]
	str	r3, [r5, #236]
	ldr	r2, [r4, #228]
	ldr	ip, [r4, #232]
	ldr	r3, [r4, #244]
	mov	r2, r2, asl #16
	ldrb	lr, [r4, #221]	@ zero_extendqisi2
	orr	r2, r2, ip, asl #13
	and	r3, r3, #31
	orr	ip, r2, r3
	ldrb	r2, [r4, #220]	@ zero_extendqisi2
	ldrb	r3, [r4, #222]	@ zero_extendqisi2
	orr	r2, ip, r2, asl #24
	ldrb	ip, [r4, #224]	@ zero_extendqisi2
	orr	r2, r2, lr, asl #23
	ldrb	lr, [r4, #223]	@ zero_extendqisi2
	orr	r3, r2, r3, asl #22
	ldrb	r2, [r4, #236]	@ zero_extendqisi2
	orr	r3, r3, lr, asl #21
	ldrb	lr, [r4, #225]	@ zero_extendqisi2
	orr	ip, r3, ip, asl #20
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	orr	ip, ip, lr, asl #19
	ldrb	lr, [r4, #237]	@ zero_extendqisi2
	orr	r2, ip, r2, asl #12
	ldr	ip, [r4, #240]
	orr	r2, r2, lr, asl #11
	and	ip, ip, #31
	orr	r3, r2, r3, asl #10
	orr	r3, r3, ip, asl #5
	str	r3, [r5, #240]
	ldr	r2, [r4, #248]
	ldr	r3, [r4, #252]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #244]
	str	r8, [r5, #252]
	bl	HEVC_GetVirAddr
	mov	r1, r7
	mov	r5, r0
	mov	r0, #64
	bl	HEVC_GetPhyAddr
	mov	r3, r5
	mov	r1, #256
	mov	r2, r0
	add	r0, r4, #260
	bl	HEVC_WriteQmatrix
.L72:
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L86:
	ldr	r1, .L87+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r9, #0
	b	.L72
.L85:
	ldr	r3, .L87+16
	mvn	r9, #0
	ldr	r2, .L87+20
	ldr	r1, .L87+24
	bl	dprint_vfmw
	b	.L72
.L88:
	.align	2
.L87:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC10
	.word	.LC11
	.word	.LC12
	.word	.LC9
	.word	.LANCHOR1+2016
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_SetPicMsg, .-HEVCHAL_V5R2C1_SetPicMsg
	.align	2
	.global	HEVCHAL_SetSliceMsgStreamAddrInfo
	.type	HEVCHAL_SetSliceMsgStreamAddrInfo, %function
HEVCHAL_SetSliceMsgStreamAddrInfo:
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
	mov	r5, #0
	mov	r4, r2
	add	r7, r1, #16
	add	r9, r4, #8
	mov	r6, r3
	mov	r8, r5
	str	r1, [fp, #-52]
	str	r0, [fp, #-48]
.L95:
	cmp	r8, #0
	mov	r3, r6
	mov	r2, r5
	ldr	r1, .L98
	mov	r0, #4
	beq	.L97
	ldr	r10, [r7, #-16]
	cmp	r10, #0
	beq	.L93
.L91:
	ldr	r2, [fp, #-48]
	mov	r3, r6
	ldr	ip, [r7]
	ldr	r1, .L98
	ldr	r0, [r2, #1332]
	bic	ip, ip, #15
	mov	r2, r5
	bic	r0, r0, #15
	rsb	r0, r0, ip
	str	r0, [r4]
	ldr	ip, [r9, #-8]
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r7]
	ldr	r0, [r7, #-8]
	add	r3, r6, #4
	add	r2, r5, #1
	ldr	r1, .L98
	add	ip, r0, ip, lsl #3
	mov	r0, #4
	and	ip, ip, #127
	str	ip, [r4, #4]
	ldr	ip, [r4, #4]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r7, #-16]
	add	r3, r6, #8
	add	r2, r5, #2
	ldr	r1, .L98
	mov	r0, #4
	str	ip, [r9]
	ldr	ip, [r4, #8]
	str	ip, [sp]
	bl	dprint_vfmw
.L94:
	add	r8, r8, #1
	add	r7, r7, #4
	cmp	r8, #2
	add	r4, r4, #12
	add	r5, r5, #3
	add	r6, r6, #12
	add	r9, r9, #12
	bne	.L95
	mov	r0, #0
.L92:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L93:
	str	r10, [r4]
	ldr	ip, [r9, #-8]
	str	ip, [sp]
	bl	dprint_vfmw
	str	r10, [r4, #4]
	ldr	ip, [r4, #4]
	add	r3, r6, #4
	add	r2, r5, #1
	ldr	r1, .L98
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	str	r10, [r9]
	ldr	ip, [r4, #8]
	add	r3, r6, #8
	add	r2, r5, #2
	ldr	r1, .L98
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L94
.L97:
	ldr	r3, [fp, #-52]
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L91
	mov	r0, r8
	ldr	r2, .L98+4
	ldr	r1, .L98+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L92
.L99:
	.align	2
.L98:
	.word	.LC14
	.word	.LANCHOR1+2044
	.word	.LC13
	UNWIND(.fnend)
	.size	HEVCHAL_SetSliceMsgStreamAddrInfo, .-HEVCHAL_SetSliceMsgStreamAddrInfo
	.align	2
	.global	HEVCHAL_SetSliceMsgAPCIndex
	.type	HEVCHAL_SetSliceMsgAPCIndex, %function
HEVCHAL_SetSliceMsgAPCIndex:
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
	ldr	lr, [r0, #68]
	cmp	lr, #0
	addne	r4, r0, #368
	movne	ip, #0
	movne	r7, #15
	movne	r2, ip
	bne	.L106
	b	.L107
.L104:
	cmp	r6, r2
	streq	ip, [r1, r7, asl #2]
	add	r2, r2, #1
	ldreq	lr, [r0, #68]
	cmp	lr, r2
	bls	.L107
.L106:
	and	r3, r2, #7
	ldr	r5, [r4, #4]!
	cmp	r3, #7
	sub	r6, lr, #1
	mov	r3, r3, asl #2
	orr	ip, ip, r5, asl r3
	bne	.L104
	str	ip, [r1, r7, asl #2]
	add	r2, r2, #1
	ldr	lr, [r0, #68]
	add	r7, r7, #1
	mov	ip, #0
	cmp	lr, r2
	bhi	.L106
.L107:
	ldr	lr, [r0, #72]
	cmp	lr, #0
	beq	.L114
	mov	ip, #0
	add	r4, r0, #432
	mov	r2, ip
	mov	r7, #17
	b	.L110
.L108:
	cmp	r6, r2
	streq	ip, [r1, r7, asl #2]
	add	r2, r2, #1
	ldreq	lr, [r0, #72]
	cmp	lr, r2
	bls	.L115
.L110:
	and	r3, r2, #7
	ldr	r5, [r4, #4]!
	cmp	r3, #7
	sub	r6, lr, #1
	mov	r3, r3, asl #2
	orr	ip, ip, r5, asl r3
	bne	.L108
	str	ip, [r1, r7, asl #2]
	add	r2, r2, #1
	ldr	lr, [r0, #72]
	add	r7, r7, #1
	mov	ip, #0
	cmp	lr, r2
	bhi	.L110
.L115:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L114:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCHAL_SetSliceMsgAPCIndex, .-HEVCHAL_SetSliceMsgAPCIndex
	.align	2
	.global	HEVCHAL_SetSliceMsgWPInfo
	.type	HEVCHAL_SetSliceMsgWPInfo, %function
HEVCHAL_SetSliceMsgWPInfo:
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
	mov	r7, r0
	mov	r4, r1
	mov	r0, #64
	mov	r1, r2
	mov	r6, r2
	bl	HEVC_GetVirAddr
	mov	r1, r6
	mov	r5, r0
	mov	r0, #128
	bl	HEVC_GetVirAddr
	ldrb	r3, [r7, #41]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L117
	ldr	r3, [r4, #76]
	cmp	r3, #1
	beq	.L118
.L117:
	ldrb	r3, [r7, #40]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, [r4, #76]
	cmp	r3, #0
	bne	.L138
	ldr	r3, [r4, #68]
	cmp	r3, #0
	beq	.L125
.L124:
	add	r7, r4, #712
	add	r6, r4, #584
	add	ip, r0, #128
	mov	lr, r5
	mov	r3, r4
	mov	r1, #0
.L122:
	ldr	r8, [r7, #4]!
	add	r1, r1, #1
	ldr	r10, [r6, #4]!
	add	r3, r3, #8
	ldr	r9, [r4, #580]
	uxtb	r8, r8
	ubfx	r10, r10, #0, #9
	and	r9, r9, #7
	mov	r8, r8, asl #12
	orr	r2, r8, r10, asl #3
	orr	r2, r2, r9
	str	r2, [lr], #4
	ldr	r9, [r3, #836]
	ldrb	r2, [r3, #1092]	@ zero_extendqisi2
	ldr	r8, [r4, #584]
	ubfx	r9, r9, #0, #9
	mov	r2, r2, asl #12
	and	r8, r8, #7
	orr	r2, r2, r9, asl #3
	orr	r2, r2, r8
	str	r2, [ip, #-128]
	ldr	r2, [r3, #840]
	ldrb	r8, [r3, #1096]	@ zero_extendqisi2
	ubfx	r2, r2, #0, #9
	orr	r2, r2, r8, asl #9
	str	r2, [ip], #4
	ldr	r2, [r4, #68]
	cmp	r2, r1
	bhi	.L122
	ldr	r3, [r4, #76]
	cmp	r3, #0
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L125:
	ldr	r3, [r4, #72]
	cmp	r3, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	add	r5, r5, #64
	add	r0, r0, #192
	add	r6, r4, #776
	add	lr, r4, #648
	mov	r1, r4
	mov	ip, #0
.L123:
	ldr	r2, [r6, #4]!
	add	ip, ip, #1
	ldr	r3, [lr, #4]!
	add	r1, r1, #8
	ldr	r7, [r4, #580]
	uxtb	r2, r2
	ubfx	r3, r3, #0, #9
	and	r7, r7, #7
	mov	r2, r2, asl #12
	orr	r3, r2, r3, asl #3
	orr	r3, r3, r7
	str	r3, [r5], #4
	ldr	r3, [r1, #964]
	ldrb	r7, [r1, #1220]	@ zero_extendqisi2
	ldr	r2, [r4, #584]
	ubfx	r8, r3, #0, #9
	mov	r3, r7, asl #12
	and	r2, r2, #7
	orr	r3, r3, r8, asl #3
	orr	r3, r3, r2
	str	r3, [r0, #-128]
	ldr	r3, [r1, #968]
	ldrb	r2, [r1, #1224]	@ zero_extendqisi2
	ubfx	r3, r3, #0, #9
	orr	r3, r3, r2, asl #9
	str	r3, [r0], #4
	ldr	r3, [r4, #72]
	cmp	r3, ip
	bhi	.L123
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L118:
	ldr	r3, [r4, #68]
	cmp	r3, #0
	bne	.L124
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L138:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCHAL_SetSliceMsgWPInfo, .-HEVCHAL_SetSliceMsgWPInfo
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	HEVCHAL_V5R2C1_SetSliceMsg
	.type	HEVCHAL_V5R2C1_SetSliceMsg, %function
HEVCHAL_V5R2C1_SetSliceMsg:
	UNWIND(.fnstart)
	@ args = 24, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r6, r0
	mov	r0, r3
	mov	r8, r3
	mov	r4, r2
	ldr	r7, [fp, #12]
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L151
	ldr	r3, .L152
	mov	r2, #1280
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	mov	r3, r8
	mov	r2, r5
	mov	r1, r4
	mov	r0, r6
	bl	HEVCHAL_SetSliceMsgStreamAddrInfo
	cmn	r0, #1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	ip, [r4, #28]
	mov	r0, r7
	ldrb	r1, [r4, #32]	@ zero_extendqisi2
	ldrb	r2, [r4, #24]	@ zero_extendqisi2
	and	ip, ip, #127
	ldrb	r3, [r4, #25]	@ zero_extendqisi2
	mov	r1, r1, asl #18
	orr	r1, r1, ip, asl #19
	ldr	ip, [r4, #36]
	mov	r2, r2, asl #27
	orr	r1, r1, ip
	orr	r3, r2, r3, asl #26
	orr	r3, r1, r3
	str	r3, [r5, #24]
	ldr	r1, [r4, #44]
	ldr	r3, [r4, #56]
	ldr	r2, [r4, #60]
	ldr	ip, [r4, #76]
	mov	r1, r1, asl #24
	orr	r3, r1, r3, asl #20
	ldr	r1, .L152+4
	orr	r2, r3, r2, asl #16
	ldr	r3, [r4, #72]
	ldr	lr, [r4, #68]
	add	r1, r1, ip, lsl #2
	orr	r2, r2, r3, asl #8
	ldr	ip, [r1, #2108]
	ldrb	r1, [r4, #64]	@ zero_extendqisi2
	orr	r3, r2, lr, asl #2
	orr	ip, r3, ip
	ldr	r2, [r4, #40]
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	orr	r1, ip, r1, asl #15
	ldrb	ip, [r4, #52]	@ zero_extendqisi2
	mov	r2, r2, asl #28
	orr	r1, r1, r3, asl #14
	orr	r2, r2, ip, asl #27
	orr	r3, r1, r2
	str	r3, [r5, #28]
	str	r7, [r5, #32]
	ldr	r8, [r6, #24]
	add	r8, r8, #1
	mov	r1, r8
	bl	__aeabi_uidiv
	mov	r1, r8
	mov	r8, r0, asl #16
	mov	r0, r7
	bl	__aeabi_uidivmod
	ldr	r3, [fp, #16]
	orr	r1, r8, r1
	str	r1, [r5, #36]
	str	r3, [r5, #40]
	ldr	r2, [r4, #96]
	ldr	r3, [r4, #100]
	and	r2, r2, #31
	and	r3, r3, #31
	orr	r3, r3, r2, asl #8
	str	r3, [r5, #44]
	ldr	r0, [r4, #108]
	ldr	r2, [r4, #104]
	and	r0, r0, #15
	ldrb	r1, [r4, #115]	@ zero_extendqisi2
	and	r2, r2, #15
	ldrb	ip, [r4, #113]	@ zero_extendqisi2
	mov	r0, r0, asl #8
	ldrb	r3, [r4, #112]	@ zero_extendqisi2
	orr	r2, r0, r2, asl #16
	orr	r2, r2, r1
	ldrb	r1, [r4, #114]	@ zero_extendqisi2
	orr	r2, r2, ip, asl #3
	orr	r3, r2, r3, asl #2
	orr	r3, r3, r1, asl #1
	str	r3, [r5, #48]
	ldr	ip, [r4, #68]
	cmp	ip, #0
	beq	.L147
	mov	r2, #0
	add	r1, r4, #112
	mov	r3, r2
.L143:
	ldr	r0, [r1, #4]!
	orr	r2, r2, r0, asl r3
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L143
.L142:
	str	r2, [r5, #52]
	ldr	ip, [r4, #72]
	cmp	ip, #0
	beq	.L148
	mov	r2, #0
	add	r1, r4, #176
	mov	r3, r2
.L145:
	ldr	r0, [r1, #4]!
	orr	r2, r2, r0, asl r3
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L145
.L144:
	str	r2, [r5, #56]
	mov	r1, r5
	mov	r0, r4
	bl	HEVCHAL_SetSliceMsgAPCIndex
	ldr	r3, [r4, #564]
	mov	r0, r6
	mov	r1, r4
	mov	r2, r5
	str	r3, [r5, #92]
	ldr	r3, [r6, #84]
	mov	r3, r3, lsr #1
	mov	r3, r3, asl #8
	orr	r3, r3, #16384
	orr	r3, r3, #10
	str	r3, [r5, #96]
	ldr	r3, [fp, #20]
	str	r3, [r5, #172]
	ldr	r3, [fp, #24]
	str	r3, [r5, #176]
	ldr	r3, [fp, #8]
	str	r3, [r5, #252]
	bl	HEVCHAL_SetSliceMsgWPInfo
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L147:
	mov	r2, ip
	b	.L142
.L148:
	mov	r2, ip
	b	.L144
.L151:
	ldr	r3, .L152+8
	ldr	r2, .L152+12
	ldr	r1, .L152+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L153:
	.align	2
.L152:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC15
	.word	.LANCHOR1+2080
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_SetSliceMsg, .-HEVCHAL_V5R2C1_SetSliceMsg
	.align	2
	.global	HEVCHAL_CheckParaValid
	.type	HEVCHAL_CheckParaValid, %function
HEVCHAL_CheckParaValid:
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
	cmp	r1, #0
	bgt	.L159
	cmp	r0, #0
	beq	.L160
	ldr	r3, [r0, #2484]
	cmp	r3, #16
	movls	r0, #0
	bhi	.L161
.L156:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L159:
	mov	r3, r1
	ldr	r2, .L162
	mov	r1, #1
	mov	r0, #0
	str	r1, [sp]
	ldr	r1, .L162+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L156
.L161:
	ldr	r3, .L162+8
	mov	r0, #0
	ldr	r2, .L162
	ldr	r1, .L162+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L156
.L160:
	ldr	r3, .L162+16
	ldr	r2, .L162
	ldr	r1, .L162+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L156
.L163:
	.align	2
.L162:
	.word	.LANCHOR1+2120
	.word	.LC16
	.word	.LC18
	.word	.LC1
	.word	.LC17
	UNWIND(.fnend)
	.size	HEVCHAL_CheckParaValid, .-HEVCHAL_CheckParaValid
	.align	2
	.global	HEVCHAL_GetVdmRegVirAddr
	.type	HEVCHAL_GetVdmRegVirAddr, %function
HEVCHAL_GetVdmRegVirAddr:
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
	mov	r4, r0
	bgt	.L169
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L167
.L168:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L167:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r4]
	bne	.L168
	ldr	r2, .L170
	ldr	r1, .L170+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L169:
	ldr	r1, .L170+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L171:
	.align	2
.L170:
	.word	.LANCHOR1+2144
	.word	.LC20
	.word	.LC19
	UNWIND(.fnend)
	.size	HEVCHAL_GetVdmRegVirAddr, .-HEVCHAL_GetVdmRegVirAddr
	.align	2
	.global	HEVCHAL_CheckSlicePara
	.type	HEVCHAL_CheckSlicePara, %function
HEVCHAL_CheckSlicePara:
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
	beq	.L176
	cmp	r1, #0
	ldr	r1, [r0, #92]
	movgt	r0, #1
	movle	r0, #0
	cmp	r1, r2
	movcs	r0, #0
	andcc	r0, r0, #1
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	mov	r3, r2
	mov	r0, #1
	mov	r2, r1
	ldr	r1, .L177
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L176:
	mov	r3, r1
	ldr	r2, .L177+4
	ldr	r1, .L177+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L178:
	.align	2
.L177:
	.word	.LC22
	.word	.LANCHOR1+2172
	.word	.LC21
	UNWIND(.fnend)
	.size	HEVCHAL_CheckSlicePara, .-HEVCHAL_CheckSlicePara
	.align	2
	.global	HEVCHAL_FindNextSlicePara
	.type	HEVCHAL_FindNextSlicePara, %function
HEVCHAL_FindNextSlicePara:
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
	cmp	r2, r1
	ldr	lr, [r0, #92]
	str	r2, [r3]
	ldmgefd	sp, {fp, sp, pc}
	ldr	r0, [r0, #1356]
	cmp	r0, #0
	beq	.L183
	ldr	ip, [r0, #92]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
	add	r2, r2, #1
	b	.L182
.L184:
	ldr	r0, [r0, #1356]
	cmp	r0, #0
	beq	.L183
	ldr	ip, [r0, #92]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
.L182:
	cmp	r2, r1
	str	r2, [r3]
	add	r2, r2, #1
	bne	.L184
	ldmfd	sp, {fp, sp, pc}
.L183:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCHAL_FindNextSlicePara, .-HEVCHAL_FindNextSlicePara
	.align	2
	.global	HEVCHAL_CheckSliceAddrValid
	.type	HEVCHAL_CheckSliceAddrValid, %function
HEVCHAL_CheckSliceAddrValid:
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
	cmp	r1, r2
	ldr	r3, [r0, #572]
	bgt	.L190
	cmp	r2, r3
	blt	.L190
	ldr	r2, [r0, #92]
	cmp	r2, r3
	movls	r0, #0
	bhi	.L194
.L192:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L190:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r1
	ldr	r1, .L195
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L192
.L194:
	ldr	r1, .L195+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L192
.L196:
	.align	2
.L195:
	.word	.LC23
	.word	.LC24
	UNWIND(.fnend)
	.size	HEVCHAL_CheckSliceAddrValid, .-HEVCHAL_CheckSliceAddrValid
	.align	2
	.global	HEVCHAL_V5R2C1_CfgVdmReg
	.type	HEVCHAL_V5R2C1_CfgVdmReg, %function
HEVCHAL_V5R2C1_CfgVdmReg:
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
	ldr	r6, .L213
	mov	lr, r2, asl #6
	mov	r5, r2
	sub	lr, lr, r2, asl #3
	ldr	ip, .L213+4
	ldrb	r2, [r6]	@ zero_extendqisi2
	mov	r10, r1
	add	ip, ip, lr
	mov	r4, r0
	subs	r2, r2, #1
	mov	r6, r3
	ldr	r0, [ip, #8]
	movne	r2, #1
	cmp	r3, #0
	movne	r1, #0
	andeq	r1, r2, #1
	cmp	r1, #0
	bne	.L211
	ldr	r3, .L213+8
	mov	r9, #0
	str	r9, [fp, #-48]
	ldr	r8, [r3, r0, asl #2]
	mov	r0, #0
	bfi	r0, r9, #7, #1
	strb	r0, [fp, #-46]
	cmp	r8, #0
	mov	r0, #8
	streq	r8, [fp, #-56]
	ldrne	r3, [r8, #1208]
	moveq	r3, r8
	strne	r3, [fp, #-56]
	uxtbne	r3, r3
	andne	r8, r3, #1
	cmp	r2, #0
	strneb	r3, [r6, #1]
	add	r3, r4, #4096
	ldr	r1, [r4, #20]
	ldr	r3, [r3, #1084]
	ldr	r2, [r4, #24]
	ldrb	ip, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	mla	r2, r1, r2, r2
	moveq	r3, #13
	movne	r3, #1
	bfi	r3, ip, #6, #1
	and	r3, r3, #111
	bfi	r3, r9, #5, #1
	strb	r3, [fp, #-45]
	ldr	r7, [fp, #-48]
	add	r1, r2, r1
	mov	r3, r6
	mov	r2, r5
	bfi	r7, r1, #0, #20
	str	r7, [r4, #2504]
	str	r7, [fp, #-48]
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L213+12
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r4, #196]
	ldr	r2, [r4, #1328]
	mov	r3, #0
	cmp	r1, #1920
	str	r9, [fp, #-48]
	strhib	r9, [r4, #5]
	bfi	r3, r2, #4, #1
	mov	r2, #13
	strb	r2, [fp, #-48]
	movls	r2, #1
	strlsb	r2, [r4, #5]
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2
	movhi	r2, r9
	ldrb	ip, [r4]	@ zero_extendqisi2
	mov	r9, #3
	ldr	r0, [r4, #1340]
	bfi	r1, r2, #5, #1
	strb	r1, [fp, #-45]
	mov	r2, r5
	ldrh	r1, [fp, #-46]
	bfi	r3, r0, #6, #1
	mov	r0, #12
	movw	r7, #3075
	bfi	r1, r9, #0, #12
	strh	r1, [fp, #-46]	@ movhi
	mvn	r3, r3, asl #25
	movt	r7, 48
	mov	r1, r1, lsr #8
	mvn	r3, r3, lsr #25
	bfi	r1, ip, #6, #1
	strb	r3, [fp, #-47]
	and	r1, r1, #127
	mov	r3, r6
	bfi	r1, r8, #4, #1
	strb	r1, [fp, #-45]
	ldr	r8, [fp, #-48]
	mov	r1, r8
	str	r8, [r4, #2508]
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L213+16
	mov	r0, r9
	bl	dprint_vfmw
	ldr	r8, [r10, #56]
	mov	r3, r6
	mov	r2, r5
	bic	r8, r8, #15
	mov	r0, #16
	str	r8, [r4, #2512]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L213+20
	mov	r0, r9
	bl	dprint_vfmw
	ldr	r1, [r10, #40]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #20
	str	r1, [r4, #2516]
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1332]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #24
	str	r1, [r4, #2520]
	bl	MFDE_ConfigReg
	mov	r1, r7
	mov	r3, r6
	mov	r2, r5
	mov	r0, #60
	str	r7, [r4, #2528]
	str	r7, [r4, #2532]
	str	r7, [r4, #2536]
	str	r7, [r4, #2540]
	str	r7, [r4, #2544]
	str	r7, [r4, #2548]
	str	r7, [r4, #2552]
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #64
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #68
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #72
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #76
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #80
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #84
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1288]
	mov	r3, r6
	mov	r2, r5
	add	r1, r1, #336
	mov	r0, #96
	ldr	r1, [r4, r1, asl #2]
	bic	r1, r1, #255
	str	r1, [r4, #2556]
	str	r1, [fp, #-48]
	bl	MFDE_ConfigReg
	ldr	r3, [fp, #-56]
	cmp	r3, #1
	beq	.L212
.L204:
	ldr	r8, [r4, #1296]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #100
	mov	r7, #0
	str	r8, [r4, #2560]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L213+24
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r4, #1304]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #104
	str	r8, [r4, #2564]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L213+28
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r4, #1312]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #108
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1316]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #116
	str	r1, [r4, #2580]
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1320]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #120
	str	r1, [r4, #2584]
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1324]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #124
	str	r1, [r4, #2588]
	bl	MFDE_ConfigReg
	str	r7, [r4, #2604]
	mov	r1, r7
	mov	r3, r6
	mov	r2, r5
	mov	r0, #128
	str	r7, [fp, #-48]
	bl	MFDE_ConfigReg
	strh	r7, [fp, #-48]	@ movhi
	mov	r3, r6
	ldr	r1, [fp, #-48]
	mov	r2, r5
	mov	r0, #132
	str	r1, [r4, #2608]
	bl	MFDE_ConfigReg
	ldr	r3, [r4, #196]
	mov	r2, r5
	mov	r0, #4
	cmp	r3, #4096
	mov	r3, r6
	movhi	r1, r7
	movls	r1, #1
	mov	r4, r1
	bl	SCD_ConfigReg
	mov	r2, r4
	ldr	r1, .L213+32
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r6
	mov	r2, r5
	mov	r1, #0
	mov	r0, #152
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L213+36
	mov	r0, #3
	bl	dprint_vfmw
	mov	r0, #32
	mov	r3, r6
	mov	r2, r5
	mvn	r1, #0
	bl	MFDE_ConfigReg
	mov	r0, #0
.L199:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L212:
	mov	r3, r6
	mov	r2, r5
	mov	r1, #60
	mov	r0, #92
	bl	MFDE_ConfigReg
	mov	r2, #60
	ldr	r1, .L213+40
	mov	r0, r9
	bl	dprint_vfmw
	ldr	r1, [r4, #1288]
	mov	r2, r5
	mov	r3, r6
	mov	r0, #112
	add	r1, r4, r1, lsl #2
	ldr	r7, [r1, #1612]
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	mov	r0, r9
	ldr	r1, .L213+44
	bl	dprint_vfmw
	b	.L204
.L211:
	ldr	r2, .L213+48
	mov	r0, #0
	ldr	r1, .L213+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L199
.L214:
	.align	2
.L213:
	.word	g_HalDisable
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC31
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC29
	.word	.LC30
	.word	.LANCHOR1+2196
	.word	.LC25
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_CfgVdmReg, .-HEVCHAL_V5R2C1_CfgVdmReg
	.align	2
	.global	HEVCHAL_V5R2C1_SetSliceMsgSedOnly
	.type	HEVCHAL_V5R2C1_SetSliceMsgSedOnly, %function
HEVCHAL_V5R2C1_SetSliceMsgSedOnly:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	mov	r6, r0
	ldr	r0, [r0, #2488]
	mov	r10, r1
	ldr	r2, [r6, #2492]
	cmp	r0, #0
	ble	.L216
	mov	r3, #0
	mov	r8, r3
	mov	r4, r3
.L218:
	ldrb	r1, [r2, #25]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r8, r3
	add	r3, r3, #1
	moveq	r4, r2
	cmp	r3, r0
	ldr	r2, [r2, #1356]
	bne	.L218
	cmp	r4, #0
	beq	.L216
	rsb	r3, r8, r3
	cmp	r3, #0
	addgt	r7, r10, #60
	movgt	r5, #0
	movgt	ip, r3
	bgt	.L226
	b	.L227
.L232:
	ldr	lr, [r4, #1356]
	mov	ip, r9
	ldrb	r2, [r6, #225]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [lr, #92]
	sub	r2, r2, #1
	beq	.L230
	ldr	lr, [lr, #568]
	mov	ip, r9
.L224:
	str	r2, [sp, #20]
	mov	r2, r4
	str	r1, [sp, #12]
	mov	r1, r10
	str	r0, [sp, #8]
	mov	r0, r6
	str	ip, [sp, #4]
	mov	ip, #0
	str	lr, [sp, #16]
	add	r5, r5, #1
	str	ip, [sp]
	bl	HEVCHAL_V5R2C1_SetSliceMsg
	cmp	r0, #0
	bne	.L231
	ldr	ip, [r6, #2488]
	ldr	r4, [r4, #1356]
	rsb	ip, r8, ip
	cmp	ip, r5
	ble	.L227
.L226:
	sub	ip, ip, #1
	ldr	r3, [r7]
	cmp	r5, #205
	cmple	r5, ip
	ldr	r9, [r7, #4]!
	ldr	r0, [r4, #80]
	movlt	ip, #1
	movge	ip, #0
	ldr	r1, [r4, #92]
	blt	.L232
	ldr	r2, [r6, #24]
	ldr	lr, [r6, #20]
	mla	lr, r2, lr, lr
	add	r2, lr, r2
.L230:
	mov	lr, r2
	b	.L224
.L227:
	mov	r0, #0
.L220:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L231:
	ldr	r2, .L233
	mov	r0, #1
	ldr	r1, .L233+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L216:
	ldr	r2, .L233
	mov	r0, #1
	ldr	r1, .L233+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L220
.L234:
	.align	2
.L233:
	.word	.LANCHOR1+2224
	.word	.LC36
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_SetSliceMsgSedOnly, .-HEVCHAL_V5R2C1_SetSliceMsgSedOnly
	.align	2
	.global	HEVCHAL_V5R2C1_StartDec
	.type	HEVCHAL_V5R2C1_StartDec, %function
HEVCHAL_V5R2C1_StartDec:
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
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	ip, .L300
	movw	r3, #1228
	str	r1, [fp, #-88]
	mov	r4, r2
	mov	r10, r0
	mla	r3, r3, r1, ip
	str	r3, [fp, #-80]
	bl	HEVCHAL_CheckParaValid
	cmn	r0, #1
	beq	.L290
	ldr	r6, [fp, #-88]
	ldr	r5, [fp, #-80]
	mov	r1, r6
	mov	r0, r5
	bl	HEVCHAL_GetVdmRegVirAddr
	cmn	r0, #1
	beq	.L290
	mov	r3, r4
	mov	r2, r6
	mov	r1, r5
	mov	r0, r10
	bl	HEVCHAL_V5R2C1_CfgVdmReg
	ldr	r3, [r5, #60]
	mov	r1, r5
	ldr	r2, [r5, #56]
	mov	r0, r10
	bl	HEVCHAL_V5R2C1_SetPicMsg
	ldr	r4, [r10, #2492]
	cmp	r4, #0
	beq	.L292
	add	r3, r10, #4096
	ldr	r3, [r3, #1084]
	cmp	r3, #1
	beq	.L293
	ldr	r5, [r4, #92]
	cmp	r5, #0
	bne	.L294
	mov	r8, r4
	str	r5, [fp, #-92]
.L241:
	ldr	r2, [r10, #24]
	ldr	r3, [r10, #20]
	ldr	r1, [r10, #2488]
	mla	r3, r2, r3, r3
	cmp	r1, #0
	add	r3, r3, r2
	str	r3, [fp, #-76]
	ble	.L244
	ldr	r0, [fp, #-88]
	movw	r2, #307
	ldr	r1, [fp, #-92]
	mul	r2, r2, r0
	add	r3, r1, #4
	add	r1, r1, #5
	str	r1, [fp, #-68]
	mov	r0, r2
	str	r2, [fp, #-72]
	mov	r2, #0
	add	r3, r0, r3
	mov	r9, r2
	str	r2, [fp, #-48]
	str	r3, [fp, #-84]
.L257:
	ldr	r3, [fp, #-68]
	mov	r0, r8
	ldr	r1, [fp, #-72]
	add	r6, r3, r9
	ldr	r3, [fp, #-84]
	ldr	lr, .L300
	add	ip, r1, r6
	add	r3, r3, r9
	add	ip, ip, #10
	add	r3, r3, #10
	mov	r1, r9
	ldr	ip, [lr, ip, asl #2]
	ldr	r3, [lr, r3, asl #2]
	str	ip, [fp, #-56]
	str	r3, [fp, #-52]
	bl	HEVCHAL_CheckSlicePara
	cmn	r0, #1
	beq	.L290
	ldr	r2, [r10, #2488]
	add	r9, r9, #1
	ldr	r3, [r8, #80]
	cmp	r2, r9
	ldr	r5, [r8, #92]
	str	r3, [fp, #-60]
	ble	.L245
	ldr	r4, [r8, #1356]
	cmp	r4, #0
	bne	.L289
	b	.L246
.L296:
	add	r9, r9, #1
	cmp	r9, r2
	beq	.L295
	ldr	r4, [r4, #1356]
	cmp	r4, #0
	beq	.L246
.L289:
	ldr	r3, [r4, #92]
	cmp	r5, r3
	bcs	.L296
.L252:
	cmp	r6, #209
	cmpne	r2, r9
	beq	.L258
	ldrb	r2, [r10, #225]	@ zero_extendqisi2
	ldr	r3, [r4, #92]
	cmp	r2, #0
	ldr	r2, [fp, #-68]
	sub	r6, r3, #1
	ldr	r3, [fp, #-72]
	ldrne	r7, [r4, #568]
	add	r2, r3, r2
	ldr	r3, .L300
	add	r2, r2, r9
	moveq	r7, r6
	add	r2, r2, #10
	ldr	r3, [r3, r2, asl #2]
	str	r3, [fp, #-64]
.L254:
	str	r6, [r8, #572]
	mov	r1, r7
	ldr	r2, [fp, #-76]
	mov	r0, r8
	bl	HEVCHAL_CheckSliceAddrValid
	cmn	r0, #1
	beq	.L290
	ldr	ip, [fp, #-64]
	mov	r2, r8
	ldr	r0, [fp, #-60]
	str	r6, [sp, #20]
	str	ip, [sp, #4]
	ldr	ip, [fp, #-52]
	str	r0, [sp, #8]
	mov	r0, r10
	ldr	r3, [fp, #-56]
	str	r7, [sp, #16]
	str	r5, [sp, #12]
	ldr	r1, [fp, #-80]
	str	ip, [sp]
	bl	HEVCHAL_V5R2C1_SetSliceMsg
	cmp	r0, #0
	bne	.L297
	ldr	r3, [r10, #2488]
	ldr	r2, [fp, #-48]
	cmp	r9, r3
	add	r2, r2, #1
	str	r2, [fp, #-48]
	ldr	r2, [r8, #572]
	bge	.L298
	mov	r8, r4
	b	.L257
.L294:
	ldrb	r3, [r10, #225]	@ zero_extendqisi2
	movw	r0, #1228
	ldr	r2, .L300
	mov	r6, #1
	cmp	r3, #0
	ldr	r3, [fp, #-88]
	ldr	r9, [r4]
	sub	lr, r5, #1
	str	r6, [r4]
	mla	r0, r0, r3, r2
	ldr	r3, [r4, #4]
	ldrne	ip, [r4, #568]
	moveq	ip, lr
	ldr	r7, [r4, #16]
	mov	r2, r4
	str	r3, [fp, #-48]
	ldr	r3, [r4, #8]
	ldr	r1, [fp, #-80]
	str	r3, [fp, #-52]
	ldr	r3, [r4, #12]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [r4, #4]
	str	r3, [r4, #8]
	str	r3, [r4, #12]
	ldr	r8, [r10, #1332]
	str	r8, [r4, #16]
	ldr	r8, [r4, #20]
	str	r3, [r4, #20]
	str	r3, [sp, #12]
	str	r3, [sp, #8]
	ldr	r3, [r0, #60]
	str	lr, [sp, #20]
	ldr	lr, [r0, #64]
	ldr	r0, [r0, #56]
	str	ip, [sp, #16]
	str	lr, [sp, #4]
	str	r0, [sp]
	mov	r0, r10
	bl	HEVCHAL_V5R2C1_SetSliceMsg
	cmp	r0, #0
	bne	.L299
	ldr	r3, [fp, #-48]
	str	r5, [r4, #92]
	str	r9, [r4]
	str	r3, [r4, #4]
	ldr	r3, [fp, #-52]
	str	r7, [r4, #16]
	str	r8, [r4, #20]
	str	r3, [r4, #8]
	ldr	r3, [fp, #-56]
	str	r6, [fp, #-92]
	str	r3, [r4, #12]
	ldr	r8, [r10, #2492]
	b	.L241
.L295:
	cmp	r4, #0
	beq	.L246
.L258:
	ldr	r3, [fp, #-76]
	mov	r6, #0
	str	r6, [r8, #1356]
	str	r6, [fp, #-64]
	mov	r7, r3
	ldr	r9, [r10, #2488]
	mov	r6, r3
	b	.L254
.L245:
	cmp	r8, #0
	beq	.L246
	mov	r4, r8
	b	.L252
.L244:
	ldr	r1, .L300+4
	mov	r0, #1
	bl	dprint_vfmw
.L290:
	mvn	r7, #0
.L285:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L246:
	ldr	r2, .L300+8
	mov	r0, #1
	ldr	r1, .L300+12
	mvn	r7, #0
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L297:
	ldr	r2, .L300+8
	mov	r0, #1
	ldr	r1, .L300+16
	mvn	r7, #0
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L298:
	cmp	r3, #0
	ldr	r1, [fp, #-48]
	mov	r7, r0
	movgt	r2, #1
	movle	r2, #0
	cmp	r1, #0
	andgt	r2, r2, #1
	movle	r2, #0
	cmp	r2, #0
	beq	.L244
	ldr	r2, [fp, #-88]
	movw	r5, #307
	ldr	r1, [fp, #-92]
	mla	r5, r5, r2, r1
	ldr	r2, .L300
	add	r3, r5, r3
	add	r3, r3, #14
	ldr	r0, [r2, r3, asl #2]
	bl	HEVCHAL_V5R2C1_CutSliceChain
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L293:
	ldr	r1, [fp, #-80]
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	HEVCHAL_V5R2C1_SetSliceMsgSedOnly
.L299:
	mov	r0, r6
	ldr	r2, .L300+8
	ldr	r1, .L300+20
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L285
.L292:
	mov	r0, r4
	ldr	r2, .L300+8
	ldr	r1, .L300+24
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L285
.L301:
	.align	2
.L300:
	.word	g_HwMem
	.word	.LC40
	.word	.LANCHOR1+2260
	.word	.LC38
	.word	.LC39
	.word	.LC36
	.word	.LC37
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_StartDec, .-HEVCHAL_V5R2C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.13999, %object
	.size	__func__.13999, 18
__func__.13999:
	.ascii	"HEVCWriteCabacTab\000"
	.space	2
	.type	s_InitValue, %object
	.size	s_InitValue, 1920
s_InitValue:
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	200
	.word	139
	.word	141
	.word	157
	.word	154
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	184
	.word	-1
	.word	-1
	.word	-1
	.word	184
	.word	63
	.word	94
	.word	138
	.word	182
	.word	154
	.word	111
	.word	141
	.word	154
	.word	154
	.word	139
	.word	139
	.word	138
	.word	153
	.word	136
	.word	167
	.word	152
	.word	152
	.word	110
	.word	110
	.word	124
	.word	125
	.word	140
	.word	153
	.word	125
	.word	127
	.word	140
	.word	109
	.word	111
	.word	143
	.word	127
	.word	111
	.word	79
	.word	108
	.word	123
	.word	63
	.word	110
	.word	110
	.word	124
	.word	125
	.word	140
	.word	153
	.word	125
	.word	127
	.word	140
	.word	109
	.word	111
	.word	143
	.word	127
	.word	111
	.word	79
	.word	108
	.word	123
	.word	63
	.word	91
	.word	171
	.word	134
	.word	141
	.word	140
	.word	92
	.word	137
	.word	138
	.word	140
	.word	152
	.word	138
	.word	139
	.word	153
	.word	74
	.word	149
	.word	92
	.word	139
	.word	107
	.word	122
	.word	152
	.word	140
	.word	179
	.word	166
	.word	182
	.word	140
	.word	227
	.word	122
	.word	197
	.word	111
	.word	111
	.word	125
	.word	110
	.word	110
	.word	94
	.word	124
	.word	108
	.word	124
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	140
	.word	139
	.word	182
	.word	182
	.word	152
	.word	136
	.word	152
	.word	136
	.word	153
	.word	136
	.word	139
	.word	111
	.word	136
	.word	139
	.word	111
	.word	-1
	.word	153
	.word	138
	.word	138
	.word	-1
	.word	-1
	.word	79
	.word	110
	.word	122
	.word	95
	.word	79
	.word	63
	.word	31
	.word	31
	.word	153
	.word	153
	.word	168
	.word	140
	.word	198
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	185
	.word	107
	.word	139
	.word	126
	.word	154
	.word	197
	.word	185
	.word	201
	.word	149
	.word	154
	.word	139
	.word	154
	.word	154
	.word	154
	.word	152
	.word	149
	.word	107
	.word	167
	.word	154
	.word	153
	.word	111
	.word	154
	.word	154
	.word	139
	.word	139
	.word	107
	.word	167
	.word	91
	.word	122
	.word	107
	.word	167
	.word	125
	.word	110
	.word	94
	.word	110
	.word	95
	.word	79
	.word	125
	.word	111
	.word	110
	.word	78
	.word	110
	.word	111
	.word	111
	.word	95
	.word	94
	.word	108
	.word	123
	.word	108
	.word	125
	.word	110
	.word	94
	.word	110
	.word	95
	.word	79
	.word	125
	.word	111
	.word	110
	.word	78
	.word	110
	.word	111
	.word	111
	.word	95
	.word	94
	.word	108
	.word	123
	.word	108
	.word	121
	.word	140
	.word	61
	.word	154
	.word	154
	.word	196
	.word	196
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	182
	.word	134
	.word	149
	.word	136
	.word	153
	.word	121
	.word	136
	.word	137
	.word	169
	.word	194
	.word	166
	.word	167
	.word	154
	.word	167
	.word	137
	.word	182
	.word	155
	.word	154
	.word	139
	.word	153
	.word	139
	.word	123
	.word	123
	.word	63
	.word	153
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	170
	.word	153
	.word	123
	.word	123
	.word	107
	.word	121
	.word	107
	.word	121
	.word	167
	.word	151
	.word	183
	.word	140
	.word	151
	.word	183
	.word	140
	.word	-1
	.word	124
	.word	138
	.word	94
	.word	-1
	.word	-1
	.word	79
	.word	154
	.word	137
	.word	95
	.word	79
	.word	63
	.word	31
	.word	31
	.word	153
	.word	153
	.word	168
	.word	169
	.word	198
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	160
	.word	107
	.word	139
	.word	126
	.word	154
	.word	197
	.word	185
	.word	201
	.word	134
	.word	154
	.word	139
	.word	154
	.word	154
	.word	183
	.word	152
	.word	149
	.word	92
	.word	167
	.word	154
	.word	153
	.word	111
	.word	154
	.word	154
	.word	139
	.word	139
	.word	107
	.word	167
	.word	91
	.word	107
	.word	107
	.word	167
	.word	125
	.word	110
	.word	124
	.word	110
	.word	95
	.word	94
	.word	125
	.word	111
	.word	111
	.word	79
	.word	125
	.word	126
	.word	111
	.word	111
	.word	79
	.word	108
	.word	123
	.word	93
	.word	125
	.word	110
	.word	124
	.word	110
	.word	95
	.word	94
	.word	125
	.word	111
	.word	111
	.word	79
	.word	125
	.word	126
	.word	111
	.word	111
	.word	79
	.word	108
	.word	123
	.word	93
	.word	121
	.word	140
	.word	61
	.word	154
	.word	154
	.word	196
	.word	167
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	182
	.word	134
	.word	149
	.word	136
	.word	153
	.word	121
	.word	136
	.word	122
	.word	169
	.word	208
	.word	166
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	170
	.word	154
	.word	139
	.word	153
	.word	139
	.word	123
	.word	123
	.word	63
	.word	124
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	170
	.word	153
	.word	138
	.word	138
	.word	122
	.word	121
	.word	122
	.word	121
	.word	167
	.word	151
	.word	183
	.word	140
	.word	151
	.word	183
	.word	140
	.word	-1
	.word	224
	.word	167
	.word	122
	.word	-1
	.word	-1
	.type	__func__.14006, %object
	.size	__func__.14006, 23
__func__.14006:
	.ascii	"HEVCHAL_V5R2C1_InitHal\000"
	.space	1
	.type	__func__.14021, %object
	.size	__func__.14021, 29
__func__.14021:
	.ascii	"HEVCHAL_V5R2C1_CutSliceChain\000"
	.space	3
	.type	__func__.14040, %object
	.size	__func__.14040, 19
__func__.14040:
	.ascii	"HEVC_WriteTileInfo\000"
	.space	1
	.type	__func__.14066, %object
	.size	__func__.14066, 25
__func__.14066:
	.ascii	"HEVCHAL_V5R2C1_SetPicMsg\000"
	.space	3
	.type	__func__.14086, %object
	.size	__func__.14086, 34
__func__.14086:
	.ascii	"HEVCHAL_SetSliceMsgStreamAddrInfo\000"
	.space	2
	.type	__func__.14140, %object
	.size	__func__.14140, 27
__func__.14140:
	.ascii	"HEVCHAL_V5R2C1_SetSliceMsg\000"
	.space	1
	.type	s_SliceTypeForPMV, %object
	.size	s_SliceTypeForPMV, 12
s_SliceTypeForPMV:
	.word	2
	.word	1
	.word	0
	.type	__func__.14151, %object
	.size	__func__.14151, 23
__func__.14151:
	.ascii	"HEVCHAL_CheckParaValid\000"
	.space	1
	.type	__func__.14157, %object
	.size	__func__.14157, 25
__func__.14157:
	.ascii	"HEVCHAL_GetVdmRegVirAddr\000"
	.space	3
	.type	__func__.14163, %object
	.size	__func__.14163, 23
__func__.14163:
	.ascii	"HEVCHAL_CheckSlicePara\000"
	.space	1
	.type	__func__.14190, %object
	.size	__func__.14190, 25
__func__.14190:
	.ascii	"HEVCHAL_V5R2C1_CfgVdmReg\000"
	.space	3
	.type	__func__.14210, %object
	.size	__func__.14210, 34
__func__.14210:
	.ascii	"HEVCHAL_V5R2C1_SetSliceMsgSedOnly\000"
	.space	2
	.type	__func__.14240, %object
	.size	__func__.14240, 24
__func__.14240:
	.ascii	"HEVCHAL_V5R2C1_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"can not map mn virtual address!\012\000" )
	.space	3
.LC1:
	ASCII(.ascii	"%s: %s\012\000" )
.LC2:
	ASCII(.ascii	"pHwMem is NULL!\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"HEVCWriteCabacTab return error.\012\000" )
	.space	3
.LC4:
	ASCII(.ascii	"can not map slice msg virtual address!\012\000" )
.LC5:
	ASCII(.ascii	"qmatrix[%d] = 0x%x\012\000" )
.LC6:
	ASCII(.ascii	"picmsg Dxx addr 0x%x = 0x%x\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"can not map slice segment info virtual address!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC8:
	ASCII(.ascii	"TileId: 0x%x\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"can not map down msg virtual address!\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC11:
	ASCII(.ascii	"picmsg D[0] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"HEVC_WriteTileInfo return error.\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"%s FATAL: i=0, valid_bitlen=0\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"slicemsg D[%d] addr 0x%x = 0x%x\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"HEVCHAL_V5R2C1_SetSliceMsg can not map slice msg vi" )
	ASCII(.ascii	"rtual address!\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"%s VdhId %d >= %d\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"pParam is null\012\000" )
.LC18:
	ASCII(.ascii	"FATAL: ApcSize > 16\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"VdhId is wrong! HEVC4HAL_V200R003_StartDec\012\000" )
.LC20:
	ASCII(.ascii	"%s vdm register virtual address not mapped, reset f" )
	ASCII(.ascii	"ailed!\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"%s: i = %d, pSlicePara = NULL!\012\000" )
.LC22:
	ASCII(.ascii	"SliceSegmentTileAddress %d < prevEndCtbInSliceTile " )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"end_ctb_in_slice_raster(%d)/end_ctb_in_slice_tile(%" )
	ASCII(.ascii	"d) > pic_max_ctb(%d)\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"SliceSegmentTileAddress %d > end_ctb_in_slice_tile " )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"HEVC_BASIC_CFG0 = 0x%x\012\000" )
.LC27:
	ASCII(.ascii	"HEVC_BASIC_CFG1 = 0x%x\012\000" )
.LC28:
	ASCII(.ascii	"AVM_ADDR = 0x%x\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"VREG_V200R003_PART_DEC_OVER_INT_LEVEL=0x%x\012\000" )
.LC30:
	ASCII(.ascii	"VREG_LINE_NUM_STADDR = 0x%x\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"HEVC_VFMW_YSTADDR_1D = 0x%x\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"HEVC_VFMW_UVOFFSET_1D = 0x%x\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"SCD REG_EMAR_ID = 0x%x\012\000" )
.LC34:
	ASCII(.ascii	"VREG_FF_APT_EN = 0x%x\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"%s : pTargetSlicePara == NULL\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	"%s 0: set slice msg failed!\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"%s pFirstSlice = NULL!\012\000" )
.LC38:
	ASCII(.ascii	"%s pTargetSlicePara is NULL!\012\000" )
	.space	2
.LC39:
	ASCII(.ascii	"%s 1: set slice msg failed!\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"No slice to dec, add up msg report.\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	s_CabacMN, %object
	.size	s_CabacMN, 928
s_CabacMN:
	.space	928
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
