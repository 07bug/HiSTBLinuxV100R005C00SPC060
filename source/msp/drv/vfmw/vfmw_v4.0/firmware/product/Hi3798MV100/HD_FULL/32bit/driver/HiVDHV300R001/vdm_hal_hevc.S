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
	ldr	r1, .L19+12
	ldr	r3, .L19+16
	ldr	r2, .L19+20
	ldr	r4, [r1, #68]
	ldr	r1, .L19+24
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L20:
	.align	2
.L19:
	.word	.LANCHOR0
	.word	.LANCHOR1+20
	.word	.LANCHOR0+1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LANCHOR1
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCWriteCabacTab, .-HEVCWriteCabacTab
	.align	2
	.global	HEVCHAL_V300R001_InitHal
	.type	HEVCHAL_V300R001_InitHal, %function
HEVCHAL_V300R001_InitHal:
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
	bl	HEVCWriteCabacTab
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, .L26
	mov	r0, #1
	ldr	r1, .L26+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L27:
	.align	2
.L26:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	UNWIND(.fnend)
	.size	HEVCHAL_V300R001_InitHal, .-HEVCHAL_V300R001_InitHal
	.align	2
	.global	HEVCGet_V300R001_VirAddr
	.type	HEVCGet_V300R001_VirAddr, %function
HEVCGet_V300R001_VirAddr:
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
	.size	HEVCGet_V300R001_VirAddr, .-HEVCGet_V300R001_VirAddr
	.align	2
	.global	HEVCGet_V300R001_PhyAddr
	.type	HEVCGet_V300R001_PhyAddr, %function
HEVCGet_V300R001_PhyAddr:
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
	.size	HEVCGet_V300R001_PhyAddr, .-HEVCGet_V300R001_PhyAddr
	.align	2
	.global	HEVCHAL_V300R001_CutSliceChain
	.type	HEVCHAL_V300R001_CutSliceChain, %function
HEVCHAL_V300R001_CutSliceChain:
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
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L33
	mov	r0, #0
	str	r0, [r3, #252]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L33:
	ldr	r1, .L34
	ldr	r3, .L34+4
	ldr	r2, .L34+8
	ldr	r4, [r1, #68]
	ldr	r1, .L34+12
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L35:
	.align	2
.L34:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	.word	.LANCHOR1+1940
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V300R001_CutSliceChain, .-HEVCHAL_V300R001_CutSliceChain
	.align	2
	.global	HEVC_WriteQmatrix
	.type	HEVC_WriteQmatrix, %function
HEVC_WriteQmatrix:
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
	mov	r9, r0
	str	r1, [fp, #-48]
	mov	r10, r2
	beq	.L36
	ldr	r8, .L41
	sub	r6, r3, #4
	sub	r7, r0, #4
	mov	r4, #0
.L38:
	ldr	r3, [r7, #4]!
	mov	r2, r4
	ldr	r1, .L41+4
	mov	r0, #4
	add	r4, r4, #1
	mov	r5, r7
	str	r3, [r6, #4]!
	ldr	r3, [r5], r10
	ldr	ip, [r8, #68]
	blx	ip
	rsb	r2, r9, r5
	ldr	r3, [r6]
	mov	r0, #4
	ldr	r5, [r8, #68]
	ldr	r1, .L41+8
	blx	r5
	ldr	r3, [fp, #-48]
	cmp	r4, r3
	bne	.L38
.L36:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L42:
	.align	2
.L41:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix, .-HEVC_WriteQmatrix
	.align	2
	.global	HEVC_WriteTileInfo
	.type	HEVC_WriteTileInfo, %function
HEVC_WriteTileInfo:
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
	mov	r6, r0
	ldr	r0, [r1, #1104]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-48]
	beq	.L44
	add	r8, r3, #1024
	add	r9, r3, #4
	add	r8, r8, #4
	mov	r7, r6
	mov	r10, r6
	mov	r5, #0
.L45:
	mov	ip, r10
	mov	lr, r9
	mov	r0, #0
.L49:
	cmp	r0, #252
	add	r0, r0, #4
	strgt	r5, [lr, #-4]
	add	ip, ip, #4
	ldrleb	r3, [ip, #1666]	@ zero_extendqisi2
	add	lr, lr, #4
	ldrleb	r4, [ip, #1667]	@ zero_extendqisi2
	ldrleb	r2, [ip, #1664]	@ zero_extendqisi2
	movle	r3, r3, asl #16
	ldrleb	r1, [ip, #1665]	@ zero_extendqisi2
	orrle	r3, r3, r4, asl #24
	orrle	r3, r3, r2
	orrle	r3, r3, r1, asl #8
	strle	r3, [lr, #-8]
	cmp	r0, #512
	bne	.L49
	add	r9, r9, #512
	add	r10, r10, #256
	cmp	r9, r8
	bne	.L45
	mov	r3, #0
	mov	r0, r3
.L50:
	cmp	r3, #9
	add	r3, r3, #1
	strgt	r0, [r8, #-4]
	add	r6, r6, #8
	ldrle	r1, [r6, #2176]
	add	r8, r8, #4
	ldrle	r2, [r6, #2172]
	orrle	r2, r2, r1, asl #16
	strle	r2, [r8, #-8]
	cmp	r3, #20
	bne	.L50
	ldr	r3, [fp, #-48]
	add	r2, r3, #1104
	mov	r3, #0
	add	r2, r2, #4
	mov	ip, r3
.L56:
	cmp	r3, #10
	add	r3, r3, #1
	strgt	ip, [r2, #-4]
	add	r7, r7, #8
	ldrle	r0, [r7, #2256]
	add	r2, r2, #4
	ldrle	r1, [r7, #2252]
	orrle	r1, r1, r0, asl #16
	strle	r1, [r2, #-8]
	cmp	r3, #22
	bne	.L56
	mov	r0, #0
.L61:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L44:
	ldr	r1, .L64
	ldr	r3, .L64+4
	ldr	r2, .L64+8
	ldr	r4, [r1, #68]
	ldr	r1, .L64+12
	blx	r4
	mvn	r0, #0
	b	.L61
.L65:
	.align	2
.L64:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LANCHOR1+1972
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVC_WriteTileInfo, .-HEVC_WriteTileInfo
	.align	2
	.global	HEVCHAL_V300R001_SetPicMsg
	.type	HEVCHAL_V300R001_SetPicMsg, %function
HEVCHAL_V300R001_SetPicMsg:
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
	mov	r8, r2
	mov	r6, r1
	mov	r9, r3
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L81
	ldr	r7, .L83
	mov	r2, #1280
	mov	r1, #0
	ldr	r3, [r7, #48]
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r1, .L83+4
	mov	r0, #4
	blx	r3
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldrb	ip, [r4, #1]	@ zero_extendqisi2
	mov	r2, r8
	ldr	lr, [r4, #16]
	mov	r0, #4
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	mov	r3, r3, asl #25
	ldr	r10, [r4, #8]
	orr	r3, r3, ip, asl #24
	ldrb	ip, [r4, #3]	@ zero_extendqisi2
	mov	lr, lr, asl #9
	orr	r1, r3, r1, asl #23
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	orr	lr, lr, r10, asl #19
	ldrb	r10, [r4, #12]	@ zero_extendqisi2
	orr	r1, r1, ip, asl #22
	ldr	ip, [r4, #20]
	orr	lr, lr, ip
	orr	ip, r1, r3, asl #21
	orr	r3, lr, r10, asl #18
	ldr	r1, .L83+8
	orr	r3, r3, ip
	str	r3, [r5]
	ldr	r3, [r5]
	ldr	r10, [r7, #68]
	blx	r10
	ldr	r3, [r4, #24]
	str	r3, [r5, #4]
	ldr	r2, [r4, #36]
	ldr	r1, [r4, #28]
	ldr	ip, [r4, #68]
	ldr	r3, [r4, #40]
	mov	r2, r2, asl #24
	ldr	r0, [r4, #44]
	orr	r2, r2, r1, asl #29
	ldr	lr, [r4, #48]
	orr	r2, r2, ip
	ldr	r1, [r4, #52]
	orr	r3, r2, r3, asl #21
	ldr	ip, [r4, #56]
	orr	r3, r3, r0, asl #18
	ldr	r2, [r4, #60]
	orr	r0, r3, lr, asl #15
	orr	r1, r0, r1, asl #12
	ldr	r0, [r4, #64]
	ldrb	r3, [r4, #32]	@ zero_extendqisi2
	orr	r1, r1, ip, asl #9
	orr	r2, r1, r2, asl #6
	ldrb	r1, [r4, #33]	@ zero_extendqisi2
	orr	r2, r2, r0, asl #3
	orr	r3, r2, r3, asl #28
	orr	r3, r3, r1, asl #27
	str	r3, [r5, #8]
	ldr	r0, [r4, #76]
	ldr	r2, [r4, #72]
	ldr	r1, [r4, #92]
	ldr	ip, [r4, #80]
	mov	r0, r0, asl #16
	ldr	r3, [r4, #84]
	orr	r2, r0, r2, asl #22
	orr	r2, r2, r1
	ldr	r1, [r4, #88]
	orr	r2, r2, ip, asl #12
	orr	r3, r2, r3, asl #8
	orr	r3, r3, r1, asl #4
	str	r3, [r5, #12]
	ldr	r3, [r6, #1084]
	str	r3, [r5, #16]
	ldr	r3, [r6, #1088]
	str	r3, [r5, #20]
	ldr	r3, [r4, #1284]
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #1452]
	str	r3, [r5, #24]
	ldr	r3, [r6, #1096]
	str	r3, [r5, #28]
	ldr	r2, [r4, #2412]
	cmp	r2, #0
	beq	.L69
	add	r0, r4, #2336
	add	ip, r5, #32
	add	r0, r0, #8
	mov	r1, #0
.L70:
	ldr	r3, [r0, #4]!
	add	r1, r1, #1
	add	r3, r3, #328
	add	r3, r3, #2
	ldr	r3, [r4, r3, asl #2]
	str	r3, [ip], #4
	ldr	r2, [r4, #2412]
	cmp	r2, r1
	bhi	.L70
	cmp	r2, #15
	bhi	.L73
.L69:
	add	r1, r2, #8
	add	r1, r5, r1, lsl #2
.L72:
	ldr	r3, [r4, #2348]
	add	r2, r2, #1
	cmp	r2, #15
	add	r3, r3, #328
	add	r3, r3, #2
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r1], #4
	bls	.L72
.L73:
	ldr	r1, [r6, #1100]
	add	r3, r4, #116
	add	r2, r5, #104
	add	r0, r4, #180
	str	r1, [r5, #100]
.L71:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2], #4
	bne	.L71
	ldr	r3, [r6, #1092]
	mov	r1, r6
	mov	r0, r4
	str	r3, [r5, #172]
	ldr	r2, [r4, #184]
	ldr	r3, [r4, #188]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #216]
	bl	HEVC_WriteTileInfo
	subs	r10, r0, #0
	bne	.L82
	ldr	r3, [r6, #1104]
	mov	r1, r5
	mov	r0, #64
	str	r3, [r5, #220]
	ldr	r3, [r6, #1116]
	str	r3, [r5, #224]
	ldr	r3, [r6, #1108]
	str	r3, [r5, #228]
	ldr	r3, [r6, #1120]
	str	r3, [r5, #232]
	ldr	r3, [r6, #1112]
	str	r3, [r5, #236]
	ldr	r2, [r4, #220]
	ldr	ip, [r4, #224]
	ldrb	r3, [r4, #212]	@ zero_extendqisi2
	mov	r2, r2, asl #16
	ldr	lr, [r4, #236]
	orr	r6, r2, ip, asl #13
	ldrb	r2, [r4, #213]	@ zero_extendqisi2
	mov	r3, r3, asl #24
	and	ip, lr, #31
	ldrb	lr, [r4, #228]	@ zero_extendqisi2
	orr	ip, r6, ip
	orr	r3, r3, r2, asl #23
	ldrb	r2, [r4, #214]	@ zero_extendqisi2
	ldr	r6, [r4, #232]
	orr	ip, ip, lr, asl #12
	ldrb	lr, [r4, #229]	@ zero_extendqisi2
	orr	r3, r3, r2, asl #22
	ldrb	r2, [r4, #215]	@ zero_extendqisi2
	and	r6, r6, #31
	orr	lr, ip, lr, asl #11
	ldrb	ip, [r4, #230]	@ zero_extendqisi2
	orr	r2, r3, r2, asl #21
	ldrb	r3, [r4, #216]	@ zero_extendqisi2
	orr	ip, lr, ip, asl #10
	orr	r2, r2, r3, asl #20
	ldrb	r3, [r4, #217]	@ zero_extendqisi2
	orr	ip, ip, r6, asl #5
	orr	r3, r2, r3, asl #19
	orr	r3, ip, r3
	str	r3, [r5, #240]
	ldr	r2, [r4, #240]
	ldr	r3, [r4, #244]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #244]
	str	r9, [r5, #252]
	bl	HEVC_GetVirAddr
	mov	r1, r8
	mov	r5, r0
	mov	r0, #64
	bl	HEVC_GetPhyAddr
	mov	r3, r5
	mov	r1, #256
	mov	r2, r0
	add	r0, r4, #252
	bl	HEVC_WriteQmatrix
.L68:
	mov	r0, r10
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L82:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L83+12
	mvn	r10, #0
	blx	r3
	b	.L68
.L81:
	ldr	r1, .L83
	mvn	r10, #0
	ldr	r3, .L83+16
	ldr	r2, .L83+20
	ldr	r4, [r1, #68]
	ldr	r1, .L83+24
	blx	r4
	b	.L68
.L84:
	.align	2
.L83:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC7
	.word	.LANCHOR1+1992
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V300R001_SetPicMsg, .-HEVCHAL_V300R001_SetPicMsg
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	HEVCHAL_V300R001_SetSliceMsg
	.type	HEVCHAL_V300R001_SetSliceMsg, %function
HEVCHAL_V300R001_SetSliceMsg:
	UNWIND(.fnstart)
	@ args = 24, pretend = 0, frame = 24
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
	str	r0, [fp, #-56]
	mov	r0, r3
	mov	r6, r3
	mov	r4, r2
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L132
	ldr	r8, .L134
	mov	r1, #0
	mov	r2, #1280
	add	ip, r5, #4
	rsb	r9, r5, r6
	mov	r10, r1
	ldr	r3, [r8, #48]
	mov	r6, r5
	str	ip, [fp, #-52]
	blx	r3
	add	r3, r5, #8
	str	r5, [fp, #-64]
	ldr	r5, [fp, #-52]
	add	r7, r4, #16
	str	r4, [fp, #-60]
	mov	r4, r10
	str	r3, [fp, #-48]
.L92:
	cmp	r4, #0
	mov	r3, r6
	mov	r2, r10
	ldr	r1, .L134+4
	mov	r0, #4
	mov	lr, r6
	beq	.L133
	ldr	ip, [r7, #-16]
	cmp	ip, #0
	str	ip, [fp, #-52]
	beq	.L90
.L89:
	ldr	r1, [fp, #-56]
	mov	r2, r10
	ldr	r3, [r7]
	mov	r0, #4
	ldr	ip, [r1, #1308]
	bic	r3, r3, #15
	ldr	r1, .L134+4
	bic	ip, ip, #15
	rsb	ip, ip, r3
	str	ip, [lr], r9
	ldr	ip, [r5, #-4]
	mov	r3, lr
	str	ip, [sp]
	ldr	ip, [r8, #68]
	blx	ip
	ldr	ip, [r7]
	ldr	r0, [r7, #-8]
	mov	r3, r5
	add	r2, r10, #1
	ldr	r1, .L134+4
	add	ip, r0, ip, lsl #3
	mov	r0, #4
	and	ip, ip, #127
	str	ip, [r3], r9
	ldr	ip, [r6, #4]
	str	ip, [sp]
	ldr	ip, [r8, #68]
	blx	ip
	ldr	ip, [r7, #-16]
	ldr	r3, [fp, #-48]
	add	r2, r10, #2
	ldr	r1, .L134+4
	mov	r0, #4
	str	ip, [r3], r9
	ldr	ip, [r6, #8]
	str	ip, [sp]
	ldr	ip, [r8, #68]
	blx	ip
.L91:
	add	r4, r4, #1
	ldr	r3, [fp, #-48]
	cmp	r4, #2
	add	r7, r7, #4
	add	r3, r3, #12
	add	r6, r6, #12
	add	r10, r10, #3
	add	r5, r5, #12
	str	r3, [fp, #-48]
	bne	.L92
	ldr	r4, [fp, #-60]
	ldr	r5, [fp, #-64]
	ldr	r0, [fp, #12]
	ldrb	r1, [r4, #24]	@ zero_extendqisi2
	ldrb	r2, [r4, #25]	@ zero_extendqisi2
	ldr	r3, [r4, #28]
	ldrb	lr, [r4, #32]	@ zero_extendqisi2
	mov	r1, r1, asl #27
	and	r3, r3, #63
	orr	r2, r1, r2, asl #26
	ldr	ip, [r4, #36]
	orr	r2, r2, r3, asl #19
	ldr	r1, .L134+8
	orr	r3, r2, lr, asl #18
	orr	r3, r3, ip
	str	r3, [r5, #24]
	ldr	ip, [r4, #44]
	ldr	r2, [r4, #56]
	ldr	lr, [r4, #76]
	ldr	r3, [r4, #60]
	mov	ip, ip, asl #24
	orr	ip, ip, r2, asl #20
	ldr	r2, [r4, #72]
	add	lr, r1, lr, lsl #2
	ldr	r1, [r4, #68]
	orr	r3, ip, r3, asl #16
	orr	r3, r3, r2, asl #8
	ldr	ip, [lr, #2052]
	ldr	lr, [r4, #40]
	orr	r2, r3, r1, asl #2
	ldrb	r3, [r4, #52]	@ zero_extendqisi2
	orr	r1, r2, ip
	ldrb	ip, [r4, #64]	@ zero_extendqisi2
	orr	r2, r1, lr, asl #28
	ldrb	r1, [r4, #65]	@ zero_extendqisi2
	orr	r2, r2, r3, asl #27
	orr	r3, r2, ip, asl #15
	orr	r3, r3, r1, asl #14
	str	r3, [r5, #28]
	ldr	r3, [fp, #-56]
	str	r0, [r5, #32]
	ldr	r6, [r3, #20]
	add	r6, r6, #1
	mov	r1, r6
	bl	__aeabi_uidiv
	mov	r1, r6
	mov	r6, r0, asl #16
	ldr	r0, [fp, #12]
	bl	__aeabi_uidivmod
	ldr	r3, [fp, #16]
	orr	r1, r6, r1
	str	r1, [r5, #36]
	str	r3, [r5, #40]
	ldr	r2, [r4, #96]
	ldr	r3, [r4, #100]
	and	r2, r2, #31
	and	r3, r3, #31
	orr	r3, r3, r2, asl #8
	str	r3, [r5, #44]
	ldr	r1, [r4, #108]
	ldr	r0, [r4, #104]
	and	r1, r1, #15
	ldrb	r2, [r4, #115]	@ zero_extendqisi2
	and	r0, r0, #15
	ldrb	r3, [r4, #113]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	ldrb	ip, [r4, #112]	@ zero_extendqisi2
	orr	r1, r1, r0, asl #16
	ldrb	r0, [r4, #114]	@ zero_extendqisi2
	orr	r2, r1, r2
	orr	r2, r2, r3, asl #3
	orr	r3, r2, ip, asl #2
	orr	r3, r3, r0, asl #1
	str	r3, [r5, #48]
	ldr	ip, [r4, #68]
	cmp	ip, #0
	beq	.L117
	mov	r2, #0
	add	r1, r4, #112
	mov	r3, r2
.L94:
	ldr	r0, [r1, #4]!
	orr	r2, r2, r0, asl r3
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L94
.L93:
	str	r2, [r5, #52]
	ldr	ip, [r4, #72]
	cmp	ip, #0
	beq	.L118
	mov	r2, #0
	add	r1, r4, #176
	mov	r3, r2
.L96:
	ldr	r0, [r1, #4]!
	orr	r2, r2, r0, asl r3
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L96
.L95:
	str	r2, [r5, #56]
	ldr	r0, [r4, #68]
	cmp	r0, #0
	addne	ip, r4, #368
	movne	r1, #0
	movne	r7, #15
	movne	r2, r1
	bne	.L102
	b	.L103
.L100:
	cmp	r6, r2
	streq	r1, [r5, r7, asl #2]
	add	r2, r2, #1
	ldreq	r0, [r4, #68]
	cmp	r0, r2
	bls	.L103
.L102:
	and	r3, r2, #7
	ldr	lr, [ip, #4]!
	cmp	r3, #7
	sub	r6, r0, #1
	mov	r3, r3, asl #2
	orr	r1, r1, lr, asl r3
	bne	.L100
	str	r1, [r5, r7, asl #2]
	add	r2, r2, #1
	ldr	r0, [r4, #68]
	add	r7, r7, #1
	mov	r1, #0
	cmp	r0, r2
	bhi	.L102
.L103:
	ldr	r0, [r4, #72]
	cmp	r0, #0
	addne	ip, r4, #432
	movne	r1, #0
	movne	r7, #17
	movne	r2, r1
	bne	.L108
	b	.L99
.L106:
	cmp	r6, r2
	streq	r1, [r5, r7, asl #2]
	add	r2, r2, #1
	ldreq	r0, [r4, #72]
	cmp	r0, r2
	bls	.L99
.L108:
	and	r3, r2, #7
	ldr	lr, [ip, #4]!
	cmp	r3, #7
	sub	r6, r0, #1
	mov	r3, r3, asl #2
	orr	r1, r1, lr, asl r3
	bne	.L106
	str	r1, [r5, r7, asl #2]
	add	r2, r2, #1
	ldr	r0, [r4, #72]
	add	r7, r7, #1
	mov	r1, #0
	cmp	r0, r2
	bhi	.L108
.L99:
	ldr	r3, [r4, #564]
	ldr	r2, [fp, #-56]
	str	r3, [r5, #92]
	ldr	r3, [r2, #76]
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
	ldrb	r3, [r2, #33]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L104
.L105:
	ldr	r3, [fp, #-56]
	ldrb	r3, [r3, #32]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L110
.L111:
	mov	r0, #0
.L87:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L90:
	ldr	ip, [fp, #-52]
	str	ip, [r3], r9
	ldr	ip, [r5, #-4]
	str	ip, [sp]
	ldr	ip, [r8, #68]
	blx	ip
	ldr	ip, [fp, #-52]
	mov	r3, r5
	add	r2, r10, #1
	ldr	r1, .L134+4
	mov	r0, #4
	str	ip, [r3], r9
	ldr	ip, [r6, #4]
	str	ip, [sp]
	ldr	ip, [r8, #68]
	blx	ip
	ldr	ip, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r2, r10, #2
	ldr	r1, .L134+4
	mov	r0, #4
	str	ip, [r3], r9
	ldr	ip, [r6, #8]
	str	ip, [sp]
	ldr	ip, [r8, #68]
	blx	ip
	b	.L91
.L104:
	ldr	r3, [r4, #76]
	cmp	r3, #1
	bne	.L105
.L109:
	mov	r1, r5
	mov	r0, #64
	bl	HEVC_GetVirAddr
	mov	r1, r5
	mov	r6, r0
	mov	r0, #128
	bl	HEVC_GetVirAddr
	ldr	r3, [r4, #68]
	cmp	r3, #0
	beq	.L115
	add	r9, r4, #712
	add	r8, r4, #584
	add	r5, r0, #128
	mov	r7, r6
	mov	ip, r4
	mov	lr, #0
.L114:
	ldr	r2, [r9, #4]!
	add	lr, lr, #1
	ldr	r10, [r8, #4]!
	add	ip, ip, #8
	ldr	r1, [r4, #580]
	uxtb	r2, r2
	ubfx	r10, r10, #0, #9
	and	r1, r1, #7
	mov	r2, r2, asl #12
	orr	r3, r2, r10, asl #3
	orr	r3, r3, r1
	str	r3, [r7], #4
	ldr	r1, [ip, #836]
	ldrb	r3, [ip, #1092]	@ zero_extendqisi2
	ldr	r2, [r4, #584]
	ubfx	r1, r1, #0, #9
	mov	r3, r3, asl #12
	and	r2, r2, #7
	orr	r3, r3, r1, asl #3
	orr	r3, r3, r2
	str	r3, [r5, #-128]
	ldr	r3, [ip, #840]
	ldrb	r2, [ip, #1096]	@ zero_extendqisi2
	ubfx	r3, r3, #0, #9
	orr	r3, r3, r2, asl #9
	str	r3, [r5], #4
	ldr	r3, [r4, #68]
	cmp	r3, lr
	bhi	.L114
.L115:
	ldr	r5, [r4, #76]
	cmp	r5, #0
	bne	.L111
	ldr	r3, [r4, #72]
	cmp	r3, #0
	beq	.L111
	add	r6, r6, #64
	add	r0, r0, #192
	add	r8, r4, #776
	add	r7, r4, #648
	mov	lr, r4
.L116:
	ldr	r2, [r8, #4]!
	add	r5, r5, #1
	ldr	r3, [r7, #4]!
	add	lr, lr, #8
	ldr	r1, [r4, #580]
	uxtb	r2, r2
	ubfx	r3, r3, #0, #9
	and	r1, r1, #7
	mov	r2, r2, asl #12
	orr	r3, r2, r3, asl #3
	orr	r3, r3, r1
	str	r3, [r6], #4
	ldr	r3, [lr, #964]
	ldrb	r1, [lr, #1220]	@ zero_extendqisi2
	ldr	r2, [r4, #584]
	ubfx	ip, r3, #0, #9
	mov	r3, r1, asl #12
	and	r2, r2, #7
	orr	r3, r3, ip, asl #3
	orr	r3, r3, r2
	str	r3, [r0, #-128]
	ldr	r3, [lr, #968]
	ldrb	r2, [lr, #1224]	@ zero_extendqisi2
	ubfx	r3, r3, #0, #9
	orr	r3, r3, r2, asl #9
	str	r3, [r0], #4
	ldr	r3, [r4, #72]
	cmp	r3, r5
	bhi	.L116
	b	.L111
.L110:
	ldr	r3, [r4, #76]
	cmp	r3, #0
	beq	.L109
	b	.L111
.L117:
	mov	r2, ip
	b	.L93
.L118:
	mov	r2, ip
	b	.L95
.L132:
	ldr	r1, .L134
	ldr	r3, .L134+12
	ldr	r2, .L134+16
	ldr	r4, [r1, #68]
	ldr	r1, .L134+20
	blx	r4
	mvn	r0, #0
	b	.L87
.L133:
	ldr	r3, [fp, #-60]
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L89
	mov	r0, r4
	ldr	r3, [r8, #68]
	ldr	r2, .L134+16
	ldr	r1, .L134+24
	blx	r3
	mvn	r0, #0
	b	.L87
.L135:
	.align	2
.L134:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LANCHOR1
	.word	.LC11
	.word	.LANCHOR1+2020
	.word	.LC1
	.word	.LC12
	UNWIND(.fnend)
	.size	HEVCHAL_V300R001_SetSliceMsg, .-HEVCHAL_V300R001_SetSliceMsg
	.align	2
	.global	HEVCHAL_V300R001_CfgVdmReg
	.type	HEVCHAL_V300R001_CfgVdmReg, %function
HEVCHAL_V300R001_CfgVdmReg:
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
	mov	r4, r0
	ldr	lr, [r4, #16]
	subs	r5, r2, #0
	ldr	r3, [r4, #20]
	mov	r0, #1
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	mov	ip, #0
	str	ip, [fp, #-48]
	mov	r8, r1
	bfi	r0, r2, #6, #1
	mov	r2, #0
	mla	r3, lr, r3, r3
	and	r0, r0, #111
	bfi	r2, ip, #7, #1
	bfi	r0, ip, #5, #1
	strb	r2, [fp, #-46]
	strb	r0, [fp, #-45]
	add	r3, r3, lr
	ldr	r2, [fp, #-48]
	bfi	r2, r3, #0, #20
	str	r2, [fp, #-48]
	str	r2, [r4, #2432]
	ble	.L160
	ldr	r6, .L164
	mov	r2, #1
	mov	r3, r5
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L164+4
	ldr	r7, [r6, #68]
	ldr	r1, .L164+8
	blx	r7
.L138:
	ldr	r2, [r4, #1316]
	mov	r3, #0
	mov	r10, #3
	strh	r10, [fp, #-46]	@ movhi
	bfi	r3, r2, #6, #1
	mov	r2, #13
	strb	r3, [fp, #-47]
	mov	r3, #32
	strb	r2, [fp, #-48]
	cmp	r5, #0
	strb	r3, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r4, #2436]
	ble	.L161
	mov	r7, #1
	ldr	r9, [r6, #68]
	str	r7, [sp]
	mov	r3, r5
	ldr	r2, .L164+4
	mov	r0, #32
	ldr	r1, .L164+8
	blx	r9
	ldr	r9, [r8, #48]
	ldr	ip, [r6, #68]
	mov	r3, r5
	bic	r9, r9, #15
	str	r7, [sp]
	ldr	r2, .L164+4
	mov	r0, #32
	ldr	r1, .L164+8
	str	r9, [r4, #2440]
	blx	ip
	mov	r2, r9
	ldr	r3, [r6, #68]
	mov	r0, r10
	ldr	r1, .L164+12
	blx	r3
	ldr	r2, [r8, #32]
	mov	r3, r5
	str	r7, [sp]
	bic	r2, r2, #15
	ldr	r8, [r6, #68]
	str	r2, [r4, #2444]
	mov	r0, #32
	ldr	r2, .L164+4
	ldr	r1, .L164+8
	blx	r8
	ldr	r2, [r4, #1308]
	mov	r3, r5
	str	r7, [sp]
	bic	r2, r2, #15
	ldr	r8, [r6, #68]
	str	r2, [r4, #2448]
	mov	r0, #32
	ldr	r2, .L164+4
	ldr	r1, .L164+8
	blx	r8
	movw	r2, #3075
	str	r7, [sp]
	movt	r2, 48
	ldr	r8, [r6, #68]
	mov	r3, r5
	str	r2, [r4, #2456]
	mov	r0, #32
	str	r2, [r4, #2460]
	str	r2, [r4, #2464]
	str	r2, [r4, #2468]
	str	r2, [r4, #2472]
	str	r2, [r4, #2476]
	str	r2, [r4, #2480]
	ldr	r1, .L164+8
	ldr	r2, .L164+4
	blx	r8
	str	r7, [sp]
	ldr	r8, [r6, #68]
	mov	r3, r5
	ldr	r2, .L164+4
	mov	r0, #32
	ldr	r1, .L164+8
	blx	r8
	str	r7, [sp]
	ldr	r8, [r6, #68]
	mov	r3, r5
	ldr	r2, .L164+4
	mov	r0, #32
	ldr	r1, .L164+8
	blx	r8
	str	r7, [sp]
	ldr	r8, [r6, #68]
	mov	r3, r5
	ldr	r2, .L164+4
	mov	r0, #32
	ldr	r1, .L164+8
	blx	r8
	str	r7, [sp]
	ldr	r8, [r6, #68]
	mov	r3, r5
	ldr	r2, .L164+4
	mov	r0, #32
	ldr	r1, .L164+8
	blx	r8
	str	r7, [sp]
	ldr	r8, [r6, #68]
	mov	r3, r5
	ldr	r2, .L164+4
	mov	r0, #32
	ldr	r1, .L164+8
	blx	r8
	str	r7, [sp]
	ldr	r8, [r6, #68]
	mov	r3, r5
	ldr	r2, .L164+4
	mov	r0, #32
	ldr	r1, .L164+8
	blx	r8
	ldr	ip, [r4, #1280]
	str	r7, [sp]
	mov	r3, r5
	add	ip, ip, #328
	ldr	r8, [r6, #68]
	add	ip, ip, #2
	ldr	r2, .L164+4
	ldr	r1, .L164+8
	mov	r0, #32
	ldr	ip, [r4, ip, asl #2]
	bic	ip, ip, #255
	str	ip, [r4, #2484]
	blx	r8
	ldr	r2, [r4, #1288]
	mov	r3, r5
	str	r7, [sp]
	ldr	r1, .L164+8
	mov	r0, #32
	str	r2, [r4, #2488]
	ldr	r8, [r6, #68]
	ldr	r2, .L164+4
	blx	r8
	ldr	r2, [r4, #1292]
	mov	r3, r5
	str	r7, [sp]
	mov	r0, #32
	ldr	r7, [r6, #68]
	str	r2, [r4, #2492]
	ldr	r1, .L164+8
	ldr	r2, .L164+4
	blx	r7
.L140:
	ldr	r3, [r4, #20]
	ldr	r2, [r4, #68]
	add	r3, r3, #1
	mov	r3, r3, asl r2
	sub	r2, r3, #1
	cmp	r2, #2048
	movcc	r2, #512
	bcc	.L141
	sub	r2, r3, #2048
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r2, #1024
	bcs	.L162
.L141:
	ldr	r3, [r4, #184]
	tst	r3, #15
	mov	r3, r3, lsr #4
	addne	r3, r3, #1
	cmp	r5, #0
	add	r3, r3, #1
	mov	r3, r3, lsr #1
	mul	r3, r2, r3
	str	r3, [fp, #-48]
	str	r3, [r4, #2496]
	ble	.L163
	mov	r7, #1
	ldr	r9, [r6, #68]
	str	r7, [sp]
	mov	r3, r5
	ldr	r2, .L164+4
	mov	r0, #32
	ldr	r1, .L164+8
	mov	r8, #0
	blx	r9
	str	r7, [sp]
	mov	r3, r5
	ldr	r2, .L164+4
	ldr	r1, .L164+8
	mov	r0, #32
	str	r8, [r4, #2532]
	ldr	r9, [r6, #68]
	str	r8, [fp, #-48]
	blx	r9
	strh	r8, [fp, #-48]	@ movhi
	mov	r3, r5
	ldr	r2, [fp, #-48]
	mov	r0, #32
	str	r7, [sp]
	ldr	r1, .L164+8
	str	r2, [r4, #2536]
	ldr	r7, [r6, #68]
	ldr	r2, .L164+4
	blx	r7
.L145:
	ldr	r3, [r4, #188]
	mov	r2, #24
	str	r2, [r4, #2540]
	cmp	r3, #4096
	movw	r3, #30480
	movtls	r3, 1
	cmp	r5, #0
	str	r3, [fp, #-48]
	beq	.L149
	cmp	r5, #1
	beq	.L150
	cmp	r5, #0
	mov	r3, #2
	str	r3, [fp, #-48]
	ble	.L151
.L152:
	mov	r2, #1
	mov	r3, r5
	str	r2, [sp]
	mov	r0, #32
	ldr	r4, [r6, #68]
	ldr	r2, .L164+4
	ldr	r1, .L164+8
	blx	r4
.L153:
	ldr	r3, [r6, #68]
	mov	r2, #2
	ldr	r1, .L164+16
	mov	r0, #3
	blx	r3
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L150:
	ldr	r3, .L164+20
	ldr	r1, [fp, #-48]
	ldr	r0, [r3]
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	b	.L152
.L162:
	sub	r2, r3, #4096
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r2, #1536
	bcc	.L141
	sub	r3, r3, #6144
	sub	r3, r3, #1
	cmp	r3, #2048
	movcs	r2, #512
	movcc	r2, #2048
	b	.L141
.L163:
	movw	r2, #1208
	ldr	r0, .L164+24
	mul	r2, r2, r5
	mov	r1, #0
	str	r1, [fp, #-48]
	strh	r1, [fp, #-48]	@ movhi
	ldr	ip, [fp, #-48]
	ldr	lr, [r0, r2]
	str	r3, [lr, #108]
	ldr	r3, [r0, r2]
	str	r1, [r4, #2532]
	str	r1, [r3, #128]
	ldr	r3, [r0, r2]
	str	ip, [r4, #2536]
	str	ip, [r3, #132]
	b	.L145
.L161:
	movw	r7, #1208
	ldr	r9, .L164+24
	mul	r7, r7, r5
	ldr	r1, .L164+12
	mov	r0, r10
	ldr	r2, [r9, r7]
	str	r3, [r2, #12]
	ldr	r3, [r9, r7]
	ldr	r2, [r8, #48]
	bic	r2, r2, #15
	str	r2, [r4, #2440]
	str	r2, [r3, #16]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r1, [r9, r7]
	ldr	r2, [r8, #32]
	movw	r3, #3075
	movt	r3, 48
	bic	r2, r2, #15
	str	r2, [r4, #2444]
	str	r2, [r1, #20]
	ldr	r1, [r9, r7]
	ldr	r2, [r4, #1308]
	bic	r2, r2, #15
	str	r2, [r4, #2448]
	str	r2, [r1, #24]
	ldr	r2, [r9, r7]
	str	r3, [r4, #2456]
	str	r3, [r4, #2460]
	str	r3, [r4, #2464]
	str	r3, [r4, #2468]
	str	r3, [r4, #2472]
	str	r3, [r4, #2476]
	str	r3, [r4, #2480]
	str	r3, [r2, #60]
	ldr	r2, [r9, r7]
	str	r3, [r2, #64]
	ldr	r2, [r9, r7]
	str	r3, [r2, #68]
	ldr	r2, [r9, r7]
	str	r3, [r2, #72]
	ldr	r2, [r9, r7]
	str	r3, [r2, #76]
	ldr	r2, [r9, r7]
	str	r3, [r2, #80]
	ldr	r2, [r9, r7]
	str	r3, [r2, #84]
	ldr	r3, [r4, #1280]
	add	r3, r3, #328
	add	r3, r3, #2
	ldr	r3, [r4, r3, asl #2]
	bic	r3, r3, #255
	str	r3, [r4, #2484]
	ldr	r2, [r9, r7]
	str	r3, [r2, #96]
	ldr	r3, [r4, #1288]
	ldr	r2, [r9, r7]
	str	r3, [r4, #2488]
	str	r3, [r2, #100]
	ldr	r3, [r4, #1292]
	ldr	r2, [r9, r7]
	str	r3, [r4, #2492]
	str	r3, [r2, #104]
	b	.L140
.L160:
	movw	r3, #1208
	ldr	r1, .L164+24
	mul	r3, r3, r5
	ldr	r6, .L164
	ldr	r3, [r1, r3]
	str	r2, [r3, #8]
	b	.L138
.L149:
	ldr	r3, .L164+28
	ldr	r1, [fp, #-48]
	ldr	r0, [r3]
	add	r0, r0, #4
	bl	MEM_WritePhyWord
.L151:
	movw	r3, #1208
	ldr	r1, .L164+24
	mul	r5, r3, r5
	mov	r2, #2
	ldr	r3, [r1, r5]
	str	r2, [r3, #152]
	b	.L153
.L165:
	.align	2
.L164:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+2064
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	s_RegPhyBaseAddr_1
	.word	g_HwMem
	.word	s_RegPhyBaseAddr
	UNWIND(.fnend)
	.size	HEVCHAL_V300R001_CfgVdmReg, .-HEVCHAL_V300R001_CfgVdmReg
	.align	2
	.global	HEVCHAL_V300R001_StartDec
	.type	HEVCHAL_V300R001_StartDec, %function
HEVCHAL_V300R001_StartDec:
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
	UNWIND(.pad #68)
	sub	sp, sp, #68
	subs	r10, r1, #0
	mov	r7, r0
	bgt	.L226
	cmp	r10, #1
	bhi	.L227
	cmp	r0, #0
	beq	.L228
	ldr	r3, [r0, #2412]
	cmp	r3, #16
	bhi	.L229
	movw	r4, #1208
	ldr	r8, .L242
	mul	r4, r4, r10
	add	r3, r8, r4
	str	r3, [fp, #-48]
	ldr	r3, [r8, r4]
	cmp	r3, #0
	beq	.L230
.L173:
	ldr	r4, [fp, #-48]
	mov	r2, r10
	mov	r0, r7
	mvn	r9, #0
	mov	r1, r4
	bl	HEVCHAL_V300R001_CfgVdmReg
	movw	r3, #1208
	mul	r3, r3, r10
	mvn	ip, #1
	mov	r1, r4
	mov	r0, r7
	add	r2, r8, r3
	ldr	lr, [r8, r3]
	str	r9, [lr, #32]
	ldr	r3, [r8, r3]
	str	ip, [r3, #36]
	ldr	r3, [r2, #52]
	ldr	r2, [r2, #48]
	bl	HEVCHAL_V300R001_SetPicMsg
	ldr	r4, [r7, #2420]
	cmp	r4, #0
	beq	.L231
	ldr	r5, [r4, #92]
	cmp	r5, #0
	bne	.L232
	mov	r6, r4
	str	r5, [fp, #-76]
.L175:
	ldr	r1, [r7, #20]
	ldr	r3, [r7, #16]
	ldr	r2, [r7, #2416]
	mla	r3, r1, r3, r3
	cmp	r2, #0
	add	r3, r3, r1
	str	r3, [fp, #-64]
	ble	.L178
	ldr	ip, [fp, #-76]
	movw	r1, #302
	mul	r1, r1, r10
	add	r3, ip, #4
	str	r3, [fp, #-72]
	cmp	r6, #0
	mov	r0, r3
	add	r3, ip, #5
	add	r0, r1, r0
	str	r3, [fp, #-56]
	mov	ip, r3
	add	r3, r1, r3
	add	r0, r0, #8
	add	r3, r3, #8
	ldr	r9, [r8, r0, asl #2]
	ldr	r3, [r8, r3, asl #2]
	beq	.L203
	str	r1, [fp, #-60]
	mov	r0, #0
	ldr	r1, [r6, #92]
	mov	r5, r0
	str	r0, [fp, #-52]
	mov	r0, ip
	str	r10, [fp, #-80]
.L180:
	add	r5, r5, #1
	cmp	r5, r2
	bge	.L205
	ldr	r4, [r6, #1356]
	cmp	r4, #0
	bne	.L224
	b	.L183
.L185:
	add	r5, r5, #1
	cmp	r5, r2
	beq	.L200
	ldr	r4, [r4, #1356]
	cmp	r4, #0
	beq	.L183
.L224:
	ldr	ip, [r4, #92]
	cmp	ip, r1
	bls	.L185
.L182:
	cmp	r0, #209
	cmpne	r5, r2
	beq	.L233
	ldr	r0, [r4, #92]
	subs	r0, r0, #1
	bmi	.L234
	ldrb	r2, [r7, #217]	@ zero_extendqisi2
	ldr	r10, [fp, #-64]
	cmp	r2, #0
	ldr	ip, [fp, #-60]
	ldrne	r2, [r4, #568]
	moveq	r2, r0
	cmp	r10, r0
	mov	lr, r10
	add	ip, ip, r5
	movge	lr, #0
	movlt	lr, #1
	str	lr, [fp, #-68]
	ldr	lr, [fp, #-56]
	add	ip, ip, lr
	ldr	lr, [fp, #-68]
	add	ip, ip, #8
	cmp	r2, r10
	orrgt	lr, lr, #1
	cmp	lr, #0
	ldr	r10, [r8, ip, asl #2]
	bne	.L235
.L189:
	cmp	r0, r1
	str	r0, [r6, #572]
	bcc	.L236
	ldr	lr, [r7, #2416]
	sub	ip, r5, #1
	sub	lr, lr, #1
	cmp	lr, ip
	moveq	ip, #0
	streq	ip, [r6, #1356]
	str	r0, [sp, #20]
	mov	r0, r7
	str	r2, [sp, #16]
	mov	r2, r6
	str	r1, [sp, #12]
	ldr	ip, [r6, #80]
	ldr	r1, [fp, #-48]
	stmia	sp, {r9, r10, ip}
	bl	HEVCHAL_V300R001_SetSliceMsg
	cmp	r0, #0
	bne	.L237
	ldr	r3, [fp, #-52]
	cmp	r10, #0
	ldr	ip, [r6, #572]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	beq	.L238
	ldr	r2, [r7, #2416]
	cmp	r2, r5
	ble	.L239
	ldr	r1, [fp, #-60]
	cmp	r4, #0
	ldr	r0, [fp, #-56]
	ldr	lr, [fp, #-72]
	add	r3, r1, r5
	add	r0, r0, r5
	add	r3, r3, lr
	add	r1, r1, r0
	add	r3, r3, #8
	add	r1, r1, #8
	ldr	r9, [r8, r3, asl #2]
	ldr	r3, [r8, r1, asl #2]
	beq	.L179
	ldr	r1, [r4, #92]
	cmp	r1, ip
	movcs	lr, #0
	movcc	lr, #1
	cmp	r5, #0
	movle	lr, #0
	cmp	lr, #0
	bne	.L240
	mov	r6, r4
	b	.L180
.L232:
	ldrb	r3, [r7, #217]	@ zero_extendqisi2
	movw	r0, #1208
	mla	r0, r0, r10, r8
	cmp	r3, #0
	ldr	r3, [r4]
	mov	r6, #1
	str	r6, [r4]
	sub	lr, r5, #1
	ldr	r1, [r4, #16]
	mov	r2, r4
	str	r3, [fp, #-52]
	moveq	ip, lr
	ldr	r3, [r4, #4]
	ldrne	ip, [r4, #568]
	str	r1, [fp, #-68]
	str	r3, [fp, #-56]
	ldr	r3, [r4, #8]
	ldr	r1, [fp, #-48]
	str	r3, [fp, #-60]
	ldr	r3, [r4, #12]
	str	r3, [fp, #-64]
	mov	r3, #0
	str	r3, [r4, #4]
	str	r3, [r4, #8]
	str	r3, [r4, #12]
	ldr	r9, [r7, #1308]
	str	r9, [r4, #16]
	ldr	r9, [r4, #20]
	str	r3, [r4, #20]
	str	r3, [sp, #12]
	str	r3, [sp, #8]
	ldr	r3, [r0, #52]
	str	lr, [sp, #20]
	ldr	lr, [r0, #56]
	ldr	r0, [r0, #48]
	str	ip, [sp, #16]
	str	lr, [sp, #4]
	str	r0, [sp]
	mov	r0, r7
	bl	HEVCHAL_V300R001_SetSliceMsg
	cmp	r0, #0
	bne	.L241
	ldr	r3, [fp, #-52]
	str	r5, [r4, #92]
	str	r6, [fp, #-76]
	str	r3, [r4]
	ldr	r3, [fp, #-56]
	str	r9, [r4, #20]
	str	r3, [r4, #4]
	ldr	r3, [fp, #-60]
	str	r3, [r4, #8]
	ldr	r3, [fp, #-64]
	str	r3, [r4, #12]
	ldr	r3, [fp, #-68]
	str	r3, [r4, #16]
	ldr	r6, [r7, #2420]
	b	.L175
.L183:
	ldr	r3, .L242+4
	mov	r0, #1
	ldr	r2, .L242+8
	mvn	r9, #0
	ldr	r1, .L242+12
	ldr	r3, [r3, #68]
	blx	r3
.L219:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L233:
	mov	r2, r5
.L200:
	ldr	r0, [fp, #-64]
	mov	r10, #0
	mov	r5, r2
	str	r10, [r6, #1356]
	mov	r2, r0
	b	.L189
.L230:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L174
	str	r3, [r4, r8]
	b	.L173
.L205:
	mov	r4, r6
	b	.L182
.L226:
	ldr	r1, .L242+4
	mov	r0, #1
	mov	r3, r10
	str	r0, [sp]
	ldr	r2, .L242+8
	mov	r0, #0
	ldr	r4, [r1, #68]
	mvn	r9, #0
	ldr	r1, .L242+16
	blx	r4
	b	.L219
.L203:
	mov	r5, r6
.L179:
	ldr	ip, .L242+4
	mov	r3, r5
	ldr	r2, .L242+8
	mov	r0, #1
	ldr	r1, .L242+20
	mvn	r9, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L219
.L239:
	ldr	r10, [fp, #-80]
	mov	r9, r0
.L196:
	cmp	r2, #0
	ldr	r1, [fp, #-52]
	movgt	r3, #1
	movle	r3, #0
	cmp	r1, #0
	andgt	r3, r3, #1
	movle	r3, #0
	cmp	r3, #0
	beq	.L178
	ldr	r1, [fp, #-76]
	movw	r3, #302
	mla	r3, r3, r10, r1
	add	r2, r3, r2
	add	r3, r2, #12
	ldr	r0, [r8, r3, asl #2]
	bl	HEVCHAL_V300R001_CutSliceChain
	b	.L219
.L237:
	ldr	r3, .L242+4
	mov	r0, #1
	ldr	r2, .L242+8
	mvn	r9, #0
	ldr	r1, .L242+24
	ldr	r3, [r3, #68]
	blx	r3
	b	.L219
.L238:
	mov	r9, r0
	ldr	r10, [fp, #-80]
	ldr	r2, [r7, #2416]
	b	.L196
.L235:
	ldr	r1, [fp, #-64]
	mov	r3, r0
	ldr	ip, .L242+4
	mov	r0, #1
	mvn	r9, #0
	str	r1, [sp]
	ldr	r1, .L242+28
	ldr	r4, [ip, #68]
	blx	r4
	b	.L219
.L236:
	ldr	ip, .L242+4
	mov	r3, r0
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L242+32
	mvn	r9, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L219
.L240:
	ldr	lr, .L242+4
	mov	r2, r1
	mov	r3, ip
	ldr	r1, .L242+36
	mov	r0, #1
	mvn	r9, #0
	ldr	r4, [lr, #68]
	blx	r4
	b	.L219
.L234:
	ldr	ip, .L242+4
	mov	r3, r0
	ldr	r2, .L242+8
	mov	r0, #1
	ldr	r1, .L242+40
	mvn	r9, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L219
.L178:
	ldr	r3, .L242+4
	mov	r0, #1
	ldr	r1, .L242+44
	mvn	r9, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L219
.L229:
	ldr	r1, .L242+4
	mov	r0, #0
	ldr	r3, .L242+48
	mvn	r9, #0
	ldr	r2, .L242+8
	ldr	r4, [r1, #68]
	ldr	r1, .L242+52
	blx	r4
	b	.L219
.L227:
	ldr	r3, .L242+4
	mov	r0, #0
	ldr	r1, .L242+56
	mvn	r9, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L219
.L241:
	ldr	r3, .L242+4
	mov	r0, r6
	ldr	r2, .L242+8
	mvn	r9, #0
	ldr	r1, .L242+60
	ldr	r3, [r3, #68]
	blx	r3
	b	.L219
.L228:
	ldr	r1, .L242+4
	mvn	r9, #0
	ldr	r3, .L242+64
	ldr	r2, .L242+8
	ldr	r4, [r1, #68]
	ldr	r1, .L242+52
	blx	r4
	b	.L219
.L231:
	ldr	r3, .L242+4
	mov	r0, r4
	ldr	r2, .L242+8
	ldr	r1, .L242+68
	ldr	r3, [r3, #68]
	blx	r3
	b	.L219
.L174:
	ldr	r3, .L242+4
	mvn	r9, #0
	ldr	r2, .L242+8
	ldr	r1, .L242+72
	ldr	r3, [r3, #68]
	blx	r3
	b	.L219
.L243:
	.align	2
.L242:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+2092
	.word	.LC26
	.word	.LC17
	.word	.LC24
	.word	.LC30
	.word	.LC28
	.word	.LC29
	.word	.LC25
	.word	.LC27
	.word	.LC31
	.word	.LC20
	.word	.LC1
	.word	.LC18
	.word	.LC23
	.word	.LC19
	.word	.LC22
	.word	.LC21
	UNWIND(.fnend)
	.size	HEVCHAL_V300R001_StartDec, .-HEVCHAL_V300R001_StartDec
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.13489, %object
	.size	__func__.13489, 18
__func__.13489:
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
	.type	__func__.13510, %object
	.size	__func__.13510, 31
__func__.13510:
	.ascii	"HEVCHAL_V300R001_CutSliceChain\000"
	.space	1
	.type	__func__.13529, %object
	.size	__func__.13529, 19
__func__.13529:
	.ascii	"HEVC_WriteTileInfo\000"
	.space	1
	.type	__func__.13555, %object
	.size	__func__.13555, 27
__func__.13555:
	.ascii	"HEVCHAL_V300R001_SetPicMsg\000"
	.space	1
	.type	__func__.13592, %object
	.size	__func__.13592, 29
__func__.13592:
	.ascii	"HEVCHAL_V300R001_SetSliceMsg\000"
	.space	3
	.type	s_SliceTypeForPMV, %object
	.size	s_SliceTypeForPMV, 12
s_SliceTypeForPMV:
	.word	2
	.word	1
	.word	0
	.type	__func__.13622, %object
	.size	__func__.13622, 27
__func__.13622:
	.ascii	"HEVCHAL_V300R001_CfgVdmReg\000"
	.space	1
	.type	__func__.13655, %object
	.size	__func__.13655, 26
__func__.13655:
	.ascii	"HEVCHAL_V300R001_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"can not map mn virtual address!\012\000" )
	.space	3
.LC1:
	ASCII(.ascii	"%s: %s\012\000" )
.LC2:
	ASCII(.ascii	"HEVCWriteCabacTab return error.\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"can not map slice msg virtual address!\012\000" )
.LC4:
	ASCII(.ascii	"qmatrix[%d] = 0x%x\012\000" )
.LC5:
	ASCII(.ascii	"picmsg Dxx addr 0x%x = 0x%x\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"can not map slice segment info virtual address!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC7:
	ASCII(.ascii	"can not map down msg virtual address!\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"picmsg D[0] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"HEVC_WriteTileInfo return error.\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"HEVCHAL_V300R001_SetSliceMsg can not map slice msg " )
	ASCII(.ascii	"virtual address!\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"%s FATAL: i=0, valid_bitlen=0\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"slicemsg D[%d] addr 0x%x = 0x%x\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"AVM_ADDR = 0x%x\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"HEVC_VFMW_PRC_CACHE_TYPE = 0x%x\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"%s VdhId %d >= %d\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"VdhId is wrong! HEVC4HAL_V200R003_StartDec\012\000" )
.LC19:
	ASCII(.ascii	"pParam is null\012\000" )
.LC20:
	ASCII(.ascii	"FATAL: ApcSize > 16\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"%s vdm register virtual address not mapped, reset f" )
	ASCII(.ascii	"ailed!\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"%s pFirstSlice = NULL!\012\000" )
.LC23:
	ASCII(.ascii	"%s 0: set slice msg failed!\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"%s: i = %d, pSlicePara = NULL!\012\000" )
.LC25:
	ASCII(.ascii	"SliceSegmentTileAddress %d < pre_end_ctb_in_slice_t" )
	ASCII(.ascii	"ile %d\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"%s pTargetSlicePara is NULL!\012\000" )
	.space	2
.LC27:
	ASCII(.ascii	"%s end_ctb_in_slice_tile(%d) < 0\012\000" )
	.space	2
.LC28:
	ASCII(.ascii	"end_ctb_in_slice_raster(%d)/end_ctb_in_slice_tile(%" )
	ASCII(.ascii	"d) > pic_max_ctb(%d)\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"SliceSegmentTileAddress %d > end_ctb_in_slice_tile " )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"%s 1: set slice msg failed!\012\000" )
	.space	3
.LC31:
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
