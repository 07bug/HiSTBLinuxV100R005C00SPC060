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
	ldr	r2, [r0, #2348]
	mov	ip, #1888
	ldr	r3, [r7, #132]
	movw	r4, #12660
	str	r1, [fp, #-64]
	ldr	r1, [r7, #1032]
	mla	ip, ip, r3, r2
	ldr	r3, [r7, #1028]
	ldr	lr, [r0, #2344]
	mov	r2, #1
	add	r3, r1, r3
	str	r3, [fp, #-60]
	mov	r5, r3
	ldr	r3, [r7, #1036]
	ldr	r1, [ip, #32]
	cmp	r5, r3
	mla	r1, r4, r1, lr
	ldr	r10, [r1, #116]
	mov	r10, r2, asl r10
	bcs	.L6
	add	r6, r5, #1296
	add	r9, r5, #5120
	add	r6, r6, #10
	add	r9, r9, #16
	ldr	r1, [r0, #2568]
	add	r3, r3, #5120
	sub	r10, r10, #1
	add	r6, r0, r6, lsl #2
	add	r9, r0, r9
	add	r3, r3, #16
	mov	r2, #0
	add	r3, r0, r3
	str	r2, [fp, #-52]
	str	r3, [fp, #-48]
	str	r2, [fp, #-56]
.L7:
	cmp	r1, #0
	beq	.L13
	add	r3, r0, #2576
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
	ldr	lr, [r0, #2384]
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
	add	r5, r0, #5120
	ldr	r10, [fp, #-60]
	ldr	ip, [fp, #-56]
	mov	r8, #0
	mov	r9, r5
	add	r5, r5, #36
	add	r9, r9, #16
.L19:
	cmp	r1, #0
	beq	.L20
	add	r4, r0, #2576
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
	ldr	lr, [r7, #108]
	add	lr, lr, ip
	ldr	ip, [r2, #8]
	cmp	ip, lr
	bne	.L16
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L16
	ldr	lr, [r0, #2384]
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
	ldr	r2, [r7, #128]
	ldr	r3, [r7, #108]
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
	ldr	r2, [r7, #128]
	ldr	r3, [r7, #108]
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
	ldr	r1, [r0, #2568]
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
	ldr	r2, [r0, #2564]
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
	add	r3, r4, #5504
	ldr	r0, [r4, #252]
	add	r3, r3, #48
	str	r6, [sp]
	mov	r2, r4
	mov	r1, #16
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L78
	ldr	r3, [r4, #2384]
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
	add	r0, r0, #24
	ldr	r3, [r3, #48]
	blx	r3
	add	r3, r4, #2880
	mov	r0, #0
	mov	r1, #0
	mov	r2, #0
	strd	r0, [r3, #32]
	strd	r0, [r3, #8]
	strd	r0, [r3, #16]
	strd	r0, [r3, #24]
	str	r2, [r4, #2868]
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
	ldr	ip, [r3, #132]
	cmp	ip, #0
	blt	.L87
	cmp	ip, lr
	bge	.L87
	ldr	r3, [r0, #2348]
	mov	r2, #1888
	mla	ip, r2, ip, r3
	ldr	lr, [ip, #32]
	ldr	ip, [r0, #160]
	cmp	lr, #0
	blt	.L91
	cmp	lr, ip
	bge	.L91
	ldr	r2, [r0, #2344]
	movw	r4, #12660
	ldr	r3, [r1, #36]
	add	ip, r0, #8192
	mla	lr, r4, lr, r2
	str	r3, [ip, #2916]
	ldr	r2, [r1, #40]
	ldr	r3, [ip, #2908]
	str	r2, [ip, #2920]
	cmp	r3, #1
	ldr	r3, [lr, #52]
	add	r3, r3, #90
	ldrb	r6, [lr, r3, asl #2]	@ zero_extendqisi2
	beq	.L99
	ldrb	r3, [ip, #2905]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L95
	ldrb	r3, [r0, #2864]	@ zero_extendqisi2
	add	lr, r0, #2880
	cmp	r3, #0
	beq	.L96
	ldrd	r2, [lr, #16]
	mov	r8, r2
	mov	r9, r3
.L97:
	ldr	r4, [r0, #2880]
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
	add	lr, r0, #2880
	ldr	r4, [r0, #2880]
	ldrd	r2, [lr, #8]
	adds	r2, r2, r4
	adc	r3, r3, #0
	strd	r2, [lr, #32]
.L94:
	add	r7, ip, #2912
	strd	r2, [lr, #24]
	mov	lr, #0
	strb	lr, [ip, #2905]
	ldrd	r4, [r7, #24]
	strd	r4, [r7, #40]
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	cmp	r1, lr
	ldr	r1, [r0, #2884]
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
	ldr	r2, [r0, #2868]
	add	lr, r0, #2880
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
	addhi	r0, r0, #2880
	ldrhid	r2, [r0, #32]
	strhid	r2, [r0, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L107:
	ldr	ip, [r0, #2384]
	mvn	r3, #0
	mvn	r2, #0
	ldrd	r4, [ip, #64]
	cmp	r5, r3
	cmpeq	r4, r2
	beq	.L105
	add	r3, r0, #11136
	movw	r2, #11120
	strd	r4, [r0, r2]
	ldrd	r4, [r3, #-8]
	strd	r4, [r3]
	strd	r4, [r3, #8]
.L105:
	add	r3, r0, #8192
	mov	r2, #1
	strb	r2, [r3, #2904]
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
	add	r3, r0, #11136
	add	r2, r0, #8192
	movw	r1, #11120
	ldrd	r6, [r3]
	mov	r4, r0
	ldr	r5, [r2, #2916]
	ldr	r10, [r2, #2920]
	strd	r6, [fp, #-60]
	cmp	r5, #0
	ldrd	r6, [r3, #-8]
	ldrd	r2, [r0, r1]
	strd	r2, [fp, #-52]
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
	add	r4, r4, #4096
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
	strd	r0, [r4, #40]
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
	ldr	r3, [r6, #2380]
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
	ldr	r2, [r6, #164]
	ldr	r1, .L218+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #164]
	cmp	r3, #0
	addne	r5, r7, #2384
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
	ldr	r3, [r6, #164]
	cmp	r3, r4
	bhi	.L204
.L205:
	ldr	r2, [r6, #168]
	mov	r0, #1
	ldr	r1, .L218+24
	bl	dprint_vfmw
	ldr	r3, [r6, #168]
	cmp	r3, #0
	addne	r5, r7, #2448
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
	ldr	r3, [r6, #168]
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
	addne	r8, r10, #12672
	movne	r9, #0
	addne	r8, r8, #40
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
	ldr	r3, [ip, #228]
	mov	r0, #1
	ldr	ip, [ip, #224]
	add	r7, r5, #12480
	add	r6, r5, #12544
	add	r5, r5, #12608
	add	r7, r7, #36
	add	r6, r6, #36
	str	ip, [sp]
	add	r5, r5, #36
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
	ldr	r1, [r9, #2580]
	ldr	lr, [r9, #2576]
	mov	r0, #1
	ldr	ip, [r9, #2584]
	ldr	r3, [r9, #2568]
	ldr	r2, [r9, #2564]
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L250+4
	bl	dprint_vfmw
	ldr	r3, [r9, #2568]
	cmp	r3, #0
	addne	r4, r9, #2576
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
	ldr	r3, [r9, #2568]
	cmp	r3, r5
	bhi	.L238
.L239:
	ldr	r1, .L250+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #2568]
	cmp	r3, #0
	addne	r5, r9, #2576
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
	ldr	r3, [r9, #2568]
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
	ldr	r3, [r0, #3504]
	cmp	r3, #0
	bne	.L262
	ldr	r2, [r0, #2384]
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
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	ldr	r0, [r4, #2336]
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
	ldr	r1, [r0, #2372]
	mov	r5, r2
	ldr	r2, [r0, #2368]
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
	ldr	r2, [r4, #2372]
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
	ldr	r2, [r4, #2372]
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
	ldr	r2, [r0, #2336]
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
	ldr	r1, [r0, #2336]
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
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r6, #3
	mov	r7, r0
.L317:
	cmp	r7, #0
	bne	.L312
	mov	r4, #16
.L313:
	mov	r1, #8
	ldr	r0, [r5, #2336]
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
	ldr	r0, [r5, #2336]
	bl	BsGet
	subs	r6, r6, #1
	bne	.L317
	b	.L322
.L321:
	mov	r1, #16
	ldr	r0, [r5, #2336]
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
	ldr	r0, [r0, #2336]
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
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #4]!
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r4, r7
	str	r0, [r4, #12]
	bne	.L328
	mov	r1, #16
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #28]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #32]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #36]
	ldr	r0, [r5, #2336]
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
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r1, #16
	strh	r0, [r5, #2]	@ movhi
	ldr	r0, [r6, #2336]
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
	ldr	r0, [r0, #2336]
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
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldr	r0, [r5, #2336]
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
	ldr	r0, [r0, #2336]
	bl	BsGet
	tst	r0, #255
	beq	.L344
.L342:
	ldr	r0, [r4, #2336]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L344:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
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
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #1]
	ldr	r0, [r6, #2336]
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
	ldr	r0, [r5, #2336]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L351
	subs	r6, r6, #16
	beq	.L353
.L352:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2336]
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
	ldr	r3, [r7, #164]
	cmp	r3, #0
	beq	.L361
	ldr	r4, [r0, #2396]
	cmp	r4, #0
	beq	.L362
	ldr	r2, [r4, #16]
	cmp	r2, #0
	addne	r6, r0, #2384
	movne	r4, #0
	addne	r6, r6, #12
	bne	.L367
	b	.L405
.L368:
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L369
	ldr	r3, [r7, #164]
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
	ldr	r3, [r5, #2396]
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
	ldr	r2, [r7, #168]
	cmp	r2, #0
	beq	.L361
	ldr	r4, [r5, #2464]
	cmp	r4, #0
	beq	.L374
	ldr	r2, [r4, #16]
	cmp	r2, #0
	addne	r6, r5, #2464
	movne	r4, #0
	bne	.L378
	b	.L407
.L379:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L380
	ldr	r3, [r7, #168]
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
	ldr	r3, [r7, #164]
.L374:
	mov	r2, r4
	ldr	r1, .L410+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L400
.L409:
	ldr	r3, [r7, #164]
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
	ldr	r3, [r0, #2568]
	cmp	r3, #16
	bhi	.L413
	cmp	r3, #0
	addne	lr, r0, #2576
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
	ldreq	r3, [r0, #2568]
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
	ldr	r3, [r0, #2564]
	mov	r4, r0
	cmp	r3, #16
	bhi	.L427
	ldr	r0, [r0, #252]
	bl	FSP_GetTotalValidFsNum
	ldr	r2, [r4, #252]
	ldr	r1, [r4, #3512]
	mov	r5, r0
	ldr	r0, [r4, #3508]
	bl	FSP_GetOccupiedNum
	rsb	r0, r0, r5
	bic	r0, r0, r0, asr #31
	cmp	r0, #0
	ble	.L426
	ldr	r3, [r4, #2564]
	add	r3, r3, #1
	cmp	r0, r3
	bcc	.L426
	str	r3, [r4, #2564]
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
	str	r5, [r4, #2564]
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
	ldr	r2, [r3, #124]
	sub	r1, r2, #16
	cmp	r1, #5
	bls	.L431
	ldr	r2, [r0, #3492]
	sub	r2, r2, #16
	cmp	r2, #5
	bls	.L442
	ldr	r3, [r3, #116]
	cmp	r3, #1
	beq	.L434
	cmp	r3, #2
	beq	.L435
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [r0, #3504]
	ldmfd	sp, {fp, sp, pc}
.L431:
	mov	r3, #0
	str	r2, [r0, #3492]
	str	r3, [r0, #3504]
	ldmfd	sp, {fp, sp, pc}
.L434:
	ldr	r2, [r0, #3504]
	cmp	r2, #2
	beq	.L443
	str	r3, [r0, #3504]
	ldmfd	sp, {fp, sp, pc}
.L435:
	ldr	r3, [r0, #3504]
	sub	r3, r3, #1
	cmp	r3, #1
	movhi	r3, #0
	strhi	r3, [r0, #3504]
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
	ldr	r0, [r0, #124]
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
	ldr	ip, [r0, #2372]
	mov	r6, r1
	ldrb	r3, [ip, #13]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L487
	ldr	r3, [ip, #72]
	ldr	r7, [ip, #68]
	ldrb	r5, [ip, #15]	@ zero_extendqisi2
	mov	r2, r3
	str	r3, [fp, #-236]
	ldr	r3, [r0, #2368]
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
	ldr	lr, [r0, #2372]
	mov	r6, r1
	ldrb	r3, [lr, #13]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r0, r1
	beq	.L528
	ldr	r3, [lr, #72]
	ldr	r7, [lr, #68]
	mov	r2, r3
	str	r3, [fp, #-232]
	ldr	r3, [r0, #2368]
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
	add	r0, r0, #28
	blx	r3
	add	r3, r10, #8192
	str	r3, [fp, #-60]
	mov	r2, r3
	mov	r3, #0
	str	r3, [r2, #408]
	ldr	r9, [r10, #2372]
	ldr	r1, [r10, #2368]
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
	ldr	r2, [r2, #408]
	str	r1, [fp, #-68]
.L541:
	add	r1, r2, #1072
	add	r0, r9, r7
	add	r1, r1, #3
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
	ldr	r9, [r10, #2372]
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
	ldr	r2, [r2, #408]
.L537:
	add	r1, r10, r2, lsl #3
	ldr	r0, [fp, #-64]
	add	r1, r1, #8576
	sub	ip, r3, #1
	ldr	lr, [fp, #-52]
	add	r2, r2, #1
	str	ip, [r1, #32]
	add	r0, r9, r0, lsl #1
	ldr	r1, [fp, #-60]
	add	lr, lr, #1
	str	lr, [fp, #-52]
	str	r2, [r1, #408]
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
	ldr	r3, [r0, #3524]
	ldr	r2, [r4, #3700]
	mov	r0, #2
	ldr	r1, .L583
	add	r5, r4, #4096
	bl	dprint_vfmw
	ldr	r1, .L583+4
	mov	r0, #4
	mov	r7, #200
	bl	dprint_vfmw
	ldr	r3, [r4, #3496]
	add	r8, r4, #8192
	mov	ip, #0
	ldr	r6, .L583+8
	add	r0, r4, #6016
	str	r3, [r5, #1840]
	add	r0, r0, #16
	ldr	r2, [r4, #3664]
	mul	r7, r7, r3
	str	r2, [r5, #3104]
	mov	r2, #64
	ldr	r3, [r4, #3668]
	str	r3, [r5, #3108]
	ldr	r3, [r4, #3588]
	ldr	r1, [r4, #3592]
	rsb	r1, r3, r1
	str	r1, [r5, #3112]
	ldr	lr, [r4, #3700]
	add	r1, r7, #12608
	add	r1, r1, #40
	add	r1, r4, r1
	str	lr, [r5, #3096]
	ldr	lr, [r4, #3524]
	str	lr, [r5, #3100]
	ldr	lr, [r4, #3688]
	str	lr, [r5, #3116]
	ldr	lr, [r4, #3692]
	str	lr, [r5, #3120]
	ldr	lr, [r4, #3696]
	str	lr, [r5, #3124]
	ldr	lr, [r4, #3596]
	rsb	r3, r3, lr
	str	r3, [r5, #3128]
	ldr	r3, [r4, #3600]
	rsb	r3, lr, r3
	str	r3, [r5, #3132]
	ldr	r3, [r4, #2388]
	str	ip, [r4, #204]
	str	r3, [r8, #204]
	ldr	r3, [r4, #2368]
	ldrb	ip, [r3, #10]	@ zero_extendqisi2
	strb	ip, [r5, #1814]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	strb	ip, [r5, #1815]
	ldrb	ip, [r3, #7]	@ zero_extendqisi2
	strb	ip, [r5, #1816]
	ldrb	ip, [r3, #6]	@ zero_extendqisi2
	strb	ip, [r5, #1817]
	ldrb	ip, [r3, #5]	@ zero_extendqisi2
	strb	ip, [r5, #1818]
	ldr	ip, [r3, #60]
	str	ip, [r5, #1820]
	ldr	ip, [r3, #104]
	strb	ip, [r5, #1824]
	ldr	ip, [r3, #192]
	sub	ip, ip, #1
	str	ip, [r5, #1828]
	ldr	ip, [r3, #188]
	sub	ip, ip, #1
	str	ip, [r5, #1832]
	ldr	ip, [r4, #3500]
	str	ip, [r5, #1836]
	ldr	ip, [r4, #2372]
	ldr	lr, [ip, #84]
	sub	lr, lr, #2
	str	lr, [r5, #1844]
	ldrb	lr, [ip, #11]	@ zero_extendqisi2
	strb	lr, [r5, #1848]
	ldrb	ip, [ip, #10]	@ zero_extendqisi2
	strb	ip, [r5, #1849]
	ldr	ip, [r3, #164]
	str	ip, [r5, #1852]
	ldr	ip, [r3, #168]
	str	ip, [r5, #1856]
	ldr	ip, [r3, #156]
	str	ip, [r5, #1860]
	ldr	ip, [r3, #160]
	str	ip, [r5, #1864]
	ldr	ip, [r3, #148]
	str	ip, [r5, #1868]
	ldr	ip, [r3, #152]
	str	ip, [r5, #1872]
	ldr	ip, [r3, #172]
	ldr	r6, [r6, #52]
	str	ip, [r5, #1876]
	ldr	ip, [r3, #124]
	str	ip, [r5, #1880]
	ldr	ip, [r3, #128]
	str	ip, [r5, #1884]
	ldr	ip, [r3, #100]
	str	ip, [r5, #1888]
	ldr	ip, [r3, #92]
	str	ip, [r5, #1892]
	ldr	ip, [r3, #112]
	str	ip, [r5, #1896]
	ldr	ip, [r3, #108]
	str	ip, [r5, #1900]
	ldr	ip, [r3, #96]
	str	ip, [r5, #1904]
	ldr	r3, [r3, #88]
	str	r3, [r5, #1908]
	blx	r6
	ldr	ip, [r4, #2368]
	add	r2, r4, #8128
	add	r1, r4, #7616
	add	r3, r8, #44
	add	r2, r2, #28
	ldr	lr, [ip, #68]
	add	r1, r1, #28
	mov	r0, r4
	str	lr, [r5, #2000]
	ldr	ip, [ip, #64]
	str	ip, [r5, #2004]
	bl	HEVC_CalcTileInfo
	subs	r6, r0, #0
	bne	.L581
	ldr	r3, [r4, #2372]
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	strb	r2, [r5, #2028]
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	strb	r2, [r5, #2029]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	strb	r2, [r5, #2030]
	ldrb	r2, [r3, #14]	@ zero_extendqisi2
	strb	r2, [r5, #2031]
	ldrb	r2, [r3, #15]	@ zero_extendqisi2
	strb	r2, [r5, #2032]
	ldrb	r2, [r3, #13]	@ zero_extendqisi2
	strb	r2, [r5, #2033]
	ldr	r2, [r4, #2368]
	ldr	r1, [r3, #56]
	ldr	r2, [r2, #128]
	rsb	r2, r1, r2
	str	r2, [r5, #2036]
	ldr	r2, [r3, #52]
	str	r2, [r5, #2040]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	strb	r2, [r5, #2044]
	ldrb	r2, [r3, #12]	@ zero_extendqisi2
	strb	r2, [r5, #2045]
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	strb	r2, [r5, #2046]
	ldr	r2, [r3, #60]
	str	r2, [r5, #2048]
	ldr	r2, [r3, #64]
	str	r2, [r5, #2052]
	ldr	r2, [r3, #72]
	sub	r2, r2, #1
	str	r2, [r5, #2056]
	ldr	r2, [r3, #68]
	sub	r2, r2, #1
	str	r2, [r5, #2060]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	strb	r2, [r5, #1849]
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	strb	r3, [r5, #1848]
	ldr	r3, [r4, #3548]
	ldr	r0, [r4, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	subs	r9, r0, #0
	beq	.L582
	ldr	r2, [r9, #28]
	ldr	r3, [r9, #32]
	cmp	r2, #0
	beq	.L566
	cmp	r3, #0
	beq	.L566
	add	r3, r4, #7488
	add	r2, r4, #7232
	add	r1, r4, #7360
	add	r3, r3, #28
	add	r2, r2, #16
	add	r1, r1, #16
	ldr	r0, [r4, #252]
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r9, #28]
	add	r2, r4, #7360
	add	r1, r4, #7488
	add	r2, r2, #20
	add	r1, r1, #20
	ldr	r3, [r3, #4]
	str	r3, [r5, #3096]
	ldr	r0, [r4, #252]
	bl	FSP_GetPmvAddrTab
	ldr	r1, [r4, #3524]
	add	r2, r4, r7
	movw	r3, #12512
	str	r1, [r5, #3100]
	ldr	r1, [r9, #12]
	str	r1, [r5, #3416]
	ldr	r1, [r9, #32]
	ldr	r1, [r1, #8]
	str	r1, [r8, #400]
	ldr	r1, [r9, #32]
	ldr	r1, [r1, #60]
	str	r1, [r8, #404]
	ldr	ip, [r2, r3]
	cmp	ip, #0
	str	ip, [r8, #196]
	beq	.L568
	add	r3, r7, #12544
	add	r2, r4, #8320
	add	r3, r3, #36
	mov	r0, r6
	add	r3, r4, r3
.L569:
	add	r0, r0, #1
	ldr	r1, [r3, #4]!
	cmp	r0, ip
	str	r1, [r2, #4]!
	bne	.L569
.L568:
	add	r7, r4, #6144
	mov	r6, #0
	add	r7, r7, #20
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
	add	r2, r2, #20
	mov	r1, r4
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r4, #6464
	add	r2, r2, #20
	mov	r1, r4
	mov	r0, #5
	add	r7, r4, #6656
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r4, #6528
	add	r2, r2, #20
	mov	r1, r4
	mov	r0, #0
	add	r7, r7, #20
	bl	HEVC_WriteQmatrix_16x16
	add	r2, r4, #6592
	add	r2, r2, #20
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
	add	r2, r2, #20
	mov	r0, #0
	bl	HEVC_WriteQmatrix_32x32
	add	r2, r4, #6976
	add	r2, r2, #20
	mov	r1, r4
	mov	r0, #1
	add	r7, r4, #7040
	bl	HEVC_WriteQmatrix_32x32
	add	r7, r7, #20
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
	str	r3, [r5, #3060]
	ldr	r1, [r4, #2312]
	ldr	r3, [r4, #2316]
	ldr	r2, [r4, #2304]
	ldr	ip, [r4, #2308]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r5, #3064]
	ldr	r3, [r4, #3524]
	str	r3, [r5, #3092]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L581:
	ldr	r2, .L583+12
	mov	r0, #1
	ldr	r1, .L583+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L566:
	ldr	r1, .L583+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L582:
	ldr	r3, [r4, #3548]
	mov	r0, #1
	ldr	r1, .L583+24
	ldr	r2, [r3, #28]
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L584:
	.align	2
.L583:
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
	ldrb	r3, [r3, #97]	@ zero_extendqisi2
	cmp	r3, #0
	addeq	r3, r0, #4160
	addeq	r3, r3, #32
	beq	.L587
	ldrsb	r3, [r0, #11]
	cmp	r3, #0
	addne	r3, r0, #11136
	addne	r3, r3, #20
	beq	.L620
.L587:
	ldr	ip, [r3, #68]
	ldr	lr, [r3, #72]
	cmp	ip, #16
	bhi	.L621
	cmp	lr, #16
	bhi	.L591
	cmp	ip, #0
	beq	.L592
	ldr	r3, [r0, #2396]
	cmp	r3, #0
	beq	.L605
	ldr	r3, [r3, #16]
	cmp	r3, #0
	addne	r1, r0, #2384
	movne	r2, #0
	addne	r1, r1, #12
	bne	.L597
	b	.L622
.L598:
	ldr	r3, [r1, #4]!
	cmp	r3, #0
	beq	.L593
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L594
.L597:
	add	r2, r2, #1
	cmp	r2, ip
	bne	.L598
.L592:
	cmp	lr, #0
	beq	.L617
	ldr	r3, [r0, #2464]
	cmp	r3, #0
	beq	.L608
	ldr	r3, [r3, #16]
	cmp	r3, #0
	addne	r0, r0, #2464
	movne	r2, #0
	bne	.L603
	b	.L623
.L604:
	ldr	r3, [r0, #4]!
	cmp	r3, #0
	beq	.L599
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L600
.L603:
	add	r2, r2, #1
	cmp	r2, lr
	bne	.L604
.L617:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L605:
	mov	r2, r3
.L593:
	ldr	r1, .L624
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L622:
	mov	r2, r3
.L594:
	ldr	r1, .L624+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L608:
	mov	r2, r3
.L599:
	ldr	r1, .L624+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L623:
	mov	r2, r3
.L600:
	ldr	r1, .L624+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L620:
	mov	r0, r3
	ldr	r2, .L624+16
	ldr	r1, .L624+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L591:
	mov	r2, lr
	mov	r3, #17
	ldr	r1, .L624+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L621:
	mov	r2, ip
	mov	r3, #17
	ldr	r1, .L624+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L625:
	.align	2
.L624:
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
	ldr	r3, [r0, #3496]
	mov	r4, r0
	str	r3, [fp, #-116]
	bl	HEVC_CheckListX
	subs	r3, r0, #0
	str	r3, [fp, #-112]
	bne	.L665
	ldr	r0, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r0, r3
	bcs	.L698
	ldr	r6, [r4, #2388]
	mov	r5, #1360
	ldr	r7, [fp, #-112]
	mov	r2, r5
	ldr	r3, .L701
	add	r8, r4, #4096
	mla	r6, r5, r0, r6
	mov	r1, r7
	ldr	r3, [r3, #48]
	mov	r0, r6
	blx	r3
	ldr	r3, .L701
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
	ldrcc	r2, [r4, #2388]
	ldrcs	r3, [fp, #-112]
	mlacc	r3, r5, r3, r2
	str	r3, [r6, #1356]
	ldr	r1, [r8, #132]
	ldr	r2, [r4, #2356]
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
	bcs	.L631
	add	r0, r6, r1, lsl #2
.L632:
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r1, r1, #1
	add	r2, r2, r3
	ldr	r2, [r2, #56]
	str	r2, [r0, #8]
	ldr	r2, [r4, #2356]
	add	r2, r2, r3
	ldr	r2, [r2, #52]
	str	r2, [r0], #4
	ldr	r2, [r4, #2356]
	add	r3, r2, r3
	ldr	r3, [r3, #60]
	str	r3, [r0, #12]
	ldr	r2, [r4, #2356]
	ldr	r3, [r2, #8]
	cmp	r3, r1
	movhi	ip, #1
	movls	ip, #0
	cmp	r1, #1
	movhi	ip, #0
	cmp	ip, #0
	bne	.L632
.L631:
	cmp	r3, #1
	addls	r3, r6, r3, lsl #2
	addls	r1, r6, #8
	movls	r2, #0
	bhi	.L637
.L636:
	str	r2, [r3, #8]
	str	r2, [r3], #4
	cmp	r3, r1
	str	r2, [r3, #12]
	bne	.L636
.L637:
	ldrb	r3, [r8, #97]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L699
.L635:
	add	r5, r4, #8192
	ldr	r3, [r5, #3032]
	cmp	r3, #0
	beq	.L638
	add	ip, r4, #2384
	add	r10, r6, #112
	add	ip, ip, #8
	add	r9, r6, #368
	mov	r1, #0
	mov	lr, ip
.L639:
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
	add	r3, r3, #4
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r0, #16]
	ldr	r3, [r3, #24]
	str	r3, [r9, #4]!
	ldr	r3, [r5, #3032]
	cmp	r3, r1
	bhi	.L639
	ldr	r2, [r5, #3036]
	cmp	r2, #0
	beq	.L640
.L664:
	add	ip, r4, #2448
	add	r10, r6, #176
	add	ip, ip, #12
	add	r9, r6, #432
	mov	r1, #0
	mov	lr, ip
.L641:
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
	add	r3, r3, #4
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r0, #16]
	ldr	r3, [r3, #24]
	str	r3, [r9, #4]!
	ldr	r2, [r5, #3036]
	cmp	r2, r1
	bhi	.L641
	ldr	r3, [r5, #3032]
.L640:
	cmp	r3, #0
	beq	.L642
	ldr	r0, [fp, #-116]
	mov	lr, #50
	ldr	r1, [r6, #372]
	ldr	r9, [r4, #3500]
	mul	lr, lr, r0
	add	r1, lr, r1
	add	r1, r1, #3152
	add	r1, r1, #10
	ldr	r1, [r4, r1, asl #2]
	cmp	r9, r1
	blt	.L671
	add	ip, r6, #372
	mov	r0, #0
	b	.L644
.L645:
	ldr	r1, [ip, #4]!
	add	r1, lr, r1
	add	r1, r1, #3152
	add	r1, r1, #10
	ldr	r1, [r4, r1, asl #2]
	cmp	r1, r9
	bgt	.L671
.L644:
	add	r0, r0, #1
	cmp	r0, r3
	bne	.L645
.L642:
	ldr	r1, [r5, #2984]
	cmp	r1, #0
	bne	.L696
	cmp	r2, #0
	beq	.L696
	ldr	r0, [fp, #-116]
	mov	ip, #50
	ldr	r3, [r6, #436]
	ldr	lr, [r4, #3500]
	mul	ip, ip, r0
	add	r3, ip, r3
	add	r3, r3, #3152
	add	r3, r3, #10
	ldr	r3, [r4, r3, asl #2]
	cmp	lr, r3
	blt	.L643
	add	r0, r6, #436
	b	.L646
.L647:
	ldr	r3, [r0, #4]!
	add	r3, ip, r3
	add	r3, r3, #3152
	add	r3, r3, #10
	ldr	r3, [r4, r3, asl #2]
	cmp	r3, lr
	bgt	.L671
.L646:
	add	r1, r1, #1
	cmp	r1, r2
	bne	.L647
.L696:
	mov	r1, #1
.L643:
	strb	r1, [r6, #24]
	ldrb	r3, [r8, #97]	@ zero_extendqisi2
	strb	r3, [r6, #25]
	ldr	r3, [r5, #2980]
	str	r3, [r6, #28]
	ldrb	r2, [r5, #2971]	@ zero_extendqisi2
	strb	r2, [r6, #32]
	ldr	r2, [r5, #3004]
	str	r2, [r6, #36]
	ldr	r9, [r4, #3548]
	ldr	r1, [r4, #204]
	ldr	r0, [r9, #316]
	sub	r2, r1, #1
	mla	r0, r0, r2, r3
	bl	__aeabi_uidiv
	str	r0, [r9, #68]
	ldr	r3, [r5, #2984]
	cmp	r3, #0
	bne	.L648
	ldrb	r3, [r5, #2972]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L649
	ldr	r3, [r5, #3008]
	add	r3, r6, r3, lsl #2
	ldr	r9, [r3, #436]
.L650:
	str	r9, [r6, #40]
	ldr	r3, [r5, #3008]
	str	r3, [r6, #48]
	ldrb	r3, [r5, #2972]	@ zero_extendqisi2
	strb	r3, [r6, #52]
	ldr	r3, [r5, #3012]
	str	r3, [r6, #44]
	ldr	r3, [r5, #3040]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #60]
	ldr	r3, [r5, #3044]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #56]
	ldrb	r3, [r5, #2968]	@ zero_extendqisi2
	strb	r3, [r6, #64]
	ldrb	r3, [r5, #2970]	@ zero_extendqisi2
	strb	r3, [r6, #65]
	ldr	r3, [r5, #3032]
	str	r3, [r6, #68]
	ldr	r3, [r5, #3036]
	str	r3, [r6, #72]
	ldr	r3, [r5, #2984]
	str	r3, [r6, #76]
	ldr	r3, [r8, #136]
	str	r3, [r6, #80]
	ldr	r3, [r4, #2368]
	ldr	r0, [r8, #136]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidivmod
	str	r1, [r6, #84]
	ldr	r3, [r4, #2368]
	ldr	r0, [r8, #136]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidiv
	str	r0, [r6, #88]
	mov	r0, r4
	ldr	r1, [r8, #136]
	bl	HEVC_CtbRsAddrToTsAddr
	str	r0, [r6, #92]
	ldr	r3, [r5, #3016]
	str	r3, [r6, #96]
	ldr	r3, [r5, #3020]
	str	r3, [r6, #100]
	ldr	r3, [r5, #3028]
	str	r3, [r6, #104]
	ldr	r3, [r5, #3024]
	str	r3, [r6, #108]
	ldrb	r3, [r5, #2967]	@ zero_extendqisi2
	strb	r3, [r6, #112]
	ldrb	r3, [r5, #2966]	@ zero_extendqisi2
	strb	r3, [r6, #113]
	ldrb	r3, [r5, #2973]	@ zero_extendqisi2
	strb	r3, [r6, #114]
	ldrb	r3, [r5, #2974]	@ zero_extendqisi2
	strb	r3, [r6, #115]
	ldr	r3, [r4, #2372]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L655
	ldr	r2, [r5, #2984]
	cmp	r2, #1
	beq	.L656
.L655:
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L700
.L658:
	ldrb	r3, [r5, #2968]	@ zero_extendqisi2
	ldr	r0, [fp, #-120]
	cmp	r3, #0
	subne	r3, fp, #44
	addne	r9, r3, r9, lsl #2
	ldreq	r3, [r8, #3284]
	ldrne	r3, [r9, #-64]
	str	r3, [r6, #564]
	mov	r3, #0
	ldr	r1, [r4, #2356]
	ldr	r2, [r4, #2376]
	str	r1, [r2, r0, asl #2]
	str	r3, [r4, #2356]
	ldrb	r2, [r8, #2033]	@ zero_extendqisi2
	cmp	r2, r3
	beq	.L679
	ldr	r1, [r4, #236]
	cmp	r1, #1
	ldreq	r2, [r6, #92]
	streq	r2, [r5, #1292]
	beq	.L663
	add	r2, r4, r1, lsl #3
	ldr	ip, [r6, #92]
	add	r2, r2, #9408
	add	r0, r1, #1184
	sub	ip, ip, #1
	sub	r3, r1, #1
	str	ip, [r2, #64]
	add	r0, r4, r0, lsl #3
	ldr	r2, [r6, #92]
	str	r2, [r0, #4]
.L663:
	ldr	r1, [r8, #1832]
	add	r3, r4, r3, lsl #3
	ldr	r2, [r8, #1828]
	add	r3, r3, #9472
	mla	r2, r1, r2, r2
	add	r2, r2, r1
	str	r2, [r3, #16]
	ldr	r1, [r6, #92]
	sub	r1, r1, #1
	cmp	r1, #36864
	bcs	.L679
	mov	r0, r4
	bl	HEVC_CtbTsAddrToRsAddr
	str	r0, [r6, #568]
.L679:
	ldr	r0, [fp, #-112]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L671:
	mov	r1, #0
	b	.L643
.L648:
	cmp	r3, #1
	movne	r9, #0
	bne	.L650
.L649:
	ldr	r3, [r5, #3008]
	add	r3, r6, r3, lsl #2
	ldr	r9, [r3, #372]
	b	.L650
.L699:
	ldr	r3, .L701
	add	r1, r4, #4160
	add	r0, r4, #11136
	add	r1, r1, #32
	add	r0, r0, #20
	movw	r2, #1356
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #1
	strb	r3, [r4, #11]
	b	.L635
.L700:
	ldr	r3, [r5, #2984]
	cmp	r3, #0
	bne	.L658
.L656:
	ldr	ip, [r5, #3120]
	add	r1, r4, #11392
	ldr	r3, .L701
	add	r1, r1, #56
	ldr	r10, .L701
	mov	r2, #64
	str	ip, [r6, #580]
	add	r0, r6, #588
	ldr	ip, [r5, #3252]
	ldr	r3, [r3, #52]
	str	ip, [r6, #584]
	blx	r3
	add	r1, r4, #11264
	add	r1, r1, #52
	ldr	r3, [r10, #52]
	mov	r2, #64
	add	r0, r6, #716
	blx	r3
	add	r1, r4, #11456
	add	r1, r1, #56
	ldr	r3, [r10, #52]
	mov	r2, #128
	add	r0, r6, #844
	blx	r3
	add	r1, r4, #11584
	add	r0, r6, #1088
	ldr	r3, [r10, #52]
	add	r1, r1, #56
	add	r0, r0, #12
	mov	r2, #128
	blx	r3
	ldr	r3, [r5, #2984]
	cmp	r3, #0
	bne	.L658
	add	r1, r4, #11712
	ldr	r3, [r10, #52]
	add	r1, r1, #56
	mov	r2, #64
	add	r0, r6, #652
	blx	r3
	add	r1, r4, #11328
	ldr	r3, [r10, #52]
	add	r1, r1, #52
	mov	r2, #64
	add	r0, r6, #780
	blx	r3
	add	r1, r4, #11776
	ldr	r3, [r10, #52]
	add	r1, r1, #56
	mov	r2, #128
	add	r0, r6, #972
	blx	r3
	add	r1, r4, #11904
	add	r0, r6, #1216
	ldr	r3, [r10, #52]
	add	r1, r1, #56
	mov	r2, #128
	add	r0, r0, #12
	blx	r3
	b	.L658
.L638:
	ldr	r3, [r5, #3036]
	cmp	r3, #0
	bne	.L664
	b	.L696
.L665:
	mvn	r3, #0
	str	r3, [fp, #-112]
	b	.L679
.L698:
	mov	r2, r0
	ldr	r1, .L701+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r3, #0
	str	r3, [fp, #-112]
	b	.L679
.L702:
	.align	2
.L701:
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
	ldr	r2, [r0, #3516]
	add	r1, r0, #4096
	mov	r3, r0
	add	ip, r0, #8192
	clz	r2, r2
	mov	r0, #0
	mov	r2, r2, lsr #5
	str	r2, [r1, #3148]
	ldr	r2, [r3, #3520]
	str	r2, [r1, #3140]
	ldr	r3, [r3, #204]
	str	r3, [ip, #200]
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
	ldr	r3, [r5, #132]
	cmp	r3, #0
	blt	.L708
	cmp	r3, r2
	bge	.L708
	ldr	r2, [r0, #2348]
	mov	r1, #1888
	mla	r3, r1, r3, r2
	ldr	r2, [r0, #160]
	ldr	r3, [r3, #32]
	cmp	r3, #0
	blt	.L712
	cmp	r3, r2
	bge	.L712
	ldr	r2, [r0, #2344]
	movw	r0, #12660
	ldr	ip, [r5, #1028]
	mov	r1, #1
	ldr	r10, [r5, #1032]
	mla	r2, r0, r3, r2
	ldr	r6, [r5, #1036]
	add	lr, r10, ip
	cmp	lr, r6
	mov	r3, lr
	ldr	r8, [r2, #116]
	mov	r8, r1, asl r8
	bcs	.L723
	cmp	lr, #15
	bgt	.L715
	add	r2, lr, #1296
	ldr	r7, [r4, #3500]
	add	r2, r2, #9
	sub	r8, r8, #1
	and	r9, r8, r7
	str	ip, [fp, #-48]
	add	r2, r4, r2, lsl #2
	b	.L717
.L734:
	cmp	r6, r3
	bls	.L733
	cmp	r3, #16
	beq	.L715
.L717:
	ldr	r1, [r2, #4]!
	mov	r0, r7
	add	r3, r3, #1
	ldr	ip, [r2, #-944]
	cmp	ip, #0
	andeq	r1, r1, r8
	moveq	r0, r9
	cmp	r0, r1
	bne	.L734
	ldr	ip, [fp, #-48]
	mov	r6, #1
.L714:
	cmp	lr, #0
	beq	.L710
	ldr	r0, [r5, #108]
	ldr	r3, [r5, #1060]
	ldr	r2, [r4, #3500]
	add	r3, r0, r3
	cmp	r2, r3
	beq	.L727
	add	r4, r4, #5120
	mov	r1, #0
	add	r4, r4, #36
	b	.L720
.L721:
	ldr	r3, [r4, #4]!
	add	r3, r0, r3
	cmp	r3, r2
	beq	.L727
.L720:
	add	r1, r1, #1
	cmp	r1, lr
	beq	.L710
	cmp	r1, #17
	bne	.L721
	mov	r3, r1
	str	r1, [sp]
	str	r10, [sp, #8]
	movw	r2, #9007
	str	ip, [sp, #4]
	mov	r0, #0
	ldr	r1, .L735
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L712:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8958
	ldr	r1, .L735+4
	mov	r6, r0
	bl	dprint_vfmw
.L710:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L708:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8946
	ldr	r1, .L735+8
	mov	r6, r0
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L715:
	str	r6, [sp, #4]
	mov	r1, #16
	mov	r0, #0
	str	r1, [sp]
	movw	r2, #8978
	ldr	r1, .L735+12
	mov	r6, r0
	bl	dprint_vfmw
	ldr	ip, [r5, #1028]
	ldr	r10, [r5, #1032]
	add	lr, r10, ip
	b	.L714
.L733:
	ldr	ip, [fp, #-48]
	mov	r6, #0
	b	.L714
.L727:
	mov	r6, #1
	b	.L710
.L723:
	mov	r6, #0
	b	.L714
.L736:
	.align	2
.L735:
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
	ldr	r2, [r0, #2364]
	ldr	r3, [r1, #4]
	ldr	r2, [r2, #4]
	cmp	r2, r3
	beq	.L740
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L740:
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
	ldr	lr, .L742
	mov	r2, #132
	ldr	r0, [r0, #2340]
	mov	r3, ip, asl #7
	add	r3, r3, ip, lsl #2
	ldr	r5, [lr, #52]
	sub	r3, r3, #132
	add	r0, r0, r3
	blx	r5
	ldr	r3, [r4, #156]
	ldr	r1, [r4, #2340]
	mov	r2, r3, asl #7
	add	r3, r2, r3, lsl #2
	sub	r3, r3, #132
	add	r3, r1, r3
	str	r3, [r4, #2364]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L743:
	.align	2
.L742:
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
	ldr	r2, [r0, #2368]
	ldr	r3, [r1, #56]
	ldr	r2, [r2, #56]
	cmp	r2, r3
	beq	.L747
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L747:
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
	ldr	ip, .L749
	mov	r4, r0
	ldr	r0, [r0, #2344]
	mov	r2, r5
	mul	r3, r5, r3
	ldr	r6, [ip, #52]
	sub	r3, r3, #12608
	sub	r3, r3, #52
	add	r0, r0, r3
	blx	r6
	ldr	r3, [r4, #160]
	ldr	r1, [r4, #2344]
	mul	r3, r5, r3
	sub	r3, r3, #12608
	sub	r3, r3, #52
	add	r3, r1, r3
	str	r3, [r4, #2368]
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
.L750:
	.align	2
.L749:
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
	ldr	r2, [r0, #2372]
	ldr	r3, [r1, #28]
	ldr	r2, [r2, #28]
	cmp	r2, r3
	beq	.L754
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L754:
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
	beq	.L756
	ldrb	r3, [r2, #15]	@ zero_extendqisi2
	cmp	r3, r4
	bne	.L774
	ldr	lr, [r2, #68]
	ldr	r3, [r1, #188]
	cmp	lr, #1
	add	r0, r2, lr, lsl #1
	strh	r3, [r0, #170]	@ movhi
	ble	.L768
	add	lr, lr, #42
	add	r2, r2, #86
	add	ip, r5, #170
	add	lr, r5, lr, lsl #1
.L767:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #170]
	rsb	r3, r1, r3
	strh	r3, [r0, #170]	@ movhi
	bne	.L767
.L768:
	ldr	lr, [r5, #72]
	ldr	r3, [r7, #192]
	cmp	lr, #1
	add	r0, r5, lr, lsl #1
	strh	r3, [r0, #210]	@ movhi
	ble	.L763
	add	lr, lr, #62
	add	r2, r5, #126
	add	ip, r5, #210
	add	lr, r5, lr, lsl #1
.L769:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #210]
	rsb	r3, r1, r3
	strh	r3, [r0, #210]	@ movhi
	bne	.L769
	b	.L763
.L756:
	ldr	r3, [r1, #188]
	strh	r3, [r2, #172]	@ movhi
	ldr	r3, [r1, #192]
	strh	r3, [r2, #212]	@ movhi
.L763:
	ldr	r3, [r6, #164]
	mov	r4, #1888
	ldr	ip, .L775
	mov	r1, r5
	ldr	r0, [r6, #2348]
	mov	r2, r4
	mul	r3, r4, r3
	ldr	r5, [ip, #52]
	sub	r3, r3, #1888
	add	r0, r0, r3
	blx	r5
	ldr	r2, [r6, #164]
	ldr	r3, [r6, #2348]
	mul	r4, r4, r2
	sub	r4, r4, #1888
	add	r4, r3, r4
	str	r4, [r6, #2372]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L774:
	ldr	r9, [r2, #68]
	cmp	r9, r4
	addgt	r3, r2, #170
	ble	.L762
.L761:
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
	bne	.L761
.L762:
	ldr	r9, [r5, #72]
	cmp	r9, #0
	addgt	r3, r5, #210
	movgt	r4, #0
	ble	.L763
.L764:
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
	bne	.L764
	b	.L763
.L776:
	.align	2
.L775:
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
	mov	r4, r0
	mov	r3, #1
	strb	r3, [r0, #3489]
	ldr	r0, [r5, #124]
	mvn	r2, #0
	ldr	r3, [r4, #2368]
	mov	r1, #0
	ldr	lr, [r4, #252]
	str	r0, [r4, #3492]
	ldr	ip, [r5, #108]
	str	r2, [r4, #3520]
	ldr	r2, .L786
	str	ip, [r4, #3500]
	ldr	r0, [r3, #64]
	ldr	r2, [r2, lr, asl #2]
	str	r0, [r4, #3508]
	ldr	r3, [r3, #68]
	str	r1, [r4, #3516]
	str	r3, [r4, #3512]
	ldrsb	r3, [r2, #44]
	cmp	r3, #1
	beq	.L785
.L778:
	ldr	r3, [r4, #2384]
	add	ip, r4, #4096
	movw	lr, #4144
	add	r2, r4, #4160
	mov	r8, #0
	ldrd	r0, [r3, #64]
	strd	r0, [ip, #40]
	add	r0, r4, #3552
	ldrd	r6, [r3, #80]
	strd	r6, [r4, lr]
	ldrd	r6, [r3, #96]
	strd	r6, [r2, #-8]
	mvn	r6, #0
	ldr	r2, [r3, #112]
	mvn	r7, #0
	str	r2, [r4, #3552]
	ldr	r2, [r3, #116]
	str	r2, [r4, #3556]
	ldr	r2, [r3, #120]
	str	r2, [r4, #3560]
	ldr	r2, [r3, #136]
	str	r2, [r4, #3564]
	ldrb	r2, [r3, #56]	@ zero_extendqisi2
	strb	r2, [r5, #88]
	strd	r6, [r3, #64]
	ldr	r3, [r4, #2368]
	ldrb	r2, [r4, #3616]	@ zero_extendqisi2
	ldr	r1, [r3, #64]
	str	r1, [r4, #3620]
	ldr	r1, [r3, #68]
	str	r8, [r4, #3604]
	str	r1, [r4, #3624]
	ldr	r1, [r3, #60]
	ldr	ip, [r3, #2084]
	subs	r1, r1, #1
	bfi	r2, ip, #5, #3
	movne	r1, #1
	bfi	r2, r1, #2, #3
	strb	r2, [r4, #3616]
	ldr	r1, [r3, #2068]
	and	r1, r1, #7
	bl	SetAspectRatio
	ldr	r2, [r5, #108]
	ldr	r3, [r4, #3548]
	str	r2, [r3, #8]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3616]
	str	r2, [r3, #144]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3604]
	str	r2, [r3, #132]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3656]
	str	r2, [r3, #184]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3652]
	str	r2, [r3, #180]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3620]
	str	r2, [r3, #148]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3624]
	str	r2, [r3, #152]
	ldr	r3, [r4, #3548]
	ldr	r0, [r4, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L781
	ldr	r3, [r4, #3604]
	mov	r1, r8
	ldr	r2, [r0, #4]
	subs	r3, r3, r8
	ldr	r0, [r4, #252]
	movne	r3, #1
	bl	FSP_SetStoreType
.L781:
	ldr	r3, [r4, #2368]
	mov	r6, #0
	ldr	ip, [r4, #3548]
	ldr	r2, [r3, #72]
	str	r2, [r4, #3772]
	ldr	r5, [r3, #76]
	str	r5, [r4, #3776]
	ldr	r1, [r3, #80]
	str	r1, [r4, #3780]
	ldr	lr, [r3, #84]
	str	lr, [r4, #3784]
	ldr	r0, [r3, #64]
	rsb	r2, r2, r0
	rsb	r2, r5, r2
	str	r2, [r4, #3628]
	ldr	r0, [r3, #68]
	rsb	r1, r1, r0
	rsb	r1, lr, r1
	str	r1, [r4, #3632]
	ldr	r1, [r3, #60]
	str	r1, [r4, #3716]
	ldr	r1, [r3, #88]
	str	r1, [r4, #3720]
	ldr	r3, [r3, #96]
	str	r3, [r4, #3724]
	ldr	r3, [ip, #164]
	str	r3, [r4, #3636]
	ldr	r3, [ip, #168]
	str	r3, [r4, #3640]
	str	r2, [ip, #156]
	ldr	r2, [r4, #3632]
	ldr	r3, [r4, #3548]
	str	r2, [r3, #160]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3636]
	str	r2, [r3, #164]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3640]
	str	r2, [r3, #168]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3720]
	str	r2, [r3, #248]
	ldr	r3, [r4, #3548]
	ldr	r2, [r4, #3724]
	str	r2, [r3, #252]
	str	r6, [r4, #3504]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L785:
	ldr	r3, [r2, #160]
	cmp	r3, #1
	bne	.L778
	ldr	r3, [r2, #164]
	cmp	r3, #2
	bne	.L778
	add	r3, r4, #8192
	ldrb	r3, [r3, #2904]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L778
	add	r3, r4, #11136
	ldrd	r0, [r3, #-8]
	mov	lr, r3
	ldrd	r8, [r3, #8]
	cmp	r1, r9
	cmpeq	r0, r8
	bls	.L779
	subs	r6, r0, r8
	sbc	r7, r1, r9
	cmp	r7, #0
	cmpeq	r6, #16
	bls	.L779
.L780:
	ldr	r1, [r4, #260]
	rsb	ip, r1, ip
	adds	r2, r8, ip
	adc	r3, r9, ip, asr #31
	strd	r2, [lr, #-8]
	b	.L778
.L779:
	cmp	r1, r9
	cmpeq	r0, r8
	bcs	.L778
	subs	r0, r8, r0
	sbc	r1, r9, r1
	cmp	r1, #0
	cmpeq	r0, #16
	bls	.L778
	b	.L780
.L787:
	.align	2
.L786:
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
	ldr	r3, [r3, #116]
	cmp	r3, #1
	beq	.L805
	cmp	r3, #2
	beq	.L806
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [fp, #-48]
	beq	.L790
	ldr	r2, .L815
	mov	r0, #1
	ldr	r1, .L815+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L805:
	str	r3, [fp, #-48]
.L790:
	add	r9, r10, #4224
	add	r7, r10, #2384
	add	r9, r9, #32
	add	r7, r7, #12
	mov	r8, #0
.L803:
	ldr	r2, [r9, #4]!
	cmp	r2, #0
	beq	.L793
	ldr	r1, [r7]
	cmp	r1, #0
	bne	.L807
	mov	r0, r7
	mov	r3, r1
	b	.L795
.L797:
	ldr	r5, [r0, #4]!
	cmp	r5, #0
	bne	.L813
.L795:
	add	r3, r3, #1
	cmp	r3, r2
	bne	.L797
	mov	r3, #255
	str	r3, [fp, #-52]
.L796:
	ldr	r3, [r10, #2384]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L798
	ldr	r5, [r10, #3548]
	add	r5, r5, #56
.L794:
	mov	r3, r1
	mov	r6, r7
	mov	r4, #0
	b	.L804
.L800:
	ldr	r3, [r6, #4]!
.L804:
	cmp	r3, #0
	beq	.L814
.L799:
	add	r4, r4, #1
	cmp	r2, r4
	bhi	.L800
.L801:
	ldr	r3, [fp, #-48]
	add	r8, r8, #1
	add	r7, r7, #68
	cmp	r8, r3
	bcc	.L803
.L806:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L793:
	ldr	r3, [r10, #2384]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	moveq	r3, #1
	streq	r3, [r9]
	ldreq	r3, [r10, #3548]
	addeq	r3, r3, #56
	streq	r3, [r7]
	b	.L801
.L814:
	ldrsb	r2, [fp, #-52]
	mov	r3, r8
	str	r4, [sp]
	mov	r0, #1
	ldr	r1, .L815+8
	str	r2, [sp, #4]
	ldr	r2, .L815
	bl	dprint_vfmw
	str	r5, [r6]
	ldr	r2, [r9]
	b	.L799
.L813:
	uxtb	r3, r3
	str	r3, [fp, #-52]
	cmp	r3, #255
	bne	.L794
	b	.L796
.L807:
	mov	r3, #0
	mov	r5, r1
	str	r3, [fp, #-52]
	b	.L794
.L798:
	mov	r3, r8
	ldr	r2, .L815
	ldr	r1, .L815+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L816:
	.align	2
.L815:
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
	beq	.L853
	ldr	r3, .L885
	mov	r2, #136
	mov	r1, #0
	sub	r0, fp, #180
	ldr	r3, [r3, #48]
	blx	r3
	ldr	lr, [r7, #2580]
	cmp	lr, #0
	beq	.L854
	add	r1, r7, #2640
	mov	r0, #0
	add	r1, r1, #12
	mov	r3, r0
	b	.L821
.L820:
	cmp	r3, lr
	beq	.L819
.L821:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #1]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L820
	ldr	ip, [r2, #60]
	cmp	ip, #0
	bne	.L820
	ldr	ip, [r2, #64]
	cmp	ip, #1
	subeq	ip, fp, #44
	addeq	r2, r2, #56
	addeq	ip, ip, r0, lsl #2
	addeq	r0, r0, #1
	streq	r2, [ip, #-136]
	cmp	r3, lr
	bne	.L821
.L819:
	ldr	r4, [r7, #2584]
	cmp	r4, #0
	beq	.L855
	add	r1, r7, #2720
	mov	ip, r0
	mov	r3, #0
	b	.L824
.L823:
	cmp	r3, r4
	beq	.L881
.L824:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L823
	ldr	lr, [r2, #60]
	cmp	lr, #0
	bne	.L823
	ldr	lr, [r2, #64]
	cmp	lr, #1
	subeq	lr, fp, #44
	addeq	r2, r2, #56
	addeq	lr, lr, ip, lsl #2
	addeq	ip, ip, #1
	streq	r2, [lr, #-136]
	cmp	r3, r4
	bne	.L824
.L881:
	rsb	r4, r0, ip
.L822:
	ldr	r5, [r7, #2576]
	cmp	r5, #0
	beq	.L856
	add	lr, r7, #2784
	mov	r10, ip
	add	lr, lr, #4
	mov	r2, #0
	b	.L827
.L826:
	cmp	r2, r5
	beq	.L882
.L827:
	ldr	r3, [lr, #4]!
	add	r2, r2, #1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L826
	ldr	r1, [r3, #60]
	cmp	r1, #1
	bne	.L826
	ldr	r1, [r3, #64]
	sub	r6, fp, #44
	add	r6, r6, r10, lsl #2
	add	r3, r3, #56
	cmp	r1, #0
	addeq	r10, r10, #1
	streq	r3, [r6, #-136]
	cmp	r2, r5
	bne	.L827
.L882:
	rsb	r5, r0, r10
	rsb	r5, r4, r5
.L825:
	cmp	r10, #0
	beq	.L883
	add	r3, r7, #4096
	str	r3, [fp, #-184]
	ldr	r3, [r3, #116]
	cmp	r3, #0
	str	r3, [fp, #-188]
	beq	.L884
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #172]
	ldr	r5, [r3, #176]
	cmp	r4, #0
	str	r4, [r3, #164]
	str	r5, [r3, #168]
	beq	.L846
.L852:
	ldr	r3, [fp, #-184]
	add	r8, r7, #2384
	add	r8, r8, #8
	mov	r6, #0
	ldrb	r9, [r3, #1192]	@ zero_extendqisi2
.L839:
	cmp	r9, #0
	mov	r1, r10
	mov	r0, r6
	ldrne	r1, [r8, #2900]
	bne	.L838
	bl	__aeabi_uidivmod
.L838:
	sub	r3, fp, #44
	add	r6, r6, #1
	add	r1, r3, r1, lsl #2
	cmp	r4, r6
	ldr	r3, [r1, #-136]
	str	r3, [r8, #4]!
	bhi	.L839
	ldr	r3, [fp, #-188]
	cmp	r3, #0
	bne	.L880
.L840:
	cmp	r5, #0
	beq	.L842
	ldr	r3, [fp, #-184]
	add	r6, r7, #2448
	add	r6, r6, #12
	mov	r4, #0
	ldrb	r8, [r3, #1193]	@ zero_extendqisi2
.L845:
	cmp	r8, #0
	mov	r1, r10
	mov	r0, r4
	ldrne	r1, [r6, #2960]
	bne	.L844
	bl	__aeabi_uidivmod
.L844:
	sub	r3, fp, #44
	add	r4, r4, #1
	add	r1, r3, r1, lsl #2
	cmp	r4, r5
	ldr	r3, [r1, #-68]
	str	r3, [r6, #4]!
	bne	.L845
.L880:
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #164]
	ldr	r5, [r3, #168]
.L841:
	cmp	r4, #16
	bhi	.L850
.L846:
	add	r4, r4, #596
	add	r2, r7, #2448
	add	r4, r4, #2
	add	r2, r2, #12
	add	r4, r7, r4, lsl #2
.L849:
	ldr	r3, [r7, #2396]
	str	r3, [r4, #4]!
	cmp	r4, r2
	bne	.L849
.L850:
	cmp	r5, #16
	bhi	.L848
	add	r5, r5, #612
	add	r2, r7, #2528
	add	r5, r5, #3
	add	r5, r7, r5, lsl #2
.L851:
	ldr	r3, [r7, #2464]
	str	r3, [r5, #4]!
	cmp	r5, r2
	bne	.L851
.L848:
	mov	r0, #0
.L879:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L884:
	cmp	r4, #0
	beq	.L831
	sub	r3, fp, #180
	ldr	r2, [fp, #-188]
	add	lr, r3, r0, lsl #2
	sub	r1, fp, #116
.L832:
	add	r2, r2, #1
	ldr	r3, [lr], #4
	cmp	r2, r4
	str	r3, [r1, #4]!
	bne	.L832
.L831:
	cmp	r0, #0
	beq	.L833
	add	r1, r4, #16
	sub	lr, fp, #180
	mov	r2, #0
	add	r1, lr, r1, lsl #2
.L834:
	add	r2, r2, #1
	ldr	r3, [lr], #4
	cmp	r2, r0
	str	r3, [r1, #4]!
	bne	.L834
	add	r4, r4, r2
.L833:
	cmp	r5, #0
	beq	.L835
	add	r4, r4, #16
	sub	r3, fp, #180
	add	ip, r3, ip, lsl #2
	mov	r2, #0
	add	r4, r3, r4, lsl #2
.L836:
	add	r2, r2, #1
	ldr	r3, [ip], #4
	cmp	r2, r5
	str	r3, [r4, #4]!
	bne	.L836
.L835:
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #172]
	ldr	r5, [r3, #176]
	cmp	r4, #0
	str	r4, [r3, #164]
	str	r5, [r3, #168]
	bne	.L852
	b	.L840
.L883:
	ldr	r3, .L885
	add	r4, r7, #4096
	add	r0, r7, #2384
	mov	r2, #136
	add	r0, r0, #12
	str	r10, [r4, #164]
	ldr	r5, [r3, #48]
	mov	r1, r10
	str	r10, [r4, #168]
	blx	r5
	ldr	r2, [r7, #2384]
	ldr	r2, [r2, #24]
	cmp	r2, #2
	bne	.L848
	mov	r2, #1
	str	r2, [r4, #164]
	ldr	r2, [r7, #3548]
	mov	r0, r10
	add	r3, r2, #56
	str	r3, [r7, #2396]
	b	.L879
.L854:
	mov	r0, lr
	b	.L819
.L855:
	mov	ip, r0
	b	.L822
.L856:
	mov	r10, ip
	b	.L825
.L842:
	ldr	r3, .L885
	add	r1, r7, #2384
	add	r1, r1, #12
	mov	r2, #68
	add	r0, r7, #2464
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #164]
	str	r4, [r3, #168]
	mov	r5, r4
	b	.L841
.L853:
	mvn	r0, #0
	b	.L879
.L886:
	.align	2
.L885:
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
	ldr	r2, [r3, #116]
	cmp	r2, #2
	beq	.L892
	bl	HEVC_InitListX
	cmp	r0, #0
	bne	.L893
	mov	r0, r4
	bl	HEVC_RepairList
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L894
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L892:
	mov	r0, #0
	str	r0, [r3, #164]
	str	r0, [r3, #168]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L893:
	ldr	r1, .L894+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L895:
	.align	2
.L894:
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
	ldr	r2, [r0, #2368]
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
	bhi	.L903
	ldr	r3, .L905
	mov	r2, #20
	sub	r0, fp, #48
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #2384]
	str	r6, [fp, #-44]
	str	r5, [fp, #-40]
	ldr	r3, [r3, #28]
	str	r6, [fp, #-36]
	cmp	r3, #24
	str	r5, [fp, #-32]
	beq	.L899
	ldrb	r3, [r4, #2564]	@ zero_extendqisi2
	strb	r3, [fp, #-47]
.L901:
	sub	r1, fp, #48
	ldr	r0, [r4, #252]
	strb	r3, [fp, #-45]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L904
	ldr	r1, [r4, #2384]
	sub	r3, fp, #52
	ldr	r0, [r4, #252]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
.L902:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L899:
	mov	r3, #1
	strb	r3, [fp, #-47]
	b	.L901
.L903:
	str	r5, [sp]
	mov	r3, r6
	ldr	r2, .L905+4
	mov	r0, #0
	ldr	r1, .L905+8
	bl	dprint_vfmw
	mvn	r0, #19
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L904:
	ldr	r2, .L905+4
	mov	r0, #1
	ldr	r1, .L905+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L902
.L906:
	.align	2
.L905:
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
	ldr	ip, [r3, #2588]
	ldr	r2, [ip, #32]
	cmp	r2, #0
	bne	.L910
	ldr	r3, [ip, #24]
	cmp	r3, #15
	bhi	.L907
	add	r3, r0, r3, lsl #2
	add	r1, r0, #12288
	add	r3, r3, #12288
	mov	lr, #16
	str	r2, [r3, #232]
	str	r2, [r3, #296]
	str	r2, [r3, #360]
	ldr	r3, [ip, #20]
	add	r3, r3, #536
	str	r2, [r0, r3, asl #2]
	str	lr, [ip, #24]
	ldr	r3, [r1, #228]
	sub	r3, r3, #1
	str	r3, [r1, #228]
.L907:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L910:
	str	r2, [sp]
	mov	r3, r1
	ldr	r2, .L911
	mov	r0, #1
	ldr	r1, .L911+4
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L912:
	.align	2
.L911:
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
	ldr	r2, [r0, #2568]
	mov	r6, r0
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #2576
	mov	r4, #0
	add	r5, r5, #8
	b	.L916
.L915:
	add	r4, r4, #1
	cmp	r4, r2
	bcs	.L919
.L916:
	ldr	r3, [r5, #4]!
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L915
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_RemoveApcStore
	ldr	r2, [r6, #2568]
	add	r4, r4, #1
	cmp	r4, r2
	bcc	.L916
.L919:
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
	ldr	r2, [r0, #2348]
	mov	lr, #1888
	ldr	r1, [r4, #132]
	movw	ip, #12660
	ldr	r3, [r0, #2344]
	mov	r9, r0
	mov	r0, #1
	mla	r2, lr, r1, r2
	ldr	r1, [r9, #2568]
	cmp	r1, #0
	ldr	r2, [r2, #32]
	mla	r3, ip, r2, r3
	ldr	r3, [r3, #116]
	mov	r3, r0, asl r3
	str	r3, [fp, #-48]
	beq	.L920
	add	r7, r9, #2576
	add	r3, r9, #5120
	add	r3, r3, #36
	add	r7, r7, #8
	str	r3, [fp, #-52]
	mov	r8, #0
	b	.L937
.L923:
	add	r8, r8, #1
	cmp	r8, r1
	bcs	.L920
.L937:
	ldr	r0, [r7, #4]!
	ldr	r3, [r4, #128]
	ldr	r2, [r0, #32]
	cmp	r2, r3
	bne	.L923
	ldr	r1, [r4, #1028]
	ldr	r3, [r4, #1032]
	ldr	r2, [r4, #1036]
	add	r3, r3, r1
	cmp	r3, r2
	mov	r6, r3
	ldrcs	ip, [r0, #8]
	movcs	r1, #0
	bcs	.L925
	add	r5, r3, #1296
	ldr	r3, [r0, #8]
	add	r5, r5, #10
	mov	r1, #0
	mov	r10, #1
	mov	r2, r3
	mov	r3, r9
	add	r5, r9, r5, lsl #2
	mov	r9, r8
	mov	r8, r3
.L931:
	ldr	ip, [r5, #-944]
	cmp	ip, #0
	ldr	ip, [r0, #60]
	beq	.L926
	cmp	ip, #0
	beq	.L927
	ldr	ip, [r5]
	cmp	ip, r2
	beq	.L959
.L927:
	cmp	r1, #0
	bne	.L942
	ldr	r1, [r5]
	mov	lr, r2
.L939:
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	rsb	r1, r1, lr
	clz	r1, r1
	cmp	ip, #0
	mov	r1, r1, lsr #5
	moveq	r1, #0
	cmp	r1, #0
	bne	.L960
.L942:
	mov	ip, r2
.L930:
	ldr	lr, [r4, #1036]
	add	r6, r6, #1
	add	r5, r5, #4
	mov	r2, ip
	cmp	r6, lr
	bcc	.L931
	mov	r3, r8
	ldr	r2, [r4, #1028]
	mov	r8, r9
	mov	r9, r3
	ldr	r3, [r4, #1032]
	add	r3, r3, r2
.L925:
	cmp	r3, #0
	ldr	lr, [r4, #108]
	ldrne	r6, [fp, #-52]
	movne	r5, #0
	movne	r10, #1
	beq	.L933
.L935:
	ldr	r3, [r0, #60]
	add	r5, r5, #1
	cmp	r3, #0
	bne	.L934
	ldr	r3, [r6]
	add	r3, lr, r3
	cmp	r3, ip
	beq	.L961
.L934:
	ldr	r3, [r4, #1032]
	add	r6, r6, #4
	ldr	r2, [r4, #1028]
	add	r3, r3, r2
	cmp	r5, r3
	bcc	.L935
.L933:
	eor	r1, r1, #1
	cmp	ip, lr
	moveq	ip, #0
	andne	ip, r1, #1
	cmp	ip, #0
	beq	.L958
	mov	r3, #0
	strb	r3, [r0, #1]
	ldr	r3, [r7]
	mov	r2, #0
	str	r2, [r3, #60]
	ldr	r3, [r7]
	ldr	r2, [r3, #52]
	cmp	r2, #1
	beq	.L958
	ldr	r1, [r3, #28]
	mov	r2, #0
	ldr	r0, [r9, #252]
	bl	FSP_SetRef
.L958:
	ldr	r1, [r9, #2568]
	add	r8, r8, #1
	cmp	r8, r1
	bcc	.L937
.L920:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L926:
	cmp	ip, #0
	beq	.L929
	ldr	lr, [r5]
	ldr	r3, [fp, #-48]
	eor	lr, lr, r2
	sub	ip, r3, #1
	tst	lr, ip
	beq	.L959
.L929:
	cmp	r1, #0
	bne	.L942
	ldr	r3, [fp, #-48]
	ldr	ip, [r5]
	sub	r1, r3, #1
	and	lr, r2, r1
	and	r1, r1, ip
	b	.L939
.L960:
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
	b	.L930
.L959:
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
	b	.L930
.L961:
	strb	r10, [r0, #1]
	mov	r2, #1
	ldr	r3, [r7]
	str	r10, [r3, #48]
	ldr	r3, [r7]
	ldr	r0, [r9, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldr	r0, [r7]
	ldr	lr, [r4, #108]
	mov	r1, #1
	ldr	ip, [r0, #8]
	b	.L934
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
	ldr	r3, [r3, #124]
	sub	r3, r3, #19
	cmp	r3, #2
	bls	.L963
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_CheckThatAllRefPicsAreAvailable.part.8
.L963:
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
	ldr	r3, [r0, #2384]
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
	add	r1, r0, #12672
	add	r4, r0, #26880
	add	r1, r1, #40
	add	r4, r4, #232
	mov	r5, #0
.L971:
	ldr	r3, [r1, #48]
	cmp	r3, #0
	bne	.L967
	cmp	r1, #0
	beq	.L968
	ldr	lr, [r0, #2568]
	cmp	lr, #0
	beq	.L968
	ldr	r2, [r0, #2588]
	cmp	r2, r1
	beq	.L967
	add	r2, r0, #2576
	add	r2, r2, #12
	b	.L969
.L970:
	ldr	ip, [r2, #4]!
	cmp	ip, r1
	beq	.L967
.L969:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L970
.L968:
	add	r5, r5, #1
.L967:
	add	r1, r1, #720
	cmp	r1, r4
	bne	.L971
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
	ldr	r1, [r5, #1028]
	cmp	r1, #0
	beq	.L1001
	add	r10, r0, #5120
	mov	r8, #0
	mov	r6, r8
	mov	r9, r10
	add	r10, r10, #15
	add	r9, r9, #36
.L987:
	ldrb	r3, [r10, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L983
	ldr	lr, [r7, #2568]
	ldr	ip, [r5, #108]
	ldr	r3, [r9]
	cmp	lr, #0
	add	ip, ip, r3
	beq	.L983
	add	r1, r7, #2576
	mov	r3, #0
	add	r1, r1, #8
	b	.L986
.L984:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L983
.L986:
	ldr	r2, [r1, #4]!
	ldr	r0, [r2, #8]
	cmp	r0, ip
	bne	.L984
	ldr	r4, [r5, #128]
	ldr	r0, [r2, #32]
	cmp	r4, r0
	bne	.L984
	add	r4, r7, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r4, #2588]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1027
.L985:
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r4, #2588]
	mov	r1, #0
	add	r3, r7, r8, lsl #2
	add	r8, r8, #1
	str	r1, [r2, #60]
	ldr	r2, [r4, #2588]
	str	r2, [r3, #2656]
.L983:
	ldr	r1, [r5, #1028]
	add	r6, r6, #1
	add	r9, r9, #4
	cmp	r1, r6
	bhi	.L987
.L982:
	ldr	r2, [r7, #2564]
	str	r8, [r7, #2580]
	cmp	r2, r8
	bls	.L992
	add	r3, r8, #660
	mov	r0, #0
	add	r3, r3, #3
	add	r3, r7, r3, lsl #2
.L991:
	add	r8, r8, #1
	str	r0, [r3, #4]!
	cmp	r8, r2
	bne	.L991
.L992:
	ldr	r3, [r5, #1032]
	add	r4, r1, r3
	cmp	r4, r6
	movls	r8, #0
	bls	.L990
	add	r9, r6, #1280
	add	r10, r6, #5120
	add	r9, r9, #9
	add	r10, r10, #15
	add	r10, r7, r10
	mov	r8, #0
	add	r9, r7, r9, lsl #2
	str	r8, [fp, #-48]
.L997:
	ldrb	r3, [r10, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L993
	ldr	ip, [r7, #2568]
	ldr	r0, [r5, #108]
	ldr	r3, [r9]
	cmp	ip, #0
	add	r0, r0, r3
	beq	.L993
	add	r1, r7, #2576
	mov	r3, #0
	add	r1, r1, #8
	b	.L996
.L994:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L993
.L996:
	ldr	r2, [r1, #4]!
	ldr	lr, [r2, #8]
	cmp	lr, r0
	bne	.L994
	ldr	r8, [r5, #128]
	ldr	lr, [r2, #32]
	cmp	r8, lr
	bne	.L994
	add	r8, r7, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r8, #2588]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1028
.L995:
	ldr	r1, [fp, #-48]
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r8, #2588]
	add	r3, r7, r1, lsl #2
	add	r1, r1, #1
	str	r1, [fp, #-48]
	mov	r1, #0
	str	r1, [r2, #60]
	ldr	r2, [r8, #2588]
	str	r2, [r3, #2724]
.L993:
	add	r6, r6, #1
	add	r9, r9, #4
	cmp	r4, r6
	bhi	.L997
	ldr	r8, [fp, #-48]
	ldr	r2, [r7, #2564]
.L990:
	cmp	r2, r8
	str	r8, [r7, #2584]
	bls	.L981
	add	r1, r8, #680
	mov	r3, #0
	add	r7, r7, r1, lsl #2
.L999:
	add	r8, r8, #1
	str	r3, [r7, #4]!
	cmp	r8, r2
	bne	.L999
.L981:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1027:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r7, #252]
	bl	FSP_SetRef
	ldr	r3, [r4, #2588]
	b	.L985
.L1028:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r7, #252]
	bl	FSP_SetRef
	ldr	r3, [r8, #2588]
	b	.L995
.L1001:
	mov	r8, r1
	mov	r6, r1
	b	.L982
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
	ldr	r2, [r0, #2348]
	mov	r7, r0
	ldr	r3, [r5, #132]
	mov	r0, #1888
	ldr	ip, [r7, #2344]
	movw	lr, #12660
	mov	r1, #1
	mla	r0, r0, r3, r2
	ldr	r3, [r5, #1028]
	ldr	r2, [r5, #1032]
	add	r2, r3, r2
	ldr	r3, [r5, #1036]
	sub	r2, r2, #1
	ldr	r0, [r0, #32]
	sub	r10, r3, #1
	cmp	r10, r2
	mla	r2, lr, r0, ip
	ldr	r2, [r2, #116]
	mov	r2, r1, asl r2
	ble	.L1040
	add	r9, r3, #1296
	add	r3, r3, #5120
	add	r9, r9, #9
	add	r3, r3, #16
	add	r3, r7, r3
	sub	r4, r2, #1
	add	r9, r7, r9, lsl #2
	mov	r8, #0
	str	r8, [fp, #-52]
	mov	r8, r3
	str	r1, [fp, #-56]
.L1036:
	ldrb	r3, [r8, #-1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1031
	ldrb	r0, [r9, #-944]	@ zero_extendqisi2
	ldr	ip, [r9]
	ldr	lr, [r7, #2568]
	cmp	r0, #0
	andeq	ip, ip, r4
	cmp	lr, #0
	ble	.L1031
	add	r1, r7, #2576
	mov	r3, #0
	add	r1, r1, #8
	str	r7, [fp, #-48]
	b	.L1035
.L1034:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L1047
.L1035:
	ldr	r2, [r1, #4]!
	cmp	r0, #0
	ldr	r6, [r2, #8]
	andeq	r6, r6, r4
	cmp	ip, r6
	bne	.L1034
	ldr	r6, [r5, #128]
	ldr	r7, [r2, #32]
	cmp	r7, r6
	bne	.L1034
	ldr	r7, [fp, #-48]
	mov	ip, #0
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-56]
	add	r3, r7, r3, lsl #2
	strb	r0, [r2, #1]
	add	r2, r7, r1, lsl #2
	add	r1, r1, #1
	str	r1, [fp, #-52]
	ldr	r1, [r3, #2588]
	str	ip, [r1, #64]
	ldr	r1, [r3, #2588]
	str	r0, [r1, #60]
	ldr	r3, [r3, #2588]
	str	r3, [r2, #2792]
.L1031:
	ldr	r3, [r5, #1028]
	sub	r10, r10, #1
	ldr	r2, [r5, #1032]
	sub	r9, r9, #4
	add	r3, r3, r2
	sub	r3, r3, #1
	cmp	r3, r10
	blt	.L1036
	ldr	r8, [fp, #-52]
	mov	r3, r8
.L1030:
	ldr	r2, [r7, #2564]
	str	r3, [r7, #2576]
	cmp	r2, r8
	ble	.L1029
	add	r3, r8, #696
	mov	r1, #0
	add	r3, r3, #1
	add	r3, r7, r3, lsl #2
.L1038:
	add	r8, r8, #1
	str	r1, [r3, #4]!
	cmp	r8, r2
	bne	.L1038
.L1029:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1047:
	ldr	r7, [fp, #-48]
	b	.L1031
.L1040:
	mov	r3, #0
	mov	r8, r3
	b	.L1030
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
	beq	.L1066
	ldr	r7, [r0, #3496]
	mov	r3, #200
	movw	r1, #12512
	mul	r3, r3, r7
	add	r2, r0, r3
	ldr	r1, [r2, r1]
	cmp	r1, #0
	beq	.L1051
	movw	r0, #12520
	ldr	r4, [r2, r0]
	cmp	r4, #0
	addne	r3, r3, #12480
	addne	r3, r3, #40
	movne	r4, #0
	addne	r3, r6, r3
	bne	.L1054
	b	.L1052
.L1057:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1052
.L1054:
	add	r4, r4, #1
	cmp	r4, r1
	bne	.L1057
.L1051:
	ldr	r1, .L1067
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L1064:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1052:
	ldr	r1, [r5, #28]
	ldr	r0, [r6, #252]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	beq	.L1055
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L1055
	mov	r2, #50
	mov	r3, #200
	mla	r2, r2, r7, r4
	mov	r0, #1
	mla	r7, r3, r7, r6
	ldr	r1, .L1067+4
	mov	r3, r4
	add	r6, r6, r2, lsl #2
	add	r7, r7, #12480
	add	r6, r6, #12288
	str	r0, [r6, #232]
	mov	r0, #13
	ldr	r2, [ip, #28]
	ldr	r2, [r2, #4]
	str	r2, [r6, #296]
	ldr	r2, [r5, #8]
	str	r2, [r6, #360]
	ldr	r2, [r7, #36]
	add	r2, r2, #1
	str	r2, [r7, #36]
	ldr	r2, [r5, #228]
	bl	dprint_vfmw
	mov	r0, #0
	str	r4, [r5, #24]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1055:
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	mov	r0, #0
	ldr	r2, [r5, #28]
	ldr	r3, [r5, #8]
	stmia	sp, {r1, ip}
	str	r0, [sp, #8]
	ldr	r1, .L1067+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1064
.L1066:
	mov	r0, r5
	movw	r3, #11586
	ldr	r2, .L1067+12
	ldr	r1, .L1067+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1064
.L1068:
	.align	2
.L1067:
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
	beq	.L1079
	ldr	r0, [r0, #252]
	ldr	r1, [r4, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1071
	ldrsb	r2, [r0, #1]
	cmp	r2, #3
	cmpne	r2, #0
	moveq	r0, #1
	movne	r0, #0
	beq	.L1090
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1076
	ldr	r2, [r4, #48]
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1075
	cmp	r3, #1
	beq	.L1075
.L1087:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1090:
	ldr	r3, [r4, #28]
	mov	r0, #13
	str	r2, [sp]
	ldr	r1, .L1091
	ldr	r2, .L1091+4
	bl	dprint_vfmw
.L1073:
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1076
	ldr	r3, [r4, #8]
	mov	r0, #1
	ldr	r2, .L1091+4
	ldr	r1, .L1091+8
	bl	dprint_vfmw
	mvn	r0, #2
	b	.L1087
.L1071:
	ldr	ip, [r4, #28]
	mov	r2, r4
	ldr	r3, [r4, #8]
	mov	r0, #1
	ldr	r1, .L1091+12
	str	ip, [sp, #4]
	ldr	ip, [r4, #52]
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1073
.L1075:
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	mov	r3, r4
	ldr	r2, .L1091+4
	ldr	r1, .L1091+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1087
.L1079:
	mvn	r0, #0
	b	.L1087
.L1076:
	mov	r2, #1
	mov	r3, #2
	strb	r2, [r4, #2]
	mvn	r0, #2
	str	r3, [r4, #52]
	b	.L1087
.L1092:
	.align	2
.L1091:
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
	beq	.L1095
	ldr	ip, [r0, #2568]
	cmp	ip, #0
	beq	.L1095
	add	r10, r0, #2576
	mvn	r3, #0
	mvn	r6, #1
	mvn	r7, #0
	add	r10, r10, #8
	str	r3, [fp, #-48]
	mov	r9, #0
	b	.L1098
.L1132:
	ldr	r1, [r10]
	ldr	ip, [r5, #2568]
	add	r1, r1, #672
	ldrd	r0, [r1, #-8]
	cmp	r1, r7
	cmpeq	r0, r6
	strcc	r9, [fp, #-48]
	movcc	r6, r0
	movcc	r7, r1
.L1097:
	add	r9, r9, #1
	cmp	r9, ip
	bcs	.L1135
.L1098:
	ldr	r1, [r10, #4]!
	cmp	r1, #0
	beq	.L1097
	ldr	r1, [r1, #28]
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1134
	ldrsb	r1, [r0, #1]
	cmp	r1, #3
	cmpne	r1, #0
	bne	.L1132
.L1134:
	ldr	ip, [r5, #2568]
	add	r9, r9, #1
	cmp	r9, ip
	bcc	.L1098
.L1135:
	ldr	r3, [fp, #-48]
	cmn	r3, #1
	beq	.L1095
	ldrd	r2, [r8, #-8]
	cmp	r3, r7
	cmpeq	r2, r6
	bhi	.L1136
.L1095:
	ldrb	r3, [r4, #145]	@ zero_extendqisi2
	ldrb	r2, [r4, #144]	@ zero_extendqisi2
	and	r3, r3, #195
	bfc	r3, #0, #2
	bfc	r2, #0, #2
	strb	r3, [r4, #145]
	strb	r2, [r4, #144]
	ldr	r3, [r5, #144]
	str	r3, [r4, #188]
	ldr	r3, [r5, #2364]
	ldrh	r3, [r3, #124]
	cmp	r3, #1
	moveq	r2, #0
	beq	.L1099
	movw	r2, #257
	cmp	r3, r2
	movne	r2, #1
	bne	.L1099
	ldr	r2, [r5, #2876]
	subs	r2, r2, #1
	movne	r2, #1
.L1099:
	ldr	r3, [r5, #2368]
	ldrb	r3, [r3, #2066]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r1, #3
	beq	.L1100
	ldr	r3, [r4, #40]
	cmp	r3, #1
	cmpne	r3, #11
	moveq	r1, #1
	bne	.L1137
.L1101:
	ldr	r2, [r4, #44]
	clz	r2, r2
	mov	r2, r2, lsr #5
.L1100:
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
	ldr	r3, [r5, #2384]
	ldr	r1, [r4, #28]
	ldr	r3, [r3, #604]
	str	r3, [r4, #204]
	ldr	r3, [r5, #2384]
	ldr	r3, [r3, #608]
	str	r3, [r4, #208]
	ldr	r3, [r5, #2384]
	ldr	r3, [r3, #612]
	str	r3, [r4, #212]
	ldr	r0, [r5, #252]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L1093
	ldr	r3, .L1138
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
.L1093:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1136:
	ldr	r0, [r5, #252]
	strd	r6, [sp]
	bl	IsPtsRewind
	cmp	r0, #0
	bne	.L1095
	ldrd	r2, [r8, #-8]
	mov	r0, #29
	ldr	r1, .L1138+4
	strd	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	add	r10, r5, r3, lsl #2
	ldrd	r2, [r8, #-8]
	ldr	r1, [r10, #2588]
	add	r1, r1, #672
	strd	r2, [r1, #-8]
	strd	r6, [r8, #-8]
	b	.L1095
.L1137:
	bic	r3, r3, #8
	cmp	r3, #2
	moveq	r1, #2
	movne	r1, #3
	b	.L1101
.L1139:
	.align	2
.L1138:
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
	bhi	.L1142
	mov	r3, #720
	mla	r1, r3, r1, r0
	add	r1, r1, #12672
	ldrb	r0, [r1, #41]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1142:
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
	beq	.L1148
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	addne	r4, r0, #576
	addne	r5, r0, #608
	movne	r6, #0
	movne	r7, #0
	beq	.L1153
.L1147:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1146
	ldr	r0, [r8, #252]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1146:
	cmp	r4, r5
	bne	.L1147
	ldr	r0, [r8, #252]
	mov	r1, r9
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1153:
	ldr	r1, .L1154
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1148:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1155:
	.align	2
.L1154:
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
	bhi	.L1160
	sub	r2, r3, #8448
	movw	ip, #4749
	sub	r2, r2, #52
	cmp	r2, ip
	movls	r3, #1
	strlsb	r3, [r0, #3]
	bls	.L1158
	sub	r3, r3, #13248
	movw	r2, #1749
	sub	r3, r3, #2
	cmp	r3, r2
	bhi	.L1160
	mov	r3, #2
	strb	r3, [r0, #3]
.L1158:
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
.L1160:
	mov	r3, #0
	strb	r3, [r0, #3]
	b	.L1158
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
	ldr	r1, .L1182
	mov	r4, r0
	ldrb	r2, [r0]	@ zero_extendqisi2
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	ldr	r1, .L1182+4
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r1, .L1182+8
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	ldr	r1, .L1182+12
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #4]
	ldr	r1, .L1182+16
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #6]
	ldr	r1, .L1182+20
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	ldr	r1, .L1182+24
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #9]	@ zero_extendqisi2
	ldr	r1, .L1182+28
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r5, [r4, #1]	@ zero_extendqisi2
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	mov	r0, #32
	cmp	r5, #0
	bne	.L1164
	ldr	r1, .L1182+32
	bl	dprint_vfmw
	ldrb	r2, [r4, #11]	@ zero_extendqisi2
	ldr	r1, .L1182+36
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	ldr	r1, .L1182+40
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #13]	@ zero_extendqisi2
	ldr	r1, .L1182+44
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #14]	@ zero_extendqisi2
	ldr	r1, .L1182+48
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #15]	@ zero_extendqisi2
	ldr	r1, .L1182+52
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #15
	addne	r6, r4, #26
	beq	.L1169
.L1168:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1182+56
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1182+60
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1168
.L1169:
	ldrb	r2, [r4, #38]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1182+64
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #38
	addne	r6, r4, #45
	movne	r5, #0
	beq	.L1170
.L1171:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1182+68
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1182+72
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1171
.L1170:
	movw	r2, #290
	ldr	r1, .L1182+76
	mov	r0, #32
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1164:
	ldr	r1, .L1182+80
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #10
	addne	r6, r4, #78
	movne	r5, #0
	beq	.L1176
.L1175:
	mov	r2, r5
	ldrh	r3, [r7, #2]!
	ldr	r1, .L1182+84
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r3, [r6, #2]!
	mov	r2, r5
	ldr	r1, .L1182+88
	mov	r0, #32
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1175
.L1176:
	ldrb	r2, [r4, #148]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1182+92
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #148
	addne	r6, r4, #216
	movne	r5, #0
	beq	.L1174
.L1177:
	mov	r3, r5
	ldrh	r2, [r7, #2]!
	ldr	r1, .L1182+96
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrh	r2, [r6, #2]!
	mov	r0, #32
	ldr	r1, .L1182+100
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1177
.L1174:
	movw	r3, #286
	ldr	r1, .L1182+104
	ldrh	r2, [r4, r3]
	add	r4, r4, #288
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r1, .L1182+108
	ldrh	r2, [r4]
	mov	r0, #32
	bl	dprint_vfmw
	b	.L1170
.L1183:
	.align	2
.L1182:
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
	beq	.L1224
	cmp	r2, #0
	bne	.L1226
.L1224:
	ldrb	ip, [r4, #59]	@ zero_extendqisi2
	ldrb	r0, [r4, #128]	@ zero_extendqisi2
.L1186:
	str	r0, [sp, #12]
	mov	r0, #22
	str	r1, [sp, #4]
	str	r2, [sp]
	str	ip, [sp, #8]
	ldr	r2, .L1229
	ldr	r1, .L1229+4
	bl	dprint_vfmw
	mov	r3, #0
	strb	r3, [r5, #458]
.L1184:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1226:
	cmp	r1, #0
	beq	.L1224
	ldrb	r0, [r4, #59]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1189
	ldrb	r0, [r4, #128]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1227
.L1189:
	mov	r3, #1
	strb	r3, [r5, #458]
	ldr	r0, [r6, #24]
	ldrb	r1, [r4, #57]	@ zero_extendqisi2
	ldrb	r2, [r4, #58]	@ zero_extendqisi2
	cmp	r0, #9
	strb	r1, [fp, #-320]
	strb	r2, [fp, #-319]
	bne	.L1191
	ldr	r2, [r6, #32]
	cmp	r2, #9
	streqb	r3, [fp, #-312]
.L1191:
	ldrb	r3, [r4, #60]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1192
	ldrb	r2, [r4, #129]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1192
	cmp	r2, #9
	cmpne	r3, #9
	ldrneb	r3, [fp, #-312]	@ zero_extendqisi2
	moveq	r3, #1
	strb	r3, [fp, #-318]
.L1192:
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
	bne	.L1196
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
	beq	.L1201
	sub	r2, fp, #320
	add	ip, r4, #66
	add	r0, r2, #15
	add	r1, r4, #81
	add	r2, r2, #26
.L1200:
	add	r3, r3, #1
	ldrb	r6, [ip, #1]!	@ zero_extendqisi2
	ldrb	lr, [r1, #1]!	@ zero_extendqisi2
	cmp	r3, r7
	strb	r6, [r0, #1]!
	strb	lr, [r2, #1]!
	bne	.L1200
.L1201:
	ldrb	r6, [r4, #97]	@ zero_extendqisi2
	cmp	r6, #0
	strb	r6, [fp, #-282]
	beq	.L1199
	sub	r1, fp, #280
	sub	r2, fp, #272
	add	r0, r4, #97
	sub	r1, r1, #2
	add	r4, r4, #112
	sub	r2, r2, #3
	mov	r3, #0
.L1204:
	add	r3, r3, #1
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	ldrb	ip, [r4, #1]!	@ zero_extendqisi2
	cmp	r3, r6
	strb	lr, [r1, #1]!
	strb	ip, [r2, #1]!
	bne	.L1204
.L1199:
	ldr	r3, [r5, #464]
	cmp	r3, #0
	bne	.L1228
	ldr	r2, .L1229
	mov	r0, #1
	ldr	r1, .L1229+8
	bl	dprint_vfmw
	b	.L1184
.L1196:
	ldrb	r7, [r4, #168]	@ zero_extendqisi2
	ldr	r2, [r4, #136]
	add	r7, r7, #1
	ldr	r3, [r4, #140]
	uxtb	r7, r7
	strh	r2, [fp, #-34]	@ movhi
	cmp	r7, #0
	strb	r7, [fp, #-310]
	strh	r3, [fp, #-32]	@ movhi
	beq	.L1208
	sub	r3, fp, #320
	add	ip, r4, #170
	add	r1, r4, #368
	sub	r2, fp, #242
	add	r0, r3, #10
	mov	r3, #0
.L1207:
	add	r3, r3, #1
	ldrh	r6, [ip, #2]!
	ldrh	lr, [r1, #2]!
	cmp	r3, r7
	strh	r6, [r0, #2]!	@ movhi
	strh	lr, [r2, #2]!	@ movhi
	bcc	.L1207
.L1208:
	ldrb	r6, [r4, #169]	@ zero_extendqisi2
	add	r6, r6, #1
	uxtb	r6, r6
	strb	r6, [fp, #-172]
	cmp	r6, #0
	beq	.L1199
	add	r2, r4, #432
	sub	r0, fp, #172
	add	r4, r4, #236
	add	r2, r2, #2
	sub	r1, fp, #104
	mov	r3, #0
.L1209:
	add	r3, r3, #1
	ldrh	lr, [r4, #2]!
	ldrh	ip, [r2, #2]!
	cmp	r3, r6
	strh	lr, [r0, #2]!	@ movhi
	strh	ip, [r1, #2]!	@ movhi
	bcc	.L1209
	b	.L1199
.L1228:
	ldr	r3, .L1229+12
	sub	r1, fp, #320
	movw	r2, #290
	ldr	r0, [r5, #472]
	ldr	r3, [r3, #52]
	blx	r3
	movw	r3, #290
	str	r3, [r5, #460]
	b	.L1184
.L1227:
	mov	ip, r0
	b	.L1186
.L1230:
	.align	2
.L1229:
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
.L1232:
	ldr	r6, [r0, #4]!
	add	r2, r2, #1
	cmp	r2, #3
	strh	r6, [lr, #2]!	@ movhi
	ldr	r6, [r5, #4]!
	strh	r6, [r4, #2]!	@ movhi
	bne	.L1232
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
	ldr	r3, [r0, #2348]
	mov	lr, #1888
	ldr	ip, [r0, #2344]
	ldr	r2, [r2, #132]
	movw	r5, #12660
	mov	r6, r0
	add	r0, r0, #12672
	mov	r1, #0
	add	r0, r0, #40
	mla	r3, lr, r2, r3
	mov	lr, r1
	ldr	r3, [r3, #32]
	strb	r1, [r6, #3489]
	mla	r5, r5, r3, ip
.L1239:
	ldr	r3, [r0, #48]
	cmp	r3, #0
	bne	.L1235
	cmp	r0, #0
	beq	.L1246
	ldr	ip, [r6, #2568]
	cmp	ip, #0
	beq	.L1246
	ldr	r2, [r6, #2588]
	cmp	r2, r0
	beq	.L1235
	add	r2, r6, #2576
	add	r2, r2, #12
	b	.L1237
.L1238:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	beq	.L1235
.L1237:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1238
.L1246:
	mov	r7, #720
	add	r9, r6, #3552
	mla	r7, r7, lr, r6
	mov	r4, r0
	mov	r3, #1
	mov	r2, #101
	strb	r3, [r6, #3489]
	mov	r0, r9
	add	r1, r7, #12736
	str	r2, [r6, #3528]
	add	r1, r1, #56
	mov	r2, #640
	bl	memcpy
	add	r3, r7, #12672
	movw	r2, #12728
	str	r4, [r6, #3548]
	mov	r8, #0
	str	r8, [r6, #3704]
	str	r8, [r7, r2]
	strb	r8, [r3, #42]
	strb	r8, [r4]
	ldr	r3, [r6, #3548]
	str	r8, [r3, #60]
	ldr	r3, [r6, #3548]
	str	r8, [r3, #64]
	ldr	r3, [r6, #3548]
	str	r8, [r3, #52]
	ldrb	r1, [r6, #3489]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1243
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
	beq	.L1241
	add	r1, r5, #2064
	add	r2, r6, #2864
	bl	HEVC_ConvertHDRInfo
	ldr	r3, [r6, #2384]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1250
.L1242:
	ldr	r5, .L1251
	add	r1, r4, #40
	ldr	r0, [r6, #3548]
	mov	r2, #640
	ldr	r3, [r5, #52]
	add	r0, r0, #80
	blx	r3
	ldr	r1, [r6, #3548]
	ldr	r3, [r5, #52]
	mov	r0, r9
	add	r1, r1, #80
	mov	r2, #640
	blx	r3
	ldr	r3, [r6, #3548]
	mov	r0, #0
	str	r7, [r3, #28]
	ldrsb	r3, [r4, #4]
	str	r3, [r6, #3524]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1235:
	add	lr, lr, #1
	add	r0, r0, #720
	cmp	lr, #20
	bne	.L1239
.L1243:
	ldr	r1, .L1251+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1250:
	ldr	r1, [r6, #2368]
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
	b	.L1242
.L1241:
	strb	r3, [r6, #3489]
	mov	r0, r3
	ldr	r1, .L1251+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1252:
	.align	2
.L1251:
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
	bne	.L1257
	b	.L1260
.L1256:
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1258
	cmp	r4, #32
	beq	.L1261
.L1257:
	mov	r1, r4
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	add	r4, r4, #1
	cmp	r0, #0
	bne	.L1256
	ldr	r1, .L1262
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1260:
	ldr	r1, .L1262+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1258:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1261:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1263:
	.align	2
.L1262:
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
	add	r0, r0, #5504
	add	r0, r0, #48
	add	r5, r8, #13312
	bl	ResetVoQueue
	add	r9, r8, #27648
	add	r5, r5, #48
	add	r9, r9, #112
	mov	r6, #0
	mov	r7, #0
.L1267:
	sub	r4, r5, #32
	mov	r3, #0
	strb	r3, [r5, #-647]
	str	r3, [r5, #-600]
.L1266:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1265
	ldr	r0, [r8, #252]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1265:
	cmp	r4, r5
	bne	.L1266
	add	r5, r4, #720
	cmp	r5, r9
	bne	.L1267
	ldr	r2, [r8, #184]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r8, r8, #2128
	mov	r3, #0
	add	r8, r8, #12
	mov	r1, r3
.L1269:
	add	r3, r3, #1
	str	r1, [r8, #4]!
	cmp	r3, r2
	bne	.L1269
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
	ldr	r3, [r6, #2588]
	str	r7, [r3, #48]
	ldr	r3, [r6, #2588]
	ldr	r0, [r0, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1278
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1279
	ldr	r3, [r6, #2588]
	mov	r2, r7
	ldr	r0, [r5, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
.L1279:
	ldr	r3, [r6, #2588]
	mov	r2, #0
	ldr	r0, [r5, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
.L1278:
	ldr	r1, [r5, #2568]
	sub	r1, r1, #1
	cmp	r4, r1
	addls	r3, r4, #644
	addls	r3, r3, #3
	addls	r3, r5, r3, lsl #2
	bhi	.L1282
.L1281:
	add	r4, r4, #1
	ldr	r2, [r3, #4]!
	cmp	r4, r1
	str	r2, [r3, #-4]
	bls	.L1281
.L1282:
	add	r3, r1, #644
	mov	r2, #0
	add	r3, r3, #2
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	str	r1, [r5, #2568]
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
	ldr	r1, [r0, #2568]
	mov	r5, r0
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r6, #0
	mov	r4, r6
	mov	r7, r6
	b	.L1294
.L1293:
	add	r4, r4, #1
	cmp	r4, r1
	mov	r6, r4
	bcs	.L1300
.L1294:
	add	r3, r5, r4, lsl #2
	ldr	r3, [r3, #2588]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1293
	mov	r1, r6
	strb	r7, [r3]
	mov	r0, r5
	sub	r4, r4, #1
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	add	r4, r4, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r1, [r5, #2568]
	mov	r6, r4
	cmp	r4, r1
	bcc	.L1294
.L1300:
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
	ldr	r5, [r0, #2568]
	mov	r10, r0
	cmp	r5, #0
	beq	.L1310
	mov	r6, #0
	mvn	r8, #0
	mov	r9, r6
	mov	r4, r6
	b	.L1309
.L1320:
	ldrsb	r2, [r0, #1]
	cmp	r2, #0
	cmpne	r2, #3
	ldr	r2, [r7, #2588]
	bne	.L1305
	ldr	r0, [r2, #52]
	cmp	r0, #1
	beq	.L1305
	str	r8, [r2, #28]
	mov	r3, #1
	ldr	r2, [r7, #2588]
	strb	r1, [r2, #1]
	ldr	r2, [r7, #2588]
	strb	r3, [r2, #2]
	ldr	r2, [r7, #2588]
.L1305:
	ldr	r3, [r2]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	addne	r9, r9, #1
	beq	.L1319
	add	r4, r4, #1
	cmp	r4, r5
	beq	.L1302
.L1309:
	add	r7, r10, r9, lsl #2
	ldr	r0, [r10, #252]
	ldr	r2, [r7, #2588]
	ldr	r1, [r2, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1303
	ldrsb	r1, [r0]
	cmp	r1, #0
	beq	.L1320
	ldr	r2, [r7, #2588]
	b	.L1305
.L1303:
	ldr	r2, [r7, #2588]
	ldr	r1, [r2, #52]
	cmp	r1, #1
	beq	.L1305
	str	r8, [r2, #28]
	mov	r3, #1
	ldr	r2, [r7, #2588]
	strb	r0, [r2, #1]
	ldr	r2, [r7, #2588]
	strb	r3, [r2, #2]
	ldr	r2, [r7, #2588]
	b	.L1305
.L1319:
	mov	r1, r9
	mov	r0, r10
	add	r4, r4, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	cmp	r4, r5
	mov	r6, #1
	bne	.L1309
.L1302:
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1310:
	mov	r6, r5
	b	.L1302
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
	ldr	r2, [r3, #228]
	ldr	r3, [r3, #224]
	cmp	r2, r3
	bcs	.L1325
	ldr	r3, [r0, #2564]
	ldr	r2, [r0, #2568]
	cmp	r2, r3
	ldmccfd	sp, {r4, r5, fp, sp, pc}
	cmp	r3, #15
	bls	.L1327
.L1325:
	ldr	r3, [r4, #2588]
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
.L1327:
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L1325
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
	ldr	r2, [r0, #2568]
	mov	r5, r0
	ldr	r3, [r0, #2564]
	cmp	r2, r3
	bhi	.L1335
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1336:
	add	r1, r5, #2576
	mov	r3, #0
	add	r1, r1, #8
.L1332:
	ldr	r2, [r1, #4]!
	ldr	r0, [r4]
	ldr	r2, [r2, #8]
	cmp	r0, r2
	strgt	r2, [r4]
	strgt	r3, [r6]
	add	r3, r3, #1
	ldr	r2, [r5, #2568]
	cmp	r2, r3
	bhi	.L1332
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1335:
	ldr	r1, .L1337
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #2564]
	cmp	r2, #0
	str	r2, [r5, #2568]
	bne	.L1336
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1338:
	.align	2
.L1337:
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
	ldr	lr, [r0, #2348]
	mov	r5, #1888
	movw	r4, #12660
	ldr	ip, [r3, #132]
	ldr	r3, [r0, #2344]
	mla	ip, r5, ip, lr
	ldr	lr, [fp, #4]
	ldr	ip, [ip, #32]
	mla	r3, r4, ip, r3
	ldr	ip, [r3, #64]
	ldr	r3, [r3, #68]
	cmp	r1, ip
	cmpeq	lr, #0
	bne	.L1343
	cmp	r2, r3
	beq	.L1344
.L1343:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1344:
	ldr	r3, [r0, #172]
	cmp	r3, #0
	beq	.L1343
	ldr	r3, [r0, #2384]
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
	ldr	r4, [r0, #2356]
	ldrb	ip, [r4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1356
	mov	r3, #0
	mov	r2, r4
	mov	lr, r3
.L1347:
	add	r3, r3, #1
	ldr	r1, [r2, #44]
	cmp	r3, ip
	add	r2, r2, #28
	add	lr, lr, r1
	bne	.L1347
.L1346:
	ldr	r2, [r0, #2336]
	mov	r3, ip, asl #5
	sub	ip, r3, ip, asl #2
	add	r4, r4, ip
	ldr	r3, [r2, #24]
	and	r3, r3, #7
	str	r3, [r4, #56]
	ldr	r2, [r0, #2356]
	ldr	r3, [r0, #2336]
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #48]
	add	r2, r2, ip, lsr #3
	rsb	r2, lr, r2
	str	r2, [r3, #60]
	ldr	r1, [r0, #2356]
	ldr	r3, [r0, #2336]
	ldrb	r2, [r1]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r2, asl #5
	sub	r2, r3, r2, asl #2
	add	r2, r1, r2
	ldr	r3, [r2, #44]
	add	r3, lr, r3
	rsb	r3, ip, r3, lsl #3
	str	r3, [r2, #52]
	ldr	r2, [r0, #2356]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	ldr	r1, [r3, #56]
	and	r2, r2, #3
	add	r2, r1, r2, lsl #3
	str	r2, [r3, #56]
	ldr	r2, [r0, #2356]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #3
	str	r2, [r3, #60]
	ldr	r1, [r0, #2356]
	ldr	r2, [r1, #8]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L1363
	ldrb	ip, [r1]	@ zero_extendqisi2
	add	lr, ip, #1
	cmp	r2, lr
	movhi	r2, #1
	movls	r2, #0
	cmp	lr, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L1349
	add	ip, ip, #2
	mov	lr, #0
.L1350:
	sub	r3, ip, #1
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	str	lr, [r1, #56]
	ldr	r2, [r0, #2356]
	add	r2, r2, r3
	ldr	r1, [r2, #48]
	str	r1, [r2, #60]
	ldr	r2, [r0, #2356]
	add	r2, r2, r3
	ldr	r1, [r2, #44]
	mov	r1, r1, asl #3
	str	r1, [r2, #52]
	ldr	r2, [r0, #2356]
	add	r2, r2, r3
	ldr	r1, [r2, #60]
	ldr	r4, [r2, #56]
	and	r1, r1, #15
	add	r1, r4, r1, lsl #3
	str	r1, [r2, #56]
	ldr	r2, [r0, #2356]
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #15
	str	r2, [r3, #60]
	ldr	r1, [r0, #2356]
	ldr	r3, [r1, #8]
	cmp	ip, #1
	cmpls	ip, r3
	add	ip, ip, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L1350
	sub	r3, r3, #1
.L1349:
	mov	r2, r3, asl #5
	ldr	ip, [r1, #12]
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	ldr	r3, [r1, #52]
	rsb	r3, ip, r3
	str	r3, [r1, #52]
	ldr	r4, [r0, #2356]
	ldrb	r2, [r4]	@ zero_extendqisi2
	ldr	lr, [r4, #8]
	cmp	r2, lr
	ldmcsfd	sp, {r4, fp, sp, pc}
	sxth	r1, r2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r4, r3
.L1354:
	ldr	r1, [r3, #60]
	add	r2, r2, #1
	ldr	ip, [r0, #3520]
	add	r3, r3, #28
	cmp	r1, ip
	strcc	r1, [r0, #3520]
	ldrcc	lr, [r4, #8]
	cmp	lr, r2
	bhi	.L1354
	ldmfd	sp, {r4, fp, sp, pc}
.L1363:
	ldr	r1, .L1364
	mov	r0, #0
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L1356:
	mov	lr, ip
	b	.L1346
.L1365:
	.align	2
.L1364:
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
	ldr	r2, [r2, #132]
	cmp	r2, r3
	bge	.L1374
	mov	r3, #1888
	ldr	r1, [r0, #2348]
	mul	r3, r3, r2
	add	ip, r1, r3
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1375
	ldr	r2, [ip, #32]
	ldr	r3, [r0, #160]
	cmp	r2, r3
	bge	.L1376
	ldr	r1, [r0, #2344]
	movw	r3, #12660
	mla	r3, r3, r2, r1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1377
	ldr	r2, [r3, #48]
	ldr	r3, [r0, #156]
	cmp	r2, r3
	bcs	.L1378
	ldr	r1, [r0, #2340]
	mov	r3, r2, asl #7
	add	r3, r3, r2, lsl #2
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1379
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1374:
	ldr	r1, .L1380
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1375:
	ldr	r1, .L1380+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1376:
	ldr	r1, .L1380+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1377:
	ldr	r1, .L1380+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1378:
	ldr	r1, .L1380+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1379:
	ldr	r1, .L1380+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1381:
	.align	2
.L1380:
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
	ldr	lr, [r0, #2356]
	ldr	r3, [r1, #128]
	ldr	r2, [lr, #16]
	add	r4, r0, r3, lsl #2
	ldr	ip, [r4, #228]
	cmn	ip, #-2147483647
	beq	.L1423
	sub	r5, r2, #16
	cmp	r2, #21
	cmpne	r5, #2
	bls	.L1420
.L1399:
	cmp	r2, #1
	bls	.L1424
.L1387:
	sub	r2, r2, #19
	cmp	r2, #1
	movls	ip, #-2147483647
	strls	ip, [r4, #228]
.L1420:
	ldr	r2, [r1, #108]
.L1389:
	cmp	ip, r2
	ble	.L1390
	ldr	r5, [lr, #16]
	sub	r6, r5, #8
	cmp	r6, #1
	addhi	r3, r0, r3
	bls	.L1425
.L1392:
	ldrb	ip, [r3, #10]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1393
	ldr	r5, [r4, #232]
	cmp	r5, r2
	ble	.L1393
	ldr	r6, [lr, #16]
	sub	r7, r6, #8
	cmp	r7, #1
	bls	.L1426
.L1393:
	ldrb	ip, [r1, #97]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1394
	ldr	lr, [lr, #16]
	sub	r5, lr, #19
	cmp	r5, #1
	bls	.L1421
	cmp	lr, #21
	beq	.L1421
	sub	lr, lr, #16
	cmp	lr, #2
	strls	r2, [r4, #232]
	movls	ip, #1
	strlsb	ip, [r3, #10]
.L1394:
	ldr	ip, [r0, #236]
	ldrb	r3, [r1, #96]	@ zero_extendqisi2
	cmp	ip, #0
	ldr	r1, [r1, #132]
	beq	.L1398
	ldr	ip, [r0, #208]
	cmp	r1, ip
	movne	r3, #1
.L1398:
	ldr	ip, [r0, #304]
	cmp	ip, r1
	movne	r0, #1
	beq	.L1427
.L1419:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1424:
	ldr	r5, [r1, #116]
	cmp	r5, #2
	bne	.L1387
	cmn	ip, #-2147483647
	bne	.L1420
.L1388:
	ldr	r2, [r1, #108]
	str	r2, [r4, #228]
	ldr	ip, [lr, #16]
	cmp	ip, #1
	bls	.L1428
.L1390:
	add	r3, r0, r3
	ldrb	ip, [r3, #5]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1392
	ldr	r5, [lr, #16]
	sub	r6, r5, #8
	cmp	r6, #1
	bhi	.L1392
	str	r2, [sp]
	movw	r3, #12994
	str	r5, [sp, #8]
	mov	r0, #1
	str	ip, [sp, #4]
	ldr	r2, .L1429
	ldr	r1, .L1429+4
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1419
.L1423:
	sub	r6, r2, #16
	cmp	r6, #5
	movhi	r7, #0
	movls	r7, #1
	cmp	r2, #1
	ldrls	r5, [r1, #116]
	movhi	r5, #0
	subls	r5, r5, #2
	clzls	r5, r5
	movls	r5, r5, lsr #5
	orrs	r5, r5, r7
	moveq	r0, #2
	beq	.L1419
	cmp	r2, #21
	cmpne	r6, #2
	bhi	.L1399
	b	.L1388
.L1427:
	ldr	r0, [r0, #260]
	cmp	r0, r2
	moveq	r0, r3
	movne	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1425:
	str	r2, [sp]
	movw	r3, #12987
	str	r5, [sp, #8]
	mov	r0, #1
	str	ip, [sp, #4]
	ldr	r2, .L1429
	ldr	r1, .L1429+8
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1419
.L1421:
	str	r2, [r4, #232]
	strb	ip, [r3, #10]
	b	.L1394
.L1428:
	mov	ip, #1
	str	ip, [r0, #332]
	ldr	ip, [r4, #228]
	b	.L1389
.L1426:
	str	r2, [sp, #4]
	movw	r3, #13003
	str	r6, [sp, #12]
	mov	r0, #1
	str	r5, [sp, #8]
	str	ip, [sp]
	ldr	r2, .L1429
	ldr	r1, .L1429+12
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1419
.L1430:
	.align	2
.L1429:
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
	ldr	r0, [r0, #2336]
	bl	BsGet
	cmp	r0, #0
	beq	.L1436
	ldr	r0, [r4, #2336]
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	beq	.L1435
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r1, .L1437
	mov	r2, r0
	mov	r0, #19
	bl	dprint_vfmw
.L1435:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1436:
	ldr	r1, .L1437+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1438:
	.align	2
.L1437:
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
	ldr	r0, [r0, #124]
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
	ldr	r0, [r0, #124]
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
	bne	.L1478
.L1476:
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r6, #0
	str	r0, [r9, #4]
	ble	.L1447
	sub	r3, fp, #84
	sub	r7, fp, #92
	add	r10, r3, r6
	mov	r4, r3
	mov	r9, r7
.L1448:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4], #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r4, r10
	strb	r0, [r9], #1
	bne	.L1448
	cmp	r6, #7
	movle	r4, r6
	ble	.L1452
	b	.L1458
.L1451:
	cmp	r4, #8
	beq	.L1458
.L1452:
	mov	r1, #2
	ldr	r0, [r5, #2336]
	bl	BsGet
	add	r4, r4, #1
	cmp	r0, #0
	beq	.L1451
	ldr	r1, .L1480
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1447:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1458:
	mov	r10, #0
	b	.L1456
.L1455:
	add	r10, r10, #1
	cmp	r6, r10
	ble	.L1447
.L1456:
	cmp	r8, #0
	beq	.L1453
	sub	r3, fp, #84
	ldrb	r3, [r3, r10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1479
.L1453:
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1455
	mov	r1, #8
	ldr	r0, [r5, #2336]
	bl	BsGet
	b	.L1455
.L1479:
	mov	r1, #2
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	mov	r4, #32
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2336]
	bl	BsGet
.L1454:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L1454
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #12
	ldr	r0, [r5, #2336]
	bl	BsGet
	b	.L1453
.L1478:
	mov	r1, #2
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	sub	r4, fp, #77
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2336]
	sub	r7, fp, #45
	bl	BsGet
	mov	r10, r0
.L1443:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	strb	r0, [r4, #1]!
	cmp	r4, r7
	bne	.L1443
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #1]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	sub	r3, r10, #4
	cmp	r3, #3
	bls	.L1444
	ldrb	r3, [fp, #-72]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1444
	ldrb	r3, [fp, #-71]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1444
	ldrb	r3, [fp, #-70]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1444
	ldrb	r3, [fp, #-69]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1444
	mov	r1, #16
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #11
	ldr	r0, [r5, #2336]
	bl	BsGet
	b	.L1446
.L1444:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #2
	ldr	r0, [r5, #2336]
	bl	BsGet
.L1446:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldrb	r2, [fp, #-75]	@ zero_extendqisi2
	ldrb	r3, [fp, #-74]	@ zero_extendqisi2
	mov	r1, #8
	str	r10, [r5, #308]
	str	r2, [r5, #312]
	str	r3, [r5, #316]
	b	.L1476
.L1481:
	.align	2
.L1480:
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
	ldr	r9, .L1500
	add	r10, r0, #2208
	add	r3, r0, #2224
	add	r10, r10, #12
	mov	r6, #0
	add	r3, r3, #12
	str	r0, [fp, #-52]
	str	r3, [fp, #-48]
.L1483:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L1491
	ldr	r3, [fp, #-52]
	mov	r8, r6, asl #9
	ldr	r7, [fp, #-48]
	sub	r8, r8, r6, asl #7
	add	r5, r3, #608
	mov	r4, #0
.L1489:
	cmp	r6, #0
	add	r0, r5, r8
	mov	r2, #64
	ldr	r3, [r9, #52]
	beq	.L1498
	cmp	r6, #3
	beq	.L1499
	ldr	ip, .L1500+4
	cmp	r4, #2
	ldr	r1, .L1500+8
	movhi	r1, ip
	blx	r3
.L1485:
	mov	r3, #16
	str	r3, [r7, #4]!
	ldr	r3, [r10]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1489
.L1491:
	add	r6, r6, #1
	ldr	r3, [fp, #-48]
	cmp	r6, #4
	add	r3, r3, #24
	str	r3, [fp, #-48]
	bne	.L1483
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1498:
	mov	r2, #16
	ldr	r1, .L1500+12
	mov	r0, r5
	blx	r3
	b	.L1485
.L1499:
	ldr	r0, .L1500+4
	cmp	r4, #0
	ldr	r1, .L1500+8
	mov	r2, #64
	movne	r1, r0
	add	r0, r5, #1152
	blx	r3
	b	.L1485
.L1501:
	.align	2
.L1500:
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
.L1503:
	cmp	r5, r8
	ldmcsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r7, #0
	beq	.L1503
	add	r3, r5, r6
	ldrb	ip, [r1]	@ zero_extendqisi2
	mov	r4, r1
	mov	r2, #0
	add	r3, r0, r3, lsl #2
	ldr	lr, [r3, #608]
	orr	ip, lr, ip
	str	ip, [r3, #608]
.L1509:
	add	r2, r2, #1
	add	r3, r5, r6
	and	lr, r2, #3
	cmp	r2, r7
	add	r3, r0, r3, lsl #2
	mov	ip, lr, asl #3
	beq	.L1503
	ldrb	r9, [r4, #1]!	@ zero_extendqisi2
	cmp	lr, #3
	ldr	lr, [r3, #608]
	addeq	r5, r5, #1
	orr	ip, lr, r9, asl ip
	str	ip, [r3, #608]
	b	.L1509
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
	ldr	r3, [r0, #2368]
	mov	r8, r0
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1511
	ldr	r2, [r0, #2372]
	ldrb	r1, [r2, #21]	@ zero_extendqisi2
	cmp	r1, #0
	addne	r3, r2, #256
	strne	r3, [fp, #-48]
	beq	.L1528
.L1513:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1514
	ldr	r10, .L1529
	mov	r2, #1536
	mov	r1, #0
	add	r0, r8, #608
	add	r7, r8, #2208
	mov	r6, #0
	ldr	r3, [r10, #48]
	add	r7, r7, #12
	blx	r3
	ldr	r9, [fp, #-48]
.L1516:
	ldr	r3, [r7, #4]!
	cmp	r3, #0
	movne	r5, r9
	movne	r4, #0
	beq	.L1519
.L1517:
	mov	r3, r4
	mov	r1, r5
	mov	r2, r6
	mov	r0, r8
	bl	HEVC_CalScalingList
	ldr	r3, [r7]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1517
.L1519:
	add	r6, r6, #1
	add	r9, r9, #384
	cmp	r6, #4
	bne	.L1516
	ldr	r2, [fp, #-48]
	add	r0, r8, #2240
	ldr	r3, [r10, #52]
	add	r1, r2, #1536
	mov	r2, #96
	blx	r3
.L1511:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1528:
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	cmp	r2, #0
	addne	r3, r3, #432
	strne	r3, [fp, #-48]
	bne	.L1513
.L1514:
	mov	r0, r8
	bl	HEVC_SetDefaultScalingList
	b	.L1511
.L1530:
	.align	2
.L1529:
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
	b	.L1532
.L1534:
	.word	.L1538
	.word	.L1536
	.word	.L1536
	.word	.L1537
.L1536:
	ldr	r3, .L1542
	cmp	r1, #2
	add	r0, r3, #64
	movhi	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1538:
	ldr	r0, .L1542+4
	ldmfd	sp, {fp, sp, pc}
.L1537:
	ldr	r3, .L1542
	cmp	r1, #0
	add	r0, r3, #64
	movne	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1532:
	ldr	r1, .L1542+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1543:
	.align	2
.L1542:
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
	bne	.L1554
	sub	r2, r3, #1
	mov	r4, #1
	movs	r2, r2, asr #1
	beq	.L1546
.L1547:
	movs	r2, r2, asr #1
	add	r4, r4, #1
	bne	.L1547
.L1546:
	mov	r1, #1
	ldr	r0, [r6, #2336]
	bl	BsGet
	cmp	r5, #1
	movls	r10, #0
	movhi	r10, #1
	uxtb	r0, r0
	strb	r0, [r8]
	cmp	r0, #0
	cmpne	r5, #1
	bls	.L1551
	ldr	r3, [r7, #76]
	cmp	r3, #0
	beq	.L1551
	mov	r9, r8
	mov	r5, #0
.L1552:
	mov	r1, r4
	ldr	r0, [r6, #2336]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r9, #4]!
	ldr	r3, [r7, #76]
	cmp	r3, r5
	bhi	.L1552
.L1551:
	ldr	r5, [r7, #20]
	cmp	r5, #0
	beq	.L1569
.L1550:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1569:
	mov	r1, #1
	ldr	r0, [r6, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #1]
	cmp	r0, #0
	moveq	r10, #0
	andne	r10, r10, #1
	cmp	r10, #0
	beq	.L1550
	ldr	r3, [r7, #80]
	cmp	r3, #0
	beq	.L1550
	add	r8, r8, #128
.L1553:
	mov	r1, r4
	ldr	r0, [r6, #2336]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r8, #4]!
	ldr	r3, [r7, #80]
	cmp	r3, r5
	bhi	.L1553
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1554:
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
	ldr	r0, [r0, #2336]
	bl	BsResidBits
	cmp	r0, #0
	ble	.L1572
	ldr	r3, [r4, #2356]
	ldr	r3, [r3, #12]
	add	r3, r3, #3
	cmp	r0, r3
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1572:
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
	ldr	r0, [r0, #2336]
	ldr	r2, [r0, #16]
	ldr	r3, [r0, #24]
	mov	r2, r2, asl #3
	cmp	r2, r3
	bls	.L1576
	mov	r1, #8
	bl	BsShow
	subs	r0, r0, #128
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1576:
	ldr	r1, .L1577
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1578:
	.align	2
.L1577:
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
.L1591:
	ldr	r1, [r6, #2356]
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
.L1580:
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r5, r7, r0
	add	r2, r1, r5
	cmp	r4, #0
	bne	.L1592
	ldr	lr, [r1, #40]
	add	ip, ip, #1
	cmp	lr, r3
	beq	.L1593
	ldr	lr, [r2, #40]
	cmp	lr, r3
	sub	r3, r3, #1
	bne	.L1580
	ldr	r1, [r2, #64]
	ldr	r0, [r6, #252]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r6, #2356]
	mov	ip, r4
	add	r5, r3, r5
	str	r4, [r5, #40]
	ldr	r2, [r6, #2356]
	ldr	r3, [r2, #8]
	sub	r3, r3, #1
	str	r3, [r2, #8]
	b	.L1591
.L1592:
	tst	r4, #1
	mov	r3, #1
	moveq	r2, r3
	bne	.L1587
.L1588:
	ands	r0, r4, r2, asl r3
	add	r3, r3, #1
	bne	.L1587
	cmp	r3, #8
	bne	.L1588
	ldr	r1, .L1594
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1593:
	ldr	r1, .L1594+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1587:
	mov	r0, #0
	str	r0, [r1, #4]
	ldr	r2, [r6, #2356]
	add	ip, r3, ip, lsl #3
	str	ip, [r2, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1595:
	.align	2
.L1594:
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
	blt	.L1597
	add	r6, r5, #1
	mov	r0, r3
	mov	r1, r6
	bl	__aeabi_uidivmod
	ldr	r7, [r8, #2380]
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1598
	mov	r4, #0
	b	.L1600
.L1601:
	bl	__aeabi_uidivmod
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1598
.L1600:
	add	r4, r4, #1
	mov	r1, r6
	cmp	r4, r5
	add	r0, r3, r4
	ble	.L1601
.L1597:
	mvn	r0, #0
	str	r3, [r8, #148]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1598:
	cmp	r3, r6
	mov	r0, r3
	str	r3, [r8, #148]
	bcs	.L1611
	rsb	r1, r1, ip
	mov	r3, #1
	add	r7, r7, r1
	str	r3, [r7, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1611:
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
	beq	.L1620
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	str	r3, [r5, #32]
	str	r3, [r5, #36]
.L1615:
	ldr	r3, [r4, #40]
	mov	r0, r6
	cmp	r3, #0
	beq	.L1614
	ldr	r1, [r4, #64]
	bl	SM_ReleaseStreamSeg
	ldr	ip, [r4, #44]
	ldr	r3, [r4, #40]
	mov	r0, #7
	ldr	r2, .L1621
	ldr	r1, .L1621+4
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #40]
	str	r3, [r4, #56]
	str	r3, [r4, #44]
.L1614:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L1615
	ldr	r3, .L1621+8
	mov	r0, r5
	mov	r2, #96
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1620:
	mov	r0, r5
	movw	r3, #14320
	ldr	r2, .L1621+12
	ldr	r1, .L1621+16
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1622:
	.align	2
.L1621:
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
	ldr	r3, [r0, #2368]
	mov	r7, r0
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r0, #2564]
	cmp	r3, #17
	bhi	.L1658
.L1624:
	add	r0, r7, #2784
	add	r1, r7, #2640
	add	r2, r7, #2576
	mov	lr, #0
	add	r0, r0, #4
	add	r1, r1, #12
	add	r2, r2, #8
	add	ip, r7, #2720
	mov	r3, lr
	mov	r6, #17
	str	lr, [r7, #2568]
	str	lr, [r7, #2580]
	str	lr, [r7, #2584]
	str	lr, [r7, #2576]
	str	lr, [r7, #2572]
.L1625:
	subs	r6, r6, #1
	str	r3, [r0, #4]!
	str	r3, [r1, #4]!
	str	r3, [ip, #4]!
	str	r3, [r2, #4]!
	bne	.L1625
	add	r4, r7, #12736
	ldr	r9, .L1659
	add	r4, r4, #56
.L1626:
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
	ldr	r3, .L1659
	bne	.L1626
	add	r0, r7, #12480
	ldr	r3, [r3, #48]
	mov	r2, #200
	mov	r1, r5
	add	r0, r0, #32
	blx	r3
	add	r2, r7, #2384
	add	r3, r7, #2448
	add	r1, r7, #12288
	add	r2, r2, #8
	add	r3, r3, #12
	mov	r0, r5
	str	r8, [r1, #224]
	str	r5, [r1, #228]
.L1628:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L1628
	add	lr, r7, #4096
	add	ip, r7, #2528
	mov	r0, r1
	str	r1, [lr, #164]
.L1629:
	str	r0, [r3, #4]!
	cmp	r3, ip
	mov	r2, #0
	bne	.L1629
	str	r2, [lr, #168]
	ldr	r0, [r7, #184]
	cmp	r0, r2
	addne	r1, r7, #2128
	movne	r3, r2
	addne	r1, r1, #12
	movne	r2, r3
	beq	.L1634
.L1633:
	add	r3, r3, #1
	str	r2, [r1, #4]!
	cmp	r3, r0
	bne	.L1633
.L1634:
	ldr	r2, [r7, #168]
	cmp	r2, #0
	movne	r4, #0
	movne	r5, r4
	beq	.L1623
.L1639:
	ldr	r3, [r7, #2376]
	mov	r6, r4, asl #2
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L1635
	ldr	r3, [r7, #2356]
	cmp	r1, r3
	beq	.L1635
	ldr	r0, [r7, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r7, #2376]
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
.L1635:
	add	r4, r4, #1
	cmp	r2, r4
	bhi	.L1639
.L1623:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1658:
	mov	r4, #17
	ldr	r2, .L1659+4
	str	r4, [sp]
	mov	r3, r4
	ldr	r1, .L1659+8
	mov	r0, #1
	bl	dprint_vfmw
	str	r4, [r7, #2564]
	b	.L1624
.L1660:
	.align	2
.L1659:
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
	beq	.L1671
	ldr	ip, [r6, #2568]
	add	r8, r6, #2576
	cmp	ip, #0
	addeq	r8, r8, #8
	beq	.L1663
	add	r8, r8, #8
	mov	r3, #0
	mov	lr, #1
	mov	r1, r8
.L1665:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	streqb	lr, [r2, #2]
	ldreq	ip, [r6, #2568]
	cmp	ip, r3
	bhi	.L1665
.L1663:
	mov	r4, r6
	mov	r7, #17
	mov	r5, #0
	mov	r3, #-2147483647
	str	r3, [r6, #212]
.L1670:
	ldr	r3, [r8, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L1666
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1666:
	ldr	r3, [r4, #2656]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1667
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1667:
	ldr	r3, [r4, #2724]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1668
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1668:
	ldr	r3, [r4, #2792]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1669
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1669:
	subs	r7, r7, #1
	str	r5, [r4, #2792]
	str	r5, [r4, #2724]
	add	r4, r4, #4
	str	r5, [r4, #2652]
	str	r5, [r4, #2584]
	bne	.L1670
	mov	r0, r6
	bl	HEVC_InitDecBuffers
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1671:
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
	ldr	r0, [r0, #2356]
	cmp	r0, #0
	beq	.L1693
	ldr	r3, [r0, #44]
	cmp	r3, #4096
	ldmcsfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L1694
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r3, [r4, #2356]
	ldr	ip, .L1694+4
	mov	r5, #0
	ldr	r2, [r3, #44]
	ldr	r0, [r3, #68]
	ldr	r1, [r3, #40]
	rsb	r0, r2, r0
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #2356]
	mov	r0, #1
	ldr	r2, [r3, #92]
	ldr	r1, [r3, #64]
	str	r2, [r3, #64]
	ldr	r3, [r4, #2356]
	str	r5, [r3, #56]
	ldr	r3, [r4, #2356]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #68]
	rsb	r2, ip, r2
	str	r2, [r3, #40]
	ldr	r3, [r4, #2356]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #76]
	rsb	r2, ip, r2
	str	r2, [r3, #48]
	ldr	r3, [r4, #2356]
	ldr	r2, [r3, #44]
	ldr	ip, [r3, #72]
	add	r2, r2, ip
	str	r2, [r3, #44]
	ldr	r3, [r4, #2356]
	str	r0, [r3, #8]
	ldr	r0, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #2356]
	str	r5, [r3, #68]
	ldr	r3, [r4, #2356]
	str	r5, [r3, #84]
	ldr	r3, [r4, #2356]
	str	r5, [r3, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1693:
	ldr	r1, .L1694+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1695:
	.align	2
.L1694:
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
	beq	.L1701
	ldr	ip, [r0, #2568]
	cmp	ip, #0
	beq	.L1701
	ldr	r3, [r0, #2588]
	cmp	r3, r1
	beq	.L1703
	add	r0, r0, #2576
	mov	r3, #0
	add	r0, r0, #12
	b	.L1698
.L1699:
	ldr	r2, [r0, #4]!
	cmp	r2, r1
	beq	.L1703
.L1698:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1699
.L1701:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1703:
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
	bls	.L1710
	movw	r0, #61166
	movt	r0, 65535
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1710:
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
	ldr	r1, .L1733
	mov	r4, r0
	ldr	r0, [r0, #2336]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2336]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	beq	.L1730
.L1716:
	mov	r1, #32
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r0, [r4, #2336]
	mov	r1, #32
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1730:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	mov	r6, r0
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r0, #8
	mov	r7, r0
	bhi	.L1731
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r0, #4
	ldrls	pc, [pc, r0, asl #2]
	b	.L1727
.L1715:
	.word	.L1716
	.word	.L1716
	.word	.L1717
	.word	.L1718
	.word	.L1719
.L1718:
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r0, #256
	mov	r8, r0
	bhi	.L1723
	cmp	r0, #0
	beq	.L1727
	add	r6, r6, #7
	add	r7, r7, #7
	bic	r6, r6, #7
	bic	r7, r7, #7
	mov	r5, #0
.L1725:
	mov	r1, r6
	ldr	r0, [r4, #2336]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, r7
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r5, r8
	bne	.L1725
.L1727:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1717:
	mov	r2, #1
	movs	r7, r2, asl r7
	addne	r6, r6, #7
	movne	r5, #0
	bicne	r6, r6, #7
	beq	.L1727
.L1721:
	add	r5, r5, #1
	mov	r1, r6
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r7, r5
	bne	.L1721
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1719:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r0, #255
	beq	.L1732
.L1726:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r0, [r4, #2336]
	mov	r1, #16
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1732:
	mov	r1, #32
	ldr	r0, [r4, #2336]
	bl	BsGet
	b	.L1726
.L1731:
	mov	r2, r0
	ldr	r1, .L1733+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1723:
	ldr	r1, .L1733+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1734:
	.align	2
.L1733:
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
	ldr	r1, .L1745
	mov	r4, r0
	ldr	r0, [r0, #2336]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2336]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	bne	.L1736
	mov	r1, #7
	ldr	r0, [r4, #2336]
	bl	BsGet
	sub	r3, r0, #3
	mov	r6, r0
	cmp	r3, #2
	bhi	.L1743
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #6
	mov	r5, r0
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	uxtb	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	clz	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	mov	r5, r5, lsr #5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r6, #5
	moveq	r5, #0
	cmp	r5, #0
	bne	.L1744
.L1739:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
.L1736:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r0, [r4, #2336]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1744:
	mov	r1, #4
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2336]
	bl	BsGet
	b	.L1739
.L1743:
	mov	r2, r0
	ldr	r1, .L1745+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1746:
	.align	2
.L1745:
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
	bne	.L1751
	ldr	r1, .L1760
	ldr	r0, [r0, #2336]
	bl	HEVC_ue_v
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1758
.L1749:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	bne	.L1759
.L1750:
	ldr	r0, [r4, #2336]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1758:
	ldr	r1, [r5, #4]
	ldr	r0, [r4, #2336]
	add	r1, r1, #1
	bl	BsGet
	b	.L1749
.L1759:
	ldr	r1, [r5, #8]
	ldr	r0, [r4, #2336]
	add	r1, r1, #1
	bl	BsGet
	b	.L1750
.L1751:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1761:
	.align	2
.L1760:
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
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldr	r0, [r5, #2336]
	ldr	r1, .L1769
	bl	HEVC_ue_v
	cmp	r0, #15
	bgt	.L1763
	cmp	r0, #0
	addge	r6, r0, #1
	movge	r4, #0
	blt	.L1767
.L1766:
	add	r4, r4, #1
	ldr	r1, .L1769+4
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r4, r6
	bne	.L1766
.L1767:
	ldr	r0, [r5, #2336]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1763:
	ldr	r1, .L1769+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1770:
	.align	2
.L1769:
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
	ldr	r1, .L1800
	mov	r7, r2
	str	r6, [r4, #2912]
	ldr	r0, [r0, #2336]
	bl	HEVC_ue_v
	cmp	r0, #15
	bhi	.L1796
	mov	r1, #1
	strb	r1, [r4, #2905]
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r8, r6
	beq	.L1797
.L1774:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r4, #1
	strb	r0, [r9]
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2336]
	add	r1, r1, r4
	bl	BsGet
	subs	r3, r4, #1
	beq	.L1798
.L1776:
	cmp	r3, #1
	beq	.L1799
.L1780:
	cmp	r4, #1
	bhi	.L1779
.L1778:
	add	r4, r4, #1
	subs	r3, r4, #1
	bne	.L1776
.L1798:
	ldrb	r2, [r7]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1780
	ldr	r2, [r7, #24]
	cmn	r2, #1
	beq	.L1778
.L1787:
	mov	r6, #0
	b	.L1783
.L1782:
	ldr	r3, [r7, #24]
	add	r3, r3, #1
	cmp	r3, r6
	bls	.L1780
.L1783:
	ldr	r1, [r7, #12]
	add	r6, r6, #1
	ldr	r0, [r5, #2336]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2336]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	orrs	r3, r8, r3
	beq	.L1782
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2336]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2336]
	add	r1, r1, #1
	bl	BsGet
	b	.L1782
.L1799:
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1779
	ldr	r3, [r7, #24]
	cmn	r3, #1
	bne	.L1787
.L1779:
	ldr	r0, [r5, #2336]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1797:
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r8, r0
	cmp	r8, #0
	beq	.L1774
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2336]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #20]
	ldr	r0, [r5, #2336]
	add	r1, r1, #1
	bl	BsGet
	b	.L1774
.L1796:
	mov	r2, r0
	ldr	r1, .L1800+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1801:
	.align	2
.L1800:
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
	ldr	r1, [r3, #2908]
	ldr	r2, [r3, #2912]
	add	r1, r1, #1
	str	r1, [r3, #2908]
	add	r2, r2, #1
	str	r2, [r3, #2912]
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1830
.L1803:
	ldrh	r3, [r5, #44]
	cmp	r3, #0
	beq	.L1805
	ldr	r1, [r5, #60]
	ldr	r0, [r4, #2336]
	add	r1, r1, #1
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r6, #8]
	ldr	r1, [r5, #64]
	ldr	r0, [r4, #2336]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #12]
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1806
.L1809:
	ldr	r2, [r4, #252]
	ldr	r3, .L1833
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L1831
.L1805:
	ldr	r0, [r4, #2336]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1830:
	mov	r1, #4
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r1, #2
	str	r0, [r6]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #4]
	ldr	r0, [r4, #2336]
	bl	BsGet
	b	.L1803
.L1831:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L1805
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L1805
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_Sei_Get_Dpb_Output_Time
	b	.L1805
.L1806:
	ldr	r1, [r5, #52]
	ldr	r0, [r4, #2336]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1809
	ldrb	r3, [r5, #47]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1809
	ldr	r1, .L1833+4
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	mov	r1, #1
	mov	r7, r0
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r8, r0
	cmp	r8, #0
	bne	.L1832
.L1810:
	cmp	r7, #255
	bhi	.L1814
	add	r7, r7, #1
	mov	r6, #0
	b	.L1813
.L1812:
	cmp	r6, r7
	beq	.L1809
.L1813:
	ldr	r1, .L1833+8
	add	r6, r6, #1
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	cmp	r8, #0
	bne	.L1812
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2336]
	add	r1, r1, #1
	bl	BsGet
	b	.L1812
.L1832:
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2336]
	add	r1, r1, #1
	bl	BsGet
	b	.L1810
.L1814:
	ldr	r1, .L1833+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1834:
	.align	2
.L1833:
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
	beq	.L1845
	ldr	r1, .L1849
	ldr	r0, [r0, #2336]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	beq	.L1837
.L1841:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r5]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1837:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L1848
.L1838:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #3]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #4]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #5]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #6]
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #7]
	addne	r7, r5, #7
	movne	r6, #0
	beq	.L1843
.L1842:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2336]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L1842
.L1843:
	mov	r1, #4
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #38]
	addne	r7, r5, #38
	movne	r6, #0
	beq	.L1841
.L1844:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2336]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #38]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L1844
	b	.L1841
.L1845:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1848:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #1]
	ldr	r0, [r4, #2336]
	bl	BsGet
	b	.L1838
.L1850:
	.align	2
.L1849:
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
	beq	.L1858
	cmp	r2, #3
	bls	.L1861
	mov	r1, #8
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #2
	beq	.L1862
	cmp	r0, #4
	beq	.L1863
	subs	r6, r6, #4
	beq	.L1857
.L1856:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r6, r4
	bne	.L1856
.L1857:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1862:
	add	r1, r5, #2912
	mov	r0, r5
	add	r1, r1, #8
	bl	HEVC_Sei_TSI
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1863:
	add	r1, r5, #2912
	mov	r0, r5
	add	r1, r1, #11
	bl	HEVC_Sei_Color_Volume_Reconstruction_Info
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1858:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1861:
	ldr	r1, .L1864
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1865:
	.align	2
.L1864:
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
	bne	.L1911
.L1867:
	ldr	r1, .L1920
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4]
	bhi	.L1912
	ldr	r1, .L1920+4
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4, #4]
	bhi	.L1913
	ldr	r6, [r4]
	add	r2, r0, r6
	str	r2, [r4, #8]
	cmp	r2, #16
	bhi	.L1890
	cmp	r6, #0
	addne	r10, r4, #28
	addne	r9, r4, #11
	movne	r7, #0
	movne	r8, r7
	bne	.L1894
	b	.L1892
.L1893:
	str	r8, [r10, #4]!
	ldr	r0, [r5, #2336]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r6, [r4]
	cmp	r6, r7
	bls	.L1914
.L1894:
	ldr	r1, .L1920+8
	add	r7, r7, #1
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	mov	r1, #1
	cmp	r0, #32768
	mvn	r3, r0
	add	r8, r8, r3
	bcc	.L1893
	mov	r2, r0
	ldr	r1, .L1920+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1911:
	mov	r1, #1
	ldr	r0, [r0, #2336]
	bl	BsGet
	cmp	r0, #0
	beq	.L1867
	ldr	r7, [r9, #176]
	cmp	r7, r6
	movne	r0, #0
	beq	.L1915
.L1868:
	sub	r3, r6, #1
	rsb	r8, r0, r3
	cmp	r8, r3
	bhi	.L1916
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldr	r1, .L1920+16
	mov	r6, r0
	ldr	r0, [r5, #2336]
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
	bhi	.L1917
	add	r6, r8, #2192
	mov	r10, #0
	add	r6, r6, #4
	str	r10, [fp, #-48]
	add	r6, r9, r6
	str	r10, [fp, #-52]
	mov	r7, r10
	b	.L1877
.L1872:
	sub	r3, r0, #1
	cmp	r3, #1
	bls	.L1918
.L1873:
	add	r3, r9, r8
	add	r10, r10, #1
	add	r6, r6, #4
	ldr	r3, [r3, #2172]
	cmp	r3, r10
	bcc	.L1919
.L1877:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r0, #0
	bne	.L1872
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r0, r0, asl #1
	sub	r3, r0, #1
	cmp	r3, #1
	bhi	.L1873
.L1918:
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
	b	.L1873
.L1919:
	ldr	r3, [fp, #-52]
	cmp	r7, #16
	ldr	r2, [fp, #-48]
	str	r7, [r4, #8]
	str	r3, [r4]
	str	r2, [r4, #4]
	bhi	.L1878
	cmp	r3, #16
	bhi	.L1878
	cmp	r2, #16
	bhi	.L1878
	cmp	r7, #1
	subhi	r7, r7, #1
	addhi	r8, r4, #32
	addhi	r6, r4, #12
	movhi	r5, #0
	bls	.L1884
.L1883:
	ldr	ip, [r8, #4]!
	cmp	r5, #0
	ldrb	lr, [r6, #1]!	@ zero_extendqisi2
	mov	r2, r5
	movge	r1, r8
	movge	r3, r6
	blt	.L1886
.L1882:
	ldr	r0, [r1, #-4]!
	sub	r3, r3, #1
	cmp	ip, r0
	strlt	r0, [r1, #4]
	ldrltb	r0, [r3]	@ zero_extendqisi2
	strltb	r0, [r3, #1]
	strlt	ip, [r1]
	strltb	lr, [r3]
	subs	r2, r2, #1
	bpl	.L1882
.L1886:
	add	r5, r5, #1
	cmp	r5, r7
	bne	.L1883
.L1884:
	ldr	r3, [fp, #-52]
	movs	r6, r3, lsr #1
	beq	.L1881
	ldr	r3, [fp, #-52]
	add	r0, r4, #28
	mov	r1, #0
	add	r2, r3, #7
	add	r3, r3, #11
	add	r3, r4, r3
	mov	ip, r0
	add	r2, r4, r2, lsl #2
	add	r4, r4, #12
.L1887:
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
	bne	.L1887
.L1881:
	mov	r0, #0
.L1869:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1914:
	ldr	r2, [r4, #8]
.L1892:
	cmp	r2, r6
	bls	.L1881
	add	r8, r6, #7
	add	r9, r6, #11
	add	r9, r4, r9
	mov	r7, #0
	add	r8, r4, r8, lsl #2
.L1895:
	ldr	r1, .L1920+20
	add	r6, r6, #1
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	mov	r1, #1
	add	r0, r0, r1
	add	r7, r7, r0
	str	r7, [r8, #4]!
	ldr	r0, [r5, #2336]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r3, [r4, #8]
	cmp	r3, r6
	bhi	.L1895
	b	.L1881
.L1915:
	ldr	r1, .L1920+24
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	add	r2, r0, #1
	cmp	r7, r2
	bcs	.L1868
	mov	r3, r7
	ldr	r1, .L1920+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1869
.L1878:
	ldr	r1, .L1920+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1869
.L1913:
	ldr	r2, [r4]
	mov	r0, #1
	ldr	r1, .L1920+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1869
.L1916:
	mov	r2, r8
	ldr	r1, .L1920+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1869
.L1917:
	ldr	r1, .L1920+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1869
.L1912:
	mov	r2, r0
	ldr	r1, .L1920+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1869
.L1890:
	mov	r3, #16
	ldr	r1, .L1920+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1869
.L1921:
	.align	2
.L1920:
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
	beq	.L1944
	cmp	r2, #0
	bne	.L1971
.L1927:
	add	r5, r9, #24
	mov	r7, #0
.L1939:
	mov	r1, #1
	ldr	r0, [r6, #2336]
	bl	BsGet
	uxtb	r4, r0
	cmp	r4, #0
	movne	r3, #0
	strne	r3, [r5]
	beq	.L1972
.L1942:
	ldr	r1, .L1977
	ldr	r0, [r6, #2336]
	bl	HEVC_ue_v
.L1930:
	ldr	r1, .L1977+4
	ldr	r0, [r6, #2336]
	bl	HEVC_ue_v
	mov	r2, r0
	str	r0, [r5]
.L1931:
	cmp	r2, #31
	bhi	.L1973
.L1932:
	mov	r4, #0
.L1943:
	cmp	r4, #0
	beq	.L1974
	cmp	r4, #1
	beq	.L1969
.L1938:
	add	r4, r4, #1
	cmp	r4, #2
	bne	.L1943
.L1937:
	add	r7, r7, #1
	add	r5, r5, #4
	cmp	r8, r7
	bcs	.L1939
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1973:
	ldr	r1, .L1977+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5]
	b	.L1932
.L1972:
	mov	r1, #1
	ldr	r0, [r6, #2336]
	bl	BsGet
	str	r4, [r5]
	tst	r0, #255
	bne	.L1942
	mov	r1, #1
	ldr	r0, [r6, #2336]
	bl	BsGet
	tst	r0, #255
	beq	.L1930
	ldr	r2, [r5]
	b	.L1931
.L1971:
	mov	r1, #1
	ldr	r0, [r0, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r6, #2336]
	bl	BsGet
	strb	r0, [r9, #1]
	ldrh	r3, [r9]
	cmp	r3, #0
	beq	.L1927
	mov	r1, #1
	ldr	r0, [r6, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r9, #2]
	cmp	r0, #0
	bne	.L1975
.L1925:
	mov	r1, #4
	ldr	r0, [r6, #2336]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r6, #2336]
	bl	BsGet
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1976
.L1926:
	mov	r1, #5
	ldr	r0, [r6, #2336]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #12]
	ldr	r0, [r6, #2336]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #16]
	ldr	r0, [r6, #2336]
	bl	BsGet
	str	r0, [r9, #20]
	b	.L1927
.L1944:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1976:
	mov	r1, #4
	ldr	r0, [r6, #2336]
	bl	BsGet
	b	.L1926
.L1975:
	mov	r1, #8
	ldr	r0, [r6, #2336]
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r6, #2336]
	bl	BsGet
	mov	r1, #1
	str	r0, [r9, #4]
	ldr	r0, [r6, #2336]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r9, #3]
	ldr	r0, [r6, #2336]
	bl	BsGet
	str	r0, [r9, #8]
	b	.L1925
.L1974:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1946
	mov	r4, #1
.L1969:
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1937
.L1946:
	mov	r10, #0
	b	.L1941
.L1940:
	mov	r1, #1
	ldr	r0, [r6, #2336]
	bl	BsGet
	ldr	r3, [r5]
	cmp	r3, r10
	bcc	.L1938
.L1941:
	ldr	r1, .L1977+12
	add	r10, r10, #1
	ldr	r0, [r6, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L1977+16
	ldr	r0, [r6, #2336]
	bl	HEVC_ue_v
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1940
	ldr	r1, .L1977+20
	ldr	r0, [r6, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L1977+24
	ldr	r0, [r6, #2336]
	bl	HEVC_ue_v
	b	.L1940
.L1978:
	.align	2
.L1977:
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
	ldr	r0, [r0, #2336]
	mov	r1, #1
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3]
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r2, r0
	cmp	r2, #1
	beq	.L1980
	ldr	r1, .L2031
	mov	r0, #1
	bl	dprint_vfmw
.L1980:
	mov	r1, #6
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r0, #63
	str	r0, [r6, #8]
	bhi	.L2024
	mov	r1, #3
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r0, #7
	mov	r7, r0
	bhi	.L2025
	str	r0, [r6, #12]
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r6, #1]
	ldr	r0, [r5, #2336]
	bl	BsGet
	movw	r3, #65535
	cmp	r0, r3
	bne	.L2026
	mov	r3, r7
	mov	r2, #1
	add	r1, r6, #124
	mov	r0, r5
	bl	HEVC_DecPTL
	subs	r4, r0, #0
	bne	.L2027
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r7, #0
	addge	r8, r6, #24
	addge	r9, r7, #1
	uxtb	r10, r0
	bge	.L1992
	b	.L1990
.L1989:
	add	r4, r4, #1
	cmp	r4, r9
	beq	.L1990
.L1992:
	ldr	r1, .L2031+4
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L2031+8
	add	r0, r0, #1
	str	r0, [r8, #4]!
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L2031+12
	str	r0, [r8, #32]
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r10, #0
	str	r0, [r8, #64]
	bne	.L1989
	add	r2, r4, #1
	cmp	r7, r2
	blt	.L1990
	add	r3, r4, #7
	add	r3, r6, r3, lsl #2
.L1991:
	ldr	r1, [r6, #28]
	add	r2, r2, #1
	cmp	r9, r2
	str	r1, [r3, #4]!
	ldr	r1, [r6, #60]
	str	r1, [r3, #32]
	ldr	r1, [r6, #92]
	str	r1, [r3, #64]
	bne	.L1991
.L1990:
	mov	r1, #6
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldr	r1, .L2031+16
	str	r0, [r6, #16]
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r6, #20]
	bcs	.L2028
	cmp	r0, #0
	movgt	r8, #1
	ble	.L1994
.L1996:
	mov	r4, #0
.L1995:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldr	r3, [r6, #16]
	add	r4, r4, #1
	cmp	r4, r3
	bls	.L1995
	ldr	r3, [r6, #20]
	add	r8, r8, #1
	cmp	r3, r8
	bge	.L1996
.L1994:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	tst	r0, #255
	beq	.L2003
	mov	r1, #32
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	tst	r0, #255
	bne	.L2029
.L2000:
	ldr	r1, .L2031+20
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r6, #24]
	bhi	.L2001
	cmp	r0, #0
	ble	.L2003
	ldr	r1, .L2031+24
	mov	r4, #0
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	mov	r0, #1
.L2008:
	uxtb	r2, r0
	sub	r1, fp, #100
	mov	r3, r7
	mov	r0, r5
	bl	HEVC_DecHrdParam
	add	r4, r4, #1
	ldr	r1, .L2031+24
	cmp	r0, #0
	bne	.L2030
	ldr	r3, [r6, #24]
	cmp	r3, r4
	ble	.L2003
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r4, #0
	mov	r0, #1
	beq	.L2008
	mov	r1, r0
	ldr	r0, [r5, #2336]
	bl	BsGet
	b	.L2008
.L2003:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	tst	r0, #255
	bne	.L2020
.L1999:
	mov	r0, #0
.L2021:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2007:
	ldr	r0, [r5, #2336]
	bl	BsGet
.L2020:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2007
	b	.L1999
.L2030:
	ldr	r1, .L2031+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2029:
	ldr	r1, .L2031+32
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	b	.L2000
.L2026:
	ldr	r1, .L2031+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2021
.L2024:
	mov	r2, r0
	ldr	r1, .L2031+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2021
.L2027:
	ldr	r1, .L2031+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2021
.L2025:
	mov	r2, r0
	ldr	r1, .L2031+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2021
.L2028:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L2031+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2021
.L2001:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L2031+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2021
.L2032:
	.align	2
.L2031:
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
	ldr	r5, .L2045
	mov	r6, r0
	ldr	r0, [r5]
	cmp	r0, #0
	beq	.L2040
	mov	r1, #4
	ldr	r0, [r6, #2336]
	bl	BsGet
	cmp	r0, #15
	mov	r7, r0
	bhi	.L2041
	ldr	r3, [r6, #2340]
	mov	r4, r0, asl #7
	add	r4, r4, r0, lsl #2
	add	r2, r3, r4
	ldrb	r9, [r3, r4]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L2042
	str	r0, [r2, #4]
	mov	r0, r6
	ldr	r1, [r6, #2340]
	add	r1, r1, r4
	bl	HEVC_ProcessVPS
	subs	r8, r0, #0
	bne	.L2043
	ldr	r3, [r6, #2340]
	mov	r2, #1
	add	r3, r3, r4
	strb	r2, [r3, #2]
	ldr	r3, [r6, #2340]
	strb	r2, [r3, r4]
.L2035:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2042:
	ldr	r5, [r5]
	mov	r2, #132
	ldr	r9, .L2045+4
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
	bne	.L2044
	mov	r3, #1
	strb	r3, [r5, #2]
	strb	r3, [r5]
	mov	r1, r5
	ldr	r0, [r6, #2340]
	mov	r2, #132
	ldr	r3, [r9, #56]
	add	r0, r0, r4
	blx	r3
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2044:
	mov	r2, r7
	ldr	r1, .L2045+8
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L2035
.L2041:
	ldr	r1, .L2045+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L2035
.L2043:
	mov	r2, r7
	ldr	r1, .L2045+16
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	ldr	r3, [r6, #2340]
	mov	r2, #1
	add	r3, r3, r4
	strb	r2, [r3, #2]
	ldr	r3, [r6, #2340]
	strb	r9, [r3, r4]
	b	.L2035
.L2040:
	ldr	r2, .L2045+20
	mvn	r8, #0
	ldr	r1, .L2045+24
	bl	dprint_vfmw
	b	.L2035
.L2046:
	.align	2
.L2045:
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
	ldr	r0, [r0, #2336]
	mov	r1, #1
	mov	r6, r2
	bl	BsGet
	tst	r0, #255
	bne	.L2091
.L2049:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	bne	.L2092
.L2051:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	bne	.L2093
.L2053:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	bne	.L2094
.L2055:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #3]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	beq	.L2056
	ldr	r1, .L2100
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r3, [r6, #60]
	cmp	r3, #3
	bhi	.L2095
	ldr	r1, .L2100+4
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L2100+8
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L2100+12
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
.L2056:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	beq	.L2059
	mov	r1, #32
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #32
	str	r0, [r5, #36]
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r2, [r5, #36]
	cmp	r2, #0
	str	r0, [r5, #40]
	bne	.L2096
.L2060:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	bne	.L2097
.L2061:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	bne	.L2098
.L2059:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r1, .L2100+16
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	cmp	r0, #4096
	bcs	.L2099
.L2062:
	ldr	r1, .L2100+20
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L2100+24
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L2100+28
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2336]
	ldr	r1, .L2100+32
	bl	HEVC_ue_v
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2091:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r0, #255
	str	r0, [r5, #8]
	bne	.L2049
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #16
	str	r0, [r5, #12]
	ldr	r0, [r4, #2336]
	bl	BsGet
	str	r0, [r5, #16]
	b	.L2049
.L2094:
	ldr	r1, .L2100+36
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L2100+40
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	b	.L2055
.L2093:
	mov	r1, #3
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #20]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5]
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	beq	.L2053
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #24]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #28]
	ldr	r0, [r4, #2336]
	bl	BsGet
	str	r0, [r5, #32]
	b	.L2053
.L2092:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	b	.L2051
.L2098:
	ldr	r3, [r6, #52]
	add	r1, r5, #44
	mov	r2, #1
	mov	r0, r4
	bl	HEVC_DecHrdParam
	cmp	r0, #0
	beq	.L2059
	ldr	r1, .L2100+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2097:
	ldr	r1, .L2100+48
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	b	.L2061
.L2096:
	ldr	r3, .L2100+52
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
	b	.L2060
.L2099:
	ldr	r1, .L2100+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2062
.L2095:
	ldr	r1, .L2100+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2101:
	.align	2
.L2100:
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
	bls	.L2107
	mvn	r0, #-2147483648
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2107:
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
	ldr	r1, .L2120
	mov	r6, r0
	ldr	r0, [r0, #2336]
	bl	HEVC_ue_v
	ldr	r0, [r6, #2336]
	ldr	r1, .L2120+4
	bl	HEVC_ue_v
	cmp	r0, #1024
	mov	r7, r0
	bhi	.L2109
	cmp	r0, #0
	movne	r4, #0
	beq	.L2115
.L2114:
	mov	r1, #6
	ldr	r0, [r6, #2336]
	bl	BsGet
	mov	r1, #3
	mov	r5, r0
	ldr	r0, [r6, #2336]
	sub	r5, r5, #19
	bl	BsGet
	cmp	r5, #1
	ldr	r1, .L2120+8
	bls	.L2112
	ldr	r0, [r6, #2336]
	bl	HEVC_ue_v
.L2112:
	cmp	r4, #0
	ldr	r1, .L2120+12
	add	r4, r4, #1
	beq	.L2113
	ldr	r0, [r6, #2336]
	bl	HEVC_se_v
.L2113:
	cmp	r4, r7
	bne	.L2114
.L2115:
	ldr	r0, [r6, #2336]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2109:
	ldr	r1, .L2120+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2121:
	.align	2
.L2120:
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
	beq	.L2124
	ldr	r1, .L2125
	ldr	r0, [r0, #2336]
	bl	HEVC_se_v
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r0, [r4, #2336]
	bl	BsToNextByte
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2124:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2126:
	.align	2
.L2125:
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
	beq	.L2144
	ldr	r1, .L2157
	ldr	r0, [r0, #2336]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	beq	.L2129
.L2142:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r8]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2129:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r1, r0
	cmp	r1, #1
	beq	.L2154
.L2130:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2336]
	mov	r7, #3
	bl	BsGet
.L2132:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	beq	.L2135
	add	r6, r0, #1
	mov	r5, #0
.L2134:
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r5, r6
	bne	.L2134
.L2135:
	subs	r7, r7, #1
	bne	.L2132
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L2155
.L2136:
	add	r10, r8, #42
	add	r7, r8, #39
	mov	r9, r10
.L2141:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #1]!
	cmp	r0, #32
	bhi	.L2156
	cmp	r0, #0
	beq	.L2143
	mov	r6, r9
	mov	r5, #0
.L2140:
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #16
	add	r5, r5, #1
	strh	r0, [r6, #2]!	@ movhi
	ldr	r0, [r4, #2336]
	bl	BsGet
	strh	r0, [r6, #198]	@ movhi
	ldrb	r3, [r7]	@ zero_extendqisi2
	add	r3, r3, #1
	cmp	r3, r5
	bhi	.L2140
.L2143:
	cmp	r10, r7
	add	r9, r9, #66
	bne	.L2141
	b	.L2142
.L2144:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2155:
	mov	r1, #4
	ldr	r0, [r4, #2336]
	bl	BsGet
	add	r7, r8, #36
	mov	r5, r8
.L2137:
	add	r6, r5, #12
.L2138:
	ldr	r1, .L2157+4
	ldr	r0, [r4, #2336]
	bl	HEVC_se_v
	str	r0, [r5, #4]!
	cmp	r6, r5
	bne	.L2138
	cmp	r5, r7
	bne	.L2137
	b	.L2136
.L2154:
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r8, #1]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	b	.L2130
.L2156:
	mov	r2, r0
	ldr	r1, .L2157+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2158:
	.align	2
.L2157:
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
	bne	.L2185
	ldr	lr, [r0, #2356]
	ldr	lr, [lr, #16]
	cmp	lr, #39
	beq	.L2203
	cmp	r3, #5
	beq	.L2189
	cmp	r3, #132
	beq	.L2190
	cmp	r6, #0
	beq	.L2184
.L2192:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r5, r6
	bne	.L2192
	b	.L2184
.L2189:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	bne	.L2185
.L2184:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_More_Data_In_Payload
	cmp	r0, #0
	bne	.L2193
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2193:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_Payload_Extension_Present
	cmp	r0, #0
	bne	.L2204
.L2194:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	b	.L2195
.L2196:
	ldr	r0, [r4, #2336]
	bl	BsGet
.L2195:
	ldr	r0, [r4, #2336]
	bl	BsIsByteAligned
	mov	r1, #1
	cmp	r0, #0
	beq	.L2196
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2203:
	cmp	r3, #147
	ldrls	pc, [pc, r3, asl #2]
	b	.L2163
.L2165:
	.word	.L2164
	.word	.L2166
	.word	.L2163
	.word	.L2163
	.word	.L2167
	.word	.L2168
	.word	.L2169
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2170
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2171
	.word	.L2163
	.word	.L2172
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2173
	.word	.L2174
	.word	.L2175
	.word	.L2176
	.word	.L2163
	.word	.L2177
	.word	.L2178
	.word	.L2163
	.word	.L2163
	.word	.L2179
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2163
	.word	.L2180
	.word	.L2163
	.word	.L2181
	.word	.L2163
	.word	.L2163
	.word	.L2182
.L2190:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Decoded_Picture_Hash
	cmp	r0, #0
	beq	.L2184
.L2185:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2204:
	ldr	r1, .L2205
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	b	.L2194
.L2182:
	add	r1, r1, #616
	add	r1, r1, #2
	bl	HEVC_Sei_HLGHDR_Comapitibility_Info
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2164:
	add	r2, r2, #2096
	add	r2, r2, #12
	bl	HEVC_Sei_Buf_Period
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2166:
	add	r2, r2, #2064
	add	r1, r1, #8
	bl	HEVC_Sei_Pic_Timming
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2167:
	add	r1, r1, #56
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Registered_Itu_T_T35
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2168:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2169:
	add	r1, r1, #568
	bl	HEVC_Sei_Recovery_Point
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2170:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Tone_Mapping_Info
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2171:
	add	r1, r1, #568
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2172:
	add	r1, r1, #568
	bl	HEVC_Sei_Display_Orientation
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2173:
	add	r1, r1, #616
	mov	r2, r6
	add	r1, r1, #3
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2174:
	add	r1, r1, #568
	bl	HEVC_Sei_Active_Param_sets
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2175:
	add	r2, r2, #2096
	add	r1, r1, #568
	add	r2, r2, #12
	bl	HEVC_Sei_Dec_Unit_Info
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2176:
	add	r1, r1, #568
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2177:
	mov	r3, r6
	bl	HEVC_Sei_Scalable_Nesting
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2178:
	cmn	r1, #568
	movne	r1, #0
	moveq	r1, #1
	orrs	r3, ip, r1
	bne	.L2185
	mov	r1, #1
	ldr	r0, [r0, #2336]
	bl	BsGet
	b	.L2184
.L2179:
	add	r1, r1, #568
	bl	HEVC_Sei_Mastering_Display_Colour_Volume
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2180:
	add	r1, r1, #128
	bl	HEVC_Sei_Color_Remapping_Info
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2181:
	add	r1, r1, #612
	bl	HEVC_Sei_Content_Light_Level_Information
	cmp	r0, #0
	beq	.L2184
	b	.L2185
.L2163:
	cmp	r6, #0
	movne	r5, #0
	beq	.L2184
.L2187:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r5, r6
	bne	.L2187
	b	.L2184
.L2206:
	.align	2
.L2205:
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
	ldr	r0, [r0, #2336]
	b	.L2208
.L2210:
	bl	BsSkip
	ldr	r0, [r4, #2336]
	add	r5, r5, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2, asl #3
	bhi	.L2216
.L2208:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2336]
	beq	.L2210
	bl	BsGet
	mov	r8, #0
	mov	r9, r0
	ldr	r0, [r4, #2336]
	b	.L2211
.L2212:
	bl	BsSkip
	ldr	r0, [r4, #2336]
	add	r8, r8, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2, asl #3
	bhi	.L2217
.L2211:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2336]
	beq	.L2212
	bl	BsGet
	add	r3, r9, r5
	mov	r2, r7
	mov	r1, r6
	add	r8, r0, r8
	mov	r0, r4
	str	r8, [sp]
	bl	HEVC_Sei_Payload
	cmp	r0, #0
	bne	.L2218
.L2209:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2216:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5039
	ldr	r1, .L2219
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2217:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5060
	ldr	r1, .L2219
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2218:
	ldr	r1, .L2219+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2209
.L2220:
	.align	2
.L2219:
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
	beq	.L2227
	ldr	r5, [r0, #2352]
	add	r6, r0, #2864
	cmp	r5, #0
	bne	.L2230
	b	.L2233
.L2225:
	ldr	r0, [r4, #2336]
	bl	BsIsByteAligned
	cmp	r0, #0
	mov	r0, r4
	beq	.L2234
	bl	HEVC_More_Rbsp_Data
	cmp	r0, #0
	beq	.L2235
.L2230:
	mov	r2, r5
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	beq	.L2225
	ldr	r1, .L2237
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2235:
	ldr	r0, [r4, #2336]
	mov	r1, #8
	bl	BsGet
	cmp	r0, #128
	bne	.L2236
.L2227:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2234:
	ldr	r1, .L2237+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2236:
	mov	r2, r0
	ldr	r1, .L2237+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2233:
	ldr	r1, .L2237+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2238:
	.align	2
.L2237:
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
	ldr	r0, [r0, #2336]
	mov	r1, #1
	mov	r7, r2
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	tst	r0, #255
	ldr	r0, [r4, #2336]
	beq	.L2240
	bl	BsGet
	ldr	r1, .L2256
	mov	r5, r0
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	cmp	r0, #63
	mov	r8, r0
	bhi	.L2253
	uxtb	r5, r5
	cmp	r0, r5
	bcc	.L2246
.L2245:
	mov	r1, #3
	ldr	r0, [r4, #2336]
	bl	BsGet
	add	r5, r5, #1
	ldr	r1, .L2256+4
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	cmp	r8, r5
	bcs	.L2245
.L2246:
	ldr	r0, [r4, #2336]
	bl	BsToNextByte
	b	.L2244
.L2249:
	bl	HEVC_MoreRbspData
	cmp	r0, #0
	beq	.L2254
.L2244:
	mov	r2, r7
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	mov	r0, r4
	beq	.L2249
	ldr	r1, .L2256+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2240:
	bl	BsGet
	uxtb	r5, r0
	cmp	r5, #0
	bne	.L2246
	mov	r1, #3
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r1, .L2256+12
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	cmp	r0, #63
	addls	r8, r0, #1
	bhi	.L2255
.L2248:
	add	r5, r5, #1
	mov	r1, #6
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r5, r8
	bne	.L2248
	b	.L2246
.L2254:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2253:
	mov	r2, #64
	ldr	r1, .L2256+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2255:
	ldr	r1, .L2256+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2257:
	.align	2
.L2256:
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
	ldr	r3, .L2299
	mov	r6, r0
	str	r1, [fp, #-60]
	ldr	r0, [r3]
	cmp	r0, #0
	beq	.L2293
	ldr	r3, .L2299+4
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
.L2261:
	ldr	r3, [r9, #4]!
	cmp	r3, #0
	beq	.L2281
	ldr	r2, [fp, #-48]
	ldr	r1, [fp, #-68]
	ldr	r7, [fp, #-64]
	mov	r3, r2, asl #3
	sub	r3, r3, r2, asl #1
	str	r1, [fp, #-56]
	str	r3, [fp, #-72]
	mov	r3, #0
	str	r3, [fp, #-52]
.L2280:
	mov	r1, #1
	ldr	r0, [r6, #2336]
	bl	BsGet
	ldr	r5, [r9, #-1888]
	ldr	r3, [fp, #-48]
	cmp	r5, #64
	movge	r5, #64
	cmp	r3, #0
	uxtb	r0, r0
	beq	.L2294
	cmp	r0, #0
	add	r4, r6, #352
	beq	.L2295
	ldr	r3, [fp, #-48]
	cmp	r3, #1
	bls	.L2286
	ldr	r1, .L2299+8
	ldr	r0, [r6, #2336]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #254
	bhi	.L2296
	ldr	r3, [fp, #-56]
	add	r8, r0, #8
	str	r8, [r3]
.L2264:
	cmp	r5, #0
	ble	.L2273
	sub	r4, r4, #4
	mov	r10, #0
	b	.L2277
.L2276:
	mov	r8, r8, lsr #24
	ldr	r2, [r4, #4]!
	add	r3, r3, r8
	cmp	r10, r5
	uxtb	r3, r3
	rsb	r8, r8, r3
	strb	r8, [r7, r2]
	beq	.L2273
.L2277:
	ldr	r1, .L2299+12
	add	r10, r10, #1
	ldr	r0, [r6, #2336]
	bl	HEVC_se_v
	add	r3, r0, r8
	add	r0, r0, #128
	add	r3, r3, #256
	cmp	r0, #255
	mov	r8, r3, asr #31
	bls	.L2276
	ldr	r1, .L2299+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2291:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2294:
	ldr	r3, .L2299
	cmp	r0, #0
	ldr	r4, [r3]
	add	r4, r4, #65536
	bne	.L2286
	ldr	r1, .L2299+20
	ldr	r0, [r6, #2336]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-52]
	cmp	r0, r3
	bhi	.L2283
	ldr	r3, [fp, #-52]
	rsb	r3, r0, r3
	uxtb	r3, r3
.L2268:
	ldr	r2, [fp, #-52]
	cmp	r3, r2
	beq	.L2297
.L2270:
	ldr	r2, [fp, #-72]
	add	r3, r2, r3
	ldr	r2, [fp, #-60]
	add	r1, r2, r3, lsl #6
.L2271:
	cmp	r1, #0
	beq	.L2298
	ldr	r3, .L2299+4
	mov	r2, r5
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
.L2273:
	ldr	r3, [fp, #-52]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	cmp	r3, #6
	beq	.L2281
	ldr	r2, [fp, #-56]
	add	r7, r7, #64
	ldr	r3, [r9]
	add	r2, r2, #4
	str	r2, [fp, #-56]
	ldr	r2, [fp, #-52]
	cmp	r2, r3
	bcc	.L2280
.L2281:
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
	bne	.L2261
	mov	r0, #0
	b	.L2291
.L2286:
	mov	r8, #8
	b	.L2264
.L2295:
	ldr	r1, .L2299+20
	ldr	r0, [r6, #2336]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-52]
	cmp	r0, r3
	bhi	.L2283
	ldr	r2, [fp, #-52]
	ldr	r1, [fp, #-48]
	rsb	r3, r0, r2
	cmp	r1, #1
	uxtb	r3, r3
	bls	.L2268
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
	bne	.L2270
.L2297:
	mov	r1, r2
	ldr	r0, [fp, #-48]
	bl	HEVC_GetScalingListDefaultAddress
	mov	r1, r0
	b	.L2271
.L2296:
	ldr	r1, .L2299+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2291
.L2298:
	ldr	r1, .L2299+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2291
.L2283:
	ldr	r1, .L2299+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2291
.L2293:
	ldr	r2, .L2299+36
	ldr	r1, .L2299+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2291
.L2300:
	.align	2
.L2299:
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
	ldr	r1, .L2467
	ldr	r0, [r0, #2336]
	bl	HEVC_ue_v
	cmp	r0, #1
	mov	r6, r0
	str	r0, [r4, #60]
	beq	.L2302
	cmp	r0, #3
	bhi	.L2445
	mov	r2, r0
	ldr	r1, .L2467+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2304:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2445:
	ldr	r1, .L2467+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2302:
	ldr	r1, .L2467+12
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #8192
	str	r0, [r4, #64]
	bhi	.L2446
	ldr	r1, .L2467+16
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #4096
	str	r0, [r4, #68]
	bhi	.L2447
	ldr	r2, [r4, #428]
	ldr	r3, [r4, #64]
	cmp	r2, #120
	mul	r0, r3, r0
	beq	.L2310
	bgt	.L2311
	cmp	r2, #60
	beq	.L2312
	ble	.L2448
	cmp	r2, #90
	beq	.L2315
	cmp	r2, #93
	beq	.L2316
	cmp	r2, #63
	beq	.L2449
.L2309:
	ldr	r1, .L2467+20
	mov	r0, #1
	bl	dprint_vfmw
.L2440:
	mvn	r0, #0
	b	.L2304
.L2446:
	ldr	r1, .L2467+24
	mov	r0, r6
.L2442:
	bl	dprint_vfmw
	ldr	r3, .L2467+28
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2440
	mov	r3, #0
	ldr	r0, [r5, #252]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2312:
	mov	r2, #30720
	mov	r3, #122880
.L2317:
	cmp	r0, r2
	movls	r3, #16
	strls	r3, [r4, #184]
	bls	.L2322
	cmp	r0, r3, lsr #1
	movls	r3, #12
	strls	r3, [r4, #184]
	bls	.L2322
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, lsr #2
	movls	r3, #8
	movhi	r3, #6
	str	r3, [r4, #184]
.L2322:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r0, #0
	beq	.L2325
	ldr	r1, .L2467+32
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r6, .L2467+36
	ldr	r1, .L2467+40
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #548]
	mul	r0, r3, r0
	str	r0, [r4, #72]
	ldr	r0, [r5, #2336]
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
	blt	.L2450
	ldr	r1, .L2467+44
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r1, .L2467+48
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #564]
	mul	r0, r3, r0
	str	r0, [r4, #80]
	ldr	r0, [r5, #2336]
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
	blt	.L2451
.L2325:
	ldr	r1, .L2467+52
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #2
	add	r2, r0, #8
	str	r2, [r4, #88]
	bhi	.L2452
	ldr	r1, .L2467+56
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #6
	add	r2, r0, #8
	str	r2, [r4, #96]
	bhi	.L2453
	ldr	r3, [r4, #88]
	ldr	r1, .L2467+60
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
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #12
	bhi	.L2454
	add	r0, r0, #4
	mov	r1, #1
	str	r0, [r4, #116]
	mov	r8, #0
	str	r0, [r4, #120]
	mov	r7, r8
	ldr	r0, [r5, #2336]
	mov	r6, r4
	bl	BsGet
	mov	r9, r0
	b	.L2336
.L2330:
	ldr	r3, [r4, #52]
	add	r7, r7, #1
	add	r6, r6, #4
	cmp	r7, r3
	bhi	.L2335
.L2336:
	ldr	r1, .L2467+64
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L2467+68
	add	r0, r0, #1
	str	r0, [r6, #328]
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	ldr	r1, .L2467+72
	str	r0, [r6, #360]
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	ldr	r3, [r6, #328]
	cmp	r8, r3
	movcc	r8, r3
	cmp	r9, #0
	str	r0, [r6, #392]
	bne	.L2330
	ldr	r1, [r4, #52]
	add	r3, r7, #1
	cmp	r3, r1
	addls	r7, r7, #82
	addls	r7, r4, r7, lsl #2
	bhi	.L2335
.L2334:
	ldr	r2, [r4, #328]
	add	r3, r3, #1
	cmp	r3, r1
	str	r2, [r7, #4]!
	ldr	r2, [r4, #360]
	str	r2, [r7, #32]
	ldr	r2, [r4, #392]
	str	r2, [r7, #64]
	bls	.L2334
.L2335:
	ldr	r3, [r4, #184]
	ldr	r1, .L2467+76
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r4, #184]
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L2455
	ldr	r1, .L2467+80
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r7, r0
	bhi	.L2456
	add	r0, r6, #3
	str	r0, [r4, #124]
	add	r6, r7, r0
	str	r6, [r4, #128]
	sub	r3, r6, #4
	cmp	r3, #2
	bhi	.L2457
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
	beq	.L2339
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L2340:
	ldr	r8, [r4, #68]
	mov	r1, r6
	str	r0, [r4, #188]
	mov	r0, r8
	bl	__aeabi_uidivmod
	mov	r0, r8
	cmp	r1, #0
	mov	r1, r6
	beq	.L2341
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L2342:
	str	r0, [r4, #192]
	ldr	r1, .L2467+84
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L2458
	ldr	r1, .L2467+88
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #3
	bhi	.L2459
	ldr	r2, [r4, #124]
	add	r3, r6, #2
	str	r3, [r4, #148]
	cmp	r3, r2
	bcs	.L2460
	add	r3, r0, r3
	str	r3, [r4, #152]
	cmp	r3, #5
	bhi	.L2346
	ldr	r2, [r4, #128]
	cmp	r3, r2
	bhi	.L2346
	ldr	r1, .L2467+92
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	ldr	r3, [r4, #128]
	ldr	r2, [r4, #148]
	rsb	r3, r2, r3
	cmp	r0, r3
	str	r0, [r4, #164]
	bhi	.L2461
	ldr	r1, .L2467+96
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	ldr	ip, [r4, #148]
	ldr	r3, [r4, #128]
	rsb	r3, ip, r3
	cmp	r0, r3
	str	r0, [r4, #168]
	bhi	.L2349
	ldr	r1, [r4, #140]
	mov	r0, #1
	mov	r3, #0
	mov	r1, r1, lsr r7
	cmp	r1, r0, asl ip
	bls	.L2351
.L2352:
	add	r3, r3, #1
	add	r2, r3, ip
	cmp	r1, r0, asl r2
	bhi	.L2352
.L2351:
	add	r3, r3, r7
	mov	r1, #1
	str	r3, [r4, #172]
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3]
	cmp	r0, #0
	beq	.L2353
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #0
	bne	.L2462
.L2353:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #6]
	cmp	r6, #0
	bne	.L2354
	ldr	r2, [r4, #68]
	cmp	r2, #64
	bls	.L2463
.L2354:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #104]
	beq	.L2355
	mov	r1, #4
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #4
	add	r0, r0, #1
	str	r0, [r4, #108]
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldr	r1, .L2467+100
	add	r0, r0, #1
	str	r0, [r4, #112]
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r7, r0
	bhi	.L2464
.L2356:
	ldr	r1, .L2467+104
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r6, r0
	bhi	.L2465
.L2357:
	add	r3, r7, #3
	str	r3, [r4, #156]
	add	r3, r6, r3
	str	r3, [r4, #160]
	cmp	r3, #5
	bhi	.L2358
	ldr	r2, [r4, #128]
	cmp	r3, r2
	bhi	.L2358
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	strb	r0, [r4, #7]
.L2355:
	ldr	r1, .L2467+108
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #64
	str	r0, [r4, #176]
	bhi	.L2360
	cmp	r0, #0
	addne	r7, r4, #2160
	movne	r6, #0
	addne	r7, r7, #4
	bne	.L2365
	b	.L2366
.L2364:
	ldr	r3, [r4, #176]
	cmp	r6, r3
	bcs	.L2366
.L2365:
	mov	r3, r6
	mov	r2, r7
	mov	r1, r4
	mov	r0, r5
	bl	HEVC_DecShortTermRefPicSet
	add	r6, r6, #1
	add	r7, r7, #164
	cmp	r0, #0
	beq	.L2364
	ldr	r1, .L2467+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2447:
	mov	r0, r6
	ldr	r1, .L2467+116
	b	.L2442
.L2311:
	cmp	r2, #156
	beq	.L2318
	bgt	.L2319
	cmp	r2, #150
	beq	.L2318
	cmp	r2, #153
	beq	.L2318
	cmp	r2, #123
	bne	.L2309
.L2310:
	mov	r2, #557056
	mov	r3, #2228224
	b	.L2317
.L2341:
	bl	__aeabi_uidiv
	b	.L2342
.L2339:
	bl	__aeabi_uidiv
	b	.L2340
.L2452:
	ldr	r1, .L2467+120
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2467+28
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L2440
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
	b	.L2304
.L2366:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	beq	.L2363
	ldr	r1, .L2467+124
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #32
	str	r0, [r4, #180]
	bhi	.L2369
	cmp	r0, #0
	addne	r8, r4, #192
	addne	r7, r4, #12
	movne	r6, #0
	beq	.L2363
.L2371:
	ldr	r1, [r4, #116]
	add	r6, r6, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #4]!
	ldr	r0, [r5, #2336]
	bl	BsGet
	strb	r0, [r7, #1]!
	ldr	r3, [r4, #180]
	cmp	r6, r3
	bcc	.L2371
.L2363:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r3, #2
	str	r3, [r4, #2096]
	uxtb	r0, r0
	strb	r0, [r4, #11]
	cmp	r0, #0
	beq	.L2368
	mov	r2, r4
	add	r1, r4, #2064
	mov	r0, r5
	bl	HEVC_DecVuiParam
	cmp	r0, #0
	bne	.L2466
.L2368:
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
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #12]
	cmp	r0, #0
	bne	.L2438
.L2374:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r4]
	b	.L2304
.L2373:
	ldr	r0, [r5, #2336]
	bl	BsGet
.L2438:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2373
	b	.L2374
.L2319:
	cmp	r2, #183
	beq	.L2320
	cmp	r2, #186
	beq	.L2320
	cmp	r2, #180
	bne	.L2309
.L2320:
	mov	r2, #8912896
	mov	r3, #35651584
	b	.L2317
.L2448:
	cmp	r2, #0
	beq	.L2314
	cmp	r2, #30
	bne	.L2309
.L2314:
	mov	r2, #9216
	mov	r3, #36864
	b	.L2317
.L2315:
	mov	r2, #138240
	mov	r3, #552960
	b	.L2317
.L2449:
	mov	r2, #61440
	mov	r3, #245760
	b	.L2317
.L2316:
	mov	r2, #245760
	mov	r3, #983040
	b	.L2317
.L2318:
	mov	r2, #2228224
	mov	r3, #8912896
	b	.L2317
.L2463:
	ldr	r1, .L2467+128
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2467+28
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2440
	ldr	r0, [r5, #252]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	b	.L2304
.L2462:
	add	r1, r4, #432
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	beq	.L2353
	ldr	r1, .L2467+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2346:
	ldr	r1, .L2467+136
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2465:
	mov	r2, r0
	ldr	r1, .L2467+140
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2357
.L2464:
	mov	r2, r0
	ldr	r1, .L2467+144
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2356
.L2454:
	ldr	r1, .L2467+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2455:
	ldr	r1, .L2467+152
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2458:
	ldr	r1, .L2467+156
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2358:
	ldr	r1, .L2467+160
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2461:
	ldr	r1, .L2467+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2456:
	ldr	r1, .L2467+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2457:
	ldr	r1, .L2467+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2453:
	ldr	r1, .L2467+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2460:
	ldr	r1, .L2467+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2459:
	ldr	r1, .L2467+184
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2349:
	ldr	r1, .L2467+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2450:
	ldr	r1, .L2467+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2360:
	mov	r2, #64
	ldr	r1, .L2467+196
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2451:
	ldr	r1, .L2467+200
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2369:
	ldr	r1, .L2467+204
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2466:
	ldr	r1, .L2467+208
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2304
.L2468:
	.align	2
.L2467:
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
	ldr	r9, .L2490
	mov	r4, r0
	ldr	r0, [r9]
	cmp	r0, #0
	beq	.L2483
	ldr	r7, .L2490+4
	mov	r2, #8
	mov	r1, #0
	sub	r0, fp, #60
	ldr	r3, [r7, #48]
	blx	r3
	mov	r1, #4
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r2, [r4, #156]
	cmp	r2, r0
	mov	r8, r0
	bls	.L2484
	ldr	r3, [r4, #2356]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L2485
	mov	r5, #0
	str	r5, [fp, #-64]
.L2473:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r3, r5
	mov	r2, #1
	sub	r1, fp, #60
	mov	r10, r0
	mov	r0, r4
	bl	HEVC_DecPTL
	subs	r3, r0, #0
	str	r3, [fp, #-68]
	bne	.L2486
	ldr	r1, .L2490+8
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r2, [r4, #160]
	cmp	r0, r2
	mov	r6, r0
	bcs	.L2487
	movw	r3, #12660
	ldr	r2, [r4, #2344]
	mul	r5, r3, r0
	uxtb	r1, r10
	str	r1, [fp, #-72]
	add	r2, r2, r5
	ldrb	r10, [r2, #1]	@ zero_extendqisi2
	cmp	r10, #0
	beq	.L2477
	ldr	r9, [r9]
	mov	r2, r3
	str	r3, [fp, #-76]
	add	r9, r9, #458752
	ldr	r3, [r7, #48]
	ldr	r1, [fp, #-68]
	mov	r0, r9
	ldr	r10, .L2490+4
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
	bne	.L2488
	mov	r2, #1
	strb	r2, [r9]
	strb	r2, [r9, #1]
	mov	r1, r9
	ldr	r0, [r4, #2344]
	mov	r2, r3
	ldr	r3, [r10, #56]
	add	r0, r0, r5
	blx	r3
	ldr	r3, [r4, #2344]
	add	r5, r3, r5
	str	r5, [r4, #2352]
.L2471:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2485:
	mov	r1, #3
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r0, #8
	mov	r5, r0
	str	r0, [fp, #-64]
	bls	.L2473
	mov	r2, #8
	ldr	r1, .L2490+12
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L2471
.L2477:
	str	r8, [r2, #48]
	sub	r1, fp, #60
	ldr	r3, [r4, #2344]
	mov	r2, #8
	ldr	r0, [fp, #-64]
	add	r3, r3, r5
	str	r0, [r3, #52]
	ldr	r3, [r4, #2344]
	ldrb	r0, [fp, #-72]	@ zero_extendqisi2
	add	r3, r3, r5
	strb	r0, [r3, #2]
	ldr	r3, [r4, #2344]
	add	r3, r3, r5
	strb	r10, [r3, #46]
	ldr	r0, [r4, #2344]
	ldr	r3, [r7, #52]
	add	r0, r0, r5
	add	r0, r0, #424
	blx	r3
	ldr	r3, [r4, #2344]
	mov	r0, r4
	add	r3, r3, r5
	str	r6, [r3, #56]
	ldr	r1, [r4, #2344]
	add	r1, r1, r5
	bl	HEVC_ProcessSPS
	subs	r7, r0, #0
	bne	.L2489
	ldr	r3, [r4, #2344]
	mov	r2, #1
	mov	r0, r7
	strb	r2, [r3, r5]
	ldr	r3, [r4, #2344]
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2344]
	add	r5, r3, r5
	str	r5, [r4, #2352]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2487:
	ldr	r1, .L2490+16
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #160]
	cmp	r6, r2
	bcc	.L2482
	ldr	r3, .L2490+20
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2482
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
.L2482:
	mvn	r7, #0
	b	.L2471
.L2486:
	ldr	r1, .L2490+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2471
.L2484:
	ldr	r1, .L2490+28
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L2471
.L2488:
	ldr	r3, [r4, #2344]
	mov	r2, r6
	ldr	r1, .L2490+32
	mov	r0, #1
	add	r5, r3, r5
	str	r5, [r4, #2352]
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2471
.L2483:
	ldr	r2, .L2490+36
	mvn	r7, #0
	ldr	r1, .L2490+40
	bl	dprint_vfmw
	b	.L2471
.L2489:
	mov	r2, r6
	ldr	r1, .L2490+44
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2344]
	mov	r2, #1
	strb	r2, [r3, r5]
	ldr	r3, [r4, #2344]
	add	r5, r3, r5
	strb	r10, [r5, #1]
	b	.L2471
.L2491:
	.align	2
.L2490:
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
	ldr	r1, .L2621
	ldr	r0, [r0, #2336]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r4, #32]
	blt	.L2493
	ldr	r3, [r5, #160]
	cmp	r0, r3
	bge	.L2493
	ldr	r3, [r5, #2344]
	movw	r6, #12660
	mla	r6, r6, r0, r3
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2600
	mov	r1, r7
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #2]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #4]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, r7
	str	r0, [r4, #36]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #3]
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldr	r1, .L2621+4
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #40]
	cmp	r0, #15
	bhi	.L2601
	ldr	r1, .L2621+8
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #44]
	cmp	r0, #15
	bhi	.L2602
	ldr	r1, .L2621+12
	ldr	r0, [r5, #2336]
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
	bne	.L2603
	mov	r1, r7
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #6]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	streq	r0, [r4, #52]
	bne	.L2604
.L2502:
	str	r0, [r4, #56]
	ldr	r1, .L2621+16
	ldr	r0, [r5, #2336]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #60]
	cmp	r3, #24
	bhi	.L2605
	ldr	r1, .L2621+20
	ldr	r0, [r5, #2336]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #64]
	cmp	r3, #24
	bhi	.L2606
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #13]
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #14]
	bne	.L2607
	ldr	r3, [r6, #188]
	strh	r3, [r4, #172]	@ movhi
	ldr	r3, [r6, #192]
	strh	r3, [r4, #212]	@ movhi
.L2541:
	ldr	r0, [r4, #68]
	cmp	r0, #0
	ble	.L2546
.L2540:
	ldr	ip, [r6, #140]
	add	r1, r4, #170
	mov	r3, #0
.L2545:
	ldrsh	r2, [r1, #2]!
	add	r3, r3, #1
	mul	r2, ip, r2
	cmp	r2, #64
	bhi	.L2544
	ldr	lr, [r6, #64]
	cmp	lr, #64
	bhi	.L2608
.L2544:
	cmp	r3, r0
	blt	.L2545
.L2546:
	ldr	r1, [r4, #72]
	cmp	r1, #0
	ble	.L2543
	ldr	r0, [r6, #140]
	ldrsh	r2, [r4, #212]
	mul	r2, r0, r2
	cmp	r2, #63
	addhi	r1, r1, #105
	addhi	r3, r4, #212
	addhi	r1, r4, r1, lsl #1
	bhi	.L2549
	b	.L2547
.L2550:
	ldrsh	r2, [r3, #2]!
	mul	r2, r0, r2
	cmp	r2, #63
	bls	.L2547
.L2549:
	cmp	r3, r1
	bne	.L2550
.L2543:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #17]
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #18]
	cmp	r0, #0
	bne	.L2609
.L2552:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #21]
	cmp	r0, #0
	beq	.L2555
	add	r1, r4, #256
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	bne	.L2610
.L2555:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldr	r1, .L2621+24
	strb	r0, [r4, #22]
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	add	r2, r0, #2
	str	r2, [r4, #84]
	cmp	r2, #1
	ble	.L2556
	ldr	r3, [r6, #128]
	cmp	r2, r3
	bhi	.L2556
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #23]
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #24]
	cmp	r0, #0
	bne	.L2587
	b	.L2560
.L2559:
	ldr	r0, [r5, #2336]
	bl	BsGet
	strb	r0, [r4, #25]
.L2587:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2559
.L2560:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2604:
	ldr	r1, .L2621+28
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #52]
	bls	.L2502
	mov	r0, r7
	ldr	r1, .L2621+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2607:
	ldr	r1, .L2621+36
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #19
	add	r2, r0, #1
	str	r2, [r4, #68]
	bhi	.L2611
	ldr	r1, .L2621+40
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	cmp	r0, #21
	add	r3, r0, #1
	str	r3, [r4, #72]
	bhi	.L2612
	ldr	r2, [r4, #68]
	cmp	r2, #10
	bgt	.L2613
	cmp	r3, #11
	ble	.L2510
	ldr	r1, .L2621+44
	mov	r2, #11
.L2597:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2621+48
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2592
.L2594:
	mov	r3, #0
	ldr	r0, [r5, #252]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
.L2588:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2547:
	ldr	r1, .L2621+52
.L2596:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2621+48
	ldr	r4, [r3]
	cmp	r4, #0
	bne	.L2594
.L2592:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2608:
	ldr	r1, .L2621+56
	b	.L2596
.L2603:
	mov	r0, r7
	ldr	r1, .L2621+60
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2510:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	ldr	r7, [r4, #68]
	uxtb	r0, r0
	strb	r0, [r4, #15]
	cmp	r0, #0
	bne	.L2524
	cmp	r7, #1
	addgt	r9, r4, #86
	movgt	r8, r0
	bgt	.L2522
	b	.L2614
.L2616:
	cmp	r3, r2
	bhi	.L2520
	ldr	r7, [r4, #68]
	add	r8, r8, #1
	sub	r3, r7, #1
	cmp	r3, r8
	ble	.L2615
.L2522:
	ldr	r1, .L2621+64
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r9, #2]!	@ movhi
	ldr	r2, [r6, #188]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2616
.L2520:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r8
	ldr	r1, .L2621+68
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2613:
	mov	r3, r2
	ldr	r1, .L2621+72
	mov	r2, #10
	b	.L2597
.L2609:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #19]
	ldr	r0, [r5, #2336]
	bl	BsGet
	uxtb	r7, r0
	strb	r7, [r4, #20]
	cmp	r7, #0
	bne	.L2552
	ldr	r1, .L2621+76
	ldr	r0, [r5, #2336]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #76]
	bhi	.L2617
.L2554:
	ldr	r1, .L2621+80
	ldr	r0, [r5, #2336]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #80]
	bls	.L2552
	ldr	r1, .L2621+84
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #80]
	b	.L2552
.L2524:
	cmp	r7, #0
	addgt	r3, r4, #170
	movgt	r8, #0
	ble	.L2514
.L2532:
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
	bne	.L2532
.L2514:
	ldr	r10, [r4, #72]
	cmp	r10, #0
	addgt	r3, r4, #210
	movgt	r8, #0
	ble	.L2531
.L2533:
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
	bne	.L2533
.L2531:
	cmp	r7, #1
	bne	.L2539
	ldr	r0, [r4, #72]
	cmp	r0, #1
	beq	.L2540
.L2539:
	mov	r1, #1
	ldr	r0, [r5, #2336]
	bl	BsGet
	strb	r0, [r4, #16]
	b	.L2541
.L2493:
	mov	r2, r0
	ldr	r1, .L2621+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2600:
	mov	r2, r0
	ldr	r1, .L2621+92
	mov	r0, r7
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2601:
	mov	r0, r7
	ldr	r1, .L2621+96
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2602:
	mov	r0, r7
	ldr	r1, .L2621+100
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2605:
	ldr	r1, .L2621+104
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2606:
	ldr	r1, .L2621+108
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2556:
	ldr	r1, .L2621+112
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2592
.L2615:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	ble	.L2518
.L2517:
	add	r8, r4, #126
	mov	r7, #0
	b	.L2529
.L2619:
	cmp	r3, r2
	bhi	.L2527
	ldr	r3, [r4, #72]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L2618
.L2529:
	ldr	r1, .L2621+116
	ldr	r0, [r5, #2336]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #192]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2619
.L2527:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r7
	ldr	r1, .L2621+120
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2611:
	mov	r3, #20
	ldr	r1, .L2621+124
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2617:
	ldr	r1, .L2621+128
	mov	r0, #1
	bl	dprint_vfmw
	str	r7, [r4, #76]
	b	.L2554
.L2618:
	ldr	r7, [r4, #68]
.L2518:
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2524
.L2525:
	sub	r2, r7, #1
	ldrh	r3, [r6, #188]
	add	ip, r4, r7, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #170]	@ movhi
	ble	.L2534
	add	r8, r7, #42
	add	r1, r4, #86
	add	lr, r4, #170
	add	r8, r4, r8, lsl #1
.L2535:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #170]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #170]	@ movhi
	bne	.L2535
.L2534:
	sxth	r3, r3
	cmp	r3, #0
	ble	.L2620
	ldr	r1, [r4, #72]
	ldrh	r3, [r6, #192]
	sub	r2, r1, #1
	add	ip, r4, r1, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #210]	@ movhi
	ble	.L2537
	add	r8, r1, #62
	add	lr, r4, #210
	add	r1, r4, #126
	add	r8, r4, r8, lsl #1
.L2538:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #210]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #210]	@ movhi
	bne	.L2538
.L2537:
	sxth	r3, r3
	cmp	r3, #0
	bgt	.L2531
	ldr	r1, .L2621+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2612:
	mov	r2, r3
	ldr	r1, .L2621+136
	mov	r3, #22
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2610:
	ldr	r1, .L2621+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2614:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	bgt	.L2517
	b	.L2525
.L2620:
	ldr	r1, .L2621+144
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2588
.L2622:
	.align	2
.L2621:
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
	ldr	r6, .L2635
	mov	r4, r0
	ldr	r0, [r6]
	cmp	r0, #0
	beq	.L2630
	ldr	r1, .L2635+4
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r3, [r4, #164]
	cmp	r0, r3
	mov	r7, r0
	bcs	.L2631
	mov	r8, #1888
	ldr	r3, [r4, #2348]
	mul	r5, r8, r0
	add	r2, r3, r5
	ldrb	r10, [r3, r5]	@ zero_extendqisi2
	cmp	r10, #0
	bne	.L2632
	str	r0, [r2, #28]
	mov	r0, r4
	ldr	r1, [r4, #2348]
	add	r1, r1, r5
	bl	HEVC_ProcessPPS
	subs	r9, r0, #0
	bne	.L2633
	ldr	r3, [r4, #2348]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2348]
	strb	r2, [r3, r5]
.L2625:
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2632:
	ldr	r6, [r6]
	mov	r2, r8
	ldr	r10, .L2635+8
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
	bne	.L2634
	mov	r3, #1
	strb	r3, [r6, #1]
	strb	r3, [r6]
	mov	r2, r8
	ldr	r0, [r4, #2348]
	mov	r1, r6
	ldr	r3, [r10, #56]
	add	r0, r0, r5
	blx	r3
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2634:
	mov	r2, r7
	ldr	r1, .L2635+12
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	b	.L2625
.L2631:
	mov	r2, r0
	ldr	r1, .L2635+16
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	b	.L2625
.L2633:
	mov	r2, r7
	ldr	r1, .L2635+12
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2348]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2348]
	strb	r10, [r3, r5]
	b	.L2625
.L2630:
	ldr	r2, .L2635+20
	mvn	r9, #0
	ldr	r1, .L2635+24
	bl	dprint_vfmw
	b	.L2625
.L2636:
	.align	2
.L2635:
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
	ldr	r3, [r0, #2348]
	mov	r7, r0
	ldr	r2, [r4, #132]
	mov	r0, #1888
	ldr	r1, [r4, #116]
	ldr	r5, [r7, #2344]
	mla	r3, r0, r2, r3
	cmp	r1, #1
	ldr	r6, [r3, #32]
	beq	.L2703
	cmp	r1, #0
	bne	.L2641
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2641
.L2639:
	ldr	r1, .L2714
	ldr	r0, [r7, #2336]
	bl	HEVC_ue_v
	cmp	r0, #7
	str	r0, [r4, #252]
	bhi	.L2704
	movw	r9, #12660
	mla	r9, r9, r6, r5
	ldr	r3, [r9, #60]
	cmp	r3, #0
	streq	r0, [r4, #384]
	bne	.L2705
.L2681:
	ldr	r3, [r4, #172]
	cmp	r3, #0
	subne	r3, fp, #172
	strne	r3, [fp, #-176]
	movne	r5, #0
	movne	r6, r3
	beq	.L2647
.L2648:
	mov	r1, #1
	ldr	r0, [r7, #2336]
	bl	BsGet
	ldr	r3, [r4, #172]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L2648
	ldr	r2, [r9, #60]
	cmp	r2, #0
	beq	.L2649
	cmp	r3, #0
	subne	r6, fp, #108
	movne	r5, #0
	beq	.L2647
.L2653:
	mov	r1, #1
	ldr	r0, [r7, #2336]
	bl	BsGet
	ldr	r3, [r4, #172]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L2653
.L2649:
	cmp	r3, #0
	beq	.L2647
	add	r6, r7, #4480
	add	r10, r7, #4544
	add	r6, r6, #4
	add	r10, r10, #12
	mov	r5, #0
	b	.L2664
.L2654:
	ldr	r2, [r4, #252]
	mov	r3, #1
	str	r1, [r6, #-132]
	mov	r2, r3, asl r2
	str	r2, [r6]
.L2656:
	ldr	r2, [r9, #60]
	cmp	r2, #0
	beq	.L2658
	sub	r2, fp, #108
	ldr	r2, [r2, r5, asl #2]
	cmp	r2, #0
	bne	.L2659
	ldr	r1, [r4, #384]
	mov	r3, #1
	str	r2, [r10, #120]
	mov	r1, r3, asl r1
	str	r2, [r10, #124]
	str	r1, [r10, #-8]
	str	r1, [r10, #-4]
.L2658:
	ldr	r2, [r4, #172]
	add	r5, r5, #1
	add	r6, r6, #4
	add	r10, r10, #8
	cmp	r2, r5
	bls	.L2647
.L2664:
	ldr	r3, [fp, #-176]
	ldr	r1, [r3, r5, asl #2]
	cmp	r1, #0
	beq	.L2654
	ldr	r1, .L2714+4
	ldr	r0, [r7, #2336]
	bl	HEVC_se_v
	add	r2, r0, #128
	cmp	r2, #255
	bhi	.L2706
	ldr	r2, [r4, #252]
	mov	r3, #1
	ldr	r1, .L2714+8
	add	r0, r0, r3, asl r2
	str	r0, [r6]
	ldr	r0, [r7, #2336]
	bl	HEVC_se_v
	add	r2, r0, #128
	str	r0, [r6, #-132]
	cmp	r2, #255
	bls	.L2656
	mov	r2, r0
	ldr	r1, .L2714+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2703:
	ldrb	r3, [r3, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2639
.L2641:
	mov	r0, #0
.L2702:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2659:
	sub	r8, r10, #8
	str	r5, [fp, #-180]
	mov	r5, r4
.L2662:
	ldr	r1, .L2714+16
	mov	r4, r8
	ldr	r0, [r7, #2336]
	bl	HEVC_se_v
	ldr	r1, .L2714+20
	add	r3, r0, #128
	cmp	r3, #255
	bhi	.L2707
	ldr	r3, [r5, #384]
	mov	r2, #1
	add	r8, r8, #4
	add	r0, r0, r2, asl r3
	str	r0, [r8, #-4]
	ldr	r0, [r7, #2336]
	bl	HEVC_se_v
	add	r3, r0, #512
	cmp	r3, #1024
	bcs	.L2708
	ldr	r1, [r4]
	cmp	r10, r8
	ldr	r3, [r5, #384]
	mov	r1, r1, asl #7
	mov	r3, r1, asr r3
	rsb	r3, r3, #128
	add	r0, r0, r3
	ssat	r0, #8, r0
	str	r0, [r8, #124]
	bne	.L2662
	mov	r4, r5
	ldr	r5, [fp, #-180]
	b	.L2658
.L2647:
	ldr	r5, [r4, #116]
	cmp	r5, #0
	bne	.L2641
	ldr	r3, [r4, #176]
	cmp	r3, #0
	beq	.L2641
	sub	r3, fp, #172
	str	r3, [fp, #-176]
	mov	r6, r3
.L2665:
	mov	r1, #1
	ldr	r0, [r7, #2336]
	bl	BsGet
	ldr	r3, [r4, #176]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L2665
	ldr	r2, [r9, #60]
	cmp	r2, #0
	bne	.L2709
.L2666:
	cmp	r3, #0
	beq	.L2641
	add	r6, r7, #4800
	add	r10, r7, #4864
	add	r6, r6, #4
	add	r10, r10, #12
	mov	r5, #0
	b	.L2680
.L2670:
	ldr	r2, [r4, #252]
	mov	r3, #1
	str	r1, [r6, #-388]
	mov	r2, r3, asl r2
	str	r2, [r6]
.L2672:
	ldr	r2, [r9, #60]
	cmp	r2, #0
	beq	.L2674
	sub	r2, fp, #108
	ldr	r2, [r2, r5, asl #2]
	cmp	r2, #0
	bne	.L2675
	ldr	r1, [r4, #384]
	mov	r3, #1
	str	r2, [r10, #120]
	mov	r1, r3, asl r1
	str	r2, [r10, #124]
	str	r1, [r10, #-8]
	str	r1, [r10, #-4]
.L2674:
	ldr	r2, [r4, #176]
	add	r5, r5, #1
	add	r6, r6, #4
	add	r10, r10, #8
	cmp	r2, r5
	bls	.L2641
.L2680:
	ldr	r3, [fp, #-176]
	ldr	r1, [r3, r5, asl #2]
	cmp	r1, #0
	beq	.L2670
	ldr	r1, .L2714+24
	ldr	r0, [r7, #2336]
	bl	HEVC_se_v
	add	r2, r0, #128
	cmp	r2, #255
	bhi	.L2710
	ldr	r2, [r4, #252]
	mov	r3, #1
	ldr	r1, .L2714+28
	add	r0, r0, r3, asl r2
	str	r0, [r6]
	ldr	r0, [r7, #2336]
	bl	HEVC_se_v
	add	r2, r0, #128
	str	r0, [r6, #-388]
	cmp	r2, #255
	bls	.L2672
	ldr	r1, .L2714+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2675:
	sub	r8, r10, #8
	str	r5, [fp, #-180]
	mov	r5, r4
.L2678:
	ldr	r1, .L2714+36
	mov	r4, r8
	ldr	r0, [r7, #2336]
	bl	HEVC_se_v
	ldr	r1, .L2714+40
	add	r3, r0, #128
	cmp	r3, #255
	bhi	.L2711
	ldr	r3, [r5, #384]
	mov	r2, #1
	add	r8, r8, #4
	add	r0, r0, r2, asl r3
	str	r0, [r8, #-4]
	ldr	r0, [r7, #2336]
	bl	HEVC_se_v
	add	r3, r0, #512
	cmp	r3, #1024
	bcs	.L2712
	ldr	r1, [r4]
	cmp	r10, r8
	ldr	r3, [r5, #384]
	mov	r1, r1, asl #7
	mov	r3, r1, asr r3
	rsb	r3, r3, #128
	add	r3, r0, r3
	ssat	r3, #8, r3
	str	r3, [r8, #124]
	bne	.L2678
	mov	r4, r5
	ldr	r5, [fp, #-180]
	b	.L2674
.L2705:
	ldr	r1, .L2714+44
	ldr	r0, [r7, #2336]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #14
	bhi	.L2713
	ldr	r3, [r4, #252]
	add	r0, r0, r3
	str	r0, [r4, #384]
	cmp	r0, #7
	bls	.L2681
	ldr	r1, .L2714+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2707:
	ldr	r1, .L2714+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2708:
	ldr	r1, .L2714+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2709:
	cmp	r3, #0
	subne	r6, fp, #108
	movne	r5, #0
	beq	.L2641
.L2669:
	mov	r1, #1
	ldr	r0, [r7, #2336]
	bl	BsGet
	ldr	r3, [r4, #176]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L2669
	b	.L2666
.L2706:
	mov	r2, r0
	ldr	r1, .L2714+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2711:
	ldr	r1, .L2714+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2712:
	ldr	r1, .L2714+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2710:
	ldr	r1, .L2714+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2704:
	ldr	r1, .L2714+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2713:
	ldr	r1, .L2714+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2702
.L2715:
	.align	2
.L2714:
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
	ldr	r3, [r0, #2356]
	add	r5, r0, #4096
	mov	r4, r0
	mov	r1, #1
	ldr	r0, [r0, #2336]
	ldr	r3, [r3, #24]
	str	r3, [fp, #-48]
	bl	BsGet
	ldr	r6, [r5, #124]
	sub	r3, r6, #16
	cmp	r3, #5
	movhi	r3, #0
	movls	r3, #1
	cmp	r3, #0
	str	r3, [fp, #-64]
	strb	r0, [r5, #96]
	bne	.L2968
.L2717:
	ldr	r1, .L3013
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r5, #132]
	ldr	r3, [r4, #164]
	blt	.L2719
	cmp	r0, r3
	bge	.L2719
	mov	r0, r4
	bl	HEVC_VpsSpsPpsCheck
	subs	r3, r0, #0
	str	r3, [fp, #-72]
	bne	.L2969
	ldr	r1, [r5, #132]
	mov	r7, #1888
	ldr	r2, [r4, #2348]
	movw	r8, #12660
	ldr	r3, [r4, #2344]
	mla	r7, r7, r1, r2
	ldrb	r1, [r7, #2]	@ zero_extendqisi2
	ldr	r2, [r7, #32]
	cmp	r1, #0
	mla	r8, r8, r2, r3
	bne	.L2970
.L2725:
	mov	r3, #0
	strb	r3, [r5, #97]
.L2726:
	ldr	r10, [r8, #140]
	ldr	r3, [r8, #144]
	cmp	r10, #0
	beq	.L2728
	cmp	r3, #0
	beq	.L2728
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
	ble	.L2857
	mov	r3, r1
	mov	r1, #0
.L2731:
	add	r1, r1, #1
	cmp	r0, r3, asl r1
	bgt	.L2731
.L2730:
	ldrb	r3, [r5, #96]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [fp, #-68]
	beq	.L2971
.L2732:
	ldrb	r10, [r5, #97]	@ zero_extendqisi2
	ldr	r3, [r4, #192]
	cmp	r10, #0
	str	r3, [r5, #108]
	beq	.L2972
.L2735:
	ldr	r3, [r7, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	bne	.L2825
.L2832:
	ldrb	r3, [r7, #23]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2973
.L2827:
	ldr	r3, [fp, #-68]
	cmp	r3, #0
	bne	.L2974
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [fp, #-64]
	beq	.L2843
	cmp	r3, #0
	beq	.L2844
	ldr	r3, [r5, #128]
	mov	r2, #1
	add	r3, r4, r3
	strb	r2, [r3, #5]
.L2841:
	ldr	r2, [r5, #108]
	ldr	r1, [fp, #-64]
	cmp	r2, #0
	moveq	r1, #0
	andne	r1, r1, #1
	cmp	r1, #0
	bne	.L2975
.L2842:
	mov	r2, #0
	strb	r2, [r3, #4]
.L2846:
	mov	r0, r4
	bl	HEVC_IsNewPic
	str	r0, [r5, #248]
	mov	r0, r4
	bl	HEVC_ReadByteAlignment
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L2953:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2970:
	ldrb	r3, [r5, #96]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2725
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	strb	r0, [r5, #97]
	b	.L2726
.L2972:
	ldr	r3, [r7, #36]
	cmp	r3, #0
	beq	.L2740
.L2739:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r3, [r7, #36]
	add	r10, r10, #1
	cmp	r3, r10
	bhi	.L2739
.L2740:
	ldr	r1, .L3013+4
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	cmp	r0, #2
	str	r0, [r5, #116]
	bhi	.L2976
	ldrb	r3, [r7, #4]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2977
.L2741:
	sub	r6, r6, #19
	cmp	r6, #1
	bhi	.L2978
	mov	r3, #0
	str	r3, [r5, #108]
	str	r3, [r4, #192]
	ldr	r3, [r5, #120]
	cmp	r3, #0
	streq	r3, [r4, #188]
	ldrb	r3, [r8, #6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2961
.L2849:
	mov	r3, #0
	strb	r3, [r5, #100]
	str	r3, [fp, #-84]
.L2851:
	ldr	r3, [r5, #116]
	cmp	r3, #2
	bne	.L2979
.L2779:
	ldrb	r3, [r5, #100]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2801
	mov	r3, #1
	strb	r3, [r5, #104]
	mov	r3, #2
.L2804:
	ldrb	r2, [r7, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2808
	cmp	r3, #1
	beq	.L2811
.L2808:
	ldrb	r2, [r7, #11]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2799
	cmp	r3, #0
	bne	.L2799
.L2811:
	mov	r0, r4
	bl	HEVC_DecPredWeightTable
	cmp	r0, #0
	ldreq	r3, [r5, #116]
	bne	.L2980
.L2799:
	cmp	r3, #2
	beq	.L2812
	ldr	r1, .L3013+8
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	rsb	r3, r0, #4
	rsb	r2, r0, #5
	cmp	r3, #4
	str	r2, [r5, #144]
	bhi	.L2981
.L2812:
	ldr	r1, .L3013+12
	ldr	r0, [r4, #2336]
	bl	HEVC_se_v
	ldr	r2, [r7, #48]
	add	r2, r0, r2
	str	r2, [r5, #112]
	ldr	r3, [r8, #92]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L2982
	ldrb	r3, [r7, #9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2983
.L2814:
	ldrb	r3, [r7, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2958
	ldrb	r3, [r7, #19]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2984
.L2820:
	ldrb	r0, [r7, #20]	@ zero_extendqisi2
	strb	r0, [r5, #105]
	ldr	r3, [r7, #76]
	str	r3, [r5, #156]
	ldr	r3, [r7, #80]
	str	r3, [r5, #160]
.L2819:
	ldrb	r3, [r8, #6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2823
	ldrh	r2, [r5, #98]
	adds	r3, r2, #0
	movne	r3, #1
.L2823:
	ldrb	r2, [r7, #17]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2824
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L2985
.L2824:
	strb	r2, [r5, #106]
	b	.L2735
.L2974:
	ldr	r3, [r5, #128]
	add	r3, r4, r3
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2842
	b	.L2841
.L2968:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	b	.L2717
.L2971:
	ldr	r0, [r4, #2336]
	bl	BsGet
	str	r0, [r5, #136]
	cmp	r0, #0
	ldr	r2, [r8, #192]
	ldr	r3, [r8, #188]
	mul	r3, r3, r2
	blt	.L2734
	cmp	r3, r0
	bls	.L2734
	mul	r3, r10, r0
	str	r3, [fp, #-68]
	b	.L2732
.L2825:
	ldr	r1, .L3013+16
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r3, [r7, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	ldreq	r3, [r8, #192]
	subeq	r3, r3, #1
	mov	r6, r0
	beq	.L2829
	cmp	r3, #256
	ldreq	r2, [r7, #68]
	ldreq	r3, [r7, #72]
	ldrne	r3, [r8, #192]
	ldrne	r2, [r7, #68]
	mul	r3, r3, r2
	sub	r3, r3, #1
.L2829:
	cmp	r3, #255
	movcs	r3, #255
	cmp	r6, r3
	bhi	.L2986
	cmp	r6, #0
	beq	.L2832
	ldr	r1, .L3013+20
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	cmp	r0, #31
	add	r8, r0, #1
	movls	r9, #0
	bhi	.L2987
.L2834:
	add	r9, r9, #1
	mov	r1, r8
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r9, r6
	bne	.L2834
	ldrb	r3, [r7, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2827
.L2973:
	ldr	r1, .L3013+24
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	cmp	r0, #256
	mov	r7, r0
	bhi	.L2988
	ldr	r0, [r4, #2336]
	bl	BsResidBits
	cmp	r7, r0
	bhi	.L2838
	cmp	r7, #0
	movne	r6, #0
	beq	.L2827
.L2840:
	add	r6, r6, #1
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	cmp	r6, r7
	bne	.L2840
	b	.L2827
.L2978:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2989
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
	beq	.L2745
	ldr	r2, [fp, #-80]
	cmp	r1, r2, lsr #1
	mov	r2, #0
	str	r2, [fp, #-76]
	bcs	.L2856
.L2745:
	ldr	r2, [r5, #124]
	ldr	r1, [fp, #-48]
	sub	r2, r2, #16
	cmp	r2, #2
	ldr	r2, [fp, #-76]
	add	r9, r4, r1, lsl #2
	movls	r3, #0
	add	r3, r3, r2
	str	r3, [r5, #108]
	ldr	r2, [r9, #212]
	cmp	r3, r2
	bge	.L2747
	ldrb	r0, [r5, #96]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L2990
.L2747:
	str	r3, [r4, #192]
	ldr	r2, [r5, #120]
	cmp	r2, #0
	bne	.L2748
	ldr	r2, [r5, #124]
	cmp	r2, #15
	bhi	.L2749
	tst	r2, #1
	movne	r1, #1
	beq	.L2749
.L2750:
	sub	r2, r2, #7
	bics	r2, r2, #2
	andne	r2, r1, #1
	moveq	r2, #0
	cmp	r2, #0
	strne	r3, [r4, #188]
.L2748:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	beq	.L2751
	ldr	r3, [r8, #176]
	mov	r1, #0
	cmp	r3, #1
	movhi	r2, #1
	bls	.L2753
.L2755:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L2755
	cmp	r1, #0
	bne	.L2991
.L2756:
	mov	r2, #164
	add	r0, r5, #1024
	mla	r1, r2, r1, r8
	add	r3, r4, #5120
	add	r0, r0, #4
	add	r3, r3, #4
	str	r3, [fp, #-84]
	add	r1, r1, #2160
	add	r1, r1, #4
	bl	memcpy
.L2754:
	ldrb	r3, [r8, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2758
	ldr	r3, [r8, #180]
	ldr	r6, [r5, #1032]
	cmp	r3, #0
	ldr	r2, [r5, #1028]
	streq	r3, [fp, #-48]
	add	r6, r6, r2
	streq	r3, [fp, #-56]
	bne	.L2992
.L2759:
	ldr	r1, .L3013+28
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r2, [r5, #1028]
	ldr	r3, [r5, #1032]
	ldr	ip, [fp, #-48]
	add	r1, r3, r2
	add	r0, r0, ip
	str	r0, [fp, #-60]
	add	r1, r1, r0
	cmp	r1, #16
	bhi	.L2993
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	add	r3, r6, r3
	str	r3, [fp, #-88]
	beq	.L2775
	ldr	r2, [fp, #-88]
	str	r7, [fp, #-92]
	add	r9, r2, #5120
	add	r3, r2, #1056
	add	r9, r9, #15
	add	r3, r3, #13
	add	r2, r4, r9
	add	r10, r4, r3, lsl #2
	mov	r1, r2
	mov	r2, #0
	mov	r9, r2
	str	r2, [fp, #-52]
	mov	r7, r1
	b	.L2774
.L2997:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	ldreq	r0, [fp, #-56]
	bne	.L2994
.L2766:
	add	r1, r8, r0
	add	r0, r8, r0, lsl #2
	ldrb	r1, [r1, #13]	@ zero_extendqisi2
	ldr	r6, [r0, #196]
	strb	r1, [r7]
.L2769:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L2995
	ldr	r3, [fp, #-48]
	str	r6, [r10, #944]
	cmp	r9, r3
	cmpne	r9, #0
	ldr	r3, [fp, #-52]
	str	r0, [r10]
	ldr	r1, [r5, #108]
	moveq	r3, #0
	str	r3, [fp, #-52]
	rsb	r6, r1, r6
	str	r6, [r10, #876]
.L2772:
	ldr	r3, [fp, #-60]
	add	r9, r9, #1
	sub	r10, r10, #4
	sub	r7, r7, #1
	cmp	r9, r3
	beq	.L2996
.L2774:
	ldr	r3, [fp, #-48]
	cmp	r3, r9
	bhi	.L2997
	ldr	r1, [r8, #120]
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	mov	r6, r0
	ldr	r0, [r4, #2336]
	bl	BsGet
	strb	r0, [r7]
	b	.L2769
.L2843:
	cmp	r3, #0
	beq	.L2844
	ldr	r3, [r5, #128]
	ldrb	r2, [fp, #-68]	@ zero_extendqisi2
	add	r3, r4, r3
	strb	r2, [r3, #5]
	b	.L2842
.L2975:
	ldr	r2, [r5, #124]
	cmp	r2, #21
	moveq	r2, #1
	streqb	r2, [r3, #4]
	bne	.L2842
	b	.L2846
.L2989:
	ldr	r1, [r8, #120]
	ldr	r0, [r4, #2336]
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
	bcs	.L2744
	ldr	r2, [fp, #-76]
	ldr	r0, [fp, #-80]
	rsb	r2, r2, r1
	cmp	r2, r0, lsr #1
	bcc	.L2744
.L2856:
	ldr	r2, [fp, #-80]
	add	r3, r3, r2
	b	.L2745
.L2749:
	sub	r1, r2, #16
	cmp	r1, #7
	movhi	r1, #0
	movls	r1, #1
	b	.L2750
.L2995:
	ldr	r1, .L3013+32
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-48]
	cmp	r9, #0
	cmpne	r9, r3
	ldrne	r3, [fp, #-52]
	addne	r0, r0, r3
	mov	r3, #1
	str	r3, [r10]
	ldr	r3, [fp, #-76]
	ldr	r1, [r5, #108]
	str	r0, [fp, #-52]
	rsb	ip, r3, r1
	ldr	r3, [fp, #-80]
	add	r6, ip, r6
	mls	r0, r3, r0, r6
	rsb	r1, r1, r0
	str	r1, [r10, #876]
	str	r0, [r10, #944]
	b	.L2772
.L2994:
	ldr	r1, [fp, #-72]
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r1, [r8, #180]
	sub	r1, r1, #1
	cmp	r0, #0
	blt	.L2768
	cmp	r1, r0
	bcs	.L2766
.L2768:
	str	r1, [sp]
	mov	r3, r0
	mov	r2, r9
	ldr	r1, .L3013+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2979:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #101]
	cmp	r0, #0
	bne	.L2998
	ldr	r3, [r5, #116]
	ldr	r2, [r7, #40]
	cmp	r3, #0
	str	r2, [r5, #172]
	bne	.L2785
	ldr	r2, [r7, #44]
	mov	r9, r3
	mov	r6, r3
	str	r2, [r5, #176]
.L2786:
	ldr	r3, [fp, #-84]
	cmp	r3, #0
	beq	.L2999
	ldr	r3, [fp, #-84]
	ldr	r2, [r3, #8]
	cmp	r2, #16
	bhi	.L2789
	cmp	r2, #0
	moveq	r3, r2
	beq	.L2791
	ldr	r3, [fp, #-84]
	add	r2, r2, #11
	add	r1, r3, #11
	add	r2, r3, r2
	mov	r3, #0
.L2793:
	ldrb	r0, [r1, #1]!	@ zero_extendqisi2
	cmp	r0, #0
	addne	r3, r3, #1
	cmp	r1, r2
	bne	.L2793
	cmp	r3, #1
	movle	r2, #0
	movgt	r2, #1
.L2791:
	ldrb	r1, [r7, #22]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r2, #0
	andne	r2, r2, #1
	cmp	r2, #0
	beq	.L3000
	add	r2, r4, #5248
	add	r1, r4, #4160
	add	r2, r2, #40
	add	r1, r1, #32
	mov	r0, r4
	bl	HEVC_DecRefPicListsModification
	cmp	r0, #0
	bne	.L3001
.L2787:
	ldr	r3, [r5, #116]
	cmp	r3, #0
	beq	.L2853
.L2794:
	cmp	r3, #2
	beq	.L2779
.L2854:
	ldrb	r3, [r7, #5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3002
.L2795:
	ldrb	r3, [r5, #100]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r5, #116]
	beq	.L2804
	cmp	r3, #0
	beq	.L3003
	cmp	r3, #2
	mov	r3, #1
	strb	r3, [r5, #104]
	beq	.L2801
.L2800:
	ldr	r3, [r5, #172]
	cmp	r3, #1
	bls	.L2957
.L2803:
	ldr	r1, .L3013+40
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldrb	r2, [r5, #104]	@ zero_extendqisi2
	cmp	r2, #0
	str	r0, [r5, #140]
	bne	.L3004
	cmp	r9, #0
	subne	r6, r9, #1
	moveq	r6, r2
.L2806:
	cmp	r6, r0
	movcs	r3, #0
	movcc	r3, #1
	orrs	r3, r3, r0, lsr #31
	beq	.L2957
	mov	r3, r0
	str	r6, [sp]
	ldr	r1, .L3013+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2957:
	ldr	r3, [r5, #116]
	b	.L2804
.L2844:
	ldr	r3, [r5, #128]
	add	r3, r4, r3
	b	.L2842
.L2958:
	ldrb	r0, [r5, #105]	@ zero_extendqisi2
	b	.L2819
.L2996:
	ldr	r7, [fp, #-92]
.L2775:
	ldr	r3, [fp, #-88]
	cmp	r3, #16
	str	r3, [r5, #1036]
	bhi	.L3005
.L2758:
	ldrb	r3, [r8, #9]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r5, #100]
	bne	.L3006
.L2777:
	ldrb	r3, [r8, #6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2851
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #98]
	ldr	r0, [r4, #2336]
	bl	BsGet
	strb	r0, [r5, #99]
	b	.L2851
.L3000:
	ldr	r3, [r5, #116]
	cmp	r3, #0
	bne	.L2854
.L2853:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r3, [r5, #116]
	strb	r0, [r5, #102]
	b	.L2794
.L2977:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	b	.L2741
.L2719:
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L3013+48
	mov	r0, #1
	ldr	r1, .L3013+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2983:
	ldr	r1, .L3013+56
	ldr	r0, [r4, #2336]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #148]
	cmp	r3, #24
	bhi	.L3007
	ldr	r3, [r7, #60]
	add	r2, r0, r3
	add	r2, r2, #12
	cmp	r2, #24
	bhi	.L3008
	ldr	r1, .L3013+60
	ldr	r0, [r4, #2336]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #152]
	cmp	r3, #24
	bhi	.L3009
	ldr	r2, [r7, #64]
	add	r2, r0, r2
	add	r3, r2, #12
	cmp	r3, #24
	bls	.L2814
	ldr	r1, .L3013+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3002:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	strb	r0, [r5, #103]
	b	.L2795
.L2857:
	mov	r1, #0
	b	.L2730
.L2785:
	mov	r9, r0
	mov	r6, r0
	str	r0, [r5, #176]
.L2784:
	cmp	r3, #2
	bne	.L2786
	b	.L2787
.L2744:
	ldr	r2, [fp, #-76]
	cmp	r2, r1
	bls	.L2745
	rsb	r1, r1, r2
	ldr	r2, [fp, #-80]
	cmp	r1, r2, lsr #1
	rsbhi	r3, r2, r3
	b	.L2745
.L2961:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #98]
	ldr	r0, [r4, #2336]
	bl	BsGet
	strb	r0, [r5, #99]
	b	.L2849
.L2751:
	add	r6, r4, #5120
	ldr	r3, [r8, #176]
	add	r6, r6, #4
	mov	r1, r8
	mov	r0, r4
	mov	r2, r6
	bl	HEVC_DecShortTermRefPicSet
	cmp	r0, #0
	streq	r6, [fp, #-84]
	beq	.L2754
	ldr	r1, .L3013+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2998:
	ldr	r1, .L3013+72
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	add	r6, r0, #1
	cmp	r6, #16
	bhi	.L3010
	ldr	r3, [r5, #116]
	str	r6, [r5, #172]
	cmp	r3, #0
	movne	r9, #0
	strne	r9, [r5, #176]
	bne	.L2784
	ldr	r1, .L3013+76
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	add	r9, r0, #1
	cmp	r9, #16
	strls	r9, [r5, #176]
	ldrls	r3, [r5, #116]
	bls	.L2784
	mov	r2, r9
	mov	r3, #16
	ldr	r1, .L3013+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2991:
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r3, [r8, #176]
	subs	r1, r0, #0
	sublt	r3, r3, #1
	blt	.L2757
.L2753:
	sub	r3, r3, #1
	cmp	r3, r1
	bcs	.L2756
.L2757:
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L3013+84
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3003:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	ldr	r3, [r5, #116]
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r5, #104]
	beq	.L2812
	cmp	r0, #0
	bne	.L2800
	ldr	r2, [r5, #176]
	cmp	r2, #1
	bhi	.L2803
	b	.L2804
.L2801:
	mov	r3, #2
	b	.L2808
.L3004:
	cmp	r6, #0
	subne	r6, r6, #1
	b	.L2806
.L2988:
	mov	r2, r0
	ldr	r1, .L3013+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3005:
	ldr	r2, [fp, #-88]
	mov	r3, #16
	ldr	r1, .L3013+92
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2728:
	mov	r2, r10
	ldr	r1, .L3013+96
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3006:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	strb	r0, [r5, #100]
	b	.L2777
.L2985:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	strb	r0, [r5, #106]
	b	.L2735
.L2984:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	tst	r0, #255
	beq	.L2820
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #105]
	cmp	r0, #0
	bne	.L2819
	ldr	r1, .L3013+100
	ldr	r0, [r4, #2336]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #156]
	bhi	.L3011
.L2821:
	ldr	r1, .L3013+104
	ldr	r0, [r4, #2336]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #160]
	bls	.L2958
	ldr	r1, .L3013+108
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #80]
	ldrb	r0, [r5, #105]	@ zero_extendqisi2
	str	r3, [r5, #160]
	b	.L2819
.L2969:
	ldr	r3, [r4, #236]
	mov	r0, r4
	cmp	r3, #0
	ldrne	r3, [r4, #192]
	str	r3, [r5, #108]
	bl	HEVC_IsNewPic
	ldr	r1, .L3013+112
	str	r0, [r5, #248]
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2992:
	ldr	r1, .L3013+116
	ldr	r0, [r4, #2336]
	bl	HEVC_ue_v
	ldr	r3, [r8, #180]
	cmp	r0, r3
	mov	r2, r0
	str	r0, [fp, #-48]
	bhi	.L3012
	cmp	r3, #1
	movls	r3, #0
	strls	r3, [fp, #-56]
	bls	.L2759
	mov	r2, #0
	mov	r1, r2
	mov	r2, #1
.L2761:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L2761
	str	r1, [fp, #-72]
	str	r1, [fp, #-56]
	b	.L2759
.L2982:
	ldr	r1, .L3013+120
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2990:
	ldr	r1, .L3013+124
	bl	dprint_vfmw
	ldr	r3, [r5, #108]
	b	.L2747
.L2734:
	mov	r2, r0
	ldr	r1, .L3013+128
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2976:
	mov	r2, r0
	ldr	r1, .L3013+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2789:
	mov	r3, #16
	ldr	r1, .L3013+136
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2981:
	ldr	r1, .L3013+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2986:
	mov	r2, r6
	ldr	r1, .L3013+144
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2838:
	mov	r2, r0
	mov	r3, r7
	ldr	r1, .L3013+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3008:
	mov	r2, r0
	ldr	r1, .L3013+152
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3011:
	ldr	r1, .L3013+156
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #76]
	str	r3, [r5, #156]
	b	.L2821
.L2980:
	ldr	r1, .L3013+160
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3007:
	mov	r2, r0
	ldr	r1, .L3013+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3009:
	mov	r2, r0
	ldr	r1, .L3013+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2993:
	str	r0, [sp]
	mov	ip, #16
	ldr	r1, .L3013+172
	mov	r0, #1
	str	ip, [sp, #4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L2999:
	ldr	r1, .L3013+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3014:
	.align	2
.L3013:
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
.L2987:
	mov	r2, r8
	ldr	r1, .L3013+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3010:
	mov	r2, r6
	mov	r3, #16
	ldr	r1, .L3013+184
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3012:
	ldr	r1, .L3013+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
.L3001:
	ldr	r1, .L3013+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2953
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
	ldr	r1, [r0, #2356]
	mov	r4, r0
	cmp	r1, #0
	beq	.L3016
	ldr	r0, [r0, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3016:
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
	ldr	r1, [r0, #2356]
	mov	r4, r0
	cmp	r1, #0
	beq	.L3022
	ldr	r0, [r0, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3022:
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
	beq	.L3030
	mov	r4, #0
	mov	r6, r4
.L3029:
	ldr	r3, [r5, #2376]
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L3028
	ldr	r0, [r5, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r5, #2376]
	str	r6, [r3, r4, asl #2]
	ldr	r2, [r5, #168]
.L3028:
	add	r4, r4, #1
	cmp	r2, r4
	bhi	.L3029
.L3030:
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
	add	r9, r5, #2576
	mov	r4, r5
	add	r9, r9, #8
	mov	r7, #17
	mov	r6, #0
.L3041:
	ldr	r3, [r9, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L3037
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L3037:
	ldr	r3, [r4, #2656]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3038
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L3038:
	ldr	r3, [r4, #2724]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3039
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L3039:
	ldr	r3, [r4, #2792]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3040
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L3040:
	subs	r7, r7, #1
	str	r6, [r4, #2792]
	str	r6, [r4, #2724]
	add	r4, r4, #4
	str	r6, [r4, #2652]
	str	r6, [r4, #2584]
	bne	.L3041
	ldr	r3, [r5, #2368]
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r5, #2564]
	cmp	r3, #17
	bhi	.L3079
.L3042:
	ldr	r3, .L3082
	mov	r4, #0
	add	r0, r5, #12480
	mov	r1, r4
	mov	r2, #200
	str	r4, [r5, #2568]
	ldr	r3, [r3, #48]
	add	r0, r0, #32
	str	r4, [r5, #2580]
	str	r4, [r5, #2584]
	str	r4, [r5, #2576]
	str	r4, [r5, #2572]
	blx	r3
	add	r2, r5, #2384
	add	r3, r5, #2448
	add	r1, r5, #12288
	add	r2, r2, #8
	add	r3, r3, #12
	mov	r0, r4
	mov	ip, #16
	str	r4, [r1, #228]
	str	ip, [r1, #224]
.L3043:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L3043
	add	lr, r5, #4096
	add	ip, r5, #2528
	mov	r0, r1
	str	r1, [lr, #164]
.L3044:
	str	r0, [r3, #4]!
	cmp	r3, ip
	mov	r2, #0
	bne	.L3044
	cmp	r8, r2
	str	r2, [lr, #168]
	bne	.L3045
	ldr	r3, [r5, #2384]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	beq	.L3045
.L3046:
	ldr	r1, [r5, #184]
	cmp	r1, #0
	addne	r2, r5, #2128
	movne	r3, #0
	addne	r2, r2, #12
	movne	r0, r3
	beq	.L3055
.L3054:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L3054
.L3055:
	ldr	r2, [r5, #168]
	cmp	r2, #0
	movne	r4, #0
	movne	r6, r4
	beq	.L3053
.L3057:
	ldr	r3, [r5, #2376]
	mov	r7, r4, asl #2
	ldr	r3, [r3, r4, asl #2]
	add	r4, r4, #1
	cmp	r3, #0
	mov	r1, r3
	beq	.L3056
	ldr	r0, [r5, #2356]
	cmp	r3, r0
	beq	.L3056
	ldr	r0, [r5, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r5, #2376]
	str	r6, [r3, r7]
	ldr	r2, [r5, #168]
.L3056:
	cmp	r2, r4
	bhi	.L3057
.L3053:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3045:
	mov	r4, #20
	mov	r0, r5
	str	r4, [r5, #180]
	str	r4, [r5, #184]
	bl	HEVC_ArrangeMem
	cmp	r0, #0
	beq	.L3047
	cmp	r0, #2
	beq	.L3080
	ldr	r2, .L3082+4
	mov	r0, #0
	ldr	r1, .L3082+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3079:
	mov	r4, #17
	ldr	r2, .L3082+4
	str	r4, [sp]
	mov	r3, r4
	ldr	r1, .L3082+12
	mov	r0, #1
	bl	dprint_vfmw
	str	r4, [r5, #2564]
	b	.L3042
.L3047:
	ldr	r0, [r5, #252]
	bl	FSP_GetTotalValidFsNum
	cmp	r0, #20
	movgt	r0, r4
	ble	.L3081
.L3050:
	str	r0, [r5, #180]
	b	.L3046
.L3080:
	add	r0, r5, #5504
	add	r0, r0, #48
	bl	ResetVoQueue
	mvn	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3081:
	ldr	r0, [r5, #252]
	bl	FSP_GetTotalValidFsNum
	b	.L3050
.L3083:
	.align	2
.L3082:
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
	beq	.L3088
	mov	r4, #0
	mov	r5, r4
	b	.L3087
.L3086:
	add	r3, r2, #1
	cmp	r3, r5
	bls	.L3088
.L3087:
	ldr	r1, [r6, #2380]
	add	r5, r5, #1
	add	r1, r1, r4
	add	r4, r4, #96
	ldr	r3, [r1, #32]
	cmp	r3, #1
	bne	.L3086
	ldr	r0, [r6, #252]
	bl	HEVC_ReleaseNAL
	ldr	r2, [r6, #168]
	add	r3, r2, #1
	cmp	r3, r5
	bhi	.L3087
.L3088:
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
	ldr	r1, .L3107
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
	add	r4, r7, #12736
	str	r3, [r7, #232]
	add	r4, r4, #56
	strb	r5, [r7, #10]
	mov	r6, r5
	bl	HEVC_ClearAllNal
	add	r0, r7, #5504
	add	r0, r0, #48
	ldr	r8, .L3107+4
	bl	ResetVoQueue
	mov	r9, #20
.L3092:
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
	bne	.L3092
	add	r3, r7, #2128
	add	r2, r7, #2208
	add	r3, r3, #12
	add	r2, r2, #12
	mov	r1, #0
.L3093:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L3093
	ldr	r3, [r7, #168]
	cmp	r3, #0
	beq	.L3094
	mov	r3, #0
	mov	r1, r3
.L3095:
	ldr	r2, [r7, #2376]
	str	r1, [r2, r3, asl #2]
	add	r3, r3, #1
	ldr	r2, [r7, #168]
	cmp	r2, r3
	bhi	.L3095
.L3094:
	add	r0, r7, #12480
	ldr	r3, [r8, #48]
	mov	r2, #200
	mov	r1, #0
	add	r0, r0, #32
	blx	r3
	add	r3, r7, #12288
	add	ip, r7, #2784
	add	r0, r7, #2640
	add	r1, r7, #2576
	add	ip, ip, #4
	add	r0, r0, #12
	add	r1, r1, #8
	add	lr, r7, #2720
	mov	r2, #16
	str	r2, [r3, #224]
	mov	r2, #17
	mov	r3, #0
.L3096:
	subs	r2, r2, #1
	str	r3, [ip, #4]!
	str	r3, [lr, #4]!
	str	r3, [r0, #4]!
	str	r3, [r1, #4]!
	bne	.L3096
	add	r3, r7, #2448
	add	r1, r7, #2384
	add	r3, r3, #12
	add	r1, r1, #8
	add	ip, r7, #2528
	mov	r0, r2
	mov	lr, #17
	str	r2, [r7, #2568]
	str	r2, [r7, #2572]
	str	r2, [r7, #2576]
	str	r2, [r7, #2580]
	str	r2, [r7, #2584]
	str	lr, [r7, #2564]
.L3097:
	str	r0, [r3, #4]!
	cmp	r3, ip
	str	r0, [r1, #4]!
	mov	r4, #0
	bne	.L3097
	add	r0, r7, #4160
	mov	r6, #2
	mov	r1, r4
	str	r4, [r7, #2356]
	str	r4, [r7, #204]
	movw	r2, #1356
	str	r4, [r7, #244]
	add	r0, r0, #32
	str	r4, [r7, #236]
	add	r5, r7, #2528
	str	r6, [r7, #176]
	add	r5, r5, #4
	ldr	r3, [r8, #48]
	mov	r9, #16
	blx	r3
	add	r2, r7, #4096
	mov	r3, #1
	mov	r1, r4
	str	r6, [r2, #116]
	mov	lr, #256
	str	r3, [r2, #248]
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
	str	r5, [r7, #2336]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3108:
	.align	2
.L3107:
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
	ldr	r3, [r4, #3548]
	cmp	r3, #0
	beq	.L3110
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #252]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3548]
	mov	r3, #0
	str	r3, [r2, #48]
	str	r3, [r4, #3548]
.L3110:
	mov	r0, #0
	strb	r0, [r4, #3489]
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
	bne	.L3117
	add	r0, r4, #5504
	add	r0, r0, #48
	bl	ResetVoQueue
	ldr	r0, [r4, #252]
	bl	FSP_EmptyInstance
.L3116:
	mov	r0, r4
	bl	HEVC_InitDecPara
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3117:
	add	r1, r4, #5504
	ldr	r0, [r4, #252]
	add	r1, r1, #48
	bl	FSP_ClearNotInVoQueue
	b	.L3116
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
	ldr	r3, [r0, #132]
	str	r2, [fp, #-52]
	ldr	r2, [r4, #284]
	cmp	r3, #0
	ldr	r9, [r4, #276]
	str	r2, [fp, #-60]
	blt	.L3135
	ldr	r2, [r4, #164]
	cmp	r3, r2
	bge	.L3135
	ldr	r2, [r4, #2348]
	mov	r1, #1888
	movw	r7, #12660
	ldr	ip, [r4, #2344]
	ldr	r0, [r0, #128]
	mla	r2, r1, r3, r2
	mov	lr, ip
	add	r0, r4, r0, lsl #2
	str	ip, [fp, #-72]
	ldr	ip, [r4, #2340]
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
	beq	.L3152
.L3120:
	ldr	r0, [r4, #2364]
	orr	r5, r5, r10
	ldr	ip, [r1, #4]
	ldr	r3, [fp, #-64]
	ldr	r0, [r0, #4]
	orr	r5, r3, r5
	cmp	r0, ip
	movne	r0, #1
	beq	.L3153
.L3121:
	orrs	r3, r0, r10
	beq	.L3122
	mov	r0, r4
	str	r2, [fp, #-68]
	bl	HEVC_UpdatePicVPS
	ldr	r2, [fp, #-68]
.L3122:
	ldr	r1, [r4, #2368]
	ldr	r0, [r6, #56]
	ldr	ip, [r1, #56]
	cmp	ip, r0
	movne	r7, #1
	beq	.L3154
.L3123:
	orrs	r7, r7, r5
	beq	.L3124
	ldr	ip, [r1, #184]
	mov	r0, r4
	ldr	r7, [r6, #184]
	mov	r1, r6
	str	r2, [fp, #-68]
	subs	r7, r7, ip
	movne	r7, #1
	bl	HEVC_UpdatePicSPS
	ldr	r2, [fp, #-68]
.L3124:
	ldr	r0, [r4, #2372]
	ldr	r1, [r2, #28]
	ldr	r0, [r0, #28]
	cmp	r0, r1
	movne	r1, #1
	beq	.L3155
.L3125:
	orrs	r3, r1, r5
	beq	.L3126
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_UpdatePicPPS
.L3126:
	ldr	r2, [r4, #280]
	ldr	r3, [fp, #-52]
	cmp	r3, r2
	movne	r1, #1
	beq	.L3156
.L3127:
	ldr	r0, [r4, #2368]
	ldr	ip, [r4, #2384]
	ldr	r3, [fp, #-48]
	ldr	r2, [r0, #96]
	ldr	r0, [r0, #88]
	cmp	r2, r0
	movcc	r2, r0
	str	r2, [ip, #932]
	ldr	r2, [r6, #56]
	cmp	r3, r2
	beq	.L3157
.L3128:
	str	r7, [sp]
	mov	r3, r9
	ldr	r2, [fp, #-56]
	mov	r1, r8
	mov	r0, r4
	bl	HEVC_GetReRangeFlag
	cmp	r0, #0
	bne	.L3129
	ldr	r3, [r4, #2384]
	ldr	r2, [r3, #920]
	cmp	r2, #1
	beq	.L3129
.L3131:
	mov	r2, #0
	str	r2, [r3, #936]
.L3130:
	mov	r0, r4
	bl	HEVC_AllocFrameStore
	subs	r5, r0, #0
	bne	.L3158
	mov	r0, r4
	bl	HEVC_InitPicInfo
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3135:
	mov	r0, #0
.L3119:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3157:
	ldr	r3, [fp, #-64]
	orr	r3, r3, r10
	orr	r3, r3, r7
	orrs	r3, r3, r1
	bne	.L3128
	ldr	r3, [r4, #2384]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L3130
.L3129:
	mov	r1, #1
	mov	r0, r4
	bl	HEVC_InitDPB
	cmn	r0, #2
	beq	.L3119
	cmp	r0, #0
	bne	.L3132
	ldr	r3, [r4, #2384]
	b	.L3131
.L3158:
	ldr	r1, .L3159
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3156:
	ldr	r1, [r4, #284]
	ldr	r3, [fp, #-60]
	subs	r1, r3, r1
	movne	r1, #1
	b	.L3127
.L3155:
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	adds	r1, r1, #0
	movne	r1, #1
	b	.L3125
.L3152:
	ldr	r0, [r6, #68]
	ldr	r3, [fp, #-56]
	subs	r3, r3, r0
	movne	r3, #1
	str	r3, [fp, #-64]
	b	.L3120
.L3154:
	ldr	r3, [fp, #-72]
	ldrb	r7, [r3, r7]	@ zero_extendqisi2
	adds	r7, r7, #0
	movne	r7, #1
	b	.L3123
.L3153:
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	b	.L3121
.L3132:
	mov	r2, r0
	ldr	r1, .L3159+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L3119
.L3160:
	.align	2
.L3159:
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
	ldr	r3, [r0, #3528]
	mov	r4, r0
	ldr	r5, [r0, #3548]
	add	r1, r0, #3552
	mov	r2, #640
	add	r0, r5, #80
	str	r3, [r5, #16]
	bl	memcpy
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_GetImagePara
	ldrb	r3, [r4, #3488]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3168
.L3162:
	add	r1, r5, #28
	mov	r0, r4
	bl	HEVC_OutputFrame.isra.10
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r2, .L3169
	mov	r0, #0
	ldr	r1, .L3169+4
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3168:
	mov	r2, #1
	ldr	r1, [r5, #28]
	ldr	r0, [r4, #252]
	bl	FSP_SetRef
	b	.L3162
.L3170:
	.align	2
.L3169:
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
	bne	.L3174
	ldr	r1, [r4, #3548]
	add	r3, r4, #8192
	mov	r2, #1
	mov	r0, #2
	str	r0, [r1, #52]
	mov	r0, r5
	str	r2, [r3, #2960]
	ldr	r3, [r4, #3496]
	ldr	r1, [r4, #3500]
	add	r3, r4, r3, lsl #2
	str	r1, [r3, #212]
	ldr	r3, [r4, #3548]
	strb	r2, [r3, #2]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3174:
	ldr	r2, .L3175
	mov	r0, #1
	ldr	r1, .L3175+4
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3176:
	.align	2
.L3175:
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
	beq	.L3182
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r6, r0, #0
	beq	.L3186
	cmn	r6, #3
	bne	.L3187
.L3181:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3186:
	add	r1, r5, #28
	mov	r0, r4
	bl	HEVC_OutputFrame.isra.10
	cmp	r0, #0
	beq	.L3181
	ldr	r2, .L3188
	mov	r0, r6
	ldr	r1, .L3188+4
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3187:
	mov	r3, r6
	movw	r2, #11897
	ldr	r1, .L3188+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #228]
	mov	r0, r4
	bl	HEVC_DECRecycleImage
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3182:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3189:
	.align	2
.L3188:
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
	ldr	r4, [r0, #3548]
	mov	r5, r0
	mov	ip, #2
	mov	r6, #0
	mov	r3, #1
	add	r1, r0, #3552
	str	ip, [r4, #48]
	add	r0, r4, #80
	strb	r3, [r4, #2]
	mov	r2, #640
	strb	r6, [r4, #1]
	ldr	r3, [r5, #3504]
	str	r3, [r4, #12]
	ldr	r3, [r5, #3528]
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
	ldr	r3, .L3191
	str	r6, [r4, #48]
	mov	r1, r6
	mov	r2, #704
	ldr	r3, [r3, #48]
	mov	r7, r0
	add	r0, r5, #3488
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3192:
	.align	2
.L3191:
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
	ldr	r3, [r4, #3524]
	ldr	r2, [r4, #184]
	cmp	r3, r2
	addne	r3, r3, #536
	movne	r1, #0
	strne	r1, [r4, r3, asl #2]
	strne	r2, [r4, #3524]
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
	ldr	lr, [r0, #2568]
	mov	r5, r0
	cmp	lr, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #2576
	mvn	ip, #-2147483648
	add	r0, r0, #8
	mvn	r4, #0
	mov	r3, #0
.L3198:
	ldr	r2, [r0, #4]!
	ldr	r1, [r2, #8]
	cmp	r1, ip
	bge	.L3197
	ldr	r2, [r2]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	moveq	ip, r1
	moveq	r4, r3
.L3197:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L3198
	cmn	r4, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r3, r5, r4, lsl #2
	mov	r1, #1
	mov	r0, r5
	ldr	r2, [r3, #2588]
	strb	r1, [r2, #2]
	ldr	r1, [r3, #2588]
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
	mov	r5, r0
	ldr	r0, [r0, #2568]
	ldr	r7, [r5, #3496]
	cmp	r0, #0
	beq	.L3212
	add	r6, r5, #2576
	add	r10, r7, #52
	add	r6, r6, #8
	mov	r3, #0
	add	r10, r5, r10, lsl #2
	str	r3, [fp, #-48]
	mov	r4, r3
	mov	r8, r6
	b	.L3211
.L3209:
	add	r4, r4, #1
	cmp	r0, r4
	bls	.L3240
.L3211:
	ldr	r3, [r8, #4]!
	ldrb	r9, [r3, #2]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L3209
	ldr	r2, [r3, #32]
	cmp	r2, r7
	bne	.L3209
	ldr	r3, [r3, #8]
	ldr	r2, [r10, #4]
	cmp	r3, r2
	blt	.L3210
	add	r4, r4, #1
	ldr	r3, [fp, #-48]
	cmp	r0, r4
	add	r3, r3, #1
	str	r3, [fp, #-48]
	bhi	.L3211
.L3240:
	add	r8, r5, #4096
	ldr	r2, [r5, #2368]
	cmp	r0, #0
	ldr	r3, [r8, #120]
	add	r3, r3, #90
	ldr	r3, [r2, r3, asl #2]
	str	r3, [fp, #-56]
	beq	.L3212
	mov	r4, #0
	add	r9, r5, r7, lsl #2
	str	r4, [fp, #-52]
	b	.L3222
.L3244:
	ldr	ip, [r5, #332]
	cmp	ip, #1
	beq	.L3218
.L3219:
	cmp	r2, #0
	bne	.L3217
	ldr	r3, [r8, #108]
	ldr	r2, [r1, #8]
	add	r3, r3, #100
	cmp	r2, r3
	ble	.L3217
	ldr	r3, [r9, #228]
	cmp	r3, #-2147483647
	beq	.L3217
	ldr	r3, [r5, #332]
	cmp	r3, #1
	beq	.L3241
.L3217:
	add	r4, r4, #1
	cmp	r0, r4
	bls	.L3242
.L3222:
	ldr	r1, [r6, #4]!
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3213
	ldr	r3, [r1, #32]
	cmp	r3, r7
	beq	.L3243
.L3213:
	add	r3, r5, r7, lsl #2
	ldr	r3, [r3, #212]
.L3215:
	cmp	r3, #0
	bne	.L3244
.L3218:
	ldr	ip, [r1, #8]
	cmp	r3, ip
	ble	.L3219
	cmp	r2, #0
	beq	.L3245
.L3220:
	str	ip, [sp]
	mov	r0, #31
	ldr	r2, .L3246
	add	r4, r4, #1
	ldr	r1, .L3246+4
	bl	dprint_vfmw
	ldr	r0, [r5, #2568]
	cmp	r0, r4
	bhi	.L3222
.L3242:
	ldr	r10, [fp, #-52]
.L3208:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3243:
	ldr	ip, [r1, #8]
	ldr	r3, [r9, #212]
	cmp	ip, r3
	str	ip, [fp, #-60]
	ble	.L3215
	ldr	lr, [fp, #-56]
	ldr	r10, [fp, #-48]
	ldr	ip, [r8, #120]
	cmp	r10, lr
	movhi	lr, #1
	movls	lr, #0
	cmp	ip, #7
	movhi	lr, #0
	cmp	lr, #0
	beq	.L3215
	ldr	lr, [r8, #108]
	ldr	ip, [fp, #-60]
	cmp	ip, lr
	blt	.L3216
	add	ip, r5, r7
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L3215
.L3216:
	mov	r3, #1
	mov	r0, r5
	strb	r3, [r1, #2]
	ldr	r1, [r6]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r6]
	ldr	r2, [fp, #-48]
	ldr	r3, [r3, #8]
	sub	r2, r2, #1
	str	r2, [fp, #-48]
	str	r3, [r9, #212]
	str	r0, [fp, #-52]
	ldr	r0, [r5, #2568]
	b	.L3217
.L3245:
	ldr	r1, [r1, #28]
	ldr	r0, [r5, #252]
	bl	FSP_SetDisplay
	ldr	r2, [r6]
	add	r3, r5, r7, lsl #2
	ldr	ip, [r2, #8]
	ldr	r3, [r3, #212]
	b	.L3220
.L3210:
	str	r2, [sp]
	mov	r0, #31
	ldr	r2, .L3246
	ldr	r1, .L3246+8
	bl	dprint_vfmw
	ldr	r3, [r8]
	ldr	r0, [r5, #252]
	mov	r2, r9
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
	ldr	r0, [r5, #2568]
	b	.L3209
.L3241:
	strb	r3, [r1, #2]
	mov	r0, r5
	ldr	r3, [fp, #-48]
	ldr	r1, [r6]
	sub	r3, r3, #1
	str	r3, [fp, #-48]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r9, #212]
	ldr	ip, [r8, #108]
	ldr	r2, .L3246
	cmp	ip, r3
	ldr	r1, .L3246+12
	sublt	r3, ip, #1
	strlt	r3, [r9, #212]
	ldr	r3, [r6]
	ldr	r3, [r3, #8]
	str	ip, [sp]
	str	r0, [fp, #-52]
	mov	r0, #31
	bl	dprint_vfmw
	ldr	r0, [r5, #2568]
	b	.L3217
.L3212:
	mov	r10, #0
	b	.L3208
.L3247:
	.align	2
.L3246:
	.word	.LANCHOR0+712
	.word	.LC426
	.word	.LC425
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
	ldr	r3, [r4, #2588]
	strb	r2, [r3, #2]
	ldr	r1, [r4, #2588]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r4, #2588]
	ldr	r2, [r3, #32]
	ldr	r1, [r3, #8]
	add	r2, r5, r2, lsl #2
	str	r1, [r2, #212]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r7, r0
	bne	.L3249
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
.L3249:
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
	bne	.L3254
	mov	r0, r4
	ldr	r1, [fp, #-24]
	bl	HEVC_OutputOneFrmFromDPB
	cmp	r0, #0
	bne	.L3255
.L3252:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L3254:
	ldr	r2, .L3256
	mov	r0, #1
	ldr	r1, .L3256+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3252
.L3255:
	ldr	r2, .L3256
	mov	r0, #1
	ldr	r1, .L3256+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3252
.L3257:
	.align	2
.L3256:
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
	beq	.L3266
	ldr	r3, [r4, #2568]
	cmp	r3, #0
	beq	.L3260
	add	r5, r4, #2576
	mov	r6, #0
	add	r5, r5, #8
	mov	r8, #1
	b	.L3265
.L3276:
	strb	r8, [r3, #2]
	ldr	r1, [r5]
	bl	HEVC_OutputFrmToVO
	cmn	r0, #1
	mov	r9, r0
	beq	.L3275
.L3263:
	ldr	r3, [r4, #2568]
	cmp	r3, r6
	bls	.L3260
.L3265:
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
	beq	.L3276
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #252]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L3263
	ldr	r3, [r5]
	ldr	r0, [r4, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #2568]
	cmp	r3, r6
	bhi	.L3265
.L3260:
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	mov	r9, #0
	bl	HEVC_InitDecBuffers
.L3274:
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3275:
	mov	r0, r7
	ldr	r2, .L3277
	ldr	r1, .L3277+4
	bl	dprint_vfmw
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3266:
	mvn	r9, #0
	b	.L3274
.L3278:
	.align	2
.L3277:
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
	ldr	r6, [r0, #2356]
	mov	r3, #0
	mov	r4, r0
	cmp	r6, r3
	str	r3, [r0, #328]
	beq	.L3307
	ldrb	r3, [r1]	@ zero_extendqisi2
	str	r3, [r6, #36]
	ldr	r3, [r0, #2384]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L3308
.L3286:
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3288
	ldr	r3, [r4, #2356]
	ldr	r2, [r3, #8]
	cmp	r2, #1
	bls	.L3289
	ldr	r0, [r3, #36]
	cmp	r0, #1
	beq	.L3288
.L3289:
	ldr	r0, [r1, #16]
	cmp	r0, #0
	ble	.L3290
	ldr	r0, [r1, #4]
	cmp	r0, #0
	beq	.L3290
	ldr	ip, [r1, #8]
	cmp	ip, #0
	bne	.L3309
.L3290:
	mov	r2, #1
	str	r2, [r3, #36]
	ldr	r1, [r1, #20]
	ldr	r0, [r4, #252]
	bl	SM_ReleaseStreamSeg
.L3285:
	ldr	r3, [r4, #2356]
	ldr	r0, [r3, #36]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
.L3283:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3309:
	mov	lr, r2, asl #5
	mov	ip, #0
	sub	r2, lr, r2, asl #2
	add	r3, r3, r2
	str	r0, [r3, #40]
	ldr	r3, [r4, #2356]
	ldr	lr, [r1, #16]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #44]
	ldr	r3, [r4, #2356]
	ldr	lr, [r1, #8]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #48]
	ldr	r3, [r4, #2356]
	ldr	lr, [r1, #20]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #64]
	ldr	r3, [r4, #2356]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	ip, [r3, #56]
	ldr	r2, [r4, #2356]
	ldr	r3, [r2, #8]
	add	r3, r3, #1
	str	r3, [r2, #8]
	ldr	r3, [r4, #2384]
	ldrb	r3, [r3, #944]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3291
	ldr	r0, [r1, #16]
	ldr	r2, [r4, #3540]
	ldr	r3, [r4, #3544]
	add	r2, r2, r0
	str	r2, [r4, #3540]
	ldr	r2, [r1, #16]
	add	r3, r3, r2
	str	r3, [r4, #3544]
.L3291:
	mov	r0, r4
	bl	HEVC_CombinePacket
	mov	r3, #1
	str	r3, [r4, #328]
	b	.L3285
.L3308:
	ldr	r3, [r3, #920]
	cmp	r3, #0
	bne	.L3285
	b	.L3286
.L3307:
	ldr	r3, [r1, #16]
	cmp	r3, #0
	ble	.L3281
	ldr	r3, [r1, #4]
	cmp	r3, #0
	beq	.L3281
	ldr	r3, [r1, #8]
	str	r1, [fp, #-32]
	cmp	r3, #0
	beq	.L3281
	bl	HEVC_FindNaluArraySlot
	ldr	r1, [fp, #-32]
	cmn	r0, #1
	mov	r5, r0
	beq	.L3310
	ldr	r3, [r4, #2380]
	mov	r0, r0, asl #7
	sub	r0, r0, r5, asl #5
	mov	r2, #1
	add	r0, r3, r0
	str	r0, [r4, #2356]
	ldr	r3, [r1, #4]
	str	r3, [r0, #40]
	ldr	r3, [r4, #2356]
	ldr	r0, [r1, #16]
	str	r0, [r3, #44]
	ldr	r3, [r4, #2356]
	ldr	r0, [r1, #20]
	str	r0, [r3, #64]
	ldr	r3, [r4, #2356]
	ldr	r0, [r1, #8]
	str	r0, [r3, #48]
	ldr	r3, [r4, #2356]
	str	r6, [r3, #56]
	ldr	r3, [r4, #2356]
	str	r2, [r3, #8]
	ldr	r3, [r4, #2356]
	strb	r6, [r3]
	ldr	r3, [r4, #2356]
	ldrb	r2, [r1]	@ zero_extendqisi2
	str	r2, [r3, #36]
	ldr	r3, [r4, #2384]
	ldrb	r3, [r3, #944]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3285
	ldr	r0, [r1, #16]
	ldr	r2, [r4, #3540]
	ldr	r3, [r4, #3544]
	add	r2, r2, r0
	str	r2, [r4, #3540]
	ldr	r2, [r1, #16]
	add	r3, r3, r2
	str	r3, [r4, #3544]
	b	.L3285
.L3288:
	ldr	r1, .L3311
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3283
.L3281:
	ldr	r1, .L3311+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3283
.L3310:
	ldr	r1, .L3311+8
	mov	r0, r6
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	mov	r0, r5
	b	.L3283
.L3312:
	.align	2
.L3311:
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
	ldr	r1, [r0, #2568]
	mov	r4, r0
	cmp	r1, #0
	beq	.L3315
	add	r6, r0, #2576
	mov	r5, #0
	add	r6, r6, #8
	mov	r7, r5
	b	.L3317
.L3316:
	cmp	r1, r5
	bls	.L3315
.L3317:
	ldr	r3, [r6, #4]!
	add	r5, r5, #1
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3316
	strb	r7, [r3, #1]
	mov	r2, #0
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #252]
	bl	FSP_SetRef
	ldr	r1, [r4, #2568]
	cmp	r1, r5
	bhi	.L3317
.L3315:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L3319
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L3315
	b	.L3319
.L3321:
	bl	HEVC_GetMinPOC
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	beq	.L3320
.L3319:
	ldr	r3, [r4, #2568]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	bne	.L3321
	mov	r0, r3
.L3320:
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
	beq	.L3330
	ldr	r2, .L3334
	mov	r0, #0
	ldr	r1, .L3334+4
	bl	dprint_vfmw
.L3330:
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3335:
	.align	2
.L3334:
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
	b	.L3337
.L3339:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L3345
.L3337:
	ldr	ip, [r4, #2568]
	mov	r0, #13
	ldr	lr, [r4, #2564]
	ldr	r2, .L3346
	cmp	ip, lr
	ldr	r1, .L3346+4
	mov	r3, ip
	bcs	.L3339
	b	.L3341
.L3342:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_OutputUnRefPicWithMinPoc
	cmp	r0, #0
	bne	.L3340
	ldr	ip, [r4, #2568]
	ldr	lr, [r4, #2564]
.L3341:
	cmp	ip, lr
	mov	r3, ip
	ldr	r2, .L3346
	mov	r0, #1
	ldr	r1, .L3346+8
	bcs	.L3342
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L3345:
	ldr	r2, .L3346
	mov	r0, #1
	ldr	r1, .L3346+12
	bl	dprint_vfmw
	ldr	ip, [r4, #2568]
	ldr	lr, [r4, #2564]
	b	.L3341
.L3340:
	ldr	r2, .L3346
	mov	r0, #1
	ldr	r1, .L3346+16
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	mov	r0, r4
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	HEVC_ClearDPB
.L3347:
	.align	2
.L3346:
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
	bhi	.L3352
	ldr	r3, [r2, #60]
	add	r5, r0, r1, lsl #2
	mov	r1, #1
	mov	r2, r1
	str	r3, [r5, #2588]
	str	r1, [r3, #48]
	ldr	r3, [r5, #2588]
	ldr	r0, [r0, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r0, [r5, #2588]
	mov	r2, #640
	adds	r3, r3, #0
	add	r1, r4, #64
	movne	r3, #1
	strb	r3, [r0, #1]
	ldr	r3, [r5, #2588]
	ldr	r0, [r4, #36]
	str	r0, [r3, #20]
	ldr	r0, [r5, #2588]
	add	r0, r0, #80
	bl	memcpy
	ldr	r2, [r5, #2588]
	ldr	ip, [r4, #40]
	add	r0, r6, #2576
	add	r1, r7, #1
	add	r0, r0, #12
	ldr	r3, .L3354
	str	ip, [r2, #16]
	mov	r2, #4
	ldr	ip, [r5, #2588]
	ldr	lr, [r4, #60]
	str	lr, [ip, #72]
	ldr	ip, [r5, #2588]
	ldr	lr, [r4, #16]
	str	lr, [ip, #12]
	ldr	ip, [r5, #2588]
	ldr	lr, [r4, #12]
	str	lr, [ip, #8]
	ldr	ip, [r5, #2588]
	ldr	lr, [r4, #8]
	str	lr, [ip, #32]
	bl	qsort
	ldr	r3, [r6, #2568]
	mov	r0, r6
	add	r3, r3, #1
	str	r3, [r6, #2568]
	ldr	r1, [r4, #60]
	bl	HEVC_GetAPC
	subs	r3, r0, #0
	bne	.L3353
	mov	r0, r3
	strb	r3, [r4, #1]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3352:
	mov	r3, r1
	ldr	r2, .L3354+4
	ldr	r1, .L3354+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3353:
	ldr	r2, .L3354+4
	mov	r0, #0
	ldr	r1, .L3354+12
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_PrintDPBState
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3355:
	.align	2
.L3354:
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
	ldrb	r3, [r0, #3488]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r3, #0
	bne	.L3369
	ldr	r3, [r0, #3548]
	mov	r2, #2
	str	r2, [r3, #48]
.L3358:
	ldr	r3, [r4, #3548]
	mov	r2, #1
	mov	r0, r4
	strb	r2, [r3, #2]
	ldr	r1, [r4, #3548]
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r5, r0
	beq	.L3370
	cmn	r0, #3
	beq	.L3362
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3371
.L3362:
	mov	r0, #0
.L3359:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3369:
	bl	HEVC_SimpleSlideDPB
	add	r2, r4, #3488
	ldr	r1, [r4, #2568]
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	beq	.L3358
	str	r0, [sp]
	movw	r3, #10993
	ldr	r2, .L3372
	mov	r0, #0
	ldr	r1, .L3372+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3359
.L3371:
	ldr	r2, .L3372
	mov	r0, #0
	ldr	r1, .L3372+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3359
.L3370:
	ldr	r2, .L3372
	mov	r0, #0
	ldr	r1, .L3372+12
	bl	dprint_vfmw
	mov	r0, r5
	b	.L3359
.L3373:
	.align	2
.L3372:
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
	ldr	r1, [r0, #2568]
	mov	r4, r0
	ldr	r3, [r0, #2564]
	cmp	r1, r3
	bcs	.L3386
.L3375:
	add	r2, r4, #3488
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L3387
	ldr	r1, [r4, #3548]
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r5, r0
	beq	.L3388
	cmn	r0, #3
	beq	.L3381
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3389
.L3381:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3386:
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3385
	ldr	r2, .L3390
	mov	r0, #0
	ldr	r1, .L3390+4
	bl	dprint_vfmw
.L3385:
	ldr	r1, [r4, #2568]
	b	.L3375
.L3387:
	ldr	r2, .L3390
	mov	r0, #0
	ldr	r1, .L3390+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3389:
	mov	r0, r6
	ldr	r2, .L3390
	ldr	r1, .L3390+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3388:
	mov	r0, r6
	ldr	r2, .L3390
	ldr	r1, .L3390+16
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3391:
	.align	2
.L3390:
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
	ldr	r3, [r3, #2960]
	cmp	r3, #1
	beq	.L3393
	bl	HEVC_FirstFrameFastOut
	cmp	r0, #0
	bne	.L3416
.L3393:
	ldr	r1, [r4, #2568]
	ldr	r3, [r4, #2564]
	cmp	r1, r3
	bcs	.L3417
.L3395:
	add	r2, r4, #3488
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L3418
	ldr	r3, [r4, #2568]
	cmp	r3, #0
	bne	.L3419
.L3398:
	ldr	r2, [r4, #2564]
	cmp	r2, r3
	bls	.L3420
.L3415:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3420:
	add	r1, r4, #5504
	ldr	r0, [r4, #252]
	add	r1, r1, #48
	bl	FSP_IfCanGetDecFs
	cmp	r0, #0
	beq	.L3415
	mov	r0, r4
	bl	HEVC_RemoveFrmFullDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3417:
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3414
	ldr	r1, .L3421
	mov	r0, #0
	bl	dprint_vfmw
.L3414:
	ldr	r1, [r4, #2568]
	b	.L3395
.L3419:
	mov	r0, r4
	bl	HEVC_OutputFrmFromDPB
	cmp	r0, #0
	bne	.L3399
	ldr	r3, [r4, #2568]
	b	.L3398
.L3418:
	mov	r2, r0
	ldr	r1, .L3421+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3416:
	ldr	r2, .L3421+8
	mov	r0, #0
	ldr	r1, .L3421+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3399:
	ldr	r2, .L3421+8
	mov	r0, #1
	ldr	r1, .L3421+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3422:
	.align	2
.L3421:
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
	ldr	r3, .L3467
	mov	r4, r0
	ldr	r2, [r0, #252]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L3458
.L3424:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	ldrb	r5, [r4, #3489]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L3459
	ldr	r2, [r4, #3528]
	cmp	r2, #0
	beq	.L3427
	ldr	r5, [r4, #3504]
	cmp	r5, #0
	beq	.L3460
.L3428:
	ldr	r3, [r4, #2384]
	ldr	r1, [r3, #4]
	cmp	r1, r2
	bcs	.L3427
	ldr	r5, [r3, #644]
	cmp	r5, #0
	beq	.L3461
.L3427:
	ldr	r3, [r4, #2392]
	ldr	r2, [r4, #3548]
	add	r3, r3, #4096
	ldr	r3, [r3, #1084]
	str	r3, [r2, #40]
	ldr	r3, [r4, #2392]
	ldr	r2, [r4, #3548]
	add	r3, r3, #4096
	ldr	r3, [r3, #1088]
	str	r3, [r2, #44]
	ldr	r3, [r4, #256]
	cmp	r3, #2
	beq	.L3462
	ldr	r3, [r4, #2384]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	beq	.L3463
	cmp	r3, #1
	beq	.L3464
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bls	.L3438
.L3440:
	mov	r0, r4
	mvn	r5, #0
	bl	HEVC_ClearCurrPic
	ldr	r2, .L3467+4
	ldr	r1, .L3467+8
	mov	r0, #1
	bl	dprint_vfmw
.L3439:
	mov	r3, #0
	strb	r3, [r4, #3489]
.L3456:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3458:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L3424
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L3424
	add	r3, r0, #8192
	ldrb	r3, [r3, #2904]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3424
	bl	HEVC_Sei_Get_Frame_Pts
	b	.L3424
.L3459:
	ldr	r2, .L3467+4
	mov	r0, #1
	ldr	r1, .L3467+12
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3461:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, [r4, #2384]
	ldr	r2, [r4, #3528]
	mov	r0, #1
	ldr	r1, .L3467+16
	ldr	r3, [r3, #4]
	bl	dprint_vfmw
	b	.L3456
.L3464:
	mov	r0, r4
	bl	HEVC_DecOrderProcess
	subs	r5, r0, #0
	bne	.L3437
	ldr	r3, [r4, #2384]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L3439
.L3438:
	mov	r0, r4
	bl	HEVC_DispOrderProcess
	subs	r5, r0, #0
	beq	.L3439
	ldr	r2, .L3467+4
	mov	r0, #0
	ldr	r1, .L3467+20
	bl	dprint_vfmw
	b	.L3433
.L3460:
	ldr	r2, .L3467+4
	mov	r0, #1
	ldr	r1, .L3467+24
	bl	dprint_vfmw
	ldr	r3, .L3467+28
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L3457
	mov	r3, r5
	mov	r2, r5
	mov	r1, #111
	ldr	r0, [r4, #252]
	blx	r6
.L3457:
	ldr	r2, [r4, #3528]
	b	.L3428
.L3462:
	mov	r0, r4
	bl	HEVC_DirectOutput
	ldr	r3, [r4, #3524]
	ldr	r2, [r4, #184]
	cmp	r3, r2
	addne	r3, r3, #536
	movne	r1, #0
	strne	r1, [r4, r3, asl #2]
	mov	r5, r0
	strne	r2, [r4, #3524]
	cmp	r0, #0
	bne	.L3465
.L3432:
	movw	r3, #11295
	mov	r2, r5
	ldr	r1, .L3467+32
	mov	r0, #14
	bl	dprint_vfmw
.L3433:
	cmn	r5, #1
	bne	.L3439
	b	.L3440
.L3463:
	mov	r0, r4
	bl	HEVC_SimpleDPBProcess
	subs	r5, r0, #0
	bne	.L3466
.L3435:
	movw	r3, #11310
	mov	r2, r5
	ldr	r1, .L3467+32
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3433
.L3465:
	ldr	r2, .L3467+4
	mov	r0, #0
	ldr	r1, .L3467+36
	bl	dprint_vfmw
	b	.L3432
.L3466:
	ldr	r2, .L3467+4
	mov	r0, #0
	ldr	r1, .L3467+40
	bl	dprint_vfmw
	b	.L3435
.L3437:
	ldr	r2, .L3467+4
	mov	r0, #0
	ldr	r1, .L3467+44
	bl	dprint_vfmw
	ldr	r3, [r4, #2384]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L3433
	b	.L3438
.L3468:
	.align	2
.L3467:
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
	ldr	r3, .L3514
	mov	r4, r0
	mov	r5, r1
	sub	r0, fp, #740
	mov	r2, #704
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	add	r0, r4, #12672
	add	r0, r0, #40
	mov	r6, #0
.L3474:
	ldr	r3, [r0, #48]
	cmp	r3, #0
	bne	.L3470
	cmp	r0, #0
	beq	.L3491
	ldr	ip, [r4, #2568]
	cmp	ip, #0
	beq	.L3491
	ldr	r2, [r4, #2588]
	cmp	r0, r2
	beq	.L3470
	add	r2, r4, #2576
	add	r2, r2, #12
	b	.L3472
.L3473:
	ldr	r1, [r2, #4]!
	cmp	r0, r1
	beq	.L3470
.L3472:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L3473
.L3491:
	mov	r8, #720
	mov	r7, r0
	mla	r8, r8, r6, r4
	mov	r2, #640
	sub	r0, fp, #676
	mov	r9, #1
	mov	r3, #101
	str	r5, [fp, #-728]
	add	r1, r8, #12736
	str	r3, [fp, #-700]
	add	r1, r1, #56
	strb	r9, [fp, #-739]
	strb	r9, [fp, #-740]
	bl	memcpy
	add	r2, r8, #12672
	add	r3, r8, #12736
	cmp	r6, #19
	movw	r1, #12712
	strb	r9, [r2, #42]
	mov	r6, #0
	str	r7, [fp, #-680]
	str	r6, [r3, #28]
	str	r6, [fp, #-524]
	strb	r9, [r8, r1]
	bgt	.L3475
	ldr	r0, [r4, #2568]
	cmp	r0, #0
	beq	.L3477
	add	r1, r4, #2576
	mov	ip, r6
	add	r1, r1, #8
	mvn	r2, #-2147483648
	mov	r8, r1
.L3480:
	ldr	lr, [r8, #4]!
	add	ip, ip, #1
	ldr	r3, [lr, #8]
	rsb	r3, r5, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bge	.L3479
	ldrb	lr, [lr, #1]	@ zero_extendqisi2
	cmp	lr, #0
	movne	r2, r3
	movne	r6, #1
.L3479:
	cmp	ip, r0
	bne	.L3480
	cmp	r6, #0
	beq	.L3477
	mov	r6, #0
	b	.L3481
.L3482:
	add	r6, r6, #1
	cmp	r6, r0
	beq	.L3483
.L3481:
	ldr	ip, [r1, #4]!
	ldr	r3, [ip, #8]
	rsb	r3, r5, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bne	.L3482
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3482
	ldr	r1, [ip, #28]
	add	r6, r4, r6, lsl #2
	ldr	r0, [r4, #252]
	ldr	r9, [ip, #32]
	bl	FSP_GetLogicFs
	ldr	r2, [r6, #2588]
	mov	r3, r5
	ldr	r1, .L3514+4
	ldr	r2, [r2, #8]
	mov	r8, r0
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r8, #0
	beq	.L3483
	ldr	r0, [r8, #28]
	cmp	r0, #0
	beq	.L3512
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
	beq	.L3486
	ldr	r1, [fp, #-680]
	sub	r2, fp, #740
	mov	r0, r4
	str	r7, [r1, #28]
	ldr	r1, [r8, #28]
	str	r1, [r3, #28]
	ldr	r1, [r8, #32]
	str	r1, [r3, #32]
	ldrsb	r3, [r8, #4]
	ldr	r1, [r4, #2568]
	str	r9, [fp, #-732]
	str	r3, [fp, #-704]
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L3513
	ldr	r0, [r4, #252]
	mov	r1, r7
	mov	r2, r6
	bl	FSP_SetDisplay
	add	r3, r4, #4096
	mov	r0, r6
	ldr	r3, [r3, #128]
	add	r4, r4, r3, lsl #2
	ldr	r3, [r4, #228]
	cmn	r3, #-2147483647
	streq	r5, [r4, #228]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3470:
	add	r6, r6, #1
	add	r0, r0, #720
	cmp	r6, #20
	bne	.L3474
.L3475:
	ldr	r1, .L3514+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L3507:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3483:
	ldr	r1, .L3514+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3486:
	ldr	r3, [fp, #-680]
	mov	r0, r2
	ldr	r1, .L3514+16
	strb	r2, [r3]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3507
.L3513:
	ldr	r3, [fp, #-680]
	mov	r1, r7
	mov	r5, #0
	mov	r2, #1
	strb	r5, [r3]
	ldr	r0, [r4, #252]
	bl	FSP_ClearLogicFs
	mov	r0, r5
	ldr	r1, .L3514+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3507
.L3477:
	mov	r0, #0
	ldr	r1, .L3514+24
	strb	r0, [r7]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3507
.L3512:
	ldr	r1, .L3514+28
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	b	.L3507
.L3515:
	.align	2
.L3514:
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
	b	.L3517
.L3520:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.8
	ldr	r1, .L3526
	cmp	r0, #0
	mov	r0, #1
	bne	.L3522
	ldr	r2, [fp, #-24]
	bl	dprint_vfmw
	ldr	r3, [r4, #2384]
	mov	r0, r4
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L3518
	ldr	r1, [fp, #-24]
	bl	HEVC_CreateLostPicture
	cmp	r0, #0
	bne	.L3525
.L3517:
	ldr	r3, [r5, #124]
	sub	r1, fp, #24
	mov	r0, r4
	sub	r3, r3, #19
	cmp	r3, #2
	bhi	.L3520
.L3522:
	mov	r0, r4
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	mov	r0, r4
	bl	HEVC_RecoverDPBProcess
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3518:
	ldr	ip, [fp, #-24]
	mov	r0, #1
	ldr	r3, [r5, #108]
	ldr	r1, .L3526+4
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3525:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3527:
	.align	2
.L3526:
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
	bls	.L3587
	ldr	r3, [r0, #296]
	mov	r0, #1
	ldr	r2, [r4, #300]
	add	r3, r3, r0
	ldr	r1, [r4, #2384]
	cmp	r3, r2
	movlt	r3, r2
	str	r3, [r4, #296]
	rsb	r3, r2, r3
	str	r3, [r1, #584]
	ldr	r5, [r4, #248]
	ldr	r2, [r4, #256]
	ubfx	r5, r5, #16, #3
	strb	r0, [r4, #3488]
	cmp	r2, r5
	beq	.L3533
	subs	r3, r5, #2
	sub	r1, r2, #2
	movne	r3, #1
	cmp	r1, r0
	movhi	r3, #0
	cmp	r3, #0
	beq	.L3533
	cmp	r5, #4
	cmpne	r5, r0
	bls	.L3588
.L3533:
	cmp	r5, #2
	str	r5, [r4, #256]
	beq	.L3535
	cmp	r5, #3
	bne	.L3583
.L3584:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
.L3582:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3583:
	ldr	r3, [r4, #236]
	cmp	r3, #0
	beq	.L3552
	cmp	r5, #4
	ldr	r3, [r4, #3504]
	beq	.L3589
.L3541:
	cmp	r3, #2
	bne	.L3543
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3590
.L3554:
	ldr	r2, [r4, #240]
	mov	r0, #2
	ldr	r1, .L3592
	sub	r2, r2, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L3591
	ldr	r0, [r4, #3516]
	add	r2, r4, #4096
	add	ip, r4, #8192
	clz	r1, r0
	mov	r1, r1, lsr #5
	str	r1, [r2, #3148]
	ldr	r1, [r4, #3520]
	str	r1, [r2, #3140]
	str	r3, [ip, #200]
	ldr	r3, [r4, #2384]
	ldr	r1, [r3, #600]
	strb	r1, [r2, #1808]
	ldr	r1, [r3, #604]
	strb	r1, [r2, #1809]
	ldr	r1, [r3, #608]
	strb	r1, [r2, #1811]
	ldr	r1, [r3, #612]
	strb	r1, [r2, #1812]
	ldr	r3, [r3, #652]
	str	r3, [r2, #3136]
	ldr	r3, [r4, #240]
	cmp	r3, #0
	beq	.L3548
	ldr	r1, [r4, #3532]
	add	r3, r4, #5888
	add	r3, r3, #16
	str	r3, [r4, #2392]
	add	r0, r0, #1
	str	r1, [ip, #2892]
	ldr	r3, [r4, #3536]
	str	r3, [ip, #2896]
	ldr	r1, [r4, #3504]
	str	r0, [r4, #3516]
	cmp	r1, #0
	bne	.L3548
	ldr	r2, [ip, #204]
	cmp	r2, #0
	beq	.L3557
.L3551:
	ldr	r3, [r2]
	ldr	r0, [r2, #4]
	ldr	r2, [r2, #1356]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L3551
.L3550:
	ldr	r3, .L3592+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3548
	sub	r2, fp, #20
	mov	r3, #4
	ldr	r0, [r4, #252]
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	r5
.L3548:
	ldr	ip, [r4, #3544]
	mov	r0, #0
	ldr	r1, [r4, #3548]
	ldr	r3, [r4, #3540]
	str	ip, [r4, #3540]
	ldr	r2, [r1, #320]
	rsb	r3, ip, r3
	add	r2, r2, r3
	str	r2, [r1, #320]
	ldr	r2, [r4, #3792]
	add	r3, r2, r3
	str	r3, [r4, #3792]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3543:
	cmp	r3, #1
	streqb	r3, [r4, #6]
	b	.L3554
.L3535:
	ldr	r3, [r4, #3504]
	cmp	r3, #0
	bne	.L3539
	ldr	r3, [r4, #236]
	cmp	r3, #0
	bne	.L3554
.L3552:
	ldr	r3, .L3592+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3539
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L3539:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L3582
.L3589:
	cmp	r3, #0
	moveq	r3, #2
	streqb	r3, [r4, #6]
	beq	.L3554
	b	.L3541
.L3590:
	ldr	r3, .L3592+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3554
	ldr	r3, [r4, #2384]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L3554
	mov	r3, #1
	ldr	r2, [r4, #3500]
	mov	r0, r3
	ldr	r1, .L3592+12
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, .L3592+4
	ldr	r5, [r3]
	cmp	r5, #0
	mvneq	r0, #0
	beq	.L3582
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #127
	blx	r5
	mvn	r0, #0
	b	.L3582
.L3588:
	mov	r3, r5
	ldr	r1, .L3592+16
	bl	dprint_vfmw
	str	r5, [r4, #256]
	b	.L3584
.L3591:
	ldr	r2, .L3592+4
	ldr	r5, [r2]
	cmp	r5, #0
	beq	.L3546
	mov	r2, r3
	mov	r1, #127
	ldr	r0, [r4, #252]
	blx	r5
.L3546:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r2, .L3592+20
	ldr	r1, .L3592+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3582
.L3587:
	bl	HEVC_ClearCurrPic
	ldr	r3, .L3592+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3530
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L3530:
	ldr	r3, [r4, #244]
	cmp	r3, #524288
	bls	.L3531
	ldr	r1, .L3592+28
	mov	r0, #0
	bl	dprint_vfmw
.L3531:
	ldr	r1, .L3592+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3582
.L3557:
	mov	r1, r2
	b	.L3550
.L3593:
	.align	2
.L3592:
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
	ldr	r0, [r0, #2336]
	mov	r1, #16
	mov	r10, r3
	mov	r9, r2
	mov	r6, #0
	str	r6, [fp, #-48]
	bl	BsGet
	mov	r1, #8
	mov	r7, r0
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #24
	and	r8, r0, #31
	ldr	r0, [r4, #2336]
	bl	BsBack
	ldr	r3, [r4, #3984]
	cmp	r5, r6
	str	r6, [r4, #3972]
	str	r3, [fp, #-48]
	beq	.L3596
	cmp	r5, #1
	bne	.L3744
	cmp	r9, #1
	beq	.L3745
	movw	r0, #31745
	cmp	r8, #25
	cmpeq	r7, r0
	moveq	r8, #1
	movne	r8, #0
	bne	.L3625
	ldr	r7, .L3755
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3626
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	r5
.L3626:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2356]
	subs	r5, r0, #0
	beq	.L3627
.L3741:
	cmp	r1, #0
	beq	.L3630
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3630:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3732
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L3604
.L3744:
	mov	r2, r5
	ldr	r1, .L3755+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
.L3604:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3596:
	cmp	r9, #1
	beq	.L3746
	bic	r7, r7, #512
	movw	r3, #31745
	cmp	r7, r3
	beq	.L3747
.L3639:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3625:
	movw	r3, #32257
	cmp	r7, r3
	movne	r0, r5
	bne	.L3604
	ldr	r1, .L3755+8
	movw	r3, #2549
	ldr	r2, .L3755+12
	mov	r0, r8
	bl	dprint_vfmw
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3732
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2356]
	mvn	r0, #0
	b	.L3604
.L3747:
	ldr	r1, .L3755+16
	movw	r3, #2404
	ldr	r2, .L3755+12
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3732
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2356]
	mvn	r0, #0
	b	.L3604
.L3627:
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r4, #3972]
	bhi	.L3748
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r4, #3976]
	add	r3, r3, r0
	ldr	r0, [r4, #252]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r6, r0, #0
	bne	.L3749
	ldr	r5, .L3755+20
	mov	r2, #5
	ldr	r1, .L3755+24
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2356]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r4, #3972]
	add	r1, r1, #6
	blx	r3
	ldr	r1, [r4, #2356]
	ldr	r0, [r4, #3972]
	add	r3, r0, #5
	str	r3, [r4, #3972]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L3632
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L3633
	add	r2, r0, #10
	ldr	r1, .L3755+28
	movw	r3, #2507
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3634
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2356]
.L3634:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3635
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L3635:
	ldr	r0, [r4, #252]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movwne	r3, #2514
	beq	.L3732
.L3731:
	ldr	r2, .L3755+12
	mov	r0, #0
	ldr	r1, .L3755+32
	bl	dprint_vfmw
.L3732:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3745:
	movw	r3, #31745
	cmp	r7, r3
	cmpeq	r10, #2
	moveq	r5, #1
	movne	r5, #0
	cmp	r8, #25
	movne	r5, #0
	andeq	r5, r5, #1
	cmp	r5, #0
	bne	.L3750
	movw	r2, #32257
	cmp	r7, r2
	beq	.L3751
	cmp	r7, r3
	bne	.L3752
.L3614:
	ldr	r1, [r4, #2356]
.L3738:
	cmp	r1, #0
	beq	.L3616
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2356]
	mov	r0, r5
	b	.L3604
.L3746:
	movw	r0, #31745
	cmp	r8, #25
	cmpeq	r7, r0
	moveq	r8, #1
	movne	r8, #0
	bne	.L3599
	ldr	r7, .L3755
	ldr	r6, [r7]
	cmp	r6, #0
	beq	.L3600
	mov	r3, r5
	mov	r2, r5
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	r6
.L3600:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2356]
	subs	r5, r0, #0
	beq	.L3601
	cmp	r1, #0
	beq	.L3606
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3606:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3732
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L3732
.L3599:
	movw	r3, #32257
	cmp	r7, r3
	bne	.L3639
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3616
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2356]
	mov	r0, r8
	b	.L3604
.L3748:
	ldr	r1, .L3755+28
	movw	r3, #2483
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3630
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2356]
	b	.L3630
.L3616:
	mov	r0, #0
	b	.L3604
.L3601:
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r4, #3972]
	bls	.L3605
	ldr	r1, .L3755+28
	movw	r3, #2318
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3606
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2356]
	b	.L3606
.L3633:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2356]
	ldr	r3, [r4, #3972]
	ldr	r2, [r2, #72]
	add	r3, r3, r2
	str	r3, [r4, #3972]
.L3632:
	ldr	r0, [r4, #252]
	ldr	r6, .L3755+36
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L3636
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #252]
	ldr	r3, [r5, #44]
	ldr	r1, [r4, #3972]
	ldr	r2, [r6, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #252]
.L3636:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	movwne	r3, #2537
	beq	.L3614
	b	.L3731
.L3752:
	mov	r1, #8
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	ldr	r0, [r4, #2336]
	ubfx	r5, r5, #1, #6
	bl	BsSkip
	cmp	r5, #49
	beq	.L3753
.L3624:
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3616
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2356]
	b	.L3604
.L3750:
	ldr	r7, .L3755
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3619
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	r5
.L3619:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2356]
	subs	r5, r0, #0
	beq	.L3738
	b	.L3741
.L3605:
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r4, #3976]
	add	r3, r3, r0
	ldr	r0, [r4, #252]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r6, r0, #0
	bne	.L3754
	ldr	r5, .L3755+20
	mov	r2, #5
	ldr	r1, .L3755+24
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2356]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r4, #3972]
	add	r1, r1, #6
	blx	r3
	ldr	r1, [r4, #2356]
	ldr	r0, [r4, #3972]
	add	r3, r0, #5
	str	r3, [r4, #3972]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L3609
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L3610
	add	r2, r0, #10
	ldr	r1, .L3755+28
	movw	r3, #2342
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3611
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2356]
.L3611:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L3612
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L3612:
	ldr	r0, [r4, #252]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movwne	r3, #2349
	beq	.L3732
	b	.L3731
.L3610:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2356]
	ldr	r3, [r4, #3972]
	ldr	r2, [r2, #72]
	add	r3, r3, r2
	str	r3, [r4, #3972]
.L3609:
	ldr	r0, [r4, #252]
	ldr	r6, .L3755+36
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L3613
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #252]
	ldr	r3, [r5, #44]
	ldr	r1, [r4, #3972]
	ldr	r2, [r6, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #252]
.L3613:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	beq	.L3614
	movw	r3, #2377
	b	.L3731
.L3751:
	ldr	r0, [r4, #2336]
	mov	r1, #16
	bl	BsSkip
	mov	r0, r9
	b	.L3604
.L3753:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	bne	.L3624
	ldr	r3, [r4, #2356]
	ldr	r0, [r4, #2336]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	ldr	r0, [r4, #2336]
	mov	r1, #24
	bl	BsSkip
	mov	r0, #2
	b	.L3604
.L3749:
	mov	r0, r5
	movw	r3, #2495
	ldr	r2, .L3755+12
	ldr	r1, .L3755+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3604
.L3754:
	mov	r0, r5
	movw	r3, #2330
	ldr	r2, .L3755+12
	ldr	r1, .L3755+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3604
.L3756:
	.align	2
.L3755:
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
	ldr	r0, [r0, #2568]
	cmp	r0, #0
	beq	.L3769
	add	r2, r4, #2576
	mov	r5, #0
	add	r2, r2, #8
	mov	r3, r5
.L3760:
	ldr	r1, [r2, #4]!
	add	r3, r3, #1
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	cmp	r1, #0
	addeq	r5, r5, #1
	cmp	r3, r0
	bne	.L3760
.L3761:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L3761
	cmp	r5, #0
	ble	.L3763
.L3767:
	ldr	r1, [r4, #2568]
	cmp	r1, #0
	beq	.L3764
	ldr	r3, [r4, #2588]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3771
	add	r2, r4, #2576
	mov	r3, #0
	add	r2, r2, #12
	b	.L3768
.L3765:
	ldr	r0, [r2, #4]!
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L3771
.L3768:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3765
.L3764:
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	subs	r5, r5, #1
	bne	.L3767
.L3763:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3771:
	mov	r1, r3
	b	.L3764
.L3769:
	mov	r5, r0
	b	.L3761
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
	ldr	r3, [r0, #2356]
	add	r5, r0, #4096
	ldr	r2, .L3849
	mov	ip, #0
	mov	r4, r0
	ldr	r1, [r3, #16]
	str	r1, [r5, #124]
	ldr	r1, [r3, #28]
	str	r1, [r5, #120]
	ldr	r6, [r3, #24]
	str	r6, [r5, #128]
	ldr	r1, [r0, #252]
	strb	ip, [r0, #3]
	ldr	r2, [r2, r1, asl #2]
	ldrsb	r1, [r2, #44]
	cmp	r1, #1
	beq	.L3838
.L3782:
	ldr	r3, [r5, #248]
	cmp	r3, #1
	beq	.L3839
.L3783:
	ldr	r2, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r2, r3
	bcs	.L3840
	ldrb	r3, [r4, #3489]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3841
	mov	r0, r4
	bl	HEVC_PicTypeStatistic
	mov	r0, r4
	bl	HEVC_CalcStreamBits
	ldr	r3, [r5, #248]
	cmp	r3, #2
	beq	.L3797
	ldrb	r3, [r5, #97]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3842
.L3798:
	mov	r0, r4
	bl	HEVC_WriteSliceMsg
	cmp	r0, #0
	bne	.L3843
.L3801:
	ldr	r2, [r5, #132]
	mov	r0, #0
	ldr	ip, [r4, #2872]
	mov	r3, #1
	ldr	r1, [r4, #2876]
	str	r2, [r4, #304]
	ldr	r2, [r5, #108]
	str	ip, [r4, #3532]
	str	r1, [r4, #3536]
	str	r2, [r4, #260]
	str	r3, [r4, #172]
.L3786:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3842:
	mov	r0, r4
	bl	HEVC_DecList
	cmp	r0, #0
	bne	.L3844
	mov	r0, r4
	bl	HEVC_IsRefListWrong
	cmp	r0, #0
	beq	.L3798
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r1, .L3849+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3786
.L3839:
	ldr	r3, [r5, #124]
	clz	r7, r6
	sub	r3, r3, #16
	mov	r7, r7, lsr #5
	cmp	r3, #4
	cmpls	r6, #0
	bne	.L3845
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L3846
.L3785:
	add	r3, r4, r6
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	andeq	r3, r7, #1
	cmp	r3, #0
	beq	.L3787
	ldr	r3, [r4, #2568]
	cmp	r3, #0
	beq	.L3787
	mov	r0, r4
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L3787
	ldr	r2, .L3849+8
	mov	r0, #1
	ldr	r1, .L3849+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3786
.L3845:
	mov	r0, r4
	bl	HEVC_IsPVRFlushPic
	cmp	r0, #0
	beq	.L3785
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	beq	.L3785
	b	.L3846
.L3838:
	ldr	r1, [r2, #160]
	cmp	r1, #1
	bne	.L3782
	ldr	r2, [r2, #164]
	cmp	r2, #2
	bne	.L3782
	ldr	r1, [r3, #16]
	bl	HEVC_Get_Last_IDR_Frame_Info
	b	.L3782
.L3797:
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3801
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
	b	.L3801
.L3787:
	ldr	r1, [r4, #2384]
	ldr	r3, [r1, #12]
	cmp	r3, #0
	bne	.L3788
	ldr	r3, [r5, #120]
	cmp	r7, #0
	ldr	r2, [r4, #2368]
	add	r3, r3, #90
	ldr	r0, [r2, r3, asl #2]
	beq	.L3788
	add	r6, r4, r6, lsl #2
	ldr	r3, [r6, #212]
	cmp	r3, #-2147483647
	beq	.L3788
	ldr	r2, [r5, #108]
	add	r0, r3, r0
	cmp	r2, r0
	bge	.L3788
	ldr	r0, [r5, #124]
	cmp	r0, #21
	bne	.L3788
	ldr	r1, .L3849+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_CRAOutputFrame
	mov	r3, #-2147483647
	str	r3, [r6, #212]
	ldr	r1, [r4, #2384]
.L3788:
	ldr	r3, [r1, #8]
	cmp	r3, #2
	beq	.L3790
	ldr	r3, [r1, #24]
	mov	r0, r4
	cmp	r3, #2
	beq	.L3847
	bl	HEVC_RefPicProcess
	cmp	r0, #0
	bne	.L3803
.L3790:
	mov	r0, r4
	bl	HEVC_InitPic
	cmn	r0, #2
	beq	.L3786
	cmp	r0, #0
	bne	.L3848
	ldr	r3, [r4, #240]
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r4, #240]
	bl	HEVC_SetScalingList
	mov	r0, r4
	bl	HEVC_WritePicMsg
	cmp	r0, #0
	beq	.L3783
	ldr	r1, .L3849+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3786
.L3847:
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	b	.L3790
.L3846:
	ldr	r2, .L3849+8
	mov	r0, #1
	ldr	r1, .L3849+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3786
.L3841:
	ldr	r1, .L3849+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3786
.L3840:
	ldr	r1, .L3849+32
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	ldr	r2, [r4, #152]
	cmp	r3, r2
	bcc	.L3795
	ldr	r1, .L3849+36
	ldr	r5, [r1]
	cmp	r5, #0
	beq	.L3795
	str	r3, [fp, #-36]
	mov	r1, #108
	str	r2, [fp, #-32]
	mov	r3, #8
	sub	r2, fp, #36
	ldr	r0, [r4, #252]
	blx	r5
.L3795:
	ldr	r1, .L3849+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L3786
.L3844:
	mov	r2, r0
	ldr	r1, .L3849+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3786
.L3843:
	ldr	r1, .L3849+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3786
.L3848:
	ldr	r1, .L3849+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3786
.L3803:
	mvn	r0, #0
	b	.L3786
.L3850:
	.align	2
.L3849:
	.word	s_pstVfmwChan
	.word	.LC487
	.word	.LANCHOR0+980
	.word	.LC479
	.word	.LC480
	.word	.LC482
	.word	.LC478
	.word	.LC485
	.word	.LC483
	.word	g_event_report
	.word	.LC484
	.word	.LC486
	.word	.LC488
	.word	.LC481
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
	ldr	ip, [r0, #2356]
	mov	r4, r0
	ldr	r3, [ip, #8]
	cmp	r3, #0
	ldrne	r1, [r0, #244]
	movne	r2, ip
	movne	r3, #0
	beq	.L3856
.L3855:
	ldr	r0, [r2, #44]
	add	r3, r3, #1
	add	r2, r2, #28
	add	r1, r1, r0
	str	r1, [r4, #244]
	ldr	r0, [ip, #8]
	cmp	r0, r3
	bhi	.L3855
.L3856:
	mov	r3, #0
	strb	r3, [ip]
	ldr	r3, [r4, #2356]
	ldr	r2, [r3, #16]
	sub	r2, r2, #36
	cmp	r2, #1
	bls	.L3997
.L3854:
	ldr	r2, [r3, #4]
	add	r2, r2, #16
	str	r2, [r3, #4]
	ldr	r1, [r4, #2356]
	ldr	r2, [r1, #16]
	cmp	r2, #49
	ldrls	pc, [pc, r2, asl #2]
	b	.L3857
.L3859:
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3858
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3860
	.word	.L3861
	.word	.L3862
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3863
	.word	.L3863
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3857
	.word	.L3864
	.word	.L3865
.L3997:
	mov	r2, #1
	strb	r2, [r4, #3]
	b	.L3854
.L3865:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	beq	.L3998
.L3881:
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3984
.L3986:
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2356]
.L3983:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3858:
	mov	r0, r4
	bl	HEVC_DecSlice
	cmn	r0, #2
	beq	.L3983
	cmp	r0, #0
	beq	.L3984
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3995
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3995:
	ldr	r3, .L4000
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3985
.L3987:
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r5
.L3985:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3860:
	mov	r0, r4
	bl	HEVC_DecVPS
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3866
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3866:
	cmp	r5, #0
	bne	.L3999
.L3984:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3861:
	mov	r0, r4
	bl	HEVC_DecSPS
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3871
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3871:
	cmp	r5, #0
	beq	.L3984
	ldr	r6, .L4000
	mov	r0, #1
	ldr	r1, .L4000+4
	bl	dprint_vfmw
	ldr	r7, [r6]
	cmp	r7, #0
	bne	.L3991
	b	.L3985
.L3862:
	mov	r0, r4
	bl	HEVC_DecPPS
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3873
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3873:
	cmp	r5, #0
	beq	.L3984
	ldr	r6, .L4000
	mov	r0, #1
	ldr	r1, .L4000+8
	bl	dprint_vfmw
	ldr	r7, [r6]
	cmp	r7, #0
	beq	.L3985
.L3991:
	sub	r2, fp, #28
	mvn	r5, #0
	mov	r3, #4
	mov	r1, #100
	str	r5, [r2, #-4]!
	ldr	r0, [r4, #252]
	blx	r7
	ldr	r6, [r6]
	cmp	r6, #0
	beq	.L3985
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3863:
	mov	r0, r4
	bl	HEVC_DecSEI
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3874
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3874:
	cmp	r5, #0
	beq	.L3984
	ldr	r1, .L4000+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3995
.L3864:
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3879
	cmp	r1, #0
	beq	.L3878
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3878:
	ldrb	r3, [r4, #3489]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3984
.L3879:
	add	r5, r4, #2528
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
	bne	.L3984
	ldr	r5, .L4000
	ldr	r7, [r5]
	cmp	r7, #0
	beq	.L3880
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	r7
.L3880:
	ldrb	r3, [r4, #3489]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3984
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L3984
.L3883:
	ldr	r5, [r5]
	cmp	r5, #0
	bne	.L3987
	b	.L3985
.L3857:
	ldr	r1, .L4000+16
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r1, [r4, #2356]
	ldr	r3, [r1, #16]
	cmp	r3, #63
	bhi	.L3884
	cmp	r1, #0
	bne	.L3986
	b	.L3984
.L3884:
	ldr	r5, .L4000
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L3885
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r6
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3886
.L3887:
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L3886:
	ldr	r5, [r5]
	cmp	r5, #0
	beq	.L3984
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L3984
.L3885:
	cmp	r1, #0
	bne	.L3887
	b	.L3984
.L3999:
	ldr	r6, .L4000
	mov	r0, #1
	ldr	r1, .L4000+20
	bl	dprint_vfmw
	ldr	r7, [r6]
	cmp	r7, #0
	bne	.L3991
	b	.L3985
.L3998:
	ldr	r5, .L4000
	strb	r0, [r4, #9]
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L3882
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r6
.L3882:
	ldrb	r3, [r4, #3489]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3881
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L3881
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L3883
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
	b	.L3883
.L4001:
	.align	2
.L4000:
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	ip, .L4018
	mov	r4, r0
	mov	r3, #0
	mov	r6, r1
	add	r0, r0, #4160
	str	r3, [r2]
	mov	r1, r3
	str	r3, [r6]
	mov	r5, r2
	ldr	r3, [ip, #48]
	movw	r2, #1356
	add	r0, r0, #32
	add	r7, r4, #4096
	blx	r3
	ldr	r3, [r4, #2356]
	mov	r0, r4
	ldr	r2, [r3, #16]
	str	r2, [r7, #124]
	ldr	r2, [r3, #28]
	str	r2, [r7, #120]
	ldr	r3, [r3, #24]
	str	r3, [r7, #128]
	bl	HEVC_DecSliceSegmentHeader
	cmp	r0, #0
	bne	.L4015
	ldr	r1, [r7, #132]
	mov	ip, #1888
	ldr	r2, [r4, #2348]
	movw	lr, #12660
	ldr	r0, [r4, #2344]
	ldr	r3, [r7, #248]
	mla	r2, ip, r1, r2
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	ldr	r2, [r2, #32]
	str	r3, [r6]
	ldr	r1, [r4, #2368]
	mla	lr, lr, r2, r0
	ldr	r6, [r4, #2384]
	ldr	r2, [r1, #184]
	ldr	r3, [r1, #64]
	ldr	r7, [r1, #68]
	ldr	ip, [r6, #872]
	ldr	r1, [lr, #184]
	ldr	r0, [lr, #64]
	subs	r2, r1, r2
	ldr	r1, [lr, #68]
	movne	r2, #1
	cmp	ip, #1
	beq	.L4016
.L4007:
	cmp	r0, r3
	moveq	r3, r2
	orrne	r3, r2, #1
	cmp	r1, r7
	moveq	r0, r3
	orrne	r0, r3, #1
	cmp	r0, #0
	movne	r0, #0
	movne	r3, #1
	strne	r3, [r5]
.L4005:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4015:
	ldr	r1, .L4018+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4018+8
	ldr	r5, [r3]
	cmp	r5, #0
	mvneq	r0, #0
	beq	.L4005
	sub	r2, fp, #28
	ldr	r0, [r4, #252]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	r5
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4016:
	ldr	ip, [lr, #96]
	ldr	lr, [lr, #88]
	cmp	ip, lr
	movcc	ip, lr
	str	ip, [r6, #932]
	ldr	lr, [r4, #2368]
	ldr	r6, [r4, #2384]
	ldr	ip, [lr, #96]
	ldr	lr, [lr, #88]
	ldr	r4, [r6, #932]
	cmp	ip, lr
	movcc	ip, lr
	cmp	ip, #8
	movls	lr, #0
	movhi	lr, #1
	cmp	r4, #8
	movne	lr, #0
	cmp	lr, #0
	beq	.L4017
.L4008:
	mov	ip, #1
	str	ip, [r6, #936]
	str	ip, [r5]
	b	.L4007
.L4017:
	sub	ip, ip, #8
	cmp	r4, #8
	clz	ip, ip
	mov	ip, ip, lsr #5
	movle	ip, #0
	cmp	ip, #0
	beq	.L4007
	b	.L4008
.L4019:
	.align	2
.L4018:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC494
	.word	g_event_report
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
	bne	.L4022
	ldrb	r3, [r4, #3489]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4024
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4022:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4024:
	ldr	r2, .L4025
	ldr	r1, .L4025+4
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4026:
	.align	2
.L4025:
	.word	.LANCHOR0+996
	.word	.LC495
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
	ldr	r2, [r0, #204]
	cmp	r2, #0
	beq	.L4030
	mov	r0, #0
.L4029:
	ldr	r3, [r2]
	ldr	r1, [r2, #4]
	ldr	r2, [r2, #1356]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L4029
	ldmfd	sp, {fp, sp, pc}
.L4030:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetPicStreamSize, .-HEVC_GetPicStreamSize
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
	ldr	r5, .L4038
	ldr	r4, [r5]
	cmp	r4, #0
	beq	.L4036
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4036:
	ldr	r6, .L4038+4
	mov	r0, #372
	movt	r0, 10
	ldr	r3, [r6, #216]
	blx	r3
	cmp	r0, #0
	str	r0, [r5]
	beq	.L4037
	mov	r2, #372
	ldr	r3, [r6, #48]
	movt	r2, 10
	mov	r1, r4
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4037:
	movw	r2, #15227
	ldr	r1, .L4038+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4039:
	.align	2
.L4038:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC496
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
	ldr	r4, .L4045
	ldr	r0, [r4]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L4045+4
	ldr	r3, [r3, #220]
	blx	r3
	mov	r3, #0
	str	r3, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4046:
	.align	2
.L4045:
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
	ldr	r3, .L4063
	mov	r5, r1
	mov	r4, r0
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L4057
	add	r7, r0, #4096
	ldr	r6, .L4063+4
	movw	r2, #27112
	mov	r1, #0
	ldr	r8, [r7, #1800]
	ldr	r3, [r6, #48]
	blx	r3
	mov	r3, #0
	str	r8, [r7, #1800]
	str	r5, [r4, #2384]
	str	r3, [r4, #2392]
	ldr	r3, [r5, #28]
	cmp	r3, #25
	beq	.L4058
	mov	r3, #17
	mov	r1, #65
	str	r3, [r4, #156]
	mov	r2, #200
	str	r3, [r4, #160]
	mov	r3, #210
	str	r1, [r4, #164]
	str	r2, [r4, #152]
	str	r3, [r4, #168]
.L4051:
	ldr	r0, [r5, #592]
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L4059
	ldr	r2, [r4, #156]
	movw	r9, #12660
	ldr	r0, [r4, #2384]
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
	str	r10, [r4, #2344]
	mla	r0, r9, r3, r0
	ldr	r3, [r4, #168]
	mul	r2, r7, r2
	add	r3, r3, #1
	str	ip, [r4, #2340]
	mov	r10, r3, asl #7
	sub	r3, r10, r3, asl #5
	add	r10, r1, r0
	str	r10, [fp, #-48]
	ldr	r10, [r4, #164]
	mla	r0, r8, r10, r0
	ldr	r10, [fp, #-48]
	str	r10, [r4, #2348]
	add	r10, r0, r2
	add	r3, r10, r3
	add	r0, r1, r0
	add	r10, r1, r10
	add	r1, r1, r3
	str	r1, [r4, #2376]
	ldr	r1, [r4, #2384]
	str	r10, [r4, #2380]
	ldr	r10, [r4, #168]
	str	r0, [r4, #2388]
	ldr	r1, [r1, #596]
	add	r3, r3, r10, lsl #2
	cmp	r3, r1
	bhi	.L4060
	ldr	r5, [r5, #624]
	cmp	r5, #0
	beq	.L4061
.L4054:
	ldr	r3, [r6, #48]
	mov	r1, #0
	blx	r3
	ldr	r3, [r4, #168]
	mov	r1, #0
	ldr	r5, [r6, #48]
	add	r3, r3, #1
	ldr	r0, [r4, #2380]
	mov	r2, r3, asl #7
	sub	r2, r2, r3, asl #5
	blx	r5
	ldr	r2, [r4, #168]
	ldr	r3, [r6, #48]
	mov	r1, #0
	ldr	r0, [r4, #2376]
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
	ldr	r0, [r4, #2340]
	sub	r1, r1, #132
	ldr	lr, [r4, #2344]
	sub	r3, r3, #12608
	add	r1, r0, r1
	ldr	r0, [r4, #2348]
	sub	r3, r3, #52
	sub	r2, r2, #1888
	str	r1, [r4, #2364]
	add	r3, lr, r3
	add	r2, r0, r2
	str	r3, [r4, #2368]
	str	r2, [r4, #2372]
	mov	r0, r4
	str	ip, [r1, #4]
	ldr	r3, [r4, #2372]
	ldr	r2, [r4, #160]
	str	r2, [r3, #28]
	ldr	r3, [r4, #2368]
	ldr	r2, [r4, #164]
	str	r2, [r3, #56]
	bl	HEVC_InitScalingOrderTable
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #252]
	beq	.L4062
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	bl	HEVC_InitDecPara
	add	r3, r4, #8192
	mov	r0, #0
	movw	r1, #9999
	str	r0, [r3, #2960]
	mov	r2, #1
	ldr	r3, [r4, #164]
	str	r1, [r4, #260]
	strb	r2, [r4]
	str	r3, [r4, #304]
.L4056:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4061:
	mov	r2, lr
	mov	r0, ip
	ldr	r3, [r6, #48]
	mov	r1, r5
	blx	r3
	ldr	r2, [r4, #160]
	ldr	r3, [r6, #48]
	mov	r1, r5
	ldr	r0, [r4, #2344]
	mul	r2, r9, r2
	blx	r3
	ldr	r2, [r4, #164]
	mov	r1, r5
	ldr	r3, [r6, #48]
	ldr	r0, [r4, #2348]
	mul	r2, r8, r2
	blx	r3
	ldr	r2, [r4, #152]
	ldr	r0, [r4, #2388]
	mul	r2, r7, r2
	b	.L4054
.L4058:
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
	b	.L4051
.L4060:
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L4063+8
	ldr	r1, .L4063+12
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4056
.L4057:
	mov	r0, r3
	ldr	r2, .L4063+8
	ldr	r1, .L4063+16
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4056
.L4062:
	ldr	r2, .L4063+8
	mov	r0, #0
	ldr	r1, .L4063+20
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4056
.L4059:
	ldr	r2, .L4063+8
	ldr	r1, .L4063+24
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4056
.L4064:
	.align	2
.L4063:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1016
	.word	.LC498
	.word	.LC61
	.word	.LC499
	.word	.LC497
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
	beq	.L4068
	ldrb	r3, [r0, #3489]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4068
	add	r1, r0, #12672
	add	lr, r0, #26880
	add	r1, r1, #40
	add	lr, lr, #232
.L4074:
	ldr	r3, [r1, #48]
	cmp	r3, #0
	bne	.L4069
	cmp	r1, #0
	beq	.L4070
	ldr	ip, [r4, #2568]
	cmp	ip, #0
	beq	.L4070
	ldr	r2, [r4, #2588]
	cmp	r2, r1
	beq	.L4069
	add	r2, r4, #2576
	add	r2, r2, #12
	b	.L4071
.L4072:
	ldr	r0, [r2, #4]!
	cmp	r0, r1
	beq	.L4069
.L4071:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L4072
.L4070:
	ldr	r0, [r4, #252]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L4068
	cmn	r0, #1
	beq	.L4093
.L4092:
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4068:
	mov	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4069:
	add	r1, r1, #720
	cmp	r1, lr
	bne	.L4074
	add	r0, r4, #5504
	sub	r2, fp, #24
	sub	r1, fp, #28
	add	r0, r0, #48
	bl	GetQueueImgNum
	mov	r0, r4
	bl	HEVC_PrintFrameStoreState
	ldr	r1, .L4094
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r2, [r4, #180]
	ldr	r0, [r4, #2568]
	ldr	r3, [fp, #-28]
	sub	r2, r2, #2
	ldr	r1, [fp, #-24]
	rsb	r2, r0, r2
	add	r0, r3, r1
	cmp	r0, r2
	bge	.L4092
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L4094+4
	ldr	r1, .L4094+8
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4093:
	ldr	r1, .L4094+12
	mov	r0, #1
	bl	dprint_vfmw
	add	r1, r4, #5504
	add	r1, r1, #48
	ldr	r0, [r4, #252]
	bl	FSP_ClearNotInVoQueue
	b	.L4092
.L4095:
	.align	2
.L4094:
	.word	.LC501
	.word	.LANCHOR0+1032
	.word	.LC502
	.word	.LC500
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
	beq	.L4166
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L4167
	ldr	r2, [r0, #2384]
	ldrb	ip, [r0, #7]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	cmp	ip, #1
	mov	r3, r3, asl #16
	and	r3, r3, #458752
	str	r3, [r0, #248]
	beq	.L4100
	ldr	r3, [r2, #872]
	cmp	r3, #1
	beq	.L4168
.L4101:
	mov	r0, r4
	bl	HEVC_ReceivePacket
	ldr	r3, [r4, #2356]
	str	r3, [r4, #2360]
	mov	r5, r0
.L4102:
	cmp	r5, #0
	mov	r0, #0
	strb	r0, [r4, #7]
	beq	.L4169
.L4164:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4168:
	ldr	r3, [r2, #920]
	cmp	r3, #1
	bne	.L4101
	ldr	r3, [r0, #328]
	cmp	r3, #1
	bne	.L4101
	ldr	r3, [r0, #2360]
	mov	r0, lr
	str	lr, [r4, #328]
	strb	lr, [r4, #7]
	str	r3, [r4, #2356]
	b	.L4164
.L4169:
	str	r5, [r3, #4]
	ldr	r3, [r4, #2356]
	ldr	r0, [r4, #2336]
	ldr	r7, .L4176
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2336]
	bl	BsSkip
	ldr	r3, [r4, #252]
	ldr	r3, [r7, r3, asl #2]
	ldrsb	r9, [r3, #44]
	cmp	r9, #1
	movne	r6, #3
	movne	r8, #2
	beq	.L4170
.L4103:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2336]
	ldr	r9, [r4, #2356]
	bl	BsGet
	mov	r1, #6
	str	r0, [r9, #16]
	ldr	r0, [r4, #2336]
	ldr	r9, [r4, #2356]
	bl	BsGet
	str	r0, [r9, #24]
	ldr	r9, [r4, #2356]
	ldr	r2, [r9, #24]
	cmp	r2, #0
	bne	.L4171
	mov	r1, #3
	ldr	r0, [r4, #2336]
	bl	BsGet
	str	r0, [r9, #28]
	ldr	r9, [r4, #2356]
	ldr	r3, [r9, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r9, #28]
	ldrne	r9, [r4, #2356]
	ldr	r0, [r9, #16]
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	mov	r10, r0
	beq	.L4172
	mov	r3, #0
	str	r3, [r9, #4]
	ldr	r3, [r4, #2356]
	add	r0, r4, #2528
	add	r0, r0, #4
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2336]
	bl	BsSkip
	cmp	r6, #1
	cmpeq	r8, #1
	moveq	r6, #1
	movne	r6, #0
	cmp	r5, #1
	moveq	r5, #0
	andne	r5, r6, #1
	cmp	r5, #0
	beq	.L4124
	mov	r1, #16
	ldr	r0, [r4, #2336]
	bl	BsSkip
.L4124:
	mov	r1, #1
	ldr	r0, [r4, #2336]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2336]
	ldr	r5, [r4, #2356]
	bl	BsGet
	mov	r1, #6
	str	r0, [r5, #16]
	ldr	r0, [r4, #2336]
	ldr	r5, [r4, #2356]
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #24]
	ldr	r0, [r4, #2336]
	ldr	r5, [r4, #2356]
	bl	BsGet
	str	r0, [r5, #28]
	ldr	r2, [r4, #2356]
	ldr	r3, [r2, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r2, #28]
.L4113:
	mov	r0, r4
	bl	HEVC_DecOneNal
	cmn	r0, #2
	beq	.L4164
	cmp	r0, #0
	streq	r0, [r4, #3544]
	beq	.L4164
	ldr	r1, .L4176+4
	mov	r0, #22
	bl	dprint_vfmw
.L4165:
	mvn	r0, #0
	b	.L4164
.L4100:
	ldr	r3, [r0, #2356]
	cmp	r3, #0
	movne	r5, #0
	mvneq	r5, #0
	cmp	r3, #0
	bne	.L4102
	mov	r0, lr
	ldr	r1, .L4176+8
	bl	dprint_vfmw
	mov	r0, r5
	b	.L4164
.L4170:
	ldr	r8, [r3, #156]
	mov	r0, r4
	ldr	r6, [r3, #160]
	ldr	r3, [r3, #164]
	mov	r1, r8
	mov	r2, r6
	bl	HEVC_VES_Splitter
	cmp	r0, #2
	beq	.L4128
	cmp	r0, #1
	bne	.L4164
	b	.L4103
.L4171:
	ldr	r1, .L4176+12
	mov	r3, #0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L4165
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r4, #2356]
	b	.L4164
.L4172:
	sub	r2, fp, #48
	sub	r1, fp, #52
	mov	r0, r4
	bl	HEVC_InquireSliceProperty
	subs	r3, r0, #0
	bne	.L4108
	ldr	r5, [fp, #-52]
	cmp	r5, #1
	beq	.L4173
.L4109:
	ldr	r5, [fp, #-48]
	cmp	r5, #1
	bne	.L4113
	ldr	r3, [r4, #2356]
	mov	r0, r4
	ldr	r3, [r3, #24]
	add	r3, r4, r3
	ldrb	r6, [r3, #4]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L4174
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L4175
.L4116:
	ldr	r0, [r4, #252]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L4113
	sub	r3, fp, #56
	ldr	r0, [r4, #252]
	sub	r2, fp, #60
	sub	r1, fp, #64
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4, #2384]
	ldr	r0, [r3, #732]
	cmp	r0, #1
	bne	.L4113
	ldr	r5, [fp, #-56]
	cmp	r5, #0
	bgt	.L4119
	ldr	r3, [fp, #-60]
	cmp	r3, #32
	bgt	.L4119
	ldr	r3, [r4, #2392]
	cmp	r3, #0
	bne	.L4119
	ldr	r2, [fp, #-48]
	cmp	r2, #0
	beq	.L4113
	ldr	r3, [r4, #240]
	cmp	r3, #0
	beq	.L4113
	ldr	r3, [r4, #2368]
	ldr	r1, [r4, #320]
	ldr	lr, [r3, #68]
	cmp	lr, r1
	beq	.L4113
	ldr	ip, [r3, #64]
	ldr	r3, [r4, #324]
	subs	r6, ip, r3
	movne	r6, #1
	cmp	r5, #0
	movne	r6, #0
	cmp	r6, #0
	beq	.L4113
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L4176+16
	bl	dprint_vfmw
	ldr	r3, [r4, #2368]
	ldr	r1, .L4176+20
	ldr	r2, [r3, #68]
	ldr	r5, [r1]
	str	r2, [r4, #320]
	cmp	r5, #0
	ldr	r3, [r3, #64]
	str	r3, [r4, #324]
	beq	.L4113
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
	b	.L4113
.L4167:
	mov	r0, lr
	ldr	r1, .L4176+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4164
.L4128:
	mov	r5, r9
	b	.L4103
.L4108:
	ldr	r1, .L4176+28
	mov	r0, r10
	bl	dprint_vfmw
	ldr	r1, [r4, #2356]
	cmp	r1, #0
	beq	.L4121
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2356]
.L4121:
	ldr	r3, .L4176+20
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4122
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	r5
.L4122:
	ldr	r3, [r4, #252]
	ldr	r3, [r7, r3, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	bne	.L4165
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L4165
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L4165
	add	r3, r4, #8192
	ldrb	r5, [r3, #2904]	@ zero_extendqisi2
	cmp	r5, #0
	bne	.L4165
	ldr	r3, .L4176+32
	add	r0, r4, #11072
	add	r0, r0, #24
	mov	r2, #56
	mov	r1, r5
	mov	r6, #0
	ldr	r3, [r3, #48]
	mov	r7, #0
	blx	r3
	add	r3, r4, #2880
	mvn	r0, #0
	strd	r6, [r3, #32]
	strd	r6, [r3, #8]
	strd	r6, [r3, #16]
	strd	r6, [r3, #24]
	str	r5, [r4, #2868]
	b	.L4164
.L4173:
	ldr	r2, [r4, #204]
	cmp	r2, #0
	bne	.L4110
	ldrb	r3, [r4, #3489]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4109
	ldr	r2, .L4176+36
	ldr	r1, .L4176+40
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	b	.L4109
.L4110:
	ldr	ip, [r4, #2356]
	add	r0, r4, #2528
	mov	r2, #21
	add	r0, r0, #4
	ldr	r1, .L4176+44
	str	r3, [ip, #4]
	bl	BsInit
	mov	r1, #40
	ldr	r0, [r4, #2336]
	bl	BsSkip
	ldr	r3, [r4, #2356]
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
	b	.L4164
.L4166:
	mov	r0, r1
	ldr	r1, .L4176+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4164
.L4174:
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L4116
	mov	r0, r6
	ldr	r2, .L4176+52
	ldr	r1, .L4176+56
	bl	dprint_vfmw
	b	.L4116
.L4175:
	mov	r0, r5
	ldr	r2, .L4176+52
	ldr	r1, .L4176+60
	bl	dprint_vfmw
	b	.L4116
.L4119:
	ldr	r2, [r4, #252]
	mov	r3, #1
	mvn	r0, #1
	ldr	r2, [r7, r2, asl #2]
	str	r3, [r2, #1528]
	strb	r3, [r4, #7]
	b	.L4164
.L4177:
	.align	2
.L4176:
	.word	s_pstVfmwChan
	.word	.LC509
	.word	.LC505
	.word	.LC506
	.word	.LC507
	.word	g_event_report
	.word	.LC504
	.word	.LC508
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+996
	.word	.LC495
	.word	.LANCHOR0+1080
	.word	.LC503
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
	ldr	ip, [r0, #2384]
	mov	r4, r0
	ldr	r2, [r0, #3548]
	mov	r7, r3
	ldmib	fp, {r0, r3}
	cmp	r2, #0
	ldr	r5, [ip, #644]
	str	r1, [r4, #3528]
	addne	r1, r4, #4096
	ldrneb	ip, [r1, #1813]	@ zero_extendqisi2
	strneb	ip, [r2, #3]
	ldrneb	r1, [r1, #1808]	@ zero_extendqisi2
	strneb	r1, [r2, #4]
	cmp	r0, #0
	beq	.L4180
	mov	r2, r3, asl #6
	ldr	r1, .L4206
	sub	r3, r2, r3, asl #3
	add	r3, r3, r1
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L4203
	cmp	r3, #1
	beq	.L4180
	cmp	r5, #1
	beq	.L4204
.L4184:
	mov	r1, r7
	mov	r0, r4
	bl	HEVC_StorePicInDPB
	subs	r2, r0, #0
	bne	.L4205
	mov	r3, #1
	mov	r0, r2
	str	r3, [r4, #172]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4205:
	ldr	r1, .L4206+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4180:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	cmp	r5, #1
	bne	.L4184
.L4204:
	ldr	r8, [r4, #2392]
	ldr	r3, [r8, #1292]
	add	r3, r8, r3, lsl #2
	ldr	r9, [r3, #1476]
	mov	r0, r9
	bl	MEM_Phy2Vir
	ldr	r6, [r8, #192]
	ldr	r3, [r8, #196]
	mov	r1, r9
	add	r6, r6, #15
	ldr	r2, .L4206+8
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
	beq	.L4195
	mov	r0, #0
	mov	r3, r5
	mov	lr, r0
	mov	r8, r0
	mov	ip, r0
	mvn	r5, #-2147483648
.L4191:
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
	bne	.L4191
	mov	r9, #100
	mul	r9, r9, lr
.L4185:
	mov	r1, r6
	bl	__aeabi_uidiv
	mov	r1, r6
	mov	r10, r0
	mov	r0, r9
	bl	__aeabi_uidiv
	ldr	r3, [r4, #3548]
	cmp	r0, #100
	moveq	r5, #0
	cmp	r3, #0
	beq	.L4193
	str	r8, [r3, #324]
	ldr	r3, [r4, #3548]
	str	r5, [r3, #328]
	ldr	r3, [r4, #3548]
	str	r10, [r3, #332]
	ldr	r3, [r4, #3548]
	str	r0, [r3, #336]
	str	r8, [r4, #3796]
	str	r5, [r4, #3800]
	str	r10, [r4, #3804]
	str	r0, [r4, #3808]
	b	.L4184
.L4203:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4195:
	mov	r9, r6
	mov	r0, r6
	mvn	r5, #-2147483648
	mov	r8, r6
	b	.L4185
.L4193:
	mov	r0, r3
	ldr	r1, .L4206+12
	bl	dprint_vfmw
	b	.L4184
.L4207:
	.align	2
.L4206:
	.word	g_VdmDrvParam+40
	.word	.LC511
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC510
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
	ldrne	r2, [r0, #2368]
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
	ldrne	r2, [r0, #2368]
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
	ldr	r3, [r0, #2568]
	mov	r4, r0
	cmp	r3, #0
	bne	.L4215
	b	.L4219
.L4229:
	ldr	r3, [fp, #-36]
.L4216:
	mov	r1, r3
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r3, [r4, #2568]
	cmp	r3, #0
	beq	.L4219
.L4215:
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	mov	r6, #1
	bl	HEVC_GetMinPOC
	ldr	r3, [fp, #-36]
	mov	r0, r4
	add	r2, r4, r3, lsl #2
	ldr	r5, [r2, #2588]
	cmp	r5, #0
	mov	r1, r5
	beq	.L4216
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	cmp	r2, r6
	beq	.L4216
	strb	r6, [r5, #2]
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r7, r0, #0
	bne	.L4229
	add	r1, r5, #28
	mov	r0, r4
	bl	HEVC_OutputFrame.isra.10
	cmp	r0, #0
	beq	.L4229
	mov	r0, r7
	ldr	r2, .L4230
	ldr	r1, .L4230+4
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	b	.L4229
.L4219:
	add	r0, r4, #5504
	add	r0, r0, #48
	bl	GetVoLastImageID
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4231:
	.align	2
.L4230:
	.word	.LANCHOR0+1104
	.word	.LC422
	UNWIND(.fnend)
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.global	g_pGlbVar
	.global	g_RpuStartCode
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.15031, %object
	.size	__func__.15031, 17
__func__.15031:
	.ascii	"HEVC_OutputFrame\000"
	.space	3
	.type	SarTable.13695, %object
	.size	SarTable.13695, 136
SarTable.13695:
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
	.type	__func__.13853, %object
	.size	__func__.13853, 18
__func__.13853:
	.ascii	"HEVC_CalcTileInfo\000"
	.space	2
	.type	__func__.14338, %object
	.size	__func__.14338, 27
__func__.14338:
	.ascii	"HEVC_GetUnRefPicWithMinPoc\000"
	.space	1
	.type	__func__.14347, %object
	.size	__func__.14347, 21
__func__.14347:
	.ascii	"HEVC_IncreaseDPBSize\000"
	.space	3
	.type	__func__.14576, %object
	.size	__func__.14576, 17
__func__.14576:
	.ascii	"HEVC_CalcTileMap\000"
	.space	3
	.type	__func__.14596, %object
	.size	__func__.14596, 17
__func__.14596:
	.ascii	"HEVC_WritePicMsg\000"
	.space	3
	.type	__func__.14625, %object
	.size	__func__.14625, 16
__func__.14625:
	.ascii	"HEVC_CheckListX\000"
	.type	__func__.14792, %object
	.size	__func__.14792, 16
__func__.14792:
	.ascii	"HEVC_RepairList\000"
	.type	__func__.14859, %object
	.size	__func__.14859, 16
__func__.14859:
	.ascii	"HEVC_ArrangeMem\000"
	.type	__func__.14932, %object
	.size	__func__.14932, 20
__func__.14932:
	.ascii	"HEVC_RemoveApcStore\000"
	.type	__func__.15207, %object
	.size	__func__.15207, 21
__func__.15207:
	.ascii	"HEVC_CheckFrameStore\000"
	.space	3
	.type	__func__.15275, %object
	.size	__func__.15275, 19
__func__.15275:
	.ascii	"HEVC_GetSLHDR1Info\000"
	.space	1
	.type	__func__.15402, %object
	.size	__func__.15402, 14
__func__.15402:
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
	.type	__func__.15718, %object
	.size	__func__.15718, 16
__func__.15718:
	.ascii	"HEVC_ReleaseNAL\000"
	.type	__func__.14891, %object
	.size	__func__.14891, 20
__func__.14891:
	.ascii	"HEVC_InitDecBuffers\000"
	.type	__func__.13904, %object
	.size	__func__.13904, 12
__func__.13904:
	.ascii	"HEVC_DecVPS\000"
	.type	__func__.15460, %object
	.size	__func__.15460, 24
__func__.15460:
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
	.type	__func__.13973, %object
	.size	__func__.13973, 12
__func__.13973:
	.ascii	"HEVC_DecSPS\000"
	.type	__func__.14014, %object
	.size	__func__.14014, 12
__func__.14014:
	.ascii	"HEVC_DecPPS\000"
	.type	__func__.14448, %object
	.size	__func__.14448, 27
__func__.14448:
	.ascii	"HEVC_DecSliceSegmentHeader\000"
	.space	1
	.type	__func__.14870, %object
	.size	__func__.14870, 13
__func__.14870:
	.ascii	"HEVC_InitDPB\000"
	.space	3
	.type	__func__.15038, %object
	.size	__func__.15038, 19
__func__.15038:
	.ascii	"HEVC_OutputCurrPic\000"
	.space	1
	.type	__func__.15043, %object
	.size	__func__.15043, 23
__func__.15043:
	.ascii	"HEVC_FirstFrameFastOut\000"
	.space	1
	.type	__func__.15199, %object
	.size	__func__.15199, 19
__func__.15199:
	.ascii	"HEVC_OutputFrmToVO\000"
	.space	1
	.type	__func__.15158, %object
	.size	__func__.15158, 22
__func__.15158:
	.ascii	"HEVC_OutputFrmFromDPB\000"
	.space	2
	.type	__func__.14353, %object
	.size	__func__.14353, 30
__func__.14353:
	.ascii	"HEVC_OutputUnRefPicWithMinPoc\000"
	.space	2
	.type	__func__.15174, %object
	.size	__func__.15174, 27
__func__.15174:
	.ascii	"HEVC_FlushOutputFrmFromDPB\000"
	.space	1
	.type	__func__.15781, %object
	.size	__func__.15781, 14
__func__.15781:
	.ascii	"HEVC_ClearDPB\000"
	.space	2
	.type	__func__.14358, %object
	.size	__func__.14358, 23
__func__.14358:
	.ascii	"HEVC_RecoverDPBProcess\000"
	.space	1
	.type	__func__.15138, %object
	.size	__func__.15138, 20
__func__.15138:
	.ascii	"HEVC_InsertFrmInDPB\000"
	.type	__func__.15048, %object
	.size	__func__.15048, 22
__func__.15048:
	.ascii	"HEVC_SimpleDPBProcess\000"
	.space	2
	.type	__func__.15053, %object
	.size	__func__.15053, 21
__func__.15053:
	.ascii	"HEVC_DecOrderProcess\000"
	.space	3
	.type	__func__.15067, %object
	.size	__func__.15067, 22
__func__.15067:
	.ascii	"HEVC_DispOrderProcess\000"
	.space	2
	.type	__func__.15081, %object
	.size	__func__.15081, 19
__func__.15081:
	.ascii	"HEVC_StorePicInDPB\000"
	.space	1
	.type	__func__.14711, %object
	.size	__func__.14711, 12
__func__.14711:
	.ascii	"HEVC_DecVDM\000"
	.type	__func__.13584, %object
	.size	__func__.13584, 18
__func__.13584:
	.ascii	"HEVC_VES_Splitter\000"
	.space	2
	.type	__func__.14388, %object
	.size	__func__.14388, 14
__func__.14388:
	.ascii	"HEVC_DecSlice\000"
	.space	2
	.type	__func__.15861, %object
	.size	__func__.15861, 20
__func__.15861:
	.ascii	"HEVC_HaveSliceToDec\000"
	.type	__func__.15889, %object
	.size	__func__.15889, 13
__func__.15889:
	.ascii	"HEVCDEC_Init\000"
	.space	3
	.type	__func__.15903, %object
	.size	__func__.15903, 23
__func__.15903:
	.ascii	"HEVCDEC_GetImageBuffer\000"
	.space	1
	.type	__func__.15918, %object
	.size	__func__.15918, 21
__func__.15918:
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
	.type	__func__.15967, %object
	.size	__func__.15967, 21
__func__.15967:
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
	ASCII(.ascii	"%s last frame fs unrelease, fix it!\012\000" )
	.space	3
.LC496:
	ASCII(.ascii	"OSAL_FP_alloc_virmem g_pGlbVar fail %d\012\000" )
.LC497:
	ASCII(.ascii	"%s: Get context addr failed!\012\000" )
	.space	2
.LC498:
	ASCII(.ascii	"%s FATAL: MemOffset %d > ContextMemSize %d.\012\000" )
	.space	3
.LC499:
	ASCII(.ascii	"%s: VCTRL_GetChanIDByCtx() return -1!\012\000" )
	.space	1
.LC500:
	ASCII(.ascii	"Fs leak, clear dpb fs not in vo queue.\012\000" )
.LC501:
	ASCII(.ascii	"No frame store available!\012\000" )
	.space	1
.LC502:
	ASCII(.ascii	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak" )
	ASCII(.ascii	", ClearAll!\012\000" )
.LC503:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pPacket!\012\000" )
	.space	1
.LC504:
	ASCII(.ascii	"HevcCtx not init!\012\000" )
	.space	1
.LC505:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC506:
	ASCII(.ascii	"nal_layer_id out %d of range[0,1].\012\000" )
.LC507:
	ASCII(.ascii	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\012" )
	ASCII(.ascii	"\000" )
.LC508:
	ASCII(.ascii	"HEVC_InquireSliceProperty error.\012\000" )
	.space	2
.LC509:
	ASCII(.ascii	"HEVC_DecOneNal ERR\012\000" )
.LC510:
	ASCII(.ascii	"pHevcCtx->CurrPic.frame_store is null pointer\012\000" )
	.space	1
.LC511:
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
