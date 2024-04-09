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
	.type	HEVC_UpdateInterLayerReflist, %function
HEVC_UpdateInterLayerReflist:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	add	r10, r0, #4096
	mov	r7, r0
	ldr	r3, [r10, #744]
	cmp	r3, #0
	streq	r3, [r0, #3064]
	streq	r3, [r0, #3068]
	beq	.L5
	ldr	r2, [r10, #2072]
	ldr	r1, [r0, #2836]
	cmp	r2, #0
	ble	.L34
	add	r2, r3, #1024
	add	r0, r1, #12288
	add	r2, r2, #8
	add	ip, r7, #6144
	mov	r3, r3, asl #1
	str	r3, [fp, #-52]
	add	r3, r1, #16384
	str	r3, [fp, #-48]
	add	r3, r0, r2, lsl #2
	str	r3, [fp, #-56]
	add	r3, ip, #24
	mov	r8, #0
	mov	r6, r8
	str	r8, [fp, #-64]
	str	r8, [fp, #-68]
	mov	r9, r0
	mov	r8, r3
.L26:
	ldr	r1, [fp, #-52]
	ldr	r3, [r8, #4]!
	ldr	r2, [fp, #-56]
	add	r3, r1, r3
	ldr	r1, [fp, #-48]
	add	r3, r3, #1040
	add	r3, r3, #4
	ldr	r2, [r2, #132]
	ldr	r1, [r1, #164]
	add	r3, r9, r3, lsl #2
	cmp	r2, r1
	ldr	lr, [r3, #132]
	add	r3, lr, #1024
	add	r3, r3, #8
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	ble	.L56
	cmp	r2, r3
	movlt	r3, #0
	movge	r3, #1
	str	r3, [fp, #-60]
.L10:
	ldr	r0, [r7, #3040]
	cmp	r0, #0
	beq	.L12
	add	r2, r7, #3200
	ldr	ip, [r10, #724]
	add	r2, r2, #4
	mov	r4, #0
	b	.L25
.L13:
	add	r4, r4, #1
	cmp	r4, r0
	beq	.L12
.L25:
	ldr	r3, [r2, #4]!
	ldr	r1, [r3, #8]
	cmp	r1, ip
	bne	.L13
	ldr	r1, [r3, #32]
	cmp	r1, lr
	bne	.L13
	add	r4, r7, r4, lsl #2
	mov	r2, #1
	strb	r2, [r3, #1]
	ldr	r3, [r4, #3208]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L57
.L14:
	mov	r5, #0
	str	r5, [r3, #64]
	ldr	r3, [r4, #3208]
	mov	r2, #1
	str	r2, [r3, #60]
	ldr	r3, [r4, #3208]
	str	r2, [r3, #72]
	ldr	r3, [r4, #3208]
	cmp	r3, r5
	beq	.L58
	ldr	r2, [r10, #744]
	mov	r1, #280
	mul	r1, r1, r2
	add	ip, r7, r1
	add	r0, ip, #13120
	add	r0, r0, #40
	ldr	r0, [r0, #4]
	cmp	r0, #0
	beq	.L16
	add	ip, ip, #13120
	add	ip, ip, #48
	ldr	ip, [ip, #4]
	cmp	ip, #0
	addne	r1, r1, #13120
	addne	r1, r1, #52
	addne	r1, r7, r1
	bne	.L19
	b	.L59
.L23:
	ldr	ip, [r1, #4]!
	cmp	ip, #0
	beq	.L17
.L19:
	add	r5, r5, #1
	cmp	r5, r0
	bne	.L23
.L16:
	ldr	r2, [fp, #-60]
	cmp	r2, #0
	beq	.L24
	ldr	r1, [fp, #-64]
	add	r2, r7, r1, lsl #2
	str	r3, [r2, #3072]
	add	r3, r1, #1
	str	r3, [fp, #-64]
.L12:
	ldr	r3, [r10, #2072]
	add	r6, r6, #1
	cmp	r3, r6
	bgt	.L26
	ldr	r9, [fp, #-64]
	ldr	r8, [fp, #-68]
	mov	r1, r9
	mov	r3, r8
.L8:
	ldr	r2, [r7, #3036]
	str	r1, [r7, #3064]
	cmp	r2, r9
	str	r3, [r7, #3068]
	ble	.L31
	add	r3, r9, #764
	mov	r1, #0
	add	r3, r3, #3
	add	r3, r7, r3, lsl #2
.L30:
	add	r9, r9, #1
	str	r1, [r3, #4]!
	cmp	r9, r2
	bne	.L30
.L31:
	cmp	r2, r8
	addgt	r1, r8, #784
	movgt	r3, #0
	addgt	r7, r7, r1, lsl #2
	ble	.L5
.L32:
	add	r8, r8, #1
	str	r3, [r7, #4]!
	cmp	r8, r2
	bne	.L32
.L5:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L56:
	cmp	r2, r3
	movle	r3, #1
	strle	r3, [fp, #-60]
	ble	.L10
	cmp	r2, r1
	movlt	r3, #0
	movge	r3, #1
	str	r3, [fp, #-60]
	b	.L10
.L24:
	ldr	r1, [fp, #-68]
	add	r2, r7, r1, lsl #2
	str	r3, [r2, #3140]
	add	r3, r1, #1
	str	r3, [fp, #-68]
	b	.L12
.L59:
	mov	r5, ip
.L17:
	ldr	r1, [r3, #28]
	ldr	r0, [r7, #276]
	str	r3, [fp, #-72]
	str	r2, [fp, #-76]
	bl	FSP_GetLogicFs
	ldr	r3, [fp, #-72]
	subs	lr, r0, #0
	beq	.L20
	ldr	r1, [lr, #28]
	ldr	r2, [fp, #-76]
	cmp	r1, #0
	beq	.L20
	mov	r1, #70
	mov	r0, #280
	mla	r1, r1, r2, r5
	mla	r2, r0, r2, r7
	mov	r0, #1
	add	r1, r7, r1, lsl #2
	add	ip, r2, #13120
	add	r1, r1, #12288
	add	r2, r2, r5
	add	r2, r2, #13376
	str	r0, [r1, #884]
	ldr	r0, [lr, #28]
	ldr	r0, [r0, #4]
	str	r0, [r1, #948]
	ldr	r0, [r3, #8]
	str	r0, [r1, #1012]
	ldr	r0, [ip, #48]
	add	r0, r0, #1
	str	r0, [ip, #48]
	ldr	r0, [r3, #32]
	str	r0, [r1, #1076]
	str	r5, [r3, #36]
	mov	r3, #1
	strb	r3, [r2, #52]
	ldr	r3, [r4, #3208]
	b	.L16
.L57:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r7, #276]
	bl	FSP_SetRef
	ldr	r3, [r4, #3208]
	b	.L14
.L34:
	mov	r3, #0
	mov	r1, r3
	mov	r8, r3
	mov	r9, r3
	b	.L8
.L58:
	mov	r0, r3
	ldr	r2, .L60
	mov	r3, #170
	ldr	r1, .L60+4
	bl	dprint_vfmw
	ldr	r3, [r4, #3208]
	b	.L16
.L20:
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	mov	r0, #0
	ldr	ip, [r3, #8]
	ldr	r2, [r3, #28]
	stmia	sp, {r1, lr}
	mov	r3, ip
	str	r0, [sp, #8]
	ldr	r1, .L60+8
	bl	dprint_vfmw
	ldr	r3, [r4, #3208]
	b	.L16
.L61:
	.align	2
.L60:
	.word	.LC2
	.word	.LC3
	.word	.LC4
	UNWIND(.fnend)
	.size	HEVC_UpdateInterLayerReflist, .-HEVC_UpdateInterLayerReflist
	.align	2
	.type	HEVC_CheckThatAllRefPicsAreAvailable.part.14, %function
HEVC_CheckThatAllRefPicsAreAvailable.part.14:
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
	ldr	r2, [r0, #2820]
	movw	ip, #5036
	ldr	r3, [r7, #748]
	movw	r4, #12668
	str	r1, [fp, #-64]
	ldr	r1, [r7, #1648]
	mla	ip, ip, r3, r2
	ldr	r3, [r7, #1644]
	ldr	lr, [r0, #2816]
	mov	r2, #1
	add	r3, r1, r3
	str	r3, [fp, #-60]
	mov	r5, r3
	ldr	r3, [r7, #1652]
	ldr	r1, [ip, #32]
	cmp	r5, r3
	mla	r1, r4, r1, lr
	ldr	r10, [r1, #116]
	mov	r10, r2, asl r10
	bcs	.L63
	add	r6, r5, #1456
	add	r9, r5, #5696
	add	r6, r6, #4
	add	r9, r9, #56
	ldr	r1, [r0, #3040]
	add	r3, r3, #5696
	sub	r10, r10, #1
	add	r6, r0, r6, lsl #2
	add	r9, r0, r9
	add	r3, r3, #56
	mov	r2, #0
	add	r3, r0, r3
	str	r2, [fp, #-52]
	str	r3, [fp, #-48]
	str	r2, [fp, #-56]
.L64:
	cmp	r1, #0
	beq	.L70
	add	r3, r0, #3200
	mov	r8, #0
	add	r3, r3, #8
	mov	r2, r8
	ldr	r5, [r6, #-944]
	b	.L67
.L122:
	cmp	lr, #0
	beq	.L66
	ldr	r4, [ip, #8]
	ldr	lr, [r6]
	cmp	r4, lr
	beq	.L120
.L66:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r1
	beq	.L121
.L67:
	ldr	ip, [r3]
	cmp	r5, #0
	ldr	lr, [ip, #60]
	bne	.L122
	cmp	lr, #0
	beq	.L66
	ldr	r4, [r6]
	ldr	lr, [ip, #8]
	eor	lr, lr, r4
	tst	lr, r10
	bne	.L66
.L120:
	ldrb	lr, [ip, #1]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L66
	ldr	lr, [r0, #2856]
	ldr	r4, [ip, #16]
	ldr	ip, [lr, #4]
	cmp	r4, ip
	movls	r8, #1
	bls	.L66
	ldr	ip, [lr, #644]
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	ip, #1
	movne	r8, #1
	cmp	r2, r1
	bne	.L67
.L121:
	cmp	r8, #0
	beq	.L70
.L68:
	ldr	r3, [fp, #-48]
	add	r9, r9, #1
	add	r6, r6, #4
	cmp	r9, r3
	bne	.L64
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	beq	.L72
.L71:
	add	r5, r0, #5760
	add	r9, r0, #5696
	ldr	r10, [fp, #-60]
	add	r5, r5, #12
	ldr	ip, [fp, #-56]
	add	r9, r9, #56
	mov	r8, #0
.L76:
	cmp	r1, #0
	beq	.L77
	add	r4, r0, #3200
	mov	r6, #0
	add	r4, r4, #4
	mov	r3, r6
	str	ip, [fp, #-48]
	b	.L74
.L73:
	add	r3, r3, #1
	cmp	r3, r1
	beq	.L123
.L74:
	ldr	r2, [r4, #4]!
	ldr	lr, [r2, #60]
	cmp	lr, #0
	bne	.L73
	ldr	ip, [r5]
	ldr	lr, [r7, #724]
	add	lr, lr, ip
	ldr	ip, [r2, #8]
	cmp	ip, lr
	bne	.L73
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L73
	ldr	lr, [r0, #2856]
	ldr	r2, [r2, #16]
	ldr	ip, [lr, #4]
	cmp	r2, ip
	movls	r6, #1
	bls	.L73
	ldr	r2, [lr, #644]
	add	r3, r3, #1
	cmp	r2, #1
	movne	r6, #1
	cmp	r3, r1
	bne	.L74
.L123:
	cmp	r6, #0
	ldr	ip, [fp, #-48]
	beq	.L77
.L75:
	add	r8, r8, #1
	add	r5, r5, #4
	cmp	r10, r8
	add	r9, r9, #1
	bhi	.L76
	str	ip, [fp, #-56]
.L72:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	beq	.L85
	ldr	r3, [fp, #-64]
	mov	r0, #0
	ldr	r2, [fp, #-52]
	str	r2, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L77:
	ldr	r2, [r7, #744]
	ldr	r3, [r7, #724]
	ldr	lr, [r5]
	add	r2, r0, r2, lsl #2
	add	r3, r3, lr
	ldr	r2, [r2, #244]
	cmp	r3, r2
	blt	.L75
	ldrb	r2, [r9]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [fp, #-52]
	movne	ip, #1
	movne	r2, r3
	str	r2, [fp, #-52]
	b	.L75
.L70:
	ldr	r2, [r7, #744]
	ldr	r3, [r7, #724]
	ldr	ip, [r6, #-68]
	add	r2, r0, r2, lsl #2
	add	r3, r3, ip
	ldr	r2, [r2, #244]
	cmp	r3, r2
	blt	.L68
	ldrb	r2, [r9]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [fp, #-52]
	movne	r2, r3
	ldr	r3, [fp, #-56]
	str	r2, [fp, #-52]
	movne	r3, #1
	str	r3, [fp, #-56]
	b	.L68
.L85:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L63:
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	beq	.L85
	mov	r3, #0
	ldr	r1, [r0, #3040]
	str	r3, [fp, #-52]
	str	r3, [fp, #-56]
	b	.L71
	UNWIND(.fnend)
	.size	HEVC_CheckThatAllRefPicsAreAvailable.part.14, .-HEVC_CheckThatAllRefPicsAreAvailable.part.14
	.align	2
	.type	HEVC_SetFrmRepeatCount.part.15, %function
HEVC_SetFrmRepeatCount.part.15:
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
	ldr	ip, [r0, #316]
	ldr	r2, [r0, #3036]
	ldr	r3, [r0, #312]
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
	ldrhi	r3, [r0, #316]
	ldrls	r3, [r0, #316]
	addhi	r3, r3, #2
	addls	r3, r3, #1
	str	r3, [r0, #316]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_SetFrmRepeatCount.part.15, .-HEVC_SetFrmRepeatCount.part.15
	.align	2
	.type	HEVC_OutputFrame, %function
HEVC_OutputFrame:
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
	mov	r6, r1
	ldr	r0, [r0, #276]
	ldr	r1, [r1, #28]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L179
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L180
.L131:
	mov	r2, #1
	ldr	r1, [r6, #28]
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
	add	r3, r4, #6144
	ldr	r0, [r4, #276]
	add	r3, r3, #40
	str	r5, [sp]
	mov	r2, r4
	mov	r1, #16
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L181
.L151:
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r5, #16]
	bcs	.L182
.L149:
	ldr	r2, [r4, #324]
	mov	r0, #0
	ldr	r3, [r4, #316]
	add	r2, r2, #1
	str	r2, [r4, #324]
	add	r3, r3, #1
	str	r3, [r4, #316]
.L172:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L182:
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.part.15
	b	.L149
.L180:
	ldr	r1, [r6, #28]
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	cmp	r3, #6
	beq	.L183
	bics	r2, r3, #4
	bne	.L146
	ldr	r3, [r6, #32]
	cmp	r3, #0
	beq	.L131
	b	.L147
.L146:
	cmp	r3, #5
	bne	.L131
	ldr	r3, [r6, #32]
	cmp	r3, #1
	beq	.L131
.L147:
	ldr	r1, [r6, #28]
	mov	r2, #0
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
	b	.L151
.L183:
	cmp	r6, #0
	addeq	r3, r4, #2416
	moveq	r9, r3
	beq	.L133
	ldr	r3, [r6, #32]
	cmp	r3, #0
	addne	r7, r4, #2608
	addeq	r3, r4, #2416
	addne	r7, r7, #4
	addne	r3, r4, #2416
	moveq	r7, r3
	moveq	r9, r3
	ldrh	r1, [r7, #2]
	movne	r9, r3
	ldrh	r0, [r7]
	add	r2, r1, #1
	and	r3, r2, #15
	cmp	r3, r0
	beq	.L184
.L136:
	mov	r3, r1, asl #4
	ldr	r0, [r6, #8]
	sub	r3, r3, r1, asl #2
	and	r2, r2, #15
	add	r3, r7, r3
	str	r0, [r3, #4]
	ldr	r1, [r6, #28]
	str	r1, [r3, #8]!
	str	r5, [r3, #4]
	strh	r2, [r7, #2]	@ movhi
.L133:
	add	r3, r4, #6144
	str	r5, [fp, #-52]
	mov	r5, r9
	mov	r1, r3
	ldrh	r3, [r9]
	add	r1, r1, #40
	str	r1, [fp, #-48]
.L137:
	ldrh	r2, [r5, #2]
	cmp	r2, r3
	beq	.L176
.L187:
	add	r8, r4, #2608
	add	r8, r8, #4
	ldrh	r6, [r8]
	ldrh	r2, [r8, #2]
	cmp	r2, r6
	beq	.L176
	mov	r7, r3, asl #4
	sub	r7, r7, r3, asl #2
	add	r7, r4, r7
	ldr	r1, [r7, #2428]
	cmp	r1, #0
	beq	.L176
	mov	r10, r6, asl #2
	mov	r6, r6, asl #4
	rsb	r9, r10, r6
	add	r9, r4, r9
	add	r2, r9, #2608
	add	r2, r2, #12
	ldr	r3, [r2, #4]
	cmp	r3, #0
	beq	.L176
	ldr	r3, [r7, #2420]
	ldr	r0, [r9, #2616]
	cmp	r3, r0
	bgt	.L185
	blt	.L186
	ldr	r3, [r1, #180]
	cmp	r3, #0
	beq	.L142
	mov	r3, #0
	str	r3, [r1, #180]
	ldr	r3, [r2, #4]
	mov	r2, #1
	str	r2, [r3, #180]
	ldr	r1, [r7, #2428]
.L142:
	ldr	r0, [r4, #276]
	mov	r2, r4
	str	r1, [sp]
	mov	r1, #16
	ldr	r3, [fp, #-48]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L143
	ldr	r2, .L188
	mov	r0, #1
	ldr	r1, .L188+4
	ldr	r3, [r7, #2420]
	bl	dprint_vfmw
	ldr	r1, [r7, #2424]
	mov	r2, #0
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
.L143:
	ldrh	r1, [r5]
	rsb	r6, r10, r6
	add	r6, r4, r6
	ldr	r3, [fp, #-48]
	add	r1, r1, #1
	mov	r2, r4
	and	r1, r1, #15
	strh	r1, [r5]	@ movhi
	ldr	ip, [r6, #2624]
	mov	r1, #16
	ldr	r0, [r4, #276]
	str	ip, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L144
	ldr	r3, [r9, #2616]
	mov	r0, #1
	ldr	r2, .L188
	ldr	r1, .L188+8
	bl	dprint_vfmw
.L177:
	ldr	r1, [r9, #2620]
	mov	r2, #0
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
.L144:
	ldrh	r3, [r8]
	add	r3, r3, #1
	and	r3, r3, #15
	strh	r3, [r8]	@ movhi
	ldrh	r3, [r5]
	ldrh	r2, [r5, #2]
	cmp	r2, r3
	bne	.L187
.L176:
	ldr	r5, [fp, #-52]
	b	.L151
.L185:
	str	r0, [sp]
	mov	r0, #1
	ldr	r2, .L188
	ldr	r1, .L188+12
	bl	dprint_vfmw
	b	.L177
.L186:
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L188
	mov	r0, #1
	ldr	r1, .L188+16
	bl	dprint_vfmw
	ldr	r1, [r7, #2424]
	mov	r2, #0
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
	ldrh	r3, [r5]
	add	r3, r3, #1
	and	r3, r3, #15
	strh	r3, [r5]	@ movhi
	b	.L137
.L181:
	ldr	r2, .L188+20
	mov	r0, #1
	ldr	r1, .L188+24
	bl	dprint_vfmw
	ldr	r0, [r4, #276]
	ldr	r1, [r6, #28]
	mov	r2, #0
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L172
.L179:
	ldr	r2, .L188+20
	ldr	r1, .L188+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L172
.L184:
	mov	r1, r3, asl #4
	mov	r2, #0
	sub	r3, r1, r3, asl #2
	ldr	r0, [r4, #276]
	add	r3, r7, r3
	ldr	r8, [r3, #8]
	mov	r1, r8
	bl	FSP_SetDisplay
	ldrh	r2, [r7]
	ldr	r1, .L188+32
	mov	r3, r8
	add	r2, r2, #1
	mov	r0, #1
	and	r2, r2, #15
	strh	r2, [r7]	@ movhi
	ldr	r2, [r6, #32]
	bl	dprint_vfmw
	ldrh	r1, [r7, #2]
	add	r2, r1, #1
	b	.L136
.L189:
	.align	2
.L188:
	.word	.LANCHOR0+20
	.word	.LC9
	.word	.LC10
	.word	.LC7
	.word	.LC8
	.word	.LANCHOR0
	.word	.LC11
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	HEVC_OutputFrame, .-HEVC_OutputFrame
	.align	2
	.global	HEVC_CheckVpsExtOverlap
	.type	HEVC_CheckVpsExtOverlap, %function
HEVC_CheckVpsExtOverlap:
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
	subs	r4, r0, #0
	beq	.L194
.L191:
	add	r3, r4, #12288
	ldrb	r0, [r4]	@ zero_extendqisi2
	ldrb	r3, [r3, #200]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #0
	cmp	r0, #0
	moveq	r0, r3
	orrne	r0, r3, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L194:
	ldr	r2, .L195
	mov	r0, #1
	ldr	r1, .L195+4
	bl	dprint_vfmw
	b	.L191
.L196:
	.align	2
.L195:
	.word	.LANCHOR0+48
	.word	.LC12
	UNWIND(.fnend)
	.size	HEVC_CheckVpsExtOverlap, .-HEVC_CheckVpsExtOverlap
	.align	2
	.global	HEVC_CheckPpsExtOverlap
	.type	HEVC_CheckPpsExtOverlap, %function
HEVC_CheckPpsExtOverlap:
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
	subs	r4, r0, #0
	beq	.L201
.L198:
	ldrb	r3, [r4, #3144]	@ zero_extendqisi2
	ldrb	r0, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #0
	cmp	r0, #0
	moveq	r0, r3
	orrne	r0, r3, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L201:
	ldr	r2, .L202
	mov	r0, #1
	ldr	r1, .L202+4
	bl	dprint_vfmw
	b	.L198
.L203:
	.align	2
.L202:
	.word	.LANCHOR0+72
	.word	.LC13
	UNWIND(.fnend)
	.size	HEVC_CheckPpsExtOverlap, .-HEVC_CheckPpsExtOverlap
	.align	2
	.global	HEVC_CheckSliceExtOverlap
	.type	HEVC_CheckSliceExtOverlap, %function
HEVC_CheckSliceExtOverlap:
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
	subs	r4, r0, #0
	beq	.L208
.L205:
	ldrb	r3, [r4, #16]	@ zero_extendqisi2
	ldrb	r0, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #0
	cmp	r0, #0
	moveq	r0, r3
	orrne	r0, r3, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L208:
	ldr	r2, .L209
	mov	r0, #1
	ldr	r1, .L209+4
	bl	dprint_vfmw
	b	.L205
.L210:
	.align	2
.L209:
	.word	.LANCHOR0+96
	.word	.LC14
	UNWIND(.fnend)
	.size	HEVC_CheckSliceExtOverlap, .-HEVC_CheckSliceExtOverlap
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
	ldr	r3, .L212
	mov	r4, r0
	add	r0, r0, #11712
	mov	r2, #56
	mov	r1, #0
	add	r0, r0, #16
	ldr	r3, [r3, #48]
	blx	r3
	add	r3, r4, #3488
	mov	r0, #0
	mov	r1, #0
	mov	r2, #0
	strd	r0, [r3, #40]
	strd	r0, [r3, #16]
	strd	r0, [r3, #24]
	strd	r0, [r3, #32]
	str	r2, [r4, #3484]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L213:
	.align	2
.L212:
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
	ldr	ip, [r3, #748]
	cmp	ip, #0
	blt	.L216
	cmp	ip, lr
	bge	.L216
	ldr	r3, [r0, #2820]
	movw	r2, #5036
	mla	ip, r2, ip, r3
	ldr	lr, [ip, #32]
	ldr	ip, [r0, #160]
	cmp	lr, #0
	blt	.L220
	cmp	lr, ip
	bge	.L220
	ldr	r2, [r0, #2816]
	movw	r4, #12668
	ldr	r3, [r1, #36]
	add	ip, r0, #8192
	mla	lr, r4, lr, r2
	str	r3, [ip, #3548]
	ldr	r2, [r1, #40]
	ldr	r3, [ip, #3540]
	str	r2, [ip, #3552]
	cmp	r3, #1
	ldr	r3, [lr, #52]
	add	r3, r3, #90
	ldrb	r6, [lr, r3, asl #2]	@ zero_extendqisi2
	beq	.L228
	ldrb	r3, [ip, #3537]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L224
	ldrb	r3, [r0, #3480]	@ zero_extendqisi2
	add	lr, r0, #3488
	cmp	r3, #0
	beq	.L225
	ldrd	r2, [lr, #24]
	mov	r8, r2
	mov	r9, r3
.L226:
	ldr	r4, [r0, #3496]
	mov	r5, #0
	adds	r2, r2, r4
	adc	r3, r3, r5
	cmp	r2, r8
	sbcs	r7, r3, r9
	strd	r2, [lr, #40]
	strd	r2, [lr, #16]
	bge	.L223
	adds	r2, r4, r8
	adc	r3, r5, r9
	strd	r2, [lr, #40]
	strd	r2, [lr, #16]
	b	.L223
.L220:
	ldr	r3, [r0, #276]
	movw	r2, #2621
	str	ip, [sp, #4]
	mov	r0, #0
	str	lr, [sp]
	ldr	r1, .L230
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L216:
	ldr	r3, [r0, #276]
	movw	r2, #2611
	str	lr, [sp, #4]
	mov	r0, #0
	str	ip, [sp]
	ldr	r1, .L230+4
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L224:
	add	lr, r0, #3488
	ldr	r4, [r0, #3496]
	ldrd	r2, [lr, #16]
	adds	r2, r2, r4
	adc	r3, r3, #0
	strd	r2, [lr, #40]
.L223:
	add	r7, ip, #3536
	strd	r2, [lr, #32]
	mov	lr, #0
	strb	lr, [ip, #3537]
	ldrd	r4, [r7, #32]
	strd	r4, [r7, #48]
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	cmp	r1, lr
	ldr	r1, [r0, #3500]
	bne	.L229
	adds	r2, r2, r1
	adc	r3, r3, #0
	subs	r2, r2, r6
	sbc	r3, r3, #0
	strd	r2, [r7, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L229:
	adds	r2, r2, r1
	adc	r3, r3, #0
	movs	r3, r3, asr #1
	mov	r2, r2, rrx
	subs	r2, r2, r6
	sbc	r3, r3, #0
	strd	r2, [r7, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L228:
	ldr	r2, [r0, #3484]
	add	lr, r0, #3488
	mov	r3, r2, asr #31
	strd	r2, [lr, #40]
	strd	r2, [lr, #16]
	b	.L223
.L225:
	ldrd	r2, [lr, #16]
	ldrd	r8, [lr, #24]
	b	.L226
.L231:
	.align	2
.L230:
	.word	.LC16
	.word	.LC15
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
	bls	.L236
.L233:
	sub	r1, r1, #6
	cmp	r1, #3
	addhi	r0, r0, #3488
	ldrhid	r2, [r0, #40]
	strhid	r2, [r0, #24]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L236:
	ldr	ip, [r0, #2856]
	mvn	r3, #0
	mvn	r2, #0
	ldrd	r4, [ip, #64]
	cmp	r5, r3
	cmpeq	r4, r2
	beq	.L234
	add	r3, r0, #11712
	movw	ip, #11760
	add	r2, r0, #11776
	strd	r4, [r3, #40]
	ldrd	r4, [r0, ip]
	strd	r4, [r2, #-8]
	strd	r4, [r2]
.L234:
	add	r3, r0, #8192
	mov	r2, #1
	strb	r2, [r3, #3536]
	b	.L233
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
	add	r3, r0, #11712
	add	r2, r0, #8192
	add	r3, r3, #48
	mov	r4, r0
	add	r0, r0, #11776
	ldr	r5, [r2, #3548]
	movw	r1, #11760
	ldr	r10, [r2, #3552]
	ldrd	r2, [r3, #-8]
	cmp	r5, #0
	ldrd	r6, [r4, r1]
	strd	r2, [fp, #-52]
	ldrd	r2, [r0, #-8]
	strd	r2, [fp, #-60]
	beq	.L240
	mov	r9, r5
	mov	r0, r10
	b	.L239
.L241:
	mov	r9, r1
.L239:
	mov	r1, r9
	bl	__aeabi_uidivmod
	mov	r0, r9
	cmp	r1, #0
	bne	.L241
.L238:
	ldrd	r2, [fp, #-60]
	mov	r1, r9
	mov	r0, r5
	mov	r8, #1000
	subs	r2, r6, r2
	movw	r5, #4752
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
	strd	r0, [r4, r5]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L240:
	mov	r9, r10
	b	.L238
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
	bgt	.L243
	cmp	r4, #8
	mul	r9, r4, r4
	beq	.L276
	cmp	r9, #0
	movne	r10, r6
	beq	.L243
.L245:
	mov	r5, #0
	rsb	r7, r4, #1
	mov	r8, r5
.L251:
	cmp	r4, r8
	bgt	.L263
	rsb	lr, r4, r8
	sub	r2, r4, #1
	add	lr, lr, #1
.L252:
	cmp	r2, #0
	cmpge	r4, lr
	ble	.L249
	mla	r0, r2, r4, lr
	add	ip, r10, r5, lsl #2
	mov	r1, r5
.L250:
	add	r1, r1, #1
	sub	r2, r2, #1
	rsb	r3, r5, r1
	str	r0, [ip], #4
	add	r3, r3, lr
	add	r0, r0, r7
	cmp	r2, #0
	cmpge	r4, r3
	bgt	.L250
	mov	r5, r1
.L249:
	cmp	r9, r5
	add	r8, r8, #1
	bhi	.L251
.L243:
	cmp	r4, #4
	ble	.L242
	mov	r3, r4, asr #2
	ldr	r1, [fp, #-48]
	str	r3, [fp, #-60]
	mov	r2, r3
	add	r3, r1, r3
	mul	r2, r2, r2
	mov	r0, r2
	str	r2, [fp, #-56]
	cmp	r0, #0
	ldrsb	r2, [r3, #15]
	add	r2, r2, #1
	beq	.L242
	add	r3, r1, #376
.L247:
	rsb	r5, r4, #1
	mov	r2, r2, asl #14
	str	r3, [fp, #-52]
	mov	r3, #0
	str	r2, [fp, #-64]
	str	r3, [fp, #-48]
.L261:
	ldr	r3, .L277
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
.L255:
	cmp	lr, #3
	mvn	r1, r2
	mov	r1, r1, lsr #31
	movgt	r1, #0
	cmp	r1, #0
	beq	.L256
	mla	r1, r2, r4, lr
	add	r0, r3, r10
	rsb	lr, r3, lr
	add	r0, r6, r0, lsl #2
	add	r1, r1, r9
.L257:
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
	bne	.L257
.L256:
	cmp	r3, #15
	add	r8, r8, #1
	bhi	.L258
	cmp	r8, #3
	movle	r2, r8
	movle	lr, #0
	subgt	lr, r8, #3
	movgt	r2, #3
	b	.L255
.L258:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r2, r2, #4
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-56]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L261
.L242:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L263:
	mov	r2, r8
	mov	lr, #0
	b	.L252
.L276:
	add	r3, r0, #376
	cmp	r9, #0
	mov	r10, r3
	bne	.L245
	ldr	r2, [fp, #-48]
	mov	r1, #2
	str	r1, [fp, #-60]
	mov	r1, #4
	str	r1, [fp, #-56]
	ldrsb	r2, [r2, #17]
	add	r2, r2, #1
	b	.L247
.L278:
	.align	2
.L277:
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
	add	r3, r0, #14
	add	r1, r0, #143
	mov	r6, r0
	mvn	r2, #0
.L280:
	strb	r2, [r3, #1]!
	cmp	r3, r1
	bne	.L280
	ldr	r7, .L284
	mov	r2, #0
	mov	r3, #2
	mov	r4, r2
	mov	r5, r3
	strb	r2, [r6, #19]
	strb	r3, [r6, #31]
	mov	r2, #1
	mov	r3, #3
	strb	r2, [r6, #23]
	strb	r3, [r6, #47]
	mov	r3, #4
	strb	r3, [r6, #79]
.L281:
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
	bne	.L281
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L285:
	.align	2
.L284:
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
	ble	.L299
	subs	lr, r0, #255
	movne	lr, #1
	cmp	r0, #16
	movle	r4, #0
	andgt	r4, lr, #1
	cmp	r4, #0
	bne	.L299
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r1, #1
	movne	r1, #0
	cmp	r0, #255
	movne	r1, #0
	andeq	r1, r1, #1
	cmp	r1, #0
	bne	.L287
	cmp	r0, #1
	beq	.L314
	cmp	lr, #0
	ldrne	r3, .L316
	addne	r0, r3, r0, lsl #3
	ldrne	r2, [r0, #128]
	ldrne	ip, [r0, #124]
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
	bgt	.L292
	rsb	r2, r0, #2256
	add	r2, r2, #7
	cmp	r3, r2
	blt	.L307
.L293:
	movw	r3, #1819
	cmp	r0, r3
	bgt	.L294
	rsb	r3, r0, #1808
	add	r3, r3, #12
	cmp	r2, r3
	bge	.L295
.L309:
	mov	r4, #3
	b	.L287
.L299:
	mov	r4, #0
.L287:
	mov	r2, r4
	ldr	r1, .L316+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L292:
	sub	r2, r0, #2256
	sub	r2, r2, #7
	cmp	r3, r2
	bge	.L293
.L307:
	mov	r4, #4
	b	.L287
.L314:
	ldr	r2, [fp, #4]
	movw	r3, #4320
	cmp	r5, #7680
	cmpeq	r2, r3
	bne	.L315
.L304:
	mov	r4, #2
	b	.L287
.L294:
	sub	r3, r0, #1808
	sub	r3, r3, #12
	cmp	r2, r3
	blt	.L309
.L295:
	movw	r2, #1364
	cmp	r0, r2
	rsble	r4, r0, #1360
	subgt	r4, r0, #1360
	addle	r4, r4, #5
	subgt	r4, r4, #5
	cmp	r3, r4
	movlt	r4, #2
	movge	r4, #1
	b	.L287
.L315:
	cmp	r5, #3840
	cmpeq	r2, #2160
	beq	.L304
	sub	r3, r2, #1072
	sub	r3, r3, #8
	bics	r3, r3, #8
	moveq	r3, #1
	movne	r3, #0
	cmp	r5, #1920
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r3, #0
	bne	.L304
	cmp	r5, #1280
	cmpeq	r2, #720
	beq	.L304
	cmp	r5, #640
	cmpeq	r2, #480
	moveq	r4, #1
	movne	r4, #5
	b	.L287
.L317:
	.align	2
.L316:
	.word	.LANCHOR0
	.word	.LC17
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
	ldr	r1, .L324
	mov	r6, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #168]
	cmn	r3, #1
	movne	r5, #0
	movwne	r7, #52429
	movne	r4, r5
	movtne	r7, 52428
	bne	.L321
	b	.L322
.L320:
	ldr	r3, [r6, #168]
	add	r3, r3, #1
	cmp	r3, r4
	bls	.L322
.L321:
	ldr	r3, [r6, #2852]
	mov	r2, r4
	ldr	r1, .L324+4
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
	bne	.L320
	ldr	r1, .L324+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #168]
	add	r3, r3, #1
	cmp	r3, r4
	bhi	.L321
.L322:
	ldr	r1, .L324+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, .L324+12
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L325:
	.align	2
.L324:
	.word	.LC18
	.word	.LC21
	.word	.LC19
	.word	.LC20
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
	ldr	r1, .L347
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #780]
	ldr	r1, .L347+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #780]
	cmp	r3, #0
	addne	r5, r7, #2864
	movne	r4, #0
	beq	.L334
.L333:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L347+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	ldr	r3, [r5]
	add	r4, r4, r0
	ldr	r1, .L347+12
	cmp	r3, #0
	beq	.L331
	ldr	r2, [r3, #20]
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L331
	ldr	r1, [r3, #28]
	ldr	r0, [r7, #276]
	bl	FSP_GetLogicFs
	ldr	r1, .L347+16
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
.L331:
	ldr	r1, .L347+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #780]
	cmp	r3, r4
	bhi	.L333
.L334:
	ldr	r2, [r6, #784]
	mov	r0, #1
	ldr	r1, .L347+24
	bl	dprint_vfmw
	ldr	r3, [r6, #784]
	cmp	r3, #0
	addne	r5, r7, #2928
	movne	r4, #0
	addne	r5, r5, #4
	beq	.L329
.L338:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L347+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	ldr	r3, [r5]
	add	r4, r4, r0
	ldr	r1, .L347+12
	cmp	r3, #0
	beq	.L336
	ldr	r2, [r3, #20]
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L336
	ldr	r1, [r3, #28]
	ldr	r0, [r7, #276]
	bl	FSP_GetLogicFs
	ldr	r1, .L347+16
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
.L336:
	ldr	r1, .L347+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #784]
	cmp	r3, r4
	bhi	.L338
.L329:
	ldr	r1, .L347+32
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L348:
	.align	2
.L347:
	.word	.LC22
	.word	.LC23
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC19
	.word	.LC24
	.word	.LC29
	.word	.LC28
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
	ldr	r1, .L356
	mov	r10, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #180]
	cmp	r3, #0
	addne	r8, r10, #13696
	movne	r9, #0
	addne	r8, r8, #32
	beq	.L353
.L352:
	ldrb	ip, [r8, #2]	@ zero_extendqisi2
	mov	r3, r8
	mov	r2, r9
	ldr	r1, .L356+4
	mov	r0, #1
	add	r5, r8, #616
	str	ip, [sp, #8]
	mov	r4, #0
	ldrb	ip, [r8, #1]	@ zero_extendqisi2
	str	ip, [sp, #4]
	ldr	ip, [r8, #48]
	str	ip, [sp]
	bl	dprint_vfmw
.L351:
	ldrd	r6, [r5, #8]!
	mov	r2, r4
	ldr	r1, .L356+8
	add	r4, r4, #1
	mov	r0, #1
	strd	r6, [sp]
	bl	dprint_vfmw
	cmp	r4, #4
	bne	.L351
	ldr	r1, .L356+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #180]
	add	r9, r9, #1
	add	r8, r8, #720
	cmp	r3, r9
	bhi	.L352
.L353:
	ldr	r1, .L356+16
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L357:
	.align	2
.L356:
	.word	.LC30
	.word	.LC32
	.word	.LC33
	.word	.LC19
	.word	.LC31
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
	ldr	r1, .L363
	mov	r6, r0
	mov	r0, #1
	bl	dprint_vfmw
	add	r6, r6, #13120
	add	r6, r6, #48
	mov	r7, #0
.L360:
	ldr	ip, [r6, #-4]
	mov	r2, r7
	ldr	r3, [r6]
	mov	r0, #1
	ldr	r1, .L363+4
	mov	r5, r6
	str	ip, [sp]
	mov	r4, #0
	bl	dprint_vfmw
.L359:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L363+8
	add	r4, r4, #1
	mov	r0, #1
	ldr	ip, [r5, #128]
	str	ip, [sp, #4]
	ldr	ip, [r5, #64]
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r4, #16
	bne	.L359
	add	r7, r7, #1
	add	r6, r6, #280
	cmp	r7, #2
	bne	.L360
	ldr	r1, .L363+12
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L364:
	.align	2
.L363:
	.word	.LC34
	.word	.LC35
	.word	.LC36
	.word	.LC37
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
	ldr	r1, .L381
	mov	r9, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r9, #3052]
	ldr	lr, [r9, #3048]
	mov	r0, #1
	ldr	ip, [r9, #3056]
	ldr	r3, [r9, #3040]
	ldr	r2, [r9, #3036]
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L381+4
	bl	dprint_vfmw
	ldr	r3, [r9, #3040]
	cmp	r3, #0
	addne	r4, r9, #3200
	movne	r5, #0
	addne	r4, r4, #4
	beq	.L370
.L369:
	ldr	r3, [r4, #4]!
	ldr	r0, [r9, #276]
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
	ldr	r0, [r9, #276]
	bl	FSP_GetRef
	ldr	r3, [r4]
	ldr	r1, [r3, #28]
	mov	r7, r0
	ldr	r0, [r9, #276]
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
	ldr	r1, .L381+8
	str	r0, [sp, #36]
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #3040]
	cmp	r3, r5
	bhi	.L369
.L370:
	ldr	r1, .L381+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #3040]
	cmp	r3, #0
	addne	r5, r9, #3200
	movne	r6, #0
	addne	r5, r5, #4
	bne	.L377
	b	.L368
.L380:
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L381+16
	mov	r0, #1
	bl	dprint_vfmw
	ldrsb	r2, [r4]
	ldr	r1, .L381+20
	mov	r0, #1
	bl	dprint_vfmw
	ldrsb	r2, [r4, #1]
	ldr	r1, .L381+24
	mov	r0, #1
	bl	dprint_vfmw
.L372:
	cmp	r8, #0
	mov	r2, r8
	ldr	r1, .L381+28
	mov	r0, #1
	beq	.L373
	bl	dprint_vfmw
	ldr	r2, [r8, #72]
	ldr	r1, .L381+32
	mov	r0, #1
	bl	dprint_vfmw
.L374:
	cmp	r7, #0
	mov	r2, r7
	ldr	r1, .L381+36
	mov	r0, #1
	beq	.L375
	bl	dprint_vfmw
	ldr	r2, [r7, #72]
	ldr	r1, .L381+40
	mov	r0, #1
	bl	dprint_vfmw
.L376:
	ldr	r1, .L381+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #3040]
	add	r6, r6, #1
	cmp	r3, r6
	bls	.L368
.L377:
	ldr	r3, [r5, #4]!
	ldr	r0, [r9, #276]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	ldr	r3, [r5]
	ldr	r1, [r3, #28]
	mov	r4, r0
	ldr	r0, [r9, #276]
	bl	FSP_GetDecPhyFs
	ldr	r3, [r5]
	ldr	r1, [r3, #28]
	mov	r8, r0
	ldr	r0, [r9, #276]
	bl	FSP_GetDispPhyFs
	mov	r2, r6
	ldr	r1, .L381+44
	mov	r7, r0
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r4, #0
	mov	r2, r4
	ldr	r1, .L381+48
	mov	r0, #1
	bne	.L380
	ldr	r1, .L381+52
	mov	r0, #1
	bl	dprint_vfmw
	b	.L372
.L375:
	ldr	r1, .L381+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L376
.L373:
	ldr	r1, .L381+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L374
.L368:
	ldr	r1, .L381+64
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L382:
	.align	2
.L381:
	.word	.LC38
	.word	.LC39
	.word	.LC40
	.word	.LC19
	.word	.LC44
	.word	.LC45
	.word	.LC46
	.word	.LC48
	.word	.LC49
	.word	.LC51
	.word	.LC52
	.word	.LC42
	.word	.LC43
	.word	.LC47
	.word	.LC53
	.word	.LC50
	.word	.LC41
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
	bls	.L385
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L385:
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
	add	r3, r0, #4096
	ldr	r3, [r3, #24]
	cmp	r3, #0
	bne	.L393
	ldr	r2, [r0, #2856]
	ldr	r1, [r2, #660]
	cmp	r1, #1
	beq	.L397
.L395:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L393:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L397:
	ldr	r0, [r2, #656]
	cmp	r0, #0
	bne	.L395
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
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	ldr	r0, [r4, #2808]
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
	ldr	r1, [r0, #2844]
	mov	r5, r2
	ldr	r2, [r0, #2840]
	mov	r4, r0
	str	r3, [fp, #-48]
	ldr	r6, [r1, #68]
	ldr	r2, [r2, #128]
	sub	r3, r6, #1
	ldr	r8, [r1, #72]
	cmp	r3, #9
	str	r2, [fp, #-52]
	bhi	.L427
	sub	r3, r8, #1
	cmp	r3, #10
	bhi	.L428
	ldr	r9, .L429
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
	ble	.L408
	ldr	r3, [fp, #-52]
	mov	ip, #0
	mov	lr, ip
	mov	r9, r5
	sub	r10, r3, #4
.L407:
	str	ip, [r5, lr, asl #3]
	mov	r3, ip, asl r10
	ldr	r2, [r4, #2844]
	add	r2, r2, lr, lsl #1
	ldrsh	r2, [r2, #172]
	add	ip, r2, ip
	sub	r2, ip, #1
	str	r2, [r9, #4]
	mov	r1, ip, asl r10
	cmp	r3, r1
	bge	.L413
	cmp	r3, #255
	bhi	.L409
	uxtb	r0, lr
	add	r2, r7, r3
	b	.L411
.L412:
	cmp	r3, #256
	beq	.L409
.L411:
	add	r3, r3, #1
	strb	r0, [r2], #1
	cmp	r3, r1
	bne	.L412
.L413:
	add	lr, lr, #1
	add	r9, r9, #8
	cmp	lr, r6
	bne	.L407
.L408:
	cmp	r8, #0
	ble	.L405
	ldr	r3, [fp, #-52]
	mov	ip, #0
	ldr	r9, [fp, #-48]
	mov	lr, ip
	sub	r5, r3, #4
	mov	r6, r9
.L415:
	str	ip, [r9, lr, asl #3]
	mov	r3, ip, asl r5
	ldr	r2, [r4, #2844]
	add	r2, r2, lr, lsl #1
	ldrsh	r2, [r2, #212]
	add	ip, r2, ip
	sub	r2, ip, #1
	str	r2, [r6, #4]
	mov	r1, ip, asl r5
	cmp	r3, r1
	bge	.L420
	cmp	r3, #255
	bhi	.L416
	add	r2, r3, #255
	uxtb	r0, lr
	add	r2, r7, r2
	b	.L418
.L419:
	cmp	r3, #256
	beq	.L416
.L418:
	add	r3, r3, #1
	strb	r0, [r2, #1]!
	cmp	r3, r1
	bne	.L419
.L420:
	add	lr, lr, #1
	add	r6, r6, #8
	cmp	lr, r8
	bne	.L415
.L405:
	mov	r0, #0
	b	.L401
.L409:
	ldr	r2, .L429+4
	mov	r0, #1
	ldr	r1, .L429+8
	bl	dprint_vfmw
	mvn	r0, #0
.L401:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L416:
	ldr	r2, .L429+4
	mov	r0, #1
	ldr	r1, .L429+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L401
.L428:
	mov	r1, #11
	mov	r3, r8
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L429+4
	ldr	r1, .L429+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L401
.L427:
	mov	r1, #10
	mov	r3, r6
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L429+4
	ldr	r1, .L429+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L401
.L430:
	.align	2
.L429:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+260
	.word	.LC56
	.word	.LC57
	.word	.LC55
	.word	.LC54
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
	ldr	r2, [r0, #2808]
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
	ldr	r3, .L439
	mov	r5, r1
	mov	r2, #32
	ldr	r1, [r0, #2808]
	sub	r0, fp, #52
	ldr	r3, [r3, #52]
	mov	r5, r5, asl #3
	blx	r3
	ldr	r3, [fp, #-28]
	ldr	r2, [fp, #-24]
	rsb	r3, r2, r3
	cmp	r3, r5
	movcs	r0, #0
	bcc	.L438
.L433:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L438:
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsShow
	cmp	r0, #0
	moveq	r0, #1
	beq	.L433
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
	b	.L434
.L435:
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
.L434:
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
	bne	.L435
	mov	r0, r3
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L440:
	.align	2
.L439:
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
	beq	.L449
	mov	r1, #8
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r6, #3
	mov	r7, r0
.L448:
	cmp	r7, #0
	bne	.L443
	mov	r4, #16
.L444:
	mov	r1, #8
	ldr	r0, [r5, #2808]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L444
.L445:
	subs	r6, r6, #1
	bne	.L448
.L453:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L443:
	cmp	r7, #1
	beq	.L452
	cmp	r7, #2
	bne	.L445
	mov	r1, #32
	ldr	r0, [r5, #2808]
	bl	BsGet
	subs	r6, r6, #1
	bne	.L448
	b	.L453
.L452:
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	subs	r6, r6, #1
	bne	.L448
	b	.L453
.L449:
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
	beq	.L456
	mov	r1, #1
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L456:
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
	beq	.L460
	add	r7, r1, #12
	mov	r4, r1
	mov	r3, #1
	strb	r3, [r1]
.L459:
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #4]!
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r4, r7
	str	r0, [r4, #12]
	bne	.L459
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #28]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #32]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #36]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r3, #0
	str	r0, [r6, #40]
.L458:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L460:
	mvn	r3, #0
	b	.L458
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
	beq	.L464
	mov	r3, #1
	mov	r1, #16
	strb	r3, [r5]
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r1, #16
	strh	r0, [r5, #2]	@ movhi
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r3, r4
	strh	r0, [r5, #4]	@ movhi
.L463:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L464:
	mvn	r3, #0
	b	.L463
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
	beq	.L467
	ldr	r0, [r0, #2808]
	mov	r1, #8
	bl	BsGet
	mov	r3, r4
	strb	r0, [r5]
.L466:
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L467:
	mvn	r3, #0
	b	.L466
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
	beq	.L470
	mov	r1, #1
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	ldr	r0, [r5, #2808]
	bl	BsToNextByte
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L470:
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
	beq	.L474
	mov	r1, #1
	ldr	r0, [r0, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L475
.L473:
	ldr	r0, [r4, #2808]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L475:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L473
.L474:
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
	beq	.L478
	mov	r1, #4
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #1]
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r3, r4
	mov	r2, #1
	strb	r2, [r5]
	strb	r0, [r5, #2]
.L477:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L478:
	mvn	r3, #0
	b	.L477
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
	bls	.L488
.L482:
	mov	r1, #8
	ldr	r0, [r5, #2808]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L482
	subs	r6, r6, #16
	beq	.L484
.L483:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r6, r4
	bne	.L483
.L484:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L488:
	ldr	r1, .L489
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L490:
	.align	2
.L489:
	.word	.LC58
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
	ldr	r3, [r7, #780]
	cmp	r3, #0
	beq	.L492
	ldr	r4, [r0, #2868]
	cmp	r4, #0
	beq	.L493
	ldr	r2, [r4, #20]
	cmp	r2, #0
	addne	r6, r0, #2864
	movne	r4, #0
	addne	r6, r6, #4
	bne	.L498
	b	.L536
.L499:
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L500
	ldr	r3, [r7, #780]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L537
	ldr	r2, [r6, #4]!
	cmp	r2, #0
	beq	.L493
	ldr	r2, [r2, #20]
	cmp	r2, #0
	beq	.L494
.L498:
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #276]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	bne	.L499
.L500:
	add	r5, r5, r4, lsl #2
	mov	r2, r4
	ldr	r1, .L541
	mov	r0, #1
	ldr	r3, [r5, #2868]
	ldr	r3, [r3, #20]
	str	ip, [sp]
	bl	dprint_vfmw
.L497:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L537:
	cmp	r3, #0
	beq	.L492
	ldr	r2, [r7, #784]
	cmp	r2, #0
	beq	.L492
	ldr	r4, [r5, #2936]
	cmp	r4, #0
	beq	.L505
	ldr	r2, [r4, #20]
	cmp	r2, #0
	addne	r6, r5, #2928
	movne	r4, #0
	addne	r6, r6, #8
	bne	.L509
	b	.L538
.L510:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L511
	ldr	r3, [r7, #784]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L492
	ldr	r3, [r6, #4]!
	cmp	r3, #0
	beq	.L539
	ldr	r2, [r3, #20]
	cmp	r2, #0
	beq	.L540
.L509:
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #276]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L510
.L511:
	mov	r3, r0
	mov	r2, r4
	ldr	r1, .L541+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L531
.L492:
	mov	r0, #0
.L531:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L493:
	mov	r2, r4
	ldr	r1, .L541+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L497
.L536:
	mov	r4, r2
.L494:
	mov	r2, r4
	ldr	r1, .L541+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L497
.L539:
	ldr	r3, [r7, #780]
.L505:
	mov	r2, r4
	ldr	r1, .L541+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L531
.L540:
	ldr	r3, [r7, #780]
.L506:
	mov	r2, r4
	ldr	r1, .L541+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L531
.L538:
	mov	r4, r2
	b	.L506
.L542:
	.align	2
.L541:
	.word	.LC61
	.word	.LC64
	.word	.LC59
	.word	.LC60
	.word	.LC62
	.word	.LC63
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
	ldr	r3, [r0, #3040]
	cmp	r3, #16
	bhi	.L544
	cmp	r3, #0
	addne	lr, r0, #3200
	mvnne	r5, #-2147483648
	addne	lr, lr, #4
	movne	r2, #0
	beq	.L546
.L549:
	ldr	ip, [lr, #4]!
	ldr	r4, [ip, #8]
	cmp	r4, r5
	bge	.L548
	ldr	ip, [ip]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #0
	streq	r2, [r1]
	ldreq	r3, [r0, #3040]
	moveq	r5, r4
.L548:
	add	r2, r2, #1
	cmp	r3, r2
	bhi	.L549
	ldr	r3, [r1]
	cmn	r3, #1
	beq	.L546
	str	r5, [sp]
	mov	r0, #1
	ldr	r2, .L552
	ldr	r1, .L552+4
	bl	dprint_vfmw
	mov	r0, #0
.L547:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L544:
	ldr	r2, .L552
	mov	r0, #1
	ldr	r1, .L552+8
	bl	dprint_vfmw
	mov	r0, r4
	b	.L547
.L546:
	ldr	r2, .L552
	mov	r0, #1
	ldr	r1, .L552+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L547
.L553:
	.align	2
.L552:
	.word	.LANCHOR0+280
	.word	.LC67
	.word	.LC65
	.word	.LC66
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
	ldr	r3, [r0, #3036]
	mov	r5, r0
	cmp	r3, #16
	bhi	.L558
	ldr	r0, [r0, #276]
	bl	FSP_GetTotalValidFsNum
	add	r3, r5, #4096
	ldr	r2, [r5, #276]
	ldr	r1, [r3, #32]
	mov	r4, r0
	ldr	r0, [r3, #28]
	bl	FSP_GetOccupiedNum
	rsb	r0, r0, r4
	bic	r0, r0, r0, asr #31
	cmp	r0, #0
	ble	.L557
	ldr	r3, [r5, #3036]
	add	r3, r3, #1
	cmp	r0, r3
	bcc	.L557
	str	r3, [r5, #3036]
	mov	r0, #13
	ldr	r2, .L559
	ldr	r1, .L559+4
	bl	dprint_vfmw
	mov	r0, #0
.L556:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L557:
	mov	r3, r0
	ldr	r2, .L559
	ldr	r1, .L559+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L556
.L558:
	mov	r4, #17
	ldr	r2, .L559
	mov	r0, #1
	str	r4, [sp]
	ldr	r1, .L559+12
	bl	dprint_vfmw
	str	r4, [r5, #3036]
	mvn	r0, #0
	b	.L556
.L560:
	.align	2
.L559:
	.word	.LANCHOR0+308
	.word	.LC69
	.word	.LC70
	.word	.LC68
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
	add	r0, r0, #4096
	ldr	r3, [r0, #740]
	sub	r2, r3, #16
	cmp	r2, #5
	bls	.L562
	ldr	r3, [r0, #12]
	sub	r3, r3, #16
	cmp	r3, #5
	bls	.L573
	ldr	r3, [r0, #732]
	cmp	r3, #1
	beq	.L565
	cmp	r3, #2
	beq	.L566
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [r0, #24]
	ldmfd	sp, {fp, sp, pc}
.L562:
	str	r3, [r0, #12]
	mov	r3, #0
	str	r3, [r0, #24]
	ldmfd	sp, {fp, sp, pc}
.L565:
	ldr	r2, [r0, #24]
	cmp	r2, #2
	beq	.L574
	str	r3, [r0, #24]
	ldmfd	sp, {fp, sp, pc}
.L566:
	ldr	r3, [r0, #24]
	sub	r3, r3, #1
	cmp	r3, #1
	movhi	r3, #0
	strhi	r3, [r0, #24]
	ldmfd	sp, {fp, sp, pc}
.L574:
	ldmfd	sp, {fp, sp, pc}
.L573:
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
	ldr	r0, [r0, #740]
	cmp	r0, #15
	bhi	.L576
	tst	r0, #1
	bne	.L578
.L576:
	sub	r0, r0, #16
	cmp	r0, #7
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L578:
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
	ldr	r0, [r1, #640]
	ldr	r3, [r1, #644]
	ldrb	ip, [r1, #632]	@ zero_extendqisi2
	ldrb	lr, [r1, #636]	@ zero_extendqisi2
	mov	r0, r0, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r0, r0
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r0
	str	r3, [r2]
	ldr	r0, [r1, #640]
	ldrb	lr, [r1, #633]	@ zero_extendqisi2
	ldrb	r3, [r1, #645]	@ zero_extendqisi2
	and	r0, r0, #65280
	ldrb	ip, [r1, #637]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #4]
	ldr	r0, [r1, #636]
	ldrb	lr, [r1, #634]	@ zero_extendqisi2
	ldrb	r3, [r1, #646]	@ zero_extendqisi2
	and	r0, r0, #16711680
	ldrb	ip, [r1, #642]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #8]
	ldr	r0, [r1, #644]
	ldrb	r3, [r1, #639]	@ zero_extendqisi2
	ldrb	lr, [r1, #635]	@ zero_extendqisi2
	and	r0, r0, #-16777216
	ldrb	ip, [r1, #643]	@ zero_extendqisi2
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
	ldr	r1, [r0, #1792]
	ldr	r3, [r0, #1808]
	ldrb	ip, [lr, #632]	@ zero_extendqisi2
	ldrb	r4, [r0, #1800]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1824]
	ldr	r3, [r0, #1840]
	ldrb	ip, [r0, #1816]	@ zero_extendqisi2
	ldrb	r4, [r0, #1832]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1792]
	ldrb	r4, [lr, #633]	@ zero_extendqisi2
	ldrb	r3, [r0, #1809]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1801]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1824]
	ldrb	r4, [r0, #1817]	@ zero_extendqisi2
	ldrb	r3, [r0, #1841]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1833]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1800]
	ldrb	r4, [lr, #634]	@ zero_extendqisi2
	ldrb	r3, [r0, #1810]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1794]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1832]
	ldrb	r4, [r0, #1818]	@ zero_extendqisi2
	ldrb	r3, [r0, #1842]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1826]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1808]
	ldrb	lr, [lr, #635]	@ zero_extendqisi2
	ldrb	r3, [r0, #1803]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1795]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1840]
	ldrb	lr, [r0, #1819]	@ zero_extendqisi2
	ldrb	r3, [r0, #1835]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1827]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1796]
	ldr	r3, [r0, #1812]
	ldrb	ip, [r0, #1788]	@ zero_extendqisi2
	ldrb	lr, [r0, #1804]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1828]
	ldr	r3, [r0, #1844]
	ldrb	ip, [r0, #1820]	@ zero_extendqisi2
	ldrb	lr, [r0, #1836]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1796]
	ldrb	lr, [r0, #1789]	@ zero_extendqisi2
	ldrb	r3, [r0, #1813]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1805]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1828]
	ldrb	lr, [r0, #1821]	@ zero_extendqisi2
	ldrb	r3, [r0, #1845]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1837]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1804]
	ldrb	lr, [r0, #1790]	@ zero_extendqisi2
	ldrb	r3, [r0, #1814]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1798]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldr	r1, [r0, #1836]
	ldrb	lr, [r0, #1822]	@ zero_extendqisi2
	ldrb	r3, [r0, #1846]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1830]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1812]
	ldrb	lr, [r0, #1791]	@ zero_extendqisi2
	ldrb	r3, [r0, #1807]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1799]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1844]
	ldrb	ip, [r0, #1823]	@ zero_extendqisi2
	ldrb	r3, [r0, #1839]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1831]	@ zero_extendqisi2
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
	ldr	r1, [r0, #1032]
	ldr	r3, [r0, #1064]
	ldrb	ip, [lr, #632]	@ zero_extendqisi2
	ldrb	r4, [r0, #1048]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1040]
	ldr	r3, [r0, #1072]
	ldrb	ip, [r0, #1024]	@ zero_extendqisi2
	ldrb	r4, [r0, #1056]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1032]
	ldrb	r4, [lr, #633]	@ zero_extendqisi2
	ldrb	r3, [r0, #1065]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1049]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1040]
	ldrb	r4, [r0, #1025]	@ zero_extendqisi2
	ldrb	r3, [r0, #1073]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1057]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1048]
	ldrb	r4, [lr, #634]	@ zero_extendqisi2
	ldrb	r3, [r0, #1066]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1034]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1056]
	ldrb	r4, [r0, #1026]	@ zero_extendqisi2
	ldrb	r3, [r0, #1074]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1042]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1064]
	ldrb	lr, [lr, #635]	@ zero_extendqisi2
	ldrb	r3, [r0, #1051]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1035]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1072]
	ldrb	lr, [r0, #1027]	@ zero_extendqisi2
	ldrb	r3, [r0, #1059]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1043]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1036]
	ldr	r3, [r0, #1068]
	ldrb	ip, [r0, #1020]	@ zero_extendqisi2
	ldrb	lr, [r0, #1052]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1044]
	ldr	r3, [r0, #1076]
	ldrb	ip, [r0, #1028]	@ zero_extendqisi2
	ldrb	lr, [r0, #1060]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1036]
	ldrb	lr, [r0, #1021]	@ zero_extendqisi2
	ldrb	r3, [r0, #1069]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1053]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1044]
	ldrb	lr, [r0, #1029]	@ zero_extendqisi2
	ldrb	r3, [r0, #1077]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1061]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1052]
	ldrb	lr, [r0, #1022]	@ zero_extendqisi2
	ldrb	r3, [r0, #1070]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1038]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldr	r1, [r0, #1060]
	ldrb	lr, [r0, #1030]	@ zero_extendqisi2
	ldrb	r3, [r0, #1078]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1046]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1068]
	ldrb	lr, [r0, #1023]	@ zero_extendqisi2
	ldrb	r3, [r0, #1055]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1039]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1076]
	ldrb	ip, [r0, #1031]	@ zero_extendqisi2
	ldrb	r3, [r0, #1063]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1047]	@ zero_extendqisi2
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
	ldr	r1, [r0, #1408]
	ldr	r3, [r0, #1424]
	ldrb	ip, [lr, #632]	@ zero_extendqisi2
	ldrb	r4, [r0, #1416]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1440]
	ldr	r3, [r0, #1456]
	ldrb	ip, [r0, #1432]	@ zero_extendqisi2
	ldrb	r4, [r0, #1448]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1408]
	ldrb	r4, [lr, #633]	@ zero_extendqisi2
	ldrb	r3, [r0, #1425]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1417]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1440]
	ldrb	r4, [r0, #1433]	@ zero_extendqisi2
	ldrb	r3, [r0, #1457]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1449]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1416]
	ldrb	r4, [lr, #634]	@ zero_extendqisi2
	ldrb	r3, [r0, #1426]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1410]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1448]
	ldrb	r4, [r0, #1434]	@ zero_extendqisi2
	ldrb	r3, [r0, #1458]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1442]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1424]
	ldrb	lr, [lr, #635]	@ zero_extendqisi2
	ldrb	r3, [r0, #1419]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1411]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1456]
	ldrb	lr, [r0, #1435]	@ zero_extendqisi2
	ldrb	r3, [r0, #1451]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1443]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1412]
	ldr	r3, [r0, #1428]
	ldrb	ip, [r0, #1404]	@ zero_extendqisi2
	ldrb	lr, [r0, #1420]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1444]
	ldr	r3, [r0, #1460]
	ldrb	ip, [r0, #1436]	@ zero_extendqisi2
	ldrb	lr, [r0, #1452]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1412]
	ldrb	lr, [r0, #1405]	@ zero_extendqisi2
	ldrb	r3, [r0, #1429]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1421]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1444]
	ldrb	lr, [r0, #1437]	@ zero_extendqisi2
	ldrb	r3, [r0, #1461]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1453]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1420]
	ldrb	lr, [r0, #1406]	@ zero_extendqisi2
	ldrb	r3, [r0, #1430]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1414]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldr	r1, [r0, #1452]
	ldrb	lr, [r0, #1438]	@ zero_extendqisi2
	ldrb	r3, [r0, #1462]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1446]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1428]
	ldrb	lr, [r0, #1407]	@ zero_extendqisi2
	ldrb	r3, [r0, #1423]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1415]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1460]
	ldrb	ip, [r0, #1439]	@ zero_extendqisi2
	ldrb	r3, [r0, #1455]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1447]	@ zero_extendqisi2
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
	ldr	ip, [r0, #2844]
	mov	r6, r1
	ldrb	r3, [ip, #13]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L618
	ldr	r3, [ip, #72]
	ldr	r7, [ip, #68]
	ldrb	r5, [ip, #15]	@ zero_extendqisi2
	mov	r2, r3
	str	r3, [fp, #-236]
	ldr	r3, [r0, #2840]
	cmp	r2, #0
	sub	r8, r2, #1
	sub	r2, r7, #1
	str	r2, [fp, #-240]
	ldr	r4, [r3, #64]
	ldr	r1, [r3, #128]
	ble	.L589
	ldr	r3, [fp, #-236]
	add	r2, ip, #210
	sub	r0, fp, #216
	add	lr, r3, #105
	add	lr, ip, lr, lsl #1
.L588:
	ldrsh	r3, [r2, #2]!
	cmp	r2, lr
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L588
.L589:
	cmp	r7, #0
	ble	.L587
	add	r3, r7, #85
	add	r2, ip, #170
	sub	r0, fp, #128
	add	ip, ip, r3, lsl #1
.L592:
	ldrsh	r3, [r2, #2]!
	cmp	r2, ip
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L592
.L587:
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
	beq	.L633
	cmp	r8, #0
	mov	r3, #0
	blt	.L609
	sub	r10, fp, #212
	mov	lr, r3
	mov	r6, r3
	mov	r8, r3
	str	r3, [fp, #-232]
	str	r3, [fp, #-244]
.L595:
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	blt	.L612
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	ip, r2
	add	r8, r8, #1
	sub	r5, fp, #128
	mov	r6, lr
	add	r9, r3, r8
	b	.L598
.L610:
	mov	r6, lr
.L598:
	ldr	r3, [r5, #4]!
	add	ip, ip, #1
	add	r3, r3, #1
	add	r1, r2, r3
	cmp	r4, r1
	mla	lr, r8, r3, lr
	bge	.L596
	cmp	r0, r9
	blt	.L630
.L596:
	cmp	ip, r7
	mov	r2, r1
	bne	.L610
.L601:
	add	r2, r1, r3
	cmp	r4, r2
	bge	.L611
	cmp	r0, r9
	blt	.L628
.L611:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	ip, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, ip
	str	r2, [fp, #-244]
	bne	.L595
.L629:
	rsb	r0, r9, r0
	mov	r2, r1
	mul	r3, r0, r3
.L593:
	rsb	r2, r2, r4
	add	r3, r2, r3
	add	r6, r3, r6
.L618:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L633:
	cmp	r8, #0
	mov	r3, r5
	blt	.L609
	ldr	r2, [fp, #-240]
	sub	r10, fp, #212
	str	r5, [fp, #-232]
	mov	lr, r5
	cmp	r2, #0
	str	r5, [fp, #-244]
	mov	r6, r5
	mov	r8, r5
	blt	.L615
.L634:
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	ip, r2
	add	r8, r8, #1
	sub	r5, fp, #128
	mov	r6, lr
	add	r9, r3, r8
	b	.L604
.L613:
	mov	r6, lr
.L604:
	ldr	r3, [r5, #4]!
	add	ip, ip, #1
	add	r3, r3, #1
	add	r1, r2, r3
	cmp	r4, r1
	mla	lr, r8, r3, lr
	bge	.L602
	cmp	r0, r9
	blt	.L603
.L602:
	cmp	ip, r7
	mov	r2, r1
	bne	.L613
.L607:
	add	r2, r1, r3
	cmp	r4, r2
	bge	.L627
	cmp	r0, r9
	blt	.L628
.L627:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	ip, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, ip
	str	r2, [fp, #-244]
	beq	.L629
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	bge	.L634
.L615:
	ldr	r2, [fp, #-232]
	mov	r1, #0
	add	r9, r2, r8
	b	.L607
.L630:
	ldr	r1, [fp, #-232]
	rsb	r0, r1, r0
	mul	r3, r0, r3
	b	.L593
.L603:
	cmp	r1, r4
	bgt	.L630
	mov	r1, r2
	b	.L627
.L612:
	ldr	r2, [fp, #-232]
	mov	r1, #0
	add	r9, r2, r8
	b	.L601
.L628:
	ldr	r2, [fp, #-232]
	rsb	r0, r2, r0
	mov	r2, r1
	mul	r3, r0, r3
	b	.L593
.L609:
	mov	r2, r3
	mov	r6, r3
	b	.L593
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
	ldr	lr, [r0, #2844]
	mov	r6, r1
	ldrb	r3, [lr, #13]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r0, r1
	beq	.L659
	ldr	r3, [lr, #72]
	ldr	r7, [lr, #68]
	mov	r2, r3
	str	r3, [fp, #-232]
	ldr	r3, [r0, #2840]
	cmp	r2, #0
	ldr	r4, [r3, #64]
	ldr	ip, [r3, #128]
	ble	.L641
	ldr	r3, [fp, #-232]
	add	r2, lr, #210
	sub	r1, fp, #216
	add	r0, r3, #105
	add	r0, lr, r0, lsl #1
.L640:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L640
.L641:
	cmp	r7, #0
	ble	.L639
	add	r0, r7, #85
	add	r2, lr, #170
	sub	r1, fp, #128
	add	r0, lr, r0, lsl #1
.L644:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L644
.L639:
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
	ble	.L643
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
.L645:
	cmp	r7, #0
	ble	.L655
	ldr	r0, [r9]
	ldr	r4, [fp, #-236]
	add	r0, r0, #1
	mla	r1, r0, r4, r3
	cmp	r6, r1
	blt	.L656
	mov	r5, #0
	mov	lr, r3
	mov	r2, r5
	mov	r3, r1
	sub	ip, fp, #124
	b	.L650
.L647:
	ldr	r4, [ip, #4]!
	mov	lr, r3
	add	r4, r4, #1
	mla	r1, r0, r4, r3
	cmp	r1, r6
	bgt	.L648
	mov	r3, r1
.L650:
	add	r2, r2, #1
	add	r5, r5, r4
	cmp	r2, r7
	bne	.L647
.L649:
	cmp	r3, r6
	bgt	.L654
	ldr	r2, [fp, #-232]
	add	r10, r10, #1
	add	r8, r8, r0
	add	r9, r9, #4
	cmp	r10, r2
	bne	.L645
.L654:
	mov	r3, lr
.L648:
	cmp	r4, #0
	beq	.L643
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
.L659:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L655:
	mov	r5, #0
	b	.L649
.L656:
	ldr	r4, [fp, #-236]
	mov	r5, #0
	b	.L648
.L643:
	ldr	r1, .L661
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L659
.L662:
	.align	2
.L661:
	.word	.LC71
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
	ldr	r4, .L690
	mov	r10, r0
	ldr	r0, [r4]
	cmp	r0, #0
	beq	.L689
	ldr	r5, .L690+4
	add	r0, r0, #483328
	mov	r2, #147456
	mov	r1, #0
	add	r0, r0, #336
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r0, [r4]
	ldr	r3, [r5, #48]
	mov	r2, #36864
	add	r0, r0, #630784
	mov	r1, #0
	add	r0, r0, #336
	blx	r3
	add	r0, r10, #9216
	ldr	r3, [r5, #48]
	mov	r2, #880
	mov	r1, #0
	add	r0, r0, #20
	blx	r3
	add	r3, r10, #8192
	str	r3, [fp, #-60]
	mov	r2, r3
	mov	r3, #0
	str	r3, [r2, #1040]
	ldr	r9, [r10, #2844]
	ldr	r1, [r10, #2840]
	ldr	r2, [r9, #72]
	ldr	r8, [r1, #188]
	cmp	r2, r3
	beq	.L666
	ldr	r2, [r4]
	str	r3, [fp, #-72]
	str	r3, [fp, #-76]
	str	r2, [fp, #-48]
.L667:
	ldr	r2, [r9, #68]
	cmp	r2, #0
	ldr	r2, [fp, #-72]
	add	r2, r2, #104
	streq	r2, [fp, #-80]
	beq	.L673
	mov	r1, r2
	str	r2, [fp, #-80]
	mov	r7, r1, asl #1
	ldr	r1, [fp, #-76]
	mov	r2, #0
	str	r2, [fp, #-52]
	str	r2, [fp, #-56]
	mul	r1, r8, r1
	ldr	r2, [fp, #-60]
	ldr	r2, [r2, #1040]
	str	r1, [fp, #-68]
.L672:
	add	r1, r2, #1152
	add	r0, r9, r7
	add	r1, r1, #2
	add	r1, r10, r1, lsl #3
	str	r3, [r1, #4]
	ldrsh	r1, [r0, #4]
	cmp	r1, #0
	ldreq	r1, [fp, #-52]
	addeq	r1, r1, #84
	streq	r1, [fp, #-64]
	beq	.L668
	ldr	r2, [fp, #-52]
	mov	r5, #0
	ldr	r1, [fp, #-56]
	add	r2, r2, #84
	ldr	r0, [fp, #-68]
	str	r2, [fp, #-64]
	add	r6, r1, r0
	mov	ip, r2, asl #1
.L669:
	add	r2, r9, ip
	ldrsh	r2, [r2, #4]
	cmp	r2, #0
	beq	.L671
	add	r2, r3, #120832
	ldr	r1, [fp, #-48]
	add	r2, r2, #83
	rsb	lr, r3, r6
	mov	r4, r3
	add	r2, r1, r2, lsl #2
.L670:
	add	r1, lr, r3
	str	r1, [r2, #4]!
	ldr	r9, [r10, #2844]
	add	r3, r3, #1
	rsb	r1, r4, r3
	add	r0, r9, ip
	ldrsh	r0, [r0, #4]
	cmp	r0, r1
	bhi	.L670
.L671:
	add	r2, r9, r7
	add	r5, r5, #1
	add	r6, r6, r8
	ldrsh	r2, [r2, #4]
	cmp	r2, r5
	bhi	.L669
	ldr	r2, [fp, #-60]
	ldr	r2, [r2, #1040]
.L668:
	add	r1, r10, r2, lsl #3
	ldr	r0, [fp, #-64]
	add	r1, r1, #9216
	sub	ip, r3, #1
	ldr	lr, [fp, #-52]
	add	r2, r2, #1
	str	ip, [r1, #24]
	add	r0, r9, r0, lsl #1
	ldr	r1, [fp, #-60]
	add	lr, lr, #1
	str	lr, [fp, #-52]
	str	r2, [r1, #1040]
	ldr	r1, [r9, #68]
	ldrsh	r0, [r0, #4]
	cmp	r1, lr
	ldr	r1, [fp, #-56]
	add	r1, r1, r0
	str	r1, [fp, #-56]
	bhi	.L672
.L673:
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
	bhi	.L667
.L666:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L689:
	ldr	r2, .L690+8
	ldr	r1, .L690+12
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L691:
	.align	2
.L690:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+332
	.word	.LC72
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
	add	r4, r0, #4096
	mov	r5, r0
	ldr	r1, .L715
	mov	r0, #2
	ldr	r3, [r4, #44]
	add	r8, r5, #8192
	ldr	r2, [r4, #220]
	mov	r7, #280
	bl	dprint_vfmw
	ldr	r1, .L715+4
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r2, [r4, #184]
	ldr	r1, [r4, #188]
	mov	ip, #0
	ldr	r0, [r4, #220]
	ldr	r3, [r4, #44]
	ldr	lr, [r4, #216]
	str	r2, [r4, #3736]
	str	r1, [r4, #3740]
	ldr	r2, [r4, #108]
	ldr	r1, [r4, #112]
	str	r0, [r4, #3728]
	str	r3, [r4, #3732]
	rsb	r1, r2, r1
	ldr	r3, [r4, #16]
	ldr	r6, [r4, #208]
	ldr	r0, [r4, #212]
	str	r1, [r4, #3744]
	str	lr, [r4, #3756]
	ldr	r1, [r4, #120]
	ldr	lr, [r4, #116]
	str	r6, [r4, #3748]
	str	r0, [r4, #3752]
	rsb	r2, r2, lr
	str	r3, [r4, #2472]
	add	r0, r5, #6656
	str	r2, [r4, #3760]
	rsb	r2, lr, r1
	str	r2, [r4, #3764]
	add	r0, r0, #8
	ldr	r2, [r5, #2860]
	str	ip, [r5, #204]
	mul	r7, r7, r3
	str	r2, [r8, #836]
	ldr	r3, [r5, #2840]
	mov	r2, #64
	ldr	r6, .L715+8
	add	r1, r5, r7
	ldrb	ip, [r3, #10]	@ zero_extendqisi2
	add	r1, r1, #13248
	add	r1, r1, #52
	strb	ip, [r4, #2446]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	strb	ip, [r4, #2447]
	ldrb	ip, [r3, #7]	@ zero_extendqisi2
	strb	ip, [r4, #2448]
	ldrb	ip, [r3, #6]	@ zero_extendqisi2
	ldr	lr, [r4, #20]
	strb	ip, [r4, #2449]
	ldrb	ip, [r3, #5]	@ zero_extendqisi2
	strb	ip, [r4, #2450]
	ldr	ip, [r3, #60]
	str	ip, [r4, #2452]
	ldr	ip, [r3, #104]
	strb	ip, [r4, #2456]
	ldr	ip, [r3, #192]
	sub	ip, ip, #1
	str	ip, [r4, #2460]
	ldr	ip, [r3, #188]
	str	lr, [r4, #2468]
	sub	ip, ip, #1
	str	ip, [r4, #2464]
	ldr	ip, [r5, #2844]
	ldr	lr, [ip, #84]
	sub	lr, lr, #2
	str	lr, [r4, #2476]
	ldrb	lr, [ip, #11]	@ zero_extendqisi2
	strb	lr, [r4, #2480]
	ldrb	ip, [ip, #10]	@ zero_extendqisi2
	strb	ip, [r4, #2481]
	ldr	ip, [r3, #164]
	str	ip, [r4, #2484]
	ldr	ip, [r3, #168]
	str	ip, [r4, #2488]
	ldr	ip, [r3, #156]
	str	ip, [r4, #2492]
	ldr	ip, [r3, #160]
	str	ip, [r4, #2496]
	ldr	ip, [r3, #148]
	str	ip, [r4, #2500]
	ldr	ip, [r3, #152]
	str	ip, [r4, #2504]
	ldr	ip, [r3, #172]
	ldr	r6, [r6, #52]
	str	ip, [r4, #2508]
	ldr	ip, [r3, #124]
	str	ip, [r4, #2512]
	ldr	ip, [r3, #128]
	str	ip, [r4, #2516]
	ldr	ip, [r3, #100]
	str	ip, [r4, #2520]
	ldr	ip, [r3, #92]
	str	ip, [r4, #2524]
	ldr	ip, [r3, #112]
	str	ip, [r4, #2528]
	ldr	ip, [r3, #108]
	str	ip, [r4, #2532]
	ldr	ip, [r3, #96]
	str	ip, [r4, #2536]
	ldr	r3, [r3, #88]
	str	r3, [r4, #2540]
	blx	r6
	ldr	ip, [r5, #2840]
	add	r3, r5, #8832
	add	r2, r5, #8768
	add	r1, r5, #8256
	add	r3, r3, #36
	ldr	lr, [ip, #68]
	add	r2, r2, #20
	add	r1, r1, #20
	mov	r0, r5
	str	lr, [r4, #2632]
	ldr	ip, [ip, #64]
	str	ip, [r4, #2636]
	bl	HEVC_CalcTileInfo
	subs	r6, r0, #0
	bne	.L713
	ldr	r3, [r5, #2844]
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	strb	r2, [r4, #2660]
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	strb	r2, [r4, #2661]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	strb	r2, [r4, #2662]
	ldrb	r2, [r3, #14]	@ zero_extendqisi2
	strb	r2, [r4, #2663]
	ldrb	r2, [r3, #15]	@ zero_extendqisi2
	strb	r2, [r4, #2664]
	ldrb	r2, [r3, #13]	@ zero_extendqisi2
	strb	r2, [r4, #2665]
	ldr	r2, [r5, #2840]
	ldr	r1, [r3, #56]
	ldr	r2, [r2, #128]
	rsb	r2, r1, r2
	str	r2, [r4, #2668]
	ldr	r2, [r3, #52]
	str	r2, [r4, #2672]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	strb	r2, [r4, #2676]
	ldrb	r2, [r3, #12]	@ zero_extendqisi2
	strb	r2, [r4, #2677]
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	strb	r2, [r4, #2678]
	ldr	r2, [r3, #60]
	str	r2, [r4, #2680]
	ldr	r2, [r3, #64]
	str	r2, [r4, #2684]
	ldr	r2, [r3, #72]
	sub	r2, r2, #1
	str	r2, [r4, #2688]
	ldr	r2, [r3, #68]
	sub	r2, r2, #1
	str	r2, [r4, #2692]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	strb	r2, [r4, #2481]
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	strb	r3, [r4, #2480]
	ldr	r3, [r5, #2368]
	str	r6, [r5, #2384]
	cmp	r3, #1
	beq	.L704
	ldr	r3, [r4, #68]
	ldr	r0, [r5, #276]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	subs	r9, r0, #0
	beq	.L714
	ldr	r2, [r9, #28]
	ldr	r3, [r9, #32]
	cmp	r2, #0
	beq	.L697
	cmp	r3, #0
	beq	.L697
	add	r3, r5, #8128
	add	r2, r5, #7872
	add	r1, r5, #8000
	add	r3, r3, #20
	add	r2, r2, #8
	add	r1, r1, #8
	ldr	r0, [r5, #276]
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r9, #28]
	add	r2, r5, #8000
	add	r1, r5, #8128
	add	r2, r2, #12
	add	r1, r1, #12
	ldr	r3, [r3, #4]
	str	r3, [r4, #3728]
	ldr	r0, [r5, #276]
	bl	FSP_GetPmvAddrTab
	ldr	r2, [r4, #44]
	add	r3, r5, r7
	add	r3, r3, #13120
	str	r2, [r4, #3732]
	ldr	r2, [r9, #12]
	str	r2, [r4, #4048]
	ldr	r2, [r9, #32]
	ldr	r2, [r2, #8]
	str	r2, [r8, #1032]
	ldr	r2, [r9, #32]
	ldr	r2, [r2, #60]
	str	r2, [r8, #1036]
	ldr	ip, [r3, #44]
	cmp	ip, #0
	str	ip, [r8, #828]
	beq	.L699
	add	r3, r7, #13184
	add	r2, r5, #8896
	add	r3, r3, #48
	add	r2, r2, #56
	add	r3, r5, r3
	mov	r0, r6
.L700:
	add	r0, r0, #1
	ldr	r1, [r3, #4]!
	cmp	r0, ip
	str	r1, [r2, #4]!
	bne	.L700
.L699:
	add	r7, r5, #6784
	mov	r6, #0
	add	r7, r7, #12
.L701:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r5
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_8x8
	cmp	r6, #4
	add	r7, r7, #64
	bne	.L701
	add	r2, r5, #7040
	mov	r0, r6
	add	r2, r2, #12
	mov	r1, r5
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r5, #7104
	add	r2, r2, #12
	mov	r1, r5
	mov	r0, #5
	add	r7, r5, #7296
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r5, #7168
	add	r2, r2, #12
	mov	r1, r5
	mov	r0, #0
	add	r7, r7, #12
	bl	HEVC_WriteQmatrix_16x16
	add	r2, r5, #7232
	add	r2, r2, #12
	mov	r1, r5
	mov	r0, #1
	mov	r6, #2
	bl	HEVC_WriteQmatrix_16x16
.L702:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r5
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_16x16
	cmp	r6, #6
	add	r7, r7, #64
	bne	.L702
	add	r2, r5, #7552
	mov	r1, r5
	add	r2, r2, #12
	mov	r0, #0
	bl	HEVC_WriteQmatrix_32x32
	add	r2, r5, #7616
	add	r2, r2, #12
	mov	r1, r5
	mov	r0, #1
	add	r7, r5, #7680
	bl	HEVC_WriteQmatrix_32x32
	add	r7, r7, #12
	mov	r6, #0
.L703:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r5
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_4x4
	cmp	r6, #6
	add	r7, r7, #16
	bne	.L703
	ldr	r1, [r5, #2320]
	mov	r0, #0
	ldr	r3, [r5, #2324]
	ldr	r2, [r5, #2312]
	ldr	ip, [r5, #2316]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	ldr	lr, [r4, #44]
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r4, #3692]
	ldr	r1, [r5, #2336]
	ldr	r3, [r5, #2340]
	ldr	r2, [r5, #2328]
	ldr	ip, [r5, #2332]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	str	lr, [r4, #3724]
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r4, #3696]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L704:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L713:
	ldr	r2, .L715+12
	mov	r0, #1
	ldr	r1, .L715+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L697:
	ldr	r1, .L715+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L714:
	ldr	r3, [r4, #68]
	mov	r0, #1
	ldr	r1, .L715+24
	ldr	r2, [r3, #28]
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L716:
	.align	2
.L715:
	.word	.LC73
	.word	.LC74
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+352
	.word	.LC75
	.word	.LC77
	.word	.LC76
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
	ldrb	r3, [r3, #713]	@ zero_extendqisi2
	cmp	r3, #0
	addeq	r3, r0, #4800
	addeq	r3, r3, #8
	beq	.L719
	ldrsb	r3, [r0, #14]
	cmp	r3, #0
	addne	r3, r0, #11776
	addne	r3, r3, #12
	beq	.L752
.L719:
	ldr	ip, [r3, #68]
	ldr	lr, [r3, #72]
	cmp	ip, #16
	bhi	.L753
	cmp	lr, #16
	bhi	.L723
	cmp	ip, #0
	beq	.L724
	ldr	r3, [r0, #2868]
	cmp	r3, #0
	beq	.L737
	ldr	r3, [r3, #20]
	cmp	r3, #0
	addne	r1, r0, #2864
	movne	r2, #0
	addne	r1, r1, #4
	bne	.L729
	b	.L754
.L730:
	ldr	r3, [r1, #4]!
	cmp	r3, #0
	beq	.L725
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L726
.L729:
	add	r2, r2, #1
	cmp	r2, ip
	bne	.L730
.L724:
	cmp	lr, #0
	beq	.L749
	ldr	r3, [r0, #2936]
	cmp	r3, #0
	beq	.L740
	ldr	r3, [r3, #20]
	cmp	r3, #0
	addne	r0, r0, #2928
	movne	r2, #0
	addne	r0, r0, #8
	bne	.L735
	b	.L755
.L736:
	ldr	r3, [r0, #4]!
	cmp	r3, #0
	beq	.L731
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L732
.L735:
	add	r2, r2, #1
	cmp	r2, lr
	bne	.L736
.L749:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L737:
	mov	r2, r3
.L725:
	ldr	r1, .L756
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L754:
	mov	r2, r3
.L726:
	ldr	r1, .L756+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L740:
	mov	r2, r3
.L731:
	ldr	r1, .L756+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L755:
	mov	r2, r3
.L732:
	ldr	r1, .L756+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L752:
	mov	r0, r3
	ldr	r2, .L756+16
	ldr	r1, .L756+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L723:
	mov	r2, lr
	mov	r3, #17
	ldr	r1, .L756+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L753:
	mov	r2, ip
	mov	r3, #17
	ldr	r1, .L756+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L757:
	.align	2
.L756:
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC84
	.word	.LANCHOR0+372
	.word	.LC78
	.word	.LC80
	.word	.LC79
	UNWIND(.fnend)
	.size	HEVC_CheckListX, .-HEVC_CheckListX
	.align	2
	.global	HEVC_WriteSliceMsg
	.type	HEVC_WriteSliceMsg, %function
HEVC_WriteSliceMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	add	r7, r0, #4096
	mov	r4, r0
	ldr	r9, [r7, #16]
	bl	HEVC_CheckListX
	subs	r3, r0, #0
	str	r3, [fp, #-112]
	bne	.L828
	ldr	r0, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r0, r3
	bcs	.L901
	ldr	r5, [r4, #2860]
	movw	r6, #1508
	ldr	r10, [fp, #-112]
	mov	r2, r6
	ldr	r3, .L909
	mla	r5, r6, r0, r5
	mov	r1, r10
	ldr	r3, [r3, #48]
	mov	r0, r5
	blx	r3
	ldr	r3, .L909
	mov	r2, #64
	mov	r1, r10
	sub	r0, fp, #108
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #204]
	ldr	r2, [r4, #152]
	add	r3, r3, #1
	str	r3, [r4, #204]
	cmp	r3, r2
	ldrcc	r2, [r4, #2860]
	ldrcs	r3, [fp, #-112]
	mlacc	r3, r6, r3, r2
	str	r3, [r5, #1504]
	ldr	r1, [r7, #748]
	ldr	r2, [r4, #2828]
	ldr	r0, [r4, #176]
	ldr	r3, [r4, #260]
	add	r0, r0, #1
	str	r1, [r4, #208]
	str	r0, [r4, #176]
	add	r3, r3, #1
	str	r3, [r4, #260]
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	str	r0, [fp, #-120]
	cmp	r1, #1
	cmpls	r1, r3
	bcs	.L763
	add	r0, r5, r1, lsl #2
.L764:
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r1, r1, #1
	add	r2, r2, r3
	ldr	r2, [r2, #56]
	str	r2, [r0, #8]
	ldr	r2, [r4, #2828]
	add	r2, r2, r3
	ldr	r2, [r2, #52]
	str	r2, [r0], #4
	ldr	r2, [r4, #2828]
	add	r3, r2, r3
	ldr	r3, [r3, #60]
	str	r3, [r0, #12]
	ldr	r2, [r4, #2828]
	ldr	r3, [r2, #8]
	cmp	r3, r1
	movhi	ip, #1
	movls	ip, #0
	cmp	r1, #1
	movhi	ip, #0
	cmp	ip, #0
	bne	.L764
.L763:
	cmp	r3, #1
	addls	r3, r5, r3, lsl #2
	addls	r1, r5, #8
	movls	r2, #0
	bhi	.L769
.L768:
	str	r2, [r3, #8]
	str	r2, [r3], #4
	cmp	r3, r1
	str	r2, [r3, #12]
	bne	.L768
.L769:
	ldrb	r3, [r7, #713]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L902
.L767:
	add	r6, r4, #8192
	ldr	r3, [r6, #3664]
	cmp	r3, #0
	beq	.L770
	add	ip, r4, #2864
	add	r1, r5, #112
	mov	r0, #0
	mov	lr, #1
	b	.L774
.L904:
	ldr	r3, [r10, #16]
	cmp	r3, #0
	beq	.L772
	ldr	r3, [r7, #744]
	cmp	r3, #0
	beq	.L772
	ldr	r2, [r10, #20]
	sub	r8, fp, #44
	add	r0, r0, #1
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #36]
	add	r3, r3, #2000
	add	r3, r3, #2
	add	r2, r8, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r10, #20]
	ldr	r3, [r3, #36]
	str	r3, [r1, #256]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #0
	strne	lr, [r1]
	ldr	r2, [r6, #3664]
	cmp	r2, r0
	bls	.L903
.L774:
	ldr	r3, [ip, #4]!
	ldr	r3, [r3, #4]
	str	r3, [r1, #4]!
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	ldr	r10, [ip]
	cmp	r3, #0
	bne	.L904
.L772:
	ldr	r2, [r10, #20]
	sub	r8, fp, #44
	add	r0, r0, #1
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #24]
	add	r3, r3, #2000
	add	r3, r3, #2
	add	r2, r8, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r10, #20]
	ldr	r3, [r3, #24]
	str	r3, [r1, #256]
	ldr	r2, [r6, #3664]
	cmp	r2, r0
	bhi	.L774
.L903:
	ldr	r0, [r6, #3668]
	cmp	r0, #0
	beq	.L775
.L827:
	add	r1, r4, #2928
	add	ip, r5, #176
	add	r1, r1, #4
	mov	lr, #0
	mov	r10, #1
	b	.L779
.L906:
	ldr	r3, [r0, #16]
	cmp	r3, #0
	beq	.L777
	ldr	r3, [r7, #744]
	cmp	r3, #0
	beq	.L777
	ldr	r2, [r0, #20]
	sub	r8, fp, #44
	add	lr, lr, #1
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #36]
	add	r3, r3, #2000
	add	r3, r3, #2
	add	r2, r8, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r0, #20]
	ldr	r3, [r3, #36]
	str	r3, [ip, #256]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #0
	strne	r10, [ip]
	ldr	r0, [r6, #3668]
	cmp	r0, lr
	bls	.L905
.L779:
	ldr	r3, [r1, #4]!
	ldr	r3, [r3, #4]
	str	r3, [ip, #4]!
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	ldr	r0, [r1]
	cmp	r3, #0
	bne	.L906
.L777:
	ldr	r2, [r0, #20]
	sub	r8, fp, #44
	add	lr, lr, #1
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #24]
	add	r3, r3, #2000
	add	r3, r3, #2
	add	r2, r8, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r0, #20]
	ldr	r3, [r3, #24]
	str	r3, [ip, #256]
	ldr	r0, [r6, #3668]
	cmp	r0, lr
	bhi	.L779
.L905:
	ldr	r2, [r6, #3664]
.L775:
	cmp	r2, #0
	beq	.L780
	mov	lr, #70
	ldr	r3, [r5, #372]
	mul	lr, lr, r9
	ldr	r10, [r7, #20]
	add	r3, lr, r3
	add	r3, r3, #3312
	add	r3, r3, #12
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	r10, r3
	blt	.L834
	add	ip, r5, #372
	mov	r1, #0
	b	.L782
.L783:
	ldr	r3, [ip, #4]!
	add	r3, lr, r3
	add	r3, r3, #3312
	add	r3, r3, #12
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, r10
	bgt	.L834
.L782:
	add	r1, r1, #1
	cmp	r1, r2
	bne	.L783
.L780:
	ldr	r2, [r6, #3616]
	cmp	r2, #0
	bne	.L899
	cmp	r0, #0
	beq	.L899
	mov	r1, #70
	ldr	r3, [r5, #436]
	mul	r9, r1, r9
	ldr	ip, [r7, #20]
	add	r3, r9, r3
	add	r3, r3, #3312
	add	r3, r3, #12
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	ip, r3
	blt	.L781
	add	r1, r5, #436
	b	.L784
.L785:
	ldr	r3, [r1, #4]!
	add	r3, r9, r3
	add	r3, r3, #3312
	add	r3, r3, #12
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, ip
	bgt	.L834
.L784:
	add	r2, r2, #1
	cmp	r2, r0
	bne	.L785
.L899:
	mov	r2, #1
.L781:
	strb	r2, [r5, #24]
	ldrb	r3, [r7, #713]	@ zero_extendqisi2
	strb	r3, [r5, #25]
	ldr	r2, [r6, #3612]
	str	r2, [r5, #28]
	ldrb	r3, [r6, #3603]	@ zero_extendqisi2
	strb	r3, [r5, #32]
	ldr	r3, [r6, #3636]
	str	r3, [r5, #36]
	ldr	r3, [r4, #2368]
	cmp	r3, #0
	bne	.L786
	ldr	r9, [r7, #68]
	ldr	r1, [r4, #204]
	ldr	r0, [r9, #316]
	sub	r3, r1, #1
	mla	r0, r0, r3, r2
	bl	__aeabi_uidiv
	str	r0, [r9, #68]
.L786:
	ldr	r3, [r6, #3616]
	cmp	r3, #0
	bne	.L787
	ldrb	r3, [r6, #3604]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L788
	ldr	r3, [r6, #3640]
	add	r3, r5, r3, lsl #2
	ldr	r9, [r3, #436]
.L789:
	str	r9, [r5, #40]
	ldr	r3, [r6, #3640]
	str	r3, [r5, #48]
	ldrb	r3, [r6, #3604]	@ zero_extendqisi2
	strb	r3, [r5, #52]
	ldr	r3, [r6, #3644]
	str	r3, [r5, #44]
	ldr	r3, [r6, #3672]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r5, #60]
	ldr	r3, [r6, #3676]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r5, #56]
	ldrb	r3, [r6, #3600]	@ zero_extendqisi2
	strb	r3, [r5, #64]
	ldrb	r3, [r6, #3602]	@ zero_extendqisi2
	strb	r3, [r5, #65]
	ldr	r3, [r6, #3664]
	str	r3, [r5, #68]
	ldr	r3, [r6, #3668]
	str	r3, [r5, #72]
	ldr	r3, [r6, #3616]
	str	r3, [r5, #76]
	ldr	r3, [r7, #752]
	str	r3, [r5, #80]
	ldr	r3, [r4, #2840]
	ldr	r0, [r7, #752]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidivmod
	str	r1, [r5, #84]
	ldr	r3, [r4, #2840]
	ldr	r0, [r7, #752]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidiv
	str	r0, [r5, #88]
	mov	r0, r4
	ldr	r1, [r7, #752]
	bl	HEVC_CtbRsAddrToTsAddr
	str	r0, [r5, #92]
	ldr	r3, [r6, #3648]
	str	r3, [r5, #96]
	ldr	r3, [r6, #3652]
	str	r3, [r5, #100]
	ldr	r3, [r6, #3660]
	str	r3, [r5, #104]
	ldr	r3, [r6, #3656]
	str	r3, [r5, #108]
	ldrb	r3, [r6, #3599]	@ zero_extendqisi2
	strb	r3, [r5, #112]
	ldrb	r3, [r6, #3598]	@ zero_extendqisi2
	strb	r3, [r5, #113]
	ldrb	r3, [r6, #3605]	@ zero_extendqisi2
	strb	r3, [r5, #114]
	ldrb	r3, [r6, #3606]	@ zero_extendqisi2
	strb	r3, [r5, #115]
	ldr	r3, [r4, #2844]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L794
	ldr	r2, [r6, #3616]
	cmp	r2, #1
	beq	.L795
.L794:
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L907
.L797:
	ldrb	r3, [r6, #3600]	@ zero_extendqisi2
	cmp	r3, #0
	subne	r3, fp, #44
	addne	r9, r3, r9, lsl #2
	ldreq	r3, [r7, #3916]
	ldrne	r3, [r9, #-64]
	str	r3, [r5, #564]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L801
	ldr	r3, [r7, #744]
	cmp	r3, #0
	beq	.L801
	ldr	r3, [r4, #2860]
	ldr	lr, [r5, #68]
	cmp	r5, r3
	str	r3, [fp, #-116]
	moveq	r3, #0
	streq	r3, [r5, #1360]
	streqb	r3, [r5, #1356]
	cmp	lr, #0
	beq	.L805
	ldr	r9, [fp, #-116]
	mov	r1, #0
	add	r0, r4, #2864
	mov	r3, r1
.L807:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldr	r2, [r2, #20]
	ldr	ip, [r2, #32]
	cmp	ip, #0
	addeq	r1, r2, #80
	cmp	r3, lr
	bne	.L807
	cmp	r1, #0
	str	r9, [fp, #-116]
	beq	.L805
.L808:
	ldr	r3, [r5, #40]
	ldr	r2, [r7, #28]
	add	r3, r4, r3
	add	r3, r3, #13696
	add	r3, r3, #8
	str	r2, [fp, #-140]
	ldr	r2, [r7, #32]
	ldrsb	r3, [r3, #4]
	cmp	r3, #0
	str	r2, [fp, #-144]
	moveq	r3, #1
	movne	r3, #0
	cmp	r1, #0
	strb	r3, [r5, #1357]
	beq	.L813
	ldr	r3, [r1, #168]
	ldr	ip, [fp, #-116]
	ldr	r0, [r1, #68]
	ldr	r2, [r1, #72]
	str	r3, [ip, #1468]
	ldr	r3, [r1, #172]
	mov	r8, r2
	str	r2, [fp, #-136]
	ldr	r9, [fp, #-140]
	str	r3, [ip, #1472]
	ldr	r3, [r1, #112]
	str	r0, [fp, #-124]
	str	r3, [ip, #1476]
	ldr	r2, [r1, #20]
	ldr	r3, [r1, #24]
	rsb	r3, r2, r3
	str	r3, [ip, #1480]
	ldr	r3, [r1, #140]
	str	r3, [ip, #1484]
	ldr	r3, [r1, #144]
	str	r3, [ip, #1488]
	ldr	r2, [r1, #20]
	ldr	r3, [r1, #44]
	rsb	r3, r2, r3
	str	r3, [ip, #1492]
	ldr	r2, [r1, #44]
	ldr	r3, [r1, #48]
	rsb	r3, r2, r3
	str	r3, [ip, #1496]
	ldr	r10, [r4, #2844]
	ldr	r3, [r10, #2984]
	ldr	r2, [r10, #3496]
	ldr	r1, [r10, #1960]
	sub	r3, r0, r3, asl #1
	ldr	r0, [r10, #2472]
	sub	lr, r3, r2, asl #1
	ldr	ip, [r10, #3240]
	sub	r1, r9, r1, asl #1
	str	lr, [fp, #-148]
	mov	r3, lr, asr #31
	sub	r1, r1, r0, asl #1
	str	r1, [fp, #-160]
	mov	r3, r3, asl #16
	ldr	lr, [r10, #3752]
	mov	r0, r1
	mov	r2, r3
	ldr	r3, [fp, #-148]
	orr	r2, r2, r3, lsr #16
	mov	r3, r3, asl #16
	str	r3, [fp, #-132]
	sub	r3, r8, ip, asl #1
	sub	ip, r3, lr, asl #1
	ldr	lr, [r10, #2216]
	ldr	r3, [fp, #-144]
	str	r2, [fp, #-128]
	mov	r2, r1
	sub	r3, r3, lr, asl #1
	ldr	lr, [r10, #2728]
	ldrd	r8, [fp, #-132]
	mov	r1, r1, asr #31
	movs	r1, r1, lsr #1
	mov	r0, r0, rrx
	str	ip, [fp, #-152]
	adds	r8, r8, r0
	sub	lr, r3, lr, asl #1
	ldr	r3, .L909
	adc	r9, r9, r1
	mov	r0, r8
	str	lr, [fp, #-132]
	mov	r1, r9
	mov	r8, ip
	ldr	r3, [r3, #244]
	blx	r3
	mov	r1, r8, asr #31
	ldr	lr, [fp, #-132]
	mov	ip, r8, asl #16
	mov	r1, r1, asl #16
	ldr	r3, .L909
	mov	r9, r1
	mov	r1, lr, asr #31
	ldr	r3, [r3, #244]
	mov	r2, lr
	str	r0, [fp, #-156]
	mov	r0, lr
	strd	r0, [fp, #-172]
	orr	r1, r9, r8, lsr #16
	mov	r9, r1
	ldrd	r0, [fp, #-172]
	movs	r1, r1, lsr #1
	mov	r0, r0, rrx
	adds	r8, ip, r0
	adc	r9, r9, r1
	mov	r0, r8
	mov	r1, r9
	blx	r3
	ldr	r9, [fp, #-140]
	mov	r8, r0
	ldr	r0, [fp, #-124]
	cmp	r9, r0
	bgt	.L814
	ldr	r3, [fp, #-156]
	cmp	r3, #65536
	movgt	r3, #0
	movle	r3, #1
	mov	r9, r3
.L815:
	ldr	r3, [fp, #-144]
	ldr	r2, [fp, #-136]
	cmp	r3, r2
	bgt	.L816
	cmp	r8, #65536
	movgt	r2, #0
	movle	r2, #1
.L817:
	ldr	r1, [fp, #-116]
	cmp	r9, #0
	ldr	r3, [fp, #-124]
	str	r3, [r1, #1364]
	ldr	r3, [fp, #-136]
	str	r3, [r1, #1368]
	mov	r3, #1
	strb	r3, [r1, #1356]
	movne	r3, r9
	orrne	r3, r2, r3
	movne	r2, r1
	strne	r3, [r2, #1360]
	ldr	r2, [fp, #-116]
	ldr	r3, [fp, #-156]
	str	r8, [r2, #1384]
	str	r3, [r2, #1380]
	str	r3, [r2, #1388]
	str	r8, [r2, #1392]
	ldrb	r3, [r10, #1890]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L819
	ldr	r2, [fp, #-152]
	add	r0, r10, #4096
	ldr	r3, [r10, #4008]
	ldr	lr, [fp, #-116]
	mov	r2, r2, asr #1
	ldr	ip, [fp, #-156]
	str	r3, [lr, #1428]
	mov	r9, r2
	ldr	r2, [r0, #168]
	mul	r1, r3, ip
	str	r2, [lr, #1432]
	ldr	r3, [r0, #424]
	mul	r2, r2, r8
	sub	r3, r3, #8
	str	r3, [lr, #1436]
	add	r1, r1, #8
	mul	r3, r3, ip
	add	r2, r2, #8
	mov	r1, r1, asr #4
	ldr	r0, [r0, #680]
	mov	r2, r2, asr #4
	rsb	r1, r1, #0
	add	r3, r3, #8
	rsb	r2, r2, #0
	sub	r0, r0, #8
	str	r0, [lr, #1440]
	mov	r3, r3, asr #4
	rsb	r3, r3, #0
.L820:
	mul	ip, r0, r8
	ldr	r8, [fp, #-116]
	ldr	lr, [fp, #-148]
	str	r1, [r8, #1444]
	add	ip, ip, #8
	ldr	r1, [fp, #-160]
	mov	r0, lr, asr #1
	mov	ip, ip, asr #4
	str	r3, [r8, #1452]
	rsb	ip, ip, #0
	str	r2, [r8, #1448]
	add	r0, r0, r1, lsl #8
	mov	r1, lr
	mov	lr, r8
	movw	r2, #4095
	str	ip, [lr, #1456]
	mov	r8, #61440
	str	r2, [fp, #-140]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-140]
	movt	r8, 65535
	ldr	r1, [fp, #-152]
	cmp	r0, r2
	movge	ip, r2
	ldr	r2, [fp, #-132]
	movlt	ip, r0
	cmp	ip, r8
	add	r0, r9, r2, lsl #8
	ldr	r9, [fp, #-116]
	movlt	ip, r8
	str	ip, [r9, #1460]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-140]
	mov	r1, #1
	cmp	r0, r2
	movge	r0, r2
	cmp	r0, r8
	movlt	r0, r8
	str	r0, [r9, #1464]
	ldr	r2, [r10, #1960]
	ldr	r0, [fp, #-136]
	mov	r2, r2, asl r1
	str	r2, [r9, #1396]
	ldr	r3, [r10, #2216]
	mov	r2, r2, asr r1
	str	r2, [r9, #1404]
	mov	r3, r3, asl r1
	str	r3, [r9, #1400]
	mov	r3, r3, asr r1
	str	r3, [r9, #1408]
	ldr	r2, [r10, #2984]
	mov	r2, r2, asl r1
	str	r2, [r9, #1412]
	ldr	r3, [r10, #3240]
	mov	r2, r2, asr r1
	str	r2, [r9, #1420]
	mov	r3, r3, asl r1
	str	r3, [r9, #1416]
	mov	r3, r3, asr r1
	str	r3, [r9, #1424]
	ldr	r3, [r4, #2840]
	ldr	r2, [r3, #128]
	ldr	r3, [fp, #-124]
	mov	r2, r1, asl r2
	sub	r1, r2, #1
	rsb	r2, r2, #0
	add	r3, r3, r1
	add	r1, r0, r1
	and	r3, r3, r2
	and	r2, r2, r1
	mov	r1, r9
	str	r3, [r9, #1372]
	str	r2, [r9, #1376]
.L813:
	add	ip, r4, #12288
	mov	r2, #0
	str	r2, [r5, #1500]
	ldr	r3, [ip, #1156]
	cmp	r3, r2
	beq	.L803
	add	r1, r4, #13696
	mov	r3, r2
	add	r1, r1, #11
.L822:
	ldrsb	r0, [r1, #1]!
	orr	r2, r2, r0, asl r3
	str	r2, [r5, #1500]
	ldr	r0, [ip, #1156]
	add	r3, r3, #1
	cmp	r3, r0
	bcc	.L822
	b	.L803
.L834:
	mov	r2, #0
	b	.L781
.L787:
	cmp	r3, #1
	movne	r9, #0
	bne	.L789
.L788:
	ldr	r3, [r6, #3640]
	add	r3, r5, r3, lsl #2
	ldr	r9, [r3, #372]
	b	.L789
.L801:
	mov	r3, #0
	str	r3, [r5, #1360]
	strb	r3, [r5, #1356]
	mov	r3, #1
	strb	r3, [r5, #1357]
.L803:
	ldr	r3, [r4, #2368]
	cmp	r3, #0
	ldreq	r1, [r4, #2828]
	ldreq	r2, [r4, #2848]
	ldreq	r0, [fp, #-120]
	streq	r1, [r2, r0, asl #2]
	streq	r3, [r4, #2828]
	ldrb	r3, [r7, #2665]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L859
	ldr	r3, [r4, #260]
	cmp	r3, #1
	beq	.L908
	add	r2, r4, r3, lsl #3
	sub	r3, r3, #1
	ldr	r0, [r5, #92]
	add	r2, r2, #10048
	add	r1, r3, #1264
	sub	r0, r0, #1
	str	r0, [r2, #56]
	add	r2, r4, r1, lsl #3
	ldr	r1, [r5, #92]
	str	r1, [r2, #4]
.L826:
	ldr	r1, [r7, #2464]
	add	r3, r4, r3, lsl #3
	ldr	r2, [r7, #2460]
	add	r3, r3, #10112
	mla	r2, r1, r2, r2
	add	r2, r2, r1
	str	r2, [r3, #8]
	ldr	r1, [r5, #92]
	sub	r1, r1, #1
	cmp	r1, #36864
	bcs	.L859
	mov	r0, r4
	bl	HEVC_CtbTsAddrToRsAddr
	str	r0, [r5, #568]
.L859:
	ldr	r0, [fp, #-112]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L902:
	ldr	r3, .L909
	add	r1, r4, #4800
	add	r0, r4, #11776
	add	r1, r1, #8
	add	r0, r0, #12
	mov	r2, #1376
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #1
	strb	r3, [r4, #14]
	b	.L767
.L907:
	ldr	r3, [r6, #3616]
	cmp	r3, #0
	bne	.L797
.L795:
	ldr	ip, [r6, #3752]
	add	r1, r4, #12032
	ldr	r3, .L909
	add	r1, r1, #48
	ldr	r10, .L909
	mov	r2, #64
	str	ip, [r5, #580]
	add	r0, r5, #588
	ldr	ip, [r6, #3884]
	ldr	r3, [r3, #52]
	str	ip, [r5, #584]
	blx	r3
	add	r1, r4, #11904
	add	r1, r1, #44
	ldr	r3, [r10, #52]
	mov	r2, #64
	add	r0, r5, #716
	blx	r3
	add	r1, r4, #12096
	add	r1, r1, #48
	ldr	r3, [r10, #52]
	mov	r2, #128
	add	r0, r5, #844
	blx	r3
	add	r1, r4, #12224
	add	r0, r5, #1088
	ldr	r3, [r10, #52]
	add	r1, r1, #48
	add	r0, r0, #12
	mov	r2, #128
	blx	r3
	ldr	r3, [r6, #3616]
	cmp	r3, #0
	bne	.L797
	add	r1, r4, #12352
	ldr	r3, [r10, #52]
	add	r1, r1, #48
	mov	r2, #64
	add	r0, r5, #652
	blx	r3
	add	r1, r4, #11968
	ldr	r3, [r10, #52]
	add	r1, r1, #44
	mov	r2, #64
	add	r0, r5, #780
	blx	r3
	add	r1, r4, #12416
	ldr	r3, [r10, #52]
	add	r1, r1, #48
	mov	r2, #128
	add	r0, r5, #972
	blx	r3
	add	r1, r4, #12544
	add	r0, r5, #1216
	ldr	r3, [r10, #52]
	add	r1, r1, #48
	mov	r2, #128
	add	r0, r0, #12
	blx	r3
	b	.L797
.L814:
	ldr	r3, [fp, #-124]
	ldr	r0, [fp, #-140]
	mov	r2, r3, asl #1
	add	r3, r2, r3
	add	r1, r3, r3, lsr #31
	cmp	r0, r1, asr #1
	movle	r3, #1
	movle	r9, r3
	ble	.L815
	cmp	r0, r2
	movle	r3, #2
	movle	r9, r3
	ble	.L815
	cmp	r0, r3
	mov	r2, r0
	movle	r3, #3
	movle	r9, r3
	ble	.L815
	ldr	r3, [fp, #-124]
	mov	r0, #1
	ldr	r1, .L909+4
	bl	dprint_vfmw
	mov	r3, #3
	mov	r9, r3
	b	.L815
.L908:
	ldr	r2, [r5, #92]
	mov	r3, #0
	str	r2, [r6, #1924]
	b	.L826
.L819:
	ldr	r1, [fp, #-152]
	ldr	ip, [fp, #-116]
	ldr	r0, [fp, #-132]
	mov	r2, r1, asr #1
	str	r3, [fp, #-140]
	str	r3, [ip, #1428]
	str	r3, [ip, #1432]
	add	r0, r2, r0, lsl #2
	str	r3, [ip, #1436]
	mov	r9, r2
	bl	__aeabi_idiv
	ldr	r3, [fp, #-140]
	ldr	ip, [fp, #-116]
	mov	r2, r3
	mov	r1, r3
	sub	r0, r0, #4
	str	r0, [ip, #1440]
	b	.L820
.L816:
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	mov	r2, r3, asl #1
	add	r3, r2, r3
	add	r1, r3, r3, lsr #31
	cmp	r0, r1, asr #1
	movle	r2, #1
	ble	.L817
	cmp	r0, r2
	movle	r2, #2
	ble	.L817
	cmp	r0, r3
	mov	r2, r0
	movle	r2, #3
	ble	.L817
	ldr	r3, [fp, #-136]
	mov	r0, #1
	ldr	r1, .L909+8
	bl	dprint_vfmw
	mov	r2, #3
	b	.L817
.L770:
	ldr	r3, [r6, #3668]
	cmp	r3, #0
	bne	.L827
	b	.L899
.L805:
	ldr	lr, [r5, #72]
	cmp	lr, #0
	beq	.L836
	add	r0, r4, #2928
	ldr	r9, [fp, #-116]
	mov	r1, #0
	add	r0, r0, #4
	mov	r3, r1
.L810:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldr	r2, [r2, #20]
	ldr	ip, [r2, #32]
	cmp	ip, #0
	addeq	r1, r2, #80
	cmp	r3, lr
	bne	.L810
	str	r9, [fp, #-116]
	b	.L808
.L836:
	mov	r1, lr
	b	.L808
.L828:
	mvn	r3, #0
	str	r3, [fp, #-112]
	b	.L859
.L901:
	mov	r2, r0
	ldr	r1, .L909+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r3, #0
	str	r3, [fp, #-112]
	b	.L859
.L910:
	.align	2
.L909:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC86
	.word	.LC87
	.word	.LC85
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
	add	r2, r0, #4096
	mov	r1, r0
	add	ip, r0, #8192
	mov	r0, #0
	ldr	r3, [r2, #36]
	ldr	lr, [r2, #40]
	clz	r3, r3
	str	lr, [r2, #3772]
	mov	r3, r3, lsr #5
	str	r3, [r2, #3780]
	ldr	r3, [r1, #204]
	str	r3, [ip, #832]
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
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r3, #1
	beq	.L943
.L915:
	add	r5, r4, #4096
	ldr	r2, [r4, #164]
	ldr	r3, [r5, #748]
	cmp	r3, #0
	blt	.L932
	cmp	r3, r2
	bge	.L932
	ldr	r2, [r4, #2820]
	movw	r1, #5036
	mla	r3, r1, r3, r2
	ldr	r2, [r4, #160]
	ldr	r3, [r3, #32]
	cmp	r3, #0
	blt	.L919
	cmp	r3, r2
	bge	.L919
	ldr	r2, [r4, #2816]
	movw	r0, #12668
	ldr	ip, [r5, #1644]
	mov	r1, #1
	ldr	r10, [r5, #1648]
	mla	r2, r0, r3, r2
	ldr	r6, [r5, #1652]
	add	lr, r10, ip
	cmp	lr, r6
	mov	r3, lr
	ldr	r8, [r2, #116]
	mov	r8, r1, asl r8
	bcs	.L933
	cmp	lr, #15
	bgt	.L922
	add	r2, lr, #1456
	ldr	r7, [r5, #20]
	add	r2, r2, #3
	sub	r8, r8, #1
	and	r9, r8, r7
	str	ip, [fp, #-48]
	add	r2, r4, r2, lsl #2
	b	.L924
.L945:
	cmp	r3, r6
	bcs	.L944
	cmp	r3, #16
	beq	.L922
.L924:
	ldr	r1, [r2, #4]!
	mov	r0, r7
	add	r3, r3, #1
	ldr	ip, [r2, #-944]
	cmp	ip, #0
	andeq	r1, r1, r8
	moveq	r0, r9
	cmp	r0, r1
	bne	.L945
	ldr	ip, [fp, #-48]
	mov	r6, #1
.L921:
	cmp	lr, #0
	beq	.L936
	ldr	r0, [r5, #724]
	ldr	r3, [r5, #1676]
	ldr	r2, [r5, #20]
	add	r3, r0, r3
	cmp	r2, r3
	beq	.L927
	add	r4, r4, #5760
	mov	r1, #0
	add	r4, r4, #12
	b	.L928
.L929:
	ldr	r3, [r4, #4]!
	add	r3, r0, r3
	cmp	r3, r2
	beq	.L927
.L928:
	add	r1, r1, #1
	cmp	r1, lr
	beq	.L936
	cmp	r1, #17
	bne	.L929
	mov	r3, r1
	str	r1, [sp]
	str	r10, [sp, #8]
	movw	r2, #9007
	str	ip, [sp, #4]
	mov	r0, #0
	ldr	r1, .L946
	bl	dprint_vfmw
	mov	r0, r6
	b	.L941
.L932:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8946
	ldr	r1, .L946+4
	bl	dprint_vfmw
	mov	r0, #0
.L941:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L943:
	ldr	r3, [r0, #2856]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L915
.L927:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L919:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8958
	ldr	r1, .L946+8
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L922:
	str	r6, [sp, #4]
	mov	r1, #16
	mov	r0, #0
	str	r1, [sp]
	movw	r2, #8978
	ldr	r1, .L946+12
	mov	r6, r0
	bl	dprint_vfmw
	ldr	ip, [r5, #1644]
	ldr	r10, [r5, #1648]
	add	lr, r10, ip
	b	.L921
.L944:
	ldr	ip, [fp, #-48]
	mov	r6, #0
	b	.L921
.L936:
	mov	r0, r6
	b	.L941
.L933:
	mov	r6, #0
	b	.L921
.L947:
	.align	2
.L946:
	.word	.LC91
	.word	.LC88
	.word	.LC89
	.word	.LC90
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
	ldr	r2, [r0, #2836]
	ldr	r3, [r1, #4]
	ldr	r2, [r2, #4]
	cmp	r2, r3
	beq	.L951
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L951:
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r2, #0
	strb	r2, [r1, #2]
	ldr	r3, [r0, #156]
	movw	r4, #24912
	ldr	ip, .L953
	mov	r5, r0
	ldr	r0, [r0, #2812]
	mov	r2, r4
	mul	r3, r4, r3
	ldr	r6, [ip, #52]
	sub	r3, r3, #24832
	sub	r3, r3, #80
	add	r0, r0, r3
	blx	r6
	ldr	r2, [r5, #156]
	ldr	r3, [r5, #2812]
	mul	r4, r4, r2
	sub	r4, r4, #24832
	sub	r4, r4, #80
	add	r4, r3, r4
	str	r4, [r5, #2836]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L954:
	.align	2
.L953:
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
	ldr	r2, [r0, #2840]
	ldr	r3, [r1, #56]
	ldr	r2, [r2, #56]
	cmp	r2, r3
	beq	.L958
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L958:
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
	movw	r5, #12668
	ldr	ip, .L960
	mov	r4, r0
	ldr	r0, [r0, #2816]
	mov	r2, r5
	mul	r3, r5, r3
	ldr	r6, [ip, #52]
	sub	r3, r3, #12608
	sub	r3, r3, #60
	add	r0, r0, r3
	blx	r6
	ldr	r3, [r4, #160]
	ldr	r1, [r4, #2816]
	mul	r3, r5, r3
	sub	r3, r3, #12608
	sub	r3, r3, #60
	add	r3, r1, r3
	str	r3, [r4, #2840]
	ldr	r2, [r3, #56]
	str	r2, [r4, #288]
	ldr	r2, [r3, #64]
	str	r2, [r4, #292]
	ldr	r2, [r3, #68]
	str	r2, [r4, #296]
	ldr	r2, [r3, #128]
	str	r2, [r4, #300]
	ldr	r2, [r3, #88]
	str	r2, [r4, #304]
	ldr	r3, [r3, #96]
	str	r3, [r4, #308]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L961:
	.align	2
.L960:
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
	ldr	r2, [r0, #2844]
	ldr	r3, [r1, #28]
	ldr	r2, [r2, #28]
	cmp	r2, r3
	beq	.L965
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L965:
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
	beq	.L967
	ldrb	r3, [r2, #15]	@ zero_extendqisi2
	cmp	r3, r4
	bne	.L985
	ldr	lr, [r2, #68]
	ldr	r3, [r1, #188]
	cmp	lr, #1
	add	r0, r2, lr, lsl #1
	strh	r3, [r0, #170]	@ movhi
	ble	.L979
	add	lr, lr, #42
	add	r2, r2, #86
	add	ip, r5, #170
	add	lr, r5, lr, lsl #1
.L978:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #170]
	rsb	r3, r1, r3
	strh	r3, [r0, #170]	@ movhi
	bne	.L978
.L979:
	ldr	lr, [r5, #72]
	ldr	r3, [r7, #192]
	cmp	lr, #1
	add	r0, r5, lr, lsl #1
	strh	r3, [r0, #210]	@ movhi
	ble	.L974
	add	lr, lr, #62
	add	r2, r5, #126
	add	ip, r5, #210
	add	lr, r5, lr, lsl #1
.L980:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #210]
	rsb	r3, r1, r3
	strh	r3, [r0, #210]	@ movhi
	bne	.L980
	b	.L974
.L967:
	ldr	r3, [r1, #188]
	strh	r3, [r2, #172]	@ movhi
	ldr	r3, [r1, #192]
	strh	r3, [r2, #212]	@ movhi
.L974:
	ldr	r3, [r6, #164]
	movw	r4, #5036
	ldr	ip, .L986
	mov	r1, r5
	ldr	r0, [r6, #2820]
	mov	r2, r4
	mul	r3, r4, r3
	ldr	r5, [ip, #52]
	sub	r3, r3, #4992
	sub	r3, r3, #44
	add	r0, r0, r3
	blx	r5
	ldr	r2, [r6, #164]
	ldr	r3, [r6, #2820]
	mul	r4, r4, r2
	sub	r4, r4, #4992
	sub	r4, r4, #44
	add	r4, r3, r4
	str	r4, [r6, #2844]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L985:
	ldr	r9, [r2, #68]
	cmp	r9, r4
	addgt	r3, r2, #170
	ble	.L973
.L972:
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
	bne	.L972
.L973:
	ldr	r9, [r5, #72]
	cmp	r9, #0
	addgt	r3, r5, #210
	movgt	r4, #0
	ble	.L974
.L975:
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
	bne	.L975
	b	.L974
.L987:
	.align	2
.L986:
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #4096
	mov	r5, r0
	mvn	r3, #0
	mov	r0, #1
	ldr	r2, [r4, #740]
	mov	r1, #0
	ldr	lr, [r4, #724]
	str	r3, [r4, #40]
	strb	r0, [r4, #9]
	str	r2, [r4, #12]
	str	lr, [r4, #20]
	ldr	ip, [r5, #2840]
	ldr	r3, .L1002
	ldr	r2, [ip, #64]
	str	r2, [r4, #28]
	ldr	r2, [ip, #68]
	str	r1, [r4, #36]
	str	r2, [r4, #32]
	ldr	r2, [r5, #276]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, r0
	beq	.L1001
.L989:
	ldr	r3, [r5, #2368]
	cmp	r3, #0
	bne	.L992
	ldr	ip, [r5, #2856]
	movw	r7, #4752
	add	lr, r5, #4736
	movw	r6, #4768
	mvn	r0, #0
	mvn	r1, #0
	ldrd	r2, [ip, #64]
	strd	r2, [r5, r7]
	ldrd	r2, [ip, #80]
	strd	r2, [lr, #24]
	ldrd	r2, [ip, #96]
	strd	r2, [r5, r6]
	ldr	r3, [ip, #112]
	str	r3, [r4, #72]
	ldr	r3, [ip, #116]
	str	r3, [r4, #76]
	ldr	r3, [ip, #120]
	str	r3, [r4, #80]
	ldr	r3, [ip, #136]
	str	r3, [r4, #84]
	ldrb	r3, [ip, #56]	@ zero_extendqisi2
	strb	r3, [r4, #704]
	strd	r0, [ip, #64]
	ldr	ip, [r5, #2840]
.L992:
	ldr	r1, [ip, #64]
	mov	r6, #0
	ldr	r2, [r4, #744]
	add	r0, r5, #4160
	ldrb	r3, [r4, #136]	@ zero_extendqisi2
	add	r0, r0, #8
	str	r1, [r4, #140]
	ldr	r1, [ip, #68]
	str	r2, [r4, #256]
	str	r2, [r4, #16]
	str	r1, [r4, #144]
	str	r6, [r4, #124]
	ldr	r2, [ip, #60]
	ldr	r1, [ip, #2084]
	subs	r2, r2, #1
	bfi	r3, r1, #5, #3
	movne	r2, #1
	bfi	r3, r2, #2, #3
	strb	r3, [r4, #136]
	ldr	r1, [ip, #2068]
	and	r1, r1, #7
	bl	SetAspectRatio
	ldr	r3, [r5, #2368]
	cmp	r3, #1
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #724]
	str	r2, [r3, #8]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #136]
	str	r2, [r3, #144]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #124]
	str	r2, [r3, #132]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #176]
	str	r2, [r3, #184]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #172]
	str	r2, [r3, #180]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #140]
	str	r2, [r3, #148]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #144]
	str	r2, [r3, #152]
	ldr	r3, [r4, #68]
	ldr	r0, [r5, #276]
	ldr	r1, [r3, #28]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L994
	ldr	r3, [r4, #124]
	mov	r1, r6
	ldr	r2, [r0, #4]
	subs	r3, r3, r6
	ldr	r0, [r5, #276]
	movne	r3, #1
	bl	FSP_SetStoreType
.L994:
	ldr	r3, [r5, #2840]
	mov	r6, #0
	ldr	ip, [r4, #68]
	ldr	r2, [r3, #72]
	str	r2, [r4, #292]
	ldr	r5, [r3, #76]
	str	r5, [r4, #296]
	ldr	r1, [r3, #80]
	str	r1, [r4, #300]
	ldr	lr, [r3, #84]
	str	lr, [r4, #304]
	ldr	r0, [r3, #64]
	rsb	r2, r2, r0
	rsb	r2, r5, r2
	str	r2, [r4, #148]
	ldr	r0, [r3, #68]
	rsb	r1, r1, r0
	rsb	r1, lr, r1
	str	r1, [r4, #152]
	ldr	r1, [r3, #60]
	str	r1, [r4, #236]
	ldr	r1, [r3, #88]
	str	r1, [r4, #240]
	ldr	r3, [r3, #96]
	str	r3, [r4, #244]
	ldr	r3, [ip, #164]
	str	r3, [r4, #156]
	ldr	r3, [ip, #168]
	str	r3, [r4, #160]
	str	r2, [ip, #156]
	ldr	r2, [r4, #152]
	ldr	r3, [r4, #68]
	str	r2, [r3, #160]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #156]
	str	r2, [r3, #164]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #160]
	str	r2, [r3, #168]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #240]
	str	r2, [r3, #248]
	ldr	r3, [r4, #68]
	ldr	r2, [r4, #244]
	str	r2, [r3, #252]
	str	r6, [r4, #24]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1001:
	ldr	r2, [r3, #160]
	cmp	r2, r0
	bne	.L989
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L989
	add	r3, r5, #8192
	ldrb	r3, [r3, #3536]	@ zero_extendqisi2
	cmp	r3, r0
	bne	.L989
	add	r3, r5, #11776
	movw	r2, #11760
	ldrd	r0, [r5, r2]
	ldrd	r2, [r3]
	cmp	r1, r3
	cmpeq	r0, r2
	bls	.L990
	subs	r6, r0, r2
	sbc	r7, r1, r3
	cmp	r7, #0
	cmpeq	r6, #16
	bls	.L990
.L991:
	ldr	r0, [r5, #284]
	movw	r1, #11760
	rsb	lr, r0, lr
	adds	r2, r2, lr
	adc	r3, r3, lr, asr #31
	strd	r2, [r5, r1]
	b	.L989
.L990:
	cmp	r1, r3
	cmpeq	r0, r2
	bcs	.L989
	subs	r0, r2, r0
	sbc	r1, r3, r1
	cmp	r1, #0
	cmpeq	r0, #16
	bls	.L989
	b	.L991
.L1003:
	.align	2
.L1002:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	HEVC_InitPicInfo, .-HEVC_InitPicInfo
	.align	2
	.global	HEVC_RepairList
	.type	HEVC_RepairList, %function
HEVC_RepairList:
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
	add	r3, r0, #4096
	str	r3, [fp, #-56]
	mov	r2, r0
	ldr	r3, [r3, #732]
	cmp	r3, #1
	beq	.L1021
	cmp	r3, #2
	beq	.L1022
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [fp, #-48]
	beq	.L1006
	ldr	r2, .L1031
	mov	r0, #1
	ldr	r1, .L1031+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1021:
	str	r3, [fp, #-48]
.L1006:
	add	r10, r2, #4864
	add	r8, r2, #2864
	add	r10, r10, #8
	add	r8, r8, #4
	mov	r9, #0
	mov	r7, r2
.L1019:
	ldr	r2, [r10, #4]!
	cmp	r2, #0
	beq	.L1009
	ldr	r1, [r8]
	cmp	r1, #0
	bne	.L1023
	mov	r0, r8
	mov	r3, r1
	b	.L1011
.L1013:
	ldr	r5, [r0, #4]!
	cmp	r5, #0
	bne	.L1029
.L1011:
	add	r3, r3, #1
	cmp	r3, r2
	bne	.L1013
	mov	r3, #255
	str	r3, [fp, #-52]
.L1012:
	ldr	r3, [r7, #2856]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L1014
	ldr	r3, [fp, #-56]
	ldr	r5, [r3, #68]
	add	r5, r5, #56
.L1010:
	mov	r3, r1
	mov	r6, r8
	mov	r4, #0
	b	.L1020
.L1016:
	ldr	r3, [r6, #4]!
.L1020:
	cmp	r3, #0
	beq	.L1030
.L1015:
	add	r4, r4, #1
	cmp	r2, r4
	bhi	.L1016
.L1017:
	ldr	r3, [fp, #-48]
	add	r9, r9, #1
	add	r8, r8, #68
	cmp	r9, r3
	bcc	.L1019
.L1022:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1009:
	ldr	r3, [r7, #2856]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L1017
	mov	r3, #1
	str	r3, [r10]
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #68]
	add	r3, r3, #56
	str	r3, [r8]
	b	.L1017
.L1030:
	ldrsb	r2, [fp, #-52]
	mov	r3, r9
	str	r4, [sp]
	mov	r0, #1
	ldr	r1, .L1031+8
	str	r2, [sp, #4]
	ldr	r2, .L1031
	bl	dprint_vfmw
	str	r5, [r6]
	ldr	r2, [r10]
	b	.L1015
.L1029:
	uxtb	r3, r3
	str	r3, [fp, #-52]
	cmp	r3, #255
	bne	.L1010
	b	.L1012
.L1023:
	mov	r3, #0
	mov	r5, r1
	str	r3, [fp, #-52]
	b	.L1010
.L1014:
	mov	r3, r9
	ldr	r2, .L1031
	ldr	r1, .L1031+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1032:
	.align	2
.L1031:
	.word	.LANCHOR0+388
	.word	.LC92
	.word	.LC94
	.word	.LC93
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
	subs	r4, r0, #0
	beq	.L1096
	ldr	r3, .L1146
	mov	r2, #136
	mov	r1, #0
	sub	r0, fp, #180
	ldr	r3, [r3, #48]
	blx	r3
	ldr	lr, [r4, #3052]
	cmp	lr, #0
	beq	.L1097
	add	r0, r4, #3264
	mov	r1, #0
	add	r0, r0, #8
	mov	r3, r1
	b	.L1037
.L1036:
	cmp	r3, lr
	beq	.L1035
.L1037:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #1]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L1036
	ldr	ip, [r2, #60]
	cmp	ip, #0
	bne	.L1036
	ldr	ip, [r2, #64]
	cmp	ip, #1
	subeq	ip, fp, #44
	addeq	r2, r2, #56
	addeq	ip, ip, r1, lsl #2
	addeq	r1, r1, #1
	streq	r2, [ip, #-136]
	cmp	r3, lr
	bne	.L1037
.L1035:
	ldrb	lr, [r4, #1]	@ zero_extendqisi2
	cmp	lr, #0
	bne	.L1139
	ldr	r3, [r4, #3056]
	mov	r5, r1
	cmp	r3, #0
	moveq	r3, lr
	moveq	ip, lr
	beq	.L1095
	mov	ip, lr
.L1094:
	add	r6, r4, #3328
	mov	r2, #0
	add	r6, r6, #12
	b	.L1044
.L1043:
	cmp	r2, r3
	bcs	.L1140
.L1044:
	ldr	r0, [r6, #4]!
	add	r2, r2, #1
	ldrb	r7, [r0, #1]	@ zero_extendqisi2
	cmp	r7, #1
	bne	.L1043
	ldr	r7, [r0, #60]
	cmp	r7, #0
	bne	.L1043
	ldr	r7, [r0, #64]
	cmp	r7, #1
	subeq	r7, fp, #44
	addeq	r0, r0, #56
	addeq	r7, r7, r5, lsl #2
	addeq	r5, r5, #1
	streq	r0, [r7, #-136]
	cmp	r2, r3
	bcc	.L1044
.L1140:
	cmp	lr, #0
	rsbne	r2, r1, r5
	rsbne	r3, ip, r2
	bne	.L1042
	rsb	r3, r1, r5
.L1095:
	ldr	r7, [r4, #3048]
	cmp	r7, #0
	beq	.L1048
.L1046:
	add	r6, r4, #3408
	mov	r2, #0
	b	.L1050
.L1049:
	cmp	r7, r2
	bls	.L1141
.L1050:
	ldr	r0, [r6, #4]!
	add	r2, r2, #1
	ldrb	r8, [r0, #1]	@ zero_extendqisi2
	cmp	r8, #1
	bne	.L1049
	ldr	r8, [r0, #60]
	cmp	r8, #1
	bne	.L1049
	ldr	r8, [r0, #64]
	sub	r9, fp, #44
	add	r9, r9, r5, lsl #2
	add	r0, r0, #56
	cmp	r8, #0
	addeq	r5, r5, #1
	streq	r0, [r9, #-136]
	cmp	r7, r2
	bhi	.L1050
.L1141:
	cmp	lr, #0
	rsbeq	r7, r1, r5
	rsbeq	r7, r3, r7
	beq	.L1048
	rsb	r2, r1, r5
.L1047:
	ldr	r0, [r4, #3068]
	rsb	r7, r3, r2
	rsb	r7, ip, r7
	cmp	r0, #0
	beq	.L1055
	add	r8, r4, #3136
	mov	r2, #0
.L1054:
	ldr	r6, [r8, #4]!
	add	r2, r2, #1
	ldrb	r9, [r6, #1]	@ zero_extendqisi2
	cmp	r9, #1
	subeq	r9, fp, #44
	addeq	r6, r6, #56
	addeq	r9, r9, r5, lsl #2
	addeq	r5, r5, #1
	streq	r6, [r9, #-136]
	cmp	r2, r0
	bne	.L1054
	rsb	r0, r1, r5
	rsb	r0, r3, r0
	rsb	r0, ip, r0
	rsb	r0, r7, r0
.L1055:
	cmp	r5, #0
	beq	.L1142
.L1056:
	add	r2, r4, #4096
	str	r2, [fp, #-184]
	ldr	r2, [r2, #732]
	cmp	r2, #0
	str	r2, [fp, #-188]
	bne	.L1143
	cmp	lr, #0
	beq	.L1144
	cmp	r3, #0
	beq	.L1102
	add	r8, ip, r1
	sub	r6, fp, #180
	ldr	r2, [fp, #-188]
	sub	r9, fp, #116
	add	r8, r6, r8, lsl #2
.L1065:
	add	r2, r2, #1
	ldr	r6, [r8], #4
	cmp	r2, r3
	str	r6, [r9, #4]!
	bne	.L1065
.L1102:
	cmp	r0, #0
	mov	r2, r3
	beq	.L1063
	add	r8, r7, r3
	add	r9, r3, #16
	add	r8, r8, r1
	sub	r6, fp, #180
	add	r8, r8, ip
	add	r9, r6, r9, lsl #2
	mov	r2, #0
	add	r8, r6, r8, lsl #2
.L1066:
	add	r2, r2, #1
	ldr	r6, [r8], #4
	cmp	r2, r0
	str	r6, [r9, #4]!
	bne	.L1066
	add	r2, r3, r2
	b	.L1063
.L1139:
	ldr	ip, [r4, #3064]
	cmp	ip, #0
	beq	.L1098
	add	r0, r4, #3056
	mov	r5, r1
	add	r0, r0, #12
	mov	r3, #0
	b	.L1041
.L1040:
	cmp	r3, ip
	beq	.L1145
.L1041:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	r6, [r2, #1]	@ zero_extendqisi2
	cmp	r6, #1
	bne	.L1040
	ldr	r6, [r2, #72]
	cmp	r6, #1
	subeq	r6, fp, #44
	addeq	r2, r2, #56
	addeq	r6, r6, r5, lsl #2
	addeq	r5, r5, #1
	streq	r2, [r6, #-136]
	cmp	r3, ip
	bne	.L1041
.L1145:
	rsb	ip, r1, r5
.L1039:
	ldr	r3, [r4, #3056]
	cmp	r3, #0
	bne	.L1094
	mov	r2, ip
.L1042:
	ldr	r7, [r4, #3048]
	cmp	r7, #0
	bne	.L1046
	b	.L1047
.L1143:
	ldr	r3, [fp, #-184]
	ldr	r7, [r3, #788]
	ldr	r8, [r3, #792]
	cmp	r7, #0
	str	r7, [r3, #780]
	str	r8, [r3, #784]
	beq	.L1088
.L1059:
	ldr	r3, [fp, #-184]
	add	r10, r4, #2864
	mov	r9, #0
	ldrb	r6, [r3, #1808]	@ zero_extendqisi2
.L1082:
	cmp	r6, #0
	mov	r1, r5
	mov	r0, r9
	ldrne	r1, [r10, #3044]
	bne	.L1081
	bl	__aeabi_uidivmod
.L1081:
	sub	r3, fp, #44
	add	r9, r9, #1
	add	r1, r3, r1, lsl #2
	cmp	r9, r7
	ldr	r3, [r1, #-136]
	str	r3, [r10, #4]!
	bne	.L1082
	ldr	r3, [fp, #-188]
	cmp	r3, #0
	bne	.L1079
.L1078:
	cmp	r8, #0
	beq	.L1084
	ldr	r3, [fp, #-184]
	add	r9, r4, #2928
	add	r9, r9, #4
	mov	r6, #0
	ldrb	r10, [r3, #1809]	@ zero_extendqisi2
.L1087:
	cmp	r10, #0
	mov	r1, r5
	mov	r0, r6
	ldrne	r1, [r9, #3104]
	bne	.L1086
	bl	__aeabi_uidivmod
.L1086:
	sub	r3, fp, #44
	add	r6, r6, #1
	add	r1, r3, r1, lsl #2
	cmp	r6, r8
	ldr	r3, [r1, #-68]
	str	r3, [r9, #4]!
	bne	.L1087
.L1079:
	cmp	r7, #16
	bhi	.L1092
.L1088:
	add	r7, r7, #716
	add	r2, r4, #2928
	add	r2, r2, #4
	add	r7, r4, r7, lsl #2
.L1091:
	ldr	r3, [r4, #2868]
	str	r3, [r7, #4]!
	cmp	r7, r2
	bne	.L1091
.L1092:
	cmp	r8, #16
	bhi	.L1090
	add	r8, r8, #732
	add	r2, r4, #2992
	add	r8, r8, #1
	add	r2, r2, #8
	add	r8, r4, r8, lsl #2
.L1093:
	ldr	r3, [r4, #2936]
	str	r3, [r8, #4]!
	cmp	r8, r2
	bne	.L1093
.L1090:
	mov	r0, #0
.L1132:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1048:
	cmp	r5, #0
	mov	r0, #0
	bne	.L1056
.L1142:
	ldr	r3, .L1146
	add	r6, r4, #4096
	add	r0, r4, #2864
	mov	r2, #136
	add	r0, r0, #4
	str	r5, [r6, #780]
	ldr	r3, [r3, #48]
	mov	r1, r5
	str	r5, [r6, #784]
	blx	r3
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L1090
	ldr	r3, [r6, #68]
	mov	r2, #1
	mov	r0, r5
	str	r2, [r6, #780]
	add	r3, r3, #56
	str	r3, [r4, #2868]
	b	.L1132
.L1144:
	cmp	r3, #0
	beq	.L1134
	sub	r2, fp, #180
	sub	r0, fp, #116
	add	r8, r2, r1, lsl #2
	mov	r2, lr
.L1069:
	add	r2, r2, #1
	ldr	r6, [r8], #4
	cmp	r2, r3
	str	r6, [r0, #4]!
	bne	.L1069
.L1134:
	mov	r2, r3
.L1063:
	cmp	r1, #0
	beq	.L1068
	add	r8, r2, #16
	sub	r9, fp, #180
	mov	r0, #0
	add	r8, r9, r8, lsl #2
.L1070:
	add	r0, r0, #1
	ldr	r6, [r9], #4
	cmp	r0, r1
	str	r6, [r8, #4]!
	bne	.L1070
	add	r2, r2, r1
.L1068:
	cmp	lr, #0
	bne	.L1071
	cmp	r7, #0
	beq	.L1073
	add	r1, r3, r1
	add	r2, r2, #16
	sub	r3, fp, #180
	add	r1, r3, r1, lsl #2
	add	r3, r3, r2, lsl #2
.L1077:
	add	lr, lr, #1
	ldr	r2, [r1], #4
	cmp	lr, r7
	str	r2, [r3, #4]!
	bne	.L1077
.L1073:
	ldr	r3, [fp, #-184]
	ldr	r7, [r3, #788]
	ldr	r8, [r3, #792]
	cmp	r7, #0
	str	r7, [r3, #780]
	str	r8, [r3, #784]
	bne	.L1059
	b	.L1078
.L1071:
	cmp	r7, #0
	beq	.L1074
	add	r0, r3, ip
	add	lr, r2, #16
	add	r0, r0, r1
	sub	r6, fp, #180
	add	lr, r6, lr, lsl #2
	mov	r3, #0
	add	r0, r6, r0, lsl #2
.L1075:
	add	r3, r3, #1
	ldr	r6, [r0], #4
	cmp	r3, r7
	str	r6, [lr, #4]!
	bne	.L1075
	add	r2, r2, r3
.L1074:
	cmp	ip, #0
	beq	.L1073
	add	r2, r2, #16
	sub	r0, fp, #180
	sub	r3, fp, #180
	add	r2, r0, r2, lsl #2
	add	r1, r3, r1, lsl #2
	mov	r3, #0
.L1076:
	add	r3, r3, #1
	ldr	r0, [r1], #4
	cmp	r3, ip
	str	r0, [r2, #4]!
	bne	.L1076
	b	.L1073
.L1097:
	mov	r1, lr
	b	.L1035
.L1098:
	mov	r5, r1
	b	.L1039
.L1084:
	ldr	r3, .L1146
	add	r1, r4, #2864
	add	r0, r4, #2928
	add	r1, r1, #4
	add	r0, r0, #8
	mov	r2, #68
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [fp, #-184]
	ldr	r7, [r3, #780]
	str	r7, [r3, #784]
	mov	r8, r7
	b	.L1079
.L1096:
	mvn	r0, #0
	b	.L1132
.L1147:
	.align	2
.L1146:
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
	ldr	r2, [r3, #732]
	cmp	r2, #2
	beq	.L1153
	bl	HEVC_InitListX
	cmp	r0, #0
	bne	.L1154
	mov	r0, r4
	bl	HEVC_RepairList
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L1155
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1153:
	mov	r0, #0
	str	r0, [r3, #780]
	str	r0, [r3, #784]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1154:
	ldr	r1, .L1155+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1156:
	.align	2
.L1155:
	.word	.LC96
	.word	.LC95
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
	ldr	r2, [r0, #2840]
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
	bhi	.L1164
	ldr	r3, .L1166
	mov	r2, #20
	sub	r0, fp, #48
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #2856]
	str	r6, [fp, #-44]
	str	r5, [fp, #-40]
	ldr	r3, [r3, #28]
	str	r6, [fp, #-36]
	cmp	r3, #24
	str	r5, [fp, #-32]
	beq	.L1160
	ldrb	r3, [r4, #3036]	@ zero_extendqisi2
	strb	r3, [fp, #-47]
.L1162:
	sub	r1, fp, #48
	ldr	r0, [r4, #276]
	strb	r3, [fp, #-45]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L1165
	ldr	r1, [r4, #2856]
	sub	r3, fp, #52
	ldr	r0, [r4, #276]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
.L1163:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1160:
	mov	r3, #1
	strb	r3, [fp, #-47]
	b	.L1162
.L1164:
	str	r5, [sp]
	mov	r3, r6
	ldr	r2, .L1166+4
	mov	r0, #0
	ldr	r1, .L1166+8
	bl	dprint_vfmw
	mvn	r0, #19
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1165:
	ldr	r2, .L1166+4
	mov	r0, #1
	ldr	r1, .L1166+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1163
.L1167:
	.align	2
.L1166:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+404
	.word	.LC97
	.word	.LC98
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
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, r1, lsl #2
	ldr	ip, [r3, #3208]
	ldr	r2, [ip, #32]
	cmp	r2, #1
	bhi	.L1171
	ldr	r3, [ip, #24]
	cmp	r3, #15
	bhi	.L1168
	mov	r1, #70
	mov	r4, #280
	mla	r1, r1, r2, r3
	mov	lr, #0
	mla	r2, r4, r2, r0
	mov	r4, #16
	add	r3, r2, r3
	add	r1, r0, r1, lsl #2
	add	r1, r1, #12288
	add	r3, r3, #13376
	add	r2, r2, #13120
	str	lr, [r1, #884]
	str	lr, [r1, #948]
	str	lr, [r1, #1012]
	str	lr, [r1, #1076]
	strb	lr, [r3, #52]
	ldr	r3, [ip, #20]
	add	r3, r3, #540
	add	r3, r3, #2
	str	lr, [r0, r3, asl #2]
	str	r4, [ip, #24]
	ldr	r3, [r2, #48]
	sub	r3, r3, #1
	str	r3, [r2, #48]
.L1168:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1171:
	str	r2, [sp]
	mov	r3, r1
	ldr	r2, .L1172
	mov	r0, #1
	ldr	r1, .L1172+4
	bl	dprint_vfmw
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1173:
	.align	2
.L1172:
	.word	.LANCHOR0+420
	.word	.LC99
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
	ldr	r2, [r0, #3040]
	mov	r6, r0
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #3200
	mov	r4, #0
	add	r5, r5, #4
	b	.L1177
.L1176:
	add	r4, r4, #1
	cmp	r4, r2
	bcs	.L1180
.L1177:
	ldr	r3, [r5, #4]!
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1176
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_RemoveApcStore
	ldr	r2, [r6, #3040]
	add	r4, r4, #1
	cmp	r4, r2
	bcc	.L1177
.L1180:
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
	ldr	r2, [r0, #2820]
	movw	lr, #5036
	ldr	r1, [r4, #748]
	movw	ip, #12668
	ldr	r3, [r0, #2816]
	mov	r9, r0
	mov	r0, #1
	mla	r2, lr, r1, r2
	ldr	r1, [r9, #3040]
	cmp	r1, #0
	ldr	r2, [r2, #32]
	mla	r3, ip, r2, r3
	ldr	r3, [r3, #116]
	mov	r3, r0, asl r3
	str	r3, [fp, #-48]
	beq	.L1181
	add	r7, r9, #3200
	add	r3, r9, #5760
	add	r3, r3, #12
	add	r7, r7, #4
	str	r3, [fp, #-52]
	mov	r8, #0
	b	.L1198
.L1184:
	add	r8, r8, #1
	cmp	r8, r1
	bcs	.L1181
.L1198:
	ldr	r0, [r7, #4]!
	ldr	r3, [r4, #744]
	ldr	r2, [r0, #32]
	cmp	r2, r3
	bne	.L1184
	ldr	r1, [r4, #1644]
	ldr	r3, [r4, #1648]
	ldr	r2, [r4, #1652]
	add	r3, r3, r1
	cmp	r3, r2
	mov	r6, r3
	ldrcs	ip, [r0, #8]
	movcs	r1, #0
	bcs	.L1186
	add	r5, r3, #1456
	ldr	r3, [r0, #8]
	add	r5, r5, #4
	mov	r1, #0
	mov	r10, #1
	mov	r2, r3
	mov	r3, r9
	add	r5, r9, r5, lsl #2
	mov	r9, r8
	mov	r8, r3
.L1192:
	ldr	ip, [r5, #-944]
	cmp	ip, #0
	ldr	ip, [r0, #60]
	beq	.L1187
	cmp	ip, #0
	beq	.L1188
	ldr	ip, [r5]
	cmp	ip, r2
	beq	.L1221
.L1188:
	cmp	r1, #0
	bne	.L1203
	ldr	r1, [r5]
	mov	lr, r2
.L1200:
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	rsb	r1, r1, lr
	clz	r1, r1
	cmp	ip, #0
	mov	r1, r1, lsr #5
	moveq	r1, #0
	cmp	r1, #0
	bne	.L1222
.L1203:
	mov	ip, r2
.L1191:
	ldr	lr, [r4, #1652]
	add	r6, r6, #1
	add	r5, r5, #4
	mov	r2, ip
	cmp	r6, lr
	bcc	.L1192
	mov	r3, r8
	ldr	r2, [r4, #1644]
	mov	r8, r9
	mov	r9, r3
	ldr	r3, [r4, #1648]
	add	r3, r3, r2
.L1186:
	cmp	r3, #0
	ldr	lr, [r4, #724]
	ldrne	r6, [fp, #-52]
	movne	r5, #0
	movne	r10, #1
	beq	.L1194
.L1196:
	ldr	r3, [r0, #60]
	add	r5, r5, #1
	cmp	r3, #0
	bne	.L1195
	ldr	r2, [r6]
	add	r2, lr, r2
	cmp	r2, ip
	beq	.L1223
.L1195:
	ldr	r3, [r4, #1648]
	add	r6, r6, #4
	ldr	r2, [r4, #1644]
	add	r3, r3, r2
	cmp	r5, r3
	bcc	.L1196
.L1194:
	eor	r1, r1, #1
	cmp	ip, lr
	moveq	ip, #0
	andne	ip, r1, #1
	cmp	ip, #0
	beq	.L1219
	mov	r3, #0
	strb	r3, [r0, #1]
	ldr	r3, [r7]
	mov	r2, #0
	str	r2, [r3, #60]
	ldr	r3, [r7]
	str	r2, [r3, #72]
	ldr	r3, [r7]
	ldr	r2, [r3, #52]
	cmp	r2, #1
	beq	.L1219
	ldr	r1, [r3, #28]
	mov	r2, #0
	ldr	r0, [r9, #276]
	bl	FSP_SetRef
.L1219:
	ldr	r1, [r9, #3040]
	add	r8, r8, #1
	cmp	r8, r1
	bcc	.L1198
.L1181:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1187:
	cmp	ip, #0
	beq	.L1190
	ldr	lr, [r5]
	ldr	r3, [fp, #-48]
	eor	lr, lr, r2
	sub	ip, r3, #1
	ands	ip, lr, ip
	beq	.L1224
.L1190:
	cmp	r1, #0
	bne	.L1203
	ldr	r3, [fp, #-48]
	ldr	ip, [r5]
	sub	r1, r3, #1
	and	lr, r2, r1
	and	r1, r1, ip
	b	.L1200
.L1222:
	strb	r10, [r0, #1]
	mov	r3, #0
	ldr	r1, [r7]
	mov	r2, #1
	str	r10, [r1, #60]
	ldr	r1, [r7]
	str	r3, [r1, #72]
	ldr	r1, [r7]
	str	r10, [r1, #48]
	ldr	r1, [r7]
	ldr	r0, [r8, #276]
	ldr	r1, [r1, #28]
	bl	FSP_SetRef
	ldr	r0, [r7]
	mov	r1, #1
	ldr	ip, [r0, #8]
	b	.L1191
.L1224:
	strb	r10, [r0, #1]
	mov	r2, #1
	ldr	r1, [r7]
	str	ip, [r1, #72]
.L1220:
	ldr	r1, [r7]
	str	r10, [r1, #48]
	ldr	r1, [r7]
	ldr	r0, [r8, #276]
	ldr	r1, [r1, #28]
	bl	FSP_SetRef
	ldr	r0, [r7]
	mov	r1, #1
	ldr	ip, [r0, #8]
	b	.L1191
.L1223:
	strb	r10, [r0, #1]
	mov	r2, #1
	ldr	r1, [r7]
	str	r3, [r1, #72]
	ldr	r3, [r7]
	str	r10, [r3, #48]
	ldr	r3, [r7]
	ldr	r0, [r9, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldr	r0, [r7]
	ldr	lr, [r4, #724]
	mov	r1, #1
	ldr	ip, [r0, #8]
	b	.L1195
.L1221:
	strb	r10, [r0, #1]
	mov	r3, #0
	ldr	r1, [r7]
	mov	r2, #1
	str	r3, [r1, #72]
	b	.L1220
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
	ldr	r3, [r3, #740]
	sub	r3, r3, #19
	cmp	r3, #2
	bls	.L1226
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_CheckThatAllRefPicsAreAvailable.part.14
.L1226:
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
	ldr	r3, [r0, #2856]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_SetFrmRepeatCount.part.15
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
	add	r1, r0, #13696
	add	r4, r0, #27904
	add	r1, r1, #32
	add	r4, r4, #224
	mov	r5, #0
.L1234:
	ldr	r3, [r1, #48]
	cmp	r3, #0
	bne	.L1230
	cmp	r1, #0
	beq	.L1231
	ldr	lr, [r0, #3040]
	cmp	lr, #0
	beq	.L1231
	ldr	r2, [r0, #3208]
	cmp	r2, r1
	beq	.L1230
	add	r2, r0, #3200
	add	r2, r2, #8
	b	.L1232
.L1233:
	ldr	ip, [r2, #4]!
	cmp	ip, r1
	beq	.L1230
.L1232:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L1233
.L1231:
	add	r5, r5, #1
.L1230:
	add	r1, r1, #720
	cmp	r1, r4
	bne	.L1234
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
	ldr	r1, [r5, #1644]
	cmp	r1, #0
	beq	.L1264
	add	r10, r0, #5696
	add	r9, r0, #5760
	mov	r8, #0
	add	r10, r10, #55
	add	r9, r9, #12
	mov	r6, r8
.L1250:
	ldrb	r3, [r10, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1246
	ldr	lr, [r7, #3040]
	ldr	ip, [r5, #724]
	ldr	r3, [r9]
	cmp	lr, #0
	add	ip, ip, r3
	beq	.L1246
	add	r1, r7, #3200
	mov	r3, #0
	add	r1, r1, #4
	b	.L1249
.L1247:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L1246
.L1249:
	ldr	r2, [r1, #4]!
	ldr	r0, [r2, #8]
	cmp	r0, ip
	bne	.L1247
	ldr	r4, [r5, #744]
	ldr	r0, [r2, #32]
	cmp	r4, r0
	bne	.L1247
	add	r4, r7, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r4, #3208]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1290
.L1248:
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r4, #3208]
	mov	r1, #0
	add	r3, r7, r8, lsl #2
	add	r8, r8, #1
	str	r1, [r2, #60]
	ldr	r2, [r4, #3208]
	str	r2, [r3, #3276]
.L1246:
	ldr	r1, [r5, #1644]
	add	r6, r6, #1
	add	r9, r9, #4
	cmp	r1, r6
	bhi	.L1250
.L1245:
	ldr	r2, [r7, #3036]
	str	r8, [r7, #3052]
	cmp	r2, r8
	bls	.L1255
	add	r3, r8, #816
	mov	r0, #0
	add	r3, r3, #2
	add	r3, r7, r3, lsl #2
.L1254:
	add	r8, r8, #1
	str	r0, [r3, #4]!
	cmp	r8, r2
	bne	.L1254
.L1255:
	ldr	r3, [r5, #1648]
	add	r4, r1, r3
	cmp	r4, r6
	movls	r8, #0
	bls	.L1253
	add	r9, r6, #1440
	add	r10, r6, #5696
	add	r9, r9, #3
	add	r10, r10, #55
	add	r10, r7, r10
	mov	r8, #0
	add	r9, r7, r9, lsl #2
	str	r8, [fp, #-48]
.L1260:
	ldrb	r3, [r10, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1256
	ldr	ip, [r7, #3040]
	ldr	r0, [r5, #724]
	ldr	r3, [r9]
	cmp	ip, #0
	add	r0, r0, r3
	beq	.L1256
	add	r1, r7, #3200
	mov	r3, #0
	add	r1, r1, #4
	b	.L1259
.L1257:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L1256
.L1259:
	ldr	r2, [r1, #4]!
	ldr	lr, [r2, #8]
	cmp	lr, r0
	bne	.L1257
	ldr	r8, [r5, #744]
	ldr	lr, [r2, #32]
	cmp	r8, lr
	bne	.L1257
	add	r8, r7, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r8, #3208]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1291
.L1258:
	ldr	r1, [fp, #-48]
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r8, #3208]
	add	r3, r7, r1, lsl #2
	add	r1, r1, #1
	str	r1, [fp, #-48]
	mov	r1, #0
	str	r1, [r2, #60]
	ldr	r2, [r8, #3208]
	str	r2, [r3, #3344]
.L1256:
	add	r6, r6, #1
	add	r9, r9, #4
	cmp	r4, r6
	bhi	.L1260
	ldr	r8, [fp, #-48]
	ldr	r2, [r7, #3036]
.L1253:
	cmp	r2, r8
	str	r8, [r7, #3056]
	bls	.L1244
	add	r1, r8, #832
	mov	r3, #0
	add	r1, r1, #3
	add	r7, r7, r1, lsl #2
.L1262:
	add	r8, r8, #1
	str	r3, [r7, #4]!
	cmp	r8, r2
	bne	.L1262
.L1244:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1290:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r7, #276]
	bl	FSP_SetRef
	ldr	r3, [r4, #3208]
	b	.L1248
.L1291:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r7, #276]
	bl	FSP_SetRef
	ldr	r3, [r8, #3208]
	b	.L1258
.L1264:
	mov	r8, r1
	mov	r6, r1
	b	.L1245
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
	ldr	r2, [r0, #2820]
	mov	r7, r0
	ldr	r3, [r5, #748]
	movw	r0, #5036
	ldr	ip, [r7, #2816]
	movw	lr, #12668
	mov	r1, #1
	mla	r0, r0, r3, r2
	ldr	r3, [r5, #1644]
	ldr	r2, [r5, #1648]
	add	r2, r3, r2
	ldr	r3, [r5, #1652]
	sub	r2, r2, #1
	ldr	r0, [r0, #32]
	sub	r10, r3, #1
	cmp	r10, r2
	mla	r2, lr, r0, ip
	ldr	r2, [r2, #116]
	mov	r2, r1, asl r2
	ble	.L1303
	add	r9, r3, #1456
	add	r3, r3, #5696
	add	r9, r9, #3
	add	r3, r3, #56
	add	r3, r7, r3
	sub	r4, r2, #1
	add	r9, r7, r9, lsl #2
	mov	r8, #0
	str	r8, [fp, #-52]
	mov	r8, r3
	str	r1, [fp, #-56]
.L1299:
	ldrb	r3, [r8, #-1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1294
	ldrb	r0, [r9, #-944]	@ zero_extendqisi2
	ldr	ip, [r9]
	ldr	lr, [r7, #3040]
	cmp	r0, #0
	andeq	ip, ip, r4
	cmp	lr, #0
	ble	.L1294
	add	r1, r7, #3200
	mov	r3, #0
	add	r1, r1, #4
	str	r7, [fp, #-48]
	b	.L1298
.L1297:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L1310
.L1298:
	ldr	r2, [r1, #4]!
	cmp	r0, #0
	ldr	r6, [r2, #8]
	andeq	r6, r6, r4
	cmp	ip, r6
	bne	.L1297
	ldr	r6, [r5, #744]
	ldr	r7, [r2, #32]
	cmp	r7, r6
	bne	.L1297
	ldr	r7, [fp, #-48]
	mov	ip, #0
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-56]
	add	r3, r7, r3, lsl #2
	strb	r0, [r2, #1]
	add	r2, r7, r1, lsl #2
	add	r1, r1, #1
	str	r1, [fp, #-52]
	ldr	r1, [r3, #3208]
	str	ip, [r1, #64]
	ldr	r1, [r3, #3208]
	str	r0, [r1, #60]
	ldr	r3, [r3, #3208]
	str	r3, [r2, #3412]
.L1294:
	ldr	r3, [r5, #1644]
	sub	r10, r10, #1
	ldr	r2, [r5, #1648]
	sub	r9, r9, #4
	add	r3, r3, r2
	sub	r3, r3, #1
	cmp	r3, r10
	blt	.L1299
	ldr	r8, [fp, #-52]
	mov	r3, r8
.L1293:
	ldr	r2, [r7, #3036]
	str	r3, [r7, #3048]
	cmp	r2, r8
	ble	.L1292
	add	r3, r8, #852
	mov	r1, #0
	add	r3, r7, r3, lsl #2
.L1301:
	add	r8, r8, #1
	str	r1, [r3, #4]!
	cmp	r8, r2
	bne	.L1301
.L1292:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1310:
	ldr	r7, [fp, #-48]
	b	.L1294
.L1303:
	mov	r3, #0
	mov	r8, r3
	b	.L1293
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
	beq	.L1329
	add	r2, r0, #4096
	mov	r3, #280
	ldr	r7, [r2, #16]
	mul	r3, r3, r7
	add	r2, r0, r3
	add	r1, r2, #13120
	add	r1, r1, #40
	ldr	r1, [r1, #4]
	cmp	r1, #0
	beq	.L1314
	add	r2, r2, #13120
	ldr	r4, [r2, #52]
	cmp	r4, #0
	addne	r3, r3, #13120
	addne	r3, r3, #52
	movne	r4, #0
	addne	r3, r0, r3
	bne	.L1317
	b	.L1315
.L1320:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1315
.L1317:
	add	r4, r4, #1
	cmp	r4, r1
	bne	.L1320
.L1314:
	ldr	r1, .L1330
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L1327:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1315:
	ldr	r1, [r5, #28]
	ldr	r0, [r6, #276]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	beq	.L1318
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L1318
	mov	r2, #70
	mov	r3, #280
	mla	r2, r2, r7, r4
	mov	lr, #1
	mla	r7, r3, r7, r6
	ldr	r1, .L1330+4
	mov	r3, r4
	mov	r0, #13
	add	r6, r6, r2, lsl #2
	add	r2, r7, #13120
	add	r6, r6, #12288
	add	r7, r7, r4
	str	lr, [r6, #884]
	ldr	ip, [ip, #28]
	ldr	ip, [ip, #4]
	str	ip, [r6, #948]
	ldr	ip, [r5, #8]
	str	ip, [r6, #1012]
	ldr	ip, [r2, #48]
	add	ip, ip, lr
	str	ip, [r2, #48]
	ldr	r2, [r5, #228]
	bl	dprint_vfmw
	ldr	r1, [r5, #32]
	add	r3, r7, #13376
	mov	r2, #0
	str	r4, [r5, #24]
	mov	r0, r2
	str	r1, [r6, #1076]
	strb	r2, [r3, #52]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1318:
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	mov	r0, #0
	ldr	r2, [r5, #28]
	ldr	r3, [r5, #8]
	stmia	sp, {r1, ip}
	str	r0, [sp, #8]
	ldr	r1, .L1330+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1327
.L1329:
	mov	r0, r5
	movw	r3, #11586
	ldr	r2, .L1330+12
	ldr	r1, .L1330+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1327
.L1331:
	.align	2
.L1330:
	.word	.LC101
	.word	.LC100
	.word	.LC4
	.word	.LC2
	.word	.LC3
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
	beq	.L1342
	ldr	r0, [r0, #276]
	ldr	r1, [r4, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1334
	ldrsb	r2, [r0, #1]
	cmp	r2, #3
	cmpne	r2, #0
	moveq	r0, #1
	movne	r0, #0
	beq	.L1353
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1339
	ldr	r2, [r4, #48]
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1338
	cmp	r3, #1
	beq	.L1338
.L1350:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1353:
	ldr	r3, [r4, #28]
	mov	r0, #13
	str	r2, [sp]
	ldr	r1, .L1354
	ldr	r2, .L1354+4
	bl	dprint_vfmw
.L1336:
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1339
	ldr	r3, [r4, #8]
	mov	r0, #1
	ldr	r2, .L1354+4
	ldr	r1, .L1354+8
	bl	dprint_vfmw
	mvn	r0, #2
	b	.L1350
.L1334:
	ldr	ip, [r4, #28]
	mov	r2, r4
	ldr	r3, [r4, #8]
	mov	r0, #1
	ldr	r1, .L1354+12
	str	ip, [sp, #4]
	ldr	ip, [r4, #52]
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1336
.L1338:
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	mov	r3, r4
	ldr	r2, .L1354+4
	ldr	r1, .L1354+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1350
.L1342:
	mvn	r0, #0
	b	.L1350
.L1339:
	mov	r2, #1
	mov	r3, #2
	strb	r2, [r4, #2]
	mvn	r0, #2
	str	r3, [r4, #52]
	b	.L1350
.L1355:
	.align	2
.L1354:
	.word	.LC102
	.word	.LANCHOR0+440
	.word	.LC104
	.word	.LC103
	.word	.LC105
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
	beq	.L1358
	ldr	ip, [r0, #3040]
	cmp	ip, #0
	beq	.L1358
	add	r10, r0, #3200
	mvn	r3, #0
	mvn	r6, #1
	mvn	r7, #0
	add	r10, r10, #4
	str	r3, [fp, #-48]
	mov	r9, #0
	b	.L1361
.L1395:
	ldr	r1, [r10]
	ldr	ip, [r5, #3040]
	add	r1, r1, #672
	ldrd	r0, [r1, #-8]
	cmp	r1, r7
	cmpeq	r0, r6
	strcc	r9, [fp, #-48]
	movcc	r6, r0
	movcc	r7, r1
.L1360:
	add	r9, r9, #1
	cmp	r9, ip
	bcs	.L1398
.L1361:
	ldr	r1, [r10, #4]!
	cmp	r1, #0
	beq	.L1360
	ldr	r1, [r1, #28]
	ldr	r0, [r5, #276]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1397
	ldrsb	r1, [r0, #1]
	cmp	r1, #3
	cmpne	r1, #0
	bne	.L1395
.L1397:
	ldr	ip, [r5, #3040]
	add	r9, r9, #1
	cmp	r9, ip
	bcc	.L1361
.L1398:
	ldr	r3, [fp, #-48]
	cmn	r3, #1
	beq	.L1358
	ldrd	r2, [r8, #-8]
	cmp	r3, r7
	cmpeq	r2, r6
	bhi	.L1399
.L1358:
	ldrb	r3, [r4, #145]	@ zero_extendqisi2
	ldrb	r2, [r4, #144]	@ zero_extendqisi2
	and	r3, r3, #195
	bfc	r3, #0, #2
	bfc	r2, #0, #2
	strb	r3, [r4, #145]
	strb	r2, [r4, #144]
	ldr	r3, [r5, #144]
	str	r3, [r4, #188]
	ldr	r3, [r5, #2836]
	ldrh	r3, [r3, #124]
	cmp	r3, #1
	moveq	r2, #0
	beq	.L1362
	movw	r2, #257
	cmp	r3, r2
	movne	r2, #1
	bne	.L1362
	ldr	r2, [r5, #3492]
	subs	r2, r2, #1
	movne	r2, #1
.L1362:
	ldr	r3, [r5, #2840]
	ldrb	r3, [r3, #2066]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r1, #3
	beq	.L1363
	ldr	r3, [r4, #40]
	cmp	r3, #1
	cmpne	r3, #11
	moveq	r1, #1
	bne	.L1400
.L1364:
	ldr	r2, [r4, #44]
	clz	r2, r2
	mov	r2, r2, lsr #5
.L1363:
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
	ldr	r3, [r5, #2856]
	ldr	r1, [r4, #28]
	ldr	r3, [r3, #604]
	str	r3, [r4, #204]
	ldr	r3, [r5, #2856]
	ldr	r3, [r3, #608]
	str	r3, [r4, #208]
	ldr	r3, [r5, #2856]
	ldr	r3, [r3, #612]
	str	r3, [r4, #212]
	ldr	r0, [r5, #276]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L1356
	ldr	r3, .L1401
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
.L1356:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1399:
	ldr	r0, [r5, #276]
	strd	r6, [sp]
	bl	IsPtsRewind
	cmp	r0, #0
	bne	.L1358
	ldrd	r2, [r8, #-8]
	mov	r0, #29
	ldr	r1, .L1401+4
	strd	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	add	r10, r5, r3, lsl #2
	ldrd	r2, [r8, #-8]
	ldr	r1, [r10, #3208]
	add	r1, r1, #672
	strd	r2, [r1, #-8]
	strd	r6, [r8, #-8]
	b	.L1358
.L1400:
	bic	r3, r3, #8
	cmp	r3, #2
	moveq	r1, #2
	movne	r1, #3
	b	.L1364
.L1402:
	.align	2
.L1401:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC106
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
	bhi	.L1405
	mov	r3, #720
	mla	r1, r3, r1, r0
	add	r1, r1, #13696
	ldrb	r0, [r1, #33]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1405:
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
	ldr	r0, [r0, #276]
	mov	r9, r1
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1411
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	addne	r4, r0, #576
	addne	r5, r0, #608
	movne	r6, #0
	movne	r7, #0
	beq	.L1416
.L1410:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1409
	ldr	r0, [r8, #276]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1409:
	cmp	r4, r5
	bne	.L1410
	ldr	r0, [r8, #276]
	mov	r1, r9
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1416:
	ldr	r1, .L1417
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1411:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1418:
	.align	2
.L1417:
	.word	.LC107
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
	bhi	.L1423
	sub	r2, r3, #8448
	movw	ip, #4749
	sub	r2, r2, #52
	cmp	r2, ip
	movls	r3, #1
	strlsb	r3, [r0, #3]
	bls	.L1421
	sub	r3, r3, #13248
	movw	r2, #1749
	sub	r3, r3, #2
	cmp	r3, r2
	bhi	.L1423
	mov	r3, #2
	strb	r3, [r0, #3]
.L1421:
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
.L1423:
	mov	r3, #0
	strb	r3, [r0, #3]
	b	.L1421
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
	ldr	r1, .L1445
	mov	r4, r0
	ldrb	r2, [r0]	@ zero_extendqisi2
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	ldr	r1, .L1445+4
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r1, .L1445+8
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	ldr	r1, .L1445+12
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #4]
	ldr	r1, .L1445+16
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #6]
	ldr	r1, .L1445+20
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	ldr	r1, .L1445+24
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #9]	@ zero_extendqisi2
	ldr	r1, .L1445+28
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r5, [r4, #1]	@ zero_extendqisi2
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	mov	r0, #32
	cmp	r5, #0
	bne	.L1427
	ldr	r1, .L1445+32
	bl	dprint_vfmw
	ldrb	r2, [r4, #11]	@ zero_extendqisi2
	ldr	r1, .L1445+36
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	ldr	r1, .L1445+40
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #13]	@ zero_extendqisi2
	ldr	r1, .L1445+44
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #14]	@ zero_extendqisi2
	ldr	r1, .L1445+48
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #15]	@ zero_extendqisi2
	ldr	r1, .L1445+52
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #15
	addne	r6, r4, #26
	beq	.L1432
.L1431:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1445+56
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1445+60
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1431
.L1432:
	ldrb	r2, [r4, #38]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1445+64
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #38
	addne	r6, r4, #45
	movne	r5, #0
	beq	.L1433
.L1434:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1445+68
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1445+72
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1434
.L1433:
	movw	r2, #290
	ldr	r1, .L1445+76
	mov	r0, #32
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1427:
	ldr	r1, .L1445+80
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #10
	addne	r6, r4, #78
	movne	r5, #0
	beq	.L1439
.L1438:
	mov	r2, r5
	ldrh	r3, [r7, #2]!
	ldr	r1, .L1445+84
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r3, [r6, #2]!
	mov	r2, r5
	ldr	r1, .L1445+88
	mov	r0, #32
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1438
.L1439:
	ldrb	r2, [r4, #148]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1445+92
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #148
	addne	r6, r4, #216
	movne	r5, #0
	beq	.L1437
.L1440:
	mov	r3, r5
	ldrh	r2, [r7, #2]!
	ldr	r1, .L1445+96
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrh	r2, [r6, #2]!
	mov	r0, #32
	ldr	r1, .L1445+100
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1440
.L1437:
	movw	r3, #286
	ldr	r1, .L1445+104
	ldrh	r2, [r4, r3]
	add	r4, r4, #288
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r1, .L1445+108
	ldrh	r2, [r4]
	mov	r0, #32
	bl	dprint_vfmw
	b	.L1433
.L1446:
	.align	2
.L1445:
	.word	.LC108
	.word	.LC109
	.word	.LC110
	.word	.LC111
	.word	.LC112
	.word	.LC113
	.word	.LC114
	.word	.LC115
	.word	.LC116
	.word	.LC117
	.word	.LC118
	.word	.LC119
	.word	.LC120
	.word	.LC121
	.word	.LC123
	.word	.LC124
	.word	.LC122
	.word	.LC125
	.word	.LC126
	.word	.LC135
	.word	.LC127
	.word	.LC129
	.word	.LC130
	.word	.LC128
	.word	.LC133
	.word	.LC134
	.word	.LC131
	.word	.LC132
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
	beq	.L1487
	cmp	r2, #0
	bne	.L1489
.L1487:
	ldrb	ip, [r4, #59]	@ zero_extendqisi2
	ldrb	r0, [r4, #128]	@ zero_extendqisi2
.L1449:
	str	r0, [sp, #12]
	mov	r0, #22
	str	r1, [sp, #4]
	str	r2, [sp]
	str	ip, [sp, #8]
	ldr	r2, .L1492
	ldr	r1, .L1492+4
	bl	dprint_vfmw
	mov	r3, #0
	strb	r3, [r5, #458]
.L1447:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1489:
	cmp	r1, #0
	beq	.L1487
	ldrb	r0, [r4, #59]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1452
	ldrb	r0, [r4, #128]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1490
.L1452:
	mov	r3, #1
	strb	r3, [r5, #458]
	ldr	r0, [r6, #24]
	ldrb	r1, [r4, #57]	@ zero_extendqisi2
	ldrb	r2, [r4, #58]	@ zero_extendqisi2
	cmp	r0, #9
	strb	r1, [fp, #-320]
	strb	r2, [fp, #-319]
	bne	.L1454
	ldr	r2, [r6, #32]
	cmp	r2, #9
	streqb	r3, [fp, #-312]
.L1454:
	ldrb	r3, [r4, #60]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1455
	ldrb	r2, [r4, #129]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1455
	cmp	r2, #9
	cmpne	r3, #9
	ldrneb	r3, [fp, #-312]	@ zero_extendqisi2
	moveq	r3, #1
	strb	r3, [fp, #-318]
.L1455:
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
	bne	.L1459
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
	beq	.L1464
	sub	r2, fp, #320
	add	ip, r4, #66
	add	r0, r2, #15
	add	r1, r4, #81
	add	r2, r2, #26
.L1463:
	add	r3, r3, #1
	ldrb	r6, [ip, #1]!	@ zero_extendqisi2
	ldrb	lr, [r1, #1]!	@ zero_extendqisi2
	cmp	r3, r7
	strb	r6, [r0, #1]!
	strb	lr, [r2, #1]!
	bne	.L1463
.L1464:
	ldrb	r6, [r4, #97]	@ zero_extendqisi2
	cmp	r6, #0
	strb	r6, [fp, #-282]
	beq	.L1462
	sub	r1, fp, #280
	sub	r2, fp, #272
	add	r0, r4, #97
	sub	r1, r1, #2
	add	r4, r4, #112
	sub	r2, r2, #3
	mov	r3, #0
.L1467:
	add	r3, r3, #1
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	ldrb	ip, [r4, #1]!	@ zero_extendqisi2
	cmp	r3, r6
	strb	lr, [r1, #1]!
	strb	ip, [r2, #1]!
	bne	.L1467
.L1462:
	ldr	r3, [r5, #464]
	cmp	r3, #0
	bne	.L1491
	ldr	r2, .L1492
	mov	r0, #1
	ldr	r1, .L1492+8
	bl	dprint_vfmw
	b	.L1447
.L1459:
	ldrb	r7, [r4, #168]	@ zero_extendqisi2
	ldr	r2, [r4, #136]
	add	r7, r7, #1
	ldr	r3, [r4, #140]
	uxtb	r7, r7
	strh	r2, [fp, #-34]	@ movhi
	cmp	r7, #0
	strb	r7, [fp, #-310]
	strh	r3, [fp, #-32]	@ movhi
	beq	.L1471
	sub	r3, fp, #320
	add	ip, r4, #170
	add	r1, r4, #368
	sub	r2, fp, #242
	add	r0, r3, #10
	mov	r3, #0
.L1470:
	add	r3, r3, #1
	ldrh	r6, [ip, #2]!
	ldrh	lr, [r1, #2]!
	cmp	r3, r7
	strh	r6, [r0, #2]!	@ movhi
	strh	lr, [r2, #2]!	@ movhi
	bcc	.L1470
.L1471:
	ldrb	r6, [r4, #169]	@ zero_extendqisi2
	add	r6, r6, #1
	uxtb	r6, r6
	strb	r6, [fp, #-172]
	cmp	r6, #0
	beq	.L1462
	add	r2, r4, #432
	sub	r0, fp, #172
	add	r4, r4, #236
	add	r2, r2, #2
	sub	r1, fp, #104
	mov	r3, #0
.L1472:
	add	r3, r3, #1
	ldrh	lr, [r4, #2]!
	ldrh	ip, [r2, #2]!
	cmp	r3, r6
	strh	lr, [r0, #2]!	@ movhi
	strh	ip, [r1, #2]!	@ movhi
	bcc	.L1472
	b	.L1462
.L1491:
	ldr	r3, .L1492+12
	sub	r1, fp, #320
	movw	r2, #290
	ldr	r0, [r5, #472]
	ldr	r3, [r3, #52]
	blx	r3
	movw	r3, #290
	str	r3, [r5, #460]
	b	.L1447
.L1490:
	mov	ip, r0
	b	.L1449
.L1493:
	.align	2
.L1492:
	.word	.LANCHOR0+464
	.word	.LC136
	.word	.LC137
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
.L1495:
	ldr	r6, [r0, #4]!
	add	r2, r2, #1
	cmp	r2, #3
	strh	r6, [lr, #2]!	@ movhi
	ldr	r6, [r5, #4]!
	strh	r6, [r4, #2]!	@ movhi
	bne	.L1495
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
	add	r4, r0, #4096
	ldr	r3, [r0, #2820]
	movw	ip, #5036
	ldr	r1, [r0, #2816]
	ldr	r2, [r4, #748]
	movw	r5, #12668
	mov	r6, r0
	add	r0, r0, #13696
	add	r0, r0, #32
	mla	r3, ip, r2, r3
	mov	r2, #0
	mov	lr, r2
	ldr	r3, [r3, #32]
	strb	r2, [r4, #9]
	mla	r5, r5, r3, r1
.L1502:
	ldr	r3, [r0, #48]
	cmp	r3, #0
	bne	.L1498
	cmp	r0, #0
	beq	.L1509
	ldr	ip, [r6, #3040]
	cmp	ip, #0
	beq	.L1509
	ldr	r2, [r6, #3208]
	cmp	r2, r0
	beq	.L1498
	add	r2, r6, #3200
	add	r2, r2, #8
	b	.L1500
.L1501:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	beq	.L1498
.L1500:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1501
.L1509:
	mov	r8, #720
	mov	r7, r0
	mla	r8, r8, lr, r6
	mov	r3, #101
	mov	r2, #640
	str	r3, [r4, #48]
	add	r0, r4, #72
	mov	r3, #1
	add	r1, r8, #13760
	strb	r3, [r4, #9]
	add	r1, r1, #48
	mov	r9, #0
	bl	memcpy
	add	r3, r8, #13696
	movw	r2, #13744
	str	r7, [r4, #68]
	str	r9, [r4, #224]
	str	r9, [r8, r2]
	strb	r9, [r3, #34]
	strb	r9, [r7]
	ldr	r3, [r4, #68]
	str	r9, [r3, #60]
	ldr	r3, [r4, #68]
	str	r9, [r3, #64]
	ldr	r3, [r4, #68]
	str	r9, [r3, #52]
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1506
	ldr	r0, [r6, #276]
	bl	FSP_NewLogicFs
	mov	r8, r0
	mov	r1, r0
	ldr	r0, [r6, #276]
	bl	FSP_GetLogicFs
	mvn	r3, r8
	mov	r3, r3, lsr #31
	cmp	r0, #0
	mov	r7, r0
	moveq	r3, #0
	cmp	r3, #0
	beq	.L1504
	add	r2, r6, #3472
	add	r1, r5, #2064
	add	r2, r2, #8
	bl	HEVC_ConvertHDRInfo
	ldr	r3, [r6, #2856]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1513
.L1505:
	ldr	r5, .L1514
	add	r1, r7, #40
	ldr	r0, [r4, #68]
	mov	r2, #640
	ldr	r3, [r5, #52]
	add	r0, r0, #80
	blx	r3
	ldr	r1, [r4, #68]
	add	r0, r6, #4160
	ldr	r3, [r5, #52]
	add	r1, r1, #80
	mov	r2, #640
	add	r0, r0, #8
	blx	r3
	ldr	r3, [r4, #68]
	mov	r0, #0
	str	r8, [r3, #28]
	ldrsb	r3, [r7, #4]
	str	r3, [r4, #44]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1498:
	add	lr, lr, #1
	add	r0, r0, #720
	cmp	lr, #20
	bne	.L1502
.L1506:
	ldr	r1, .L1514+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1513:
	ldr	r1, [r6, #2840]
	ldr	r5, [r7, #152]
	ldr	r3, [r7, #76]
	ldr	r2, [r1, #68]
	ldr	r1, [r1, #64]
	str	r9, [r7, #280]
	mul	r5, r5, r2
	str	r2, [r7, #112]
	str	r1, [r7, #108]
	str	r9, [r7, #284]
	add	r3, r5, r3
	str	r9, [r7, #288]
	str	r3, [r7, #80]
	mov	r0, r3
	str	r9, [r7, #292]
	str	r9, [r7, #296]
	bl	MEM_Phy2Vir
	ldr	r2, [r7, #60]
	ldr	r3, [r7, #156]
	add	r5, r5, r2
	str	r9, [r7, #556]
	str	r5, [r7, #64]
	add	r5, r5, r3
	str	r5, [r7, #72]
	str	r0, [r7, #552]
	b	.L1505
.L1504:
	strb	r3, [r4, #9]
	mov	r0, r3
	ldr	r1, .L1514+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1515:
	.align	2
.L1514:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC138
	.word	.LC139
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
	ldr	r0, [r0, #276]
	bl	FSP_GetFspType
	cmn	r0, #1
	mov	r4, r0
	movne	r4, #0
	bne	.L1520
	b	.L1523
.L1519:
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1521
	cmp	r4, #32
	beq	.L1524
.L1520:
	mov	r1, r4
	ldr	r0, [r5, #276]
	bl	FSP_GetLogicFs
	add	r4, r4, #1
	cmp	r0, #0
	bne	.L1519
	ldr	r1, .L1525
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1523:
	ldr	r1, .L1525+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1521:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1524:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1526:
	.align	2
.L1525:
	.word	.LC141
	.word	.LC140
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
	add	r0, r0, #6144
	add	r0, r0, #40
	add	r5, r8, #14336
	bl	ResetVoQueue
	add	r9, r8, #28672
	add	r5, r5, #40
	add	r9, r9, #104
	mov	r6, #0
	mov	r7, #0
.L1530:
	sub	r4, r5, #32
	mov	r3, #0
	strb	r3, [r5, #-647]
	str	r3, [r5, #-600]
.L1529:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1528
	ldr	r0, [r8, #276]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1528:
	cmp	r4, r5
	bne	.L1529
	add	r5, r4, #720
	cmp	r5, r9
	bne	.L1530
	ldr	r2, [r8, #184]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r8, r8, #2160
	mov	r3, #0
	add	r8, r8, #4
	mov	r1, r3
.L1532:
	add	r3, r3, #1
	str	r1, [r8, #4]!
	cmp	r3, r2
	bne	.L1532
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
	ldr	r3, [r6, #3208]
	str	r7, [r3, #48]
	ldr	r3, [r6, #3208]
	ldr	r0, [r0, #276]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1541
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1542
	ldr	r3, [r6, #3208]
	mov	r2, r7
	ldr	r0, [r5, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
.L1542:
	ldr	r3, [r6, #3208]
	mov	r2, #0
	ldr	r0, [r5, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
.L1541:
	ldr	r1, [r5, #3040]
	sub	r1, r1, #1
	cmp	r4, r1
	addls	r3, r4, #800
	addls	r3, r3, #2
	addls	r3, r5, r3, lsl #2
	bhi	.L1545
.L1544:
	add	r4, r4, #1
	ldr	r2, [r3, #4]!
	cmp	r4, r1
	str	r2, [r3, #-4]
	bls	.L1544
.L1545:
	add	r3, r1, #800
	mov	r2, #0
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #8]
	str	r1, [r5, #3040]
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
	ldr	r1, [r0, #3040]
	mov	r5, r0
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r6, #0
	mov	r4, r6
	mov	r7, r6
	b	.L1557
.L1556:
	add	r4, r4, #1
	cmp	r4, r1
	mov	r6, r4
	bcs	.L1563
.L1557:
	add	r3, r5, r4, lsl #2
	ldr	r3, [r3, #3208]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1556
	mov	r1, r6
	strb	r7, [r3]
	mov	r0, r5
	sub	r4, r4, #1
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	add	r4, r4, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r1, [r5, #3040]
	mov	r6, r4
	cmp	r4, r1
	bcc	.L1557
.L1563:
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
	ldr	r5, [r0, #3040]
	mov	r10, r0
	cmp	r5, #0
	beq	.L1573
	mov	r6, #0
	mvn	r8, #0
	mov	r9, r6
	mov	r4, r6
	b	.L1572
.L1583:
	ldrsb	r2, [r0, #1]
	cmp	r2, #0
	cmpne	r2, #3
	ldr	r2, [r7, #3208]
	bne	.L1568
	ldr	r0, [r2, #52]
	cmp	r0, #1
	beq	.L1568
	str	r8, [r2, #28]
	mov	r3, #1
	ldr	r2, [r7, #3208]
	strb	r1, [r2, #1]
	ldr	r2, [r7, #3208]
	strb	r3, [r2, #2]
	ldr	r2, [r7, #3208]
.L1568:
	ldr	r3, [r2]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	addne	r9, r9, #1
	beq	.L1582
	add	r4, r4, #1
	cmp	r4, r5
	beq	.L1565
.L1572:
	add	r7, r10, r9, lsl #2
	ldr	r0, [r10, #276]
	ldr	r2, [r7, #3208]
	ldr	r1, [r2, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1566
	ldrsb	r1, [r0]
	cmp	r1, #0
	beq	.L1583
	ldr	r2, [r7, #3208]
	b	.L1568
.L1566:
	ldr	r2, [r7, #3208]
	ldr	r1, [r2, #52]
	cmp	r1, #1
	beq	.L1568
	str	r8, [r2, #28]
	mov	r3, #1
	ldr	r2, [r7, #3208]
	strb	r0, [r2, #1]
	ldr	r2, [r7, #3208]
	strb	r3, [r2, #2]
	ldr	r2, [r7, #3208]
	b	.L1568
.L1582:
	mov	r1, r9
	mov	r0, r10
	add	r4, r4, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	cmp	r4, r5
	mov	r6, #1
	bne	.L1572
.L1565:
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1573:
	mov	r6, r5
	b	.L1565
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
	ldr	r1, [r3, #880]
	ldr	r2, [r3, #876]
	cmp	r1, r2
	bcs	.L1586
	ldr	r2, [r3, #1160]
	ldr	r3, [r3, #1156]
	cmp	r2, r3
	bcs	.L1586
	ldr	r3, [r0, #3036]
	ldr	r2, [r0, #3040]
	cmp	r2, r3
	ldmccfd	sp, {r4, r5, fp, sp, pc}
	cmp	r3, #15
	bls	.L1590
.L1586:
	ldr	r3, [r4, #3208]
	mov	r5, #0
	mov	r2, r5
	strb	r5, [r3, #1]
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #276]
	bl	FSP_SetRef
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HEVC_RemoveFrameStoreOutDPB
.L1590:
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L1586
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
	ldr	r2, [r0, #3040]
	mov	r5, r0
	ldr	r3, [r0, #3036]
	cmp	r2, r3
	bhi	.L1598
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1599:
	add	r1, r5, #3200
	mov	r3, #0
	add	r1, r1, #4
.L1595:
	ldr	r2, [r1, #4]!
	ldr	r0, [r4]
	ldr	r2, [r2, #8]
	cmp	r0, r2
	strgt	r2, [r4]
	strgt	r3, [r6]
	add	r3, r3, #1
	ldr	r2, [r5, #3040]
	cmp	r2, r3
	bhi	.L1595
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1598:
	ldr	r1, .L1600
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #3036]
	cmp	r2, #0
	str	r2, [r5, #3040]
	bne	.L1599
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1601:
	.align	2
.L1600:
	.word	.LC142
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
	ldr	lr, [r0, #2820]
	movw	r5, #5036
	movw	r4, #12668
	ldr	ip, [r3, #748]
	ldr	r3, [r0, #2816]
	mla	ip, r5, ip, lr
	ldr	lr, [fp, #4]
	ldr	ip, [ip, #32]
	mla	r3, r4, ip, r3
	ldr	ip, [r3, #64]
	ldr	r3, [r3, #68]
	cmp	r1, ip
	cmpeq	lr, #0
	bne	.L1603
	cmp	r2, r3
	beq	.L1614
.L1603:
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1615
.L1608:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1615:
	ldr	r2, [r0, #2856]
	ldr	r2, [r2, #24]
	bics	r2, r2, #4
	beq	.L1608
	ldr	r2, [r0, #2396]
	cmp	r2, #0
	bne	.L1613
	str	r3, [r0, #2396]
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1614:
	ldr	r3, [r0, #172]
	cmp	r3, #0
	beq	.L1603
	ldr	r3, [r0, #2856]
	ldr	r3, [r3, #936]
	cmp	r3, #0
	bne	.L1603
.L1613:
	mov	r0, #0
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
	ldr	r4, [r0, #2828]
	ldrb	ip, [r4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1627
	mov	r3, #0
	mov	r2, r4
	mov	lr, r3
.L1618:
	add	r3, r3, #1
	ldr	r1, [r2, #44]
	cmp	r3, ip
	add	r2, r2, #28
	add	lr, lr, r1
	bne	.L1618
.L1617:
	ldr	r2, [r0, #2808]
	mov	r3, ip, asl #5
	sub	ip, r3, ip, asl #2
	add	r4, r4, ip
	ldr	r3, [r2, #24]
	and	r3, r3, #7
	str	r3, [r4, #56]
	ldr	r2, [r0, #2828]
	ldr	r3, [r0, #2808]
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #48]
	add	r2, r2, ip, lsr #3
	rsb	r2, lr, r2
	str	r2, [r3, #60]
	ldr	r1, [r0, #2828]
	ldr	r3, [r0, #2808]
	ldrb	r2, [r1]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r2, asl #5
	sub	r2, r3, r2, asl #2
	add	r2, r1, r2
	ldr	r3, [r2, #44]
	add	r3, lr, r3
	rsb	r3, ip, r3, lsl #3
	str	r3, [r2, #52]
	ldr	r2, [r0, #2828]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	ldr	r1, [r3, #56]
	and	r2, r2, #3
	add	r2, r1, r2, lsl #3
	str	r2, [r3, #56]
	ldr	r2, [r0, #2828]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #3
	str	r2, [r3, #60]
	ldr	r1, [r0, #2828]
	ldr	r2, [r1, #8]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L1634
	ldrb	ip, [r1]	@ zero_extendqisi2
	add	lr, ip, #1
	cmp	r2, lr
	movhi	r2, #1
	movls	r2, #0
	cmp	lr, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L1620
	add	ip, ip, #2
	mov	lr, #0
.L1621:
	sub	r3, ip, #1
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	str	lr, [r1, #56]
	ldr	r2, [r0, #2828]
	add	r2, r2, r3
	ldr	r1, [r2, #48]
	str	r1, [r2, #60]
	ldr	r2, [r0, #2828]
	add	r2, r2, r3
	ldr	r1, [r2, #44]
	mov	r1, r1, asl #3
	str	r1, [r2, #52]
	ldr	r2, [r0, #2828]
	add	r2, r2, r3
	ldr	r1, [r2, #60]
	ldr	r4, [r2, #56]
	and	r1, r1, #15
	add	r1, r4, r1, lsl #3
	str	r1, [r2, #56]
	ldr	r2, [r0, #2828]
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #15
	str	r2, [r3, #60]
	ldr	r1, [r0, #2828]
	ldr	r3, [r1, #8]
	cmp	ip, #1
	cmpls	ip, r3
	add	ip, ip, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L1621
	sub	r3, r3, #1
.L1620:
	mov	r2, r3, asl #5
	ldr	ip, [r1, #12]
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	ldr	r3, [r1, #52]
	rsb	r3, ip, r3
	str	r3, [r1, #52]
	ldr	r4, [r0, #2828]
	ldrb	r1, [r4]	@ zero_extendqisi2
	ldr	lr, [r4, #8]
	cmp	r1, lr
	ldmcsfd	sp, {r4, fp, sp, pc}
	sxth	r3, r1
	add	r0, r0, #4096
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r3, r4, r3
.L1625:
	ldr	r2, [r3, #60]
	add	r1, r1, #1
	ldr	ip, [r0, #40]
	add	r3, r3, #28
	cmp	r2, ip
	strcc	r2, [r0, #40]
	ldrcc	lr, [r4, #8]
	cmp	lr, r1
	bhi	.L1625
	ldmfd	sp, {r4, fp, sp, pc}
.L1634:
	ldr	r1, .L1635
	mov	r0, #0
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L1627:
	mov	lr, ip
	b	.L1617
.L1636:
	.align	2
.L1635:
	.word	.LC143
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
	ldr	r2, [r2, #748]
	cmp	r2, r3
	bge	.L1645
	movw	r3, #5036
	ldr	r1, [r0, #2820]
	mul	r3, r3, r2
	add	ip, r1, r3
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1646
	ldr	r2, [ip, #32]
	ldr	r3, [r0, #160]
	cmp	r2, r3
	bge	.L1647
	ldr	r1, [r0, #2816]
	movw	r3, #12668
	mla	r3, r3, r2, r1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1648
	ldr	r2, [r3, #48]
	ldr	r3, [r0, #156]
	cmp	r2, r3
	bcs	.L1649
	movw	r3, #24912
	ldr	r1, [r0, #2812]
	mul	r3, r3, r2
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1650
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1645:
	ldr	r1, .L1651
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1646:
	ldr	r1, .L1651+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1647:
	ldr	r1, .L1651+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1648:
	ldr	r1, .L1651+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1649:
	ldr	r1, .L1651+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1650:
	ldr	r1, .L1651+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1652:
	.align	2
.L1651:
	.word	.LC144
	.word	.LC145
	.word	.LC146
	.word	.LC147
	.word	.LC148
	.word	.LC149
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
	ldr	lr, [r0, #2828]
	ldr	r3, [r1, #744]
	ldr	r2, [lr, #16]
	add	r4, r0, r3, lsl #2
	ldr	ip, [r4, #244]
	cmn	ip, #-2147483647
	beq	.L1694
	sub	r5, r2, #16
	cmp	r2, #21
	cmpne	r5, #2
	bls	.L1691
.L1670:
	cmp	r2, #1
	bls	.L1695
.L1658:
	sub	r2, r2, #19
	cmp	r2, #1
	movls	ip, #-2147483647
	strls	ip, [r4, #244]
.L1691:
	ldr	r2, [r1, #724]
.L1660:
	cmp	ip, r2
	ble	.L1661
	ldr	r5, [lr, #16]
	sub	r6, r5, #8
	cmp	r6, #1
	addhi	r3, r0, r3
	bls	.L1696
.L1663:
	ldrb	ip, [r3, #12]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1664
	ldr	r5, [r4, #252]
	cmp	r5, r2
	ble	.L1664
	ldr	r6, [lr, #16]
	sub	r7, r6, #8
	cmp	r7, #1
	bls	.L1697
.L1664:
	ldrb	ip, [r1, #713]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1665
	ldr	lr, [lr, #16]
	sub	r5, lr, #19
	cmp	r5, #1
	bls	.L1692
	cmp	lr, #21
	beq	.L1692
	sub	lr, lr, #16
	cmp	lr, #2
	strls	r2, [r4, #252]
	movls	ip, #1
	strlsb	ip, [r3, #12]
.L1665:
	ldr	ip, [r0, #260]
	ldrb	r3, [r1, #712]	@ zero_extendqisi2
	cmp	ip, #0
	ldr	r1, [r1, #748]
	beq	.L1669
	ldr	ip, [r0, #208]
	cmp	r1, ip
	movne	r3, #1
.L1669:
	ldr	ip, [r0, #328]
	cmp	ip, r1
	movne	r0, #1
	beq	.L1698
.L1690:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1695:
	ldr	r5, [r1, #732]
	cmp	r5, #2
	bne	.L1658
	cmn	ip, #-2147483647
	bne	.L1691
.L1659:
	ldr	r2, [r1, #724]
	str	r2, [r4, #244]
	ldr	ip, [lr, #16]
	cmp	ip, #1
	bls	.L1699
.L1661:
	add	r3, r0, r3
	ldrb	ip, [r3, #6]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1663
	ldr	r5, [lr, #16]
	sub	r6, r5, #8
	cmp	r6, #1
	bhi	.L1663
	str	r2, [sp]
	movw	r3, #12994
	str	r5, [sp, #8]
	mov	r0, #1
	str	ip, [sp, #4]
	ldr	r2, .L1700
	ldr	r1, .L1700+4
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1690
.L1694:
	sub	r6, r2, #16
	cmp	r6, #5
	movhi	r7, #0
	movls	r7, #1
	cmp	r2, #1
	ldrls	r5, [r1, #732]
	movhi	r5, #0
	subls	r5, r5, #2
	clzls	r5, r5
	movls	r5, r5, lsr #5
	orrs	r5, r5, r7
	moveq	r0, #2
	beq	.L1690
	cmp	r2, #21
	cmpne	r6, #2
	bhi	.L1670
	b	.L1659
.L1698:
	ldr	r0, [r0, #284]
	cmp	r0, r2
	moveq	r0, r3
	movne	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1696:
	str	r2, [sp]
	movw	r3, #12987
	str	r5, [sp, #8]
	mov	r0, #1
	str	ip, [sp, #4]
	ldr	r2, .L1700
	ldr	r1, .L1700+8
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1690
.L1692:
	str	r2, [r4, #252]
	strb	ip, [r3, #12]
	b	.L1665
.L1699:
	mov	ip, #1
	str	ip, [r0, #356]
	ldr	ip, [r4, #244]
	b	.L1660
.L1697:
	str	r2, [sp, #4]
	movw	r3, #13003
	str	r6, [sp, #12]
	mov	r0, #1
	str	r5, [sp, #8]
	str	ip, [sp]
	ldr	r2, .L1700
	ldr	r1, .L1700+12
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1690
.L1701:
	.align	2
.L1700:
	.word	.LANCHOR0+484
	.word	.LC151
	.word	.LC150
	.word	.LC152
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
	ldr	r0, [r0, #2808]
	bl	BsGet
	cmp	r0, #0
	beq	.L1707
	ldr	r0, [r4, #2808]
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	beq	.L1706
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r1, .L1708
	mov	r2, r0
	mov	r0, #19
	bl	dprint_vfmw
.L1706:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1707:
	ldr	r1, .L1708+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1709:
	.align	2
.L1708:
	.word	.LC154
	.word	.LC153
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
	ldr	r0, [r0, #740]
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
	ldr	r0, [r0, #740]
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
	bne	.L1749
.L1747:
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r6, #0
	str	r0, [r9, #4]
	ble	.L1718
	sub	r3, fp, #84
	sub	r7, fp, #92
	add	r10, r3, r6
	mov	r4, r3
	mov	r9, r7
.L1719:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4], #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r4, r10
	strb	r0, [r9], #1
	bne	.L1719
	cmp	r6, #7
	movle	r4, r6
	ble	.L1723
	b	.L1729
.L1722:
	cmp	r4, #8
	beq	.L1729
.L1723:
	mov	r1, #2
	ldr	r0, [r5, #2808]
	bl	BsGet
	add	r4, r4, #1
	cmp	r0, #0
	beq	.L1722
	ldr	r1, .L1751
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1718:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1729:
	mov	r10, #0
	b	.L1727
.L1726:
	add	r10, r10, #1
	cmp	r6, r10
	ble	.L1718
.L1727:
	cmp	r8, #0
	beq	.L1724
	sub	r3, fp, #84
	ldrb	r3, [r3, r10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1750
.L1724:
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1726
	mov	r1, #8
	ldr	r0, [r5, #2808]
	bl	BsGet
	b	.L1726
.L1750:
	mov	r1, #2
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	mov	r4, #32
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2808]
	bl	BsGet
.L1725:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L1725
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #12
	ldr	r0, [r5, #2808]
	bl	BsGet
	b	.L1724
.L1749:
	mov	r1, #2
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	sub	r4, fp, #77
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2808]
	sub	r7, fp, #45
	bl	BsGet
	mov	r10, r0
.L1714:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	strb	r0, [r4, #1]!
	cmp	r4, r7
	bne	.L1714
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #1]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	sub	r3, r10, #4
	cmp	r3, #3
	bls	.L1715
	ldrb	r3, [fp, #-72]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1715
	ldrb	r3, [fp, #-71]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1715
	ldrb	r3, [fp, #-70]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1715
	ldrb	r3, [fp, #-69]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1715
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #11
	ldr	r0, [r5, #2808]
	bl	BsGet
	b	.L1717
.L1715:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #2
	ldr	r0, [r5, #2808]
	bl	BsGet
.L1717:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	ldrb	r2, [fp, #-75]	@ zero_extendqisi2
	ldrb	r3, [fp, #-74]	@ zero_extendqisi2
	mov	r1, #8
	str	r10, [r5, #332]
	str	r2, [r5, #336]
	str	r3, [r5, #340]
	b	.L1747
.L1752:
	.align	2
.L1751:
	.word	.LC155
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
	ldr	r9, .L1771
	add	r10, r0, #2240
	add	r3, r0, #2256
	add	r10, r10, #4
	mov	r6, #0
	add	r3, r3, #4
	str	r0, [fp, #-52]
	str	r3, [fp, #-48]
.L1754:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L1762
	ldr	r3, [fp, #-52]
	mov	r8, r6, asl #9
	ldr	r7, [fp, #-48]
	sub	r8, r8, r6, asl #7
	add	r5, r3, #632
	mov	r4, #0
.L1760:
	cmp	r6, #0
	add	r0, r5, r8
	mov	r2, #64
	ldr	r3, [r9, #52]
	beq	.L1769
	cmp	r6, #3
	beq	.L1770
	ldr	ip, .L1771+4
	cmp	r4, #2
	ldr	r1, .L1771+8
	movhi	r1, ip
	blx	r3
.L1756:
	mov	r3, #16
	str	r3, [r7, #4]!
	ldr	r3, [r10]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1760
.L1762:
	add	r6, r6, #1
	ldr	r3, [fp, #-48]
	cmp	r6, #4
	add	r3, r3, #24
	str	r3, [fp, #-48]
	bne	.L1754
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1769:
	mov	r2, #16
	ldr	r1, .L1771+12
	mov	r0, r5
	blx	r3
	b	.L1756
.L1770:
	ldr	r0, .L1771+4
	cmp	r4, #0
	ldr	r1, .L1771+8
	mov	r2, #64
	movne	r1, r0
	add	r0, r5, #1152
	blx	r3
	b	.L1756
.L1772:
	.align	2
.L1771:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+500
	.word	.LANCHOR2
	.word	.LANCHOR0+564
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
	add	lr, r2, #90
	mov	ip, r2, asl #3
	sub	r2, ip, r2, asl #1
	mov	r5, #0
	ldr	r7, [r0, lr, asl #2]
	add	r3, r3, r2
	cmp	r7, #64
	mov	r6, r3, asl #4
	movcs	r7, #64
	mov	r8, r7, lsr #2
.L1774:
	cmp	r5, r8
	ldmcsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r7, #0
	beq	.L1774
	add	r3, r5, r6
	ldrb	ip, [r1]	@ zero_extendqisi2
	mov	r4, r1
	mov	r2, #0
	add	r3, r0, r3, lsl #2
	ldr	lr, [r3, #632]
	orr	ip, lr, ip
	str	ip, [r3, #632]
.L1780:
	add	r2, r2, #1
	add	r3, r5, r6
	and	lr, r2, #3
	cmp	r2, r7
	add	r3, r0, r3, lsl #2
	mov	ip, lr, asl #3
	beq	.L1774
	ldrb	r9, [r4, #1]!	@ zero_extendqisi2
	cmp	lr, #3
	ldr	lr, [r3, #632]
	addeq	r5, r5, #1
	orr	ip, lr, r9, asl ip
	str	ip, [r3, #632]
	b	.L1780
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
	ldr	r1, [r0, #2840]
	mov	r7, r0
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1808
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1819
	ldr	r3, [r0, #2844]
	ldrb	r2, [r3, #21]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1792
	cmn	r3, #256
	add	r2, r3, #256
	str	r2, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
.L1791:
	cmp	r1, #0
	bne	.L1809
.L1794:
	ldr	r10, .L1822
	mov	r2, #1536
	add	r0, r7, #632
	add	r8, r7, #2240
	mov	r6, r1
	add	r8, r8, #4
	ldr	r3, [r10, #48]
	blx	r3
	ldr	r9, [fp, #-48]
.L1795:
	ldr	r3, [r8, #4]!
	cmp	r3, #0
	movne	r5, r9
	movne	r4, #0
	beq	.L1798
.L1796:
	mov	r3, r4
	mov	r1, r5
	mov	r2, r6
	mov	r0, r7
	bl	HEVC_CalScalingList
	ldr	r3, [r8]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1796
.L1798:
	add	r6, r6, #1
	add	r9, r9, #384
	cmp	r6, #4
	bne	.L1795
	ldr	r2, [fp, #-48]
	add	r0, r7, #2256
	ldr	r3, [r10, #52]
	add	r0, r0, #8
	add	r1, r2, #1536
	mov	r2, #96
	blx	r3
.L1808:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1819:
	ldr	r2, [r0, #2844]
	ldrb	r3, [r2, #1889]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1820
	add	r0, r1, #12288
	ldrb	ip, [r0, #372]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L1821
	ldrb	r3, [r2, #21]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1799
.L1792:
	ldrb	r3, [r1, #4]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1809
.L1814:
	cmn	r1, #432
	add	r3, r1, #432
	str	r3, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
	cmp	r1, #0
	beq	.L1794
.L1809:
	mov	r0, r7
	bl	HEVC_SetDefaultScalingList
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1788:
	ldrb	r3, [r2, #21]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1814
.L1799:
	cmn	r2, #256
	add	r3, r2, #256
	str	r3, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
	b	.L1791
.L1821:
	ldrb	ip, [r1, #4]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1788
	ldrb	r1, [r2, #21]	@ zero_extendqisi2
	orrs	r3, r1, r3
	bne	.L1789
	ldr	r2, [r0, #376]
	movw	r1, #12668
	ldr	r3, [r7, #2816]
	add	r2, r7, r2, lsl #2
	ldr	r2, [r2, #228]
	mla	r3, r1, r2, r3
.L1817:
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1809
	cmn	r3, #432
	add	r2, r3, #432
	str	r2, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
	b	.L1791
.L1820:
	ldr	r2, [r2, #1956]
	movw	r0, #5036
	ldr	r1, [r7, #2820]
	movw	lr, #12668
	ldr	r3, [r7, #2816]
	add	r2, r7, r2, lsl #2
	ldr	ip, [r2, #236]
	ldr	r2, [r2, #228]
	mla	r0, r0, ip, r1
	mla	r3, lr, r2, r3
	ldrb	r2, [r0, #21]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1817
	cmn	r0, #256
	add	r3, r0, #256
	str	r3, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
	b	.L1791
.L1789:
	cmp	r1, #0
	beq	.L1809
	b	.L1799
.L1823:
	.align	2
.L1822:
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
	b	.L1825
.L1827:
	.word	.L1831
	.word	.L1829
	.word	.L1829
	.word	.L1830
.L1829:
	ldr	r3, .L1835
	cmp	r1, #2
	add	r0, r3, #64
	movhi	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1831:
	ldr	r0, .L1835+4
	ldmfd	sp, {fp, sp, pc}
.L1830:
	ldr	r3, .L1835
	cmp	r1, #0
	add	r0, r3, #64
	movne	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1825:
	ldr	r1, .L1835+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1836:
	.align	2
.L1835:
	.word	.LANCHOR2+80
	.word	.LANCHOR2+64
	.word	.LC156
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
	bne	.L1847
	sub	r2, r3, #1
	mov	r4, #1
	movs	r2, r2, asr #1
	beq	.L1839
.L1840:
	movs	r2, r2, asr #1
	add	r4, r4, #1
	bne	.L1840
.L1839:
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	cmp	r5, #1
	movls	r10, #0
	movhi	r10, #1
	uxtb	r0, r0
	strb	r0, [r8]
	cmp	r0, #0
	cmpne	r5, #1
	bls	.L1844
	ldr	r3, [r7, #76]
	cmp	r3, #0
	beq	.L1844
	mov	r9, r8
	mov	r5, #0
.L1845:
	mov	r1, r4
	ldr	r0, [r6, #2808]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r9, #4]!
	ldr	r3, [r7, #76]
	cmp	r3, r5
	bhi	.L1845
.L1844:
	ldr	r5, [r7, #20]
	cmp	r5, #0
	beq	.L1862
.L1843:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1862:
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #1]
	cmp	r0, #0
	moveq	r10, #0
	andne	r10, r10, #1
	cmp	r10, #0
	beq	.L1843
	ldr	r3, [r7, #80]
	cmp	r3, #0
	beq	.L1843
	add	r8, r8, #128
.L1846:
	mov	r1, r4
	ldr	r0, [r6, #2808]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r8, #4]!
	ldr	r3, [r7, #80]
	cmp	r3, r5
	bhi	.L1846
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1847:
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
	ldr	r0, [r0, #2808]
	bl	BsResidBits
	cmp	r0, #0
	ble	.L1865
	ldr	r3, [r4, #2828]
	ldr	r3, [r3, #12]
	add	r3, r3, #3
	cmp	r0, r3
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1865:
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
	ldr	r0, [r0, #2808]
	ldr	r2, [r0, #16]
	ldr	r3, [r0, #24]
	mov	r2, r2, asl #3
	cmp	r2, r3
	bls	.L1869
	mov	r1, #8
	bl	BsShow
	subs	r0, r0, #128
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1869:
	ldr	r1, .L1870
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1871:
	.align	2
.L1870:
	.word	.LC157
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
.L1884:
	ldr	r1, [r6, #2828]
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
.L1873:
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r5, r7, r0
	add	r2, r1, r5
	cmp	r4, #0
	bne	.L1885
	ldr	lr, [r1, #40]
	add	ip, ip, #1
	cmp	lr, r3
	beq	.L1886
	ldr	lr, [r2, #40]
	cmp	lr, r3
	sub	r3, r3, #1
	bne	.L1873
	ldr	r1, [r2, #64]
	ldr	r0, [r6, #276]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r6, #2828]
	mov	ip, r4
	add	r5, r3, r5
	str	r4, [r5, #40]
	ldr	r2, [r6, #2828]
	ldr	r3, [r2, #8]
	sub	r3, r3, #1
	str	r3, [r2, #8]
	b	.L1884
.L1885:
	tst	r4, #1
	mov	r3, #1
	moveq	r2, r3
	bne	.L1880
.L1881:
	ands	r0, r4, r2, asl r3
	add	r3, r3, #1
	bne	.L1880
	cmp	r3, #8
	bne	.L1881
	ldr	r1, .L1887
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1886:
	ldr	r1, .L1887+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1880:
	mov	r0, #0
	str	r0, [r1, #4]
	ldr	r2, [r6, #2828]
	add	ip, r3, ip, lsl #3
	str	ip, [r2, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1888:
	.align	2
.L1887:
	.word	.LC159
	.word	.LC158
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
	blt	.L1890
	add	r6, r5, #1
	mov	r0, r3
	mov	r1, r6
	bl	__aeabi_uidivmod
	ldr	r7, [r8, #2852]
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1891
	mov	r4, #0
	b	.L1893
.L1894:
	bl	__aeabi_uidivmod
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1891
.L1893:
	add	r4, r4, #1
	mov	r1, r6
	cmp	r4, r5
	add	r0, r3, r4
	ble	.L1894
.L1890:
	mvn	r0, #0
	str	r3, [r8, #148]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1891:
	cmp	r3, r6
	mov	r0, r3
	str	r3, [r8, #148]
	bcs	.L1904
	rsb	r1, r1, ip
	mov	r3, #1
	add	r7, r7, r1
	str	r3, [r7, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1904:
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
	beq	.L1913
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	str	r3, [r5, #32]
	str	r3, [r5, #36]
.L1908:
	ldr	r3, [r4, #40]
	mov	r0, r6
	cmp	r3, #0
	beq	.L1907
	ldr	r1, [r4, #64]
	bl	SM_ReleaseStreamSeg
	ldr	ip, [r4, #44]
	ldr	r3, [r4, #40]
	mov	r0, #7
	ldr	r2, .L1914
	ldr	r1, .L1914+4
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #40]
	str	r3, [r4, #56]
	str	r3, [r4, #44]
.L1907:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L1908
	ldr	r3, .L1914+8
	mov	r0, r5
	mov	r2, #96
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1913:
	mov	r0, r5
	movw	r3, #14320
	ldr	r2, .L1914+12
	ldr	r1, .L1914+16
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1915:
	.align	2
.L1914:
	.word	.LANCHOR0+580
	.word	.LC160
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC3
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	mov	r6, r0
	cmp	r3, #1
	beq	.L1952
.L1917:
	ldr	r3, [r6, #2840]
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r6, #3036]
.L1919:
	cmp	r3, #17
	bhi	.L1953
.L1920:
	add	lr, r6, #3264
	add	ip, r6, #3328
	add	r0, r6, #3200
	add	r1, r6, #3056
	mov	r7, #0
	add	lr, lr, #8
	add	ip, ip, #12
	add	r0, r0, #4
	add	r1, r1, #12
	add	r5, r6, #3408
	add	r4, r6, #3136
	mov	r2, r7
	mov	r3, r7
	str	r7, [r6, #3040]
	str	r7, [r6, #3052]
	str	r7, [r6, #3056]
	str	r7, [r6, #3048]
	str	r7, [r6, #3044]
	str	r7, [r6, #3064]
	str	r7, [r6, #3068]
.L1921:
	add	r2, r2, #1
	str	r3, [r5, #4]!
	cmp	r2, #17
	str	r3, [lr, #4]!
	str	r3, [ip, #4]!
	str	r3, [r0, #4]!
	str	r3, [r1, #4]!
	str	r3, [r4, #4]!
	bne	.L1921
	add	r4, r6, #13760
	ldr	r9, .L1954
	add	r4, r4, #48
	mov	r7, #0
.L1922:
	ldr	r3, [r9, #48]
	mov	r2, #640
	mov	r0, r4
	mov	r1, #0
	blx	r3
	str	r7, [r4, #148]
	add	r7, r7, #1
	mov	r5, #0
	cmp	r7, #20
	sub	r3, r4, #80
	strb	r5, [r4, #-80]
	mov	r2, #20
	str	r5, [r4, #-32]
	mov	r8, #16
	strb	r5, [r4, #-79]
	add	r4, r4, #720
	str	r5, [r4, #-792]
	strb	r5, [r4, #-798]
	str	r5, [r4, #-744]
	str	r2, [r4, #-780]
	str	r8, [r4, #-776]
	str	r3, [r4, #-724]
	ldr	r10, .L1954
	bne	.L1922
	add	r0, r6, #13120
	add	r4, r6, #12288
	ldr	r3, [r10, #48]
	mov	r2, #280
	mov	r1, r5
	add	r0, r0, #44
	blx	r3
	add	r0, r6, #13440
	ldr	r3, [r10, #48]
	mov	r2, #280
	mov	r1, r5
	add	r0, r0, #4
	str	r8, [r4, #876]
	str	r5, [r4, #880]
	blx	r3
	add	r3, r6, #2928
	add	r3, r3, #4
	add	r2, r6, #2864
	mov	r1, r5
	str	r8, [r4, #1156]
	str	r5, [r4, #1160]
.L1923:
	str	r1, [r2, #4]!
	cmp	r2, r3
	mov	r0, #0
	bne	.L1923
	add	r1, r6, #2992
	add	lr, r6, #4096
	add	r1, r1, #8
	mov	ip, r0
	str	r0, [lr, #780]
.L1924:
	str	ip, [r3, #4]!
	cmp	r3, r1
	mov	r2, #0
	bne	.L1924
	str	r2, [lr, #784]
	ldr	r0, [r6, #184]
	cmp	r0, r2
	addne	r1, r6, #2160
	movne	r3, r2
	addne	r1, r1, #4
	movne	r2, r3
	beq	.L1929
.L1928:
	add	r3, r3, #1
	str	r2, [r1, #4]!
	cmp	r3, r0
	bne	.L1928
.L1929:
	ldr	r2, [r6, #168]
	cmp	r2, #0
	movne	r4, #0
	movne	r5, r4
	beq	.L1916
.L1934:
	ldr	r3, [r6, #2848]
	mov	r7, r4, asl #2
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L1930
	ldr	r3, [r6, #2828]
	cmp	r1, r3
	beq	.L1930
	ldr	r0, [r6, #276]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r6, #2848]
	str	r5, [r3, r7]
	ldr	r3, [r6, #204]
	ldr	r2, [r6, #260]
	cmp	r3, #0
	subne	r3, r3, #1
	cmp	r2, #0
	str	r3, [r6, #204]
	subne	r2, r2, #1
	ldr	r3, [r6, #176]
	str	r2, [r6, #260]
	ldr	r2, [r6, #168]
	cmp	r3, #2
	subhi	r3, r3, #1
	movls	r3, #2
	str	r3, [r6, #176]
.L1930:
	add	r4, r4, #1
	cmp	r2, r4
	bhi	.L1934
.L1916:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1953:
	mov	r4, #17
	ldr	r2, .L1954+4
	str	r4, [sp]
	mov	r3, r4
	ldr	r1, .L1954+8
	mov	r0, #1
	bl	dprint_vfmw
	str	r4, [r6, #3036]
	b	.L1920
.L1952:
	ldr	r3, [r0, #2856]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L1917
	ldr	r2, [r0, #2392]
	cmp	r2, #0
	beq	.L1917
	ldr	r3, [r6, #2840]
	ldr	r3, [r3, #184]
	mul	r3, r3, r2
	add	r3, r3, #1
	str	r3, [r6, #3036]
	b	.L1919
.L1955:
	.align	2
.L1954:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+596
	.word	.LC161
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
	beq	.L1967
	ldr	ip, [r6, #3040]
	add	r8, r6, #3200
	cmp	ip, #0
	addne	r8, r8, #4
	movne	r3, #0
	movne	lr, #1
	movne	r1, r8
	beq	.L1982
.L1961:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	streqb	lr, [r2, #2]
	ldreq	ip, [r6, #3040]
	cmp	ip, r3
	bhi	.L1961
.L1962:
	mov	r4, r6
	mov	r7, #17
	mov	r5, #0
	mov	r3, #-2147483647
	str	r3, [r6, #212]
	str	r3, [r6, #216]
.L1959:
	ldr	r3, [r8, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L1963
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #276]
	bl	FSP_ClearLogicFs
.L1963:
	ldr	r3, [r4, #3276]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1964
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #276]
	bl	FSP_ClearLogicFs
.L1964:
	ldr	r3, [r4, #3344]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1965
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #276]
	bl	FSP_ClearLogicFs
.L1965:
	ldr	r3, [r4, #3412]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1966
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #276]
	bl	FSP_ClearLogicFs
.L1966:
	subs	r7, r7, #1
	str	r5, [r4, #3412]
	str	r5, [r4, #3344]
	add	r4, r4, #4
	str	r5, [r4, #3272]
	str	r5, [r4, #3204]
	bne	.L1959
	mov	r0, r6
	bl	HEVC_InitDecBuffers
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1982:
	add	r8, r8, #4
	b	.L1962
.L1967:
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
	ldr	r0, [r0, #2828]
	cmp	r0, #0
	beq	.L1986
	ldr	r3, [r0, #44]
	cmp	r3, #4096
	ldmcsfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L1987
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r3, [r4, #2828]
	ldr	ip, .L1987+4
	mov	r5, #0
	ldr	r2, [r3, #44]
	ldr	r0, [r3, #68]
	ldr	r1, [r3, #40]
	rsb	r0, r2, r0
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #2828]
	mov	r0, #1
	ldr	r2, [r3, #92]
	ldr	r1, [r3, #64]
	str	r2, [r3, #64]
	ldr	r3, [r4, #2828]
	str	r5, [r3, #56]
	ldr	r3, [r4, #2828]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #68]
	rsb	r2, ip, r2
	str	r2, [r3, #40]
	ldr	r3, [r4, #2828]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #76]
	rsb	r2, ip, r2
	str	r2, [r3, #48]
	ldr	r3, [r4, #2828]
	ldr	r2, [r3, #44]
	ldr	ip, [r3, #72]
	add	r2, r2, ip
	str	r2, [r3, #44]
	ldr	r3, [r4, #2828]
	str	r0, [r3, #8]
	ldr	r0, [r4, #276]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #2828]
	str	r5, [r3, #68]
	ldr	r3, [r4, #2828]
	str	r5, [r3, #84]
	ldr	r3, [r4, #2828]
	str	r5, [r3, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1986:
	ldr	r1, .L1987+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1988:
	.align	2
.L1987:
	.word	.LC163
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC162
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
	beq	.L1994
	ldr	ip, [r0, #3040]
	cmp	ip, #0
	beq	.L1994
	ldr	r3, [r0, #3208]
	cmp	r3, r1
	beq	.L1996
	add	r0, r0, #3200
	mov	r3, #0
	add	r0, r0, #8
	b	.L1991
.L1992:
	ldr	r2, [r0, #4]!
	cmp	r2, r1
	beq	.L1996
.L1991:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1992
.L1994:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1996:
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
	bls	.L2003
	movw	r0, #61166
	movt	r0, 65535
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2003:
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
	ldr	r1, .L2026
	mov	r4, r0
	ldr	r0, [r0, #2808]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2808]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	beq	.L2023
.L2009:
	mov	r1, #32
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r0, [r4, #2808]
	mov	r1, #32
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2023:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	mov	r6, r0
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r0, #8
	mov	r7, r0
	bhi	.L2024
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r0, #4
	ldrls	pc, [pc, r0, asl #2]
	b	.L2020
.L2008:
	.word	.L2009
	.word	.L2009
	.word	.L2010
	.word	.L2011
	.word	.L2012
.L2011:
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r0, #256
	mov	r8, r0
	bhi	.L2016
	cmp	r0, #0
	beq	.L2020
	add	r6, r6, #7
	add	r7, r7, #7
	bic	r6, r6, #7
	bic	r7, r7, #7
	mov	r5, #0
.L2018:
	mov	r1, r6
	ldr	r0, [r4, #2808]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, r7
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r5, r8
	bne	.L2018
.L2020:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2010:
	mov	r2, #1
	movs	r7, r2, asl r7
	addne	r6, r6, #7
	movne	r5, #0
	bicne	r6, r6, #7
	beq	.L2020
.L2014:
	add	r5, r5, #1
	mov	r1, r6
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r7, r5
	bne	.L2014
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2012:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r0, #255
	beq	.L2025
.L2019:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r0, [r4, #2808]
	mov	r1, #16
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2025:
	mov	r1, #32
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L2019
.L2024:
	mov	r2, r0
	ldr	r1, .L2026+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2016:
	ldr	r1, .L2026+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2027:
	.align	2
.L2026:
	.word	.LC164
	.word	.LC165
	.word	.LC166
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
	ldr	r1, .L2038
	mov	r4, r0
	ldr	r0, [r0, #2808]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2808]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	bne	.L2029
	mov	r1, #7
	ldr	r0, [r4, #2808]
	bl	BsGet
	sub	r3, r0, #3
	mov	r6, r0
	cmp	r3, #2
	bhi	.L2036
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #6
	mov	r5, r0
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	uxtb	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	clz	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	mov	r5, r5, lsr #5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r6, #5
	moveq	r5, #0
	cmp	r5, #0
	bne	.L2037
.L2032:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
.L2029:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r0, [r4, #2808]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2037:
	mov	r1, #4
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L2032
.L2036:
	mov	r2, r0
	ldr	r1, .L2038+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2039:
	.align	2
.L2038:
	.word	.LC167
	.word	.LC168
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
	bne	.L2044
	ldr	r1, .L2053
	ldr	r0, [r0, #2808]
	bl	HEVC_ue_v
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2051
.L2042:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L2052
.L2043:
	ldr	r0, [r4, #2808]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2051:
	ldr	r1, [r5, #4]
	ldr	r0, [r4, #2808]
	add	r1, r1, #1
	bl	BsGet
	b	.L2042
.L2052:
	ldr	r1, [r5, #8]
	ldr	r0, [r4, #2808]
	add	r1, r1, #1
	bl	BsGet
	b	.L2043
.L2044:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2054:
	.align	2
.L2053:
	.word	.LC169
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
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	ldr	r0, [r5, #2808]
	ldr	r1, .L2062
	bl	HEVC_ue_v
	cmp	r0, #15
	bgt	.L2056
	cmp	r0, #0
	addge	r6, r0, #1
	movge	r4, #0
	blt	.L2060
.L2059:
	add	r4, r4, #1
	ldr	r1, .L2062+4
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r4, r6
	bne	.L2059
.L2060:
	ldr	r0, [r5, #2808]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2056:
	ldr	r1, .L2062+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2063:
	.align	2
.L2062:
	.word	.LC170
	.word	.LC172
	.word	.LC171
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
	ldr	r1, .L2093
	mov	r7, r2
	str	r6, [r4, #3544]
	ldr	r0, [r0, #2808]
	bl	HEVC_ue_v
	cmp	r0, #15
	bhi	.L2089
	mov	r1, #1
	strb	r1, [r4, #3537]
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r8, r6
	beq	.L2090
.L2067:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r4, #1
	strb	r0, [r9]
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2808]
	add	r1, r1, r4
	bl	BsGet
	subs	r3, r4, #1
	beq	.L2091
.L2069:
	cmp	r3, #1
	beq	.L2092
.L2073:
	cmp	r4, #1
	bhi	.L2072
.L2071:
	add	r4, r4, #1
	subs	r3, r4, #1
	bne	.L2069
.L2091:
	ldrb	r2, [r7]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2073
	ldr	r2, [r7, #24]
	cmn	r2, #1
	beq	.L2071
.L2080:
	mov	r6, #0
	b	.L2076
.L2075:
	ldr	r3, [r7, #24]
	add	r3, r3, #1
	cmp	r3, r6
	bls	.L2073
.L2076:
	ldr	r1, [r7, #12]
	add	r6, r6, #1
	ldr	r0, [r5, #2808]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2808]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	orrs	r3, r8, r3
	beq	.L2075
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2808]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2808]
	add	r1, r1, #1
	bl	BsGet
	b	.L2075
.L2092:
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2072
	ldr	r3, [r7, #24]
	cmn	r3, #1
	bne	.L2080
.L2072:
	ldr	r0, [r5, #2808]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2090:
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r8, r0
	cmp	r8, #0
	beq	.L2067
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2808]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #20]
	ldr	r0, [r5, #2808]
	add	r1, r1, #1
	bl	BsGet
	b	.L2067
.L2089:
	mov	r2, r0
	ldr	r1, .L2093+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2094:
	.align	2
.L2093:
	.word	.LC173
	.word	.LC174
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
	ldr	r1, [r3, #3540]
	ldr	r2, [r3, #3544]
	add	r1, r1, #1
	str	r1, [r3, #3540]
	add	r2, r2, #1
	str	r2, [r3, #3544]
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2123
.L2096:
	ldrh	r3, [r5, #44]
	cmp	r3, #0
	beq	.L2098
	ldr	r1, [r5, #60]
	ldr	r0, [r4, #2808]
	add	r1, r1, #1
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r6, #8]
	ldr	r1, [r5, #64]
	ldr	r0, [r4, #2808]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #12]
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2099
.L2102:
	ldr	r2, [r4, #276]
	ldr	r3, .L2126
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L2124
.L2098:
	ldr	r0, [r4, #2808]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2123:
	mov	r1, #4
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r1, #2
	str	r0, [r6]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #4]
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L2096
.L2124:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L2098
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L2098
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_Sei_Get_Dpb_Output_Time
	b	.L2098
.L2099:
	ldr	r1, [r5, #52]
	ldr	r0, [r4, #2808]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2102
	ldrb	r3, [r5, #47]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2102
	ldr	r1, .L2126+4
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	mov	r1, #1
	mov	r7, r0
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r8, r0
	cmp	r8, #0
	bne	.L2125
.L2103:
	cmp	r7, #255
	bhi	.L2107
	add	r7, r7, #1
	mov	r6, #0
	b	.L2106
.L2105:
	cmp	r6, r7
	beq	.L2102
.L2106:
	ldr	r1, .L2126+8
	add	r6, r6, #1
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	cmp	r8, #0
	bne	.L2105
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2808]
	add	r1, r1, #1
	bl	BsGet
	b	.L2105
.L2125:
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2808]
	add	r1, r1, #1
	bl	BsGet
	b	.L2103
.L2107:
	ldr	r1, .L2126+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2127:
	.align	2
.L2126:
	.word	s_pstVfmwChan
	.word	.LC175
	.word	.LC177
	.word	.LC176
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
	beq	.L2138
	ldr	r1, .L2142
	ldr	r0, [r0, #2808]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L2130
.L2134:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r5]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2130:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L2141
.L2131:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #3]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #4]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #5]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #6]
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #7]
	addne	r7, r5, #7
	movne	r6, #0
	beq	.L2136
.L2135:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2808]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L2135
.L2136:
	mov	r1, #4
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #38]
	addne	r7, r5, #38
	movne	r6, #0
	beq	.L2134
.L2137:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2808]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #38]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L2137
	b	.L2134
.L2138:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2141:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #1]
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L2131
.L2143:
	.align	2
.L2142:
	.word	.LC178
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
	beq	.L2151
	cmp	r2, #3
	bls	.L2154
	mov	r1, #8
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #2
	beq	.L2155
	cmp	r0, #4
	beq	.L2156
	subs	r6, r6, #4
	beq	.L2150
.L2149:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r6, r4
	bne	.L2149
.L2150:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2155:
	add	r1, r5, #3536
	mov	r0, r5
	bl	HEVC_Sei_TSI
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2156:
	add	r1, r5, #3536
	mov	r0, r5
	add	r1, r1, #3
	bl	HEVC_Sei_Color_Volume_Reconstruction_Info
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2151:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2154:
	ldr	r1, .L2157
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2158:
	.align	2
.L2157:
	.word	.LC179
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
	bne	.L2204
.L2160:
	ldr	r1, .L2213
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4]
	bhi	.L2205
	ldr	r1, .L2213+4
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4, #4]
	bhi	.L2206
	ldr	r6, [r4]
	add	r2, r0, r6
	str	r2, [r4, #8]
	cmp	r2, #16
	bhi	.L2183
	cmp	r6, #0
	addne	r10, r4, #28
	addne	r9, r4, #11
	movne	r7, #0
	movne	r8, r7
	bne	.L2187
	b	.L2185
.L2186:
	str	r8, [r10, #4]!
	ldr	r0, [r5, #2808]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r6, [r4]
	cmp	r6, r7
	bls	.L2207
.L2187:
	ldr	r1, .L2213+8
	add	r7, r7, #1
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	mov	r1, #1
	cmp	r0, #32768
	mvn	r3, r0
	add	r8, r8, r3
	bcc	.L2186
	mov	r2, r0
	ldr	r1, .L2213+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2204:
	mov	r1, #1
	ldr	r0, [r0, #2808]
	bl	BsGet
	cmp	r0, #0
	beq	.L2160
	ldr	r7, [r9, #176]
	cmp	r7, r6
	movne	r0, #0
	beq	.L2208
.L2161:
	sub	r3, r6, #1
	rsb	r8, r0, r3
	cmp	r8, r3
	bhi	.L2209
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	ldr	r1, .L2213+16
	mov	r6, r0
	ldr	r0, [r5, #2808]
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
	bhi	.L2210
	add	r6, r8, #2192
	mov	r10, #0
	add	r6, r6, #4
	str	r10, [fp, #-48]
	add	r6, r9, r6
	str	r10, [fp, #-52]
	mov	r7, r10
	b	.L2170
.L2165:
	sub	r3, r0, #1
	cmp	r3, #1
	bls	.L2211
.L2166:
	add	r3, r9, r8
	add	r10, r10, #1
	add	r6, r6, #4
	ldr	r3, [r3, #2172]
	cmp	r3, r10
	bcc	.L2212
.L2170:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r0, #0
	bne	.L2165
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r0, r0, asl #1
	sub	r3, r0, #1
	cmp	r3, #1
	bhi	.L2166
.L2211:
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
	b	.L2166
.L2212:
	ldr	r3, [fp, #-52]
	cmp	r7, #16
	ldr	r2, [fp, #-48]
	str	r7, [r4, #8]
	str	r3, [r4]
	str	r2, [r4, #4]
	bhi	.L2171
	cmp	r3, #16
	bhi	.L2171
	cmp	r2, #16
	bhi	.L2171
	cmp	r7, #1
	subhi	r7, r7, #1
	addhi	r8, r4, #32
	addhi	r6, r4, #12
	movhi	r5, #0
	bls	.L2177
.L2176:
	ldr	ip, [r8, #4]!
	cmp	r5, #0
	ldrb	lr, [r6, #1]!	@ zero_extendqisi2
	mov	r2, r5
	movge	r1, r8
	movge	r3, r6
	blt	.L2179
.L2175:
	ldr	r0, [r1, #-4]!
	sub	r3, r3, #1
	cmp	ip, r0
	strlt	r0, [r1, #4]
	ldrltb	r0, [r3]	@ zero_extendqisi2
	strltb	r0, [r3, #1]
	strlt	ip, [r1]
	strltb	lr, [r3]
	subs	r2, r2, #1
	bpl	.L2175
.L2179:
	add	r5, r5, #1
	cmp	r5, r7
	bne	.L2176
.L2177:
	ldr	r3, [fp, #-52]
	movs	r6, r3, lsr #1
	beq	.L2174
	ldr	r3, [fp, #-52]
	add	r0, r4, #28
	mov	r1, #0
	add	r2, r3, #7
	add	r3, r3, #11
	add	r3, r4, r3
	mov	ip, r0
	add	r2, r4, r2, lsl #2
	add	r4, r4, #12
.L2180:
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
	bne	.L2180
.L2174:
	mov	r0, #0
.L2162:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2207:
	ldr	r2, [r4, #8]
.L2185:
	cmp	r2, r6
	bls	.L2174
	add	r8, r6, #7
	add	r9, r6, #11
	add	r9, r4, r9
	mov	r7, #0
	add	r8, r4, r8, lsl #2
.L2188:
	ldr	r1, .L2213+20
	add	r6, r6, #1
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	mov	r1, #1
	add	r0, r0, r1
	add	r7, r7, r0
	str	r7, [r8, #4]!
	ldr	r0, [r5, #2808]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r3, [r4, #8]
	cmp	r3, r6
	bhi	.L2188
	b	.L2174
.L2208:
	ldr	r1, .L2213+24
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	add	r2, r0, #1
	cmp	r7, r2
	bcs	.L2161
	mov	r3, r7
	ldr	r1, .L2213+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2162
.L2171:
	ldr	r1, .L2213+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2162
.L2206:
	ldr	r2, [r4]
	mov	r0, #1
	ldr	r1, .L2213+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2162
.L2209:
	mov	r2, r8
	ldr	r1, .L2213+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2162
.L2210:
	ldr	r1, .L2213+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2162
.L2205:
	mov	r2, r0
	ldr	r1, .L2213+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2162
.L2183:
	mov	r3, #16
	ldr	r1, .L2213+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2162
.L2214:
	.align	2
.L2213:
	.word	.LC186
	.word	.LC188
	.word	.LC191
	.word	.LC192
	.word	.LC183
	.word	.LC193
	.word	.LC180
	.word	.LC181
	.word	.LC185
	.word	.LC189
	.word	.LC182
	.word	.LC184
	.word	.LC187
	.word	.LC190
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
	beq	.L2237
	cmp	r2, #0
	bne	.L2264
.L2220:
	add	r5, r9, #24
	mov	r7, #0
.L2232:
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	uxtb	r4, r0
	cmp	r4, #0
	movne	r3, #0
	strne	r3, [r5]
	beq	.L2265
.L2235:
	ldr	r1, .L2270
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
.L2223:
	ldr	r1, .L2270+4
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	mov	r2, r0
	str	r0, [r5]
.L2224:
	cmp	r2, #31
	bhi	.L2266
.L2225:
	mov	r4, #0
.L2236:
	cmp	r4, #0
	beq	.L2267
	cmp	r4, #1
	beq	.L2262
.L2231:
	add	r4, r4, #1
	cmp	r4, #2
	bne	.L2236
.L2230:
	add	r7, r7, #1
	add	r5, r5, #4
	cmp	r8, r7
	bcs	.L2232
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2266:
	ldr	r1, .L2270+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5]
	b	.L2225
.L2265:
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	str	r4, [r5]
	tst	r0, #255
	bne	.L2235
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L2223
	ldr	r2, [r5]
	b	.L2224
.L2264:
	mov	r1, #1
	ldr	r0, [r0, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r6, #2808]
	bl	BsGet
	strb	r0, [r9, #1]
	ldrh	r3, [r9]
	cmp	r3, #0
	beq	.L2220
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r9, #2]
	cmp	r0, #0
	bne	.L2268
.L2218:
	mov	r1, #4
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r6, #2808]
	bl	BsGet
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2269
.L2219:
	mov	r1, #5
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #12]
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #16]
	ldr	r0, [r6, #2808]
	bl	BsGet
	str	r0, [r9, #20]
	b	.L2220
.L2237:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2269:
	mov	r1, #4
	ldr	r0, [r6, #2808]
	bl	BsGet
	b	.L2219
.L2268:
	mov	r1, #8
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #1
	str	r0, [r9, #4]
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r9, #3]
	ldr	r0, [r6, #2808]
	bl	BsGet
	str	r0, [r9, #8]
	b	.L2218
.L2267:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2239
	mov	r4, #1
.L2262:
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2230
.L2239:
	mov	r10, #0
	b	.L2234
.L2233:
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	ldr	r3, [r5]
	cmp	r3, r10
	bcc	.L2231
.L2234:
	ldr	r1, .L2270+12
	add	r10, r10, #1
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2270+16
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2233
	ldr	r1, .L2270+20
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2270+24
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	b	.L2233
.L2271:
	.align	2
.L2270:
	.word	.LC194
	.word	.LC195
	.word	.LC196
	.word	.LC197
	.word	.LC198
	.word	.LC199
	.word	.LC200
	UNWIND(.fnend)
	.size	HEVC_DecHrdParam, .-HEVC_DecHrdParam
	.align	2
	.type	HEVC_ParseVPSExtension, %function
HEVC_ParseVPSExtension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 672
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #692)
	sub	sp, sp, #692
	mov	r4, #0
	mov	r5, r1
	str	r1, [fp, #-648]
	mov	r2, #64
	mov	r1, r4
	mov	r10, r0
	sub	r0, fp, #496
	str	r4, [fp, #-640]
	str	r4, [fp, #-636]
	bl	memset
	mov	r1, r4
	mov	r2, #128
	sub	r0, fp, #172
	bl	memset
	add	r3, r5, #16384
	mov	r1, r4
	mov	r2, #64
	sub	r0, fp, #432
	mov	r6, r3
	str	r3, [fp, #-656]
	str	r4, [fp, #-632]
	str	r4, [fp, #-628]
	str	r4, [fp, #-624]
	str	r4, [fp, #-620]
	str	r4, [fp, #-608]
	str	r4, [fp, #-604]
	str	r4, [fp, #-600]
	str	r4, [fp, #-596]
	bl	memset
	mov	r1, r4
	mov	r2, #64
	sub	r0, fp, #368
	bl	memset
	mov	r1, r4
	mov	r2, #64
	sub	r0, fp, #304
	bl	memset
	ldr	r3, .L2790
	add	r0, r5, #12416
	mov	r1, r4
	add	r0, r0, #4
	movw	r2, #12492
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r5, #8]
	cmp	r3, #62
	movge	r3, #62
	cmp	r3, #1
	str	r3, [r6, #152]
	bgt	.L2760
	cmp	r3, #0
	ble	.L2275
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2761
.L2275:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	sub	r6, fp, #500
	sub	r4, fp, #436
	mov	r5, #0
	uxtb	r3, r0
	str	r3, [fp, #-664]
.L2276:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	str	r0, [r6, #4]!
	cmp	r0, #0
	addne	r5, r5, #1
	cmp	r6, r4
	bne	.L2276
	ldr	r3, [fp, #-664]
	adds	r6, r3, #0
	movne	r6, #1
	rsb	r9, r6, r5
	cmp	r9, #0
	subgt	r8, fp, #304
	movgt	r7, #0
	ble	.L2281
.L2280:
	mov	r1, #3
	ldr	r0, [r10, #2808]
	bl	BsGet
	add	r7, r7, #1
	cmp	r7, r9
	add	r0, r0, #1
	str	r0, [r8], #4
	bne	.L2280
.L2281:
	cmp	r5, #0
	addge	r7, r5, #1
	subge	lr, fp, #432
	movge	ip, #0
	movge	r8, #6
	blt	.L2279
.L2289:
	cmp	r5, ip
	movne	r2, #0
	andeq	r2, r6, #1
	cmp	r2, #0
	strne	r8, [lr]
	bne	.L2286
	cmp	ip, #0
	subgt	r0, fp, #304
	ldrgt	r1, [lr]
	ble	.L2286
.L2287:
	add	r2, r2, #1
	ldr	r3, [r0], #4
	cmp	r2, ip
	add	r3, r3, #1
	add	r1, r1, r3
	bne	.L2287
	str	r1, [lr]
.L2286:
	add	ip, ip, #1
	add	lr, lr, #4
	cmp	ip, r7
	bne	.L2289
.L2279:
	cmp	r6, #0
	beq	.L2283
	sub	r3, r5, #1
	sub	r2, fp, #44
	add	r3, r2, r3, lsl #2
	ldr	r2, [r3, #-388]
	rsb	r2, r2, #5
	str	r2, [r3, #-260]
.L2283:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	uxtb	r3, r0
	str	r3, [fp, #-672]
	ldr	r3, [fp, #-648]
	ble	.L2762
	add	r2, r3, #16384
	add	r9, r3, #12288
	str	r9, [fp, #-668]
	mov	r1, r2
	mov	r2, #1
	mov	r8, r2
	mov	r6, r2
	add	r1, r1, #176
	str	r1, [fp, #-660]
	sub	r1, fp, #112
	str	r1, [fp, #-652]
.L2297:
	ldr	r3, [fp, #-672]
	cmp	r3, #0
	bne	.L2763
	ldr	r3, [fp, #-660]
	mov	r0, r6
	str	r6, [r3]
.L2294:
	ldr	r2, [fp, #-664]
	add	r3, r0, #1024
	add	r3, r3, #12
	cmp	r2, #0
	ldr	r2, [fp, #-668]
	add	r3, r2, r3, lsl #2
	str	r6, [r3, #132]
	beq	.L2295
	cmp	r5, #0
	ble	.L2299
	ldr	r7, [fp, #-432]
	sub	lr, fp, #432
	ldr	ip, [fp, #-652]
	mov	r2, #0
.L2301:
	ldr	r1, [lr, #4]!
	add	r2, r2, #1
	cmp	r2, r5
	mov	r3, r8, asl r1
	sub	r3, r3, #1
	and	r3, r3, r0
	mov	r3, r3, asr r7
	mov	r7, r1
	str	r3, [ip, #4]!
	bne	.L2301
.L2299:
	ldr	r3, [fp, #-656]
	add	r6, r6, #1
	ldr	r2, [fp, #-652]
	ldr	r3, [r3, #152]
	add	r2, r2, #64
	str	r2, [fp, #-652]
	cmp	r3, r6
	ldr	r2, [fp, #-660]
	add	r2, r2, #4
	str	r2, [fp, #-660]
	bge	.L2297
	ldr	r9, [fp, #-668]
.L2298:
	mov	r1, #4
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	str	r3, [fp, #-652]
	str	r0, [fp, #-660]
	blt	.L2764
	ldr	r3, [fp, #-648]
	mov	r7, #1
	mov	r5, #0
	add	r8, r3, #16384
	ldr	r3, [fp, #-496]
	add	r8, r8, #168
	str	r8, [fp, #-664]
	str	r3, [fp, #-668]
	ldr	r3, [fp, #-652]
	add	r3, r3, #1
	str	r3, [fp, #-676]
.L2308:
	ldr	r3, [fp, #-664]
	sub	r2, fp, #496
	str	r2, [fp, #-672]
	mov	lr, r5, asl #4
	ldr	r2, [fp, #-668]
	sub	r1, fp, #368
	ldr	r6, [r3, #4]!
	mov	r0, #0
	mov	ip, r2
	str	r3, [fp, #-664]
	mov	r6, r6, asl #2
	sub	r3, fp, #44
	add	r3, r3, r6
	str	r2, [r3, #-596]
	ldr	r2, [fp, #-672]
	b	.L2304
.L2765:
	ldr	ip, [r2, #4]!
.L2304:
	add	r3, lr, r0
	cmp	ip, #0
	sub	ip, fp, #44
	addne	r0, r0, #1
	add	r3, ip, r3, lsl #2
	add	r1, r1, #4
	ldrne	r3, [r3, #-128]
	strne	r3, [r1, #-4]
	cmp	r2, r4
	bne	.L2765
	ldr	r0, [fp, #-364]
	sub	r3, fp, #44
	add	r6, r3, r6
	cmp	r5, #0
	str	r0, [r6, #-596]
	ble	.L2305
	mov	ip, r8
	mov	r2, #0
	mov	r1, #1
.L2307:
	ldr	r3, [ip, #4]!
	sub	lr, fp, #44
	add	r2, r2, #1
	add	r3, lr, r3, lsl #2
	ldr	r3, [r3, #-596]
	cmp	r0, r3
	moveq	r1, #0
	cmp	r2, r5
	bne	.L2307
	cmp	r1, #0
	addne	r7, r7, #1
.L2305:
	ldr	r3, [fp, #-676]
	add	r5, r5, #1
	cmp	r5, r3
	bne	.L2308
	ldr	r3, [fp, #-660]
	cmp	r3, #0
	ble	.L2309
	cmp	r7, #0
	ble	.L2309
.L2310:
	ldr	r3, [fp, #-648]
	mov	r5, #0
	add	r4, r3, #16384
	add	r4, r4, #160
.L2314:
	ldr	r1, [fp, #-660]
	add	r5, r5, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r7, r5
	str	r0, [r4, #4]!
	bgt	.L2314
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #152]
	str	r3, [fp, #-652]
.L2309:
	ldr	r3, [fp, #-652]
	cmp	r3, #0
	ble	.L2319
	ldr	r3, [fp, #-648]
	add	r5, r3, #12416
	add	r2, r3, #16384
	add	r2, r2, #172
	str	r2, [fp, #-672]
	mov	r3, r5
	add	r5, r5, #11
	add	r3, r3, #10
	str	r2, [fp, #-664]
	str	r3, [fp, #-660]
	mov	r3, #1
	str	r3, [fp, #-652]
.L2318:
	ldr	r3, [fp, #-652]
	cmp	r3, #0
	ldr	r3, [fp, #-664]
	ldr	r2, [r3, #4]!
	str	r2, [fp, #-668]
	str	r3, [fp, #-664]
	ble	.L2552
	ldr	r7, [fp, #-672]
	mov	r6, r2, asl #1
	ldr	r4, [fp, #-660]
	mov	r8, #0
.L2317:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	add	r3, r6, r8
	add	r3, r3, #1040
	add	r7, r7, #4
	add	r3, r3, #4
	add	r3, r9, r3, lsl #2
	uxtb	r0, r0
	strb	r0, [r4, #1]!
	cmp	r0, #0
	addne	r8, r8, #1
	ldrne	r2, [r7, #-4]
	strne	r2, [r3, #132]
	cmp	r5, r4
	bne	.L2317
.L2315:
	ldr	r3, [fp, #-668]
	add	r5, r5, #3
	ldr	r2, [fp, #-652]
	add	r3, r3, #1040
	ldr	r1, [fp, #-660]
	add	r2, r2, #1
	str	r2, [fp, #-652]
	add	r3, r9, r3, lsl #2
	add	r1, r1, #2
	str	r1, [fp, #-660]
	str	r8, [r3, #132]
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #152]
	cmp	r3, r2
	bge	.L2318
.L2319:
	ldr	r3, .L2790
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #608
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	str	r3, [fp, #-652]
	blt	.L2556
	ldr	r3, [fp, #-648]
	mov	r6, #1
	add	r8, r3, #16384
	ldr	r3, [fp, #-652]
	add	r8, r8, #168
	str	r8, [fp, #-660]
	add	r3, r3, #1
	str	r3, [fp, #-668]
	mov	r3, #0
	str	r3, [fp, #-664]
.L2323:
	ldr	r3, [fp, #-660]
	ldr	r2, [r3, #4]!
	str	r3, [fp, #-660]
	add	r3, r2, #1040
	add	r3, r9, r3, lsl #2
	ldr	r4, [r3, #132]
	cmp	r4, #0
	ble	.L2328
	add	lr, r2, #2064
	sub	r3, fp, #44
	mov	r5, r2, asl #1
	add	lr, lr, #10
	add	r2, r3, r2, lsl #3
	ldr	r3, [fp, #-648]
	mov	ip, #0
	str	r8, [fp, #-672]
	add	lr, r3, lr, lsl #3
.L2327:
	ldr	r3, [lr, #4]!
	sub	r8, fp, #44
	sub	r7, fp, #44
	mov	r0, #1
	add	r1, r5, r3
	add	r7, r7, r3, lsl #3
	add	r1, r8, r1, lsl #2
	str	r6, [r1, #-564]
	ldr	r1, [r2, #-564]
	cmp	r1, #0
	bne	.L2325
	ldr	r0, [r7, #-564]
	adds	r0, r0, #0
	movne	r0, #1
.L2325:
	ldr	r1, [r2, #-560]
	sub	r7, fp, #44
	add	r3, r7, r3, lsl #3
	str	r0, [r2, #-564]
	cmp	r1, #0
	mov	r7, #1
	bne	.L2326
	ldr	r7, [r3, #-560]
	adds	r7, r7, #0
	movne	r7, #1
.L2326:
	add	ip, ip, #1
	str	r7, [r2, #-560]
	cmp	ip, r4
	bne	.L2327
	ldr	r8, [fp, #-672]
.L2328:
	ldr	r3, [fp, #-664]
	ldr	r2, [fp, #-668]
	add	r3, r3, #1
	str	r3, [fp, #-664]
	cmp	r3, r2
	bne	.L2323
	ldr	r3, [fp, #-652]
	cmp	r3, #0
	movgt	r4, r8
	movgt	lr, #0
	ble	.L2334
.L2332:
	ldr	ip, [r4, #4]!
	mov	r1, #0
	add	r3, ip, #1
	cmp	r3, #1
	mov	ip, ip, asl #2
	bgt	.L2329
	sub	r2, fp, #608
	add	r0, r2, ip
.L2331:
	ldr	r2, [r0, r3, asl #3]
	add	r3, r3, #1
	cmp	r2, #0
	addne	r1, r1, #1
	cmp	r3, #2
	bne	.L2331
.L2329:
	sub	r3, fp, #44
	add	lr, lr, #1
	add	ip, r3, ip
	ldr	r3, [fp, #-652]
	cmp	lr, r3
	str	r1, [ip, #-588]
	bne	.L2332
.L2334:
	mov	r5, #0
	mov	r0, #1
	mov	r2, r5
.L2333:
	ldr	r3, [r8, #4]!
	sub	r1, fp, #44
	add	ip, r1, r5, lsl #2
	sub	lr, fp, #44
	add	r1, r3, #1040
	add	r3, lr, r3, lsl #2
	add	r1, r9, r1, lsl #2
	ldr	r1, [r1, #132]
	cmp	r1, #0
	bne	.L2336
	ldr	r3, [r3, #-588]
	add	r5, r5, #1
	str	r0, [ip, #-580]
	cmp	r3, #0
	add	r3, r3, #1
	strgt	r3, [ip, #-580]
.L2336:
	ldr	r3, [fp, #-652]
	add	r2, r2, #1
	cmp	r2, r3
	ble	.L2333
	cmp	r5, #1
	ble	.L2556
	ldr	r1, .L2790+4
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	cmp	r0, #1024
	mov	r7, r0
	bge	.L2766
	cmp	r0, #0
	movgt	r3, #0
	movgt	r4, #1
	strgt	r3, [fp, #-652]
	ble	.L2335
.L2344:
	cmp	r5, #1
	ble	.L2345
	sub	r6, fp, #624
	mov	r8, #1
.L2343:
	ldr	r2, [r6, #4]!
	ldr	r0, [r10, #2808]
	add	r2, r2, #1
	cmp	r2, #1
	bls	.L2557
	mov	r3, #0
.L2342:
	add	r3, r3, #1
	cmp	r2, r4, asl r3
	mov	r1, r3
	bhi	.L2342
	add	r8, r8, #1
	bl	BsGet
	cmp	r8, r5
	bne	.L2343
.L2345:
	ldr	r3, [fp, #-652]
	add	r3, r3, #1
	str	r3, [fp, #-652]
	cmp	r7, r3
	bne	.L2344
.L2335:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	uxtb	r3, r0
	cmp	r3, #0
	bne	.L2346
	ldr	r2, [fp, #-656]
	ldr	r1, [r2, #152]
	cmp	r1, #0
	blt	.L2350
	ldr	r0, [fp, #-648]
	add	r1, r1, #1
	add	r2, r0, #16384
	ldr	r0, [r0, #12]
	add	r2, r2, #200
.L2353:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L2353
.L2350:
	ldr	r3, [fp, #-648]
	ldr	r8, [r3, #20]
	cmp	r8, #0
	blt	.L2349
	ldr	r3, [fp, #-648]
	add	r8, r8, #1
	mov	r4, #0
	add	lr, r3, #20480
	add	r6, r3, #8320
	add	lr, lr, #228
	add	r5, r3, #128
.L2352:
	ldr	ip, [r6, #4]!
	cmp	ip, #0
	beq	.L2558
	mov	r2, #0
	mov	r0, r5
	mov	r1, r2
.L2354:
	ldr	r3, [r0, #4]!
	add	r1, r1, #1
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	add	r3, r3, #1040
	add	r3, r3, #2
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r2, r3
	movlt	r2, r3
	cmp	r1, ip
	bne	.L2354
.L2355:
	add	r4, r4, #1
	str	r2, [lr, #4]!
	cmp	r4, r8
	add	r5, r5, #8
	bne	.L2352
.L2349:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L2356
	ldr	r3, [fp, #-656]
	mov	ip, r0
	mov	r1, #7
	ldr	r4, [r3, #152]
	ldr	r3, [fp, #-648]
	cmp	ip, r4
	add	r0, r4, #1
	add	lr, r3, #24576
	add	lr, lr, #236
	bge	.L2370
.L2369:
	add	ip, ip, #1
	cmp	ip, r4
	bgt	.L2366
	mov	r2, lr
	mov	r3, ip
.L2367:
	add	r3, r3, #1
	str	r1, [r2, #4]!
	cmp	r3, r0
	bne	.L2367
.L2366:
	cmp	ip, r4
	add	lr, lr, #12
	blt	.L2369
.L2370:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r1, .L2790+8
	strb	r0, [r9, #134]
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r4, #2
	moveq	r4, #1
	cmp	r0, r4
	str	r0, [fp, #-700]
	blt	.L2375
.L2374:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [fp, #-648]
	sub	r1, fp, #616
	add	r4, r4, #1
	ldr	r3, [r3, #12]
	uxtb	r2, r0
	mov	r0, r10
	bl	HEVC_DecPTL
	ldr	r3, [fp, #-700]
	cmp	r3, r4
	bge	.L2374
.L2375:
	ldr	r3, [fp, #-648]
	ldr	r2, [r3, #20]
	ldr	r3, [fp, #-656]
	add	r2, r7, r2
	add	r2, r2, #1
	cmp	r2, #1
	str	r2, [r3, #148]
	ble	.L2767
	ldr	r1, .L2790+12
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	mov	r1, #2
	mov	r4, r0
	ldr	r0, [r10, #2808]
	bl	BsGet
	movw	r1, #1025
	str	r0, [fp, #-704]
	ldr	r0, [fp, #-656]
	ldr	r3, [r0, #148]
	add	r2, r4, r3
	str	r2, [r0, #156]
	cmp	r2, r1
	bgt	.L2548
	ldr	r1, [fp, #-656]
	cmp	r2, #1
	mvn	r2, #0
	str	r2, [r1, #228]
	ble	.L2377
	ldr	r2, [fp, #-648]
	str	r10, [fp, #-692]
	add	r1, r2, #16384
	add	r0, r2, #12416
	add	r2, r2, #14464
	mov	ip, r1
	add	r1, r1, #232
	str	r1, [fp, #-688]
	add	r1, r0, #14
	str	r1, [fp, #-684]
	add	r1, ip, #224
	str	r1, [fp, #-712]
	add	r2, r2, #14
	ldr	r1, [fp, #-704]
	str	r2, [fp, #-716]
	mov	r2, #0
	sub	r1, r1, #2
	str	r2, [fp, #-696]
	clz	r1, r1
	mov	r2, #1
	mov	r8, r2
	str	r2, [fp, #-672]
	mov	r1, r1, lsr #5
	str	r1, [fp, #-708]
.L2412:
	cmp	r3, #2
	ldr	r1, [fp, #-672]
	movgt	r2, #1
	movle	r2, #0
	cmp	r3, r1
	movgt	r2, #0
	cmp	r2, #0
	beq	.L2378
	sub	r2, r3, #1
	ldr	r3, [fp, #-692]
	cmp	r2, #1
	ldr	r0, [r3, #2808]
	bls	.L2560
	mov	r3, #0
.L2380:
	add	r3, r3, #1
	cmp	r2, r8, asl r3
	mov	r1, r3
	bhi	.L2380
.L2379:
	bl	BsGet
	ldr	r3, [fp, #-688]
	str	r0, [r3]
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #148]
.L2381:
	ldr	r2, [fp, #-672]
	ldr	r1, [fp, #-708]
	cmp	r3, r2
	ldr	r0, [fp, #-672]
	ldrle	r3, [fp, #-688]
	ldrgt	r3, [fp, #-672]
	ldrle	r3, [r3]
	addle	r3, r3, #1
	str	r3, [fp, #-680]
	ldr	r3, [fp, #-648]
	ldr	r2, [r3, #20]
	cmp	r0, r2
	orrgt	r1, r1, #1
	cmp	r1, #0
	mov	r2, r1
	bne	.L2383
	ldr	r1, [fp, #-680]
	add	r1, r3, r1, lsl #2
	add	r1, r1, #8192
	ldr	r3, [r1, #132]
	cmp	r3, #0
	str	r3, [fp, #-676]
	beq	.L2385
	ldr	r3, [fp, #-672]
	ldr	r5, [fp, #-676]
	ldr	r0, [fp, #-704]
	mov	lr, r3, asl #1
	sub	r4, r5, #1
	add	ip, r9, lr
	mov	r3, r2
	b	.L2393
.L2768:
	cmp	r0, #2
	beq	.L2389
	cmp	r0, #0
	addeq	r2, ip, r3
	add	r3, r3, #1
	streqb	r8, [r2, #141]
	cmp	r3, r5
	mov	r2, r3
	bcs	.L2551
.L2393:
	cmp	r0, #1
	bne	.L2768
	add	r6, ip, r3
	rsb	r2, r4, r2
	add	r3, r3, #1
	clz	r2, r2
	cmp	r3, r5
	mov	r2, r2, lsr #5
	strb	r2, [r6, #141]
	mov	r2, r3
	bcc	.L2393
.L2551:
	ldr	r3, [r1, #132]
.L2751:
	str	r3, [fp, #-676]
.L2385:
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #156]
	cmp	r3, #0
	str	r3, [fp, #-668]
	beq	.L2399
	ldr	r3, [fp, #-648]
	ldr	r10, [fp, #-716]
	add	r3, r3, #132
	str	r3, [fp, #-652]
	ldr	r3, [fp, #-712]
	str	r3, [fp, #-664]
	mov	r3, #0
	str	r3, [fp, #-660]
.L2398:
	ldr	r3, [fp, #-664]
	ldr	r2, [fp, #-648]
	ldr	r7, [r3, #4]!
	str	r3, [fp, #-664]
	add	r3, r7, #2080
	add	r3, r3, #1
	add	r3, r2, r3, lsl #2
	ldr	r6, [r3, #4]
	cmp	r6, #0
	beq	.L2402
	add	r7, r7, #17
	ldr	r3, [fp, #-648]
	sub	r5, r10, #2048
	ldr	r4, [fp, #-652]
	sub	r5, r5, #2
	add	r7, r3, r7, lsl #3
	mov	r0, r10
	mov	lr, #0
.L2401:
	mov	r3, #0
	strb	r3, [r0, #1]!
	ldrb	r3, [r5, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2403
	cmp	lr, #0
	strb	r8, [r0]
	ldr	r3, [r4]
	beq	.L2403
	add	r3, r3, #1024
	add	r2, r10, #1
	add	r3, r3, #12
	mov	r1, r7
	add	r3, r9, r3, lsl #2
	ldr	ip, [r3, #132]
	add	ip, r9, ip, lsl #1
.L2405:
	ldr	r3, [r1, #4]!
	add	r2, r2, #1
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	add	r3, ip, r3
	ldrb	r3, [r3, #137]	@ zero_extendqisi2
	cmp	r3, #0
	strneb	r8, [r2, #-1]
	cmp	r0, r2
	bne	.L2405
.L2403:
	add	lr, lr, #1
	add	r4, r4, #4
	cmp	lr, r6
	bne	.L2401
.L2402:
	ldr	r3, [fp, #-660]
	add	r10, r10, #2
	ldr	r2, [fp, #-668]
	add	r3, r3, #1
	str	r3, [fp, #-660]
	cmp	r3, r2
	ldr	r3, [fp, #-652]
	add	r3, r3, #8
	str	r3, [fp, #-652]
	bne	.L2398
.L2399:
	ldr	r3, [fp, #-676]
	cmp	r3, #0
	beq	.L2396
	ldr	r2, [fp, #-672]
	mov	r10, #0
	ldr	r3, [fp, #-676]
	ldr	r1, [fp, #-680]
	add	r3, r3, r2, lsl #1
	ldr	r2, [fp, #-648]
	add	r3, r3, #12416
	ldr	ip, [fp, #-696]
	add	r0, r2, r1, lsl #3
	add	r3, r3, #12
	ldr	r1, [fp, #-684]
	add	r0, r0, #132
	add	r2, r2, r3
.L2407:
	ldrb	r3, [r1, #1]!	@ zero_extendqisi2
	add	r0, r0, #4
	cmp	r3, #0
	addne	r10, r10, #1
	ldrne	ip, [r0, #-4]
	cmp	r1, r2
	bne	.L2407
	ldr	r3, [fp, #-680]
	mov	r5, #0
	str	r10, [fp, #-652]
	add	r7, r3, #2080
	ldr	r3, [fp, #-684]
	str	r9, [fp, #-660]
	add	r6, r3, #2048
	ldr	r3, [fp, #-700]
	add	r6, r6, #2
	str	ip, [fp, #-696]
	add	r4, r3, #1
	ldr	r3, [fp, #-648]
	add	r7, r3, r7, lsl #2
	mov	r9, r3
	mov	r10, r7
	ldr	r7, [fp, #-692]
.L2411:
	ldrb	r1, [r6, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L2408
	ldr	r1, [r9, #20]
	cmp	r1, #0
	ble	.L2408
	cmp	r4, #1
	ldr	r0, [r7, #2808]
	bls	.L2562
	mov	ip, #0
.L2410:
	add	ip, ip, #1
	cmp	r4, r8, asl ip
	mov	r1, ip
	bhi	.L2410
.L2409:
	bl	BsGet
.L2408:
	ldr	r1, [r10, #4]
	add	r5, r5, #1
	cmp	r5, r1
	bcc	.L2411
	ldr	r10, [fp, #-652]
	ldr	r9, [fp, #-660]
	cmp	r10, #1
	beq	.L2769
.L2396:
	ldr	r1, [fp, #-656]
	ldr	r2, [fp, #-672]
	ldr	r0, [fp, #-688]
	ldr	r3, [r1, #156]
	add	r2, r2, #1
	add	r0, r0, #4
	str	r0, [fp, #-688]
	cmp	r3, r2
	ldr	r0, [fp, #-684]
	str	r2, [fp, #-672]
	add	r0, r0, #2
	str	r0, [fp, #-684]
	ble	.L2746
	ldr	r3, [r1, #148]
	b	.L2412
.L2557:
	mov	r1, #0
	add	r8, r8, #1
	bl	BsGet
	cmp	r8, r5
	bne	.L2343
	b	.L2345
.L2295:
	cmp	r5, #0
	ble	.L2299
	ldr	r9, [fp, #-652]
	ldr	r7, [fp, #-664]
.L2300:
	sub	r3, fp, #304
	ldr	r0, [r10, #2808]
	ldr	r1, [r3, r7, asl #2]
	add	r7, r7, #1
	bl	BsGet
	cmp	r7, r5
	str	r0, [r9, #4]!
	bne	.L2300
	b	.L2299
.L2763:
	mov	r1, #6
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [fp, #-660]
	str	r0, [r3]
	b	.L2294
.L2552:
	mov	r8, #0
	b	.L2315
.L2378:
	ldr	r1, [fp, #-688]
	str	r2, [r1]
	b	.L2381
.L2383:
	ldr	r2, [fp, #-680]
	ldr	r3, [fp, #-648]
	add	r4, r3, r2, lsl #2
	add	r4, r4, #8192
	ldr	r3, [r4, #132]
	cmp	r3, #0
	str	r3, [fp, #-676]
	beq	.L2385
	ldr	r6, [fp, #-684]
	mov	r5, #0
	ldr	r7, [fp, #-692]
.L2386:
	mov	r1, #1
	ldr	r0, [r7, #2808]
	bl	BsGet
	add	r5, r5, #1
	strb	r0, [r6, #1]!
	ldr	r3, [r4, #132]
	cmp	r5, r3
	bcc	.L2386
	str	r3, [fp, #-676]
	b	.L2385
.L2389:
	add	lr, lr, #12416
	ldr	r0, [fp, #-676]
	add	lr, lr, #12
.L2550:
	ldr	ip, [fp, #-648]
	add	r2, lr, r3
	add	r2, ip, r2
	ldr	ip, [fp, #-672]
	orrs	ip, r3, ip
	add	r3, r3, #1
	bne	.L2391
.L2770:
	cmp	r3, r0
	strb	r8, [r2, #1]!
	bcs	.L2551
	ldr	ip, [fp, #-672]
	orrs	ip, r3, ip
	add	r3, r3, #1
	beq	.L2770
.L2391:
	cmp	r3, r0
	bcc	.L2550
	ldr	r3, [r1, #132]
	b	.L2751
.L2562:
	mov	r1, #0
	b	.L2409
.L2769:
	ldr	r3, [fp, #-696]
	add	r3, r3, #1040
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, #0
	ble	.L2396
	ldr	r3, [fp, #-692]
	mov	r1, r10
	ldr	r0, [r3, #2808]
	bl	BsGet
	b	.L2396
.L2746:
	ldr	r10, [fp, #-692]
.L2377:
	ldr	r1, .L2790+16
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-656]
	cmp	r0, #255
	mov	r2, r0
	str	r0, [r3, #160]
	bhi	.L2545
	ldr	r3, [fp, #-648]
	mov	r5, #0
	add	r7, r3, #24576
	add	r7, r7, #252
	mov	r6, r7
	b	.L2426
.L2415:
	mov	r1, #16
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #4]
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #8]
	ldr	r0, [r10, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L2771
	cmp	r8, #0
	beq	.L2420
	ldr	r3, [r8, #12]
	str	r3, [r4, #12]
	ldrb	r3, [r8]	@ zero_extendqisi2
	strb	r3, [r4]
	ldr	r3, [r8, #16]
	str	r3, [r4, #16]
	ldr	r3, [r8, #20]
	str	r3, [r4, #20]
.L2420:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L2772
	str	r0, [r4, #24]
	str	r0, [r4, #28]
	str	r0, [r4, #32]
	str	r0, [r4, #36]
.L2422:
	ldr	r2, [r4, #16]
	ldr	r3, [r4, #20]
	cmp	r2, #8
	bhi	.L2424
	cmp	r3, #8
	bls	.L2425
.L2424:
	ldr	r1, .L2790+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #16]
	str	r3, [r4, #20]
.L2425:
	ldr	r3, [fp, #-656]
	add	r5, r5, #1
	add	r6, r6, #40
	ldr	r2, [r3, #160]
	cmp	r5, r2
	bhi	.L2773
.L2426:
	cmp	r5, #1
	subgt	r4, fp, #592
	movgt	r8, r7
	bgt	.L2415
	cmp	r5, #0
	mov	r4, r6
	subne	r8, r6, #40
	moveq	r8, r5
	b	.L2415
.L2772:
	ldr	r1, .L2790+24
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2790+28
	str	r0, [r4, #24]
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2790+32
	str	r0, [r4, #28]
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2790+36
	str	r0, [r4, #32]
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	str	r0, [r4, #36]
	b	.L2422
.L2791:
	.align	2
.L2790:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC202
	.word	.LC204
	.word	.LC205
	.word	.LC230
	.word	.LC212
	.word	.LC208
	.word	.LC209
	.word	.LC210
	.word	.LC211
	.word	.LC216
	.word	.LC214
	.word	.LC215
	.word	.LC213
	.word	.LC217
	.word	.LC206
	.word	.LC218
	.word	.LC219
	.word	.LC201
	.word	.LC220
	.word	.LC222
	.word	.LC223
	.word	.LC224
	.word	.LC226
	.word	.LC227
	.word	.LC229
	.word	.LC228
	.word	.LC231
	.word	.LC225
	.word	.LC221
	.word	.LC203
	.word	.LANCHOR0+616
	.word	.LC207
.L2771:
	mov	r1, #2
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r0, #3
	str	r0, [r4, #12]
	beq	.L2774
	cmp	r8, #0
	streqb	r8, [r4]
	ldrneb	r3, [r8]	@ zero_extendqisi2
	strneb	r3, [r4]
.L2418:
	mov	r1, #4
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #4
	str	r0, [r4, #16]
	ldr	r0, [r10, #2808]
	bl	BsGet
	str	r0, [r4, #20]
	b	.L2420
.L2773:
	cmp	r2, #0
	bne	.L2775
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ble	.L2430
.L2546:
	ldr	r1, [fp, #-648]
	add	r0, r1, #16384
	mov	r1, #0
	add	r0, r0, #184
	mov	ip, r1
.L2429:
	add	r1, r1, #1
	str	ip, [r0, #4]!
	cmp	r1, r3
	blt	.L2429
.L2428:
	cmp	r2, #0
	beq	.L2430
	ldr	r2, [fp, #-656]
	adds	r4, r3, #0
	movne	r4, #1
	ldr	r2, [r2, #152]
	cmp	r4, r2
	bgt	.L2437
	add	r6, r4, #4096
	ldr	r3, [fp, #-648]
	add	r6, r6, #46
	ldr	r7, [fp, #-656]
	mov	r5, #1
	add	r6, r3, r6, lsl #2
.L2436:
	ldr	r2, [r7, #160]
	ldr	r0, [r10, #2808]
	add	r2, r2, #1
	cmp	r2, #1
	bls	.L2564
	mov	r3, #0
.L2435:
	add	r3, r3, #1
	cmp	r2, r5, asl r3
	mov	r1, r3
	bhi	.L2435
.L2434:
	bl	BsGet
	add	r4, r4, #1
	str	r0, [r6, #4]!
	ldr	r3, [r7, #152]
	cmp	r3, r4
	bge	.L2436
.L2437:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #133]
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	ble	.L2433
	ldr	r3, [fp, #-648]
	mov	r6, #1
	ldr	r7, [fp, #-656]
	add	r5, r3, #16384
	add	r4, r3, #12416
	add	r5, r5, #172
	add	r4, r4, #8
	b	.L2442
.L2441:
	ldr	r3, [r7, #152]
	add	r4, r4, #1
	cmp	r3, r6
	blt	.L2433
.L2442:
	ldr	r3, [r5, #4]!
	add	r6, r6, #1
	add	r3, r3, #1040
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, #0
	bne	.L2441
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	add	r4, r4, #1
	strb	r0, [r4, #-1]
	ldr	r3, [r7, #152]
	cmp	r3, r6
	bge	.L2442
.L2433:
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #156]
	cmp	r3, #1
	bls	.L2440
	ldr	r3, [fp, #-648]
	str	r9, [fp, #-652]
	add	r2, r3, #14464
	add	r1, r3, #16384
	mov	r7, r3
	add	r2, r2, #16
	str	r2, [fp, #-668]
	add	r2, r1, #232
	str	r2, [fp, #-684]
	mov	r2, #1
	str	r2, [fp, #-680]
.L2454:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [fp, #-656]
	ldr	r2, [fp, #-680]
	mov	r6, #0
	ldr	r3, [r3, #148]
	cmp	r3, r2
	ldrls	r3, [fp, #-684]
	ldrhi	r3, [fp, #-680]
	ldrls	r3, [r3]
	addls	r3, r3, #1
	add	r1, r3, #2064
	add	r2, r7, r3, lsl #3
	add	r3, r7, r3, lsl #2
	add	r2, r2, #132
	str	r3, [fp, #-672]
	str	r2, [fp, #-676]
	add	r2, r1, #8
	str	r2, [fp, #-664]
	adds	r0, r0, #0
	movne	r0, #1
	str	r0, [fp, #-660]
.L2453:
	ldr	r3, [fp, #-660]
	cmp	r6, #0
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	clzeq	r0, r6
	moveq	r0, r0, lsr #5
	bne	.L2776
.L2447:
	cmp	r0, #0
	beq	.L2448
	ldr	r3, [fp, #-672]
	add	r9, r3, #8192
	ldr	r1, [r9, #132]
	cmp	r1, #0
	beq	.L2452
	ldr	r5, [fp, #-676]
	mov	r4, #0
	ldr	r8, [fp, #-668]
.L2449:
	ldrb	r3, [r8, #1]!	@ zero_extendqisi2
	add	r4, r4, #1
	cmp	r3, #0
	beq	.L2450
	ldrb	r3, [r7, #3]	@ zero_extendqisi2
	ldr	r1, .L2790+40
	cmp	r3, #0
	bne	.L2451
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L2450
.L2451:
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
.L2450:
	ldr	r3, [r9, #132]
	add	r5, r5, #4
	cmp	r4, r3
	bcc	.L2449
.L2452:
	ldr	r1, .L2790+44
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2790+48
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
.L2448:
	ldr	r2, [fp, #-664]
	add	r6, r6, #1
	ldr	r3, [fp, #-652]
	add	r3, r3, r2, lsl #2
	ldr	r3, [r3, #136]
	cmp	r6, r3
	bls	.L2453
	ldr	r3, [fp, #-656]
	ldr	r2, [fp, #-680]
	ldr	r1, [fp, #-668]
	ldr	r3, [r3, #156]
	add	r2, r2, #1
	add	r1, r1, #2
	str	r1, [fp, #-668]
	cmp	r2, r3
	ldr	r1, [fp, #-684]
	str	r2, [fp, #-680]
	add	r1, r1, #4
	str	r1, [fp, #-684]
	bcc	.L2454
	ldr	r9, [fp, #-652]
.L2440:
	ldr	r1, .L2790+52
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	mov	r1, #1
	mov	r6, r0
	ldr	r0, [r10, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L2777
	ldr	r1, [fp, #-648]
	ldr	r2, [fp, #-656]
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	ldr	r2, [r2, #152]
	cmp	r3, #0
	movne	r8, #1
	moveq	r8, #2
	cmp	r8, r2
	bgt	.L2455
	mov	r5, r8, asl #1
	add	r6, r6, #2
	add	r7, r5, r8
	add	r7, r7, #12416
	add	r7, r7, #8
	add	r7, r1, r7
.L2464:
	clz	r3, r3
	mov	r3, r3, lsr #5
	cmp	r3, r8
	bge	.L2463
	add	r2, r5, #12416
	add	r2, r2, #8
	add	r3, r2, r3
	ldr	r2, [fp, #-648]
	add	r4, r2, r3
	b	.L2462
.L2461:
	cmp	r7, r4
	beq	.L2463
.L2462:
	ldrb	r3, [r4, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2461
	mov	r1, r6
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r7, r4
	bne	.L2462
.L2463:
	ldr	r3, [fp, #-656]
	add	r8, r8, #1
	add	r7, r7, #3
	add	r5, r5, #2
	ldr	r3, [r3, #152]
	cmp	r3, r8
	blt	.L2455
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	b	.L2464
.L2776:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	b	.L2447
.L2777:
	add	r1, r6, #2
	ldr	r0, [r10, #2808]
	bl	BsGet
.L2455:
	ldr	r1, .L2790+56
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	subs	r5, r0, #0
	movgt	r4, #1
	ble	.L2468
.L2467:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r5, r4
	bge	.L2467
.L2468:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L2778
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2558:
	mov	r2, ip
	b	.L2355
.L2564:
	mov	r1, #0
	b	.L2434
.L2430:
	ldr	r0, [fp, #-656]
	adds	r3, r3, #0
	movne	r3, #1
	ldr	r1, [r0, #152]
	cmp	r3, r1
	bgt	.L2437
	add	r2, r3, #4096
	ldr	ip, [fp, #-648]
	add	r2, r2, #46
	ldr	r0, [r0, #160]
	add	r1, r1, #1
	add	r2, ip, r2, lsl #2
.L2438:
	cmp	r3, r0
	movcc	ip, r3
	add	r3, r3, #1
	movcs	ip, r0
	cmp	r3, r1
	str	ip, [r2, #4]!
	bne	.L2438
	b	.L2437
.L2767:
	movw	r3, #1025
	cmp	r2, r3
	ldr	r3, [fp, #-656]
	str	r2, [r3, #156]
	mvnle	r3, #0
	ldrle	r2, [fp, #-656]
	strle	r3, [r2, #228]
	ble	.L2377
	mov	r3, r2
	mov	r4, #0
.L2548:
	str	r3, [sp, #12]
	movw	r1, #1025
	str	r2, [sp]
	movw	r3, #1635
	str	r1, [sp, #4]
	mov	r0, #1
	str	r4, [sp, #8]
	ldr	r2, .L2790+124
	ldr	r1, .L2790+60
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2774:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	strb	r0, [r4]
	b	.L2418
.L2556:
	mov	r7, #0
	b	.L2335
.L2356:
	ldr	r1, [fp, #-648]
	mov	r8, #7
	ldr	r0, [fp, #-656]
	add	r3, r1, #24576
	str	r10, [fp, #-660]
	str	r7, [fp, #-664]
	mov	r7, r1
	mov	r2, r3
	ldr	r3, [r0, #152]
	add	r2, r2, #240
	str	r2, [fp, #-652]
	mov	r2, #0
	str	r9, [fp, #-668]
	mov	r10, r2
	cmp	r10, r3
	mov	r9, r0
	bge	.L2779
.L2363:
	add	r10, r10, #1
	cmp	r10, r3
	bgt	.L2359
	sub	r6, r10, #1
	ldr	r5, [fp, #-652]
	mov	r4, r10
	b	.L2362
.L2361:
	ldr	r3, [r9, #152]
	add	r4, r4, #1
	add	r5, r5, #4
	cmp	r3, r4
	blt	.L2359
.L2362:
	add	r3, r6, r4, lsl #1
	add	r3, r3, #12416
	add	r3, r3, #9
	ldrb	r3, [r7, r3]	@ zero_extendqisi2
	cmp	r3, #0
	streq	r8, [r5]
	beq	.L2361
	ldr	r3, [fp, #-660]
	mov	r1, #3
	ldr	r0, [r3, #2808]
	bl	BsGet
	str	r0, [r5]
	b	.L2361
.L2359:
	ldr	r2, [fp, #-652]
	cmp	r10, r3
	add	r2, r2, #12
	str	r2, [fp, #-652]
	blt	.L2363
.L2779:
	ldr	r7, [fp, #-664]
	ldr	r10, [fp, #-660]
	ldr	r9, [fp, #-668]
	b	.L2370
.L2346:
	ldr	r6, [fp, #-656]
	ldr	r3, [r6, #152]
	cmp	r3, #0
	blt	.L2350
	ldr	r3, [fp, #-648]
	mov	r5, #0
	add	r4, r3, #16384
	add	r4, r4, #200
.L2351:
	mov	r1, #3
	ldr	r0, [r10, #2808]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r4, #4]!
	ldr	r3, [r6, #152]
	cmp	r3, r5
	bge	.L2351
	b	.L2350
.L2778:
	ldr	r0, [r10, #2808]
	bl	BsToNextByte
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r0, #0
	beq	.L2780
.L2470:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #1
	mov	r6, r0
	ldr	r0, [r10, #2808]
	bl	BsGet
	orrs	r3, r0, r6
	mov	r7, r0
	beq	.L2472
	ldr	r3, [fp, #-648]
	ldrb	r4, [r3, #3]	@ zero_extendqisi2
	ldr	r3, [r3, #20]
	clz	r4, r4
	mov	r4, r4, lsr #5
	cmp	r4, r3
	bhi	.L2472
	mov	r5, #0
	str	r5, [fp, #-652]
	mov	r8, r5
	mov	r5, r4
	ldr	r4, [fp, #-648]
	str	r9, [fp, #-660]
.L2479:
	mov	r9, #0
	b	.L2478
.L2474:
	cmp	r7, #0
	bne	.L2781
.L2475:
	ldr	r3, [fp, #-652]
	cmp	r3, #0
	bne	.L2782
.L2476:
	cmp	r8, #0
	bne	.L2783
.L2477:
	ldr	r3, [r4, #12]
	cmp	r9, r3
	bhi	.L2784
.L2478:
	cmp	r6, #0
	add	r9, r9, #1
	beq	.L2474
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r7, #0
	str	r0, [fp, #-652]
	beq	.L2475
.L2781:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [fp, #-652]
	cmp	r3, #0
	mov	r8, r0
	beq	.L2476
.L2782:
	mov	r1, #16
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r8, #0
	beq	.L2477
.L2783:
	mov	r1, #2
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #2
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [r4, #12]
	cmp	r9, r3
	bls	.L2478
.L2784:
	ldr	r3, [r4, #20]
	add	r5, r5, #1
	cmp	r5, r3
	bls	.L2479
	ldr	r9, [fp, #-660]
.L2472:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	subs	r6, r0, #0
	bne	.L2785
	ldr	r3, [fp, #-656]
	ldr	r4, [r3, #152]
.L2481:
	mov	r5, #0
.L2482:
	mov	r1, #3
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r10, #2808]
	add	r5, r5, r1
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r5, r4
	bls	.L2482
	cmp	r4, #0
	cmpne	r6, #0
	beq	.L2483
	ldr	r3, [fp, #-648]
	ldr	r5, [fp, #-656]
	ldrb	r4, [r3, #3]	@ zero_extendqisi2
	ldr	r3, [r5, #152]
	clz	r4, r4
	mov	r4, r4, lsr #5
	cmp	r4, r3
	bhi	.L2483
.L2484:
	mov	r1, #4
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [r5, #152]
	add	r4, r4, #1
	cmp	r4, r3
	bls	.L2484
.L2483:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r0, #0
	bne	.L2547
	sub	r6, fp, #644
	mov	r4, r0
	mov	r5, r6
.L2486:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	add	r4, r4, #1
	uxtb	r0, r0
	strb	r0, [r5], #1
	cmp	r0, #0
	beq	.L2485
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
.L2485:
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #152]
	cmp	r4, r3
	bls	.L2486
	cmp	r3, #0
	beq	.L2547
	ldr	r3, [fp, #-648]
	mov	r7, #1
	add	r5, r3, #16384
	add	r5, r5, #172
.L2488:
	ldr	r2, [r5, #4]!
	add	r3, r2, #1040
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, #0
	beq	.L2491
	ldrb	r8, [r6, r7]	@ zero_extendqisi2
	mov	r4, #0
	b	.L2490
.L2489:
	add	r3, r2, #1040
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r4, r3
	bcs	.L2491
.L2490:
	add	r3, r4, r2, lsl #1
	cmp	r8, #0
	add	r3, r3, #1040
	add	r4, r4, #1
	add	r3, r3, #4
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	beq	.L2489
	sub	r1, fp, #44
	add	r3, r1, r3
	ldrb	r3, [r3, #-600]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2489
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r2, [r5]
	b	.L2489
.L2491:
	ldr	r3, [fp, #-656]
	add	r7, r7, #1
	ldr	r3, [r3, #152]
	cmp	r7, r3
	bls	.L2488
.L2547:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r0, #0
	beq	.L2492
.L2496:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r0, #0
	beq	.L2494
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	beq	.L2494
	ldr	r3, [fp, #-648]
	mov	r5, #1
	mov	r7, #0
	add	r6, r3, #16384
	add	r6, r6, #172
	mov	r8, r3
.L2497:
	ldr	r3, [r6, #4]!
	add	r2, r3, #1040
	add	r2, r9, r2, lsl #2
	ldr	r2, [r2, #132]
	cmp	r2, #0
	movne	r4, #0
	bne	.L2503
	b	.L2505
.L2501:
	ldr	r3, [r6]
	add	r2, r3, #1040
	add	r2, r9, r2, lsl #2
	ldr	r2, [r2, #132]
	cmp	r4, r2
	bcs	.L2505
.L2503:
	add	r3, r4, r3, lsl #1
	ldrb	r2, [r8, #3]	@ zero_extendqisi2
	add	r3, r3, #1040
	add	r4, r4, #1
	add	r3, r3, #4
	cmp	r2, #0
	ldr	r1, .L2790+64
	add	r3, r9, r3, lsl #2
	bne	.L2498
	ldr	r3, [r3, #132]
	cmp	r3, #0
	ble	.L2499
.L2498:
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	mov	r7, r0
.L2499:
	cmp	r7, #0
	beq	.L2501
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r0, #0
	beq	.L2501
	ldr	r1, .L2790+68
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	b	.L2501
.L2505:
	ldr	r3, [fp, #-656]
	add	r5, r5, #1
	ldr	r3, [r3, #152]
	cmp	r5, r3
	bls	.L2497
.L2494:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r0, #0
	bne	.L2786
.L2506:
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	beq	.L2544
	ldr	r3, [fp, #-648]
	mov	r5, #1
	ldr	r6, [fp, #-656]
	add	r4, r3, #16384
	add	r4, r4, #172
	b	.L2543
.L2542:
	ldr	r3, [r6, #152]
	cmp	r5, r3
	bhi	.L2544
.L2543:
	ldr	r3, [r4, #4]!
	add	r5, r5, #1
	add	r3, r3, #1040
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, #0
	bne	.L2542
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [r6, #152]
	cmp	r5, r3
	bls	.L2543
.L2544:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2492:
	ldr	r5, [fp, #-656]
	mov	r4, #0
.L2495:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [r5, #152]
	add	r4, r4, #1
	cmp	r4, r3
	bls	.L2495
	b	.L2496
.L2760:
	mov	r0, #1
	ldr	r2, .L2790+124
	str	r0, [sp]
	ldr	r1, .L2790+72
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2786:
	ldr	r1, .L2790+76
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-648]
	ldr	r5, [r3, #24]
	add	r4, r0, r5
	cmp	r4, #1024
	bhi	.L2507
	cmp	r5, r4
	bcc	.L2513
	b	.L2514
.L2788:
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r6, r0
.L2511:
	ldr	r1, .L2790+80
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	uxtb	r2, r6
	sub	r1, fp, #552
	mov	ip, r0
	cmp	ip, #7
	mov	r3, r0
	mov	r0, r10
	bhi	.L2787
	add	r5, r5, #1
	bl	HEVC_DecHrdParam
	cmp	r4, r5
	bls	.L2514
.L2513:
	cmp	r5, #0
	mov	r1, #1
	bne	.L2788
	mov	r6, #1
	b	.L2511
.L2785:
	mov	r1, #4
	ldr	r0, [r10, #2808]
	bl	BsGet
	mov	r4, r0
	b	.L2481
.L2787:
	mov	r0, #7
	mov	r2, r5
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L2790+84
	bl	dprint_vfmw
	b	.L2506
.L2514:
	cmp	r4, #0
	beq	.L2506
	ldr	r3, [fp, #-656]
	ldr	r3, [r3, #156]
	cmp	r3, #1
	bls	.L2506
	ldr	r3, [fp, #-648]
	mov	r8, #1
	str	r9, [fp, #-664]
	mov	r9, r4
	add	r7, r3, #16384
	add	r2, r3, #8320
	add	r7, r7, #232
	add	r3, r2, #4
	str	r3, [fp, #-668]
.L2540:
	ldr	r2, [fp, #-668]
	ldr	r1, .L2790+88
	ldr	r0, [r10, #2808]
	ldr	r3, [r2, #4]!
	cmp	r3, #2
	subhi	r3, r3, #1
	str	r2, [fp, #-668]
	movls	r3, #1
	str	r3, [fp, #-240]
	bl	HEVC_ue_v
	cmp	r0, #16
	bhi	.L2518
	add	r3, r0, #1
	str	r3, [fp, #-672]
	cmp	r3, #1
	bls	.L2529
	sub	r5, fp, #240
	str	r9, [fp, #-660]
	mov	r9, r8
	mov	r8, r7
	add	r3, r5, r0, lsl #2
	str	r3, [fp, #-652]
.L2528:
	ldr	r1, .L2790+92
	mov	r4, r9
	ldr	r0, [r10, #2808]
	mov	r6, #0
	bl	HEVC_ue_v
	ldr	r3, [fp, #-656]
	ldr	ip, [r3, #148]
	str	r0, [r5, #4]!
	mov	r7, r0
	mov	r9, r5
.L2523:
	mov	r5, #0
	mov	r3, r4
	mov	r4, r5
	mov	r5, r3
	b	.L2527
.L2525:
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [fp, #-656]
	ldr	ip, [r3, #148]
.L2527:
	cmp	ip, r5
	mov	r1, r5
	ldr	r3, [fp, #-648]
	ldrls	r1, [r8]
	addls	r1, r1, #1
	add	r0, r1, #2080
	mov	r1, #1
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #4]
	cmp	r4, r0
	add	r4, r4, r1
	bcc	.L2525
	add	r6, r6, r1
	mov	r4, r5
	cmp	r7, r6
	bcs	.L2523
	ldr	r3, [fp, #-652]
	mov	r5, r9
	mov	r9, r4
	cmp	r5, r3
	bne	.L2528
	ldr	r9, [fp, #-660]
	mov	r7, r8
	mov	r8, r4
.L2529:
	ldr	r3, [fp, #-672]
	cmp	r3, #0
	beq	.L2521
	ldr	r3, [fp, #-656]
	mov	r4, #1
	str	r7, [fp, #-676]
	mov	r7, r9
	mov	r9, r8
	ldr	r0, [r3, #148]
	mov	r3, #0
	str	r3, [fp, #-660]
.L2530:
	mov	r8, r7
	mov	r3, #0
	str	r3, [fp, #-652]
.L2539:
	cmp	r0, r9
	ldr	r2, [fp, #-664]
	ldrls	r3, [fp, #-676]
	movhi	r3, r9
	ldrls	r3, [r3]
	addls	r3, r3, #1
	add	r3, r3, #2064
	add	r3, r3, #8
	add	r3, r2, r3, lsl #2
	ldr	r2, [fp, #-652]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	bhi	.L2789
	ldr	r1, .L2790+96
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	cmp	r0, #31
	bhi	.L2531
	add	r2, r0, #1
	str	r2, [fp, #-680]
	ldr	r2, [fp, #-660]
	sub	r3, fp, #240
	mov	r7, #0
	ldr	r6, [r3, r2, asl #2]
.L2532:
	mov	r5, #0
.L2535:
	cmp	r8, #1
	ldr	r0, [r10, #2808]
	bls	.L2570
	mov	r3, #0
.L2534:
	add	r3, r3, #1
	cmp	r8, r4, asl r3
	mov	r1, r3
	bhi	.L2534
.L2533:
	bl	BsGet
	add	r5, r5, #1
	ldr	r1, .L2790+100
	ldr	r0, [r10, #2808]
	bl	HEVC_ue_v
	cmp	r5, r6
	bls	.L2535
	ldr	r3, [fp, #-680]
	add	r7, r7, #1
	cmp	r7, r3
	bne	.L2532
	ldr	r3, [fp, #-656]
	ldr	r0, [r3, #148]
	ldr	r3, [fp, #-652]
	add	r3, r3, #1
	str	r3, [fp, #-652]
	b	.L2539
.L2570:
	mov	r1, #0
	b	.L2533
.L2531:
	ldr	r2, [fp, #-652]
	mov	r8, r9
	str	r0, [sp, #4]
	mov	r0, #1
	ldr	r3, [fp, #-660]
	str	r2, [sp]
	mov	r2, r8
	ldr	r1, .L2790+104
	ldr	r9, [fp, #-664]
	bl	dprint_vfmw
.L2522:
	ldr	r1, .L2790+108
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2506
.L2789:
	ldr	r3, [fp, #-660]
	mov	r7, r8
	ldr	r2, [fp, #-672]
	add	r3, r3, #1
	str	r3, [fp, #-660]
	cmp	r3, r2
	bne	.L2530
	mov	r8, r9
	mov	r9, r7
	ldr	r7, [fp, #-676]
.L2521:
	ldr	r3, [fp, #-656]
	add	r8, r8, #1
	add	r7, r7, #4
	ldr	r3, [r3, #156]
	cmp	r8, r3
	bcc	.L2540
	ldr	r9, [fp, #-664]
	b	.L2506
.L2775:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	uxtb	r2, r0
	bgt	.L2546
	b	.L2428
.L2780:
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	cmp	r0, #0
	beq	.L2470
	mov	r1, #1
	ldr	r0, [r10, #2808]
	bl	BsGet
	b	.L2470
.L2518:
	mov	r3, r0
	mov	r2, r8
	mov	r0, #16
	ldr	r1, .L2790+112
	str	r0, [sp]
	mov	r0, #1
	ldr	r9, [fp, #-664]
	bl	dprint_vfmw
	b	.L2522
.L2507:
	mov	r2, r4
	mov	r3, #1024
	ldr	r1, .L2790+116
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2506
.L2766:
	str	r0, [sp]
	mov	r2, #1024
	movw	r3, #1537
	str	r2, [sp, #4]
	ldr	r1, .L2790+120
	mov	r0, #1
	ldr	r2, .L2790+124
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2764:
	ldr	r3, [fp, #-660]
	cmp	r3, #0
	movgt	r7, #1
	bgt	.L2310
	b	.L2309
.L2560:
	mov	r1, #0
	b	.L2379
.L2762:
	add	r9, r3, #12288
	b	.L2298
.L2761:
	ldr	r3, [fp, #-648]
	mov	r2, r4
	sub	r1, fp, #616
	mov	r0, r10
	ldr	r3, [r3, #12]
	bl	HEVC_DecPTL
	b	.L2275
.L2545:
	ldr	r1, .L2790+128
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ParseVPSExtension, .-HEVC_ParseVPSExtension
	.align	2
	.global	HEVC_ProcessVPS
	.type	HEVC_ProcessVPS, %function
HEVC_ProcessVPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
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
	mov	r6, r0
	mov	r5, r1
	ldr	r0, [r0, #2808]
	mov	r1, #1
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #3]
	ldr	r0, [r6, #2808]
	bl	BsGet
	uxtb	r2, r0
	cmp	r2, #1
	beq	.L2793
	ldr	r1, .L2858
	mov	r0, #1
	bl	dprint_vfmw
.L2793:
	mov	r1, #6
	ldr	r0, [r6, #2808]
	bl	BsGet
	cmp	r0, #63
	str	r0, [r5, #8]
	bhi	.L2847
	mov	r1, #3
	ldr	r0, [r6, #2808]
	bl	BsGet
	cmp	r0, #7
	str	r0, [fp, #-104]
	bhi	.L2848
	ldr	r3, [fp, #-104]
	mov	r1, #1
	str	r3, [r5, #12]
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r5, #1]
	ldr	r0, [r6, #2808]
	bl	BsGet
	movw	r3, #65535
	cmp	r0, r3
	bne	.L2849
	ldr	r3, [fp, #-104]
	mov	r2, #1
	add	r1, r5, #124
	mov	r0, r6
	bl	HEVC_DecPTL
	subs	r4, r0, #0
	bne	.L2850
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	ldr	r3, [fp, #-104]
	cmp	r3, #0
	addge	r7, r5, #24
	ldrge	r3, [fp, #-104]
	addge	r8, r3, #1
	uxtb	r9, r0
	bge	.L2805
	b	.L2803
.L2802:
	add	r4, r4, #1
	cmp	r4, r8
	beq	.L2803
.L2805:
	ldr	r1, .L2858+4
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2858+8
	add	r0, r0, #1
	str	r0, [r7, #4]!
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2858+12
	str	r0, [r7, #32]
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	cmp	r9, #0
	str	r0, [r7, #64]
	bne	.L2802
	ldr	r3, [fp, #-104]
	add	r2, r4, #1
	cmp	r3, r2
	blt	.L2803
	add	r3, r4, #7
	add	r3, r5, r3, lsl #2
.L2804:
	ldr	r1, [r5, #28]
	add	r2, r2, #1
	cmp	r2, r8
	str	r1, [r3, #4]!
	ldr	r1, [r5, #60]
	str	r1, [r3, #32]
	ldr	r1, [r5, #92]
	str	r1, [r3, #64]
	bne	.L2804
.L2803:
	mov	r1, #6
	ldr	r0, [r6, #2808]
	bl	BsGet
	cmp	r0, #1
	str	r0, [r5, #16]
	bhi	.L2851
	ldr	r3, [r5, #8]
	adds	r0, r0, #0
	sub	r3, r3, #1
	movne	r0, #1
	cmp	r3, #61
	movhi	r0, #0
	cmp	r0, #0
	bne	.L2852
.L2806:
	ldr	r1, .L2858+16
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r5, #20]
	bcs	.L2853
	ldr	r4, .L2858+20
	add	r9, r5, #8320
	add	r9, r9, #4
	mov	r2, #8192
	mov	r1, #0
	add	r0, r5, #132
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r3, [r4, #48]
	mov	r0, r9
	mov	r2, #4096
	mov	r1, #0
	blx	r3
	ldr	r3, [r5, #20]
	cmp	r3, #0
	ble	.L2808
	mov	r8, #1
.L2809:
	mov	r4, #0
	mov	r7, r8, asl #1
	mov	r10, r4
.L2811:
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	add	r3, r7, r10
	add	r3, r5, r3, lsl #2
	tst	r0, #255
	strne	r4, [r3, #132]
	ldr	r3, [r5, #16]
	add	r4, r4, #1
	addne	r10, r10, #1
	cmp	r4, r3
	bls	.L2811
	str	r10, [r9, #4]!
	add	r8, r8, #1
	ldr	r3, [r5, #20]
	cmp	r8, r3
	ble	.L2809
.L2808:
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L2818
	mov	r1, #32
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L2854
.L2815:
	ldr	r1, .L2858+24
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r5, #24]
	bhi	.L2816
	cmp	r0, #0
	ble	.L2818
	ldr	r1, .L2858+28
	mov	r4, #0
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	mov	r0, #1
.L2827:
	uxtb	r2, r0
	sub	r1, fp, #100
	ldr	r3, [fp, #-104]
	mov	r0, r6
	bl	HEVC_DecHrdParam
	add	r4, r4, #1
	ldr	r1, .L2858+28
	cmp	r0, #0
	bne	.L2855
	ldr	r3, [r5, #24]
	cmp	r3, r4
	ble	.L2818
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	cmp	r4, #0
	mov	r0, #1
	beq	.L2827
	mov	r1, r0
	ldr	r0, [r6, #2808]
	bl	BsGet
	b	.L2827
.L2818:
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L2814
	ldrb	r4, [r6, #1]	@ zero_extendqisi2
	cmp	r4, #1
	bne	.L2823
	b	.L2856
.L2826:
	ldr	r0, [r6, #2808]
	bl	BsGet
.L2823:
	mov	r0, r6
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2826
.L2814:
	mov	r0, #0
.L2844:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2855:
	ldr	r1, .L2858+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2854:
	ldr	r1, .L2858+36
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	b	.L2815
.L2852:
	ldr	r1, .L2858+40
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, #1
	strb	r3, [r6, #1]
	b	.L2806
.L2849:
	ldr	r1, .L2858+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2844
.L2856:
	ldr	r0, [r6, #2808]
	bl	BsToNextByte
	mov	r1, r5
	mov	r0, r6
	bl	HEVC_ParseVPSExtension
	cmp	r0, #0
	bne	.L2857
	mov	r1, r4
	ldr	r0, [r6, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L2814
	b	.L2823
.L2848:
	mov	r2, r0
	ldr	r1, .L2858+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2844
.L2847:
	mov	r2, r0
	ldr	r1, .L2858+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2844
.L2850:
	ldr	r1, .L2858+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2844
.L2853:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L2858+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2844
.L2851:
	mov	r2, #1
	ldr	r1, .L2858+64
	mov	r0, r2
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2844
.L2816:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L2858+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2844
.L2857:
	mov	r0, r4
	ldr	r1, .L2858+72
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2844
.L2859:
	.align	2
.L2858:
	.word	.LC232
	.word	.LC237
	.word	.LC238
	.word	.LC239
	.word	.LC242
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC245
	.word	.LC247
	.word	.LC248
	.word	.LC244
	.word	.LC241
	.word	.LC235
	.word	.LC234
	.word	.LC233
	.word	.LC236
	.word	.LC243
	.word	.LC240
	.word	.LC246
	.word	.LC249
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
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, .L2872
	mov	r4, r0
	ldr	r0, [r6]
	cmp	r0, #0
	beq	.L2867
	mov	r1, #4
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r0, #15
	mov	r7, r0
	bhi	.L2868
	movw	r8, #24912
	ldr	r3, [r4, #2812]
	mul	r5, r8, r0
	add	r2, r3, r5
	ldrb	r10, [r3, r5]	@ zero_extendqisi2
	cmp	r10, #0
	bne	.L2869
	str	r0, [r2, #4]
	mov	r0, r4
	ldr	r1, [r4, #2812]
	add	r1, r1, r5
	bl	HEVC_ProcessVPS
	subs	r9, r0, #0
	bne	.L2870
	ldr	r3, [r4, #2812]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2812]
	strb	r2, [r3, r5]
.L2862:
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2869:
	ldr	r6, [r6]
	mov	r2, r8
	ldr	r10, .L2872+4
	mov	r1, #0
	add	r6, r6, #458752
	ldr	r3, [r10, #48]
	mov	r0, r6
	blx	r3
	str	r7, [r6, #4]
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ProcessVPS
	subs	r9, r0, #0
	bne	.L2871
	mov	r3, #1
	strb	r3, [r6, #2]
	strb	r3, [r6]
	mov	r2, r8
	ldr	r0, [r4, #2812]
	mov	r1, r6
	ldr	r3, [r10, #56]
	add	r0, r0, r5
	blx	r3
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2871:
	mov	r2, r7
	ldr	r1, .L2872+8
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	b	.L2862
.L2868:
	ldr	r1, .L2872+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r9, #0
	b	.L2862
.L2870:
	mov	r2, r7
	ldr	r1, .L2872+16
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2812]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2812]
	strb	r10, [r3, r5]
	b	.L2862
.L2867:
	ldr	r2, .L2872+20
	mvn	r9, #0
	ldr	r1, .L2872+24
	bl	dprint_vfmw
	b	.L2862
.L2873:
	.align	2
.L2872:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC251
	.word	.LC250
	.word	.LC252
	.word	.LANCHOR0+640
	.word	.LC72
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
	ldr	r0, [r0, #2808]
	mov	r1, #1
	mov	r6, r2
	bl	BsGet
	tst	r0, #255
	bne	.L2918
.L2876:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L2919
.L2878:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L2920
.L2880:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L2921
.L2882:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #3]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L2883
	ldr	r1, .L2927
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r3, [r6, #60]
	cmp	r3, #3
	bhi	.L2922
	ldr	r1, .L2927+4
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2927+8
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2927+12
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
.L2883:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L2886
	mov	r1, #32
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #32
	str	r0, [r5, #36]
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r2, [r5, #36]
	cmp	r2, #0
	str	r0, [r5, #40]
	bne	.L2923
.L2887:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L2924
.L2888:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L2925
.L2886:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r1, .L2927+16
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	cmp	r0, #4096
	bcs	.L2926
.L2889:
	ldr	r1, .L2927+20
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2927+24
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2927+28
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2808]
	ldr	r1, .L2927+32
	bl	HEVC_ue_v
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2918:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r0, #255
	str	r0, [r5, #8]
	bne	.L2876
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #16
	str	r0, [r5, #12]
	ldr	r0, [r4, #2808]
	bl	BsGet
	str	r0, [r5, #16]
	b	.L2876
.L2921:
	ldr	r1, .L2927+36
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L2927+40
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	b	.L2882
.L2920:
	mov	r1, #3
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #20]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5]
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	beq	.L2880
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #24]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #28]
	ldr	r0, [r4, #2808]
	bl	BsGet
	str	r0, [r5, #32]
	b	.L2880
.L2919:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L2878
.L2925:
	ldr	r3, [r6, #52]
	add	r1, r5, #44
	mov	r2, #1
	mov	r0, r4
	bl	HEVC_DecHrdParam
	cmp	r0, #0
	beq	.L2886
	ldr	r1, .L2927+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2924:
	ldr	r1, .L2927+48
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	b	.L2888
.L2923:
	ldr	r3, .L2927+52
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
	b	.L2887
.L2926:
	ldr	r1, .L2927+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2889
.L2922:
	ldr	r1, .L2927+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2928:
	.align	2
.L2927:
	.word	.LC255
	.word	.LC257
	.word	.LC258
	.word	.LC259
	.word	.LC262
	.word	.LC264
	.word	.LC265
	.word	.LC266
	.word	.LC267
	.word	.LC253
	.word	.LC254
	.word	.LC261
	.word	.LC260
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC263
	.word	.LC256
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
	bls	.L2934
	mvn	r0, #-2147483648
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2934:
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
	ldr	r1, .L2947
	mov	r6, r0
	ldr	r0, [r0, #2808]
	bl	HEVC_ue_v
	ldr	r0, [r6, #2808]
	ldr	r1, .L2947+4
	bl	HEVC_ue_v
	cmp	r0, #1024
	mov	r7, r0
	bhi	.L2936
	cmp	r0, #0
	movne	r4, #0
	beq	.L2942
.L2941:
	mov	r1, #6
	ldr	r0, [r6, #2808]
	bl	BsGet
	mov	r1, #3
	mov	r5, r0
	ldr	r0, [r6, #2808]
	sub	r5, r5, #19
	bl	BsGet
	cmp	r5, #1
	ldr	r1, .L2947+8
	bls	.L2939
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
.L2939:
	cmp	r4, #0
	ldr	r1, .L2947+12
	add	r4, r4, #1
	beq	.L2940
	ldr	r0, [r6, #2808]
	bl	HEVC_se_v
.L2940:
	cmp	r4, r7
	bne	.L2941
.L2942:
	ldr	r0, [r6, #2808]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2936:
	ldr	r1, .L2947+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2948:
	.align	2
.L2947:
	.word	.LC268
	.word	.LC269
	.word	.LC271
	.word	.LC272
	.word	.LC270
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
	beq	.L2951
	ldr	r1, .L2952
	ldr	r0, [r0, #2808]
	bl	HEVC_se_v
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r0, [r4, #2808]
	bl	BsToNextByte
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2951:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2953:
	.align	2
.L2952:
	.word	.LC273
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
	beq	.L2971
	ldr	r1, .L2984
	ldr	r0, [r0, #2808]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L2956
.L2969:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r8]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2956:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r1, r0
	cmp	r1, #1
	beq	.L2981
.L2957:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2808]
	mov	r7, #3
	bl	BsGet
.L2959:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	beq	.L2962
	add	r6, r0, #1
	mov	r5, #0
.L2961:
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r5, r6
	bne	.L2961
.L2962:
	subs	r7, r7, #1
	bne	.L2959
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L2982
.L2963:
	add	r10, r8, #42
	add	r7, r8, #39
	mov	r9, r10
.L2968:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #1]!
	cmp	r0, #32
	bhi	.L2983
	cmp	r0, #0
	beq	.L2970
	mov	r6, r9
	mov	r5, #0
.L2967:
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #16
	add	r5, r5, #1
	strh	r0, [r6, #2]!	@ movhi
	ldr	r0, [r4, #2808]
	bl	BsGet
	strh	r0, [r6, #198]	@ movhi
	ldrb	r3, [r7]	@ zero_extendqisi2
	add	r3, r3, #1
	cmp	r3, r5
	bhi	.L2967
.L2970:
	cmp	r10, r7
	add	r9, r9, #66
	bne	.L2968
	b	.L2969
.L2971:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2982:
	mov	r1, #4
	ldr	r0, [r4, #2808]
	bl	BsGet
	add	r7, r8, #36
	mov	r5, r8
.L2964:
	add	r6, r5, #12
.L2965:
	ldr	r1, .L2984+4
	ldr	r0, [r4, #2808]
	bl	HEVC_se_v
	str	r0, [r5, #4]!
	cmp	r6, r5
	bne	.L2965
	cmp	r5, r7
	bne	.L2964
	b	.L2963
.L2981:
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r8, #1]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L2957
.L2983:
	mov	r2, r0
	ldr	r1, .L2984+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2985:
	.align	2
.L2984:
	.word	.LC274
	.word	.LC275
	.word	.LC276
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
	bne	.L3012
	ldr	lr, [r0, #2828]
	ldr	lr, [lr, #16]
	cmp	lr, #39
	beq	.L3030
	cmp	r3, #5
	beq	.L3016
	cmp	r3, #132
	beq	.L3017
	cmp	r6, #0
	beq	.L3011
.L3019:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r5, r6
	bne	.L3019
	b	.L3011
.L3016:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	bne	.L3012
.L3011:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_More_Data_In_Payload
	cmp	r0, #0
	bne	.L3020
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3020:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_Payload_Extension_Present
	cmp	r0, #0
	bne	.L3031
.L3021:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L3022
.L3023:
	ldr	r0, [r4, #2808]
	bl	BsGet
.L3022:
	ldr	r0, [r4, #2808]
	bl	BsIsByteAligned
	mov	r1, #1
	cmp	r0, #0
	beq	.L3023
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3030:
	cmp	r3, #147
	ldrls	pc, [pc, r3, asl #2]
	b	.L2990
.L2992:
	.word	.L2991
	.word	.L2993
	.word	.L2990
	.word	.L2990
	.word	.L2994
	.word	.L2995
	.word	.L2996
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2997
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2998
	.word	.L2990
	.word	.L2999
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L3000
	.word	.L3001
	.word	.L3002
	.word	.L3003
	.word	.L2990
	.word	.L3004
	.word	.L3005
	.word	.L2990
	.word	.L2990
	.word	.L3006
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L2990
	.word	.L3007
	.word	.L2990
	.word	.L3008
	.word	.L2990
	.word	.L2990
	.word	.L3009
.L3017:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Decoded_Picture_Hash
	cmp	r0, #0
	beq	.L3011
.L3012:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3031:
	ldr	r1, .L3032
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	b	.L3021
.L3009:
	add	r1, r1, #616
	add	r1, r1, #2
	bl	HEVC_Sei_HLGHDR_Comapitibility_Info
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L2991:
	add	r2, r2, #2096
	add	r2, r2, #12
	bl	HEVC_Sei_Buf_Period
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L2993:
	add	r2, r2, #2064
	add	r1, r1, #8
	bl	HEVC_Sei_Pic_Timming
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L2994:
	add	r1, r1, #56
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Registered_Itu_T_T35
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L2995:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L2996:
	add	r1, r1, #568
	bl	HEVC_Sei_Recovery_Point
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L2997:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Tone_Mapping_Info
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L2998:
	add	r1, r1, #568
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L2999:
	add	r1, r1, #568
	bl	HEVC_Sei_Display_Orientation
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L3000:
	add	r1, r1, #616
	mov	r2, r6
	add	r1, r1, #3
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L3001:
	add	r1, r1, #568
	bl	HEVC_Sei_Active_Param_sets
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L3002:
	add	r2, r2, #2096
	add	r1, r1, #568
	add	r2, r2, #12
	bl	HEVC_Sei_Dec_Unit_Info
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L3003:
	add	r1, r1, #568
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L3004:
	mov	r3, r6
	bl	HEVC_Sei_Scalable_Nesting
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L3005:
	cmn	r1, #568
	movne	r1, #0
	moveq	r1, #1
	orrs	r3, ip, r1
	bne	.L3012
	mov	r1, #1
	ldr	r0, [r0, #2808]
	bl	BsGet
	b	.L3011
.L3006:
	add	r1, r1, #568
	bl	HEVC_Sei_Mastering_Display_Colour_Volume
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L3007:
	add	r1, r1, #128
	bl	HEVC_Sei_Color_Remapping_Info
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L3008:
	add	r1, r1, #612
	bl	HEVC_Sei_Content_Light_Level_Information
	cmp	r0, #0
	beq	.L3011
	b	.L3012
.L2990:
	cmp	r6, #0
	movne	r5, #0
	beq	.L3011
.L3014:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r5, r6
	bne	.L3014
	b	.L3011
.L3033:
	.align	2
.L3032:
	.word	.LC277
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
	ldr	r0, [r0, #2808]
	b	.L3035
.L3037:
	bl	BsSkip
	ldr	r0, [r4, #2808]
	add	r5, r5, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2, asl #3
	bhi	.L3043
.L3035:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2808]
	beq	.L3037
	bl	BsGet
	mov	r8, #0
	mov	r9, r0
	ldr	r0, [r4, #2808]
	b	.L3038
.L3039:
	bl	BsSkip
	ldr	r0, [r4, #2808]
	add	r8, r8, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2, asl #3
	bhi	.L3044
.L3038:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2808]
	beq	.L3039
	bl	BsGet
	add	r3, r9, r5
	mov	r2, r7
	mov	r1, r6
	add	r8, r0, r8
	mov	r0, r4
	str	r8, [sp]
	bl	HEVC_Sei_Payload
	cmp	r0, #0
	bne	.L3045
.L3036:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3043:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5039
	ldr	r1, .L3046
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3044:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5060
	ldr	r1, .L3046
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3045:
	ldr	r1, .L3046+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3036
.L3047:
	.align	2
.L3046:
	.word	.LC278
	.word	.LC279
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
	beq	.L3054
	ldr	r6, [r0, #2824]
	add	r5, r0, #3472
	add	r5, r5, #8
	cmp	r6, #0
	bne	.L3057
	b	.L3060
.L3052:
	ldr	r0, [r4, #2808]
	bl	BsIsByteAligned
	cmp	r0, #0
	mov	r0, r4
	beq	.L3061
	bl	HEVC_More_Rbsp_Data
	cmp	r0, #0
	beq	.L3062
.L3057:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	beq	.L3052
	ldr	r1, .L3064
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3062:
	ldr	r0, [r4, #2808]
	mov	r1, #8
	bl	BsGet
	cmp	r0, #128
	bne	.L3063
.L3054:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3061:
	ldr	r1, .L3064+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3063:
	mov	r2, r0
	ldr	r1, .L3064+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3060:
	ldr	r1, .L3064+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3065:
	.align	2
.L3064:
	.word	.LC281
	.word	.LC282
	.word	.LC283
	.word	.LC280
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
	ldr	r0, [r0, #2808]
	mov	r1, #1
	mov	r7, r2
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	tst	r0, #255
	ldr	r0, [r4, #2808]
	beq	.L3067
	bl	BsGet
	ldr	r1, .L3083
	mov	r5, r0
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	cmp	r0, #63
	mov	r8, r0
	bhi	.L3080
	uxtb	r5, r5
	cmp	r0, r5
	bcc	.L3073
.L3072:
	mov	r1, #3
	ldr	r0, [r4, #2808]
	bl	BsGet
	add	r5, r5, #1
	ldr	r1, .L3083+4
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	cmp	r8, r5
	bcs	.L3072
.L3073:
	ldr	r0, [r4, #2808]
	bl	BsToNextByte
	b	.L3071
.L3076:
	bl	HEVC_MoreRbspData
	cmp	r0, #0
	beq	.L3081
.L3071:
	mov	r2, r7
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	mov	r0, r4
	beq	.L3076
	ldr	r1, .L3083+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3067:
	bl	BsGet
	uxtb	r5, r0
	cmp	r5, #0
	bne	.L3073
	mov	r1, #3
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r1, .L3083+12
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	cmp	r0, #63
	addls	r8, r0, #1
	bhi	.L3082
.L3075:
	add	r5, r5, #1
	mov	r1, #6
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r5, r8
	bne	.L3075
	b	.L3073
.L3081:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3080:
	mov	r2, #64
	ldr	r1, .L3083+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3082:
	ldr	r1, .L3083+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3084:
	.align	2
.L3083:
	.word	.LC284
	.word	.LC286
	.word	.LC281
	.word	.LC287
	.word	.LC285
	.word	.LC288
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
	ldr	r3, .L3126
	mov	r6, r0
	str	r1, [fp, #-60]
	ldr	r0, [r3]
	cmp	r0, #0
	beq	.L3120
	ldr	r3, .L3126+4
	add	r9, r6, #2240
	ldr	r4, [fp, #-60]
	add	r9, r9, #4
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
.L3088:
	ldr	r3, [r9, #4]!
	cmp	r3, #0
	beq	.L3108
	ldr	r2, [fp, #-48]
	ldr	r1, [fp, #-68]
	ldr	r7, [fp, #-64]
	mov	r3, r2, asl #3
	sub	r3, r3, r2, asl #1
	str	r1, [fp, #-56]
	str	r3, [fp, #-72]
	mov	r3, #0
	str	r3, [fp, #-52]
.L3107:
	mov	r1, #1
	ldr	r0, [r6, #2808]
	bl	BsGet
	ldr	r5, [r9, #-1888]
	ldr	r3, [fp, #-48]
	cmp	r5, #64
	movge	r5, #64
	cmp	r3, #0
	uxtb	r0, r0
	beq	.L3121
	cmp	r0, #0
	add	r4, r6, #376
	beq	.L3122
	ldr	r3, [fp, #-48]
	cmp	r3, #1
	bls	.L3113
	ldr	r1, .L3126+8
	ldr	r0, [r6, #2808]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #254
	bhi	.L3123
	ldr	r3, [fp, #-56]
	add	r8, r0, #8
	str	r8, [r3]
.L3091:
	cmp	r5, #0
	ble	.L3100
	sub	r4, r4, #4
	mov	r10, #0
	b	.L3104
.L3103:
	mov	r8, r8, lsr #24
	ldr	r2, [r4, #4]!
	add	r3, r3, r8
	cmp	r10, r5
	uxtb	r3, r3
	rsb	r8, r8, r3
	strb	r8, [r7, r2]
	beq	.L3100
.L3104:
	ldr	r1, .L3126+12
	add	r10, r10, #1
	ldr	r0, [r6, #2808]
	bl	HEVC_se_v
	add	r3, r0, r8
	add	r0, r0, #128
	add	r3, r3, #256
	cmp	r0, #255
	mov	r8, r3, asr #31
	bls	.L3103
	ldr	r1, .L3126+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L3118:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3121:
	ldr	r3, .L3126
	cmp	r0, #0
	ldr	r4, [r3]
	add	r4, r4, #65536
	bne	.L3113
	ldr	r1, .L3126+20
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-52]
	cmp	r0, r3
	bhi	.L3110
	ldr	r3, [fp, #-52]
	rsb	r3, r0, r3
	uxtb	r3, r3
.L3095:
	ldr	r2, [fp, #-52]
	cmp	r3, r2
	beq	.L3124
.L3097:
	ldr	r2, [fp, #-72]
	add	r3, r2, r3
	ldr	r2, [fp, #-60]
	add	r1, r2, r3, lsl #6
.L3098:
	cmp	r1, #0
	beq	.L3125
	ldr	r3, .L3126+4
	mov	r2, r5
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
.L3100:
	ldr	r3, [fp, #-52]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	cmp	r3, #6
	beq	.L3108
	ldr	r2, [fp, #-56]
	add	r7, r7, #64
	ldr	r3, [r9]
	add	r2, r2, #4
	str	r2, [fp, #-56]
	ldr	r2, [fp, #-52]
	cmp	r2, r3
	bcc	.L3107
.L3108:
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
	bne	.L3088
	mov	r0, #0
	b	.L3118
.L3113:
	mov	r8, #8
	b	.L3091
.L3122:
	ldr	r1, .L3126+20
	ldr	r0, [r6, #2808]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-52]
	cmp	r0, r3
	bhi	.L3110
	ldr	r2, [fp, #-52]
	ldr	r1, [fp, #-48]
	rsb	r3, r0, r2
	cmp	r1, #1
	uxtb	r3, r3
	bls	.L3095
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
	bne	.L3097
.L3124:
	mov	r1, r2
	ldr	r0, [fp, #-48]
	bl	HEVC_GetScalingListDefaultAddress
	mov	r1, r0
	b	.L3098
.L3123:
	ldr	r1, .L3126+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3118
.L3125:
	ldr	r1, .L3126+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3118
.L3110:
	ldr	r1, .L3126+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3118
.L3120:
	ldr	r2, .L3126+36
	ldr	r1, .L3126+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3118
.L3127:
	.align	2
.L3126:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC292
	.word	.LC294
	.word	.LC295
	.word	.LC289
	.word	.LC293
	.word	.LC291
	.word	.LC290
	.word	.LANCHOR0+652
	.word	.LC72
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r4, r1
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	mov	r5, r0
	cmp	r1, #1
	beq	.L3314
.L3129:
	ldr	r1, .L3342
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #1
	mov	r6, r0
	str	r0, [r4, #60]
	beq	.L3315
	cmp	r6, #3
	bhi	.L3316
	mov	r2, r6
	ldr	r1, .L3342+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L3302:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3316:
	ldr	r1, .L3342+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3314:
	ldr	r3, [r0, #2828]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L3129
	ldrb	r3, [r4, #46]	@ zero_extendqisi2
	cmp	r3, #7
	bne	.L3129
	ldr	r3, [r0, #2812]
	movw	r6, #24912
	ldr	r2, [r4, #48]
	ldr	r0, [r0, #2808]
	mla	r6, r6, r2, r3
	bl	BsGet
	cmp	r0, #0
	bne	.L3317
	ldr	r3, [r5, #2828]
	add	r2, r6, #12288
	ldr	r3, [r3, #24]
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #132]
	add	r3, r3, #1024
	add	r3, r3, #14
	add	r2, r2, r3, lsl #2
	ldr	r0, [r2, #132]
.L3131:
	cmp	r0, #1
	bhi	.L3318
	mov	r3, r0, asl #5
	add	r6, r6, #12288
	add	r0, r3, r0, lsl #3
	movw	r1, #12540
	add	r0, r6, r0
	movw	lr, #12548
	add	r2, r0, #12544
	add	r3, r0, #12480
	add	r2, r2, #4
	add	r3, r3, #60
	movw	r7, #12556
	add	ip, r0, #12544
	ldr	r2, [r2, #4]
	add	ip, ip, #12
	movw	r6, #12564
	str	r2, [r4, #60]
	ldrb	r2, [r0, r1]	@ zero_extendqisi2
	add	r1, r0, #12544
	add	r1, r1, #20
	strb	r2, [r4, #47]
	add	r2, r0, #12544
	ldr	r3, [r3, #4]
	add	r2, r2, #28
	str	r3, [r4, #64]
	ldr	r3, [r0, lr]
	movw	lr, #12572
	str	r3, [r4, #68]
	ldr	r3, [r0, r7]
	add	r3, r3, #8
	str	r3, [r4, #88]
	ldr	ip, [ip, #4]
	add	ip, ip, #8
	str	ip, [r4, #96]
	ldr	ip, [r0, r6]
	str	ip, [r4, #72]
	ldr	r1, [r1, #4]
	str	r1, [r4, #76]
	ldr	r1, [r0, lr]
	str	r1, [r4, #80]
	ldr	r2, [r2, #4]
	str	r2, [r4, #84]
.L3134:
	str	r3, [r5, #196]
	ldr	r3, [r4, #96]
	ldr	r1, .L3342+12
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
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #12
	bhi	.L3319
	add	r0, r0, #4
	str	r0, [r4, #116]
	str	r0, [r4, #120]
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3320
.L3161:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r9, #0
	mov	r7, r9
	mov	r6, r4
	mov	r8, r0
	b	.L3169
.L3165:
	ldr	r3, [r4, #52]
	add	r7, r7, #1
	add	r6, r6, #4
	cmp	r3, r7
	bcc	.L3168
.L3169:
	ldr	r1, .L3342+16
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L3342+20
	add	r0, r0, #1
	str	r0, [r6, #328]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L3342+24
	str	r0, [r6, #360]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r3, [r6, #328]
	cmp	r9, r3
	movcc	r9, r3
	cmp	r8, #0
	str	r0, [r6, #392]
	bne	.L3165
	ldr	r1, [r4, #52]
	add	r3, r7, #1
	cmp	r3, r1
	addls	r7, r7, #82
	addls	r7, r4, r7, lsl #2
	bhi	.L3168
.L3167:
	ldr	r2, [r4, #328]
	add	r3, r3, #1
	cmp	r3, r1
	str	r2, [r7, #4]!
	ldr	r2, [r4, #360]
	str	r2, [r7, #32]
	ldr	r2, [r4, #392]
	str	r2, [r7, #64]
	bls	.L3167
.L3168:
	ldr	r3, [r4, #184]
	cmp	r3, r9
	movcs	r3, r9
	str	r3, [r4, #184]
.L3164:
	ldr	r1, .L3342+28
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L3321
	ldr	r1, .L3342+32
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r7, r0
	bhi	.L3322
	add	r0, r6, #3
	str	r0, [r4, #124]
	add	r6, r7, r0
	str	r6, [r4, #128]
	sub	r3, r6, #4
	cmp	r3, #2
	bhi	.L3323
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
	beq	.L3173
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L3174:
	ldr	r8, [r4, #68]
	mov	r1, r6
	str	r0, [r4, #188]
	mov	r0, r8
	bl	__aeabi_uidivmod
	mov	r0, r8
	cmp	r1, #0
	mov	r1, r6
	beq	.L3175
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L3176:
	str	r0, [r4, #192]
	ldr	r1, .L3342+36
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L3324
	ldr	r1, .L3342+40
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #3
	bhi	.L3325
	ldr	r2, [r4, #124]
	add	r3, r6, #2
	str	r3, [r4, #148]
	cmp	r3, r2
	bcs	.L3326
	add	r3, r0, r3
	str	r3, [r4, #152]
	cmp	r3, #5
	bhi	.L3180
	ldr	r2, [r4, #128]
	cmp	r3, r2
	bhi	.L3180
	ldr	r1, .L3342+44
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r3, [r4, #128]
	ldr	r2, [r4, #148]
	rsb	r3, r2, r3
	cmp	r0, r3
	str	r0, [r4, #164]
	bhi	.L3327
	ldr	r1, .L3342+48
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	ip, [r4, #148]
	ldr	r3, [r4, #128]
	rsb	r3, ip, r3
	cmp	r0, r3
	str	r0, [r4, #168]
	bhi	.L3183
	ldr	r1, [r4, #140]
	mov	r0, #1
	mov	r3, #0
	mov	r1, r1, lsr r7
	cmp	r1, r0, asl ip
	bls	.L3185
.L3186:
	add	r3, r3, #1
	add	r2, r3, ip
	cmp	r1, r0, asl r2
	bhi	.L3186
.L3185:
	add	r3, r3, r7
	mov	r1, #1
	str	r3, [r4, #172]
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3]
	cmp	r0, #0
	beq	.L3190
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L3328
.L3188:
	add	r3, r4, #12288
	mov	r2, #0
	strb	r2, [r3, #372]
.L3221:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #0
	bne	.L3329
.L3190:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #6]
	cmp	r6, #0
	bne	.L3191
	ldr	r2, [r4, #68]
	cmp	r2, #64
	bls	.L3330
.L3191:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #104]
	beq	.L3192
	mov	r1, #4
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #4
	add	r0, r0, #1
	str	r0, [r4, #108]
	ldr	r0, [r5, #2808]
	bl	BsGet
	ldr	r1, .L3342+52
	add	r0, r0, #1
	str	r0, [r4, #112]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r7, r0
	bhi	.L3331
.L3193:
	ldr	r1, .L3342+56
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r6, r0
	bhi	.L3332
.L3194:
	add	r0, r7, #3
	str	r0, [r4, #156]
	add	r0, r6, r0
	str	r0, [r4, #160]
	cmp	r0, #5
	bhi	.L3195
	ldr	r3, [r4, #128]
	cmp	r0, r3
	bhi	.L3195
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	strb	r0, [r4, #7]
.L3192:
	ldr	r1, .L3342+60
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #64
	str	r0, [r4, #176]
	bhi	.L3197
	cmp	r0, #0
	addne	r7, r4, #2160
	movne	r6, #0
	addne	r7, r7, #4
	bne	.L3202
	b	.L3203
.L3201:
	ldr	r3, [r4, #176]
	cmp	r3, r6
	bls	.L3203
.L3202:
	mov	r3, r6
	mov	r2, r7
	mov	r1, r4
	mov	r0, r5
	bl	HEVC_DecShortTermRefPicSet
	add	r6, r6, #1
	add	r7, r7, #164
	cmp	r0, #0
	beq	.L3201
	ldr	r1, .L3342+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3315:
	ldr	r1, .L3342+68
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #8192
	str	r0, [r4, #64]
	bls	.L3136
	ldr	r1, .L3342+72
	mov	r0, r6
.L3307:
	bl	dprint_vfmw
	ldr	r3, .L3342+76
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L3305
	mov	r3, #0
	ldr	r0, [r5, #276]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	b	.L3302
.L3136:
	ldr	r1, .L3342+80
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #4096
	str	r0, [r4, #68]
	bhi	.L3333
	ldr	r2, [r4, #428]
	ldr	r3, [r4, #64]
	cmp	r2, #120
	mul	r0, r3, r0
	beq	.L3141
	bgt	.L3142
	cmp	r2, #60
	beq	.L3143
	ble	.L3334
	cmp	r2, #90
	beq	.L3146
	cmp	r2, #93
	beq	.L3147
	cmp	r2, #63
	beq	.L3335
.L3140:
	ldr	r1, .L3342+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3339:
	ldr	r1, .L3342+88
	mov	r0, #1
	bl	dprint_vfmw
.L3305:
	mvn	r0, #0
	b	.L3302
.L3142:
	cmp	r2, #156
	beq	.L3149
	bgt	.L3150
	cmp	r2, #150
	beq	.L3149
	cmp	r2, #153
	beq	.L3149
	cmp	r2, #123
	bne	.L3140
.L3141:
	mov	r2, #557056
	mov	r3, #2228224
.L3148:
	cmp	r0, r2
	movls	r3, #16
	strls	r3, [r4, #184]
	bls	.L3153
	cmp	r0, r3, lsr #1
	movls	r3, #12
	strls	r3, [r4, #184]
	bls	.L3153
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, lsr #2
	movls	r3, #8
	movhi	r3, #6
	str	r3, [r4, #184]
.L3153:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r0, #0
	beq	.L3156
	ldr	r1, .L3342+92
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r6, .L3342+96
	ldr	r1, .L3342+100
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #676]
	mul	r0, r3, r0
	str	r0, [r4, #72]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r2, [r4, #60]
	ldr	r3, [r4, #64]
	ldr	r1, [r4, #72]
	add	r2, r6, r2, lsl #2
	rsb	r3, r1, r3
	ldr	r2, [r2, #676]
	mul	r0, r2, r0
	rsb	r3, r0, r3
	cmp	r3, #0
	str	r0, [r4, #76]
	blt	.L3336
	ldr	r1, .L3342+104
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r1, .L3342+108
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #692]
	mul	r0, r3, r0
	str	r0, [r4, #80]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r1, [r4, #60]
	ldr	r2, [r4, #80]
	ldr	r3, [r4, #68]
	add	r6, r6, r1, lsl #2
	rsb	r3, r2, r3
	ldr	r2, [r6, #692]
	mul	r0, r2, r0
	rsb	r3, r0, r3
	cmp	r3, #0
	str	r0, [r4, #84]
	blt	.L3337
.L3156:
	ldr	r1, .L3342+112
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #2
	add	r2, r0, #8
	str	r2, [r4, #88]
	bhi	.L3338
	ldr	r1, .L3342+116
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #6
	add	r2, r0, #8
	str	r2, [r4, #96]
	ldrls	r3, [r4, #88]
	bls	.L3134
	ldr	r1, .L3342+120
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3175:
	bl	__aeabi_uidiv
	b	.L3176
.L3173:
	bl	__aeabi_uidiv
	b	.L3174
.L3320:
	ldr	r3, [r5, #2828]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L3161
	ldrb	r3, [r4, #46]	@ zero_extendqisi2
	cmp	r3, #7
	bne	.L3161
	ldr	r3, [r4, #48]
	movw	ip, #24912
	ldr	r0, [r5, #2812]
	mov	r2, #0
	ldr	r9, [r4, #52]
	add	r8, r4, #324
	add	r7, r4, #356
	add	r6, r4, #388
	mla	r0, ip, r3, r0
	mov	r1, r2
	add	lr, r0, #24
	add	ip, r0, #56
	add	r0, r0, #88
.L3163:
	ldr	r3, [lr, #4]!
	add	r1, r1, #1
	cmp	r2, r3
	str	r3, [r8, #4]!
	ldr	r10, [ip, #4]!
	movcc	r2, r3
	cmp	r9, r1
	str	r10, [r7, #4]!
	ldr	r3, [r0, #4]!
	str	r3, [r6, #4]!
	bcs	.L3163
	str	r2, [r4, #184]
	b	.L3164
.L3203:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	beq	.L3200
	ldr	r1, .L3342+124
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #32
	str	r0, [r4, #180]
	bhi	.L3206
	cmp	r0, #0
	addne	r8, r4, #192
	addne	r7, r4, #12
	movne	r6, #0
	beq	.L3200
.L3208:
	ldr	r1, [r4, #116]
	add	r6, r6, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #4]!
	ldr	r0, [r5, #2808]
	bl	BsGet
	strb	r0, [r7, #1]!
	ldr	r3, [r4, #180]
	cmp	r3, r6
	bhi	.L3208
.L3200:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r3, #2
	str	r3, [r4, #2096]
	uxtb	r0, r0
	strb	r0, [r4, #11]
	cmp	r0, #0
	beq	.L3205
	mov	r2, r4
	add	r1, r4, #2064
	mov	r0, r5
	bl	HEVC_DecVuiParam
	cmp	r0, #0
	bne	.L3339
.L3205:
	ldr	r1, [r4, #68]
	ldrb	ip, [r4, #2067]	@ zero_extendqisi2
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #2080]
	mla	ip, ip, r1, r1
	ldr	r0, [r4, #2072]
	ldr	r1, [r4, #2076]
	str	ip, [sp]
	bl	HEVC_GetDar
	str	r0, [r4, #2068]
	ldrb	r6, [r5, #1]	@ zero_extendqisi2
	cmp	r6, #1
	movne	r3, #1
	movne	r0, #0
	strneb	r3, [r4]
	bne	.L3302
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	tst	r0, #255
	bne	.L3210
.L3214:
	mov	r0, #0
	b	.L3302
.L3317:
	mov	r1, #8
	ldr	r0, [r5, #2808]
	bl	BsGet
	b	.L3131
.L3330:
	ldr	r1, .L3342+128
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3342+76
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L3305
	ldr	r0, [r5, #276]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	b	.L3302
.L3328:
	ldr	r3, [r5, #2828]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L3188
	ldrb	r3, [r4, #46]	@ zero_extendqisi2
	cmp	r3, #7
	bne	.L3188
	ldr	r0, [r5, #2808]
	add	r6, r4, #12288
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #372]
	cmp	r0, #0
	beq	.L3221
	mov	r1, #6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r3, #0
	str	r0, [r6, #376]
	strb	r3, [r4, #4]
	b	.L3190
.L3180:
	ldr	r1, .L3342+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3333:
	mov	r0, r6
	ldr	r1, .L3342+136
	b	.L3307
.L3332:
	mov	r2, r0
	ldr	r1, .L3342+140
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3194
.L3331:
	mov	r2, r0
	ldr	r1, .L3342+144
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3193
.L3329:
	add	r1, r4, #432
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	beq	.L3190
	ldr	r1, .L3342+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3338:
	ldr	r1, .L3342+152
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3342+76
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L3305
	ldr	r1, [r4, #88]
	mov	r2, #0
	ldr	r0, [r5, #276]
	mov	r3, #8
	str	r2, [fp, #-52]
	sub	r2, fp, #52
	str	r1, [fp, #-48]
	mov	r1, #119
	blx	r6
	mvn	r0, #0
	b	.L3302
.L3321:
	ldr	r1, .L3342+156
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3318:
	mov	r2, #1
	ldr	r1, .L3342+160
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r1, .L3342+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3324:
	ldr	r1, .L3342+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3150:
	cmp	r2, #183
	beq	.L3151
	cmp	r2, #186
	beq	.L3151
	cmp	r2, #180
	bne	.L3140
.L3151:
	mov	r2, #8912896
	mov	r3, #35651584
	b	.L3148
.L3334:
	cmp	r2, #0
	beq	.L3145
	cmp	r2, #30
	bne	.L3140
.L3145:
	mov	r2, #9216
	mov	r3, #36864
	b	.L3148
.L3327:
	ldr	r1, .L3342+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3195:
	ldr	r1, .L3342+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3147:
	mov	r2, #245760
	mov	r3, #983040
	b	.L3148
.L3146:
	mov	r2, #138240
	mov	r3, #552960
	b	.L3148
.L3149:
	mov	r2, #2228224
	mov	r3, #8912896
	b	.L3148
.L3143:
	mov	r2, #30720
	mov	r3, #122880
	b	.L3148
.L3335:
	mov	r2, #61440
	mov	r3, #245760
	b	.L3148
.L3319:
	ldr	r1, .L3342+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3322:
	ldr	r1, .L3342+184
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3323:
	ldr	r1, .L3342+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3326:
	ldr	r1, .L3342+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3325:
	ldr	r1, .L3342+196
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3183:
	ldr	r1, .L3342+200
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3210:
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	mov	r4, r0
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	uxtb	r7, r0
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2808]
	bl	BsGet
	tst	r4, #255
	uxtb	r4, r0
	bne	.L3340
.L3211:
	cmp	r7, #0
	bne	.L3341
.L3212:
	cmp	r4, #0
	bne	.L3301
	b	.L3214
.L3215:
	ldr	r0, [r5, #2808]
	bl	BsGet
.L3301:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L3215
	b	.L3214
.L3197:
	mov	r2, #64
	ldr	r1, .L3342+204
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3341:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	b	.L3212
.L3340:
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	b	.L3211
.L3206:
	ldr	r1, .L3342+208
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3336:
	ldr	r1, .L3342+212
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3337:
	ldr	r1, .L3342+216
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3302
.L3343:
	.align	2
.L3342:
	.word	.LC348
	.word	.LC299
	.word	.LC298
	.word	.LC315
	.word	.LC317
	.word	.LC318
	.word	.LC319
	.word	.LC320
	.word	.LC322
	.word	.LC325
	.word	.LC327
	.word	.LC331
	.word	.LC333
	.word	.LC337
	.word	.LC339
	.word	.LC342
	.word	.LC344
	.word	.LC300
	.word	.LC301
	.word	g_event_report
	.word	.LC302
	.word	.LC304
	.word	.LC347
	.word	.LC305
	.word	.LANCHOR0
	.word	.LC306
	.word	.LC308
	.word	.LC309
	.word	.LC311
	.word	.LC313
	.word	.LC314
	.word	.LC345
	.word	.LC336
	.word	.LC330
	.word	.LC303
	.word	.LC340
	.word	.LC338
	.word	.LC335
	.word	.LC312
	.word	.LC321
	.word	.LC296
	.word	.LC297
	.word	.LC326
	.word	.LC332
	.word	.LC341
	.word	.LC316
	.word	.LC323
	.word	.LC324
	.word	.LC329
	.word	.LC328
	.word	.LC334
	.word	.LC343
	.word	.LC346
	.word	.LC307
	.word	.LC310
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
	ldr	r10, .L3374
	mov	r4, r0
	ldr	r0, [r10]
	cmp	r0, #0
	beq	.L3366
	ldr	r8, .L3374+4
	mov	r2, #8
	mov	r1, #0
	sub	r0, fp, #60
	ldr	r3, [r8, #48]
	blx	r3
	mov	r1, #4
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r2, [r4, #156]
	cmp	r2, r0
	mov	r9, r0
	bls	.L3367
	ldr	r3, [r4, #2828]
	mov	r1, #3
	ldr	r0, [r4, #2808]
	ldr	r5, [r3, #24]
	cmp	r5, #0
	beq	.L3368
	bl	BsGet
	uxtb	r3, r0
	str	r3, [fp, #-68]
	cmp	r3, #7
	movne	r7, r3
	beq	.L3369
.L3351:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r3, r7
	mov	r2, #1
	sub	r1, fp, #60
	uxtb	r0, r0
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	HEVC_DecPTL
	cmp	r0, #0
	bne	.L3370
.L3352:
	ldr	r1, .L3374+8
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r2, [r4, #160]
	cmp	r0, r2
	mov	r6, r0
	bcs	.L3371
	movw	r3, #12668
	ldr	r2, [r4, #2816]
	mul	r5, r3, r0
	add	r2, r2, r5
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3354
	ldr	r10, [r10]
	movw	r2, #12668
	ldr	r3, [r8, #48]
	mov	r1, #0
	add	r10, r10, #458752
	mov	r0, r10
	blx	r3
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	str	r7, [r10, #52]
	sub	r1, fp, #60
	mov	r2, #8
	str	r9, [r10, #48]
	strb	r3, [r10, #2]
	add	r0, r10, #424
	ldrb	r3, [fp, #-68]	@ zero_extendqisi2
	strb	r3, [r10, #46]
	ldr	r3, [r8, #52]
	blx	r3
	str	r6, [r10, #56]
	mov	r1, r10
	mov	r0, r4
	bl	HEVC_ProcessSPS
	subs	r7, r0, #0
	bne	.L3372
	mov	r3, #1
	strb	r3, [r10]
	strb	r3, [r10, #1]
	movw	r2, #12668
	ldr	r3, .L3374+4
	mov	r1, r10
	ldr	r0, [r4, #2816]
	ldr	r3, [r3, #56]
	add	r0, r0, r5
	blx	r3
	ldr	r3, [r4, #2816]
	add	r5, r3, r5
	str	r5, [r4, #2824]
.L3365:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3368:
	bl	BsGet
	cmp	r0, #8
	mov	r7, r0
	strls	r5, [fp, #-68]
	bls	.L3351
	mov	r2, #8
	ldr	r1, .L3374+12
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L3365
.L3354:
	str	r9, [r2, #48]
	sub	r1, fp, #60
	ldr	r0, [r4, #2816]
	mov	r2, #8
	str	r3, [fp, #-72]
	add	r0, r0, r5
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	str	r7, [r0, #52]
	ldr	r0, [r4, #2816]
	add	r0, r0, r5
	strb	r3, [r0, #2]
	ldr	r0, [r4, #2816]
	ldrb	r3, [fp, #-68]	@ zero_extendqisi2
	add	r0, r0, r5
	strb	r3, [r0, #46]
	ldr	r0, [r4, #2816]
	ldr	r7, [r8, #52]
	add	r0, r0, r5
	add	r0, r0, #424
	blx	r7
	ldr	r2, [r4, #2816]
	mov	r0, r4
	add	r2, r2, r5
	str	r6, [r2, #56]
	ldr	r1, [r4, #2816]
	add	r1, r1, r5
	bl	HEVC_ProcessSPS
	ldr	r3, [fp, #-72]
	subs	r7, r0, #0
	bne	.L3373
	ldr	r3, [r4, #2816]
	mov	r2, #1
	mov	r0, r7
	strb	r2, [r3, r5]
	ldr	r3, [r4, #2816]
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2816]
	add	r5, r3, r5
	str	r5, [r4, #2824]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3371:
	ldr	r1, .L3374+16
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #160]
	cmp	r6, r2
	bcc	.L3361
	ldr	r3, .L3374+20
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3361
	str	r2, [fp, #-48]
	mov	r3, #8
	str	r6, [fp, #-52]
	sub	r2, fp, #52
	ldr	r0, [r4, #276]
	mov	r1, #109
	blx	r5
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3361:
	mvn	r7, #0
	b	.L3365
.L3369:
	ldr	r3, [r4, #2828]
	ldr	r7, [r3, #24]
	cmp	r7, #0
	beq	.L3351
	ldr	r2, [r4, #2812]
	movw	r3, #24912
	mla	r3, r3, r9, r2
	ldr	r7, [r3, #12]
	cmp	r7, #0
	moveq	r3, #1
	streq	r3, [fp, #-64]
	ldrneb	r3, [r3, #1]	@ zero_extendqisi2
	strne	r3, [fp, #-64]
	b	.L3352
.L3367:
	ldr	r1, .L3374+24
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L3365
.L3372:
	ldr	r3, [r4, #2816]
	mov	r2, r6
	ldr	r1, .L3374+28
	mov	r0, #1
	add	r5, r3, r5
	str	r5, [r4, #2824]
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L3365
.L3370:
	ldr	r1, .L3374+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L3365
.L3366:
	ldr	r2, .L3374+36
	mvn	r7, #0
	ldr	r1, .L3374+40
	bl	dprint_vfmw
	b	.L3365
.L3373:
	mov	r2, r6
	ldr	r1, .L3374+44
	mov	r0, #1
	str	r3, [fp, #-64]
	bl	dprint_vfmw
	ldr	r2, [r4, #2816]
	mov	r1, #1
	ldr	r3, [fp, #-64]
	mvn	r7, #0
	strb	r1, [r2, r5]
	ldr	r2, [r4, #2816]
	add	r5, r2, r5
	strb	r3, [r5, #1]
	b	.L3365
.L3375:
	.align	2
.L3374:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC352
	.word	.LC350
	.word	.LC353
	.word	g_event_report
	.word	.LC349
	.word	.LC354
	.word	.LC351
	.word	.LANCHOR0+708
	.word	.LC72
	.word	.LC355
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
	ldr	r1, .L3551
	ldr	r0, [r0, #2808]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r4, #32]
	blt	.L3377
	ldr	r3, [r5, #160]
	cmp	r0, r3
	bge	.L3377
	ldr	r3, [r5, #2816]
	movw	r6, #12668
	mla	r6, r6, r0, r3
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3523
	mov	r1, r7
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #2]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #4]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r7
	str	r0, [r4, #36]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #3]
	ldr	r0, [r5, #2808]
	bl	BsGet
	ldr	r1, .L3551+4
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #40]
	cmp	r0, #15
	bhi	.L3524
	ldr	r1, .L3551+8
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #44]
	cmp	r0, #15
	bhi	.L3525
	ldr	r1, .L3551+12
	ldr	r0, [r5, #2808]
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
	bne	.L3526
	mov	r1, r7
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #6]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	streq	r0, [r4, #52]
	bne	.L3527
.L3386:
	str	r0, [r4, #56]
	ldr	r1, .L3551+16
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #60]
	cmp	r3, #24
	bhi	.L3528
	ldr	r1, .L3551+20
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #64]
	cmp	r3, #24
	bhi	.L3529
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #13]
	ldr	r0, [r5, #2808]
	bl	BsGet
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #14]
	bne	.L3530
	ldr	r3, [r6, #188]
	strh	r3, [r4, #172]	@ movhi
	ldr	r3, [r6, #192]
	strh	r3, [r4, #212]	@ movhi
.L3424:
	ldr	r0, [r4, #68]
	cmp	r0, #0
	ble	.L3429
.L3423:
	ldr	ip, [r6, #140]
	add	r1, r4, #170
	mov	r3, #0
.L3428:
	ldrsh	r2, [r1, #2]!
	add	r3, r3, #1
	mul	r2, ip, r2
	cmp	r2, #64
	bhi	.L3427
	ldr	lr, [r6, #64]
	cmp	lr, #64
	bhi	.L3531
.L3427:
	cmp	r3, r0
	blt	.L3428
.L3429:
	ldr	r1, [r4, #72]
	cmp	r1, #0
	ble	.L3426
	ldr	r0, [r6, #140]
	ldrsh	r2, [r4, #212]
	mul	r2, r0, r2
	cmp	r2, #63
	addhi	r1, r1, #105
	addhi	r3, r4, #212
	addhi	r1, r4, r1, lsl #1
	bhi	.L3432
	b	.L3430
.L3433:
	ldrsh	r2, [r3, #2]!
	mul	r2, r0, r2
	cmp	r2, #63
	bls	.L3430
.L3432:
	cmp	r3, r1
	bne	.L3433
.L3426:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #17]
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #18]
	cmp	r0, #0
	bne	.L3532
.L3435:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #21]
	cmp	r0, #0
	beq	.L3438
	add	r1, r4, #256
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	bne	.L3533
.L3438:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	ldr	r1, .L3551+24
	strb	r0, [r4, #22]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	add	r2, r0, #2
	str	r2, [r4, #84]
	cmp	r2, #1
	ble	.L3439
	ldr	r3, [r6, #128]
	cmp	r2, r3
	bhi	.L3439
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #23]
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #24]
	cmp	r0, #0
	beq	.L3509
	ldrb	r6, [r5, #1]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L3534
.L3464:
	mov	r0, #0
	b	.L3509
.L3527:
	ldr	r1, .L3551+28
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #52]
	bls	.L3386
	mov	r0, r7
	ldr	r1, .L3551+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3530:
	ldr	r1, .L3551+36
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #19
	add	r2, r0, #1
	str	r2, [r4, #68]
	bhi	.L3535
	ldr	r1, .L3551+40
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #21
	add	r3, r0, #1
	str	r3, [r4, #72]
	bhi	.L3536
	ldr	r2, [r4, #68]
	cmp	r2, #10
	bgt	.L3537
	cmp	r3, #11
	ble	.L3394
	ldr	r1, .L3551+44
	mov	r2, #11
.L3520:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3551+48
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L3515
.L3516:
	mov	r3, #0
	ldr	r0, [r5, #276]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
.L3509:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3430:
	ldr	r1, .L3551+52
.L3518:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3551+48
	ldr	r4, [r3]
	cmp	r4, #0
	bne	.L3516
.L3515:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3531:
	ldr	r1, .L3551+56
	b	.L3518
.L3526:
	mov	r0, r7
	ldr	r1, .L3551+60
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3394:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	ldr	r7, [r4, #68]
	uxtb	r0, r0
	strb	r0, [r4, #15]
	cmp	r0, #0
	bne	.L3407
	cmp	r7, #1
	addgt	r9, r4, #86
	movgt	r8, r0
	bgt	.L3405
	b	.L3538
.L3540:
	cmp	r3, r2
	bhi	.L3403
	ldr	r7, [r4, #68]
	add	r8, r8, #1
	sub	r3, r7, #1
	cmp	r3, r8
	ble	.L3539
.L3405:
	ldr	r1, .L3551+64
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r9, #2]!	@ movhi
	ldr	r2, [r6, #188]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L3540
.L3403:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r8
	ldr	r1, .L3551+68
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3537:
	mov	r3, r2
	ldr	r1, .L3551+72
	mov	r2, #10
	b	.L3520
.L3532:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #19]
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r7, r0
	strb	r7, [r4, #20]
	cmp	r7, #0
	bne	.L3435
	ldr	r1, .L3551+76
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #76]
	bhi	.L3541
.L3437:
	ldr	r1, .L3551+80
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #80]
	bls	.L3435
	ldr	r1, .L3551+84
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #80]
	b	.L3435
.L3407:
	cmp	r7, #0
	addgt	r3, r4, #170
	movgt	r8, #0
	ble	.L3397
.L3415:
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
	bne	.L3415
.L3397:
	ldr	r10, [r4, #72]
	cmp	r10, #0
	addgt	r3, r4, #210
	movgt	r8, #0
	ble	.L3414
.L3416:
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
	bne	.L3416
.L3414:
	cmp	r7, #1
	bne	.L3422
	ldr	r0, [r4, #72]
	cmp	r0, #1
	beq	.L3423
.L3422:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	strb	r0, [r4, #16]
	b	.L3424
.L3377:
	mov	r2, r0
	ldr	r1, .L3551+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3523:
	mov	r2, r0
	ldr	r1, .L3551+92
	mov	r0, r7
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3524:
	mov	r0, r7
	ldr	r1, .L3551+96
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3525:
	mov	r0, r7
	ldr	r1, .L3551+100
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3528:
	ldr	r1, .L3551+104
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3529:
	ldr	r1, .L3551+108
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3439:
	ldr	r1, .L3551+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3539:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	ble	.L3401
.L3400:
	add	r8, r4, #126
	mov	r7, #0
	b	.L3412
.L3543:
	cmp	r3, r2
	bhi	.L3410
	ldr	r3, [r4, #72]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L3542
.L3412:
	ldr	r1, .L3551+116
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #192]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L3543
.L3410:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r7
	ldr	r1, .L3551+120
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3534:
	mov	r1, r6
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	mov	r7, r0
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, r6
	uxtb	r8, r0
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2808]
	bl	BsGet
	tst	r7, #255
	uxtb	r9, r0
	beq	.L3442
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3544
.L3443:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L3447
	ldr	r1, .L3551+124
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L3551+128
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #5
	bgt	.L3445
	cmp	r0, #0
	addge	r7, r0, #1
	movge	r6, #0
	blt	.L3447
.L3449:
	ldr	r1, .L3551+132
	add	r6, r6, #1
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	ldr	r1, .L3551+136
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	cmp	r6, r7
	bne	.L3449
.L3447:
	ldr	r1, .L3551+140
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L3551+144
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
.L3442:
	cmp	r8, #0
	beq	.L3441
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #1889]
	cmp	r0, #0
	streq	r0, [r4, #1956]
	bne	.L3545
.L3451:
	ldr	r1, .L3551+148
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	cmp	r0, #63
	bhi	.L3546
	add	r2, r4, #4096
	cmp	r0, #0
	mov	r3, #0
	mov	r1, #8
	str	r3, [r4, #1960]
	str	r3, [r4, #2216]
	str	r3, [r4, #2472]
	str	r3, [r4, #2728]
	str	r3, [r4, #2984]
	str	r3, [r4, #3240]
	str	r3, [r4, #3496]
	str	r3, [r4, #3752]
	str	r3, [r4, #4008]
	str	r3, [r2, #168]
	str	r1, [r2, #424]
	str	r1, [r2, #680]
	beq	.L3462
	add	r0, r0, #1888
	add	r7, r4, #1888
	add	r0, r0, #1
	add	r7, r7, #1
	add	r8, r4, r0
	b	.L3461
.L3455:
	mov	r6, r6, asl #2
	add	r3, r4, r6
	str	r0, [r3, #1960]
	str	r0, [r3, #2216]
	str	r0, [r3, #2472]
	str	r0, [r3, #2728]
.L3456:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L3547
	add	r3, r4, r6
	str	r0, [r3, #2984]
	str	r0, [r3, #3240]
	str	r0, [r3, #3496]
	str	r0, [r3, #3752]
.L3458:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #1]!
	cmp	r0, #0
	bne	.L3548
	add	r6, r4, r6
	mov	r2, #8
	add	r3, r6, #4096
	str	r0, [r6, #4008]
	str	r0, [r3, #168]
	str	r2, [r3, #424]
	str	r2, [r3, #680]
.L3460:
	cmp	r7, r8
	beq	.L3462
.L3461:
	mov	r1, #6
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r0, #63
	mov	r6, r0
	bgt	.L3549
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	beq	.L3455
	ldr	r1, .L3551+152
	mov	r6, r6, asl #2
	ldr	r0, [r5, #2808]
	add	r10, r4, r6
	bl	HEVC_se_v
	ldr	r1, .L3551+156
	str	r0, [r10, #1960]
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	ldr	r1, .L3551+160
	str	r0, [r10, #2216]
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	ldr	r1, .L3551+164
	str	r0, [r10, #2472]
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	str	r0, [r10, #2728]
	b	.L3456
.L3462:
	mov	r1, #1
	ldr	r0, [r5, #2808]
	bl	BsGet
.L3441:
	cmp	r9, #0
	bne	.L3508
	b	.L3464
.L3465:
	ldr	r0, [r5, #2808]
	bl	BsGet
	strb	r0, [r4, #25]
.L3508:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L3465
	b	.L3464
.L3548:
	ldr	r1, .L3551+168
	add	r6, r4, r6
	ldr	r0, [r5, #2808]
	add	r10, r6, #4096
	bl	HEVC_ue_v
	ldr	r1, .L3551+172
	str	r0, [r6, #4008]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L3551+176
	str	r0, [r10, #168]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	ldr	r1, .L3551+180
	str	r0, [r10, #424]
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	str	r0, [r10, #680]
	b	.L3460
.L3547:
	ldr	r1, .L3551+184
	add	r10, r4, r6
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	ldr	r1, .L3551+188
	str	r0, [r10, #2984]
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	ldr	r1, .L3551+192
	str	r0, [r10, #3240]
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	ldr	r1, .L3551+196
	str	r0, [r10, #3496]
	ldr	r0, [r5, #2808]
	bl	HEVC_se_v
	str	r0, [r10, #3752]
	b	.L3458
.L3544:
	ldr	r1, .L3551+200
	ldr	r0, [r5, #2808]
	bl	HEVC_ue_v
	b	.L3443
.L3549:
	mov	r2, r0
	mov	r3, #64
	ldr	r1, .L3551+204
	mov	r0, #1
	bl	dprint_vfmw
.L3448:
	ldr	r2, [r4, #84]
	mov	r0, #1
	ldr	r1, .L3551+208
	bl	dprint_vfmw
	b	.L3515
.L3535:
	mov	r3, #20
	ldr	r1, .L3551+212
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3545:
	mov	r1, #6
	ldr	r0, [r5, #2808]
	bl	BsGet
	cmp	r0, #1
	mov	r2, r0
	str	r0, [r4, #1956]
	ble	.L3451
	mov	r3, #2
	ldr	r1, .L3551+216
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3448
.L3541:
	ldr	r1, .L3551+220
	mov	r0, #1
	bl	dprint_vfmw
	str	r7, [r4, #76]
	b	.L3437
.L3542:
	ldr	r7, [r4, #68]
.L3401:
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3407
.L3408:
	sub	r2, r7, #1
	ldrh	r3, [r6, #188]
	add	ip, r4, r7, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #170]	@ movhi
	ble	.L3417
	add	r8, r7, #42
	add	r1, r4, #86
	add	lr, r4, #170
	add	r8, r4, r8, lsl #1
.L3418:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #170]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #170]	@ movhi
	bne	.L3418
.L3417:
	sxth	r3, r3
	cmp	r3, #0
	ble	.L3550
	ldr	r1, [r4, #72]
	ldrh	r3, [r6, #192]
	sub	r2, r1, #1
	add	ip, r4, r1, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #210]	@ movhi
	ble	.L3420
	add	r8, r1, #62
	add	lr, r4, #210
	add	r1, r4, #126
	add	r8, r4, r8, lsl #1
.L3421:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #210]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #210]	@ movhi
	bne	.L3421
.L3420:
	sxth	r3, r3
	cmp	r3, #0
	bgt	.L3414
	ldr	r1, .L3551+224
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3536:
	mov	r2, r3
	ldr	r1, .L3551+228
	mov	r3, #22
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3533:
	ldr	r1, .L3551+232
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3538:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	bgt	.L3400
	b	.L3408
.L3550:
	ldr	r1, .L3551+236
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3509
.L3445:
	mov	r2, r0
	ldr	r1, .L3551+240
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3448
.L3546:
	mov	r2, r0
	mov	r3, #64
	ldr	r1, .L3551+244
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3448
.L3552:
	.align	2
.L3551:
	.word	.LC356
	.word	.LC359
	.word	.LC361
	.word	.LC363
	.word	.LC367
	.word	.LC369
	.word	.LC390
	.word	.LC365
	.word	.LC366
	.word	.LC371
	.word	.LC373
	.word	.LC376
	.word	g_event_report
	.word	.LC384
	.word	.LC383
	.word	.LC364
	.word	.LC377
	.word	.LC378
	.word	.LC375
	.word	.LC385
	.word	.LC387
	.word	.LC388
	.word	.LC357
	.word	.LC358
	.word	.LC360
	.word	.LC362
	.word	.LC368
	.word	.LC370
	.word	.LC391
	.word	.LC379
	.word	.LC380
	.word	.LC395
	.word	.LC396
	.word	.LC398
	.word	.LC399
	.word	.LC393
	.word	.LC394
	.word	.LC401
	.word	.LC404
	.word	.LC405
	.word	.LC406
	.word	.LC407
	.word	.LC412
	.word	.LC413
	.word	.LC414
	.word	.LC415
	.word	.LC408
	.word	.LC409
	.word	.LC410
	.word	.LC411
	.word	.LC392
	.word	.LC403
	.word	.LC416
	.word	.LC372
	.word	.LC400
	.word	.LC386
	.word	.LC382
	.word	.LC374
	.word	.LC389
	.word	.LC381
	.word	.LC397
	.word	.LC402
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
	ldr	r6, .L3565
	mov	r4, r0
	ldr	r0, [r6]
	cmp	r0, #0
	beq	.L3560
	ldr	r1, .L3565+4
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r3, [r4, #164]
	cmp	r0, r3
	mov	r7, r0
	bcs	.L3561
	movw	r8, #5036
	ldr	r3, [r4, #2820]
	mul	r5, r8, r0
	add	r2, r3, r5
	ldrb	r10, [r3, r5]	@ zero_extendqisi2
	cmp	r10, #0
	bne	.L3562
	str	r0, [r2, #28]
	mov	r0, r4
	ldr	r1, [r4, #2820]
	add	r1, r1, r5
	bl	HEVC_ProcessPPS
	subs	r9, r0, #0
	bne	.L3563
	ldr	r3, [r4, #2820]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2820]
	strb	r2, [r3, r5]
.L3555:
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3562:
	ldr	r6, [r6]
	mov	r2, r8
	ldr	r10, .L3565+8
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
	bne	.L3564
	mov	r3, #1
	strb	r3, [r6, #1]
	strb	r3, [r6]
	mov	r2, r8
	ldr	r0, [r4, #2820]
	mov	r1, r6
	ldr	r3, [r10, #56]
	add	r0, r0, r5
	blx	r3
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3564:
	mov	r2, r7
	ldr	r1, .L3565+12
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	b	.L3555
.L3561:
	mov	r2, r0
	ldr	r1, .L3565+16
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	b	.L3555
.L3563:
	mov	r2, r7
	ldr	r1, .L3565+12
	mov	r0, #1
	mvn	r9, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2820]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2820]
	strb	r10, [r3, r5]
	b	.L3555
.L3560:
	ldr	r2, .L3565+20
	mvn	r9, #0
	ldr	r1, .L3565+24
	bl	dprint_vfmw
	b	.L3555
.L3566:
	.align	2
.L3565:
	.word	.LANCHOR1
	.word	.LC417
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC419
	.word	.LC418
	.word	.LANCHOR0+720
	.word	.LC72
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
	ldr	r3, [r0, #2820]
	mov	r7, r0
	ldr	r2, [r4, #748]
	movw	r0, #5036
	ldr	r1, [r4, #732]
	ldr	r5, [r7, #2816]
	mla	r3, r0, r2, r3
	cmp	r1, #1
	ldr	r6, [r3, #32]
	beq	.L3633
	cmp	r1, #0
	bne	.L3571
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3571
.L3569:
	ldr	r1, .L3644
	ldr	r0, [r7, #2808]
	bl	HEVC_ue_v
	cmp	r0, #7
	str	r0, [r4, #868]
	bhi	.L3634
	movw	r9, #12668
	mla	r9, r9, r6, r5
	ldr	r3, [r9, #60]
	cmp	r3, #0
	streq	r0, [r4, #1000]
	bne	.L3635
.L3611:
	ldr	r3, [r4, #788]
	cmp	r3, #0
	subne	r3, fp, #172
	strne	r3, [fp, #-176]
	movne	r5, #0
	movne	r6, r3
	beq	.L3577
.L3578:
	mov	r1, #1
	ldr	r0, [r7, #2808]
	bl	BsGet
	ldr	r3, [r4, #788]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L3578
	ldr	r2, [r9, #60]
	cmp	r2, #0
	beq	.L3579
	cmp	r3, #0
	subne	r6, fp, #108
	movne	r5, #0
	beq	.L3577
.L3583:
	mov	r1, #1
	ldr	r0, [r7, #2808]
	bl	BsGet
	ldr	r3, [r4, #788]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L3583
.L3579:
	cmp	r3, #0
	beq	.L3577
	add	r6, r7, #5056
	add	r10, r7, #5120
	add	r6, r6, #44
	add	r10, r10, #52
	mov	r5, #0
	b	.L3594
.L3584:
	ldr	r2, [r4, #868]
	mov	r3, #1
	str	r1, [r6, #-132]
	mov	r2, r3, asl r2
	str	r2, [r6]
.L3586:
	ldr	r2, [r9, #60]
	cmp	r2, #0
	beq	.L3588
	sub	r2, fp, #108
	ldr	r2, [r2, r5, asl #2]
	cmp	r2, #0
	bne	.L3589
	ldr	r1, [r4, #1000]
	mov	r3, #1
	str	r2, [r10, #120]
	mov	r1, r3, asl r1
	str	r2, [r10, #124]
	str	r1, [r10, #-8]
	str	r1, [r10, #-4]
.L3588:
	ldr	r2, [r4, #788]
	add	r5, r5, #1
	add	r6, r6, #4
	add	r10, r10, #8
	cmp	r2, r5
	bls	.L3577
.L3594:
	ldr	r3, [fp, #-176]
	ldr	r1, [r3, r5, asl #2]
	cmp	r1, #0
	beq	.L3584
	ldr	r1, .L3644+4
	ldr	r0, [r7, #2808]
	bl	HEVC_se_v
	add	r2, r0, #128
	cmp	r2, #255
	bhi	.L3636
	ldr	r2, [r4, #868]
	mov	r3, #1
	ldr	r1, .L3644+8
	add	r0, r0, r3, asl r2
	str	r0, [r6]
	ldr	r0, [r7, #2808]
	bl	HEVC_se_v
	add	r2, r0, #128
	str	r0, [r6, #-132]
	cmp	r2, #255
	bls	.L3586
	mov	r2, r0
	ldr	r1, .L3644+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3633:
	ldrb	r3, [r3, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3569
.L3571:
	mov	r0, #0
.L3632:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3589:
	sub	r8, r10, #8
	str	r5, [fp, #-180]
	mov	r5, r4
.L3592:
	ldr	r1, .L3644+16
	mov	r4, r8
	ldr	r0, [r7, #2808]
	bl	HEVC_se_v
	ldr	r1, .L3644+20
	add	r3, r0, #128
	cmp	r3, #255
	bhi	.L3637
	ldr	r3, [r5, #1000]
	mov	r2, #1
	add	r8, r8, #4
	add	r0, r0, r2, asl r3
	str	r0, [r8, #-4]
	ldr	r0, [r7, #2808]
	bl	HEVC_se_v
	add	r3, r0, #512
	cmp	r3, #1024
	bcs	.L3638
	ldr	r1, [r4]
	cmp	r10, r8
	ldr	r3, [r5, #1000]
	mov	r1, r1, asl #7
	mov	r3, r1, asr r3
	rsb	r3, r3, #128
	add	r0, r0, r3
	ssat	r0, #8, r0
	str	r0, [r8, #124]
	bne	.L3592
	mov	r4, r5
	ldr	r5, [fp, #-180]
	b	.L3588
.L3577:
	ldr	r5, [r4, #732]
	cmp	r5, #0
	bne	.L3571
	ldr	r3, [r4, #792]
	cmp	r3, #0
	beq	.L3571
	sub	r3, fp, #172
	str	r3, [fp, #-176]
	mov	r6, r3
.L3595:
	mov	r1, #1
	ldr	r0, [r7, #2808]
	bl	BsGet
	ldr	r3, [r4, #792]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L3595
	ldr	r2, [r9, #60]
	cmp	r2, #0
	bne	.L3639
.L3596:
	cmp	r3, #0
	beq	.L3571
	add	r6, r7, #5376
	add	r10, r7, #5440
	add	r6, r6, #44
	add	r10, r10, #52
	mov	r5, #0
	b	.L3610
.L3600:
	ldr	r2, [r4, #868]
	mov	r3, #1
	str	r1, [r6, #-388]
	mov	r2, r3, asl r2
	str	r2, [r6]
.L3602:
	ldr	r2, [r9, #60]
	cmp	r2, #0
	beq	.L3604
	sub	r2, fp, #108
	ldr	r2, [r2, r5, asl #2]
	cmp	r2, #0
	bne	.L3605
	ldr	r1, [r4, #1000]
	mov	r3, #1
	str	r2, [r10, #120]
	mov	r1, r3, asl r1
	str	r2, [r10, #124]
	str	r1, [r10, #-8]
	str	r1, [r10, #-4]
.L3604:
	ldr	r2, [r4, #792]
	add	r5, r5, #1
	add	r6, r6, #4
	add	r10, r10, #8
	cmp	r2, r5
	bls	.L3571
.L3610:
	ldr	r3, [fp, #-176]
	ldr	r1, [r3, r5, asl #2]
	cmp	r1, #0
	beq	.L3600
	ldr	r1, .L3644+24
	ldr	r0, [r7, #2808]
	bl	HEVC_se_v
	add	r2, r0, #128
	cmp	r2, #255
	bhi	.L3640
	ldr	r2, [r4, #868]
	mov	r3, #1
	ldr	r1, .L3644+28
	add	r0, r0, r3, asl r2
	str	r0, [r6]
	ldr	r0, [r7, #2808]
	bl	HEVC_se_v
	add	r2, r0, #128
	str	r0, [r6, #-388]
	cmp	r2, #255
	bls	.L3602
	ldr	r1, .L3644+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3605:
	sub	r8, r10, #8
	str	r5, [fp, #-180]
	mov	r5, r4
.L3608:
	ldr	r1, .L3644+36
	mov	r4, r8
	ldr	r0, [r7, #2808]
	bl	HEVC_se_v
	ldr	r1, .L3644+40
	add	r3, r0, #128
	cmp	r3, #255
	bhi	.L3641
	ldr	r3, [r5, #1000]
	mov	r2, #1
	add	r8, r8, #4
	add	r0, r0, r2, asl r3
	str	r0, [r8, #-4]
	ldr	r0, [r7, #2808]
	bl	HEVC_se_v
	add	r3, r0, #512
	cmp	r3, #1024
	bcs	.L3642
	ldr	r1, [r4]
	cmp	r10, r8
	ldr	r3, [r5, #1000]
	mov	r1, r1, asl #7
	mov	r3, r1, asr r3
	rsb	r3, r3, #128
	add	r3, r0, r3
	ssat	r3, #8, r3
	str	r3, [r8, #124]
	bne	.L3608
	mov	r4, r5
	ldr	r5, [fp, #-180]
	b	.L3604
.L3635:
	ldr	r1, .L3644+44
	ldr	r0, [r7, #2808]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #14
	bhi	.L3643
	ldr	r3, [r4, #868]
	add	r0, r0, r3
	str	r0, [r4, #1000]
	cmp	r0, #7
	bls	.L3611
	ldr	r1, .L3644+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3637:
	ldr	r1, .L3644+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3638:
	ldr	r1, .L3644+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3639:
	cmp	r3, #0
	subne	r6, fp, #108
	movne	r5, #0
	beq	.L3571
.L3599:
	mov	r1, #1
	ldr	r0, [r7, #2808]
	bl	BsGet
	ldr	r3, [r4, #792]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r6], #4
	bhi	.L3599
	b	.L3596
.L3636:
	mov	r2, r0
	ldr	r1, .L3644+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3641:
	ldr	r1, .L3644+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3642:
	ldr	r1, .L3644+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3640:
	ldr	r1, .L3644+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3634:
	ldr	r1, .L3644+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3643:
	ldr	r1, .L3644+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3632
.L3645:
	.align	2
.L3644:
	.word	.LC420
	.word	.LC425
	.word	.LC427
	.word	.LC428
	.word	.LC429
	.word	.LC431
	.word	.LC433
	.word	.LC435
	.word	.LC436
	.word	.LC437
	.word	.LC439
	.word	.LC422
	.word	.LC424
	.word	.LC430
	.word	.LC432
	.word	.LC426
	.word	.LC438
	.word	.LC440
	.word	.LC434
	.word	.LC421
	.word	.LC423
	UNWIND(.fnend)
	.size	HEVC_DecPredWeightTable, .-HEVC_DecPredWeightTable
	.align	2
	.global	HEVC_DecSliceSegmentHeader
	.type	HEVC_DecSliceSegmentHeader, %function
HEVC_DecSliceSegmentHeader:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
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
	ldr	r3, [r0, #2828]
	add	r5, r0, #4096
	mov	r4, r0
	mov	r1, #1
	ldr	r0, [r0, #2808]
	ldr	r3, [r3, #24]
	str	r3, [fp, #-48]
	bl	BsGet
	ldr	r6, [r5, #740]
	sub	r3, r6, #16
	cmp	r3, #5
	movhi	r3, #0
	movls	r3, #1
	cmp	r3, #0
	str	r3, [fp, #-68]
	strb	r0, [r5, #712]
	bne	.L3962
.L3647:
	ldr	r1, .L4009
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r5, #748]
	ldr	r3, [r4, #164]
	blt	.L3649
	cmp	r0, r3
	bge	.L3649
	mov	r0, r4
	bl	HEVC_VpsSpsPpsCheck
	subs	r3, r0, #0
	str	r3, [fp, #-84]
	bne	.L3963
	ldr	r1, [r5, #748]
	movw	r8, #5036
	ldr	r3, [r4, #2820]
	movw	r7, #12668
	ldr	r2, [r4, #2816]
	mla	r8, r8, r1, r3
	ldr	r3, [r4, #2812]
	str	r3, [fp, #-52]
	ldr	r1, [r8, #32]
	ldrb	r3, [r8, #2]	@ zero_extendqisi2
	mla	r7, r7, r1, r2
	cmp	r3, #0
	ldr	r3, [r7, #48]
	str	r3, [fp, #-56]
	bne	.L3964
.L3655:
	mov	r3, #0
	strb	r3, [r5, #713]
.L3656:
	ldr	r9, [r7, #140]
	ldr	r3, [r7, #144]
	cmp	r9, #0
	beq	.L3658
	cmp	r3, #0
	beq	.L3658
	ldr	r0, [r7, #68]
	mov	r1, r3
	add	r0, r3, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	mov	r1, r9
	mov	r10, r0
	ldr	r0, [r7, #64]
	add	r0, r9, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	ldr	r2, [r7, #172]
	mov	r1, #1
	mov	r2, r2, asl r1
	mov	r9, r1, asl r2
	mul	r0, r0, r10
	cmp	r0, r1
	ble	.L3821
	mov	r3, r1
	mov	r1, #0
.L3661:
	add	r1, r1, #1
	cmp	r0, r3, asl r1
	bgt	.L3661
.L3660:
	ldrb	r3, [r5, #712]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [fp, #-72]
	beq	.L3965
.L3662:
	ldrb	r3, [r5, #713]	@ zero_extendqisi2
	ldr	r2, [r4, #192]
	cmp	r3, #0
	str	r2, [r5, #724]
	bne	.L3665
	ldrb	r10, [r4, #1]	@ zero_extendqisi2
	cmp	r10, #1
	beq	.L3666
	ldr	r2, [r8, #36]
	cmp	r2, #0
	movne	r10, r3
	beq	.L3670
.L3672:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r3, [r8, #36]
	add	r10, r10, #1
	cmp	r3, r10
	bhi	.L3672
.L3670:
	ldr	r1, .L4009+4
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	cmp	r0, #2
	str	r0, [r5, #732]
	bhi	.L3966
	ldrb	r3, [r8, #4]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3967
.L3673:
	sub	r6, r6, #19
	ldr	r1, [fp, #-56]
	cmp	r6, #1
	ldr	r0, [fp, #-52]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	movhi	r2, #0
	movls	r2, #1
	str	r2, [fp, #-80]
	movw	r2, #24912
	mla	r2, r2, r1, r0
	cmp	r3, #1
	str	r2, [fp, #-92]
	movne	r2, #0
	strne	r2, [fp, #-76]
	strne	r2, [fp, #-64]
	beq	.L3968
.L3674:
	ldr	r2, [fp, #-80]
	cmp	r2, #0
	bne	.L3678
	cmp	r3, #0
	beq	.L3969
.L3679:
	ldr	r3, [r7, #116]
	mov	r2, #1
	ldr	r6, [r4, #188]
	mov	r3, r2, asl r3
	str	r3, [fp, #-88]
	mov	r1, r3
	mov	r0, r6
	bl	__aeabi_uidivmod
	ldr	r3, [fp, #-64]
	cmp	r3, r1
	rsb	r3, r1, r6
	bcs	.L3680
	ldr	r0, [fp, #-88]
	ldr	r2, [fp, #-64]
	rsb	r2, r2, r1
	cmp	r2, r0, lsr #1
	movcs	r2, r0
	addcs	r3, r3, r2
	bcs	.L3681
.L3680:
	ldr	r2, [fp, #-64]
	cmp	r2, r1
	bls	.L3681
	rsb	r1, r1, r2
	ldr	r2, [fp, #-88]
	cmp	r1, r2, lsr #1
	rsbhi	r3, r2, r3
.L3681:
	ldr	r1, [r5, #740]
	ldr	r2, [fp, #-48]
	sub	r1, r1, #16
	cmp	r1, #2
	ldr	r1, [fp, #-64]
	add	r2, r4, r2, lsl #2
	movls	r3, #0
	add	r3, r3, r1
	str	r3, [r5, #724]
	ldr	r2, [r2, #212]
	cmp	r3, r2
	bge	.L3683
	ldrb	r0, [r5, #712]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L3970
.L3683:
	ldr	r3, [r4, #2368]
	cmp	r3, #0
	ldreq	r3, [r5, #724]
	streq	r3, [r4, #192]
	ldr	r3, [r5, #736]
	cmp	r3, #0
	bne	.L3685
	ldr	r3, [r5, #740]
	cmp	r3, #15
	bhi	.L3686
	tst	r3, #1
	movne	r2, #1
	beq	.L3686
.L3687:
	sub	r3, r3, #7
	bics	r3, r3, #2
	andne	r3, r2, #1
	moveq	r3, #0
	cmp	r3, #0
	ldrne	r3, [r5, #724]
	strne	r3, [r4, #188]
.L3685:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L3688
	ldr	r3, [r7, #176]
	mov	r1, #0
	cmp	r3, #1
	movhi	r2, #1
	bls	.L3690
.L3692:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L3692
	cmp	r1, #0
	bne	.L3971
.L3693:
	mov	r2, #164
	add	r0, r5, #1632
	mla	r1, r2, r1, r7
	add	r3, r4, #5696
	add	r0, r0, #12
	add	r3, r3, #44
	str	r3, [fp, #-76]
	add	r1, r1, #2160
	add	r1, r1, #4
	bl	memcpy
.L3691:
	ldrb	r3, [r7, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3695
	ldr	r3, [r7, #180]
	ldr	r6, [r5, #1648]
	cmp	r3, #0
	ldr	r2, [r5, #1644]
	streq	r3, [fp, #-96]
	add	r6, r6, r2
	streq	r3, [fp, #-48]
	streq	r3, [fp, #-56]
	bne	.L3972
.L3696:
	ldr	r1, .L4009+8
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r2, [r5, #1644]
	ldr	r3, [r5, #1648]
	ldr	ip, [fp, #-48]
	add	r1, r3, r2
	add	r0, r0, ip
	str	r0, [fp, #-60]
	add	r1, r1, r0
	cmp	r1, #16
	bhi	.L3973
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	add	r3, r6, r3
	str	r3, [fp, #-100]
	beq	.L3712
	ldr	r2, [fp, #-100]
	str	r8, [fp, #-104]
	add	r9, r2, #5696
	add	r3, r2, #1216
	add	r9, r9, #55
	add	r3, r3, #7
	add	r2, r4, r9
	add	r10, r4, r3, lsl #2
	mov	r1, r2
	mov	r2, #0
	mov	r9, r2
	str	r2, [fp, #-52]
	mov	r8, r1
	b	.L3711
.L3977:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	ldreq	r0, [fp, #-56]
	bne	.L3974
.L3703:
	add	r1, r7, r0
	add	r0, r7, r0, lsl #2
	ldrb	r1, [r1, #13]	@ zero_extendqisi2
	ldr	r6, [r0, #196]
	strb	r1, [r8]
.L3706:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L3975
	ldr	r3, [fp, #-48]
	str	r6, [r10, #944]
	cmp	r9, r3
	cmpne	r9, #0
	ldr	r3, [fp, #-52]
	str	r0, [r10]
	ldr	r1, [r5, #724]
	moveq	r3, #0
	str	r3, [fp, #-52]
	rsb	r6, r1, r6
	str	r6, [r10, #876]
.L3709:
	ldr	r3, [fp, #-60]
	add	r9, r9, #1
	sub	r10, r10, #4
	sub	r8, r8, #1
	cmp	r9, r3
	beq	.L3976
.L3711:
	ldr	r3, [fp, #-48]
	cmp	r3, r9
	bhi	.L3977
	ldr	r1, [r7, #120]
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	mov	r6, r0
	ldr	r0, [r4, #2808]
	bl	BsGet
	strb	r0, [r8]
	b	.L3706
.L3998:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #717]
	cmp	r0, #0
	bne	.L3978
	ldr	r3, [r5, #732]
	ldr	r2, [r8, #40]
	cmp	r3, #0
	str	r2, [r5, #788]
	bne	.L3754
	ldr	r2, [r8, #44]
	mov	r9, r3
	mov	r6, r3
	str	r2, [r5, #792]
.L3755:
	ldr	r3, [fp, #-76]
	cmp	r3, #0
	beq	.L3979
	ldr	r3, [fp, #-76]
	ldr	r2, [r3, #8]
	cmp	r2, #16
	bhi	.L3758
	cmp	r2, #0
	moveq	r3, r2
	beq	.L3760
	ldr	r3, [fp, #-76]
	add	r2, r2, #11
	add	r1, r3, #11
	add	r0, r3, r2
	mov	r3, #0
.L3762:
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	cmp	r2, #0
	addne	r3, r3, #1
	cmp	r1, r0
	bne	.L3762
.L3760:
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #1
	ldreq	r2, [r5, #2072]
	addeq	r3, r3, r2
	ldrb	r2, [r8, #22]	@ zero_extendqisi2
	cmp	r2, #0
	cmpne	r3, #1
	ble	.L3958
	add	r2, r4, #5888
	add	r1, r4, #4800
	add	r2, r2, #16
	add	r1, r1, #8
	mov	r0, r4
	bl	HEVC_DecRefPicListsModification
	cmp	r0, #0
	bne	.L3980
.L3756:
	ldr	r3, [r5, #732]
	cmp	r3, #0
	beq	.L3818
.L3764:
	cmp	r3, #2
	beq	.L3748
.L3819:
	ldrb	r3, [r8, #5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3981
.L3765:
	ldrb	r3, [r5, #716]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r5, #732]
	beq	.L3774
	cmp	r3, #0
	beq	.L3982
	cmp	r3, #2
	mov	r3, #1
	strb	r3, [r5, #720]
	beq	.L3771
.L3770:
	ldr	r3, [r5, #788]
	cmp	r3, #1
	bhi	.L3773
.L3952:
	ldr	r3, [r5, #732]
.L3774:
	ldrb	r2, [r8, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3778
	cmp	r3, #1
	beq	.L3781
.L3778:
	ldrb	r2, [r8, #11]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3769
	cmp	r3, #0
	bne	.L3769
.L3781:
	mov	r0, r4
	bl	HEVC_DecPredWeightTable
	cmp	r0, #0
	ldreq	r3, [r5, #732]
	bne	.L3983
.L3769:
	cmp	r3, #2
	beq	.L3782
	ldr	r1, .L4009+12
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	rsb	r3, r0, #4
	rsb	r2, r0, #5
	cmp	r3, #4
	str	r2, [r5, #760]
	bhi	.L3984
.L3782:
	ldr	r1, .L4009+16
	ldr	r0, [r4, #2808]
	bl	HEVC_se_v
	ldr	r2, [r8, #48]
	add	r2, r0, r2
	str	r2, [r5, #728]
	ldr	r3, [r7, #92]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L3985
	ldrb	r3, [r8, #9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3986
.L3784:
	ldrb	r3, [r8, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3953
	ldrb	r3, [r8, #19]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3987
.L3790:
	ldrb	r0, [r8, #20]	@ zero_extendqisi2
	strb	r0, [r5, #721]
	ldr	r3, [r8, #76]
	str	r3, [r5, #772]
	ldr	r3, [r8, #80]
	str	r3, [r5, #776]
.L3789:
	ldrb	r3, [r7, #6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3793
	movw	r3, #714
	ldrh	r2, [r5, r3]
	adds	r3, r2, #0
	movne	r3, #1
.L3793:
	ldrb	r2, [r8, #17]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3794
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L3988
.L3794:
	strb	r2, [r5, #722]
.L3665:
	ldr	r3, [r8, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	bne	.L3795
.L3802:
	ldrb	r3, [r8, #23]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3989
.L3797:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	bne	.L3990
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [fp, #-68]
	beq	.L3813
	cmp	r3, #0
	beq	.L3814
	ldr	r3, [r5, #744]
	mov	r2, #1
	add	r3, r4, r3
	strb	r2, [r3, #6]
.L3811:
	ldr	r2, [r5, #724]
	ldr	r1, [fp, #-68]
	cmp	r2, #0
	moveq	r1, #0
	andne	r1, r1, #1
	cmp	r1, #0
	bne	.L3991
.L3812:
	mov	r2, #0
	strb	r2, [r3, #4]
.L3816:
	mov	r0, r4
	bl	HEVC_IsNewPic
	str	r0, [r5, #864]
	mov	r0, r4
	bl	HEVC_ReadByteAlignment
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L3948:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3964:
	ldrb	r3, [r5, #712]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3655
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	strb	r0, [r5, #713]
	b	.L3656
.L3990:
	ldr	r3, [r5, #744]
	add	r3, r4, r3
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3811
	b	.L3812
.L3962:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L3647
.L3965:
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #752]
	blt	.L3992
	ldr	r1, [r7, #192]
	ldr	r3, [r7, #188]
	mul	r3, r3, r1
	cmp	r3, r0
	bls	.L3664
	mul	r3, r9, r0
	str	r3, [fp, #-72]
	b	.L3662
.L3795:
	ldr	r1, .L4009+20
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r3, [r8, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	ldreq	r3, [r7, #192]
	subeq	r3, r3, #1
	mov	r6, r0
	beq	.L3799
	cmp	r3, #256
	ldreq	r2, [r8, #68]
	ldreq	r3, [r8, #72]
	ldrne	r3, [r7, #192]
	ldrne	r2, [r8, #68]
	mul	r3, r3, r2
	sub	r3, r3, #1
.L3799:
	cmp	r3, #255
	movcs	r3, #255
	cmp	r6, r3
	bhi	.L3993
	cmp	r6, #0
	beq	.L3802
	ldr	r1, .L4009+24
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	cmp	r0, #31
	add	r7, r0, #1
	movls	r9, #0
	bhi	.L3994
.L3804:
	add	r9, r9, #1
	mov	r1, r7
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r9, r6
	bne	.L3804
	ldrb	r3, [r8, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3797
.L3989:
	ldr	r1, .L4009+28
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	cmp	r0, #256
	mov	r7, r0
	bhi	.L3995
	ldr	r0, [r4, #2808]
	bl	BsResidBits
	cmp	r7, r0
	bhi	.L3808
	cmp	r7, #0
	movne	r6, #0
	beq	.L3797
.L3810:
	add	r6, r6, #1
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	cmp	r6, r7
	bne	.L3810
	b	.L3797
.L3678:
	mov	r2, #0
	str	r2, [r5, #724]
	ldr	r2, [r4, #2368]
	cmp	r2, #0
	streq	r2, [r4, #192]
	ldr	r2, [r5, #736]
	cmp	r2, #0
	streq	r2, [r4, #188]
.L3714:
	cmp	r3, #1
	beq	.L3996
.L3716:
	ldrb	r3, [r7, #6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3997
.L3746:
	ldr	r3, [fp, #-80]
	cmp	r3, #0
	movne	r3, #0
	strneb	r3, [r5, #716]
	ldr	r3, [r5, #732]
	cmp	r3, #2
	bne	.L3998
.L3748:
	ldrb	r3, [r5, #716]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3771
	mov	r3, #1
	strb	r3, [r5, #720]
	mov	r3, #2
	b	.L3774
.L3813:
	cmp	r3, #0
	beq	.L3814
	ldr	r3, [r5, #744]
	ldrb	r2, [fp, #-72]	@ zero_extendqisi2
	add	r3, r4, r3
	strb	r2, [r3, #6]
	b	.L3812
.L3991:
	ldr	r2, [r5, #740]
	cmp	r2, #21
	moveq	r2, #1
	streqb	r2, [r3, #4]
	bne	.L3812
	b	.L3816
.L3686:
	sub	r2, r3, #16
	cmp	r2, #7
	movhi	r2, #0
	movls	r2, #1
	b	.L3687
.L3975:
	ldr	r1, .L4009+32
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-48]
	cmp	r9, #0
	cmpne	r9, r3
	ldrne	r3, [fp, #-52]
	addne	r0, r0, r3
	mov	r3, #1
	str	r3, [r10]
	ldr	r3, [fp, #-64]
	ldr	r1, [r5, #724]
	str	r0, [fp, #-52]
	rsb	ip, r3, r1
	ldr	r3, [fp, #-88]
	add	r6, ip, r6
	mls	r0, r3, r0, r6
	rsb	r1, r1, r0
	str	r1, [r10, #876]
	str	r0, [r10, #944]
	b	.L3709
.L3974:
	ldr	r1, [fp, #-96]
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r1, [r7, #180]
	sub	r1, r1, #1
	cmp	r0, #0
	blt	.L3705
	cmp	r1, r0
	bcs	.L3703
.L3705:
	str	r1, [sp]
	mov	r3, r0
	mov	r2, r9
	ldr	r1, .L4009+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3982:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r3, [r5, #732]
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r5, #720]
	beq	.L3782
	cmp	r0, #0
	bne	.L3770
	ldr	r2, [r5, #792]
	cmp	r2, #1
	bls	.L3774
.L3773:
	ldr	r1, .L4009+40
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldrb	r2, [r5, #720]	@ zero_extendqisi2
	cmp	r2, #0
	str	r0, [r5, #756]
	bne	.L3999
	cmp	r9, #0
	subne	r6, r9, #1
	moveq	r6, r2
.L3776:
	cmp	r6, r0
	movcs	r3, #0
	movcc	r3, #1
	orrs	r3, r3, r0, lsr #31
	beq	.L3952
	mov	r3, r0
	str	r6, [sp]
	ldr	r1, .L4009+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3814:
	ldr	r3, [r5, #744]
	add	r3, r4, r3
	b	.L3812
.L3953:
	ldrb	r0, [r5, #721]	@ zero_extendqisi2
	b	.L3789
.L3976:
	ldr	r8, [fp, #-104]
.L3712:
	ldr	r3, [fp, #-100]
	cmp	r3, #16
	str	r3, [r5, #1652]
	bhi	.L4000
.L3695:
	ldrb	r3, [r7, #9]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r5, #716]
	ldreqb	r3, [r4, #1]	@ zero_extendqisi2
	beq	.L3714
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	strb	r0, [r5, #716]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	b	.L3714
.L3958:
	ldr	r3, [r5, #732]
	cmp	r3, #0
	bne	.L3819
.L3818:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r3, [r5, #732]
	strb	r0, [r5, #718]
	b	.L3764
.L3967:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	b	.L3673
.L3968:
	ldr	r1, [fp, #-48]
	add	r2, r1, #4096
	cmp	r1, #0
	add	r2, r2, #44
	ldr	r1, [fp, #-92]
	add	r2, r1, r2, lsl #2
	ldr	r2, [r2, #4]
	beq	.L3675
	add	r2, r1, r2
	add	r2, r2, #12416
	ldrb	r2, [r2, #7]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3675
.L3676:
	ldr	r1, [r7, #120]
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	str	r0, [fp, #-64]
.L3677:
	add	r2, r4, #5696
	add	r2, r2, #44
	str	r2, [fp, #-76]
	b	.L3674
.L3675:
	ldr	r2, [fp, #-80]
	cmp	r2, #0
	movne	r2, #0
	strne	r2, [fp, #-64]
	bne	.L3677
	b	.L3676
.L3997:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #714]
	ldr	r0, [r4, #2808]
	bl	BsGet
	strb	r0, [r5, #715]
	b	.L3746
.L3649:
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L4009+48
	mov	r0, #1
	ldr	r1, .L4009+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3986:
	ldr	r1, .L4009+56
	ldr	r0, [r4, #2808]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #764]
	cmp	r3, #24
	bhi	.L4001
	ldr	r3, [r8, #60]
	add	r2, r0, r3
	add	r2, r2, #12
	cmp	r2, #24
	bhi	.L4002
	ldr	r1, .L4009+60
	ldr	r0, [r4, #2808]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #768]
	cmp	r3, #24
	bhi	.L4003
	ldr	r2, [r8, #64]
	add	r2, r0, r2
	add	r3, r2, #12
	cmp	r3, #24
	bls	.L3784
	ldr	r1, .L4009+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3981:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	strb	r0, [r5, #719]
	b	.L3765
.L3821:
	mov	r1, #0
	b	.L3660
.L3754:
	mov	r9, r0
	mov	r6, r0
	str	r0, [r5, #792]
.L3753:
	cmp	r3, #2
	bne	.L3755
	b	.L3756
.L3969:
	ldr	r1, [r7, #120]
	ldr	r0, [r4, #2808]
	bl	BsGet
	str	r0, [fp, #-64]
	b	.L3679
.L3688:
	add	r6, r4, #5696
	ldr	r3, [r7, #176]
	add	r6, r6, #44
	mov	r1, r7
	mov	r0, r4
	mov	r2, r6
	bl	HEVC_DecShortTermRefPicSet
	cmp	r0, #0
	streq	r6, [fp, #-76]
	beq	.L3691
	ldr	r1, .L4009+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3666:
	ldr	r3, [r8, #36]
	cmp	r3, #0
	beq	.L3670
	mov	r1, r10
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r3, [r8, #36]
	cmp	r3, #1
	bls	.L3670
	mov	r1, r10
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r3, [r8, #36]
	cmp	r3, #2
	bls	.L3670
	mov	r1, r10
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r3, [r8, #36]
	cmp	r3, #3
	bls	.L3670
	mov	r10, #3
.L3671:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r3, [r8, #36]
	add	r10, r10, #1
	cmp	r10, r3
	bcc	.L3671
	b	.L3670
.L3978:
	ldr	r1, .L4009+72
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	add	r6, r0, #1
	cmp	r6, #16
	bhi	.L4004
	ldr	r3, [r5, #732]
	str	r6, [r5, #788]
	cmp	r3, #0
	movne	r9, #0
	strne	r9, [r5, #792]
	bne	.L3753
	ldr	r1, .L4009+76
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	add	r9, r0, #1
	cmp	r9, #16
	strls	r9, [r5, #792]
	ldrls	r3, [r5, #732]
	bls	.L3753
	mov	r2, r9
	mov	r3, #16
	ldr	r1, .L4009+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3971:
	ldr	r0, [r4, #2808]
	bl	BsGet
	ldr	r3, [r7, #176]
	subs	r1, r0, #0
	sublt	r3, r3, #1
	blt	.L3694
.L3690:
	sub	r3, r3, #1
	cmp	r3, r1
	bcs	.L3693
.L3694:
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L4009+84
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3771:
	mov	r3, #2
	b	.L3778
.L3999:
	cmp	r6, #0
	subne	r6, r6, #1
	b	.L3776
.L3995:
	mov	r2, r0
	ldr	r1, .L4009+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L4000:
	ldr	r2, [fp, #-100]
	mov	r3, #16
	ldr	r1, .L4009+92
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3996:
	ldr	r1, [r4, #2828]
	ldr	r0, [r1, #24]
	cmp	r0, #0
	beq	.L3717
	ldr	r2, [fp, #-92]
	add	r10, r2, #12288
	ldrb	r6, [r10, #134]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L3718
	add	r9, r2, r0, lsl #2
	add	r9, r9, #16384
	ldr	r2, [r9, #196]
	cmp	r2, #0
	ble	.L3719
	mov	r1, r3
	ldr	r0, [r4, #2808]
	str	r3, [fp, #-48]
	bl	BsGet
	ldr	ip, [r9, #196]
	ldr	r3, [fp, #-48]
	tst	r0, #255
	beq	.L3721
	cmp	ip, #1
	ble	.L3721
	ldrb	r2, [r10, #133]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3722
	cmp	ip, #1
	ldr	r0, [r4, #2808]
	bls	.L3832
.L3724:
	add	r2, r2, #1
	cmp	ip, r3, asl r2
	mov	r1, r2
	bhi	.L3724
.L3723:
	bl	BsGet
	add	r2, r0, #1
	str	r2, [r5, #2072]
	ldr	r3, [r9, #196]
	cmp	r2, r3
	streq	r2, [fp, #-84]
	moveq	r6, #0
	beq	.L3726
	cmp	r2, #2
	bgt	.L4005
	cmp	r2, #0
	bgt	.L3727
	mov	r6, #1
	str	r2, [fp, #-84]
.L3728:
	ldr	r3, [fp, #-84]
	cmp	r3, #0
	ble	.L3716
.L3740:
	add	r1, r4, #6144
	mov	r2, #0
	add	r1, r1, #28
	ldr	r0, [fp, #-84]
	b	.L3745
.L3744:
	add	r2, r2, #1
	cmp	r2, r0
	beq	.L3716
.L3745:
	cmp	r6, #0
	mov	r3, r2
	streq	r2, [r1]
	add	r1, r1, #4
	ldrne	r3, [r1, #-4]
	cmp	r3, #2
	ble	.L3744
	mov	r0, #2
	ldr	r1, .L4009+96
	str	r0, [sp]
	mov	r0, #1
	bl	dprint_vfmw
.L3730:
	ldr	r1, .L4009+100
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3658:
	mov	r2, r9
	ldr	r1, .L4009+104
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3988:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	strb	r0, [r5, #722]
	b	.L3665
.L4010:
	.align	2
.L4009:
	.word	.LC441
	.word	.LC446
	.word	.LC453
	.word	.LC471
	.word	.LC473
	.word	.LC485
	.word	.LC487
	.word	.LC489
	.word	.LC456
	.word	.LC455
	.word	.LC468
	.word	.LC469
	.word	.LANCHOR0+732
	.word	.LC442
	.word	.LC475
	.word	.LC478
	.word	.LC480
	.word	.LC449
	.word	.LC461
	.word	.LC463
	.word	.LC464
	.word	.LC450
	.word	.LC490
	.word	.LC457
	.word	.LC460
	.word	.LC492
	.word	.LC444
	.word	.LC481
	.word	.LC483
	.word	.LC484
	.word	.LC443
	.word	.LC451
	.word	.LC474
	.word	.LC459
	.word	.LC448
	.word	.LC445
	.word	.LC447
	.word	.LC472
	.word	.LC466
	.word	.LC491
	.word	.LC486
	.word	.LC477
	.word	.LC482
	.word	.LC476
	.word	.LC470
	.word	.LC479
	.word	.LC454
	.word	.LC465
	.word	.LC452
	.word	.LC467
	.word	.LC488
	.word	.LC462
	.word	.LC458
.L3987:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	tst	r0, #255
	beq	.L3790
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #721]
	cmp	r0, #0
	bne	.L3789
	ldr	r1, .L4009+108
	ldr	r0, [r4, #2808]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #772]
	bhi	.L4006
.L3791:
	ldr	r1, .L4009+112
	ldr	r0, [r4, #2808]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #776]
	bls	.L3953
	ldr	r1, .L4009+116
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r8, #80]
	ldrb	r0, [r5, #721]	@ zero_extendqisi2
	str	r3, [r5, #776]
	b	.L3789
.L3963:
	ldr	r3, [r4, #260]
	mov	r0, r4
	cmp	r3, #0
	ldrne	r3, [r4, #192]
	str	r3, [r5, #724]
	bl	HEVC_IsNewPic
	ldr	r1, .L4009+120
	str	r0, [r5, #864]
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3717:
	ldr	r3, [fp, #-92]
	add	r9, r3, #12288
	ldrb	r6, [r9, #134]	@ zero_extendqisi2
.L3718:
	cmp	r6, #1
	beq	.L4007
.L3719:
	mov	r3, #0
	str	r3, [r5, #2072]
.L3734:
	mov	r6, #0
	b	.L3728
.L3972:
	ldr	r1, .L4009+124
	ldr	r0, [r4, #2808]
	bl	HEVC_ue_v
	ldr	r3, [r7, #180]
	cmp	r0, r3
	mov	r2, r0
	str	r0, [fp, #-48]
	bhi	.L4008
	cmp	r3, #1
	bls	.L3829
	mov	r2, #0
	mov	r1, r2
	mov	r2, #1
.L3698:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L3698
	str	r1, [fp, #-96]
	str	r1, [fp, #-56]
	b	.L3696
.L3985:
	ldr	r1, .L4009+128
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3833:
	mov	r1, #0
.L3731:
	str	r3, [fp, #-48]
	bl	BsGet
	add	r4, r4, #1
	ldr	r3, [fp, #-48]
	str	r0, [r10, #4]!
	ldr	r2, [r7, #2072]
	cmp	r4, r2
	blt	.L3733
	mov	r4, r5
	mov	r6, #1
	mov	r5, r7
	mov	r7, r3
	str	r2, [fp, #-84]
.L3726:
	ldr	r3, [fp, #-84]
	cmp	r3, #2
	ble	.L3728
	ldr	r2, [fp, #-84]
	mov	r3, #2
	ldr	r1, .L4009+132
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3730
.L3970:
	ldr	r1, .L4009+136
	bl	dprint_vfmw
	b	.L3683
.L4007:
	ldr	r2, [r4, #2812]
	add	r10, r2, r0, lsl #2
	add	r10, r10, #16384
	ldr	r6, [r10, #196]
	cmp	r6, #0
	ble	.L3834
	add	r3, r0, #2064
	mov	r9, #0
	add	r3, r3, #10
	add	ip, r2, #12288
	ldr	lr, [r1, #28]
	mov	r1, r9
	add	r0, r2, r3, lsl #3
.L3738:
	ldr	r3, [r0, #4]!
	add	r1, r1, #1
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, ip, r3, lsl #2
	ldr	r2, [r3, #132]
	add	r3, r2, #1040
	add	r3, r3, #2
	add	r3, ip, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, lr
	blt	.L3736
	cmp	lr, #0
	beq	.L3737
	ldr	r3, [r10, #180]
	add	r3, r3, r2, lsl #1
	add	r3, r3, #3088
	add	r3, r3, #10
	add	r3, ip, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, #0
	beq	.L3736
.L3737:
	add	r9, r9, #1
.L3736:
	cmp	r1, r6
	bne	.L3738
.L3735:
	str	r9, [fp, #-84]
	mov	r6, #0
	str	r9, [r5, #2072]
	b	.L3726
.L3992:
	ldr	r2, [r7, #192]
	ldr	r3, [r7, #188]
	mul	r3, r3, r2
.L3664:
	mov	r2, r0
	ldr	r1, .L4009+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3966:
	mov	r2, r0
	ldr	r1, .L4009+144
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3984:
	ldr	r1, .L4009+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3758:
	mov	r3, #16
	ldr	r1, .L4009+152
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3721:
	cmp	ip, #1
	streq	ip, [r5, #2072]
	streq	ip, [fp, #-84]
	bne	.L3719
	b	.L3734
.L3808:
	mov	r2, r0
	mov	r3, r7
	ldr	r1, .L4009+156
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3993:
	mov	r2, r6
	ldr	r1, .L4009+160
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L4002:
	mov	r2, r0
	ldr	r1, .L4009+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L4006:
	ldr	r1, .L4009+168
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r8, #76]
	str	r3, [r5, #772]
	b	.L3791
.L4001:
	mov	r2, r0
	ldr	r1, .L4009+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3983:
	ldr	r1, .L4009+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L4003:
	mov	r2, r0
	ldr	r1, .L4009+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3973:
	str	r0, [sp]
	mov	ip, #16
	ldr	r1, .L4009+184
	mov	r0, #1
	str	ip, [sp, #4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3979:
	ldr	r1, .L4009+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L4008:
	ldr	r1, .L4009+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3834:
	mov	r9, #0
	b	.L3735
.L3980:
	ldr	r1, .L4009+196
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3994:
	mov	r2, r7
	ldr	r1, .L4009+200
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3722:
	str	r3, [r5, #2072]
	ldr	r2, [r9, #196]
	cmp	r2, #1
	streq	r3, [fp, #-84]
	beq	.L3740
.L3727:
	add	r10, r4, #6144
	mov	r3, #0
	mov	r2, r5
	add	r10, r10, #24
	mov	r5, r4
	mov	r6, #1
	mov	r4, r3
	mov	r3, r7
	mov	r7, r2
.L3733:
	ldr	ip, [r9, #196]
	ldr	r0, [r5, #2808]
	cmp	ip, #1
	bls	.L3833
	mov	r2, #0
.L3732:
	add	r2, r2, #1
	cmp	ip, r6, asl r2
	mov	r1, r2
	bhi	.L3732
	b	.L3731
.L4004:
	mov	r2, r6
	mov	r3, #16
	ldr	r1, .L4009+204
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3948
.L3832:
	mov	r1, r2
	b	.L3723
.L3829:
	mov	r3, #0
	str	r3, [fp, #-96]
	str	r3, [fp, #-56]
	b	.L3696
.L4005:
	mov	r3, #2
	ldr	r1, .L4009+208
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3730
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
	ldr	r1, [r0, #2828]
	mov	r4, r0
	cmp	r1, #0
	beq	.L4012
	ldr	r0, [r0, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4012:
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
	ldr	r1, [r0, #2828]
	mov	r4, r0
	cmp	r1, #0
	beq	.L4018
	ldr	r0, [r0, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4018:
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
	beq	.L4026
	mov	r4, #0
	mov	r6, r4
.L4025:
	ldr	r3, [r5, #2848]
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L4024
	ldr	r0, [r5, #276]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r5, #2848]
	str	r6, [r3, r4, asl #2]
	ldr	r2, [r5, #168]
.L4024:
	add	r4, r4, #1
	cmp	r2, r4
	bhi	.L4025
.L4026:
	mov	r0, #0
	mov	r3, #2
	str	r0, [r5, #204]
	str	r0, [r5, #268]
	str	r0, [r5, #260]
	strb	r0, [r5, #14]
	str	r3, [r5, #176]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearAllSlice, .-HEVC_ClearAllSlice
	.align	2
	.global	HEVC_InitDPB
	.type	HEVC_InitDPB, %function
HEVC_InitDPB:
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
	mov	r4, r0
	mov	r9, r1
	bl	HEVC_ClearAllSlice
	add	r8, r4, #3200
	mov	r6, r4
	add	r8, r8, #4
	mov	r5, #17
	mov	r7, #0
.L4039:
	ldr	r3, [r8, #4]!
	cmp	r3, #0
	beq	.L4033
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L4033:
	ldr	r3, [r6, #3276]
	cmp	r3, #0
	beq	.L4034
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L4034:
	ldr	r3, [r6, #3344]
	cmp	r3, #0
	beq	.L4035
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L4035:
	ldr	r3, [r6, #3412]
	cmp	r3, #0
	beq	.L4036
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L4036:
	ldr	r3, [r6, #3072]
	str	r7, [r6, #3412]
	cmp	r3, #0
	str	r7, [r6, #3344]
	str	r7, [r6, #3276]
	str	r7, [r6, #3208]
	beq	.L4037
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L4037:
	ldr	r3, [r6, #3140]
	cmp	r3, #0
	beq	.L4038
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L4038:
	subs	r5, r5, #1
	str	r7, [r6, #3140]
	str	r7, [r6, #3072]
	add	r6, r6, #4
	bne	.L4039
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4103
.L4040:
	ldr	r3, [r4, #2840]
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r4, #3036]
.L4042:
	cmp	r3, #17
	bhi	.L4104
.L4043:
	ldr	r3, .L4112
	mov	r6, #0
	add	r0, r4, #13120
	mov	r1, r6
	mov	r2, #280
	str	r6, [r4, #3040]
	ldr	r3, [r3, #48]
	add	r0, r0, #44
	str	r6, [r4, #3052]
	add	r10, r4, #12288
	str	r6, [r4, #3056]
	mov	r7, #16
	str	r6, [r4, #3048]
	str	r6, [r4, #3044]
	str	r6, [r4, #3064]
	str	r6, [r4, #3068]
	blx	r3
	ldr	r3, .L4112
	add	r0, r4, #13440
	mov	r2, #280
	str	r6, [r10, #880]
	mov	r1, r6
	ldr	r3, [r3, #48]
	add	r0, r0, #4
	str	r7, [r10, #876]
	blx	r3
	add	r3, r4, #2928
	add	r3, r3, #4
	add	r2, r4, #2864
	mov	r0, r6
	str	r7, [r10, #1156]
	str	r6, [r10, #1160]
.L4044:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L4044
	add	r2, r4, #2992
	add	r0, r4, #4096
	add	r2, r2, #8
	mov	ip, r1
	str	r1, [r0, #780]
.L4045:
	str	ip, [r3, #4]!
	cmp	r3, r2
	mov	r1, #0
	bne	.L4045
	cmp	r9, r1
	str	r1, [r0, #784]
	bne	.L4046
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	beq	.L4046
.L4047:
	ldr	r1, [r4, #184]
	cmp	r1, #0
	addne	r2, r4, #2160
	movne	r3, #0
	addne	r2, r2, #4
	movne	r0, r3
	beq	.L4064
.L4063:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L4063
.L4064:
	ldr	r2, [r4, #168]
	cmp	r2, #0
	movne	r5, #0
	movne	r6, r5
	beq	.L4062
.L4066:
	ldr	r3, [r4, #2848]
	mov	r7, r5, asl #2
	ldr	r3, [r3, r5, asl #2]
	add	r5, r5, #1
	cmp	r3, #0
	mov	r1, r3
	beq	.L4065
	ldr	r0, [r4, #2828]
	cmp	r3, r0
	beq	.L4065
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r4, #2848]
	str	r6, [r3, r7]
	ldr	r2, [r4, #168]
.L4065:
	cmp	r2, r5
	bhi	.L4066
.L4062:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4046:
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	mov	r3, #20
	str	r3, [r4, #180]
	cmp	r2, #1
	str	r3, [r4, #184]
	beq	.L4105
.L4048:
	mov	r0, r4
	bl	HEVC_ArrangeMem
.L4070:
	cmp	r0, #0
	beq	.L4056
	cmp	r0, #2
	beq	.L4106
.L4057:
	ldr	r2, .L4112+4
	mov	r0, #0
	ldr	r1, .L4112+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4104:
	mov	r6, #17
	ldr	r2, .L4112+4
	str	r6, [sp]
	mov	r3, r6
	ldr	r1, .L4112+12
	mov	r0, #1
	bl	dprint_vfmw
	str	r6, [r4, #3036]
	b	.L4043
.L4103:
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L4040
	ldr	r2, [r4, #2392]
	cmp	r2, #0
	beq	.L4040
	ldr	r3, [r4, #2840]
	ldr	r3, [r3, #184]
	mul	r3, r3, r2
	add	r3, r3, #1
	str	r3, [r4, #3036]
	b	.L4042
.L4056:
	ldr	r0, [r4, #276]
	bl	FSP_GetTotalValidFsNum
	cmp	r0, #20
	movgt	r0, #20
	ble	.L4107
.L4059:
	str	r0, [r4, #180]
	b	.L4047
.L4105:
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L4048
	ldr	r3, [r4, #2392]
	ldr	r10, [r4, #2840]
	cmp	r3, #0
	str	r3, [fp, #-88]
	beq	.L4108
	ldr	r2, [r10, #140]
	mov	r6, #0
	ldr	r3, [r10, #144]
	mov	r7, r6
	rsb	r1, r2, #0
	str	r1, [fp, #-76]
	ldr	r1, [r4, #3036]
	sub	r2, r2, #1
	ldr	r9, [r0, #744]
	movw	r0, #8160
	str	r2, [fp, #-80]
	rsb	r2, r3, #0
	str	r1, [fp, #-92]
	sub	r3, r3, #1
	str	r2, [fp, #-72]
	str	r3, [fp, #-84]
	mov	r3, r6
	b	.L4053
.L4051:
	cmp	r7, r1
	movcc	r7, r1
	cmp	r6, r2
	sub	r1, r7, #32
	movcc	r6, r2
	sub	r2, r6, #32
	cmp	r1, r0
	cmpls	r2, r0
	movhi	r1, #1
	movls	r1, #0
	bhi	.L4109
	ldr	r2, [fp, #-88]
	uxtb	r3, ip
	cmp	r2, r3
	mov	r5, r3
	bls	.L4110
.L4053:
	add	r2, r4, r3, lsl #2
	ldr	lr, [fp, #-80]
	cmp	r9, r5
	add	ip, r3, #1
	ldr	r1, [r2, #2400]
	ldr	r2, [r2, #2408]
	add	r1, lr, r1
	ldr	lr, [fp, #-84]
	add	r2, lr, r2
	ldr	lr, [fp, #-76]
	and	r1, r1, lr
	ldr	lr, [fp, #-72]
	and	r2, r2, lr
	bne	.L4051
	ldr	r5, [r10, #188]
	ldr	lr, [r10, #128]
	ldr	r8, [r10, #192]
	mov	r5, r5, asl lr
	cmp	r1, r5
	mov	lr, r8, asl lr
	movcc	r1, r5
	cmp	r2, lr
	movcc	r2, lr
	b	.L4051
.L4109:
	str	r6, [sp, #4]
	mov	r0, #0
	str	r7, [sp]
	ldr	r2, .L4112+16
	ldr	r1, .L4112+20
	bl	dprint_vfmw
	b	.L4057
.L4106:
	add	r0, r4, #6144
	add	r0, r0, #40
	bl	ResetVoQueue
	mvn	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4110:
	ldr	r3, .L4112
	mov	r2, #20
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #2856]
	str	r7, [fp, #-60]
	str	r6, [fp, #-56]
	ldr	r3, [r3, #28]
	str	r7, [fp, #-52]
	cmp	r3, #24
	str	r6, [fp, #-48]
	beq	.L4054
	ldrb	r3, [fp, #-92]	@ zero_extendqisi2
	strb	r3, [fp, #-63]
.L4071:
	sub	r1, fp, #64
	ldr	r0, [r4, #276]
	strb	r3, [fp, #-61]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L4111
	ldr	r1, [r4, #2856]
	sub	r3, fp, #68
	ldr	r0, [r4, #276]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	b	.L4070
.L4107:
	ldr	r0, [r4, #276]
	bl	FSP_GetTotalValidFsNum
	b	.L4059
.L4054:
	mov	r3, #1
	strb	r3, [fp, #-63]
	b	.L4071
.L4108:
	ldr	r3, [fp, #-88]
	ldr	r2, .L4112+16
	ldr	r1, .L4112+24
	mov	r0, r3
	bl	dprint_vfmw
	b	.L4057
.L4111:
	ldr	r2, .L4112+16
	mov	r0, #1
	ldr	r1, .L4112+28
	bl	dprint_vfmw
	b	.L4057
.L4113:
	.align	2
.L4112:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+760
	.word	.LC495
	.word	.LC161
	.word	.LANCHOR0+776
	.word	.LC494
	.word	.LC493
	.word	.LC98
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
	beq	.L4118
	mov	r4, #0
	mov	r5, r4
	b	.L4117
.L4116:
	add	r3, r2, #1
	cmp	r3, r5
	bls	.L4118
.L4117:
	ldr	r1, [r6, #2852]
	add	r5, r5, #1
	add	r1, r1, r4
	add	r4, r4, #96
	ldr	r3, [r1, #32]
	cmp	r3, #1
	bne	.L4116
	ldr	r0, [r6, #276]
	bl	HEVC_ReleaseNAL
	ldr	r2, [r6, #168]
	add	r3, r2, #1
	cmp	r3, r5
	bhi	.L4117
.L4118:
	mov	r0, #0
	strb	r0, [r6, #9]
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
	ldr	r1, .L4137
	mov	r7, r0
	mov	r0, #22
	mov	r8, #0
	bl	dprint_vfmw
	mov	r3, #-2147483647
	mov	r1, #1
	mvn	r2, #-2147483648
	strb	r8, [r7, #4]
	mov	r0, r7
	strb	r8, [r7, #12]
	add	r4, r7, #13760
	strb	r8, [r7, #5]
	mov	r6, r8
	strb	r8, [r7, #13]
	mov	r5, r8
	str	r3, [r7, #212]
	add	r4, r4, #48
	str	r3, [r7, #252]
	mov	r9, #20
	str	r3, [r7, #216]
	str	r3, [r7, #256]
	strb	r1, [r7, #6]
	strb	r1, [r7, #7]
	str	r2, [r7, #244]
	str	r2, [r7, #248]
	bl	HEVC_ClearAllNal
	add	r0, r7, #6144
	add	r0, r0, #40
	ldr	r8, .L4137+4
	bl	ResetVoQueue
.L4122:
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
	str	r3, [r4, #-4]
	add	r4, r4, #720
	bne	.L4122
	add	r3, r7, #2160
	add	r2, r7, #2240
	add	r3, r3, #4
	add	r2, r2, #4
	mov	r1, #0
.L4123:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L4123
	ldr	r3, [r7, #168]
	cmp	r3, #0
	beq	.L4124
	mov	r3, #0
	mov	r1, r3
.L4125:
	ldr	r2, [r7, #2848]
	str	r1, [r2, r3, asl #2]
	add	r3, r3, #1
	ldr	r2, [r7, #168]
	cmp	r2, r3
	bhi	.L4125
.L4124:
	add	r0, r7, #13120
	ldr	r3, [r8, #48]
	mov	r2, #280
	mov	r1, #0
	add	r4, r7, #12288
	add	r0, r0, #44
	blx	r3
	add	r0, r7, #13440
	mov	r5, #16
	mov	r2, #280
	ldr	r3, [r8, #48]
	mov	r1, #0
	add	r0, r0, #4
	str	r5, [r4, #876]
	blx	r3
	add	ip, r7, #3328
	add	r0, r7, #3264
	add	r1, r7, #3200
	add	ip, ip, #12
	add	r0, r0, #8
	add	r1, r1, #4
	add	lr, r7, #3408
	mov	r2, #17
	mov	r3, #0
	str	r5, [r4, #1156]
.L4126:
	subs	r2, r2, #1
	str	r3, [lr, #4]!
	str	r3, [ip, #4]!
	str	r3, [r0, #4]!
	str	r3, [r1, #4]!
	bne	.L4126
	add	r3, r7, #2928
	add	ip, r7, #2992
	add	r3, r3, #4
	add	ip, ip, #8
	add	r0, r7, #2864
	mov	r1, r2
	mov	lr, #17
	str	r2, [r7, #3040]
	str	r2, [r7, #3044]
	str	r2, [r7, #3048]
	str	r2, [r7, #3052]
	str	r2, [r7, #3056]
	str	lr, [r7, #3036]
.L4127:
	str	r1, [r3, #4]!
	cmp	r3, ip
	str	r1, [r0, #4]!
	mov	r4, #0
	bne	.L4127
	add	r0, r7, #4800
	mov	r6, #2
	mov	r1, r4
	str	r4, [r7, #2828]
	str	r4, [r7, #204]
	mov	r2, #1376
	str	r4, [r7, #268]
	add	r0, r0, #8
	str	r4, [r7, #260]
	add	r5, r7, #2992
	str	r6, [r7, #176]
	add	r5, r5, #12
	ldr	r3, [r8, #48]
	mov	r9, #16
	blx	r3
	add	r2, r7, #4096
	mov	r3, #1
	mov	r1, r4
	str	r6, [r2, #732]
	mov	lr, #256
	str	r3, [r2, #864]
	movw	ip, #1025
	mov	r2, #20
	strb	r3, [r7, #3]
	str	r6, [r7, #2260]
	mov	r3, #8
	strb	r4, [r7, #8]
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
	str	r9, [r7, #360]
	str	r6, [r7, #364]
	str	lr, [r7, #368]
	str	ip, [r7, #372]
	str	r3, [r7, #2248]
	str	r3, [r7, #2252]
	str	r3, [r7, #2256]
	blx	r4
	str	r5, [r7, #2808]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4138:
	.align	2
.L4137:
	.word	.LC496
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
	add	r4, r0, #4096
	mov	r5, r0
	bl	HEVC_ClearAllSlice
	ldr	r3, [r4, #68]
	cmp	r3, #0
	beq	.L4140
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r5, #276]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #68]
	mov	r3, #0
	str	r3, [r2, #48]
	str	r3, [r4, #68]
.L4140:
	mov	r0, #0
	strb	r0, [r4, #9]
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
	bne	.L4147
	add	r0, r4, #6144
	add	r0, r0, #40
	bl	ResetVoQueue
	ldr	r0, [r4, #276]
	bl	FSP_EmptyInstance
.L4146:
	mov	r0, r4
	bl	HEVC_InitDecPara
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4147:
	add	r1, r4, #6144
	ldr	r0, [r4, #276]
	add	r1, r1, #40
	bl	FSP_ClearNotInVoQueue
	b	.L4146
	UNWIND(.fnend)
	.size	HEVC_ClearAll, .-HEVC_ClearAll
	.align	2
	.global	HEVC_InitPic
	.type	HEVC_InitPic, %function
HEVC_InitPic:
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
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	r1, [r0, #292]
	ldr	r3, [r0, #288]
	add	r2, r0, #4096
	mov	r10, r0
	ldr	r6, [r0, #304]
	mov	r4, r1
	str	r1, [fp, #-84]
	ldr	r1, [r0, #296]
	str	r3, [fp, #-76]
	ldr	r3, [r2, #748]
	str	r1, [fp, #-80]
	ldr	r1, [r0, #300]
	cmp	r3, #0
	ldr	r7, [r0, #308]
	str	r1, [fp, #-68]
	blt	.L4178
	ldr	r1, [r0, #164]
	cmp	r3, r1
	bge	.L4178
	ldr	r1, [r0, #2820]
	movw	r5, #5036
	movw	r8, #12668
	ldr	r2, [r2, #744]
	ldr	r9, [r0, #2816]
	movw	ip, #24912
	mla	r5, r5, r3, r1
	add	r2, r0, r2, lsl #2
	ldr	r0, [r0, #2812]
	ldr	r1, [r5, #32]
	mul	r8, r8, r1
	add	r1, r9, r8
	str	r1, [fp, #-64]
	mov	lr, r1
	ldr	r1, [r1, #48]
	str	r3, [r2, #236]
	ldr	r3, [r5, #32]
	mla	r1, ip, r1, r0
	str	r3, [r2, #228]
	ldr	r3, [lr, #48]
	str	r3, [r2, #220]
	ldr	r2, [r10, #172]
	ldr	r3, [lr, #128]
	clz	ip, r2
	ldr	r2, [fp, #-68]
	ldr	r0, [lr, #64]
	subs	r3, r2, r3
	mov	r2, ip, lsr #5
	str	r2, [fp, #-72]
	movne	r3, #1
	cmp	r4, r0
	movne	r2, #1
	strne	r2, [fp, #-88]
	beq	.L4204
.L4150:
	ldr	r0, [fp, #-72]
	ldr	r2, [r10, #2836]
	ldr	ip, [fp, #-88]
	orr	r3, r3, r0
	ldr	r0, [r1, #4]
	orr	r4, ip, r3
	ldr	r3, [r2, #4]
	cmp	r3, r0
	movne	r3, #1
	beq	.L4205
.L4151:
	ldr	r2, [fp, #-72]
	orrs	r3, r3, r2
	beq	.L4152
	mov	r0, r10
	bl	HEVC_UpdatePicVPS
.L4152:
	ldr	r3, [r10, #2840]
	ldr	r2, [fp, #-64]
	ldr	r1, [r3, #56]
	ldr	r2, [r2, #56]
	cmp	r1, r2
	movne	r2, #1
	beq	.L4206
.L4153:
	orrs	r2, r2, r4
	streq	r2, [fp, #-92]
	beq	.L4154
	ldr	r2, [fp, #-64]
	mov	r0, r10
	ldr	r3, [r3, #184]
	mov	r1, r2
	ldr	r2, [r2, #184]
	subs	r3, r2, r3
	movne	r3, #1
	str	r3, [fp, #-92]
	bl	HEVC_UpdatePicSPS
.L4154:
	ldr	r2, [r10, #2844]
	ldr	r3, [r5, #28]
	ldr	r2, [r2, #28]
	cmp	r2, r3
	movne	r3, #1
	beq	.L4207
.L4155:
	orrs	r3, r3, r4
	beq	.L4156
	mov	r2, r5
	ldr	r1, [fp, #-64]
	mov	r0, r10
	bl	HEVC_UpdatePicPPS
.L4156:
	ldr	r3, [r10, #304]
	cmp	r6, r3
	movne	r3, #1
	strne	r3, [fp, #-96]
	beq	.L4208
.L4157:
	ldr	r2, [r10, #2840]
	ldr	r1, [r10, #2856]
	ldr	r3, [r2, #96]
	ldr	r2, [r2, #88]
	cmp	r3, r2
	movcc	r3, r2
	str	r3, [r1, #932]
	ldr	r3, [r10, #2836]
	str	r3, [fp, #-60]
	add	r3, r3, #16384
	ldr	r3, [r3, #160]
	cmp	r3, #0
	beq	.L4171
	add	r9, r3, #1
	add	r3, r10, #2384
	cmp	r9, #2
	add	r3, r3, #12
	mov	r8, #0
	str	r3, [fp, #-52]
	movcs	r9, #2
	ldr	r3, [fp, #-60]
	cmp	r8, r9
	str	r9, [r10, #2392]
	add	r3, r3, #24832
	str	r3, [fp, #-48]
	bcs	.L4171
.L4170:
	add	r3, r8, #1
	ldr	r4, [r10, #2836]
	cmp	r3, r9
	str	r3, [fp, #-56]
	bcs	.L4168
	mov	r2, r8, asl #5
	add	r7, r4, #12288
	add	r2, r2, r8, lsl #3
	ldr	r3, [fp, #-60]
	add	r7, r7, r2
	ldr	r2, [fp, #-48]
	rsb	r3, r3, #40
	add	r6, r7, #12480
	add	r3, r3, r2
	add	r7, r7, #12544
	add	r6, r6, #60
	add	r7, r7, #4
	add	r4, r4, r3
	ldr	r5, [fp, #-56]
	b	.L4167
.L4165:
	ldrb	r3, [r10, #2]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4166
	mov	r3, #1
	strb	r3, [r10, #2]
	ldr	ip, [r4, #4]
	ldr	r3, [r6, #4]
	str	ip, [sp, #12]
	ldr	ip, [r4]
	stmib	sp, {r5, ip}
	ldr	ip, [r7]
	str	ip, [sp]
	bl	dprint_vfmw
.L4166:
	add	r5, r5, #1
	add	r4, r4, #40
	cmp	r5, r9
	bcs	.L4168
.L4167:
	ldr	ip, [r6, #4]
	mov	r2, r8
	ldr	r3, [r4]
	mov	r0, #32
	ldr	r1, .L4211
	cmp	ip, r3
	bne	.L4165
	ldr	ip, [r7]
	ldr	r3, [r4, #4]
	cmp	ip, r3
	bne	.L4165
	add	r5, r5, #1
	add	r4, r4, #40
	cmp	r5, r9
	bcc	.L4167
.L4168:
	ldr	r1, [fp, #-52]
	ldr	r3, [fp, #-48]
	ldr	r2, [r1, #4]!
	ldr	r3, [r3]
	cmp	r2, r3
	str	r1, [fp, #-52]
	bne	.L4163
	ldr	r2, [fp, #-52]
	ldr	r1, [r2, #8]
	ldr	r2, [fp, #-48]
	ldr	r2, [r2, #4]
	cmp	r1, r2
	beq	.L4169
.L4163:
	ldr	lr, [fp, #-52]
	mov	r0, #32
	ldr	r2, [fp, #-48]
	ldr	r1, .L4211+4
	str	r3, [lr]
	ldr	ip, [r2, #4]
	mov	r2, r8
	str	ip, [lr, #8]
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r10, #2396]
.L4169:
	ldr	r9, [r10, #2392]
	ldr	r8, [fp, #-56]
	ldr	r3, [fp, #-48]
	cmp	r8, r9
	add	r3, r3, #40
	str	r3, [fp, #-48]
	bcc	.L4170
.L4171:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-76]
	ldr	r3, [r3, #56]
	cmp	r2, r3
	beq	.L4209
.L4159:
	ldr	r3, [fp, #-92]
	mov	r0, r10
	ldr	r2, [fp, #-80]
	ldr	r1, [fp, #-84]
	str	r3, [sp]
	ldr	r3, [fp, #-68]
	bl	HEVC_GetReRangeFlag
	cmp	r0, #0
	bne	.L4173
	ldr	r3, [r10, #2856]
	ldr	r2, [r3, #920]
	cmp	r2, #1
	beq	.L4173
.L4174:
	mov	r2, #0
	str	r2, [r3, #936]
.L4172:
	ldr	r3, [r10, #2368]
	cmp	r3, #0
	bne	.L4176
	mov	r0, r10
	bl	HEVC_AllocFrameStore
	subs	r4, r0, #0
	bne	.L4210
.L4176:
	mov	r0, r10
	bl	HEVC_InitPicInfo
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4178:
	mov	r0, #0
.L4149:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4173:
	mov	r1, #1
	mov	r0, r10
	bl	HEVC_InitDPB
	cmn	r0, #2
	beq	.L4149
	cmp	r0, #0
	bne	.L4175
	ldr	r3, [r10, #2856]
	b	.L4174
.L4209:
	ldr	r2, [fp, #-72]
	ldr	r3, [fp, #-88]
	orr	r3, r3, r2
	ldr	r2, [fp, #-92]
	orr	r3, r3, r2
	ldr	r2, [fp, #-96]
	orrs	r3, r3, r2
	bne	.L4159
	ldr	r3, [r10, #2856]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L4172
	b	.L4159
.L4208:
	ldr	r3, [r10, #308]
	subs	r3, r7, r3
	movne	r3, #1
	str	r3, [fp, #-96]
	b	.L4157
.L4207:
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	adds	r3, r3, #0
	movne	r3, #1
	b	.L4155
.L4206:
	ldrb	r2, [r9, r8]	@ zero_extendqisi2
	adds	r2, r2, #0
	movne	r2, #1
	b	.L4153
.L4205:
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	adds	r3, r3, #0
	movne	r3, #1
	b	.L4151
.L4204:
	ldr	r2, [lr, #68]
	ldr	r0, [fp, #-80]
	subs	r2, r0, r2
	movne	r2, #1
	str	r2, [fp, #-88]
	b	.L4150
.L4210:
	ldr	r1, .L4211+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L4149
.L4175:
	mov	r2, r0
	ldr	r1, .L4211+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r10
	mov	r1, #0
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L4149
.L4212:
	.align	2
.L4211:
	.word	.LC497
	.word	.LC498
	.word	.LC500
	.word	.LC499
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #4096
	mov	r6, r0
	add	r1, r5, #72
	mov	r2, #640
	ldr	r4, [r5, #68]
	ldr	r3, [r5, #48]
	add	r0, r4, #80
	str	r3, [r4, #16]
	bl	memcpy
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_GetImagePara
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4220
.L4214:
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_OutputFrame
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, .L4221
	mov	r0, #0
	ldr	r1, .L4221+4
	bl	dprint_vfmw
	mov	r0, r6
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4220:
	mov	r2, #1
	ldr	r1, [r4, #28]
	ldr	r0, [r6, #276]
	bl	FSP_SetRef
	b	.L4214
.L4222:
	.align	2
.L4221:
	.word	.LANCHOR0+796
	.word	.LC501
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
	bne	.L4226
	add	r3, r4, #4096
	add	r1, r4, #8192
	mov	r2, #1
	mov	ip, #2
	ldr	r0, [r3, #68]
	str	ip, [r0, #52]
	str	r2, [r1, #3592]
	ldr	r0, [r3, #16]
	ldr	r1, [r3, #20]
	add	r4, r4, r0, lsl #2
	mov	r0, r5
	str	r1, [r4, #212]
	ldr	r3, [r3, #68]
	strb	r2, [r3, #2]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4226:
	ldr	r2, .L4227
	mov	r0, #1
	ldr	r1, .L4227+4
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4228:
	.align	2
.L4227:
	.word	.LANCHOR0+816
	.word	.LC502
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
	beq	.L4234
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r6, r0, #0
	beq	.L4238
	cmn	r6, #3
	bne	.L4239
.L4233:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4238:
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_OutputFrame
	cmp	r0, #0
	beq	.L4233
	ldr	r2, .L4240
	mov	r0, r6
	ldr	r1, .L4240+4
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4239:
	mov	r3, r6
	movw	r2, #11897
	ldr	r1, .L4240+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #228]
	mov	r0, r4
	bl	HEVC_DECRecycleImage
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4234:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4241:
	.align	2
.L4240:
	.word	.LANCHOR0+840
	.word	.LC501
	.word	.LC503
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
	add	r3, r0, #4096
	mov	r5, #0
	mov	r6, r0
	mov	ip, #1
	ldr	r4, [r3, #68]
	mov	r0, #2
	add	r1, r3, #72
	mov	r2, #640
	str	r0, [r4, #48]
	add	r0, r4, #80
	strb	ip, [r4, #2]
	strb	r5, [r4, #1]
	ldr	ip, [r3, #24]
	str	ip, [r4, #12]
	ldr	r3, [r3, #48]
	str	r3, [r4, #16]
	bl	memcpy
	mov	r2, r5
	str	r5, [r4, #56]
	ldr	r1, [r4, #28]
	ldr	r0, [r6, #276]
	bl	FSP_SetRef
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_OutputFrmToVO
	ldr	r3, .L4243
	str	r5, [r4, #48]
	mov	r1, r5
	mov	r2, #704
	ldr	r3, [r3, #48]
	mov	r7, r0
	add	r0, r6, #4096
	add	r0, r0, #8
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4244:
	.align	2
.L4243:
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
	add	r2, r4, #4096
	ldr	r1, [r4, #184]
	ldr	r3, [r2, #44]
	cmp	r3, r1
	addne	r3, r3, #540
	addne	r3, r3, #2
	movne	ip, #0
	strne	ip, [r4, r3, asl #2]
	strne	r1, [r2, #44]
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
	ldr	lr, [r0, #3040]
	mov	r5, r0
	cmp	lr, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #3200
	mvn	ip, #-2147483648
	add	r0, r0, #4
	mvn	r4, #0
	mov	r3, #0
.L4250:
	ldr	r2, [r0, #4]!
	ldr	r1, [r2, #8]
	cmp	r1, ip
	bge	.L4249
	ldr	r2, [r2]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	moveq	ip, r1
	moveq	r4, r3
.L4249:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L4250
	cmn	r4, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r3, r5, r4, lsl #2
	mov	r1, #1
	mov	r0, r5
	ldr	r2, [r3, #3208]
	strb	r1, [r2, #2]
	ldr	r1, [r3, #3208]
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
	add	r8, r0, #4096
	mov	r5, r0
	ldr	r0, [r0, #3040]
	ldr	r7, [r8, #16]
	cmp	r0, #0
	beq	.L4277
	add	r10, r7, #52
	mov	r3, #0
	add	r6, r5, #3200
	str	r3, [fp, #-48]
	add	r6, r6, #4
	add	r10, r5, r10, lsl #2
	mov	r4, r3
	b	.L4262
.L4260:
	add	r4, r4, #1
	cmp	r0, r4
	bls	.L4259
.L4262:
	ldr	r3, [r6, #4]!
	ldrb	r9, [r3, #2]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L4260
	ldr	r2, [r3, #32]
	cmp	r2, r7
	bne	.L4260
	ldr	r3, [r3, #8]
	ldr	r2, [r10, #4]
	cmp	r3, r2
	blt	.L4261
	add	r4, r4, #1
	ldr	r3, [fp, #-48]
	cmp	r0, r4
	add	r3, r3, #1
	str	r3, [fp, #-48]
	bhi	.L4262
.L4259:
	ldr	r3, [r5, #2376]
	cmp	r3, #1
	beq	.L4295
	ldr	r3, [r8, #736]
	ldr	r2, [r5, #2840]
	add	r3, r3, #90
	ldr	r9, [r2, r3, asl #2]
.L4264:
	cmp	r0, #0
	beq	.L4278
	add	r6, r5, #3200
	mov	r4, #0
	add	r6, r6, #4
	add	r10, r5, r7, lsl #2
	str	r4, [fp, #-52]
	b	.L4275
.L4298:
	ldr	ip, [r5, #356]
	cmp	ip, #1
	beq	.L4271
.L4272:
	cmp	r2, #0
	bne	.L4270
	ldr	r3, [r8, #724]
	ldr	r2, [r1, #8]
	add	r3, r3, #100
	cmp	r2, r3
	ble	.L4270
	ldr	r3, [r10, #244]
	cmp	r3, #-2147483647
	beq	.L4270
	ldr	r3, [r5, #356]
	cmp	r3, #1
	beq	.L4296
.L4270:
	add	r4, r4, #1
	cmp	r0, r4
	bls	.L4294
.L4275:
	ldr	r1, [r6, #4]!
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L4266
	ldr	r3, [r1, #32]
	cmp	r3, r7
	beq	.L4297
.L4266:
	add	r3, r5, r7, lsl #2
	ldr	r3, [r3, #212]
.L4268:
	cmp	r3, #0
	bne	.L4298
.L4271:
	ldr	ip, [r1, #8]
	cmp	r3, ip
	ble	.L4272
	cmp	r2, #0
	beq	.L4299
.L4273:
	str	ip, [sp]
	mov	r0, #31
	ldr	r2, .L4300
	add	r4, r4, #1
	ldr	r1, .L4300+4
	bl	dprint_vfmw
	ldr	r0, [r5, #3040]
	cmp	r0, r4
	bhi	.L4275
.L4294:
	ldr	r0, [fp, #-52]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4297:
	ldr	ip, [r1, #8]
	ldr	r3, [r10, #212]
	cmp	ip, r3
	str	ip, [fp, #-56]
	ble	.L4268
	ldr	lr, [fp, #-48]
	ldr	ip, [r8, #736]
	cmp	lr, r9
	movhi	lr, #1
	movls	lr, #0
	cmp	ip, #7
	movhi	lr, #0
	cmp	lr, #0
	beq	.L4268
	ldr	lr, [r8, #724]
	ldr	ip, [fp, #-56]
	cmp	ip, lr
	blt	.L4269
	add	ip, r5, r7
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L4268
.L4269:
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
	str	r3, [r10, #212]
	str	r0, [fp, #-52]
	ldr	r0, [r5, #3040]
	b	.L4270
.L4299:
	ldr	r1, [r1, #28]
	ldr	r0, [r5, #276]
	bl	FSP_SetDisplay
	ldr	r2, [r6]
	add	r3, r5, r7, lsl #2
	ldr	ip, [r2, #8]
	ldr	r3, [r3, #212]
	b	.L4273
.L4261:
	str	r2, [sp]
	mov	r0, #31
	ldr	r2, .L4300
	ldr	r1, .L4300+8
	bl	dprint_vfmw
	ldr	r3, [r6]
	ldr	r0, [r5, #276]
	mov	r2, r9
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
	ldr	r0, [r5, #3040]
	b	.L4260
.L4295:
	ldr	r1, [r5, #2840]
	mov	r9, #0
	add	r3, r1, #356
	add	r1, r1, #388
.L4263:
	ldr	r2, [r3, #4]!
	cmp	r9, r2
	movcc	r9, r2
	cmp	r3, r1
	bne	.L4263
	b	.L4264
.L4296:
	strb	r3, [r1, #2]
	mov	r0, r5
	ldr	r3, [fp, #-48]
	ldr	r1, [r6]
	sub	r3, r3, #1
	str	r3, [fp, #-48]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r10, #212]
	ldr	ip, [r8, #724]
	ldr	r2, .L4300
	cmp	ip, r3
	ldr	r1, .L4300+12
	sublt	r3, ip, #1
	strlt	r3, [r10, #212]
	ldr	r3, [r6]
	ldr	r3, [r3, #8]
	str	ip, [sp]
	str	r0, [fp, #-52]
	mov	r0, #31
	bl	dprint_vfmw
	ldr	r0, [r5, #3040]
	b	.L4270
.L4277:
	str	r0, [fp, #-48]
	b	.L4259
.L4278:
	str	r0, [fp, #-52]
	b	.L4294
.L4301:
	.align	2
.L4300:
	.word	.LANCHOR0+860
	.word	.LC505
	.word	.LC504
	.word	.LC506
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
	ldr	r3, [r4, #3208]
	strb	r2, [r3, #2]
	ldr	r1, [r4, #3208]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r4, #3208]
	ldr	r2, [r3, #32]
	ldr	r1, [r3, #8]
	add	r2, r5, r2, lsl #2
	str	r1, [r2, #212]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r7, r0
	bne	.L4303
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
.L4303:
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
	bne	.L4308
	mov	r0, r4
	ldr	r1, [fp, #-24]
	bl	HEVC_OutputOneFrmFromDPB
	cmp	r0, #0
	bne	.L4309
.L4306:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4308:
	ldr	r2, .L4310
	mov	r0, #1
	ldr	r1, .L4310+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4306
.L4309:
	ldr	r2, .L4310
	mov	r0, #1
	ldr	r1, .L4310+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4306
.L4311:
	.align	2
.L4310:
	.word	.LANCHOR0+884
	.word	.LC507
	.word	.LC508
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
	beq	.L4321
	ldr	r3, [r4, #3040]
	cmp	r3, #0
	addne	r5, r4, #3200
	movne	r6, #0
	addne	r5, r5, #4
	movne	r8, #1
	bne	.L4319
	b	.L4320
.L4327:
	strb	r8, [r3, #2]
	ldr	r1, [r5]
	bl	HEVC_OutputFrmToVO
	cmn	r0, #1
	mov	r9, r0
	beq	.L4326
.L4317:
	ldr	r3, [r4, #3040]
	cmp	r3, r6
	bls	.L4320
.L4319:
	ldr	r3, [r5, #4]!
	mov	r2, #0
	ldr	r0, [r4, #276]
	add	r6, r6, #1
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldr	r3, [r5]
	mov	r0, r4
	ldrb	r7, [r3, #2]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L4327
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #276]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L4317
	ldr	r3, [r5]
	ldr	r0, [r4, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #3040]
	cmp	r3, r6
	bhi	.L4319
.L4320:
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	mov	r9, #0
	str	r3, [r4, #216]
	bl	HEVC_InitDecBuffers
.L4313:
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4326:
	mov	r0, r7
	ldr	r2, .L4328
	ldr	r1, .L4328+4
	bl	dprint_vfmw
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4321:
	mvn	r9, #0
	b	.L4313
.L4329:
	.align	2
.L4328:
	.word	.LANCHOR0+916
	.word	.LC509
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
	ldr	r6, [r0, #2828]
	mov	r3, #0
	mov	r4, r0
	cmp	r6, r3
	str	r3, [r0, #352]
	beq	.L4360
	ldrb	r3, [r1]	@ zero_extendqisi2
	str	r3, [r6, #36]
	ldr	r3, [r0, #2856]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L4361
.L4337:
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L4338
	ldr	r3, [r4, #2828]
	ldr	r2, [r3, #8]
	cmp	r2, #1
	bls	.L4339
	ldr	r0, [r3, #36]
	cmp	r0, #1
	beq	.L4338
.L4339:
	ldr	r0, [r1, #16]
	cmp	r0, #0
	ble	.L4340
	ldr	r0, [r1, #4]
	cmp	r0, #0
	beq	.L4340
	ldr	ip, [r1, #8]
	cmp	ip, #0
	bne	.L4362
.L4340:
	mov	r2, #1
	str	r2, [r3, #36]
	ldr	r1, [r1, #20]
	ldr	r0, [r4, #276]
	bl	SM_ReleaseStreamSeg
.L4336:
	ldr	r3, [r4, #2828]
	ldr	r0, [r3, #36]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
.L4334:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4362:
	mov	lr, r2, asl #5
	mov	ip, #0
	sub	r2, lr, r2, asl #2
	add	r3, r3, r2
	str	r0, [r3, #40]
	ldr	r3, [r4, #2828]
	ldr	lr, [r1, #16]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #44]
	ldr	r3, [r4, #2828]
	ldr	lr, [r1, #8]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #48]
	ldr	r3, [r4, #2828]
	ldr	lr, [r1, #20]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #64]
	ldr	r3, [r4, #2828]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	ip, [r3, #56]
	ldr	r2, [r4, #2828]
	ldr	r3, [r2, #8]
	add	r3, r3, #1
	str	r3, [r2, #8]
	ldr	r3, [r4, #2856]
	ldrb	r3, [r3, #944]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4341
	add	r3, r4, #4096
	ldr	r0, [r1, #16]
	ldr	r2, [r3, #60]
	ldr	ip, [r3, #64]
	add	r0, r0, r2
	str	r0, [r3, #60]
	ldr	r2, [r1, #16]
	add	r2, r2, ip
	str	r2, [r3, #64]
.L4341:
	mov	r0, r4
	bl	HEVC_CombinePacket
	mov	r3, #1
	str	r3, [r4, #352]
	b	.L4336
.L4361:
	ldr	r3, [r3, #920]
	cmp	r3, #0
	bne	.L4336
	b	.L4337
.L4360:
	ldr	r3, [r1, #16]
	cmp	r3, #0
	ble	.L4332
	ldr	r3, [r1, #4]
	cmp	r3, #0
	beq	.L4332
	ldr	r3, [r1, #8]
	str	r1, [fp, #-32]
	cmp	r3, #0
	beq	.L4332
	bl	HEVC_FindNaluArraySlot
	ldr	r1, [fp, #-32]
	cmn	r0, #1
	mov	r5, r0
	beq	.L4363
	ldr	r3, [r4, #2852]
	mov	r0, r0, asl #7
	sub	r0, r0, r5, asl #5
	mov	r2, #1
	add	r0, r3, r0
	str	r0, [r4, #2828]
	ldr	r3, [r1, #4]
	str	r3, [r0, #40]
	ldr	r3, [r4, #2828]
	ldr	r0, [r1, #16]
	str	r0, [r3, #44]
	ldr	r3, [r4, #2828]
	ldr	r0, [r1, #20]
	str	r0, [r3, #64]
	ldr	r3, [r4, #2828]
	ldr	r0, [r1, #8]
	str	r0, [r3, #48]
	ldr	r3, [r4, #2828]
	str	r6, [r3, #56]
	ldr	r3, [r4, #2828]
	str	r2, [r3, #8]
	ldr	r3, [r4, #2828]
	strb	r6, [r3]
	ldr	r3, [r4, #2828]
	ldrb	r2, [r1]	@ zero_extendqisi2
	str	r2, [r3, #36]
	ldr	r3, [r4, #2856]
	ldrb	r3, [r3, #944]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4335
	add	r3, r4, #4096
	ldr	r0, [r1, #16]
	ldr	r2, [r3, #60]
	ldr	ip, [r3, #64]
	add	r0, r0, r2
	str	r0, [r3, #60]
	ldr	r2, [r1, #16]
	add	r2, r2, ip
	str	r2, [r3, #64]
.L4335:
	ldr	r3, [r1, #12]
	str	r3, [r4, #2364]
	b	.L4336
.L4338:
	ldr	r1, .L4364
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4334
.L4332:
	ldr	r1, .L4364+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4334
.L4363:
	ldr	r1, .L4364+8
	mov	r0, r6
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	mov	r0, r5
	b	.L4334
.L4365:
	.align	2
.L4364:
	.word	.LC512
	.word	.LC511
	.word	.LC510
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
	ldr	r1, [r0, #3040]
	mov	r4, r0
	cmp	r1, #0
	beq	.L4368
	add	r6, r0, #3200
	mov	r5, #0
	add	r6, r6, #4
	mov	r7, r5
	b	.L4370
.L4369:
	cmp	r1, r5
	bls	.L4368
.L4370:
	ldr	r3, [r6, #4]!
	add	r5, r5, #1
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L4369
	strb	r7, [r3, #1]
	mov	r2, #0
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #276]
	bl	FSP_SetRef
	ldr	r1, [r4, #3040]
	cmp	r1, r5
	bhi	.L4370
.L4368:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L4372
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L4368
	b	.L4372
.L4374:
	bl	HEVC_GetMinPOC
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	beq	.L4373
.L4372:
	ldr	r3, [r4, #3040]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	bne	.L4374
	mov	r0, r3
.L4373:
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
	beq	.L4383
	ldr	r2, .L4387
	mov	r0, #0
	ldr	r1, .L4387+4
	bl	dprint_vfmw
.L4383:
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4388:
	.align	2
.L4387:
	.word	.LANCHOR0+944
	.word	.LC513
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
	b	.L4390
.L4392:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L4398
.L4390:
	ldr	ip, [r4, #3040]
	mov	r0, #13
	ldr	lr, [r4, #3036]
	ldr	r2, .L4399
	cmp	ip, lr
	ldr	r1, .L4399+4
	mov	r3, ip
	bcs	.L4392
	b	.L4394
.L4395:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_OutputUnRefPicWithMinPoc
	cmp	r0, #0
	bne	.L4393
	ldr	ip, [r4, #3040]
	ldr	lr, [r4, #3036]
.L4394:
	cmp	ip, lr
	mov	r3, ip
	ldr	r2, .L4399
	mov	r0, #1
	ldr	r1, .L4399+8
	bcs	.L4395
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4398:
	ldr	r2, .L4399
	mov	r0, #1
	ldr	r1, .L4399+12
	bl	dprint_vfmw
	ldr	ip, [r4, #3040]
	ldr	lr, [r4, #3036]
	b	.L4394
.L4393:
	ldr	r2, .L4399
	mov	r0, #1
	ldr	r1, .L4399+16
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	mov	r0, r4
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	HEVC_ClearDPB
.L4400:
	.align	2
.L4399:
	.word	.LANCHOR0+960
	.word	.LC514
	.word	.LC516
	.word	.LC515
	.word	.LC508
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #16
	mov	r7, r1
	mov	r6, r0
	mov	r4, r2
	bhi	.L4405
	ldr	r3, [r2, #60]
	add	r5, r0, r1, lsl #2
	mov	r1, #1
	mov	r8, #0
	mov	r2, r1
	str	r3, [r5, #3208]
	str	r1, [r3, #48]
	ldr	r3, [r5, #3208]
	ldr	r0, [r0, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r1, [r5, #3208]
	mov	r2, #640
	subs	r3, r3, r8
	movne	r3, #1
	strb	r3, [r1, #1]
	ldr	r3, [r5, #3208]
	add	r1, r4, #64
	ldr	r0, [r4, #36]
	str	r0, [r3, #20]
	ldr	r0, [r5, #3208]
	add	r0, r0, #80
	bl	memcpy
	ldr	r3, [r5, #3208]
	ldr	r2, [r4, #40]
	add	r0, r6, #3200
	add	r1, r7, #1
	add	r0, r0, #8
	str	r2, [r3, #16]
	mov	r2, #4
	ldr	r3, [r5, #3208]
	ldr	ip, [r4, #60]
	str	ip, [r3, #76]
	ldr	r3, [r5, #3208]
	ldr	ip, [r4, #16]
	str	ip, [r3, #12]
	ldr	r3, [r5, #3208]
	ldr	ip, [r4, #12]
	str	ip, [r3, #8]
	ldr	r3, [r5, #3208]
	ldr	ip, [r4, #8]
	str	ip, [r3, #32]
	ldr	ip, [r5, #3208]
	ldr	r3, .L4407
	str	r8, [ip, #72]
	bl	qsort
	ldr	r3, [r6, #3040]
	mov	r0, r6
	add	r3, r3, #1
	str	r3, [r6, #3040]
	ldr	r1, [r4, #60]
	bl	HEVC_GetAPC
	subs	r3, r0, #0
	bne	.L4406
	mov	r0, r3
	strb	r3, [r4, #1]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4405:
	mov	r3, r1
	ldr	r2, .L4407+4
	ldr	r1, .L4407+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4406:
	ldr	r2, .L4407+4
	mov	r0, r8
	ldr	r1, .L4407+12
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_PrintDPBState
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4408:
	.align	2
.L4407:
	.word	HEVC_ComparePicByPocAsc
	.word	.LANCHOR0+984
	.word	.LC517
	.word	.LC518
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
	add	r4, r0, #4096
	mov	r5, r0
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4422
	ldr	r3, [r4, #68]
	mov	r2, #2
	str	r2, [r3, #48]
.L4411:
	ldr	r3, [r4, #68]
	mov	r2, #1
	mov	r0, r5
	strb	r2, [r3, #2]
	ldr	r1, [r4, #68]
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r4, r0
	beq	.L4423
	cmn	r0, #3
	beq	.L4415
	mov	r0, r5
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L4424
.L4415:
	mov	r0, #0
.L4412:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4422:
	bl	HEVC_SimpleSlideDPB
	add	r2, r4, #8
	ldr	r1, [r5, #3040]
	mov	r0, r5
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	beq	.L4411
	str	r0, [sp]
	movw	r3, #10993
	ldr	r2, .L4425
	mov	r0, #0
	ldr	r1, .L4425+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4412
.L4424:
	ldr	r2, .L4425
	mov	r0, #0
	ldr	r1, .L4425+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4412
.L4423:
	ldr	r2, .L4425
	mov	r0, #0
	ldr	r1, .L4425+12
	bl	dprint_vfmw
	mov	r0, r4
	b	.L4412
.L4426:
	.align	2
.L4425:
	.word	.LANCHOR0+1004
	.word	.LC519
	.word	.LC502
	.word	.LC520
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
	ldr	r1, [r0, #3040]
	mov	r4, r0
	ldr	r3, [r0, #3036]
	cmp	r1, r3
	bcs	.L4439
.L4428:
	add	r2, r4, #4096
	mov	r0, r4
	add	r2, r2, #8
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L4440
	add	r3, r4, #4096
	mov	r0, r4
	ldr	r1, [r3, #68]
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r5, r0
	beq	.L4441
	cmn	r0, #3
	beq	.L4434
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L4442
.L4434:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4439:
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L4438
	ldr	r2, .L4443
	mov	r0, #0
	ldr	r1, .L4443+4
	bl	dprint_vfmw
.L4438:
	ldr	r1, [r4, #3040]
	b	.L4428
.L4440:
	ldr	r2, .L4443
	mov	r0, #0
	ldr	r1, .L4443+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4442:
	mov	r0, r6
	ldr	r2, .L4443
	ldr	r1, .L4443+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4441:
	mov	r0, r6
	ldr	r2, .L4443
	ldr	r1, .L4443+16
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4444:
	.align	2
.L4443:
	.word	.LANCHOR0+1028
	.word	.LC521
	.word	.LC522
	.word	.LC502
	.word	.LC520
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
	ldr	r3, [r3, #3592]
	cmp	r3, #1
	beq	.L4446
	bl	HEVC_FirstFrameFastOut
	cmp	r0, #0
	bne	.L4469
.L4446:
	ldr	r1, [r4, #3040]
	ldr	r3, [r4, #3036]
	cmp	r1, r3
	bcs	.L4470
.L4448:
	add	r2, r4, #4096
	mov	r0, r4
	add	r2, r2, #8
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L4471
	ldr	r3, [r4, #3040]
	cmp	r3, #0
	bne	.L4472
.L4451:
	ldr	r2, [r4, #3036]
	cmp	r2, r3
	bls	.L4473
.L4468:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4473:
	add	r1, r4, #6144
	ldr	r0, [r4, #276]
	add	r1, r1, #40
	bl	FSP_IfCanGetDecFs
	cmp	r0, #0
	beq	.L4468
	mov	r0, r4
	bl	HEVC_RemoveFrmFullDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4470:
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L4467
	ldr	r1, .L4474
	mov	r0, #0
	bl	dprint_vfmw
.L4467:
	ldr	r1, [r4, #3040]
	b	.L4448
.L4472:
	mov	r0, r4
	bl	HEVC_OutputFrmFromDPB
	cmp	r0, #0
	bne	.L4452
	ldr	r3, [r4, #3040]
	b	.L4451
.L4471:
	mov	r2, r0
	ldr	r1, .L4474+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4469:
	ldr	r2, .L4474+8
	mov	r0, #0
	ldr	r1, .L4474+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4452:
	ldr	r2, .L4474+8
	mov	r0, #1
	ldr	r1, .L4474+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4475:
	.align	2
.L4474:
	.word	.LC524
	.word	.LC525
	.word	.LANCHOR0+1052
	.word	.LC523
	.word	.LC526
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
	ldr	r3, .L4539
	mov	r4, r0
	ldr	r2, [r0, #276]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L4529
.L4477:
	mov	r0, r4
	add	r6, r4, #4096
	bl	HEVC_RemoveDummyFrame
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4530
.L4478:
	ldrb	r5, [r6, #9]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L4531
	ldr	r2, [r6, #48]
	cmp	r2, #0
	beq	.L4483
	ldr	r5, [r6, #24]
	cmp	r5, #0
	beq	.L4532
.L4484:
	ldr	r3, [r4, #2856]
	ldr	r1, [r3, #4]
	cmp	r1, r2
	bcs	.L4483
	ldr	r5, [r3, #644]
	cmp	r5, #0
	beq	.L4533
.L4483:
	ldr	r3, [r4, #2864]
	ldr	r2, [r6, #68]
	add	r3, r3, #4096
	ldr	r3, [r3, #1088]
	str	r3, [r2, #40]
	ldr	r3, [r4, #2864]
	ldr	r2, [r6, #68]
	add	r3, r3, #4096
	ldr	r3, [r3, #1092]
	str	r3, [r2, #44]
	ldr	r3, [r4, #280]
	cmp	r3, #2
	beq	.L4534
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	beq	.L4535
	cmp	r3, #1
	beq	.L4536
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bls	.L4494
.L4496:
	mov	r0, r4
	mvn	r5, #0
	bl	HEVC_ClearCurrPic
	ldr	r2, .L4539+4
	ldr	r1, .L4539+8
	mov	r0, #1
	bl	dprint_vfmw
.L4495:
	mov	r3, #0
	strb	r3, [r6, #9]
.L4527:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4530:
	ldr	lr, [r6, #16]
	cmp	lr, #0
	beq	.L4478
	mov	r3, #280
	mul	r3, r3, lr
	add	r2, r4, r3
	add	r2, r2, #13120
	ldr	ip, [r2, #44]
	cmp	ip, #0
	beq	.L4478
	add	r1, r3, #13120
	add	r3, r3, #13376
	add	r1, r1, #48
	add	r3, r3, #52
	add	r1, r4, r1
	add	r3, r4, r3
	mov	r2, #0
	b	.L4480
.L4479:
	add	r2, r2, #1
	add	r3, r3, #1
	cmp	r2, ip
	beq	.L4478
.L4480:
	ldr	r0, [r1, #4]!
	cmp	r0, #0
	beq	.L4479
	ldrsb	r0, [r3]
	cmp	r0, #0
	beq	.L4479
	mov	r3, #70
	mov	r0, #280
	mla	r3, r3, lr, r2
	mov	r1, #0
	mla	lr, r0, lr, r4
	add	r3, r4, r3, lsl #2
	add	r0, lr, #13120
	add	r3, r3, #12288
	add	r2, lr, r2
	add	r2, r2, #13376
	str	r1, [r3, #884]
	str	r1, [r3, #948]
	str	r1, [r3, #1012]
	ldr	ip, [r0, #48]
	sub	ip, ip, #1
	str	ip, [r0, #48]
	strb	r1, [r2, #52]
	str	r1, [r3, #1076]
	b	.L4478
.L4529:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L4477
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L4477
	add	r3, r0, #8192
	ldrb	r3, [r3, #3536]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L4477
	bl	HEVC_Sei_Get_Frame_Pts
	b	.L4477
.L4531:
	ldr	r2, .L4539+4
	mov	r0, #1
	ldr	r1, .L4539+12
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4533:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, [r4, #2856]
	ldr	r2, [r6, #48]
	mov	r0, #1
	ldr	r1, .L4539+16
	ldr	r3, [r3, #4]
	bl	dprint_vfmw
	b	.L4527
.L4536:
	mov	r0, r4
	bl	HEVC_DecOrderProcess
	subs	r5, r0, #0
	bne	.L4493
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L4495
.L4494:
	mov	r0, r4
	bl	HEVC_DispOrderProcess
	subs	r5, r0, #0
	beq	.L4495
	ldr	r2, .L4539+4
	mov	r0, #0
	ldr	r1, .L4539+20
	bl	dprint_vfmw
	b	.L4489
.L4532:
	ldr	r2, .L4539+4
	mov	r0, #1
	ldr	r1, .L4539+24
	bl	dprint_vfmw
	ldr	r3, .L4539+28
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L4528
	mov	r3, r5
	mov	r2, r5
	mov	r1, #111
	ldr	r0, [r4, #276]
	blx	r7
.L4528:
	ldr	r2, [r6, #48]
	b	.L4484
.L4534:
	mov	r0, r4
	bl	HEVC_DirectOutput
	ldr	r3, [r6, #44]
	ldr	r2, [r4, #184]
	cmp	r3, r2
	addne	r3, r3, #540
	addne	r3, r3, #2
	movne	r1, #0
	strne	r1, [r4, r3, asl #2]
	mov	r5, r0
	strne	r2, [r6, #44]
	cmp	r0, #0
	bne	.L4537
.L4488:
	movw	r3, #11295
	mov	r2, r5
	ldr	r1, .L4539+32
	mov	r0, #14
	bl	dprint_vfmw
.L4489:
	cmn	r5, #1
	bne	.L4495
	b	.L4496
.L4535:
	mov	r0, r4
	bl	HEVC_SimpleDPBProcess
	subs	r5, r0, #0
	bne	.L4538
.L4491:
	movw	r3, #11310
	mov	r2, r5
	ldr	r1, .L4539+32
	mov	r0, #14
	bl	dprint_vfmw
	b	.L4489
.L4537:
	ldr	r2, .L4539+4
	mov	r0, #0
	ldr	r1, .L4539+36
	bl	dprint_vfmw
	b	.L4488
.L4538:
	ldr	r2, .L4539+4
	mov	r0, #0
	ldr	r1, .L4539+40
	bl	dprint_vfmw
	b	.L4491
.L4493:
	ldr	r2, .L4539+4
	mov	r0, #0
	ldr	r1, .L4539+44
	bl	dprint_vfmw
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L4489
	b	.L4494
.L4540:
	.align	2
.L4539:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+1076
	.word	.LC535
	.word	.LC527
	.word	.LC529
	.word	.LC534
	.word	.LC528
	.word	g_event_report
	.word	.LC531
	.word	.LC530
	.word	.LC532
	.word	.LC533
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
	ldr	r3, .L4586
	mov	r4, r0
	mov	r5, r1
	sub	r0, fp, #740
	mov	r2, #704
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	add	r0, r4, #13696
	add	r0, r0, #32
	mov	r6, #0
.L4546:
	ldr	r3, [r0, #48]
	cmp	r3, #0
	bne	.L4542
	cmp	r0, #0
	beq	.L4563
	ldr	ip, [r4, #3040]
	cmp	ip, #0
	beq	.L4563
	ldr	r2, [r4, #3208]
	cmp	r0, r2
	beq	.L4542
	add	r2, r4, #3200
	add	r2, r2, #8
	b	.L4544
.L4545:
	ldr	r1, [r2, #4]!
	cmp	r0, r1
	beq	.L4542
.L4544:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L4545
.L4563:
	mov	r8, #720
	mov	r7, r0
	mla	r8, r8, r6, r4
	mov	r2, #640
	sub	r0, fp, #676
	mov	r9, #1
	mov	r3, #101
	str	r5, [fp, #-728]
	add	r1, r8, #13760
	str	r3, [fp, #-700]
	add	r1, r1, #48
	strb	r9, [fp, #-739]
	strb	r9, [fp, #-740]
	bl	memcpy
	add	r2, r8, #13696
	add	r3, r8, #13760
	cmp	r6, #19
	movw	r1, #13728
	strb	r9, [r2, #34]
	mov	r6, #0
	str	r7, [fp, #-680]
	str	r6, [r3, #20]
	str	r6, [fp, #-524]
	strb	r9, [r8, r1]
	bgt	.L4547
	ldr	r0, [r4, #3040]
	cmp	r0, #0
	beq	.L4549
	add	r1, r4, #3200
	mov	ip, r6
	add	r1, r1, #4
	mvn	r2, #-2147483648
	mov	r8, r1
.L4552:
	ldr	lr, [r8, #4]!
	add	ip, ip, #1
	ldr	r3, [lr, #8]
	rsb	r3, r5, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bge	.L4551
	ldrb	lr, [lr, #1]	@ zero_extendqisi2
	cmp	lr, #0
	movne	r2, r3
	movne	r6, #1
.L4551:
	cmp	ip, r0
	bne	.L4552
	cmp	r6, #0
	beq	.L4549
	mov	r6, #0
	b	.L4553
.L4554:
	add	r6, r6, #1
	cmp	r6, r0
	beq	.L4555
.L4553:
	ldr	ip, [r1, #4]!
	ldr	r3, [ip, #8]
	rsb	r3, r5, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bne	.L4554
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4554
	ldr	r1, [ip, #28]
	add	r6, r4, r6, lsl #2
	ldr	r0, [r4, #276]
	ldr	r9, [ip, #32]
	bl	FSP_GetLogicFs
	ldr	r2, [r6, #3208]
	mov	r3, r5
	ldr	r1, .L4586+4
	ldr	r2, [r2, #8]
	mov	r8, r0
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r8, #0
	beq	.L4555
	ldr	r0, [r8, #28]
	cmp	r0, #0
	beq	.L4584
	mov	r1, #0
	ldr	r0, [r4, #276]
	bl	FSP_NewLogicFs
	mov	r7, r0
	mov	r1, r0
	ldr	r0, [r4, #276]
	bl	FSP_GetLogicFs
	mvn	r2, r7
	mov	r2, r2, lsr #31
	cmp	r0, #0
	mov	r3, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L4558
	ldr	r1, [fp, #-680]
	sub	r2, fp, #740
	mov	r0, r4
	str	r7, [r1, #28]
	ldr	r1, [r8, #28]
	str	r1, [r3, #28]
	ldr	r1, [r8, #32]
	str	r1, [r3, #32]
	ldrsb	r3, [r8, #4]
	ldr	r1, [r4, #3040]
	str	r9, [fp, #-732]
	str	r3, [fp, #-704]
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L4585
	ldr	r0, [r4, #276]
	mov	r1, r7
	mov	r2, r6
	bl	FSP_SetDisplay
	add	r3, r4, #4096
	mov	r0, r6
	ldr	r3, [r3, #744]
	add	r4, r4, r3, lsl #2
	ldr	r3, [r4, #244]
	cmn	r3, #-2147483647
	streq	r5, [r4, #244]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4542:
	add	r6, r6, #1
	add	r0, r0, #720
	cmp	r6, #20
	bne	.L4546
.L4547:
	ldr	r1, .L4586+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L4579:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4555:
	ldr	r1, .L4586+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4558:
	ldr	r3, [fp, #-680]
	mov	r0, r2
	ldr	r1, .L4586+16
	strb	r2, [r3]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4579
.L4585:
	ldr	r3, [fp, #-680]
	mov	r1, r7
	mov	r5, #0
	mov	r2, #1
	strb	r5, [r3]
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
	mov	r0, r5
	ldr	r1, .L4586+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4579
.L4549:
	mov	r0, #0
	ldr	r1, .L4586+24
	strb	r0, [r7]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4579
.L4584:
	ldr	r1, .L4586+28
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	b	.L4579
.L4587:
	.align	2
.L4586:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC539
	.word	.LC536
	.word	.LC537
	.word	.LC541
	.word	.LC542
	.word	.LC538
	.word	.LC540
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
	ldrb	r0, [r4, #1]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L4589
.L4593:
	mov	r0, r4
	add	r5, r4, #4096
	bl	HEVC_ApplyReferencePictureSet
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	b	.L4590
.L4599:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.14
	ldr	r1, .L4611
	cmp	r0, #0
	mov	r0, #1
	bne	.L4603
	ldr	r2, [fp, #-24]
	bl	dprint_vfmw
	ldr	r3, [r4, #2856]
	mov	r0, r4
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L4597
	ldr	r1, [fp, #-24]
	bl	HEVC_CreateLostPicture
	cmp	r0, #0
	bne	.L4609
.L4590:
	ldr	r3, [r5, #740]
	sub	r1, fp, #24
	mov	r0, r4
	sub	r3, r3, #19
	cmp	r3, #2
	bhi	.L4599
.L4603:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4610
.L4601:
	mov	r0, r4
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	mov	r0, r4
	bl	HEVC_RecoverDPBProcess
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4597:
	ldr	ip, [fp, #-24]
	mov	r0, #1
	ldr	r3, [r5, #724]
	ldr	r1, .L4611+4
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4609:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4589:
	ldr	r3, [r4, #3064]
	cmp	r3, #0
	addne	r3, r4, #3056
	movne	r2, #0
	addne	r3, r3, #12
	movne	ip, r2
	beq	.L4595
.L4594:
	ldr	r1, [r3, #4]!
	add	r2, r2, #1
	str	ip, [r1, #60]
	ldr	r1, [r3]
	str	r0, [r1, #64]
	ldr	r1, [r4, #3064]
	cmp	r2, r1
	bcc	.L4594
.L4595:
	ldr	r3, [r4, #3068]
	cmp	r3, #0
	addne	r2, r4, #3136
	movne	r3, #0
	movne	r0, #1
	movne	ip, r3
	beq	.L4593
.L4596:
	ldr	r1, [r2, #4]!
	add	r3, r3, #1
	str	ip, [r1, #60]
	ldr	r1, [r2]
	str	r0, [r1, #64]
	ldr	r1, [r4, #3068]
	cmp	r3, r1
	bcc	.L4596
	b	.L4593
.L4610:
	mov	r0, r4
	bl	HEVC_UpdateInterLayerReflist
	b	.L4601
.L4612:
	.align	2
.L4611:
	.word	.LC543
	.word	.LC544
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
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, [r0, #176]
	mov	r4, r0
	cmp	r3, #2
	bls	.L4672
	ldr	r3, [r0, #320]
	add	r5, r0, #4096
	ldr	r2, [r0, #324]
	mov	r0, #1
	ldr	r1, [r4, #2856]
	add	r3, r3, r0
	cmp	r3, r2
	movlt	r3, r2
	str	r3, [r4, #320]
	rsb	r3, r2, r3
	str	r3, [r1, #584]
	strb	r0, [r5, #8]
	ldr	r6, [r4, #272]
	ldr	r2, [r4, #280]
	ubfx	r6, r6, #16, #3
	cmp	r2, r6
	beq	.L4618
	subs	r3, r6, #2
	sub	r1, r2, #2
	movne	r3, #1
	cmp	r1, r0
	movhi	r3, #0
	cmp	r3, #0
	beq	.L4618
	cmp	r6, #4
	cmpne	r6, r0
	bls	.L4673
.L4618:
	cmp	r6, #2
	str	r6, [r4, #280]
	beq	.L4620
	cmp	r6, #3
	bne	.L4668
.L4669:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
.L4667:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4668:
	ldr	r3, [r4, #260]
	cmp	r3, #0
	beq	.L4637
	cmp	r6, #4
	ldr	r3, [r5, #24]
	beq	.L4674
.L4626:
	cmp	r3, #2
	bne	.L4628
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4675
.L4639:
	ldr	r2, [r4, #264]
	mov	r0, #2
	ldr	r1, .L4677
	sub	r2, r2, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L4676
	ldr	r1, [r5, #36]
	add	r0, r4, #8192
	ldr	ip, [r5, #40]
	clz	r2, r1
	str	ip, [r5, #3772]
	mov	r2, r2, lsr #5
	str	r2, [r5, #3780]
	str	r3, [r0, #832]
	ldr	r3, [r4, #2856]
	ldr	r2, [r3, #600]
	strb	r2, [r5, #2440]
	ldr	r2, [r3, #604]
	strb	r2, [r5, #2441]
	ldr	r2, [r3, #608]
	strb	r2, [r5, #2443]
	ldr	r2, [r3, #612]
	strb	r2, [r5, #2444]
	ldr	r3, [r3, #652]
	str	r3, [r5, #3768]
	ldr	r3, [r4, #264]
	cmp	r3, #0
	beq	.L4633
	add	r2, r4, #6528
	add	r3, r5, #4096
	add	r2, r2, #8
	str	r2, [r4, #2864]
	ldr	ip, [r5, #52]
	add	r1, r1, #1
	mov	r2, #0
	str	ip, [r3, #3528]
	ldr	ip, [r5, #56]
	str	ip, [r3, #3532]
	str	r1, [r5, #36]
	str	r2, [r3, #3524]
	ldr	r1, [r5, #24]
	cmp	r1, r2
	bne	.L4633
	ldr	r2, [r0, #836]
	cmp	r2, #0
	beq	.L4642
.L4636:
	ldr	r3, [r2]
	ldr	r0, [r2, #4]
	ldr	r2, [r2, #1504]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L4636
.L4635:
	ldr	r3, .L4677+4
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L4633
	sub	r2, fp, #28
	ldr	r0, [r4, #276]
	mov	r3, #4
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	r6
.L4633:
	ldr	ip, [r5, #64]
	mov	r0, #0
	ldr	r1, [r5, #68]
	ldr	r3, [r5, #60]
	str	ip, [r5, #60]
	ldr	r2, [r1, #320]
	rsb	r3, ip, r3
	add	r2, r2, r3
	str	r2, [r1, #320]
	ldr	r2, [r5, #312]
	add	r3, r3, r2
	str	r3, [r5, #312]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4628:
	cmp	r3, #1
	streqb	r3, [r4, #8]
	b	.L4639
.L4620:
	ldr	r3, [r5, #24]
	cmp	r3, #0
	bne	.L4624
	ldr	r3, [r4, #260]
	cmp	r3, #0
	bne	.L4639
.L4637:
	ldr	r3, .L4677+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4624
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	r5
.L4624:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L4667
.L4674:
	cmp	r3, #0
	moveq	r3, #2
	streqb	r3, [r4, #8]
	beq	.L4639
	b	.L4626
.L4675:
	ldr	r3, .L4677+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4639
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L4639
	mov	r3, #1
	ldr	r2, [r5, #20]
	mov	r0, r3
	ldr	r1, .L4677+12
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, .L4677+4
	ldr	r5, [r3]
	cmp	r5, #0
	mvneq	r0, #0
	beq	.L4667
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #127
	blx	r5
	mvn	r0, #0
	b	.L4667
.L4673:
	mov	r3, r6
	ldr	r1, .L4677+16
	bl	dprint_vfmw
	str	r6, [r4, #280]
	b	.L4669
.L4676:
	ldr	r2, .L4677+4
	ldr	r5, [r2]
	cmp	r5, #0
	beq	.L4631
	mov	r2, r3
	mov	r1, #127
	ldr	r0, [r4, #276]
	blx	r5
.L4631:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r2, .L4677+20
	ldr	r1, .L4677+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4667
.L4672:
	bl	HEVC_ClearCurrPic
	ldr	r3, .L4677+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4615
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	r5
.L4615:
	ldr	r3, [r4, #268]
	cmp	r3, #524288
	bls	.L4616
	ldr	r1, .L4677+28
	mov	r0, #0
	bl	dprint_vfmw
.L4616:
	ldr	r1, .L4677+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4667
.L4642:
	mov	r1, r2
	b	.L4635
.L4678:
	.align	2
.L4677:
	.word	.LC549
	.word	g_event_report
	.word	g_allow_B_before_P
	.word	.LC548
	.word	.LC547
	.word	.LANCHOR0+1096
	.word	.LC550
	.word	.LC545
	.word	.LC546
	UNWIND(.fnend)
	.size	HEVC_DecVDM, .-HEVC_DecVDM
	.align	2
	.global	HEVC_VES_Splitter
	.type	HEVC_VES_Splitter, %function
HEVC_VES_Splitter:
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
	mov	r4, r0
	mov	r5, r1
	ldr	r0, [r0, #2808]
	mov	r1, #16
	mov	r9, r2
	str	r3, [fp, #-56]
	mov	r10, #0
	str	r10, [fp, #-48]
	bl	BsGet
	mov	r1, #8
	add	r6, r4, #4096
	mov	r7, r0
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #24
	and	r8, r0, #31
	ldr	r0, [r4, #2808]
	bl	BsBack
	ldr	r2, [r6, #504]
	cmp	r5, r10
	str	r10, [r6, #492]
	str	r2, [fp, #-48]
	beq	.L4681
	cmp	r5, #1
	bne	.L4829
	cmp	r9, #1
	beq	.L4830
	movw	r0, #31745
	cmp	r8, #25
	cmpeq	r7, r0
	moveq	r8, #1
	movne	r8, #0
	bne	.L4710
	ldr	r7, .L4840
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L4711
	mov	r3, r10
	mov	r2, r10
	mov	r1, #112
	ldr	r0, [r4, #276]
	blx	r5
.L4711:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2828]
	subs	r5, r0, #0
	beq	.L4712
.L4826:
	cmp	r1, #0
	beq	.L4715
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4715:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L4817
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4689
.L4829:
	mov	r2, r5
	ldr	r1, .L4840+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
.L4689:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4681:
	cmp	r9, #1
	beq	.L4831
	bic	r7, r7, #512
	movw	r3, #31745
	cmp	r7, r3
	beq	.L4832
.L4724:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4710:
	movw	r3, #32257
	cmp	r7, r3
	movne	r0, r5
	bne	.L4689
	ldr	r1, .L4840+8
	movw	r3, #2549
	ldr	r2, .L4840+12
	mov	r0, r8
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4817
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2828]
	mvn	r0, #0
	b	.L4689
.L4832:
	ldr	r1, .L4840+16
	movw	r3, #2404
	ldr	r2, .L4840+12
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4817
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2828]
	mvn	r0, #0
	b	.L4689
.L4712:
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r6, #492]
	bhi	.L4833
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r6, #496]
	add	r3, r3, r0
	ldr	r0, [r4, #276]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r8, r0, #0
	bne	.L4834
	ldr	r5, .L4840+20
	mov	r2, #5
	ldr	r1, .L4840+24
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2828]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r6, #492]
	add	r1, r1, #6
	blx	r3
	ldr	r0, [r6, #492]
	add	r3, r0, #5
	str	r3, [r6, #492]
	ldr	r1, [r4, #2828]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L4717
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L4718
	add	r2, r0, #10
	ldr	r1, .L4840+28
	movw	r3, #2507
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4719
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2828]
.L4719:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L4720
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	r5
.L4720:
	ldr	r0, [r4, #276]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movwne	r3, #2514
	beq	.L4817
.L4816:
	ldr	r2, .L4840+12
	mov	r0, #0
	ldr	r1, .L4840+32
	bl	dprint_vfmw
.L4817:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4830:
	ldr	r3, [fp, #-56]
	movw	r2, #31745
	cmp	r7, r2
	cmpeq	r3, #2
	moveq	r5, #1
	movne	r5, #0
	cmp	r8, #25
	movne	r5, #0
	andeq	r5, r5, #1
	cmp	r5, #0
	bne	.L4835
	movw	r3, #32257
	cmp	r7, r3
	beq	.L4836
	cmp	r7, r2
	bne	.L4837
.L4699:
	ldr	r1, [r4, #2828]
.L4823:
	cmp	r1, #0
	beq	.L4701
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2828]
	mov	r0, r5
	b	.L4689
.L4831:
	movw	r0, #31745
	cmp	r8, #25
	cmpeq	r7, r0
	moveq	r8, #1
	movne	r8, #0
	bne	.L4684
	ldr	r7, .L4840
	ldr	r8, [r7]
	cmp	r8, #0
	beq	.L4685
	mov	r3, r5
	mov	r2, r5
	mov	r1, #112
	ldr	r0, [r4, #276]
	blx	r8
.L4685:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2828]
	subs	r5, r0, #0
	beq	.L4686
	cmp	r1, #0
	beq	.L4691
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4691:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L4817
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L4817
.L4684:
	movw	r3, #32257
	cmp	r7, r3
	bne	.L4724
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4701
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2828]
	mov	r0, r8
	b	.L4689
.L4833:
	ldr	r1, .L4840+28
	movw	r3, #2483
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4715
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2828]
	b	.L4715
.L4701:
	mov	r0, #0
	b	.L4689
.L4686:
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r6, #492]
	bls	.L4690
	ldr	r1, .L4840+28
	movw	r3, #2318
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4691
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2828]
	b	.L4691
.L4718:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r3, [r4, #2828]
	ldr	r2, [r6, #492]
	ldr	r3, [r3, #72]
	add	r3, r3, r2
	str	r3, [r6, #492]
.L4717:
	ldr	r0, [r4, #276]
	ldr	r7, .L4840+36
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L4721
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #276]
	ldr	r1, [r6, #492]
	ldr	r3, [r5, #44]
	ldr	r2, [r7, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #276]
.L4721:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	movwne	r3, #2537
	beq	.L4699
	b	.L4816
.L4837:
	mov	r1, #8
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	ldr	r0, [r4, #2808]
	ubfx	r5, r5, #1, #6
	bl	BsSkip
	cmp	r5, #49
	beq	.L4838
.L4709:
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4701
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2828]
	b	.L4689
.L4835:
	ldr	r7, .L4840
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L4704
	mov	r3, r10
	mov	r2, r10
	mov	r1, #112
	ldr	r0, [r4, #276]
	blx	r5
.L4704:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2828]
	subs	r5, r0, #0
	beq	.L4823
	b	.L4826
.L4690:
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r6, #496]
	add	r3, r3, r0
	ldr	r0, [r4, #276]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r8, r0, #0
	bne	.L4839
	ldr	r5, .L4840+20
	mov	r2, #5
	ldr	r1, .L4840+24
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2828]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r6, #492]
	add	r1, r1, #6
	blx	r3
	ldr	r0, [r6, #492]
	add	r3, r0, #5
	str	r3, [r6, #492]
	ldr	r1, [r4, #2828]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L4694
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L4695
	add	r2, r0, #10
	ldr	r1, .L4840+28
	movw	r3, #2342
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4696
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2828]
.L4696:
	ldr	r5, [r7]
	cmp	r5, #0
	beq	.L4697
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	r5
.L4697:
	ldr	r0, [r4, #276]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movwne	r3, #2349
	beq	.L4817
	b	.L4816
.L4695:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r3, [r4, #2828]
	ldr	r2, [r6, #492]
	ldr	r3, [r3, #72]
	add	r3, r3, r2
	str	r3, [r6, #492]
.L4694:
	ldr	r0, [r4, #276]
	ldr	r7, .L4840+36
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L4698
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #276]
	ldr	r1, [r6, #492]
	ldr	r3, [r5, #44]
	ldr	r2, [r7, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #276]
.L4698:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	beq	.L4699
	movw	r3, #2377
	b	.L4816
.L4836:
	ldr	r0, [r4, #2808]
	mov	r1, #16
	bl	BsSkip
	mov	r0, r9
	b	.L4689
.L4838:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	bne	.L4709
	ldr	r3, [r4, #2828]
	ldr	r0, [r4, #2808]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	ldr	r0, [r4, #2808]
	mov	r1, #24
	bl	BsSkip
	mov	r0, #2
	b	.L4689
.L4834:
	mov	r0, r5
	movw	r3, #2495
	ldr	r2, .L4840+12
	ldr	r1, .L4840+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4689
.L4839:
	mov	r0, r5
	movw	r3, #2330
	ldr	r2, .L4840+12
	ldr	r1, .L4840+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4689
.L4841:
	.align	2
.L4840:
	.word	g_event_report
	.word	.LC556
	.word	.LC555
	.word	.LANCHOR0+1108
	.word	.LC554
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+208
	.word	.LC551
	.word	.LC553
	.word	vfmw_save_metadata_file
	.word	.LC552
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
	ldr	r0, [r0, #3040]
	cmp	r0, #0
	beq	.L4854
	add	r2, r4, #3200
	mov	r5, #0
	add	r2, r2, #4
	mov	r3, r5
.L4845:
	ldr	r1, [r2, #4]!
	add	r3, r3, #1
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	cmp	r1, #0
	addeq	r5, r5, #1
	cmp	r3, r0
	bne	.L4845
.L4846:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L4846
	cmp	r5, #0
	ble	.L4848
.L4852:
	ldr	r1, [r4, #3040]
	cmp	r1, #0
	beq	.L4849
	ldr	r3, [r4, #3208]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4856
	add	r2, r4, #3200
	mov	r3, #0
	add	r2, r2, #8
	b	.L4853
.L4850:
	ldr	r0, [r2, #4]!
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L4856
.L4853:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L4850
.L4849:
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	subs	r5, r5, #1
	bne	.L4852
.L4848:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4856:
	mov	r1, r3
	b	.L4849
.L4854:
	mov	r5, r0
	b	.L4846
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
	ldr	r3, [r0, #2828]
	add	r5, r0, #4096
	ldr	r2, .L4946
	mov	ip, #0
	mov	r4, r0
	ldr	r1, [r3, #16]
	str	r1, [r5, #740]
	ldr	r1, [r3, #28]
	str	r1, [r5, #736]
	ldr	r6, [r3, #24]
	str	r6, [r5, #744]
	ldr	r1, [r0, #276]
	strb	ip, [r0, #3]
	ldr	r2, [r2, r1, asl #2]
	ldrsb	r1, [r2, #44]
	cmp	r1, #1
	beq	.L4932
.L4867:
	ldr	r3, [r5, #864]
	cmp	r3, #1
	beq	.L4933
.L4868:
	ldr	r2, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r2, r3
	bcs	.L4934
	ldrb	r3, [r5, #9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4935
	mov	r0, r4
	bl	HEVC_PicTypeStatistic
	mov	r0, r4
	bl	HEVC_CalcStreamBits
	ldr	r3, [r5, #864]
	cmp	r3, #2
	beq	.L4886
	ldr	r3, [r4, #2368]
	cmp	r3, #0
	bne	.L4887
	ldrb	r3, [r5, #713]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4936
.L4887:
	mov	r0, r4
	bl	HEVC_WriteSliceMsg
	cmp	r0, #0
	bne	.L4937
.L4890:
	ldr	r3, [r4, #2368]
	cmp	r3, #0
	beq	.L4938
.L4892:
	ldr	r3, [r4, #3488]
	mov	r0, #0
	str	r3, [r5, #52]
	ldr	r3, [r4, #3492]
	str	r3, [r5, #56]
.L4873:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4938:
	ldr	r3, [r5, #748]
	mov	r2, #1
	str	r3, [r4, #328]
	ldr	r3, [r5, #724]
	str	r2, [r4, #172]
	str	r3, [r4, #284]
	b	.L4892
.L4933:
	ldr	r3, [r4, #2368]
	cmp	r3, #0
	bne	.L4870
	ldr	r3, [r5, #740]
	clz	r7, r6
	sub	r3, r3, #16
	mov	r7, r7, lsr #5
	cmp	r3, #4
	cmpls	r6, #0
	bne	.L4939
.L4871:
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L4940
.L4872:
	add	r3, r4, r6
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	andeq	r3, r7, #1
	cmp	r3, #0
	beq	.L4874
	ldr	r3, [r4, #3040]
	cmp	r3, #0
	bne	.L4941
.L4874:
	ldr	r0, [r4, #2856]
	ldr	r1, [r0, #12]
	cmp	r1, #0
	bne	.L4875
	ldr	r3, [r4, #2376]
	cmp	r3, #1
	beq	.L4942
	ldr	r3, [r5, #736]
	ldr	r2, [r4, #2840]
	add	r3, r3, #90
	ldr	r1, [r2, r3, asl #2]
.L4878:
	cmp	r7, #0
	beq	.L4875
	add	r6, r4, r6, lsl #2
	ldr	r3, [r6, #212]
	cmp	r3, #-2147483647
	beq	.L4875
	ldr	r2, [r5, #724]
	add	r1, r1, r3
	cmp	r2, r1
	bge	.L4875
	ldr	r1, [r5, #740]
	cmp	r1, #21
	bne	.L4875
	ldr	r1, .L4946+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_CRAOutputFrame
	mov	r3, #-2147483647
	str	r3, [r6, #212]
	ldr	r0, [r4, #2856]
.L4875:
	ldr	r3, [r0, #8]
	cmp	r3, #2
	beq	.L4870
	ldr	r3, [r0, #24]
	cmp	r3, #2
	bne	.L4880
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4943
.L4881:
	mov	r0, r4
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
.L4870:
	mov	r0, r4
	bl	HEVC_InitPic
	cmn	r0, #2
	beq	.L4873
	cmp	r0, #0
	bne	.L4944
	ldr	r3, [r4, #264]
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r4, #264]
	bl	HEVC_SetScalingList
	mov	r0, r4
	bl	HEVC_WritePicMsg
	cmp	r0, #0
	beq	.L4868
	ldr	r1, .L4946+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4873
.L4932:
	ldr	r1, [r2, #160]
	cmp	r1, #1
	bne	.L4867
	ldr	r2, [r2, #164]
	cmp	r2, #2
	bne	.L4867
	ldr	r1, [r3, #16]
	bl	HEVC_Get_Last_IDR_Frame_Info
	b	.L4867
.L4886:
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4890
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
	b	.L4890
.L4936:
	mov	r0, r4
	bl	HEVC_DecList
	cmp	r0, #0
	bne	.L4945
	mov	r0, r4
	bl	HEVC_IsRefListWrong
	cmp	r0, #0
	beq	.L4887
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r1, .L4946+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4873
.L4939:
	mov	r0, r4
	bl	HEVC_IsPVRFlushPic
	cmp	r0, #0
	beq	.L4872
	b	.L4871
.L4880:
	mov	r0, r4
	bl	HEVC_RefPicProcess
	cmp	r0, #0
	beq	.L4870
	mvn	r0, #0
	b	.L4873
.L4941:
	mov	r0, r4
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L4874
	ldr	r2, .L4946+16
	mov	r0, #1
	ldr	r1, .L4946+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4873
.L4935:
	ldr	r1, .L4946+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4873
.L4942:
	ldr	ip, [r4, #2840]
	add	r3, ip, #356
	add	ip, ip, #388
.L4877:
	ldr	r2, [r3, #4]!
	cmp	r1, r2
	movcc	r1, r2
	cmp	r3, ip
	bne	.L4877
	b	.L4878
.L4934:
	ldr	r1, .L4946+28
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	ldr	r2, [r4, #152]
	cmp	r3, r2
	bcc	.L4884
	ldr	r1, .L4946+32
	ldr	r5, [r1]
	cmp	r5, #0
	beq	.L4884
	str	r3, [fp, #-36]
	mov	r1, #108
	str	r2, [fp, #-32]
	mov	r3, #8
	sub	r2, fp, #36
	ldr	r0, [r4, #276]
	blx	r5
.L4884:
	ldr	r1, .L4946+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L4873
.L4937:
	ldr	r1, .L4946+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4873
.L4944:
	ldr	r1, .L4946+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4873
.L4943:
	mov	r0, r4
	bl	HEVC_UpdateInterLayerReflist
	b	.L4881
.L4945:
	mov	r2, r0
	ldr	r1, .L4946+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4873
.L4940:
	ldr	r2, .L4946+16
	mov	r0, #1
	ldr	r1, .L4946+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4873
.L4947:
	.align	2
.L4946:
	.word	s_pstVfmwChan
	.word	.LC559
	.word	.LC561
	.word	.LC566
	.word	.LANCHOR0+1128
	.word	.LC558
	.word	.LC564
	.word	.LC562
	.word	g_event_report
	.word	.LC563
	.word	.LC567
	.word	.LC560
	.word	.LC565
	.word	.LC557
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
	ldr	ip, [r0, #2828]
	mov	r4, r0
	ldr	r3, [ip, #8]
	cmp	r3, #0
	ldrne	r1, [r0, #268]
	movne	r2, ip
	movne	r3, #0
	beq	.L4953
.L4952:
	ldr	r0, [r2, #44]
	add	r3, r3, #1
	add	r2, r2, #28
	add	r1, r1, r0
	str	r1, [r4, #268]
	ldr	r0, [ip, #8]
	cmp	r0, r3
	bhi	.L4952
.L4953:
	mov	r3, #0
	strb	r3, [ip]
	ldr	r3, [r4, #2828]
	ldr	r2, [r3, #16]
	sub	r2, r2, #36
	cmp	r2, #1
	bls	.L5094
.L4951:
	ldr	r2, [r3, #4]
	add	r2, r2, #16
	str	r2, [r3, #4]
	ldr	r1, [r4, #2828]
	ldr	r2, [r1, #16]
	cmp	r2, #49
	ldrls	pc, [pc, r2, asl #2]
	b	.L4954
.L4956:
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4955
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4957
	.word	.L4958
	.word	.L4959
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4960
	.word	.L4960
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4954
	.word	.L4961
	.word	.L4962
.L5094:
	mov	r2, #1
	strb	r2, [r4, #3]
	b	.L4951
.L4962:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	beq	.L5095
.L4978:
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L5081
.L5083:
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2828]
.L5080:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4955:
	mov	r0, r4
	bl	HEVC_DecSlice
	cmn	r0, #2
	beq	.L5080
	cmp	r0, #0
	beq	.L5081
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L5092
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L5092:
	ldr	r3, .L5097
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L5082
.L5084:
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #113
	blx	r5
.L5082:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4957:
	mov	r0, r4
	bl	HEVC_DecVPS
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4963
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4963:
	cmp	r5, #0
	bne	.L5096
.L5081:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4958:
	mov	r0, r4
	bl	HEVC_DecSPS
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4968
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4968:
	cmp	r5, #0
	beq	.L5081
	ldr	r6, .L5097
	mov	r0, #1
	ldr	r1, .L5097+4
	bl	dprint_vfmw
	ldr	r7, [r6]
	cmp	r7, #0
	bne	.L5088
	b	.L5082
.L4959:
	mov	r0, r4
	bl	HEVC_DecPPS
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4970
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4970:
	cmp	r5, #0
	beq	.L5081
	ldr	r6, .L5097
	mov	r0, #1
	ldr	r1, .L5097+8
	bl	dprint_vfmw
	ldr	r7, [r6]
	cmp	r7, #0
	beq	.L5082
.L5088:
	sub	r2, fp, #28
	mvn	r5, #0
	mov	r3, #4
	mov	r1, #100
	str	r5, [r2, #-4]!
	ldr	r0, [r4, #276]
	blx	r7
	ldr	r6, [r6]
	cmp	r6, #0
	beq	.L5082
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #113
	blx	r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4960:
	mov	r0, r4
	bl	HEVC_DecSEI
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4971
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4971:
	cmp	r5, #0
	beq	.L5081
	ldr	r1, .L5097+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L5092
.L4961:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4976
	cmp	r1, #0
	beq	.L4975
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4975:
	add	r3, r4, #4096
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L5081
.L4976:
	add	r5, r4, #2992
	mov	r1, #32
	add	r5, r5, #12
	mov	r6, #0
	strb	r6, [r4, #10]
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
	bne	.L5081
	ldr	r5, .L5097
	ldr	r7, [r5]
	cmp	r7, #0
	beq	.L4977
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #276]
	blx	r7
.L4977:
	add	r3, r4, #4096
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L5081
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L5081
.L4980:
	ldr	r5, [r5]
	cmp	r5, #0
	bne	.L5084
	b	.L5082
.L4954:
	ldr	r1, .L5097+16
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	ldr	r3, [r1, #16]
	cmp	r3, #63
	bhi	.L4981
	cmp	r1, #0
	bne	.L5083
	b	.L5081
.L4981:
	ldr	r5, .L5097
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L4982
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	r6
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4983
.L4984:
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L4983:
	ldr	r5, [r5]
	cmp	r5, #0
	beq	.L5081
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L5081
.L4982:
	cmp	r1, #0
	bne	.L4984
	b	.L5081
.L5096:
	ldr	r6, .L5097
	mov	r0, #1
	ldr	r1, .L5097+20
	bl	dprint_vfmw
	ldr	r7, [r6]
	cmp	r7, #0
	bne	.L5088
	b	.L5082
.L5095:
	ldr	r5, .L5097
	strb	r0, [r4, #11]
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L4979
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	r6
.L4979:
	add	r3, r4, #4096
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4978
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L4978
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L4980
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
	b	.L4980
.L5098:
	.align	2
.L5097:
	.word	g_event_report
	.word	.LC569
	.word	.LC570
	.word	.LC571
	.word	.LC572
	.word	.LC568
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
	ldr	r0, [r0, #276]
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
	ldr	ip, .L5125
	mov	r4, r0
	mov	r3, #0
	mov	r8, r1
	add	r0, r0, #4800
	str	r3, [r2]
	mov	r1, r3
	str	r3, [r8]
	mov	r6, r2
	ldr	r3, [ip, #48]
	mov	r2, #1376
	add	r0, r0, #8
	add	r5, r4, #4096
	blx	r3
	ldr	r3, [r4, #2828]
	mov	r0, r4
	ldr	r2, [r3, #16]
	str	r2, [r5, #740]
	ldr	r2, [r3, #28]
	str	r2, [r5, #736]
	ldr	r3, [r3, #24]
	str	r3, [r5, #744]
	bl	HEVC_DecSliceSegmentHeader
	cmp	r0, #0
	bne	.L5120
	ldr	r2, [r5, #748]
	movw	r1, #5036
	ldr	r3, [r4, #2820]
	movw	r7, #12668
	ldr	r9, [r4, #2368]
	mla	r3, r1, r2, r3
	ldr	r2, [r4, #2816]
	cmp	r9, #1
	ldr	r3, [r3, #32]
	mla	r7, r7, r3, r2
	beq	.L5121
	ldr	r3, [r5, #864]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r8]
	ldr	r0, [r4, #2840]
	ldr	ip, [r4, #2856]
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
	beq	.L5122
.L5106:
	cmp	r3, r2
	moveq	r2, r1
	orrne	r2, r1, #1
	cmp	lr, r0
	moveq	r3, r2
	orrne	r3, r2, #1
	cmp	r3, #0
	beq	.L5109
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L5123
.L5110:
	mov	r0, #0
	mov	r3, #1
	str	r3, [r6]
.L5119:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L5121:
	ldr	r0, [r4, #2808]
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
	bne	.L5104
.L5109:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L5120:
	ldr	r1, .L5125+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L5125+8
	ldr	r5, [r3]
	cmp	r5, #0
	mvneq	r0, #0
	beq	.L5119
	sub	r2, fp, #36
	ldr	r0, [r4, #276]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	r5
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L5122:
	ldr	r5, [r7, #96]
	ldr	r7, [r7, #88]
	cmp	r5, r7
	movcc	r5, r7
	str	r5, [ip, #932]
	ldr	r5, [r4, #2840]
	ldr	r7, [r4, #2856]
	ldr	ip, [r5, #96]
	ldr	r5, [r5, #88]
	ldr	r8, [r7, #932]
	cmp	ip, r5
	movcc	ip, r5
	cmp	ip, #8
	movls	r5, #0
	movhi	r5, #1
	cmp	r8, #8
	movne	r5, #0
	cmp	r5, #0
	beq	.L5124
.L5107:
	mov	ip, #1
	str	ip, [r7, #936]
	str	ip, [r6]
	b	.L5106
.L5123:
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L5110
	ldr	r3, [r4, #2396]
	mov	r0, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r6]
	b	.L5119
.L5124:
	sub	ip, ip, #8
	cmp	r8, #8
	clz	ip, ip
	mov	ip, ip, lsr #5
	movle	ip, #0
	cmp	ip, #0
	beq	.L5106
	b	.L5107
.L5104:
	mov	r3, r0
	mov	r2, r5
	mov	r0, r9
	ldr	r1, .L5125+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L5119
.L5126:
	.align	2
.L5125:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC573
	.word	g_event_report
	.word	.LC574
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
	bne	.L5129
	add	r3, r4, #4096
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L5131
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5129:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5131:
	ldr	r2, .L5132
	ldr	r1, .L5132+4
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5133:
	.align	2
.L5132:
	.word	.LANCHOR0+1144
	.word	.LC575
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
	ldr	r2, [r0, #836]
	cmp	r2, #0
	beq	.L5137
	mov	r0, #0
.L5136:
	ldr	r3, [r2]
	ldr	r1, [r2, #4]
	ldr	r2, [r2, #1504]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L5136
	ldmfd	sp, {fp, sp, pc}
.L5137:
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
	ldr	r3, [r0, #2364]
	mov	r5, #0
	mov	r4, r0
	str	r5, [r0, #2368]
	cmp	r3, #2
	str	r5, [r0, #2376]
	beq	.L5168
	cmp	r3, #1
	beq	.L5169
.L5153:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5169:
	ldr	r3, [r0, #2372]
	cmp	r3, #1
	bne	.L5153
	str	r5, [r0, #2372]
.L5167:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5168:
	ldr	r3, [r0, #2360]
	cmp	r3, r5
	beq	.L5167
	ldr	r3, [r0, #2372]
	cmp	r3, #1
	beq	.L5153
	ldr	r0, [r0, #276]
	bl	VCTRL_CheckFreshSeg
	cmp	r0, #0
	beq	.L5167
	ldr	r0, [r4, #276]
	bl	VCTRL_CheckFreshRaw
	cmp	r0, #0
	beq	.L5167
	ldr	r3, [r4, #2828]
	ldr	r0, [r4, #2808]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2808]
	bl	BsSkip
	ldr	r0, [r4, #2808]
	bl	BsResidBits
	cmp	r0, #15
	ble	.L5167
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsSkip
	mov	r1, #6
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #9
	mov	r6, r0
	ldr	r0, [r4, #2808]
	bl	BsSkip
	mov	r0, r6
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	mov	r7, r0
	beq	.L5170
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L5167
	sub	r3, r6, #48
	sub	r6, r6, #32
	cmp	r6, #2
	cmphi	r3, #1
	bhi	.L5167
.L5149:
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	bne	.L5167
	add	r2, r4, #4096
	mov	r3, #1
	mvn	r0, #0
	str	r3, [r4, #2376]
	strb	r3, [r2, #8]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5170:
	ldr	r0, [r4, #2808]
	bl	BsResidBits
	cmp	r0, #0
	movle	r0, r5
	ble	.L5146
	mov	r1, r7
	ldr	r0, [r4, #2808]
	bl	BsGet
.L5146:
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L5147
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
	bne	.L5149
.L5147:
	add	r3, r4, #4096
	mov	r5, #0
	mov	r2, #1
	str	r5, [r4, #2372]
	str	r2, [r4, #2368]
	mov	r0, r5
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	str	r3, [r4, #2380]
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
	beq	.L5174
	ldr	r2, [r0, #2864]
	cmp	r2, #0
	beq	.L5179
.L5174:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5179:
	add	r2, r0, #4096
	ldr	r2, [r2, #2464]
	cmp	r2, #1
	bls	.L5174
	ldr	r2, [r0, #2384]
	cmp	r3, r2
	beq	.L5174
	ldr	r3, [r0, #2368]
	cmp	r3, #1
	beq	.L5180
	cmp	r3, #0
	bne	.L5174
	ldr	r0, [r0, #276]
	bl	VCTRL_CheckFreshRaw
	cmp	r0, #0
	beq	.L5174
	ldr	r0, [r4, #276]
	bl	VCTRL_CheckFreshSeg
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5180:
	ldr	r0, [r0, #2828]
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
	ldr	r5, [r0, #2372]
	mov	r4, r0
	cmp	r5, #1
	beq	.L5194
.L5182:
	mov	r0, r4
	bl	HEVCDEC_IsNeedSedOnly
	cmp	r0, #1
	beq	.L5195
	ldr	r3, [r4, #2368]
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	ip, [r4, #2380]
	add	r3, r4, #4096
	ldr	r0, [r4, #204]
	ldr	r1, [r4, #176]
	ldr	r2, [r4, #260]
	sub	r0, r0, #1
	sub	r1, r1, #1
	str	r0, [r4, #204]
	str	r1, [r4, #176]
	sub	r2, r2, #1
	str	r2, [r4, #260]
	strb	ip, [r3, #9]
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5194:
	ldr	r3, [r0, #204]
	cmp	r3, #0
	beq	.L5182
	ldr	r6, [r0, #2864]
	cmp	r6, #0
	bne	.L5182
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L5196
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2828]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5195:
	add	r2, r4, #8192
	add	lr, r4, #4096
	add	r3, r4, #6528
	mov	ip, #0
	str	r0, [r2, #3524]
	add	r3, r3, #8
	ldr	r1, [r4, #204]
	str	r1, [r4, #2384]
	str	r1, [r2, #832]
	ldr	r2, [r4, #2856]
	ldr	r2, [r2, #652]
	str	r2, [lr, #3768]
	str	r3, [r4, #2864]
	str	ip, [r4, #2372]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5196:
	add	r3, r4, #4096
	str	r5, [r4, #2376]
	strb	r5, [r3, #8]
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
	ldr	r6, .L5209
	mov	r3, #180
	ldr	r2, [r0, #2864]
	mov	r4, r0
	ldr	lr, [r0, #276]
	mov	r0, #22
	mla	r1, r3, r1, r6
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #20]
	ldr	ip, .L5209+4
	add	r6, r1, #16
	ldr	r1, .L5209+8
	mla	r5, r2, r3, r3
	ldr	r3, [r6, #4]
	ldr	r7, [ip, lr, asl #2]
	add	r5, r5, r2
	mov	r2, r5
	bl	dprint_vfmw
	ldr	r3, [r6, #4]
	cmp	r3, r5
	ldr	r3, [r4, #2368]
	beq	.L5207
	cmp	r3, #1
	beq	.L5208
.L5202:
	mov	r3, #0
	str	r3, [r4, #2864]
.L5200:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5207:
	cmp	r3, #1
	beq	.L5199
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	addeq	r2, r4, #4096
	moveq	r3, #1
	streq	r3, [r4, #2376]
	streqb	r3, [r2, #8]
	b	.L5200
.L5208:
	ldr	ip, [r4, #2380]
	add	r3, r4, #4096
	ldr	r0, [r4, #204]
	mov	r5, #0
	ldr	r1, [r4, #176]
	ldr	r2, [r4, #260]
	sub	r0, r0, #1
	sub	r1, r1, #1
	str	r0, [r4, #204]
	str	r1, [r4, #176]
	sub	r2, r2, #1
	str	r5, [r4, #2372]
	str	r2, [r4, #260]
	strb	ip, [r3, #9]
	ldr	r1, [r4, #2828]
	cmp	r1, r5
	beq	.L5202
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2828]
	b	.L5202
.L5199:
	ldr	r5, [r4, #2380]
	add	lr, r4, #4096
	ldr	r0, [r4, #204]
	mov	ip, #0
	ldr	r1, [r4, #176]
	ldr	r2, [r4, #260]
	sub	r0, r0, #1
	str	r3, [r4, #2372]
	sub	r1, r1, #1
	str	r0, [r4, #204]
	sub	r2, r2, #1
	str	r1, [r4, #176]
	mov	r0, #0
	str	r2, [r4, #260]
	strb	r5, [lr, #9]
	strb	r3, [r7, #721]
	strb	r3, [r4, #9]
	str	ip, [r4, #2864]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5210:
	.align	2
.L5209:
	.word	g_BackUp
	.word	s_pstVfmwChan
	.word	.LC576
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
	ldr	r5, .L5217
	ldr	r4, [r5]
	cmp	r4, #0
	beq	.L5215
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5215:
	ldr	r6, .L5217+4
	movw	r0, #12624
	movt	r0, 10
	ldr	r3, [r6, #216]
	blx	r3
	cmp	r0, #0
	str	r0, [r5]
	beq	.L5216
	movw	r2, #12624
	ldr	r3, [r6, #48]
	movt	r2, 10
	mov	r1, r4
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5216:
	movw	r2, #15227
	ldr	r1, .L5217+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5218:
	.align	2
.L5217:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC577
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
	ldr	r4, .L5224
	ldr	r0, [r4]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L5224+4
	ldr	r3, [r3, #220]
	blx	r3
	mov	r3, #0
	str	r3, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5225:
	.align	2
.L5224:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVCDEC_ReleaseHevcGlbMem, .-HEVCDEC_ReleaseHevcGlbMem
	.align	2
	.global	HEVCDEC_Init
	.type	HEVCDEC_Init, %function
HEVCDEC_Init:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, .L5242
	mov	r5, r1
	mov	r4, r0
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L5237
	add	r7, r0, #4096
	ldr	r6, .L5242+4
	movw	r2, #28128
	mov	r1, #0
	ldr	r8, [r7, #2432]
	ldr	r3, [r6, #48]
	blx	r3
	mov	r3, #0
	str	r8, [r7, #2432]
	str	r5, [r4, #2856]
	str	r3, [r4, #2864]
	ldr	r3, [r5, #28]
	cmp	r3, #25
	beq	.L5238
	mov	r3, #17
	mov	r1, #65
	str	r3, [r4, #156]
	mov	r2, #200
	str	r3, [r4, #160]
	mov	r3, #210
	str	r1, [r4, #164]
	str	r2, [r4, #152]
	str	r3, [r4, #168]
.L5230:
	ldr	r0, [r5, #592]
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L5239
	ldr	r3, [r4, #156]
	movw	lr, #24912
	ldr	r0, [r4, #160]
	movw	r8, #12668
	ldr	r2, [r4, #152]
	movw	r7, #5036
	mul	lr, lr, r3
	ldr	r3, [r4, #2856]
	ldr	ip, [r3, #588]
	add	r9, r1, ip
	add	ip, lr, ip
	add	r3, r1, ip
	str	r3, [r4, #2816]
	mla	ip, r8, r0, ip
	ldr	r0, [r4, #168]
	str	r9, [r4, #2812]
	add	r10, r0, #1
	movw	r0, #1508
	mul	r2, r0, r2
	add	r0, r1, ip
	str	r0, [r4, #2820]
	mov	r3, r10, asl #7
	ldr	r0, [r4, #164]
	sub	r3, r3, r10, asl #5
	mla	r0, r7, r0, ip
	ldr	ip, [r4, #168]
	add	r10, r0, r2
	add	r0, r1, r0
	add	r3, r10, r3
	add	r10, r1, r10
	add	r1, r1, r3
	str	r1, [r4, #2848]
	ldr	r1, [r4, #2856]
	add	r3, r3, ip, lsl #2
	str	r0, [r4, #2860]
	str	r10, [r4, #2852]
	ldr	r1, [r1, #596]
	cmp	r3, r1
	bhi	.L5240
	ldr	r5, [r5, #624]
	cmp	r5, #0
	beq	.L5241
.L5233:
	ldr	r3, [r6, #48]
	mov	r1, #0
	blx	r3
	ldr	r3, [r4, #168]
	mov	r1, #0
	ldr	r5, [r6, #48]
	add	r3, r3, #1
	ldr	r0, [r4, #2852]
	mov	r2, r3, asl #7
	sub	r2, r2, r3, asl #5
	blx	r5
	ldr	r2, [r4, #168]
	ldr	r3, [r6, #48]
	mov	r1, #0
	ldr	r0, [r4, #2848]
	mov	r2, r2, asl #2
	blx	r3
	ldr	ip, [r4, #156]
	ldr	r0, [r4, #164]
	movw	r1, #24912
	ldr	lr, [r4, #160]
	movw	r2, #5036
	mul	r1, r1, ip
	movw	r3, #12668
	mul	r2, r2, r0
	ldr	r0, [r4, #2812]
	mul	r3, r3, lr
	sub	r1, r1, #24832
	sub	r1, r1, #80
	ldr	lr, [r4, #2820]
	add	r1, r0, r1
	sub	r2, r2, #4992
	ldr	r0, [r4, #2816]
	sub	r3, r3, #12608
	sub	r2, r2, #44
	sub	r3, r3, #60
	str	r1, [r4, #2836]
	add	r2, lr, r2
	add	r3, r0, r3
	str	r2, [r4, #2844]
	str	r3, [r4, #2840]
	mov	r0, r4
	str	ip, [r1, #4]
	ldr	r3, [r4, #2844]
	ldr	r2, [r4, #160]
	str	r2, [r3, #28]
	ldr	r3, [r4, #2840]
	ldr	r2, [r4, #164]
	str	r2, [r3, #56]
	bl	HEVC_InitScalingOrderTable
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #276]
	beq	.L5234
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	str	r3, [r4, #216]
	bl	HEVC_InitDecPara
	add	r3, r4, #8192
	mov	r2, #0
	movw	r0, #9999
	str	r2, [r3, #3592]
	mov	r2, #1
	ldr	r1, [r4, #164]
	ldr	r3, [r4, #2856]
	str	r0, [r4, #284]
	str	r1, [r4, #328]
	strb	r2, [r4]
	ldr	r2, [r3, #12]
	cmp	r2, #0
	bne	.L5235
.L5236:
	mov	r0, #0
	str	r0, [r4, #2388]
	ldr	r3, [r3, #640]
	str	r3, [r4, #2360]
.L5228:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5235:
	mov	r2, #6
	str	r2, [r3, #24]
	ldr	r3, [r4, #2856]
	b	.L5236
.L5241:
	mov	r2, lr
	ldr	r3, [r6, #48]
	mov	r1, r5
	mov	r0, r9
	blx	r3
	ldr	r2, [r4, #160]
	ldr	r3, [r6, #48]
	mov	r1, r5
	ldr	r0, [r4, #2816]
	mul	r2, r8, r2
	blx	r3
	ldr	r2, [r4, #164]
	ldr	r3, [r6, #48]
	mov	r1, r5
	ldr	r0, [r4, #2820]
	mul	r2, r7, r2
	blx	r3
	ldr	r2, [r4, #152]
	movw	r3, #1508
	ldr	r0, [r4, #2860]
	mul	r2, r3, r2
	b	.L5233
.L5238:
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
	b	.L5230
.L5240:
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L5242+8
	ldr	r1, .L5242+12
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L5228
.L5237:
	mov	r0, r3
	ldr	r2, .L5242+8
	ldr	r1, .L5242+16
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L5228
.L5234:
	ldr	r2, .L5242+8
	mov	r0, #0
	ldr	r1, .L5242+20
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L5228
.L5239:
	ldr	r2, .L5242+8
	ldr	r1, .L5242+24
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L5228
.L5243:
	.align	2
.L5242:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1164
	.word	.LC579
	.word	.LC72
	.word	.LC580
	.word	.LC578
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
	beq	.L5247
	add	r3, r0, #4096
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L5247
	add	r1, r0, #13696
	add	lr, r0, #27904
	add	r1, r1, #32
	add	lr, lr, #224
.L5253:
	ldr	r3, [r1, #48]
	cmp	r3, #0
	bne	.L5248
	cmp	r1, #0
	beq	.L5249
	ldr	ip, [r4, #3040]
	cmp	ip, #0
	beq	.L5249
	ldr	r2, [r4, #3208]
	cmp	r2, r1
	beq	.L5248
	add	r2, r4, #3200
	add	r2, r2, #8
	b	.L5250
.L5251:
	ldr	r0, [r2, #4]!
	cmp	r0, r1
	beq	.L5248
.L5250:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L5251
.L5249:
	ldr	r0, [r4, #276]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L5247
	cmn	r0, #1
	beq	.L5272
.L5271:
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L5247:
	mov	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L5248:
	add	r1, r1, #720
	cmp	r1, lr
	bne	.L5253
	add	r0, r4, #6144
	sub	r2, fp, #24
	sub	r1, fp, #28
	add	r0, r0, #40
	bl	GetQueueImgNum
	mov	r0, r4
	bl	HEVC_PrintFrameStoreState
	ldr	r1, .L5273
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r2, [r4, #180]
	ldr	r0, [r4, #3040]
	ldr	r3, [fp, #-28]
	sub	r2, r2, #2
	ldr	r1, [fp, #-24]
	rsb	r2, r0, r2
	add	r0, r3, r1
	cmp	r0, r2
	bge	.L5271
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L5273+4
	ldr	r1, .L5273+8
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L5272:
	ldr	r1, .L5273+12
	mov	r0, #1
	bl	dprint_vfmw
	add	r1, r4, #6144
	add	r1, r1, #40
	ldr	r0, [r4, #276]
	bl	FSP_ClearNotInVoQueue
	b	.L5271
.L5274:
	.align	2
.L5273:
	.word	.LC582
	.word	.LANCHOR0+1180
	.word	.LC583
	.word	.LC581
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
	beq	.L5362
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L5363
	ldr	r2, [r0, #2856]
	ldrb	ip, [r0, #9]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	cmp	ip, #1
	mov	r3, r3, asl #16
	and	r3, r3, #458752
	str	r3, [r0, #272]
	beq	.L5279
	ldr	r3, [r2, #872]
	cmp	r3, #1
	beq	.L5364
.L5280:
	mov	r0, r4
	bl	HEVC_ReceivePacket
	ldr	r3, [r4, #2828]
	str	r3, [r4, #2832]
	mov	r5, r0
.L5281:
	cmp	r5, #0
	mov	r3, #0
	strb	r3, [r4, #9]
	beq	.L5282
.L5309:
	mov	r0, #0
.L5359:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5364:
	ldr	r3, [r2, #920]
	cmp	r3, #1
	bne	.L5280
	ldr	r3, [r0, #352]
	cmp	r3, #1
	bne	.L5280
	ldr	r3, [r0, #2832]
	mov	r0, lr
	str	lr, [r4, #352]
	strb	lr, [r4, #9]
	str	r3, [r4, #2828]
	b	.L5359
.L5282:
	mov	r0, r4
	bl	HEVCDEC_CheckSedOnly
	cmp	r0, #0
	beq	.L5283
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L5365
.L5283:
	ldr	r3, [r4, #2828]
	mov	r5, #0
	ldr	r6, .L5373
	str	r5, [r3, #4]
	ldr	r3, [r4, #2828]
	ldr	r0, [r4, #2808]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2808]
	bl	BsSkip
	ldr	r3, [r4, #276]
	ldr	r3, [r6, r3, asl #2]
	ldrsb	r9, [r3, #44]
	cmp	r9, #1
	movne	r7, #3
	movne	r8, #2
	beq	.L5366
.L5285:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2808]
	ldr	r9, [r4, #2828]
	bl	BsGet
	mov	r1, #6
	str	r0, [r9, #16]
	ldr	r0, [r4, #2808]
	ldr	r9, [r4, #2828]
	bl	BsGet
	str	r0, [r9, #24]
	ldr	r9, [r4, #2828]
	ldr	r2, [r9, #24]
	cmp	r2, #1
	bls	.L5286
	mov	r3, #1
	ldr	r1, .L5373+4
	mov	r0, r3
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L5360
.L5361:
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r4, #2828]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5279:
	ldr	r3, [r0, #2828]
	cmp	r3, #0
	movne	r5, #0
	mvneq	r5, #0
	cmp	r3, #0
	bne	.L5281
	mov	r0, lr
	ldr	r1, .L5373+8
	bl	dprint_vfmw
	mov	r0, r5
	b	.L5359
.L5286:
	ldr	r3, [r4, #2856]
	ldr	r3, [r3, #24]
	bics	r1, r3, #4
	moveq	r1, #1
	movne	r1, #0
	cmp	r2, #0
	moveq	r1, #0
	andne	r1, r1, #1
	cmp	r1, #0
	bne	.L5367
	mov	r1, #3
	ldr	r0, [r4, #2808]
	bl	BsGet
	str	r0, [r9, #28]
	ldr	r9, [r4, #2828]
	ldr	r3, [r9, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r9, #28]
	ldrne	r9, [r4, #2828]
	ldr	r0, [r9, #16]
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	mov	r10, r0
	beq	.L5368
	mov	r3, #0
	str	r3, [r9, #4]
	ldr	r3, [r4, #2828]
	add	r0, r4, #2992
	add	r0, r0, #12
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2808]
	bl	BsSkip
	cmp	r7, #1
	cmpeq	r8, #1
	moveq	r7, #1
	movne	r7, #0
	cmp	r5, #1
	moveq	r5, #0
	andne	r5, r7, #1
	cmp	r5, #0
	beq	.L5307
	mov	r1, #16
	ldr	r0, [r4, #2808]
	bl	BsSkip
.L5307:
	mov	r1, #1
	ldr	r0, [r4, #2808]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2808]
	ldr	r5, [r4, #2828]
	bl	BsGet
	mov	r1, #6
	str	r0, [r5, #16]
	ldr	r0, [r4, #2808]
	ldr	r5, [r4, #2828]
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #24]
	ldr	r0, [r4, #2808]
	ldr	r5, [r4, #2828]
	bl	BsGet
	str	r0, [r5, #28]
	ldr	r2, [r4, #2828]
	ldr	r3, [r2, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r2, #28]
.L5297:
	mov	r0, r4
	bl	HEVC_DecOneNal
	cmn	r0, #2
	mov	r5, r0
	beq	.L5359
	cmp	r0, #0
	bne	.L5369
	add	r3, r4, #4096
	str	r0, [r3, #64]
	ldr	r3, [r4, #2360]
	cmp	r3, #1
	bne	.L5309
	mov	r0, r4
	bl	HEVCDEC_SetDecParam
	mov	r0, r5
	b	.L5359
.L5366:
	ldr	r8, [r3, #156]
	mov	r0, r4
	ldr	r7, [r3, #160]
	ldr	r3, [r3, #164]
	mov	r1, r8
	mov	r2, r7
	bl	HEVC_VES_Splitter
	cmp	r0, #2
	beq	.L5311
	cmp	r0, #1
	bne	.L5359
	b	.L5285
.L5369:
	ldr	r1, .L5373+12
	mov	r0, #22
	bl	dprint_vfmw
.L5360:
	mvn	r0, #0
	b	.L5359
.L5363:
	mov	r0, lr
	ldr	r1, .L5373+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L5359
.L5368:
	sub	r2, fp, #48
	sub	r1, fp, #52
	mov	r0, r4
	bl	HEVC_InquireSliceProperty
	subs	r3, r0, #0
	bne	.L5292
	ldr	r5, [fp, #-52]
	cmp	r5, #1
	beq	.L5370
.L5293:
	ldr	r5, [fp, #-48]
	cmp	r5, #1
	bne	.L5297
	ldr	r3, [r4, #2828]
	mov	r0, r4
	ldr	r3, [r3, #24]
	add	r3, r4, r3
	ldrb	r7, [r3, #4]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L5371
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L5372
.L5300:
	ldr	r0, [r4, #276]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L5297
	sub	r3, fp, #56
	ldr	r0, [r4, #276]
	sub	r2, fp, #60
	sub	r1, fp, #64
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4, #2856]
	ldr	r0, [r3, #732]
	cmp	r0, #1
	bne	.L5297
	ldr	r5, [fp, #-56]
	cmp	r5, #0
	bgt	.L5303
	ldr	r3, [fp, #-60]
	cmp	r3, #32
	bgt	.L5303
	ldr	r3, [r4, #2864]
	cmp	r3, #0
	bne	.L5303
	ldr	r2, [fp, #-48]
	cmp	r2, #0
	beq	.L5297
	ldr	r3, [r4, #264]
	cmp	r3, #0
	beq	.L5297
	ldr	r3, [r4, #2840]
	ldr	r1, [r4, #344]
	ldr	lr, [r3, #68]
	cmp	lr, r1
	beq	.L5297
	ldr	ip, [r3, #64]
	ldr	r3, [r4, #348]
	subs	r6, ip, r3
	movne	r6, #1
	cmp	r5, #0
	movne	r6, #0
	cmp	r6, #0
	beq	.L5297
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L5373+20
	bl	dprint_vfmw
	ldr	r3, [r4, #2840]
	ldr	r1, .L5373+24
	ldr	r2, [r3, #68]
	ldr	r5, [r1]
	str	r2, [r4, #344]
	cmp	r5, #0
	ldr	r3, [r3, #64]
	str	r3, [r4, #348]
	beq	.L5297
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	r5
	b	.L5297
.L5367:
	ldr	r1, .L5373+28
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	bne	.L5361
	b	.L5360
.L5311:
	mov	r5, r9
	b	.L5285
.L5365:
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L5284
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2828]
.L5284:
	mov	r0, r4
	bl	HEVCDEC_SetDecParam
	mvn	r0, #0
	b	.L5359
.L5292:
	ldr	r1, .L5373+32
	mov	r0, r10
	bl	dprint_vfmw
	ldr	r1, [r4, #2828]
	cmp	r1, #0
	beq	.L5305
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2828]
.L5305:
	ldr	r3, .L5373+24
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L5306
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	r5
.L5306:
	ldr	r3, [r4, #276]
	ldr	r3, [r6, r3, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	bne	.L5360
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L5360
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L5360
	add	r3, r4, #8192
	ldrb	r5, [r3, #3536]	@ zero_extendqisi2
	cmp	r5, #0
	bne	.L5360
	ldr	r3, .L5373+36
	add	r0, r4, #11712
	add	r0, r0, #16
	mov	r2, #56
	mov	r1, r5
	mov	r6, #0
	ldr	r3, [r3, #48]
	mov	r7, #0
	blx	r3
	add	r3, r4, #3488
	mvn	r0, #0
	strd	r6, [r3, #40]
	strd	r6, [r3, #16]
	strd	r6, [r3, #24]
	strd	r6, [r3, #32]
	str	r5, [r4, #3484]
	b	.L5359
.L5370:
	ldr	r2, [r4, #204]
	cmp	r2, #0
	bne	.L5294
	add	r3, r4, #4096
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L5293
	ldr	r2, .L5373+40
	ldr	r1, .L5373+44
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	b	.L5293
.L5362:
	mov	r0, r1
	ldr	r1, .L5373+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L5359
.L5294:
	ldr	ip, [r4, #2828]
	add	r0, r4, #2992
	mov	r2, #21
	add	r0, r0, #12
	ldr	r1, .L5373+52
	str	r3, [ip, #4]
	bl	BsInit
	mov	r1, #40
	ldr	r0, [r4, #2808]
	bl	BsSkip
	ldr	r3, [r4, #2828]
	mov	r2, #48
	mov	r0, r4
	str	r2, [r3, #16]
	strb	r5, [r4, #10]
	bl	HEVC_DecOneNal
	ldr	r3, [r4, #312]
	mvn	r0, #1
	strb	r5, [r4, #9]
	add	r3, r3, #1
	str	r3, [r4, #312]
	b	.L5359
.L5371:
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L5300
	mov	r0, r7
	ldr	r2, .L5373+56
	ldr	r1, .L5373+60
	bl	dprint_vfmw
	b	.L5300
.L5372:
	mov	r0, r5
	ldr	r2, .L5373+56
	ldr	r1, .L5373+64
	bl	dprint_vfmw
	b	.L5300
.L5303:
	ldr	r2, [r4, #276]
	mov	r3, #1
	mvn	r0, #1
	ldr	r2, [r6, r2, asl #2]
	str	r3, [r2, #1528]
	strb	r3, [r4, #9]
	b	.L5359
.L5374:
	.align	2
.L5373:
	.word	s_pstVfmwChan
	.word	.LC587
	.word	.LC586
	.word	.LC591
	.word	.LC585
	.word	.LC589
	.word	g_event_report
	.word	.LC588
	.word	.LC590
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1144
	.word	.LC575
	.word	.LC584
	.word	.LANCHOR0+1228
	.word	.LANCHOR0+1204
	.word	.LC558
	.word	.LC557
	UNWIND(.fnend)
	.size	HEVCDEC_DecodePacket, .-HEVCDEC_DecodePacket
	.align	2
	.global	HEVCDEC_VDMPostProc
	.type	HEVCDEC_VDMPostProc, %function
HEVCDEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 8
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
	ldr	r2, [r0, #2856]
	mov	r4, r0
	ldr	r0, [r5, #68]
	mov	r8, r3
	ldr	ip, [fp, #4]
	cmp	r0, #0
	ldr	r6, [r2, #644]
	str	r1, [r5, #48]
	ldrneb	r2, [r5, #2445]	@ zero_extendqisi2
	ldr	r3, [fp, #8]
	strneb	r2, [r0, #3]
	ldrneb	r2, [r5, #2440]	@ zero_extendqisi2
	strneb	r2, [r0, #4]
	ldr	r1, [r4, #2388]
	ldrne	r2, [r4, #2856]
	cmp	r1, #1
	bls	.L5377
.L5380:
	ldr	r1, [r5, #28]
	cmp	r1, #1920
	bhi	.L5409
.L5378:
	ldr	r2, [r2, #640]
	cmp	ip, #0
	str	r2, [r4, #2360]
	beq	.L5383
.L5413:
	mov	r2, r3, asl #6
	ldr	r1, .L5414
	sub	r3, r2, r3, asl #3
	add	r3, r3, r1
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L5410
	cmp	r3, #1
	beq	.L5383
	cmp	r6, #1
	beq	.L5411
.L5387:
	mov	r1, r8
	mov	r0, r4
	bl	HEVC_StorePicInDPB
	subs	r2, r0, #0
	bne	.L5412
	mov	r0, r2
	mov	r3, #1
	str	r3, [r4, #172]
.L5385:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5409:
	ldr	r1, [r2, #8]
	cmp	r1, #2
	movne	r2, #0
	strne	r2, [r4, #2360]
	beq	.L5378
	cmp	ip, #0
	bne	.L5413
.L5383:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	cmp	r6, #1
	bne	.L5387
.L5411:
	ldr	r9, [r4, #2864]
	ldr	r3, [r9, #1292]
	add	r3, r9, r3, lsl #2
	ldr	r10, [r3, #1476]
	mov	r0, r10
	bl	MEM_Phy2Vir
	ldr	r7, [r9, #192]
	ldr	r3, [r9, #196]
	mov	r1, r10
	add	r7, r7, #15
	ldr	r2, .L5414+4
	add	r3, r3, #15
	bic	r7, r7, #15
	bic	r3, r3, #15
	ldr	r9, [r2, #140]
	mul	r7, r3, r7
	mov	r7, r7, lsr #8
	mov	r2, r7, asl #4
	mov	r6, r0
	blx	r9
	cmp	r7, #0
	beq	.L5398
	mov	r0, #0
	mov	r3, r6
	mov	r10, r0
	mov	r9, r0
	mov	lr, r0
	mvn	r6, #-2147483648
	str	r4, [fp, #-48]
.L5394:
	ldrh	r1, [r3, #4]
	add	lr, lr, #1
	add	r3, r3, #16
	ubfx	r2, r1, #0, #15
	sxth	r1, r1
	rsb	ip, r1, #0
	tst	r1, #32768
	ldrh	r1, [r3, #-10]
	ubfxne	r2, ip, #0, #15
	ubfx	ip, r1, #0, #15
	sxth	r1, r1
	tst	r1, #32768
	rsb	r4, r1, #0
	ubfxne	ip, r4, #0, #15
	add	r2, r2, ip
	cmp	r6, r2
	add	r0, r0, r2
	movge	r6, r2
	cmp	r9, r2
	movlt	r9, r2
	cmp	r2, #0
	addeq	r10, r10, #1
	cmp	lr, r7
	bne	.L5394
	mov	r3, r10
	mov	r10, #100
	mul	r3, r10, r3
	ldr	r4, [fp, #-48]
	str	r3, [fp, #-48]
.L5388:
	mov	r1, r7
	bl	__aeabi_uidiv
	mov	r1, r7
	mov	r10, r0
	ldr	r0, [fp, #-48]
	bl	__aeabi_uidiv
	ldr	r2, [r5, #68]
	cmp	r0, #100
	moveq	r6, #0
	cmp	r2, #0
	beq	.L5396
	str	r9, [r2, #324]
	ldr	r2, [r5, #68]
	str	r6, [r2, #328]
	ldr	r2, [r5, #68]
	str	r10, [r2, #332]
	ldr	r2, [r5, #68]
	str	r0, [r2, #336]
	str	r9, [r5, #316]
	str	r6, [r5, #320]
	str	r10, [r5, #324]
	str	r0, [r5, #328]
	b	.L5387
.L5412:
	ldr	r1, .L5414+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5377:
	add	r1, r1, #1
	str	r1, [r4, #2388]
	cmp	r1, #1
	bls	.L5378
	b	.L5380
.L5410:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	mov	r0, #0
	b	.L5385
.L5398:
	str	r7, [fp, #-48]
	mov	r0, r7
	mvn	r6, #-2147483648
	mov	r9, r7
	b	.L5388
.L5396:
	mov	r0, r2
	ldr	r1, .L5414+12
	bl	dprint_vfmw
	b	.L5387
.L5415:
	.align	2
.L5414:
	.word	g_VdmDrvParam+40
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC593
	.word	.LC592
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
	ldrne	r2, [r0, #2840]
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
	ldrne	r2, [r0, #2840]
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
	ldr	r3, [r0, #3040]
	mov	r4, r0
	cmp	r3, #0
	bne	.L5423
	b	.L5427
.L5437:
	ldr	r3, [fp, #-36]
.L5424:
	mov	r1, r3
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r3, [r4, #3040]
	cmp	r3, #0
	beq	.L5427
.L5423:
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	mov	r6, #1
	bl	HEVC_GetMinPOC
	ldr	r3, [fp, #-36]
	mov	r0, r4
	add	r2, r4, r3, lsl #2
	ldr	r5, [r2, #3208]
	cmp	r5, #0
	mov	r1, r5
	beq	.L5424
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	cmp	r2, r6
	beq	.L5424
	strb	r6, [r5, #2]
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r7, r0, #0
	bne	.L5437
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_OutputFrame
	cmp	r0, #0
	beq	.L5437
	mov	r0, r7
	ldr	r2, .L5438
	ldr	r1, .L5438+4
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	b	.L5437
.L5427:
	add	r0, r4, #6144
	add	r0, r0, #40
	bl	GetVoLastImageID
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5439:
	.align	2
.L5438:
	.word	.LANCHOR0+1252
	.word	.LC501
	UNWIND(.fnend)
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.global	g_pGlbVar
	.global	g_RpuStartCode
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.16250, %object
	.size	__func__.16250, 17
__func__.16250:
	.ascii	"HEVC_OutputFrame\000"
	.space	3
	.type	__func__.14708, %object
	.size	__func__.14708, 26
__func__.14708:
	.ascii	"HEVC_OutputImgToViewQueue\000"
	.space	2
	.type	__func__.14137, %object
	.size	__func__.14137, 24
__func__.14137:
	.ascii	"HEVC_CheckVpsExtOverlap\000"
	.type	__func__.14142, %object
	.size	__func__.14142, 24
__func__.14142:
	.ascii	"HEVC_CheckPpsExtOverlap\000"
	.type	__func__.14147, %object
	.size	__func__.14147, 26
__func__.14147:
	.ascii	"HEVC_CheckSliceExtOverlap\000"
	.space	2
	.type	SarTable.14902, %object
	.size	SarTable.14902, 136
SarTable.14902:
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
	.type	__func__.15060, %object
	.size	__func__.15060, 18
__func__.15060:
	.ascii	"HEVC_CalcTileInfo\000"
	.space	2
	.type	__func__.15533, %object
	.size	__func__.15533, 27
__func__.15533:
	.ascii	"HEVC_GetUnRefPicWithMinPoc\000"
	.space	1
	.type	__func__.15542, %object
	.size	__func__.15542, 21
__func__.15542:
	.ascii	"HEVC_IncreaseDPBSize\000"
	.space	3
	.type	__func__.15775, %object
	.size	__func__.15775, 17
__func__.15775:
	.ascii	"HEVC_CalcTileMap\000"
	.space	3
	.type	__func__.15795, %object
	.size	__func__.15795, 17
__func__.15795:
	.ascii	"HEVC_WritePicMsg\000"
	.space	3
	.type	__func__.15824, %object
	.size	__func__.15824, 16
__func__.15824:
	.ascii	"HEVC_CheckListX\000"
	.type	__func__.15991, %object
	.size	__func__.15991, 16
__func__.15991:
	.ascii	"HEVC_RepairList\000"
	.type	__func__.16078, %object
	.size	__func__.16078, 16
__func__.16078:
	.ascii	"HEVC_ArrangeMem\000"
	.type	__func__.16151, %object
	.size	__func__.16151, 20
__func__.16151:
	.ascii	"HEVC_RemoveApcStore\000"
	.type	__func__.16429, %object
	.size	__func__.16429, 21
__func__.16429:
	.ascii	"HEVC_CheckFrameStore\000"
	.space	3
	.type	__func__.16497, %object
	.size	__func__.16497, 19
__func__.16497:
	.ascii	"HEVC_GetSLHDR1Info\000"
	.space	1
	.type	__func__.16624, %object
	.size	__func__.16624, 14
__func__.16624:
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
	.type	__func__.16940, %object
	.size	__func__.16940, 16
__func__.16940:
	.ascii	"HEVC_ReleaseNAL\000"
	.type	__func__.16110, %object
	.size	__func__.16110, 20
__func__.16110:
	.ascii	"HEVC_InitDecBuffers\000"
	.type	__func__.14556, %object
	.size	__func__.14556, 23
__func__.14556:
	.ascii	"HEVC_ParseVPSExtension\000"
	.space	1
	.type	__func__.15105, %object
	.size	__func__.15105, 12
__func__.15105:
	.ascii	"HEVC_DecVPS\000"
	.type	__func__.16682, %object
	.size	__func__.16682, 24
__func__.16682:
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
	.type	__func__.15171, %object
	.size	__func__.15171, 12
__func__.15171:
	.ascii	"HEVC_DecSPS\000"
	.type	__func__.15209, %object
	.size	__func__.15209, 12
__func__.15209:
	.ascii	"HEVC_DecPPS\000"
	.type	__func__.15647, %object
	.size	__func__.15647, 27
__func__.15647:
	.ascii	"HEVC_DecSliceSegmentHeader\000"
	.space	1
	.type	__func__.16089, %object
	.size	__func__.16089, 13
__func__.16089:
	.ascii	"HEVC_InitDPB\000"
	.space	3
	.type	__func__.14765, %object
	.size	__func__.14765, 20
__func__.14765:
	.ascii	"HEVC_ArrangeShvcMem\000"
	.type	__func__.16257, %object
	.size	__func__.16257, 19
__func__.16257:
	.ascii	"HEVC_OutputCurrPic\000"
	.space	1
	.type	__func__.16262, %object
	.size	__func__.16262, 23
__func__.16262:
	.ascii	"HEVC_FirstFrameFastOut\000"
	.space	1
	.type	__func__.16421, %object
	.size	__func__.16421, 19
__func__.16421:
	.ascii	"HEVC_OutputFrmToVO\000"
	.space	1
	.type	__func__.16377, %object
	.size	__func__.16377, 22
__func__.16377:
	.ascii	"HEVC_OutputFrmFromDPB\000"
	.space	2
	.type	__func__.15548, %object
	.size	__func__.15548, 30
__func__.15548:
	.ascii	"HEVC_OutputUnRefPicWithMinPoc\000"
	.space	2
	.type	__func__.16396, %object
	.size	__func__.16396, 27
__func__.16396:
	.ascii	"HEVC_FlushOutputFrmFromDPB\000"
	.space	1
	.type	__func__.17003, %object
	.size	__func__.17003, 14
__func__.17003:
	.ascii	"HEVC_ClearDPB\000"
	.space	2
	.type	__func__.15553, %object
	.size	__func__.15553, 23
__func__.15553:
	.ascii	"HEVC_RecoverDPBProcess\000"
	.space	1
	.type	__func__.16357, %object
	.size	__func__.16357, 20
__func__.16357:
	.ascii	"HEVC_InsertFrmInDPB\000"
	.type	__func__.16267, %object
	.size	__func__.16267, 22
__func__.16267:
	.ascii	"HEVC_SimpleDPBProcess\000"
	.space	2
	.type	__func__.16272, %object
	.size	__func__.16272, 21
__func__.16272:
	.ascii	"HEVC_DecOrderProcess\000"
	.space	3
	.type	__func__.16286, %object
	.size	__func__.16286, 22
__func__.16286:
	.ascii	"HEVC_DispOrderProcess\000"
	.space	2
	.type	__func__.16300, %object
	.size	__func__.16300, 19
__func__.16300:
	.ascii	"HEVC_StorePicInDPB\000"
	.space	1
	.type	__func__.15910, %object
	.size	__func__.15910, 12
__func__.15910:
	.ascii	"HEVC_DecVDM\000"
	.type	__func__.14791, %object
	.size	__func__.14791, 18
__func__.14791:
	.ascii	"HEVC_VES_Splitter\000"
	.space	2
	.type	__func__.15584, %object
	.size	__func__.15584, 14
__func__.15584:
	.ascii	"HEVC_DecSlice\000"
	.space	2
	.type	__func__.17085, %object
	.size	__func__.17085, 20
__func__.17085:
	.ascii	"HEVC_HaveSliceToDec\000"
	.type	__func__.17137, %object
	.size	__func__.17137, 13
__func__.17137:
	.ascii	"HEVCDEC_Init\000"
	.space	3
	.type	__func__.17151, %object
	.size	__func__.17151, 23
__func__.17151:
	.ascii	"HEVCDEC_GetImageBuffer\000"
	.space	1
	.type	__func__.17166, %object
	.size	__func__.17166, 21
__func__.17166:
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
	.type	__func__.17215, %object
	.size	__func__.17215, 21
__func__.17215:
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
	ASCII(.ascii	"../../core/syntax/hevc.c\000" )
	.space	3
.LC3:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%" )
	ASCII(.ascii	"d, logic_fs=%p, dec_fs=%p)\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"%s: pImg is NULL!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"View %d image queue is full, discard head image %d." )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"%s: view0 frame poc(%d) > view1 frame poc(%d)\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"%s: view1 frame poc(%d) > view0 frame poc(%d)\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"%s: Image(view=0, poc=%d) output failed!\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"%s: Image(view=1, poc=%d) output failed!\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"%s: InsertImgToVoQueue failed!\012\000" )
.LC12:
	ASCII(.ascii	"%s pVPSExt = NULL\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"%s pPPSExt = NULL\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"%s pSlcExt = NULL\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"line:%d ChanID(%d), pic_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range(0,%d).\012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"line:%d ChanID(%d), seq_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range[0,%d].\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"dar=%d\012\000" )
.LC18:
	ASCII(.ascii	"--------------- PrintNaluArraySlot START ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"--------------- PrintNaluArraySlot END ------------" )
	ASCII(.ascii	"---\012\000" )
.LC21:
	ASCII(.ascii	"NalArray[%d]=%p,is_valid=%d   \000" )
	.space	1
.LC22:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX START ---------" )
	ASCII(.ascii	"------\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"List0, size: %d\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"List1, size: %d\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"pListX[0][%d]:%p \000" )
	.space	2
.LC26:
	ASCII(.ascii	"pFrameStore:%p \000" )
.LC27:
	ASCII(.ascii	"pLogicFs:%p \000" )
	.space	3
.LC28:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX END -----------" )
	ASCII(.ascii	"----\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"pListX[1][%d]: %p\000" )
	.space	2
.LC30:
	ASCII(.ascii	"--------------- PrintFrameStoreState START --------" )
	ASCII(.ascii	"-------\012\000" )
.LC31:
	ASCII(.ascii	"--------------- PrintFrameStoreState END ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displa" )
	ASCII(.ascii	"yed=%d \000" )
	.space	1
.LC33:
	ASCII(.ascii	"p_usrdat[%d]=%p \000" )
	.space	3
.LC34:
	ASCII(.ascii	"--------------- PrintAPCState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"Layer %d: APC.used_size:%d, APC.size:%d\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"%d: is_used=%d, idc=%d, poc=%d\012\000" )
.LC37:
	ASCII(.ascii	"--------------- PrintAPCState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC38:
	ASCII(.ascii	"--------------- PrintDPBState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"DPB: size:%d, used_size:%d, negative:%d, positive:%" )
	ASCII(.ascii	"d, longterm:%d\012\000" )
	.space	1
.LC40:
	ASCII(.ascii	"fs[%d]:%p view %d non_existing:%d state:%d is_ref:%" )
	ASCII(.ascii	"d displayed:%d poc:%d long_term:%d LogicFs:%p, fsp_" )
	ASCII(.ascii	"ref:%d fsp_disp:%d logic_id:%d img_id:%d\012\000" )
.LC41:
	ASCII(.ascii	"--------------- PrintDPBState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC42:
	ASCII(.ascii	"fs[%d]\011\000" )
.LC43:
	ASCII(.ascii	"LogicFs:%p\011\000" )
.LC44:
	ASCII(.ascii	"LogicTick:%d\011\000" )
	.space	2
.LC45:
	ASCII(.ascii	"IsRef:%d\011\000" )
	.space	2
.LC46:
	ASCII(.ascii	"DispState:%d\011\000" )
	.space	2
.LC47:
	ASCII(.ascii	"LogicFs:Null\011\000" )
	.space	2
.LC48:
	ASCII(.ascii	"DecFs:%p\011\000" )
	.space	2
.LC49:
	ASCII(.ascii	"DecTick:%d\011\000" )
.LC50:
	ASCII(.ascii	"DecFs:Null\011\000" )
.LC51:
	ASCII(.ascii	"DispFs:%p\011\000" )
	.space	1
.LC52:
	ASCII(.ascii	"DispTick:%d\011\000" )
	.space	3
.LC53:
	ASCII(.ascii	"DispFs:Null\011\000" )
	.space	3
.LC54:
	ASCII(.ascii	"%s num_tile_columns(%d) out of range(0, %d].\012\000" )
	.space	2
.LC55:
	ASCII(.ascii	"%s num_tile_rows(%d) out of range(0, %d].\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"%s 0 idx(%d) out of range(0, 512).\012\000" )
.LC57:
	ASCII(.ascii	"%s 1 idx(%d) out of range(0, 512).\012\000" )
.LC58:
	ASCII(.ascii	"HEVC_Sei_User_Data_Unregistered payloadSize < 16\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC59:
	ASCII(.ascii	"pListX[0][%d] = NULL, listXsize[0] = %d\012\000" )
	.space	3
.LC60:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL, listXsize[0] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"pListX[0][%d] frame_store(%p), pstLogicFs(%p) inval" )
	ASCII(.ascii	"id\012\000" )
	.space	1
.LC62:
	ASCII(.ascii	"pListX[1][%d] = NULL, listXsize[1] = %d\012\000" )
	.space	3
.LC63:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL, listXsize[1] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC64:
	ASCII(.ascii	"pListX[i][%d] pstLogicFs(%p) invalid\012\000" )
	.space	2
.LC65:
	ASCII(.ascii	"%s DPB.used_size(%d) >= 17.\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"%s can't find such pic.\012\000" )
	.space	3
.LC67:
	ASCII(.ascii	"%s find pos=%d, poc=%d.\012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"%s DPB.size(%d) already reached max(%d).\012\000" )
	.space	2
.LC69:
	ASCII(.ascii	"%s increase DPB size to %d\012\000" )
.LC70:
	ASCII(.ascii	"%s no enough fs(total_fs_num=%d) to increase DPB si" )
	ASCII(.ascii	"ze.\012\000" )
.LC71:
	ASCII(.ascii	"TileWidthInCtb is 0\012\000" )
	.space	3
.LC72:
	ASCII(.ascii	"%s: g_pGlbVar is NULL!\012\000" )
.LC73:
	ASCII(.ascii	"image_id=%d, pmv_idc=%d\012\000" )
	.space	3
.LC74:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC75:
	ASCII(.ascii	"%s call HEVC_CalcTileInfo failed.\012\000" )
	.space	1
.LC76:
	ASCII(.ascii	"logic frame id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC77:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC78:
	ASCII(.ascii	"%s ERROR: bHaveIndependentSlice = 0\012\012\000" )
	.space	2
.LC79:
	ASCII(.ascii	"ListX ERROR: list0size >= %d\012\000" )
	.space	2
.LC80:
	ASCII(.ascii	"ListX ERROR: list1size >= %d\012\000" )
	.space	2
.LC81:
	ASCII(.ascii	"pListX[0][%d] = NULL\012\000" )
	.space	2
.LC82:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL\012\000" )
	.space	1
.LC83:
	ASCII(.ascii	"pListX[1][%d] = NULL\012\000" )
	.space	2
.LC84:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL\012\000" )
	.space	1
.LC85:
	ASCII(.ascii	"NumSlicePara(%d) >= MaxSliceNum(%d)\012\000" )
	.space	3
.LC86:
	ASCII(.ascii	"width is larger than 3! (%d, %d)\012\000" )
	.space	2
.LC87:
	ASCII(.ascii	"height is larger than 3! (%d, %d)\012\000" )
	.space	1
.LC88:
	ASCII(.ascii	"line:%d pic_parameter_set_id(%d) out of range(0,%d)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC89:
	ASCII(.ascii	"line:%d seq_parameter_set_id(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC90:
	ASCII(.ascii	"line:%d, i(%d) > Max(%d) num_of_pics %d\012\000" )
	.space	3
.LC91:
	ASCII(.ascii	"line:%d, i(%d) > Max(%d)(neg%d + pos%d)\012\000" )
	.space	3
.LC92:
	ASCII(.ascii	"%s unkown slice type(%d).\012\000" )
	.space	1
.LC93:
	ASCII(.ascii	"%s pListX[%d] no available pic to repair.\012\000" )
	.space	1
.LC94:
	ASCII(.ascii	"%s: pListX[%d][%d] = NULL, repair it with pos(%d).\012" )
	ASCII(.ascii	"\000" )
.LC95:
	ASCII(.ascii	"HEVC_InitListX error.\012\000" )
	.space	1
.LC96:
	ASCII(.ascii	"HEVC_RepairList error.\012\000" )
.LC97:
	ASCII(.ascii	"%s image size abnormal(%dx%d)\012\000" )
	.space	1
.LC98:
	ASCII(.ascii	"%s HEVC FSP_ConfigInstance failed!\012\000" )
.LC99:
	ASCII(.ascii	"%s fs[%d]->view_id = %d invalid.\012\000" )
	.space	2
.LC100:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC101:
	ASCII(.ascii	"Cant find free apc slot.\012\000" )
	.space	2
.LC102:
	ASCII(.ascii	"%s frame logic_fs_id=%d, state=%d\012\000" )
	.space	1
.LC103:
	ASCII(.ascii	"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null," )
	ASCII(.ascii	" logic_fs_id = %d\012\000" )
	.space	2
.LC104:
	ASCII(.ascii	"%s frame poc=%d, is already output\012\000" )
.LC105:
	ASCII(.ascii	"%s frame(%p) invalid, state:%d, non_existing:%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC106:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC107:
	ASCII(.ascii	"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STA" )
	ASCII(.ascii	"TE_NOT_USED\012\000" )
.LC108:
	ASCII(.ascii	"%-5d   specVersion\012\000" )
.LC109:
	ASCII(.ascii	"%-5d   payloadMode\012\000" )
.LC110:
	ASCII(.ascii	"%-5d   hdrPicColourSpace\012\000" )
	.space	2
.LC111:
	ASCII(.ascii	"%-5d   hdrMasterDisplayColourSpace\012\000" )
.LC112:
	ASCII(.ascii	"%-5d   hdrMasterDisplayMaxLuminance\012\000" )
	.space	3
.LC113:
	ASCII(.ascii	"%-5d   hdrMasterDisplayMinLuminance\012\000" )
	.space	3
.LC114:
	ASCII(.ascii	"%-5d   sdrPicColourSpace\012\000" )
	.space	2
.LC115:
	ASCII(.ascii	"%-5d   sdrMasterDisplayColourSpace\012\000" )
.LC116:
	ASCII(.ascii	"%-5d   tmInputSignalBlackLevelOffset\012\000" )
	.space	2
.LC117:
	ASCII(.ascii	"%-5d   tmInputSignalWhiteLevelOffset\012\000" )
	.space	2
.LC118:
	ASCII(.ascii	"%-5d   shadowGain\012\000" )
	.space	1
.LC119:
	ASCII(.ascii	"%-5d   highlightGain\012\000" )
	.space	2
.LC120:
	ASCII(.ascii	"%-5d   midToneWidthAdjFactor\012\000" )
	.space	2
.LC121:
	ASCII(.ascii	"%-5d   tmOutputFineTuningNumVal\012\000" )
	.space	3
.LC122:
	ASCII(.ascii	"%-5d   saturationGainNumVal\012\000" )
	.space	3
.LC123:
	ASCII(.ascii	"%-5d   tmOutputFineTuningX[%d]\012\000" )
.LC124:
	ASCII(.ascii	"%-5d   tmOutputFineTuningY[%d]\012\000" )
.LC125:
	ASCII(.ascii	"%-5d   saturationGainX[%d]\012\000" )
.LC126:
	ASCII(.ascii	"%-5d   saturationGainY[%d]\012\000" )
.LC127:
	ASCII(.ascii	"%-5d   luminanceMappingNumVal\012\000" )
	.space	1
.LC128:
	ASCII(.ascii	"%-5d   colourCorrectionNumVal\012\000" )
	.space	1
.LC129:
	ASCII(.ascii	"%-5d   luminanceMappingX[%d]\012\000" )
	.space	2
.LC130:
	ASCII(.ascii	"%-5d   luminanceMappingY[%d]\012\000" )
	.space	2
.LC131:
	ASCII(.ascii	"%-5d   chromaToLumaInjectionMuA\012\000" )
	.space	3
.LC132:
	ASCII(.ascii	"%-5d   chromaToLumaInjectionMuB\012\000" )
	.space	3
.LC133:
	ASCII(.ascii	"%-5d   colourCorrectionX[%d]\012\000" )
	.space	2
.LC134:
	ASCII(.ascii	"%-5d   colourCorrectionY[%d]\012\000" )
	.space	2
.LC135:
	ASCII(.ascii	"======SL_HDR1_METADATA= %d=======\012\000" )
	.space	1
.LC136:
	ASCII(.ascii	"%s, [%d %d %d %d %d]\012\000" )
	.space	2
.LC137:
	ASCII(.ascii	"%s HDR_Metadata_phy_addr is invalid!!\012\000" )
	.space	1
.LC138:
	ASCII(.ascii	"FS_ALLOC_ERR, ClearAll\012\000" )
.LC139:
	ASCII(.ascii	"Can not new logic fs! ClearAll\012\000" )
.LC140:
	ASCII(.ascii	"FSP_GetFspType -1\012\000" )
	.space	1
.LC141:
	ASCII(.ascii	"FSP_GetLogicFs return NULL\012\000" )
.LC142:
	ASCII(.ascii	"%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), err" )
	ASCII(.ascii	"or resilence.\012\000" )
	.space	2
.LC143:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC144:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC145:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC146:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC147:
	ASCII(.ascii	"sps with this seq_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC148:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck video_parameter_set_id out of r" )
	ASCII(.ascii	"ange\012\000" )
	.space	3
.LC149:
	ASCII(.ascii	"vps with this video_parameter_set_id = %d havn't be" )
	ASCII(.ascii	" decoded\012\000" )
	.space	3
.LC150:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, n" )
	ASCII(.ascii	"al_unit_type = %d, should skip this frame\012\000" )
	.space	2
.LC151:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d," )
	ASCII(.ascii	" nal_unit_type = %d, should skip this frame\012\000" )
.LC152:
	ASCII(.ascii	"%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocC" )
	ASCII(.ascii	"RA = %d, nal_unit_type = %d, should skip this frame" )
	ASCII(.ascii	"\012\000" )
.LC153:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code should not be zero.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC154:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code:%d\012\000" )
	.space	3
.LC155:
	ASCII(.ascii	"reserved_zero_2bits not equal 0.\012\000" )
	.space	2
.LC156:
	ASCII(.ascii	"HEVC_GetScalingListDefaultAddress NULL.\012\000" )
	.space	3
.LC157:
	ASCII(.ascii	"Error, BsLen: 0x%x, TotalPos: 0x%x\012\000" )
.LC158:
	ASCII(.ascii	"Panic: All zero data sequence in RBSP \012\000" )
.LC159:
	ASCII(.ascii	"nal_trail_zero_bit_num err\012\000" )
.LC160:
	ASCII(.ascii	"%s release streambuff=%p, bitstream_length=%d\012\000" )
	.space	1
.LC161:
	ASCII(.ascii	"%s DPB size exceed %d, force to %d\012\000" )
.LC162:
	ASCII(.ascii	"HEVC_CombinePacket FATAL: pCurrNal=NULL!\012\000" )
	.space	2
.LC163:
	ASCII(.ascii	"END of the bit buffer, copy the first packet!\012\000" )
	.space	1
.LC164:
	ASCII(.ascii	"tone_map_id\000" )
.LC165:
	ASCII(.ascii	"Unsupport: target_bit_depth(%d) > 8\012\000" )
	.space	3
.LC166:
	ASCII(.ascii	"pTon->num_pivots > 256\012\000" )
.LC167:
	ASCII(.ascii	"frame_packing_arrangement_id\000" )
	.space	3
.LC168:
	ASCII(.ascii	"frame_packing_arrangement_type(%d) out of range\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC169:
	ASCII(.ascii	"decoding_unit_idx\000" )
	.space	2
.LC170:
	ASCII(.ascii	"num_sps_ids_minus1\000" )
	.space	1
.LC171:
	ASCII(.ascii	"pAct->num_sps_ids_minus1 > 15\012\000" )
	.space	1
.LC172:
	ASCII(.ascii	"active_seq_parameter_set_id\000" )
.LC173:
	ASCII(.ascii	"bp_seq_parameter_set_id\000" )
.LC174:
	ASCII(.ascii	"Wrong bp_seq_parameter_set_id = %d, should be 0 to " )
	ASCII(.ascii	"15!\012\000" )
.LC175:
	ASCII(.ascii	"num_decoding_units_minus1\000" )
	.space	2
.LC176:
	ASCII(.ascii	"pPic->num_decoding_units_minus1 > 255\012\000" )
	.space	1
.LC177:
	ASCII(.ascii	"num_nalus_in_du_minus1\000" )
	.space	1
.LC178:
	ASCII(.ascii	"cv_rec_id\000" )
	.space	2
.LC179:
	ASCII(.ascii	"HEVC_Sei_User_Data_Registered_Itu_T_T35 payloadSize" )
	ASCII(.ascii	" < 4!!\012\000" )
	.space	1
.LC180:
	ASCII(.ascii	"delta_idx_minus1\000" )
	.space	3
.LC181:
	ASCII(.ascii	"delta_idx(%d) > idx(%d).\012\000" )
	.space	2
.LC182:
	ASCII(.ascii	"rIdx(%d) > (idx-1)(%d) or < 0).\012\000" )
	.space	3
.LC183:
	ASCII(.ascii	"abs_delta_rps_minus1\000" )
	.space	3
.LC184:
	ASCII(.ascii	"pTempRPset->num_of_pics(%d) out of range(0,15).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC185:
	ASCII(.ascii	"num_of_pics out of range(0,15).\012\000" )
	.space	3
.LC186:
	ASCII(.ascii	"num_negative_pics\000" )
	.space	2
.LC187:
	ASCII(.ascii	"pTempRPset->num_negative_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC188:
	ASCII(.ascii	"num_positive_pics\000" )
	.space	2
.LC189:
	ASCII(.ascii	"pTempRPset->num_positive_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC190:
	ASCII(.ascii	"pShortTermRpset->num_of_pics(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC191:
	ASCII(.ascii	"delta_poc_s0_minus1\000" )
.LC192:
	ASCII(.ascii	"delta_poc_s0_minus1(%d) out of range.\012\000" )
	.space	1
.LC193:
	ASCII(.ascii	"delta_poc_s1_minus1\000" )
.LC194:
	ASCII(.ascii	"elemental_duration_in_tc_minus1\000" )
.LC195:
	ASCII(.ascii	"cpb_cnt_minus1\000" )
	.space	1
.LC196:
	ASCII(.ascii	"cpb_cnt_minus1(%d) out of range(0,31).\012\000" )
.LC197:
	ASCII(.ascii	"bit_rate_value_minus1\000" )
	.space	2
.LC198:
	ASCII(.ascii	"cpb_size_value_minus1\000" )
	.space	2
.LC199:
	ASCII(.ascii	"cpb_size_du_value_minus1\000" )
	.space	3
.LC200:
	ASCII(.ascii	"bit_rate_du_value_minus1\000" )
	.space	3
.LC201:
	ASCII(.ascii	"%s: vps_max_layers_minus1 %d out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC202:
	ASCII(.ascii	"num_add_layer_sets\000" )
	.space	1
.LC203:
	ASCII(.ascii	"%s %d: num_add_layer_sets %d >= HEVC_MAX_VPS_OP_SET" )
	ASCII(.ascii	"S_PLUS1 %d\012\000" )
	.space	1
.LC204:
	ASCII(.ascii	"vps_num_profile_tier_level_minus1\000" )
	.space	2
.LC205:
	ASCII(.ascii	"num_add_olss\000" )
	.space	3
.LC206:
	ASCII(.ascii	"%s %d: num_output_layer_sets %d >= HEVC_MAX_VPS_OP_" )
	ASCII(.ascii	"SETS_PLUS1 %d, num_add_olss %d, num_layer_sets %d\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC207:
	ASCII(.ascii	"vps_num_rep_formats_minus1 > 255.\012\000" )
	.space	1
.LC208:
	ASCII(.ascii	"conf_win_vps_left_offset\000" )
	.space	3
.LC209:
	ASCII(.ascii	"conf_win_vps_right_offset\000" )
	.space	2
.LC210:
	ASCII(.ascii	"conf_win_vps_top_offset\000" )
.LC211:
	ASCII(.ascii	"conf_win_vps_bottom_offset\000" )
	.space	1
.LC212:
	ASCII(.ascii	"bit_depth_vps_luma_minus8(%d) or bit_depth_vps_chro" )
	ASCII(.ascii	"ma_minus8(%d) out of range [0,8]\012\000" )
	.space	3
.LC213:
	ASCII(.ascii	"direct_dep_type_len_minus2\000" )
	.space	1
.LC214:
	ASCII(.ascii	"max_vps_num_reorder_pics\000" )
	.space	3
.LC215:
	ASCII(.ascii	"max_vps_latency_increase_plus1\000" )
	.space	1
.LC216:
	ASCII(.ascii	"max_vps_dec_pic_buffering_minus1\000" )
	.space	3
.LC217:
	ASCII(.ascii	"vps_non_vui_extension_length\000" )
	.space	3
.LC218:
	ASCII(.ascii	"min_spatial_segment_offset_plus1\000" )
	.space	3
.LC219:
	ASCII(.ascii	"min_horizontal_ctu_offset_plus1\000" )
.LC220:
	ASCII(.ascii	"vps_num_add_hrd_params\000" )
	.space	1
.LC221:
	ASCII(.ascii	"vps_num_hrd_params %d out of range [0,%d]\012\000" )
	.space	1
.LC222:
	ASCII(.ascii	"num_sub_layer_hrd_minus1\000" )
	.space	3
.LC223:
	ASCII(.ascii	"hrd %d num_sub_layer_hrd_minus1 %d out of range [0," )
	ASCII(.ascii	"%d]\012\000" )
.LC224:
	ASCII(.ascii	"num_signalled_partitioning_schemes\000" )
	.space	1
.LC225:
	ASCII(.ascii	"OPL %d num_signalled_partitioning_schemes %d out of" )
	ASCII(.ascii	" range [0,%d]\012\000" )
	.space	2
.LC226:
	ASCII(.ascii	"num_partitions_in_scheme_minus1\000" )
.LC227:
	ASCII(.ascii	"num_bsp_schedules_minus1\000" )
	.space	3
.LC228:
	ASCII(.ascii	"OPL %d Partition %d Tid %dnum_bsp_schedules_minus1 " )
	ASCII(.ascii	"%d out of range [0,31]\012\000" )
	.space	1
.LC229:
	ASCII(.ascii	"bsp_sched_idx\000" )
	.space	2
.LC230:
	ASCII(.ascii	"vps_num_rep_formats_minus1\000" )
	.space	1
.LC231:
	ASCII(.ascii	"HEVCC_ParseBspPartitonParameters failed.\012\000" )
	.space	2
.LC232:
	ASCII(.ascii	"vps_base_layer_available_flag(%d) not equal 0x1.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC233:
	ASCII(.ascii	"vps_max_layers_minus1 %d out of range[0,63].\012\000" )
	.space	2
.LC234:
	ASCII(.ascii	"vps_max_sub_layers_minus1=%d\012\000" )
	.space	2
.LC235:
	ASCII(.ascii	"vps_reserved_0xffff_16bits not equal 0xffff.\012\000" )
	.space	2
.LC236:
	ASCII(.ascii	"VPS HEVC_DecPTL error.\012\000" )
.LC237:
	ASCII(.ascii	"vps_max_dec_pic_buffering_minus1[i]\000" )
.LC238:
	ASCII(.ascii	"vps_num_reorder_pics[i]\000" )
.LC239:
	ASCII(.ascii	"vps_max_latency_increase_plus1[i]\000" )
	.space	2
.LC240:
	ASCII(.ascii	"vps_max_layer_id out of range[0,%d].\012\000" )
	.space	2
.LC241:
	ASCII(.ascii	"This is MV_HEVC!\012\000" )
	.space	2
.LC242:
	ASCII(.ascii	"vps_num_layer_sets_minus1\000" )
	.space	2
.LC243:
	ASCII(.ascii	"vps_num_layer_sets_minus1(%d) out of range(0,%d).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC244:
	ASCII(.ascii	"vps_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC245:
	ASCII(.ascii	"vps_num_hrd_parameters\000" )
	.space	1
.LC246:
	ASCII(.ascii	"vps_num_hrd_parameters(%d) out of range[0,%d].\012\000" )
.LC247:
	ASCII(.ascii	"hrd_layer_set_idx\000" )
	.space	2
.LC248:
	ASCII(.ascii	"VPS HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC249:
	ASCII(.ascii	"HEVC VPSExtension error.\012\000" )
	.space	2
.LC250:
	ASCII(.ascii	"pVPS->vps_video_parameter_set_id out of range(0,15)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC251:
	ASCII(.ascii	"VPS[%d] decode error0.\012\000" )
.LC252:
	ASCII(.ascii	"VPS[%d] decode error1.\012\000" )
.LC253:
	ASCII(.ascii	"chroma_sample_loc_type_top_field\000" )
	.space	3
.LC254:
	ASCII(.ascii	"chroma_sample_loc_type_bottom_field\000" )
.LC255:
	ASCII(.ascii	"def_disp_win_left_offset\000" )
	.space	3
.LC256:
	ASCII(.ascii	"VUI pSps->chroma_format_idc out of range(0,3).\012\000" )
.LC257:
	ASCII(.ascii	"def_disp_win_right_offset\000" )
	.space	2
.LC258:
	ASCII(.ascii	"def_disp_win_top_offset\000" )
.LC259:
	ASCII(.ascii	"def_disp_win_bottom_offset\000" )
	.space	1
.LC260:
	ASCII(.ascii	"vui_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC261:
	ASCII(.ascii	"VUI HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC262:
	ASCII(.ascii	"min_spatial_segmentation_idc\000" )
	.space	3
.LC263:
	ASCII(.ascii	"VUI min_spatial_segmentation_idc out of range(0,409" )
	ASCII(.ascii	"5).\012\000" )
.LC264:
	ASCII(.ascii	"max_bytes_per_pic_denom\000" )
.LC265:
	ASCII(.ascii	"max_bits_per_min_cu_denom\000" )
	.space	2
.LC266:
	ASCII(.ascii	"log2_max_mv_length_horizontal\000" )
	.space	2
.LC267:
	ASCII(.ascii	"log2_max_mv_length_vertical\000" )
.LC268:
	ASCII(.ascii	"sop_seq_parameter_set_id\000" )
	.space	3
.LC269:
	ASCII(.ascii	"num_entries_in_sop_minus1\000" )
	.space	2
.LC270:
	ASCII(.ascii	"num_entries_in_sop_minus1 out of range(0,1024)\012\000" )
.LC271:
	ASCII(.ascii	"sop_short_term_rps_idx\000" )
	.space	1
.LC272:
	ASCII(.ascii	"sop_poc_delta\000" )
	.space	2
.LC273:
	ASCII(.ascii	"recovery_poc_cnt\000" )
	.space	3
.LC274:
	ASCII(.ascii	"colour_remap_id\000" )
.LC275:
	ASCII(.ascii	"colour_remap_coeffs\000" )
.LC276:
	ASCII(.ascii	"ERROR: post_lut_num_val_minus1 %d out of range[0, 3" )
	ASCII(.ascii	"2]\012\000" )
	.space	1
.LC277:
	ASCII(.ascii	"reserved_payload_extension_data\000" )
.LC278:
	ASCII(.ascii	"line:%d Cosume TotalPos(%d > %d)!!!\012\000" )
	.space	3
.LC279:
	ASCII(.ascii	"HEVC_SeiMessage HEVC_Sei_Payload error.\012\000" )
	.space	3
.LC280:
	ASCII(.ascii	"SEI pSEISPS = NULL.\012\000" )
	.space	3
.LC281:
	ASCII(.ascii	"SEI HEVC_SeiMessage error.\012\000" )
.LC282:
	ASCII(.ascii	"SEI BsIsByteAligned error.\012\000" )
.LC283:
	ASCII(.ascii	"SEI rbsp_trailing_bits(%d) not equal 0x80.\012\000" )
.LC284:
	ASCII(.ascii	"nesting_num_ops_minus1\000" )
	.space	1
.LC285:
	ASCII(.ascii	"nesting_num_ops_minus1 out of range(0,%d)\012\000" )
	.space	1
.LC286:
	ASCII(.ascii	"nesting_op_idx\000" )
	.space	1
.LC287:
	ASCII(.ascii	"nesting_num_layers_minus1\000" )
	.space	2
.LC288:
	ASCII(.ascii	"nesting_num_layers_minus1 out of range(0,63)\012\000" )
	.space	2
.LC289:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta\000" )
	.space	2
.LC290:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta out of range(0,ma" )
	ASCII(.ascii	"trixId).\012\000" )
	.space	3
.LC291:
	ASCII(.ascii	"HEVC_DecScalingListData pMatrixAddress NULL.\012\000" )
	.space	2
.LC292:
	ASCII(.ascii	"scaling_list_dc_coef_minus8\000" )
.LC293:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-7,247).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC294:
	ASCII(.ascii	"scaling_list_delta_coef\000" )
.LC295:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-128,127)." )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC296:
	ASCII(.ascii	"sps_rep_format_idx %d > HEVC_MAX_NUM_LAYERS %d\012\000" )
.LC297:
	ASCII(.ascii	"HEVC_DeriveSPSRepFormat failed.\012\000" )
	.space	3
.LC298:
	ASCII(.ascii	"pSPS->chroma_format_idc out of range(0,3).\012\000" )
.LC299:
	ASCII(.ascii	"pSPS->chroma_format_idc not equal(%d) 1.\012\000" )
	.space	2
.LC300:
	ASCII(.ascii	"pic_width_in_luma_samples\000" )
	.space	2
.LC301:
	ASCII(.ascii	"pic_width_in_luma_samples out of range(0,8192).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC302:
	ASCII(.ascii	"pic_height_in_luma_samples\000" )
	.space	1
.LC303:
	ASCII(.ascii	"pic_height_in_luma_samples out of range(0,4096).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC304:
	ASCII(.ascii	"ERROR Unkown level: %d\012\000" )
.LC305:
	ASCII(.ascii	"conf_win_left_offset\000" )
	.space	3
.LC306:
	ASCII(.ascii	"conf_win_right_offset\000" )
	.space	2
.LC307:
	ASCII(.ascii	"conf_win_left_offset+conf_win_right_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC308:
	ASCII(.ascii	"conf_win_top_offset\000" )
.LC309:
	ASCII(.ascii	"conf_win_bottom_offset\000" )
	.space	1
.LC310:
	ASCII(.ascii	"conf_win_top_offset+conf_win_bottom_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC311:
	ASCII(.ascii	"bit_depth_luma_minus8\000" )
	.space	2
.LC312:
	ASCII(.ascii	"bit_depth_luma(%d) out of range(8,10).\012\000" )
.LC313:
	ASCII(.ascii	"bit_depth_chroma_minus8\000" )
.LC314:
	ASCII(.ascii	"bit_depth_chroma(%d) out of range[8,14].\012\000" )
	.space	2
.LC315:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	2
.LC316:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4 out of range[0,12" )
	ASCII(.ascii	"].\012\000" )
	.space	1
.LC317:
	ASCII(.ascii	"sps_max_dec_pic_buffering_minus1\000" )
	.space	3
.LC318:
	ASCII(.ascii	"sps_num_reorder_pics\000" )
	.space	3
.LC319:
	ASCII(.ascii	"sps_max_latency_increase_plus1\000" )
	.space	1
.LC320:
	ASCII(.ascii	"log2_min_coding_block_size_minus3\000" )
	.space	2
.LC321:
	ASCII(.ascii	"log2_min_luma_coding_block_size_minus3 out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC322:
	ASCII(.ascii	"log2_diff_max_min_coding_block_size\000" )
.LC323:
	ASCII(.ascii	"log2_diff_max_min_luma_coding_block_size out of ran" )
	ASCII(.ascii	"ge(0,3).\012\000" )
	.space	3
.LC324:
	ASCII(.ascii	"log2_ctb_sizeY out of range(4,6).\012\000" )
	.space	1
.LC325:
	ASCII(.ascii	"log2_min_transform_block_size_minus2\000" )
	.space	3
.LC326:
	ASCII(.ascii	"log2_min_transform_block_size_minus2 out of range(0" )
	ASCII(.ascii	",3).\012\000" )
	.space	3
.LC327:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size\000" )
	.space	1
.LC328:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC329:
	ASCII(.ascii	"quadtree_tu_log2_min_size not less than log2_min_cb" )
	ASCII(.ascii	"_sizeY.\012\000" )
.LC330:
	ASCII(.ascii	"quadtree_tu_log2_max_size greater than Min( CtbLog2" )
	ASCII(.ascii	"SizeY, 5 ).\012\000" )
.LC331:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter\000" )
.LC332:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC333:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra\000" )
.LC334:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC335:
	ASCII(.ascii	"SPS HEVC_DecScalingListData error.\012\000" )
.LC336:
	ASCII(.ascii	"SPS sao is off and pic height(%d) is too small.(Log" )
	ASCII(.ascii	"ic Unsupported).\012\000" )
	.space	3
.LC337:
	ASCII(.ascii	"log2_min_pcm_luma_coding_block_size_minus3\000" )
	.space	1
.LC338:
	ASCII(.ascii	"log2_min_pcm_coding_block_size_minus3(%d) out of ra" )
	ASCII(.ascii	"nge[0,2].\012\000" )
	.space	2
.LC339:
	ASCII(.ascii	"log2_diff_max_min_pcm_luma_coding_block_size\000" )
	.space	3
.LC340:
	ASCII(.ascii	"log2_diff_max_min_pcm_coding_block_size(%d) out of " )
	ASCII(.ascii	"range[0,2].\012\000" )
.LC341:
	ASCII(.ascii	"pcm_log2_max_size greater than Min( CtbLog2SizeY, 5" )
	ASCII(.ascii	" ).\012\000" )
.LC342:
	ASCII(.ascii	"num_short_term_ref_pic_sets\000" )
.LC343:
	ASCII(.ascii	"num_short_term_ref_pic_sets out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC344:
	ASCII(.ascii	"SPS HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	1
.LC345:
	ASCII(.ascii	"num_long_term_ref_pic_sps\000" )
	.space	2
.LC346:
	ASCII(.ascii	"num_long_term_ref_pic_sps out of range[0,32].\012\000" )
	.space	1
.LC347:
	ASCII(.ascii	"SPS HEVC_DecVuiParam error.\012\000" )
	.space	3
.LC348:
	ASCII(.ascii	"chroma_format_idc\000" )
	.space	2
.LC349:
	ASCII(.ascii	"sps_video_parameter_set_id out of range(0,%d).\012\000" )
.LC350:
	ASCII(.ascii	"sps_max_sub_layers_minus1 out of range(0,%d).\012\000" )
	.space	1
.LC351:
	ASCII(.ascii	"SPS HEVC_DecPTL error.\012\000" )
.LC352:
	ASCII(.ascii	"sps_seq_parameter_set_id\000" )
	.space	3
.LC353:
	ASCII(.ascii	"sps_seq_parameter_set_id out of range(0,%d).\012\000" )
	.space	2
.LC354:
	ASCII(.ascii	"SPS[%d] decode error0.\012\000" )
.LC355:
	ASCII(.ascii	"SPS[%d] decode error.\012\000" )
	.space	1
.LC356:
	ASCII(.ascii	"pps_seq_parameter_set_id\000" )
	.space	3
.LC357:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range[0,15].\012\000" )
	.space	2
.LC358:
	ASCII(.ascii	"SPS(%d) haven't decode.\012\000" )
	.space	3
.LC359:
	ASCII(.ascii	"num_ref_idx_l0_default_active_minus1\000" )
	.space	3
.LC360:
	ASCII(.ascii	"num_ref_idx_l0_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC361:
	ASCII(.ascii	"num_ref_idx_l1_default_active_minus1\000" )
	.space	3
.LC362:
	ASCII(.ascii	"num_ref_idx_l1_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC363:
	ASCII(.ascii	"init_qp_minus26\000" )
.LC364:
	ASCII(.ascii	"pic_init_qp(%d) out of range[-%d,51].\012\000" )
	.space	1
.LC365:
	ASCII(.ascii	"diff_cu_qp_delta_depth\000" )
	.space	1
.LC366:
	ASCII(.ascii	"diff_cu_qp_delta_depth out of range[0,3].\012\000" )
	.space	1
.LC367:
	ASCII(.ascii	"pps_cb_qp_offset\000" )
	.space	3
.LC368:
	ASCII(.ascii	"pic_cb_qp_offset out of range[-12,12].\012\000" )
.LC369:
	ASCII(.ascii	"pps_cr_qp_offset\000" )
	.space	3
.LC370:
	ASCII(.ascii	"pic_cr_qp_offset out of range[-12,12].\012\000" )
.LC371:
	ASCII(.ascii	"num_tile_columns_minus1\000" )
.LC372:
	ASCII(.ascii	"num_tile_columns(%d) out of range(0,%d).\012\000" )
	.space	2
.LC373:
	ASCII(.ascii	"num_tile_rows_minus1\000" )
	.space	3
.LC374:
	ASCII(.ascii	"num_tile_rows out(%d) of range(0,%d).\012\000" )
	.space	1
.LC375:
	ASCII(.ascii	"Logic limit(%d), num_tile_columns(%d) exceed.\012\000" )
	.space	1
.LC376:
	ASCII(.ascii	"Logic limit(%d), num_tile_rows(%d) exceed.\012\000" )
.LC377:
	ASCII(.ascii	"column_width_minus1\000" )
.LC378:
	ASCII(.ascii	"column_width[%d](%d) out of range (0 %d)\012\000" )
	.space	2
.LC379:
	ASCII(.ascii	"row_height_minus1\000" )
	.space	2
.LC380:
	ASCII(.ascii	"row_height[%d](%d) out of range (0 %d)\012\000" )
.LC381:
	ASCII(.ascii	"column_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	2
.LC382:
	ASCII(.ascii	"row_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	1
.LC383:
	ASCII(.ascii	"PPS tile width(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC384:
	ASCII(.ascii	"PPS tile height(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
.LC385:
	ASCII(.ascii	"pps_beta_offset_div2\000" )
	.space	3
.LC386:
	ASCII(.ascii	"pps_beta_offset_div2(%d) out of range(-6,6).\012\000" )
	.space	2
.LC387:
	ASCII(.ascii	"pps_tc_offset_div2\000" )
	.space	1
.LC388:
	ASCII(.ascii	"pps_tc_offset_div2(%d) out of range(-6,6).\012\000" )
.LC389:
	ASCII(.ascii	"PPS HEVC_DecScalingListData error.\012\000" )
.LC390:
	ASCII(.ascii	"log2_parallel_merge_level_minus2\000" )
	.space	3
.LC391:
	ASCII(.ascii	"log2_parallel_merge_level(%d) out of range(2,log2_c" )
	ASCII(.ascii	"tb_sizeY).\012\000" )
	.space	1
.LC392:
	ASCII(.ascii	"log2_max_transform_skip_block_size_minus2\000" )
	.space	2
.LC393:
	ASCII(.ascii	"log2_sao_offset_scale_luma\000" )
	.space	1
.LC394:
	ASCII(.ascii	"log2_sao_offset_scale_chroma\000" )
	.space	3
.LC395:
	ASCII(.ascii	"diff_cu_chroma_qp_offset_depth\000" )
	.space	1
.LC396:
	ASCII(.ascii	"chroma_qp_offset_list_len_minus1\000" )
	.space	3
.LC397:
	ASCII(.ascii	"chroma_qp_offset_list_len_minus1 %d > 5\012\000" )
	.space	3
.LC398:
	ASCII(.ascii	"cb_qp_offset_list\000" )
	.space	2
.LC399:
	ASCII(.ascii	"cr_qp_offset_list\000" )
	.space	2
.LC400:
	ASCII(.ascii	"pps_scaling_list_ref_layer_id %d > HEVC_MAX_NUM_LAY" )
	ASCII(.ascii	"ERS %d\012\000" )
	.space	1
.LC401:
	ASCII(.ascii	"num_ref_loc_offsets\000" )
.LC402:
	ASCII(.ascii	"num_ref_loc_offsets %d > HEVC_EXT_MAX_REF_LOC_OFFSE" )
	ASCII(.ascii	"T %d\012\000" )
	.space	3
.LC403:
	ASCII(.ascii	"ref_loc_offset_layer_id %d > HEVC_EXT_MAX_REF_LOC_O" )
	ASCII(.ascii	"FFSET %d\012\000" )
	.space	3
.LC404:
	ASCII(.ascii	"scaled_ref_layer_left_offset\000" )
	.space	3
.LC405:
	ASCII(.ascii	"scaled_ref_layer_top_offset\000" )
.LC406:
	ASCII(.ascii	"scaled_ref_layer_right_offset\000" )
	.space	2
.LC407:
	ASCII(.ascii	"scaled_ref_layer_bottom_offset\000" )
	.space	1
.LC408:
	ASCII(.ascii	"ref_region_left_offset\000" )
	.space	1
.LC409:
	ASCII(.ascii	"ref_region_top_offset\000" )
	.space	2
.LC410:
	ASCII(.ascii	"ref_region_right_offset\000" )
.LC411:
	ASCII(.ascii	"ref_region_bottom_offset\000" )
	.space	3
.LC412:
	ASCII(.ascii	"phase_hor_luma\000" )
	.space	1
.LC413:
	ASCII(.ascii	"phase_ver_luma\000" )
	.space	1
.LC414:
	ASCII(.ascii	"phase_hor_chroma_plus8\000" )
	.space	1
.LC415:
	ASCII(.ascii	"phase_ver_chroma_plus8\000" )
	.space	1
.LC416:
	ASCII(.ascii	"HEVC_ParsePPSExtension failed.\012\000" )
.LC417:
	ASCII(.ascii	"pps_pic_parameter_set_id\000" )
	.space	3
.LC418:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range(0,%d).\012\000" )
	.space	2
.LC419:
	ASCII(.ascii	"PPS[%d] decode error.\012\000" )
	.space	1
.LC420:
	ASCII(.ascii	"luma_log2_weight_denom\000" )
	.space	1
.LC421:
	ASCII(.ascii	"luma_log2_weight_denom out of range(0,7).\012\000" )
	.space	1
.LC422:
	ASCII(.ascii	"delta_chroma_log2_weight_denom\000" )
	.space	1
.LC423:
	ASCII(.ascii	"delta_chroma_log2_weight_denom out of range(-7,7).\012" )
	ASCII(.ascii	"\000" )
.LC424:
	ASCII(.ascii	"chroma_log2_weight_denom out of range(0,7).\012\000" )
	.space	3
.LC425:
	ASCII(.ascii	"delta_luma_weight_l0\000" )
	.space	3
.LC426:
	ASCII(.ascii	"delta_luma_weight_l0(%d) out of range(-128,127).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC427:
	ASCII(.ascii	"luma_offset_l0\000" )
	.space	1
.LC428:
	ASCII(.ascii	"luma_offset_l0(%d) out of range(-128,127).\012\000" )
.LC429:
	ASCII(.ascii	"delta_chroma_weight_l0\000" )
	.space	1
.LC430:
	ASCII(.ascii	"delta_chroma_weight_l0 out of range(-128,127).\012\000" )
.LC431:
	ASCII(.ascii	"delta_chroma_offset_l0\000" )
	.space	1
.LC432:
	ASCII(.ascii	"delta_chroma_offset_l0 out of range(-512,511).\012\000" )
.LC433:
	ASCII(.ascii	"delta_luma_weight_l1\000" )
	.space	3
.LC434:
	ASCII(.ascii	"delta_luma_weight_l1 out of range(-128,127).\012\000" )
	.space	2
.LC435:
	ASCII(.ascii	"luma_offset_l1\000" )
	.space	1
.LC436:
	ASCII(.ascii	"luma_offset_l1 out of range(-128,127).\012\000" )
.LC437:
	ASCII(.ascii	"delta_chroma_weight_l1\000" )
	.space	1
.LC438:
	ASCII(.ascii	"delta_chroma_weight_l1 out of range(-128,127).\012\000" )
.LC439:
	ASCII(.ascii	"delta_chroma_offset_l1\000" )
	.space	1
.LC440:
	ASCII(.ascii	"delta_chroma_offset_l1 out of range(-512,511).\012\000" )
.LC441:
	ASCII(.ascii	"slice_pic_parameter_set_id\000" )
	.space	1
.LC442:
	ASCII(.ascii	"%s: pic_parameter_set_id(%d) out of range(0 %d)!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC443:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\012\000" )
.LC444:
	ASCII(.ascii	"max_cu_width(%d)/max_cu_height(%d) = 0\012\000" )
.LC445:
	ASCII(.ascii	"slice_segment_address(%d) out of range(0,%d).\012\000" )
	.space	1
.LC446:
	ASCII(.ascii	"slice_type\000" )
	.space	1
.LC447:
	ASCII(.ascii	"slice_type(%d) out of range(0,2].\012\000" )
	.space	1
.LC448:
	ASCII(.ascii	"HEVC_ClearDPB,LastDisplayPoc:%d poc:%d \012\000" )
	.space	3
.LC449:
	ASCII(.ascii	"SH HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	2
.LC450:
	ASCII(.ascii	"short_term_ref_pic_set_idx(%d) out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
.LC451:
	ASCII(.ascii	"num_long_term_sps\000" )
	.space	2
.LC452:
	ASCII(.ascii	"num_long_term_sps(%d) out of range[0,%d].\012\000" )
	.space	1
.LC453:
	ASCII(.ascii	"num_long_term_pics\000" )
	.space	1
.LC454:
	ASCII(.ascii	"SH ERROR: (num_negative_pics(%d) + num_positive_pic" )
	ASCII(.ascii	"s(%d) + num_of_longterm_pics(%d)) > %d\012\000" )
	.space	1
.LC455:
	ASCII(.ascii	"lt_idx_sps[%d] = %d, but out of range[0,%d].\012\000" )
	.space	2
.LC456:
	ASCII(.ascii	"delta_poc_msb_cycle_lt\000" )
	.space	1
.LC457:
	ASCII(.ascii	"ERROR: pRPS->num_of_pics(%d) > %d.\012\000" )
.LC458:
	ASCII(.ascii	"Error0: Parse num_active_ref_layer_pics %d > HEVC_M" )
	ASCII(.ascii	"AX_NUM_LAYERS %d, not support\012\000" )
	.space	2
.LC459:
	ASCII(.ascii	"Error1: Parse num_active_ref_layer_pics %d > HEVC_M" )
	ASCII(.ascii	"AX_NUM_LAYERS %d, not support\012\000" )
	.space	2
.LC460:
	ASCII(.ascii	"Parse inter_layer_pred_layer_idc[%d] %d > HEVC_MAX_" )
	ASCII(.ascii	"NUM_LAYERS %d, not support\000" )
	.space	2
.LC461:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC462:
	ASCII(.ascii	"num_ref_idx_l0_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC463:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC464:
	ASCII(.ascii	"num_ref_idx_l1_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC465:
	ASCII(.ascii	"pRPS is null.\012\000" )
	.space	1
.LC466:
	ASCII(.ascii	"pRPS->num_of_pics out(%d) of range(0,%d).\012\000" )
	.space	1
.LC467:
	ASCII(.ascii	"SH HEVC_DecRefPicListsModification error.\012\000" )
	.space	1
.LC468:
	ASCII(.ascii	"collocated_ref_idx\000" )
	.space	1
.LC469:
	ASCII(.ascii	"collocated_from_l0_flag=%d, collocated_ref_idx(%d) " )
	ASCII(.ascii	"out of range(0,%d).\012\000" )
.LC470:
	ASCII(.ascii	"SH HEVC_DecPredWeightTable error.\012\000" )
	.space	1
.LC471:
	ASCII(.ascii	"five_minus_max_num_merge_cand\000" )
	.space	2
.LC472:
	ASCII(.ascii	"SH max_num_merge_cand(%d) out of range(1,5).\012\000" )
	.space	2
.LC473:
	ASCII(.ascii	"slice_qp_delta\000" )
	.space	1
.LC474:
	ASCII(.ascii	"SH slice_qp(%d) out of range [-%d,51].\012\000" )
.LC475:
	ASCII(.ascii	"slice_cb_qp_offset\000" )
	.space	1
.LC476:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC477:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out " )
	ASCII(.ascii	"of range[-12,12].\012\000" )
	.space	2
.LC478:
	ASCII(.ascii	"slice_cr_qp_offset\000" )
	.space	1
.LC479:
	ASCII(.ascii	"SH slice_cr_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC480:
	ASCII(.ascii	"SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) ou" )
	ASCII(.ascii	"t of range[-12,12].\012\000" )
.LC481:
	ASCII(.ascii	"slice_beta_offset_div2\000" )
	.space	1
.LC482:
	ASCII(.ascii	"SH slice_beta_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC483:
	ASCII(.ascii	"slice_tc_offset_div2\000" )
	.space	3
.LC484:
	ASCII(.ascii	"SH slice_tc_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC485:
	ASCII(.ascii	"num_entry_point_offsets\000" )
.LC486:
	ASCII(.ascii	"CurrSlice.num_entry_point_offsets(%d) out of range[" )
	ASCII(.ascii	"0,%d].\012\000" )
	.space	1
.LC487:
	ASCII(.ascii	"offset_len_minus1\000" )
	.space	2
.LC488:
	ASCII(.ascii	"CurrSlice.offset_len(%d) out of range[1,32].\012\000" )
	.space	2
.LC489:
	ASCII(.ascii	"slice_segment_header_extension_length\000" )
	.space	2
.LC490:
	ASCII(.ascii	"slice_segment_header_extension_length(%d) out of ra" )
	ASCII(.ascii	"nge [0,256]\012\000" )
.LC491:
	ASCII(.ascii	"bitsLeft(%d) < slice_segment_header_extension_lengt" )
	ASCII(.ascii	"h(%d)\012\000" )
	.space	2
.LC492:
	ASCII(.ascii	"HEVC_ParseSliceExtension failed\012\000" )
	.space	3
.LC493:
	ASCII(.ascii	"%s layer num %d invalid!\012\000" )
	.space	2
.LC494:
	ASCII(.ascii	"%s layer %d image size abnormal(%dx%d)\012\000" )
.LC495:
	ASCII(.ascii	"%s arrange mem failed.\012\000" )
.LC496:
	ASCII(.ascii	"Init dec para\012\000" )
	.space	1
.LC497:
	ASCII(.ascii	"Is SHVC: layer%d %dx%d, layer%d %dx%d.\012\000" )
.LC498:
	ASCII(.ascii	"Layer %d: %d x %d\012\000" )
	.space	1
.LC499:
	ASCII(.ascii	"HEVC_InitDPB error, return %d\012\000" )
	.space	1
.LC500:
	ASCII(.ascii	"HEVC_AllocFrameStore error\012\000" )
.LC501:
	ASCII(.ascii	"%s: HEVC_OutputFrame failed!\012\000" )
	.space	2
.LC502:
	ASCII(.ascii	"%s output current picture failed\012\000" )
	.space	2
.LC503:
	ASCII(.ascii	"HEVC.c line %d: frame para err(ret=%d), recycle ima" )
	ASCII(.ascii	"ge self\012\000" )
.LC504:
	ASCII(.ascii	"%s: BlockFsPoc:%d, LastPoc:%d!\012\000" )
.LC505:
	ASCII(.ascii	"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\012\000" )
.LC506:
	ASCII(.ascii	"%s: poc:%d, CurPos: %d !\012\000" )
	.space	2
.LC507:
	ASCII(.ascii	"%s call HEVC_GetUnRefPicWithMinPoc failed\012\000" )
	.space	1
.LC508:
	ASCII(.ascii	"%s call HEVC_OutputOneFrmFromDPB failed\012\000" )
	.space	3
.LC509:
	ASCII(.ascii	"%s: HEVC_OutputFrmToVO err!\012\000" )
	.space	3
.LC510:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC511:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC512:
	ASCII(.ascii	"nal_release_err\012\000" )
	.space	3
.LC513:
	ASCII(.ascii	"%s: flush dpb failed, return %d\012\000" )
	.space	3
.LC514:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), need to incr" )
	ASCII(.ascii	"ease DPB size.\012\000" )
	.space	1
.LC515:
	ASCII(.ascii	"%s call HEVC_IncreaseDPBSize failed\012\000" )
	.space	3
.LC516:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), output minpo" )
	ASCII(.ascii	"c frame.\012\000" )
	.space	3
.LC517:
	ASCII(.ascii	"%s with invalid pos(%d)\012\000" )
	.space	3
.LC518:
	ASCII(.ascii	"%s get APC error, ret %d\012\000" )
	.space	2
.LC519:
	ASCII(.ascii	"%s %d: InsertFrmInDPB failed, return %d\012\000" )
	.space	3
.LC520:
	ASCII(.ascii	"%s call HEVC_CheckFrameStore failed!\012\000" )
	.space	2
.LC521:
	ASCII(.ascii	"%s call HEVC_RemoveUnUsedFrameStore Failed.\012\000" )
	.space	3
.LC522:
	ASCII(.ascii	"%s call HEVC_InsertFrmInDPB Failed.\012\000" )
	.space	3
.LC523:
	ASCII(.ascii	"%s call HEVC_FirstFrameFastOut Failed\012\000" )
	.space	1
.LC524:
	ASCII(.ascii	"DPB.used_size may bigger than DPB.size\012\000" )
.LC525:
	ASCII(.ascii	"HEVC_InsertFrmInDPB Failed, ret = %d\012\000" )
	.space	2
.LC526:
	ASCII(.ascii	"%s call HEVC_OutputFrmFromDPB failed\012\000" )
	.space	2
.LC527:
	ASCII(.ascii	"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_" )
	ASCII(.ascii	"NORMAL\012\000" )
	.space	1
.LC528:
	ASCII(.ascii	"%s, REPORT_IFRAME_ERR\012\000" )
	.space	1
.LC529:
	ASCII(.ascii	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\012\000" )
	.space	1
.LC530:
	ASCII(.ascii	"%s call HEVC_IModeProcess Failed\012\000" )
	.space	2
.LC531:
	ASCII(.ascii	"HEVC_StorePicInDpb return(%d) from L%d\012\000" )
.LC532:
	ASCII(.ascii	"%s call HEVC_SimpleDPBProcess Failed\012\000" )
	.space	2
.LC533:
	ASCII(.ascii	"%s call HEVC_DecOrderProcess Failed\012\000" )
	.space	3
.LC534:
	ASCII(.ascii	"%s call HEVC_DispOrderProcess Failed\012\000" )
	.space	2
.LC535:
	ASCII(.ascii	"%s return HEVC_DEC_ERR\012\000" )
.LC536:
	ASCII(.ascii	"No frame store for lost pic.\012\000" )
	.space	2
.LC537:
	ASCII(.ascii	"DPB ERROR: Can not get ref_fs!\012\000" )
.LC538:
	ASCII(.ascii	"DPB no suited fs for lost pic.\012\000" )
.LC539:
	ASCII(.ascii	"Take poc(%d) to creat lost poc(%d).\012\000" )
	.space	3
.LC540:
	ASCII(.ascii	"DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\012\000" )
	.space	1
.LC541:
	ASCII(.ascii	"ERROR: Can not new logic fs!\012\000" )
	.space	2
.LC542:
	ASCII(.ascii	"Lost pic insert in DPB Failed!\012\000" )
.LC543:
	ASCII(.ascii	"Ref frame(poc %d) lost.\012\000" )
	.space	3
.LC544:
	ASCII(.ascii	"s32OutErrThr = %d,drop poc %d because lost ref fram" )
	ASCII(.ascii	"e(pod %d)\012\000" )
	.space	2
.LC545:
	ASCII(.ascii	"DecVDM MaxBytesReceived exceed threshold!\012\000" )
	.space	1
.LC546:
	ASCII(.ascii	"DecVDM no slice and needn't start VDM\012\000" )
	.space	1
.LC547:
	ASCII(.ascii	"IPBDecMode Changed (%d -> %d)\012\000" )
	.space	1
.LC548:
	ASCII(.ascii	"Discard this B(poc=%d) before P, is_ref_idc=%d.\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC549:
	ASCII(.ascii	"VDM start, TotalPicNum=%d.\012\000" )
.LC550:
	ASCII(.ascii	"%s no correct slice in the pic\012\000" )
.LC551:
	ASCII(.ascii	"metadatasize is too large:%d at line:%d\012\000" )
	.space	3
.LC552:
	ASCII(.ascii	"%s:%d Metadata map failed\012\000" )
	.space	1
.LC553:
	ASCII(.ascii	"%s:%d Metadata unmap failed\012\000" )
	.space	3
.LC554:
	ASCII(.ascii	"*****[%s][%d],BL Codec can only dec BL stream!!****" )
	ASCII(.ascii	"*\012\000" )
	.space	2
.LC555:
	ASCII(.ascii	"*****[%s][%d],EL Codec can only dec EL stream in DV" )
	ASCII(.ascii	"_DUAL_VES_IMP stream!!*****\012\000" )
.LC556:
	ASCII(.ascii	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC557:
	ASCII(.ascii	"%s call HEVC_FlushOutputFrmFromDPB failed\012\000" )
	.space	1
.LC558:
	ASCII(.ascii	"%s call HEVC_EmptyFrmFromDPB failed\012\000" )
	.space	3
.LC559:
	ASCII(.ascii	"Meet CRA frame, force output remain frame, CurPoc %" )
	ASCII(.ascii	"d, LastPoc %d\012\000" )
	.space	2
.LC560:
	ASCII(.ascii	"Init pic err, exit\012\000" )
.LC561:
	ASCII(.ascii	"HEVC_WritePicMsg failed!\012\000" )
	.space	2
.LC562:
	ASCII(.ascii	"Start Reason: SliceParaNum= %d\012\000" )
.LC563:
	ASCII(.ascii	"Too many slice , err!\012\000" )
	.space	1
.LC564:
	ASCII(.ascii	"Cur pic not init yet, discard this slice!\012\000" )
	.space	1
.LC565:
	ASCII(.ascii	"Dec List error, ret=%d\012\000" )
.LC566:
	ASCII(.ascii	"Ref List is Wrong!\012\000" )
.LC567:
	ASCII(.ascii	"HEVC_WriteSliceMsg err.\012\000" )
	.space	3
.LC568:
	ASCII(.ascii	"VPS decode error.\012\000" )
	.space	1
.LC569:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC570:
	ASCII(.ascii	"PPS decode error.\012\000" )
	.space	1
.LC571:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC572:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d\012\000" )
.LC573:
	ASCII(.ascii	"HEVC_DecSliceSegmentHeader dec err\012\000" )
.LC574:
	ASCII(.ascii	"CurBitsLen = %d, MinBitsLen = %d\012\000" )
	.space	2
.LC575:
	ASCII(.ascii	"%s last frame fs unrelease, fix it!\012\000" )
	.space	3
.LC576:
	ASCII(.ascii	"CtbNumOneFrame=%d, SedEnd0=%d\012\000" )
	.space	1
.LC577:
	ASCII(.ascii	"OSAL_FP_alloc_virmem g_pGlbVar fail %d\012\000" )
.LC578:
	ASCII(.ascii	"%s: Get context addr failed!\012\000" )
	.space	2
.LC579:
	ASCII(.ascii	"%s FATAL: MemOffset %d > ContextMemSize %d.\012\000" )
	.space	3
.LC580:
	ASCII(.ascii	"%s: VCTRL_GetChanIDByCtx() return -1!\012\000" )
	.space	1
.LC581:
	ASCII(.ascii	"Fs leak, clear dpb fs not in vo queue.\012\000" )
.LC582:
	ASCII(.ascii	"No frame store available!\012\000" )
	.space	1
.LC583:
	ASCII(.ascii	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak" )
	ASCII(.ascii	", ClearAll!\012\000" )
.LC584:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pPacket!\012\000" )
	.space	1
.LC585:
	ASCII(.ascii	"HevcCtx not init!\012\000" )
	.space	1
.LC586:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC587:
	ASCII(.ascii	"nal_layer_id out %d of range[0,1].\012\000" )
.LC588:
	ASCII(.ascii	"Not need nal of layer %d in output order %d.\012\000" )
	.space	2
.LC589:
	ASCII(.ascii	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\012" )
	ASCII(.ascii	"\000" )
.LC590:
	ASCII(.ascii	"HEVC_InquireSliceProperty error.\012\000" )
	.space	2
.LC591:
	ASCII(.ascii	"HEVC_DecOneNal ERR\012\000" )
.LC592:
	ASCII(.ascii	"pHevcCtx->CurrPic.frame_store is null pointer\012\000" )
	.space	1
.LC593:
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
