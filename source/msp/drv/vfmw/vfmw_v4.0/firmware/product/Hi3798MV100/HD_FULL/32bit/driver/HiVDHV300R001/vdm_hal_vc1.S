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
	.file	"vdm_hal_vc1.c"
	.text
	.align	2
	.global	VC1HAL_V300R001_CfgSliceMsg
	.type	VC1HAL_V300R001_CfgSliceMsg, %function
VC1HAL_V300R001_CfgSliceMsg:
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
	ldr	r3, [r1, #52]
	add	r2, r0, #84
	mov	r10, r0
	str	r2, [fp, #-52]
	mov	r0, r3
	str	r3, [fp, #-56]
	bl	MEM_Phy2Vir
	subs	r4, r0, #0
	beq	.L60
	ldrb	r3, [r10, #4]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L61
	ldr	lr, [r10, #96]
	add	r3, r10, #12288
	str	r3, [fp, #-48]
	bic	r8, lr, #15
	str	r8, [r3, #172]
	ldrb	r0, [r10, #70]	@ zero_extendqisi2
	cmp	r0, #0
	ble	.L1
	mov	r1, #0
	mov	ip, r4
	mov	r7, r1
	cmp	r7, #0
	add	r6, r10, #144
	mov	r4, r1
	bne	.L25
.L62:
	cmp	r0, #1
	ldr	r4, [r10, #108]
	beq	.L46
	ble	.L27
	ldr	r3, [r10, #156]
	cmp	r4, r3
	blt	.L27
	ldr	r3, [fp, #-52]
	mov	r1, #1
	b	.L28
.L30:
	ldr	r2, [r3, #72]
	cmp	r4, r2
	blt	.L40
.L28:
	add	r1, r1, #1
	add	r3, r3, #48
	cmp	r1, r0
	bne	.L30
.L57:
	mov	r2, #0
.L31:
	mov	r3, #0
.L26:
	ldr	r5, [r6, #-44]
	rsb	lr, r8, lr
	ldr	r0, [r6, #-40]
	add	r3, r3, r4, lsl #16
	add	r5, r5, lr, lsl #3
	bic	lr, lr, #15
	add	r7, r7, #1
	add	r6, r6, #48
	add	r0, r0, r5, lsl #25
	str	r0, [ip]
	str	lr, [ip, #4]
	mov	r0, #0
	str	r0, [ip, #8]
	add	ip, ip, #256
	str	r0, [ip, #-244]
	str	r3, [ip, #-240]
	str	r2, [ip, #-4]
	ldrb	r0, [r10, #70]	@ zero_extendqisi2
	cmp	r0, r7
	ble	.L1
	ldr	r3, [fp, #-48]
	cmp	r7, #0
	ldr	lr, [r6, #-48]
	ldr	r8, [r3, #172]
	beq	.L62
.L25:
	ldr	r5, [fp, #-52]
	mov	r3, r1, asl #6
	add	r2, r1, #1
	sub	r3, r3, r1, asl #4
	add	r3, r5, r3
	cmp	r2, r0
	ldr	r5, [r3, #24]
	bge	.L32
	ldr	r9, [r3, #72]
	cmp	r5, r9
	blt	.L32
	mov	r9, r1
	b	.L33
.L35:
	ldr	r1, [r3, #72]
	cmp	r5, r1
	blt	.L58
.L33:
	add	r2, r2, #1
	add	r3, r3, #48
	cmp	r2, r0
	bne	.L35
	mov	r1, r9
	mov	r2, #0
.L36:
	add	r3, r4, #1
	mov	r4, r5
	b	.L26
.L32:
	cmp	r2, r0
	moveq	r2, #0
	beq	.L36
.L58:
	ldr	r3, [fp, #-56]
	mov	r1, r2
	add	r2, r3, r2, lsl #8
	b	.L36
.L27:
	cmp	r0, #1
	beq	.L47
	mov	r1, #1
.L40:
	ldr	r3, [fp, #-56]
	add	r2, r3, r1, lsl #8
	b	.L31
.L46:
	mov	r2, r7
	mov	r3, r7
	b	.L26
.L61:
	ldr	r0, [r10, #96]
	add	r3, r10, #12288
	str	r3, [fp, #-48]
	mov	lr, r3
	str	r0, [r3, #172]
	ldrb	r2, [r10, #70]	@ zero_extendqisi2
	cmp	r2, #0
	ble	.L4
	mov	r3, r10
	mov	r1, #0
.L7:
	ldr	ip, [r3, #88]
	cmp	ip, #0
	beq	.L5
	ldr	ip, [r3, #112]
	cmp	ip, r0
	strcc	ip, [lr, #172]
	movcc	r0, ip
	bcc	.L6
.L5:
	ldr	ip, [r3, #96]
	cmp	ip, r0
	strcc	ip, [lr, #172]
	movcc	r0, ip
.L6:
	add	r1, r1, #1
	add	r3, r3, #48
	cmp	r1, r2
	bne	.L7
.L4:
	ldr	r3, [fp, #-48]
	bic	r0, r0, #15
	ldr	r6, .L63
	ldr	r1, .L63+4
	str	r0, [r3, #172]
	mov	r0, #4
	ldr	r3, [r6, #68]
	blx	r3
	ldrb	ip, [r10, #70]	@ zero_extendqisi2
	cmp	ip, #0
	ble	.L1
	mov	r7, #0
	mov	r9, r10
	str	r10, [fp, #-88]
	mov	r8, r4
	mov	r5, r7
	mov	r10, r7
.L23:
	ldr	r3, [fp, #-48]
	ldr	r2, [r9, #96]
	ldr	r1, [r9, #88]
	ldr	r3, [r3, #172]
	ldr	r4, [r9, #100]
	cmp	r1, #0
	rsb	r2, r3, r2
	ldr	r0, [r9, #104]
	and	lr, r2, #15
	bic	r2, r2, #15
	str	r2, [fp, #-64]
	add	lr, r4, lr, lsl #3
	beq	.L42
	ldr	r2, [r9, #112]
	ldr	r1, [r9, #116]
	rsb	r3, r3, r2
	str	r3, [fp, #-60]
	mov	r2, r3
	ldr	r3, [r9, #120]
	add	r1, r1, r2, lsl #3
	str	r2, [fp, #-76]
	add	r3, r3, r1, lsl #25
	str	r3, [fp, #-68]
	str	r3, [fp, #-72]
.L10:
	cmp	r10, #0
	bne	.L11
	ldr	r3, [fp, #-88]
	cmp	ip, #1
	ldr	r5, [r3, #108]
	beq	.L43
	ble	.L13
	ldr	r3, [r3, #156]
	cmp	r5, r3
	blt	.L13
	ldr	r3, [fp, #-52]
	mov	r7, #1
	b	.L14
.L16:
	ldr	r2, [r3, #72]
	cmp	r5, r2
	blt	.L38
.L14:
	add	r7, r7, #1
	add	r3, r3, #48
	cmp	r7, ip
	bne	.L16
	mov	r3, #0
	mov	r4, r3
.L17:
	mov	r2, #0
	str	r2, [fp, #-84]
.L12:
	add	r2, r0, lr, lsl #25
	str	r3, [fp, #-80]
	str	r2, [r8]
	mov	r0, #4
	ldr	r1, .L63+8
	add	r10, r10, #1
	ldr	r3, [r6, #68]
	add	r9, r9, #48
	blx	r3
	ldr	r3, [fp, #-64]
	ldr	r1, .L63+12
	mov	r0, #4
	add	r8, r8, #256
	str	r3, [r8, #-252]
	mov	r2, r3
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [fp, #-72]
	ldr	r2, [fp, #-68]
	mov	r0, #4
	ldr	r1, .L63+16
	str	r3, [r8, #-248]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [fp, #-76]
	ldr	r2, [fp, #-60]
	mov	r0, #4
	ldr	r1, .L63+20
	str	r3, [r8, #-244]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [fp, #-84]
	ldr	r1, .L63+24
	mov	r0, #4
	add	r2, r3, r5, lsl #16
	str	r2, [r8, #-240]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [fp, #-80]
	mov	r2, r4
	ldr	r1, .L63+28
	mov	r0, #4
	str	r3, [r8, #-4]
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [fp, #-88]
	ldrb	ip, [r3, #70]	@ zero_extendqisi2
	cmp	ip, r10
	bgt	.L23
.L1:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L11:
	ldr	r2, [fp, #-52]
	mov	r3, r7, asl #6
	add	r4, r7, #1
	sub	r3, r3, r7, asl #4
	add	r3, r2, r3
	cmp	r4, ip
	ldr	r2, [r3, #24]
	bge	.L18
	ldr	r1, [r3, #72]
	cmp	r2, r1
	bge	.L19
	b	.L18
.L21:
	ldr	r1, [r3, #72]
	cmp	r2, r1
	blt	.L56
.L19:
	add	r4, r4, #1
	add	r3, r3, #48
	cmp	r4, ip
	bne	.L21
.L45:
	mov	r3, #0
	mov	r4, r3
.L22:
	add	r1, r5, #1
	mov	r5, r2
	str	r1, [fp, #-84]
	b	.L12
.L18:
	cmp	r4, ip
	beq	.L45
.L56:
	ldr	r3, [fp, #-56]
	mov	r7, r4
	add	r4, r3, r4, lsl #8
	mov	r3, r4
	b	.L22
.L13:
	cmp	ip, #1
	beq	.L44
	mov	r7, #1
.L38:
	ldr	r3, [fp, #-56]
	add	r4, r3, r7, lsl #8
	mov	r3, r4
	b	.L17
.L42:
	str	r1, [fp, #-76]
	str	r1, [fp, #-72]
	str	r1, [fp, #-68]
	str	r1, [fp, #-60]
	b	.L10
.L43:
	mov	r3, r10
	str	r10, [fp, #-84]
	mov	r4, r10
	b	.L12
.L60:
	ldr	r3, .L63
	ldr	r2, .L63+32
	ldr	r1, .L63+36
	ldr	r3, [r3, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L44:
	mov	r3, #0
	mov	r7, ip
	mov	r4, r3
	b	.L17
.L47:
	mov	r1, r0
	b	.L57
.L64:
	.align	2
.L63:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR0
	.word	.LC0
	UNWIND(.fnend)
	.size	VC1HAL_V300R001_CfgSliceMsg, .-VC1HAL_V300R001_CfgSliceMsg
	.align	2
	.global	VC1HAL_V300R001_CfgReg
	.type	VC1HAL_V300R001_CfgReg, %function
VC1HAL_V300R001_CfgReg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r4, r2, #0
	mov	r5, r0
	ble	.L84
	ldr	r6, .L87
	mov	r7, #1
	mov	r3, r4
	str	r7, [sp]
	ldr	r2, .L87+4
	mov	r0, #32
	ldr	r8, [r6, #68]
	ldr	r1, .L87+8
	blx	r8
	str	r7, [sp]
	mov	r3, r4
	ldr	r8, [r6, #68]
	ldr	r2, .L87+4
	mov	r0, #32
	ldr	r1, .L87+8
	blx	r8
	str	r7, [sp]
	mov	r3, r4
	ldr	r8, [r6, #68]
	ldr	r2, .L87+4
	mov	r0, #32
	ldr	r1, .L87+8
	blx	r8
	str	r7, [sp]
	mov	r3, r4
	ldr	r8, [r6, #68]
	ldr	r2, .L87+4
	mov	r0, #32
	ldr	r1, .L87+8
	blx	r8
	str	r7, [sp]
	mov	r3, r4
	ldr	r8, [r6, #68]
	ldr	r2, .L87+4
	mov	r0, #32
	ldr	r1, .L87+8
	blx	r8
	str	r7, [sp]
	mov	r3, r4
	ldr	r6, [r6, #68]
	ldr	r2, .L87+4
	mov	r0, #32
	ldr	r1, .L87+8
	blx	r6
.L67:
	ldrh	r1, [r5, #78]
	movw	r2, #30480
	movt	r2, 1
	movw	r3, #30480
	cmp	r1, #256
	movhi	r1, r3
	movls	r1, r2
	cmp	r4, #0
	beq	.L70
	cmp	r4, #1
	bne	.L85
	ldr	r3, .L87+12
	ldr	r0, [r3]
	add	r0, r0, #4
	bl	MEM_WritePhyWord
.L73:
	ldr	r1, .L87
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L87+4
	ldr	r4, [r1, #68]
	ldr	r1, .L87+16
	blx	r4
	mvn	r0, #0
	b	.L82
.L85:
	cmp	r4, #0
	bgt	.L73
.L72:
	movw	r3, #1208
	ldr	r2, .L87+20
	mul	r3, r3, r4
	movw	r1, #3075
	movt	r1, 48
	add	r6, r5, #12288
	ldr	r0, [r2, r3]
	str	r1, [r0, #60]
	ldr	r0, [r2, r3]
	str	r1, [r0, #64]
	ldr	r0, [r2, r3]
	str	r1, [r0, #68]
	ldr	r0, [r2, r3]
	str	r1, [r0, #72]
	ldr	r0, [r2, r3]
	str	r1, [r0, #76]
	ldr	r0, [r2, r3]
	str	r1, [r0, #80]
	ldr	r3, [r2, r3]
	str	r1, [r3, #84]
	ldr	ip, [r6, #176]
	str	ip, [r6, #216]
	ldrh	r3, [r5, #74]
	sub	r1, r3, #1
	cmp	r1, #2048
	movcc	lr, #16
	bcs	.L86
.L75:
	ldrh	r0, [r5, #76]
	movw	r3, #1208
	mul	r3, r3, r4
	adds	r1, r0, #31
	addmi	r1, r0, #62
	add	ip, lr, ip, lsr #4
	bic	r1, r1, #31
	ldr	r4, [r6, #212]
	mov	r0, #0
	mul	r1, ip, r1
	ldr	ip, [r2, r3]
	str	r1, [r6, #220]
	str	r4, [ip, #96]
	ldr	r1, [r2, r3]
	ldr	ip, [r6, #216]
	str	ip, [r1, #100]
	ldr	r1, [r2, r3]
	ldr	ip, [r6, #220]
	str	ip, [r1, #104]
	ldr	r1, [r2, r3]
	ldrb	ip, [r5, #69]	@ zero_extendqisi2
	str	ip, [r1, #152]
	ldr	r1, [r2, r3]
	ldrb	ip, [r5, #68]	@ zero_extendqisi2
	str	ip, [r1, #148]
	ldrh	r1, [r5, #76]
	ldr	r2, [r2, r3]
	adds	r3, r1, #31
	addmi	r3, r1, #62
	bic	r3, r3, #31
	mul	r3, lr, r3
	str	r3, [r2, #108]
.L82:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L86:
	sub	r1, r3, #2048
	sub	r1, r1, #1
	cmp	r1, #2048
	movcc	lr, #32
	bcc	.L75
	sub	r1, r3, #4096
	sub	r1, r1, #1
	cmp	r1, #2048
	movcc	lr, #48
	bcc	.L75
	sub	r3, r3, #6144
	sub	r3, r3, #1
	cmp	r3, #2048
	movcs	lr, #16
	movcc	lr, #64
	b	.L75
.L84:
	movw	r3, #1208
	ldr	r2, .L87+20
	mul	r3, r3, r4
	add	ip, r0, #12288
	mvn	lr, #0
	ldr	r0, [r2, r3]
	str	lr, [r0, #32]
	ldr	lr, [r2, r3]
	ldr	r0, [ip, #164]
	ubfx	r0, r0, #0, #20
	orr	r0, r0, #1090519040
	str	r0, [lr, #8]
	ldr	r0, [r2, r3]
	ldr	lr, [ip, #168]
	str	lr, [r0, #12]
	ldr	r0, [r2, r3]
	ldr	lr, [r1, #48]
	str	lr, [r0, #16]
	ldr	r0, [r1, #32]
	ldr	r1, [r2, r3]
	str	r0, [r1, #20]
	ldr	r3, [r2, r3]
	ldr	r2, [ip, #172]
	str	r2, [r3, #24]
	b	.L67
.L70:
	ldr	r3, .L87+24
	ldr	r0, [r3]
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	b	.L72
.L88:
	.align	2
.L87:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+28
	.word	.LC8
	.word	s_RegPhyBaseAddr_1
	.word	.LC9
	.word	g_HwMem
	.word	s_RegPhyBaseAddr
	UNWIND(.fnend)
	.size	VC1HAL_V300R001_CfgReg, .-VC1HAL_V300R001_CfgReg
	.align	2
	.global	VC1HAL_V300R001_CfgDnMsg
	.type	VC1HAL_V300R001_CfgDnMsg, %function
VC1HAL_V300R001_CfgDnMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r4, r0
	ldr	r0, [r1, #48]
	mov	r6, r1
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L93
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	mov	r2, #0
	ldrb	r0, [r4, #3]	@ zero_extendqisi2
	mov	r5, #0
	ldrb	ip, [r4, #5]	@ zero_extendqisi2
	bfi	r2, r1, #4, #2
	str	r5, [fp, #-40]
	bfi	r2, r0, #0, #2
	mov	r1, #0
	strb	r2, [fp, #-40]
	bfi	r1, ip, #6, #2
	strb	r1, [fp, #-39]
	ldr	r1, [fp, #-40]
	mov	r2, #0
	str	r5, [fp, #-40]
	mov	ip, r2
	mov	r0, r2
	str	r1, [r3]
	ldrh	lr, [r4, #80]
	ldrh	r1, [r4, #78]
	strb	lr, [fp, #-38]
	strb	r1, [fp, #-40]
	mov	r1, r2
	ldr	lr, [fp, #-40]
	str	r5, [fp, #-40]
	str	lr, [r3, #4]
	ldrb	lr, [r4, #8]	@ zero_extendqisi2
	bfi	r2, lr, #2, #1
	ldrb	lr, [r4, #6]	@ zero_extendqisi2
	bfi	r2, lr, #0, #1
	ldrb	lr, [r4, #9]	@ zero_extendqisi2
	bfi	r2, lr, #3, #1
	ldrb	lr, [r4, #7]	@ zero_extendqisi2
	bfi	r2, lr, #1, #1
	ldrb	lr, [r4, #10]	@ zero_extendqisi2
	bfi	r2, lr, #4, #2
	ldrb	lr, [r4, #11]	@ zero_extendqisi2
	bfi	r2, lr, #6, #2
	strb	r2, [fp, #-40]
	ldr	r2, [fp, #-40]
	mov	lr, ip
	str	r5, [fp, #-40]
	str	r2, [r3, #8]
	ldrb	r2, [r4, #15]	@ zero_extendqisi2
	ldrb	r7, [r4, #13]	@ zero_extendqisi2
	bfi	ip, r2, #4, #2
	mov	r2, ip
	ldrb	ip, [r4, #14]	@ zero_extendqisi2
	bfi	r2, r7, #1, #1
	bfi	r2, ip, #2, #1
	ldrb	ip, [r4, #12]	@ zero_extendqisi2
	bfi	r2, ip, #0, #1
	strb	r2, [fp, #-40]
	ldr	r2, [fp, #-40]
	mov	ip, r0
	str	r2, [r3, #12]
	ldrb	r7, [r4, #18]	@ zero_extendqisi2
	ldrb	r2, [r4, #19]	@ zero_extendqisi2
	bfi	r0, r7, #0, #5
	strb	r0, [fp, #-38]
	bfi	r1, r2, #0, #1
	ldrb	r0, [r4, #17]	@ zero_extendqisi2
	strb	r1, [fp, #-37]
	mov	r2, lr
	ldrb	r1, [r4, #16]	@ zero_extendqisi2
	bfi	lr, r0, #0, #5
	strb	lr, [fp, #-39]
	mov	lr, ip
	bfi	ip, r1, #0, #5
	strb	ip, [fp, #-40]
	ldr	r0, [fp, #-40]
	mov	ip, r2
	mov	r1, r2
	str	r5, [fp, #-40]
	str	r0, [r3, #16]
	ldrb	r0, [r4, #24]	@ zero_extendqisi2
	ldrb	r7, [r4, #23]	@ zero_extendqisi2
	bfi	r2, r0, #4, #1
	ldrb	r0, [r4, #20]	@ zero_extendqisi2
	ldrb	r8, [r4, #25]	@ zero_extendqisi2
	bfi	r2, r7, #0, #2
	ldrb	r7, [r4, #22]	@ zero_extendqisi2
	and	r0, r0, #1
	bfi	r2, r8, #6, #1
	ldrb	r8, [r4, #21]	@ zero_extendqisi2
	bfi	r0, r7, #2, #2
	ldrb	r7, [r4, #26]	@ zero_extendqisi2
	strb	r2, [fp, #-39]
	bfi	lr, r7, #0, #4
	mov	r2, r0
	strb	lr, [fp, #-38]
	bfi	r2, r8, #1, #1
	strb	r2, [fp, #-40]
	mov	r0, ip
	ldr	r2, [fp, #-40]
	str	r5, [fp, #-40]
	str	r2, [r3, #20]
	ldrb	r2, [r4, #27]	@ zero_extendqisi2
	ldrb	lr, [r4, #28]	@ zero_extendqisi2
	and	r2, r2, #7
	bfi	r2, lr, #4, #2
	strb	r2, [fp, #-40]
	ldr	lr, [fp, #-40]
	mov	r2, ip
	str	r5, [fp, #-40]
	str	lr, [r3, #24]
	ldrb	lr, [r4, #34]	@ zero_extendqisi2
	bfi	ip, lr, #6, #1
	ldrb	lr, [r4, #33]	@ zero_extendqisi2
	bfi	ip, lr, #4, #2
	strb	ip, [fp, #-39]
	ldrb	lr, [r4, #30]	@ zero_extendqisi2
	mov	ip, r1
	bfi	r1, lr, #1, #1
	ldrb	lr, [r4, #29]	@ zero_extendqisi2
	bfi	r1, lr, #0, #1
	ldrb	lr, [r4, #31]	@ zero_extendqisi2
	bfi	r1, lr, #2, #2
	ldrb	lr, [r4, #32]	@ zero_extendqisi2
	strb	r1, [fp, #-40]
	ldrh	r1, [fp, #-40]
	bfi	r1, lr, #4, #5
	strh	r1, [fp, #-40]	@ movhi
	ldr	r1, [fp, #-40]
	str	r5, [fp, #-40]
	str	r1, [r3, #28]
	ldrb	r1, [r4, #35]	@ zero_extendqisi2
	ldrb	lr, [r4, #36]	@ zero_extendqisi2
	and	r1, r1, #1
	ldrb	r7, [r4, #39]	@ zero_extendqisi2
	bfi	r1, lr, #1, #1
	ldrb	lr, [r4, #37]	@ zero_extendqisi2
	bfi	r1, lr, #2, #1
	ldrb	lr, [r4, #38]	@ zero_extendqisi2
	bfi	r1, lr, #4, #2
	ldrb	lr, [r4, #40]	@ zero_extendqisi2
	bfi	r1, r7, #6, #2
	strb	r1, [fp, #-40]
	bfi	r0, lr, #0, #2
	strb	r0, [fp, #-39]
	ldr	lr, [fp, #-40]
	mov	r1, r2
	mov	r0, r2
	str	r5, [fp, #-40]
	str	lr, [r3, #32]
	ldrb	lr, [r4, #46]	@ zero_extendqisi2
	bfi	r2, lr, #5, #1
	ldrb	lr, [r4, #42]	@ zero_extendqisi2
	bfi	r2, lr, #1, #1
	ldrb	lr, [r4, #44]	@ zero_extendqisi2
	bfi	r2, lr, #3, #1
	ldrb	lr, [r4, #41]	@ zero_extendqisi2
	bfi	r2, lr, #0, #1
	ldrb	lr, [r4, #43]	@ zero_extendqisi2
	bfi	r2, lr, #2, #1
	ldrb	lr, [r4, #47]	@ zero_extendqisi2
	bfi	r2, lr, #6, #1
	ldrb	lr, [r4, #45]	@ zero_extendqisi2
	bfi	r2, lr, #4, #1
	strb	r2, [fp, #-40]
	ldr	lr, [fp, #-40]
	add	r2, r4, #12288
	str	r5, [fp, #-40]
	str	lr, [r3, #36]
	ldrb	r7, [r4, #50]	@ zero_extendqisi2
	ldrb	lr, [r4, #49]	@ zero_extendqisi2
	bfi	ip, r7, #0, #7
	strb	ip, [fp, #-38]
	ldrb	ip, [r4, #48]	@ zero_extendqisi2
	bfi	r0, lr, #0, #3
	strb	r0, [fp, #-39]
	mov	r0, r1
	bfi	r1, ip, #0, #3
	strb	r1, [fp, #-40]
	ldr	ip, [fp, #-40]
	mov	r1, r0
	str	r5, [fp, #-40]
	str	ip, [r3, #40]
	ldrb	lr, [r4, #53]	@ zero_extendqisi2
	ldrb	r7, [r4, #54]	@ zero_extendqisi2
	ldrb	ip, [r4, #51]	@ zero_extendqisi2
	and	lr, lr, #3
	bfi	lr, r7, #4, #1
	strb	lr, [fp, #-39]
	ldrb	lr, [r4, #52]	@ zero_extendqisi2
	and	ip, ip, #7
	bfi	ip, lr, #4, #2
	strb	ip, [fp, #-40]
	ldr	lr, [fp, #-40]
	mov	ip, r0
	str	lr, [r3, #44]
	ldr	lr, [r2, #84]
	str	lr, [r3, #48]
	ldr	lr, [r2, #88]
	str	lr, [r3, #52]
	ldr	lr, [r2, #92]
	str	lr, [r3, #56]
	ldrb	lr, [r4, #55]	@ zero_extendqisi2
	ldrb	r7, [r4, #56]	@ zero_extendqisi2
	bfi	r0, lr, #4, #1
	ldrb	lr, [r4, #57]	@ zero_extendqisi2
	bfi	r0, r7, #5, #3
	strb	r0, [fp, #-38]
	ldrh	r0, [r4, #72]
	and	lr, lr, #1
	ldrb	r7, [r4, #58]	@ zero_extendqisi2
	strh	r0, [fp, #-40]	@ movhi
	bfi	lr, r7, #1, #3
	strb	lr, [fp, #-37]
	ldr	r0, [fp, #-40]
	str	r0, [r3, #60]
	ldr	r0, [r2, #96]
	str	r0, [r3, #64]
	ldr	r0, [r2, #100]
	str	r0, [r3, #68]
	ldr	r0, [r2, #104]
	str	r0, [r3, #72]
	ldr	r0, [r2, #108]
	str	r0, [r3, #76]
	ldr	r0, [r2, #112]
	str	r0, [r3, #80]
	ldr	r0, [r6, #1136]
	str	r0, [r3, #84]
	ldr	r0, [r6, #1140]
	str	r0, [r3, #88]
	ldr	r0, [r6, #1148]
	str	r0, [r3, #92]
	ldr	r0, [r6, #1152]
	str	r0, [r3, #96]
	ldr	r0, [r6, #1168]
	str	r0, [r3, #104]
	ldrh	lr, [r4, #74]
	ldrh	r0, [r4, #76]
	strh	lr, [fp, #-40]	@ movhi
	strh	r0, [fp, #-38]	@ movhi
	ldr	r0, [fp, #-40]
	str	r5, [fp, #-40]
	str	r0, [r3, #108]
	ldrb	r0, [r4, #59]	@ zero_extendqisi2
	ldrb	lr, [r4, #61]	@ zero_extendqisi2
	bfi	r1, r0, #4, #1
	ldrb	r0, [r4, #60]	@ zero_extendqisi2
	bfi	r1, r0, #5, #1
	ldrb	r0, [r4, #63]	@ zero_extendqisi2
	bfi	r1, lr, #6, #1
	strb	r1, [fp, #-38]
	bfi	ip, r0, #1, #3
	ldrb	r0, [r4, #62]	@ zero_extendqisi2
	mov	r1, ip
	bfi	r1, r0, #0, #1
	strb	r1, [fp, #-37]
	ldr	r1, [fp, #-40]
	str	r1, [r3, #112]
	ldr	r1, [r2, #116]
	str	r1, [r3, #116]
	ldr	r1, [r2, #120]
	str	r1, [r3, #120]
	ldr	r1, [r2, #124]
	str	r1, [r3, #124]
	ldr	r1, [r2, #128]
	str	r1, [r3, #128]
	ldr	r1, [r2, #132]
	str	r1, [r3, #132]
	ldr	r1, [r2, #136]
	str	r1, [r3, #136]
	ldr	r1, [r2, #140]
	str	r1, [r3, #140]
	ldr	r2, [r2, #144]
	str	r2, [r3, #144]
	ldr	r2, [r6, #52]
	str	r2, [r3, #252]
	ldr	r0, [r6, #1168]
	str	r2, [fp, #-40]
	bl	MEM_Phy2Vir
	ldr	r3, .L95
	cmp	r0, r5
	beq	.L94
	mov	r2, #3072
	ldr	r1, [r4, #64]
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r5
.L91:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L93:
	ldr	r3, .L95
	ldr	r2, .L95+4
	ldr	r1, .L95+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L91
.L94:
	ldr	r2, .L95+4
	ldr	r1, .L95+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L91
.L96:
	.align	2
.L95:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+52
	.word	.LC0
	.word	.LC10
	UNWIND(.fnend)
	.size	VC1HAL_V300R001_CfgDnMsg, .-VC1HAL_V300R001_CfgDnMsg
	.align	2
	.global	VC1HAL_V300R001_StartDec
	.type	VC1HAL_V300R001_StartDec, %function
VC1HAL_V300R001_StartDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r1, #1
	mov	r5, r1
	mov	r4, r0
	bhi	.L110
	cmp	r1, #0
	bgt	.L111
	cmp	r0, #0
	ldreq	r1, .L115
	ldreq	r3, .L115+4
	beq	.L109
	ldrh	r3, [r0, #78]
	cmp	r3, #512
	bhi	.L112
	ldrh	r3, [r0, #80]
	cmp	r3, #512
	bhi	.L113
	movw	r6, #1208
	ldr	r8, .L115+8
	mul	r6, r6, r5
	add	r7, r6, r8
	ldr	r0, [r7, #48]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	ldreq	r1, .L115
	ldreq	r3, .L115+12
	beq	.L109
	ldr	r3, [r6, r8]
	cmp	r3, #0
	beq	.L114
.L106:
	mov	r1, r7
	mov	r0, r4
	bl	VC1HAL_V300R001_CfgSliceMsg
	mov	r2, r5
	mov	r1, r7
	mov	r0, r4
	bl	VC1HAL_V300R001_CfgReg
	mov	r1, r7
	mov	r0, r4
	bl	VC1HAL_V300R001_CfgDnMsg
	mov	r0, #0
.L100:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L114:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L107
	str	r3, [r6, r8]
	b	.L106
.L112:
	ldr	r1, .L115
	mov	r0, #0
	ldr	r3, .L115+16
.L109:
	ldr	r4, [r1, #68]
	ldr	r2, .L115+20
	ldr	r1, .L115+24
	blx	r4
	mvn	r0, #0
	b	.L100
.L111:
	ldr	r1, .L115
	mov	r0, #0
	mov	r3, r5
	str	r0, [sp]
	ldr	r2, .L115+20
	ldr	r4, [r1, #68]
	ldr	r1, .L115+28
	blx	r4
	mvn	r0, #0
	b	.L100
.L113:
	ldr	r1, .L115
	mov	r0, #0
	ldr	r3, .L115+32
	b	.L109
.L110:
	ldr	r3, .L115
	mov	r0, #0
	ldr	r1, .L115+36
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L100
.L107:
	ldr	r3, .L115
	ldr	r1, .L115+40
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L100
.L116:
	.align	2
.L115:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC12
	.word	g_HwMem
	.word	.LC16
	.word	.LC14
	.word	.LANCHOR0+80
	.word	.LC13
	.word	.LC9
	.word	.LC15
	.word	.LC11
	.word	.LC17
	UNWIND(.fnend)
	.size	VC1HAL_V300R001_StartDec, .-VC1HAL_V300R001_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13904, %object
	.size	__func__.13904, 28
__func__.13904:
	.ascii	"VC1HAL_V300R001_CfgSliceMsg\000"
	.type	__func__.13933, %object
	.size	__func__.13933, 23
__func__.13933:
	.ascii	"VC1HAL_V300R001_CfgReg\000"
	.space	1
	.type	__func__.13945, %object
	.size	__func__.13945, 25
__func__.13945:
	.ascii	"VC1HAL_V300R001_CfgDnMsg\000"
	.space	3
	.type	__func__.13880, %object
	.size	__func__.13880, 25
__func__.13880:
	.ascii	"VC1HAL_V300R001_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%s: pMsgBase = NULL\012\000" )
	.space	3
.LC1:
	ASCII(.ascii	"pVc1DecParam->SlcNum = %d\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"D0 = 0x%08x\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"D1 = 0x%08x\012\000" )
	.space	3
.LC4:
	ASCII(.ascii	"D2 = 0x%08x\012\000" )
	.space	3
.LC5:
	ASCII(.ascii	"D3 = 0x%08x\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"D4 = 0x%08x\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"D63 = 0x%08x\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC10:
	ASCII(.ascii	"%s: u8Tmp = NULL\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"VdhId is wrong! VC1HAL_V200R003_StartDec\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"point of picture para null\012\000" )
.LC13:
	ASCII(.ascii	"%s: %s\012\000" )
.LC14:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC15:
	ASCII(.ascii	"picture height out of range\000" )
.LC16:
	ASCII(.ascii	"can not map down msg virtual address!\000" )
	.space	2
.LC17:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
