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
	.file	"hevc.c"
	.text
	.align	2
	.type	HEVC_ComparePicByPocAsc, %function
HEVC_ComparePicByPocAsc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #8]
	ldr	r3, [r3, #8]
	cmp	r2, r3
	blt	.L3
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L3:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ComparePicByPocAsc, .-HEVC_ComparePicByPocAsc
	.align	2
	.type	HEVC_CheckThatAllRefPicsAreAvailable.part.8, %function
HEVC_CheckThatAllRefPicsAreAvailable.part.8:
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
	add	r7, r0, #4096
	ldr	r2, [r0, #2380]
	mov	ip, #1888
	ldr	r3, [r7, #164]
	movw	r4, #12660
	str	r1, [fp, #-64]
	ldr	r1, [r7, #1064]
	mla	ip, ip, r3, r2
	ldr	r3, [r7, #1060]
	ldr	lr, [r0, #2376]
	mov	r2, #1
	add	r3, r1, r3
	str	r3, [fp, #-60]
	mov	r5, r3
	ldr	r3, [r7, #1068]
	ldr	r1, [ip, #32]
	cmp	r5, r3
	mla	r1, r4, r1, lr
	ldr	r10, [r1, #116]
	mov	r10, r2, asl r10
	bcs	.L6
	add	r6, r5, #1312
	add	r9, r5, #5120
	add	r6, r6, #2
	add	r9, r9, #48
	ldr	r1, [r0, #2600]
	add	r3, r3, #5120
	sub	r10, r10, #1
	add	r6, r0, r6, lsl #2
	add	r9, r0, r9
	add	r3, r3, #48
	mov	r2, #0
	add	r3, r0, r3
	str	r2, [fp, #-52]
	str	r3, [fp, #-48]
	str	r2, [fp, #-56]
.L7:
	cmp	r1, #0
	beq	.L13
	add	r3, r0, #2608
	mov	r8, #0
	add	r3, r3, #12
	mov	r2, r8
	ldr	r5, [r6, #-944]
	b	.L10
.L65:
	cmp	lr, #0
	beq	.L9
	ldr	r4, [ip, #8]
	ldr	lr, [r6]
	cmp	r4, lr
	beq	.L63
.L9:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r1
	beq	.L64
.L10:
	ldr	ip, [r3]
	cmp	r5, #0
	ldr	lr, [ip, #60]
	bne	.L65
	cmp	lr, #0
	beq	.L9
	ldr	r4, [r6]
	ldr	lr, [ip, #8]
	eor	lr, lr, r4
	tst	lr, r10
	bne	.L9
.L63:
	ldrb	lr, [ip, #1]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L9
	ldr	lr, [r0, #2416]
	ldr	r4, [ip, #16]
	ldr	ip, [lr, #4]
	cmp	r4, ip
	movls	r8, #1
	bls	.L9
	ldr	ip, [lr, #644]
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	ip, #1
	movne	r8, #1
	cmp	r2, r1
	bne	.L10
.L64:
	cmp	r8, #0
	beq	.L13
.L11:
	ldr	r3, [fp, #-48]
	add	r9, r9, #1
	add	r6, r6, #4
	cmp	r9, r3
	bne	.L7
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	beq	.L15
.L14:
	add	r5, r0, #5184
	add	r9, r0, #5120
	ldr	r10, [fp, #-60]
	add	r5, r5, #4
	ldr	ip, [fp, #-56]
	add	r9, r9, #48
	mov	r8, #0
.L19:
	cmp	r1, #0
	beq	.L20
	add	r4, r0, #2608
	mov	r6, #0
	add	r4, r4, #8
	mov	r3, r6
	str	ip, [fp, #-48]
	b	.L17
.L16:
	add	r3, r3, #1
	cmp	r3, r1
	beq	.L66
.L17:
	ldr	r2, [r4, #4]!
	ldr	lr, [r2, #60]
	cmp	lr, #0
	bne	.L16
	ldr	ip, [r5]
	ldr	lr, [r7, #140]
	add	lr, lr, ip
	ldr	ip, [r2, #8]
	cmp	ip, lr
	bne	.L16
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L16
	ldr	lr, [r0, #2416]
	ldr	r2, [r2, #16]
	ldr	ip, [lr, #4]
	cmp	r2, ip
	movls	r6, #1
	bls	.L16
	ldr	r2, [lr, #644]
	add	r3, r3, #1
	cmp	r2, #1
	movne	r6, #1
	cmp	r3, r1
	bne	.L17
.L66:
	cmp	r6, #0
	ldr	ip, [fp, #-48]
	beq	.L20
.L18:
	add	r8, r8, #1
	add	r5, r5, #4
	cmp	r10, r8
	add	r9, r9, #1
	bhi	.L19
	str	ip, [fp, #-56]
.L15:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	beq	.L28
	ldr	r3, [fp, #-64]
	mov	r0, #0
	ldr	r2, [fp, #-52]
	str	r2, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L20:
	ldr	r2, [r7, #160]
	ldr	r3, [r7, #140]
	ldr	lr, [r5]
	add	r2, r0, r2, lsl #2
	add	r3, r3, lr
	ldr	r2, [r2, #228]
	cmp	r3, r2
	blt	.L18
	ldrb	r2, [r9]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [fp, #-52]
	movne	ip, #1
	movne	r2, r3
	str	r2, [fp, #-52]
	b	.L18
.L13:
	ldr	r2, [r7, #160]
	ldr	r3, [r7, #140]
	ldr	ip, [r6, #-68]
	add	r2, r0, r2, lsl #2
	add	r3, r3, ip
	ldr	r2, [r2, #228]
	cmp	r3, r2
	blt	.L11
	ldrb	r2, [r9]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [fp, #-52]
	movne	r2, r3
	ldr	r3, [fp, #-56]
	str	r2, [fp, #-52]
	movne	r3, #1
	str	r3, [fp, #-56]
	b	.L11
.L28:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L6:
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	beq	.L28
	mov	r3, #0
	ldr	r1, [r0, #2600]
	str	r3, [fp, #-52]
	str	r3, [fp, #-56]
	b	.L14
	UNWIND(.fnend)
	.size	HEVC_CheckThatAllRefPicsAreAvailable.part.8, .-HEVC_CheckThatAllRefPicsAreAvailable.part.8
	.align	2
	.type	HEVC_SetFrmRepeatCount.part.9, %function
HEVC_SetFrmRepeatCount.part.9:
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
	ldr	ip, [r0, #292]
	ldr	r2, [r0, #2596]
	ldr	r3, [r0, #288]
	add	r2, r2, ip
	add	ip, r2, #1
	cmp	r3, ip
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	r3, r3, #1
	rsb	r3, r2, r3
	cmp	r3, #1
	movhi	r3, #2
	movls	r3, #1
	strhi	r3, [r1, #16]
	strls	r3, [r1, #16]
	ldrhi	r3, [r0, #292]
	ldrls	r3, [r0, #292]
	addhi	r3, r3, #2
	addls	r3, r3, #1
	str	r3, [r0, #292]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_SetFrmRepeatCount.part.9, .-HEVC_SetFrmRepeatCount.part.9
	.align	2
	.type	HEVC_OutputFrame.isra.10, %function
HEVC_OutputFrame.isra.10:
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
	mov	r4, r0
	mov	r5, r1
	ldr	r0, [r0, #252]
	ldr	r1, [r1]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L77
	mov	r2, #1
	ldr	r1, [r5]
	ldr	r0, [r4, #252]
	bl	FSP_SetDisplay
	add	r3, r4, #5568
	ldr	r0, [r4, #252]
	add	r3, r3, #16
	str	r6, [sp]
	mov	r2, r4
	mov	r1, #16
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L78
	ldr	r3, [r4, #2416]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r6, #16]
	bcs	.L79
.L76:
	ldr	r2, [r4, #300]
	mov	r0, #0
	ldr	r3, [r4, #292]
	add	r2, r2, #1
	str	r2, [r4, #300]
	add	r3, r3, #1
	str	r3, [r4, #292]
.L73:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L79:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.part.9
	b	.L76
.L78:
	ldr	r2, .L80
	mov	r0, #1
	ldr	r1, .L80+4
	bl	dprint_vfmw
	ldr	r0, [r4, #252]
	ldr	r1, [r5]
	mov	r2, #0
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L73
.L77:
	ldr	r2, .L80
	ldr	r1, .L80+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L73
.L81:
	.align	2
.L80:
	.word	.LANCHOR0
	.word	.LC3
	.word	.LC2
	UNWIND(.fnend)
	.size	HEVC_OutputFrame.isra.10, .-HEVC_OutputFrame.isra.10
	.align	2
	.global	HEVC_Sei_ParsePts_Init
	.type	HEVC_Sei_ParsePts_Init, %function
HEVC_Sei_ParsePts_Init:
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
	ldr	r3, .L83
	mov	r4, r0
	add	r0, r0, #11072
	mov	r2, #56
	mov	r1, #0
	add	r0, r0, r2
	ldr	r3, [r3, #48]
	blx	r3
	add	r3, r4, #2912
	mov	r0, #0
	mov	r1, #0
	mov	r2, #0
	strd	r0, [r3, #32]
	strd	r0, [r3, #8]
	strd	r0, [r3, #16]
	strd	r0, [r3, #24]
	str	r2, [r4, #2900]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L84:
	.align	2
.L83:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_Sei_ParsePts_Init, .-HEVC_Sei_ParsePts_Init
	.align	2
	.global	HEVC_Sei_Get_Dpb_Output_Time
	.type	HEVC_Sei_Get_Dpb_Output_Time, %function
HEVC_Sei_Get_Dpb_Output_Time:
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
	add	r3, r0, #4096
	ldr	lr, [r0, #164]
	ldr	ip, [r3, #164]
	cmp	ip, #0
	blt	.L87
	cmp	ip, lr
	bge	.L87
	ldr	r3, [r0, #2380]
	mov	r2, #1888
	mla	ip, r2, ip, r3
	ldr	lr, [ip, #32]
	ldr	ip, [r0, #160]
	cmp	lr, #0
	blt	.L91
	cmp	lr, ip
	bge	.L91
	ldr	r2, [r0, #2376]
	movw	r4, #12660
	ldr	r3, [r1, #36]
	add	ip, r0, #8192
	mla	lr, r4, lr, r2
	str	r3, [ip, #2948]
	ldr	r2, [r1, #40]
	ldr	r3, [ip, #2940]
	str	r2, [ip, #2952]
	cmp	r3, #1
	ldr	r3, [lr, #52]
	add	r3, r3, #90
	ldrb	r6, [lr, r3, asl #2]	@ zero_extendqisi2
	beq	.L99
	ldrb	r3, [ip, #2937]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L95
	ldrb	r3, [r0, #2896]	@ zero_extendqisi2
	add	lr, r0, #2912
	cmp	r3, #0
	beq	.L96
	ldrd	r2, [lr, #16]
	mov	r8, r2
	mov	r9, r3
.L97:
	ldr	r4, [r0, #2912]
	mov	r5, #0
	adds	r2, r2, r4
	adc	r3, r3, r5
	cmp	r2, r8
	sbcs	r7, r3, r9
	strd	r2, [lr, #32]
	strd	r2, [lr, #8]
	bge	.L94
	adds	r2, r4, r8
	adc	r3, r5, r9
	strd	r2, [lr, #32]
	strd	r2, [lr, #8]
	b	.L94
.L91:
	ldr	r3, [r0, #252]
	movw	r2, #2621
	str	ip, [sp, #4]
	mov	r0, #0
	str	lr, [sp]
	ldr	r1, .L101
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L87:
	ldr	r3, [r0, #252]
	movw	r2, #2611
	str	lr, [sp, #4]
	mov	r0, #0
	str	ip, [sp]
	ldr	r1, .L101+4
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L95:
	add	lr, r0, #2912
	ldr	r4, [r0, #2912]
	ldrd	r2, [lr, #8]
	adds	r2, r2, r4
	adc	r3, r3, #0
	strd	r2, [lr, #32]
.L94:
	add	r7, r0, #11136
	strd	r2, [lr, #24]
	mov	lr, #0
	strb	lr, [ip, #2937]
	ldrd	r4, [r7, #24]
	strd	r4, [r7, #40]
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	cmp	r1, lr
	ldr	r1, [r0, #2916]
	bne	.L100
	adds	r2, r2, r1
	adc	r3, r3, #0
	subs	r2, r2, r6
	sbc	r3, r3, #0
	strd	r2, [r7, #24]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L100:
	adds	r2, r2, r1
	adc	r3, r3, #0
	movs	r3, r3, asr #1
	mov	r2, r2, rrx
	subs	r2, r2, r6
	sbc	r3, r3, #0
	strd	r2, [r7, #24]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L99:
	ldr	r2, [r0, #2900]
	add	lr, r0, #2912
	mov	r3, r2, asr #31
	strd	r2, [lr, #32]
	strd	r2, [lr, #8]
	b	.L94
.L96:
	ldrd	r2, [lr, #8]
	ldrd	r8, [lr, #16]
	b	.L97
.L102:
	.align	2
.L101:
	.word	.LC5
	.word	.LC4
	UNWIND(.fnend)
	.size	HEVC_Sei_Get_Dpb_Output_Time, .-HEVC_Sei_Get_Dpb_Output_Time
	.align	2
	.global	HEVC_Get_Last_IDR_Frame_Info
	.type	HEVC_Get_Last_IDR_Frame_Info, %function
HEVC_Get_Last_IDR_Frame_Info:
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
	sub	r3, r1, #19
	cmp	r3, #1
	bls	.L107
.L104:
	sub	r1, r1, #6
	cmp	r1, #3
	addhi	r0, r0, #2912
	ldrhid	r2, [r0, #32]
	strhid	r2, [r0, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L107:
	ldr	ip, [r0, #2416]
	mvn	r3, #0
	mvn	r2, #0
	ldrd	r4, [ip, #64]
	cmp	r5, r3
	cmpeq	r4, r2
	beq	.L105
	add	r2, r0, #11136
	movw	r3, #11152
	strd	r4, [r0, r3]
	movw	ip, #11168
	ldrd	r4, [r2, #24]
	mov	r3, r2
	strd	r4, [r0, ip]
	strd	r4, [r3, #40]
.L105:
	add	r3, r0, #8192
	mov	r2, #1
	strb	r2, [r3, #2936]
	b	.L104
	UNWIND(.fnend)
	.size	HEVC_Get_Last_IDR_Frame_Info, .-HEVC_Get_Last_IDR_Frame_Info
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.align	2
	.global	HEVC_Sei_Get_Frame_Pts
	.type	HEVC_Sei_Get_Frame_Pts, %function
HEVC_Sei_Get_Frame_Pts:
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
	add	r2, r0, #8192
	add	r3, r0, #11136
	mov	r4, r0
	movw	r0, #11152
	ldr	r5, [r2, #2948]
	ldr	r10, [r2, #2952]
	movw	r1, #11168
	ldrd	r6, [r3, #24]
	cmp	r5, #0
	ldrd	r2, [r4, r0]
	strd	r2, [fp, #-52]
	ldrd	r2, [r4, r1]
	strd	r2, [fp, #-60]
	beq	.L111
	mov	r9, r5
	mov	r0, r10
	b	.L110
.L112:
	mov	r9, r1
.L110:
	mov	r1, r9
	bl	__aeabi_uidivmod
	mov	r0, r9
	cmp	r1, #0
	bne	.L112
.L109:
	ldrd	r2, [fp, #-60]
	mov	r1, r9
	mov	r0, r5
	mov	r8, #1000
	subs	r2, r6, r2
	add	r4, r4, #4160
	mul	r6, r8, r2
	bl	__aeabi_uidiv
	mov	r1, r9
	mul	r6, r0, r6
	mov	r0, r10
	bl	__aeabi_uidiv
	mov	r1, r0
	mov	r0, r6
	bl	__aeabi_uidiv
	ldrd	r2, [fp, #-52]
	adds	r2, r2, r0
	adc	r3, r3, #0
	mov	r0, r2
	mov	r1, r3
	strd	r0, [r4, #8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L111:
	mov	r9, r10
	b	.L109
	UNWIND(.fnend)
	.size	HEVC_Sei_Get_Frame_Pts, .-HEVC_Sei_Get_Frame_Pts
	.align	2
	.global	HEVC_InitSigLastScan
	.type	HEVC_InitSigLastScan, %function
HEVC_InitSigLastScan:
	UNWIND(.fnstart)
	@ args = 16, pretend = 0, frame = 24
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
	ldr	r4, [fp, #8]
	str	r0, [fp, #-48]
	cmp	r4, #15
	ldr	r6, [fp, #4]
	bgt	.L114
	cmp	r4, #8
	mul	r9, r4, r4
	beq	.L147
	cmp	r9, #0
	movne	r10, r6
	beq	.L114
.L116:
	mov	r5, #0
	rsb	r7, r4, #1
	mov	r8, r5
.L122:
	cmp	r4, r8
	bgt	.L134
	rsb	lr, r4, r8
	sub	r2, r4, #1
	add	lr, lr, #1
.L123:
	cmp	r2, #0
	cmpge	r4, lr
	ble	.L120
	mla	r0, r2, r4, lr
	add	ip, r10, r5, lsl #2
	mov	r1, r5
.L121:
	add	r1, r1, #1
	sub	r2, r2, #1
	rsb	r3, r5, r1
	str	r0, [ip], #4
	add	r3, r3, lr
	add	r0, r0, r7
	cmp	r2, #0
	cmpge	r4, r3
	bgt	.L121
	mov	r5, r1
.L120:
	cmp	r9, r5
	add	r8, r8, #1
	bhi	.L122
.L114:
	cmp	r4, #4
	ble	.L113
	mov	r3, r4, asr #2
	ldr	r1, [fp, #-48]
	str	r3, [fp, #-60]
	mov	r2, r3
	add	r3, r1, r3
	mul	r2, r2, r2
	mov	r0, r2
	str	r2, [fp, #-56]
	cmp	r0, #0
	ldrsb	r2, [r3, #12]
	add	r2, r2, #1
	beq	.L113
	add	r3, r1, #352
.L118:
	rsb	r5, r4, #1
	mov	r2, r2, asl #14
	str	r3, [fp, #-52]
	mov	r3, #0
	str	r2, [fp, #-64]
	str	r3, [fp, #-48]
.L132:
	ldr	r3, .L148
	cmp	r4, #32
	ldr	r1, [fp, #-48]
	mov	r8, #0
	ldr	r2, [fp, #-64]
	ldr	r3, [r3]
	add	r2, r2, r1
	ldr	r9, [fp, #-60]
	ldr	r7, [r3, r2, asl #2]
	ldreq	r3, [fp, #-52]
	mov	r1, r9
	ldreq	r7, [r3]
	mov	r0, r7
	bl	__aeabi_uidiv
	ldr	ip, [fp, #-48]
	mov	r3, r8
	mov	r2, r8
	mov	lr, r8
	mov	r10, ip, asl #4
	mla	r1, r4, r0, r7
	mls	r1, r9, r0, r1
	mov	r9, r1, asl #2
.L126:
	cmp	lr, #3
	mvn	r1, r2
	mov	r1, r1, lsr #31
	movgt	r1, #0
	cmp	r1, #0
	beq	.L127
	mla	r1, r2, r4, lr
	add	r0, r3, r10
	rsb	lr, r3, lr
	add	r0, r6, r0, lsl #2
	add	r1, r1, r9
.L128:
	add	r3, r3, #1
	sub	r2, r2, #1
	add	r7, lr, r3
	str	r1, [r0], #4
	cmp	r7, #3
	mvn	ip, r2
	mov	ip, ip, lsr #31
	add	r1, r1, r5
	movgt	ip, #0
	cmp	ip, #0
	bne	.L128
.L127:
	cmp	r3, #15
	add	r8, r8, #1
	bhi	.L129
	cmp	r8, #3
	movle	r2, r8
	movle	lr, #0
	subgt	lr, r8, #3
	movgt	r2, #3
	b	.L126
.L129:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r2, r2, #4
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-56]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L132
.L113:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L134:
	mov	r2, r8
	mov	lr, #0
	b	.L123
.L147:
	add	r3, r0, #352
	cmp	r9, #0
	mov	r10, r3
	bne	.L116
	ldr	r2, [fp, #-48]
	mov	r1, #2
	str	r1, [fp, #-60]
	mov	r1, #4
	str	r1, [fp, #-56]
	ldrsb	r2, [r2, #14]
	add	r2, r2, #1
	b	.L118
.L149:
	.align	2
.L148:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	HEVC_InitSigLastScan, .-HEVC_InitSigLastScan
	.align	2
	.global	HEVC_InitScalingOrderTable
	.type	HEVC_InitScalingOrderTable, %function
HEVC_InitScalingOrderTable:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	add	r3, r0, #11
	add	r1, r0, #140
	mov	r6, r0
	mvn	r2, #0
.L151:
	strb	r2, [r3, #1]!
	cmp	r3, r1
	bne	.L151
	ldr	r7, .L155
	mov	r2, #0
	mov	r3, #2
	mov	r4, r2
	mov	r5, r3
	strb	r2, [r6, #16]
	strb	r3, [r6, #28]
	mov	r2, #1
	mov	r3, #3
	strb	r2, [r6, #20]
	strb	r3, [r6, #44]
	mov	r3, #4
	strb	r3, [r6, #76]
.L152:
	ldr	r1, [r7]
	mov	r3, #0
	str	r4, [sp, #12]
	mov	r2, r3
	add	r1, r1, r4, lsl #16
	str	r5, [sp, #8]
	str	r5, [sp, #4]
	add	r4, r4, #1
	str	r1, [sp]
	mov	r0, r6
	mov	r1, r3
	mov	r5, r5, asl #1
	bl	HEVC_InitSigLastScan
	cmp	r4, #7
	bne	.L152
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L156:
	.align	2
.L155:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	HEVC_InitScalingOrderTable, .-HEVC_InitScalingOrderTable
	.global	__aeabi_idiv
	.align	2
	.global	HEVC_GetDar
	.type	HEVC_GetDar, %function
HEVC_GetDar:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	mov	ip, r1
	mov	r5, r3
	ble	.L170
	subs	lr, r0, #255
	movne	lr, #1
	cmp	r0, #16
	movle	r4, #0
	andgt	r4, lr, #1
	cmp	r4, #0
	bne	.L170
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r1, #1
	movne	r1, #0
	cmp	r0, #255
	movne	r1, #0
	andeq	r1, r1, #1
	cmp	r1, #0
	bne	.L158
	cmp	r0, #1
	beq	.L185
	cmp	lr, #0
	ldrne	r3, .L187
	addne	r0, r3, r0, lsl #3
	ldrne	r2, [r0, #24]
	ldrne	ip, [r0, #20]
	mov	r1, r2
	mov	r0, ip, asl #10
	bl	__aeabi_idiv
	ldr	r1, [fp, #4]
	mov	r4, r0
	mov	r0, r5, asl #10
	bl	__aeabi_idiv
	movw	r3, #2405
	movw	r2, #2262
	mul	r0, r0, r4
	add	r4, r0, #1020
	cmp	r0, #0
	add	r4, r4, #3
	movlt	r0, r4
	mov	r0, r0, asr #10
	cmp	r0, r3
	rsble	r3, r0, #2400
	subgt	r3, r0, #2400
	addle	r3, r3, #6
	subgt	r3, r3, #6
	cmp	r0, r2
	bgt	.L163
	rsb	r2, r0, #2256
	add	r2, r2, #7
	cmp	r3, r2
	blt	.L178
.L164:
	movw	r3, #1819
	cmp	r0, r3
	bgt	.L165
	rsb	r3, r0, #1808
	add	r3, r3, #12
	cmp	r2, r3
	bge	.L166
.L180:
	mov	r4, #3
	b	.L158
.L170:
	mov	r4, #0
.L158:
	mov	r2, r4
	ldr	r1, .L187+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L163:
	sub	r2, r0, #2256
	sub	r2, r2, #7
	cmp	r3, r2
	bge	.L164
.L178:
	mov	r4, #4
	b	.L158
.L185:
	ldr	r2, [fp, #4]
	movw	r3, #4320
	cmp	r5, #7680
	cmpeq	r2, r3
	bne	.L186
.L175:
	mov	r4, #2
	b	.L158
.L165:
	sub	r3, r0, #1808
	sub	r3, r3, #12
	cmp	r2, r3
	blt	.L180
.L166:
	movw	r2, #1364
	cmp	r0, r2
	rsble	r4, r0, #1360
	subgt	r4, r0, #1360
	addle	r4, r4, #5
	subgt	r4, r4, #5
	cmp	r3, r4
	movlt	r4, #2
	movge	r4, #1
	b	.L158
.L186:
	cmp	r5, #3840
	cmpeq	r2, #2160
	beq	.L175
	sub	r3, r2, #1072
	sub	r3, r3, #8
	bics	r3, r3, #8
	moveq	r3, #1
	movne	r3, #0
	cmp	r5, #1920
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r3, #0
	bne	.L175
	cmp	r5, #1280
	cmpeq	r2, #720
	beq	.L175
	cmp	r5, #640
	cmpeq	r2, #480
	moveq	r4, #1
	movne	r4, #5
	b	.L158
.L188:
	.align	2
.L187:
	.word	.LANCHOR0
	.word	.LC6
	UNWIND(.fnend)
	.size	HEVC_GetDar, .-HEVC_GetDar
	.align	2
	.global	HEVC_PrintNaluArraySlot
	.type	HEVC_PrintNaluArraySlot, %function
HEVC_PrintNaluArraySlot:
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
	ldr	r1, .L195
	mov	r6, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #168]
	cmn	r3, #1
	movne	r5, #0
	movwne	r7, #52429
	movne	r4, r5
	movtne	r7, 52428
	bne	.L192
	b	.L193
.L191:
	ldr	r3, [r6, #168]
	add	r3, r3, #1
	cmp	r3, r4
	bls	.L193
.L192:
	ldr	r3, [r6, #2412]
	mov	r2, r4
	ldr	r1, .L195+4
	mov	r0, #1
	add	r3, r3, r5
	add	r5, r5, #96
	ldr	ip, [r3, #32]
	str	ip, [sp]
	bl	dprint_vfmw
	umull	r2, r3, r4, r7
	mov	r2, r3, lsr #3
	mov	r3, r2, asl #3
	add	r3, r3, r2, lsl #1
	cmp	r4, r3
	add	r4, r4, #1
	bne	.L191
	ldr	r1, .L195+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #168]
	add	r3, r3, #1
	cmp	r3, r4
	bhi	.L192
.L193:
	ldr	r1, .L195+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, .L195+12
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L196:
	.align	2
.L195:
	.word	.LC7
	.word	.LC10
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	HEVC_PrintNaluArraySlot, .-HEVC_PrintNaluArraySlot
	.align	2
	.global	HEVC_PrintCurrSlicelistX
	.type	HEVC_PrintCurrSlicelistX, %function
HEVC_PrintCurrSlicelistX:
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
	add	r6, r0, #4096
	mov	r7, r0
	ldr	r1, .L218
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #196]
	ldr	r1, .L218+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #196]
	cmp	r3, #0
	addne	r5, r7, #2416
	movne	r4, #0
	addne	r5, r5, #8
	beq	.L205
.L204:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L218+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	ldr	r3, [r5]
	add	r4, r4, r0
	ldr	r1, .L218+12
	cmp	r3, #0
	beq	.L202
	ldr	r2, [r3, #16]
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L202
	ldr	r1, [r3, #28]
	ldr	r0, [r7, #252]
	bl	FSP_GetLogicFs
	ldr	r1, .L218+16
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
.L202:
	ldr	r1, .L218+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #196]
	cmp	r3, r4
	bhi	.L204
.L205:
	ldr	r2, [r6, #200]
	mov	r0, #1
	ldr	r1, .L218+24
	bl	dprint_vfmw
	ldr	r3, [r6, #200]
	cmp	r3, #0
	addne	r5, r7, #2480
	movne	r4, #0
	addne	r5, r5, #12
	beq	.L200
.L209:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L218+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	ldr	r3, [r5]
	add	r4, r4, r0
	ldr	r1, .L218+12
	cmp	r3, #0
	beq	.L207
	ldr	r2, [r3, #16]
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L207
	ldr	r1, [r3, #28]
	ldr	r0, [r7, #252]
	bl	FSP_GetLogicFs
	ldr	r1, .L218+16
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
.L207:
	ldr	r1, .L218+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #200]
	cmp	r3, r4
	bhi	.L209
.L200:
	ldr	r1, .L218+32
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L219:
	.align	2
.L218:
	.word	.LC11
	.word	.LC12
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC8
	.word	.LC13
	.word	.LC18
	.word	.LC17
	UNWIND(.fnend)
	.size	HEVC_PrintCurrSlicelistX, .-HEVC_PrintCurrSlicelistX
	.align	2
	.global	HEVC_PrintFrameStoreState
	.type	HEVC_PrintFrameStoreState, %function
HEVC_PrintFrameStoreState:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r1, .L227
	mov	r10, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #180]
	cmp	r3, #0
	addne	r8, r10, #12736
	movne	r9, #0
	addne	r8, r8, #8
	beq	.L224
.L223:
	ldrb	ip, [r8, #2]	@ zero_extendqisi2
	mov	r3, r8
	mov	r2, r9
	ldr	r1, .L227+4
	mov	r0, #1
	add	r5, r8, #616
	str	ip, [sp, #8]
	mov	r4, #0
	ldrb	ip, [r8, #1]	@ zero_extendqisi2
	str	ip, [sp, #4]
	ldr	ip, [r8, #48]
	str	ip, [sp]
	bl	dprint_vfmw
.L222:
	ldrd	r6, [r5, #8]!
	mov	r2, r4
	ldr	r1, .L227+8
	add	r4, r4, #1
	mov	r0, #1
	strd	r6, [sp]
	bl	dprint_vfmw
	cmp	r4, #4
	bne	.L222
	ldr	r1, .L227+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #180]
	add	r9, r9, #1
	add	r8, r8, #720
	cmp	r3, r9
	bhi	.L223
.L224:
	ldr	r1, .L227+16
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L228:
	.align	2
.L227:
	.word	.LC19
	.word	.LC21
	.word	.LC22
	.word	.LC8
	.word	.LC20
	UNWIND(.fnend)
	.size	HEVC_PrintFrameStoreState, .-HEVC_PrintFrameStoreState
	.align	2
	.global	HEVC_PrintAPCState
	.type	HEVC_PrintAPCState, %function
HEVC_PrintAPCState:
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
	ldr	r1, .L232
	mov	r5, r0
	mov	r0, #1
	bl	dprint_vfmw
	add	ip, r5, #12288
	mov	r2, #0
	ldr	r1, .L232+4
	ldr	r3, [ip, #260]
	mov	r0, #1
	ldr	ip, [ip, #256]
	add	r7, r5, #12544
	add	r6, r5, #12608
	add	r5, r5, #12672
	add	r7, r7, #4
	add	r6, r6, #4
	str	ip, [sp]
	add	r5, r5, #4
	bl	dprint_vfmw
	mov	r4, #0
.L230:
	ldr	lr, [r5, #4]!
	mov	r2, r4
	ldr	ip, [r6, #4]!
	add	r4, r4, #1
	ldr	r3, [r7, #4]!
	mov	r0, #1
	ldr	r1, .L232+8
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	cmp	r4, #16
	bne	.L230
	ldr	r1, .L232+12
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L233:
	.align	2
.L232:
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC26
	UNWIND(.fnend)
	.size	HEVC_PrintAPCState, .-HEVC_PrintAPCState
	.align	2
	.global	HEVC_PrintDPBState
	.type	HEVC_PrintDPBState, %function
HEVC_PrintDPBState:
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
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	r1, .L250
	mov	r9, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r9, #2612]
	ldr	lr, [r9, #2608]
	mov	r0, #1
	ldr	ip, [r9, #2616]
	ldr	r3, [r9, #2600]
	ldr	r2, [r9, #2596]
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L250+4
	bl	dprint_vfmw
	ldr	r3, [r9, #2600]
	cmp	r3, #0
	addne	r4, r9, #2608
	movne	r5, #0
	addne	r4, r4, #8
	beq	.L239
.L238:
	ldr	r3, [r4, #4]!
	ldr	r0, [r9, #252]
	ldr	r2, [r3, #32]
	ldrb	ip, [r3]	@ zero_extendqisi2
	ldr	lr, [r3, #48]
	ldrb	r6, [r3, #1]	@ zero_extendqisi2
	ldrb	r7, [r3, #2]	@ zero_extendqisi2
	ldr	r1, [r3, #28]
	str	r2, [fp, #-48]
	str	ip, [fp, #-52]
	str	lr, [fp, #-56]
	ldr	r8, [r3, #8]
	ldr	r10, [r3, #60]
	str	r6, [fp, #-60]
	str	r7, [fp, #-64]
	bl	FSP_GetLogicFs
	ldr	r3, [r4]
	ldr	r1, [r3, #28]
	mov	r6, r0
	ldr	r0, [r9, #252]
	bl	FSP_GetRef
	ldr	r3, [r4]
	ldr	r1, [r3, #28]
	mov	r7, r0
	ldr	r0, [r9, #252]
	bl	FSP_GetDisplay
	ldr	r1, [r4]
	ldr	lr, [fp, #-56]
	mov	r2, r5
	add	r5, r5, #1
	ldr	ip, [r1, #228]
	mov	r3, r1
	str	ip, [sp, #44]
	ldr	r1, [r1, #28]
	ldr	ip, [fp, #-52]
	str	r10, [sp, #24]
	str	r8, [sp, #20]
	str	r1, [sp, #40]
	ldr	r10, [fp, #-64]
	ldr	r1, [fp, #-48]
	ldr	r8, [fp, #-60]
	str	r10, [sp, #16]
	str	r1, [sp]
	str	r8, [sp, #12]
	str	lr, [sp, #8]
	str	ip, [sp, #4]
	str	r7, [sp, #32]
	str	r6, [sp, #28]
	ldr	r1, .L250+8
	str	r0, [sp, #36]
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #2600]
	cmp	r3, r5
	bhi	.L238
.L239:
	ldr	r1, .L250+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #2600]
	cmp	r3, #0
	addne	r5, r9, #2608
	movne	r6, #0
	addne	r5, r5, #8
	bne	.L246
	b	.L237
.L249:
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L250+16
	mov	r0, #1
	bl	dprint_vfmw
	ldrsb	r2, [r4]
	ldr	r1, .L250+20
	mov	r0, #1
	bl	dprint_vfmw
	ldrsb	r2, [r4, #1]
	ldr	r1, .L250+24
	mov	r0, #1
	bl	dprint_vfmw
.L241:
	cmp	r8, #0
	mov	r2, r8
	ldr	r1, .L250+28
	mov	r0, #1
	beq	.L242
	bl	dprint_vfmw
	ldr	r2, [r8, #72]
	ldr	r1, .L250+32
	mov	r0, #1
	bl	dprint_vfmw
.L243:
	cmp	r7, #0
	mov	r2, r7
	ldr	r1, .L250+36
	mov	r0, #1
	beq	.L244
	bl	dprint_vfmw
	ldr	r2, [r7, #72]
	ldr	r1, .L250+40
	mov	r0, #1
	bl	dprint_vfmw
.L245:
	ldr	r1, .L250+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #2600]
	add	r6, r6, #1
	cmp	r3, r6
	bls	.L237
.L246:
	ldr	r3, [r5, #4]!
	ldr	r0, [r9, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	ldr	r3, [r5]
	ldr	r1, [r3, #28]
	mov	r4, r0
	ldr	r0, [r9, #252]
	bl	FSP_GetDecPhyFs
	ldr	r3, [r5]
	ldr	r1, [r3, #28]
	mov	r8, r0
	ldr	r0, [r9, #252]
	bl	FSP_GetDispPhyFs
	mov	r2, r6
	ldr	r1, .L250+44
	mov	r7, r0
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r4, #0
	mov	r2, r4
	ldr	r1, .L250+48
	mov	r0, #1
	bne	.L249
	ldr	r1, .L250+52
	mov	r0, #1
	bl	dprint_vfmw
	b	.L241
.L244:
	ldr	r1, .L250+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L245
.L242:
	ldr	r1, .L250+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L243
.L237:
	ldr	r1, .L250+64
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L251:
	.align	2
.L250:
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC8
	.word	.LC33
	.word	.LC34
	.word	.LC35
	.word	.LC37
	.word	.LC38
	.word	.LC40
	.word	.LC41
	.word	.LC31
	.word	.LC32
	.word	.LC36
	.word	.LC42
	.word	.LC39
	.word	.LC30
	UNWIND(.fnend)
	.size	HEVC_PrintDPBState, .-HEVC_PrintDPBState
	.align	2
	.global	HEVC_IsSliceUnit
	.type	HEVC_IsSliceUnit, %function
HEVC_IsSliceUnit:
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
	cmp	r0, #9
	bls	.L254
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L254:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsSliceUnit, .-HEVC_IsSliceUnit
	.align	2
	.global	HEVC_IsIUnit
	.type	HEVC_IsIUnit, %function
HEVC_IsIUnit:
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
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsIUnit, .-HEVC_IsIUnit
	.align	2
	.global	HEVC_IsNonRefPic
	.type	HEVC_IsNonRefPic, %function
HEVC_IsNonRefPic:
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
	bics	r0, r0, #6
	subne	r0, r0, #8
	clzne	r0, r0
	movne	r0, r0, lsr #5
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsNonRefPic, .-HEVC_IsNonRefPic
	.align	2
	.global	HEVC_IsFlushUnit
	.type	HEVC_IsFlushUnit, %function
HEVC_IsFlushUnit:
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
	sub	r0, r0, #16
	cmp	r0, #4
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsFlushUnit, .-HEVC_IsFlushUnit
	.align	2
	.global	HEVC_IsPVRFlushPic
	.type	HEVC_IsPVRFlushPic, %function
HEVC_IsPVRFlushPic:
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
	ldr	r3, [r0, #3536]
	cmp	r3, #0
	bne	.L262
	ldr	r2, [r0, #2416]
	ldr	r1, [r2, #660]
	cmp	r1, #1
	beq	.L266
.L264:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L262:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L266:
	ldr	r0, [r2, #656]
	cmp	r0, #0
	bne	.L264
	ldr	r3, [r2, #664]
	cmp	r3, #0
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, [r2, #620]
	add	r3, r3, #1024
	cmp	r3, #2048
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsPVRFlushPic, .-HEVC_IsPVRFlushPic
	.align	2
	.global	HEVC_IsEosNal
	.type	HEVC_IsEosNal, %function
HEVC_IsEosNal:
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
	mov	r1, #32
	mov	r4, r0
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	ldr	r0, [r4, #2368]
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r5, r3
	moveq	r0, #1
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsEosNal, .-HEVC_IsEosNal
	.align	2
	.global	HEVC_CalcTileInfo
	.type	HEVC_CalcTileInfo, %function
HEVC_CalcTileInfo:
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
	mov	r7, r1
	ldr	r1, [r0, #2404]
	mov	r5, r2
	ldr	r2, [r0, #2400]
	mov	r4, r0
	str	r3, [fp, #-48]
	ldr	r6, [r1, #68]
	ldr	r2, [r2, #128]
	sub	r3, r6, #1
	ldr	r8, [r1, #72]
	cmp	r3, #9
	str	r2, [fp, #-52]
	bhi	.L296
	sub	r3, r8, #1
	cmp	r3, #10
	bhi	.L297
	ldr	r9, .L298
	mov	r2, #512
	mov	r1, #0
	mov	r0, r7
	ldr	r3, [r9, #48]
	blx	r3
	ldr	r3, [r9, #48]
	mov	r2, #80
	mov	r1, #0
	mov	r0, r5
	blx	r3
	ldr	r3, [r9, #48]
	mov	r2, #88
	mov	r1, #0
	ldr	r0, [fp, #-48]
	blx	r3
	cmp	r6, #0
	ble	.L277
	ldr	r3, [fp, #-52]
	mov	ip, #0
	mov	lr, ip
	mov	r9, r5
	sub	r10, r3, #4
.L276:
	str	ip, [r5, lr, asl #3]
	mov	r3, ip, asl r10
	ldr	r2, [r4, #2404]
	add	r2, r2, lr, lsl #1
	ldrsh	r2, [r2, #172]
	add	ip, r2, ip
	sub	r2, ip, #1
	str	r2, [r9, #4]
	mov	r1, ip, asl r10
	cmp	r3, r1
	bge	.L282
	cmp	r3, #255
	bhi	.L278
	uxtb	r0, lr
	add	r2, r7, r3
	b	.L280
.L281:
	cmp	r3, #256
	beq	.L278
.L280:
	add	r3, r3, #1
	strb	r0, [r2], #1
	cmp	r3, r1
	bne	.L281
.L282:
	add	lr, lr, #1
	add	r9, r9, #8
	cmp	lr, r6
	bne	.L276
.L277:
	cmp	r8, #0
	ble	.L274
	ldr	r3, [fp, #-52]
	mov	ip, #0
	ldr	r9, [fp, #-48]
	mov	lr, ip
	sub	r5, r3, #4
	mov	r6, r9
.L284:
	str	ip, [r9, lr, asl #3]
	mov	r3, ip, asl r5
	ldr	r2, [r4, #2404]
	add	r2, r2, lr, lsl #1
	ldrsh	r2, [r2, #212]
	add	ip, r2, ip
	sub	r2, ip, #1
	str	r2, [r6, #4]
	mov	r1, ip, asl r5
	cmp	r3, r1
	bge	.L289
	cmp	r3, #255
	bhi	.L285
	add	r2, r3, #255
	uxtb	r0, lr
	add	r2, r7, r2
	b	.L287
.L288:
	cmp	r3, #256
	beq	.L285
.L287:
	add	r3, r3, #1
	strb	r0, [r2, #1]!
	cmp	r3, r1
	bne	.L288
.L289:
	add	lr, lr, #1
	add	r6, r6, #8
	cmp	lr, r8
	bne	.L284
.L274:
	mov	r0, #0
	b	.L270
.L278:
	ldr	r2, .L298+4
	mov	r0, #1
	ldr	r1, .L298+8
	bl	dprint_vfmw
	mvn	r0, #0
.L270:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L285:
	ldr	r2, .L298+4
	mov	r0, #1
	ldr	r1, .L298+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L270
.L297:
	mov	r1, #11
	mov	r3, r8
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L298+4
	ldr	r1, .L298+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L270
.L296:
	mov	r1, #10
	mov	r3, r6
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L298+4
	ldr	r1, .L298+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L270
.L299:
	.align	2
.L298:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+156
	.word	.LC45
	.word	.LC46
	.word	.LC44
	.word	.LC43
	UNWIND(.fnend)
	.size	HEVC_CalcTileInfo, .-HEVC_CalcTileInfo
	.align	2
	.global	HEVC_Sei_More_Data_In_Payload
	.type	HEVC_Sei_More_Data_In_Payload, %function
HEVC_Sei_More_Data_In_Payload:
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
	ldr	r2, [r0, #2368]
	mov	r5, r1
	ldr	r3, [r2, #24]
	mov	r0, r2
	ldr	r4, [r2, #28]
	rsb	r4, r4, r3
	bl	BsIsByteAligned
	cmp	r4, r5, asl #3
	movne	r3, #1
	moveq	r3, #0
	cmp	r0, #0
	moveq	r0, #0
	andne	r0, r3, #1
	eor	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_More_Data_In_Payload, .-HEVC_Sei_More_Data_In_Payload
	.align	2
	.global	HEVC_Sei_Payload_Extension_Present
	.type	HEVC_Sei_Payload_Extension_Present, %function
HEVC_Sei_Payload_Extension_Present:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	ldr	r3, .L308
	mov	r5, r1
	mov	r2, #32
	ldr	r1, [r0, #2368]
	sub	r0, fp, #52
	ldr	r3, [r3, #52]
	mov	r5, r5, asl #3
	blx	r3
	ldr	r3, [fp, #-28]
	ldr	r2, [fp, #-24]
	rsb	r3, r2, r3
	cmp	r3, r5
	movcs	r0, #0
	bcc	.L307
.L302:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L307:
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsShow
	cmp	r0, #0
	moveq	r0, #1
	beq	.L302
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
	b	.L303
.L304:
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
.L303:
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsShow
	cmp	r4, r5
	mov	r1, #1
	movcs	r3, #0
	movcc	r3, #1
	cmp	r0, #0
	movne	r2, #0
	andeq	r2, r3, #1
	sub	r0, fp, #52
	cmp	r2, #0
	bne	.L304
	mov	r0, r3
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L309:
	.align	2
.L308:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_Sei_Payload_Extension_Present, .-HEVC_Sei_Payload_Extension_Present
	.align	2
	.global	HEVC_Sei_Decoded_Picture_Hash
	.type	HEVC_Sei_Decoded_Picture_Hash, %function
HEVC_Sei_Decoded_Picture_Hash:
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
	mov	r5, r0
	beq	.L318
	mov	r1, #8
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r6, #3
	mov	r7, r0
.L317:
	cmp	r7, #0
	bne	.L312
	mov	r4, #16
.L313:
	mov	r1, #8
	ldr	r0, [r5, #2368]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L313
.L314:
	subs	r6, r6, #1
	bne	.L317
.L322:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L312:
	cmp	r7, #1
	beq	.L321
	cmp	r7, #2
	bne	.L314
	mov	r1, #32
	ldr	r0, [r5, #2368]
	bl	BsGet
	subs	r6, r6, #1
	bne	.L317
	b	.L322
.L321:
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	subs	r6, r6, #1
	bne	.L317
	b	.L322
.L318:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Decoded_Picture_Hash, .-HEVC_Sei_Decoded_Picture_Hash
	.align	2
	.global	HEVC_Sei_Region_Refresh_Info
	.type	HEVC_Sei_Region_Refresh_Info, %function
HEVC_Sei_Region_Refresh_Info:
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
	moveq	r4, #1
	movne	r4, #0
	beq	.L325
	mov	r1, #1
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L325:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Region_Refresh_Info, .-HEVC_Sei_Region_Refresh_Info
	.align	2
	.global	HEVC_Sei_Mastering_Display_Colour_Volume
	.type	HEVC_Sei_Mastering_Display_Colour_Volume, %function
HEVC_Sei_Mastering_Display_Colour_Volume:
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
	mov	r5, r0
	mov	r6, r1
	beq	.L329
	add	r7, r1, #12
	mov	r4, r1
	mov	r3, #1
	strb	r3, [r1]
.L328:
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #4]!
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r4, r7
	str	r0, [r4, #12]
	bne	.L328
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #28]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #32]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #36]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r3, #0
	str	r0, [r6, #40]
.L327:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L329:
	mvn	r3, #0
	b	.L327
	UNWIND(.fnend)
	.size	HEVC_Sei_Mastering_Display_Colour_Volume, .-HEVC_Sei_Mastering_Display_Colour_Volume
	.align	2
	.global	HEVC_Sei_Content_Light_Level_Information
	.type	HEVC_Sei_Content_Light_Level_Information, %function
HEVC_Sei_Content_Light_Level_Information:
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
	moveq	r4, #1
	movne	r4, #0
	beq	.L333
	mov	r3, #1
	mov	r1, #16
	strb	r3, [r5]
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r1, #16
	strh	r0, [r5, #2]	@ movhi
	ldr	r0, [r6, #2368]
	bl	BsGet
	mov	r3, r4
	strh	r0, [r5, #4]	@ movhi
.L332:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L333:
	mvn	r3, #0
	b	.L332
	UNWIND(.fnend)
	.size	HEVC_Sei_Content_Light_Level_Information, .-HEVC_Sei_Content_Light_Level_Information
	.align	2
	.global	HEVC_Sei_HLGHDR_Comapitibility_Info
	.type	HEVC_Sei_HLGHDR_Comapitibility_Info, %function
HEVC_Sei_HLGHDR_Comapitibility_Info:
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
	mov	r5, r1
	moveq	r4, #1
	movne	r4, #0
	beq	.L336
	ldr	r0, [r0, #2368]
	mov	r1, #8
	bl	BsGet
	mov	r3, r4
	strb	r0, [r5]
.L335:
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L336:
	mvn	r3, #0
	b	.L335
	UNWIND(.fnend)
	.size	HEVC_Sei_HLGHDR_Comapitibility_Info, .-HEVC_Sei_HLGHDR_Comapitibility_Info
	.align	2
	.global	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.type	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, %function
HEVC_Sei_Temporal_Sub_Layer_Zero_Index:
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
	mov	r5, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L339
	mov	r1, #1
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldr	r0, [r5, #2368]
	bl	BsToNextByte
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L339:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, .-HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.align	2
	.global	HEVC_Sei_Display_Orientation
	.type	HEVC_Sei_Display_Orientation, %function
HEVC_Sei_Display_Orientation:
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
	mov	r4, r0
	beq	.L343
	mov	r1, #1
	ldr	r0, [r0, #2368]
	bl	BsGet
	tst	r0, #255
	beq	.L344
.L342:
	ldr	r0, [r4, #2368]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L344:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L342
.L343:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Display_Orientation, .-HEVC_Sei_Display_Orientation
	.align	2
	.global	HEVC_Sei_TSI
	.type	HEVC_Sei_TSI, %function
HEVC_Sei_TSI:
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
	moveq	r4, #1
	movne	r4, #0
	beq	.L347
	mov	r1, #4
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #1]
	ldr	r0, [r6, #2368]
	bl	BsGet
	mov	r3, r4
	mov	r2, #1
	strb	r2, [r5]
	strb	r0, [r5, #2]
.L346:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L347:
	mvn	r3, #0
	b	.L346
	UNWIND(.fnend)
	.size	HEVC_Sei_TSI, .-HEVC_Sei_TSI
	.align	2
	.global	HEVC_Sei_User_Data_Unregistered
	.type	HEVC_Sei_User_Data_Unregistered, %function
HEVC_Sei_User_Data_Unregistered:
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
	cmp	r2, #15
	mov	r6, r2
	mov	r5, r0
	movhi	r4, #16
	bls	.L357
.L351:
	mov	r1, #8
	ldr	r0, [r5, #2368]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L351
	subs	r6, r6, #16
	beq	.L353
.L352:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r6, r4
	bne	.L352
.L353:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L357:
	ldr	r1, .L358
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L359:
	.align	2
.L358:
	.word	.LC47
	UNWIND(.fnend)
	.size	HEVC_Sei_User_Data_Unregistered, .-HEVC_Sei_User_Data_Unregistered
	.align	2
	.global	HEVC_IsRefListWrong
	.type	HEVC_IsRefListWrong, %function
HEVC_IsRefListWrong:
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
	add	r7, r0, #4096
	mov	r5, r0
	ldr	r3, [r7, #196]
	cmp	r3, #0
	beq	.L361
	ldr	r4, [r0, #2428]
	cmp	r4, #0
	beq	.L362
	ldr	r2, [r4, #16]
	cmp	r2, #0
	addne	r6, r0, #2416
	movne	r4, #0
	addne	r6, r6, #12
	bne	.L367
	b	.L405
.L368:
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L369
	ldr	r3, [r7, #196]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L406
	ldr	r2, [r6, #4]!
	cmp	r2, #0
	beq	.L362
	ldr	r2, [r2, #16]
	cmp	r2, #0
	beq	.L363
.L367:
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	bne	.L368
.L369:
	add	r5, r5, r4, lsl #2
	mov	r2, r4
	ldr	r1, .L410
	mov	r0, #1
	ldr	r3, [r5, #2428]
	ldr	r3, [r3, #16]
	str	ip, [sp]
	bl	dprint_vfmw
.L366:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L406:
	cmp	r3, #0
	beq	.L361
	ldr	r2, [r7, #200]
	cmp	r2, #0
	beq	.L361
	ldr	r4, [r5, #2496]
	cmp	r4, #0
	beq	.L374
	ldr	r2, [r4, #16]
	cmp	r2, #0
	addne	r6, r5, #2496
	movne	r4, #0
	bne	.L378
	b	.L407
.L379:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L380
	ldr	r3, [r7, #200]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L361
	ldr	r3, [r6, #4]!
	cmp	r3, #0
	beq	.L408
	ldr	r2, [r3, #16]
	cmp	r2, #0
	beq	.L409
.L378:
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L379
.L380:
	mov	r3, r0
	mov	r2, r4
	ldr	r1, .L410+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L400
.L361:
	mov	r0, #0
.L400:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L362:
	mov	r2, r4
	ldr	r1, .L410+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L366
.L405:
	mov	r4, r2
.L363:
	mov	r2, r4
	ldr	r1, .L410+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L366
.L408:
	ldr	r3, [r7, #196]
.L374:
	mov	r2, r4
	ldr	r1, .L410+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L400
.L409:
	ldr	r3, [r7, #196]
.L375:
	mov	r2, r4
	ldr	r1, .L410+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L400
.L407:
	mov	r4, r2
	b	.L375
.L411:
	.align	2
.L410:
	.word	.LC50
	.word	.LC53
	.word	.LC48
	.word	.LC49
	.word	.LC51
	.word	.LC52
	UNWIND(.fnend)
	.size	HEVC_IsRefListWrong, .-HEVC_IsRefListWrong
	.align	2
	.global	HEVC_GetUnRefPicWithMinPoc
	.type	HEVC_GetUnRefPicWithMinPoc, %function
HEVC_GetUnRefPicWithMinPoc:
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
	mvn	r4, #0
	str	r4, [r1]
	ldr	r3, [r0, #2600]
	cmp	r3, #16
	bhi	.L413
	cmp	r3, #0
	addne	lr, r0, #2608
	mvnne	r5, #-2147483648
	addne	lr, lr, #8
	movne	r2, #0
	beq	.L415
.L418:
	ldr	ip, [lr, #4]!
	ldr	r4, [ip, #8]
	cmp	r4, r5
	bge	.L417
	ldr	ip, [ip]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #0
	streq	r2, [r1]
	ldreq	r3, [r0, #2600]
	moveq	r5, r4
.L417:
	add	r2, r2, #1
	cmp	r3, r2
	bhi	.L418
	ldr	r3, [r1]
	cmn	r3, #1
	beq	.L415
	str	r5, [sp]
	mov	r0, #1
	ldr	r2, .L421
	ldr	r1, .L421+4
	bl	dprint_vfmw
	mov	r0, #0
.L416:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L413:
	ldr	r2, .L421
	mov	r0, #1
	ldr	r1, .L421+8
	bl	dprint_vfmw
	mov	r0, r4
	b	.L416
.L415:
	ldr	r2, .L421
	mov	r0, #1
	ldr	r1, .L421+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L416
.L422:
	.align	2
.L421:
	.word	.LANCHOR0+176
	.word	.LC56
	.word	.LC54
	.word	.LC55
	UNWIND(.fnend)
	.size	HEVC_GetUnRefPicWithMinPoc, .-HEVC_GetUnRefPicWithMinPoc
	.align	2
	.global	HEVC_IncreaseDPBSize
	.type	HEVC_IncreaseDPBSize, %function
HEVC_IncreaseDPBSize:
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
	ldr	r3, [r0, #2596]
	mov	r4, r0
	cmp	r3, #16
	bhi	.L427
	ldr	r0, [r0, #252]
	bl	FSP_GetTotalValidFsNum
	ldr	r2, [r4, #252]
	ldr	r1, [r4, #3544]
	mov	r5, r0
	ldr	r0, [r4, #3540]
	bl	FSP_GetOccupiedNum
	rsb	r0, r0, r5
	bic	r0, r0, r0, asr #31
	cmp	r0, #0
	ble	.L426
	ldr	r3, [r4, #2596]
	add	r3, r3, #1
	cmp	r0, r3
	bcc	.L426
	str	r3, [r4, #2596]
	mov	r0, #13
	ldr	r2, .L428
	ldr	r1, .L428+4
	bl	dprint_vfmw
	mov	r0, #0
.L425:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L426:
	mov	r3, r0
	ldr	r2, .L428
	ldr	r1, .L428+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L425
.L427:
	mov	r5, #17
	ldr	r2, .L428
	mov	r0, #1
	str	r5, [sp]
	ldr	r1, .L428+12
	bl	dprint_vfmw
	str	r5, [r4, #2596]
	mvn	r0, #0
	b	.L425
.L429:
	.align	2
.L428:
	.word	.LANCHOR0+204
	.word	.LC58
	.word	.LC59
	.word	.LC57
	UNWIND(.fnend)
	.size	HEVC_IncreaseDPBSize, .-HEVC_IncreaseDPBSize
	.align	2
	.global	HEVC_PicTypeStatistic
	.type	HEVC_PicTypeStatistic, %function
HEVC_PicTypeStatistic:
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
	add	r3, r0, #4096
	ldr	r2, [r3, #156]
	sub	r1, r2, #16
	cmp	r1, #5
	bls	.L431
	ldr	r2, [r0, #3524]
	sub	r2, r2, #16
	cmp	r2, #5
	bls	.L442
	ldr	r3, [r3, #148]
	cmp	r3, #1
	beq	.L434
	cmp	r3, #2
	beq	.L435
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [r0, #3536]
	ldmfd	sp, {fp, sp, pc}
.L431:
	mov	r3, #0
	str	r2, [r0, #3524]
	str	r3, [r0, #3536]
	ldmfd	sp, {fp, sp, pc}
.L434:
	ldr	r2, [r0, #3536]
	cmp	r2, #2
	beq	.L443
	str	r3, [r0, #3536]
	ldmfd	sp, {fp, sp, pc}
.L435:
	ldr	r3, [r0, #3536]
	sub	r3, r3, #1
	cmp	r3, #1
	movhi	r3, #0
	strhi	r3, [r0, #3536]
	ldmfd	sp, {fp, sp, pc}
.L443:
	ldmfd	sp, {fp, sp, pc}
.L442:
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_PicTypeStatistic, .-HEVC_PicTypeStatistic
	.align	2
	.global	HEVC_IsReferenceNalu
	.type	HEVC_IsReferenceNalu, %function
HEVC_IsReferenceNalu:
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
	add	r0, r0, #4096
	ldr	r0, [r0, #156]
	cmp	r0, #15
	bhi	.L445
	tst	r0, #1
	bne	.L447
.L445:
	sub	r0, r0, #16
	cmp	r0, #7
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L447:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsReferenceNalu, .-HEVC_IsReferenceNalu
	.align	2
	.global	HEVC_WriteQmatrix_4x4
	.type	HEVC_WriteQmatrix_4x4, %function
HEVC_WriteQmatrix_4x4:
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
	add	r1, r1, r0, lsl #6
	ldr	r0, [r1, #616]
	ldr	r3, [r1, #620]
	ldrb	ip, [r1, #608]	@ zero_extendqisi2
	ldrb	lr, [r1, #612]	@ zero_extendqisi2
	mov	r0, r0, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r0, r0
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r0
	str	r3, [r2]
	ldr	r0, [r1, #616]
	ldrb	lr, [r1, #609]	@ zero_extendqisi2
	ldrb	r3, [r1, #621]	@ zero_extendqisi2
	and	r0, r0, #65280
	ldrb	ip, [r1, #613]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #4]
	ldr	r0, [r1, #612]
	ldrb	lr, [r1, #610]	@ zero_extendqisi2
	ldrb	r3, [r1, #622]	@ zero_extendqisi2
	and	r0, r0, #16711680
	ldrb	ip, [r1, #618]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #8]
	ldr	r0, [r1, #620]
	ldrb	r3, [r1, #615]	@ zero_extendqisi2
	ldrb	lr, [r1, #611]	@ zero_extendqisi2
	and	r0, r0, #-16777216
	ldrb	ip, [r1, #619]	@ zero_extendqisi2
	orr	r1, lr, r0
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #12]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_4x4, .-HEVC_WriteQmatrix_4x4
	.align	2
	.global	HEVC_WriteQmatrix_32x32
	.type	HEVC_WriteQmatrix_32x32, %function
HEVC_WriteQmatrix_32x32:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	lr, r0, #18
	add	r0, r1, r0, lsl #6
	add	lr, r1, lr, lsl #6
	ldr	r1, [r0, #1768]
	ldr	r3, [r0, #1784]
	ldrb	ip, [lr, #608]	@ zero_extendqisi2
	ldrb	r4, [r0, #1776]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1800]
	ldr	r3, [r0, #1816]
	ldrb	ip, [r0, #1792]	@ zero_extendqisi2
	ldrb	r4, [r0, #1808]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1768]
	ldrb	r4, [lr, #609]	@ zero_extendqisi2
	ldrb	r3, [r0, #1785]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1777]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1800]
	ldrb	r4, [r0, #1793]	@ zero_extendqisi2
	ldrb	r3, [r0, #1817]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1809]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1776]
	ldrb	r4, [lr, #610]	@ zero_extendqisi2
	ldrb	r3, [r0, #1786]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1770]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1808]
	ldrb	r4, [r0, #1794]	@ zero_extendqisi2
	ldrb	r3, [r0, #1818]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1802]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1784]
	ldrb	lr, [lr, #611]	@ zero_extendqisi2
	ldrb	r3, [r0, #1779]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1771]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1816]
	ldrb	lr, [r0, #1795]	@ zero_extendqisi2
	ldrb	r3, [r0, #1811]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1803]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1772]
	ldr	r3, [r0, #1788]
	ldrb	ip, [r0, #1764]	@ zero_extendqisi2
	ldrb	lr, [r0, #1780]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1804]
	ldr	r3, [r0, #1820]
	ldrb	ip, [r0, #1796]	@ zero_extendqisi2
	ldrb	lr, [r0, #1812]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1772]
	ldrb	lr, [r0, #1765]	@ zero_extendqisi2
	ldrb	r3, [r0, #1789]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1781]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1804]
	ldrb	lr, [r0, #1797]	@ zero_extendqisi2
	ldrb	r3, [r0, #1821]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1813]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1780]
	ldrb	lr, [r0, #1766]	@ zero_extendqisi2
	ldrb	r3, [r0, #1790]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1774]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldr	r1, [r0, #1812]
	ldrb	lr, [r0, #1798]	@ zero_extendqisi2
	ldrb	r3, [r0, #1822]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1806]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1788]
	ldrb	lr, [r0, #1767]	@ zero_extendqisi2
	ldrb	r3, [r0, #1783]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1775]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1820]
	ldrb	ip, [r0, #1799]	@ zero_extendqisi2
	ldrb	r3, [r0, #1815]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1807]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_32x32, .-HEVC_WriteQmatrix_32x32
	.align	2
	.global	HEVC_WriteQmatrix_8x8
	.type	HEVC_WriteQmatrix_8x8, %function
HEVC_WriteQmatrix_8x8:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	lr, r0, #6
	add	r0, r1, r0, lsl #6
	add	lr, r1, lr, lsl #6
	ldr	r1, [r0, #1008]
	ldr	r3, [r0, #1040]
	ldrb	ip, [lr, #608]	@ zero_extendqisi2
	ldrb	r4, [r0, #1024]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1016]
	ldr	r3, [r0, #1048]
	ldrb	ip, [r0, #1000]	@ zero_extendqisi2
	ldrb	r4, [r0, #1032]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1008]
	ldrb	r4, [lr, #609]	@ zero_extendqisi2
	ldrb	r3, [r0, #1041]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1025]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1016]
	ldrb	r4, [r0, #1001]	@ zero_extendqisi2
	ldrb	r3, [r0, #1049]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1033]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1024]
	ldrb	r4, [lr, #610]	@ zero_extendqisi2
	ldrb	r3, [r0, #1042]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1010]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1032]
	ldrb	r4, [r0, #1002]	@ zero_extendqisi2
	ldrb	r3, [r0, #1050]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1018]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1040]
	ldrb	lr, [lr, #611]	@ zero_extendqisi2
	ldrb	r3, [r0, #1027]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1011]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1048]
	ldrb	lr, [r0, #1003]	@ zero_extendqisi2
	ldrb	r3, [r0, #1035]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1019]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1012]
	ldr	r3, [r0, #1044]
	ldrb	ip, [r0, #996]	@ zero_extendqisi2
	ldrb	lr, [r0, #1028]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1020]
	ldr	r3, [r0, #1052]
	ldrb	ip, [r0, #1004]	@ zero_extendqisi2
	ldrb	lr, [r0, #1036]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1012]
	ldrb	lr, [r0, #997]	@ zero_extendqisi2
	ldrb	r3, [r0, #1045]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1029]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1020]
	ldrb	lr, [r0, #1005]	@ zero_extendqisi2
	ldrb	r3, [r0, #1053]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1037]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1028]
	ldrb	lr, [r0, #998]	@ zero_extendqisi2
	ldrb	r3, [r0, #1046]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1014]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldr	r1, [r0, #1036]
	ldrb	lr, [r0, #1006]	@ zero_extendqisi2
	ldrb	r3, [r0, #1054]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1022]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1044]
	ldrb	lr, [r0, #999]	@ zero_extendqisi2
	ldrb	r3, [r0, #1031]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1015]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1052]
	ldrb	ip, [r0, #1007]	@ zero_extendqisi2
	ldrb	r3, [r0, #1039]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1023]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_8x8, .-HEVC_WriteQmatrix_8x8
	.align	2
	.global	HEVC_WriteQmatrix_16x16
	.type	HEVC_WriteQmatrix_16x16, %function
HEVC_WriteQmatrix_16x16:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	lr, r0, #12
	add	r0, r1, r0, lsl #6
	add	lr, r1, lr, lsl #6
	ldr	r1, [r0, #1384]
	ldr	r3, [r0, #1400]
	ldrb	ip, [lr, #608]	@ zero_extendqisi2
	ldrb	r4, [r0, #1392]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1416]
	ldr	r3, [r0, #1432]
	ldrb	ip, [r0, #1408]	@ zero_extendqisi2
	ldrb	r4, [r0, #1424]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1384]
	ldrb	r4, [lr, #609]	@ zero_extendqisi2
	ldrb	r3, [r0, #1401]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1393]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1416]
	ldrb	r4, [r0, #1409]	@ zero_extendqisi2
	ldrb	r3, [r0, #1433]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1425]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1392]
	ldrb	r4, [lr, #610]	@ zero_extendqisi2
	ldrb	r3, [r0, #1402]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1386]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1424]
	ldrb	r4, [r0, #1410]	@ zero_extendqisi2
	ldrb	r3, [r0, #1434]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1418]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1400]
	ldrb	lr, [lr, #611]	@ zero_extendqisi2
	ldrb	r3, [r0, #1395]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1387]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1432]
	ldrb	lr, [r0, #1411]	@ zero_extendqisi2
	ldrb	r3, [r0, #1427]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1419]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1388]
	ldr	r3, [r0, #1404]
	ldrb	ip, [r0, #1380]	@ zero_extendqisi2
	ldrb	lr, [r0, #1396]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1420]
	ldr	r3, [r0, #1436]
	ldrb	ip, [r0, #1412]	@ zero_extendqisi2
	ldrb	lr, [r0, #1428]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1388]
	ldrb	lr, [r0, #1381]	@ zero_extendqisi2
	ldrb	r3, [r0, #1405]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1397]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1420]
	ldrb	lr, [r0, #1413]	@ zero_extendqisi2
	ldrb	r3, [r0, #1437]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1429]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1396]
	ldrb	lr, [r0, #1382]	@ zero_extendqisi2
	ldrb	r3, [r0, #1406]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1390]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldr	r1, [r0, #1428]
	ldrb	lr, [r0, #1414]	@ zero_extendqisi2
	ldrb	r3, [r0, #1438]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1422]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1404]
	ldrb	lr, [r0, #1383]	@ zero_extendqisi2
	ldrb	r3, [r0, #1399]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1391]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1436]
	ldrb	ip, [r0, #1415]	@ zero_extendqisi2
	ldrb	r3, [r0, #1431]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1423]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_16x16, .-HEVC_WriteQmatrix_16x16
	.global	__aeabi_idivmod
	.align	2
	.global	HEVC_CtbRsAddrToTsAddr
	.type	HEVC_CtbRsAddrToTsAddr, %function
HEVC_CtbRsAddrToTsAddr:
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
	ldr	ip, [r0, #2404]
	mov	r6, r1
	ldrb	r3, [ip, #13]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L487
	ldr	r3, [ip, #72]
	ldr	r7, [ip, #68]
	ldrb	r5, [ip, #15]	@ zero_extendqisi2
	mov	r2, r3
	str	r3, [fp, #-236]
	ldr	r3, [r0, #2400]
	cmp	r2, #0
	sub	r8, r2, #1
	sub	r2, r7, #1
	str	r2, [fp, #-240]
	ldr	r4, [r3, #64]
	ldr	r1, [r3, #128]
	ble	.L458
	ldr	r3, [fp, #-236]
	add	r2, ip, #210
	sub	r0, fp, #216
	add	lr, r3, #105
	add	lr, ip, lr, lsl #1
.L457:
	ldrsh	r3, [r2, #2]!
	cmp	r2, lr
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L457
.L458:
	cmp	r7, #0
	ble	.L456
	add	r3, r7, #85
	add	r2, ip, #170
	sub	r0, fp, #128
	add	ip, ip, r3, lsl #1
.L461:
	ldrsh	r3, [r2, #2]!
	cmp	r2, ip
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L461
.L456:
	mov	r10, #1
	mov	r0, r4
	mov	r10, r10, asl r1
	mov	r1, r10
	bl	__aeabi_idiv
	mov	r1, r10
	mov	r9, r0
	mov	r0, r4
	bl	__aeabi_idivmod
	mov	r0, r6
	cmp	r1, #0
	addne	r9, r9, #1
	mov	r1, r9
	bl	__aeabi_idivmod
	mov	r0, r6
	mov	r4, r1
	mov	r1, r9
	bl	__aeabi_idiv
	cmp	r5, #0
	beq	.L502
	cmp	r8, #0
	mov	r3, #0
	blt	.L478
	sub	r10, fp, #212
	mov	lr, r3
	mov	r6, r3
	mov	r8, r3
	str	r3, [fp, #-232]
	str	r3, [fp, #-244]
.L464:
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	blt	.L481
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	ip, r2
	add	r8, r8, #1
	sub	r5, fp, #128
	mov	r6, lr
	add	r9, r3, r8
	b	.L467
.L479:
	mov	r6, lr
.L467:
	ldr	r3, [r5, #4]!
	add	ip, ip, #1
	add	r3, r3, #1
	add	r1, r2, r3
	cmp	r4, r1
	mla	lr, r8, r3, lr
	bge	.L465
	cmp	r0, r9
	blt	.L499
.L465:
	cmp	ip, r7
	mov	r2, r1
	bne	.L479
.L470:
	add	r2, r1, r3
	cmp	r4, r2
	bge	.L480
	cmp	r0, r9
	blt	.L497
.L480:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	ip, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, ip
	str	r2, [fp, #-244]
	bne	.L464
.L498:
	rsb	r0, r9, r0
	mov	r2, r1
	mul	r3, r0, r3
.L462:
	rsb	r2, r2, r4
	add	r3, r2, r3
	add	r6, r3, r6
.L487:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L502:
	cmp	r8, #0
	mov	r3, r5
	blt	.L478
	ldr	r2, [fp, #-240]
	sub	r10, fp, #212
	str	r5, [fp, #-232]
	mov	lr, r5
	cmp	r2, #0
	str	r5, [fp, #-244]
	mov	r6, r5
	mov	r8, r5
	blt	.L484
.L503:
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	ip, r2
	add	r8, r8, #1
	sub	r5, fp, #128
	mov	r6, lr
	add	r9, r3, r8
	b	.L473
.L482:
	mov	r6, lr
.L473:
	ldr	r3, [r5, #4]!
	add	ip, ip, #1
	add	r3, r3, #1
	add	r1, r2, r3
	cmp	r4, r1
	mla	lr, r8, r3, lr
	bge	.L471
	cmp	r0, r9
	blt	.L472
.L471:
	cmp	ip, r7
	mov	r2, r1
	bne	.L482
.L476:
	add	r2, r1, r3
	cmp	r4, r2
	bge	.L496
	cmp	r0, r9
	blt	.L497
.L496:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	ip, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, ip
	str	r2, [fp, #-244]
	beq	.L498
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	bge	.L503
.L484:
	ldr	r2, [fp, #-232]
	mov	r1, #0
	add	r9, r2, r8
	b	.L476
.L499:
	ldr	r1, [fp, #-232]
	rsb	r0, r1, r0
	mul	r3, r0, r3
	b	.L462
.L472:
	cmp	r1, r4
	bgt	.L499
	mov	r1, r2
	b	.L496
.L481:
	ldr	r2, [fp, #-232]
	mov	r1, #0
	add	r9, r2, r8
	b	.L470
.L497:
	ldr	r2, [fp, #-232]
	rsb	r0, r2, r0
	mov	r2, r1
	mul	r3, r0, r3
	b	.L462
.L478:
	mov	r2, r3
	mov	r6, r3
	b	.L462
	UNWIND(.fnend)
	.size	HEVC_CtbRsAddrToTsAddr, .-HEVC_CtbRsAddrToTsAddr
	.align	2
	.global	HEVC_CtbTsAddrToRsAddr
	.type	HEVC_CtbTsAddrToRsAddr, %function
HEVC_CtbTsAddrToRsAddr:
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
	ldr	lr, [r0, #2404]
	mov	r6, r1
	ldrb	r3, [lr, #13]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r0, r1
	beq	.L528
	ldr	r3, [lr, #72]
	ldr	r7, [lr, #68]
	mov	r2, r3
	str	r3, [fp, #-232]
	ldr	r3, [r0, #2400]
	cmp	r2, #0
	ldr	r4, [r3, #64]
	ldr	ip, [r3, #128]
	ble	.L510
	ldr	r3, [fp, #-232]
	add	r2, lr, #210
	sub	r1, fp, #216
	add	r0, r3, #105
	add	r0, lr, r0, lsl #1
.L509:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L509
.L510:
	cmp	r7, #0
	ble	.L508
	add	r0, r7, #85
	add	r2, lr, #170
	sub	r1, fp, #128
	add	r0, lr, r0, lsl #1
.L513:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L513
.L508:
	mov	r5, #1
	mov	r0, r4
	mov	r5, r5, asl ip
	mov	r1, r5
	bl	__aeabi_idiv
	mov	r1, r5
	mov	r8, r0
	mov	r0, r4
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-232]
	cmp	r1, #0
	addne	r8, r8, #1
	cmp	r3, #0
	str	r8, [fp, #-240]
	ble	.L512
	mov	r8, #0
	ldr	r2, [fp, #-124]
	sub	r9, fp, #212
	mov	r10, r8
	mov	r3, r8
	mov	lr, r8
	mov	r0, r8
	mov	r4, r8
	add	r2, r2, #1
	str	r2, [fp, #-236]
.L514:
	cmp	r7, #0
	ble	.L524
	ldr	r0, [r9]
	ldr	r4, [fp, #-236]
	add	r0, r0, #1
	mla	r1, r0, r4, r3
	cmp	r6, r1
	blt	.L525
	mov	r5, #0
	mov	lr, r3
	mov	r2, r5
	mov	r3, r1
	sub	ip, fp, #124
	b	.L519
.L516:
	ldr	r4, [ip, #4]!
	mov	lr, r3
	add	r4, r4, #1
	mla	r1, r0, r4, r3
	cmp	r1, r6
	bgt	.L517
	mov	r3, r1
.L519:
	add	r2, r2, #1
	add	r5, r5, r4
	cmp	r2, r7
	bne	.L516
.L518:
	cmp	r3, r6
	bgt	.L523
	ldr	r2, [fp, #-232]
	add	r10, r10, #1
	add	r8, r8, r0
	add	r9, r9, #4
	cmp	r10, r2
	bne	.L514
.L523:
	mov	r3, lr
.L517:
	cmp	r4, #0
	beq	.L512
	rsb	r6, r3, r6
	mov	r1, r4
	mov	r0, r6
	bl	__aeabi_idiv
	ldr	r3, [fp, #-240]
	mov	r1, r4
	add	r4, r0, r8
	mov	r0, r6
	mul	r4, r4, r3
	bl	__aeabi_idivmod
	add	r1, r1, r5
	add	r0, r4, r1
.L528:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L524:
	mov	r5, #0
	b	.L518
.L525:
	ldr	r4, [fp, #-236]
	mov	r5, #0
	b	.L517
.L512:
	ldr	r1, .L530
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L528
.L531:
	.align	2
.L530:
	.word	.LC60
	UNWIND(.fnend)
	.size	HEVC_CtbTsAddrToRsAddr, .-HEVC_CtbTsAddrToRsAddr
	.align	2
	.global	HEVC_CalcTileMap
	.type	HEVC_CalcTileMap, %function
HEVC_CalcTileMap:
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
	ldr	r4, .L559
	mov	r10, r0
	ldr	r0, [r4]
	cmp	r0, #0
	beq	.L558
	ldr	r5, .L559+4
	add	r0, r0, #471040
	mov	r2, #147456
	mov	r1, #0
	add	r0, r0, #372
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r0, [r4]
	ldr	r3, [r5, #48]
	mov	r2, #36864
	add	r0, r0, #618496
	mov	r1, #0
	add	r0, r0, #372
	blx	r3
	add	r0, r10, #8576
	ldr	r3, [r5, #48]
	mov	r2, #880
	mov	r1, #0
	add	r0, r0, #60
	blx	r3
	add	r3, r10, #8192
	str	r3, [fp, #-60]
	mov	r2, r3
	mov	r3, #0
	str	r3, [r2, #440]
	ldr	r9, [r10, #2404]
	ldr	r1, [r10, #2400]
	ldr	r2, [r9, #72]
	ldr	r8, [r1, #188]
	cmp	r2, r3
	beq	.L535
	ldr	r2, [r4]
	str	r3, [fp, #-72]
	str	r3, [fp, #-76]
	str	r2, [fp, #-48]
.L536:
	ldr	r2, [r9, #68]
	cmp	r2, #0
	ldr	r2, [fp, #-72]
	add	r2, r2, #104
	streq	r2, [fp, #-80]
	beq	.L542
	mov	r1, r2
	str	r2, [fp, #-80]
	mov	r7, r1, asl #1
	ldr	r1, [fp, #-76]
	mov	r2, #0
	str	r2, [fp, #-52]
	str	r2, [fp, #-56]
	mul	r1, r8, r1
	ldr	r2, [fp, #-60]
	ldr	r2, [r2, #440]
	str	r1, [fp, #-68]
.L541:
	add	r1, r2, #1072
	add	r0, r9, r7
	add	r1, r1, #7
	add	r1, r10, r1, lsl #3
	str	r3, [r1, #4]
	ldrsh	r1, [r0, #4]
	cmp	r1, #0
	ldreq	r1, [fp, #-52]
	addeq	r1, r1, #84
	streq	r1, [fp, #-64]
	beq	.L537
	ldr	r2, [fp, #-52]
	mov	r5, #0
	ldr	r1, [fp, #-56]
	add	r2, r2, #84
	ldr	r0, [fp, #-68]
	str	r2, [fp, #-64]
	add	r6, r1, r0
	mov	ip, r2, asl #1
.L538:
	add	r2, r9, ip
	ldrsh	r2, [r2, #4]
	cmp	r2, #0
	beq	.L540
	add	r2, r3, #117760
	ldr	r1, [fp, #-48]
	add	r2, r2, #92
	rsb	lr, r3, r6
	mov	r4, r3
	add	r2, r1, r2, lsl #2
.L539:
	add	r1, lr, r3
	str	r1, [r2, #4]!
	ldr	r9, [r10, #2404]
	add	r3, r3, #1
	rsb	r1, r4, r3
	add	r0, r9, ip
	ldrsh	r0, [r0, #4]
	cmp	r0, r1
	bhi	.L539
.L540:
	add	r2, r9, r7
	add	r5, r5, #1
	add	r6, r6, r8
	ldrsh	r2, [r2, #4]
	cmp	r2, r5
	bhi	.L538
	ldr	r2, [fp, #-60]
	ldr	r2, [r2, #440]
.L537:
	add	r1, r10, r2, lsl #3
	ldr	r0, [fp, #-64]
	add	r1, r1, #8576
	sub	ip, r3, #1
	ldr	lr, [fp, #-52]
	add	r2, r2, #1
	str	ip, [r1, #64]
	add	r0, r9, r0, lsl #1
	ldr	r1, [fp, #-60]
	add	lr, lr, #1
	str	lr, [fp, #-52]
	str	r2, [r1, #440]
	ldr	r1, [r9, #68]
	ldrsh	r0, [r0, #4]
	cmp	r1, lr
	ldr	r1, [fp, #-56]
	add	r1, r1, r0
	str	r1, [fp, #-56]
	bhi	.L541
.L542:
	ldr	r2, [fp, #-80]
	ldr	r0, [fp, #-72]
	ldr	r1, [r9, #72]
	add	r2, r9, r2, lsl #1
	add	r0, r0, #1
	cmp	r1, r0
	ldr	r1, [fp, #-76]
	ldrsh	r2, [r2, #4]
	str	r0, [fp, #-72]
	add	r2, r1, r2
	str	r2, [fp, #-76]
	bhi	.L536
.L535:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L558:
	ldr	r2, .L559+8
	ldr	r1, .L559+12
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L560:
	.align	2
.L559:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+228
	.word	.LC61
	UNWIND(.fnend)
	.size	HEVC_CalcTileMap, .-HEVC_CalcTileMap
	.align	2
	.global	HEVC_WritePicMsg
	.type	HEVC_WritePicMsg, %function
HEVC_WritePicMsg:
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
	mov	r4, r0
	ldr	r3, [r0, #3556]
	ldr	r2, [r4, #3732]
	mov	r0, #2
	ldr	r1, .L584
	add	r5, r4, #4096
	bl	dprint_vfmw
	ldr	r1, .L584+4
	mov	r0, #4
	mov	r7, #200
	bl	dprint_vfmw
	ldr	r3, [r4, #3528]
	add	r8, r4, #8192
	mov	ip, #0
	ldr	r6, .L584+8
	add	r0, r4, #6016
	str	r3, [r5, #1872]
	add	r0, r0, #48
	ldr	r2, [r4, #3696]
	mul	r7, r7, r3
	str	r2, [r5, #3136]
	mov	r2, #64
	ldr	r3, [r4, #3700]
	str	r3, [r5, #3140]
	ldr	r3, [r4, #3620]
	ldr	r1, [r4, #3624]
	rsb	r1, r3, r1
	str	r1, [r5, #3144]
	ldr	lr, [r4, #3732]
	add	r1, r7, #12672
	add	r1, r1, #8
	add	r1, r4, r1
	str	lr, [r5, #3128]
	ldr	lr, [r4, #3556]
	str	lr, [r5, #3132]
	ldr	lr, [r4, #3720]
	str	lr, [r5, #3148]
	ldr	lr, [r4, #3724]
	str	lr, [r5, #3152]
	ldr	lr, [r4, #3728]
	str	lr, [r5, #3156]
	ldr	lr, [r4, #3628]
	rsb	r3, r3, lr
	str	r3, [r5, #3160]
	ldr	r3, [r4, #3632]
	rsb	r3, lr, r3
	str	r3, [r5, #3164]
	ldr	r3, [r4, #2420]
	str	ip, [r4, #204]
	str	r3, [r8, #236]
	ldr	r3, [r4, #2400]
	ldrb	ip, [r3, #10]	@ zero_extendqisi2
	strb	ip, [r5, #1846]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	strb	ip, [r5, #1847]
	ldrb	ip, [r3, #7]	@ zero_extendqisi2
	strb	ip, [r5, #1848]
	ldrb	ip, [r3, #6]	@ zero_extendqisi2
	strb	ip, [r5, #1849]
	ldrb	ip, [r3, #5]	@ zero_extendqisi2
	strb	ip, [r5, #1850]
	ldr	ip, [r3, #60]
	str	ip, [r5, #1852]
	ldr	ip, [r3, #104]
	strb	ip, [r5, #1856]
	ldr	ip, [r3, #192]
	sub	ip, ip, #1
	str	ip, [r5, #1860]
	ldr	ip, [r3, #188]
	sub	ip, ip, #1
	str	ip, [r5, #1864]
	ldr	ip, [r4, #3532]
	str	ip, [r5, #1868]
	ldr	ip, [r4, #2404]
	ldr	lr, [ip, #84]
	sub	lr, lr, #2
	str	lr, [r5, #1876]
	ldrb	lr, [ip, #11]	@ zero_extendqisi2
	strb	lr, [r5, #1880]
	ldrb	ip, [ip, #10]	@ zero_extendqisi2
	strb	ip, [r5, #1881]
	ldr	ip, [r3, #164]
	str	ip, [r5, #1884]
	ldr	ip, [r3, #168]
	str	ip, [r5, #1888]
	ldr	ip, [r3, #156]
	str	ip, [r5, #1892]
	ldr	ip, [r3, #160]
	str	ip, [r5, #1896]
	ldr	ip, [r3, #148]
	str	ip, [r5, #1900]
	ldr	ip, [r3, #152]
	str	ip, [r5, #1904]
	ldr	ip, [r3, #172]
	ldr	r6, [r6, #52]
	str	ip, [r5, #1908]
	ldr	ip, [r3, #124]
	str	ip, [r5, #1912]
	ldr	ip, [r3, #128]
	str	ip, [r5, #1916]
	ldr	ip, [r3, #100]
	str	ip, [r5, #1920]
	ldr	ip, [r3, #92]
	str	ip, [r5, #1924]
	ldr	ip, [r3, #112]
	str	ip, [r5, #1928]
	ldr	ip, [r3, #108]
	str	ip, [r5, #1932]
	ldr	ip, [r3, #96]
	str	ip, [r5, #1936]
	ldr	r3, [r3, #88]
	str	r3, [r5, #1940]
	blx	r6
	ldr	ip, [r4, #2400]
	add	r3, r4, #8256
	add	r2, r4, #8128
	add	r1, r4, #7616
	add	r3, r3, #12
	ldr	lr, [ip, #68]
	add	r2, r2, #60
	add	r1, r1, #60
	mov	r0, r4
	str	lr, [r5, #2032]
	ldr	ip, [ip, #64]
	str	ip, [r5, #2036]
	bl	HEVC_CalcTileInfo
	subs	r6, r0, #0
	bne	.L582
	ldr	r3, [r4, #2404]
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	strb	r2, [r5, #2060]
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	strb	r2, [r5, #2061]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	strb	r2, [r5, #2062]
	ldrb	r2, [r3, #14]	@ zero_extendqisi2
	strb	r2, [r5, #2063]
	ldrb	r2, [r3, #15]	@ zero_extendqisi2
	strb	r2, [r5, #2064]
	ldrb	r2, [r3, #13]	@ zero_extendqisi2
	strb	r2, [r5, #2065]
	ldr	r2, [r4, #2400]
	ldr	r1, [r3, #56]
	ldr	r2, [r2, #128]
	rsb	r2, r1, r2
	str	r2, [r5, #2068]
	ldr	r2, [r3, #52]
	str	r2, [r5, #2072]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	strb	r2, [r5, #2076]
	ldrb	r2, [r3, #12]	@ zero_extendqisi2
	strb	r2, [r5, #2077]
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	strb	r2, [r5, #2078]
	ldr	r2, [r3, #60]
	str	r2, [r5, #2080]
	ldr	r2, [r3, #64]
	str	r2, [r5, #2084]
	ldr	r2, [r3, #72]
	sub	r2, r2, #1
	str	r2, [r5, #2088]
	ldr	r2, [r3, #68]
	sub	r2, r2, #1
	str	r2, [r5, #2092]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	strb	r2, [r5, #1881]
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	strb	r3, [r5, #1880]
	ldr	r3, [r4, #2344]
	str	r6, [r4, #2360]
	cmp	r3, #1
	beq	.L573
	ldr	r3, [r4, #3580]
	ldr	r0, [r4, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	subs	r9, r0, #0
	beq	.L583
	ldr	r2, [r9, #28]
	ldr	r3, [r9, #32]
	cmp	r2, #0
	beq	.L566
	cmp	r3, #0
	beq	.L566
	add	r3, r4, #7488
	add	r2, r4, #7232
	add	r1, r4, #7360
	add	r3, r3, #60
	add	r2, r2, #48
	add	r1, r1, #48
	ldr	r0, [r4, #252]
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r9, #28]
	add	r2, r4, #7360
	add	r1, r4, #7488
	add	r2, r2, #52
	add	r1, r1, #52
	ldr	r3, [r3, #4]
	str	r3, [r5, #3128]
	ldr	r0, [r4, #252]
	bl	FSP_GetPmvAddrTab
	ldr	r2, [r4, #3556]
	add	r3, r4, r7
	add	r3, r3, #12544
	str	r2, [r5, #3132]
	ldr	r2, [r9, #12]
	str	r2, [r5, #3448]
	ldr	r2, [r9, #32]
	ldr	r2, [r2, #8]
	str	r2, [r8, #432]
	ldr	r2, [r9, #32]
	ldr	r2, [r2, #60]
	str	r2, [r8, #436]
	ldr	ip, [r3]
	cmp	ip, #0
	str	ip, [r8, #228]
	beq	.L568
	add	r3, r7, #12608
	add	r2, r4, #8320
	add	r3, r3, #4
	add	r2, r2, #32
	add	r3, r4, r3
	mov	r0, r6
.L569:
	add	r0, r0, #1
	ldr	r1, [r3, #4]!
	cmp	r0, ip
	str	r1, [r2, #4]!
	bne	.L569
.L568:
	add	r7, r4, #6144
	mov	r6, #0
	add	r7, r7, #52
.L570:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r4
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_8x8
	cmp	r6, #4
	add	r7, r7, #64
	bne	.L570
	add	r2, r4, #6400
	mov	r0, r6
	add	r2, r2, #52
	mov	r1, r4
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r4, #6464
	add	r2, r2, #52
	mov	r1, r4
	mov	r0, #5
	add	r7, r4, #6656
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r4, #6528
	add	r2, r2, #52
	mov	r1, r4
	mov	r0, #0
	add	r7, r7, #52
	bl	HEVC_WriteQmatrix_16x16
	add	r2, r4, #6592
	add	r2, r2, #52
	mov	r1, r4
	mov	r0, #1
	mov	r6, #2
	bl	HEVC_WriteQmatrix_16x16
.L571:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r4
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_16x16
	cmp	r6, #6
	add	r7, r7, #64
	bne	.L571
	add	r2, r4, #6912
	mov	r1, r4
	add	r2, r2, #52
	mov	r0, #0
	bl	HEVC_WriteQmatrix_32x32
	add	r2, r4, #6976
	add	r2, r2, #52
	mov	r1, r4
	mov	r0, #1
	add	r7, r4, #7040
	bl	HEVC_WriteQmatrix_32x32
	add	r7, r7, #52
	mov	r6, #0
.L572:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r4
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_4x4
	cmp	r6, #6
	add	r7, r7, #16
	bne	.L572
	ldr	r1, [r4, #2296]
	mov	r0, #0
	ldr	r3, [r4, #2300]
	ldr	r2, [r4, #2288]
	ldr	ip, [r4, #2292]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r5, #3092]
	ldr	r1, [r4, #2312]
	ldr	r3, [r4, #2316]
	ldr	r2, [r4, #2304]
	ldr	ip, [r4, #2308]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r5, #3096]
	ldr	r3, [r4, #3556]
	str	r3, [r5, #3124]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L573:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L582:
	ldr	r2, .L584+12
	mov	r0, #1
	ldr	r1, .L584+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L566:
	ldr	r1, .L584+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L583:
	ldr	r3, [r4, #3580]
	mov	r0, #1
	ldr	r1, .L584+24
	ldr	r2, [r3, #28]
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L585:
	.align	2
.L584:
	.word	.LC62
	.word	.LC63
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+248
	.word	.LC64
	.word	.LC66
	.word	.LC65
	UNWIND(.fnend)
	.size	HEVC_WritePicMsg, .-HEVC_WritePicMsg
	.align	2
	.global	HEVC_CheckListX
	.type	HEVC_CheckListX, %function
HEVC_CheckListX:
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
	add	r3, r0, #4096
	ldrb	r3, [r3, #129]	@ zero_extendqisi2
	cmp	r3, #0
	addeq	r3, r0, #4224
	beq	.L588
	ldrsb	r3, [r0, #11]
	cmp	r3, #0
	addne	r3, r0, #11136
	addne	r3, r3, #52
	beq	.L621
.L588:
	ldr	ip, [r3, #68]
	ldr	lr, [r3, #72]
	cmp	ip, #16
	bhi	.L622
	cmp	lr, #16
	bhi	.L592
	cmp	ip, #0
	beq	.L593
	ldr	r3, [r0, #2428]
	cmp	r3, #0
	beq	.L606
	ldr	r3, [r3, #16]
	cmp	r3, #0
	addne	r1, r0, #2416
	movne	r2, #0
	addne	r1, r1, #12
	bne	.L598
	b	.L623
.L599:
	ldr	r3, [r1, #4]!
	cmp	r3, #0
	beq	.L594
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L595
.L598:
	add	r2, r2, #1
	cmp	r2, ip
	bne	.L599
.L593:
	cmp	lr, #0
	beq	.L618
	ldr	r3, [r0, #2496]
	cmp	r3, #0
	beq	.L609
	ldr	r3, [r3, #16]
	cmp	r3, #0
	addne	r0, r0, #2496
	movne	r2, #0
	bne	.L604
	b	.L624
.L605:
	ldr	r3, [r0, #4]!
	cmp	r3, #0
	beq	.L600
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L601
.L604:
	add	r2, r2, #1
	cmp	r2, lr
	bne	.L605
.L618:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L606:
	mov	r2, r3
.L594:
	ldr	r1, .L625
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L623:
	mov	r2, r3
.L595:
	ldr	r1, .L625+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L609:
	mov	r2, r3
.L600:
	ldr	r1, .L625+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L624:
	mov	r2, r3
.L601:
	ldr	r1, .L625+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L621:
	mov	r0, r3
	ldr	r2, .L625+16
	ldr	r1, .L625+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L592:
	mov	r2, lr
	mov	r3, #17
	ldr	r1, .L625+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L622:
	mov	r2, ip
	mov	r3, #17
	ldr	r1, .L625+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L626:
	.align	2
.L625:
	.word	.LC70
	.word	.LC71
	.word	.LC72
	.word	.LC73
	.word	.LANCHOR0+268
	.word	.LC67
	.word	.LC69
	.word	.LC68
	UNWIND(.fnend)
	.size	HEVC_CheckListX, .-HEVC_CheckListX
	.align	2
	.global	HEVC_WriteSliceMsg
	.type	HEVC_WriteSliceMsg, %function
HEVC_WriteSliceMsg:
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
	UNWIND(.pad #84)
	sub	sp, sp, #84
	ldr	r3, [r0, #3528]
	mov	r4, r0
	str	r3, [fp, #-116]
	bl	HEVC_CheckListX
	subs	r3, r0, #0
	str	r3, [fp, #-112]
	bne	.L668
	ldr	r0, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r0, r3
	bcs	.L701
	ldr	r6, [r4, #2420]
	mov	r5, #1360
	ldr	r7, [fp, #-112]
	mov	r2, r5
	ldr	r3, .L705
	add	r8, r4, #4096
	mla	r6, r5, r0, r6
	mov	r1, r7
	ldr	r3, [r3, #48]
	mov	r0, r6
	blx	r3
	ldr	r3, .L705
	mov	r2, #64
	mov	r1, r7
	sub	r0, fp, #108
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #204]
	ldr	r2, [r4, #152]
	add	r3, r3, #1
	str	r3, [r4, #204]
	cmp	r3, r2
	ldrcc	r2, [r4, #2420]
	ldrcs	r3, [fp, #-112]
	mlacc	r3, r5, r3, r2
	str	r3, [r6, #1356]
	ldr	r1, [r8, #164]
	ldr	r2, [r4, #2388]
	ldr	r0, [r4, #176]
	ldr	r3, [r4, #236]
	add	r0, r0, #1
	str	r1, [r4, #208]
	str	r0, [r4, #176]
	add	r3, r3, #1
	str	r3, [r4, #236]
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	str	r0, [fp, #-120]
	cmp	r1, #1
	cmpls	r1, r3
	bcs	.L632
	add	r0, r6, r1, lsl #2
.L633:
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r1, r1, #1
	add	r2, r2, r3
	ldr	r2, [r2, #56]
	str	r2, [r0, #8]
	ldr	r2, [r4, #2388]
	add	r2, r2, r3
	ldr	r2, [r2, #52]
	str	r2, [r0], #4
	ldr	r2, [r4, #2388]
	add	r3, r2, r3
	ldr	r3, [r3, #60]
	str	r3, [r0, #12]
	ldr	r2, [r4, #2388]
	ldr	r3, [r2, #8]
	cmp	r3, r1
	movhi	ip, #1
	movls	ip, #0
	cmp	r1, #1
	movhi	ip, #0
	cmp	ip, #0
	bne	.L633
.L632:
	cmp	r3, #1
	addls	r3, r6, r3, lsl #2
	addls	r1, r6, #8
	movls	r2, #0
	bhi	.L638
.L637:
	str	r2, [r3, #8]
	str	r2, [r3], #4
	cmp	r3, r1
	str	r2, [r3, #12]
	bne	.L637
.L638:
	ldrb	r3, [r8, #129]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L702
.L636:
	add	r5, r4, #8192
	ldr	r3, [r5, #3064]
	cmp	r3, #0
	beq	.L639
	add	ip, r4, #2416
	add	r10, r6, #112
	add	ip, ip, #8
	add	r9, r6, #368
	mov	r1, #0
	mov	lr, ip
.L640:
	ldr	r3, [ip, #4]!
	sub	r7, fp, #44
	add	r1, r1, #1
	ldr	r3, [r3, #4]
	str	r3, [r10, #4]!
	ldr	r0, [lr, #4]!
	ldr	r2, [r0, #16]
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #24]
	add	r3, r3, #1840
	add	r3, r3, #12
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r0, #16]
	ldr	r3, [r3, #24]
	str	r3, [r9, #4]!
	ldr	r3, [r5, #3064]
	cmp	r3, r1
	bhi	.L640
	ldr	r2, [r5, #3068]
	cmp	r2, #0
	beq	.L641
.L667:
	add	ip, r4, #2480
	add	r10, r6, #176
	add	ip, ip, #12
	add	r9, r6, #432
	mov	r1, #0
	mov	lr, ip
.L642:
	ldr	r3, [lr, #4]!
	sub	r7, fp, #44
	add	r1, r1, #1
	ldr	r3, [r3, #4]
	str	r3, [r10, #4]!
	ldr	r0, [ip, #4]!
	ldr	r2, [r0, #16]
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #24]
	add	r3, r3, #1840
	add	r3, r3, #12
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r0, #16]
	ldr	r3, [r3, #24]
	str	r3, [r9, #4]!
	ldr	r2, [r5, #3068]
	cmp	r2, r1
	bhi	.L642
	ldr	r3, [r5, #3064]
.L641:
	cmp	r3, #0
	beq	.L643
	ldr	r0, [fp, #-116]
	mov	lr, #50
	ldr	r1, [r6, #372]
	ldr	r9, [r4, #3532]
	mul	lr, lr, r0
	add	r1, lr, r1
	add	r1, r1, #3168
	add	r1, r1, #2
	ldr	r1, [r4, r1, asl #2]
	cmp	r9, r1
	blt	.L674
	add	ip, r6, #372
	mov	r0, #0
	b	.L645
.L646:
	ldr	r1, [ip, #4]!
	add	r1, lr, r1
	add	r1, r1, #3168
	add	r1, r1, #2
	ldr	r1, [r4, r1, asl #2]
	cmp	r1, r9
	bgt	.L674
.L645:
	add	r0, r0, #1
	cmp	r0, r3
	bne	.L646
.L643:
	ldr	r1, [r5, #3016]
	cmp	r1, #0
	bne	.L699
	cmp	r2, #0
	beq	.L699
	ldr	r0, [fp, #-116]
	mov	ip, #50
	ldr	r3, [r6, #436]
	ldr	lr, [r4, #3532]
	mul	ip, ip, r0
	add	r3, ip, r3
	add	r3, r3, #3168
	add	r3, r3, #2
	ldr	r3, [r4, r3, asl #2]
	cmp	lr, r3
	blt	.L644
	add	r0, r6, #436
	b	.L647
.L648:
	ldr	r3, [r0, #4]!
	add	r3, ip, r3
	add	r3, r3, #3168
	add	r3, r3, #2
	ldr	r3, [r4, r3, asl #2]
	cmp	r3, lr
	bgt	.L674
.L647:
	add	r1, r1, #1
	cmp	r1, r2
	bne	.L648
.L699:
	mov	r1, #1
.L644:
	strb	r1, [r6, #24]
	ldrb	r3, [r8, #129]	@ zero_extendqisi2
	strb	r3, [r6, #25]
	ldr	r3, [r5, #3012]
	str	r3, [r6, #28]
	ldrb	r2, [r5, #3003]	@ zero_extendqisi2
	strb	r2, [r6, #32]
	ldr	r2, [r5, #3036]
	str	r2, [r6, #36]
	ldr	r2, [r4, #2344]
	cmp	r2, #0
	bne	.L649
	ldr	r9, [r4, #3580]
	ldr	r1, [r4, #204]
	ldr	r0, [r9, #316]
	sub	r2, r1, #1
	mla	r0, r0, r2, r3
	bl	__aeabi_uidiv
	str	r0, [r9, #68]
.L649:
	ldr	r3, [r5, #3016]
	cmp	r3, #0
	bne	.L650
	ldrb	r3, [r5, #3004]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L651
	ldr	r3, [r5, #3040]
	add	r3, r6, r3, lsl #2
	ldr	r9, [r3, #436]
.L652:
	str	r9, [r6, #40]
	ldr	r3, [r5, #3040]
	str	r3, [r6, #48]
	ldrb	r3, [r5, #3004]	@ zero_extendqisi2
	strb	r3, [r6, #52]
	ldr	r3, [r5, #3044]
	str	r3, [r6, #44]
	ldr	r3, [r5, #3072]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #60]
	ldr	r3, [r5, #3076]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #56]
	ldrb	r3, [r5, #3000]	@ zero_extendqisi2
	strb	r3, [r6, #64]
	ldrb	r3, [r5, #3002]	@ zero_extendqisi2
	strb	r3, [r6, #65]
	ldr	r3, [r5, #3064]
	str	r3, [r6, #68]
	ldr	r3, [r5, #3068]
	str	r3, [r6, #72]
	ldr	r3, [r5, #3016]
	str	r3, [r6, #76]
	ldr	r3, [r8, #168]
	str	r3, [r6, #80]
	ldr	r3, [r4, #2400]
	ldr	r0, [r8, #168]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidivmod
	str	r1, [r6, #84]
	ldr	r3, [r4, #2400]
	ldr	r0, [r8, #168]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidiv
	str	r0, [r6, #88]
	mov	r0, r4
	ldr	r1, [r8, #168]
	bl	HEVC_CtbRsAddrToTsAddr
	str	r0, [r6, #92]
	ldr	r3, [r5, #3048]
	str	r3, [r6, #96]
	ldr	r3, [r5, #3052]
	str	r3, [r6, #100]
	ldr	r3, [r5, #3060]
	str	r3, [r6, #104]
	ldr	r3, [r5, #3056]
	str	r3, [r6, #108]
	ldrb	r3, [r5, #2999]	@ zero_extendqisi2
	strb	r3, [r6, #112]
	ldrb	r3, [r5, #2998]	@ zero_extendqisi2
	strb	r3, [r6, #113]
	ldrb	r3, [r5, #3005]	@ zero_extendqisi2
	strb	r3, [r6, #114]
	ldrb	r3, [r5, #3006]	@ zero_extendqisi2
	strb	r3, [r6, #115]
	ldr	r3, [r4, #2404]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L657
	ldr	r2, [r5, #3016]
	cmp	r2, #1
	beq	.L658
.L657:
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L703
.L660:
	ldrb	r3, [r5, #3000]	@ zero_extendqisi2
	cmp	r3, #0
	subne	r3, fp, #44
	addne	r9, r3, r9, lsl #2
	ldreq	r3, [r8, #3316]
	ldrne	r3, [r9, #-64]
	str	r3, [r6, #564]
	ldr	r3, [r4, #2344]
	cmp	r3, #0
	ldreq	r1, [r4, #2388]
	ldreq	r2, [r4, #2408]
	ldreq	r0, [fp, #-120]
	streq	r1, [r2, r0, asl #2]
	streq	r3, [r4, #2388]
	ldrb	r3, [r8, #2065]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L682
	ldr	r3, [r4, #236]
	cmp	r3, #1
	beq	.L704
	add	r1, r4, r3, lsl #3
	ldr	r0, [r6, #92]
	add	r1, r1, #9472
	add	r2, r3, #1184
	add	r2, r2, #4
	sub	r0, r0, #1
	str	r0, [r1, #32]
	sub	r3, r3, #1
	ldr	r1, [r6, #92]
	add	r2, r4, r2, lsl #3
	str	r1, [r2, #4]
.L666:
	ldr	r1, [r8, #1864]
	add	r3, r4, r3, lsl #3
	ldr	r2, [r8, #1860]
	add	r3, r3, #9472
	mla	r2, r1, r2, r2
	add	r2, r2, r1
	str	r2, [r3, #48]
	ldr	r1, [r6, #92]
	sub	r1, r1, #1
	cmp	r1, #36864
	bcs	.L682
	mov	r0, r4
	bl	HEVC_CtbTsAddrToRsAddr
	str	r0, [r6, #568]
.L682:
	ldr	r0, [fp, #-112]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L674:
	mov	r1, #0
	b	.L644
.L650:
	cmp	r3, #1
	movne	r9, #0
	bne	.L652
.L651:
	ldr	r3, [r5, #3040]
	add	r3, r6, r3, lsl #2
	ldr	r9, [r3, #372]
	b	.L652
.L702:
	ldr	r3, .L705
	add	r0, r4, #11136
	add	r0, r0, #52
	movw	r2, #1356
	add	r1, r4, #4224
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #1
	strb	r3, [r4, #11]
	b	.L636
.L703:
	ldr	r3, [r5, #3016]
	cmp	r3, #0
	bne	.L660
.L658:
	ldr	ip, [r5, #3152]
	add	r1, r4, #11456
	ldr	r3, .L705
	add	r1, r1, #24
	ldr	r10, .L705
	mov	r2, #64
	str	ip, [r6, #580]
	add	r0, r6, #588
	ldr	ip, [r5, #3284]
	ldr	r3, [r3, #52]
	str	ip, [r6, #584]
	blx	r3
	add	r1, r4, #11328
	add	r1, r1, #20
	ldr	r3, [r10, #52]
	mov	r2, #64
	add	r0, r6, #716
	blx	r3
	add	r1, r4, #11520
	add	r1, r1, #24
	ldr	r3, [r10, #52]
	mov	r2, #128
	add	r0, r6, #844
	blx	r3
	add	r1, r4, #11648
	add	r0, r6, #1088
	ldr	r3, [r10, #52]
	add	r1, r1, #24
	add	r0, r0, #12
	mov	r2, #128
	blx	r3
	ldr	r3, [r5, #3016]
	cmp	r3, #0
	bne	.L660
	add	r1, r4, #11776
	ldr	r3, [r10, #52]
	add	r1, r1, #24
	mov	r2, #64
	add	r0, r6, #652
	blx	r3
	add	r1, r4, #11392
	ldr	r3, [r10, #52]
	add	r1, r1, #20
	mov	r2, #64
	add	r0, r6, #780
	blx	r3
	add	r1, r4, #11840
	ldr	r3, [r10, #52]
	add	r1, r1, #24
	mov	r2, #128
	add	r0, r6, #972
	blx	r3
	add	r1, r4, #11968
	add	r0, r6, #1216
	ldr	r3, [r10, #52]
	add	r1, r1, #24
	mov	r2, #128
	add	r0, r0, #12
	blx	r3
	b	.L660
.L704:
	ldr	r2, [r6, #92]
	mov	r3, #0
	str	r2, [r5, #1324]
	b	.L666
.L639:
	ldr	r3, [r5, #3068]
	cmp	r3, #0
	bne	.L667
	b	.L699
.L668:
	mvn	r3, #0
	str	r3, [fp, #-112]
	b	.L682
.L701:
	mov	r2, r0
	ldr	r1, .L705+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r3, #0
	str	r3, [fp, #-112]
	b	.L682
.L706:
	.align	2
.L705:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC74
	UNWIND(.fnend)
	.size	HEVC_WriteSliceMsg, .-HEVC_WriteSliceMsg
	.align	2
	.global	HEVC_GetVirAddr
	.type	HEVC_GetVirAddr, %function
HEVC_GetVirAddr:
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
	.size	HEVC_GetVirAddr, .-HEVC_GetVirAddr
	.align	2
	.global	HEVC_GetPhyAddr
	.type	HEVC_GetPhyAddr, %function
HEVC_GetPhyAddr:
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
	.size	HEVC_GetPhyAddr, .-HEVC_GetPhyAddr
	.align	2
	.global	HEVC_CfgVDMReg
	.type	HEVC_CfgVDMReg, %function
HEVC_CfgVDMReg:
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
	ldr	r2, [r0, #3548]
	add	r1, r0, #4096
	mov	r3, r0
	add	ip, r0, #8192
	clz	r2, r2
	mov	r0, #0
	mov	r2, r2, lsr #5
	str	r2, [r1, #3180]
	ldr	r2, [r3, #3552]
	str	r2, [r1, #3172]
	ldr	r3, [r3, #204]
	str	r3, [ip, #232]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_CfgVDMReg, .-HEVC_CfgVDMReg
	.align	2
	.global	HEVC_IsRefForCurrPic
	.type	HEVC_IsRefForCurrPic, %function
HEVC_IsRefForCurrPic:
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
	add	r5, r0, #4096
	mov	r4, r0
	ldr	r2, [r0, #164]
	ldr	r3, [r5, #164]
	cmp	r3, #0
	blt	.L712
	cmp	r3, r2
	bge	.L712
	ldr	r2, [r0, #2380]
	mov	r1, #1888
	mla	r3, r1, r3, r2
	ldr	r2, [r0, #160]
	ldr	r3, [r3, #32]
	cmp	r3, #0
	blt	.L716
	cmp	r3, r2
	bge	.L716
	ldr	r2, [r0, #2376]
	movw	r0, #12660
	ldr	ip, [r5, #1060]
	mov	r1, #1
	ldr	r10, [r5, #1064]
	mla	r2, r0, r3, r2
	ldr	r6, [r5, #1068]
	add	lr, r10, ip
	cmp	lr, r6
	mov	r3, lr
	ldr	r8, [r2, #116]
	mov	r8, r1, asl r8
	bcs	.L727
	cmp	lr, #15
	bgt	.L719
	add	r2, lr, #1312
	ldr	r7, [r4, #3532]
	add	r2, r2, #1
	sub	r8, r8, #1
	and	r9, r8, r7
	str	ip, [fp, #-48]
	add	r2, r4, r2, lsl #2
	b	.L721
.L738:
	cmp	r6, r3
	bls	.L737
	cmp	r3, #16
	beq	.L719
.L721:
	ldr	r1, [r2, #4]!
	mov	r0, r7
	add	r3, r3, #1
	ldr	ip, [r2, #-944]
	cmp	ip, #0
	andeq	r1, r1, r8
	moveq	r0, r9
	cmp	r0, r1
	bne	.L738
	ldr	ip, [fp, #-48]
	mov	r6, #1
.L718:
	cmp	lr, #0
	beq	.L714
	ldr	r0, [r5, #140]
	ldr	r3, [r5, #1092]
	ldr	r2, [r4, #3532]
	add	r3, r0, r3
	cmp	r2, r3
	beq	.L731
	add	r4, r4, #5184
	mov	r1, #0
	add	r4, r4, #4
	b	.L724
.L725:
	ldr	r3, [r4, #4]!
	add	r3, r0, r3
	cmp	r3, r2
	beq	.L731
.L724:
	add	r1, r1, #1
	cmp	r1, lr
	beq	.L714
	cmp	r1, #17
	bne	.L725
	mov	r3, r1
	str	r1, [sp]
	str	r10, [sp, #8]
	movw	r2, #9007
	str	ip, [sp, #4]
	mov	r0, #0
	ldr	r1, .L739
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L716:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8958
	ldr	r1, .L739+4
	mov	r6, r0
	bl	dprint_vfmw
.L714:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L712:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8946
	ldr	r1, .L739+8
	mov	r6, r0
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L719:
	str	r6, [sp, #4]
	mov	r1, #16
	mov	r0, #0
	str	r1, [sp]
	movw	r2, #8978
	ldr	r1, .L739+12
	mov	r6, r0
	bl	dprint_vfmw
	ldr	ip, [r5, #1060]
	ldr	r10, [r5, #1064]
	add	lr, r10, ip
	b	.L718
.L737:
	ldr	ip, [fp, #-48]
	mov	r6, #0
	b	.L718
.L731:
	mov	r6, #1
	b	.L714
.L727:
	mov	r6, #0
	b	.L718
.L740:
	.align	2
.L739:
	.word	.LC78
	.word	.LC76
	.word	.LC75
	.word	.LC77
	UNWIND(.fnend)
	.size	HEVC_IsRefForCurrPic, .-HEVC_IsRefForCurrPic
	.align	2
	.global	HEVC_IsPicVPSRefresh
	.type	HEVC_IsPicVPSRefresh, %function
HEVC_IsPicVPSRefresh:
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
	ldr	r2, [r0, #2396]
	ldr	r3, [r1, #4]
	ldr	r2, [r2, #4]
	cmp	r2, r3
	beq	.L744
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L744:
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsPicVPSRefresh, .-HEVC_IsPicVPSRefresh
	.align	2
	.global	HEVC_UpdatePicVPS
	.type	HEVC_UpdatePicVPS, %function
HEVC_UpdatePicVPS:
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
	mov	r2, #0
	strb	r2, [r1, #2]
	ldr	ip, [r0, #156]
	mov	r4, r0
	ldr	lr, .L746
	mov	r2, #132
	ldr	r0, [r0, #2372]
	mov	r3, ip, asl #7
	add	r3, r3, ip, lsl #2
	ldr	r5, [lr, #52]
	sub	r3, r3, #132
	add	r0, r0, r3
	blx	r5
	ldr	r3, [r4, #156]
	ldr	r1, [r4, #2372]
	mov	r2, r3, asl #7
	add	r3, r2, r3, lsl #2
	sub	r3, r3, #132
	add	r3, r1, r3
	str	r3, [r4, #2396]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L747:
	.align	2
.L746:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_UpdatePicVPS, .-HEVC_UpdatePicVPS
	.align	2
	.global	HEVC_IsPicSPSRefresh
	.type	HEVC_IsPicSPSRefresh, %function
HEVC_IsPicSPSRefresh:
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
	ldr	r2, [r0, #2400]
	ldr	r3, [r1, #56]
	ldr	r2, [r2, #56]
	cmp	r2, r3
	beq	.L751
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L751:
	ldrb	r0, [r1]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsPicSPSRefresh, .-HEVC_IsPicSPSRefresh
	.align	2
	.global	HEVC_UpdatePicSPS
	.type	HEVC_UpdatePicSPS, %function
HEVC_UpdatePicSPS:
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
	mov	r2, #0
	strb	r2, [r1]
	ldr	r3, [r0, #160]
	movw	r5, #12660
	ldr	ip, .L753
	mov	r4, r0
	ldr	r0, [r0, #2376]
	mov	r2, r5
	mul	r3, r5, r3
	ldr	r6, [ip, #52]
	sub	r3, r3, #12608
	sub	r3, r3, #52
	add	r0, r0, r3
	blx	r6
	ldr	r3, [r4, #160]
	ldr	r1, [r4, #2376]
	mul	r3, r5, r3
	sub	r3, r3, #12608
	sub	r3, r3, #52
	add	r3, r1, r3
	str	r3, [r4, #2400]
	ldr	r2, [r3, #56]
	str	r2, [r4, #264]
	ldr	r2, [r3, #64]
	str	r2, [r4, #268]
	ldr	r2, [r3, #68]
	str	r2, [r4, #272]
	ldr	r2, [r3, #128]
	str	r2, [r4, #276]
	ldr	r2, [r3, #88]
	str	r2, [r4, #280]
	ldr	r3, [r3, #96]
	str	r3, [r4, #284]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L754:
	.align	2
.L753:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_UpdatePicSPS, .-HEVC_UpdatePicSPS
	.align	2
	.global	HEVC_IsPicPPSRefresh
	.type	HEVC_IsPicPPSRefresh, %function
HEVC_IsPicPPSRefresh:
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
	ldr	r2, [r0, #2404]
	ldr	r3, [r1, #28]
	ldr	r2, [r2, #28]
	cmp	r2, r3
	beq	.L758
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L758:
	ldrb	r0, [r1, #1]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsPicPPSRefresh, .-HEVC_IsPicPPSRefresh
	.align	2
	.global	HEVC_UpdatePicPPS
	.type	HEVC_UpdatePicPPS, %function
HEVC_UpdatePicPPS:
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
	ldrb	r3, [r2, #13]	@ zero_extendqisi2
	mov	r4, #0
	mov	r5, r2
	cmp	r3, r4
	mov	r6, r0
	mov	r7, r1
	strb	r4, [r2, #1]
	beq	.L760
	ldrb	r3, [r2, #15]	@ zero_extendqisi2
	cmp	r3, r4
	bne	.L778
	ldr	lr, [r2, #68]
	ldr	r3, [r1, #188]
	cmp	lr, #1
	add	r0, r2, lr, lsl #1
	strh	r3, [r0, #170]	@ movhi
	ble	.L772
	add	lr, lr, #42
	add	r2, r2, #86
	add	ip, r5, #170
	add	lr, r5, lr, lsl #1
.L771:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #170]
	rsb	r3, r1, r3
	strh	r3, [r0, #170]	@ movhi
	bne	.L771
.L772:
	ldr	lr, [r5, #72]
	ldr	r3, [r7, #192]
	cmp	lr, #1
	add	r0, r5, lr, lsl #1
	strh	r3, [r0, #210]	@ movhi
	ble	.L767
	add	lr, lr, #62
	add	r2, r5, #126
	add	ip, r5, #210
	add	lr, r5, lr, lsl #1
.L773:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #210]
	rsb	r3, r1, r3
	strh	r3, [r0, #210]	@ movhi
	bne	.L773
	b	.L767
.L760:
	ldr	r3, [r1, #188]
	strh	r3, [r2, #172]	@ movhi
	ldr	r3, [r1, #192]
	strh	r3, [r2, #212]	@ movhi
.L767:
	ldr	r3, [r6, #164]
	mov	r4, #1888
	ldr	ip, .L779
	mov	r1, r5
	ldr	r0, [r6, #2380]
	mov	r2, r4
	mul	r3, r4, r3
	ldr	r5, [ip, #52]
	sub	r3, r3, #1888
	add	r0, r0, r3
	blx	r5
	ldr	r2, [r6, #164]
	ldr	r3, [r6, #2380]
	mul	r4, r4, r2
	sub	r4, r4, #1888
	add	r4, r3, r4
	str	r4, [r6, #2404]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L778:
	ldr	r9, [r2, #68]
	cmp	r9, r4
	addgt	r3, r2, #170
	ble	.L766
.L765:
	ldr	r10, [r7, #188]
	add	r4, r4, #1
	mov	r1, r9
	str	r3, [fp, #-48]
	mul	r0, r10, r4
	bl	__aeabi_uidiv
	mov	r1, r9
	mov	r8, r0
	sub	r0, r4, #1
	mul	r0, r0, r10
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	cmp	r4, r9
	rsb	r0, r0, r8
	strh	r0, [r3, #2]!	@ movhi
	bne	.L765
.L766:
	ldr	r9, [r5, #72]
	cmp	r9, #0
	addgt	r3, r5, #210
	movgt	r4, #0
	ble	.L767
.L768:
	ldr	r10, [r7, #192]
	add	r4, r4, #1
	mov	r1, r9
	str	r3, [fp, #-48]
	mul	r0, r10, r4
	bl	__aeabi_uidiv
	mov	r1, r9
	mov	r8, r0
	sub	r0, r4, #1
	mul	r0, r0, r10
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	cmp	r4, r9
	rsb	r0, r0, r8
	strh	r0, [r3, #2]!	@ movhi
	bne	.L768
	b	.L767
.L780:
	.align	2
.L779:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_UpdatePicPPS, .-HEVC_UpdatePicPPS
	.align	2
	.global	HEVC_InitPicInfo
	.type	HEVC_InitPicInfo, %function
HEVC_InitPicInfo:
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
	add	r5, r0, #4096
	mov	r3, #1
	strb	r3, [r0, #3521]
	mov	r4, r0
	ldr	r1, [r5, #156]
	mvn	r2, #0
	ldr	r3, [r0, #2400]
	mov	r0, #0
	ldr	lr, [r4, #252]
	str	r1, [r4, #3524]
	ldr	ip, [r5, #140]
	str	r2, [r4, #3552]
	ldr	r2, .L795
	str	ip, [r4, #3532]
	ldr	r1, [r3, #64]
	ldr	r2, [r2, lr, asl #2]
	str	r1, [r4, #3540]
	ldr	r1, [r3, #68]
	str	r0, [r4, #3548]
	str	r1, [r4, #3544]
	ldrsb	r1, [r2, #44]
	cmp	r1, #1
	beq	.L794
.L782:
	ldr	r2, [r4, #2344]
	cmp	r2, #0
	bne	.L785
	ldr	ip, [r4, #2416]
	add	r1, r4, #4160
	movw	r6, #4176
	mvn	r0, #0
	mov	lr, r1
	ldrd	r2, [ip, #64]
	strd	r2, [r1, #8]
	mvn	r1, #0
	ldrd	r2, [ip, #80]
	strd	r2, [r4, r6]
	ldrd	r2, [ip, #96]
	strd	r2, [lr, #24]
	ldr	r3, [ip, #112]
	str	r3, [r4, #3584]
	ldr	r3, [ip, #116]
	str	r3, [r4, #3588]
	ldr	r3, [ip, #120]
	str	r3, [r4, #3592]
	ldr	r3, [ip, #136]
	str	r3, [r4, #3596]
	ldrb	r3, [ip, #56]	@ zero_extendqisi2
	strb	r3, [r5, #120]
	strd	r0, [ip, #64]
	ldr	r3, [r4, #2400]
.L785:
	ldr	r1, [r3, #64]
	mov	r6, #0
	ldrb	r2, [r4, #3648]	@ zero_extendqisi2
	add	r0, r4, #3584
	str	r1, [r4, #3652]
	ldr	r1, [r3, #68]
	str	r6, [r4, #3636]
	str	r1, [r4, #3656]
	ldr	r1, [r3, #60]
	ldr	ip, [r3, #2084]
	subs	r1, r1, #1
	bfi	r2, ip, #5, #3
	movne	r1, #1
	bfi	r2, r1, #2, #3
	strb	r2, [r4, #3648]
	ldr	r1, [r3, #2068]
	and	r1, r1, #7
	bl	SetAspectRatio
	ldr	r3, [r4, #2344]
	cmp	r3, #1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r2, [r5, #140]
	ldr	r3, [r4, #3580]
	str	r2, [r3, #8]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3648]
	str	r2, [r3, #144]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3636]
	str	r2, [r3, #132]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3688]
	str	r2, [r3, #184]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3684]
	str	r2, [r3, #180]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3652]
	str	r2, [r3, #148]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3656]
	str	r2, [r3, #152]
	ldr	r3, [r4, #3580]
	ldr	r0, [r4, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L787
	ldr	r3, [r4, #3636]
	mov	r1, r6
	ldr	r2, [r0, #4]
	subs	r3, r3, r6
	ldr	r0, [r4, #252]
	movne	r3, #1
	bl	FSP_SetStoreType
.L787:
	ldr	r3, [r4, #2400]
	mov	r6, #0
	ldr	ip, [r4, #3580]
	ldr	r2, [r3, #72]
	str	r2, [r4, #3804]
	ldr	r5, [r3, #76]
	str	r5, [r4, #3808]
	ldr	r1, [r3, #80]
	str	r1, [r4, #3812]
	ldr	lr, [r3, #84]
	str	lr, [r4, #3816]
	ldr	r0, [r3, #64]
	rsb	r2, r2, r0
	rsb	r2, r5, r2
	str	r2, [r4, #3660]
	ldr	r0, [r3, #68]
	rsb	r1, r1, r0
	rsb	r1, lr, r1
	str	r1, [r4, #3664]
	ldr	r1, [r3, #60]
	str	r1, [r4, #3748]
	ldr	r1, [r3, #88]
	str	r1, [r4, #3752]
	ldr	r3, [r3, #96]
	str	r3, [r4, #3756]
	ldr	r3, [ip, #164]
	str	r3, [r4, #3668]
	ldr	r3, [ip, #168]
	str	r3, [r4, #3672]
	str	r2, [ip, #156]
	ldr	r2, [r4, #3664]
	ldr	r3, [r4, #3580]
	str	r2, [r3, #160]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3668]
	str	r2, [r3, #164]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3672]
	str	r2, [r3, #168]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3752]
	str	r2, [r3, #248]
	ldr	r3, [r4, #3580]
	ldr	r2, [r4, #3756]
	str	r2, [r3, #252]
	str	r6, [r4, #3536]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L794:
	ldr	r1, [r2, #160]
	cmp	r1, #1
	bne	.L782
	ldr	r2, [r2, #164]
	cmp	r2, #2
	bne	.L782
	add	r2, r4, #8192
	ldrb	r2, [r2, #2936]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L782
	add	r2, r4, #11136
	mov	r1, r2
	add	r2, r2, #32
	add	r1, r1, #48
	ldrd	r6, [r2, #-8]
	ldrd	r0, [r1, #-8]
	cmp	r7, r1
	cmpeq	r6, r0
	bls	.L783
	subs	r8, r6, r0
	sbc	r9, r7, r1
	cmp	r9, #0
	cmpeq	r8, #16
	bls	.L783
.L784:
	ldr	lr, [r4, #260]
	rsb	ip, lr, ip
	adds	r0, r0, ip
	adc	r1, r1, ip, asr #31
	strd	r0, [r2, #-8]
	b	.L782
.L783:
	cmp	r7, r1
	cmpeq	r6, r0
	bcs	.L782
	subs	r6, r0, r6
	sbc	r7, r1, r7
	cmp	r7, #0
	cmpeq	r6, #16
	bls	.L782
	b	.L784
.L796:
	.align	2
.L795:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	HEVC_InitPicInfo, .-HEVC_InitPicInfo
	.align	2
	.global	HEVC_RepairList
	.type	HEVC_RepairList, %function
HEVC_RepairList:
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
	add	r3, r0, #4096
	mov	r10, r0
	ldr	r3, [r3, #148]
	cmp	r3, #1
	beq	.L814
	cmp	r3, #2
	beq	.L815
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [fp, #-48]
	beq	.L799
	ldr	r2, .L824
	mov	r0, #1
	ldr	r1, .L824+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L814:
	str	r3, [fp, #-48]
.L799:
	add	r7, r10, #2416
	add	r9, r10, #4288
	add	r7, r7, #12
	mov	r8, #0
.L812:
	ldr	r2, [r9, #4]!
	cmp	r2, #0
	beq	.L802
	ldr	r1, [r7]
	cmp	r1, #0
	bne	.L816
	mov	r0, r7
	mov	r3, r1
	b	.L804
.L806:
	ldr	r5, [r0, #4]!
	cmp	r5, #0
	bne	.L822
.L804:
	add	r3, r3, #1
	cmp	r3, r2
	bne	.L806
	mov	r3, #255
	str	r3, [fp, #-52]
.L805:
	ldr	r3, [r10, #2416]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L807
	ldr	r5, [r10, #3580]
	add	r5, r5, #56
.L803:
	mov	r3, r1
	mov	r6, r7
	mov	r4, #0
	b	.L813
.L809:
	ldr	r3, [r6, #4]!
.L813:
	cmp	r3, #0
	beq	.L823
.L808:
	add	r4, r4, #1
	cmp	r2, r4
	bhi	.L809
.L810:
	ldr	r3, [fp, #-48]
	add	r8, r8, #1
	add	r7, r7, #68
	cmp	r8, r3
	bcc	.L812
.L815:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L802:
	ldr	r3, [r10, #2416]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	moveq	r3, #1
	streq	r3, [r9]
	ldreq	r3, [r10, #3580]
	addeq	r3, r3, #56
	streq	r3, [r7]
	b	.L810
.L823:
	ldrsb	r2, [fp, #-52]
	mov	r3, r8
	str	r4, [sp]
	mov	r0, #1
	ldr	r1, .L824+8
	str	r2, [sp, #4]
	ldr	r2, .L824
	bl	dprint_vfmw
	str	r5, [r6]
	ldr	r2, [r9]
	b	.L808
.L822:
	uxtb	r3, r3
	str	r3, [fp, #-52]
	cmp	r3, #255
	bne	.L803
	b	.L805
.L816:
	mov	r3, #0
	mov	r5, r1
	str	r3, [fp, #-52]
	b	.L803
.L807:
	mov	r3, r8
	ldr	r2, .L824
	ldr	r1, .L824+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L825:
	.align	2
.L824:
	.word	.LANCHOR0+284
	.word	.LC79
	.word	.LC81
	.word	.LC80
	UNWIND(.fnend)
	.size	HEVC_RepairList, .-HEVC_RepairList
	.align	2
	.global	HEVC_InitListX
	.type	HEVC_InitListX, %function
HEVC_InitListX:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 144
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #148)
	sub	sp, sp, #148
	subs	r7, r0, #0
	beq	.L862
	ldr	r3, .L894
	mov	r2, #136
	mov	r1, #0
	sub	r0, fp, #180
	ldr	r3, [r3, #48]
	blx	r3
	ldr	lr, [r7, #2612]
	cmp	lr, #0
	beq	.L863
	add	r1, r7, #2672
	mov	r0, #0
	add	r1, r1, #12
	mov	r3, r0
	b	.L830
.L829:
	cmp	r3, lr
	beq	.L828
.L830:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #1]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L829
	ldr	ip, [r2, #60]
	cmp	ip, #0
	bne	.L829
	ldr	ip, [r2, #64]
	cmp	ip, #1
	subeq	ip, fp, #44
	addeq	r2, r2, #56
	addeq	ip, ip, r0, lsl #2
	addeq	r0, r0, #1
	streq	r2, [ip, #-136]
	cmp	r3, lr
	bne	.L830
.L828:
	ldr	r4, [r7, #2616]
	cmp	r4, #0
	beq	.L864
	add	r1, r7, #2752
	mov	ip, r0
	mov	r3, #0
	b	.L833
.L832:
	cmp	r3, r4
	beq	.L890
.L833:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L832
	ldr	lr, [r2, #60]
	cmp	lr, #0
	bne	.L832
	ldr	lr, [r2, #64]
	cmp	lr, #1
	subeq	lr, fp, #44
	addeq	r2, r2, #56
	addeq	lr, lr, ip, lsl #2
	addeq	ip, ip, #1
	streq	r2, [lr, #-136]
	cmp	r3, r4
	bne	.L833
.L890:
	rsb	r4, r0, ip
.L831:
	ldr	r5, [r7, #2608]
	cmp	r5, #0
	beq	.L865
	add	lr, r7, #2816
	mov	r10, ip
	add	lr, lr, #4
	mov	r2, #0
	b	.L836
.L835:
	cmp	r2, r5
	beq	.L891
.L836:
	ldr	r3, [lr, #4]!
	add	r2, r2, #1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L835
	ldr	r1, [r3, #60]
	cmp	r1, #1
	bne	.L835
	ldr	r1, [r3, #64]
	sub	r6, fp, #44
	add	r6, r6, r10, lsl #2
	add	r3, r3, #56
	cmp	r1, #0
	addeq	r10, r10, #1
	streq	r3, [r6, #-136]
	cmp	r2, r5
	bne	.L836
.L891:
	rsb	r5, r0, r10
	rsb	r5, r4, r5
.L834:
	cmp	r10, #0
	beq	.L892
	add	r3, r7, #4096
	str	r3, [fp, #-184]
	ldr	r3, [r3, #148]
	cmp	r3, #0
	str	r3, [fp, #-188]
	beq	.L893
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #204]
	ldr	r5, [r3, #208]
	cmp	r4, #0
	str	r4, [r3, #196]
	str	r5, [r3, #200]
	beq	.L855
.L861:
	ldr	r3, [fp, #-184]
	add	r8, r7, #2416
	add	r8, r8, #8
	mov	r6, #0
	ldrb	r9, [r3, #1224]	@ zero_extendqisi2
.L848:
	cmp	r9, #0
	mov	r1, r10
	mov	r0, r6
	ldrne	r1, [r8, #2900]
	bne	.L847
	bl	__aeabi_uidivmod
.L847:
	sub	r3, fp, #44
	add	r6, r6, #1
	add	r1, r3, r1, lsl #2
	cmp	r4, r6
	ldr	r3, [r1, #-136]
	str	r3, [r8, #4]!
	bhi	.L848
	ldr	r3, [fp, #-188]
	cmp	r3, #0
	bne	.L889
.L849:
	cmp	r5, #0
	beq	.L851
	ldr	r3, [fp, #-184]
	add	r6, r7, #2480
	add	r6, r6, #12
	mov	r4, #0
	ldrb	r8, [r3, #1225]	@ zero_extendqisi2
.L854:
	cmp	r8, #0
	mov	r1, r10
	mov	r0, r4
	ldrne	r1, [r6, #2960]
	bne	.L853
	bl	__aeabi_uidivmod
.L853:
	sub	r3, fp, #44
	add	r4, r4, #1
	add	r1, r3, r1, lsl #2
	cmp	r4, r5
	ldr	r3, [r1, #-68]
	str	r3, [r6, #4]!
	bne	.L854
.L889:
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #196]
	ldr	r5, [r3, #200]
.L850:
	cmp	r4, #16
	bhi	.L859
.L855:
	add	r4, r4, #604
	add	r2, r7, #2480
	add	r4, r4, #2
	add	r2, r2, #12
	add	r4, r7, r4, lsl #2
.L858:
	ldr	r3, [r7, #2428]
	str	r3, [r4, #4]!
	cmp	r4, r2
	bne	.L858
.L859:
	cmp	r5, #16
	bhi	.L857
	add	r5, r5, #620
	add	r2, r7, #2560
	add	r5, r5, #3
	add	r5, r7, r5, lsl #2
.L860:
	ldr	r3, [r7, #2496]
	str	r3, [r5, #4]!
	cmp	r5, r2
	bne	.L860
.L857:
	mov	r0, #0
.L888:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L893:
	cmp	r4, #0
	beq	.L840
	sub	r3, fp, #180
	ldr	r2, [fp, #-188]
	add	lr, r3, r0, lsl #2
	sub	r1, fp, #116
.L841:
	add	r2, r2, #1
	ldr	r3, [lr], #4
	cmp	r2, r4
	str	r3, [r1, #4]!
	bne	.L841
.L840:
	cmp	r0, #0
	beq	.L842
	add	r1, r4, #16
	sub	lr, fp, #180
	mov	r2, #0
	add	r1, lr, r1, lsl #2
.L843:
	add	r2, r2, #1
	ldr	r3, [lr], #4
	cmp	r2, r0
	str	r3, [r1, #4]!
	bne	.L843
	add	r4, r4, r2
.L842:
	cmp	r5, #0
	beq	.L844
	add	r4, r4, #16
	sub	r3, fp, #180
	add	ip, r3, ip, lsl #2
	mov	r2, #0
	add	r4, r3, r4, lsl #2
.L845:
	add	r2, r2, #1
	ldr	r3, [ip], #4
	cmp	r2, r5
	str	r3, [r4, #4]!
	bne	.L845
.L844:
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #204]
	ldr	r5, [r3, #208]
	cmp	r4, #0
	str	r4, [r3, #196]
	str	r5, [r3, #200]
	bne	.L861
	b	.L849
.L892:
	ldr	r3, .L894
	add	r4, r7, #4096
	add	r0, r7, #2416
	mov	r2, #136
	add	r0, r0, #12
	str	r10, [r4, #196]
	ldr	r5, [r3, #48]
	mov	r1, r10
	str	r10, [r4, #200]
	blx	r5
	ldr	r2, [r7, #2416]
	ldr	r2, [r2, #24]
	cmp	r2, #2
	bne	.L857
	mov	r2, #1
	str	r2, [r4, #196]
	ldr	r2, [r7, #3580]
	mov	r0, r10
	add	r3, r2, #56
	str	r3, [r7, #2428]
	b	.L888
.L863:
	mov	r0, lr
	b	.L828
.L864:
	mov	ip, r0
	b	.L831
.L865:
	mov	r10, ip
	b	.L834
.L851:
	ldr	r3, .L894
	add	r1, r7, #2416
	add	r1, r1, #12
	mov	r2, #68
	add	r0, r7, #2496
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #196]
	str	r4, [r3, #200]
	mov	r5, r4
	b	.L850
.L862:
	mvn	r0, #0
	b	.L888
.L895:
	.align	2
.L894:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_InitListX, .-HEVC_InitListX
	.align	2
	.global	HEVC_DecList
	.type	HEVC_DecList, %function
HEVC_DecList:
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
	add	r3, r0, #4096
	mov	r4, r0
	ldr	r2, [r3, #148]
	cmp	r2, #2
	beq	.L901
	bl	HEVC_InitListX
	cmp	r0, #0
	bne	.L902
	mov	r0, r4
	bl	HEVC_RepairList
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L903
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L901:
	mov	r0, #0
	str	r0, [r3, #196]
	str	r0, [r3, #200]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L902:
	ldr	r1, .L903+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L904:
	.align	2
.L903:
	.word	.LC83
	.word	.LC82
	UNWIND(.fnend)
	.size	HEVC_DecList, .-HEVC_DecList
	.align	2
	.global	HEVC_ArrangeMem
	.type	HEVC_ArrangeMem, %function
HEVC_ArrangeMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r2, [r0, #2400]
	movw	r1, #8160
	mov	r4, r0
	ldr	r6, [r2, #188]
	ldr	r5, [r2, #192]
	ldr	r2, [r2, #128]
	mov	r6, r6, asl r2
	mov	r5, r5, asl r2
	sub	r2, r5, #32
	sub	r3, r6, #32
	cmp	r3, r1
	cmpls	r2, r1
	movhi	r1, #1
	movls	r1, #0
	bhi	.L912
	ldr	r3, .L914
	mov	r2, #20
	sub	r0, fp, #48
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #2416]
	str	r6, [fp, #-44]
	str	r5, [fp, #-40]
	ldr	r3, [r3, #28]
	str	r6, [fp, #-36]
	cmp	r3, #24
	str	r5, [fp, #-32]
	beq	.L908
	ldrb	r3, [r4, #2596]	@ zero_extendqisi2
	strb	r3, [fp, #-47]
.L910:
	sub	r1, fp, #48
	ldr	r0, [r4, #252]
	strb	r3, [fp, #-45]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L913
	ldr	r1, [r4, #2416]
	sub	r3, fp, #52
	ldr	r0, [r4, #252]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
.L911:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L908:
	mov	r3, #1
	strb	r3, [fp, #-47]
	b	.L910
.L912:
	str	r5, [sp]
	mov	r3, r6
	ldr	r2, .L914+4
	mov	r0, #0
	ldr	r1, .L914+8
	bl	dprint_vfmw
	mvn	r0, #19
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L913:
	ldr	r2, .L914+4
	mov	r0, #1
	ldr	r1, .L914+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L911
.L915:
	.align	2
.L914:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+300
	.word	.LC84
	.word	.LC85
	UNWIND(.fnend)
	.size	HEVC_ArrangeMem, .-HEVC_ArrangeMem
	.align	2
	.global	HEVC_RemoveApcStore
	.type	HEVC_RemoveApcStore, %function
HEVC_RemoveApcStore:
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
	add	r3, r0, r1, lsl #2
	ldr	ip, [r3, #2620]
	ldr	r2, [ip, #32]
	cmp	r2, #0
	bne	.L919
	ldr	r3, [ip, #24]
	cmp	r3, #15
	bhi	.L916
	add	r3, r0, r3, lsl #2
	add	r1, r0, #12288
	add	r3, r3, #12288
	mov	lr, #16
	str	r2, [r3, #264]
	str	r2, [r3, #328]
	str	r2, [r3, #392]
	ldr	r3, [ip, #20]
	add	r3, r3, #536
	str	r2, [r0, r3, asl #2]
	str	lr, [ip, #24]
	ldr	r3, [r1, #260]
	sub	r3, r3, #1
	str	r3, [r1, #260]
.L916:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L919:
	str	r2, [sp]
	mov	r3, r1
	ldr	r2, .L920
	mov	r0, #1
	ldr	r1, .L920+4
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L921:
	.align	2
.L920:
	.word	.LANCHOR0+316
	.word	.LC86
	UNWIND(.fnend)
	.size	HEVC_RemoveApcStore, .-HEVC_RemoveApcStore
	.align	2
	.global	HEVC_RemoveUnusedApcStore
	.type	HEVC_RemoveUnusedApcStore, %function
HEVC_RemoveUnusedApcStore:
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
	ldr	r2, [r0, #2600]
	mov	r6, r0
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #2608
	mov	r4, #0
	add	r5, r5, #8
	b	.L925
.L924:
	add	r4, r4, #1
	cmp	r4, r2
	bcs	.L928
.L925:
	ldr	r3, [r5, #4]!
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L924
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_RemoveApcStore
	ldr	r2, [r6, #2600]
	add	r4, r4, #1
	cmp	r4, r2
	bcc	.L925
.L928:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_RemoveUnusedApcStore, .-HEVC_RemoveUnusedApcStore
	.align	2
	.global	HEVC_ApplyReferencePictureSet
	.type	HEVC_ApplyReferencePictureSet, %function
HEVC_ApplyReferencePictureSet:
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
	add	r4, r0, #4096
	ldr	r2, [r0, #2380]
	mov	lr, #1888
	ldr	r1, [r4, #164]
	movw	ip, #12660
	ldr	r3, [r0, #2376]
	mov	r9, r0
	mov	r0, #1
	mla	r2, lr, r1, r2
	ldr	r1, [r9, #2600]
	cmp	r1, #0
	ldr	r2, [r2, #32]
	mla	r3, ip, r2, r3
	ldr	r3, [r3, #116]
	mov	r3, r0, asl r3
	str	r3, [fp, #-48]
	beq	.L929
	add	r7, r9, #2608
	add	r3, r9, #5184
	add	r3, r3, #4
	add	r7, r7, #8
	str	r3, [fp, #-52]
	mov	r8, #0
	b	.L946
.L932:
	add	r8, r8, #1
	cmp	r8, r1
	bcs	.L929
.L946:
	ldr	r0, [r7, #4]!
	ldr	r3, [r4, #160]
	ldr	r2, [r0, #32]
	cmp	r2, r3
	bne	.L932
	ldr	r1, [r4, #1060]
	ldr	r3, [r4, #1064]
	ldr	r2, [r4, #1068]
	add	r3, r3, r1
	cmp	r3, r2
	mov	r6, r3
	ldrcs	ip, [r0, #8]
	movcs	r1, #0
	bcs	.L934
	add	r5, r3, #1312
	ldr	r3, [r0, #8]
	add	r5, r5, #2
	mov	r1, #0
	mov	r10, #1
	mov	r2, r3
	mov	r3, r9
	add	r5, r9, r5, lsl #2
	mov	r9, r8
	mov	r8, r3
.L940:
	ldr	ip, [r5, #-944]
	cmp	ip, #0
	ldr	ip, [r0, #60]
	beq	.L935
	cmp	ip, #0
	beq	.L936
	ldr	ip, [r5]
	cmp	ip, r2
	beq	.L968
.L936:
	cmp	r1, #0
	bne	.L951
	ldr	r1, [r5]
	mov	lr, r2
.L948:
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	rsb	r1, r1, lr
	clz	r1, r1
	cmp	ip, #0
	mov	r1, r1, lsr #5
	moveq	r1, #0
	cmp	r1, #0
	bne	.L969
.L951:
	mov	ip, r2
.L939:
	ldr	lr, [r4, #1068]
	add	r6, r6, #1
	add	r5, r5, #4
	mov	r2, ip
	cmp	r6, lr
	bcc	.L940
	mov	r3, r8
	ldr	r2, [r4, #1060]
	mov	r8, r9
	mov	r9, r3
	ldr	r3, [r4, #1064]
	add	r3, r3, r2
.L934:
	cmp	r3, #0
	ldr	lr, [r4, #140]
	ldrne	r6, [fp, #-52]
	movne	r5, #0
	movne	r10, #1
	beq	.L942
.L944:
	ldr	r3, [r0, #60]
	add	r5, r5, #1
	cmp	r3, #0
	bne	.L943
	ldr	r3, [r6]
	add	r3, lr, r3
	cmp	r3, ip
	beq	.L970
.L943:
	ldr	r3, [r4, #1064]
	add	r6, r6, #4
	ldr	r2, [r4, #1060]
	add	r3, r3, r2
	cmp	r5, r3
	bcc	.L944
.L942:
	eor	r1, r1, #1
	cmp	ip, lr
	moveq	ip, #0
	andne	ip, r1, #1
	cmp	ip, #0
	beq	.L967
	mov	r3, #0
	strb	r3, [r0, #1]
	ldr	r3, [r7]
	mov	r2, #0
	str	r2, [r3, #60]
	ldr	r3, [r7]
	ldr	r2, [r3, #52]
	cmp	r2, #1
	beq	.L967
	ldr	r1, [r3, #28]
	mov	r2, #0
	ldr	r0, [r9, #252]
	bl	FSP_SetRef
.L967:
	ldr	r1, [r9, #2600]
	add	r8, r8, #1
	cmp	r8, r1
	bcc	.L946
.L929:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L935:
	cmp	ip, #0
	beq	.L938
	ldr	lr, [r5]
	ldr	r3, [fp, #-48]
	eor	lr, lr, r2
	sub	ip, r3, #1
	tst	lr, ip
	beq	.L968
.L938:
	cmp	r1, #0
	bne	.L951
	ldr	r3, [fp, #-48]
	ldr	ip, [r5]
	sub	r1, r3, #1
	and	lr, r2, r1
	and	r1, r1, ip
	b	.L948
.L969:
	strb	r10, [r0, #1]
	mov	r2, #1
	ldr	r1, [r7]
	str	r10, [r1, #60]
	ldr	r1, [r7]
	str	r10, [r1, #48]
	ldr	r1, [r7]
	ldr	r0, [r8, #252]
	ldr	r1, [r1, #28]
	bl	FSP_SetRef
	ldr	r0, [r7]
	mov	r1, #1
	ldr	ip, [r0, #8]
	b	.L939
.L968:
	strb	r10, [r0, #1]
	mov	r2, #1
	ldr	r1, [r7]
	str	r10, [r1, #48]
	ldr	r1, [r7]
	ldr	r0, [r8, #252]
	ldr	r1, [r1, #28]
	bl	FSP_SetRef
	ldr	r0, [r7]
	mov	r1, #1
	ldr	ip, [r0, #8]
	b	.L939
.L970:
	strb	r10, [r0, #1]
	mov	r2, #1
	ldr	r3, [r7]
	str	r10, [r3, #48]
	ldr	r3, [r7]
	ldr	r0, [r9, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldr	r0, [r7]
	ldr	lr, [r4, #140]
	mov	r1, #1
	ldr	ip, [r0, #8]
	b	.L943
	UNWIND(.fnend)
	.size	HEVC_ApplyReferencePictureSet, .-HEVC_ApplyReferencePictureSet
	.align	2
	.global	HEVC_CheckThatAllRefPicsAreAvailable
	.type	HEVC_CheckThatAllRefPicsAreAvailable, %function
HEVC_CheckThatAllRefPicsAreAvailable:
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
	add	r3, r0, #4096
	ldr	r3, [r3, #156]
	sub	r3, r3, #19
	cmp	r3, #2
	bls	.L972
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_CheckThatAllRefPicsAreAvailable.part.8
.L972:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_CheckThatAllRefPicsAreAvailable, .-HEVC_CheckThatAllRefPicsAreAvailable
	.align	2
	.global	HEVC_SetFrmRepeatCount
	.type	HEVC_SetFrmRepeatCount, %function
HEVC_SetFrmRepeatCount:
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
	ldr	r3, [r0, #2416]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_SetFrmRepeatCount.part.9
	UNWIND(.fnend)
	.size	HEVC_SetFrmRepeatCount, .-HEVC_SetFrmRepeatCount
	.align	2
	.global	HEVC_GetFreeFrameStoreNum
	.type	HEVC_GetFreeFrameStoreNum, %function
HEVC_GetFreeFrameStoreNum:
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
	add	r1, r0, #12736
	add	r4, r0, #27136
	add	r1, r1, #8
	add	r4, r4, #8
	mov	r5, #0
.L980:
	ldr	r3, [r1, #48]
	cmp	r3, #0
	bne	.L976
	cmp	r1, #0
	beq	.L977
	ldr	lr, [r0, #2600]
	cmp	lr, #0
	beq	.L977
	ldr	r2, [r0, #2620]
	cmp	r2, r1
	beq	.L976
	add	r2, r0, #2608
	add	r2, r2, #12
	b	.L978
.L979:
	ldr	ip, [r2, #4]!
	cmp	ip, r1
	beq	.L976
.L978:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L979
.L977:
	add	r5, r5, #1
.L976:
	add	r1, r1, #720
	cmp	r1, r4
	bne	.L980
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetFreeFrameStoreNum, .-HEVC_GetFreeFrameStoreNum
	.align	2
	.global	HEVC_UpdateReflist
	.type	HEVC_UpdateReflist, %function
HEVC_UpdateReflist:
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
	add	r5, r0, #4096
	mov	r7, r0
	ldr	r1, [r5, #1060]
	cmp	r1, #0
	beq	.L1010
	add	r10, r0, #5120
	add	r9, r0, #5184
	mov	r8, #0
	add	r10, r10, #47
	add	r9, r9, #4
	mov	r6, r8
.L996:
	ldrb	r3, [r10, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L992
	ldr	lr, [r7, #2600]
	ldr	ip, [r5, #140]
	ldr	r3, [r9]
	cmp	lr, #0
	add	ip, ip, r3
	beq	.L992
	add	r1, r7, #2608
	mov	r3, #0
	add	r1, r1, #8
	b	.L995
.L993:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L992
.L995:
	ldr	r2, [r1, #4]!
	ldr	r0, [r2, #8]
	cmp	r0, ip
	bne	.L993
	ldr	r4, [r5, #160]
	ldr	r0, [r2, #32]
	cmp	r4, r0
	bne	.L993
	add	r4, r7, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r4, #2620]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1036
.L994:
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r4, #2620]
	mov	r1, #0
	add	r3, r7, r8, lsl #2
	add	r8, r8, #1
	str	r1, [r2, #60]
	ldr	r2, [r4, #2620]
	str	r2, [r3, #2688]
.L992:
	ldr	r1, [r5, #1060]
	add	r6, r6, #1
	add	r9, r9, #4
	cmp	r1, r6
	bhi	.L996
.L991:
	ldr	r2, [r7, #2596]
	str	r8, [r7, #2612]
	cmp	r2, r8
	bls	.L1001
	add	r3, r8, #668
	mov	r0, #0
	add	r3, r3, #3
	add	r3, r7, r3, lsl #2
.L1000:
	add	r8, r8, #1
	str	r0, [r3, #4]!
	cmp	r8, r2
	bne	.L1000
.L1001:
	ldr	r3, [r5, #1064]
	add	r4, r1, r3
	cmp	r4, r6
	movls	r8, #0
	bls	.L999
	add	r9, r6, #1296
	add	r10, r6, #5120
	add	r9, r9, #1
	add	r10, r10, #47
	add	r10, r7, r10
	mov	r8, #0
	add	r9, r7, r9, lsl #2
	str	r8, [fp, #-48]
.L1006:
	ldrb	r3, [r10, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1002
	ldr	ip, [r7, #2600]
	ldr	r0, [r5, #140]
	ldr	r3, [r9]
	cmp	ip, #0
	add	r0, r0, r3
	beq	.L1002
	add	r1, r7, #2608
	mov	r3, #0
	add	r1, r1, #8
	b	.L1005
.L1003:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L1002
.L1005:
	ldr	r2, [r1, #4]!
	ldr	lr, [r2, #8]
	cmp	lr, r0
	bne	.L1003
	ldr	r8, [r5, #160]
	ldr	lr, [r2, #32]
	cmp	r8, lr
	bne	.L1003
	add	r8, r7, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r8, #2620]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1037
.L1004:
	ldr	r1, [fp, #-48]
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r8, #2620]
	add	r3, r7, r1, lsl #2
	add	r1, r1, #1
	str	r1, [fp, #-48]
	mov	r1, #0
	str	r1, [r2, #60]
	ldr	r2, [r8, #2620]
	str	r2, [r3, #2756]
.L1002:
	add	r6, r6, #1
	add	r9, r9, #4
	cmp	r4, r6
	bhi	.L1006
	ldr	r8, [fp, #-48]
	ldr	r2, [r7, #2596]
.L999:
	cmp	r2, r8
	str	r8, [r7, #2616]
	bls	.L990
	add	r1, r8, #688
	mov	r3, #0
	add	r7, r7, r1, lsl #2
.L1008:
	add	r8, r8, #1
	str	r3, [r7, #4]!
	cmp	r8, r2
	bne	.L1008
.L990:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1036:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r7, #252]
	bl	FSP_SetRef
	ldr	r3, [r4, #2620]
	b	.L994
.L1037:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r7, #252]
	bl	FSP_SetRef
	ldr	r3, [r8, #2620]
	b	.L1004
.L1010:
	mov	r8, r1
	mov	r6, r1
	b	.L991
	UNWIND(.fnend)
	.size	HEVC_UpdateReflist, .-HEVC_UpdateReflist
	.align	2
	.global	HEVC_UpdateLTReflist
	.type	HEVC_UpdateLTReflist, %function
HEVC_UpdateLTReflist:
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
	add	r5, r0, #4096
	ldr	r2, [r0, #2380]
	mov	r7, r0
	ldr	r3, [r5, #164]
	mov	r0, #1888
	ldr	ip, [r7, #2376]
	movw	lr, #12660
	mov	r1, #1
	mla	r0, r0, r3, r2
	ldr	r3, [r5, #1060]
	ldr	r2, [r5, #1064]
	add	r2, r3, r2
	ldr	r3, [r5, #1068]
	sub	r2, r2, #1
	ldr	r0, [r0, #32]
	sub	r10, r3, #1
	cmp	r10, r2
	mla	r2, lr, r0, ip
	ldr	r2, [r2, #116]
	mov	r2, r1, asl r2
	ble	.L1049
	add	r9, r3, #1312
	add	r3, r3, #5120
	add	r9, r9, r1
	add	r3, r3, #48
	add	r3, r7, r3
	sub	r4, r2, #1
	add	r9, r7, r9, lsl #2
	mov	r8, #0
	str	r8, [fp, #-52]
	mov	r8, r3
	str	r1, [fp, #-56]
.L1045:
	ldrb	r3, [r8, #-1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1040
	ldrb	r0, [r9, #-944]	@ zero_extendqisi2
	ldr	ip, [r9]
	ldr	lr, [r7, #2600]
	cmp	r0, #0
	andeq	ip, ip, r4
	cmp	lr, #0
	ble	.L1040
	add	r1, r7, #2608
	mov	r3, #0
	add	r1, r1, #8
	str	r7, [fp, #-48]
	b	.L1044
.L1043:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L1056
.L1044:
	ldr	r2, [r1, #4]!
	cmp	r0, #0
	ldr	r6, [r2, #8]
	andeq	r6, r6, r4
	cmp	ip, r6
	bne	.L1043
	ldr	r6, [r5, #160]
	ldr	r7, [r2, #32]
	cmp	r7, r6
	bne	.L1043
	ldr	r7, [fp, #-48]
	mov	ip, #0
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-56]
	add	r3, r7, r3, lsl #2
	strb	r0, [r2, #1]
	add	r2, r7, r1, lsl #2
	add	r1, r1, #1
	str	r1, [fp, #-52]
	ldr	r1, [r3, #2620]
	str	ip, [r1, #64]
	ldr	r1, [r3, #2620]
	str	r0, [r1, #60]
	ldr	r3, [r3, #2620]
	str	r3, [r2, #2824]
.L1040:
	ldr	r3, [r5, #1060]
	sub	r10, r10, #1
	ldr	r2, [r5, #1064]
	sub	r9, r9, #4
	add	r3, r3, r2
	sub	r3, r3, #1
	cmp	r3, r10
	blt	.L1045
	ldr	r8, [fp, #-52]
	mov	r3, r8
.L1039:
	ldr	r2, [r7, #2596]
	str	r3, [r7, #2608]
	cmp	r2, r8
	ble	.L1038
	add	r3, r8, #704
	mov	r1, #0
	add	r3, r3, #1
	add	r3, r7, r3, lsl #2
.L1047:
	add	r8, r8, #1
	str	r1, [r3, #4]!
	cmp	r8, r2
	bne	.L1047
.L1038:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1056:
	ldr	r7, [fp, #-48]
	b	.L1040
.L1049:
	mov	r3, #0
	mov	r8, r3
	b	.L1039
	UNWIND(.fnend)
	.size	HEVC_UpdateLTReflist, .-HEVC_UpdateLTReflist
	.align	2
	.global	HEVC_GetAPC
	.type	HEVC_GetAPC, %function
HEVC_GetAPC:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L1075
	ldr	r7, [r0, #3528]
	mov	r3, #200
	mul	r3, r3, r7
	add	r2, r0, r3
	add	r1, r2, #12544
	ldr	r1, [r1]
	cmp	r1, #0
	beq	.L1060
	movw	r0, #12552
	ldr	r4, [r2, r0]
	cmp	r4, #0
	addne	r3, r3, #12544
	addne	r3, r3, #8
	movne	r4, #0
	addne	r3, r6, r3
	bne	.L1063
	b	.L1061
.L1066:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1061
.L1063:
	add	r4, r4, #1
	cmp	r4, r1
	bne	.L1066
.L1060:
	ldr	r1, .L1076
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L1073:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1061:
	ldr	r1, [r5, #28]
	ldr	r0, [r6, #252]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	beq	.L1064
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L1064
	mov	r2, #50
	mov	r3, #200
	mla	r2, r2, r7, r4
	mov	lr, #1
	mla	r7, r3, r7, r6
	ldr	r1, .L1076+4
	mov	r3, r4
	mov	r0, #13
	add	r6, r6, r2, lsl #2
	add	r7, r7, #12544
	add	r6, r6, #12288
	str	lr, [r6, #264]
	ldr	r2, [ip, #28]
	ldr	r2, [r2, #4]
	str	r2, [r6, #328]
	ldr	r2, [r5, #8]
	str	r2, [r6, #392]
	ldr	r2, [r7, #4]
	add	r2, r2, lr
	str	r2, [r7, #4]
	ldr	r2, [r5, #228]
	bl	dprint_vfmw
	mov	r0, #0
	str	r4, [r5, #24]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1064:
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	mov	r0, #0
	ldr	r2, [r5, #28]
	ldr	r3, [r5, #8]
	stmia	sp, {r1, ip}
	str	r0, [sp, #8]
	ldr	r1, .L1076+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1073
.L1075:
	mov	r0, r5
	movw	r3, #11586
	ldr	r2, .L1076+12
	ldr	r1, .L1076+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1073
.L1077:
	.align	2
.L1076:
	.word	.LC91
	.word	.LC89
	.word	.LC90
	.word	.LC87
	.word	.LC88
	UNWIND(.fnend)
	.size	HEVC_GetAPC, .-HEVC_GetAPC
	.align	2
	.global	HEVC_CheckFrameStore
	.type	HEVC_CheckFrameStore, %function
HEVC_CheckFrameStore:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r4, r1, #0
	beq	.L1088
	ldr	r0, [r0, #252]
	ldr	r1, [r4, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1080
	ldrsb	r2, [r0, #1]
	cmp	r2, #3
	cmpne	r2, #0
	moveq	r0, #1
	movne	r0, #0
	beq	.L1099
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1085
	ldr	r2, [r4, #48]
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1084
	cmp	r3, #1
	beq	.L1084
.L1096:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1099:
	ldr	r3, [r4, #28]
	mov	r0, #13
	str	r2, [sp]
	ldr	r1, .L1100
	ldr	r2, .L1100+4
	bl	dprint_vfmw
.L1082:
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1085
	ldr	r3, [r4, #8]
	mov	r0, #1
	ldr	r2, .L1100+4
	ldr	r1, .L1100+8
	bl	dprint_vfmw
	mvn	r0, #2
	b	.L1096
.L1080:
	ldr	ip, [r4, #28]
	mov	r2, r4
	ldr	r3, [r4, #8]
	mov	r0, #1
	ldr	r1, .L1100+12
	str	ip, [sp, #4]
	ldr	ip, [r4, #52]
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1082
.L1084:
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	mov	r3, r4
	ldr	r2, .L1100+4
	ldr	r1, .L1100+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1096
.L1088:
	mvn	r0, #0
	b	.L1096
.L1085:
	mov	r2, #1
	mov	r3, #2
	strb	r2, [r4, #2]
	mvn	r0, #2
	str	r3, [r4, #52]
	b	.L1096
.L1101:
	.align	2
.L1100:
	.word	.LC92
	.word	.LANCHOR0+336
	.word	.LC94
	.word	.LC93
	.word	.LC95
	UNWIND(.fnend)
	.size	HEVC_CheckFrameStore, .-HEVC_CheckFrameStore
	.align	2
	.global	HEVC_GetImagePara
	.type	HEVC_GetImagePara, %function
HEVC_GetImagePara:
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
	add	r8, r1, #672
	mov	r4, r1
	mvn	r7, #0
	ldrd	r2, [r8, #-8]
	mvn	r6, #0
	ldr	r1, [r1, #12]
	mov	r5, r0
	cmp	r3, r7
	cmpeq	r2, r6
	str	r1, [fp, #-52]
	beq	.L1104
	ldr	ip, [r0, #2600]
	cmp	ip, #0
	beq	.L1104
	add	r10, r0, #2608
	mvn	r3, #0
	mvn	r6, #1
	mvn	r7, #0
	add	r10, r10, #8
	str	r3, [fp, #-48]
	mov	r9, #0
	b	.L1107
.L1141:
	ldr	r1, [r10]
	ldr	ip, [r5, #2600]
	add	r1, r1, #672
	ldrd	r0, [r1, #-8]
	cmp	r1, r7
	cmpeq	r0, r6
	strcc	r9, [fp, #-48]
	movcc	r6, r0
	movcc	r7, r1
.L1106:
	add	r9, r9, #1
	cmp	r9, ip
	bcs	.L1144
.L1107:
	ldr	r1, [r10, #4]!
	cmp	r1, #0
	beq	.L1106
	ldr	r1, [r1, #28]
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1143
	ldrsb	r1, [r0, #1]
	cmp	r1, #3
	cmpne	r1, #0
	bne	.L1141
.L1143:
	ldr	ip, [r5, #2600]
	add	r9, r9, #1
	cmp	r9, ip
	bcc	.L1107
.L1144:
	ldr	r3, [fp, #-48]
	cmn	r3, #1
	beq	.L1104
	ldrd	r2, [r8, #-8]
	cmp	r3, r7
	cmpeq	r2, r6
	bhi	.L1145
.L1104:
	ldrb	r3, [r4, #145]	@ zero_extendqisi2
	ldrb	r2, [r4, #144]	@ zero_extendqisi2
	and	r3, r3, #195
	bfc	r3, #0, #2
	bfc	r2, #0, #2
	strb	r3, [r4, #145]
	strb	r2, [r4, #144]
	ldr	r3, [r5, #144]
	str	r3, [r4, #188]
	ldr	r3, [r5, #2396]
	ldrh	r3, [r3, #124]
	cmp	r3, #1
	moveq	r2, #0
	beq	.L1108
	movw	r2, #257
	cmp	r3, r2
	movne	r2, #1
	bne	.L1108
	ldr	r2, [r5, #2908]
	subs	r2, r2, #1
	movne	r2, #1
.L1108:
	ldr	r3, [r5, #2400]
	ldrb	r3, [r3, #2066]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r1, #3
	beq	.L1109
	ldr	r3, [r4, #40]
	cmp	r3, #1
	cmpne	r3, #11
	moveq	r1, #1
	bne	.L1146
.L1110:
	ldr	r2, [r4, #44]
	clz	r2, r2
	mov	r2, r2, lsr #5
.L1109:
	ldrb	r3, [r4, #145]	@ zero_extendqisi2
	mov	ip, #2
	ldr	r0, [r4, #48]
	bfi	r3, ip, #4, #2
	ldr	lr, [fp, #-52]
	cmp	r0, #0
	bfi	r3, r1, #2, #2
	ldrb	r0, [r4, #144]	@ zero_extendqisi2
	bfi	r3, r2, #0, #2
	ldrb	ip, [r4, #4]	@ zero_extendqisi2
	strb	r3, [r4, #145]
	bfi	r0, lr, #0, #2
	ldrne	r3, [r4, #16]
	ldrb	r1, [r4, #146]	@ zero_extendqisi2
	ldrb	lr, [r4, #3]	@ zero_extendqisi2
	strne	r3, [r4, #232]
	strb	r0, [r4, #144]
	bfi	r1, lr, #1, #1
	str	ip, [r4, #200]
	strb	r1, [r4, #146]
	ldr	r3, [r5, #2416]
	ldr	r1, [r4, #28]
	ldr	r3, [r3, #604]
	str	r3, [r4, #204]
	ldr	r3, [r5, #2416]
	ldr	r3, [r3, #608]
	str	r3, [r4, #208]
	ldr	r3, [r5, #2416]
	ldr	r3, [r3, #612]
	str	r3, [r4, #212]
	ldr	r0, [r5, #252]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L1102
	ldr	r3, .L1147
	mov	r2, #640
	add	r1, r4, #80
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #16
	str	r3, [r5, #296]
	mov	r3, #1
	ldr	r2, [r4, #56]
	strb	r3, [r5, #291]
	cmp	r2, #0
	strb	r3, [r5, #289]
	moveq	r3, #0
	movne	r3, #4
	strb	r3, [r5, #284]
	ldr	r3, [r4, #68]
	str	r3, [r5, #236]
.L1102:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1145:
	ldr	r0, [r5, #252]
	strd	r6, [sp]
	bl	IsPtsRewind
	cmp	r0, #0
	bne	.L1104
	ldrd	r2, [r8, #-8]
	mov	r0, #29
	ldr	r1, .L1147+4
	strd	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	add	r10, r5, r3, lsl #2
	ldrd	r2, [r8, #-8]
	ldr	r1, [r10, #2620]
	add	r1, r1, #672
	strd	r2, [r1, #-8]
	strd	r6, [r8, #-8]
	b	.L1104
.L1146:
	bic	r3, r3, #8
	cmp	r3, #2
	moveq	r1, #2
	movne	r1, #3
	b	.L1110
.L1148:
	.align	2
.L1147:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC96
	UNWIND(.fnend)
	.size	HEVC_GetImagePara, .-HEVC_GetImagePara
	.align	2
	.global	HEVC_CheckOutputImage
	.type	HEVC_CheckOutputImage, %function
HEVC_CheckOutputImage:
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
	cmp	r1, #19
	bhi	.L1151
	mov	r3, #720
	mla	r1, r3, r1, r0
	add	r1, r1, #12736
	ldrb	r0, [r1, #9]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1151:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_CheckOutputImage, .-HEVC_CheckOutputImage
	.align	2
	.global	HEVC_DECRecycleImage
	.type	HEVC_DECRecycleImage, %function
HEVC_DECRecycleImage:
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
	mov	r8, r0
	ldr	r0, [r0, #252]
	mov	r9, r1
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1157
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	addne	r4, r0, #576
	addne	r5, r0, #608
	movne	r6, #0
	movne	r7, #0
	beq	.L1162
.L1156:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1155
	ldr	r0, [r8, #252]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1155:
	cmp	r4, r5
	bne	.L1156
	ldr	r0, [r8, #252]
	mov	r1, r9
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1162:
	ldr	r1, .L1163
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1157:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1164:
	.align	2
.L1163:
	.word	.LC97
	UNWIND(.fnend)
	.size	HEVC_DECRecycleImage, .-HEVC_DECRecycleImage
	.align	2
	.global	HEVC_GetSLHDR1MasteringDisplayInfo
	.type	HEVC_GetSLHDR1MasteringDisplayInfo, %function
HEVC_GetSLHDR1MasteringDisplayInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r1, #572]
	movw	r2, #14999
	cmp	r3, r2
	bhi	.L1169
	sub	r2, r3, #8448
	movw	ip, #4749
	sub	r2, r2, #52
	cmp	r2, ip
	movls	r3, #1
	strlsb	r3, [r0, #3]
	bls	.L1167
	sub	r3, r3, #13248
	movw	r2, #1749
	sub	r3, r3, #2
	cmp	r3, r2
	bhi	.L1169
	mov	r3, #2
	strb	r3, [r0, #3]
.L1167:
	ldr	r3, [r1, #604]
	movw	r2, #56963
	movt	r2, 17179
	mov	ip, #50
	add	r3, r3, #249856
	movw	lr, #10000
	add	r3, r3, #144
	movw	r4, #2063
	movt	r4, 1526
	umull	r2, r3, r3, r2
	mov	r3, r3, lsr #17
	mul	r3, ip, r3
	cmp	r3, lr
	movcs	r3, lr
	strh	r3, [r0, #4]	@ movhi
	ldr	r3, [r1, #608]
	cmp	r3, r4
	movwls	r2, #5977
	movtls	r2, 53687
	umullls	r2, r3, r3, r2
	ubfxls	lr, r3, #13, #16
	strh	lr, [r0, #6]	@ movhi
	ldmfd	sp, {r4, fp, sp, pc}
.L1169:
	mov	r3, #0
	strb	r3, [r0, #3]
	b	.L1167
	UNWIND(.fnend)
	.size	HEVC_GetSLHDR1MasteringDisplayInfo, .-HEVC_GetSLHDR1MasteringDisplayInfo
	.align	2
	.global	HEVC_PrintSLHDR1Info
	.type	HEVC_PrintSLHDR1Info, %function
HEVC_PrintSLHDR1Info:
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
	ldr	r1, .L1191
	mov	r4, r0
	ldrb	r2, [r0]	@ zero_extendqisi2
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	ldr	r1, .L1191+4
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r1, .L1191+8
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	ldr	r1, .L1191+12
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #4]
	ldr	r1, .L1191+16
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #6]
	ldr	r1, .L1191+20
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	ldr	r1, .L1191+24
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #9]	@ zero_extendqisi2
	ldr	r1, .L1191+28
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r5, [r4, #1]	@ zero_extendqisi2
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	mov	r0, #32
	cmp	r5, #0
	bne	.L1173
	ldr	r1, .L1191+32
	bl	dprint_vfmw
	ldrb	r2, [r4, #11]	@ zero_extendqisi2
	ldr	r1, .L1191+36
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	ldr	r1, .L1191+40
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #13]	@ zero_extendqisi2
	ldr	r1, .L1191+44
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #14]	@ zero_extendqisi2
	ldr	r1, .L1191+48
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #15]	@ zero_extendqisi2
	ldr	r1, .L1191+52
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #15
	addne	r6, r4, #26
	beq	.L1178
.L1177:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1191+56
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1191+60
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1177
.L1178:
	ldrb	r2, [r4, #38]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1191+64
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #38
	addne	r6, r4, #45
	movne	r5, #0
	beq	.L1179
.L1180:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1191+68
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1191+72
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1180
.L1179:
	movw	r2, #290
	ldr	r1, .L1191+76
	mov	r0, #32
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1173:
	ldr	r1, .L1191+80
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #10
	addne	r6, r4, #78
	movne	r5, #0
	beq	.L1185
.L1184:
	mov	r2, r5
	ldrh	r3, [r7, #2]!
	ldr	r1, .L1191+84
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r3, [r6, #2]!
	mov	r2, r5
	ldr	r1, .L1191+88
	mov	r0, #32
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1184
.L1185:
	ldrb	r2, [r4, #148]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1191+92
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #148
	addne	r6, r4, #216
	movne	r5, #0
	beq	.L1183
.L1186:
	mov	r3, r5
	ldrh	r2, [r7, #2]!
	ldr	r1, .L1191+96
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrh	r2, [r6, #2]!
	mov	r0, #32
	ldr	r1, .L1191+100
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1186
.L1183:
	movw	r3, #286
	ldr	r1, .L1191+104
	ldrh	r2, [r4, r3]
	add	r4, r4, #288
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r1, .L1191+108
	ldrh	r2, [r4]
	mov	r0, #32
	bl	dprint_vfmw
	b	.L1179
.L1192:
	.align	2
.L1191:
	.word	.LC98
	.word	.LC99
	.word	.LC100
	.word	.LC101
	.word	.LC102
	.word	.LC103
	.word	.LC104
	.word	.LC105
	.word	.LC106
	.word	.LC107
	.word	.LC108
	.word	.LC109
	.word	.LC110
	.word	.LC111
	.word	.LC113
	.word	.LC114
	.word	.LC112
	.word	.LC115
	.word	.LC116
	.word	.LC125
	.word	.LC117
	.word	.LC119
	.word	.LC120
	.word	.LC118
	.word	.LC123
	.word	.LC124
	.word	.LC121
	.word	.LC122
	UNWIND(.fnend)
	.size	HEVC_PrintSLHDR1Info, .-HEVC_PrintSLHDR1Info
	.align	2
	.global	HEVC_GetSLHDR1Info
	.type	HEVC_GetSLHDR1Info, %function
HEVC_GetSLHDR1Info:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 296
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #312)
	sub	sp, sp, #312
	mov	r4, r2
	mov	r6, r1
	movw	r2, #290
	mov	r1, #0
	mov	r5, r0
	sub	r0, fp, #320
	bl	memset
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	ldrb	r2, [r4, #56]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r1, [r4, #568]	@ zero_extendqisi2
	beq	.L1233
	cmp	r2, #0
	bne	.L1235
.L1233:
	ldrb	ip, [r4, #59]	@ zero_extendqisi2
	ldrb	r0, [r4, #128]	@ zero_extendqisi2
.L1195:
	str	r0, [sp, #12]
	mov	r0, #22
	str	r1, [sp, #4]
	str	r2, [sp]
	str	ip, [sp, #8]
	ldr	r2, .L1238
	ldr	r1, .L1238+4
	bl	dprint_vfmw
	mov	r3, #0
	strb	r3, [r5, #458]
.L1193:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1235:
	cmp	r1, #0
	beq	.L1233
	ldrb	r0, [r4, #59]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1198
	ldrb	r0, [r4, #128]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1236
.L1198:
	mov	r3, #1
	strb	r3, [r5, #458]
	ldr	r0, [r6, #24]
	ldrb	r1, [r4, #57]	@ zero_extendqisi2
	ldrb	r2, [r4, #58]	@ zero_extendqisi2
	cmp	r0, #9
	strb	r1, [fp, #-320]
	strb	r2, [fp, #-319]
	bne	.L1200
	ldr	r2, [r6, #32]
	cmp	r2, #9
	streqb	r3, [fp, #-312]
.L1200:
	ldrb	r3, [r4, #60]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1201
	ldrb	r2, [r4, #129]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1201
	cmp	r2, #9
	cmpne	r3, #9
	ldrneb	r3, [fp, #-312]	@ zero_extendqisi2
	moveq	r3, #1
	strb	r3, [fp, #-318]
.L1201:
	mov	r1, r4
	sub	r0, fp, #320
	bl	HEVC_GetSLHDR1MasteringDisplayInfo
	ldrb	r3, [fp, #-318]	@ zero_extendqisi2
	ldrb	r2, [fp, #-312]	@ zero_extendqisi2
	cmp	r2, r3
	ldreqb	r3, [fp, #-317]	@ zero_extendqisi2
	movne	r3, #0
	strb	r3, [fp, #-311]
	ldrb	r3, [fp, #-319]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1205
	ldrb	r2, [r4, #61]	@ zero_extendqisi2
	ldrb	r7, [r4, #66]	@ zero_extendqisi2
	ldrb	ip, [r4, #62]	@ zero_extendqisi2
	ldrb	r0, [r4, #63]	@ zero_extendqisi2
	cmp	r7, #0
	ldrb	r1, [r4, #64]	@ zero_extendqisi2
	strb	r2, [fp, #-310]
	ldrb	r2, [r4, #65]	@ zero_extendqisi2
	strb	r7, [fp, #-305]
	strb	ip, [fp, #-309]
	strb	r0, [fp, #-308]
	strb	r1, [fp, #-307]
	strb	r2, [fp, #-306]
	beq	.L1210
	sub	r2, fp, #320
	add	ip, r4, #66
	add	r0, r2, #15
	add	r1, r4, #81
	add	r2, r2, #26
.L1209:
	add	r3, r3, #1
	ldrb	r6, [ip, #1]!	@ zero_extendqisi2
	ldrb	lr, [r1, #1]!	@ zero_extendqisi2
	cmp	r3, r7
	strb	r6, [r0, #1]!
	strb	lr, [r2, #1]!
	bne	.L1209
.L1210:
	ldrb	r6, [r4, #97]	@ zero_extendqisi2
	cmp	r6, #0
	strb	r6, [fp, #-282]
	beq	.L1208
	sub	r1, fp, #280
	sub	r2, fp, #272
	add	r0, r4, #97
	sub	r1, r1, #2
	add	r4, r4, #112
	sub	r2, r2, #3
	mov	r3, #0
.L1213:
	add	r3, r3, #1
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	ldrb	ip, [r4, #1]!	@ zero_extendqisi2
	cmp	r3, r6
	strb	lr, [r1, #1]!
	strb	ip, [r2, #1]!
	bne	.L1213
.L1208:
	ldr	r3, [r5, #464]
	cmp	r3, #0
	bne	.L1237
	ldr	r2, .L1238
	mov	r0, #1
	ldr	r1, .L1238+8
	bl	dprint_vfmw
	b	.L1193
.L1205:
	ldrb	r7, [r4, #168]	@ zero_extendqisi2
	ldr	r2, [r4, #136]
	add	r7, r7, #1
	ldr	r3, [r4, #140]
	uxtb	r7, r7
	strh	r2, [fp, #-34]	@ movhi
	cmp	r7, #0
	strb	r7, [fp, #-310]
	strh	r3, [fp, #-32]	@ movhi
	beq	.L1217
	sub	r3, fp, #320
	add	ip, r4, #170
	add	r1, r4, #368
	sub	r2, fp, #242
	add	r0, r3, #10
	mov	r3, #0
.L1216:
	add	r3, r3, #1
	ldrh	r6, [ip, #2]!
	ldrh	lr, [r1, #2]!
	cmp	r3, r7
	strh	r6, [r0, #2]!	@ movhi
	strh	lr, [r2, #2]!	@ movhi
	bcc	.L1216
.L1217:
	ldrb	r6, [r4, #169]	@ zero_extendqisi2
	add	r6, r6, #1
	uxtb	r6, r6
	strb	r6, [fp, #-172]
	cmp	r6, #0
	beq	.L1208
	add	r2, r4, #432
	sub	r0, fp, #172
	add	r4, r4, #236
	add	r2, r2, #2
	sub	r1, fp, #104
	mov	r3, #0
.L1218:
	add	r3, r3, #1
	ldrh	lr, [r4, #2]!
	ldrh	ip, [r2, #2]!
	cmp	r3, r6
	strh	lr, [r0, #2]!	@ movhi
	strh	ip, [r1, #2]!	@ movhi
	bcc	.L1218
	b	.L1208
.L1237:
	ldr	r3, .L1238+12
	sub	r1, fp, #320
	movw	r2, #290
	ldr	r0, [r5, #472]
	ldr	r3, [r3, #52]
	blx	r3
	movw	r3, #290
	str	r3, [r5, #460]
	b	.L1193
.L1236:
	mov	ip, r0
	b	.L1195
.L1239:
	.align	2
.L1238:
	.word	.LANCHOR0+360
	.word	.LC126
	.word	.LC127
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_GetSLHDR1Info, .-HEVC_GetSLHDR1Info
	.align	2
	.global	HEVC_ConvertHDRInfo
	.type	HEVC_ConvertHDRInfo, %function
HEVC_ConvertHDRInfo:
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
	ldrb	r4, [r1]	@ zero_extendqisi2
	mov	r3, r0
	mov	r0, r2
	add	lr, r3, #484
	add	lr, lr, #2
	mov	ip, r2
	strb	r4, [r3, #480]
	add	r4, r3, #492
	ldr	r6, [r1, #24]
	add	r5, r2, #580
	mov	r2, #0
	strb	r6, [r3, #481]
	ldr	r6, [r1, #32]
	strb	r6, [r3, #482]
	ldr	r6, [r1, #28]
	str	r6, [r3, #484]
	ldrb	r6, [r0, #568]!	@ zero_extendqisi2
	strb	r6, [r3, #456]
.L1241:
	ldr	r6, [r0, #4]!
	add	r2, r2, #1
	cmp	r2, #3
	strh	r6, [lr, #2]!	@ movhi
	ldr	r6, [r5, #4]!
	strh	r6, [r4, #2]!	@ movhi
	bne	.L1241
	ldr	r0, [ip, #596]
	add	lr, r3, #456
	movw	r5, #614
	add	r4, ip, #616
	mov	r2, ip
	strh	r0, [lr, #44]	@ movhi
	mov	r0, r3
	ldr	r6, [ip, #600]
	strh	r6, [lr, #46]	@ movhi
	ldr	lr, [ip, #604]
	str	lr, [r3, #504]
	ldr	lr, [ip, #608]
	str	lr, [r3, #508]
	ldrb	lr, [ip, #612]	@ zero_extendqisi2
	strb	lr, [r3, #457]
	ldrh	lr, [ip, r5]
	str	lr, [r3, #512]
	ldrh	lr, [r4]
	str	lr, [r3, #516]
	ldrb	ip, [ip, #618]	@ zero_extendqisi2
	strb	ip, [r3, #520]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	HEVC_GetSLHDR1Info
	UNWIND(.fnend)
	.size	HEVC_ConvertHDRInfo, .-HEVC_ConvertHDRInfo
	.align	2
	.global	HEVC_AllocFrameStore
	.type	HEVC_AllocFrameStore, %function
HEVC_AllocFrameStore:
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
	add	r2, r0, #4096
	ldr	r3, [r0, #2380]
	mov	lr, #1888
	ldr	ip, [r0, #2376]
	ldr	r2, [r2, #164]
	movw	r5, #12660
	mov	r6, r0
	add	r0, r0, #12736
	mov	r1, #0
	add	r0, r0, #8
	mla	r3, lr, r2, r3
	mov	lr, r1
	ldr	r3, [r3, #32]
	strb	r1, [r6, #3521]
	mla	r5, r5, r3, ip
.L1248:
	ldr	r3, [r0, #48]
	cmp	r3, #0
	bne	.L1244
	cmp	r0, #0
	beq	.L1255
	ldr	ip, [r6, #2600]
	cmp	ip, #0
	beq	.L1255
	ldr	r2, [r6, #2620]
	cmp	r2, r0
	beq	.L1244
	add	r2, r6, #2608
	add	r2, r2, #12
	b	.L1246
.L1247:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	beq	.L1244
.L1246:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1247
.L1255:
	mov	r7, #720
	add	r9, r6, #3584
	mla	r7, r7, lr, r6
	mov	r4, r0
	mov	r3, #1
	mov	r2, #101
	strb	r3, [r6, #3521]
	mov	r0, r9
	add	r1, r7, #12800
	str	r2, [r6, #3560]
	add	r1, r1, #24
	mov	r2, #640
	bl	memcpy
	add	r3, r7, #12736
	movw	r2, #12760
	str	r4, [r6, #3580]
	mov	r8, #0
	str	r8, [r6, #3736]
	str	r8, [r7, r2]
	strb	r8, [r3, #10]
	strb	r8, [r4]
	ldr	r3, [r6, #3580]
	str	r8, [r3, #60]
	ldr	r3, [r6, #3580]
	str	r8, [r3, #64]
	ldr	r3, [r6, #3580]
	str	r8, [r3, #52]
	ldrb	r1, [r6, #3521]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1252
	ldr	r0, [r6, #252]
	bl	FSP_NewLogicFs
	mov	r7, r0
	mov	r1, r0
	ldr	r0, [r6, #252]
	bl	FSP_GetLogicFs
	mvn	r3, r7
	mov	r3, r3, lsr #31
	cmp	r0, #0
	mov	r4, r0
	moveq	r3, #0
	cmp	r3, #0
	beq	.L1250
	add	r1, r5, #2064
	add	r2, r6, #2896
	bl	HEVC_ConvertHDRInfo
	ldr	r3, [r6, #2416]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1259
.L1251:
	ldr	r5, .L1260
	add	r1, r4, #40
	ldr	r0, [r6, #3580]
	mov	r2, #640
	ldr	r3, [r5, #52]
	add	r0, r0, #80
	blx	r3
	ldr	r1, [r6, #3580]
	ldr	r3, [r5, #52]
	mov	r0, r9
	add	r1, r1, #80
	mov	r2, #640
	blx	r3
	ldr	r3, [r6, #3580]
	mov	r0, #0
	str	r7, [r3, #28]
	ldrsb	r3, [r4, #4]
	str	r3, [r6, #3556]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1244:
	add	lr, lr, #1
	add	r0, r0, #720
	cmp	lr, #20
	bne	.L1248
.L1252:
	ldr	r1, .L1260+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1259:
	ldr	r1, [r6, #2400]
	ldr	r5, [r4, #152]
	ldr	r3, [r4, #76]
	ldr	r2, [r1, #68]
	ldr	r1, [r1, #64]
	str	r8, [r4, #280]
	mul	r5, r5, r2
	str	r2, [r4, #112]
	str	r1, [r4, #108]
	str	r8, [r4, #284]
	add	r3, r5, r3
	str	r8, [r4, #288]
	str	r3, [r4, #80]
	mov	r0, r3
	str	r8, [r4, #292]
	str	r8, [r4, #296]
	bl	MEM_Phy2Vir
	ldr	r2, [r4, #60]
	ldr	r3, [r4, #156]
	add	r5, r5, r2
	str	r8, [r4, #556]
	str	r5, [r4, #64]
	add	r5, r5, r3
	str	r5, [r4, #72]
	str	r0, [r4, #552]
	b	.L1251
.L1250:
	strb	r3, [r6, #3521]
	mov	r0, r3
	ldr	r1, .L1260+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1261:
	.align	2
.L1260:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC128
	.word	.LC129
	UNWIND(.fnend)
	.size	HEVC_AllocFrameStore, .-HEVC_AllocFrameStore
	.align	2
	.global	HEVC_IsVoFinish
	.type	HEVC_IsVoFinish, %function
HEVC_IsVoFinish:
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
	mov	r5, r0
	ldr	r0, [r0, #252]
	bl	FSP_GetFspType
	cmn	r0, #1
	mov	r4, r0
	movne	r4, #0
	bne	.L1266
	b	.L1269
.L1265:
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1267
	cmp	r4, #32
	beq	.L1270
.L1266:
	mov	r1, r4
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	add	r4, r4, #1
	cmp	r0, #0
	bne	.L1265
	ldr	r1, .L1271
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1269:
	ldr	r1, .L1271+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1267:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1270:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1272:
	.align	2
.L1271:
	.word	.LC131
	.word	.LC130
	UNWIND(.fnend)
	.size	HEVC_IsVoFinish, .-HEVC_IsVoFinish
	.align	2
	.global	HEVC_GetBackPicFromVOQueue
	.type	HEVC_GetBackPicFromVOQueue, %function
HEVC_GetBackPicFromVOQueue:
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
	mov	r8, r0
	add	r0, r0, #5568
	add	r0, r0, #16
	add	r5, r8, #13376
	bl	ResetVoQueue
	add	r9, r8, #27648
	add	r5, r5, #16
	add	r9, r9, #144
	mov	r6, #0
	mov	r7, #0
.L1276:
	sub	r4, r5, #32
	mov	r3, #0
	strb	r3, [r5, #-647]
	str	r3, [r5, #-600]
.L1275:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1274
	ldr	r0, [r8, #252]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1274:
	cmp	r4, r5
	bne	.L1275
	add	r5, r4, #720
	cmp	r5, r9
	bne	.L1276
	ldr	r2, [r8, #184]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r8, r8, #2128
	mov	r3, #0
	add	r8, r8, #12
	mov	r1, r3
.L1278:
	add	r3, r3, #1
	str	r1, [r8, #4]!
	cmp	r3, r2
	bne	.L1278
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetBackPicFromVOQueue, .-HEVC_GetBackPicFromVOQueue
	.align	2
	.global	HEVC_RemoveFrameStoreOutDPB
	.type	HEVC_RemoveFrameStoreOutDPB, %function
HEVC_RemoveFrameStoreOutDPB:
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
	add	r6, r0, r1, lsl #2
	mov	r7, #0
	mov	r4, r1
	mov	r5, r0
	ldr	r3, [r6, #2620]
	str	r7, [r3, #48]
	ldr	r3, [r6, #2620]
	ldr	r0, [r0, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1287
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1288
	ldr	r3, [r6, #2620]
	mov	r2, r7
	ldr	r0, [r5, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
.L1288:
	ldr	r3, [r6, #2620]
	mov	r2, #0
	ldr	r0, [r5, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
.L1287:
	ldr	r1, [r5, #2600]
	sub	r1, r1, #1
	cmp	r4, r1
	addls	r3, r4, #652
	addls	r3, r3, #3
	addls	r3, r5, r3, lsl #2
	bhi	.L1291
.L1290:
	add	r4, r4, #1
	ldr	r2, [r3, #4]!
	cmp	r4, r1
	str	r2, [r3, #-4]
	bls	.L1290
.L1291:
	add	r3, r1, #652
	mov	r2, #0
	add	r3, r3, #2
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	str	r1, [r5, #2600]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_RemoveFrameStoreOutDPB, .-HEVC_RemoveFrameStoreOutDPB
	.align	2
	.global	HEVC_RemoveDummyFrame
	.type	HEVC_RemoveDummyFrame, %function
HEVC_RemoveDummyFrame:
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
	ldr	r1, [r0, #2600]
	mov	r5, r0
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r6, #0
	mov	r4, r6
	mov	r7, r6
	b	.L1303
.L1302:
	add	r4, r4, #1
	cmp	r4, r1
	mov	r6, r4
	bcs	.L1309
.L1303:
	add	r3, r5, r4, lsl #2
	ldr	r3, [r3, #2620]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1302
	mov	r1, r6
	strb	r7, [r3]
	mov	r0, r5
	sub	r4, r4, #1
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	add	r4, r4, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r1, [r5, #2600]
	mov	r6, r4
	cmp	r4, r1
	bcc	.L1303
.L1309:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_RemoveDummyFrame, .-HEVC_RemoveDummyFrame
	.align	2
	.global	HEVC_RemoveUnUsedFrameStore
	.type	HEVC_RemoveUnUsedFrameStore, %function
HEVC_RemoveUnUsedFrameStore:
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
	ldr	r5, [r0, #2600]
	mov	r10, r0
	cmp	r5, #0
	beq	.L1319
	mov	r6, #0
	mvn	r8, #0
	mov	r9, r6
	mov	r4, r6
	b	.L1318
.L1329:
	ldrsb	r2, [r0, #1]
	cmp	r2, #0
	cmpne	r2, #3
	ldr	r2, [r7, #2620]
	bne	.L1314
	ldr	r0, [r2, #52]
	cmp	r0, #1
	beq	.L1314
	str	r8, [r2, #28]
	mov	r3, #1
	ldr	r2, [r7, #2620]
	strb	r1, [r2, #1]
	ldr	r2, [r7, #2620]
	strb	r3, [r2, #2]
	ldr	r2, [r7, #2620]
.L1314:
	ldr	r3, [r2]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	addne	r9, r9, #1
	beq	.L1328
	add	r4, r4, #1
	cmp	r4, r5
	beq	.L1311
.L1318:
	add	r7, r10, r9, lsl #2
	ldr	r0, [r10, #252]
	ldr	r2, [r7, #2620]
	ldr	r1, [r2, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1312
	ldrsb	r1, [r0]
	cmp	r1, #0
	beq	.L1329
	ldr	r2, [r7, #2620]
	b	.L1314
.L1312:
	ldr	r2, [r7, #2620]
	ldr	r1, [r2, #52]
	cmp	r1, #1
	beq	.L1314
	str	r8, [r2, #28]
	mov	r3, #1
	ldr	r2, [r7, #2620]
	strb	r0, [r2, #1]
	ldr	r2, [r7, #2620]
	strb	r3, [r2, #2]
	ldr	r2, [r7, #2620]
	b	.L1314
.L1328:
	mov	r1, r9
	mov	r0, r10
	add	r4, r4, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	cmp	r4, r5
	mov	r6, #1
	bne	.L1318
.L1311:
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1319:
	mov	r6, r5
	b	.L1311
	UNWIND(.fnend)
	.size	HEVC_RemoveUnUsedFrameStore, .-HEVC_RemoveUnUsedFrameStore
	.align	2
	.global	HEVC_SimpleSlideDPB
	.type	HEVC_SimpleSlideDPB, %function
HEVC_SimpleSlideDPB:
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
	add	r3, r0, #12288
	mov	r4, r0
	ldr	r2, [r3, #260]
	ldr	r3, [r3, #256]
	cmp	r2, r3
	bcs	.L1334
	ldr	r3, [r0, #2596]
	ldr	r2, [r0, #2600]
	cmp	r2, r3
	ldmccfd	sp, {r4, r5, fp, sp, pc}
	cmp	r3, #15
	bls	.L1336
.L1334:
	ldr	r3, [r4, #2620]
	mov	r5, #0
	mov	r2, r5
	strb	r5, [r3, #1]
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #252]
	bl	FSP_SetRef
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HEVC_RemoveFrameStoreOutDPB
.L1336:
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L1334
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_SimpleSlideDPB, .-HEVC_SimpleSlideDPB
	.align	2
	.global	HEVC_GetMinPOC
	.type	HEVC_GetMinPOC, %function
HEVC_GetMinPOC:
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
	mov	r6, r2
	mvn	r3, #-2147483648
	mov	r2, #0
	str	r2, [r6]
	str	r3, [r1]
	mov	r4, r1
	ldr	r2, [r0, #2600]
	mov	r5, r0
	ldr	r3, [r0, #2596]
	cmp	r2, r3
	bhi	.L1344
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1345:
	add	r1, r5, #2608
	mov	r3, #0
	add	r1, r1, #8
.L1341:
	ldr	r2, [r1, #4]!
	ldr	r0, [r4]
	ldr	r2, [r2, #8]
	cmp	r0, r2
	strgt	r2, [r4]
	strgt	r3, [r6]
	add	r3, r3, #1
	ldr	r2, [r5, #2600]
	cmp	r2, r3
	bhi	.L1341
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1344:
	ldr	r1, .L1346
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #2596]
	cmp	r2, #0
	str	r2, [r5, #2600]
	bne	.L1345
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1347:
	.align	2
.L1346:
	.word	.LC132
	UNWIND(.fnend)
	.size	HEVC_GetMinPOC, .-HEVC_GetMinPOC
	.align	2
	.global	HEVC_GetReRangeFlag
	.type	HEVC_GetReRangeFlag, %function
HEVC_GetReRangeFlag:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #4096
	ldr	lr, [r0, #2380]
	mov	r5, #1888
	movw	r4, #12660
	ldr	ip, [r3, #164]
	ldr	r3, [r0, #2376]
	mla	ip, r5, ip, lr
	ldr	lr, [fp, #4]
	ldr	ip, [ip, #32]
	mla	r3, r4, ip, r3
	ldr	ip, [r3, #64]
	ldr	r3, [r3, #68]
	cmp	r1, ip
	cmpeq	lr, #0
	bne	.L1352
	cmp	r2, r3
	beq	.L1353
.L1352:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1353:
	ldr	r3, [r0, #172]
	cmp	r3, #0
	beq	.L1352
	ldr	r3, [r0, #2416]
	ldr	r0, [r3, #936]
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetReRangeFlag, .-HEVC_GetReRangeFlag
	.align	2
	.global	HEVC_CalcStreamBits
	.type	HEVC_CalcStreamBits, %function
HEVC_CalcStreamBits:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0, #2388]
	ldrb	ip, [r4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1365
	mov	r3, #0
	mov	r2, r4
	mov	lr, r3
.L1356:
	add	r3, r3, #1
	ldr	r1, [r2, #44]
	cmp	r3, ip
	add	r2, r2, #28
	add	lr, lr, r1
	bne	.L1356
.L1355:
	ldr	r2, [r0, #2368]
	mov	r3, ip, asl #5
	sub	ip, r3, ip, asl #2
	add	r4, r4, ip
	ldr	r3, [r2, #24]
	and	r3, r3, #7
	str	r3, [r4, #56]
	ldr	r2, [r0, #2388]
	ldr	r3, [r0, #2368]
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #48]
	add	r2, r2, ip, lsr #3
	rsb	r2, lr, r2
	str	r2, [r3, #60]
	ldr	r1, [r0, #2388]
	ldr	r3, [r0, #2368]
	ldrb	r2, [r1]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r2, asl #5
	sub	r2, r3, r2, asl #2
	add	r2, r1, r2
	ldr	r3, [r2, #44]
	add	r3, lr, r3
	rsb	r3, ip, r3, lsl #3
	str	r3, [r2, #52]
	ldr	r2, [r0, #2388]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	ldr	r1, [r3, #56]
	and	r2, r2, #3
	add	r2, r1, r2, lsl #3
	str	r2, [r3, #56]
	ldr	r2, [r0, #2388]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #3
	str	r2, [r3, #60]
	ldr	r1, [r0, #2388]
	ldr	r2, [r1, #8]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L1372
	ldrb	ip, [r1]	@ zero_extendqisi2
	add	lr, ip, #1
	cmp	r2, lr
	movhi	r2, #1
	movls	r2, #0
	cmp	lr, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L1358
	add	ip, ip, #2
	mov	lr, #0
.L1359:
	sub	r3, ip, #1
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	str	lr, [r1, #56]
	ldr	r2, [r0, #2388]
	add	r2, r2, r3
	ldr	r1, [r2, #48]
	str	r1, [r2, #60]
	ldr	r2, [r0, #2388]
	add	r2, r2, r3
	ldr	r1, [r2, #44]
	mov	r1, r1, asl #3
	str	r1, [r2, #52]
	ldr	r2, [r0, #2388]
	add	r2, r2, r3
	ldr	r1, [r2, #60]
	ldr	r4, [r2, #56]
	and	r1, r1, #15
	add	r1, r4, r1, lsl #3
	str	r1, [r2, #56]
	ldr	r2, [r0, #2388]
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #15
	str	r2, [r3, #60]
	ldr	r1, [r0, #2388]
	ldr	r3, [r1, #8]
	cmp	ip, #1
	cmpls	ip, r3
	add	ip, ip, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L1359
	sub	r3, r3, #1
.L1358:
	mov	r2, r3, asl #5
	ldr	ip, [r1, #12]
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	ldr	r3, [r1, #52]
	rsb	r3, ip, r3
	str	r3, [r1, #52]
	ldr	r4, [r0, #2388]
	ldrb	r2, [r4]	@ zero_extendqisi2
	ldr	lr, [r4, #8]
	cmp	r2, lr
	ldmcsfd	sp, {r4, fp, sp, pc}
	sxth	r1, r2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r4, r3
.L1363:
	ldr	r1, [r3, #60]
	add	r2, r2, #1
	ldr	ip, [r0, #3552]
	add	r3, r3, #28
	cmp	r1, ip
	strcc	r1, [r0, #3552]
	ldrcc	lr, [r4, #8]
	cmp	lr, r2
	bhi	.L1363
	ldmfd	sp, {r4, fp, sp, pc}
.L1372:
	ldr	r1, .L1373
	mov	r0, #0
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L1365:
	mov	lr, ip
	b	.L1355
.L1374:
	.align	2
.L1373:
	.word	.LC133
	UNWIND(.fnend)
	.size	HEVC_CalcStreamBits, .-HEVC_CalcStreamBits
	.align	2
	.global	HEVC_VpsSpsPpsCheck
	.type	HEVC_VpsSpsPpsCheck, %function
HEVC_VpsSpsPpsCheck:
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
	add	r2, r0, #4096
	ldr	r3, [r0, #164]
	ldr	r2, [r2, #164]
	cmp	r2, r3
	bge	.L1383
	mov	r3, #1888
	ldr	r1, [r0, #2380]
	mul	r3, r3, r2
	add	ip, r1, r3
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1384
	ldr	r2, [ip, #32]
	ldr	r3, [r0, #160]
	cmp	r2, r3
	bge	.L1385
	ldr	r1, [r0, #2376]
	movw	r3, #12660
	mla	r3, r3, r2, r1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1386
	ldr	r2, [r3, #48]
	ldr	r3, [r0, #156]
	cmp	r2, r3
	bcs	.L1387
	ldr	r1, [r0, #2372]
	mov	r3, r2, asl #7
	add	r3, r3, r2, lsl #2
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1388
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1383:
	ldr	r1, .L1389
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1384:
	ldr	r1, .L1389+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1385:
	ldr	r1, .L1389+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1386:
	ldr	r1, .L1389+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1387:
	ldr	r1, .L1389+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1388:
	ldr	r1, .L1389+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1390:
	.align	2
.L1389:
	.word	.LC134
	.word	.LC135
	.word	.LC136
	.word	.LC137
	.word	.LC138
	.word	.LC139
	UNWIND(.fnend)
	.size	HEVC_VpsSpsPpsCheck, .-HEVC_VpsSpsPpsCheck
	.align	2
	.global	HEVC_IsNewPic
	.type	HEVC_IsNewPic, %function
HEVC_IsNewPic:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	add	r1, r0, #4096
	ldr	lr, [r0, #2388]
	ldr	r3, [r1, #160]
	ldr	r2, [lr, #16]
	add	r4, r0, r3, lsl #2
	ldr	ip, [r4, #228]
	cmn	ip, #-2147483647
	beq	.L1432
	sub	r5, r2, #16
	cmp	r2, #21
	cmpne	r5, #2
	bls	.L1429
.L1408:
	cmp	r2, #1
	bls	.L1433
.L1396:
	sub	r2, r2, #19
	cmp	r2, #1
	movls	ip, #-2147483647
	strls	ip, [r4, #228]
.L1429:
	ldr	r2, [r1, #140]
.L1398:
	cmp	ip, r2
	ble	.L1399
	ldr	r5, [lr, #16]
	sub	r6, r5, #8
	cmp	r6, #1
	addhi	r3, r0, r3
	bls	.L1434
.L1401:
	ldrb	ip, [r3, #10]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1402
	ldr	r5, [r4, #232]
	cmp	r5, r2
	ble	.L1402
	ldr	r6, [lr, #16]
	sub	r7, r6, #8
	cmp	r7, #1
	bls	.L1435
.L1402:
	ldrb	ip, [r1, #129]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1403
	ldr	lr, [lr, #16]
	sub	r5, lr, #19
	cmp	r5, #1
	bls	.L1430
	cmp	lr, #21
	beq	.L1430
	sub	lr, lr, #16
	cmp	lr, #2
	strls	r2, [r4, #232]
	movls	ip, #1
	strlsb	ip, [r3, #10]
.L1403:
	ldr	ip, [r0, #236]
	ldrb	r3, [r1, #128]	@ zero_extendqisi2
	cmp	ip, #0
	ldr	r1, [r1, #164]
	beq	.L1407
	ldr	ip, [r0, #208]
	cmp	r1, ip
	movne	r3, #1
.L1407:
	ldr	ip, [r0, #304]
	cmp	ip, r1
	movne	r0, #1
	beq	.L1436
.L1428:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1433:
	ldr	r5, [r1, #148]
	cmp	r5, #2
	bne	.L1396
	cmn	ip, #-2147483647
	bne	.L1429
.L1397:
	ldr	r2, [r1, #140]
	str	r2, [r4, #228]
	ldr	ip, [lr, #16]
	cmp	ip, #1
	bls	.L1437
.L1399:
	add	r3, r0, r3
	ldrb	ip, [r3, #5]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1401
	ldr	r5, [lr, #16]
	sub	r6, r5, #8
	cmp	r6, #1
	bhi	.L1401
	str	r2, [sp]
	movw	r3, #12994
	str	r5, [sp, #8]
	mov	r0, #1
	str	ip, [sp, #4]
	ldr	r2, .L1438
	ldr	r1, .L1438+4
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1428
.L1432:
	sub	r6, r2, #16
	cmp	r6, #5
	movhi	r7, #0
	movls	r7, #1
	cmp	r2, #1
	ldrls	r5, [r1, #148]
	movhi	r5, #0
	subls	r5, r5, #2
	clzls	r5, r5
	movls	r5, r5, lsr #5
	orrs	r5, r5, r7
	moveq	r0, #2
	beq	.L1428
	cmp	r2, #21
	cmpne	r6, #2
	bhi	.L1408
	b	.L1397
.L1436:
	ldr	r0, [r0, #260]
	cmp	r0, r2
	moveq	r0, r3
	movne	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1434:
	str	r2, [sp]
	movw	r3, #12987
	str	r5, [sp, #8]
	mov	r0, #1
	str	ip, [sp, #4]
	ldr	r2, .L1438
	ldr	r1, .L1438+8
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1428
.L1430:
	str	r2, [r4, #232]
	strb	ip, [r3, #10]
	b	.L1403
.L1437:
	mov	ip, #1
	str	ip, [r0, #332]
	ldr	ip, [r4, #228]
	b	.L1398
.L1435:
	str	r2, [sp, #4]
	movw	r3, #13003
	str	r6, [sp, #12]
	mov	r0, #1
	str	r5, [sp, #8]
	str	ip, [sp]
	ldr	r2, .L1438
	ldr	r1, .L1438+12
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1428
.L1439:
	.align	2
.L1438:
	.word	.LANCHOR0+380
	.word	.LC141
	.word	.LC140
	.word	.LC142
	UNWIND(.fnend)
	.size	HEVC_IsNewPic, .-HEVC_IsNewPic
	.align	2
	.global	HEVC_ReadByteAlignment
	.type	HEVC_ReadByteAlignment, %function
HEVC_ReadByteAlignment:
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
	mov	r1, #1
	mov	r4, r0
	ldr	r0, [r0, #2368]
	bl	BsGet
	cmp	r0, #0
	beq	.L1445
	ldr	r0, [r4, #2368]
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	beq	.L1444
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r1, .L1446
	mov	r2, r0
	mov	r0, #19
	bl	dprint_vfmw
.L1444:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1445:
	ldr	r1, .L1446+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1447:
	.align	2
.L1446:
	.word	.LC144
	.word	.LC143
	UNWIND(.fnend)
	.size	HEVC_ReadByteAlignment, .-HEVC_ReadByteAlignment
	.align	2
	.global	HEVC_GetRapPicFlag
	.type	HEVC_GetRapPicFlag, %function
HEVC_GetRapPicFlag:
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
	add	r0, r0, #4096
	ldr	r0, [r0, #156]
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetRapPicFlag, .-HEVC_GetRapPicFlag
	.align	2
	.global	HEVC_GetIdrPicFlag
	.type	HEVC_GetIdrPicFlag, %function
HEVC_GetIdrPicFlag:
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
	add	r0, r0, #4096
	ldr	r0, [r0, #156]
	sub	r0, r0, #19
	cmp	r0, #1
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetIdrPicFlag, .-HEVC_GetIdrPicFlag
	.align	2
	.global	HEVC_DecPTL
	.type	HEVC_DecPTL, %function
HEVC_DecPTL:
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
	subs	r8, r2, #0
	mov	r9, r1
	mov	r5, r0
	mov	r6, r3
	moveq	r1, #8
	bne	.L1487
.L1485:
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r6, #0
	str	r0, [r9, #4]
	ble	.L1456
	sub	r3, fp, #84
	sub	r7, fp, #92
	add	r10, r3, r6
	mov	r4, r3
	mov	r9, r7
.L1457:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4], #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r4, r10
	strb	r0, [r9], #1
	bne	.L1457
	cmp	r6, #7
	movle	r4, r6
	ble	.L1461
	b	.L1467
.L1460:
	cmp	r4, #8
	beq	.L1467
.L1461:
	mov	r1, #2
	ldr	r0, [r5, #2368]
	bl	BsGet
	add	r4, r4, #1
	cmp	r0, #0
	beq	.L1460
	ldr	r1, .L1489
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1456:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1467:
	mov	r10, #0
	b	.L1465
.L1464:
	add	r10, r10, #1
	cmp	r6, r10
	ble	.L1456
.L1465:
	cmp	r8, #0
	beq	.L1462
	sub	r3, fp, #84
	ldrb	r3, [r3, r10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1488
.L1462:
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1464
	mov	r1, #8
	ldr	r0, [r5, #2368]
	bl	BsGet
	b	.L1464
.L1488:
	mov	r1, #2
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	mov	r4, #32
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2368]
	bl	BsGet
.L1463:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L1463
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #12
	ldr	r0, [r5, #2368]
	bl	BsGet
	b	.L1462
.L1487:
	mov	r1, #2
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	sub	r4, fp, #77
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2368]
	sub	r7, fp, #45
	bl	BsGet
	mov	r10, r0
.L1452:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	strb	r0, [r4, #1]!
	cmp	r4, r7
	bne	.L1452
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #1]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	sub	r3, r10, #4
	cmp	r3, #3
	bls	.L1453
	ldrb	r3, [fp, #-72]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1453
	ldrb	r3, [fp, #-71]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1453
	ldrb	r3, [fp, #-70]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1453
	ldrb	r3, [fp, #-69]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1453
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #11
	ldr	r0, [r5, #2368]
	bl	BsGet
	b	.L1455
.L1453:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #2
	ldr	r0, [r5, #2368]
	bl	BsGet
.L1455:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldrb	r2, [fp, #-75]	@ zero_extendqisi2
	ldrb	r3, [fp, #-74]	@ zero_extendqisi2
	mov	r1, #8
	str	r10, [r5, #308]
	str	r2, [r5, #312]
	str	r3, [r5, #316]
	b	.L1485
.L1490:
	.align	2
.L1489:
	.word	.LC145
	UNWIND(.fnend)
	.size	HEVC_DecPTL, .-HEVC_DecPTL
	.align	2
	.global	HEVC_SetDefaultScalingList
	.type	HEVC_SetDefaultScalingList, %function
HEVC_SetDefaultScalingList:
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
	ldr	r9, .L1509
	add	r10, r0, #2208
	add	r3, r0, #2224
	add	r10, r10, #12
	mov	r6, #0
	add	r3, r3, #12
	str	r0, [fp, #-52]
	str	r3, [fp, #-48]
.L1492:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L1500
	ldr	r3, [fp, #-52]
	mov	r8, r6, asl #9
	ldr	r7, [fp, #-48]
	sub	r8, r8, r6, asl #7
	add	r5, r3, #608
	mov	r4, #0
.L1498:
	cmp	r6, #0
	add	r0, r5, r8
	mov	r2, #64
	ldr	r3, [r9, #52]
	beq	.L1507
	cmp	r6, #3
	beq	.L1508
	ldr	ip, .L1509+4
	cmp	r4, #2
	ldr	r1, .L1509+8
	movhi	r1, ip
	blx	r3
.L1494:
	mov	r3, #16
	str	r3, [r7, #4]!
	ldr	r3, [r10]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1498
.L1500:
	add	r6, r6, #1
	ldr	r3, [fp, #-48]
	cmp	r6, #4
	add	r3, r3, #24
	str	r3, [fp, #-48]
	bne	.L1492
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1507:
	mov	r2, #16
	ldr	r1, .L1509+12
	mov	r0, r5
	blx	r3
	b	.L1494
.L1508:
	ldr	r0, .L1509+4
	cmp	r4, #0
	ldr	r1, .L1509+8
	mov	r2, #64
	movne	r1, r0
	add	r0, r5, #1152
	blx	r3
	b	.L1494
.L1510:
	.align	2
.L1509:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+396
	.word	.LANCHOR2
	.word	.LANCHOR0+460
	UNWIND(.fnend)
	.size	HEVC_SetDefaultScalingList, .-HEVC_SetDefaultScalingList
	.align	2
	.global	HEVC_CalScalingList
	.type	HEVC_CalScalingList, %function
HEVC_CalScalingList:
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
	add	lr, r2, #84
	mov	ip, r2, asl #3
	sub	r2, ip, r2, asl #1
	mov	r5, #0
	ldr	r7, [r0, lr, asl #2]
	add	r3, r3, r2
	cmp	r7, #64
	mov	r6, r3, asl #4
	movcs	r7, #64
	mov	r8, r7, lsr #2
.L1512:
	cmp	r5, r8
	ldmcsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r7, #0
	beq	.L1512
	add	r3, r5, r6
	ldrb	ip, [r1]	@ zero_extendqisi2
	mov	r4, r1
	mov	r2, #0
	add	r3, r0, r3, lsl #2
	ldr	lr, [r3, #608]
	orr	ip, lr, ip
	str	ip, [r3, #608]
.L1518:
	add	r2, r2, #1
	add	r3, r5, r6
	and	lr, r2, #3
	cmp	r2, r7
	add	r3, r0, r3, lsl #2
	mov	ip, lr, asl #3
	beq	.L1512
	ldrb	r9, [r4, #1]!	@ zero_extendqisi2
	cmp	lr, #3
	ldr	lr, [r3, #608]
	addeq	r5, r5, #1
	orr	ip, lr, r9, asl ip
	str	ip, [r3, #608]
	b	.L1518
	UNWIND(.fnend)
	.size	HEVC_CalScalingList, .-HEVC_CalScalingList
	.align	2
	.global	HEVC_SetScalingList
	.type	HEVC_SetScalingList, %function
HEVC_SetScalingList:
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
	ldr	r3, [r0, #2400]
	mov	r8, r0
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1520
	ldr	r2, [r0, #2404]
	ldrb	r1, [r2, #21]	@ zero_extendqisi2
	cmp	r1, #0
	addne	r3, r2, #256
	strne	r3, [fp, #-48]
	beq	.L1537
.L1522:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1523
	ldr	r10, .L1538
	mov	r2, #1536
	mov	r1, #0
	add	r0, r8, #608
	add	r7, r8, #2208
	mov	r6, #0
	ldr	r3, [r10, #48]
	add	r7, r7, #12
	blx	r3
	ldr	r9, [fp, #-48]
.L1525:
	ldr	r3, [r7, #4]!
	cmp	r3, #0
	movne	r5, r9
	movne	r4, #0
	beq	.L1528
.L1526:
	mov	r3, r4
	mov	r1, r5
	mov	r2, r6
	mov	r0, r8
	bl	HEVC_CalScalingList
	ldr	r3, [r7]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1526
.L1528:
	add	r6, r6, #1
	add	r9, r9, #384
	cmp	r6, #4
	bne	.L1525
	ldr	r2, [fp, #-48]
	add	r0, r8, #2240
	ldr	r3, [r10, #52]
	add	r1, r2, #1536
	mov	r2, #96
	blx	r3
.L1520:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1537:
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	cmp	r2, #0
	addne	r3, r3, #432
	strne	r3, [fp, #-48]
	bne	.L1522
.L1523:
	mov	r0, r8
	bl	HEVC_SetDefaultScalingList
	b	.L1520
.L1539:
	.align	2
.L1538:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_SetScalingList, .-HEVC_SetScalingList
	.align	2
	.global	HEVC_GetScalingListDefaultAddress
	.type	HEVC_GetScalingListDefaultAddress, %function
HEVC_GetScalingListDefaultAddress:
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
	cmp	r0, #3
	ldrls	pc, [pc, r0, asl #2]
	b	.L1541
.L1543:
	.word	.L1547
	.word	.L1545
	.word	.L1545
	.word	.L1546
.L1545:
	ldr	r3, .L1551
	cmp	r1, #2
	add	r0, r3, #64
	movhi	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1547:
	ldr	r0, .L1551+4
	ldmfd	sp, {fp, sp, pc}
.L1546:
	ldr	r3, .L1551
	cmp	r1, #0
	add	r0, r3, #64
	movne	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1541:
	ldr	r1, .L1551+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1552:
	.align	2
.L1551:
	.word	.LANCHOR2+80
	.word	.LANCHOR2+64
	.word	.LC146
	UNWIND(.fnend)
	.size	HEVC_GetScalingListDefaultAddress, .-HEVC_GetScalingListDefaultAddress
	.align	2
	.global	HEVC_DecRefPicListsModification
	.type	HEVC_DecRefPicListsModification, %function
HEVC_DecRefPicListsModification:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r5, r3
	mov	r7, r1
	mov	r8, r2
	moveq	ip, #1
	movne	ip, #0
	cmp	r0, #0
	orreq	ip, ip, #1
	mov	r6, r0
	cmp	ip, #0
	bne	.L1563
	sub	r2, r3, #1
	mov	r4, #1
	movs	r2, r2, asr #1
	beq	.L1555
.L1556:
	movs	r2, r2, asr #1
	add	r4, r4, #1
	bne	.L1556
.L1555:
	mov	r1, #1
	ldr	r0, [r6, #2368]
	bl	BsGet
	cmp	r5, #1
	movls	r10, #0
	movhi	r10, #1
	uxtb	r0, r0
	strb	r0, [r8]
	cmp	r0, #0
	cmpne	r5, #1
	bls	.L1560
	ldr	r3, [r7, #76]
	cmp	r3, #0
	beq	.L1560
	mov	r9, r8
	mov	r5, #0
.L1561:
	mov	r1, r4
	ldr	r0, [r6, #2368]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r9, #4]!
	ldr	r3, [r7, #76]
	cmp	r3, r5
	bhi	.L1561
.L1560:
	ldr	r5, [r7, #20]
	cmp	r5, #0
	beq	.L1578
.L1559:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1578:
	mov	r1, #1
	ldr	r0, [r6, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #1]
	cmp	r0, #0
	moveq	r10, #0
	andne	r10, r10, #1
	cmp	r10, #0
	beq	.L1559
	ldr	r3, [r7, #80]
	cmp	r3, #0
	beq	.L1559
	add	r8, r8, #128
.L1562:
	mov	r1, r4
	ldr	r0, [r6, #2368]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r8, #4]!
	ldr	r3, [r7, #80]
	cmp	r3, r5
	bhi	.L1562
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1563:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_DecRefPicListsModification, .-HEVC_DecRefPicListsModification
	.align	2
	.global	HEVC_MoreRbspData
	.type	HEVC_MoreRbspData, %function
HEVC_MoreRbspData:
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
	ldr	r0, [r0, #2368]
	bl	BsResidBits
	cmp	r0, #0
	ble	.L1581
	ldr	r3, [r4, #2388]
	ldr	r3, [r3, #12]
	add	r3, r3, #3
	cmp	r0, r3
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1581:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_MoreRbspData, .-HEVC_MoreRbspData
	.align	2
	.global	HEVC_More_Rbsp_Data
	.type	HEVC_More_Rbsp_Data, %function
HEVC_More_Rbsp_Data:
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
	ldr	r0, [r0, #2368]
	ldr	r2, [r0, #16]
	ldr	r3, [r0, #24]
	mov	r2, r2, asl #3
	cmp	r2, r3
	bls	.L1585
	mov	r1, #8
	bl	BsShow
	subs	r0, r0, #128
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1585:
	ldr	r1, .L1586
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1587:
	.align	2
.L1586:
	.word	.LC147
	UNWIND(.fnend)
	.size	HEVC_More_Rbsp_Data, .-HEVC_More_Rbsp_Data
	.align	2
	.global	HEVC_FindTrailZeros
	.type	HEVC_FindTrailZeros, %function
HEVC_FindTrailZeros:
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
	mov	ip, #0
	mov	r6, r0
.L1600:
	ldr	r1, [r6, #2388]
	ldr	r0, [r1, #8]
	sub	r0, r0, #1
	mov	r7, r0, asl #2
	mov	r0, r0, asl #5
	rsb	r2, r7, r0
	add	r2, r1, r2
	ldr	r3, [r2, #44]
	ldr	r2, [r2, #40]
	sub	r3, r3, #1
	add	r3, r2, r3
.L1589:
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r5, r7, r0
	add	r2, r1, r5
	cmp	r4, #0
	bne	.L1601
	ldr	lr, [r1, #40]
	add	ip, ip, #1
	cmp	lr, r3
	beq	.L1602
	ldr	lr, [r2, #40]
	cmp	lr, r3
	sub	r3, r3, #1
	bne	.L1589
	ldr	r1, [r2, #64]
	ldr	r0, [r6, #252]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r6, #2388]
	mov	ip, r4
	add	r5, r3, r5
	str	r4, [r5, #40]
	ldr	r2, [r6, #2388]
	ldr	r3, [r2, #8]
	sub	r3, r3, #1
	str	r3, [r2, #8]
	b	.L1600
.L1601:
	tst	r4, #1
	mov	r3, #1
	moveq	r2, r3
	bne	.L1596
.L1597:
	ands	r0, r4, r2, asl r3
	add	r3, r3, #1
	bne	.L1596
	cmp	r3, #8
	bne	.L1597
	ldr	r1, .L1603
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1602:
	ldr	r1, .L1603+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1596:
	mov	r0, #0
	str	r0, [r1, #4]
	ldr	r2, [r6, #2388]
	add	ip, r3, ip, lsl #3
	str	ip, [r2, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1604:
	.align	2
.L1603:
	.word	.LC149
	.word	.LC148
	UNWIND(.fnend)
	.size	HEVC_FindTrailZeros, .-HEVC_FindTrailZeros
	.align	2
	.global	HEVC_FindNaluArraySlot
	.type	HEVC_FindNaluArraySlot, %function
HEVC_FindNaluArraySlot:
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
	ldr	r5, [r0, #168]
	mov	r8, r0
	ldr	r3, [r0, #148]
	cmp	r5, #0
	blt	.L1606
	add	r6, r5, #1
	mov	r0, r3
	mov	r1, r6
	bl	__aeabi_uidivmod
	ldr	r7, [r8, #2412]
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1607
	mov	r4, #0
	b	.L1609
.L1610:
	bl	__aeabi_uidivmod
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1607
.L1609:
	add	r4, r4, #1
	mov	r1, r6
	cmp	r4, r5
	add	r0, r3, r4
	ble	.L1610
.L1606:
	mvn	r0, #0
	str	r3, [r8, #148]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1607:
	cmp	r3, r6
	mov	r0, r3
	str	r3, [r8, #148]
	bcs	.L1620
	rsb	r1, r1, ip
	mov	r3, #1
	add	r7, r7, r1
	str	r3, [r7, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1620:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_FindNaluArraySlot, .-HEVC_FindNaluArraySlot
	.align	2
	.global	HEVC_ReleaseNAL
	.type	HEVC_ReleaseNAL, %function
HEVC_ReleaseNAL:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L1629
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	str	r3, [r5, #32]
	str	r3, [r5, #36]
.L1624:
	ldr	r3, [r4, #40]
	mov	r0, r6
	cmp	r3, #0
	beq	.L1623
	ldr	r1, [r4, #64]
	bl	SM_ReleaseStreamSeg
	ldr	ip, [r4, #44]
	ldr	r3, [r4, #40]
	mov	r0, #7
	ldr	r2, .L1630
	ldr	r1, .L1630+4
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #40]
	str	r3, [r4, #56]
	str	r3, [r4, #44]
.L1623:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L1624
	ldr	r3, .L1630+8
	mov	r0, r5
	mov	r2, #96
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1629:
	mov	r0, r5
	movw	r3, #14320
	ldr	r2, .L1630+12
	ldr	r1, .L1630+16
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1631:
	.align	2
.L1630:
	.word	.LANCHOR0+476
	.word	.LC150
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC87
	.word	.LC88
	UNWIND(.fnend)
	.size	HEVC_ReleaseNAL, .-HEVC_ReleaseNAL
	.align	2
	.global	HEVC_InitDecBuffers
	.type	HEVC_InitDecBuffers, %function
HEVC_InitDecBuffers:
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
	ldr	r3, [r0, #2400]
	mov	r7, r0
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r0, #2596]
	cmp	r3, #17
	bhi	.L1667
.L1633:
	add	r0, r7, #2816
	add	r1, r7, #2672
	add	r2, r7, #2608
	mov	lr, #0
	add	r0, r0, #4
	add	r1, r1, #12
	add	r2, r2, #8
	add	ip, r7, #2752
	mov	r3, lr
	mov	r6, #17
	str	lr, [r7, #2600]
	str	lr, [r7, #2612]
	str	lr, [r7, #2616]
	str	lr, [r7, #2608]
	str	lr, [r7, #2604]
.L1634:
	subs	r6, r6, #1
	str	r3, [r0, #4]!
	str	r3, [r1, #4]!
	str	r3, [ip, #4]!
	str	r3, [r2, #4]!
	bne	.L1634
	add	r4, r7, #12800
	ldr	r9, .L1668
	add	r4, r4, #24
.L1635:
	ldr	r3, [r9, #48]
	mov	r2, #640
	mov	r0, r4
	mov	r1, #0
	blx	r3
	str	r6, [r4, #148]
	add	r6, r6, #1
	mov	r5, #0
	cmp	r6, #20
	sub	r3, r4, #80
	strb	r5, [r4, #-80]
	mov	r2, #20
	str	r3, [r4, #-8]
	mov	r8, #16
	str	r5, [r4, #-32]
	add	r4, r4, #720
	strb	r5, [r4, #-799]
	str	r5, [r4, #-792]
	strb	r5, [r4, #-798]
	str	r5, [r4, #-744]
	str	r2, [r4, #-780]
	str	r8, [r4, #-776]
	ldr	r3, .L1668
	bne	.L1635
	ldr	r3, [r3, #48]
	mov	r2, #200
	mov	r1, r5
	add	r0, r7, #12544
	blx	r3
	add	r2, r7, #2416
	add	r3, r7, #2480
	add	r1, r7, #12288
	add	r2, r2, #8
	add	r3, r3, #12
	mov	r0, r5
	str	r8, [r1, #256]
	str	r5, [r1, #260]
.L1637:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L1637
	add	lr, r7, #4096
	add	ip, r7, #2560
	mov	r0, r1
	str	r1, [lr, #196]
.L1638:
	str	r0, [r3, #4]!
	cmp	r3, ip
	mov	r2, #0
	bne	.L1638
	str	r2, [lr, #200]
	ldr	r0, [r7, #184]
	cmp	r0, r2
	addne	r1, r7, #2128
	movne	r3, r2
	addne	r1, r1, #12
	movne	r2, r3
	beq	.L1643
.L1642:
	add	r3, r3, #1
	str	r2, [r1, #4]!
	cmp	r3, r0
	bne	.L1642
.L1643:
	ldr	r2, [r7, #168]
	cmp	r2, #0
	movne	r4, #0
	movne	r5, r4
	beq	.L1632
.L1648:
	ldr	r3, [r7, #2408]
	mov	r6, r4, asl #2
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L1644
	ldr	r3, [r7, #2388]
	cmp	r1, r3
	beq	.L1644
	ldr	r0, [r7, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r7, #2408]
	str	r5, [r3, r6]
	ldr	r3, [r7, #204]
	ldr	r2, [r7, #236]
	cmp	r3, #0
	subne	r3, r3, #1
	cmp	r2, #0
	str	r3, [r7, #204]
	subne	r2, r2, #1
	ldr	r3, [r7, #176]
	str	r2, [r7, #236]
	ldr	r2, [r7, #168]
	cmp	r3, #2
	subhi	r3, r3, #1
	movls	r3, #2
	str	r3, [r7, #176]
.L1644:
	add	r4, r4, #1
	cmp	r2, r4
	bhi	.L1648
.L1632:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1667:
	mov	r4, #17
	ldr	r2, .L1668+4
	str	r4, [sp]
	mov	r3, r4
	ldr	r1, .L1668+8
	mov	r0, #1
	bl	dprint_vfmw
	str	r4, [r7, #2596]
	b	.L1633
.L1669:
	.align	2
.L1668:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+492
	.word	.LC151
	UNWIND(.fnend)
	.size	HEVC_InitDecBuffers, .-HEVC_InitDecBuffers
	.align	2
	.global	HEVC_EmptyFrmFromDPB
	.type	HEVC_EmptyFrmFromDPB, %function
HEVC_EmptyFrmFromDPB:
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
	subs	r6, r0, #0
	beq	.L1680
	ldr	ip, [r6, #2600]
	add	r8, r6, #2608
	cmp	ip, #0
	addeq	r8, r8, #8
	beq	.L1672
	add	r8, r8, #8
	mov	r3, #0
	mov	lr, #1
	mov	r1, r8
.L1674:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	streqb	lr, [r2, #2]
	ldreq	ip, [r6, #2600]
	cmp	ip, r3
	bhi	.L1674
.L1672:
	mov	r4, r6
	mov	r7, #17
	mov	r5, #0
	mov	r3, #-2147483647
	str	r3, [r6, #212]
.L1679:
	ldr	r3, [r8, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L1675
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1675:
	ldr	r3, [r4, #2688]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1676
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1676:
	ldr	r3, [r4, #2756]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1677
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1677:
	ldr	r3, [r4, #2824]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1678
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1678:
	subs	r7, r7, #1
	str	r5, [r4, #2824]
	str	r5, [r4, #2756]
	add	r4, r4, #4
	str	r5, [r4, #2684]
	str	r5, [r4, #2616]
	bne	.L1679
	mov	r0, r6
	bl	HEVC_InitDecBuffers
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1680:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_EmptyFrmFromDPB, .-HEVC_EmptyFrmFromDPB
	.align	2
	.global	HEVC_CombinePacket
	.type	HEVC_CombinePacket, %function
HEVC_CombinePacket:
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
	ldr	r0, [r0, #2388]
	cmp	r0, #0
	beq	.L1702
	ldr	r3, [r0, #44]
	cmp	r3, #4096
	ldmcsfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L1703
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r3, [r4, #2388]
	ldr	ip, .L1703+4
	mov	r5, #0
	ldr	r2, [r3, #44]
	ldr	r0, [r3, #68]
	ldr	r1, [r3, #40]
	rsb	r0, r2, r0
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #2388]
	mov	r0, #1
	ldr	r2, [r3, #92]
	ldr	r1, [r3, #64]
	str	r2, [r3, #64]
	ldr	r3, [r4, #2388]
	str	r5, [r3, #56]
	ldr	r3, [r4, #2388]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #68]
	rsb	r2, ip, r2
	str	r2, [r3, #40]
	ldr	r3, [r4, #2388]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #76]
	rsb	r2, ip, r2
	str	r2, [r3, #48]
	ldr	r3, [r4, #2388]
	ldr	r2, [r3, #44]
	ldr	ip, [r3, #72]
	add	r2, r2, ip
	str	r2, [r3, #44]
	ldr	r3, [r4, #2388]
	str	r0, [r3, #8]
	ldr	r0, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #2388]
	str	r5, [r3, #68]
	ldr	r3, [r4, #2388]
	str	r5, [r3, #84]
	ldr	r3, [r4, #2388]
	str	r5, [r3, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1702:
	ldr	r1, .L1703+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1704:
	.align	2
.L1703:
	.word	.LC153
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC152
	UNWIND(.fnend)
	.size	HEVC_CombinePacket, .-HEVC_CombinePacket
	.align	2
	.global	HEVC_IsOutDPB
	.type	HEVC_IsOutDPB, %function
HEVC_IsOutDPB:
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
	beq	.L1710
	ldr	ip, [r0, #2600]
	cmp	ip, #0
	beq	.L1710
	ldr	r3, [r0, #2620]
	cmp	r3, r1
	beq	.L1712
	add	r0, r0, #2608
	mov	r3, #0
	add	r0, r0, #12
	b	.L1707
.L1708:
	ldr	r2, [r0, #4]!
	cmp	r2, r1
	beq	.L1712
.L1707:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1708
.L1710:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1712:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsOutDPB, .-HEVC_IsOutDPB
	.align	2
	.global	HEVC_IsNewPicNal
	.type	HEVC_IsNewPicNal, %function
HEVC_IsNewPicNal:
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
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsNewPicNal, .-HEVC_IsNewPicNal
	.align	2
	.global	HEVC_u_v
	.type	HEVC_u_v, %function
HEVC_u_v:
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
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	HEVC_u_v, .-HEVC_u_v
	.align	2
	.global	HEVC_f_v
	.type	HEVC_f_v, %function
HEVC_f_v:
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
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	HEVC_f_v, .-HEVC_f_v
	.align	2
	.global	HEVC_ue_v
	.type	HEVC_ue_v, %function
HEVC_ue_v:
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
	mov	r1, #32
	mov	r5, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	bls	.L1719
	movw	r0, #61166
	movt	r0, 65535
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1719:
	add	r4, r0, #1
	mov	r1, r0
	mov	r0, r5
	bl	BsSkip
	mov	r1, r4
	mov	r0, r5
	bl	BsShow
	mov	r1, r4
	sub	r4, r0, #1
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ue_v, .-HEVC_ue_v
	.align	2
	.global	HEVC_Sei_Tone_Mapping_Info
	.type	HEVC_Sei_Tone_Mapping_Info, %function
HEVC_Sei_Tone_Mapping_Info:
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
	ldr	r1, .L1742
	mov	r4, r0
	ldr	r0, [r0, #2368]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2368]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	beq	.L1739
.L1725:
	mov	r1, #32
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r0, [r4, #2368]
	mov	r1, #32
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1739:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	mov	r6, r0
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r0, #8
	mov	r7, r0
	bhi	.L1740
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r0, #4
	ldrls	pc, [pc, r0, asl #2]
	b	.L1736
.L1724:
	.word	.L1725
	.word	.L1725
	.word	.L1726
	.word	.L1727
	.word	.L1728
.L1727:
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r0, #256
	mov	r8, r0
	bhi	.L1732
	cmp	r0, #0
	beq	.L1736
	add	r6, r6, #7
	add	r7, r7, #7
	bic	r6, r6, #7
	bic	r7, r7, #7
	mov	r5, #0
.L1734:
	mov	r1, r6
	ldr	r0, [r4, #2368]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, r7
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r5, r8
	bne	.L1734
.L1736:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1726:
	mov	r2, #1
	movs	r7, r2, asl r7
	addne	r6, r6, #7
	movne	r5, #0
	bicne	r6, r6, #7
	beq	.L1736
.L1730:
	add	r5, r5, #1
	mov	r1, r6
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r7, r5
	bne	.L1730
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1728:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r0, #255
	beq	.L1741
.L1735:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r0, [r4, #2368]
	mov	r1, #16
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1741:
	mov	r1, #32
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L1735
.L1740:
	mov	r2, r0
	ldr	r1, .L1742+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1732:
	ldr	r1, .L1742+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1743:
	.align	2
.L1742:
	.word	.LC154
	.word	.LC155
	.word	.LC156
	UNWIND(.fnend)
	.size	HEVC_Sei_Tone_Mapping_Info, .-HEVC_Sei_Tone_Mapping_Info
	.align	2
	.global	HEVC_Sei_Frame_Packing_Arrangement
	.type	HEVC_Sei_Frame_Packing_Arrangement, %function
HEVC_Sei_Frame_Packing_Arrangement:
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
	ldr	r1, .L1754
	mov	r4, r0
	ldr	r0, [r0, #2368]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2368]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	bne	.L1745
	mov	r1, #7
	ldr	r0, [r4, #2368]
	bl	BsGet
	sub	r3, r0, #3
	mov	r6, r0
	cmp	r3, #2
	bhi	.L1752
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #6
	mov	r5, r0
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	uxtb	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	clz	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	mov	r5, r5, lsr #5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r6, #5
	moveq	r5, #0
	cmp	r5, #0
	bne	.L1753
.L1748:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
.L1745:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r0, [r4, #2368]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1753:
	mov	r1, #4
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L1748
.L1752:
	mov	r2, r0
	ldr	r1, .L1754+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1755:
	.align	2
.L1754:
	.word	.LC157
	.word	.LC158
	UNWIND(.fnend)
	.size	HEVC_Sei_Frame_Packing_Arrangement, .-HEVC_Sei_Frame_Packing_Arrangement
	.align	2
	.global	HEVC_Sei_Dec_Unit_Info
	.type	HEVC_Sei_Dec_Unit_Info, %function
HEVC_Sei_Dec_Unit_Info:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r5, r2
	mov	r4, r0
	moveq	r1, #1
	movne	r1, #0
	cmp	r0, #0
	orreq	r1, r1, #1
	cmp	r1, #0
	bne	.L1760
	ldr	r1, .L1769
	ldr	r0, [r0, #2368]
	bl	HEVC_ue_v
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1767
.L1758:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	bne	.L1768
.L1759:
	ldr	r0, [r4, #2368]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1767:
	ldr	r1, [r5, #4]
	ldr	r0, [r4, #2368]
	add	r1, r1, #1
	bl	BsGet
	b	.L1758
.L1768:
	ldr	r1, [r5, #8]
	ldr	r0, [r4, #2368]
	add	r1, r1, #1
	bl	BsGet
	b	.L1759
.L1760:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1770:
	.align	2
.L1769:
	.word	.LC159
	UNWIND(.fnend)
	.size	HEVC_Sei_Dec_Unit_Info, .-HEVC_Sei_Dec_Unit_Info
	.align	2
	.global	HEVC_Sei_Active_Param_sets
	.type	HEVC_Sei_Active_Param_sets, %function
HEVC_Sei_Active_Param_sets:
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
	mov	r1, #4
	mov	r5, r0
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldr	r0, [r5, #2368]
	ldr	r1, .L1778
	bl	HEVC_ue_v
	cmp	r0, #15
	bgt	.L1772
	cmp	r0, #0
	addge	r6, r0, #1
	movge	r4, #0
	blt	.L1776
.L1775:
	add	r4, r4, #1
	ldr	r1, .L1778+4
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r4, r6
	bne	.L1775
.L1776:
	ldr	r0, [r5, #2368]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1772:
	ldr	r1, .L1778+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1779:
	.align	2
.L1778:
	.word	.LC160
	.word	.LC162
	.word	.LC161
	UNWIND(.fnend)
	.size	HEVC_Sei_Active_Param_sets, .-HEVC_Sei_Active_Param_sets
	.align	2
	.global	HEVC_Sei_Buf_Period
	.type	HEVC_Sei_Buf_Period, %function
HEVC_Sei_Buf_Period:
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
	add	r4, r0, #8192
	mov	r5, r0
	mov	r9, r1
	mov	r6, #0
	ldr	r1, .L1809
	mov	r7, r2
	str	r6, [r4, #2944]
	ldr	r0, [r0, #2368]
	bl	HEVC_ue_v
	cmp	r0, #15
	bhi	.L1805
	mov	r1, #1
	strb	r1, [r4, #2937]
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r8, r6
	beq	.L1806
.L1783:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r4, #1
	strb	r0, [r9]
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2368]
	add	r1, r1, r4
	bl	BsGet
	subs	r3, r4, #1
	beq	.L1807
.L1785:
	cmp	r3, #1
	beq	.L1808
.L1789:
	cmp	r4, #1
	bhi	.L1788
.L1787:
	add	r4, r4, #1
	subs	r3, r4, #1
	bne	.L1785
.L1807:
	ldrb	r2, [r7]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1789
	ldr	r2, [r7, #24]
	cmn	r2, #1
	beq	.L1787
.L1796:
	mov	r6, #0
	b	.L1792
.L1791:
	ldr	r3, [r7, #24]
	add	r3, r3, #1
	cmp	r3, r6
	bls	.L1789
.L1792:
	ldr	r1, [r7, #12]
	add	r6, r6, #1
	ldr	r0, [r5, #2368]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2368]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	orrs	r3, r8, r3
	beq	.L1791
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2368]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2368]
	add	r1, r1, #1
	bl	BsGet
	b	.L1791
.L1808:
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1788
	ldr	r3, [r7, #24]
	cmn	r3, #1
	bne	.L1796
.L1788:
	ldr	r0, [r5, #2368]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1806:
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r8, r0
	cmp	r8, #0
	beq	.L1783
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2368]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #20]
	ldr	r0, [r5, #2368]
	add	r1, r1, #1
	bl	BsGet
	b	.L1783
.L1805:
	mov	r2, r0
	ldr	r1, .L1809+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1810:
	.align	2
.L1809:
	.word	.LC163
	.word	.LC164
	UNWIND(.fnend)
	.size	HEVC_Sei_Buf_Period, .-HEVC_Sei_Buf_Period
	.align	2
	.global	HEVC_Sei_Pic_Timming
	.type	HEVC_Sei_Pic_Timming, %function
HEVC_Sei_Pic_Timming:
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
	add	r3, r0, #8192
	mov	r5, r2
	mov	r6, r1
	mov	r4, r0
	ldr	r1, [r3, #2940]
	ldr	r2, [r3, #2944]
	add	r1, r1, #1
	str	r1, [r3, #2940]
	add	r2, r2, #1
	str	r2, [r3, #2944]
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1839
.L1812:
	ldrh	r3, [r5, #44]
	cmp	r3, #0
	beq	.L1814
	ldr	r1, [r5, #60]
	ldr	r0, [r4, #2368]
	add	r1, r1, #1
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r6, #8]
	ldr	r1, [r5, #64]
	ldr	r0, [r4, #2368]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #12]
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1815
.L1818:
	ldr	r2, [r4, #252]
	ldr	r3, .L1842
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L1840
.L1814:
	ldr	r0, [r4, #2368]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1839:
	mov	r1, #4
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r1, #2
	str	r0, [r6]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #4]
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L1812
.L1840:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L1814
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L1814
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_Sei_Get_Dpb_Output_Time
	b	.L1814
.L1815:
	ldr	r1, [r5, #52]
	ldr	r0, [r4, #2368]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1818
	ldrb	r3, [r5, #47]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1818
	ldr	r1, .L1842+4
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	mov	r1, #1
	mov	r7, r0
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r8, r0
	cmp	r8, #0
	bne	.L1841
.L1819:
	cmp	r7, #255
	bhi	.L1823
	add	r7, r7, #1
	mov	r6, #0
	b	.L1822
.L1821:
	cmp	r6, r7
	beq	.L1818
.L1822:
	ldr	r1, .L1842+8
	add	r6, r6, #1
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	cmp	r8, #0
	bne	.L1821
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2368]
	add	r1, r1, #1
	bl	BsGet
	b	.L1821
.L1841:
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2368]
	add	r1, r1, #1
	bl	BsGet
	b	.L1819
.L1823:
	ldr	r1, .L1842+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1843:
	.align	2
.L1842:
	.word	s_pstVfmwChan
	.word	.LC165
	.word	.LC167
	.word	.LC166
	UNWIND(.fnend)
	.size	HEVC_Sei_Pic_Timming, .-HEVC_Sei_Pic_Timming
	.align	2
	.global	HEVC_Sei_Color_Volume_Reconstruction_Info
	.type	HEVC_Sei_Color_Volume_Reconstruction_Info, %function
HEVC_Sei_Color_Volume_Reconstruction_Info:
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
	mov	r4, r0
	mov	r5, r1
	beq	.L1854
	ldr	r1, .L1858
	ldr	r0, [r0, #2368]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	beq	.L1846
.L1850:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r5]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1846:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L1857
.L1847:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #3]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #4]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #5]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #6]
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #7]
	addne	r7, r5, #7
	movne	r6, #0
	beq	.L1852
.L1851:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2368]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L1851
.L1852:
	mov	r1, #4
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #38]
	addne	r7, r5, #38
	movne	r6, #0
	beq	.L1850
.L1853:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2368]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #38]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L1853
	b	.L1850
.L1854:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1857:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #1]
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L1847
.L1859:
	.align	2
.L1858:
	.word	.LC168
	UNWIND(.fnend)
	.size	HEVC_Sei_Color_Volume_Reconstruction_Info, .-HEVC_Sei_Color_Volume_Reconstruction_Info
	.align	2
	.global	HEVC_Sei_User_Data_Registered_Itu_T_T35
	.type	HEVC_Sei_User_Data_Registered_Itu_T_T35, %function
HEVC_Sei_User_Data_Registered_Itu_T_T35:
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
	mov	r6, r2
	mov	r5, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L1867
	cmp	r2, #3
	bls	.L1870
	mov	r1, #8
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #2
	beq	.L1871
	cmp	r0, #4
	beq	.L1872
	subs	r6, r6, #4
	beq	.L1866
.L1865:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r6, r4
	bne	.L1865
.L1866:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1871:
	add	r1, r5, #2944
	mov	r0, r5
	add	r1, r1, #8
	bl	HEVC_Sei_TSI
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1872:
	add	r1, r5, #2944
	mov	r0, r5
	add	r1, r1, #11
	bl	HEVC_Sei_Color_Volume_Reconstruction_Info
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1867:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1870:
	ldr	r1, .L1873
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1874:
	.align	2
.L1873:
	.word	.LC169
	UNWIND(.fnend)
	.size	HEVC_Sei_User_Data_Registered_Itu_T_T35, .-HEVC_Sei_User_Data_Registered_Itu_T_T35
	.align	2
	.global	HEVC_DecShortTermRefPicSet
	.type	HEVC_DecShortTermRefPicSet, %function
HEVC_DecShortTermRefPicSet:
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
	subs	r6, r3, #0
	mov	r5, r0
	mov	r9, r1
	mov	r4, r2
	bne	.L1920
.L1876:
	ldr	r1, .L1929
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4]
	bhi	.L1921
	ldr	r1, .L1929+4
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4, #4]
	bhi	.L1922
	ldr	r6, [r4]
	add	r2, r0, r6
	str	r2, [r4, #8]
	cmp	r2, #16
	bhi	.L1899
	cmp	r6, #0
	addne	r10, r4, #28
	addne	r9, r4, #11
	movne	r7, #0
	movne	r8, r7
	bne	.L1903
	b	.L1901
.L1902:
	str	r8, [r10, #4]!
	ldr	r0, [r5, #2368]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r6, [r4]
	cmp	r6, r7
	bls	.L1923
.L1903:
	ldr	r1, .L1929+8
	add	r7, r7, #1
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	mov	r1, #1
	cmp	r0, #32768
	mvn	r3, r0
	add	r8, r8, r3
	bcc	.L1902
	mov	r2, r0
	ldr	r1, .L1929+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1920:
	mov	r1, #1
	ldr	r0, [r0, #2368]
	bl	BsGet
	cmp	r0, #0
	beq	.L1876
	ldr	r7, [r9, #176]
	cmp	r7, r6
	movne	r0, #0
	beq	.L1924
.L1877:
	sub	r3, r6, #1
	rsb	r8, r0, r3
	cmp	r8, r3
	bhi	.L1925
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldr	r1, .L1929+16
	mov	r6, r0
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	mov	r3, #164
	mul	r8, r3, r8
	mov	r3, r6, asl #1
	rsb	r3, r3, #1
	add	r2, r9, r8
	ldr	r2, [r2, #2172]
	cmp	r2, #16
	mla	r3, r0, r3, r3
	str	r3, [fp, #-56]
	bhi	.L1926
	add	r6, r8, #2192
	mov	r10, #0
	add	r6, r6, #4
	str	r10, [fp, #-48]
	add	r6, r9, r6
	str	r10, [fp, #-52]
	mov	r7, r10
	b	.L1886
.L1881:
	sub	r3, r0, #1
	cmp	r3, #1
	bls	.L1927
.L1882:
	add	r3, r9, r8
	add	r10, r10, #1
	add	r6, r6, #4
	ldr	r3, [r3, #2172]
	cmp	r3, r10
	bcc	.L1928
.L1886:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r0, #0
	bne	.L1881
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r0, r0, asl #1
	sub	r3, r0, #1
	cmp	r3, #1
	bhi	.L1882
.L1927:
	add	r3, r9, r8
	ldr	r2, [fp, #-56]
	add	r1, r4, r7
	add	ip, r7, #8
	ldr	r3, [r3, #2172]
	sub	r0, r0, #1
	clz	r0, r0
	add	r7, r7, #1
	cmp	r3, r10
	mov	r0, r0, lsr #5
	ldrhi	r3, [r6]
	movls	r3, #0
	add	r3, r3, r2
	str	r3, [r4, ip, asl #2]
	cmp	r3, #0
	mov	r3, r1
	strb	r0, [r1, #12]
	ldrlt	r3, [fp, #-52]
	ldrge	r3, [fp, #-48]
	addlt	r3, r3, #1
	addge	r3, r3, #1
	strlt	r3, [fp, #-52]
	strge	r3, [fp, #-48]
	b	.L1882
.L1928:
	ldr	r3, [fp, #-52]
	cmp	r7, #16
	ldr	r2, [fp, #-48]
	str	r7, [r4, #8]
	str	r3, [r4]
	str	r2, [r4, #4]
	bhi	.L1887
	cmp	r3, #16
	bhi	.L1887
	cmp	r2, #16
	bhi	.L1887
	cmp	r7, #1
	subhi	r7, r7, #1
	addhi	r8, r4, #32
	addhi	r6, r4, #12
	movhi	r5, #0
	bls	.L1893
.L1892:
	ldr	ip, [r8, #4]!
	cmp	r5, #0
	ldrb	lr, [r6, #1]!	@ zero_extendqisi2
	mov	r2, r5
	movge	r1, r8
	movge	r3, r6
	blt	.L1895
.L1891:
	ldr	r0, [r1, #-4]!
	sub	r3, r3, #1
	cmp	ip, r0
	strlt	r0, [r1, #4]
	ldrltb	r0, [r3]	@ zero_extendqisi2
	strltb	r0, [r3, #1]
	strlt	ip, [r1]
	strltb	lr, [r3]
	subs	r2, r2, #1
	bpl	.L1891
.L1895:
	add	r5, r5, #1
	cmp	r5, r7
	bne	.L1892
.L1893:
	ldr	r3, [fp, #-52]
	movs	r6, r3, lsr #1
	beq	.L1890
	ldr	r3, [fp, #-52]
	add	r0, r4, #28
	mov	r1, #0
	add	r2, r3, #7
	add	r3, r3, #11
	add	r3, r4, r3
	mov	ip, r0
	add	r2, r4, r2, lsl #2
	add	r4, r4, #12
.L1896:
	ldr	r7, [r2]
	add	r1, r1, #1
	ldr	r5, [ip, #4]!
	cmp	r1, r6
	ldrb	lr, [r4]	@ zero_extendqisi2
	str	r7, [r0, #4]!
	ldrb	r7, [r3]	@ zero_extendqisi2
	strb	r7, [r4], #1
	str	r5, [r2], #-4
	strb	lr, [r3], #-1
	bne	.L1896
.L1890:
	mov	r0, #0
.L1878:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1923:
	ldr	r2, [r4, #8]
.L1901:
	cmp	r2, r6
	bls	.L1890
	add	r8, r6, #7
	add	r9, r6, #11
	add	r9, r4, r9
	mov	r7, #0
	add	r8, r4, r8, lsl #2
.L1904:
	ldr	r1, .L1929+20
	add	r6, r6, #1
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	mov	r1, #1
	add	r0, r0, r1
	add	r7, r7, r0
	str	r7, [r8, #4]!
	ldr	r0, [r5, #2368]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r3, [r4, #8]
	cmp	r3, r6
	bhi	.L1904
	b	.L1890
.L1924:
	ldr	r1, .L1929+24
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	add	r2, r0, #1
	cmp	r7, r2
	bcs	.L1877
	mov	r3, r7
	ldr	r1, .L1929+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1878
.L1887:
	ldr	r1, .L1929+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1878
.L1922:
	ldr	r2, [r4]
	mov	r0, #1
	ldr	r1, .L1929+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1878
.L1925:
	mov	r2, r8
	ldr	r1, .L1929+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1878
.L1926:
	ldr	r1, .L1929+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1878
.L1921:
	mov	r2, r0
	ldr	r1, .L1929+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1878
.L1899:
	mov	r3, #16
	ldr	r1, .L1929+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1878
.L1930:
	.align	2
.L1929:
	.word	.LC176
	.word	.LC178
	.word	.LC181
	.word	.LC182
	.word	.LC173
	.word	.LC183
	.word	.LC170
	.word	.LC171
	.word	.LC175
	.word	.LC179
	.word	.LC172
	.word	.LC174
	.word	.LC177
	.word	.LC180
	UNWIND(.fnend)
	.size	HEVC_DecShortTermRefPicSet, .-HEVC_DecShortTermRefPicSet
	.align	2
	.global	HEVC_DecHrdParam
	.type	HEVC_DecHrdParam, %function
HEVC_DecHrdParam:
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
	mov	r8, r3
	mov	r6, r0
	mov	r9, r1
	beq	.L1953
	cmp	r2, #0
	bne	.L1980
.L1936:
	add	r5, r9, #24
	mov	r7, #0
.L1948:
	mov	r1, #1
	ldr	r0, [r6, #2368]
	bl	BsGet
	uxtb	r4, r0
	cmp	r4, #0
	movne	r3, #0
	strne	r3, [r5]
	beq	.L1981
.L1951:
	ldr	r1, .L1986
	ldr	r0, [r6, #2368]
	bl	HEVC_ue_v
.L1939:
	ldr	r1, .L1986+4
	ldr	r0, [r6, #2368]
	bl	HEVC_ue_v
	mov	r2, r0
	str	r0, [r5]
.L1940:
	cmp	r2, #31
	bhi	.L1982
.L1941:
	mov	r4, #0
.L1952:
	cmp	r4, #0
	beq	.L1983
	cmp	r4, #1
	beq	.L1978
.L1947:
	add	r4, r4, #1
	cmp	r4, #2
	bne	.L1952
.L1946:
	add	r7, r7, #1
	add	r5, r5, #4
	cmp	r8, r7
	bcs	.L1948
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1982:
	ldr	r1, .L1986+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5]
	b	.L1941
.L1981:
	mov	r1, #1
	ldr	r0, [r6, #2368]
	bl	BsGet
	str	r4, [r5]
	tst	r0, #255
	bne	.L1951
	mov	r1, #1
	ldr	r0, [r6, #2368]
	bl	BsGet
	tst	r0, #255
	beq	.L1939
	ldr	r2, [r5]
	b	.L1940
.L1980:
	mov	r1, #1
	ldr	r0, [r0, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r6, #2368]
	bl	BsGet
	strb	r0, [r9, #1]
	ldrh	r3, [r9]
	cmp	r3, #0
	beq	.L1936
	mov	r1, #1
	ldr	r0, [r6, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r9, #2]
	cmp	r0, #0
	bne	.L1984
.L1934:
	mov	r1, #4
	ldr	r0, [r6, #2368]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r6, #2368]
	bl	BsGet
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1985
.L1935:
	mov	r1, #5
	ldr	r0, [r6, #2368]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #12]
	ldr	r0, [r6, #2368]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #16]
	ldr	r0, [r6, #2368]
	bl	BsGet
	str	r0, [r9, #20]
	b	.L1936
.L1953:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1985:
	mov	r1, #4
	ldr	r0, [r6, #2368]
	bl	BsGet
	b	.L1935
.L1984:
	mov	r1, #8
	ldr	r0, [r6, #2368]
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r6, #2368]
	bl	BsGet
	mov	r1, #1
	str	r0, [r9, #4]
	ldr	r0, [r6, #2368]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r9, #3]
	ldr	r0, [r6, #2368]
	bl	BsGet
	str	r0, [r9, #8]
	b	.L1934
.L1983:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1955
	mov	r4, #1
.L1978:
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1946
.L1955:
	mov	r10, #0
	b	.L1950
.L1949:
	mov	r1, #1
	ldr	r0, [r6, #2368]
	bl	BsGet
	ldr	r3, [r5]
	cmp	r3, r10
	bcc	.L1947
.L1950:
	ldr	r1, .L1986+12
	add	r10, r10, #1
	ldr	r0, [r6, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L1986+16
	ldr	r0, [r6, #2368]
	bl	HEVC_ue_v
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1949
	ldr	r1, .L1986+20
	ldr	r0, [r6, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L1986+24
	ldr	r0, [r6, #2368]
	bl	HEVC_ue_v
	b	.L1949
.L1987:
	.align	2
.L1986:
	.word	.LC184
	.word	.LC185
	.word	.LC186
	.word	.LC187
	.word	.LC188
	.word	.LC189
	.word	.LC190
	UNWIND(.fnend)
	.size	HEVC_DecHrdParam, .-HEVC_DecHrdParam
	.align	2
	.global	HEVC_ProcessVPS
	.type	HEVC_ProcessVPS, %function
HEVC_ProcessVPS:
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
	UNWIND(.pad #60)
	sub	sp, sp, #60
	mov	r5, r0
	mov	r6, r1
	ldr	r0, [r0, #2368]
	mov	r1, #1
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3]
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r2, r0
	cmp	r2, #1
	beq	.L1989
	ldr	r1, .L2040
	mov	r0, #1
	bl	dprint_vfmw
.L1989:
	mov	r1, #6
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r0, #63
	str	r0, [r6, #8]
	bhi	.L2033
	mov	r1, #3
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r0, #7
	mov	r7, r0
	bhi	.L2034
	str	r0, [r6, #12]
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r6, #1]
	ldr	r0, [r5, #2368]
	bl	BsGet
	movw	r3, #65535
	cmp	r0, r3
	bne	.L2035
	mov	r3, r7
	mov	r2, #1
	add	r1, r6, #124
	mov	r0, r5
	bl	HEVC_DecPTL
	subs	r4, r0, #0
	bne	.L2036
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r7, #0
	addge	r8, r6, #24
	addge	r9, r7, #1
	uxtb	r10, r0
	bge	.L2001
	b	.L1999
.L1998:
	add	r4, r4, #1
	cmp	r4, r9
	beq	.L1999
.L2001:
	ldr	r1, .L2040+4
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L2040+8
	add	r0, r0, #1
	str	r0, [r8, #4]!
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L2040+12
	str	r0, [r8, #32]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r10, #0
	str	r0, [r8, #64]
	bne	.L1998
	add	r2, r4, #1
	cmp	r7, r2
	blt	.L1999
	add	r3, r4, #7
	add	r3, r6, r3, lsl #2
.L2000:
	ldr	r1, [r6, #28]
	add	r2, r2, #1
	cmp	r9, r2
	str	r1, [r3, #4]!
	ldr	r1, [r6, #60]
	str	r1, [r3, #32]
	ldr	r1, [r6, #92]
	str	r1, [r3, #64]
	bne	.L2000
.L1999:
	mov	r1, #6
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldr	r1, .L2040+16
	str	r0, [r6, #16]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r6, #20]
	bcs	.L2037
	cmp	r0, #0
	movgt	r8, #1
	ble	.L2003
.L2005:
	mov	r4, #0
.L2004:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldr	r3, [r6, #16]
	add	r4, r4, #1
	cmp	r4, r3
	bls	.L2004
	ldr	r3, [r6, #20]
	add	r8, r8, #1
	cmp	r3, r8
	bge	.L2005
.L2003:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	tst	r0, #255
	beq	.L2012
	mov	r1, #32
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	tst	r0, #255
	bne	.L2038
.L2009:
	ldr	r1, .L2040+20
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r6, #24]
	bhi	.L2010
	cmp	r0, #0
	ble	.L2012
	ldr	r1, .L2040+24
	mov	r4, #0
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	mov	r0, #1
.L2017:
	uxtb	r2, r0
	sub	r1, fp, #100
	mov	r3, r7
	mov	r0, r5
	bl	HEVC_DecHrdParam
	add	r4, r4, #1
	ldr	r1, .L2040+24
	cmp	r0, #0
	bne	.L2039
	ldr	r3, [r6, #24]
	cmp	r3, r4
	ble	.L2012
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r4, #0
	mov	r0, #1
	beq	.L2017
	mov	r1, r0
	ldr	r0, [r5, #2368]
	bl	BsGet
	b	.L2017
.L2012:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	tst	r0, #255
	bne	.L2029
.L2008:
	mov	r0, #0
.L2030:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2016:
	ldr	r0, [r5, #2368]
	bl	BsGet
.L2029:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2016
	b	.L2008
.L2039:
	ldr	r1, .L2040+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2038:
	ldr	r1, .L2040+32
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	b	.L2009
.L2035:
	ldr	r1, .L2040+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2030
.L2033:
	mov	r2, r0
	ldr	r1, .L2040+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2030
.L2036:
	ldr	r1, .L2040+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2030
.L2034:
	mov	r2, r0
	ldr	r1, .L2040+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2030
.L2037:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L2040+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2030
.L2010:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L2040+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2030
.L2041:
	.align	2
.L2040:
	.word	.LC191
	.word	.LC197
	.word	.LC198
	.word	.LC199
	.word	.LC196
	.word	.LC202
	.word	.LC204
	.word	.LC205
	.word	.LC201
	.word	.LC194
	.word	.LC192
	.word	.LC195
	.word	.LC193
	.word	.LC200
	.word	.LC203
	UNWIND(.fnend)
	.size	HEVC_ProcessVPS, .-HEVC_ProcessVPS
	.align	2
	.global	HEVC_DecVPS
	.type	HEVC_DecVPS, %function
HEVC_DecVPS:
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
	ldr	r5, .L2054
	mov	r6, r0
	ldr	r0, [r5]
	cmp	r0, #0
	beq	.L2049
	mov	r1, #4
	ldr	r0, [r6, #2368]
	bl	BsGet
	cmp	r0, #15
	mov	r7, r0
	bhi	.L2050
	ldr	r3, [r6, #2372]
	mov	r4, r0, asl #7
	add	r4, r4, r0, lsl #2
	add	r2, r3, r4
	ldrb	r9, [r3, r4]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L2051
	str	r0, [r2, #4]
	mov	r0, r6
	ldr	r1, [r6, #2372]
	add	r1, r1, r4
	bl	HEVC_ProcessVPS
	subs	r8, r0, #0
	bne	.L2052
	ldr	r3, [r6, #2372]
	mov	r2, #1
	add	r3, r3, r4
	strb	r2, [r3, #2]
	ldr	r3, [r6, #2372]
	strb	r2, [r3, r4]
.L2044:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2051:
	ldr	r5, [r5]
	mov	r2, #132
	ldr	r9, .L2054+4
	mov	r1, #0
	add	r5, r5, #458752
	ldr	r3, [r9, #48]
	mov	r0, r5
	blx	r3
	str	r7, [r5, #4]
	mov	r1, r5
	mov	r0, r6
	bl	HEVC_ProcessVPS
	subs	r8, r0, #0
	bne	.L2053
	mov	r3, #1
	strb	r3, [r5, #2]
	strb	r3, [r5]
	mov	r1, r5
	ldr	r0, [r6, #2372]
	mov	r2, #132
	ldr	r3, [r9, #56]
	add	r0, r0, r4
	blx	r3
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2053:
	mov	r2, r7
	ldr	r1, .L2054+8
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L2044
.L2050:
	ldr	r1, .L2054+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L2044
.L2052:
	mov	r2, r7
	ldr	r1, .L2054+16
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	ldr	r3, [r6, #2372]
	mov	r2, #1
	add	r3, r3, r4
	strb	r2, [r3, #2]
	ldr	r3, [r6, #2372]
	strb	r9, [r3, r4]
	b	.L2044
.L2049:
	ldr	r2, .L2054+20
	mvn	r8, #0
	ldr	r1, .L2054+24
	bl	dprint_vfmw
	b	.L2044
.L2055:
	.align	2
.L2054:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC207
	.word	.LC206
	.word	.LC208
	.word	.LANCHOR0+512
	.word	.LC61
	UNWIND(.fnend)
	.size	HEVC_DecVPS, .-HEVC_DecVPS
	.align	2
	.global	HEVC_DecVuiParam
	.type	HEVC_DecVuiParam, %function
HEVC_DecVuiParam:
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
	mov	r5, r1
	ldr	r0, [r0, #2368]
	mov	r1, #1
	mov	r6, r2
	bl	BsGet
	tst	r0, #255
	bne	.L2100
.L2058:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	bne	.L2101
.L2060:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	bne	.L2102
.L2062:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	bne	.L2103
.L2064:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #3]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	beq	.L2065
	ldr	r1, .L2109
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r3, [r6, #60]
	cmp	r3, #3
	bhi	.L2104
	ldr	r1, .L2109+4
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L2109+8
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L2109+12
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
.L2065:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	beq	.L2068
	mov	r1, #32
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #32
	str	r0, [r5, #36]
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r2, [r5, #36]
	cmp	r2, #0
	str	r0, [r5, #40]
	bne	.L2105
.L2069:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	bne	.L2106
.L2070:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	bne	.L2107
.L2068:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r1, .L2109+16
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	cmp	r0, #4096
	bcs	.L2108
.L2071:
	ldr	r1, .L2109+20
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L2109+24
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L2109+28
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2368]
	ldr	r1, .L2109+32
	bl	HEVC_ue_v
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2100:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r0, #255
	str	r0, [r5, #8]
	bne	.L2058
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #16
	str	r0, [r5, #12]
	ldr	r0, [r4, #2368]
	bl	BsGet
	str	r0, [r5, #16]
	b	.L2058
.L2103:
	ldr	r1, .L2109+36
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L2109+40
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	b	.L2064
.L2102:
	mov	r1, #3
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #20]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5]
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	beq	.L2062
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #24]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #28]
	ldr	r0, [r4, #2368]
	bl	BsGet
	str	r0, [r5, #32]
	b	.L2062
.L2101:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L2060
.L2107:
	ldr	r3, [r6, #52]
	add	r1, r5, #44
	mov	r2, #1
	mov	r0, r4
	bl	HEVC_DecHrdParam
	cmp	r0, #0
	beq	.L2068
	ldr	r1, .L2109+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2106:
	ldr	r1, .L2109+48
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	b	.L2070
.L2105:
	ldr	r3, .L2109+52
	movw	r1, #10000
	umull	r0, r1, r0, r1
	ldr	r3, [r3, #244]
	blx	r3
	movw	r3, #52429
	movt	r3, 52428
	add	r0, r0, #5
	umull	r0, r1, r0, r3
	mov	r3, r1, lsr #3
	str	r3, [r4, #144]
	b	.L2069
.L2108:
	ldr	r1, .L2109+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2071
.L2104:
	ldr	r1, .L2109+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2110:
	.align	2
.L2109:
	.word	.LC211
	.word	.LC213
	.word	.LC214
	.word	.LC215
	.word	.LC218
	.word	.LC220
	.word	.LC221
	.word	.LC222
	.word	.LC223
	.word	.LC209
	.word	.LC210
	.word	.LC217
	.word	.LC216
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC219
	.word	.LC212
	UNWIND(.fnend)
	.size	HEVC_DecVuiParam, .-HEVC_DecVuiParam
	.align	2
	.global	HEVC_se_v
	.type	HEVC_se_v, %function
HEVC_se_v:
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
	mov	r1, #32
	mov	r5, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	bls	.L2116
	mvn	r0, #-2147483648
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2116:
	add	r6, r0, #1
	mov	r1, r0
	mov	r0, r5
	bl	BsSkip
	mov	r1, r6
	mov	r0, r5
	bl	BsShow
	mov	r1, r6
	sub	r0, r0, #1
	tst	r0, #1
	mov	r0, r0, asr #1
	addne	r4, r0, #1
	rsbeq	r4, r0, #0
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_se_v, .-HEVC_se_v
	.align	2
	.global	HEVC_Sei_Structure_Of_Pictures_Info
	.type	HEVC_Sei_Structure_Of_Pictures_Info, %function
HEVC_Sei_Structure_Of_Pictures_Info:
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
	ldr	r1, .L2129
	mov	r6, r0
	ldr	r0, [r0, #2368]
	bl	HEVC_ue_v
	ldr	r0, [r6, #2368]
	ldr	r1, .L2129+4
	bl	HEVC_ue_v
	cmp	r0, #1024
	mov	r7, r0
	bhi	.L2118
	cmp	r0, #0
	movne	r4, #0
	beq	.L2124
.L2123:
	mov	r1, #6
	ldr	r0, [r6, #2368]
	bl	BsGet
	mov	r1, #3
	mov	r5, r0
	ldr	r0, [r6, #2368]
	sub	r5, r5, #19
	bl	BsGet
	cmp	r5, #1
	ldr	r1, .L2129+8
	bls	.L2121
	ldr	r0, [r6, #2368]
	bl	HEVC_ue_v
.L2121:
	cmp	r4, #0
	ldr	r1, .L2129+12
	add	r4, r4, #1
	beq	.L2122
	ldr	r0, [r6, #2368]
	bl	HEVC_se_v
.L2122:
	cmp	r4, r7
	bne	.L2123
.L2124:
	ldr	r0, [r6, #2368]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2118:
	ldr	r1, .L2129+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2130:
	.align	2
.L2129:
	.word	.LC224
	.word	.LC225
	.word	.LC227
	.word	.LC228
	.word	.LC226
	UNWIND(.fnend)
	.size	HEVC_Sei_Structure_Of_Pictures_Info, .-HEVC_Sei_Structure_Of_Pictures_Info
	.align	2
	.global	HEVC_Sei_Recovery_Point
	.type	HEVC_Sei_Recovery_Point, %function
HEVC_Sei_Recovery_Point:
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
	mov	r4, r0
	moveq	r5, #1
	movne	r5, #0
	beq	.L2133
	ldr	r1, .L2134
	ldr	r0, [r0, #2368]
	bl	HEVC_se_v
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r0, [r4, #2368]
	bl	BsToNextByte
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2133:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2135:
	.align	2
.L2134:
	.word	.LC229
	UNWIND(.fnend)
	.size	HEVC_Sei_Recovery_Point, .-HEVC_Sei_Recovery_Point
	.align	2
	.global	HEVC_Sei_Color_Remapping_Info
	.type	HEVC_Sei_Color_Remapping_Info, %function
HEVC_Sei_Color_Remapping_Info:
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
	mov	r4, r0
	mov	r8, r1
	beq	.L2153
	ldr	r1, .L2166
	ldr	r0, [r0, #2368]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	beq	.L2138
.L2151:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r8]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2138:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r1, r0
	cmp	r1, #1
	beq	.L2163
.L2139:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2368]
	mov	r7, #3
	bl	BsGet
.L2141:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	beq	.L2144
	add	r6, r0, #1
	mov	r5, #0
.L2143:
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r5, r6
	bne	.L2143
.L2144:
	subs	r7, r7, #1
	bne	.L2141
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L2164
.L2145:
	add	r10, r8, #42
	add	r7, r8, #39
	mov	r9, r10
.L2150:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #1]!
	cmp	r0, #32
	bhi	.L2165
	cmp	r0, #0
	beq	.L2152
	mov	r6, r9
	mov	r5, #0
.L2149:
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #16
	add	r5, r5, #1
	strh	r0, [r6, #2]!	@ movhi
	ldr	r0, [r4, #2368]
	bl	BsGet
	strh	r0, [r6, #198]	@ movhi
	ldrb	r3, [r7]	@ zero_extendqisi2
	add	r3, r3, #1
	cmp	r3, r5
	bhi	.L2149
.L2152:
	cmp	r10, r7
	add	r9, r9, #66
	bne	.L2150
	b	.L2151
.L2153:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2164:
	mov	r1, #4
	ldr	r0, [r4, #2368]
	bl	BsGet
	add	r7, r8, #36
	mov	r5, r8
.L2146:
	add	r6, r5, #12
.L2147:
	ldr	r1, .L2166+4
	ldr	r0, [r4, #2368]
	bl	HEVC_se_v
	str	r0, [r5, #4]!
	cmp	r6, r5
	bne	.L2147
	cmp	r5, r7
	bne	.L2146
	b	.L2145
.L2163:
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r8, #1]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L2139
.L2165:
	mov	r2, r0
	ldr	r1, .L2166+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2167:
	.align	2
.L2166:
	.word	.LC230
	.word	.LC231
	.word	.LC232
	UNWIND(.fnend)
	.size	HEVC_Sei_Color_Remapping_Info, .-HEVC_Sei_Color_Remapping_Info
	.align	2
	.global	HEVC_Sei_Payload
	.type	HEVC_Sei_Payload, %function
HEVC_Sei_Payload:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	clz	ip, r0
	ldr	r6, [fp, #4]
	mov	r4, r0
	mov	ip, ip, lsr #5
	cmp	r1, #0
	movne	r5, ip
	orreq	r5, ip, #1
	cmp	r5, #0
	bne	.L2194
	ldr	lr, [r0, #2388]
	ldr	lr, [lr, #16]
	cmp	lr, #39
	beq	.L2212
	cmp	r3, #5
	beq	.L2198
	cmp	r3, #132
	beq	.L2199
	cmp	r6, #0
	beq	.L2193
.L2201:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r5, r6
	bne	.L2201
	b	.L2193
.L2198:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	bne	.L2194
.L2193:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_More_Data_In_Payload
	cmp	r0, #0
	bne	.L2202
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2202:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_Payload_Extension_Present
	cmp	r0, #0
	bne	.L2213
.L2203:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L2204
.L2205:
	ldr	r0, [r4, #2368]
	bl	BsGet
.L2204:
	ldr	r0, [r4, #2368]
	bl	BsIsByteAligned
	mov	r1, #1
	cmp	r0, #0
	beq	.L2205
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2212:
	cmp	r3, #147
	ldrls	pc, [pc, r3, asl #2]
	b	.L2172
.L2174:
	.word	.L2173
	.word	.L2175
	.word	.L2172
	.word	.L2172
	.word	.L2176
	.word	.L2177
	.word	.L2178
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2179
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2180
	.word	.L2172
	.word	.L2181
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2182
	.word	.L2183
	.word	.L2184
	.word	.L2185
	.word	.L2172
	.word	.L2186
	.word	.L2187
	.word	.L2172
	.word	.L2172
	.word	.L2188
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2172
	.word	.L2189
	.word	.L2172
	.word	.L2190
	.word	.L2172
	.word	.L2172
	.word	.L2191
.L2199:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Decoded_Picture_Hash
	cmp	r0, #0
	beq	.L2193
.L2194:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2213:
	ldr	r1, .L2214
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	b	.L2203
.L2191:
	add	r1, r1, #616
	add	r1, r1, #2
	bl	HEVC_Sei_HLGHDR_Comapitibility_Info
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2173:
	add	r2, r2, #2096
	add	r2, r2, #12
	bl	HEVC_Sei_Buf_Period
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2175:
	add	r2, r2, #2064
	add	r1, r1, #8
	bl	HEVC_Sei_Pic_Timming
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2176:
	add	r1, r1, #56
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Registered_Itu_T_T35
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2177:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2178:
	add	r1, r1, #568
	bl	HEVC_Sei_Recovery_Point
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2179:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Tone_Mapping_Info
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2180:
	add	r1, r1, #568
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2181:
	add	r1, r1, #568
	bl	HEVC_Sei_Display_Orientation
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2182:
	add	r1, r1, #616
	mov	r2, r6
	add	r1, r1, #3
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2183:
	add	r1, r1, #568
	bl	HEVC_Sei_Active_Param_sets
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2184:
	add	r2, r2, #2096
	add	r1, r1, #568
	add	r2, r2, #12
	bl	HEVC_Sei_Dec_Unit_Info
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2185:
	add	r1, r1, #568
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2186:
	mov	r3, r6
	bl	HEVC_Sei_Scalable_Nesting
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2187:
	cmn	r1, #568
	movne	r1, #0
	moveq	r1, #1
	orrs	r3, ip, r1
	bne	.L2194
	mov	r1, #1
	ldr	r0, [r0, #2368]
	bl	BsGet
	b	.L2193
.L2188:
	add	r1, r1, #568
	bl	HEVC_Sei_Mastering_Display_Colour_Volume
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2189:
	add	r1, r1, #128
	bl	HEVC_Sei_Color_Remapping_Info
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2190:
	add	r1, r1, #612
	bl	HEVC_Sei_Content_Light_Level_Information
	cmp	r0, #0
	beq	.L2193
	b	.L2194
.L2172:
	cmp	r6, #0
	movne	r5, #0
	beq	.L2193
.L2196:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r5, r6
	bne	.L2196
	b	.L2193
.L2215:
	.align	2
.L2214:
	.word	.LC233
	UNWIND(.fnend)
	.size	HEVC_Sei_Payload, .-HEVC_Sei_Payload
	.align	2
	.global	HEVC_SeiMessage
	.type	HEVC_SeiMessage, %function
HEVC_SeiMessage:
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
	mov	r5, #0
	mov	r4, r0
	mov	r6, r1
	mov	r7, r2
	ldr	r0, [r0, #2368]
	b	.L2217
.L2219:
	bl	BsSkip
	ldr	r0, [r4, #2368]
	add	r5, r5, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2, asl #3
	bhi	.L2225
.L2217:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2368]
	beq	.L2219
	bl	BsGet
	mov	r8, #0
	mov	r9, r0
	ldr	r0, [r4, #2368]
	b	.L2220
.L2221:
	bl	BsSkip
	ldr	r0, [r4, #2368]
	add	r8, r8, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2, asl #3
	bhi	.L2226
.L2220:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2368]
	beq	.L2221
	bl	BsGet
	add	r3, r9, r5
	mov	r2, r7
	mov	r1, r6
	add	r8, r0, r8
	mov	r0, r4
	str	r8, [sp]
	bl	HEVC_Sei_Payload
	cmp	r0, #0
	bne	.L2227
.L2218:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2225:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5039
	ldr	r1, .L2228
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2226:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5060
	ldr	r1, .L2228
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2227:
	ldr	r1, .L2228+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2218
.L2229:
	.align	2
.L2228:
	.word	.LC234
	.word	.LC235
	UNWIND(.fnend)
	.size	HEVC_SeiMessage, .-HEVC_SeiMessage
	.align	2
	.global	HEVC_DecSEI
	.type	HEVC_DecSEI, %function
HEVC_DecSEI:
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
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r3, #1
	beq	.L2236
	ldr	r5, [r0, #2384]
	add	r6, r0, #2896
	cmp	r5, #0
	bne	.L2239
	b	.L2242
.L2234:
	ldr	r0, [r4, #2368]
	bl	BsIsByteAligned
	cmp	r0, #0
	mov	r0, r4
	beq	.L2243
	bl	HEVC_More_Rbsp_Data
	cmp	r0, #0
	beq	.L2244
.L2239:
	mov	r2, r5
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	beq	.L2234
	ldr	r1, .L2246
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2244:
	ldr	r0, [r4, #2368]
	mov	r1, #8
	bl	BsGet
	cmp	r0, #128
	bne	.L2245
.L2236:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2243:
	ldr	r1, .L2246+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2245:
	mov	r2, r0
	ldr	r1, .L2246+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2242:
	ldr	r1, .L2246+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2247:
	.align	2
.L2246:
	.word	.LC237
	.word	.LC238
	.word	.LC239
	.word	.LC236
	UNWIND(.fnend)
	.size	HEVC_DecSEI, .-HEVC_DecSEI
	.align	2
	.global	HEVC_Sei_Scalable_Nesting
	.type	HEVC_Sei_Scalable_Nesting, %function
HEVC_Sei_Scalable_Nesting:
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
	mov	r4, r0
	mov	r6, r1
	ldr	r0, [r0, #2368]
	mov	r1, #1
	mov	r7, r2
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	tst	r0, #255
	ldr	r0, [r4, #2368]
	beq	.L2249
	bl	BsGet
	ldr	r1, .L2265
	mov	r5, r0
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	cmp	r0, #63
	mov	r8, r0
	bhi	.L2262
	uxtb	r5, r5
	cmp	r0, r5
	bcc	.L2255
.L2254:
	mov	r1, #3
	ldr	r0, [r4, #2368]
	bl	BsGet
	add	r5, r5, #1
	ldr	r1, .L2265+4
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	cmp	r8, r5
	bcs	.L2254
.L2255:
	ldr	r0, [r4, #2368]
	bl	BsToNextByte
	b	.L2253
.L2258:
	bl	HEVC_MoreRbspData
	cmp	r0, #0
	beq	.L2263
.L2253:
	mov	r2, r7
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	mov	r0, r4
	beq	.L2258
	ldr	r1, .L2265+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2249:
	bl	BsGet
	uxtb	r5, r0
	cmp	r5, #0
	bne	.L2255
	mov	r1, #3
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r1, .L2265+12
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	cmp	r0, #63
	addls	r8, r0, #1
	bhi	.L2264
.L2257:
	add	r5, r5, #1
	mov	r1, #6
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r5, r8
	bne	.L2257
	b	.L2255
.L2263:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2262:
	mov	r2, #64
	ldr	r1, .L2265+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2264:
	ldr	r1, .L2265+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2266:
	.align	2
.L2265:
	.word	.LC240
	.word	.LC242
	.word	.LC237
	.word	.LC243
	.word	.LC241
	.word	.LC244
	UNWIND(.fnend)
	.size	HEVC_Sei_Scalable_Nesting, .-HEVC_Sei_Scalable_Nesting
	.align	2
	.global	HEVC_DecScalingListData
	.type	HEVC_DecScalingListData, %function
HEVC_DecScalingListData:
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
	ldr	r3, .L2308
	mov	r6, r0
	str	r1, [fp, #-60]
	ldr	r0, [r3]
	cmp	r0, #0
	beq	.L2302
	ldr	r3, .L2308+4
	add	r9, r6, #2208
	ldr	r4, [fp, #-60]
	add	r9, r9, #12
	mov	r2, #64
	ldr	r3, [r3, #52]
	add	r1, r4, #1216
	add	r0, r4, #1344
	blx	r3
	add	r3, r4, #1536
	str	r4, [fp, #-64]
	str	r3, [fp, #-68]
	mov	r3, #0
	str	r3, [fp, #-48]
.L2270:
	ldr	r3, [r9, #4]!
	cmp	r3, #0
	beq	.L2290
	ldr	r2, [fp, #-48]
	ldr	r1, [fp, #-68]
	ldr	r7, [fp, #-64]
	mov	r3, r2, asl #3
	sub	r3, r3, r2, asl #1
	str	r1, [fp, #-56]
	str	r3, [fp, #-72]
	mov	r3, #0
	str	r3, [fp, #-52]
.L2289:
	mov	r1, #1
	ldr	r0, [r6, #2368]
	bl	BsGet
	ldr	r5, [r9, #-1888]
	ldr	r3, [fp, #-48]
	cmp	r5, #64
	movge	r5, #64
	cmp	r3, #0
	uxtb	r0, r0
	beq	.L2303
	cmp	r0, #0
	add	r4, r6, #352
	beq	.L2304
	ldr	r3, [fp, #-48]
	cmp	r3, #1
	bls	.L2295
	ldr	r1, .L2308+8
	ldr	r0, [r6, #2368]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #254
	bhi	.L2305
	ldr	r3, [fp, #-56]
	add	r8, r0, #8
	str	r8, [r3]
.L2273:
	cmp	r5, #0
	ble	.L2282
	sub	r4, r4, #4
	mov	r10, #0
	b	.L2286
.L2285:
	mov	r8, r8, lsr #24
	ldr	r2, [r4, #4]!
	add	r3, r3, r8
	cmp	r10, r5
	uxtb	r3, r3
	rsb	r8, r8, r3
	strb	r8, [r7, r2]
	beq	.L2282
.L2286:
	ldr	r1, .L2308+12
	add	r10, r10, #1
	ldr	r0, [r6, #2368]
	bl	HEVC_se_v
	add	r3, r0, r8
	add	r0, r0, #128
	add	r3, r3, #256
	cmp	r0, #255
	mov	r8, r3, asr #31
	bls	.L2285
	ldr	r1, .L2308+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2300:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2303:
	ldr	r3, .L2308
	cmp	r0, #0
	ldr	r4, [r3]
	add	r4, r4, #65536
	bne	.L2295
	ldr	r1, .L2308+20
	ldr	r0, [r6, #2368]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-52]
	cmp	r0, r3
	bhi	.L2292
	ldr	r3, [fp, #-52]
	rsb	r3, r0, r3
	uxtb	r3, r3
.L2277:
	ldr	r2, [fp, #-52]
	cmp	r3, r2
	beq	.L2306
.L2279:
	ldr	r2, [fp, #-72]
	add	r3, r2, r3
	ldr	r2, [fp, #-60]
	add	r1, r2, r3, lsl #6
.L2280:
	cmp	r1, #0
	beq	.L2307
	ldr	r3, .L2308+4
	mov	r2, r5
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
.L2282:
	ldr	r3, [fp, #-52]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	cmp	r3, #6
	beq	.L2290
	ldr	r2, [fp, #-56]
	add	r7, r7, #64
	ldr	r3, [r9]
	add	r2, r2, #4
	str	r2, [fp, #-56]
	ldr	r2, [fp, #-52]
	cmp	r2, r3
	bcc	.L2289
.L2290:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-64]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, #4
	ldr	r3, [fp, #-68]
	add	r2, r2, #384
	str	r2, [fp, #-64]
	add	r3, r3, #24
	str	r3, [fp, #-68]
	bne	.L2270
	mov	r0, #0
	b	.L2300
.L2295:
	mov	r8, #8
	b	.L2273
.L2304:
	ldr	r1, .L2308+20
	ldr	r0, [r6, #2368]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-52]
	cmp	r0, r3
	bhi	.L2292
	ldr	r2, [fp, #-52]
	ldr	r1, [fp, #-48]
	rsb	r3, r0, r2
	cmp	r1, #1
	uxtb	r3, r3
	bls	.L2277
	cmp	r2, r3
	ldrne	r2, [fp, #-72]
	moveq	r2, #16
	ldrne	r1, [fp, #-60]
	addne	r2, r2, r3
	addne	r2, r2, #384
	ldrne	r2, [r1, r2, asl #2]
	ldr	r1, [fp, #-56]
	str	r2, [r1]
	ldr	r2, [fp, #-52]
	cmp	r3, r2
	bne	.L2279
.L2306:
	mov	r1, r2
	ldr	r0, [fp, #-48]
	bl	HEVC_GetScalingListDefaultAddress
	mov	r1, r0
	b	.L2280
.L2305:
	ldr	r1, .L2308+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2300
.L2307:
	ldr	r1, .L2308+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2300
.L2292:
	ldr	r1, .L2308+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2300
.L2302:
	ldr	r2, .L2308+36
	ldr	r1, .L2308+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2300
.L2309:
	.align	2
.L2308:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC248
	.word	.LC250
	.word	.LC251
	.word	.LC245
	.word	.LC249
	.word	.LC247
	.word	.LC246
	.word	.LANCHOR0+524
	.word	.LC61
	UNWIND(.fnend)
	.size	HEVC_DecScalingListData, .-HEVC_DecScalingListData
	.align	2
	.global	HEVC_ProcessSPS
	.type	HEVC_ProcessSPS, %function
HEVC_ProcessSPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	mov	r4, r1
	mov	r5, r0
	ldr	r1, .L2476
	ldr	r0, [r0, #2368]
	bl	HEVC_ue_v
	cmp	r0, #1
	mov	r6, r0
	str	r0, [r4, #60]
	beq	.L2311
	cmp	r0, #3
	bhi	.L2454
	mov	r2, r0
	ldr	r1, .L2476+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2313:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2454:
	ldr	r1, .L2476+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2311:
	ldr	r1, .L2476+12
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #8192
	str	r0, [r4, #64]
	bhi	.L2455
	ldr	r1, .L2476+16
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #4096
	str	r0, [r4, #68]
	bhi	.L2456
	ldr	r2, [r4, #428]
	ldr	r3, [r4, #64]
	cmp	r2, #120
	mul	r0, r3, r0
	beq	.L2319
	bgt	.L2320
	cmp	r2, #60
	beq	.L2321
	ble	.L2457
	cmp	r2, #90
	beq	.L2324
	cmp	r2, #93
	beq	.L2325
	cmp	r2, #63
	beq	.L2458
.L2318:
	ldr	r1, .L2476+20
	mov	r0, #1
	bl	dprint_vfmw
.L2449:
	mvn	r0, #0
	b	.L2313
.L2455:
	ldr	r1, .L2476+24
	mov	r0, r6
.L2451:
	bl	dprint_vfmw
	ldr	r3, .L2476+28
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2449
	mov	r3, #0
	ldr	r0, [r5, #252]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2321:
	mov	r2, #30720
	mov	r3, #122880
.L2326:
	cmp	r0, r2
	movls	r3, #16
	strls	r3, [r4, #184]
	bls	.L2331
	cmp	r0, r3, lsr #1
	movls	r3, #12
	strls	r3, [r4, #184]
	bls	.L2331
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, lsr #2
	movls	r3, #8
	movhi	r3, #6
	str	r3, [r4, #184]
.L2331:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r0, #0
	beq	.L2334
	ldr	r1, .L2476+32
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r6, .L2476+36
	ldr	r1, .L2476+40
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #548]
	mul	r0, r3, r0
	str	r0, [r4, #72]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r2, [r4, #60]
	ldr	r3, [r4, #64]
	ldr	r1, [r4, #72]
	add	r2, r6, r2, lsl #2
	rsb	r3, r1, r3
	ldr	r2, [r2, #548]
	mul	r0, r2, r0
	rsb	r3, r0, r3
	cmp	r3, #0
	str	r0, [r4, #76]
	blt	.L2459
	ldr	r1, .L2476+44
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r1, .L2476+48
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #564]
	mul	r0, r3, r0
	str	r0, [r4, #80]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #68]
	ldr	r1, [r4, #80]
	add	r3, r6, r3, lsl #2
	rsb	r2, r1, r2
	ldr	r3, [r3, #564]
	mul	r0, r3, r0
	rsb	r2, r0, r2
	cmp	r2, #0
	str	r0, [r4, #84]
	blt	.L2460
.L2334:
	ldr	r1, .L2476+52
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #2
	add	r2, r0, #8
	str	r2, [r4, #88]
	bhi	.L2461
	ldr	r1, .L2476+56
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #6
	add	r2, r0, #8
	str	r2, [r4, #96]
	bhi	.L2462
	ldr	r3, [r4, #88]
	ldr	r1, .L2476+60
	str	r3, [r5, #196]
	ldr	r3, [r4, #96]
	str	r3, [r5, #200]
	ldr	r0, [r4, #96]
	ldr	ip, [r4, #88]
	mov	r3, r0, asl #3
	mov	r2, ip, asl #3
	sub	r3, r3, r0, asl #1
	sub	r2, r2, ip, asl #1
	sub	r3, r3, #48
	sub	r2, r2, #48
	str	r3, [r4, #100]
	str	r2, [r4, #92]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #12
	bhi	.L2463
	add	r0, r0, #4
	mov	r1, #1
	str	r0, [r4, #116]
	mov	r8, #0
	str	r0, [r4, #120]
	mov	r7, r8
	ldr	r0, [r5, #2368]
	mov	r6, r4
	bl	BsGet
	mov	r9, r0
	b	.L2345
.L2339:
	ldr	r3, [r4, #52]
	add	r7, r7, #1
	add	r6, r6, #4
	cmp	r7, r3
	bhi	.L2344
.L2345:
	ldr	r1, .L2476+64
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L2476+68
	add	r0, r0, #1
	str	r0, [r6, #328]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r1, .L2476+72
	str	r0, [r6, #360]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r3, [r6, #328]
	cmp	r8, r3
	movcc	r8, r3
	cmp	r9, #0
	str	r0, [r6, #392]
	bne	.L2339
	ldr	r1, [r4, #52]
	add	r3, r7, #1
	cmp	r3, r1
	addls	r7, r7, #82
	addls	r7, r4, r7, lsl #2
	bhi	.L2344
.L2343:
	ldr	r2, [r4, #328]
	add	r3, r3, #1
	cmp	r3, r1
	str	r2, [r7, #4]!
	ldr	r2, [r4, #360]
	str	r2, [r7, #32]
	ldr	r2, [r4, #392]
	str	r2, [r7, #64]
	bls	.L2343
.L2344:
	ldr	r3, [r4, #184]
	ldr	r1, .L2476+76
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r4, #184]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L2464
	ldr	r1, .L2476+80
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r7, r0
	bhi	.L2465
	add	r0, r6, #3
	str	r0, [r4, #124]
	add	r6, r7, r0
	str	r6, [r4, #128]
	sub	r3, r6, #4
	cmp	r3, #2
	bhi	.L2466
	mov	r3, #1
	ldr	r8, [r4, #64]
	mov	r6, r3, asl r6
	mov	r3, r3, asl r0
	str	r6, [r4, #136]
	str	r6, [r4, #140]
	mov	r1, r6
	str	r6, [r4, #144]
	mov	r0, r8
	str	r3, [r4, #132]
	bl	__aeabi_uidivmod
	mov	r0, r8
	cmp	r1, #0
	mov	r1, r6
	beq	.L2348
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L2349:
	ldr	r8, [r4, #68]
	mov	r1, r6
	str	r0, [r4, #188]
	mov	r0, r8
	bl	__aeabi_uidivmod
	mov	r0, r8
	cmp	r1, #0
	mov	r1, r6
	beq	.L2350
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L2351:
	str	r0, [r4, #192]
	ldr	r1, .L2476+84
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L2467
	ldr	r1, .L2476+88
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #3
	bhi	.L2468
	ldr	r2, [r4, #124]
	add	r3, r6, #2
	str	r3, [r4, #148]
	cmp	r3, r2
	bcs	.L2469
	add	r3, r0, r3
	str	r3, [r4, #152]
	cmp	r3, #5
	bhi	.L2355
	ldr	r2, [r4, #128]
	cmp	r3, r2
	bhi	.L2355
	ldr	r1, .L2476+92
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	r3, [r4, #128]
	ldr	r2, [r4, #148]
	rsb	r3, r2, r3
	cmp	r0, r3
	str	r0, [r4, #164]
	bhi	.L2470
	ldr	r1, .L2476+96
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	ldr	ip, [r4, #148]
	ldr	r3, [r4, #128]
	rsb	r3, ip, r3
	cmp	r0, r3
	str	r0, [r4, #168]
	bhi	.L2358
	ldr	r1, [r4, #140]
	mov	r0, #1
	mov	r3, #0
	mov	r1, r1, lsr r7
	cmp	r1, r0, asl ip
	bls	.L2360
.L2361:
	add	r3, r3, #1
	add	r2, r3, ip
	cmp	r1, r0, asl r2
	bhi	.L2361
.L2360:
	add	r3, r3, r7
	mov	r1, #1
	str	r3, [r4, #172]
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3]
	cmp	r0, #0
	beq	.L2362
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #0
	bne	.L2471
.L2362:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #6]
	cmp	r6, #0
	bne	.L2363
	ldr	r2, [r4, #68]
	cmp	r2, #64
	bls	.L2472
.L2363:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #104]
	beq	.L2364
	mov	r1, #4
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #4
	add	r0, r0, #1
	str	r0, [r4, #108]
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldr	r1, .L2476+100
	add	r0, r0, #1
	str	r0, [r4, #112]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r7, r0
	bhi	.L2473
.L2365:
	ldr	r1, .L2476+104
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r6, r0
	bhi	.L2474
.L2366:
	add	r3, r7, #3
	str	r3, [r4, #156]
	add	r3, r6, r3
	str	r3, [r4, #160]
	cmp	r3, #5
	bhi	.L2367
	ldr	r2, [r4, #128]
	cmp	r3, r2
	bhi	.L2367
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	strb	r0, [r4, #7]
.L2364:
	ldr	r1, .L2476+108
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #64
	str	r0, [r4, #176]
	bhi	.L2369
	cmp	r0, #0
	addne	r7, r4, #2160
	movne	r6, #0
	addne	r7, r7, #4
	bne	.L2374
	b	.L2375
.L2373:
	ldr	r3, [r4, #176]
	cmp	r6, r3
	bcs	.L2375
.L2374:
	mov	r3, r6
	mov	r2, r7
	mov	r1, r4
	mov	r0, r5
	bl	HEVC_DecShortTermRefPicSet
	add	r6, r6, #1
	add	r7, r7, #164
	cmp	r0, #0
	beq	.L2373
	ldr	r1, .L2476+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2456:
	mov	r0, r6
	ldr	r1, .L2476+116
	b	.L2451
.L2320:
	cmp	r2, #156
	beq	.L2327
	bgt	.L2328
	cmp	r2, #150
	beq	.L2327
	cmp	r2, #153
	beq	.L2327
	cmp	r2, #123
	bne	.L2318
.L2319:
	mov	r2, #557056
	mov	r3, #2228224
	b	.L2326
.L2350:
	bl	__aeabi_uidiv
	b	.L2351
.L2348:
	bl	__aeabi_uidiv
	b	.L2349
.L2461:
	ldr	r1, .L2476+120
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2476+28
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L2449
	ldr	r1, [r4, #88]
	mov	r2, #0
	ldr	r0, [r5, #252]
	mov	r3, #8
	str	r2, [fp, #-44]
	sub	r2, fp, #44
	str	r1, [fp, #-40]
	mov	r1, #119
	blx	r6
	mvn	r0, #0
	b	.L2313
.L2375:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	beq	.L2372
	ldr	r1, .L2476+124
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #32
	str	r0, [r4, #180]
	bhi	.L2378
	cmp	r0, #0
	addne	r8, r4, #192
	addne	r7, r4, #12
	movne	r6, #0
	beq	.L2372
.L2380:
	ldr	r1, [r4, #116]
	add	r6, r6, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #4]!
	ldr	r0, [r5, #2368]
	bl	BsGet
	strb	r0, [r7, #1]!
	ldr	r3, [r4, #180]
	cmp	r6, r3
	bcc	.L2380
.L2372:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r3, #2
	str	r3, [r4, #2096]
	uxtb	r0, r0
	strb	r0, [r4, #11]
	cmp	r0, #0
	beq	.L2377
	mov	r2, r4
	add	r1, r4, #2064
	mov	r0, r5
	bl	HEVC_DecVuiParam
	cmp	r0, #0
	bne	.L2475
.L2377:
	ldr	r1, [r4, #68]
	ldrb	ip, [r4, #2067]	@ zero_extendqisi2
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #2080]
	mla	ip, ip, r1, r1
	ldr	r0, [r4, #2072]
	ldr	r1, [r4, #2076]
	str	ip, [sp]
	bl	HEVC_GetDar
	mov	r1, #1
	str	r0, [r4, #2068]
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #12]
	cmp	r0, #0
	bne	.L2447
.L2383:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r4]
	b	.L2313
.L2382:
	ldr	r0, [r5, #2368]
	bl	BsGet
.L2447:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2382
	b	.L2383
.L2328:
	cmp	r2, #183
	beq	.L2329
	cmp	r2, #186
	beq	.L2329
	cmp	r2, #180
	bne	.L2318
.L2329:
	mov	r2, #8912896
	mov	r3, #35651584
	b	.L2326
.L2457:
	cmp	r2, #0
	beq	.L2323
	cmp	r2, #30
	bne	.L2318
.L2323:
	mov	r2, #9216
	mov	r3, #36864
	b	.L2326
.L2324:
	mov	r2, #138240
	mov	r3, #552960
	b	.L2326
.L2458:
	mov	r2, #61440
	mov	r3, #245760
	b	.L2326
.L2325:
	mov	r2, #245760
	mov	r3, #983040
	b	.L2326
.L2327:
	mov	r2, #2228224
	mov	r3, #8912896
	b	.L2326
.L2472:
	ldr	r1, .L2476+128
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2476+28
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2449
	ldr	r0, [r5, #252]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	b	.L2313
.L2471:
	add	r1, r4, #432
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	beq	.L2362
	ldr	r1, .L2476+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2355:
	ldr	r1, .L2476+136
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2474:
	mov	r2, r0
	ldr	r1, .L2476+140
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2366
.L2473:
	mov	r2, r0
	ldr	r1, .L2476+144
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2365
.L2463:
	ldr	r1, .L2476+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2464:
	ldr	r1, .L2476+152
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2467:
	ldr	r1, .L2476+156
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2367:
	ldr	r1, .L2476+160
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2470:
	ldr	r1, .L2476+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2465:
	ldr	r1, .L2476+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2466:
	ldr	r1, .L2476+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2462:
	ldr	r1, .L2476+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2469:
	ldr	r1, .L2476+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2468:
	ldr	r1, .L2476+184
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2358:
	ldr	r1, .L2476+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2459:
	ldr	r1, .L2476+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2369:
	mov	r2, #64
	ldr	r1, .L2476+196
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2460:
	ldr	r1, .L2476+200
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2378:
	ldr	r1, .L2476+204
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2475:
	ldr	r1, .L2476+208
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2313
.L2477:
	.align	2
.L2476:
	.word	.LC252
	.word	.LC254
	.word	.LC253
	.word	.LC255
	.word	.LC257
	.word	.LC259
	.word	.LC256
	.word	g_event_report
	.word	.LC260
	.word	.LANCHOR0
	.word	.LC261
	.word	.LC263
	.word	.LC264
	.word	.LC266
	.word	.LC268
	.word	.LC270
	.word	.LC272
	.word	.LC273
	.word	.LC274
	.word	.LC275
	.word	.LC277
	.word	.LC280
	.word	.LC282
	.word	.LC286
	.word	.LC288
	.word	.LC292
	.word	.LC294
	.word	.LC297
	.word	.LC299
	.word	.LC258
	.word	.LC267
	.word	.LC300
	.word	.LC291
	.word	.LC290
	.word	.LC285
	.word	.LC295
	.word	.LC293
	.word	.LC271
	.word	.LC276
	.word	.LC281
	.word	.LC296
	.word	.LC287
	.word	.LC278
	.word	.LC279
	.word	.LC269
	.word	.LC284
	.word	.LC283
	.word	.LC289
	.word	.LC262
	.word	.LC298
	.word	.LC265
	.word	.LC301
	.word	.LC302
	UNWIND(.fnend)
	.size	HEVC_ProcessSPS, .-HEVC_ProcessSPS
	.align	2
	.global	HEVC_DecSPS
	.type	HEVC_DecSPS, %function
HEVC_DecSPS:
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
	ldr	r9, .L2499
	mov	r4, r0
	ldr	r0, [r9]
	cmp	r0, #0
	beq	.L2492
	ldr	r7, .L2499+4
	mov	r2, #8
	mov	r1, #0
	sub	r0, fp, #60
	ldr	r3, [r7, #48]
	blx	r3
	mov	r1, #4
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r2, [r4, #156]
	cmp	r2, r0
	mov	r8, r0
	bls	.L2493
	ldr	r3, [r4, #2388]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L2494
	mov	r5, #0
	str	r5, [fp, #-64]
.L2482:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r3, r5
	mov	r2, #1
	sub	r1, fp, #60
	mov	r10, r0
	mov	r0, r4
	bl	HEVC_DecPTL
	subs	r3, r0, #0
	str	r3, [fp, #-68]
	bne	.L2495
	ldr	r1, .L2499+8
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r2, [r4, #160]
	cmp	r0, r2
	mov	r6, r0
	bcs	.L2496
	movw	r3, #12660
	ldr	r2, [r4, #2376]
	mul	r5, r3, r0
	uxtb	r1, r10
	str	r1, [fp, #-72]
	add	r2, r2, r5
	ldrb	r10, [r2, #1]	@ zero_extendqisi2
	cmp	r10, #0
	beq	.L2486
	ldr	r9, [r9]
	mov	r2, r3
	str	r3, [fp, #-76]
	add	r9, r9, #458752
	ldr	r3, [r7, #48]
	ldr	r1, [fp, #-68]
	mov	r0, r9
	ldr	r10, .L2499+4
	blx	r3
	ldr	r3, [fp, #-64]
	sub	r1, fp, #60
	mov	r2, #8
	ldr	r7, [r7, #52]
	add	r0, r9, #424
	str	r3, [r9, #52]
	ldrb	r3, [fp, #-72]	@ zero_extendqisi2
	str	r8, [r9, #48]
	strb	r3, [r9, #2]
	ldrb	r3, [fp, #-68]	@ zero_extendqisi2
	strb	r3, [r9, #46]
	blx	r7
	str	r6, [r9, #56]
	mov	r1, r9
	mov	r0, r4
	bl	HEVC_ProcessSPS
	ldr	r3, [fp, #-76]
	subs	r7, r0, #0
	bne	.L2497
	mov	r2, #1
	strb	r2, [r9]
	strb	r2, [r9, #1]
	mov	r1, r9
	ldr	r0, [r4, #2376]
	mov	r2, r3
	ldr	r3, [r10, #56]
	add	r0, r0, r5
	blx	r3
	ldr	r3, [r4, #2376]
	add	r5, r3, r5
	str	r5, [r4, #2384]
.L2480:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2494:
	mov	r1, #3
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r0, #8
	mov	r5, r0
	str	r0, [fp, #-64]
	bls	.L2482
	mov	r2, #8
	ldr	r1, .L2499+12
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L2480
.L2486:
	str	r8, [r2, #48]
	sub	r1, fp, #60
	ldr	r3, [r4, #2376]
	mov	r2, #8
	ldr	r0, [fp, #-64]
	add	r3, r3, r5
	str	r0, [r3, #52]
	ldr	r3, [r4, #2376]
	ldrb	r0, [fp, #-72]	@ zero_extendqisi2
	add	r3, r3, r5
	strb	r0, [r3, #2]
	ldr	r3, [r4, #2376]
	add	r3, r3, r5
	strb	r10, [r3, #46]
	ldr	r0, [r4, #2376]
	ldr	r3, [r7, #52]
	add	r0, r0, r5
	add	r0, r0, #424
	blx	r3
	ldr	r3, [r4, #2376]
	mov	r0, r4
	add	r3, r3, r5
	str	r6, [r3, #56]
	ldr	r1, [r4, #2376]
	add	r1, r1, r5
	bl	HEVC_ProcessSPS
	subs	r7, r0, #0
	bne	.L2498
	ldr	r3, [r4, #2376]
	mov	r2, #1
	mov	r0, r7
	strb	r2, [r3, r5]
	ldr	r3, [r4, #2376]
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2376]
	add	r5, r3, r5
	str	r5, [r4, #2384]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2496:
	ldr	r1, .L2499+16
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #160]
	cmp	r6, r2
	bcc	.L2491
	ldr	r3, .L2499+20
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2491
	str	r2, [fp, #-48]
	mov	r3, #8
	str	r6, [fp, #-52]
	sub	r2, fp, #52
	ldr	r0, [r4, #252]
	mov	r1, #109
	blx	r5
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2491:
	mvn	r7, #0
	b	.L2480
.L2495:
	ldr	r1, .L2499+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2480
.L2493:
	ldr	r1, .L2499+28
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L2480
.L2497:
	ldr	r3, [r4, #2376]
	mov	r2, r6
	ldr	r1, .L2499+32
	mov	r0, #1
	add	r5, r3, r5
	str	r5, [r4, #2384]
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2480
.L2492:
	ldr	r2, .L2499+36
	mvn	r7, #0
	ldr	r1, .L2499+40
	bl	dprint_vfmw
	b	.L2480
.L2498:
	mov	r2, r6
	ldr	r1, .L2499+44
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2376]
	mov	r2, #1
	strb	r2, [r3, r5]
	ldr	r3, [r4, #2376]
	add	r5, r3, r5
	strb	r10, [r5, #1]
	b	.L2480
.L2500:
	.align	2
.L2499:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC306
	.word	.LC304
	.word	.LC307
	.word	g_event_report
	.word	.LC305
	.word	.LC303
	.word	.LC308
	.word	.LANCHOR0+580
	.word	.LC61
	.word	.LC309
	UNWIND(.fnend)
	.size	HEVC_DecSPS, .-HEVC_DecSPS
	.align	2
	.global	HEVC_ProcessPPS
	.type	HEVC_ProcessPPS, %function
HEVC_ProcessPPS:
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
	mov	r4, r1
	mov	r7, #1
	mov	r5, r0
	strb	r7, [r4, #16]
	str	r7, [r4, #68]
	str	r7, [r4, #72]
	ldr	r1, .L2630
	ldr	r0, [r0, #2368]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r4, #32]
	blt	.L2502
	ldr	r3, [r5, #160]
	cmp	r0, r3
	bge	.L2502
	ldr	r3, [r5, #2376]
	movw	r6, #12660
	mla	r6, r6, r0, r3
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2609
	mov	r1, r7
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #2]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #4]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, r7
	str	r0, [r4, #36]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #3]
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldr	r1, .L2630+4
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #40]
	cmp	r0, #15
	bhi	.L2610
	ldr	r1, .L2630+8
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #44]
	cmp	r0, #15
	bhi	.L2611
	ldr	r1, .L2630+12
	ldr	r0, [r5, #2368]
	bl	HEVC_se_v
	add	r2, r0, #26
	str	r2, [r4, #48]
	ldr	r3, [r6, #92]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L2612
	mov	r1, r7
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #6]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	streq	r0, [r4, #52]
	bne	.L2613
.L2511:
	str	r0, [r4, #56]
	ldr	r1, .L2630+16
	ldr	r0, [r5, #2368]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #60]
	cmp	r3, #24
	bhi	.L2614
	ldr	r1, .L2630+20
	ldr	r0, [r5, #2368]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #64]
	cmp	r3, #24
	bhi	.L2615
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #13]
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #14]
	bne	.L2616
	ldr	r3, [r6, #188]
	strh	r3, [r4, #172]	@ movhi
	ldr	r3, [r6, #192]
	strh	r3, [r4, #212]	@ movhi
.L2550:
	ldr	r0, [r4, #68]
	cmp	r0, #0
	ble	.L2555
.L2549:
	ldr	ip, [r6, #140]
	add	r1, r4, #170
	mov	r3, #0
.L2554:
	ldrsh	r2, [r1, #2]!
	add	r3, r3, #1
	mul	r2, ip, r2
	cmp	r2, #64
	bhi	.L2553
	ldr	lr, [r6, #64]
	cmp	lr, #64
	bhi	.L2617
.L2553:
	cmp	r3, r0
	blt	.L2554
.L2555:
	ldr	r1, [r4, #72]
	cmp	r1, #0
	ble	.L2552
	ldr	r0, [r6, #140]
	ldrsh	r2, [r4, #212]
	mul	r2, r0, r2
	cmp	r2, #63
	addhi	r1, r1, #105
	addhi	r3, r4, #212
	addhi	r1, r4, r1, lsl #1
	bhi	.L2558
	b	.L2556
.L2559:
	ldrsh	r2, [r3, #2]!
	mul	r2, r0, r2
	cmp	r2, #63
	bls	.L2556
.L2558:
	cmp	r3, r1
	bne	.L2559
.L2552:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #17]
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #18]
	cmp	r0, #0
	bne	.L2618
.L2561:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #21]
	cmp	r0, #0
	beq	.L2564
	add	r1, r4, #256
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	bne	.L2619
.L2564:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldr	r1, .L2630+24
	strb	r0, [r4, #22]
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	add	r2, r0, #2
	str	r2, [r4, #84]
	cmp	r2, #1
	ble	.L2565
	ldr	r3, [r6, #128]
	cmp	r2, r3
	bhi	.L2565
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #23]
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #24]
	cmp	r0, #0
	bne	.L2596
	b	.L2569
.L2568:
	ldr	r0, [r5, #2368]
	bl	BsGet
	strb	r0, [r4, #25]
.L2596:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2568
.L2569:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2613:
	ldr	r1, .L2630+28
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #52]
	bls	.L2511
	mov	r0, r7
	ldr	r1, .L2630+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2616:
	ldr	r1, .L2630+36
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #19
	add	r2, r0, #1
	str	r2, [r4, #68]
	bhi	.L2620
	ldr	r1, .L2630+40
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	cmp	r0, #21
	add	r3, r0, #1
	str	r3, [r4, #72]
	bhi	.L2621
	ldr	r2, [r4, #68]
	cmp	r2, #10
	bgt	.L2622
	cmp	r3, #11
	ble	.L2519
	ldr	r1, .L2630+44
	mov	r2, #11
.L2606:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2630+48
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2601
.L2603:
	mov	r3, #0
	ldr	r0, [r5, #252]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
.L2597:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2556:
	ldr	r1, .L2630+52
.L2605:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2630+48
	ldr	r4, [r3]
	cmp	r4, #0
	bne	.L2603
.L2601:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2617:
	ldr	r1, .L2630+56
	b	.L2605
.L2612:
	mov	r0, r7
	ldr	r1, .L2630+60
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2519:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	ldr	r7, [r4, #68]
	uxtb	r0, r0
	strb	r0, [r4, #15]
	cmp	r0, #0
	bne	.L2533
	cmp	r7, #1
	addgt	r9, r4, #86
	movgt	r8, r0
	bgt	.L2531
	b	.L2623
.L2625:
	cmp	r3, r2
	bhi	.L2529
	ldr	r7, [r4, #68]
	add	r8, r8, #1
	sub	r3, r7, #1
	cmp	r3, r8
	ble	.L2624
.L2531:
	ldr	r1, .L2630+64
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r9, #2]!	@ movhi
	ldr	r2, [r6, #188]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2625
.L2529:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r8
	ldr	r1, .L2630+68
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2622:
	mov	r3, r2
	ldr	r1, .L2630+72
	mov	r2, #10
	b	.L2606
.L2618:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #19]
	ldr	r0, [r5, #2368]
	bl	BsGet
	uxtb	r7, r0
	strb	r7, [r4, #20]
	cmp	r7, #0
	bne	.L2561
	ldr	r1, .L2630+76
	ldr	r0, [r5, #2368]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #76]
	bhi	.L2626
.L2563:
	ldr	r1, .L2630+80
	ldr	r0, [r5, #2368]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #80]
	bls	.L2561
	ldr	r1, .L2630+84
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #80]
	b	.L2561
.L2533:
	cmp	r7, #0
	addgt	r3, r4, #170
	movgt	r8, #0
	ble	.L2523
.L2541:
	ldr	r10, [r6, #188]
	add	r8, r8, #1
	mov	r1, r7
	str	r3, [fp, #-48]
	mul	r0, r10, r8
	bl	__aeabi_uidiv
	mov	r1, r7
	mov	r9, r0
	sub	r0, r8, #1
	mul	r0, r10, r0
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	cmp	r8, r7
	rsb	r0, r0, r9
	strh	r0, [r3, #2]!	@ movhi
	bne	.L2541
.L2523:
	ldr	r10, [r4, #72]
	cmp	r10, #0
	addgt	r3, r4, #210
	movgt	r8, #0
	ble	.L2540
.L2542:
	ldr	r2, [r6, #192]
	add	r8, r8, #1
	mov	r1, r10
	str	r3, [fp, #-52]
	mul	r0, r2, r8
	str	r2, [fp, #-48]
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-48]
	mov	r1, r10
	mov	r9, r0
	sub	r0, r8, #1
	mul	r0, r0, r2
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-52]
	cmp	r8, r10
	rsb	r0, r0, r9
	strh	r0, [r3, #2]!	@ movhi
	bne	.L2542
.L2540:
	cmp	r7, #1
	bne	.L2548
	ldr	r0, [r4, #72]
	cmp	r0, #1
	beq	.L2549
.L2548:
	mov	r1, #1
	ldr	r0, [r5, #2368]
	bl	BsGet
	strb	r0, [r4, #16]
	b	.L2550
.L2502:
	mov	r2, r0
	ldr	r1, .L2630+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2609:
	mov	r2, r0
	ldr	r1, .L2630+92
	mov	r0, r7
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2610:
	mov	r0, r7
	ldr	r1, .L2630+96
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2611:
	mov	r0, r7
	ldr	r1, .L2630+100
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2614:
	ldr	r1, .L2630+104
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2615:
	ldr	r1, .L2630+108
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2565:
	ldr	r1, .L2630+112
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2601
.L2624:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	ble	.L2527
.L2526:
	add	r8, r4, #126
	mov	r7, #0
	b	.L2538
.L2628:
	cmp	r3, r2
	bhi	.L2536
	ldr	r3, [r4, #72]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L2627
.L2538:
	ldr	r1, .L2630+116
	ldr	r0, [r5, #2368]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #192]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2628
.L2536:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r7
	ldr	r1, .L2630+120
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2620:
	mov	r3, #20
	ldr	r1, .L2630+124
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2626:
	ldr	r1, .L2630+128
	mov	r0, #1
	bl	dprint_vfmw
	str	r7, [r4, #76]
	b	.L2563
.L2627:
	ldr	r7, [r4, #68]
.L2527:
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2533
.L2534:
	sub	r2, r7, #1
	ldrh	r3, [r6, #188]
	add	ip, r4, r7, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #170]	@ movhi
	ble	.L2543
	add	r8, r7, #42
	add	r1, r4, #86
	add	lr, r4, #170
	add	r8, r4, r8, lsl #1
.L2544:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #170]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #170]	@ movhi
	bne	.L2544
.L2543:
	sxth	r3, r3
	cmp	r3, #0
	ble	.L2629
	ldr	r1, [r4, #72]
	ldrh	r3, [r6, #192]
	sub	r2, r1, #1
	add	ip, r4, r1, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #210]	@ movhi
	ble	.L2546
	add	r8, r1, #62
	add	lr, r4, #210
	add	r1, r4, #126
	add	r8, r4, r8, lsl #1
.L2547:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #210]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #210]	@ movhi
	bne	.L2547
.L2546:
	sxth	r3, r3
	cmp	r3, #0
	bgt	.L2540
	ldr	r1, .L2630+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2621:
	mov	r2, r3
	ldr	r1, .L2630+136
	mov	r3, #22
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2619:
	ldr	r1, .L2630+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2623:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	bgt	.L2526
	b	.L2534
.L2629:
	ldr	r1, .L2630+144
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2597
.L2631:
	.align	2
.L2630:
	.word	.LC310
	.word	.LC313
	.word	.LC315
	.word	.LC317
	.word	.LC321
	.word	.LC323
	.word	.LC344
	.word	.LC319
	.word	.LC320
	.word	.LC325
	.word	.LC327
	.word	.LC330
	.word	g_event_report
	.word	.LC338
	.word	.LC337
	.word	.LC318
	.word	.LC331
	.word	.LC332
	.word	.LC329
	.word	.LC339
	.word	.LC341
	.word	.LC342
	.word	.LC311
	.word	.LC312
	.word	.LC314
	.word	.LC316
	.word	.LC322
	.word	.LC324
	.word	.LC345
	.word	.LC333
	.word	.LC334
	.word	.LC326
	.word	.LC340
	.word	.LC336
	.word	.LC328
	.word	.LC343
	.word	.LC335
	UNWIND(.fnend)
	.size	HEVC_ProcessPPS, .-HEVC_ProcessPPS
	.align	2
	.global	HEVC_DecPPS
	.type	HEVC_DecPPS, %function
HEVC_DecPPS:
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
	ldr	r6, .L2644
	mov	r4, r0
	ldr	r0, [r6]
	cmp	r0, #0
	beq	.L2639
	ldr	r1, .L2644+4
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r3, [r4, #164]
	cmp	r0, r3
	mov	r7, r0
	bcs	.L2640
	mov	r8, #1888
	ldr	r3, [r4, #2380]
	mul	r5, r8, r0
	add	r2, r3, r5
	ldrb	r10, [r3, r5]	@ zero_extendqisi2
	cmp	r10, #0
	bne	.L2641
	str	r0, [r2, #28]
	mov	r0, r4
	ldr	r1, [r4, #2380]
	add	r1, r1, r5
	bl	HEVC_ProcessPPS
	subs	r9, r0, #0
	bne	.L2642
	ldr	r3, [r4, #2380]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2380]
	strb	r2, [r3, r5]
.L2634:
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2641:
	ldr	r6, [r6]
	mov	r2, r8
	ldr	r10, .L2644+8
	mov	r1, #0
	add	r6, r6, #458752
	ldr	r3, [r10, #48]
	mov	r0, r6
	blx	r3
	str	r7, [r6, #28]
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ProcessPPS
	subs	r9, r0, #0
	bne	.L2643
	mov	r3, #1
	strb	r3, [r6, #1]
	strb	r3, [r6]
	mov	r2, r8
	ldr	r0, [r4, #2380]
	mov	r1, r6
	ldr	r3, [r10, #56]
	add	r0, r0, r5
	blx	r3
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2643:
	mov	r2, r7
	ldr	r1, .L2644+12
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	b	.L2634
.L2640:
	mov	r2, r0
	ldr	r1, .L2644+16
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	b	.L2634
.L2642:
	mov	r2, r7
	ldr	r1, .L2644+12
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2380]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2380]
	strb	r10, [r3, r5]
	b	.L2634
.L2639:
	ldr	r2, .L2644+20
	mvn	r9, #0
	ldr	r1, .L2644+24
	bl	dprint_vfmw
	b	.L2634
.L2645:
	.align	2
.L2644:
	.word	.LANCHOR1
	.word	.LC346
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC348
	.word	.LC347
	.word	.LANCHOR0+592
	.word	.LC61
	UNWIND(.fnend)
	.size	HEVC_DecPPS, .-HEVC_DecPPS
	.align	2
	.global	HEVC_DecPredWeightTable
	.type	HEVC_DecPredWeightTable, %function
HEVC_DecPredWeightTable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 136
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
	add	r4, r0, #4096
	ldr	r3, [r0, #2380]
	mov	r7, r0
	ldr	r2, [r4, #164]
	mov	r0, #1888
	ldr	r1, [r4, #148]
	ldr	r5, [r7, #2376]
	mla	r3, r0, r2, r3
	cmp	r1, #1
	ldr	r6, [r3, #32]
	beq	.L2712
	cmp	r1, #0
	bne	.L2650
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2650
.L2648:
	ldr	r1, .L2723
	ldr	r0, [r7, #2368]
	bl	HEVC_ue_v
	cmp	r0, #7
	str	r0, [r4, #284]
	bhi	.L2713
	movw	r9, #12660
	mla	r9, r9, r6, r5
	ldr	r3, [r9, #60]
	cmp	r3, #0
	streq	r0, [r4, #416]
	bne	.L2714
.L2690:
	ldr	r3, [r4, #204]
	cmp	r3, #0
	subne	r3, fp, #172
	strne	r3, [fp, #-176]
	movne	r5, #0
	movne	r6, r3
	beq	.L2656
.L2657:
	mov	r1, #1
	ldr	r0, [r7, #2368]
	bl	BsGet
	ldr	r3, [r4, #204]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L2657
	ldr	r2, [r9, #60]
	cmp	r2, #0
	beq	.L2658
	cmp	r3, #0
	subne	r6, fp, #108
	movne	r5, #0
	beq	.L2656
.L2662:
	mov	r1, #1
	ldr	r0, [r7, #2368]
	bl	BsGet
	ldr	r3, [r4, #204]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L2662
.L2658:
	cmp	r3, #0
	beq	.L2656
	add	r6, r7, #4480
	add	r10, r7, #4544
	add	r6, r6, #36
	add	r10, r10, #44
	mov	r5, #0
	b	.L2673
.L2663:
	ldr	r2, [r4, #284]
	mov	r3, #1
	str	r1, [r6, #-132]
	mov	r2, r3, asl r2
	str	r2, [r6]
.L2665:
	ldr	r2, [r9, #60]
	cmp	r2, #0
	beq	.L2667
	sub	r2, fp, #108
	ldr	r2, [r2, r5, asl #2]
	cmp	r2, #0
	bne	.L2668
	ldr	r1, [r4, #416]
	mov	r3, #1
	str	r2, [r10, #120]
	mov	r1, r3, asl r1
	str	r2, [r10, #124]
	str	r1, [r10, #-8]
	str	r1, [r10, #-4]
.L2667:
	ldr	r2, [r4, #204]
	add	r5, r5, #1
	add	r6, r6, #4
	add	r10, r10, #8
	cmp	r2, r5
	bls	.L2656
.L2673:
	ldr	r3, [fp, #-176]
	ldr	r1, [r3, r5, asl #2]
	cmp	r1, #0
	beq	.L2663
	ldr	r1, .L2723+4
	ldr	r0, [r7, #2368]
	bl	HEVC_se_v
	add	r2, r0, #128
	cmp	r2, #255
	bhi	.L2715
	ldr	r2, [r4, #284]
	mov	r3, #1
	ldr	r1, .L2723+8
	add	r0, r0, r3, asl r2
	str	r0, [r6]
	ldr	r0, [r7, #2368]
	bl	HEVC_se_v
	add	r2, r0, #128
	str	r0, [r6, #-132]
	cmp	r2, #255
	bls	.L2665
	mov	r2, r0
	ldr	r1, .L2723+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2712:
	ldrb	r3, [r3, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2648
.L2650:
	mov	r0, #0
.L2711:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2668:
	sub	r8, r10, #8
	str	r5, [fp, #-180]
	mov	r5, r4
.L2671:
	ldr	r1, .L2723+16
	mov	r4, r8
	ldr	r0, [r7, #2368]
	bl	HEVC_se_v
	ldr	r1, .L2723+20
	add	r3, r0, #128
	cmp	r3, #255
	bhi	.L2716
	ldr	r3, [r5, #416]
	mov	r2, #1
	add	r8, r8, #4
	add	r0, r0, r2, asl r3
	str	r0, [r8, #-4]
	ldr	r0, [r7, #2368]
	bl	HEVC_se_v
	add	r3, r0, #512
	cmp	r3, #1024
	bcs	.L2717
	ldr	r1, [r4]
	cmp	r10, r8
	ldr	r3, [r5, #416]
	mov	r1, r1, asl #7
	mov	r3, r1, asr r3
	rsb	r3, r3, #128
	add	r0, r0, r3
	ssat	r0, #8, r0
	str	r0, [r8, #124]
	bne	.L2671
	mov	r4, r5
	ldr	r5, [fp, #-180]
	b	.L2667
.L2656:
	ldr	r5, [r4, #148]
	cmp	r5, #0
	bne	.L2650
	ldr	r3, [r4, #208]
	cmp	r3, #0
	beq	.L2650
	sub	r3, fp, #172
	str	r3, [fp, #-176]
	mov	r6, r3
.L2674:
	mov	r1, #1
	ldr	r0, [r7, #2368]
	bl	BsGet
	ldr	r3, [r4, #208]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L2674
	ldr	r2, [r9, #60]
	cmp	r2, #0
	bne	.L2718
.L2675:
	cmp	r3, #0
	beq	.L2650
	add	r6, r7, #4800
	add	r10, r7, #4864
	add	r6, r6, #36
	add	r10, r10, #44
	mov	r5, #0
	b	.L2689
.L2679:
	ldr	r2, [r4, #284]
	mov	r3, #1
	str	r1, [r6, #-388]
	mov	r2, r3, asl r2
	str	r2, [r6]
.L2681:
	ldr	r2, [r9, #60]
	cmp	r2, #0
	beq	.L2683
	sub	r2, fp, #108
	ldr	r2, [r2, r5, asl #2]
	cmp	r2, #0
	bne	.L2684
	ldr	r1, [r4, #416]
	mov	r3, #1
	str	r2, [r10, #120]
	mov	r1, r3, asl r1
	str	r2, [r10, #124]
	str	r1, [r10, #-8]
	str	r1, [r10, #-4]
.L2683:
	ldr	r2, [r4, #208]
	add	r5, r5, #1
	add	r6, r6, #4
	add	r10, r10, #8
	cmp	r2, r5
	bls	.L2650
.L2689:
	ldr	r3, [fp, #-176]
	ldr	r1, [r3, r5, asl #2]
	cmp	r1, #0
	beq	.L2679
	ldr	r1, .L2723+24
	ldr	r0, [r7, #2368]
	bl	HEVC_se_v
	add	r2, r0, #128
	cmp	r2, #255
	bhi	.L2719
	ldr	r2, [r4, #284]
	mov	r3, #1
	ldr	r1, .L2723+28
	add	r0, r0, r3, asl r2
	str	r0, [r6]
	ldr	r0, [r7, #2368]
	bl	HEVC_se_v
	add	r2, r0, #128
	str	r0, [r6, #-388]
	cmp	r2, #255
	bls	.L2681
	ldr	r1, .L2723+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2684:
	sub	r8, r10, #8
	str	r5, [fp, #-180]
	mov	r5, r4
.L2687:
	ldr	r1, .L2723+36
	mov	r4, r8
	ldr	r0, [r7, #2368]
	bl	HEVC_se_v
	ldr	r1, .L2723+40
	add	r3, r0, #128
	cmp	r3, #255
	bhi	.L2720
	ldr	r3, [r5, #416]
	mov	r2, #1
	add	r8, r8, #4
	add	r0, r0, r2, asl r3
	str	r0, [r8, #-4]
	ldr	r0, [r7, #2368]
	bl	HEVC_se_v
	add	r3, r0, #512
	cmp	r3, #1024
	bcs	.L2721
	ldr	r1, [r4]
	cmp	r10, r8
	ldr	r3, [r5, #416]
	mov	r1, r1, asl #7
	mov	r3, r1, asr r3
	rsb	r3, r3, #128
	add	r3, r0, r3
	ssat	r3, #8, r3
	str	r3, [r8, #124]
	bne	.L2687
	mov	r4, r5
	ldr	r5, [fp, #-180]
	b	.L2683
.L2714:
	ldr	r1, .L2723+44
	ldr	r0, [r7, #2368]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #14
	bhi	.L2722
	ldr	r3, [r4, #284]
	add	r0, r0, r3
	str	r0, [r4, #416]
	cmp	r0, #7
	bls	.L2690
	ldr	r1, .L2723+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2716:
	ldr	r1, .L2723+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2717:
	ldr	r1, .L2723+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2718:
	cmp	r3, #0
	subne	r6, fp, #108
	movne	r5, #0
	beq	.L2650
.L2678:
	mov	r1, #1
	ldr	r0, [r7, #2368]
	bl	BsGet
	ldr	r3, [r4, #208]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L2678
	b	.L2675
.L2715:
	mov	r2, r0
	ldr	r1, .L2723+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2720:
	ldr	r1, .L2723+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2721:
	ldr	r1, .L2723+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2719:
	ldr	r1, .L2723+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2713:
	ldr	r1, .L2723+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2722:
	ldr	r1, .L2723+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2711
.L2724:
	.align	2
.L2723:
	.word	.LC349
	.word	.LC354
	.word	.LC356
	.word	.LC357
	.word	.LC358
	.word	.LC360
	.word	.LC362
	.word	.LC364
	.word	.LC365
	.word	.LC366
	.word	.LC368
	.word	.LC351
	.word	.LC353
	.word	.LC359
	.word	.LC361
	.word	.LC355
	.word	.LC367
	.word	.LC369
	.word	.LC363
	.word	.LC350
	.word	.LC352
	UNWIND(.fnend)
	.size	HEVC_DecPredWeightTable, .-HEVC_DecPredWeightTable
	.align	2
	.global	HEVC_DecSliceSegmentHeader
	.type	HEVC_DecSliceSegmentHeader, %function
HEVC_DecSliceSegmentHeader:
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
	UNWIND(.pad #60)
	sub	sp, sp, #60
	ldr	r3, [r0, #2388]
	add	r5, r0, #4096
	mov	r4, r0
	mov	r1, #1
	ldr	r0, [r0, #2368]
	ldr	r3, [r3, #24]
	str	r3, [fp, #-48]
	bl	BsGet
	ldr	r6, [r5, #156]
	sub	r3, r6, #16
	cmp	r3, #5
	movhi	r3, #0
	movls	r3, #1
	cmp	r3, #0
	str	r3, [fp, #-64]
	strb	r0, [r5, #128]
	bne	.L2979
.L2726:
	ldr	r1, .L3024
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r5, #164]
	ldr	r3, [r4, #164]
	blt	.L2728
	cmp	r0, r3
	bge	.L2728
	mov	r0, r4
	bl	HEVC_VpsSpsPpsCheck
	subs	r3, r0, #0
	str	r3, [fp, #-72]
	bne	.L2980
	ldr	r1, [r5, #164]
	mov	r7, #1888
	ldr	r2, [r4, #2380]
	movw	r8, #12660
	ldr	r3, [r4, #2376]
	mla	r7, r7, r1, r2
	ldrb	r1, [r7, #2]	@ zero_extendqisi2
	ldr	r2, [r7, #32]
	cmp	r1, #0
	mla	r8, r8, r2, r3
	bne	.L2981
.L2734:
	mov	r3, #0
	strb	r3, [r5, #129]
.L2735:
	ldr	r10, [r8, #140]
	ldr	r3, [r8, #144]
	cmp	r10, #0
	beq	.L2737
	cmp	r3, #0
	beq	.L2737
	ldr	r0, [r8, #68]
	mov	r1, r3
	add	r0, r3, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	mov	r1, r10
	mov	r9, r0
	ldr	r0, [r8, #64]
	add	r0, r10, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	ldr	r10, [r8, #172]
	mov	r1, #1
	mov	r10, r10, asl r1
	mov	r10, r1, asl r10
	mul	r0, r0, r9
	cmp	r0, r1
	ble	.L2868
	mov	r3, r1
	mov	r1, #0
.L2740:
	add	r1, r1, #1
	cmp	r0, r3, asl r1
	bgt	.L2740
.L2739:
	ldrb	r3, [r5, #128]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [fp, #-68]
	beq	.L2982
.L2741:
	ldrb	r10, [r5, #129]	@ zero_extendqisi2
	ldr	r3, [r4, #192]
	cmp	r10, #0
	str	r3, [r5, #140]
	beq	.L2983
.L2744:
	ldr	r3, [r7, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	bne	.L2836
.L2843:
	ldrb	r3, [r7, #23]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2984
.L2838:
	ldr	r3, [fp, #-68]
	cmp	r3, #0
	bne	.L2985
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [fp, #-64]
	beq	.L2854
	cmp	r3, #0
	beq	.L2855
	ldr	r3, [r5, #160]
	mov	r2, #1
	add	r3, r4, r3
	strb	r2, [r3, #5]
.L2852:
	ldr	r2, [r5, #140]
	ldr	r1, [fp, #-64]
	cmp	r2, #0
	moveq	r1, #0
	andne	r1, r1, #1
	cmp	r1, #0
	bne	.L2986
.L2853:
	mov	r2, #0
	strb	r2, [r3, #4]
.L2857:
	mov	r0, r4
	bl	HEVC_IsNewPic
	str	r0, [r5, #280]
	mov	r0, r4
	bl	HEVC_ReadByteAlignment
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L2964:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2981:
	ldrb	r3, [r5, #128]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2734
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	strb	r0, [r5, #129]
	b	.L2735
.L2983:
	ldr	r3, [r7, #36]
	cmp	r3, #0
	beq	.L2749
.L2748:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r3, [r7, #36]
	add	r10, r10, #1
	cmp	r3, r10
	bhi	.L2748
.L2749:
	ldr	r1, .L3024+4
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	cmp	r0, #2
	str	r0, [r5, #148]
	bhi	.L2987
	ldrb	r3, [r7, #4]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2988
.L2750:
	sub	r6, r6, #19
	cmp	r6, #1
	bhi	.L2989
	mov	r3, #0
	str	r3, [r5, #140]
	ldr	r3, [r4, #2344]
	cmp	r3, #0
	streq	r3, [r4, #192]
	ldr	r3, [r5, #152]
	cmp	r3, #0
	streq	r3, [r4, #188]
	ldrb	r3, [r8, #6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2972
.L2860:
	mov	r3, #0
	strb	r3, [r5, #132]
	str	r3, [fp, #-84]
.L2862:
	ldr	r3, [r5, #148]
	cmp	r3, #2
	bne	.L2990
.L2790:
	ldrb	r3, [r5, #132]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2812
	mov	r3, #1
	strb	r3, [r5, #136]
	mov	r3, #2
.L2815:
	ldrb	r2, [r7, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2819
	cmp	r3, #1
	beq	.L2822
.L2819:
	ldrb	r2, [r7, #11]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2810
	cmp	r3, #0
	bne	.L2810
.L2822:
	mov	r0, r4
	bl	HEVC_DecPredWeightTable
	cmp	r0, #0
	ldreq	r3, [r5, #148]
	bne	.L2991
.L2810:
	cmp	r3, #2
	beq	.L2823
	ldr	r1, .L3024+8
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	rsb	r3, r0, #4
	rsb	r2, r0, #5
	cmp	r3, #4
	str	r2, [r5, #176]
	bhi	.L2992
.L2823:
	ldr	r1, .L3024+12
	ldr	r0, [r4, #2368]
	bl	HEVC_se_v
	ldr	r2, [r7, #48]
	add	r2, r0, r2
	str	r2, [r5, #144]
	ldr	r3, [r8, #92]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L2993
	ldrb	r3, [r7, #9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2994
.L2825:
	ldrb	r3, [r7, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2969
	ldrb	r3, [r7, #19]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2995
.L2831:
	ldrb	r0, [r7, #20]	@ zero_extendqisi2
	strb	r0, [r5, #137]
	ldr	r3, [r7, #76]
	str	r3, [r5, #188]
	ldr	r3, [r7, #80]
	str	r3, [r5, #192]
.L2830:
	ldrb	r3, [r8, #6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2834
	ldrh	r2, [r5, #130]
	adds	r3, r2, #0
	movne	r3, #1
.L2834:
	ldrb	r2, [r7, #17]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2835
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L2996
.L2835:
	strb	r2, [r5, #138]
	b	.L2744
.L2985:
	ldr	r3, [r5, #160]
	add	r3, r4, r3
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2853
	b	.L2852
.L2979:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L2726
.L2982:
	ldr	r0, [r4, #2368]
	bl	BsGet
	str	r0, [r5, #168]
	cmp	r0, #0
	ldr	r2, [r8, #192]
	ldr	r3, [r8, #188]
	mul	r3, r3, r2
	blt	.L2743
	cmp	r3, r0
	bls	.L2743
	mul	r3, r10, r0
	str	r3, [fp, #-68]
	b	.L2741
.L2836:
	ldr	r1, .L3024+16
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r3, [r7, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	ldreq	r3, [r8, #192]
	subeq	r3, r3, #1
	mov	r6, r0
	beq	.L2840
	cmp	r3, #256
	ldreq	r2, [r7, #68]
	ldreq	r3, [r7, #72]
	ldrne	r3, [r8, #192]
	ldrne	r2, [r7, #68]
	mul	r3, r3, r2
	sub	r3, r3, #1
.L2840:
	cmp	r3, #255
	movcs	r3, #255
	cmp	r6, r3
	bhi	.L2997
	cmp	r6, #0
	beq	.L2843
	ldr	r1, .L3024+20
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	cmp	r0, #31
	add	r8, r0, #1
	movls	r9, #0
	bhi	.L2998
.L2845:
	add	r9, r9, #1
	mov	r1, r8
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r9, r6
	bne	.L2845
	ldrb	r3, [r7, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2838
.L2984:
	ldr	r1, .L3024+24
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	cmp	r0, #256
	mov	r7, r0
	bhi	.L2999
	ldr	r0, [r4, #2368]
	bl	BsResidBits
	cmp	r7, r0
	bhi	.L2849
	cmp	r7, #0
	movne	r6, #0
	beq	.L2838
.L2851:
	add	r6, r6, #1
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	cmp	r6, r7
	bne	.L2851
	b	.L2838
.L2989:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3000
	ldr	r3, [r8, #116]
	mov	r2, #1
	ldr	r6, [r4, #188]
	mov	r3, r2, asl r3
	str	r3, [fp, #-80]
	mov	r1, r3
	mov	r0, r6
	bl	__aeabi_uidivmod
	cmp	r1, #0
	rsb	r3, r1, r6
	streq	r1, [fp, #-76]
	beq	.L2754
	ldr	r2, [fp, #-80]
	cmp	r1, r2, lsr #1
	mov	r2, #0
	str	r2, [fp, #-76]
	bcs	.L2867
.L2754:
	ldr	r2, [r5, #156]
	ldr	r1, [fp, #-48]
	sub	r2, r2, #16
	cmp	r2, #2
	ldr	r2, [fp, #-76]
	add	r9, r4, r1, lsl #2
	movls	r3, #0
	add	r3, r3, r2
	str	r3, [r5, #140]
	ldr	r2, [r9, #212]
	cmp	r3, r2
	bge	.L2756
	ldrb	r0, [r5, #128]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L3001
.L2756:
	ldr	r3, [r4, #2344]
	cmp	r3, #0
	ldreq	r3, [r5, #140]
	streq	r3, [r4, #192]
	ldr	r3, [r5, #152]
	cmp	r3, #0
	bne	.L2758
	ldr	r3, [r5, #156]
	cmp	r3, #15
	bhi	.L2759
	tst	r3, #1
	movne	r2, #1
	beq	.L2759
.L2760:
	sub	r3, r3, #7
	bics	r3, r3, #2
	andne	r3, r2, #1
	moveq	r3, #0
	cmp	r3, #0
	ldrne	r3, [r5, #140]
	strne	r3, [r4, #188]
.L2758:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	beq	.L2761
	ldr	r3, [r8, #176]
	mov	r1, #0
	cmp	r3, #1
	movhi	r2, #1
	bls	.L2763
.L2765:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L2765
	cmp	r1, #0
	bne	.L3002
.L2766:
	mov	r2, #164
	add	r0, r5, #1056
	mla	r1, r2, r1, r8
	add	r3, r4, #5120
	add	r0, r0, #4
	add	r3, r3, #36
	str	r3, [fp, #-84]
	add	r1, r1, #2160
	add	r1, r1, #4
	bl	memcpy
.L2764:
	ldrb	r3, [r8, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2768
	ldr	r3, [r8, #180]
	ldr	r6, [r5, #1064]
	cmp	r3, #0
	ldr	r2, [r5, #1060]
	streq	r3, [fp, #-48]
	add	r6, r6, r2
	streq	r3, [fp, #-56]
	bne	.L3003
.L2769:
	ldr	r1, .L3024+28
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r2, [r5, #1060]
	ldr	r3, [r5, #1064]
	ldr	ip, [fp, #-48]
	add	r1, r3, r2
	add	r0, r0, ip
	str	r0, [fp, #-60]
	add	r1, r1, r0
	cmp	r1, #16
	bhi	.L3004
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	add	r3, r6, r3
	str	r3, [fp, #-88]
	beq	.L2785
	ldr	r2, [fp, #-88]
	str	r7, [fp, #-92]
	add	r9, r2, #5120
	add	r3, r2, #1072
	add	r9, r9, #47
	add	r3, r3, #5
	add	r2, r4, r9
	add	r10, r4, r3, lsl #2
	mov	r1, r2
	mov	r2, #0
	mov	r9, r2
	str	r2, [fp, #-52]
	mov	r7, r1
	b	.L2784
.L3008:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	ldreq	r0, [fp, #-56]
	bne	.L3005
.L2776:
	add	r1, r8, r0
	add	r0, r8, r0, lsl #2
	ldrb	r1, [r1, #13]	@ zero_extendqisi2
	ldr	r6, [r0, #196]
	strb	r1, [r7]
.L2779:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L3006
	ldr	r3, [fp, #-48]
	str	r6, [r10, #944]
	cmp	r9, r3
	cmpne	r9, #0
	ldr	r3, [fp, #-52]
	str	r0, [r10]
	ldr	r1, [r5, #140]
	moveq	r3, #0
	str	r3, [fp, #-52]
	rsb	r6, r1, r6
	str	r6, [r10, #876]
.L2782:
	ldr	r3, [fp, #-60]
	add	r9, r9, #1
	sub	r10, r10, #4
	sub	r7, r7, #1
	cmp	r9, r3
	beq	.L3007
.L2784:
	ldr	r3, [fp, #-48]
	cmp	r3, r9
	bhi	.L3008
	ldr	r1, [r8, #120]
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	mov	r6, r0
	ldr	r0, [r4, #2368]
	bl	BsGet
	strb	r0, [r7]
	b	.L2779
.L2854:
	cmp	r3, #0
	beq	.L2855
	ldr	r3, [r5, #160]
	ldrb	r2, [fp, #-68]	@ zero_extendqisi2
	add	r3, r4, r3
	strb	r2, [r3, #5]
	b	.L2853
.L2986:
	ldr	r2, [r5, #156]
	cmp	r2, #21
	moveq	r2, #1
	streqb	r2, [r3, #4]
	bne	.L2853
	b	.L2857
.L3000:
	ldr	r1, [r8, #120]
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r3, [r8, #116]
	mov	r2, #1
	ldr	r6, [r4, #188]
	mov	r3, r2, asl r3
	str	r3, [fp, #-80]
	mov	r1, r3
	mov	r9, r0
	str	r0, [fp, #-76]
	mov	r0, r6
	bl	__aeabi_uidivmod
	cmp	r9, r1
	rsb	r3, r1, r6
	bcs	.L2753
	ldr	r2, [fp, #-76]
	ldr	r0, [fp, #-80]
	rsb	r2, r2, r1
	cmp	r2, r0, lsr #1
	bcc	.L2753
.L2867:
	ldr	r2, [fp, #-80]
	add	r3, r3, r2
	b	.L2754
.L2759:
	sub	r2, r3, #16
	cmp	r2, #7
	movhi	r2, #0
	movls	r2, #1
	b	.L2760
.L3006:
	ldr	r1, .L3024+32
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-48]
	cmp	r9, #0
	cmpne	r9, r3
	ldrne	r3, [fp, #-52]
	addne	r0, r0, r3
	mov	r3, #1
	str	r3, [r10]
	ldr	r3, [fp, #-76]
	ldr	r1, [r5, #140]
	str	r0, [fp, #-52]
	rsb	ip, r3, r1
	ldr	r3, [fp, #-80]
	add	r6, ip, r6
	mls	r0, r3, r0, r6
	rsb	r1, r1, r0
	str	r1, [r10, #876]
	str	r0, [r10, #944]
	b	.L2782
.L3005:
	ldr	r1, [fp, #-72]
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r1, [r8, #180]
	sub	r1, r1, #1
	cmp	r0, #0
	blt	.L2778
	cmp	r1, r0
	bcs	.L2776
.L2778:
	str	r1, [sp]
	mov	r3, r0
	mov	r2, r9
	ldr	r1, .L3024+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L2990:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #133]
	cmp	r0, #0
	bne	.L3009
	ldr	r3, [r5, #148]
	ldr	r2, [r7, #40]
	cmp	r3, #0
	str	r2, [r5, #204]
	bne	.L2796
	ldr	r2, [r7, #44]
	mov	r9, r3
	mov	r6, r3
	str	r2, [r5, #208]
.L2797:
	ldr	r3, [fp, #-84]
	cmp	r3, #0
	beq	.L3010
	ldr	r3, [fp, #-84]
	ldr	r2, [r3, #8]
	cmp	r2, #16
	bhi	.L2800
	cmp	r2, #0
	moveq	r3, r2
	beq	.L2802
	ldr	r3, [fp, #-84]
	add	r2, r2, #11
	add	r1, r3, #11
	add	r2, r3, r2
	mov	r3, #0
.L2804:
	ldrb	r0, [r1, #1]!	@ zero_extendqisi2
	cmp	r0, #0
	addne	r3, r3, #1
	cmp	r1, r2
	bne	.L2804
	cmp	r3, #1
	movle	r2, #0
	movgt	r2, #1
.L2802:
	ldrb	r1, [r7, #22]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r2, #0
	andne	r2, r2, #1
	cmp	r2, #0
	beq	.L3011
	add	r2, r4, #5312
	add	r1, r4, #4224
	add	r2, r2, #8
	mov	r0, r4
	bl	HEVC_DecRefPicListsModification
	cmp	r0, #0
	bne	.L3012
.L2798:
	ldr	r3, [r5, #148]
	cmp	r3, #0
	beq	.L2864
.L2805:
	cmp	r3, #2
	beq	.L2790
.L2865:
	ldrb	r3, [r7, #5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3013
.L2806:
	ldrb	r3, [r5, #132]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r5, #148]
	beq	.L2815
	cmp	r3, #0
	beq	.L3014
	cmp	r3, #2
	mov	r3, #1
	strb	r3, [r5, #136]
	beq	.L2812
.L2811:
	ldr	r3, [r5, #204]
	cmp	r3, #1
	bls	.L2968
.L2814:
	ldr	r1, .L3024+40
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldrb	r2, [r5, #136]	@ zero_extendqisi2
	cmp	r2, #0
	str	r0, [r5, #172]
	bne	.L3015
	cmp	r9, #0
	subne	r6, r9, #1
	moveq	r6, r2
.L2817:
	cmp	r6, r0
	movcs	r3, #0
	movcc	r3, #1
	orrs	r3, r3, r0, lsr #31
	beq	.L2968
	mov	r3, r0
	str	r6, [sp]
	ldr	r1, .L3024+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L2968:
	ldr	r3, [r5, #148]
	b	.L2815
.L2855:
	ldr	r3, [r5, #160]
	add	r3, r4, r3
	b	.L2853
.L2969:
	ldrb	r0, [r5, #137]	@ zero_extendqisi2
	b	.L2830
.L3007:
	ldr	r7, [fp, #-92]
.L2785:
	ldr	r3, [fp, #-88]
	cmp	r3, #16
	str	r3, [r5, #1068]
	bhi	.L3016
.L2768:
	ldrb	r3, [r8, #9]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r5, #132]
	bne	.L3017
.L2787:
	ldrb	r3, [r8, #6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2862
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #130]
	ldr	r0, [r4, #2368]
	bl	BsGet
	strb	r0, [r5, #131]
	b	.L2862
.L3011:
	ldr	r3, [r5, #148]
	cmp	r3, #0
	bne	.L2865
.L2864:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r3, [r5, #148]
	strb	r0, [r5, #134]
	b	.L2805
.L2988:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	b	.L2750
.L2728:
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L3024+48
	mov	r0, #1
	ldr	r1, .L3024+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L2994:
	ldr	r1, .L3024+56
	ldr	r0, [r4, #2368]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #180]
	cmp	r3, #24
	bhi	.L3018
	ldr	r3, [r7, #60]
	add	r2, r0, r3
	add	r2, r2, #12
	cmp	r2, #24
	bhi	.L3019
	ldr	r1, .L3024+60
	ldr	r0, [r4, #2368]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #184]
	cmp	r3, #24
	bhi	.L3020
	ldr	r2, [r7, #64]
	add	r2, r0, r2
	add	r3, r2, #12
	cmp	r3, #24
	bls	.L2825
	ldr	r1, .L3024+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3013:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	strb	r0, [r5, #135]
	b	.L2806
.L2868:
	mov	r1, #0
	b	.L2739
.L2796:
	mov	r9, r0
	mov	r6, r0
	str	r0, [r5, #208]
.L2795:
	cmp	r3, #2
	bne	.L2797
	b	.L2798
.L2753:
	ldr	r2, [fp, #-76]
	cmp	r2, r1
	bls	.L2754
	rsb	r1, r1, r2
	ldr	r2, [fp, #-80]
	cmp	r1, r2, lsr #1
	rsbhi	r3, r2, r3
	b	.L2754
.L2972:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #130]
	ldr	r0, [r4, #2368]
	bl	BsGet
	strb	r0, [r5, #131]
	b	.L2860
.L2761:
	add	r6, r4, #5120
	ldr	r3, [r8, #176]
	add	r6, r6, #36
	mov	r1, r8
	mov	r0, r4
	mov	r2, r6
	bl	HEVC_DecShortTermRefPicSet
	cmp	r0, #0
	streq	r6, [fp, #-84]
	beq	.L2764
	ldr	r1, .L3024+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3009:
	ldr	r1, .L3024+72
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	add	r6, r0, #1
	cmp	r6, #16
	bhi	.L3021
	ldr	r3, [r5, #148]
	str	r6, [r5, #204]
	cmp	r3, #0
	movne	r9, #0
	strne	r9, [r5, #208]
	bne	.L2795
	ldr	r1, .L3024+76
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	add	r9, r0, #1
	cmp	r9, #16
	strls	r9, [r5, #208]
	ldrls	r3, [r5, #148]
	bls	.L2795
	mov	r2, r9
	mov	r3, #16
	ldr	r1, .L3024+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3002:
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r3, [r8, #176]
	subs	r1, r0, #0
	sublt	r3, r3, #1
	blt	.L2767
.L2763:
	sub	r3, r3, #1
	cmp	r3, r1
	bcs	.L2766
.L2767:
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L3024+84
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3014:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	ldr	r3, [r5, #148]
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r5, #136]
	beq	.L2823
	cmp	r0, #0
	bne	.L2811
	ldr	r2, [r5, #208]
	cmp	r2, #1
	bhi	.L2814
	b	.L2815
.L2812:
	mov	r3, #2
	b	.L2819
.L3015:
	cmp	r6, #0
	subne	r6, r6, #1
	b	.L2817
.L2999:
	mov	r2, r0
	ldr	r1, .L3024+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3016:
	ldr	r2, [fp, #-88]
	mov	r3, #16
	ldr	r1, .L3024+92
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L2737:
	mov	r2, r10
	ldr	r1, .L3024+96
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3017:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	strb	r0, [r5, #132]
	b	.L2787
.L2996:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	strb	r0, [r5, #138]
	b	.L2744
.L2995:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	tst	r0, #255
	beq	.L2831
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #137]
	cmp	r0, #0
	bne	.L2830
	ldr	r1, .L3024+100
	ldr	r0, [r4, #2368]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #188]
	bhi	.L3022
.L2832:
	ldr	r1, .L3024+104
	ldr	r0, [r4, #2368]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #192]
	bls	.L2969
	ldr	r1, .L3024+108
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #80]
	ldrb	r0, [r5, #137]	@ zero_extendqisi2
	str	r3, [r5, #192]
	b	.L2830
.L2980:
	ldr	r3, [r4, #236]
	mov	r0, r4
	cmp	r3, #0
	ldrne	r3, [r4, #192]
	str	r3, [r5, #140]
	bl	HEVC_IsNewPic
	ldr	r1, .L3024+112
	str	r0, [r5, #280]
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3003:
	ldr	r1, .L3024+116
	ldr	r0, [r4, #2368]
	bl	HEVC_ue_v
	ldr	r3, [r8, #180]
	cmp	r0, r3
	mov	r2, r0
	str	r0, [fp, #-48]
	bhi	.L3023
	cmp	r3, #1
	movls	r3, #0
	strls	r3, [fp, #-56]
	bls	.L2769
	mov	r2, #0
	mov	r1, r2
	mov	r2, #1
.L2771:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L2771
	str	r1, [fp, #-72]
	str	r1, [fp, #-56]
	b	.L2769
.L2993:
	ldr	r1, .L3024+120
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3001:
	ldr	r1, .L3024+124
	bl	dprint_vfmw
	b	.L2756
.L2743:
	mov	r2, r0
	ldr	r1, .L3024+128
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L2987:
	mov	r2, r0
	ldr	r1, .L3024+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L2800:
	mov	r3, #16
	ldr	r1, .L3024+136
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L2992:
	ldr	r1, .L3024+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L2997:
	mov	r2, r6
	ldr	r1, .L3024+144
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L2849:
	mov	r2, r0
	mov	r3, r7
	ldr	r1, .L3024+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3019:
	mov	r2, r0
	ldr	r1, .L3024+152
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3022:
	ldr	r1, .L3024+156
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #76]
	str	r3, [r5, #188]
	b	.L2832
.L2991:
	ldr	r1, .L3024+160
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3018:
	mov	r2, r0
	ldr	r1, .L3024+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3020:
	mov	r2, r0
	ldr	r1, .L3024+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3004:
	str	r0, [sp]
	mov	ip, #16
	ldr	r1, .L3024+172
	mov	r0, #1
	str	ip, [sp, #4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3010:
	ldr	r1, .L3024+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3025:
	.align	2
.L3024:
	.word	.LC370
	.word	.LC375
	.word	.LC397
	.word	.LC399
	.word	.LC411
	.word	.LC413
	.word	.LC415
	.word	.LC382
	.word	.LC385
	.word	.LC384
	.word	.LC394
	.word	.LC395
	.word	.LANCHOR0+604
	.word	.LC371
	.word	.LC401
	.word	.LC404
	.word	.LC406
	.word	.LC378
	.word	.LC387
	.word	.LC389
	.word	.LC390
	.word	.LC379
	.word	.LC416
	.word	.LC386
	.word	.LC373
	.word	.LC407
	.word	.LC409
	.word	.LC410
	.word	.LC372
	.word	.LC380
	.word	.LC400
	.word	.LC377
	.word	.LC374
	.word	.LC376
	.word	.LC392
	.word	.LC398
	.word	.LC412
	.word	.LC417
	.word	.LC403
	.word	.LC408
	.word	.LC396
	.word	.LC402
	.word	.LC405
	.word	.LC383
	.word	.LC391
	.word	.LC414
	.word	.LC388
	.word	.LC381
	.word	.LC393
.L2998:
	mov	r2, r8
	ldr	r1, .L3024+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3021:
	mov	r2, r6
	mov	r3, #16
	ldr	r1, .L3024+184
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3023:
	ldr	r1, .L3024+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
.L3012:
	ldr	r1, .L3024+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2964
	UNWIND(.fnend)
	.size	HEVC_DecSliceSegmentHeader, .-HEVC_DecSliceSegmentHeader
	.align	2
	.global	HEVC_ClearCurrNal
	.type	HEVC_ClearCurrNal, %function
HEVC_ClearCurrNal:
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
	ldr	r1, [r0, #2388]
	mov	r4, r0
	cmp	r1, #0
	beq	.L3027
	ldr	r0, [r0, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3027:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearCurrNal, .-HEVC_ClearCurrNal
	.align	2
	.global	HEVC_FrameStoreRefFlg
	.type	HEVC_FrameStoreRefFlg, %function
HEVC_FrameStoreRefFlg:
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
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_FrameStoreRefFlg, .-HEVC_FrameStoreRefFlg
	.align	2
	.global	HEVC_ClearCurrSlice
	.type	HEVC_ClearCurrSlice, %function
HEVC_ClearCurrSlice:
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
	ldr	r1, [r0, #2388]
	mov	r4, r0
	cmp	r1, #0
	beq	.L3033
	ldr	r0, [r0, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3033:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearCurrSlice, .-HEVC_ClearCurrSlice
	.align	2
	.global	HEVC_ClearAllSlice
	.type	HEVC_ClearAllSlice, %function
HEVC_ClearAllSlice:
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
	ldr	r2, [r0, #168]
	mov	r5, r0
	cmp	r2, #0
	beq	.L3041
	mov	r4, #0
	mov	r6, r4
.L3040:
	ldr	r3, [r5, #2408]
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L3039
	ldr	r0, [r5, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r5, #2408]
	str	r6, [r3, r4, asl #2]
	ldr	r2, [r5, #168]
.L3039:
	add	r4, r4, #1
	cmp	r2, r4
	bhi	.L3040
.L3041:
	mov	r0, #0
	mov	r3, #2
	str	r0, [r5, #204]
	str	r0, [r5, #244]
	str	r0, [r5, #236]
	strb	r0, [r5, #11]
	str	r3, [r5, #176]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearAllSlice, .-HEVC_ClearAllSlice
	.align	2
	.global	HEVC_InitDPB
	.type	HEVC_InitDPB, %function
HEVC_InitDPB:
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
	mov	r5, r0
	mov	r8, r1
	bl	HEVC_ClearAllSlice
	add	r9, r5, #2608
	mov	r4, r5
	add	r9, r9, #8
	mov	r7, #17
	mov	r6, #0
.L3052:
	ldr	r3, [r9, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L3048
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L3048:
	ldr	r3, [r4, #2688]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3049
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L3049:
	ldr	r3, [r4, #2756]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3050
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L3050:
	ldr	r3, [r4, #2824]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3051
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L3051:
	subs	r7, r7, #1
	str	r6, [r4, #2824]
	str	r6, [r4, #2756]
	add	r4, r4, #4
	str	r6, [r4, #2684]
	str	r6, [r4, #2616]
	bne	.L3052
	ldr	r3, [r5, #2400]
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r5, #2596]
	cmp	r3, #17
	bhi	.L3090
.L3053:
	ldr	r3, .L3093
	mov	r4, #0
	mov	r1, r4
	mov	r2, #200
	str	r4, [r5, #2600]
	add	r0, r5, #12544
	ldr	r3, [r3, #48]
	str	r4, [r5, #2612]
	str	r4, [r5, #2616]
	str	r4, [r5, #2608]
	str	r4, [r5, #2604]
	blx	r3
	add	r2, r5, #2416
	add	r3, r5, #2480
	add	r1, r5, #12288
	add	r2, r2, #8
	add	r3, r3, #12
	mov	r0, r4
	mov	ip, #16
	str	r4, [r1, #260]
	str	ip, [r1, #256]
.L3054:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L3054
	add	lr, r5, #4096
	add	ip, r5, #2560
	mov	r0, r1
	str	r1, [lr, #196]
.L3055:
	str	r0, [r3, #4]!
	cmp	r3, ip
	mov	r2, #0
	bne	.L3055
	cmp	r8, r2
	str	r2, [lr, #200]
	bne	.L3056
	ldr	r3, [r5, #2416]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	beq	.L3056
.L3057:
	ldr	r1, [r5, #184]
	cmp	r1, #0
	addne	r2, r5, #2128
	movne	r3, #0
	addne	r2, r2, #12
	movne	r0, r3
	beq	.L3066
.L3065:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L3065
.L3066:
	ldr	r2, [r5, #168]
	cmp	r2, #0
	movne	r4, #0
	movne	r6, r4
	beq	.L3064
.L3068:
	ldr	r3, [r5, #2408]
	mov	r7, r4, asl #2
	ldr	r3, [r3, r4, asl #2]
	add	r4, r4, #1
	cmp	r3, #0
	mov	r1, r3
	beq	.L3067
	ldr	r0, [r5, #2388]
	cmp	r3, r0
	beq	.L3067
	ldr	r0, [r5, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r5, #2408]
	str	r6, [r3, r7]
	ldr	r2, [r5, #168]
.L3067:
	cmp	r2, r4
	bhi	.L3068
.L3064:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3056:
	mov	r4, #20
	mov	r0, r5
	str	r4, [r5, #180]
	str	r4, [r5, #184]
	bl	HEVC_ArrangeMem
	cmp	r0, #0
	beq	.L3058
	cmp	r0, #2
	beq	.L3091
	ldr	r2, .L3093+4
	mov	r0, #0
	ldr	r1, .L3093+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3090:
	mov	r4, #17
	ldr	r2, .L3093+4
	str	r4, [sp]
	mov	r3, r4
	ldr	r1, .L3093+12
	mov	r0, #1
	bl	dprint_vfmw
	str	r4, [r5, #2596]
	b	.L3053
.L3058:
	ldr	r0, [r5, #252]
	bl	FSP_GetTotalValidFsNum
	cmp	r0, #20
	movgt	r0, r4
	ble	.L3092
.L3061:
	str	r0, [r5, #180]
	b	.L3057
.L3091:
	add	r0, r5, #5568
	add	r0, r0, #16
	bl	ResetVoQueue
	mvn	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3092:
	ldr	r0, [r5, #252]
	bl	FSP_GetTotalValidFsNum
	b	.L3061
.L3094:
	.align	2
.L3093:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+632
	.word	.LC418
	.word	.LC151
	UNWIND(.fnend)
	.size	HEVC_InitDPB, .-HEVC_InitDPB
	.align	2
	.global	HEVC_ClearAllNal
	.type	HEVC_ClearAllNal, %function
HEVC_ClearAllNal:
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
	ldr	r2, [r0, #168]
	mov	r6, r0
	cmn	r2, #1
	beq	.L3099
	mov	r4, #0
	mov	r5, r4
	b	.L3098
.L3097:
	add	r3, r2, #1
	cmp	r3, r5
	bls	.L3099
.L3098:
	ldr	r1, [r6, #2412]
	add	r5, r5, #1
	add	r1, r1, r4
	add	r4, r4, #96
	ldr	r3, [r1, #32]
	cmp	r3, #1
	bne	.L3097
	ldr	r0, [r6, #252]
	bl	HEVC_ReleaseNAL
	ldr	r2, [r6, #168]
	add	r3, r2, #1
	cmp	r3, r5
	bhi	.L3098
.L3099:
	mov	r0, #0
	strb	r0, [r6, #7]
	str	r0, [r6, #148]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearAllNal, .-HEVC_ClearAllNal
	.align	2
	.global	HEVC_InitDecPara
	.type	HEVC_InitDecPara, %function
HEVC_InitDecPara:
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
	ldr	r1, .L3118
	mov	r7, r0
	mov	r0, #22
	mov	r5, #0
	bl	dprint_vfmw
	mov	r2, #1
	mvn	r3, #-2147483648
	strb	r2, [r7, #5]
	str	r3, [r7, #228]
	mov	r0, r7
	mov	r3, #-2147483647
	strb	r5, [r7, #4]
	str	r3, [r7, #212]
	add	r4, r7, #12800
	str	r3, [r7, #232]
	add	r4, r4, #24
	strb	r5, [r7, #10]
	mov	r6, r5
	bl	HEVC_ClearAllNal
	add	r0, r7, #5568
	add	r0, r0, #16
	ldr	r8, .L3118+4
	bl	ResetVoQueue
	mov	r9, #20
.L3103:
	strb	r5, [r4, #-80]
	mov	r3, #16
	str	r5, [r4, #-32]
	mov	r0, r4
	strb	r5, [r4, #-79]
	mov	r2, #640
	str	r5, [r4, #-72]
	mov	r1, #0
	strb	r5, [r4, #-78]
	str	r9, [r4, #-60]
	str	r3, [r4, #-56]
	ldr	r3, [r8, #48]
	blx	r3
	str	r6, [r4, #148]
	add	r6, r6, #1
	sub	r3, r4, #80
	cmp	r6, #20
	str	r5, [r4, #-24]
	str	r3, [r4, #-8]
	add	r4, r4, #720
	bne	.L3103
	add	r3, r7, #2128
	add	r2, r7, #2208
	add	r3, r3, #12
	add	r2, r2, #12
	mov	r1, #0
.L3104:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L3104
	ldr	r3, [r7, #168]
	cmp	r3, #0
	beq	.L3105
	mov	r3, #0
	mov	r1, r3
.L3106:
	ldr	r2, [r7, #2408]
	str	r1, [r2, r3, asl #2]
	add	r3, r3, #1
	ldr	r2, [r7, #168]
	cmp	r2, r3
	bhi	.L3106
.L3105:
	ldr	r3, [r8, #48]
	mov	r2, #200
	mov	r1, #0
	add	r0, r7, #12544
	blx	r3
	add	r3, r7, #12288
	add	ip, r7, #2816
	add	r0, r7, #2672
	add	r1, r7, #2608
	add	ip, ip, #4
	add	r0, r0, #12
	add	r1, r1, #8
	add	lr, r7, #2752
	mov	r2, #16
	str	r2, [r3, #256]
	mov	r2, #17
	mov	r3, #0
.L3107:
	subs	r2, r2, #1
	str	r3, [ip, #4]!
	str	r3, [lr, #4]!
	str	r3, [r0, #4]!
	str	r3, [r1, #4]!
	bne	.L3107
	add	r3, r7, #2480
	add	r1, r7, #2416
	add	r3, r3, #12
	add	r1, r1, #8
	add	ip, r7, #2560
	mov	r0, r2
	mov	lr, #17
	str	r2, [r7, #2600]
	str	r2, [r7, #2604]
	str	r2, [r7, #2608]
	str	r2, [r7, #2612]
	str	r2, [r7, #2616]
	str	lr, [r7, #2596]
.L3108:
	str	r0, [r3, #4]!
	cmp	r3, ip
	str	r0, [r1, #4]!
	mov	r4, #0
	bne	.L3108
	mov	r6, #2
	mov	r1, r4
	str	r4, [r7, #2388]
	movw	r2, #1356
	str	r4, [r7, #204]
	add	r0, r7, #4224
	str	r4, [r7, #244]
	add	r5, r7, #2560
	str	r4, [r7, #236]
	add	r5, r5, #4
	str	r6, [r7, #176]
	mov	r9, #16
	ldr	r3, [r8, #48]
	blx	r3
	add	r2, r7, #4096
	mov	r3, #1
	mov	r1, r4
	str	r6, [r2, #148]
	mov	lr, #256
	str	r3, [r2, #280]
	movw	ip, #1025
	mov	r2, #20
	strb	r3, [r7, #3]
	str	r6, [r7, #2236]
	mov	r3, #8
	strb	r4, [r7, #6]
	mov	r0, r5
	str	r4, [r7, #172]
	mov	r6, #64
	str	r2, [r7, #180]
	str	r2, [r7, #184]
	mov	r2, #32
	str	r3, [r7, #196]
	str	r3, [r7, #200]
	mov	r3, #6
	ldr	r4, [r8, #48]
	str	r9, [r7, #336]
	str	r6, [r7, #340]
	str	lr, [r7, #344]
	str	ip, [r7, #348]
	str	r3, [r7, #2224]
	str	r3, [r7, #2228]
	str	r3, [r7, #2232]
	blx	r4
	str	r5, [r7, #2368]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3119:
	.align	2
.L3118:
	.word	.LC419
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_InitDecPara, .-HEVC_InitDecPara
	.align	2
	.global	HEVC_ClearCurrPic
	.type	HEVC_ClearCurrPic, %function
HEVC_ClearCurrPic:
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
	bl	HEVC_ClearAllSlice
	ldr	r3, [r4, #3580]
	cmp	r3, #0
	beq	.L3121
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #252]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3580]
	mov	r3, #0
	str	r3, [r2, #48]
	str	r3, [r4, #3580]
.L3121:
	mov	r0, #0
	strb	r0, [r4, #3521]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearCurrPic, .-HEVC_ClearCurrPic
	.align	2
	.global	HEVC_ClearAll
	.type	HEVC_ClearAll, %function
HEVC_ClearAll:
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
	mov	r5, r1
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	cmp	r5, #0
	bne	.L3128
	add	r0, r4, #5568
	add	r0, r0, #16
	bl	ResetVoQueue
	ldr	r0, [r4, #252]
	bl	FSP_EmptyInstance
.L3127:
	mov	r0, r4
	bl	HEVC_InitDecPara
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3128:
	add	r1, r4, #5568
	ldr	r0, [r4, #252]
	add	r1, r1, #16
	bl	FSP_ClearNotInVoQueue
	b	.L3127
	UNWIND(.fnend)
	.size	HEVC_ClearAll, .-HEVC_ClearAll
	.align	2
	.global	HEVC_InitPic
	.type	HEVC_InitPic, %function
HEVC_InitPic:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	mov	r4, r0
	ldr	r2, [r4, #272]
	add	r0, r0, #4096
	ldr	r3, [r4, #264]
	ldr	r8, [r4, #268]
	str	r2, [fp, #-56]
	ldr	r2, [r4, #280]
	str	r3, [fp, #-48]
	ldr	r3, [r0, #164]
	str	r2, [fp, #-52]
	ldr	r2, [r4, #284]
	cmp	r3, #0
	ldr	r9, [r4, #276]
	str	r2, [fp, #-60]
	blt	.L3146
	ldr	r2, [r4, #164]
	cmp	r3, r2
	bge	.L3146
	ldr	r2, [r4, #2380]
	mov	r1, #1888
	movw	r7, #12660
	ldr	ip, [r4, #2376]
	ldr	r0, [r0, #160]
	mla	r2, r1, r3, r2
	mov	lr, ip
	add	r0, r4, r0, lsl #2
	str	ip, [fp, #-72]
	ldr	ip, [r4, #2372]
	ldr	r1, [r2, #32]
	mul	r7, r7, r1
	add	r6, lr, r7
	ldr	r1, [r6, #48]
	str	r3, [r0, #224]
	ldr	lr, [r2, #32]
	mov	r3, r1, asl #7
	add	r1, r3, r1, lsl #2
	str	lr, [r0, #220]
	add	r1, ip, r1
	ldr	r3, [r6, #48]
	str	r3, [r0, #216]
	ldr	r5, [r6, #128]
	ldr	r3, [r4, #172]
	subs	r5, r9, r5
	ldr	r0, [r6, #64]
	clz	r10, r3
	movne	r5, #1
	cmp	r8, r0
	mov	r10, r10, lsr #5
	movne	r3, #1
	strne	r3, [fp, #-64]
	beq	.L3166
.L3131:
	ldr	r0, [r4, #2396]
	orr	r5, r5, r10
	ldr	ip, [r1, #4]
	ldr	r3, [fp, #-64]
	ldr	r0, [r0, #4]
	orr	r5, r3, r5
	cmp	r0, ip
	movne	r0, #1
	beq	.L3167
.L3132:
	orrs	r3, r0, r10
	beq	.L3133
	mov	r0, r4
	str	r2, [fp, #-68]
	bl	HEVC_UpdatePicVPS
	ldr	r2, [fp, #-68]
.L3133:
	ldr	r1, [r4, #2400]
	ldr	r0, [r6, #56]
	ldr	ip, [r1, #56]
	cmp	ip, r0
	movne	r7, #1
	beq	.L3168
.L3134:
	orrs	r7, r7, r5
	beq	.L3135
	ldr	ip, [r1, #184]
	mov	r0, r4
	ldr	r7, [r6, #184]
	mov	r1, r6
	str	r2, [fp, #-68]
	subs	r7, r7, ip
	movne	r7, #1
	bl	HEVC_UpdatePicSPS
	ldr	r2, [fp, #-68]
.L3135:
	ldr	r0, [r4, #2404]
	ldr	r1, [r2, #28]
	ldr	r0, [r0, #28]
	cmp	r0, r1
	movne	r1, #1
	beq	.L3169
.L3136:
	orrs	r3, r1, r5
	beq	.L3137
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_UpdatePicPPS
.L3137:
	ldr	r2, [r4, #280]
	ldr	r3, [fp, #-52]
	cmp	r3, r2
	movne	r1, #1
	beq	.L3170
.L3138:
	ldr	r0, [r4, #2400]
	ldr	ip, [r4, #2416]
	ldr	r3, [fp, #-48]
	ldr	r2, [r0, #96]
	ldr	r0, [r0, #88]
	cmp	r2, r0
	movcc	r2, r0
	str	r2, [ip, #932]
	ldr	r2, [r6, #56]
	cmp	r3, r2
	beq	.L3171
.L3139:
	str	r7, [sp]
	mov	r3, r9
	ldr	r2, [fp, #-56]
	mov	r1, r8
	mov	r0, r4
	bl	HEVC_GetReRangeFlag
	cmp	r0, #0
	bne	.L3140
	ldr	r3, [r4, #2416]
	ldr	r2, [r3, #920]
	cmp	r2, #1
	beq	.L3140
.L3142:
	mov	r2, #0
	str	r2, [r3, #936]
.L3141:
	ldr	r3, [r4, #2344]
	cmp	r3, #0
	bne	.L3144
	mov	r0, r4
	bl	HEVC_AllocFrameStore
	subs	r5, r0, #0
	bne	.L3172
.L3144:
	mov	r0, r4
	bl	HEVC_InitPicInfo
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3146:
	mov	r0, #0
.L3130:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3171:
	ldr	r3, [fp, #-64]
	orr	r10, r3, r10
	orr	r10, r10, r7
	orrs	r3, r10, r1
	bne	.L3139
	ldr	r3, [r4, #2416]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L3141
.L3140:
	mov	r1, #1
	mov	r0, r4
	bl	HEVC_InitDPB
	cmn	r0, #2
	beq	.L3130
	cmp	r0, #0
	bne	.L3143
	ldr	r3, [r4, #2416]
	b	.L3142
.L3170:
	ldr	r1, [r4, #284]
	ldr	r3, [fp, #-60]
	subs	r1, r3, r1
	movne	r1, #1
	b	.L3138
.L3169:
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	adds	r1, r1, #0
	movne	r1, #1
	b	.L3136
.L3168:
	ldr	r3, [fp, #-72]
	ldrb	r7, [r3, r7]	@ zero_extendqisi2
	adds	r7, r7, #0
	movne	r7, #1
	b	.L3134
.L3167:
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	b	.L3132
.L3166:
	ldr	r3, [r6, #68]
	ldr	r0, [fp, #-56]
	subs	r3, r0, r3
	movne	r3, #1
	str	r3, [fp, #-64]
	b	.L3131
.L3172:
	ldr	r1, .L3173
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	b	.L3130
.L3143:
	mov	r2, r0
	ldr	r1, .L3173+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L3130
.L3174:
	.align	2
.L3173:
	.word	.LC421
	.word	.LC420
	UNWIND(.fnend)
	.size	HEVC_InitPic, .-HEVC_InitPic
	.align	2
	.global	HEVC_OutputCurrPic
	.type	HEVC_OutputCurrPic, %function
HEVC_OutputCurrPic:
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
	ldr	r3, [r0, #3560]
	mov	r4, r0
	ldr	r5, [r0, #3580]
	add	r1, r0, #3584
	mov	r2, #640
	add	r0, r5, #80
	str	r3, [r5, #16]
	bl	memcpy
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_GetImagePara
	ldrb	r3, [r4, #3520]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3182
.L3176:
	add	r1, r5, #28
	mov	r0, r4
	bl	HEVC_OutputFrame.isra.10
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r2, .L3183
	mov	r0, #0
	ldr	r1, .L3183+4
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3182:
	mov	r2, #1
	ldr	r1, [r5, #28]
	ldr	r0, [r4, #252]
	bl	FSP_SetRef
	b	.L3176
.L3184:
	.align	2
.L3183:
	.word	.LANCHOR0+648
	.word	.LC422
	UNWIND(.fnend)
	.size	HEVC_OutputCurrPic, .-HEVC_OutputCurrPic
	.align	2
	.global	HEVC_FirstFrameFastOut
	.type	HEVC_FirstFrameFastOut, %function
HEVC_FirstFrameFastOut:
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
	bl	HEVC_OutputCurrPic
	subs	r5, r0, #0
	bne	.L3188
	ldr	r1, [r4, #3580]
	add	r3, r4, #8192
	mov	r2, #1
	mov	r0, #2
	str	r0, [r1, #52]
	mov	r0, r5
	str	r2, [r3, #2992]
	ldr	r3, [r4, #3528]
	ldr	r1, [r4, #3532]
	add	r3, r4, r3, lsl #2
	str	r1, [r3, #212]
	ldr	r3, [r4, #3580]
	strb	r2, [r3, #2]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3188:
	ldr	r2, .L3189
	mov	r0, #1
	ldr	r1, .L3189+4
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3190:
	.align	2
.L3189:
	.word	.LANCHOR0+668
	.word	.LC423
	UNWIND(.fnend)
	.size	HEVC_FirstFrameFastOut, .-HEVC_FirstFrameFastOut
	.align	2
	.global	HEVC_OutputFrmToVO
	.type	HEVC_OutputFrmToVO, %function
HEVC_OutputFrmToVO:
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
	subs	r5, r1, #0
	mov	r4, r0
	beq	.L3196
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r6, r0, #0
	beq	.L3200
	cmn	r6, #3
	bne	.L3201
.L3195:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3200:
	add	r1, r5, #28
	mov	r0, r4
	bl	HEVC_OutputFrame.isra.10
	cmp	r0, #0
	beq	.L3195
	ldr	r2, .L3202
	mov	r0, r6
	ldr	r1, .L3202+4
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3201:
	mov	r3, r6
	movw	r2, #11897
	ldr	r1, .L3202+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #228]
	mov	r0, r4
	bl	HEVC_DECRecycleImage
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3196:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3203:
	.align	2
.L3202:
	.word	.LANCHOR0+692
	.word	.LC422
	.word	.LC424
	UNWIND(.fnend)
	.size	HEVC_OutputFrmToVO, .-HEVC_OutputFrmToVO
	.align	2
	.global	HEVC_DirectOutput
	.type	HEVC_DirectOutput, %function
HEVC_DirectOutput:
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
	ldr	r4, [r0, #3580]
	mov	r5, r0
	mov	ip, #2
	mov	r6, #0
	mov	r3, #1
	add	r1, r0, #3584
	str	ip, [r4, #48]
	add	r0, r4, #80
	strb	r3, [r4, #2]
	mov	r2, #640
	strb	r6, [r4, #1]
	ldr	r3, [r5, #3536]
	str	r3, [r4, #12]
	ldr	r3, [r5, #3560]
	str	r3, [r4, #16]
	bl	memcpy
	mov	r2, r6
	str	r6, [r4, #56]
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #252]
	bl	FSP_SetRef
	mov	r1, r4
	mov	r0, r5
	bl	HEVC_OutputFrmToVO
	ldr	r3, .L3205
	str	r6, [r4, #48]
	mov	r1, r6
	mov	r2, #704
	ldr	r3, [r3, #48]
	mov	r7, r0
	add	r0, r5, #3520
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3206:
	.align	2
.L3205:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_DirectOutput, .-HEVC_DirectOutput
	.align	2
	.global	HEVC_IModeProcess
	.type	HEVC_IModeProcess, %function
HEVC_IModeProcess:
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
	bl	HEVC_DirectOutput
	ldr	r3, [r4, #3556]
	ldr	r2, [r4, #184]
	cmp	r3, r2
	addne	r3, r3, #536
	movne	r1, #0
	strne	r1, [r4, r3, asl #2]
	strne	r2, [r4, #3556]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IModeProcess, .-HEVC_IModeProcess
	.align	2
	.global	HEVC_RemoveFrmFullDPB
	.type	HEVC_RemoveFrmFullDPB, %function
HEVC_RemoveFrmFullDPB:
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
	ldr	lr, [r0, #2600]
	mov	r5, r0
	cmp	lr, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #2608
	mvn	ip, #-2147483648
	add	r0, r0, #8
	mvn	r4, #0
	mov	r3, #0
.L3212:
	ldr	r2, [r0, #4]!
	ldr	r1, [r2, #8]
	cmp	r1, ip
	bge	.L3211
	ldr	r2, [r2]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	moveq	ip, r1
	moveq	r4, r3
.L3211:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L3212
	cmn	r4, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r3, r5, r4, lsl #2
	mov	r1, #1
	mov	r0, r5
	ldr	r2, [r3, #2620]
	strb	r1, [r2, #2]
	ldr	r1, [r3, #2620]
	bl	HEVC_OutputFrmToVO
	mov	r1, r4
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HEVC_RemoveFrameStoreOutDPB
	UNWIND(.fnend)
	.size	HEVC_RemoveFrmFullDPB, .-HEVC_RemoveFrmFullDPB
	.align	2
	.global	HEVC_OutputFrmFromDPB
	.type	HEVC_OutputFrmFromDPB, %function
HEVC_OutputFrmFromDPB:
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
	mov	r4, r0
	ldr	r0, [r0, #2600]
	ldr	r7, [r4, #3528]
	cmp	r0, #0
	beq	.L3239
	add	r9, r7, #52
	mov	r3, #0
	add	r6, r4, #2608
	mov	r10, r3
	add	r6, r6, #8
	add	r9, r4, r9, lsl #2
	mov	r5, r3
	b	.L3224
.L3222:
	add	r5, r5, #1
	cmp	r0, r5
	bls	.L3257
.L3224:
	ldr	r3, [r6, #4]!
	ldrb	r8, [r3, #2]	@ zero_extendqisi2
	cmp	r8, #0
	bne	.L3222
	ldr	r2, [r3, #32]
	cmp	r2, r7
	bne	.L3222
	ldr	r3, [r3, #8]
	ldr	r2, [r9, #4]
	cmp	r3, r2
	addge	r10, r10, #1
	bge	.L3222
	str	r2, [sp]
	mov	r0, #31
	ldr	r2, .L3263
	add	r5, r5, #1
	ldr	r1, .L3263+4
	bl	dprint_vfmw
	ldr	r3, [r6]
	ldr	r0, [r4, #252]
	mov	r2, r8
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
	ldr	r0, [r4, #2600]
	cmp	r0, r5
	bhi	.L3224
.L3257:
	str	r10, [fp, #-52]
.L3221:
	ldr	r3, [r4, #2352]
	cmp	r3, #1
	beq	.L3258
	add	r3, r4, #4096
	ldr	r2, [r4, #2400]
	ldr	r3, [r3, #152]
	add	r3, r3, #90
	ldr	r8, [r2, r3, asl #2]
.L3226:
	cmp	r0, #0
	beq	.L3240
	add	r6, r4, #2608
	mov	r5, #0
	add	r6, r6, #8
	add	r9, r4, r7, lsl #2
	str	r5, [fp, #-48]
	b	.L3237
.L3261:
	ldr	ip, [r4, #332]
	cmp	ip, #1
	beq	.L3233
.L3234:
	cmp	r2, #0
	bne	.L3232
	add	r10, r4, #4096
	ldr	r2, [r1, #8]
	ldr	r3, [r10, #140]
	add	r3, r3, #100
	cmp	r2, r3
	ble	.L3232
	ldr	r3, [r9, #228]
	cmp	r3, #-2147483647
	beq	.L3232
	ldr	r3, [r4, #332]
	cmp	r3, #1
	beq	.L3259
.L3232:
	add	r5, r5, #1
	cmp	r0, r5
	bls	.L3256
.L3237:
	ldr	r1, [r6, #4]!
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3228
	ldr	r3, [r1, #32]
	cmp	r3, r7
	beq	.L3260
.L3228:
	add	r3, r4, r7, lsl #2
	ldr	r3, [r3, #212]
.L3230:
	cmp	r3, #0
	bne	.L3261
.L3233:
	ldr	ip, [r1, #8]
	cmp	r3, ip
	ble	.L3234
	cmp	r2, #0
	beq	.L3262
.L3235:
	str	ip, [sp]
	mov	r0, #31
	ldr	r2, .L3263
	add	r5, r5, #1
	ldr	r1, .L3263+8
	bl	dprint_vfmw
	ldr	r0, [r4, #2600]
	cmp	r0, r5
	bhi	.L3237
.L3256:
	ldr	r0, [fp, #-48]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3260:
	ldr	ip, [r1, #8]
	ldr	r3, [r9, #212]
	cmp	ip, r3
	str	ip, [fp, #-56]
	ble	.L3230
	ldr	r10, [fp, #-52]
	add	lr, r4, #4096
	cmp	r10, r8
	ldr	ip, [lr, #152]
	movhi	r10, #1
	movls	r10, #0
	cmp	ip, #7
	movhi	r10, #0
	cmp	r10, #0
	beq	.L3230
	ldr	lr, [lr, #140]
	ldr	ip, [fp, #-56]
	cmp	ip, lr
	blt	.L3231
	add	ip, r4, r7
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L3230
.L3231:
	mov	r3, #1
	mov	r0, r4
	strb	r3, [r1, #2]
	ldr	r1, [r6]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r6]
	ldr	r2, [fp, #-52]
	ldr	r3, [r3, #8]
	sub	r2, r2, #1
	str	r2, [fp, #-52]
	str	r3, [r9, #212]
	str	r0, [fp, #-48]
	ldr	r0, [r4, #2600]
	b	.L3232
.L3262:
	ldr	r1, [r1, #28]
	ldr	r0, [r4, #252]
	bl	FSP_SetDisplay
	ldr	r2, [r6]
	add	r3, r4, r7, lsl #2
	ldr	ip, [r2, #8]
	ldr	r3, [r3, #212]
	b	.L3235
.L3258:
	ldr	r1, [r4, #2400]
	mov	r8, #0
	add	r3, r1, #356
	add	r1, r1, #388
.L3225:
	ldr	r2, [r3, #4]!
	cmp	r8, r2
	movcc	r8, r2
	cmp	r3, r1
	bne	.L3225
	b	.L3226
.L3259:
	strb	r3, [r1, #2]
	mov	r0, r4
	ldr	r3, [fp, #-52]
	ldr	r1, [r6]
	sub	r3, r3, #1
	str	r3, [fp, #-52]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r9, #212]
	ldr	ip, [r10, #140]
	ldr	r2, .L3263
	cmp	ip, r3
	ldr	r1, .L3263+12
	sublt	r3, ip, #1
	strlt	r3, [r9, #212]
	ldr	r3, [r6]
	ldr	r3, [r3, #8]
	str	ip, [sp]
	str	r0, [fp, #-48]
	mov	r0, #31
	bl	dprint_vfmw
	ldr	r0, [r4, #2600]
	b	.L3232
.L3239:
	str	r0, [fp, #-52]
	b	.L3221
.L3240:
	str	r0, [fp, #-48]
	b	.L3256
.L3264:
	.align	2
.L3263:
	.word	.LANCHOR0+712
	.word	.LC425
	.word	.LC426
	.word	.LC427
	UNWIND(.fnend)
	.size	HEVC_OutputFrmFromDPB, .-HEVC_OutputFrmFromDPB
	.align	2
	.global	HEVC_OutputOneFrmFromDPB
	.type	HEVC_OutputOneFrmFromDPB, %function
HEVC_OutputOneFrmFromDPB:
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
	add	r4, r0, r1, lsl #2
	mov	r2, #1
	mov	r6, r1
	mov	r5, r0
	ldr	r3, [r4, #2620]
	strb	r2, [r3, #2]
	ldr	r1, [r4, #2620]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r4, #2620]
	ldr	r2, [r3, #32]
	ldr	r1, [r3, #8]
	add	r2, r5, r2, lsl #2
	str	r1, [r2, #212]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r7, r0
	bne	.L3266
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
.L3266:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_OutputOneFrmFromDPB, .-HEVC_OutputOneFrmFromDPB
	.align	2
	.global	HEVC_OutputUnRefPicWithMinPoc
	.type	HEVC_OutputUnRefPicWithMinPoc, %function
HEVC_OutputUnRefPicWithMinPoc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	sub	r1, fp, #24
	mov	r4, r0
	bl	HEVC_GetUnRefPicWithMinPoc
	cmp	r0, #0
	bne	.L3271
	mov	r0, r4
	ldr	r1, [fp, #-24]
	bl	HEVC_OutputOneFrmFromDPB
	cmp	r0, #0
	bne	.L3272
.L3269:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L3271:
	ldr	r2, .L3273
	mov	r0, #1
	ldr	r1, .L3273+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3269
.L3272:
	ldr	r2, .L3273
	mov	r0, #1
	ldr	r1, .L3273+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3269
.L3274:
	.align	2
.L3273:
	.word	.LANCHOR0+736
	.word	.LC428
	.word	.LC429
	UNWIND(.fnend)
	.size	HEVC_OutputUnRefPicWithMinPoc, .-HEVC_OutputUnRefPicWithMinPoc
	.align	2
	.global	HEVC_FlushOutputFrmFromDPB
	.type	HEVC_FlushOutputFrmFromDPB, %function
HEVC_FlushOutputFrmFromDPB:
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
	subs	r4, r0, #0
	beq	.L3283
	ldr	r3, [r4, #2600]
	cmp	r3, #0
	beq	.L3277
	add	r5, r4, #2608
	mov	r6, #0
	add	r5, r5, #8
	mov	r8, #1
	b	.L3282
.L3293:
	strb	r8, [r3, #2]
	ldr	r1, [r5]
	bl	HEVC_OutputFrmToVO
	cmn	r0, #1
	mov	r9, r0
	beq	.L3292
.L3280:
	ldr	r3, [r4, #2600]
	cmp	r3, r6
	bls	.L3277
.L3282:
	ldr	r3, [r5, #4]!
	mov	r2, #0
	ldr	r0, [r4, #252]
	add	r6, r6, #1
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldr	r3, [r5]
	mov	r0, r4
	ldrb	r7, [r3, #2]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L3293
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #252]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L3280
	ldr	r3, [r5]
	ldr	r0, [r4, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #2600]
	cmp	r3, r6
	bhi	.L3282
.L3277:
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	mov	r9, #0
	bl	HEVC_InitDecBuffers
.L3291:
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3292:
	mov	r0, r7
	ldr	r2, .L3294
	ldr	r1, .L3294+4
	bl	dprint_vfmw
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3283:
	mvn	r9, #0
	b	.L3291
.L3295:
	.align	2
.L3294:
	.word	.LANCHOR0+768
	.word	.LC430
	UNWIND(.fnend)
	.size	HEVC_FlushOutputFrmFromDPB, .-HEVC_FlushOutputFrmFromDPB
	.align	2
	.global	HEVC_ReceivePacket
	.type	HEVC_ReceivePacket, %function
HEVC_ReceivePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r6, [r0, #2388]
	mov	r3, #0
	mov	r4, r0
	cmp	r6, r3
	str	r3, [r0, #328]
	beq	.L3326
	ldrb	r3, [r1]	@ zero_extendqisi2
	str	r3, [r6, #36]
	ldr	r3, [r0, #2416]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L3327
.L3303:
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3304
	ldr	r3, [r4, #2388]
	ldr	r2, [r3, #8]
	cmp	r2, #1
	bls	.L3305
	ldr	r0, [r3, #36]
	cmp	r0, #1
	beq	.L3304
.L3305:
	ldr	r0, [r1, #16]
	cmp	r0, #0
	ble	.L3306
	ldr	r0, [r1, #4]
	cmp	r0, #0
	beq	.L3306
	ldr	ip, [r1, #8]
	cmp	ip, #0
	bne	.L3328
.L3306:
	mov	r2, #1
	str	r2, [r3, #36]
	ldr	r1, [r1, #20]
	ldr	r0, [r4, #252]
	bl	SM_ReleaseStreamSeg
.L3302:
	ldr	r3, [r4, #2388]
	ldr	r0, [r3, #36]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
.L3300:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3328:
	mov	lr, r2, asl #5
	mov	ip, #0
	sub	r2, lr, r2, asl #2
	add	r3, r3, r2
	str	r0, [r3, #40]
	ldr	r3, [r4, #2388]
	ldr	lr, [r1, #16]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #44]
	ldr	r3, [r4, #2388]
	ldr	lr, [r1, #8]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #48]
	ldr	r3, [r4, #2388]
	ldr	lr, [r1, #20]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #64]
	ldr	r3, [r4, #2388]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	ip, [r3, #56]
	ldr	r2, [r4, #2388]
	ldr	r3, [r2, #8]
	add	r3, r3, #1
	str	r3, [r2, #8]
	ldr	r3, [r4, #2416]
	ldrb	r3, [r3, #944]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3307
	ldr	r0, [r1, #16]
	ldr	r2, [r4, #3572]
	ldr	r3, [r4, #3576]
	add	r2, r2, r0
	str	r2, [r4, #3572]
	ldr	r2, [r1, #16]
	add	r3, r3, r2
	str	r3, [r4, #3576]
.L3307:
	mov	r0, r4
	bl	HEVC_CombinePacket
	mov	r3, #1
	str	r3, [r4, #328]
	b	.L3302
.L3327:
	ldr	r3, [r3, #920]
	cmp	r3, #0
	bne	.L3302
	b	.L3303
.L3326:
	ldr	r3, [r1, #16]
	cmp	r3, #0
	ble	.L3298
	ldr	r3, [r1, #4]
	cmp	r3, #0
	beq	.L3298
	ldr	r3, [r1, #8]
	str	r1, [fp, #-32]
	cmp	r3, #0
	beq	.L3298
	bl	HEVC_FindNaluArraySlot
	ldr	r1, [fp, #-32]
	cmn	r0, #1
	mov	r5, r0
	beq	.L3329
	ldr	r3, [r4, #2412]
	mov	r0, r0, asl #7
	sub	r0, r0, r5, asl #5
	mov	r2, #1
	add	r0, r3, r0
	str	r0, [r4, #2388]
	ldr	r3, [r1, #4]
	str	r3, [r0, #40]
	ldr	r3, [r4, #2388]
	ldr	r0, [r1, #16]
	str	r0, [r3, #44]
	ldr	r3, [r4, #2388]
	ldr	r0, [r1, #20]
	str	r0, [r3, #64]
	ldr	r3, [r4, #2388]
	ldr	r0, [r1, #8]
	str	r0, [r3, #48]
	ldr	r3, [r4, #2388]
	str	r6, [r3, #56]
	ldr	r3, [r4, #2388]
	str	r2, [r3, #8]
	ldr	r3, [r4, #2388]
	strb	r6, [r3]
	ldr	r3, [r4, #2388]
	ldrb	r2, [r1]	@ zero_extendqisi2
	str	r2, [r3, #36]
	ldr	r3, [r4, #2416]
	ldrb	r3, [r3, #944]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3301
	ldr	r0, [r1, #16]
	ldr	r2, [r4, #3572]
	ldr	r3, [r4, #3576]
	add	r2, r2, r0
	str	r2, [r4, #3572]
	ldr	r2, [r1, #16]
	add	r3, r3, r2
	str	r3, [r4, #3576]
.L3301:
	ldr	r3, [r1, #12]
	str	r3, [r4, #2340]
	b	.L3302
.L3304:
	ldr	r1, .L3330
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3300
.L3298:
	ldr	r1, .L3330+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3300
.L3329:
	ldr	r1, .L3330+8
	mov	r0, r6
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	mov	r0, r5
	b	.L3300
.L3331:
	.align	2
.L3330:
	.word	.LC433
	.word	.LC432
	.word	.LC431
	UNWIND(.fnend)
	.size	HEVC_ReceivePacket, .-HEVC_ReceivePacket
	.align	2
	.global	HEVC_FlushDPB
	.type	HEVC_FlushDPB, %function
HEVC_FlushDPB:
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
	ldr	r1, [r0, #2600]
	mov	r4, r0
	cmp	r1, #0
	beq	.L3334
	add	r6, r0, #2608
	mov	r5, #0
	add	r6, r6, #8
	mov	r7, r5
	b	.L3336
.L3335:
	cmp	r1, r5
	bls	.L3334
.L3336:
	ldr	r3, [r6, #4]!
	add	r5, r5, #1
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3335
	strb	r7, [r3, #1]
	mov	r2, #0
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #252]
	bl	FSP_SetRef
	ldr	r1, [r4, #2600]
	cmp	r1, r5
	bhi	.L3336
.L3334:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L3338
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L3334
	b	.L3338
.L3340:
	bl	HEVC_GetMinPOC
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	beq	.L3339
.L3338:
	ldr	r3, [r4, #2600]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	bne	.L3340
	mov	r0, r3
.L3339:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_FlushDPB, .-HEVC_FlushDPB
	.align	2
	.global	HEVC_ClearDPB
	.type	HEVC_ClearDPB, %function
HEVC_ClearDPB:
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
	bl	HEVC_FlushDPB
	subs	r3, r0, #0
	beq	.L3349
	ldr	r2, .L3353
	mov	r0, #0
	ldr	r1, .L3353+4
	bl	dprint_vfmw
.L3349:
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3354:
	.align	2
.L3353:
	.word	.LANCHOR0+796
	.word	.LC434
	UNWIND(.fnend)
	.size	HEVC_ClearDPB, .-HEVC_ClearDPB
	.align	2
	.global	HEVC_RecoverDPBProcess
	.type	HEVC_RecoverDPBProcess, %function
HEVC_RecoverDPBProcess:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r4, r0
	b	.L3356
.L3358:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L3364
.L3356:
	ldr	ip, [r4, #2600]
	mov	r0, #13
	ldr	lr, [r4, #2596]
	ldr	r2, .L3365
	cmp	ip, lr
	ldr	r1, .L3365+4
	mov	r3, ip
	bcs	.L3358
	b	.L3360
.L3361:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_OutputUnRefPicWithMinPoc
	cmp	r0, #0
	bne	.L3359
	ldr	ip, [r4, #2600]
	ldr	lr, [r4, #2596]
.L3360:
	cmp	ip, lr
	mov	r3, ip
	ldr	r2, .L3365
	mov	r0, #1
	ldr	r1, .L3365+8
	bcs	.L3361
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L3364:
	ldr	r2, .L3365
	mov	r0, #1
	ldr	r1, .L3365+12
	bl	dprint_vfmw
	ldr	ip, [r4, #2600]
	ldr	lr, [r4, #2596]
	b	.L3360
.L3359:
	ldr	r2, .L3365
	mov	r0, #1
	ldr	r1, .L3365+16
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	mov	r0, r4
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	HEVC_ClearDPB
.L3366:
	.align	2
.L3365:
	.word	.LANCHOR0+812
	.word	.LC435
	.word	.LC437
	.word	.LC436
	.word	.LC429
	UNWIND(.fnend)
	.size	HEVC_RecoverDPBProcess, .-HEVC_RecoverDPBProcess
	.align	2
	.global	HEVC_InsertFrmInDPB
	.type	HEVC_InsertFrmInDPB, %function
HEVC_InsertFrmInDPB:
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
	cmp	r1, #16
	mov	r7, r1
	mov	r6, r0
	mov	r4, r2
	bhi	.L3371
	ldr	r3, [r2, #60]
	add	r5, r0, r1, lsl #2
	mov	r1, #1
	mov	r2, r1
	str	r3, [r5, #2620]
	str	r1, [r3, #48]
	ldr	r3, [r5, #2620]
	ldr	r0, [r0, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r0, [r5, #2620]
	mov	r2, #640
	adds	r3, r3, #0
	add	r1, r4, #64
	movne	r3, #1
	strb	r3, [r0, #1]
	ldr	r3, [r5, #2620]
	ldr	r0, [r4, #36]
	str	r0, [r3, #20]
	ldr	r0, [r5, #2620]
	add	r0, r0, #80
	bl	memcpy
	ldr	r2, [r5, #2620]
	ldr	ip, [r4, #40]
	add	r0, r6, #2608
	add	r1, r7, #1
	add	r0, r0, #12
	ldr	r3, .L3373
	str	ip, [r2, #16]
	mov	r2, #4
	ldr	ip, [r5, #2620]
	ldr	lr, [r4, #60]
	str	lr, [ip, #72]
	ldr	ip, [r5, #2620]
	ldr	lr, [r4, #16]
	str	lr, [ip, #12]
	ldr	ip, [r5, #2620]
	ldr	lr, [r4, #12]
	str	lr, [ip, #8]
	ldr	ip, [r5, #2620]
	ldr	lr, [r4, #8]
	str	lr, [ip, #32]
	bl	qsort
	ldr	r3, [r6, #2600]
	mov	r0, r6
	add	r3, r3, #1
	str	r3, [r6, #2600]
	ldr	r1, [r4, #60]
	bl	HEVC_GetAPC
	subs	r3, r0, #0
	bne	.L3372
	mov	r0, r3
	strb	r3, [r4, #1]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3371:
	mov	r3, r1
	ldr	r2, .L3373+4
	ldr	r1, .L3373+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3372:
	ldr	r2, .L3373+4
	mov	r0, #0
	ldr	r1, .L3373+12
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_PrintDPBState
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3374:
	.align	2
.L3373:
	.word	HEVC_ComparePicByPocAsc
	.word	.LANCHOR0+836
	.word	.LC438
	.word	.LC439
	UNWIND(.fnend)
	.size	HEVC_InsertFrmInDPB, .-HEVC_InsertFrmInDPB
	.align	2
	.global	HEVC_SimpleDPBProcess
	.type	HEVC_SimpleDPBProcess, %function
HEVC_SimpleDPBProcess:
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
	ldrb	r3, [r0, #3520]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r3, #0
	bne	.L3388
	ldr	r3, [r0, #3580]
	mov	r2, #2
	str	r2, [r3, #48]
.L3377:
	ldr	r3, [r4, #3580]
	mov	r2, #1
	mov	r0, r4
	strb	r2, [r3, #2]
	ldr	r1, [r4, #3580]
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r5, r0
	beq	.L3389
	cmn	r0, #3
	beq	.L3381
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3390
.L3381:
	mov	r0, #0
.L3378:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3388:
	bl	HEVC_SimpleSlideDPB
	add	r2, r4, #3520
	ldr	r1, [r4, #2600]
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	beq	.L3377
	str	r0, [sp]
	movw	r3, #10993
	ldr	r2, .L3391
	mov	r0, #0
	ldr	r1, .L3391+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3378
.L3390:
	ldr	r2, .L3391
	mov	r0, #0
	ldr	r1, .L3391+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3378
.L3389:
	ldr	r2, .L3391
	mov	r0, #0
	ldr	r1, .L3391+12
	bl	dprint_vfmw
	mov	r0, r5
	b	.L3378
.L3392:
	.align	2
.L3391:
	.word	.LANCHOR0+856
	.word	.LC440
	.word	.LC423
	.word	.LC441
	UNWIND(.fnend)
	.size	HEVC_SimpleDPBProcess, .-HEVC_SimpleDPBProcess
	.align	2
	.global	HEVC_DecOrderProcess
	.type	HEVC_DecOrderProcess, %function
HEVC_DecOrderProcess:
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
	ldr	r1, [r0, #2600]
	mov	r4, r0
	ldr	r3, [r0, #2596]
	cmp	r1, r3
	bcs	.L3405
.L3394:
	add	r2, r4, #3520
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L3406
	ldr	r1, [r4, #3580]
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r5, r0
	beq	.L3407
	cmn	r0, #3
	beq	.L3400
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3408
.L3400:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3405:
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3404
	ldr	r2, .L3409
	mov	r0, #0
	ldr	r1, .L3409+4
	bl	dprint_vfmw
.L3404:
	ldr	r1, [r4, #2600]
	b	.L3394
.L3406:
	ldr	r2, .L3409
	mov	r0, #0
	ldr	r1, .L3409+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3408:
	mov	r0, r6
	ldr	r2, .L3409
	ldr	r1, .L3409+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3407:
	mov	r0, r6
	ldr	r2, .L3409
	ldr	r1, .L3409+16
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3410:
	.align	2
.L3409:
	.word	.LANCHOR0+880
	.word	.LC442
	.word	.LC443
	.word	.LC423
	.word	.LC441
	UNWIND(.fnend)
	.size	HEVC_DecOrderProcess, .-HEVC_DecOrderProcess
	.align	2
	.global	HEVC_DispOrderProcess
	.type	HEVC_DispOrderProcess, %function
HEVC_DispOrderProcess:
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
	add	r3, r0, #8192
	mov	r4, r0
	ldr	r3, [r3, #2992]
	cmp	r3, #1
	beq	.L3412
	bl	HEVC_FirstFrameFastOut
	cmp	r0, #0
	bne	.L3435
.L3412:
	ldr	r1, [r4, #2600]
	ldr	r3, [r4, #2596]
	cmp	r1, r3
	bcs	.L3436
.L3414:
	add	r2, r4, #3520
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L3437
	ldr	r3, [r4, #2600]
	cmp	r3, #0
	bne	.L3438
.L3417:
	ldr	r2, [r4, #2596]
	cmp	r2, r3
	bls	.L3439
.L3434:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3439:
	add	r1, r4, #5568
	ldr	r0, [r4, #252]
	add	r1, r1, #16
	bl	FSP_IfCanGetDecFs
	cmp	r0, #0
	beq	.L3434
	mov	r0, r4
	bl	HEVC_RemoveFrmFullDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3436:
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3433
	ldr	r1, .L3440
	mov	r0, #0
	bl	dprint_vfmw
.L3433:
	ldr	r1, [r4, #2600]
	b	.L3414
.L3438:
	mov	r0, r4
	bl	HEVC_OutputFrmFromDPB
	cmp	r0, #0
	bne	.L3418
	ldr	r3, [r4, #2600]
	b	.L3417
.L3437:
	mov	r2, r0
	ldr	r1, .L3440+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3435:
	ldr	r2, .L3440+8
	mov	r0, #0
	ldr	r1, .L3440+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3418:
	ldr	r2, .L3440+8
	mov	r0, #1
	ldr	r1, .L3440+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3441:
	.align	2
.L3440:
	.word	.LC445
	.word	.LC446
	.word	.LANCHOR0+904
	.word	.LC444
	.word	.LC447
	UNWIND(.fnend)
	.size	HEVC_DispOrderProcess, .-HEVC_DispOrderProcess
	.align	2
	.global	HEVC_StorePicInDPB
	.type	HEVC_StorePicInDPB, %function
HEVC_StorePicInDPB:
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
	ldr	r3, .L3486
	mov	r4, r0
	ldr	r2, [r0, #252]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L3477
.L3443:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	ldrb	r5, [r4, #3521]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L3478
	ldr	r2, [r4, #3560]
	cmp	r2, #0
	beq	.L3446
	ldr	r5, [r4, #3536]
	cmp	r5, #0
	beq	.L3479
.L3447:
	ldr	r3, [r4, #2416]
	ldr	r1, [r3, #4]
	cmp	r1, r2
	bcs	.L3446
	ldr	r5, [r3, #644]
	cmp	r5, #0
	beq	.L3480
.L3446:
	ldr	r3, [r4, #2424]
	ldr	r2, [r4, #3580]
	add	r3, r3, #4096
	ldr	r3, [r3, #1088]
	str	r3, [r2, #40]
	ldr	r3, [r4, #2424]
	ldr	r2, [r4, #3580]
	add	r3, r3, #4096
	ldr	r3, [r3, #1092]
	str	r3, [r2, #44]
	ldr	r3, [r4, #256]
	cmp	r3, #2
	beq	.L3481
	ldr	r3, [r4, #2416]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	beq	.L3482
	cmp	r3, #1
	beq	.L3483
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bls	.L3457
.L3459:
	mov	r0, r4
	mvn	r5, #0
	bl	HEVC_ClearCurrPic
	ldr	r2, .L3486+4
	ldr	r1, .L3486+8
	mov	r0, #1
	bl	dprint_vfmw
.L3458:
	mov	r3, #0
	strb	r3, [r4, #3521]
.L3475:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3477:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L3443
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L3443
	add	r3, r0, #8192
	ldrb	r3, [r3, #2936]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3443
	bl	HEVC_Sei_Get_Frame_Pts
	b	.L3443
.L3478:
	ldr	r2, .L3486+4
	mov	r0, #1
	ldr	r1, .L3486+12
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3480:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, [r4, #2416]
	ldr	r2, [r4, #3560]
	mov	r0, #1
	ldr	r1, .L3486+16
	ldr	r3, [r3, #4]
	bl	dprint_vfmw
	b	.L3475
.L3483:
	mov	r0, r4
	bl	HEVC_DecOrderProcess
	subs	r5, r0, #0
	bne	.L3456
	ldr	r3, [r4, #2416]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L3458
.L3457:
	mov	r0, r4
	bl	HEVC_DispOrderProcess
	subs	r5, r0, #0
	beq	.L3458
	ldr	r2, .L3486+4
	mov	r0, #0
	ldr	r1, .L3486+20
	bl	dprint_vfmw
	b	.L3452
.L3479:
	ldr	r2, .L3486+4
	mov	r0, #1
	ldr	r1, .L3486+24
	bl	dprint_vfmw
	ldr	r3, .L3486+28
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L3476
	mov	r3, r5
	mov	r2, r5
	mov	r1, #111
	ldr	r0, [r4, #252]
	blx	r6
.L3476:
	ldr	r2, [r4, #3560]
	b	.L3447
.L3481:
	mov	r0, r4
	bl	HEVC_DirectOutput
	ldr	r3, [r4, #3556]
	ldr	r2, [r4, #184]
	cmp	r3, r2
	addne	r3, r3, #536
	movne	r1, #0
	strne	r1, [r4, r3, asl #2]
	mov	r5, r0
	strne	r2, [r4, #3556]
	cmp	r0, #0
	bne	.L3484
.L3451:
	movw	r3, #11295
	mov	r2, r5
	ldr	r1, .L3486+32
	mov	r0, #14
	bl	dprint_vfmw
.L3452:
	cmn	r5, #1
	bne	.L3458
	b	.L3459
.L3482:
	mov	r0, r4
	bl	HEVC_SimpleDPBProcess
	subs	r5, r0, #0
	bne	.L3485
.L3454:
	movw	r3, #11310
	mov	r2, r5
	ldr	r1, .L3486+32
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3452
.L3484:
	ldr	r2, .L3486+4
	mov	r0, #0
	ldr	r1, .L3486+36
	bl	dprint_vfmw
	b	.L3451
.L3485:
	ldr	r2, .L3486+4
	mov	r0, #0
	ldr	r1, .L3486+40
	bl	dprint_vfmw
	b	.L3454
.L3456:
	ldr	r2, .L3486+4
	mov	r0, #0
	ldr	r1, .L3486+44
	bl	dprint_vfmw
	ldr	r3, [r4, #2416]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L3452
	b	.L3457
.L3487:
	.align	2
.L3486:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+928
	.word	.LC456
	.word	.LC448
	.word	.LC450
	.word	.LC455
	.word	.LC449
	.word	g_event_report
	.word	.LC452
	.word	.LC451
	.word	.LC453
	.word	.LC454
	UNWIND(.fnend)
	.size	HEVC_StorePicInDPB, .-HEVC_StorePicInDPB
	.align	2
	.global	HEVC_CreateLostPicture
	.type	HEVC_CreateLostPicture, %function
HEVC_CreateLostPicture:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 704
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #704)
	sub	sp, sp, #704
	ldr	r3, .L3533
	mov	r4, r0
	mov	r5, r1
	sub	r0, fp, #740
	mov	r2, #704
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	add	r0, r4, #12736
	add	r0, r0, #8
	mov	r6, #0
.L3493:
	ldr	r3, [r0, #48]
	cmp	r3, #0
	bne	.L3489
	cmp	r0, #0
	beq	.L3510
	ldr	ip, [r4, #2600]
	cmp	ip, #0
	beq	.L3510
	ldr	r2, [r4, #2620]
	cmp	r0, r2
	beq	.L3489
	add	r2, r4, #2608
	add	r2, r2, #12
	b	.L3491
.L3492:
	ldr	r1, [r2, #4]!
	cmp	r0, r1
	beq	.L3489
.L3491:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L3492
.L3510:
	mov	r8, #720
	mov	r7, r0
	mla	r8, r8, r6, r4
	mov	r2, #640
	sub	r0, fp, #676
	mov	r9, #1
	mov	r3, #101
	str	r5, [fp, #-728]
	add	r1, r8, #12800
	str	r3, [fp, #-700]
	add	r1, r1, #24
	strb	r9, [fp, #-739]
	strb	r9, [fp, #-740]
	bl	memcpy
	add	r2, r8, #12736
	cmp	r6, #19
	movw	r1, #12744
	mov	r6, #0
	strb	r9, [r2, #10]
	str	r6, [r2, #60]
	str	r7, [fp, #-680]
	str	r6, [fp, #-524]
	strb	r9, [r8, r1]
	bgt	.L3494
	ldr	r0, [r4, #2600]
	cmp	r0, #0
	beq	.L3496
	add	r1, r4, #2608
	mov	ip, r6
	add	r1, r1, #8
	mvn	r2, #-2147483648
	mov	r8, r1
.L3499:
	ldr	lr, [r8, #4]!
	add	ip, ip, #1
	ldr	r3, [lr, #8]
	rsb	r3, r5, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bge	.L3498
	ldrb	lr, [lr, #1]	@ zero_extendqisi2
	cmp	lr, #0
	movne	r2, r3
	movne	r6, #1
.L3498:
	cmp	ip, r0
	bne	.L3499
	cmp	r6, #0
	beq	.L3496
	mov	r6, #0
	b	.L3500
.L3501:
	add	r6, r6, #1
	cmp	r6, r0
	beq	.L3502
.L3500:
	ldr	ip, [r1, #4]!
	ldr	r3, [ip, #8]
	rsb	r3, r5, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bne	.L3501
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3501
	ldr	r1, [ip, #28]
	add	r6, r4, r6, lsl #2
	ldr	r0, [r4, #252]
	ldr	r9, [ip, #32]
	bl	FSP_GetLogicFs
	ldr	r2, [r6, #2620]
	mov	r3, r5
	ldr	r1, .L3533+4
	ldr	r2, [r2, #8]
	mov	r8, r0
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r8, #0
	beq	.L3502
	ldr	r0, [r8, #28]
	cmp	r0, #0
	beq	.L3531
	mov	r1, #0
	ldr	r0, [r4, #252]
	bl	FSP_NewLogicFs
	mov	r7, r0
	mov	r1, r0
	ldr	r0, [r4, #252]
	bl	FSP_GetLogicFs
	mvn	r2, r7
	mov	r2, r2, lsr #31
	cmp	r0, #0
	mov	r3, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L3505
	ldr	r1, [fp, #-680]
	sub	r2, fp, #740
	mov	r0, r4
	str	r7, [r1, #28]
	ldr	r1, [r8, #28]
	str	r1, [r3, #28]
	ldr	r1, [r8, #32]
	str	r1, [r3, #32]
	ldrsb	r3, [r8, #4]
	ldr	r1, [r4, #2600]
	str	r9, [fp, #-732]
	str	r3, [fp, #-704]
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L3532
	ldr	r0, [r4, #252]
	mov	r1, r7
	mov	r2, r6
	bl	FSP_SetDisplay
	add	r3, r4, #4096
	mov	r0, r6
	ldr	r3, [r3, #160]
	add	r4, r4, r3, lsl #2
	ldr	r3, [r4, #228]
	cmn	r3, #-2147483647
	streq	r5, [r4, #228]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3489:
	add	r6, r6, #1
	add	r0, r0, #720
	cmp	r6, #20
	bne	.L3493
.L3494:
	ldr	r1, .L3533+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L3526:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3502:
	ldr	r1, .L3533+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3505:
	ldr	r3, [fp, #-680]
	mov	r0, r2
	ldr	r1, .L3533+16
	strb	r2, [r3]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3526
.L3532:
	ldr	r3, [fp, #-680]
	mov	r1, r7
	mov	r5, #0
	mov	r2, #1
	strb	r5, [r3]
	ldr	r0, [r4, #252]
	bl	FSP_ClearLogicFs
	mov	r0, r5
	ldr	r1, .L3533+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3526
.L3496:
	mov	r0, #0
	ldr	r1, .L3533+24
	strb	r0, [r7]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3526
.L3531:
	ldr	r1, .L3533+28
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	b	.L3526
.L3534:
	.align	2
.L3533:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC460
	.word	.LC457
	.word	.LC458
	.word	.LC462
	.word	.LC463
	.word	.LC459
	.word	.LC461
	UNWIND(.fnend)
	.size	HEVC_CreateLostPicture, .-HEVC_CreateLostPicture
	.align	2
	.global	HEVC_RefPicProcess
	.type	HEVC_RefPicProcess, %function
HEVC_RefPicProcess:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	mov	r4, r0
	bl	HEVC_RemoveDummyFrame
	mov	r0, r4
	bl	HEVC_ApplyReferencePictureSet
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	add	r5, r4, #4096
	bl	HEVC_RemoveUnUsedFrameStore
	b	.L3536
.L3539:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.8
	ldr	r1, .L3545
	cmp	r0, #0
	mov	r0, #1
	bne	.L3541
	ldr	r2, [fp, #-24]
	bl	dprint_vfmw
	ldr	r3, [r4, #2416]
	mov	r0, r4
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L3537
	ldr	r1, [fp, #-24]
	bl	HEVC_CreateLostPicture
	cmp	r0, #0
	bne	.L3544
.L3536:
	ldr	r3, [r5, #156]
	sub	r1, fp, #24
	mov	r0, r4
	sub	r3, r3, #19
	cmp	r3, #2
	bhi	.L3539
.L3541:
	mov	r0, r4
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	mov	r0, r4
	bl	HEVC_RecoverDPBProcess
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3537:
	ldr	ip, [fp, #-24]
	mov	r0, #1
	ldr	r3, [r5, #140]
	ldr	r1, .L3545+4
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3544:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3546:
	.align	2
.L3545:
	.word	.LC464
	.word	.LC465
	UNWIND(.fnend)
	.size	HEVC_RefPicProcess, .-HEVC_RefPicProcess
	.align	2
	.global	HEVC_DecVDM
	.type	HEVC_DecVDM, %function
HEVC_DecVDM:
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
	ldr	r3, [r0, #176]
	mov	r4, r0
	cmp	r3, #2
	bls	.L3606
	ldr	r3, [r0, #296]
	mov	r0, #1
	ldr	r2, [r4, #300]
	add	r3, r3, r0
	ldr	r1, [r4, #2416]
	cmp	r3, r2
	movlt	r3, r2
	str	r3, [r4, #296]
	rsb	r3, r2, r3
	str	r3, [r1, #584]
	ldr	r5, [r4, #248]
	ldr	r2, [r4, #256]
	ubfx	r5, r5, #16, #3
	strb	r0, [r4, #3520]
	cmp	r2, r5
	beq	.L3552
	subs	r3, r5, #2
	sub	r1, r2, #2
	movne	r3, #1
	cmp	r1, r0
	movhi	r3, #0
	cmp	r3, #0
	beq	.L3552
	cmp	r5, #4
	cmpne	r5, r0
	bls	.L3607
.L3552:
	cmp	r5, #2
	str	r5, [r4, #256]
	beq	.L3554
	cmp	r5, #3
	bne	.L3602
.L3603:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
.L3601:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3602:
	ldr	r3, [r4, #236]
	cmp	r3, #0
	beq	.L3571
	cmp	r5, #4
	ldr	r3, [r4, #3536]
	beq	.L3608
.L3560:
	cmp	r3, #2
	bne	.L3562
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3609
.L3573:
	ldr	r2, [r4, #240]
	mov	r0, #2
	ldr	r1, .L3611
	sub	r2, r2, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L3610
	ldr	r0, [r4, #3548]
	add	r2, r4, #4096
	add	ip, r4, #8192
	clz	r1, r0
	mov	r1, r1, lsr #5
	str	r1, [r2, #3180]
	ldr	r1, [r4, #3552]
	str	r1, [r2, #3172]
	str	r3, [ip, #232]
	ldr	r3, [r4, #2416]
	ldr	r1, [r3, #600]
	strb	r1, [r2, #1840]
	ldr	r1, [r3, #604]
	strb	r1, [r2, #1841]
	ldr	r1, [r3, #608]
	strb	r1, [r2, #1843]
	ldr	r1, [r3, #612]
	strb	r1, [r2, #1844]
	ldr	r3, [r3, #652]
	str	r3, [r2, #3168]
	ldr	r3, [r4, #240]
	cmp	r3, #0
	beq	.L3567
	ldr	r1, [r4, #3564]
	add	r3, r4, #5888
	add	r3, r3, #48
	str	r3, [r4, #2424]
	add	r0, r0, #1
	mov	r3, #0
	str	r1, [ip, #2928]
	ldr	r1, [r4, #3568]
	str	r1, [ip, #2932]
	str	r0, [r4, #3548]
	str	r3, [ip, #2924]
	ldr	r1, [r4, #3536]
	cmp	r1, r3
	bne	.L3567
	ldr	r2, [ip, #236]
	cmp	r2, r3
	beq	.L3576
.L3570:
	ldr	r3, [r2]
	ldr	r0, [r2, #4]
	ldr	r2, [r2, #1356]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L3570
.L3569:
	ldr	r3, .L3611+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3567
	sub	r2, fp, #20
	mov	r3, #4
	ldr	r0, [r4, #252]
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	r5
.L3567:
	ldr	ip, [r4, #3576]
	mov	r0, #0
	ldr	r1, [r4, #3580]
	ldr	r3, [r4, #3572]
	str	ip, [r4, #3572]
	ldr	r2, [r1, #320]
	rsb	r3, ip, r3
	add	r2, r2, r3
	str	r2, [r1, #320]
	ldr	r2, [r4, #3824]
	add	r3, r2, r3
	str	r3, [r4, #3824]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3562:
	cmp	r3, #1
	streqb	r3, [r4, #6]
	b	.L3573
.L3554:
	ldr	r3, [r4, #3536]
	cmp	r3, #0
	bne	.L3558
	ldr	r3, [r4, #236]
	cmp	r3, #0
	bne	.L3573
.L3571:
	ldr	r3, .L3611+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3558
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L3558:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L3601
.L3608:
	cmp	r3, #0
	moveq	r3, #2
	streqb	r3, [r4, #6]
	beq	.L3573
	b	.L3560
.L3609:
	ldr	r3, .L3611+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3573
	ldr	r3, [r4, #2416]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L3573
	mov	r3, #1
	ldr	r2, [r4, #3532]
	mov	r0, r3
	ldr	r1, .L3611+12
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, .L3611+4
	ldr	r5, [r3]
	cmp	r5, #0
	mvneq	r0, #0
	beq	.L3601
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #127
	blx	r5
	mvn	r0, #0
	b	.L3601
.L3607:
	mov	r3, r5
	ldr	r1, .L3611+16
	bl	dprint_vfmw
	str	r5, [r4, #256]
	b	.L3603
.L3610:
	ldr	r2, .L3611+4
	ldr	r5, [r2]
	cmp	r5, #0
	beq	.L3565
	mov	r2, r3
	mov	r1, #127
	ldr	r0, [r4, #252]
	blx	r5
.L3565:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r2, .L3611+20
	ldr	r1, .L3611+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3601
.L3606:
	bl	HEVC_ClearCurrPic
	ldr	r3, .L3611+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3549
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L3549:
	ldr	r3, [r4, #244]
	cmp	r3, #524288
	bls	.L3550
	ldr	r1, .L3611+28
	mov	r0, #0
	bl	dprint_vfmw
.L3550:
	ldr	r1, .L3611+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3601
.L3576:
	mov	r1, r2
	b	.L3569
.L3612:
	.align	2
.L3611:
	.word	.LC470
	.word	g_event_report
	.word	g_allow_B_before_P
	.word	.LC469
	.word	.LC468
	.word	.LANCHOR0+948
	.word	.LC471
	.word	.LC466
	.word	.LC467
	UNWIND(.fnend)
	.size	HEVC_DecVDM, .-HEVC_DecVDM
	.align	2
	.global	HEVC_VES_Splitter
	.type	HEVC_VES_Splitter, %function
HEVC_VES_Splitter:
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
	mov	r4, r0
	mov	r5, r1
	ldr	r0, [r0, #2368]
	mov	r1, #16
	mov	r10, r3
	mov	r9, r2
	mov	r6, #0
	str	r6, [fp, #-48]
	bl	BsGet
	mov	r1, #8
	mov	r7, r0
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #24
	and	r8, r0, #31
	ldr	r0, [r4, #2368]
	bl	BsBack
	ldr	r3, [r4, #4016]
	cmp	r5, r6
	str	r6, [r4, #4004]
	str	r3, [fp, #-48]
	beq	.L3615
	cmp	r5, #1
	bne	.L3763
	cmp	r9, #1
	beq	.L3764
	movw	r0, #31745
	cmp	r8, #25
	cmpeq	r7, r0
	moveq	r8, #1
	movne	r8, #0
	bne	.L3644
	ldr	r7, .L3774
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3645
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	r5
.L3645:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2388]
	subs	r5, r0, #0
	beq	.L3646
.L3760:
	cmp	r1, #0
	beq	.L3649
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3649:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3751
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L3623
.L3763:
	mov	r2, r5
	ldr	r1, .L3774+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
.L3623:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3615:
	cmp	r9, #1
	beq	.L3765
	bic	r7, r7, #512
	movw	r3, #31745
	cmp	r7, r3
	beq	.L3766
.L3658:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3644:
	movw	r3, #32257
	cmp	r7, r3
	movne	r0, r5
	bne	.L3623
	ldr	r1, .L3774+8
	movw	r3, #2549
	ldr	r2, .L3774+12
	mov	r0, r8
	bl	dprint_vfmw
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3751
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2388]
	mvn	r0, #0
	b	.L3623
.L3766:
	ldr	r1, .L3774+16
	movw	r3, #2404
	ldr	r2, .L3774+12
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3751
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2388]
	mvn	r0, #0
	b	.L3623
.L3646:
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r4, #4004]
	bhi	.L3767
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r4, #4008]
	add	r3, r3, r0
	ldr	r0, [r4, #252]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r6, r0, #0
	bne	.L3768
	ldr	r5, .L3774+20
	mov	r2, #5
	ldr	r1, .L3774+24
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2388]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r4, #4004]
	add	r1, r1, #6
	blx	r3
	ldr	r1, [r4, #2388]
	ldr	r0, [r4, #4004]
	add	r3, r0, #5
	str	r3, [r4, #4004]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L3651
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L3652
	add	r2, r0, #10
	ldr	r1, .L3774+28
	movw	r3, #2507
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3653
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2388]
.L3653:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3654
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L3654:
	ldr	r0, [r4, #252]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movwne	r3, #2514
	beq	.L3751
.L3750:
	ldr	r2, .L3774+12
	mov	r0, #0
	ldr	r1, .L3774+32
	bl	dprint_vfmw
.L3751:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3764:
	movw	r3, #31745
	cmp	r7, r3
	cmpeq	r10, #2
	moveq	r5, #1
	movne	r5, #0
	cmp	r8, #25
	movne	r5, #0
	andeq	r5, r5, #1
	cmp	r5, #0
	bne	.L3769
	movw	r2, #32257
	cmp	r7, r2
	beq	.L3770
	cmp	r7, r3
	bne	.L3771
.L3633:
	ldr	r1, [r4, #2388]
.L3757:
	cmp	r1, #0
	beq	.L3635
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2388]
	mov	r0, r5
	b	.L3623
.L3765:
	movw	r0, #31745
	cmp	r8, #25
	cmpeq	r7, r0
	moveq	r8, #1
	movne	r8, #0
	bne	.L3618
	ldr	r7, .L3774
	ldr	r6, [r7]
	cmp	r6, #0
	beq	.L3619
	mov	r3, r5
	mov	r2, r5
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	r6
.L3619:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2388]
	subs	r5, r0, #0
	beq	.L3620
	cmp	r1, #0
	beq	.L3625
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3625:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3751
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L3751
.L3618:
	movw	r3, #32257
	cmp	r7, r3
	bne	.L3658
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3635
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2388]
	mov	r0, r8
	b	.L3623
.L3767:
	ldr	r1, .L3774+28
	movw	r3, #2483
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3649
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2388]
	b	.L3649
.L3635:
	mov	r0, #0
	b	.L3623
.L3620:
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r4, #4004]
	bls	.L3624
	ldr	r1, .L3774+28
	movw	r3, #2318
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3625
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2388]
	b	.L3625
.L3652:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2388]
	ldr	r3, [r4, #4004]
	ldr	r2, [r2, #72]
	add	r3, r3, r2
	str	r3, [r4, #4004]
.L3651:
	ldr	r0, [r4, #252]
	ldr	r6, .L3774+36
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L3655
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #252]
	ldr	r3, [r5, #44]
	ldr	r1, [r4, #4004]
	ldr	r2, [r6, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #252]
.L3655:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	movwne	r3, #2537
	beq	.L3633
	b	.L3750
.L3771:
	mov	r1, #8
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	ldr	r0, [r4, #2368]
	ubfx	r5, r5, #1, #6
	bl	BsSkip
	cmp	r5, #49
	beq	.L3772
.L3643:
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3635
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2388]
	b	.L3623
.L3769:
	ldr	r7, .L3774
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3638
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	r5
.L3638:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2388]
	subs	r5, r0, #0
	beq	.L3757
	b	.L3760
.L3624:
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r4, #4008]
	add	r3, r3, r0
	ldr	r0, [r4, #252]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r6, r0, #0
	bne	.L3773
	ldr	r5, .L3774+20
	mov	r2, #5
	ldr	r1, .L3774+24
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2388]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r4, #4004]
	add	r1, r1, #6
	blx	r3
	ldr	r1, [r4, #2388]
	ldr	r0, [r4, #4004]
	add	r3, r0, #5
	str	r3, [r4, #4004]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L3628
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L3629
	add	r2, r0, #10
	ldr	r1, .L3774+28
	movw	r3, #2342
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3630
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2388]
.L3630:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3631
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L3631:
	ldr	r0, [r4, #252]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movwne	r3, #2349
	beq	.L3751
	b	.L3750
.L3629:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2388]
	ldr	r3, [r4, #4004]
	ldr	r2, [r2, #72]
	add	r3, r3, r2
	str	r3, [r4, #4004]
.L3628:
	ldr	r0, [r4, #252]
	ldr	r6, .L3774+36
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L3632
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #252]
	ldr	r3, [r5, #44]
	ldr	r1, [r4, #4004]
	ldr	r2, [r6, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #252]
.L3632:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	beq	.L3633
	movw	r3, #2377
	b	.L3750
.L3770:
	ldr	r0, [r4, #2368]
	mov	r1, #16
	bl	BsSkip
	mov	r0, r9
	b	.L3623
.L3772:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	bne	.L3643
	ldr	r3, [r4, #2388]
	ldr	r0, [r4, #2368]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	ldr	r0, [r4, #2368]
	mov	r1, #24
	bl	BsSkip
	mov	r0, #2
	b	.L3623
.L3768:
	mov	r0, r5
	movw	r3, #2495
	ldr	r2, .L3774+12
	ldr	r1, .L3774+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3623
.L3773:
	mov	r0, r5
	movw	r3, #2330
	ldr	r2, .L3774+12
	ldr	r1, .L3774+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3623
.L3775:
	.align	2
.L3774:
	.word	g_event_report
	.word	.LC477
	.word	.LC476
	.word	.LANCHOR0+960
	.word	.LC475
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+208
	.word	.LC472
	.word	.LC474
	.word	vfmw_save_metadata_file
	.word	.LC473
	UNWIND(.fnend)
	.size	HEVC_VES_Splitter, .-HEVC_VES_Splitter
	.align	2
	.global	HEVC_CRAOutputFrame
	.type	HEVC_CRAOutputFrame, %function
HEVC_CRAOutputFrame:
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
	ldr	r0, [r0, #2600]
	cmp	r0, #0
	beq	.L3788
	add	r2, r4, #2608
	mov	r5, #0
	add	r2, r2, #8
	mov	r3, r5
.L3779:
	ldr	r1, [r2, #4]!
	add	r3, r3, #1
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	cmp	r1, #0
	addeq	r5, r5, #1
	cmp	r3, r0
	bne	.L3779
.L3780:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L3780
	cmp	r5, #0
	ble	.L3782
.L3786:
	ldr	r1, [r4, #2600]
	cmp	r1, #0
	beq	.L3783
	ldr	r3, [r4, #2620]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3790
	add	r2, r4, #2608
	mov	r3, #0
	add	r2, r2, #12
	b	.L3787
.L3784:
	ldr	r0, [r2, #4]!
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L3790
.L3787:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3784
.L3783:
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	subs	r5, r5, #1
	bne	.L3786
.L3782:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3790:
	mov	r1, r3
	b	.L3783
.L3788:
	mov	r5, r0
	b	.L3780
	UNWIND(.fnend)
	.size	HEVC_CRAOutputFrame, .-HEVC_CRAOutputFrame
	.align	2
	.global	HEVC_DecSlice
	.type	HEVC_DecSlice, %function
HEVC_DecSlice:
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
	ldr	r3, [r0, #2388]
	add	r5, r0, #4096
	ldr	r2, .L3879
	mov	ip, #0
	mov	r4, r0
	ldr	r1, [r3, #16]
	str	r1, [r5, #156]
	ldr	r1, [r3, #28]
	str	r1, [r5, #152]
	ldr	r6, [r3, #24]
	str	r6, [r5, #160]
	ldr	r1, [r0, #252]
	strb	ip, [r0, #3]
	ldr	r2, [r2, r1, asl #2]
	ldrsb	r1, [r2, #44]
	cmp	r1, #1
	beq	.L3865
.L3801:
	ldr	r3, [r5, #280]
	cmp	r3, #1
	beq	.L3866
.L3802:
	ldr	r2, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r2, r3
	bcs	.L3867
	ldrb	r3, [r4, #3521]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3868
	mov	r0, r4
	bl	HEVC_PicTypeStatistic
	mov	r0, r4
	bl	HEVC_CalcStreamBits
	ldr	r3, [r5, #280]
	cmp	r3, #2
	beq	.L3819
	ldr	r3, [r4, #2344]
	cmp	r3, #0
	bne	.L3820
	ldrb	r3, [r5, #129]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3869
.L3820:
	mov	r0, r4
	bl	HEVC_WriteSliceMsg
	cmp	r0, #0
	bne	.L3870
.L3823:
	ldr	r3, [r4, #2344]
	cmp	r3, #0
	beq	.L3871
.L3825:
	ldr	r2, [r4, #2904]
	mov	r0, #0
	ldr	r3, [r4, #2908]
	str	r2, [r4, #3564]
	str	r3, [r4, #3568]
.L3807:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3871:
	ldr	r3, [r5, #164]
	mov	r2, #1
	str	r3, [r4, #304]
	ldr	r3, [r5, #140]
	str	r2, [r4, #172]
	str	r3, [r4, #260]
	b	.L3825
.L3866:
	ldr	r3, [r4, #2344]
	cmp	r3, #0
	bne	.L3804
	ldr	r3, [r5, #156]
	clz	r7, r6
	sub	r3, r3, #16
	mov	r7, r7, lsr #5
	cmp	r3, #4
	cmpls	r6, #0
	bne	.L3872
.L3805:
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L3873
.L3806:
	add	r3, r4, r6
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	andeq	r3, r7, #1
	cmp	r3, #0
	beq	.L3808
	ldr	r3, [r4, #2600]
	cmp	r3, #0
	bne	.L3874
.L3808:
	ldr	r0, [r4, #2416]
	ldr	r1, [r0, #12]
	cmp	r1, #0
	bne	.L3809
	ldr	r3, [r4, #2352]
	cmp	r3, #1
	beq	.L3875
	ldr	r3, [r5, #152]
	ldr	r2, [r4, #2400]
	add	r3, r3, #90
	ldr	r1, [r2, r3, asl #2]
.L3812:
	cmp	r7, #0
	beq	.L3809
	add	r6, r4, r6, lsl #2
	ldr	r3, [r6, #212]
	cmp	r3, #-2147483647
	beq	.L3809
	ldr	r2, [r5, #140]
	add	r1, r1, r3
	cmp	r2, r1
	bge	.L3809
	ldr	r1, [r5, #156]
	cmp	r1, #21
	bne	.L3809
	ldr	r1, .L3879+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_CRAOutputFrame
	mov	r3, #-2147483647
	str	r3, [r6, #212]
	ldr	r0, [r4, #2416]
.L3809:
	ldr	r3, [r0, #8]
	cmp	r3, #2
	beq	.L3804
	ldr	r3, [r0, #24]
	mov	r0, r4
	cmp	r3, #2
	beq	.L3876
	bl	HEVC_RefPicProcess
	cmp	r0, #0
	bne	.L3826
.L3804:
	mov	r0, r4
	bl	HEVC_InitPic
	cmn	r0, #2
	beq	.L3807
	cmp	r0, #0
	bne	.L3877
	ldr	r3, [r4, #240]
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r4, #240]
	bl	HEVC_SetScalingList
	mov	r0, r4
	bl	HEVC_WritePicMsg
	cmp	r0, #0
	beq	.L3802
	ldr	r1, .L3879+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3807
.L3865:
	ldr	r1, [r2, #160]
	cmp	r1, #1
	bne	.L3801
	ldr	r2, [r2, #164]
	cmp	r2, #2
	bne	.L3801
	ldr	r1, [r3, #16]
	bl	HEVC_Get_Last_IDR_Frame_Info
	b	.L3801
.L3819:
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3823
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
	b	.L3823
.L3869:
	mov	r0, r4
	bl	HEVC_DecList
	cmp	r0, #0
	bne	.L3878
	mov	r0, r4
	bl	HEVC_IsRefListWrong
	cmp	r0, #0
	beq	.L3820
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r1, .L3879+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3807
.L3872:
	mov	r0, r4
	bl	HEVC_IsPVRFlushPic
	cmp	r0, #0
	beq	.L3806
	b	.L3805
.L3874:
	mov	r0, r4
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L3808
	ldr	r2, .L3879+16
	mov	r0, #1
	ldr	r1, .L3879+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3807
.L3826:
	mvn	r0, #0
	b	.L3807
.L3876:
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	b	.L3804
.L3868:
	ldr	r1, .L3879+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3807
.L3875:
	ldr	ip, [r4, #2400]
	add	r3, ip, #356
	add	ip, ip, #388
.L3811:
	ldr	r2, [r3, #4]!
	cmp	r1, r2
	movcc	r1, r2
	cmp	r3, ip
	bne	.L3811
	b	.L3812
.L3867:
	ldr	r1, .L3879+28
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	ldr	r2, [r4, #152]
	cmp	r3, r2
	bcc	.L3817
	ldr	r1, .L3879+32
	ldr	r5, [r1]
	cmp	r5, #0
	beq	.L3817
	str	r3, [fp, #-36]
	mov	r1, #108
	str	r2, [fp, #-32]
	mov	r3, #8
	sub	r2, fp, #36
	ldr	r0, [r4, #252]
	blx	r5
.L3817:
	ldr	r1, .L3879+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L3807
.L3870:
	ldr	r1, .L3879+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3807
.L3877:
	ldr	r1, .L3879+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3807
.L3878:
	mov	r2, r0
	ldr	r1, .L3879+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3807
.L3873:
	ldr	r2, .L3879+16
	mov	r0, #1
	ldr	r1, .L3879+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3807
.L3880:
	.align	2
.L3879:
	.word	s_pstVfmwChan
	.word	.LC480
	.word	.LC482
	.word	.LC487
	.word	.LANCHOR0+980
	.word	.LC479
	.word	.LC485
	.word	.LC483
	.word	g_event_report
	.word	.LC484
	.word	.LC488
	.word	.LC481
	.word	.LC486
	.word	.LC478
	UNWIND(.fnend)
	.size	HEVC_DecSlice, .-HEVC_DecSlice
	.align	2
	.global	HEVC_DecOneNal
	.type	HEVC_DecOneNal, %function
HEVC_DecOneNal:
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
	ldr	ip, [r0, #2388]
	mov	r4, r0
	ldr	r3, [ip, #8]
	cmp	r3, #0
	ldrne	r1, [r0, #244]
	movne	r2, ip
	movne	r3, #0
	beq	.L3886
.L3885:
	ldr	r0, [r2, #44]
	add	r3, r3, #1
	add	r2, r2, #28
	add	r1, r1, r0
	str	r1, [r4, #244]
	ldr	r0, [ip, #8]
	cmp	r0, r3
	bhi	.L3885
.L3886:
	mov	r3, #0
	strb	r3, [ip]
	ldr	r3, [r4, #2388]
	ldr	r2, [r3, #16]
	sub	r2, r2, #36
	cmp	r2, #1
	bls	.L4027
.L3884:
	ldr	r2, [r3, #4]
	add	r2, r2, #16
	str	r2, [r3, #4]
	ldr	r1, [r4, #2388]
	ldr	r2, [r1, #16]
	cmp	r2, #49
	ldrls	pc, [pc, r2, asl #2]
	b	.L3887
.L3889:
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3888
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3890
	.word	.L3891
	.word	.L3892
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3893
	.word	.L3893
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3887
	.word	.L3894
	.word	.L3895
.L4027:
	mov	r2, #1
	strb	r2, [r4, #3]
	b	.L3884
.L3895:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	beq	.L4028
.L3911:
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L4014
.L4016:
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2388]
.L4013:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3888:
	mov	r0, r4
	bl	HEVC_DecSlice
	cmn	r0, #2
	beq	.L4013
	cmp	r0, #0
	beq	.L4014
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L4025
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L4025:
	ldr	r3, .L4030
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4015
.L4017:
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r5
.L4015:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3890:
	mov	r0, r4
	bl	HEVC_DecVPS
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3896
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3896:
	cmp	r5, #0
	bne	.L4029
.L4014:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3891:
	mov	r0, r4
	bl	HEVC_DecSPS
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3901
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3901:
	cmp	r5, #0
	beq	.L4014
	ldr	r6, .L4030
	mov	r0, #1
	ldr	r1, .L4030+4
	bl	dprint_vfmw
	ldr	r7, [r6]
	cmp	r7, #0
	bne	.L4021
	b	.L4015
.L3892:
	mov	r0, r4
	bl	HEVC_DecPPS
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3903
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3903:
	cmp	r5, #0
	beq	.L4014
	ldr	r6, .L4030
	mov	r0, #1
	ldr	r1, .L4030+8
	bl	dprint_vfmw
	ldr	r7, [r6]
	cmp	r7, #0
	beq	.L4015
.L4021:
	sub	r2, fp, #28
	mvn	r5, #0
	mov	r3, #4
	mov	r1, #100
	str	r5, [r2, #-4]!
	ldr	r0, [r4, #252]
	blx	r7
	ldr	r6, [r6]
	cmp	r6, #0
	beq	.L4015
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3893:
	mov	r0, r4
	bl	HEVC_DecSEI
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3904
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3904:
	cmp	r5, #0
	beq	.L4014
	ldr	r1, .L4030+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4025
.L3894:
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3909
	cmp	r1, #0
	beq	.L3908
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3908:
	ldrb	r3, [r4, #3521]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4014
.L3909:
	add	r5, r4, #2560
	mov	r1, #32
	add	r5, r5, #4
	mov	r6, #0
	strb	r6, [r4, #8]
	mov	r0, r5
	bl	BsGet
	mov	r1, #32
	mov	r7, r0
	mov	r0, r5
	bl	BsGet
	movw	r1, #20036
	movw	r2, #20553
	movt	r1, 17221
	movt	r2, 18515
	cmp	r0, r1
	cmpeq	r7, r2
	bne	.L4014
	ldr	r5, .L4030
	ldr	r7, [r5]
	cmp	r7, #0
	beq	.L3910
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	r7
.L3910:
	ldrb	r3, [r4, #3521]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4014
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L4014
.L3913:
	ldr	r5, [r5]
	cmp	r5, #0
	bne	.L4017
	b	.L4015
.L3887:
	ldr	r1, .L4030+16
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r1, [r4, #2388]
	ldr	r3, [r1, #16]
	cmp	r3, #63
	bhi	.L3914
	cmp	r1, #0
	bne	.L4016
	b	.L4014
.L3914:
	ldr	r5, .L4030
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L3915
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r6
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3916
.L3917:
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L3916:
	ldr	r5, [r5]
	cmp	r5, #0
	beq	.L4014
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L4014
.L3915:
	cmp	r1, #0
	bne	.L3917
	b	.L4014
.L4029:
	ldr	r6, .L4030
	mov	r0, #1
	ldr	r1, .L4030+20
	bl	dprint_vfmw
	ldr	r7, [r6]
	cmp	r7, #0
	bne	.L4021
	b	.L4015
.L4028:
	ldr	r5, .L4030
	strb	r0, [r4, #9]
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L3912
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r6
.L3912:
	ldrb	r3, [r4, #3521]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3911
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L3911
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L3913
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
	b	.L3913
.L4031:
	.align	2
.L4030:
	.word	g_event_report
	.word	.LC490
	.word	.LC491
	.word	.LC492
	.word	.LC493
	.word	.LC489
	UNWIND(.fnend)
	.size	HEVC_DecOneNal, .-HEVC_DecOneNal
	.align	2
	.global	HEVC_UnMarkFrameStoreRef
	.type	HEVC_UnMarkFrameStoreRef, %function
HEVC_UnMarkFrameStoreRef:
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
	mov	r3, #0
	strb	r3, [r1, #1]
	mov	r2, r3
	ldr	r1, [r1, #28]
	ldr	r0, [r0, #252]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetRef
	UNWIND(.fnend)
	.size	HEVC_UnMarkFrameStoreRef, .-HEVC_UnMarkFrameStoreRef
	.align	2
	.global	HEVC_InquireSliceProperty
	.type	HEVC_InquireSliceProperty, %function
HEVC_InquireSliceProperty:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	ip, .L4054
	mov	r3, #0
	mov	r8, r1
	mov	r4, r0
	str	r3, [r2]
	mov	r1, r3
	str	r3, [r8]
	mov	r6, r2
	ldr	r3, [ip, #48]
	movw	r2, #1356
	add	r0, r0, #4224
	blx	r3
	ldr	r3, [r4, #2388]
	add	r5, r4, #4096
	mov	r0, r4
	ldr	r2, [r3, #16]
	str	r2, [r5, #156]
	ldr	r2, [r3, #28]
	str	r2, [r5, #152]
	ldr	r3, [r3, #24]
	str	r3, [r5, #160]
	bl	HEVC_DecSliceSegmentHeader
	cmp	r0, #0
	bne	.L4050
	ldr	r2, [r5, #164]
	mov	r1, #1888
	ldr	r3, [r4, #2380]
	movw	r7, #12660
	ldr	r9, [r4, #2344]
	mla	r3, r1, r2, r3
	ldr	r2, [r4, #2376]
	cmp	r9, #1
	ldr	r3, [r3, #32]
	mla	r7, r7, r3, r2
	beq	.L4051
	ldr	r3, [r5, #280]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r8]
	ldr	r0, [r4, #2400]
	ldr	ip, [r4, #2416]
	ldr	r2, [r7, #184]
	ldr	r3, [r0, #184]
	ldr	lr, [ip, #872]
	subs	r1, r2, r3
	ldr	r2, [r0, #64]
	ldr	r3, [r7, #64]
	movne	r1, #1
	cmp	lr, #1
	ldr	r0, [r0, #68]
	ldr	lr, [r7, #68]
	beq	.L4052
.L4039:
	cmp	r3, r2
	moveq	r2, r1
	orrne	r2, r1, #1
	cmp	lr, r0
	moveq	r3, r2
	orrne	r3, r2, #1
	cmp	r3, #0
	beq	.L4042
	mov	r0, #0
	mov	r3, #1
	str	r3, [r6]
.L4035:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4051:
	ldr	r0, [r4, #2368]
	bl	BsResidBits
	ldr	r3, [r7, #188]
	ldr	r1, [r4, #204]
	add	r1, r1, #1
	mov	r5, r0
	ldr	r0, [r7, #192]
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	cmp	r5, r0
	movge	r3, #0
	movlt	r3, #1
	orrs	r3, r3, r5, lsr #31
	bne	.L4037
.L4042:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4050:
	ldr	r1, .L4054+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4054+8
	ldr	r5, [r3]
	cmp	r5, #0
	mvneq	r0, #0
	beq	.L4035
	sub	r2, fp, #36
	ldr	r0, [r4, #252]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	r5
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4052:
	ldr	r5, [r7, #96]
	ldr	r7, [r7, #88]
	cmp	r5, r7
	movcc	r5, r7
	str	r5, [ip, #932]
	ldr	r5, [r4, #2400]
	ldr	r7, [r4, #2416]
	ldr	ip, [r5, #96]
	ldr	r4, [r5, #88]
	ldr	r5, [r7, #932]
	cmp	ip, r4
	movcc	ip, r4
	cmp	ip, #8
	movls	r4, #0
	movhi	r4, #1
	cmp	r5, #8
	movne	r4, #0
	cmp	r4, #0
	beq	.L4053
.L4040:
	mov	ip, #1
	str	ip, [r7, #936]
	str	ip, [r6]
	b	.L4039
.L4053:
	sub	ip, ip, #8
	cmp	r5, #8
	clz	ip, ip
	mov	ip, ip, lsr #5
	movle	ip, #0
	cmp	ip, #0
	beq	.L4039
	b	.L4040
.L4037:
	mov	r3, r0
	mov	r2, r5
	mov	r0, r9
	ldr	r1, .L4054+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4035
.L4055:
	.align	2
.L4054:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC494
	.word	g_event_report
	.word	.LC495
	UNWIND(.fnend)
	.size	HEVC_InquireSliceProperty, .-HEVC_InquireSliceProperty
	.align	2
	.global	HEVC_HaveSliceToDec
	.type	HEVC_HaveSliceToDec, %function
HEVC_HaveSliceToDec:
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
	ldr	r0, [r0, #204]
	cmp	r0, #0
	bne	.L4058
	ldrb	r3, [r4, #3521]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4060
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4058:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4060:
	ldr	r2, .L4061
	ldr	r1, .L4061+4
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4062:
	.align	2
.L4061:
	.word	.LANCHOR0+996
	.word	.LC496
	UNWIND(.fnend)
	.size	HEVC_HaveSliceToDec, .-HEVC_HaveSliceToDec
	.align	2
	.global	HEVC_GetPicStreamSize
	.type	HEVC_GetPicStreamSize, %function
HEVC_GetPicStreamSize:
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
	add	r0, r0, #8192
	ldr	r2, [r0, #236]
	cmp	r2, #0
	beq	.L4066
	mov	r0, #0
.L4065:
	ldr	r3, [r2]
	ldr	r1, [r2, #4]
	ldr	r2, [r2, #1356]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L4065
	ldmfd	sp, {fp, sp, pc}
.L4066:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetPicStreamSize, .-HEVC_GetPicStreamSize
	.align	2
	.global	HEVC_IsFrameEndNal
	.type	HEVC_IsFrameEndNal, %function
HEVC_IsFrameEndNal:
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
	sub	r3, r0, #48
	sub	r0, r0, #32
	cmp	r0, #2
	cmphi	r3, #1
	movls	r0, #1
	movhi	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsFrameEndNal, .-HEVC_IsFrameEndNal
	.align	2
	.global	HEVCDEC_CheckSedOnly
	.type	HEVCDEC_CheckSedOnly, %function
HEVCDEC_CheckSedOnly:
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
	ldr	r3, [r0, #2340]
	mov	r5, #0
	mov	r4, r0
	str	r5, [r0, #2344]
	cmp	r3, #2
	str	r5, [r0, #2352]
	beq	.L4097
	cmp	r3, #1
	beq	.L4098
.L4082:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4098:
	ldr	r3, [r0, #2348]
	cmp	r3, #1
	bne	.L4082
	str	r5, [r0, #2348]
.L4096:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4097:
	ldr	r3, [r0, #2336]
	cmp	r3, r5
	beq	.L4096
	ldr	r3, [r0, #2348]
	cmp	r3, #1
	beq	.L4082
	ldr	r0, [r0, #252]
	bl	VCTRL_CheckFreshSeg
	cmp	r0, #0
	beq	.L4096
	ldr	r0, [r4, #252]
	bl	VCTRL_CheckFreshRaw
	cmp	r0, #0
	beq	.L4096
	ldr	r3, [r4, #2388]
	ldr	r0, [r4, #2368]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2368]
	bl	BsSkip
	ldr	r0, [r4, #2368]
	bl	BsResidBits
	cmp	r0, #15
	ble	.L4096
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsSkip
	mov	r1, #6
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #9
	mov	r6, r0
	ldr	r0, [r4, #2368]
	bl	BsSkip
	mov	r0, r6
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	mov	r7, r0
	beq	.L4099
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L4096
	sub	r3, r6, #48
	sub	r6, r6, #32
	cmp	r6, #2
	cmphi	r3, #1
	bhi	.L4096
.L4078:
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	bne	.L4096
	mov	r3, #1
	mvn	r0, #0
	str	r3, [r4, #2352]
	strb	r3, [r4, #3520]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4099:
	ldr	r0, [r4, #2368]
	bl	BsResidBits
	cmp	r0, #0
	movle	r0, r5
	ble	.L4075
	mov	r1, r7
	ldr	r0, [r4, #2368]
	bl	BsGet
.L4075:
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L4076
	sub	r3, r6, #48
	sub	r6, r6, #32
	cmp	r6, #2
	cmphi	r3, #1
	movls	r3, #1
	movhi	r3, #0
	cmp	r0, #0
	moveq	r0, r3
	orrne	r0, r3, #1
	cmp	r0, #0
	bne	.L4078
.L4076:
	ldrb	r2, [r4, #3521]	@ zero_extendqisi2
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2348]
	mov	r3, #1
	str	r3, [r4, #2344]
	str	r2, [r4, #2356]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_CheckSedOnly, .-HEVCDEC_CheckSedOnly
	.align	2
	.global	HEVCDEC_IsNeedSedOnly
	.type	HEVCDEC_IsNeedSedOnly, %function
HEVCDEC_IsNeedSedOnly:
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
	ldr	r3, [r0, #204]
	mov	r4, r0
	cmp	r3, #0
	beq	.L4103
	ldr	r2, [r0, #2424]
	cmp	r2, #0
	beq	.L4108
.L4103:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4108:
	add	r2, r0, #4096
	ldr	r2, [r2, #1864]
	cmp	r2, #1
	bls	.L4103
	ldr	r2, [r0, #2360]
	cmp	r3, r2
	beq	.L4103
	ldr	r3, [r0, #2344]
	cmp	r3, #1
	beq	.L4109
	cmp	r3, #0
	bne	.L4103
	ldr	r0, [r0, #252]
	bl	VCTRL_CheckFreshRaw
	cmp	r0, #0
	beq	.L4103
	ldr	r0, [r4, #252]
	bl	VCTRL_CheckFreshSeg
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4109:
	ldr	r0, [r0, #2388]
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_IsNeedSedOnly, .-HEVCDEC_IsNeedSedOnly
	.align	2
	.global	HEVCDEC_SetDecParam
	.type	HEVCDEC_SetDecParam, %function
HEVCDEC_SetDecParam:
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
	ldr	r5, [r0, #2348]
	mov	r4, r0
	cmp	r5, #1
	beq	.L4123
.L4111:
	mov	r0, r4
	bl	HEVCDEC_IsNeedSedOnly
	cmp	r0, #1
	beq	.L4124
	ldr	r3, [r4, #2344]
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r4, #2388]
	ldr	ip, [r4, #2356]
	ldr	r0, [r4, #204]
	cmp	r1, #0
	ldr	r2, [r4, #176]
	ldr	r3, [r4, #236]
	sub	r0, r0, #1
	sub	r2, r2, #1
	str	r0, [r4, #204]
	sub	r3, r3, #1
	str	r2, [r4, #176]
	strb	ip, [r4, #3521]
	str	r3, [r4, #236]
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4123:
	ldr	r3, [r0, #204]
	cmp	r3, #0
	beq	.L4111
	ldr	r6, [r0, #2424]
	cmp	r6, #0
	bne	.L4111
	bl	HEVC_DecVDM
	cmp	r0, #0
	streq	r5, [r4, #2352]
	streqb	r5, [r4, #3520]
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2388]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4124:
	add	r2, r4, #8192
	add	lr, r4, #4096
	add	r3, r4, #5888
	mov	ip, #0
	str	r0, [r2, #2924]
	add	r3, r3, #48
	ldr	r1, [r4, #204]
	str	r1, [r4, #2360]
	str	r1, [r2, #232]
	ldr	r2, [r4, #2416]
	ldr	r2, [r2, #652]
	str	r2, [lr, #3168]
	str	r3, [r4, #2424]
	str	ip, [r4, #2348]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_SetDecParam, .-HEVCDEC_SetDecParam
	.align	2
	.global	HEVCDEC_VDMProcSedOnly
	.type	HEVCDEC_VDMProcSedOnly, %function
HEVCDEC_VDMProcSedOnly:
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
	ldr	r6, .L4137
	mov	r3, #180
	ldr	r2, [r0, #2424]
	mov	r4, r0
	ldr	lr, [r0, #252]
	mov	r0, #22
	mla	r1, r3, r1, r6
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #20]
	ldr	ip, .L4137+4
	add	r6, r1, #16
	ldr	r1, .L4137+8
	mla	r5, r2, r3, r3
	ldr	r3, [r6, #4]
	ldr	r7, [ip, lr, asl #2]
	add	r5, r5, r2
	mov	r2, r5
	bl	dprint_vfmw
	ldr	r3, [r6, #4]
	cmp	r3, r5
	ldr	r3, [r4, #2344]
	beq	.L4135
	cmp	r3, #1
	beq	.L4136
.L4130:
	mov	r3, #0
	str	r3, [r4, #2424]
.L4128:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4135:
	cmp	r3, #1
	beq	.L4127
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	moveq	r3, #1
	streq	r3, [r4, #2352]
	streqb	r3, [r4, #3520]
	b	.L4128
.L4136:
	ldr	r1, [r4, #2388]
	mov	r5, #0
	ldr	ip, [r4, #2356]
	ldr	r0, [r4, #204]
	cmp	r1, r5
	ldr	r2, [r4, #176]
	ldr	r3, [r4, #236]
	sub	r0, r0, #1
	sub	r2, r2, #1
	str	r0, [r4, #204]
	sub	r3, r3, #1
	str	r2, [r4, #176]
	strb	ip, [r4, #3521]
	str	r3, [r4, #236]
	str	r5, [r4, #2348]
	beq	.L4130
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2388]
	b	.L4130
.L4127:
	ldr	lr, [r4, #2356]
	mov	ip, #0
	ldr	r0, [r4, #204]
	ldr	r1, [r4, #176]
	ldr	r2, [r4, #236]
	sub	r0, r0, #1
	str	r3, [r4, #2348]
	sub	r1, r1, #1
	str	r0, [r4, #204]
	sub	r2, r2, #1
	str	r1, [r4, #176]
	mov	r0, #0
	str	r2, [r4, #236]
	strb	lr, [r4, #3521]
	strb	r3, [r7, #721]
	strb	r3, [r4, #7]
	str	ip, [r4, #2424]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4138:
	.align	2
.L4137:
	.word	g_BackUp
	.word	s_pstVfmwChan
	.word	.LC497
	UNWIND(.fnend)
	.size	HEVCDEC_VDMProcSedOnly, .-HEVCDEC_VDMProcSedOnly
	.align	2
	.global	HEVCDEC_AllocHevcGlbMem
	.type	HEVCDEC_AllocHevcGlbMem, %function
HEVCDEC_AllocHevcGlbMem:
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
	ldr	r5, .L4145
	ldr	r4, [r5]
	cmp	r4, #0
	beq	.L4143
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4143:
	ldr	r6, .L4145+4
	mov	r0, #372
	movt	r0, 10
	ldr	r3, [r6, #216]
	blx	r3
	cmp	r0, #0
	str	r0, [r5]
	beq	.L4144
	mov	r2, #372
	ldr	r3, [r6, #48]
	movt	r2, 10
	mov	r1, r4
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4144:
	movw	r2, #15227
	ldr	r1, .L4145+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4146:
	.align	2
.L4145:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC498
	UNWIND(.fnend)
	.size	HEVCDEC_AllocHevcGlbMem, .-HEVCDEC_AllocHevcGlbMem
	.align	2
	.global	HEVCDEC_ReleaseHevcGlbMem
	.type	HEVCDEC_ReleaseHevcGlbMem, %function
HEVCDEC_ReleaseHevcGlbMem:
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
	ldr	r4, .L4152
	ldr	r0, [r4]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L4152+4
	ldr	r3, [r3, #220]
	blx	r3
	mov	r3, #0
	str	r3, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4153:
	.align	2
.L4152:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVCDEC_ReleaseHevcGlbMem, .-HEVCDEC_ReleaseHevcGlbMem
	.align	2
	.global	HEVCDEC_Init
	.type	HEVCDEC_Init, %function
HEVCDEC_Init:
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
	ldr	r3, .L4170
	mov	r5, r1
	mov	r4, r0
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L4164
	add	r7, r0, #4096
	ldr	r6, .L4170+4
	movw	r2, #27144
	mov	r1, #0
	ldr	r8, [r7, #1832]
	ldr	r3, [r6, #48]
	blx	r3
	mov	r3, #0
	str	r8, [r7, #1832]
	str	r5, [r4, #2416]
	str	r3, [r4, #2424]
	ldr	r3, [r5, #28]
	cmp	r3, #25
	beq	.L4165
	mov	r3, #17
	mov	r1, #65
	str	r3, [r4, #156]
	mov	r2, #200
	str	r3, [r4, #160]
	mov	r3, #210
	str	r1, [r4, #164]
	str	r2, [r4, #152]
	str	r3, [r4, #168]
.L4158:
	ldr	r0, [r5, #592]
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L4166
	ldr	r2, [r4, #156]
	movw	r9, #12660
	ldr	r0, [r4, #2416]
	mov	r8, #1888
	ldr	r3, [r4, #160]
	mov	r7, #1360
	mov	lr, r2, asl #7
	ldr	ip, [r0, #588]
	add	lr, lr, r2, lsl #2
	ldr	r2, [r4, #152]
	add	r0, lr, ip
	add	ip, r1, ip
	add	r10, r1, r0
	str	r10, [r4, #2376]
	mla	r0, r9, r3, r0
	ldr	r3, [r4, #168]
	mul	r2, r7, r2
	add	r3, r3, #1
	str	ip, [r4, #2372]
	mov	r10, r3, asl #7
	sub	r3, r10, r3, asl #5
	add	r10, r1, r0
	str	r10, [fp, #-48]
	ldr	r10, [r4, #164]
	mla	r0, r8, r10, r0
	ldr	r10, [fp, #-48]
	str	r10, [r4, #2380]
	add	r10, r0, r2
	add	r3, r10, r3
	add	r0, r1, r0
	add	r10, r1, r10
	add	r1, r1, r3
	str	r1, [r4, #2408]
	ldr	r1, [r4, #2416]
	str	r10, [r4, #2412]
	ldr	r10, [r4, #168]
	str	r0, [r4, #2420]
	ldr	r1, [r1, #596]
	add	r3, r3, r10, lsl #2
	cmp	r3, r1
	bhi	.L4167
	ldr	r5, [r5, #624]
	cmp	r5, #0
	beq	.L4168
.L4161:
	ldr	r3, [r6, #48]
	mov	r1, #0
	blx	r3
	ldr	r3, [r4, #168]
	mov	r1, #0
	ldr	r5, [r6, #48]
	add	r3, r3, #1
	ldr	r0, [r4, #2412]
	mov	r2, r3, asl #7
	sub	r2, r2, r3, asl #5
	blx	r5
	ldr	r2, [r4, #168]
	ldr	r3, [r6, #48]
	mov	r1, #0
	ldr	r0, [r4, #2408]
	mov	r2, r2, asl #2
	blx	r3
	ldr	r1, [r4, #160]
	ldr	ip, [r4, #156]
	movw	r3, #12660
	ldr	r0, [r4, #164]
	mov	r2, #1888
	mul	r3, r3, r1
	mov	r1, ip, asl #7
	mul	r2, r2, r0
	add	r1, r1, ip, lsl #2
	ldr	r0, [r4, #2372]
	sub	r1, r1, #132
	ldr	lr, [r4, #2376]
	sub	r3, r3, #12608
	add	r1, r0, r1
	ldr	r0, [r4, #2380]
	sub	r3, r3, #52
	sub	r2, r2, #1888
	str	r1, [r4, #2396]
	add	r3, lr, r3
	add	r2, r0, r2
	str	r3, [r4, #2400]
	str	r2, [r4, #2404]
	mov	r0, r4
	str	ip, [r1, #4]
	ldr	r3, [r4, #2404]
	ldr	r2, [r4, #160]
	str	r2, [r3, #28]
	ldr	r3, [r4, #2400]
	ldr	r2, [r4, #164]
	str	r2, [r3, #56]
	bl	HEVC_InitScalingOrderTable
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #252]
	beq	.L4169
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	bl	HEVC_InitDecPara
	add	r2, r4, #8192
	mov	r3, #0
	movw	ip, #9999
	str	r3, [r2, #2992]
	mov	r1, #1
	ldr	lr, [r4, #164]
	mov	r0, r3
	ldr	r2, [r4, #2416]
	str	r3, [r4, #2364]
	str	lr, [r4, #304]
	str	ip, [r4, #260]
	strb	r1, [r4]
	ldr	r3, [r2, #640]
	str	r3, [r4, #2336]
.L4163:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4168:
	mov	r2, lr
	mov	r0, ip
	ldr	r3, [r6, #48]
	mov	r1, r5
	blx	r3
	ldr	r2, [r4, #160]
	ldr	r3, [r6, #48]
	mov	r1, r5
	ldr	r0, [r4, #2376]
	mul	r2, r9, r2
	blx	r3
	ldr	r2, [r4, #164]
	mov	r1, r5
	ldr	r3, [r6, #48]
	ldr	r0, [r4, #2380]
	mul	r2, r8, r2
	blx	r3
	ldr	r2, [r4, #152]
	ldr	r0, [r4, #2420]
	mul	r2, r7, r2
	b	.L4161
.L4165:
	ldr	r3, [r5, #704]
	str	r3, [r4, #156]
	ldr	r3, [r5, #708]
	str	r3, [r4, #160]
	ldr	r3, [r5, #712]
	str	r3, [r4, #164]
	ldr	r3, [r5, #700]
	add	r2, r3, #5
	str	r2, [r4, #168]
	str	r3, [r4, #152]
	b	.L4158
.L4167:
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L4170+8
	ldr	r1, .L4170+12
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4163
.L4164:
	mov	r0, r3
	ldr	r2, .L4170+8
	ldr	r1, .L4170+16
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4163
.L4169:
	ldr	r2, .L4170+8
	mov	r0, #0
	ldr	r1, .L4170+20
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4163
.L4166:
	ldr	r2, .L4170+8
	ldr	r1, .L4170+24
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4163
.L4171:
	.align	2
.L4170:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1016
	.word	.LC500
	.word	.LC61
	.word	.LC501
	.word	.LC499
	UNWIND(.fnend)
	.size	HEVCDEC_Init, .-HEVCDEC_Init
	.align	2
	.global	HEVCDEC_GetImageBuffer
	.type	HEVCDEC_GetImageBuffer, %function
HEVCDEC_GetImageBuffer:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r3, [r0, #180]
	mov	r4, r0
	cmp	r3, #0
	beq	.L4175
	ldrb	r3, [r0, #3521]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4175
	add	r1, r0, #12736
	add	lr, r0, #27136
	add	r1, r1, #8
	add	lr, lr, #8
.L4181:
	ldr	r3, [r1, #48]
	cmp	r3, #0
	bne	.L4176
	cmp	r1, #0
	beq	.L4177
	ldr	ip, [r4, #2600]
	cmp	ip, #0
	beq	.L4177
	ldr	r2, [r4, #2620]
	cmp	r2, r1
	beq	.L4176
	add	r2, r4, #2608
	add	r2, r2, #12
	b	.L4178
.L4179:
	ldr	r0, [r2, #4]!
	cmp	r0, r1
	beq	.L4176
.L4178:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L4179
.L4177:
	ldr	r0, [r4, #252]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L4175
	cmn	r0, #1
	beq	.L4200
.L4199:
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4175:
	mov	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4176:
	add	r1, r1, #720
	cmp	r1, lr
	bne	.L4181
	add	r0, r4, #5568
	sub	r2, fp, #24
	sub	r1, fp, #28
	add	r0, r0, #16
	bl	GetQueueImgNum
	mov	r0, r4
	bl	HEVC_PrintFrameStoreState
	ldr	r1, .L4201
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r2, [r4, #180]
	ldr	r0, [r4, #2600]
	ldr	r3, [fp, #-28]
	sub	r2, r2, #2
	ldr	r1, [fp, #-24]
	rsb	r2, r0, r2
	add	r0, r3, r1
	cmp	r0, r2
	bge	.L4199
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L4201+4
	ldr	r1, .L4201+8
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4200:
	ldr	r1, .L4201+12
	mov	r0, #1
	bl	dprint_vfmw
	add	r1, r4, #5568
	add	r1, r1, #16
	ldr	r0, [r4, #252]
	bl	FSP_ClearNotInVoQueue
	b	.L4199
.L4202:
	.align	2
.L4201:
	.word	.LC503
	.word	.LANCHOR0+1032
	.word	.LC504
	.word	.LC502
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageBuffer, .-HEVCDEC_GetImageBuffer
	.align	2
	.global	HEVCDEC_DecodePacket
	.type	HEVCDEC_DecodePacket, %function
HEVCDEC_DecodePacket:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	cmp	r1, #0
	mov	lr, #0
	mov	r4, r0
	str	lr, [fp, #-64]
	str	lr, [fp, #-60]
	str	lr, [fp, #-56]
	beq	.L4285
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L4286
	ldr	r2, [r0, #2416]
	ldrb	ip, [r0, #7]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	cmp	ip, #1
	mov	r3, r3, asl #16
	and	r3, r3, #458752
	str	r3, [r0, #248]
	beq	.L4207
	ldr	r3, [r2, #872]
	cmp	r3, #1
	beq	.L4287
.L4208:
	mov	r0, r4
	bl	HEVC_ReceivePacket
	ldr	r3, [r4, #2388]
	str	r3, [r4, #2392]
	mov	r5, r0
.L4209:
	cmp	r5, #0
	mov	r3, #0
	strb	r3, [r4, #7]
	beq	.L4210
.L4236:
	mov	r0, #0
.L4283:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4287:
	ldr	r3, [r2, #920]
	cmp	r3, #1
	bne	.L4208
	ldr	r3, [r0, #328]
	cmp	r3, #1
	bne	.L4208
	ldr	r3, [r0, #2392]
	mov	r0, lr
	str	lr, [r4, #328]
	strb	lr, [r4, #7]
	str	r3, [r4, #2388]
	b	.L4283
.L4210:
	mov	r0, r4
	bl	HEVCDEC_CheckSedOnly
	cmp	r0, #0
	beq	.L4211
	ldr	r3, [r4, #2416]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L4288
.L4211:
	ldr	r3, [r4, #2388]
	mov	r5, #0
	ldr	r6, .L4296
	str	r5, [r3, #4]
	ldr	r3, [r4, #2388]
	ldr	r0, [r4, #2368]
	ldr	r2, [r3, #44]
	ldr	r1, [r3, #40]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2368]
	bl	BsSkip
	ldr	r3, [r4, #252]
	ldr	r2, [r6, r3, asl #2]
	ldrsb	r9, [r2, #44]
	cmp	r9, #1
	movne	r7, #3
	movne	r8, #2
	beq	.L4289
.L4213:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2368]
	ldr	r9, [r4, #2388]
	bl	BsGet
	mov	r1, #6
	str	r0, [r9, #16]
	ldr	r0, [r4, #2368]
	ldr	r9, [r4, #2388]
	bl	BsGet
	str	r0, [r9, #24]
	ldr	r9, [r4, #2388]
	ldr	r2, [r9, #24]
	cmp	r2, #0
	bne	.L4290
	mov	r1, #3
	ldr	r0, [r4, #2368]
	bl	BsGet
	str	r0, [r9, #28]
	ldr	r9, [r4, #2388]
	ldr	r3, [r9, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r9, #28]
	ldrne	r9, [r4, #2388]
	ldr	r0, [r9, #16]
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	mov	r10, r0
	beq	.L4291
	mov	r3, #0
	str	r3, [r9, #4]
	ldr	r3, [r4, #2388]
	add	r0, r4, #2560
	add	r0, r0, #4
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2368]
	bl	BsSkip
	cmp	r7, #1
	cmpeq	r8, #1
	moveq	r3, #1
	movne	r3, #0
	cmp	r5, #1
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	beq	.L4234
	mov	r1, #16
	ldr	r0, [r4, #2368]
	bl	BsSkip
.L4234:
	mov	r1, #1
	ldr	r0, [r4, #2368]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2368]
	ldr	r5, [r4, #2388]
	bl	BsGet
	mov	r1, #6
	str	r0, [r5, #16]
	ldr	r0, [r4, #2368]
	ldr	r5, [r4, #2388]
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #24]
	ldr	r0, [r4, #2368]
	ldr	r5, [r4, #2388]
	bl	BsGet
	str	r0, [r5, #28]
	ldr	r2, [r4, #2388]
	ldr	r3, [r2, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r2, #28]
.L4223:
	mov	r0, r4
	bl	HEVC_DecOneNal
	cmn	r0, #2
	mov	r5, r0
	beq	.L4283
	cmp	r0, #0
	bne	.L4292
	ldr	r3, [r4, #2336]
	str	r0, [r4, #3576]
	cmp	r3, #1
	bne	.L4236
	mov	r0, r4
	bl	HEVCDEC_SetDecParam
	mov	r0, r5
	b	.L4283
.L4207:
	ldr	r3, [r0, #2388]
	cmp	r3, #0
	movne	r5, #0
	mvneq	r5, #0
	cmp	r3, #0
	bne	.L4209
	mov	r0, lr
	ldr	r1, .L4296+4
	bl	dprint_vfmw
	mov	r0, r5
	b	.L4283
.L4289:
	ldr	r8, [r2, #156]
	mov	r0, r4
	ldr	r7, [r2, #160]
	ldr	r3, [r2, #164]
	mov	r1, r8
	mov	r2, r7
	bl	HEVC_VES_Splitter
	cmp	r0, #2
	beq	.L4238
	cmp	r0, #1
	bne	.L4283
	b	.L4213
.L4290:
	ldr	r1, .L4296+8
	mov	r3, #0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L4284
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r4, #2388]
	b	.L4283
.L4291:
	sub	r2, fp, #48
	sub	r1, fp, #52
	mov	r0, r4
	bl	HEVC_InquireSliceProperty
	subs	r3, r0, #0
	bne	.L4218
	ldr	r5, [fp, #-52]
	cmp	r5, #1
	beq	.L4293
.L4219:
	ldr	r5, [fp, #-48]
	cmp	r5, #1
	bne	.L4223
	ldr	r3, [r4, #2388]
	mov	r0, r4
	ldr	r3, [r3, #24]
	add	r3, r4, r3
	ldrb	r7, [r3, #4]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L4294
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L4295
.L4226:
	ldr	r0, [r4, #252]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L4223
	sub	r3, fp, #56
	ldr	r0, [r4, #252]
	sub	r2, fp, #60
	sub	r1, fp, #64
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4, #2416]
	ldr	r0, [r3, #732]
	cmp	r0, #1
	bne	.L4223
	ldr	r5, [fp, #-56]
	cmp	r5, #0
	bgt	.L4229
	ldr	r3, [fp, #-60]
	cmp	r3, #32
	bgt	.L4229
	ldr	r3, [r4, #2424]
	cmp	r3, #0
	bne	.L4229
	ldr	r2, [fp, #-48]
	cmp	r2, #0
	beq	.L4223
	ldr	r3, [r4, #240]
	cmp	r3, #0
	beq	.L4223
	ldr	r3, [r4, #2400]
	ldr	r1, [r4, #320]
	ldr	lr, [r3, #68]
	cmp	lr, r1
	beq	.L4223
	ldr	ip, [r3, #64]
	ldr	r3, [r4, #324]
	subs	r6, ip, r3
	movne	r6, #1
	cmp	r5, #0
	movne	r6, #0
	cmp	r6, #0
	beq	.L4223
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L4296+12
	bl	dprint_vfmw
	ldr	r3, [r4, #2400]
	ldr	r1, .L4296+16
	ldr	r2, [r3, #68]
	ldr	r5, [r1]
	str	r2, [r4, #320]
	cmp	r5, #0
	ldr	r3, [r3, #64]
	str	r3, [r4, #324]
	beq	.L4223
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
	b	.L4223
.L4286:
	mov	r0, lr
	ldr	r1, .L4296+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4283
.L4292:
	ldr	r1, .L4296+24
	mov	r0, #22
	bl	dprint_vfmw
.L4284:
	mvn	r0, #0
	b	.L4283
.L4238:
	mov	r5, r9
	b	.L4213
.L4288:
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L4212
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2388]
.L4212:
	mov	r0, r4
	bl	HEVCDEC_SetDecParam
	mvn	r0, #0
	b	.L4283
.L4218:
	ldr	r1, .L4296+28
	mov	r0, r10
	bl	dprint_vfmw
	ldr	r1, [r4, #2388]
	cmp	r1, #0
	beq	.L4231
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2388]
.L4231:
	ldr	r3, .L4296+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4232
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L4232:
	ldr	r3, [r4, #252]
	ldr	r3, [r6, r3, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	bne	.L4284
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L4284
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L4284
	add	r3, r4, #8192
	ldrb	r5, [r3, #2936]	@ zero_extendqisi2
	cmp	r5, #0
	bne	.L4284
	ldr	r3, .L4296+32
	add	r0, r4, #11072
	add	r0, r0, #56
	mov	r2, #56
	mov	r1, r5
	mov	r6, #0
	ldr	r3, [r3, #48]
	mov	r7, #0
	blx	r3
	add	r3, r4, #2912
	mvn	r0, #0
	strd	r6, [r3, #32]
	strd	r6, [r3, #8]
	strd	r6, [r3, #16]
	strd	r6, [r3, #24]
	str	r5, [r4, #2900]
	b	.L4283
.L4293:
	ldr	r2, [r4, #204]
	cmp	r2, #0
	bne	.L4220
	ldrb	r3, [r4, #3521]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4219
	ldr	r2, .L4296+36
	ldr	r1, .L4296+40
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	b	.L4219
.L4220:
	ldr	ip, [r4, #2388]
	add	r0, r4, #2560
	mov	r2, #21
	add	r0, r0, #4
	ldr	r1, .L4296+44
	str	r3, [ip, #4]
	bl	BsInit
	mov	r1, #40
	ldr	r0, [r4, #2368]
	bl	BsSkip
	ldr	r3, [r4, #2388]
	mov	r2, #48
	mov	r0, r4
	str	r2, [r3, #16]
	strb	r5, [r4, #8]
	bl	HEVC_DecOneNal
	ldr	r3, [r4, #288]
	mvn	r0, #1
	strb	r5, [r4, #7]
	add	r3, r3, #1
	str	r3, [r4, #288]
	b	.L4283
.L4285:
	mov	r0, r1
	ldr	r1, .L4296+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4283
.L4294:
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L4226
	mov	r0, r7
	ldr	r2, .L4296+52
	ldr	r1, .L4296+56
	bl	dprint_vfmw
	b	.L4226
.L4295:
	mov	r0, r5
	ldr	r2, .L4296+52
	ldr	r1, .L4296+60
	bl	dprint_vfmw
	b	.L4226
.L4229:
	ldr	r2, [r4, #252]
	mov	r3, #1
	mvn	r0, #1
	ldr	r2, [r6, r2, asl #2]
	str	r3, [r2, #1528]
	strb	r3, [r4, #7]
	b	.L4283
.L4297:
	.align	2
.L4296:
	.word	s_pstVfmwChan
	.word	.LC507
	.word	.LC508
	.word	.LC509
	.word	g_event_report
	.word	.LC506
	.word	.LC511
	.word	.LC510
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+996
	.word	.LC496
	.word	.LANCHOR0+1080
	.word	.LC505
	.word	.LANCHOR0+1056
	.word	.LC479
	.word	.LC478
	UNWIND(.fnend)
	.size	HEVCDEC_DecodePacket, .-HEVCDEC_DecodePacket
	.align	2
	.global	HEVCDEC_VDMPostProc
	.type	HEVCDEC_VDMPostProc, %function
HEVCDEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r0, [r0, #3580]
	ldr	r2, [r4, #2416]
	mov	r7, r3
	cmp	r0, #0
	ldr	ip, [fp, #4]
	ldr	r3, [fp, #8]
	ldr	r5, [r2, #644]
	str	r1, [r4, #3560]
	beq	.L4299
	add	r2, r4, #4096
	ldrb	r1, [r2, #1845]	@ zero_extendqisi2
	strb	r1, [r0, #3]
	ldrb	r2, [r2, #1840]	@ zero_extendqisi2
	strb	r2, [r0, #4]
	ldr	r2, [r4, #2416]
.L4299:
	ldr	r1, [r4, #2364]
	cmp	r1, #1
	bls	.L4300
.L4303:
	ldr	r1, [r4, #3540]
	cmp	r1, #1920
	bhi	.L4332
.L4301:
	ldr	r2, [r2, #640]
	cmp	ip, #0
	str	r2, [r4, #2336]
	beq	.L4306
.L4336:
	mov	r2, r3, asl #6
	ldr	r1, .L4337
	sub	r3, r2, r3, asl #3
	add	r3, r3, r1
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L4333
	cmp	r3, #1
	beq	.L4306
	cmp	r5, #1
	beq	.L4334
.L4310:
	mov	r1, r7
	mov	r0, r4
	bl	HEVC_StorePicInDPB
	subs	r2, r0, #0
	bne	.L4335
	mov	r3, #1
	mov	r0, r2
	str	r3, [r4, #172]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4332:
	ldr	r1, [r2, #8]
	cmp	r1, #2
	movne	r2, #0
	strne	r2, [r4, #2336]
	beq	.L4301
	cmp	ip, #0
	bne	.L4336
.L4306:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	cmp	r5, #1
	bne	.L4310
.L4334:
	ldr	r8, [r4, #2424]
	ldr	r3, [r8, #1292]
	add	r3, r8, r3, lsl #2
	ldr	r9, [r3, #1476]
	mov	r0, r9
	bl	MEM_Phy2Vir
	ldr	r6, [r8, #192]
	ldr	r3, [r8, #196]
	mov	r1, r9
	add	r6, r6, #15
	ldr	r2, .L4337+4
	add	r3, r3, #15
	bic	r6, r6, #15
	bic	r3, r3, #15
	ldr	r8, [r2, #140]
	mul	r6, r3, r6
	mov	r6, r6, lsr #8
	mov	r2, r6, asl #4
	mov	r5, r0
	blx	r8
	cmp	r6, #0
	beq	.L4321
	mov	r0, #0
	mov	r3, r5
	mov	lr, r0
	mov	r8, r0
	mov	ip, r0
	mvn	r5, #-2147483648
.L4317:
	ldrh	r1, [r3, #4]
	add	ip, ip, #1
	add	r3, r3, #16
	ubfx	r2, r1, #0, #15
	sxth	r1, r1
	rsb	r9, r1, #0
	tst	r1, #32768
	ldrh	r1, [r3, #-10]
	ubfxne	r2, r9, #0, #15
	ubfx	r9, r1, #0, #15
	sxth	r1, r1
	tst	r1, #32768
	rsb	r10, r1, #0
	ubfxne	r9, r10, #0, #15
	add	r2, r2, r9
	cmp	r5, r2
	add	r0, r0, r2
	movge	r5, r2
	cmp	r8, r2
	movlt	r8, r2
	cmp	r2, #0
	addeq	lr, lr, #1
	cmp	ip, r6
	bne	.L4317
	mov	r9, #100
	mul	r9, r9, lr
.L4311:
	mov	r1, r6
	bl	__aeabi_uidiv
	mov	r1, r6
	mov	r10, r0
	mov	r0, r9
	bl	__aeabi_uidiv
	ldr	r3, [r4, #3580]
	cmp	r0, #100
	moveq	r5, #0
	cmp	r3, #0
	beq	.L4319
	str	r8, [r3, #324]
	ldr	r3, [r4, #3580]
	str	r5, [r3, #328]
	ldr	r3, [r4, #3580]
	str	r10, [r3, #332]
	ldr	r3, [r4, #3580]
	str	r0, [r3, #336]
	str	r8, [r4, #3828]
	str	r5, [r4, #3832]
	str	r10, [r4, #3836]
	str	r0, [r4, #3840]
	b	.L4310
.L4335:
	ldr	r1, .L4337+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4300:
	add	r1, r1, #1
	str	r1, [r4, #2364]
	cmp	r1, #1
	bls	.L4301
	b	.L4303
.L4333:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4321:
	mov	r9, r6
	mov	r0, r6
	mvn	r5, #-2147483648
	mov	r8, r6
	b	.L4311
.L4319:
	mov	r0, r3
	ldr	r1, .L4337+12
	bl	dprint_vfmw
	b	.L4310
.L4338:
	.align	2
.L4337:
	.word	g_VdmDrvParam+40
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC513
	.word	.LC512
	UNWIND(.fnend)
	.size	HEVCDEC_VDMPostProc, .-HEVCDEC_VDMPostProc
	.align	2
	.global	HEVCDEC_GetImageWidth
	.type	HEVCDEC_GetImageWidth, %function
HEVCDEC_GetImageWidth:
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
	ldrne	r2, [r0, #2400]
	ldrne	r3, [r2, #132]
	ldrne	r2, [r2, #64]
	rsbne	r0, r3, #0
	addne	r3, r3, r2
	subne	r3, r3, #1
	andne	r0, r0, r3
	mvneq	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageWidth, .-HEVCDEC_GetImageWidth
	.align	2
	.global	HEVCDEC_GetImageHeight
	.type	HEVCDEC_GetImageHeight, %function
HEVCDEC_GetImageHeight:
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
	ldrne	r2, [r0, #2400]
	ldrne	r3, [r2, #132]
	ldrne	r2, [r2, #68]
	rsbne	r0, r3, #0
	addne	r3, r3, r2
	subne	r3, r3, #1
	andne	r0, r0, r3
	mvneq	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageHeight, .-HEVCDEC_GetImageHeight
	.align	2
	.global	HEVCDEC_GetRemainImg
	.type	HEVCDEC_GetRemainImg, %function
HEVCDEC_GetRemainImg:
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
	ldr	r3, [r0, #2600]
	mov	r4, r0
	cmp	r3, #0
	bne	.L4346
	b	.L4350
.L4360:
	ldr	r3, [fp, #-36]
.L4347:
	mov	r1, r3
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r3, [r4, #2600]
	cmp	r3, #0
	beq	.L4350
.L4346:
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	mov	r6, #1
	bl	HEVC_GetMinPOC
	ldr	r3, [fp, #-36]
	mov	r0, r4
	add	r2, r4, r3, lsl #2
	ldr	r5, [r2, #2620]
	cmp	r5, #0
	mov	r1, r5
	beq	.L4347
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	cmp	r2, r6
	beq	.L4347
	strb	r6, [r5, #2]
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r7, r0, #0
	bne	.L4360
	add	r1, r5, #28
	mov	r0, r4
	bl	HEVC_OutputFrame.isra.10
	cmp	r0, #0
	beq	.L4360
	mov	r0, r7
	ldr	r2, .L4361
	ldr	r1, .L4361+4
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	b	.L4360
.L4350:
	add	r0, r4, #5568
	add	r0, r0, #16
	bl	GetVoLastImageID
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4362:
	.align	2
.L4361:
	.word	.LANCHOR0+1104
	.word	.LC422
	UNWIND(.fnend)
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.global	g_pGlbVar
	.global	g_RpuStartCode
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.15082, %object
	.size	__func__.15082, 17
__func__.15082:
	.ascii	"HEVC_OutputFrame\000"
	.space	3
	.type	SarTable.13742, %object
	.size	SarTable.13742, 136
SarTable.13742:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	12
	.word	11
	.word	10
	.word	11
	.word	16
	.word	11
	.word	40
	.word	33
	.word	24
	.word	11
	.word	20
	.word	11
	.word	32
	.word	11
	.word	80
	.word	33
	.word	18
	.word	11
	.word	15
	.word	11
	.word	64
	.word	33
	.word	160
	.word	99
	.word	4
	.word	3
	.word	3
	.word	2
	.word	2
	.word	1
	.type	__func__.13900, %object
	.size	__func__.13900, 18
__func__.13900:
	.ascii	"HEVC_CalcTileInfo\000"
	.space	2
	.type	__func__.14385, %object
	.size	__func__.14385, 27
__func__.14385:
	.ascii	"HEVC_GetUnRefPicWithMinPoc\000"
	.space	1
	.type	__func__.14394, %object
	.size	__func__.14394, 21
__func__.14394:
	.ascii	"HEVC_IncreaseDPBSize\000"
	.space	3
	.type	__func__.14627, %object
	.size	__func__.14627, 17
__func__.14627:
	.ascii	"HEVC_CalcTileMap\000"
	.space	3
	.type	__func__.14647, %object
	.size	__func__.14647, 17
__func__.14647:
	.ascii	"HEVC_WritePicMsg\000"
	.space	3
	.type	__func__.14676, %object
	.size	__func__.14676, 16
__func__.14676:
	.ascii	"HEVC_CheckListX\000"
	.type	__func__.14843, %object
	.size	__func__.14843, 16
__func__.14843:
	.ascii	"HEVC_RepairList\000"
	.type	__func__.14910, %object
	.size	__func__.14910, 16
__func__.14910:
	.ascii	"HEVC_ArrangeMem\000"
	.type	__func__.14983, %object
	.size	__func__.14983, 20
__func__.14983:
	.ascii	"HEVC_RemoveApcStore\000"
	.type	__func__.15261, %object
	.size	__func__.15261, 21
__func__.15261:
	.ascii	"HEVC_CheckFrameStore\000"
	.space	3
	.type	__func__.15329, %object
	.size	__func__.15329, 19
__func__.15329:
	.ascii	"HEVC_GetSLHDR1Info\000"
	.space	1
	.type	__func__.15456, %object
	.size	__func__.15456, 14
__func__.15456:
	.ascii	"HEVC_IsNewPic\000"
	.space	2
	.type	g_Quant8InterDefault, %object
	.size	g_Quant8InterDefault, 64
g_Quant8InterDefault:
	.word	269488144
	.word	403968529
	.word	286265360
	.word	421008402
	.word	303108112
	.word	471406612
	.word	336728336
	.word	555489560
	.word	403968529
	.word	690035737
	.word	421008402
	.word	908665116
	.word	471406612
	.word	1194731809
	.word	555489560
	.word	1531393577
	.type	g_QuantTsDefault, %object
	.size	g_QuantTsDefault, 16
g_QuantTsDefault:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	__func__.15772, %object
	.size	__func__.15772, 16
__func__.15772:
	.ascii	"HEVC_ReleaseNAL\000"
	.type	__func__.14942, %object
	.size	__func__.14942, 20
__func__.14942:
	.ascii	"HEVC_InitDecBuffers\000"
	.type	__func__.13951, %object
	.size	__func__.13951, 12
__func__.13951:
	.ascii	"HEVC_DecVPS\000"
	.type	__func__.15514, %object
	.size	__func__.15514, 24
__func__.15514:
	.ascii	"HEVC_DecScalingListData\000"
	.type	g_CropUnitX, %object
	.size	g_CropUnitX, 16
g_CropUnitX:
	.word	1
	.word	2
	.word	2
	.word	1
	.type	g_CropUnitY, %object
	.size	g_CropUnitY, 16
g_CropUnitY:
	.word	1
	.word	2
	.word	1
	.word	1
	.type	__func__.14020, %object
	.size	__func__.14020, 12
__func__.14020:
	.ascii	"HEVC_DecSPS\000"
	.type	__func__.14061, %object
	.size	__func__.14061, 12
__func__.14061:
	.ascii	"HEVC_DecPPS\000"
	.type	__func__.14499, %object
	.size	__func__.14499, 27
__func__.14499:
	.ascii	"HEVC_DecSliceSegmentHeader\000"
	.space	1
	.type	__func__.14921, %object
	.size	__func__.14921, 13
__func__.14921:
	.ascii	"HEVC_InitDPB\000"
	.space	3
	.type	__func__.15089, %object
	.size	__func__.15089, 19
__func__.15089:
	.ascii	"HEVC_OutputCurrPic\000"
	.space	1
	.type	__func__.15094, %object
	.size	__func__.15094, 23
__func__.15094:
	.ascii	"HEVC_FirstFrameFastOut\000"
	.space	1
	.type	__func__.15253, %object
	.size	__func__.15253, 19
__func__.15253:
	.ascii	"HEVC_OutputFrmToVO\000"
	.space	1
	.type	__func__.15209, %object
	.size	__func__.15209, 22
__func__.15209:
	.ascii	"HEVC_OutputFrmFromDPB\000"
	.space	2
	.type	__func__.14400, %object
	.size	__func__.14400, 30
__func__.14400:
	.ascii	"HEVC_OutputUnRefPicWithMinPoc\000"
	.space	2
	.type	__func__.15228, %object
	.size	__func__.15228, 27
__func__.15228:
	.ascii	"HEVC_FlushOutputFrmFromDPB\000"
	.space	1
	.type	__func__.15835, %object
	.size	__func__.15835, 14
__func__.15835:
	.ascii	"HEVC_ClearDPB\000"
	.space	2
	.type	__func__.14405, %object
	.size	__func__.14405, 23
__func__.14405:
	.ascii	"HEVC_RecoverDPBProcess\000"
	.space	1
	.type	__func__.15189, %object
	.size	__func__.15189, 20
__func__.15189:
	.ascii	"HEVC_InsertFrmInDPB\000"
	.type	__func__.15099, %object
	.size	__func__.15099, 22
__func__.15099:
	.ascii	"HEVC_SimpleDPBProcess\000"
	.space	2
	.type	__func__.15104, %object
	.size	__func__.15104, 21
__func__.15104:
	.ascii	"HEVC_DecOrderProcess\000"
	.space	3
	.type	__func__.15118, %object
	.size	__func__.15118, 22
__func__.15118:
	.ascii	"HEVC_DispOrderProcess\000"
	.space	2
	.type	__func__.15132, %object
	.size	__func__.15132, 19
__func__.15132:
	.ascii	"HEVC_StorePicInDPB\000"
	.space	1
	.type	__func__.14762, %object
	.size	__func__.14762, 12
__func__.14762:
	.ascii	"HEVC_DecVDM\000"
	.type	__func__.13631, %object
	.size	__func__.13631, 18
__func__.13631:
	.ascii	"HEVC_VES_Splitter\000"
	.space	2
	.type	__func__.14436, %object
	.size	__func__.14436, 14
__func__.14436:
	.ascii	"HEVC_DecSlice\000"
	.space	2
	.type	__func__.15917, %object
	.size	__func__.15917, 20
__func__.15917:
	.ascii	"HEVC_HaveSliceToDec\000"
	.type	__func__.15969, %object
	.size	__func__.15969, 13
__func__.15969:
	.ascii	"HEVCDEC_Init\000"
	.space	3
	.type	__func__.15983, %object
	.size	__func__.15983, 23
__func__.15983:
	.ascii	"HEVCDEC_GetImageBuffer\000"
	.space	1
	.type	__func__.15998, %object
	.size	__func__.15998, 21
__func__.15998:
	.ascii	"HEVCDEC_DecodePacket\000"
	.space	3
	.type	g_HevcNalTypeEOP, %object
	.size	g_HevcNalTypeEOP, 21
g_HevcNalTypeEOP:
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
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.space	3
	.type	__func__.16047, %object
	.size	__func__.16047, 21
__func__.16047:
	.ascii	"HEVCDEC_GetRemainImg\000"
	.data
	.align	2
.LANCHOR2 = . + 0
	.type	g_Quant8IntraDefault, %object
	.size	g_Quant8IntraDefault, 64
g_Quant8IntraDefault:
	.word	269488144
	.word	404034065
	.word	269488144
	.word	420877073
	.word	303108112
	.word	488183316
	.word	353505296
	.word	606018328
	.word	403968273
	.word	791225118
	.word	454431506
	.word	1094069283
	.word	521737749
	.word	1480996393
	.word	605886744
	.word	1935163695
	.type	g_QuantTSDefault4x4, %object
	.size	g_QuantTSDefault4x4, 16
g_QuantTSDefault4x4:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.type	g_QuantInterDefault8x8, %object
	.size	g_QuantInterDefault8x8, 64
g_QuantInterDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	91
	.type	g_QuantIntraDefault8x8, %object
	.size	g_QuantIntraDefault8x8, 64
g_QuantIntraDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	21
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	19
	.byte	22
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	22
	.byte	25
	.byte	29
	.byte	16
	.byte	16
	.byte	18
	.byte	21
	.byte	24
	.byte	27
	.byte	31
	.byte	36
	.byte	17
	.byte	17
	.byte	20
	.byte	24
	.byte	30
	.byte	35
	.byte	41
	.byte	47
	.byte	18
	.byte	19
	.byte	22
	.byte	27
	.byte	35
	.byte	44
	.byte	54
	.byte	65
	.byte	21
	.byte	22
	.byte	25
	.byte	31
	.byte	41
	.byte	54
	.byte	70
	.byte	88
	.byte	24
	.byte	25
	.byte	29
	.byte	36
	.byte	47
	.byte	65
	.byte	88
	.byte	115
	.type	g_RpuStartCode, %object
	.size	g_RpuStartCode, 5
g_RpuStartCode:
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	25
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC2:
	ASCII(.ascii	"%s: pImg is NULL!\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"%s: InsertImgToVoQueue failed!\012\000" )
.LC4:
	ASCII(.ascii	"line:%d ChanID(%d), pic_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range(0,%d).\012\000" )
	.space	2
.LC5:
	ASCII(.ascii	"line:%d ChanID(%d), seq_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range[0,%d].\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	"dar=%d\012\000" )
.LC7:
	ASCII(.ascii	"--------------- PrintNaluArraySlot START ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"--------------- PrintNaluArraySlot END ------------" )
	ASCII(.ascii	"---\012\000" )
.LC10:
	ASCII(.ascii	"NalArray[%d]=%p,is_valid=%d   \000" )
	.space	1
.LC11:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX START ---------" )
	ASCII(.ascii	"------\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"List0, size: %d\012\000" )
	.space	3
.LC13:
	ASCII(.ascii	"List1, size: %d\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"pListX[0][%d]:%p \000" )
	.space	2
.LC15:
	ASCII(.ascii	"pFrameStore:%p \000" )
.LC16:
	ASCII(.ascii	"pLogicFs:%p \000" )
	.space	3
.LC17:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX END -----------" )
	ASCII(.ascii	"----\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"pListX[1][%d]: %p\000" )
	.space	2
.LC19:
	ASCII(.ascii	"--------------- PrintFrameStoreState START --------" )
	ASCII(.ascii	"-------\012\000" )
.LC20:
	ASCII(.ascii	"--------------- PrintFrameStoreState END ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC21:
	ASCII(.ascii	"Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displa" )
	ASCII(.ascii	"yed=%d \000" )
	.space	1
.LC22:
	ASCII(.ascii	"p_usrdat[%d]=%p \000" )
	.space	3
.LC23:
	ASCII(.ascii	"--------------- PrintAPCState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"Layer %d: APC.used_size:%d, APC.size:%d\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"%d: is_used=%d, idc=%d, poc=%d\012\000" )
.LC26:
	ASCII(.ascii	"--------------- PrintAPCState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC27:
	ASCII(.ascii	"--------------- PrintDPBState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"DPB: size:%d, used_size:%d, negative:%d, positive:%" )
	ASCII(.ascii	"d, longterm:%d\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"fs[%d]:%p view %d non_existing:%d state:%d is_ref:%" )
	ASCII(.ascii	"d displayed:%d poc:%d long_term:%d LogicFs:%p, fsp_" )
	ASCII(.ascii	"ref:%d fsp_disp:%d logic_id:%d img_id:%d\012\000" )
.LC30:
	ASCII(.ascii	"--------------- PrintDPBState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC31:
	ASCII(.ascii	"fs[%d]\011\000" )
.LC32:
	ASCII(.ascii	"LogicFs:%p\011\000" )
.LC33:
	ASCII(.ascii	"LogicTick:%d\011\000" )
	.space	2
.LC34:
	ASCII(.ascii	"IsRef:%d\011\000" )
	.space	2
.LC35:
	ASCII(.ascii	"DispState:%d\011\000" )
	.space	2
.LC36:
	ASCII(.ascii	"LogicFs:Null\011\000" )
	.space	2
.LC37:
	ASCII(.ascii	"DecFs:%p\011\000" )
	.space	2
.LC38:
	ASCII(.ascii	"DecTick:%d\011\000" )
.LC39:
	ASCII(.ascii	"DecFs:Null\011\000" )
.LC40:
	ASCII(.ascii	"DispFs:%p\011\000" )
	.space	1
.LC41:
	ASCII(.ascii	"DispTick:%d\011\000" )
	.space	3
.LC42:
	ASCII(.ascii	"DispFs:Null\011\000" )
	.space	3
.LC43:
	ASCII(.ascii	"%s num_tile_columns(%d) out of range(0, %d].\012\000" )
	.space	2
.LC44:
	ASCII(.ascii	"%s num_tile_rows(%d) out of range(0, %d].\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"%s 0 idx(%d) out of range(0, 512).\012\000" )
.LC46:
	ASCII(.ascii	"%s 1 idx(%d) out of range(0, 512).\012\000" )
.LC47:
	ASCII(.ascii	"HEVC_Sei_User_Data_Unregistered payloadSize < 16\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC48:
	ASCII(.ascii	"pListX[0][%d] = NULL, listXsize[0] = %d\012\000" )
	.space	3
.LC49:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL, listXsize[0] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC50:
	ASCII(.ascii	"pListX[0][%d] frame_store(%p), pstLogicFs(%p) inval" )
	ASCII(.ascii	"id\012\000" )
	.space	1
.LC51:
	ASCII(.ascii	"pListX[1][%d] = NULL, listXsize[1] = %d\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL, listXsize[1] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC53:
	ASCII(.ascii	"pListX[i][%d] pstLogicFs(%p) invalid\012\000" )
	.space	2
.LC54:
	ASCII(.ascii	"%s DPB.used_size(%d) >= 17.\012\000" )
	.space	3
.LC55:
	ASCII(.ascii	"%s can't find such pic.\012\000" )
	.space	3
.LC56:
	ASCII(.ascii	"%s find pos=%d, poc=%d.\012\000" )
	.space	3
.LC57:
	ASCII(.ascii	"%s DPB.size(%d) already reached max(%d).\012\000" )
	.space	2
.LC58:
	ASCII(.ascii	"%s increase DPB size to %d\012\000" )
.LC59:
	ASCII(.ascii	"%s no enough fs(total_fs_num=%d) to increase DPB si" )
	ASCII(.ascii	"ze.\012\000" )
.LC60:
	ASCII(.ascii	"TileWidthInCtb is 0\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"%s: g_pGlbVar is NULL!\012\000" )
.LC62:
	ASCII(.ascii	"image_id=%d, pmv_idc=%d\012\000" )
	.space	3
.LC63:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"%s call HEVC_CalcTileInfo failed.\012\000" )
	.space	1
.LC65:
	ASCII(.ascii	"logic frame id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC67:
	ASCII(.ascii	"%s ERROR: bHaveIndependentSlice = 0\012\012\000" )
	.space	2
.LC68:
	ASCII(.ascii	"ListX ERROR: list0size >= %d\012\000" )
	.space	2
.LC69:
	ASCII(.ascii	"ListX ERROR: list1size >= %d\012\000" )
	.space	2
.LC70:
	ASCII(.ascii	"pListX[0][%d] = NULL\012\000" )
	.space	2
.LC71:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL\012\000" )
	.space	1
.LC72:
	ASCII(.ascii	"pListX[1][%d] = NULL\012\000" )
	.space	2
.LC73:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL\012\000" )
	.space	1
.LC74:
	ASCII(.ascii	"NumSlicePara(%d) >= MaxSliceNum(%d)\012\000" )
	.space	3
.LC75:
	ASCII(.ascii	"line:%d pic_parameter_set_id(%d) out of range(0,%d)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC76:
	ASCII(.ascii	"line:%d seq_parameter_set_id(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC77:
	ASCII(.ascii	"line:%d, i(%d) > Max(%d) num_of_pics %d\012\000" )
	.space	3
.LC78:
	ASCII(.ascii	"line:%d, i(%d) > Max(%d)(neg%d + pos%d)\012\000" )
	.space	3
.LC79:
	ASCII(.ascii	"%s unkown slice type(%d).\012\000" )
	.space	1
.LC80:
	ASCII(.ascii	"%s pListX[%d] no available pic to repair.\012\000" )
	.space	1
.LC81:
	ASCII(.ascii	"%s: pListX[%d][%d] = NULL, repair it with pos(%d).\012" )
	ASCII(.ascii	"\000" )
.LC82:
	ASCII(.ascii	"HEVC_InitListX error.\012\000" )
	.space	1
.LC83:
	ASCII(.ascii	"HEVC_RepairList error.\012\000" )
.LC84:
	ASCII(.ascii	"%s image size abnormal(%dx%d)\012\000" )
	.space	1
.LC85:
	ASCII(.ascii	"%s HEVC FSP_ConfigInstance failed!\012\000" )
.LC86:
	ASCII(.ascii	"%s fs[%d]->view_id = %d invalid.\012\000" )
	.space	2
.LC87:
	ASCII(.ascii	"../../core/syntax/hevc.c\000" )
	.space	3
.LC88:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC89:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC90:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%" )
	ASCII(.ascii	"d, logic_fs=%p, dec_fs=%p)\012\000" )
	.space	1
.LC91:
	ASCII(.ascii	"Cant find free apc slot.\012\000" )
	.space	2
.LC92:
	ASCII(.ascii	"%s frame logic_fs_id=%d, state=%d\012\000" )
	.space	1
.LC93:
	ASCII(.ascii	"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null," )
	ASCII(.ascii	" logic_fs_id = %d\012\000" )
	.space	2
.LC94:
	ASCII(.ascii	"%s frame poc=%d, is already output\012\000" )
.LC95:
	ASCII(.ascii	"%s frame(%p) invalid, state:%d, non_existing:%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC96:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC97:
	ASCII(.ascii	"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STA" )
	ASCII(.ascii	"TE_NOT_USED\012\000" )
.LC98:
	ASCII(.ascii	"%-5d   specVersion\012\000" )
.LC99:
	ASCII(.ascii	"%-5d   payloadMode\012\000" )
.LC100:
	ASCII(.ascii	"%-5d   hdrPicColourSpace\012\000" )
	.space	2
.LC101:
	ASCII(.ascii	"%-5d   hdrMasterDisplayColourSpace\012\000" )
.LC102:
	ASCII(.ascii	"%-5d   hdrMasterDisplayMaxLuminance\012\000" )
	.space	3
.LC103:
	ASCII(.ascii	"%-5d   hdrMasterDisplayMinLuminance\012\000" )
	.space	3
.LC104:
	ASCII(.ascii	"%-5d   sdrPicColourSpace\012\000" )
	.space	2
.LC105:
	ASCII(.ascii	"%-5d   sdrMasterDisplayColourSpace\012\000" )
.LC106:
	ASCII(.ascii	"%-5d   tmInputSignalBlackLevelOffset\012\000" )
	.space	2
.LC107:
	ASCII(.ascii	"%-5d   tmInputSignalWhiteLevelOffset\012\000" )
	.space	2
.LC108:
	ASCII(.ascii	"%-5d   shadowGain\012\000" )
	.space	1
.LC109:
	ASCII(.ascii	"%-5d   highlightGain\012\000" )
	.space	2
.LC110:
	ASCII(.ascii	"%-5d   midToneWidthAdjFactor\012\000" )
	.space	2
.LC111:
	ASCII(.ascii	"%-5d   tmOutputFineTuningNumVal\012\000" )
	.space	3
.LC112:
	ASCII(.ascii	"%-5d   saturationGainNumVal\012\000" )
	.space	3
.LC113:
	ASCII(.ascii	"%-5d   tmOutputFineTuningX[%d]\012\000" )
.LC114:
	ASCII(.ascii	"%-5d   tmOutputFineTuningY[%d]\012\000" )
.LC115:
	ASCII(.ascii	"%-5d   saturationGainX[%d]\012\000" )
.LC116:
	ASCII(.ascii	"%-5d   saturationGainY[%d]\012\000" )
.LC117:
	ASCII(.ascii	"%-5d   luminanceMappingNumVal\012\000" )
	.space	1
.LC118:
	ASCII(.ascii	"%-5d   colourCorrectionNumVal\012\000" )
	.space	1
.LC119:
	ASCII(.ascii	"%-5d   luminanceMappingX[%d]\012\000" )
	.space	2
.LC120:
	ASCII(.ascii	"%-5d   luminanceMappingY[%d]\012\000" )
	.space	2
.LC121:
	ASCII(.ascii	"%-5d   chromaToLumaInjectionMuA\012\000" )
	.space	3
.LC122:
	ASCII(.ascii	"%-5d   chromaToLumaInjectionMuB\012\000" )
	.space	3
.LC123:
	ASCII(.ascii	"%-5d   colourCorrectionX[%d]\012\000" )
	.space	2
.LC124:
	ASCII(.ascii	"%-5d   colourCorrectionY[%d]\012\000" )
	.space	2
.LC125:
	ASCII(.ascii	"======SL_HDR1_METADATA= %d=======\012\000" )
	.space	1
.LC126:
	ASCII(.ascii	"%s, [%d %d %d %d %d]\012\000" )
	.space	2
.LC127:
	ASCII(.ascii	"%s HDR_Metadata_phy_addr is invalid!!\012\000" )
	.space	1
.LC128:
	ASCII(.ascii	"FS_ALLOC_ERR, ClearAll\012\000" )
.LC129:
	ASCII(.ascii	"Can not new logic fs! ClearAll\012\000" )
.LC130:
	ASCII(.ascii	"FSP_GetFspType -1\012\000" )
	.space	1
.LC131:
	ASCII(.ascii	"FSP_GetLogicFs return NULL\012\000" )
.LC132:
	ASCII(.ascii	"%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), err" )
	ASCII(.ascii	"or resilence.\012\000" )
	.space	2
.LC133:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC134:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC135:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC136:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC137:
	ASCII(.ascii	"sps with this seq_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC138:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck video_parameter_set_id out of r" )
	ASCII(.ascii	"ange\012\000" )
	.space	3
.LC139:
	ASCII(.ascii	"vps with this video_parameter_set_id = %d havn't be" )
	ASCII(.ascii	" decoded\012\000" )
	.space	3
.LC140:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, n" )
	ASCII(.ascii	"al_unit_type = %d, should skip this frame\012\000" )
	.space	2
.LC141:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d," )
	ASCII(.ascii	" nal_unit_type = %d, should skip this frame\012\000" )
.LC142:
	ASCII(.ascii	"%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocC" )
	ASCII(.ascii	"RA = %d, nal_unit_type = %d, should skip this frame" )
	ASCII(.ascii	"\012\000" )
.LC143:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code should not be zero.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC144:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code:%d\012\000" )
	.space	3
.LC145:
	ASCII(.ascii	"reserved_zero_2bits not equal 0.\012\000" )
	.space	2
.LC146:
	ASCII(.ascii	"HEVC_GetScalingListDefaultAddress NULL.\012\000" )
	.space	3
.LC147:
	ASCII(.ascii	"Error, BsLen: 0x%x, TotalPos: 0x%x\012\000" )
.LC148:
	ASCII(.ascii	"Panic: All zero data sequence in RBSP \012\000" )
.LC149:
	ASCII(.ascii	"nal_trail_zero_bit_num err\012\000" )
.LC150:
	ASCII(.ascii	"%s release streambuff=%p, bitstream_length=%d\012\000" )
	.space	1
.LC151:
	ASCII(.ascii	"%s DPB size exceed %d, force to %d\012\000" )
.LC152:
	ASCII(.ascii	"HEVC_CombinePacket FATAL: pCurrNal=NULL!\012\000" )
	.space	2
.LC153:
	ASCII(.ascii	"END of the bit buffer, copy the first packet!\012\000" )
	.space	1
.LC154:
	ASCII(.ascii	"tone_map_id\000" )
.LC155:
	ASCII(.ascii	"Unsupport: target_bit_depth(%d) > 8\012\000" )
	.space	3
.LC156:
	ASCII(.ascii	"pTon->num_pivots > 256\012\000" )
.LC157:
	ASCII(.ascii	"frame_packing_arrangement_id\000" )
	.space	3
.LC158:
	ASCII(.ascii	"frame_packing_arrangement_type(%d) out of range\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC159:
	ASCII(.ascii	"decoding_unit_idx\000" )
	.space	2
.LC160:
	ASCII(.ascii	"num_sps_ids_minus1\000" )
	.space	1
.LC161:
	ASCII(.ascii	"pAct->num_sps_ids_minus1 > 15\012\000" )
	.space	1
.LC162:
	ASCII(.ascii	"active_seq_parameter_set_id\000" )
.LC163:
	ASCII(.ascii	"bp_seq_parameter_set_id\000" )
.LC164:
	ASCII(.ascii	"Wrong bp_seq_parameter_set_id = %d, should be 0 to " )
	ASCII(.ascii	"15!\012\000" )
.LC165:
	ASCII(.ascii	"num_decoding_units_minus1\000" )
	.space	2
.LC166:
	ASCII(.ascii	"pPic->num_decoding_units_minus1 > 255\012\000" )
	.space	1
.LC167:
	ASCII(.ascii	"num_nalus_in_du_minus1\000" )
	.space	1
.LC168:
	ASCII(.ascii	"cv_rec_id\000" )
	.space	2
.LC169:
	ASCII(.ascii	"HEVC_Sei_User_Data_Registered_Itu_T_T35 payloadSize" )
	ASCII(.ascii	" < 4!!\012\000" )
	.space	1
.LC170:
	ASCII(.ascii	"delta_idx_minus1\000" )
	.space	3
.LC171:
	ASCII(.ascii	"delta_idx(%d) > idx(%d).\012\000" )
	.space	2
.LC172:
	ASCII(.ascii	"rIdx(%d) > (idx-1)(%d) or < 0).\012\000" )
	.space	3
.LC173:
	ASCII(.ascii	"abs_delta_rps_minus1\000" )
	.space	3
.LC174:
	ASCII(.ascii	"pTempRPset->num_of_pics(%d) out of range(0,15).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC175:
	ASCII(.ascii	"num_of_pics out of range(0,15).\012\000" )
	.space	3
.LC176:
	ASCII(.ascii	"num_negative_pics\000" )
	.space	2
.LC177:
	ASCII(.ascii	"pTempRPset->num_negative_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC178:
	ASCII(.ascii	"num_positive_pics\000" )
	.space	2
.LC179:
	ASCII(.ascii	"pTempRPset->num_positive_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC180:
	ASCII(.ascii	"pShortTermRpset->num_of_pics(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC181:
	ASCII(.ascii	"delta_poc_s0_minus1\000" )
.LC182:
	ASCII(.ascii	"delta_poc_s0_minus1(%d) out of range.\012\000" )
	.space	1
.LC183:
	ASCII(.ascii	"delta_poc_s1_minus1\000" )
.LC184:
	ASCII(.ascii	"elemental_duration_in_tc_minus1\000" )
.LC185:
	ASCII(.ascii	"cpb_cnt_minus1\000" )
	.space	1
.LC186:
	ASCII(.ascii	"cpb_cnt_minus1(%d) out of range(0,31).\012\000" )
.LC187:
	ASCII(.ascii	"bit_rate_value_minus1\000" )
	.space	2
.LC188:
	ASCII(.ascii	"cpb_size_value_minus1\000" )
	.space	2
.LC189:
	ASCII(.ascii	"cpb_size_du_value_minus1\000" )
	.space	3
.LC190:
	ASCII(.ascii	"bit_rate_du_value_minus1\000" )
	.space	3
.LC191:
	ASCII(.ascii	"vps_base_layer_available_flag(%d) not equal 0x1.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC192:
	ASCII(.ascii	"vps_max_layers_minus1 %d out of range[0,63].\012\000" )
	.space	2
.LC193:
	ASCII(.ascii	"vps_max_sub_layers_minus1=%d\012\000" )
	.space	2
.LC194:
	ASCII(.ascii	"vps_reserved_0xffff_16bits not equal 0xffff.\012\000" )
	.space	2
.LC195:
	ASCII(.ascii	"VPS HEVC_DecPTL error.\012\000" )
.LC196:
	ASCII(.ascii	"vps_num_layer_sets_minus1\000" )
	.space	2
.LC197:
	ASCII(.ascii	"vps_max_dec_pic_buffering_minus1[i]\000" )
.LC198:
	ASCII(.ascii	"vps_num_reorder_pics[i]\000" )
.LC199:
	ASCII(.ascii	"vps_max_latency_increase_plus1[i]\000" )
	.space	2
.LC200:
	ASCII(.ascii	"vps_num_layer_sets_minus1(%d) out of range(0,%d).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC201:
	ASCII(.ascii	"vps_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC202:
	ASCII(.ascii	"vps_num_hrd_parameters\000" )
	.space	1
.LC203:
	ASCII(.ascii	"vps_num_hrd_parameters(%d) out of range[0,%d].\012\000" )
.LC204:
	ASCII(.ascii	"hrd_layer_set_idx\000" )
	.space	2
.LC205:
	ASCII(.ascii	"VPS HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC206:
	ASCII(.ascii	"pVPS->vps_video_parameter_set_id out of range(0,15)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC207:
	ASCII(.ascii	"VPS[%d] decode error0.\012\000" )
.LC208:
	ASCII(.ascii	"VPS[%d] decode error1.\012\000" )
.LC209:
	ASCII(.ascii	"chroma_sample_loc_type_top_field\000" )
	.space	3
.LC210:
	ASCII(.ascii	"chroma_sample_loc_type_bottom_field\000" )
.LC211:
	ASCII(.ascii	"def_disp_win_left_offset\000" )
	.space	3
.LC212:
	ASCII(.ascii	"VUI pSps->chroma_format_idc out of range(0,3).\012\000" )
.LC213:
	ASCII(.ascii	"def_disp_win_right_offset\000" )
	.space	2
.LC214:
	ASCII(.ascii	"def_disp_win_top_offset\000" )
.LC215:
	ASCII(.ascii	"def_disp_win_bottom_offset\000" )
	.space	1
.LC216:
	ASCII(.ascii	"vui_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC217:
	ASCII(.ascii	"VUI HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC218:
	ASCII(.ascii	"min_spatial_segmentation_idc\000" )
	.space	3
.LC219:
	ASCII(.ascii	"VUI min_spatial_segmentation_idc out of range(0,409" )
	ASCII(.ascii	"5).\012\000" )
.LC220:
	ASCII(.ascii	"max_bytes_per_pic_denom\000" )
.LC221:
	ASCII(.ascii	"max_bits_per_min_cu_denom\000" )
	.space	2
.LC222:
	ASCII(.ascii	"log2_max_mv_length_horizontal\000" )
	.space	2
.LC223:
	ASCII(.ascii	"log2_max_mv_length_vertical\000" )
.LC224:
	ASCII(.ascii	"sop_seq_parameter_set_id\000" )
	.space	3
.LC225:
	ASCII(.ascii	"num_entries_in_sop_minus1\000" )
	.space	2
.LC226:
	ASCII(.ascii	"num_entries_in_sop_minus1 out of range(0,1024)\012\000" )
.LC227:
	ASCII(.ascii	"sop_short_term_rps_idx\000" )
	.space	1
.LC228:
	ASCII(.ascii	"sop_poc_delta\000" )
	.space	2
.LC229:
	ASCII(.ascii	"recovery_poc_cnt\000" )
	.space	3
.LC230:
	ASCII(.ascii	"colour_remap_id\000" )
.LC231:
	ASCII(.ascii	"colour_remap_coeffs\000" )
.LC232:
	ASCII(.ascii	"ERROR: post_lut_num_val_minus1 %d out of range[0, 3" )
	ASCII(.ascii	"2]\012\000" )
	.space	1
.LC233:
	ASCII(.ascii	"reserved_payload_extension_data\000" )
.LC234:
	ASCII(.ascii	"line:%d Cosume TotalPos(%d > %d)!!!\012\000" )
	.space	3
.LC235:
	ASCII(.ascii	"HEVC_SeiMessage HEVC_Sei_Payload error.\012\000" )
	.space	3
.LC236:
	ASCII(.ascii	"SEI pSEISPS = NULL.\012\000" )
	.space	3
.LC237:
	ASCII(.ascii	"SEI HEVC_SeiMessage error.\012\000" )
.LC238:
	ASCII(.ascii	"SEI BsIsByteAligned error.\012\000" )
.LC239:
	ASCII(.ascii	"SEI rbsp_trailing_bits(%d) not equal 0x80.\012\000" )
.LC240:
	ASCII(.ascii	"nesting_num_ops_minus1\000" )
	.space	1
.LC241:
	ASCII(.ascii	"nesting_num_ops_minus1 out of range(0,%d)\012\000" )
	.space	1
.LC242:
	ASCII(.ascii	"nesting_op_idx\000" )
	.space	1
.LC243:
	ASCII(.ascii	"nesting_num_layers_minus1\000" )
	.space	2
.LC244:
	ASCII(.ascii	"nesting_num_layers_minus1 out of range(0,63)\012\000" )
	.space	2
.LC245:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta\000" )
	.space	2
.LC246:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta out of range(0,ma" )
	ASCII(.ascii	"trixId).\012\000" )
	.space	3
.LC247:
	ASCII(.ascii	"HEVC_DecScalingListData pMatrixAddress NULL.\012\000" )
	.space	2
.LC248:
	ASCII(.ascii	"scaling_list_dc_coef_minus8\000" )
.LC249:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-7,247).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC250:
	ASCII(.ascii	"scaling_list_delta_coef\000" )
.LC251:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-128,127)." )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC252:
	ASCII(.ascii	"chroma_format_idc\000" )
	.space	2
.LC253:
	ASCII(.ascii	"pSPS->chroma_format_idc out of range(0,3).\012\000" )
.LC254:
	ASCII(.ascii	"pSPS->chroma_format_idc not equal(%d) 1.\012\000" )
	.space	2
.LC255:
	ASCII(.ascii	"pic_width_in_luma_samples\000" )
	.space	2
.LC256:
	ASCII(.ascii	"pic_width_in_luma_samples out of range(0,8192).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC257:
	ASCII(.ascii	"pic_height_in_luma_samples\000" )
	.space	1
.LC258:
	ASCII(.ascii	"pic_height_in_luma_samples out of range(0,4096).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC259:
	ASCII(.ascii	"ERROR Unkown level: %d\012\000" )
.LC260:
	ASCII(.ascii	"conf_win_left_offset\000" )
	.space	3
.LC261:
	ASCII(.ascii	"conf_win_right_offset\000" )
	.space	2
.LC262:
	ASCII(.ascii	"conf_win_left_offset+conf_win_right_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC263:
	ASCII(.ascii	"conf_win_top_offset\000" )
.LC264:
	ASCII(.ascii	"conf_win_bottom_offset\000" )
	.space	1
.LC265:
	ASCII(.ascii	"conf_win_top_offset+conf_win_bottom_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC266:
	ASCII(.ascii	"bit_depth_luma_minus8\000" )
	.space	2
.LC267:
	ASCII(.ascii	"bit_depth_luma(%d) out of range(8,10).\012\000" )
.LC268:
	ASCII(.ascii	"bit_depth_chroma_minus8\000" )
.LC269:
	ASCII(.ascii	"bit_depth_chroma(%d) out of range[8,14].\012\000" )
	.space	2
.LC270:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	2
.LC271:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4 out of range[0,12" )
	ASCII(.ascii	"].\012\000" )
	.space	1
.LC272:
	ASCII(.ascii	"sps_max_dec_pic_buffering_minus1\000" )
	.space	3
.LC273:
	ASCII(.ascii	"sps_num_reorder_pics\000" )
	.space	3
.LC274:
	ASCII(.ascii	"sps_max_latency_increase_plus1\000" )
	.space	1
.LC275:
	ASCII(.ascii	"log2_min_coding_block_size_minus3\000" )
	.space	2
.LC276:
	ASCII(.ascii	"log2_min_luma_coding_block_size_minus3 out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC277:
	ASCII(.ascii	"log2_diff_max_min_coding_block_size\000" )
.LC278:
	ASCII(.ascii	"log2_diff_max_min_luma_coding_block_size out of ran" )
	ASCII(.ascii	"ge(0,3).\012\000" )
	.space	3
.LC279:
	ASCII(.ascii	"log2_ctb_sizeY out of range(4,6).\012\000" )
	.space	1
.LC280:
	ASCII(.ascii	"log2_min_transform_block_size_minus2\000" )
	.space	3
.LC281:
	ASCII(.ascii	"log2_min_transform_block_size_minus2 out of range(0" )
	ASCII(.ascii	",3).\012\000" )
	.space	3
.LC282:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size\000" )
	.space	1
.LC283:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC284:
	ASCII(.ascii	"quadtree_tu_log2_min_size not less than log2_min_cb" )
	ASCII(.ascii	"_sizeY.\012\000" )
.LC285:
	ASCII(.ascii	"quadtree_tu_log2_max_size greater than Min( CtbLog2" )
	ASCII(.ascii	"SizeY, 5 ).\012\000" )
.LC286:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter\000" )
.LC287:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC288:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra\000" )
.LC289:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC290:
	ASCII(.ascii	"SPS HEVC_DecScalingListData error.\012\000" )
.LC291:
	ASCII(.ascii	"SPS sao is off and pic height(%d) is too small.(Log" )
	ASCII(.ascii	"ic Unsupported).\012\000" )
	.space	3
.LC292:
	ASCII(.ascii	"log2_min_pcm_luma_coding_block_size_minus3\000" )
	.space	1
.LC293:
	ASCII(.ascii	"log2_min_pcm_coding_block_size_minus3(%d) out of ra" )
	ASCII(.ascii	"nge[0,2].\012\000" )
	.space	2
.LC294:
	ASCII(.ascii	"log2_diff_max_min_pcm_luma_coding_block_size\000" )
	.space	3
.LC295:
	ASCII(.ascii	"log2_diff_max_min_pcm_coding_block_size(%d) out of " )
	ASCII(.ascii	"range[0,2].\012\000" )
.LC296:
	ASCII(.ascii	"pcm_log2_max_size greater than Min( CtbLog2SizeY, 5" )
	ASCII(.ascii	" ).\012\000" )
.LC297:
	ASCII(.ascii	"num_short_term_ref_pic_sets\000" )
.LC298:
	ASCII(.ascii	"num_short_term_ref_pic_sets out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC299:
	ASCII(.ascii	"SPS HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	1
.LC300:
	ASCII(.ascii	"num_long_term_ref_pic_sps\000" )
	.space	2
.LC301:
	ASCII(.ascii	"num_long_term_ref_pic_sps out of range[0,32].\012\000" )
	.space	1
.LC302:
	ASCII(.ascii	"SPS HEVC_DecVuiParam error.\012\000" )
	.space	3
.LC303:
	ASCII(.ascii	"sps_video_parameter_set_id out of range(0,%d).\012\000" )
.LC304:
	ASCII(.ascii	"sps_max_sub_layers_minus1 out of range(0,%d).\012\000" )
	.space	1
.LC305:
	ASCII(.ascii	"SPS HEVC_DecPTL error.\012\000" )
.LC306:
	ASCII(.ascii	"sps_seq_parameter_set_id\000" )
	.space	3
.LC307:
	ASCII(.ascii	"sps_seq_parameter_set_id out of range(0,%d).\012\000" )
	.space	2
.LC308:
	ASCII(.ascii	"SPS[%d] decode error0.\012\000" )
.LC309:
	ASCII(.ascii	"SPS[%d] decode error.\012\000" )
	.space	1
.LC310:
	ASCII(.ascii	"pps_seq_parameter_set_id\000" )
	.space	3
.LC311:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range[0,15].\012\000" )
	.space	2
.LC312:
	ASCII(.ascii	"SPS(%d) haven't decode.\012\000" )
	.space	3
.LC313:
	ASCII(.ascii	"num_ref_idx_l0_default_active_minus1\000" )
	.space	3
.LC314:
	ASCII(.ascii	"num_ref_idx_l0_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC315:
	ASCII(.ascii	"num_ref_idx_l1_default_active_minus1\000" )
	.space	3
.LC316:
	ASCII(.ascii	"num_ref_idx_l1_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC317:
	ASCII(.ascii	"init_qp_minus26\000" )
.LC318:
	ASCII(.ascii	"pic_init_qp(%d) out of range[-%d,51].\012\000" )
	.space	1
.LC319:
	ASCII(.ascii	"diff_cu_qp_delta_depth\000" )
	.space	1
.LC320:
	ASCII(.ascii	"diff_cu_qp_delta_depth out of range[0,3].\012\000" )
	.space	1
.LC321:
	ASCII(.ascii	"pps_cb_qp_offset\000" )
	.space	3
.LC322:
	ASCII(.ascii	"pic_cb_qp_offset out of range[-12,12].\012\000" )
.LC323:
	ASCII(.ascii	"pps_cr_qp_offset\000" )
	.space	3
.LC324:
	ASCII(.ascii	"pic_cr_qp_offset out of range[-12,12].\012\000" )
.LC325:
	ASCII(.ascii	"num_tile_columns_minus1\000" )
.LC326:
	ASCII(.ascii	"num_tile_columns(%d) out of range(0,%d).\012\000" )
	.space	2
.LC327:
	ASCII(.ascii	"num_tile_rows_minus1\000" )
	.space	3
.LC328:
	ASCII(.ascii	"num_tile_rows out(%d) of range(0,%d).\012\000" )
	.space	1
.LC329:
	ASCII(.ascii	"Logic limit(%d), num_tile_columns(%d) exceed.\012\000" )
	.space	1
.LC330:
	ASCII(.ascii	"Logic limit(%d), num_tile_rows(%d) exceed.\012\000" )
.LC331:
	ASCII(.ascii	"column_width_minus1\000" )
.LC332:
	ASCII(.ascii	"column_width[%d](%d) out of range (0 %d)\012\000" )
	.space	2
.LC333:
	ASCII(.ascii	"row_height_minus1\000" )
	.space	2
.LC334:
	ASCII(.ascii	"row_height[%d](%d) out of range (0 %d)\012\000" )
.LC335:
	ASCII(.ascii	"column_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	2
.LC336:
	ASCII(.ascii	"row_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	1
.LC337:
	ASCII(.ascii	"PPS tile width(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC338:
	ASCII(.ascii	"PPS tile height(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
.LC339:
	ASCII(.ascii	"pps_beta_offset_div2\000" )
	.space	3
.LC340:
	ASCII(.ascii	"pps_beta_offset_div2(%d) out of range(-6,6).\012\000" )
	.space	2
.LC341:
	ASCII(.ascii	"pps_tc_offset_div2\000" )
	.space	1
.LC342:
	ASCII(.ascii	"pps_tc_offset_div2(%d) out of range(-6,6).\012\000" )
.LC343:
	ASCII(.ascii	"PPS HEVC_DecScalingListData error.\012\000" )
.LC344:
	ASCII(.ascii	"log2_parallel_merge_level_minus2\000" )
	.space	3
.LC345:
	ASCII(.ascii	"log2_parallel_merge_level(%d) out of range(2,log2_c" )
	ASCII(.ascii	"tb_sizeY).\012\000" )
	.space	1
.LC346:
	ASCII(.ascii	"pps_pic_parameter_set_id\000" )
	.space	3
.LC347:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range(0,%d).\012\000" )
	.space	2
.LC348:
	ASCII(.ascii	"PPS[%d] decode error.\012\000" )
	.space	1
.LC349:
	ASCII(.ascii	"luma_log2_weight_denom\000" )
	.space	1
.LC350:
	ASCII(.ascii	"luma_log2_weight_denom out of range(0,7).\012\000" )
	.space	1
.LC351:
	ASCII(.ascii	"delta_chroma_log2_weight_denom\000" )
	.space	1
.LC352:
	ASCII(.ascii	"delta_chroma_log2_weight_denom out of range(-7,7).\012" )
	ASCII(.ascii	"\000" )
.LC353:
	ASCII(.ascii	"chroma_log2_weight_denom out of range(0,7).\012\000" )
	.space	3
.LC354:
	ASCII(.ascii	"delta_luma_weight_l0\000" )
	.space	3
.LC355:
	ASCII(.ascii	"delta_luma_weight_l0(%d) out of range(-128,127).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC356:
	ASCII(.ascii	"luma_offset_l0\000" )
	.space	1
.LC357:
	ASCII(.ascii	"luma_offset_l0(%d) out of range(-128,127).\012\000" )
.LC358:
	ASCII(.ascii	"delta_chroma_weight_l0\000" )
	.space	1
.LC359:
	ASCII(.ascii	"delta_chroma_weight_l0 out of range(-128,127).\012\000" )
.LC360:
	ASCII(.ascii	"delta_chroma_offset_l0\000" )
	.space	1
.LC361:
	ASCII(.ascii	"delta_chroma_offset_l0 out of range(-512,511).\012\000" )
.LC362:
	ASCII(.ascii	"delta_luma_weight_l1\000" )
	.space	3
.LC363:
	ASCII(.ascii	"delta_luma_weight_l1 out of range(-128,127).\012\000" )
	.space	2
.LC364:
	ASCII(.ascii	"luma_offset_l1\000" )
	.space	1
.LC365:
	ASCII(.ascii	"luma_offset_l1 out of range(-128,127).\012\000" )
.LC366:
	ASCII(.ascii	"delta_chroma_weight_l1\000" )
	.space	1
.LC367:
	ASCII(.ascii	"delta_chroma_weight_l1 out of range(-128,127).\012\000" )
.LC368:
	ASCII(.ascii	"delta_chroma_offset_l1\000" )
	.space	1
.LC369:
	ASCII(.ascii	"delta_chroma_offset_l1 out of range(-512,511).\012\000" )
.LC370:
	ASCII(.ascii	"slice_pic_parameter_set_id\000" )
	.space	1
.LC371:
	ASCII(.ascii	"%s: pic_parameter_set_id(%d) out of range(0 %d)!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC372:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\012\000" )
.LC373:
	ASCII(.ascii	"max_cu_width(%d)/max_cu_height(%d) = 0\012\000" )
.LC374:
	ASCII(.ascii	"slice_segment_address(%d) out of range(0,%d).\012\000" )
	.space	1
.LC375:
	ASCII(.ascii	"slice_type\000" )
	.space	1
.LC376:
	ASCII(.ascii	"slice_type(%d) out of range(0,2].\012\000" )
	.space	1
.LC377:
	ASCII(.ascii	"HEVC_ClearDPB,LastDisplayPoc:%d poc:%d \012\000" )
	.space	3
.LC378:
	ASCII(.ascii	"SH HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	2
.LC379:
	ASCII(.ascii	"short_term_ref_pic_set_idx(%d) out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
.LC380:
	ASCII(.ascii	"num_long_term_sps\000" )
	.space	2
.LC381:
	ASCII(.ascii	"num_long_term_sps(%d) out of range[0,%d].\012\000" )
	.space	1
.LC382:
	ASCII(.ascii	"num_long_term_pics\000" )
	.space	1
.LC383:
	ASCII(.ascii	"SH ERROR: (num_negative_pics(%d) + num_positive_pic" )
	ASCII(.ascii	"s(%d) + num_of_longterm_pics(%d)) > %d\012\000" )
	.space	1
.LC384:
	ASCII(.ascii	"lt_idx_sps[%d] = %d, but out of range[0,%d].\012\000" )
	.space	2
.LC385:
	ASCII(.ascii	"delta_poc_msb_cycle_lt\000" )
	.space	1
.LC386:
	ASCII(.ascii	"ERROR: pRPS->num_of_pics(%d) > %d.\012\000" )
.LC387:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC388:
	ASCII(.ascii	"num_ref_idx_l0_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC389:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC390:
	ASCII(.ascii	"num_ref_idx_l1_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC391:
	ASCII(.ascii	"pRPS is null.\012\000" )
	.space	1
.LC392:
	ASCII(.ascii	"pRPS->num_of_pics out(%d) of range(0,%d).\012\000" )
	.space	1
.LC393:
	ASCII(.ascii	"SH HEVC_DecRefPicListsModification error.\012\000" )
	.space	1
.LC394:
	ASCII(.ascii	"collocated_ref_idx\000" )
	.space	1
.LC395:
	ASCII(.ascii	"collocated_from_l0_flag=%d, collocated_ref_idx(%d) " )
	ASCII(.ascii	"out of range(0,%d).\012\000" )
.LC396:
	ASCII(.ascii	"SH HEVC_DecPredWeightTable error.\012\000" )
	.space	1
.LC397:
	ASCII(.ascii	"five_minus_max_num_merge_cand\000" )
	.space	2
.LC398:
	ASCII(.ascii	"SH max_num_merge_cand(%d) out of range(1,5).\012\000" )
	.space	2
.LC399:
	ASCII(.ascii	"slice_qp_delta\000" )
	.space	1
.LC400:
	ASCII(.ascii	"SH slice_qp(%d) out of range [-%d,51].\012\000" )
.LC401:
	ASCII(.ascii	"slice_cb_qp_offset\000" )
	.space	1
.LC402:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC403:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out " )
	ASCII(.ascii	"of range[-12,12].\012\000" )
	.space	2
.LC404:
	ASCII(.ascii	"slice_cr_qp_offset\000" )
	.space	1
.LC405:
	ASCII(.ascii	"SH slice_cr_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC406:
	ASCII(.ascii	"SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) ou" )
	ASCII(.ascii	"t of range[-12,12].\012\000" )
.LC407:
	ASCII(.ascii	"slice_beta_offset_div2\000" )
	.space	1
.LC408:
	ASCII(.ascii	"SH slice_beta_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC409:
	ASCII(.ascii	"slice_tc_offset_div2\000" )
	.space	3
.LC410:
	ASCII(.ascii	"SH slice_tc_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC411:
	ASCII(.ascii	"num_entry_point_offsets\000" )
.LC412:
	ASCII(.ascii	"CurrSlice.num_entry_point_offsets(%d) out of range[" )
	ASCII(.ascii	"0,%d].\012\000" )
	.space	1
.LC413:
	ASCII(.ascii	"offset_len_minus1\000" )
	.space	2
.LC414:
	ASCII(.ascii	"CurrSlice.offset_len(%d) out of range[1,32].\012\000" )
	.space	2
.LC415:
	ASCII(.ascii	"slice_segment_header_extension_length\000" )
	.space	2
.LC416:
	ASCII(.ascii	"slice_segment_header_extension_length(%d) out of ra" )
	ASCII(.ascii	"nge [0,256]\012\000" )
.LC417:
	ASCII(.ascii	"bitsLeft(%d) < slice_segment_header_extension_lengt" )
	ASCII(.ascii	"h(%d)\012\000" )
	.space	2
.LC418:
	ASCII(.ascii	"%s arrange mem failed.\012\000" )
.LC419:
	ASCII(.ascii	"Init dec para\012\000" )
	.space	1
.LC420:
	ASCII(.ascii	"HEVC_InitDPB error, return %d\012\000" )
	.space	1
.LC421:
	ASCII(.ascii	"HEVC_AllocFrameStore error\012\000" )
.LC422:
	ASCII(.ascii	"%s: HEVC_OutputFrame failed!\012\000" )
	.space	2
.LC423:
	ASCII(.ascii	"%s output current picture failed\012\000" )
	.space	2
.LC424:
	ASCII(.ascii	"HEVC.c line %d: frame para err(ret=%d), recycle ima" )
	ASCII(.ascii	"ge self\012\000" )
.LC425:
	ASCII(.ascii	"%s: BlockFsPoc:%d, LastPoc:%d!\012\000" )
.LC426:
	ASCII(.ascii	"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\012\000" )
.LC427:
	ASCII(.ascii	"%s: poc:%d, CurPos: %d !\012\000" )
	.space	2
.LC428:
	ASCII(.ascii	"%s call HEVC_GetUnRefPicWithMinPoc failed\012\000" )
	.space	1
.LC429:
	ASCII(.ascii	"%s call HEVC_OutputOneFrmFromDPB failed\012\000" )
	.space	3
.LC430:
	ASCII(.ascii	"%s: HEVC_OutputFrmToVO err!\012\000" )
	.space	3
.LC431:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC432:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC433:
	ASCII(.ascii	"nal_release_err\012\000" )
	.space	3
.LC434:
	ASCII(.ascii	"%s: flush dpb failed, return %d\012\000" )
	.space	3
.LC435:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), need to incr" )
	ASCII(.ascii	"ease DPB size.\012\000" )
	.space	1
.LC436:
	ASCII(.ascii	"%s call HEVC_IncreaseDPBSize failed\012\000" )
	.space	3
.LC437:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), output minpo" )
	ASCII(.ascii	"c frame.\012\000" )
	.space	3
.LC438:
	ASCII(.ascii	"%s with invalid pos(%d)\012\000" )
	.space	3
.LC439:
	ASCII(.ascii	"%s get APC error, ret %d\012\000" )
	.space	2
.LC440:
	ASCII(.ascii	"%s %d: InsertFrmInDPB failed, return %d\012\000" )
	.space	3
.LC441:
	ASCII(.ascii	"%s call HEVC_CheckFrameStore failed!\012\000" )
	.space	2
.LC442:
	ASCII(.ascii	"%s call HEVC_RemoveUnUsedFrameStore Failed.\012\000" )
	.space	3
.LC443:
	ASCII(.ascii	"%s call HEVC_InsertFrmInDPB Failed.\012\000" )
	.space	3
.LC444:
	ASCII(.ascii	"%s call HEVC_FirstFrameFastOut Failed\012\000" )
	.space	1
.LC445:
	ASCII(.ascii	"DPB.used_size may bigger than DPB.size\012\000" )
.LC446:
	ASCII(.ascii	"HEVC_InsertFrmInDPB Failed, ret = %d\012\000" )
	.space	2
.LC447:
	ASCII(.ascii	"%s call HEVC_OutputFrmFromDPB failed\012\000" )
	.space	2
.LC448:
	ASCII(.ascii	"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_" )
	ASCII(.ascii	"NORMAL\012\000" )
	.space	1
.LC449:
	ASCII(.ascii	"%s, REPORT_IFRAME_ERR\012\000" )
	.space	1
.LC450:
	ASCII(.ascii	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\012\000" )
	.space	1
.LC451:
	ASCII(.ascii	"%s call HEVC_IModeProcess Failed\012\000" )
	.space	2
.LC452:
	ASCII(.ascii	"HEVC_StorePicInDpb return(%d) from L%d\012\000" )
.LC453:
	ASCII(.ascii	"%s call HEVC_SimpleDPBProcess Failed\012\000" )
	.space	2
.LC454:
	ASCII(.ascii	"%s call HEVC_DecOrderProcess Failed\012\000" )
	.space	3
.LC455:
	ASCII(.ascii	"%s call HEVC_DispOrderProcess Failed\012\000" )
	.space	2
.LC456:
	ASCII(.ascii	"%s return HEVC_DEC_ERR\012\000" )
.LC457:
	ASCII(.ascii	"No frame store for lost pic.\012\000" )
	.space	2
.LC458:
	ASCII(.ascii	"DPB ERROR: Can not get ref_fs!\012\000" )
.LC459:
	ASCII(.ascii	"DPB no suited fs for lost pic.\012\000" )
.LC460:
	ASCII(.ascii	"Take poc(%d) to creat lost poc(%d).\012\000" )
	.space	3
.LC461:
	ASCII(.ascii	"DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\012\000" )
	.space	1
.LC462:
	ASCII(.ascii	"ERROR: Can not new logic fs!\012\000" )
	.space	2
.LC463:
	ASCII(.ascii	"Lost pic insert in DPB Failed!\012\000" )
.LC464:
	ASCII(.ascii	"Ref frame(poc %d) lost.\012\000" )
	.space	3
.LC465:
	ASCII(.ascii	"s32OutErrThr = %d,drop poc %d because lost ref fram" )
	ASCII(.ascii	"e(pod %d)\012\000" )
	.space	2
.LC466:
	ASCII(.ascii	"DecVDM MaxBytesReceived exceed threshold!\012\000" )
	.space	1
.LC467:
	ASCII(.ascii	"DecVDM no slice and needn't start VDM\012\000" )
	.space	1
.LC468:
	ASCII(.ascii	"IPBDecMode Changed (%d -> %d)\012\000" )
	.space	1
.LC469:
	ASCII(.ascii	"Discard this B(poc=%d) before P, is_ref_idc=%d.\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC470:
	ASCII(.ascii	"VDM start, TotalPicNum=%d.\012\000" )
.LC471:
	ASCII(.ascii	"%s no correct slice in the pic\012\000" )
.LC472:
	ASCII(.ascii	"metadatasize is too large:%d at line:%d\012\000" )
	.space	3
.LC473:
	ASCII(.ascii	"%s:%d Metadata map failed\012\000" )
	.space	1
.LC474:
	ASCII(.ascii	"%s:%d Metadata unmap failed\012\000" )
	.space	3
.LC475:
	ASCII(.ascii	"*****[%s][%d],BL Codec can only dec BL stream!!****" )
	ASCII(.ascii	"*\012\000" )
	.space	2
.LC476:
	ASCII(.ascii	"*****[%s][%d],EL Codec can only dec EL stream in DV" )
	ASCII(.ascii	"_DUAL_VES_IMP stream!!*****\012\000" )
.LC477:
	ASCII(.ascii	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC478:
	ASCII(.ascii	"%s call HEVC_FlushOutputFrmFromDPB failed\012\000" )
	.space	1
.LC479:
	ASCII(.ascii	"%s call HEVC_EmptyFrmFromDPB failed\012\000" )
	.space	3
.LC480:
	ASCII(.ascii	"Meet CRA frame, force output remain frame, CurPoc %" )
	ASCII(.ascii	"d, LastPoc %d\012\000" )
	.space	2
.LC481:
	ASCII(.ascii	"Init pic err, exit\012\000" )
.LC482:
	ASCII(.ascii	"HEVC_WritePicMsg failed!\012\000" )
	.space	2
.LC483:
	ASCII(.ascii	"Start Reason: SliceParaNum= %d\012\000" )
.LC484:
	ASCII(.ascii	"Too many slice , err!\012\000" )
	.space	1
.LC485:
	ASCII(.ascii	"Cur pic not init yet, discard this slice!\012\000" )
	.space	1
.LC486:
	ASCII(.ascii	"Dec List error, ret=%d\012\000" )
.LC487:
	ASCII(.ascii	"Ref List is Wrong!\012\000" )
.LC488:
	ASCII(.ascii	"HEVC_WriteSliceMsg err.\012\000" )
	.space	3
.LC489:
	ASCII(.ascii	"VPS decode error.\012\000" )
	.space	1
.LC490:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC491:
	ASCII(.ascii	"PPS decode error.\012\000" )
	.space	1
.LC492:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC493:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d\012\000" )
.LC494:
	ASCII(.ascii	"HEVC_DecSliceSegmentHeader dec err\012\000" )
.LC495:
	ASCII(.ascii	"CurBitsLen = %d, MinBitsLen = %d\012\000" )
	.space	2
.LC496:
	ASCII(.ascii	"%s last frame fs unrelease, fix it!\012\000" )
	.space	3
.LC497:
	ASCII(.ascii	"CtbNumOneFrame=%d, SedEnd0=%d\012\000" )
	.space	1
.LC498:
	ASCII(.ascii	"OSAL_FP_alloc_virmem g_pGlbVar fail %d\012\000" )
.LC499:
	ASCII(.ascii	"%s: Get context addr failed!\012\000" )
	.space	2
.LC500:
	ASCII(.ascii	"%s FATAL: MemOffset %d > ContextMemSize %d.\012\000" )
	.space	3
.LC501:
	ASCII(.ascii	"%s: VCTRL_GetChanIDByCtx() return -1!\012\000" )
	.space	1
.LC502:
	ASCII(.ascii	"Fs leak, clear dpb fs not in vo queue.\012\000" )
.LC503:
	ASCII(.ascii	"No frame store available!\012\000" )
	.space	1
.LC504:
	ASCII(.ascii	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak" )
	ASCII(.ascii	", ClearAll!\012\000" )
.LC505:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pPacket!\012\000" )
	.space	1
.LC506:
	ASCII(.ascii	"HevcCtx not init!\012\000" )
	.space	1
.LC507:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC508:
	ASCII(.ascii	"nal_layer_id out %d of range[0,1].\012\000" )
.LC509:
	ASCII(.ascii	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\012" )
	ASCII(.ascii	"\000" )
.LC510:
	ASCII(.ascii	"HEVC_InquireSliceProperty error.\012\000" )
	.space	2
.LC511:
	ASCII(.ascii	"HEVC_DecOneNal ERR\012\000" )
.LC512:
	ASCII(.ascii	"pHevcCtx->CurrPic.frame_store is null pointer\012\000" )
	.space	1
.LC513:
	ASCII(.ascii	"HEVC_StorePicInDPB failed, ret = %d\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	g_pGlbVar, %object
	.size	g_pGlbVar, 4
g_pGlbVar:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
