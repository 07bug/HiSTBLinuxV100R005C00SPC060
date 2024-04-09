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
	.file	"vfmw_write_yuv.c"
	.text
	.align	2
	.global	YUV_DumpFrame_Cmp
	.type	YUV_DumpFrame_Cmp, %function
YUV_DumpFrame_Cmp:
	UNWIND(.fnstart)
	@ args = 44, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, .L2
	mov	r0, #32
	ldr	r1, .L2+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L3:
	.align	2
.L2:
	.word	.LANCHOR0
	.word	.LC0
	UNWIND(.fnend)
	.size	YUV_DumpFrame_Cmp, .-YUV_DumpFrame_Cmp
	.align	2
	.global	YUV_DumpFrame_Tile
	.type	YUV_DumpFrame_Tile, %function
YUV_DumpFrame_Tile:
	UNWIND(.fnstart)
	@ args = 32, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #100)
	sub	sp, sp, #100
	cmp	r0, #0
	mov	r7, r2
	mov	r5, r3
	str	r0, [fp, #-112]
	ldr	r2, [fp, #20]
	ldr	r3, [fp, #28]
	ldr	ip, [fp, #32]
	beq	.L4
	sub	r0, r2, #1
	cmp	r0, #16
	bhi	.L6
	mov	lr, #1
	movw	r4, #7683
	mov	r0, lr, asl r0
	and	r4, r4, r0
	cmp	r4, #0
	bne	.L7
	tst	r0, #65536
	bne	.L8
.L6:
	cmp	r2, #16
	add	r0, r5, #255
	bic	r0, r0, #255
	beq	.L60
	sub	r2, r2, #17
	cmp	r2, #1
	bls	.L61
	ldr	r2, [fp, #4]
	mov	r4, #0
	mov	lr, r4
	add	r2, r2, #31
	bic	r2, r2, #31
.L10:
	ldr	r8, [ip, #168]
	str	r7, [fp, #-72]
	cmp	r8, #10
	ldr	r7, [ip, #144]
	str	r1, [fp, #-80]
	muleq	r0, r2, r0
	movne	r6, #0
	ldr	r2, .L64
	movne	r0, r6
	str	r7, [fp, #-48]
	addeq	r0, r0, r0, lsl #1
	addeq	r0, r1, r0, asr #1
	mov	r1, r5
	str	r0, [fp, #-76]
	mlaeq	r6, r4, lr, r0
	ldr	lr, .L64+4
	cmp	r8, #0
	ldr	r4, [r2]
	sub	r0, fp, #80
	moveq	r8, #8
	ldr	lr, [lr]
	cmp	r8, r3
	str	r8, [fp, #-64]
	str	r6, [fp, #-68]
	ldrb	r8, [ip, #66]	@ zero_extendqisi2
	movge	r2, r3
	ldr	r6, [ip, #112]
	movlt	r2, #8
	sub	r3, fp, #96
	str	r2, [fp, #-60]
	eor	r8, r8, #2
	ldr	r2, [fp, #4]
	ubfx	ip, r8, #1, #1
	str	r4, [fp, #-96]
	str	lr, [fp, #-92]
	add	r4, r4, #9437184
	add	lr, lr, #9437184
	str	r4, [fp, #-88]
	str	lr, [fp, #-84]
	str	ip, [fp, #-56]
	str	r6, [fp, #-52]
	bl	IMAGE_ConvertTo2D
	ldr	r3, [fp, #-60]
	cmp	r3, #10
	beq	.L62
	ldr	r3, [fp, #4]
	ldr	r0, [fp, #-96]
	mul	r3, r5, r3
	str	r3, [fp, #-108]
.L19:
	ldr	r3, .L64+8
	ldr	r2, [fp, #-112]
	ldr	r1, [fp, #-108]
	str	r3, [fp, #-116]
	ldr	r3, [r3, #44]
	blx	r3
.L20:
	ldr	r3, [fp, #-60]
	cmp	r3, #10
	beq	.L63
	ldr	r2, [fp, #4]
	ldr	r9, [fp, #-88]
	movs	r10, r2, lsr #1
	ldreq	r4, .L64+12
	ldreq	ip, .L64+16
	beq	.L26
.L24:
	ldr	r4, .L64+12
	mov	r8, #0
	ldr	ip, .L64+16
	mov	r6, r5, lsr #1
	mov	r7, r8
	mov	r2, r5, asl #1
	str	r2, [fp, #-104]
.L34:
	cmp	r3, #10
	beq	.L27
	cmp	r6, #0
	movne	r3, r8, lsr #1
	addne	r2, r9, #1
	addne	lr, r6, r3
	beq	.L29
.L33:
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	ldr	r1, [r4]
	strb	r0, [r1, r3]
	ldrb	r0, [r2], #2	@ zero_extendqisi2
	ldr	r1, [ip]
	strb	r0, [r1, r3]
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L33
	ldr	r3, [fp, #-60]
.L29:
	add	r9, r9, r5
.L32:
	add	r7, r7, #1
	add	r8, r8, r5
	cmp	r7, r10
	bcc	.L34
.L25:
	cmp	r3, #10
	beq	.L36
.L26:
	ldr	r3, [fp, #-108]
	mov	r6, r3, lsr #2
.L58:
	ldr	r7, [fp, #-116]
	mov	r1, r6
	ldr	r8, [fp, #-112]
	ldr	r0, [ip]
	ldr	r3, [r7, #44]
	mov	r2, r8
	blx	r3
	mov	r1, r6
	mov	r2, r8
	ldr	r0, [r4]
	ldr	r3, [r7, #44]
	blx	r3
	ldr	ip, [fp, #16]
	ldr	r0, [fp, #-60]
	mov	r2, r5
	ldr	r1, [fp, #-64]
	str	ip, [sp, #8]
	ldr	ip, [fp, #8]
	ldr	r3, [fp, #4]
	str	ip, [sp, #4]
	ldr	ip, [fp, #12]
	str	ip, [sp]
	ldr	ip, [fp, #-116]
	ldr	r4, [ip, #64]
	str	r0, [sp, #16]
	str	r1, [sp, #12]
	ldr	r0, .L64+20
	ldr	r1, .L64+24
	blx	r4
.L4:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L27:
	cmp	r6, #0
	beq	.L30
	bic	r2, r8, #1
	mov	r3, r9
	mov	r1, #0
.L31:
	ldrh	lr, [r3]
	add	r1, r1, #1
	ldr	r0, [r4]
	cmp	r1, r6
	add	r3, r3, #4
	strh	lr, [r0, r2]	@ movhi
	ldrh	lr, [r3, #-2]
	ldr	r0, [ip]
	strh	lr, [r0, r2]	@ movhi
	add	r2, r2, #2
	bne	.L31
	ldr	r3, [fp, #-60]
.L30:
	ldr	r2, [fp, #-104]
	add	r9, r9, r2
	b	.L32
.L60:
	ldr	r2, [fp, #24]
	cmp	r2, #8
	ldr	r2, [fp, #4]
	ble	.L38
	cmp	r0, #0
	add	lr, r0, #3
	add	r4, r2, #31
	movge	lr, r0
	bic	r4, r4, #31
	mov	lr, lr, asr #2
	b	.L10
.L38:
	mov	r4, #0
	mov	lr, r4
	b	.L10
.L63:
	ldr	r0, [fp, #-108]
	ldr	r2, .L64+28
	cmp	r0, #0
	beq	.L22
	mov	ip, #2
	mov	r3, #0
.L23:
	ldr	lr, [fp, #-88]
	mov	r4, r3, asl #1
	ldr	r1, [fp, #-84]
	ldr	r6, [r2]
	ldrb	r7, [lr, r3]	@ zero_extendqisi2
	ldrb	r1, [r1, r3, lsr #2]	@ zero_extendqisi2
	ldr	lr, .L64+28
	and	r1, r1, #3
	add	r1, r1, r7, lsl #2
	strh	r1, [r6, r4]	@ movhi
	ldr	r1, [fp, #-88]
	ldr	r7, [fp, #-84]
	add	r1, r1, r3
	ldr	r4, [r2]
	ldrb	r6, [r1, #1]	@ zero_extendqisi2
	ldrb	r1, [r7, r3, lsr #2]	@ zero_extendqisi2
	ubfx	r1, r1, #2, #2
	add	r1, r1, r6, lsl #2
	strh	r1, [r4, ip]	@ movhi
	ldr	r1, [fp, #-88]
	ldr	r7, [fp, #-84]
	add	r1, r1, r3
	ldr	r4, [r2]
	ldrb	r6, [r1, #2]	@ zero_extendqisi2
	add	r4, r4, ip
	ldrb	r1, [r7, r3, lsr #2]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #2
	add	r1, r1, r6, lsl #2
	strh	r1, [r4, #2]	@ movhi
	ldr	r6, [fp, #-88]
	ldr	r1, [fp, #-84]
	add	r6, r6, r3
	ldr	r4, [r2]
	ldrb	r1, [r1, r3, lsr #2]	@ zero_extendqisi2
	add	r3, r3, #4
	ldrb	r6, [r6, #3]	@ zero_extendqisi2
	add	r4, r4, ip
	cmp	r3, r0
	add	ip, ip, #8
	mov	r1, r1, lsr #6
	add	r1, r1, r6, lsl #2
	strh	r1, [r4, #4]	@ movhi
	bcc	.L23
	ldr	r3, [fp, #4]
	ldr	r9, [lr]
	movs	r10, r3, lsr #1
	ldr	r3, [fp, #-60]
	ldreq	r4, .L64+12
	ldreq	ip, .L64+16
	bne	.L24
	b	.L25
.L62:
	ldr	r3, [fp, #4]
	ldr	r2, .L64+28
	mul	r3, r5, r3
	cmp	r3, #0
	mov	r0, r3
	str	r3, [fp, #-108]
	beq	.L16
	mov	ip, #2
	mov	r3, #0
.L17:
	ldr	lr, [fp, #-96]
	mov	r4, r3, asl #1
	ldr	r1, [fp, #-92]
	ldr	r6, [r2]
	ldrb	r7, [lr, r3]	@ zero_extendqisi2
	ldrb	r1, [r1, r3, lsr #2]	@ zero_extendqisi2
	ldr	lr, .L64+28
	and	r1, r1, #3
	add	r1, r1, r7, lsl #2
	strh	r1, [r6, r4]	@ movhi
	ldr	r1, [fp, #-96]
	ldr	r7, [fp, #-92]
	add	r1, r1, r3
	ldr	r4, [r2]
	ldrb	r6, [r1, #1]	@ zero_extendqisi2
	ldrb	r1, [r7, r3, lsr #2]	@ zero_extendqisi2
	ubfx	r1, r1, #2, #2
	add	r1, r1, r6, lsl #2
	strh	r1, [r4, ip]	@ movhi
	ldr	r1, [fp, #-96]
	ldr	r7, [fp, #-92]
	add	r1, r1, r3
	ldr	r4, [r2]
	ldrb	r6, [r1, #2]	@ zero_extendqisi2
	add	r4, r4, ip
	ldrb	r1, [r7, r3, lsr #2]	@ zero_extendqisi2
	ubfx	r1, r1, #4, #2
	add	r1, r1, r6, lsl #2
	strh	r1, [r4, #2]	@ movhi
	ldr	r6, [fp, #-96]
	ldr	r1, [fp, #-92]
	add	r6, r6, r3
	ldr	r4, [r2]
	ldrb	r1, [r1, r3, lsr #2]	@ zero_extendqisi2
	add	r3, r3, #4
	ldrb	r6, [r6, #3]	@ zero_extendqisi2
	add	r4, r4, ip
	cmp	r3, r0
	add	ip, ip, #8
	mov	r1, r1, lsr #6
	add	r1, r1, r6, lsl #2
	strh	r1, [r4, #4]	@ movhi
	bcc	.L17
	ldr	r3, [fp, #-60]
	ldr	r0, [lr]
	cmp	r3, #10
	bne	.L19
.L18:
	ldr	r3, .L64+8
	ldr	r1, [fp, #-108]
	ldr	r2, [fp, #-112]
	str	r3, [fp, #-116]
	mov	r1, r1, asl #1
	ldr	r3, [r3, #44]
	blx	r3
	b	.L20
.L7:
	ldr	r0, [fp, #4]
	add	r5, r5, #15
	bic	r5, r5, #15
	add	r0, r0, #15
	bic	r0, r0, #15
	str	r0, [fp, #4]
	b	.L6
.L61:
	ldr	r2, [fp, #24]
	cmp	r2, #8
	ldr	r2, [fp, #4]
	add	r2, r2, #63
	bic	r2, r2, #63
	ble	.L38
	cmp	r0, #0
	add	lr, r0, #3
	mov	r4, r2
	movge	lr, r0
	mov	lr, lr, asr #2
	b	.L10
.L8:
	ldr	r0, [fp, #4]
	add	r5, r5, #7
	bic	r5, r5, #7
	add	r0, r0, #7
	bic	r0, r0, #7
	str	r0, [fp, #4]
	b	.L6
.L22:
	ldr	r1, [fp, #4]
	ldr	r9, [r2]
	movs	r10, r1, lsr #1
	ldreq	r4, .L64+12
	ldreq	ip, .L64+16
	bne	.L24
.L36:
	ldr	r3, [fp, #-108]
	mov	r6, r3, lsr #1
	b	.L58
.L16:
	ldr	r0, [r2]
	b	.L18
.L65:
	.align	2
.L64:
	.word	pY
	.word	pY_2bit
	.word	vfmw_Osal_Func_Ptr_S
	.word	pVl
	.word	pUl
	.word	.LC1
	.word	.LANCHOR0+20
	.word	pPixelArray
	UNWIND(.fnend)
	.size	YUV_DumpFrame_Tile, .-YUV_DumpFrame_Tile
	.align	2
	.global	YUV_DumpImage
	.type	YUV_DumpImage, %function
YUV_DumpImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #60)
	sub	sp, sp, #60
	ldr	r7, .L94
	mov	r3, #0
	mov	r5, r0
	mov	r4, r1
	str	r3, [fp, #-60]
	ldr	r2, [r7, r0, asl #2]
	str	r3, [fp, #-56]
	cmp	r2, r3
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	beq	.L68
	add	r3, r1, #512
	ldrb	r6, [r1, #64]	@ zero_extendqisi2
	ldrd	r0, [r3, #-8]
	orrs	r2, r0, r1
	beq	.L69
	ldrd	r2, [r3]
	orrs	ip, r2, r3
	bne	.L70
.L69:
	ldr	r2, [r4, #20]
	sub	r0, fp, #60
	ldr	r3, .L94+4
	str	r2, [fp, #-52]
	ldr	r3, [r3, #160]
	blx	r3
	subs	r8, r0, #0
	beq	.L92
	ldr	r3, [r4, #24]
	ldr	r2, [r4, #20]
	rsb	r2, r2, r3
	add	r2, r8, r2
.L72:
	cmp	r2, #0
	cmpne	r8, #0
	beq	.L68
	ldr	r3, .L94+8
	ldr	r3, [r3, r5, asl #2]
	ldr	ip, [r3, #1176]
	cmp	ip, #0
	beq	.L74
	ldr	r2, .L94+12
	mov	r0, #32
	ldr	r1, .L94+16
	bl	dprint_vfmw
.L75:
	ldr	r3, .L94+4
	mov	r0, r8
	ldr	r3, [r3, #164]
	blx	r3
.L68:
	ldr	r3, .L94+20
	ldr	r2, [r3, r5, asl #2]
	cmp	r2, #0
	beq	.L76
	add	r3, r4, #432
	ldrd	r0, [r3]
	orrs	r3, r0, r1
	beq	.L76
	ldr	r3, [r4, #420]
	cmp	r3, #0
	bne	.L93
.L76:
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L70:
	mov	r8, r0
	b	.L72
.L93:
	ldr	ip, .L94+4
	mov	r1, r3
	ldr	r3, [ip, #44]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L74:
	ldr	r1, .L94+24
	tst	r6, #28
	ldr	lr, [r4, #168]
	str	r4, [sp, #28]
	moveq	r6, #1
	ldr	r1, [r1]
	movne	r6, #0
	ldr	r0, [r7, r5, asl #2]
	str	lr, [sp, #20]
	str	r1, [sp, #24]
	mov	r1, r8
	ldr	r7, [r3, #52]
	ldr	r3, [r4, #68]
	str	ip, [sp, #4]
	ldr	lr, [r4, #112]
	str	r7, [sp, #16]
	ldr	ip, [r4, #72]
	str	r6, [sp, #12]
	str	lr, [sp, #8]
	str	ip, [sp]
	bl	YUV_DumpFrame_Tile
	b	.L75
.L92:
	ldr	r1, .L94+28
	mov	r0, #32
	bl	dprint_vfmw
	b	.L68
.L95:
	.align	2
.L94:
	.word	vfmw_save_yuv_file
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	.LANCHOR0
	.word	.LC0
	.word	vfmw_save_metadata_reorder_file
	.word	g_SaveYUVBitWidth
	.word	.LC2
	UNWIND(.fnend)
	.size	YUV_DumpImage, .-YUV_DumpImage
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13621, %object
	.size	__func__.13621, 18
__func__.13621:
	.ascii	"YUV_DumpFrame_Cmp\000"
	.space	2
	.type	__func__.13678, %object
	.size	__func__.13678, 19
__func__.13678:
	.ascii	"YUV_DumpFrame_Tile\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%s not support now.\012\000" )
	.space	3
.LC1:
	ASCII(.ascii	"%s: Width=%d, Height=%d, Stride=%d, PicStructure=%d" )
	ASCII(.ascii	", ChromaIDC=%d, RealBitDepth=%d, SaveBitDepth=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC2:
	ASCII(.ascii	" luma_vir_addr MAP return error\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
