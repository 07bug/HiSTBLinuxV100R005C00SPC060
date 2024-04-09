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
	bls	.L3
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L3:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsSliceUnit, .-HEVC_IsSliceUnit
	.align	2
	.type	HEVC_IsNewPic, %function
HEVC_IsNewPic:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r2, [r0, #2316]
	ldr	r1, [r0, #200]
	ldr	r3, [r2, #16]
	cmn	r1, #-2147483647
	sub	ip, r3, #16
	beq	.L37
	cmp	r3, #21
	cmpne	ip, #2
	addls	ip, r0, #40960
	ldrls	lr, [ip, #2624]
	bls	.L11
.L19:
	sub	r3, r3, #19
	add	ip, r0, #40960
	cmp	r3, #1
	movls	r1, #-2147483647
	strls	r1, [r0, #200]
	ldr	lr, [ip, #2624]
.L11:
	cmp	lr, r1
	bge	.L9
	ldr	r4, [r2, #16]
	sub	r3, r4, #8
	cmp	r3, #1
	bls	.L38
.L12:
	ldrb	r1, [r0, #7]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L13
	ldr	r4, [r0, #204]
	cmp	lr, r4
	bge	.L13
	ldr	r5, [r2, #16]
	sub	r3, r5, #8
	cmp	r3, #1
	bls	.L39
.L13:
	ldrb	r3, [ip, #2579]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L14
	ldr	r2, [r2, #16]
	sub	r1, r2, #19
	cmp	r1, #1
	bls	.L34
	cmp	r2, #21
	beq	.L34
	sub	r2, r2, #16
	cmp	r2, #2
	strls	lr, [r0, #204]
	movls	r3, #1
	strlsb	r3, [r0, #7]
.L14:
	ldr	r2, [r0, #216]
	ldrb	r3, [ip, #2577]	@ zero_extendqisi2
	cmp	r2, #0
	ldreq	r1, [ip, #2652]
	bne	.L40
	ldr	r2, [r0, #272]
	cmp	r2, r1
	movne	r0, #1
	beq	.L41
.L32:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L37:
	cmp	ip, #5
	bhi	.L35
	cmp	r3, #21
	cmpne	ip, #2
	bhi	.L19
	add	ip, r0, #40960
	ldr	lr, [ip, #2624]
	str	lr, [r0, #200]
.L9:
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L12
	ldr	r4, [r2, #16]
	sub	r3, r4, #8
	cmp	r3, #1
	bhi	.L12
	ldr	r2, .L42
	movw	r3, #4539
	str	r1, [sp, #4]
	mov	r0, #1
	str	r4, [sp, #8]
	str	lr, [sp]
	ldr	r1, .L42+4
	ldr	r4, [r2, #68]
	ldr	r2, .L42+8
	blx	r4
	mov	r0, #2
	b	.L32
.L40:
	add	r2, r2, #14080
	ldr	r1, [ip, #2652]
	add	r2, r2, #45
	ldr	r2, [r0, r2, asl #2]
	cmp	r1, r2
	ldr	r2, [r0, #272]
	movne	r3, #1
	cmp	r2, r1
	movne	r0, #1
	bne	.L32
	b	.L41
.L39:
	ldr	r2, .L42
	movw	r3, #4549
	stmia	sp, {r1, lr}
	mov	r0, #1
	str	r5, [sp, #12]
	str	r4, [sp, #8]
	ldr	r1, .L42+12
	ldr	r4, [r2, #68]
	ldr	r2, .L42+8
	blx	r4
.L35:
	mov	r0, #2
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L41:
	ldr	r0, [r0, #252]
	cmp	r0, lr
	moveq	r0, r3
	movne	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L38:
	ldr	r2, .L42
	movw	r3, #4531
	str	r1, [sp, #4]
	mov	r0, #1
	str	r4, [sp, #8]
	str	lr, [sp]
	ldr	r1, .L42+16
	ldr	r4, [r2, #68]
	ldr	r2, .L42+8
	blx	r4
	mov	r0, #2
	b	.L32
.L34:
	str	lr, [r0, #204]
	strb	r3, [r0, #7]
	b	.L14
.L43:
	.align	2
.L42:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	.word	.LANCHOR0
	.word	.LC4
	.word	.LC2
	UNWIND(.fnend)
	.size	HEVC_IsNewPic, .-HEVC_IsNewPic
	.align	2
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
	ldr	r1, [r0, #964]
	ldr	r3, [r0, #996]
	ldrb	ip, [lr, #564]	@ zero_extendqisi2
	ldrb	r4, [r0, #980]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #972]
	ldr	r3, [r0, #1004]
	ldrb	ip, [r0, #956]	@ zero_extendqisi2
	ldrb	r4, [r0, #988]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #964]
	ldrb	r4, [lr, #565]	@ zero_extendqisi2
	ldrb	r3, [r0, #997]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #981]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #972]
	ldrb	r4, [r0, #957]	@ zero_extendqisi2
	ldrb	r3, [r0, #1005]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #989]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #980]
	ldrb	r4, [lr, #566]	@ zero_extendqisi2
	ldrb	r3, [r0, #998]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #966]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #988]
	ldrb	r4, [r0, #958]	@ zero_extendqisi2
	ldrb	r3, [r0, #1006]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #974]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #996]
	ldrb	lr, [lr, #567]	@ zero_extendqisi2
	ldrb	r3, [r0, #983]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #967]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1004]
	ldrb	lr, [r0, #959]	@ zero_extendqisi2
	ldrb	r3, [r0, #991]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #975]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #968]
	ldr	r3, [r0, #1000]
	ldrb	ip, [r0, #952]	@ zero_extendqisi2
	ldrb	lr, [r0, #984]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #976]
	ldr	r3, [r0, #1008]
	ldrb	ip, [r0, #960]	@ zero_extendqisi2
	ldrb	lr, [r0, #992]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #968]
	ldrb	lr, [r0, #953]	@ zero_extendqisi2
	ldrb	r3, [r0, #1001]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #985]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #976]
	ldrb	lr, [r0, #961]	@ zero_extendqisi2
	ldrb	r3, [r0, #1009]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #993]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #984]
	ldrb	lr, [r0, #954]	@ zero_extendqisi2
	ldrb	r3, [r0, #1002]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #970]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldr	r1, [r0, #992]
	ldrb	lr, [r0, #962]	@ zero_extendqisi2
	ldrb	r3, [r0, #1010]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #978]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1000]
	ldrb	lr, [r0, #955]	@ zero_extendqisi2
	ldrb	r3, [r0, #987]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #971]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1008]
	ldrb	ip, [r0, #963]	@ zero_extendqisi2
	ldrb	r3, [r0, #995]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #979]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_8x8, .-HEVC_WriteQmatrix_8x8
	.align	2
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
	ldr	r1, [r0, #1340]
	ldr	r3, [r0, #1356]
	ldrb	ip, [lr, #564]	@ zero_extendqisi2
	ldrb	r4, [r0, #1348]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1372]
	ldr	r3, [r0, #1388]
	ldrb	ip, [r0, #1364]	@ zero_extendqisi2
	ldrb	r4, [r0, #1380]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1340]
	ldrb	r4, [lr, #565]	@ zero_extendqisi2
	ldrb	r3, [r0, #1357]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1349]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1372]
	ldrb	r4, [r0, #1365]	@ zero_extendqisi2
	ldrb	r3, [r0, #1389]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1381]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1348]
	ldrb	r4, [lr, #566]	@ zero_extendqisi2
	ldrb	r3, [r0, #1358]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1342]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1380]
	ldrb	r4, [r0, #1366]	@ zero_extendqisi2
	ldrb	r3, [r0, #1390]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1374]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1356]
	ldrb	lr, [lr, #567]	@ zero_extendqisi2
	ldrb	r3, [r0, #1351]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1343]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1388]
	ldrb	lr, [r0, #1367]	@ zero_extendqisi2
	ldrb	r3, [r0, #1383]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1375]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1344]
	ldr	r3, [r0, #1360]
	ldrb	ip, [r0, #1336]	@ zero_extendqisi2
	ldrb	lr, [r0, #1352]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1376]
	ldr	r3, [r0, #1392]
	ldrb	ip, [r0, #1368]	@ zero_extendqisi2
	ldrb	lr, [r0, #1384]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1344]
	ldrb	lr, [r0, #1337]	@ zero_extendqisi2
	ldrb	r3, [r0, #1361]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1353]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1376]
	ldrb	lr, [r0, #1369]	@ zero_extendqisi2
	ldrb	r3, [r0, #1393]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1385]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1352]
	ldrb	lr, [r0, #1338]	@ zero_extendqisi2
	ldrb	r3, [r0, #1362]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1346]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldr	r1, [r0, #1384]
	ldrb	lr, [r0, #1370]	@ zero_extendqisi2
	ldrb	r3, [r0, #1394]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1378]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1360]
	ldrb	lr, [r0, #1339]	@ zero_extendqisi2
	ldrb	r3, [r0, #1355]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1347]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1392]
	ldrb	ip, [r0, #1371]	@ zero_extendqisi2
	ldrb	r3, [r0, #1387]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1379]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_16x16, .-HEVC_WriteQmatrix_16x16
	.align	2
	.type	compare_pic_by_poc_asc, %function
compare_pic_by_poc_asc:
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
	ldr	r2, [r2, #12]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	blt	.L48
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L48:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_poc_asc, .-compare_pic_by_poc_asc
	.align	2
	.type	HEVC_GetMinPOC, %function
HEVC_GetMinPOC:
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
	mov	r8, r2
	mvn	r3, #-2147483648
	mov	r2, #0
	str	r2, [r8]
	str	r3, [r1]
	mov	r6, r1
	ldr	r2, [r0, #2492]
	mov	r7, r0
	ldr	r3, [r0, #2488]
	cmp	r2, r3
	bhi	.L56
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L58:
	add	r5, r7, #2496
	ldr	r9, .L59
	add	r5, r5, #12
	mov	r4, #0
	b	.L53
.L52:
	ldr	r3, [r7, #2492]
	add	r4, r4, #1
	cmp	r3, r4
	bls	.L57
.L53:
	ldr	r3, [r5, #4]!
	ldr	r2, [r6]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	ble	.L52
	ldr	r3, [r9, #112]
	blx	r3
	ldr	r3, [r5]
	ldr	r3, [r3, #12]
	str	r3, [r6]
	str	r4, [r8]
	add	r4, r4, #1
	ldr	r3, [r7, #2492]
	cmp	r3, r4
	bhi	.L53
.L57:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L56:
	ldr	ip, .L59
	mov	r0, #1
	ldr	r1, .L59+4
	ldr	r4, [ip, #68]
	blx	r4
	ldr	r2, [r7, #2488]
	cmp	r2, #0
	str	r2, [r7, #2492]
	bne	.L58
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L60:
	.align	2
.L59:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	UNWIND(.fnend)
	.size	HEVC_GetMinPOC, .-HEVC_GetMinPOC
	.align	2
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
	add	lr, r0, r2, lsl #2
	mov	ip, r2, asl #3
	sub	r2, ip, r2, asl #1
	mov	r5, #0
	ldr	r7, [lr, #276]
	add	r3, r3, r2
	cmp	r7, #64
	mov	r6, r3, asl #4
	movcs	r7, #64
	mov	r8, r7, lsr #2
.L62:
	cmp	r5, r8
	ldmcsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r7, #0
	beq	.L62
	add	r3, r5, r6
	ldrb	ip, [r1]	@ zero_extendqisi2
	mov	r4, r1
	mov	r2, #0
	add	r3, r0, r3, lsl #2
	ldr	lr, [r3, #564]
	orr	ip, lr, ip
	str	ip, [r3, #564]
.L68:
	add	r2, r2, #1
	add	r3, r5, r6
	and	lr, r2, #3
	cmp	r2, r7
	add	r3, r0, r3, lsl #2
	mov	ip, lr, asl #3
	beq	.L62
	ldrb	r9, [r4, #1]!	@ zero_extendqisi2
	cmp	lr, #3
	ldr	lr, [r3, #564]
	addeq	r5, r5, #1
	orr	ip, lr, r9, asl ip
	str	ip, [r3, #564]
	b	.L68
	UNWIND(.fnend)
	.size	HEVC_CalScalingList, .-HEVC_CalScalingList
	.align	2
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
	ldr	r10, .L85
	mov	r7, r0
	ldr	r1, .L85+4
	mov	r0, #1
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r1, [r7, #2504]
	ldr	lr, [r7, #2500]
	mov	r0, #1
	ldr	ip, [r7, #2508]
	ldr	r3, [r7, #2492]
	ldr	r4, [r10, #68]
	ldr	r2, [r7, #2488]
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L85+8
	blx	r4
	ldr	r3, [r7, #2492]
	cmp	r3, #0
	addne	r4, r7, #2496
	movne	r5, #0
	addne	r4, r4, #12
	beq	.L74
.L73:
	ldr	r3, [r4, #4]!
	ldr	r2, [r10, #68]
	ldr	r0, [r7, #244]
	ldrb	lr, [r3]	@ zero_extendqisi2
	ldr	ip, [r3, #12]
	ldr	r6, [r3, #4]
	ldrb	r8, [r3, #1]	@ zero_extendqisi2
	str	r2, [fp, #-48]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	ldr	r1, [r3, #32]
	str	lr, [fp, #-52]
	str	r2, [fp, #-64]
	str	ip, [fp, #-68]
	ldr	r9, [r3, #52]
	str	r6, [fp, #-56]
	str	r8, [fp, #-60]
	bl	FSP_GetLogicFs
	ldr	r3, [r4]
	ldr	r1, [r3, #32]
	mov	r6, r0
	ldr	r0, [r7, #244]
	bl	FSP_GetRef
	ldr	r3, [r4]
	ldr	r1, [r3, #32]
	mov	r8, r0
	ldr	r0, [r7, #244]
	bl	FSP_GetDisplay
	ldr	r1, [r4]
	ldr	lr, [fp, #-52]
	mov	r2, r5
	add	r5, r5, #1
	ldr	ip, [r1, #268]
	mov	r3, r1
	str	ip, [sp, #40]
	ldr	r1, [r1, #32]
	ldr	ip, [fp, #-68]
	str	r9, [sp, #20]
	str	r1, [sp, #36]
	ldr	r1, [fp, #-64]
	ldr	r9, [fp, #-60]
	str	ip, [sp, #16]
	str	r1, [sp, #12]
	ldr	r1, [fp, #-56]
	str	r9, [sp, #8]
	str	lr, [sp]
	str	r1, [sp, #4]
	str	r8, [sp, #28]
	str	r6, [sp, #24]
	ldr	r1, .L85+12
	ldr	ip, [fp, #-48]
	str	r0, [sp, #32]
	mov	r0, #1
	blx	ip
	ldr	r3, [r7, #2492]
	cmp	r3, r5
	bhi	.L73
.L74:
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L85+16
	blx	r3
	ldr	r3, [r7, #2492]
	cmp	r3, #0
	beq	.L72
	add	r5, r7, #2496
	ldr	r9, .L85
	add	r5, r5, #12
	mov	r6, #0
	b	.L81
.L84:
	blx	r3
	ldr	r3, [r9, #68]
	ldr	r2, [r4, #512]
	mov	r0, #1
	ldr	r1, .L85+20
	blx	r3
	ldr	r3, [r9, #68]
	ldrsb	r2, [r4]
	mov	r0, #1
	ldr	r1, .L85+24
	blx	r3
	ldrsb	r2, [r4, #1]
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r1, .L85+28
	blx	r3
.L76:
	cmp	r8, #0
	ldr	r3, [r10, #68]
	mov	r2, r8
	ldr	r1, .L85+32
	mov	r0, #1
	beq	.L77
	blx	r3
	ldr	r2, [r8, #56]
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L85+36
	blx	r3
.L78:
	ldr	r4, [fp, #-48]
	mov	r0, #1
	ldr	r1, .L85+40
	cmp	r4, #0
	ldr	r3, [r10, #68]
	mov	r2, r4
	beq	.L79
	blx	r3
	ldr	r2, [r4, #56]
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L85+44
	blx	r3
.L80:
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L85+16
	add	r6, r6, r0
	blx	r3
	ldr	r3, [r7, #2492]
	cmp	r3, r6
	bls	.L72
.L81:
	ldr	r3, [r5, #4]!
	ldr	r0, [r7, #244]
	ldr	r1, [r3, #32]
	bl	FSP_GetLogicFs
	ldr	r3, [r5]
	ldr	r1, [r3, #32]
	mov	r4, r0
	ldr	r0, [r7, #244]
	bl	FSP_GetDecPhyFs
	ldr	r3, [r5]
	ldr	r1, [r3, #32]
	mov	r8, r0
	ldr	r0, [r7, #244]
	bl	FSP_GetDispPhyFs
	ldr	r3, [r10, #68]
	mov	r2, r6
	ldr	r1, .L85+48
	str	r0, [fp, #-48]
	mov	r0, #1
	blx	r3
	cmp	r4, #0
	mov	r2, r4
	ldr	r1, .L85+52
	mov	r0, #1
	ldr	r3, [r9, #68]
	bne	.L84
	ldr	r1, .L85+56
	mov	r0, #1
	blx	r3
	b	.L76
.L79:
	ldr	r1, .L85+60
	mov	r0, #1
	blx	r3
	b	.L80
.L77:
	ldr	r1, .L85+64
	mov	r0, #1
	blx	r3
	b	.L78
.L72:
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L85+68
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L86:
	.align	2
.L85:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC7
	.word	.LC9
	.word	.LC8
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC17
	.word	.LC18
	.word	.LC20
	.word	.LC21
	.word	.LC11
	.word	.LC12
	.word	.LC16
	.word	.LC22
	.word	.LC19
	.word	.LC10
	UNWIND(.fnend)
	.size	HEVC_PrintDPBState, .-HEVC_PrintDPBState
	.align	2
	.type	HEVC_SetFrmRepeatCount.isra.11.part.12, %function
HEVC_SetFrmRepeatCount.isra.11.part.12:
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
	ldr	ip, [r0, #260]
	ldr	r2, [r0, #2488]
	ldr	r3, [r0, #256]
	add	r2, r2, ip
	add	ip, r2, #1
	cmp	r3, ip
	movcc	r3, #0
	strcc	r3, [r1]
	ldmccfd	sp, {fp, sp, pc}
	sub	r3, r3, #1
	rsb	r3, r2, r3
	cmp	r3, #1
	movhi	r3, #2
	movls	r3, #1
	strhi	r3, [r1]
	strls	r3, [r1]
	ldrhi	r3, [r0, #260]
	ldrls	r3, [r0, #260]
	addhi	r3, r3, #2
	addls	r3, r3, #1
	str	r3, [r0, #260]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_SetFrmRepeatCount.isra.11.part.12, .-HEVC_SetFrmRepeatCount.isra.11.part.12
	.align	2
	.type	HEVC_Sei_User_Data_Unregistered.isra.14, %function
HEVC_Sei_User_Data_Unregistered.isra.14:
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
	cmp	r2, #15
	mov	r8, r2
	mov	r5, r0
	mov	r7, r1
	addhi	r4, r1, #3
	addhi	r6, r1, #19
	bls	.L99
.L94:
	mov	r1, #8
	ldr	r0, [r5]
	bl	BsGet
	strb	r0, [r4, #1]!
	cmp	r4, r6
	bne	.L94
	sub	r0, r8, #16
	str	r0, [r7, #20]
	cmp	r0, #0
	movne	r4, #0
	beq	.L100
.L96:
	mov	r1, #8
	ldr	r0, [r5]
	bl	BsGet
	ldr	r3, [r7, #20]
	add	r4, r4, #1
	cmp	r4, r3
	bcc	.L96
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L100:
	str	r0, [r7]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L99:
	ldr	r3, .L101
	mov	r0, #1
	ldr	r1, .L101+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L102:
	.align	2
.L101:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC23
	UNWIND(.fnend)
	.size	HEVC_Sei_User_Data_Unregistered.isra.14, .-HEVC_Sei_User_Data_Unregistered.isra.14
	.align	2
	.type	HEVC_ue_v.isra.18, %function
HEVC_ue_v.isra.18:
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
	bls	.L106
	ldr	ip, .L107
	movw	r3, #61166
	mov	r2, r0
	movt	r3, 65535
	ldr	r1, .L107+4
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	movw	r0, #61166
	movt	r0, 65535
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L106:
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
.L108:
	.align	2
.L107:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	UNWIND(.fnend)
	.size	HEVC_ue_v.isra.18, .-HEVC_ue_v.isra.18
	.align	2
	.type	HEVC_DecShortTermRefPicSet.isra.19, %function
HEVC_DecShortTermRefPicSet.isra.19:
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
	mov	r10, r1
	mov	r4, r2
	streq	r6, [r2]
	bne	.L151
.L112:
	ldr	r0, [r5]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #16
	str	r0, [r4, #16]
	bhi	.L152
	ldr	r0, [r5]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #16
	str	r0, [r4, #20]
	bhi	.L153
	ldr	r6, [r4, #16]
	add	r2, r0, r6
	str	r2, [r4, #24]
	cmp	r2, #16
	bhi	.L137
	cmp	r6, #0
	addne	r10, r4, #68
	addne	r9, r4, #52
	movne	r7, #0
	movne	r8, r7
	beq	.L139
.L140:
	ldr	r0, [r5]
	add	r7, r7, #1
	bl	HEVC_ue_v.isra.18
	mov	r1, #1
	mvn	r0, r0
	add	r8, r8, r0
	str	r8, [r10, #4]!
	ldr	r0, [r5]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r6, [r4, #16]
	cmp	r7, r6
	bcc	.L140
	ldr	r2, [r4, #24]
.L139:
	cmp	r2, r6
	bls	.L128
	add	r8, r6, #17
	add	r9, r6, #52
	add	r9, r4, r9
	mov	r7, #0
	add	r8, r4, r8, lsl #2
.L141:
	ldr	r0, [r5]
	add	r6, r6, #1
	bl	HEVC_ue_v.isra.18
	mov	r1, #1
	add	r0, r0, r1
	add	r7, r7, r0
	str	r7, [r8, #4]!
	ldr	r0, [r5]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r3, [r4, #24]
	cmp	r6, r3
	bcc	.L141
.L128:
	mov	r0, #0
.L117:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L151:
	mov	r1, #1
	ldr	r0, [r0]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4]
	beq	.L112
	ldr	r3, [r10, #228]
	cmp	r6, r3
	subne	r6, r6, #1
	movne	r3, #0
	strne	r3, [r4, #4]
	beq	.L154
.L116:
	mov	r1, #1
	ldr	r0, [r5]
	bl	BsGet
	mov	r9, #204
	mul	r9, r9, r6
	str	r0, [r4, #8]
	ldr	r0, [r5]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [r4, #8]
	add	r2, r10, r9
	mov	r3, r3, asl #1
	rsb	r3, r3, #1
	add	r0, r0, #1
	str	r0, [r4, #12]
	ldr	r2, [r2, #2756]
	mul	r3, r3, r0
	cmp	r2, #16
	str	r3, [fp, #-60]
	bhi	.L155
	add	r6, r9, #2800
	mov	r3, #0
	add	r6, r6, #4
	mov	r2, r9
	add	r8, r4, #35
	str	r4, [fp, #-56]
	str	r3, [fp, #-48]
	add	r6, r10, r6
	str	r3, [fp, #-52]
	mov	r7, r3
	mov	r4, r3
	mov	r9, r2
	b	.L124
.L119:
	sub	r3, r0, #1
	cmp	r3, #1
	bls	.L156
.L120:
	add	r3, r10, r9
	strb	r0, [r8, #1]!
	add	r4, r4, #1
	add	r6, r6, #4
	ldr	r3, [r3, #2756]
	cmp	r4, r3
	bhi	.L157
.L124:
	mov	r1, #1
	ldr	r0, [r5]
	bl	BsGet
	cmp	r0, #0
	bne	.L119
	mov	r1, #1
	ldr	r0, [r5]
	bl	BsGet
	mov	r0, r0, asl #1
	sub	r3, r0, #1
	cmp	r3, #1
	bhi	.L120
.L156:
	add	r3, r10, r9
	ldr	r2, [fp, #-60]
	add	r1, r7, #18
	sub	ip, r0, #1
	ldr	r3, [r3, #2756]
	clz	ip, ip
	cmp	r3, r4
	mov	ip, ip, lsr #5
	ldrhi	r3, [r6]
	movls	r3, #0
	add	r3, r2, r3
	ldr	r2, [fp, #-56]
	cmp	r3, #0
	str	r3, [r2, r1, asl #2]
	add	r3, r2, r7
	add	r7, r7, #1
	strb	ip, [r3, #53]
	ldrlt	r3, [fp, #-52]
	ldrge	r3, [fp, #-48]
	addlt	r3, r3, #1
	addge	r3, r3, #1
	strlt	r3, [fp, #-52]
	strge	r3, [fp, #-48]
	b	.L120
.L157:
	ldr	r4, [fp, #-56]
	add	r3, r3, #1
	ldr	r2, [fp, #-48]
	cmp	r7, #16
	str	r3, [r4, #28]
	ldr	r3, [fp, #-52]
	str	r7, [r4, #24]
	str	r2, [r4, #20]
	str	r3, [r4, #16]
	bhi	.L125
	cmp	r3, #16
	bhi	.L125
	cmp	r2, #16
	bhi	.L125
	cmp	r7, #1
	subhi	r7, r7, #1
	addhi	r8, r4, #72
	addhi	r6, r4, #53
	movhi	r5, #0
	bls	.L131
.L130:
	ldr	ip, [r8, #4]!
	cmp	r5, #0
	ldrb	lr, [r6, #1]!	@ zero_extendqisi2
	mov	r2, r5
	movge	r1, r8
	movge	r3, r6
	blt	.L133
.L129:
	ldr	r0, [r1, #-4]!
	sub	r3, r3, #1
	cmp	ip, r0
	strlt	r0, [r1, #4]
	ldrltb	r0, [r3]	@ zero_extendqisi2
	strltb	r0, [r3, #1]
	strlt	ip, [r1]
	strltb	lr, [r3]
	subs	r2, r2, #1
	bpl	.L129
.L133:
	add	r5, r5, #1
	cmp	r5, r7
	bne	.L130
.L131:
	ldr	r3, [fp, #-52]
	movs	r6, r3, lsr #1
	beq	.L128
	ldr	r3, [fp, #-52]
	add	r0, r4, #68
	mov	r1, #0
	add	r2, r3, #17
	add	r3, r3, #52
	add	r3, r4, r3
	mov	ip, r0
	add	r2, r4, r2, lsl #2
	add	r4, r4, #53
.L134:
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
	bne	.L134
	b	.L128
.L154:
	ldr	r0, [r5]
	bl	HEVC_ue_v.isra.18
	add	r2, r0, #1
	str	r2, [r4, #4]
	cmp	r6, r2
	bcc	.L158
	sub	r3, r6, #1
	rsb	r6, r0, r3
	cmp	r6, r3
	bls	.L116
	ldr	ip, .L159
	mov	r2, r6
	ldr	r1, .L159+4
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L117
.L125:
	ldr	r3, .L159
	mov	r0, #1
	ldr	r1, .L159+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L117
.L152:
	ldr	r3, .L159
	mov	r2, r0
	ldr	r1, .L159+12
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L117
.L158:
	ldr	ip, .L159
	mov	r3, r6
	ldr	r1, .L159+16
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L117
.L155:
	ldr	r3, .L159
	mov	r0, #1
	ldr	r1, .L159+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L117
.L137:
	ldr	ip, .L159
	mov	r3, #16
	ldr	r1, .L159+24
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L117
.L153:
	ldr	r3, .L159
	mov	r0, #1
	ldr	r2, [r4, #16]
	ldr	r1, .L159+28
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L117
.L160:
	.align	2
.L159:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC26
	.word	.LC28
	.word	.LC29
	.word	.LC25
	.word	.LC27
	.word	.LC31
	.word	.LC30
	UNWIND(.fnend)
	.size	HEVC_DecShortTermRefPicSet.isra.19, .-HEVC_DecShortTermRefPicSet.isra.19
	.align	2
	.type	HEVC_se_v.isra.21, %function
HEVC_se_v.isra.21:
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
	bls	.L166
	mvn	r0, #-2147483648
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L166:
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
	.size	HEVC_se_v.isra.21, .-HEVC_se_v.isra.21
	.align	2
	.type	HEVC_IncreaseDPBSize.isra.28, %function
HEVC_IncreaseDPBSize.isra.28:
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
	ldr	r3, [r1]
	mov	r4, r1
	cmp	r3, #16
	bhi	.L171
	bl	FSP_GetTotalValidFsNum
	subs	r3, r0, #0
	ble	.L170
	ldr	r2, [r4]
	add	r2, r2, #1
	cmp	r3, r2
	bcc	.L170
	ldr	r1, .L172
	mov	r3, r2
	str	r2, [r4]
	mov	r0, #13
	ldr	r2, .L172+4
	ldr	r4, [r1, #68]
	ldr	r1, .L172+8
	blx	r4
	mov	r0, #0
.L169:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L170:
	ldr	ip, .L172
	mov	r0, #1
	ldr	r2, .L172+4
	ldr	r1, .L172+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L169
.L171:
	ldr	r1, .L172
	mov	r5, #17
	ldr	r2, .L172+4
	mov	r0, #1
	str	r5, [sp]
	ldr	r6, [r1, #68]
	ldr	r1, .L172+16
	blx	r6
	str	r5, [r4]
	mvn	r0, #0
	b	.L169
.L173:
	.align	2
.L172:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+16
	.word	.LC33
	.word	.LC34
	.word	.LC32
	UNWIND(.fnend)
	.size	HEVC_IncreaseDPBSize.isra.28, .-HEVC_IncreaseDPBSize.isra.28
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
	subs	r3, r0, #0
	str	r3, [fp, #-56]
	beq	.L198
	ldr	r4, .L199
	mov	r2, #147456
	mov	r1, #0
	ldr	r0, .L199+4
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #36864
	mov	r1, #0
	ldr	r0, .L199+8
	blx	r3
	ldr	r5, [fp, #-56]
	ldr	r3, [r4, #48]
	mov	r2, #880
	add	r0, r5, #53760
	mov	r1, #0
	add	r0, r0, #248
	add	r10, r5, #24576
	blx	r3
	add	r2, r5, #53248
	mov	r3, #0
	str	r2, [fp, #-60]
	str	r3, [r2, #756]
	ldr	r9, [r10, #2608]
	ldr	r1, [r10, #2604]
	ldr	r2, [r9, #72]
	ldr	r8, [r1, #240]
	cmp	r2, r3
	strne	r3, [fp, #-72]
	strne	r3, [fp, #-76]
	beq	.L174
.L183:
	ldr	r2, [r9, #68]
	cmp	r2, #0
	ldr	r2, [fp, #-72]
	add	r2, r2, #108
	streq	r2, [fp, #-80]
	beq	.L184
	mov	r1, r2
	str	r2, [fp, #-80]
	mov	r7, r1, asl #1
	ldr	r1, [fp, #-76]
	mov	r2, #0
	str	r2, [fp, #-48]
	str	r2, [fp, #-52]
	mul	r1, r8, r1
	ldr	r2, [fp, #-60]
	ldr	r2, [r2, #756]
	str	r1, [fp, #-68]
.L182:
	add	r1, r2, #6720
	ldr	r0, [fp, #-56]
	add	r1, r1, #30
	add	r1, r0, r1, lsl #3
	str	r3, [r1, #8]
	ldrsh	r1, [r9, r7]
	cmp	r1, #0
	ldreq	r1, [fp, #-48]
	addeq	r1, r1, #88
	streq	r1, [fp, #-64]
	beq	.L178
	ldr	r2, [fp, #-48]
	mov	r5, #0
	ldr	r1, [fp, #-52]
	add	r2, r2, #88
	ldr	r0, [fp, #-68]
	str	r2, [fp, #-64]
	add	r6, r1, r0
	mov	ip, r2, asl #1
.L179:
	ldrsh	r2, [r9, ip]
	cmp	r2, #0
	beq	.L181
	ldr	r2, .L199+4
	rsb	lr, r3, r6
	mov	r4, r3
	add	r2, r2, r3, lsl #2
.L180:
	add	r1, lr, r3
	str	r1, [r2], #4
	ldr	r9, [r10, #2608]
	add	r3, r3, #1
	rsb	r1, r4, r3
	ldrsh	r0, [r9, ip]
	cmp	r0, r1
	bhi	.L180
.L181:
	ldrsh	r2, [r9, r7]
	add	r5, r5, #1
	add	r6, r6, r8
	cmp	r2, r5
	bhi	.L179
	ldr	r2, [fp, #-60]
	ldr	r2, [r2, #756]
.L178:
	ldr	r1, [fp, #-56]
	sub	ip, r3, #1
	ldr	r0, [fp, #-64]
	add	r1, r1, r2, lsl #3
	ldr	lr, [fp, #-48]
	add	r1, r1, #53760
	add	r2, r2, #1
	mov	r0, r0, asl #1
	add	lr, lr, #1
	str	ip, [r1, #252]
	ldr	r1, [fp, #-60]
	str	lr, [fp, #-48]
	str	r2, [r1, #756]
	ldr	r1, [r9, #68]
	ldrsh	r0, [r9, r0]
	cmp	r1, lr
	ldr	r1, [fp, #-52]
	add	r1, r1, r0
	str	r1, [fp, #-52]
	bhi	.L182
.L184:
	ldr	r2, [fp, #-80]
	ldr	r0, [fp, #-72]
	ldr	r1, [r9, #72]
	mov	r2, r2, asl #1
	add	r0, r0, #1
	cmp	r1, r0
	ldr	r1, [fp, #-76]
	ldrsh	r2, [r9, r2]
	str	r0, [fp, #-72]
	add	r2, r1, r2
	str	r2, [fp, #-76]
	bhi	.L183
.L174:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L198:
	ldr	ip, .L199
	movw	r3, #6082
	ldr	r2, .L199+12
	mov	r0, #1
	ldr	r1, .L199+16
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L200:
	.align	2
.L199:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LANCHOR2+144
	.word	.LANCHOR0+40
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_CalcTileMap, .-HEVC_CalcTileMap
	.align	2
	.global	HEVC_WritePicMsg
	.type	HEVC_WritePicMsg, %function
HEVC_WritePicMsg:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	subs	r4, r0, #0
	beq	.L253
	ldr	r7, .L257
	add	r6, r4, #40960
	ldr	r1, .L257+4
	mov	r0, #2
	ldr	r2, [r6, #2268]
	add	r5, r4, #49152
	ldr	r3, [r6, #2052]
	add	r10, r4, #53248
	ldr	r8, [r7, #68]
	mov	r9, #0
	blx	r8
	ldr	r3, [r7, #68]
	ldr	r1, .L257+8
	mov	r0, #4
	blx	r3
	ldr	r3, [r6, #2264]
	add	r8, r4, #24576
	add	lr, r4, #53504
	add	lr, lr, #32
	str	lr, [fp, #-48]
	str	r3, [r5, #3492]
	add	lr, r4, #53504
	ldr	r3, [r6, #2176]
	add	lr, lr, #112
	ldr	ip, [r6, #2180]
	add	r1, r4, #2912
	str	lr, [fp, #-60]
	add	r0, r4, #51456
	rsb	ip, r3, ip
	str	ip, [r5, #3496]
	ldr	ip, [r6, #2268]
	mov	r2, #64
	add	r1, r1, #8
	add	r0, r0, #20
	str	ip, [r5, #3484]
	ldr	ip, [r6, #2052]
	str	ip, [r5, #3488]
	ldr	ip, [r6, #2216]
	str	ip, [r5, #3500]
	ldr	ip, [r6, #2204]
	rsb	r3, r3, ip
	str	r3, [r5, #3504]
	ldr	r3, [r6, #2212]
	rsb	ip, ip, r3
	str	ip, [r5, #3508]
	str	r9, [r4, #208]
	ldr	r3, [r10, #3248]
	str	r3, [r10, #528]
	ldr	r3, [r8, #2604]
	ldrb	ip, [r3, #12]	@ zero_extendqisi2
	strb	ip, [r5, #2204]
	ldrb	ip, [r3, #5]	@ zero_extendqisi2
	strb	ip, [r5, #2205]
	ldrb	ip, [r3, #9]	@ zero_extendqisi2
	strb	ip, [r5, #2206]
	ldrb	ip, [r3, #8]	@ zero_extendqisi2
	strb	ip, [r5, #2207]
	ldrb	ip, [r3, #7]	@ zero_extendqisi2
	strb	ip, [r5, #2208]
	ldr	ip, [r3, #64]
	str	ip, [r5, #2212]
	ldr	ip, [r3, #116]
	strb	ip, [r5, #2216]
	ldr	ip, [r3, #244]
	sub	ip, ip, #1
	str	ip, [r5, #2220]
	ldr	ip, [r3, #240]
	sub	ip, ip, #1
	str	ip, [r5, #2224]
	ldr	ip, [r6, #2024]
	str	ip, [r5, #2228]
	ldr	ip, [r8, #2608]
	ldr	lr, [ip, #84]
	sub	lr, lr, #2
	str	lr, [r5, #2232]
	ldrb	lr, [ip, #11]	@ zero_extendqisi2
	strb	lr, [r5, #2236]
	ldrb	ip, [ip, #10]	@ zero_extendqisi2
	strb	ip, [r5, #2237]
	ldr	ip, [r3, #200]
	str	ip, [r5, #2240]
	ldr	ip, [r3, #208]
	str	ip, [r5, #2244]
	ldr	ip, [r3, #188]
	str	ip, [r5, #2248]
	ldr	ip, [r3, #196]
	str	ip, [r5, #2252]
	ldr	ip, [r3, #172]
	str	ip, [r5, #2256]
	ldr	ip, [r3, #180]
	str	ip, [r5, #2260]
	ldr	ip, [r3, #216]
	str	ip, [r5, #2264]
	ldr	ip, [r3, #140]
	str	ip, [r5, #2268]
	ldr	ip, [r3, #148]
	str	ip, [r5, #2272]
	ldr	ip, [r3, #112]
	str	ip, [r5, #2276]
	ldr	ip, [r3, #104]
	str	ip, [r5, #2280]
	ldr	ip, [r3, #124]
	str	ip, [r5, #2284]
	ldr	ip, [r3, #120]
	str	ip, [r5, #2288]
	ldr	ip, [r3, #108]
	str	ip, [r5, #2292]
	ldr	r3, [r3, #100]
	str	r3, [r5, #2296]
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r8, #2604]
	add	r0, r4, #52992
	add	r0, r0, #32
	ldr	r2, [r3, #76]
	str	r2, [r5, #2388]
	ldr	r2, [r3, #72]
	str	r2, [r5, #2392]
	ldr	r2, [r8, #2608]
	ldr	r3, [r3, #148]
	str	r3, [fp, #-64]
	ldr	r3, [r2, #68]
	ldr	r2, [r2, #72]
	str	r3, [fp, #-52]
	sub	r3, r3, #1
	cmp	r3, #9
	str	r2, [fp, #-56]
	bhi	.L254
	ldr	r3, [fp, #-56]
	sub	r3, r3, #1
	cmp	r3, #10
	bhi	.L255
	ldr	r3, [r7, #48]
	mov	r2, #512
	mov	r1, r9
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, r9
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #88
	mov	r1, r9
	ldr	r0, [fp, #-60]
	blx	r3
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	ble	.L212
	ldr	r3, [fp, #-64]
	mov	r1, r9
	mov	lr, r9
	ldr	r9, [fp, #-48]
	sub	r3, r3, #4
	str	r5, [fp, #-68]
	mov	r5, r3
.L211:
	ldr	r3, [fp, #-48]
	str	r1, [r3, lr, asl #3]
	mov	r3, r1, asl r5
	ldr	r2, [r8, #2608]
	add	r2, r2, lr, lsl #1
	ldrsh	r2, [r2, #176]
	add	r1, r1, r2
	sub	r2, r1, #1
	str	r2, [r9, #4]
	mov	r0, r1, asl r5
	cmp	r3, r0
	bge	.L217
	cmp	r3, #255
	bhi	.L213
	add	r2, r3, #52992
	uxtb	ip, lr
	add	r2, r2, #31
	add	r2, r4, r2
	b	.L215
.L216:
	cmp	r3, #256
	beq	.L213
.L215:
	add	r3, r3, #1
	strb	ip, [r2, #1]!
	cmp	r3, r0
	bne	.L216
.L217:
	ldr	r3, [fp, #-52]
	add	lr, lr, #1
	add	r9, r9, #8
	cmp	lr, r3
	bne	.L211
	ldr	r5, [fp, #-68]
.L212:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	ble	.L209
	ldr	r3, [fp, #-64]
	mov	ip, #0
	str	r5, [fp, #-48]
	mov	lr, ip
	sub	r9, r3, #4
	ldr	r3, [fp, #-60]
	mov	r5, r3
.L219:
	ldr	r3, [fp, #-60]
	str	ip, [r3, lr, asl #3]
	mov	r3, ip, asl r9
	ldr	r2, [r8, #2608]
	add	r2, r2, lr, lsl #1
	ldrsh	r2, [r2, #216]
	add	ip, ip, r2
	sub	r2, ip, #1
	str	r2, [r5, #4]
	mov	r1, ip, asl r9
	cmp	r3, r1
	bge	.L224
	cmp	r3, #255
	bhi	.L220
	add	r2, r3, #53248
	uxtb	r0, lr
	add	r2, r2, #31
	add	r2, r4, r2
	b	.L222
.L223:
	cmp	r3, #256
	beq	.L220
.L222:
	add	r3, r3, #1
	strb	r0, [r2, #1]!
	cmp	r3, r1
	bne	.L223
.L224:
	ldr	r3, [fp, #-56]
	add	lr, lr, #1
	add	r5, r5, #8
	cmp	lr, r3
	bne	.L219
	ldr	r5, [fp, #-48]
.L209:
	ldr	r3, [r8, #2608]
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	strb	r2, [r5, #2416]
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	strb	r2, [r5, #2417]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	strb	r2, [r5, #2418]
	ldrb	r2, [r3, #14]	@ zero_extendqisi2
	strb	r2, [r5, #2419]
	ldrb	r2, [r3, #15]	@ zero_extendqisi2
	strb	r2, [r5, #2420]
	ldrb	r2, [r3, #13]	@ zero_extendqisi2
	strb	r2, [r5, #2421]
	ldr	r2, [r8, #2604]
	ldr	r1, [r3, #56]
	ldr	r2, [r2, #148]
	rsb	r2, r1, r2
	str	r2, [r3, #88]
	ldr	r3, [r8, #2608]
	ldr	r2, [r3, #88]
	str	r2, [r5, #2424]
	ldr	r2, [r3, #52]
	str	r2, [r5, #2428]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	strb	r2, [r5, #2432]
	ldrb	r2, [r3, #12]	@ zero_extendqisi2
	strb	r2, [r5, #2433]
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	strb	r2, [r5, #2434]
	ldr	r2, [r3, #60]
	str	r2, [r5, #2436]
	ldr	r2, [r3, #64]
	str	r2, [r5, #2440]
	ldr	r2, [r3, #72]
	sub	r2, r2, #1
	str	r2, [r5, #2444]
	ldr	r2, [r3, #68]
	sub	r2, r2, #1
	str	r2, [r5, #2448]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	strb	r2, [r5, #2237]
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	strb	r3, [r5, #2236]
	ldr	r3, [r6, #2068]
	ldr	r0, [r4, #244]
	ldr	r1, [r3, #32]
	bl	FSP_GetLogicFs
	subs	r8, r0, #0
	beq	.L256
	ldr	r2, [r8, #520]
	ldr	r3, [r8, #524]
	cmp	r2, #0
	beq	.L226
	cmp	r3, #0
	beq	.L226
	add	r3, r4, #52736
	add	r2, r4, #52480
	add	r2, r2, #196
	ldr	r0, [r4, #244]
	mov	r1, r3
	add	r3, r3, #160
	add	r1, r1, #68
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r8, #520]
	add	r2, r4, #52736
	ldr	r3, [r3, #4]
	mov	r1, r2
	add	r2, r2, #72
	add	r1, r1, #152
	str	r3, [r5, #3484]
	ldr	r0, [r4, #244]
	bl	FSP_GetPmvAddrTab
	ldr	r3, [r6, #2052]
	str	r3, [r5, #3488]
	ldr	r3, [r8, #536]
	str	r3, [r5, #3740]
	ldr	r3, [r8, #524]
	ldr	r3, [r3, #12]
	str	r3, [r10, #748]
	ldr	r3, [r8, #524]
	ldr	r3, [r3, #44]
	str	r3, [r10, #752]
	ldr	ip, [r4, #2784]
	cmp	ip, #0
	str	ip, [r10, #520]
	beq	.L228
	add	r1, r4, #2848
	add	r2, r4, #53504
	add	r1, r1, #4
	add	r2, r2, #196
	mov	r3, #0
.L229:
	add	r3, r3, #1
	ldr	r0, [r1, #4]!
	cmp	r3, ip
	str	r0, [r2, #4]!
	bne	.L229
.L228:
	add	r8, r4, #51456
	mov	r7, #0
	add	r8, r8, #152
.L230:
	mov	r2, r8
	mov	r0, r7
	mov	r1, r4
	add	r7, r7, #1
	bl	HEVC_WriteQmatrix_8x8
	cmp	r7, #4
	add	r8, r8, #64
	bne	.L230
	add	r2, r4, #51712
	mov	r0, r7
	add	r2, r2, #152
	mov	r1, r4
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r4, #51712
	add	r2, r2, #216
	mov	r1, r4
	mov	r0, #5
	add	r8, r4, #51968
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r8, #24
	mov	r1, r4
	mov	r0, #0
	bl	HEVC_WriteQmatrix_16x16
	add	r2, r4, #51968
	add	r2, r2, #88
	mov	r1, r4
	mov	r0, #1
	add	r8, r8, #152
	mov	r7, #2
	bl	HEVC_WriteQmatrix_16x16
.L231:
	mov	r2, r8
	mov	r0, r7
	mov	r1, r4
	add	r7, r7, #1
	bl	HEVC_WriteQmatrix_16x16
	cmp	r7, #6
	add	r8, r8, #64
	bne	.L231
	mov	ip, r4
	mov	r3, r4
	mov	r9, #2
.L232:
	ldr	r1, [r3, #1724]
	add	r0, r3, #52224
	ldr	r7, [r3, #1740]
	subs	r9, r9, #1
	ldrb	lr, [r3, #1732]	@ zero_extendqisi2
	add	r3, r3, #64
	ldrb	r2, [r3, #1652]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r2, r2, r7, asl #24
	uxth	r1, r1
	orr	r2, r2, lr, asl #16
	mov	r7, r0
	orr	r2, r2, r1
	str	r2, [r0, #152]
	ldr	r1, [r3, #1692]
	mov	lr, r0
	ldr	r2, [r3, #1708]
	ldrb	r0, [r3, #1684]	@ zero_extendqisi2
	ldrb	r8, [r3, #1700]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r2, r0, r2, asl #24
	mov	r0, r7
	uxth	r1, r1
	orr	r2, r2, r8, asl #16
	orr	r2, r2, r1
	str	r2, [r7, #156]
	ldr	r1, [r3, #1660]
	ldrb	r8, [r3, #1653]	@ zero_extendqisi2
	ldrb	r2, [r3, #1677]	@ zero_extendqisi2
	and	r1, r1, #65280
	orr	r1, r8, r1
	ldrb	r8, [r3, #1669]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #24
	orr	r2, r2, r8, asl #16
	str	r2, [lr, #160]
	ldr	r1, [r3, #1692]
	mov	lr, r7
	ldrb	r8, [r3, #1685]	@ zero_extendqisi2
	ldrb	r2, [r3, #1709]	@ zero_extendqisi2
	and	r1, r1, #65280
	orr	r1, r8, r1
	ldrb	r8, [r3, #1701]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #24
	orr	r2, r2, r8, asl #16
	str	r2, [r0, #164]
	ldr	r1, [r3, #1668]
	mov	r0, r7
	ldrb	r8, [r3, #1654]	@ zero_extendqisi2
	ldrb	r2, [r3, #1678]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, r8, r1
	ldrb	r8, [r3, #1662]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #24
	orr	r2, r2, r8, asl #8
	str	r2, [r7, #168]
	ldr	r1, [r3, #1700]
	ldrb	r8, [r3, #1686]	@ zero_extendqisi2
	ldrb	r2, [r3, #1710]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, r8, r1
	ldrb	r8, [r3, #1694]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #24
	orr	r2, r2, r8, asl #8
	str	r2, [lr, #172]
	ldr	r1, [r3, #1676]
	mov	lr, r7
	ldrb	r8, [r3, #1655]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r2, [r3, #1671]	@ zero_extendqisi2
	orr	r1, r8, r1
	ldrb	r8, [r3, #1663]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #16
	orr	r2, r2, r8, asl #8
	str	r2, [r0, #176]
	ldr	r1, [r3, #1708]
	mov	r0, r7
	ldrb	r8, [r3, #1687]	@ zero_extendqisi2
	ldrb	r2, [r3, #1703]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	orr	r1, r8, r1
	ldrb	r8, [r3, #1695]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #16
	orr	r2, r2, r8, asl #8
	str	r2, [r7, #180]
	ldr	r1, [r3, #1664]
	ldr	r2, [r3, #1680]
	ldrb	r7, [r3, #1656]	@ zero_extendqisi2
	ldrb	r8, [r3, #1672]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r2, r7, r2, asl #24
	mov	r7, lr
	uxth	r1, r1
	orr	r2, r2, r8, asl #16
	orr	r2, r2, r1
	str	r2, [lr, #184]
	ldr	r1, [r3, #1696]
	ldr	r2, [r3, #1712]
	ldrb	lr, [r3, #1688]	@ zero_extendqisi2
	ldrb	r8, [r3, #1704]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r2, lr, r2, asl #24
	mov	lr, r0
	uxth	r1, r1
	orr	r2, r2, r8, asl #16
	orr	r2, r2, r1
	str	r2, [r0, #188]
	ldr	r1, [r3, #1664]
	ldrb	r8, [r3, #1657]	@ zero_extendqisi2
	ldrb	r2, [r3, #1681]	@ zero_extendqisi2
	and	r1, r1, #65280
	orr	r1, r8, r1
	ldrb	r8, [r3, #1673]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #24
	orr	r2, r2, r8, asl #16
	str	r2, [r7, #192]
	ldr	r1, [r3, #1696]
	mov	r7, r0
	ldrb	r8, [r3, #1689]	@ zero_extendqisi2
	ldrb	r2, [r3, #1713]	@ zero_extendqisi2
	and	r1, r1, #65280
	orr	r1, r8, r1
	ldrb	r8, [r3, #1705]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #24
	orr	r2, r2, r8, asl #16
	str	r2, [lr, #196]
	ldr	r1, [r3, #1672]
	mov	lr, r0
	ldrb	r8, [r3, #1658]	@ zero_extendqisi2
	ldrb	r2, [r3, #1682]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, r8, r1
	ldrb	r8, [r3, #1666]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #24
	orr	r2, r2, r8, asl #8
	str	r2, [r0, #200]
	ldr	r1, [r3, #1704]
	ldrb	r8, [r3, #1690]	@ zero_extendqisi2
	ldrb	r2, [r3, #1714]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, r8, r1
	ldrb	r8, [r3, #1698]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #24
	orr	r2, r2, r8, asl #8
	str	r2, [r7, #204]
	ldr	r1, [r3, #1680]
	ldrb	r7, [r3, #1659]	@ zero_extendqisi2
	ldrb	r2, [r3, #1675]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	orr	r1, r7, r1
	ldrb	r7, [r3, #1667]	@ zero_extendqisi2
	orr	r2, r1, r2, asl #16
	orr	r2, r2, r7, asl #8
	str	r2, [lr, #208]
	ldr	r1, [r3, #1712]
	ldrb	r7, [r3, #1691]	@ zero_extendqisi2
	ldrb	r2, [r3, #1707]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	lr, [r3, #1699]	@ zero_extendqisi2
	orr	r1, r7, r1
	orr	r2, r1, r2, asl #16
	orr	r2, r2, lr, asl #8
	str	r2, [r0, #212]
	bne	.L232
	add	lr, r4, #52480
	add	r7, r4, #384
	add	lr, lr, #24
.L233:
	ldr	r3, [ip, #572]
	add	ip, ip, #64
	ldr	r0, [ip, #500]
	add	lr, lr, #16
	ldr	r8, [ip, #504]
	and	r1, r3, #65280
	ldr	r2, [ip, #512]
	ubfx	r9, r0, #8, #8
	orr	r1, r9, r1
	mov	r3, r3, asl #8
	uxtb	r9, r8
	uxtb	r0, r0
	ubfx	r10, r2, #8, #8
	orr	r0, r0, r2, asl #24
	ubfx	r8, r8, #8, #8
	orr	r0, r0, r9, asl #16
	orr	r2, r1, r10, asl #24
	uxth	r3, r3
	orr	r3, r0, r3
	orr	r2, r2, r8, asl #16
	str	r3, [lr, #-16]
	str	r2, [lr, #-12]
	ldr	r2, [ip, #504]
	ldrb	r0, [ip, #502]	@ zero_extendqisi2
	ldrb	r3, [ip, #514]	@ zero_extendqisi2
	and	r2, r2, #16711680
	ldrb	r1, [ip, #510]	@ zero_extendqisi2
	orr	r2, r0, r2
	orr	r3, r2, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [lr, #-8]
	ldr	r2, [ip, #512]
	ldrb	r0, [ip, #503]	@ zero_extendqisi2
	ldrb	r3, [ip, #507]	@ zero_extendqisi2
	and	r2, r2, #-16777216
	ldrb	r1, [ip, #511]	@ zero_extendqisi2
	orr	r2, r0, r2
	cmp	ip, r7
	orr	r3, r2, r3, asl #16
	orr	r3, r3, r1, asl #8
	str	r3, [lr, #-4]
	bne	.L233
	ldr	r1, [r4, #2252]
	mov	r0, #0
	ldr	r3, [r4, #2256]
	ldr	r2, [r4, #2244]
	ldr	ip, [r4, #2248]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r5, #3448]
	ldr	r1, [r4, #2268]
	ldr	r3, [r4, #2272]
	ldr	r2, [r4, #2260]
	ldr	ip, [r4, #2264]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r5, #3452]
	ldr	r3, [r6, #2052]
	str	r3, [r5, #3480]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L213:
	ldr	r4, [r7, #68]
	mov	r0, #1
	ldr	r2, .L257+12
	ldr	r1, .L257+16
	blx	r4
.L205:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r2, .L257+20
	ldr	r1, .L257+24
	blx	r3
	mvn	r0, #0
.L248:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L220:
	ldr	r4, [r7, #68]
	mov	r0, #1
	ldr	r2, .L257+12
	ldr	r1, .L257+28
	blx	r4
	b	.L205
.L255:
	mov	r2, #11
	ldr	r4, [r7, #68]
	ldr	r3, [fp, #-56]
	mov	r0, #1
	str	r2, [sp]
	ldr	r1, .L257+32
	ldr	r2, .L257+12
	blx	r4
	b	.L205
.L226:
	ldr	r4, [r7, #68]
	mov	r0, #1
	ldr	r1, .L257+36
	blx	r4
	mvn	r0, #0
	b	.L248
.L254:
	mov	r2, #10
	ldr	r4, [r7, #68]
	ldr	r3, [fp, #-52]
	mov	r0, #1
	str	r2, [sp]
	ldr	r1, .L257+40
	ldr	r2, .L257+12
	blx	r4
	b	.L205
.L253:
	ldr	ip, .L257
	movw	r3, #6137
	ldr	r2, .L257+20
	mov	r0, #1
	ldr	r1, .L257+44
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L248
.L256:
	ldr	r2, [r6, #2068]
	mov	r0, #1
	ldr	r3, [r7, #68]
	ldr	r1, .L257+48
	ldr	r2, [r2, #32]
	blx	r3
	mvn	r0, #0
	b	.L248
.L258:
	.align	2
.L257:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC36
	.word	.LC37
	.word	.LANCHOR0+80
	.word	.LC40
	.word	.LANCHOR0+60
	.word	.LC44
	.word	.LC41
	.word	.LC39
	.word	.LC43
	.word	.LC38
	.word	.LC35
	.word	.LC42
	UNWIND(.fnend)
	.size	HEVC_WritePicMsg, .-HEVC_WritePicMsg
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.global	__aeabi_idiv
	.global	__aeabi_idivmod
	.align	2
	.global	HEVC_WriteSliceMsg
	.type	HEVC_WriteSliceMsg, %function
HEVC_WriteSliceMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 296
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #300)
	sub	sp, sp, #300
	subs	r4, r0, #0
	beq	.L445
	add	r5, r4, #40960
	ldrb	r3, [r5, #2579]	@ zero_extendqisi2
	cmp	r3, #0
	addeq	r3, r4, #43520
	addne	r3, r4, #47104
	addeq	r3, r3, #16
	addne	r3, r3, #164
	ldr	r0, [r3, #160]
	ldr	ip, [r3, #164]
	cmp	r0, #16
	bhi	.L446
	cmp	ip, #16
	bhi	.L266
	cmp	r0, #0
	beq	.L267
	ldr	r3, [r4, #2320]
	cmp	r3, #0
	beq	.L360
	ldr	r3, [r3, #32]
	cmp	r3, #0
	addne	r1, r4, #2320
	movne	r2, #0
	bne	.L272
	b	.L447
.L273:
	ldr	r3, [r1, #4]!
	cmp	r3, #0
	beq	.L268
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L269
.L272:
	add	r2, r2, #1
	cmp	r2, r0
	bne	.L273
.L267:
	cmp	ip, #0
	beq	.L274
	ldr	r3, [r4, #2388]
	cmp	r3, #0
	beq	.L362
	ldr	r3, [r3, #32]
	cmp	r3, #0
	addne	r1, r4, #2384
	movne	r2, #0
	addne	r1, r1, #4
	bne	.L279
	b	.L448
.L280:
	ldr	r3, [r1, #4]!
	cmp	r3, #0
	beq	.L275
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L276
.L279:
	add	r2, r2, #1
	cmp	r2, ip
	bne	.L280
.L274:
	ldr	r0, [r4, #208]
	ldr	r3, [r4, #144]
	cmp	r0, r3
	bcs	.L449
	add	r3, r4, #53248
	str	r3, [fp, #-320]
	mov	r6, #1360
	ldr	ip, .L458
	ldr	r3, [r3, #3248]
	mov	r2, r6
	mov	r1, #0
	ldr	r7, [ip, #48]
	mla	r3, r6, r0, r3
	mov	r0, r3
	str	r3, [fp, #-296]
	blx	r7
	ldr	r3, .L458
	mov	r2, #64
	mov	r1, #0
	sub	r0, fp, #288
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #208]
	ldr	r2, [r4, #144]
	add	r3, r3, #1
	str	r3, [r4, #208]
	cmp	r3, r2
	ldrcc	r2, [fp, #-320]
	movcs	r3, #0
	ldrcc	r2, [r2, #3248]
	mlacc	r3, r6, r3, r2
	ldr	r2, [fp, #-296]
	str	r3, [r2, #1356]
	ldr	r3, [r4, #216]
	ldr	r0, [r5, #2652]
	add	r1, r3, #14080
	add	r2, r3, #1
	add	r1, r1, #46
	str	r0, [r4, r1, asl #2]
	ldr	r3, [r4, #172]
	str	r2, [r4, #216]
	ldr	r2, [fp, #-320]
	add	r3, r3, #1
	str	r3, [r4, #172]
	mov	r0, r3, asl #5
	ldr	r1, [r5, #2636]
	ldr	r2, [r2, #4056]
	sub	r3, r0, r3, asl #2
	str	r3, [fp, #-332]
	add	r3, r2, r3
	str	r1, [r3, #8]
	ldr	r2, [r4, #2316]
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	cmp	r1, #1
	cmpls	r1, r3
	bcs	.L283
	ldr	r3, [fp, #-296]
	add	r0, r3, r1, lsl #2
.L284:
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r1, r1, #1
	add	r2, r2, r3
	ldr	r2, [r2, #60]
	str	r2, [r0, #8]
	ldr	r2, [r4, #2316]
	add	r2, r2, r3
	ldr	r2, [r2, #56]
	str	r2, [r0], #4
	ldr	r2, [r4, #2316]
	add	r3, r2, r3
	ldr	r3, [r3, #64]
	str	r3, [r0, #12]
	ldr	r2, [r4, #2316]
	ldr	r3, [r2, #8]
	cmp	r3, r1
	movhi	ip, #1
	movls	ip, #0
	cmp	r1, #1
	movhi	ip, #0
	cmp	ip, #0
	bne	.L284
.L283:
	cmp	r3, #1
	bhi	.L289
	ldr	r2, [fp, #-296]
	add	r3, r2, r3, lsl #2
	add	r1, r2, #8
	mov	r2, #0
.L288:
	str	r2, [r3, #8]
	str	r2, [r3], #4
	cmp	r3, r1
	str	r2, [r3, #12]
	bne	.L288
.L289:
	ldrb	r3, [r5, #2579]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L450
.L287:
	add	r3, r4, #45056
	str	r3, [fp, #-300]
	mov	r8, r3
	ldr	r3, [r3, #2372]
	cmp	r3, #0
	beq	.L290
	ldr	r3, [fp, #-296]
	add	ip, r4, #2304
	add	ip, ip, #12
	mov	r1, #0
	add	r7, r3, #112
	add	r6, r3, #368
	mov	lr, ip
.L291:
	ldr	r0, [lr, #4]!
	sub	r9, fp, #44
	add	r1, r1, #1
	ldr	r2, [r0, #32]
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #28]
	add	r3, r3, #13184
	add	r3, r3, #16
	add	r2, r9, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #8]
	str	r3, [r2, #-244]
	ldr	r3, [r0, #16]
	str	r3, [r7, #4]!
	ldr	r3, [ip, #4]!
	ldr	r3, [r3, #32]
	ldr	r3, [r3, #28]
	str	r3, [r6, #4]!
	ldr	r3, [r8, #2372]
	cmp	r3, r1
	bhi	.L291
	ldr	r2, [fp, #-300]
	ldr	r2, [r2, #2376]
	cmp	r2, #0
	beq	.L292
.L357:
	ldr	r3, [fp, #-296]
	add	ip, r4, #2384
	ldr	r8, [fp, #-300]
	mov	r1, #0
	add	r7, r3, #176
	add	r6, r3, #432
	mov	lr, ip
.L293:
	ldr	r0, [lr, #4]!
	sub	r9, fp, #44
	add	r1, r1, #1
	ldr	r2, [r0, #32]
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #28]
	add	r3, r3, #13184
	add	r3, r3, #16
	add	r2, r9, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #8]
	str	r3, [r2, #-244]
	ldr	r3, [r0, #16]
	str	r3, [r7, #4]!
	ldr	r3, [ip, #4]!
	ldr	r3, [r3, #32]
	ldr	r3, [r3, #28]
	str	r3, [r6, #4]!
	ldr	r2, [r8, #2376]
	cmp	r2, r1
	bhi	.L293
	ldr	r3, [fp, #-300]
	ldr	r3, [r3, #2372]
.L292:
	cmp	r3, #0
	beq	.L294
	ldr	r0, [fp, #-296]
	ldr	lr, [r5, #2024]
	ldr	r1, [r0, #372]
	add	r1, r1, #728
	add	r1, r1, #2
	ldr	r1, [r4, r1, asl #2]
	cmp	lr, r1
	blt	.L369
	add	ip, r0, #372
	mov	r0, #0
	b	.L296
.L297:
	ldr	r1, [ip, #4]!
	add	r1, r1, #728
	add	r1, r1, #2
	ldr	r1, [r4, r1, asl #2]
	cmp	r1, lr
	bgt	.L369
.L296:
	add	r0, r0, #1
	cmp	r0, r3
	bne	.L297
.L294:
	ldr	r3, [fp, #-300]
	ldr	r1, [r3, #2272]
	cmp	r1, #0
	bne	.L434
	cmp	r2, #0
	beq	.L434
	ldr	ip, [fp, #-296]
	ldr	r0, [r5, #2024]
	ldr	r3, [ip, #436]
	add	r3, r3, #728
	add	r3, r3, #2
	ldr	r3, [r4, r3, asl #2]
	cmp	r0, r3
	blt	.L295
	add	ip, ip, #436
	b	.L298
.L299:
	ldr	r3, [ip, #4]!
	add	r3, r3, #728
	add	r3, r3, #2
	ldr	r3, [r4, r3, asl #2]
	cmp	r3, r0
	bgt	.L369
.L298:
	add	r1, r1, #1
	cmp	r1, r2
	bne	.L299
.L434:
	mov	r1, #1
.L295:
	ldr	r2, [fp, #-296]
	strb	r1, [r2, #24]
	ldr	r1, [fp, #-300]
	ldrb	r3, [r5, #2579]	@ zero_extendqisi2
	strb	r3, [r2, #25]
	ldr	r3, [r1, #2268]
	str	r3, [r2, #28]
	ldrb	r3, [r1, #2222]	@ zero_extendqisi2
	strb	r3, [r2, #32]
	ldr	r3, [r1, #2292]
	str	r3, [r2, #36]
	ldr	r3, [r1, #2272]
	cmp	r3, #0
	beq	.L451
	cmp	r3, #1
	movne	r3, #0
	strne	r3, [fp, #-324]
	beq	.L301
.L302:
	ldr	r2, [fp, #-296]
	ldr	r1, [fp, #-324]
	ldr	r6, [fp, #-296]
	str	r1, [r2, #40]
	ldr	r1, [fp, #-300]
	ldr	r3, [r1, #2324]
	str	r3, [r2, #48]
	ldrb	r3, [r1, #2223]	@ zero_extendqisi2
	strb	r3, [r2, #52]
	ldr	r3, [r1, #2328]
	str	r3, [r2, #44]
	ldr	r3, [r1, #2380]
	ldr	r1, [fp, #-300]
	cmp	r3, #0
	subne	r3, r3, #1
	ldreq	r2, [fp, #-296]
	str	r3, [r2, #60]
	ldr	r3, [fp, #-300]
	ldr	r2, [fp, #-296]
	ldr	r3, [r3, #2384]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r2, #56]
	ldrb	r3, [r1, #2219]	@ zero_extendqisi2
	add	r2, r4, #24576
	str	r2, [fp, #-328]
	mov	r7, r2
	strb	r3, [r6, #64]
	ldrb	r3, [r1, #2221]	@ zero_extendqisi2
	strb	r3, [r6, #65]
	ldr	r3, [r1, #2372]
	str	r3, [r6, #68]
	ldr	r3, [r1, #2376]
	str	r3, [r6, #72]
	ldr	r3, [r1, #2272]
	str	r3, [r6, #76]
	ldr	r3, [r5, #2656]
	str	r3, [r6, #80]
	ldr	r3, [r7, #2604]
	ldr	r0, [r5, #2656]
	ldr	r1, [r3, #240]
	bl	__aeabi_uidivmod
	str	r1, [r6, #84]
	ldr	r3, [r7, #2604]
	ldr	r0, [r5, #2656]
	ldr	r1, [r3, #240]
	bl	__aeabi_uidiv
	mov	r2, r7
	str	r0, [r6, #88]
	ldr	ip, [r7, #2608]
	ldr	r3, [r2, #2604]
	ldr	r7, [r5, #2656]
	ldrb	r2, [ip, #13]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L307
	ldr	r2, [ip, #72]
	ldr	r6, [ip, #68]
	cmp	r2, #0
	ldr	r9, [r3, #72]
	str	r2, [fp, #-304]
	sub	r2, r2, #1
	ldr	lr, [r3, #148]
	str	r2, [fp, #-312]
	sub	r2, r6, #1
	ldrb	r10, [ip, #15]	@ zero_extendqisi2
	str	r2, [fp, #-308]
	ble	.L312
	ldr	r3, [fp, #-304]
	add	r2, ip, #214
	sub	r1, fp, #216
	add	r0, r3, #107
	add	r0, ip, r0, lsl #1
.L311:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L311
.L312:
	cmp	r6, #0
	ble	.L310
	add	r3, r6, #87
	add	r2, ip, #174
	sub	r1, fp, #128
	add	ip, ip, r3, lsl #1
.L315:
	ldrsh	r3, [r2, #2]!
	cmp	r2, ip
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L315
.L310:
	mov	r5, #1
	mov	r0, r9
	mov	r5, r5, asl lr
	mov	r1, r5
	bl	__aeabi_idiv
	mov	r1, r5
	mov	r8, r0
	mov	r0, r9
	bl	__aeabi_idivmod
	mov	r0, r7
	cmp	r1, #0
	addne	r8, r8, #1
	mov	r1, r8
	bl	__aeabi_idivmod
	mov	r0, r7
	mov	r5, r1
	mov	r1, r8
	bl	__aeabi_idiv
	cmp	r10, #0
	beq	.L452
	ldr	r3, [fp, #-312]
	cmp	r3, #0
	mov	r3, #0
	blt	.L372
	sub	r2, fp, #212
	mov	ip, r3
	mov	r7, r3
	mov	r9, r3
	mov	r8, r2
	str	r3, [fp, #-316]
	str	r3, [fp, #-312]
	str	r4, [fp, #-336]
.L318:
	ldr	r2, [fp, #-308]
	cmp	r2, #0
	blt	.L375
	ldr	r9, [r8]
	mov	lr, #0
	ldr	r3, [fp, #-316]
	mov	r1, lr
	add	r9, r9, #1
	sub	r4, fp, #128
	mov	r7, ip
	add	r10, r3, r9
	b	.L321
.L373:
	mov	r7, ip
.L321:
	ldr	r3, [r4, #4]!
	add	r1, r1, #1
	add	r3, r3, #1
	add	r2, r3, lr
	cmp	r5, r2
	mla	ip, r9, r3, ip
	bge	.L319
	cmp	r0, r10
	blt	.L432
.L319:
	cmp	r1, r6
	mov	lr, r2
	bne	.L373
.L324:
	add	r1, r2, r3
	cmp	r5, r1
	blt	.L453
.L374:
	ldr	r1, [fp, #-312]
	add	r8, r8, #4
	ldr	lr, [fp, #-304]
	add	r1, r1, #1
	str	r10, [fp, #-316]
	cmp	r1, lr
	str	r1, [fp, #-312]
	bne	.L318
.L435:
	rsb	r0, r10, r0
	ldr	r4, [fp, #-336]
	mul	r3, r0, r3
.L316:
	rsb	r2, r2, r5
	add	r3, r2, r3
	add	r7, r3, r7
.L307:
	ldr	r2, [fp, #-296]
	ldr	r1, [fp, #-300]
	str	r7, [r2, #92]
	ldr	r3, [r1, #2336]
	str	r3, [r2, #96]
	ldr	r3, [r1, #2340]
	str	r3, [r2, #100]
	ldr	r3, [r1, #2348]
	str	r3, [r2, #104]
	ldr	r3, [r1, #2344]
	str	r3, [r2, #108]
	ldrb	r3, [r1, #2218]	@ zero_extendqisi2
	strb	r3, [r2, #112]
	ldrb	r3, [r1, #2217]	@ zero_extendqisi2
	strb	r3, [r2, #113]
	ldrb	r3, [r1, #2225]	@ zero_extendqisi2
	strb	r3, [r2, #114]
	ldrb	r3, [r1, #2226]	@ zero_extendqisi2
	strb	r3, [r2, #115]
	ldr	r3, [fp, #-328]
	ldr	r3, [r3, #2608]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L331
	ldr	r2, [r1, #2272]
	cmp	r2, #1
	beq	.L332
.L331:
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L454
.L436:
	add	r5, r4, #49152
.L334:
	ldr	r3, [fp, #-300]
	ldrb	r3, [r3, #2219]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L336
	ldr	r2, [fp, #-324]
	sub	r3, fp, #44
	add	r3, r3, r2, lsl #2
	ldr	r2, [fp, #-296]
	ldr	r3, [r3, #-244]
	str	r3, [r2, #564]
.L336:
	ldr	r3, [fp, #-320]
	mov	r1, #0
	ldr	r0, [fp, #-332]
	ldr	r2, [r4, #2316]
	ldr	r3, [r3, #4056]
	add	r3, r3, r0
	str	r2, [r3, #24]
	str	r1, [r4, #2316]
	ldrb	r0, [r5, #2421]	@ zero_extendqisi2
	cmp	r0, r1
	beq	.L426
	ldr	r0, [r4, #216]
	cmp	r0, #1
	beq	.L455
	ldr	lr, [fp, #-296]
	add	r1, r4, r0, lsl #3
	add	r1, r1, #54784
	add	r2, r0, #6848
	add	r2, r2, #11
	sub	r3, r0, #1
	ldr	ip, [lr, #92]
	add	r2, r4, r2, lsl #3
	sub	ip, ip, #1
	str	ip, [r1, #92]
	ldr	r1, [lr, #92]
	str	r1, [r2, #8]
.L338:
	ldr	r1, [r5, #2224]
	add	r3, r4, r3, lsl #3
	ldr	r2, [r5, #2220]
	add	r3, r3, #54784
	mla	r2, r1, r2, r2
	add	r2, r2, r1
	str	r2, [r3, #108]
	ldr	r3, [fp, #-296]
	ldr	r6, [r3, #92]
	sub	r6, r6, #1
	cmp	r6, #36864
	movcs	r0, #0
	bcs	.L426
	ldr	r3, [fp, #-328]
	ldr	r2, [r3, #2608]
	ldr	r1, [r3, #2604]
	ldrb	r3, [r2, #13]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L339
	ldr	r3, [r2, #72]
	ldr	r4, [r1, #72]
	cmp	r3, #0
	ldr	r1, [r1, #148]
	str	r3, [fp, #-300]
	ldr	r7, [r2, #68]
	ble	.L344
	ldr	r3, [fp, #-300]
	add	r0, r2, #214
	sub	ip, fp, #216
	add	lr, r3, #107
	add	lr, r2, lr, lsl #1
.L343:
	ldrsh	r3, [r0, #2]!
	cmp	r0, lr
	sub	r3, r3, #1
	str	r3, [ip, #4]!
	bne	.L343
.L344:
	cmp	r7, #0
	ble	.L342
	add	r3, r7, #87
	add	r0, r2, #174
	sub	ip, fp, #128
	add	r2, r2, r3, lsl #1
.L347:
	ldrsh	r3, [r0, #2]!
	cmp	r0, r2
	sub	r3, r3, #1
	str	r3, [ip, #4]!
	bne	.L347
.L342:
	mov	r5, #1
	mov	r0, r4
	mov	r5, r5, asl r1
	mov	r1, r5
	bl	__aeabi_idiv
	mov	r1, r5
	mov	r8, r0
	mov	r0, r4
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-300]
	cmp	r1, #0
	addne	r8, r8, #1
	cmp	r3, #0
	str	r8, [fp, #-308]
	ble	.L346
	mov	r10, #0
	ldr	r2, [fp, #-124]
	sub	r8, fp, #212
	mov	r9, r10
	mov	r3, r10
	mov	lr, r10
	mov	ip, r10
	mov	r4, r10
	add	r2, r2, #1
	str	r2, [fp, #-304]
.L348:
	cmp	r7, #0
	ble	.L384
	ldr	ip, [r8]
	ldr	r4, [fp, #-304]
	add	ip, ip, #1
	mla	r1, ip, r4, r3
	cmp	r6, r1
	blt	.L385
	mov	r5, #0
	mov	lr, r3
	mov	r2, r5
	mov	r3, r1
	sub	r0, fp, #124
	b	.L353
.L350:
	ldr	r4, [r0, #4]!
	mov	lr, r3
	add	r4, r4, #1
	mla	r1, ip, r4, r3
	cmp	r6, r1
	blt	.L351
	mov	r3, r1
.L353:
	add	r2, r2, #1
	add	r5, r5, r4
	cmp	r2, r7
	bne	.L350
.L352:
	cmp	r6, r3
	blt	.L383
	ldr	r2, [fp, #-300]
	add	r9, r9, #1
	add	r10, r10, ip
	add	r8, r8, #4
	cmp	r9, r2
	bne	.L348
.L383:
	mov	r3, lr
.L351:
	cmp	r4, #0
	beq	.L346
	rsb	r6, r3, r6
	mov	r1, r4
	mov	r0, r6
	bl	__aeabi_idivmod
	mov	r0, r6
	add	r6, r1, r5
	mov	r1, r4
	bl	__aeabi_idiv
	ldr	r3, [fp, #-308]
	add	r0, r10, r0
	mla	r6, r0, r3, r6
.L339:
	ldr	r3, [fp, #-296]
	mov	r0, #0
	str	r6, [r3, #568]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L360:
	mov	r2, r3
.L268:
	ldr	r3, .L458
	mov	r0, #0
	ldr	r1, .L458+4
	ldr	r3, [r3, #68]
	blx	r3
.L265:
	ldr	r1, [r4, #208]
	mvn	r0, #0
	ldr	r2, [r4, #172]
.L437:
	ldr	r3, [r4, #216]
	add	r1, r1, r0
	add	r2, r2, r0
	str	r1, [r4, #208]
	add	r3, r3, r0
	str	r2, [r4, #172]
	str	r3, [r4, #216]
.L426:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L447:
	mov	r2, r3
.L269:
	ldr	r3, .L458
	mov	r0, #0
	ldr	r1, .L458+8
	ldr	r3, [r3, #68]
	blx	r3
	b	.L265
.L432:
	ldr	r4, [fp, #-336]
.L359:
	ldr	r2, [fp, #-316]
	rsb	r0, r2, r0
	mov	r2, lr
	mul	r3, r0, r3
	b	.L316
.L453:
	cmp	r0, r10
	bge	.L374
.L438:
	ldr	r4, [fp, #-336]
	mov	lr, r2
	b	.L359
.L369:
	mov	r1, #0
	b	.L295
.L451:
	ldrb	r3, [r1, #2223]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L301
	ldr	r3, [r1, #2324]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #436]
	str	r3, [fp, #-324]
	b	.L302
.L301:
	ldr	r3, [fp, #-300]
	ldr	r2, [fp, #-296]
	ldr	r3, [r3, #2324]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #372]
	str	r3, [fp, #-324]
	b	.L302
.L452:
	ldr	r3, [fp, #-312]
	cmp	r3, #0
	mov	r3, r10
	blt	.L372
	sub	r2, fp, #212
	str	r10, [fp, #-316]
	str	r10, [fp, #-312]
	mov	ip, r10
	mov	r8, r2
	ldr	r2, [fp, #-308]
	mov	r7, r10
	mov	r9, r10
	cmp	r2, #0
	str	r4, [fp, #-336]
	blt	.L378
.L457:
	ldr	r9, [r8]
	mov	lr, #0
	ldr	r3, [fp, #-316]
	mov	r1, lr
	add	r9, r9, #1
	sub	r4, fp, #128
	mov	r7, ip
	add	r10, r3, r9
	b	.L327
.L376:
	mov	r7, ip
.L327:
	ldr	r3, [r4, #4]!
	add	r1, r1, #1
	add	r3, r3, #1
	add	r2, r3, lr
	cmp	r5, r2
	mla	ip, r9, r3, ip
	bge	.L325
	cmp	r0, r10
	blt	.L432
.L325:
	cmp	r1, r6
	mov	lr, r2
	bne	.L376
	add	r1, r2, r3
	cmp	r5, r1
	blt	.L456
.L377:
	ldr	r1, [fp, #-312]
	add	r8, r8, #4
	ldr	lr, [fp, #-304]
	add	r1, r1, #1
	str	r10, [fp, #-316]
	cmp	r1, lr
	str	r1, [fp, #-312]
	beq	.L435
	ldr	r2, [fp, #-308]
	cmp	r2, #0
	bge	.L457
.L378:
	ldr	r2, [fp, #-316]
	add	r10, r2, r9
	mov	r2, #0
	add	r1, r2, r3
	cmp	r5, r1
	bge	.L377
.L456:
	cmp	r0, r10
	bge	.L377
	b	.L438
.L450:
	ldr	r3, .L458
	add	r1, r4, #43520
	add	r0, r4, #47104
	add	r1, r1, #16
	movw	r2, #3732
	add	r0, r0, #164
	ldr	r3, [r3, #52]
	blx	r3
	b	.L287
.L454:
	ldr	r3, [fp, #-300]
	ldr	r3, [r3, #2272]
	cmp	r3, #0
	bne	.L436
.L332:
	ldr	r8, [fp, #-300]
	add	r5, r4, #49152
	ldr	r7, [fp, #-296]
	add	r1, r4, #49664
	ldr	r3, .L458
	add	r1, r1, #232
	ldr	r0, [r8, #3804]
	mov	r2, #64
	ldr	r6, .L458
	ldr	r3, [r3, #52]
	str	r0, [r7, #580]
	add	r0, r7, #588
	ldr	ip, [r5, #740]
	str	ip, [r7, #584]
	blx	r3
	add	r1, r4, #48896
	add	r1, r1, #164
	ldr	r3, [r6, #52]
	mov	r2, #64
	add	r0, r7, #716
	blx	r3
	add	r1, r4, #49920
	add	r1, r1, #40
	ldr	r3, [r6, #52]
	mov	r2, #128
	add	r0, r7, #844
	blx	r3
	add	r1, r4, #49920
	add	r0, r7, #1088
	ldr	r3, [r6, #52]
	add	r1, r1, #168
	add	r0, r0, #12
	mov	r2, #128
	blx	r3
	ldr	r3, [r8, #2272]
	cmp	r3, #0
	bne	.L334
	ldr	r7, [fp, #-296]
	add	r1, r4, #50176
	ldr	r3, [r6, #52]
	add	r1, r1, #40
	mov	r2, #64
	add	r0, r7, #652
	blx	r3
	add	r1, r4, #49408
	ldr	r3, [r6, #52]
	add	r1, r1, #164
	mov	r2, #64
	add	r0, r7, #780
	blx	r3
	add	r1, r4, #50176
	ldr	r3, [r6, #52]
	add	r1, r1, #104
	mov	r2, #128
	add	r0, r7, #972
	blx	r3
	add	r1, r4, #50176
	add	r0, r7, #1216
	ldr	r3, [r6, #52]
	add	r1, r1, #232
	mov	r2, #128
	add	r0, r0, #12
	blx	r3
	b	.L334
.L375:
	ldr	r2, [fp, #-316]
	add	r10, r2, r9
	mov	r2, #0
	b	.L324
.L455:
	ldr	r3, [fp, #-296]
	ldr	r2, [r3, #92]
	mov	r3, r1
	ldr	r1, [fp, #-320]
	str	r2, [r1, #1640]
	b	.L338
.L448:
	mov	r2, r3
.L276:
	ldr	r3, .L458
	mov	r0, #0
	ldr	r1, .L458+12
	ldr	r3, [r3, #68]
	blx	r3
	b	.L265
.L362:
	mov	r2, r3
.L275:
	ldr	r3, .L458
	mov	r0, #0
	ldr	r1, .L458+16
	ldr	r3, [r3, #68]
	blx	r3
	b	.L265
.L290:
	ldr	r3, [fp, #-300]
	ldr	r3, [r3, #2376]
	cmp	r3, #0
	bne	.L357
	b	.L434
.L384:
	mov	r5, #0
	b	.L352
.L385:
	ldr	r4, [fp, #-304]
	mov	r5, #0
	b	.L351
.L449:
	ldr	ip, .L458
	mov	r2, r0
	ldr	r1, .L458+20
	mov	r0, #1
	ldr	r5, [ip, #68]
	blx	r5
	ldr	r1, [r4, #208]
	ldr	r2, [r4, #172]
	mvn	r0, #0
	b	.L437
.L372:
	mov	r2, r3
	mov	r7, r3
	b	.L316
.L446:
	ldr	ip, .L458
	mov	r2, r0
	mov	r3, #17
	ldr	r1, .L458+24
	mov	r0, #0
	ldr	r5, [ip, #68]
	blx	r5
	b	.L265
.L266:
	ldr	lr, .L458
	mov	r2, ip
	mov	r3, #17
	ldr	r1, .L458+28
	mov	r0, #0
	ldr	r5, [lr, #68]
	blx	r5
	b	.L265
.L445:
	ldr	ip, .L458
	movw	r3, #6401
	ldr	r2, .L458+32
	mov	r0, #1
	ldr	r1, .L458+36
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L426
.L346:
	ldr	r3, .L458
	mov	r0, #1
	ldr	r1, .L458+40
	mvn	r6, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L339
.L459:
	.align	2
.L458:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	.LC48
	.word	.LC50
	.word	.LC49
	.word	.LC51
	.word	.LC45
	.word	.LC46
	.word	.LANCHOR0+100
	.word	.LC35
	.word	.LC52
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
	.global	HEVC_DecList
	.type	HEVC_DecList, %function
HEVC_DecList:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #164)
	sub	sp, sp, #164
	subs	r9, r0, #0
	beq	.L551
	add	r3, r9, #40960
	str	r3, [fp, #-192]
	ldr	r3, [r3, #2636]
	cmp	r3, #2
	beq	.L552
	ldr	r3, .L559
	mov	r2, #136
	mov	r1, #0
	sub	r0, fp, #180
	ldr	r3, [r3, #48]
	blx	r3
	ldr	ip, [r9, #2504]
	cmp	ip, #0
	beq	.L516
	mov	r4, #0
	add	r1, r9, #2576
	mov	r3, r4
	b	.L468
.L467:
	cmp	r3, ip
	beq	.L466
.L468:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #1
	bne	.L467
	ldr	r0, [r2, #52]
	cmp	r0, #0
	bne	.L467
	ldr	r0, [r2, #56]
	cmp	r0, #1
	subeq	r0, fp, #44
	addeq	r2, r2, #36
	addeq	r0, r0, r4, lsl #2
	addeq	r4, r4, #1
	streq	r2, [r0, #-136]
	cmp	r3, ip
	bne	.L468
.L466:
	ldr	ip, [r9, #2508]
	cmp	ip, #0
	beq	.L517
	add	r1, r9, #2640
	mov	r5, r4
	add	r1, r1, #4
	mov	r3, #0
	b	.L471
.L470:
	cmp	r3, ip
	beq	.L553
.L471:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #1
	bne	.L470
	ldr	r0, [r2, #52]
	cmp	r0, #0
	bne	.L470
	ldr	r0, [r2, #56]
	cmp	r0, #1
	subeq	r0, fp, #44
	addeq	r2, r2, #36
	addeq	r0, r0, r5, lsl #2
	addeq	r5, r5, #1
	streq	r2, [r0, #-136]
	cmp	r3, ip
	bne	.L471
.L553:
	rsb	ip, r4, r5
.L469:
	ldr	lr, [r9, #2500]
	cmp	lr, #0
	beq	.L518
	add	r0, r9, #2704
	mov	r3, r5
	add	r0, r0, #8
	mov	r2, #0
	b	.L474
.L473:
	cmp	r2, lr
	beq	.L554
.L474:
	ldr	r1, [r0, #4]!
	add	r2, r2, #1
	ldrb	r6, [r1, #1]	@ zero_extendqisi2
	cmp	r6, #1
	bne	.L473
	ldr	r6, [r1, #52]
	cmp	r6, #1
	bne	.L473
	ldr	r6, [r1, #56]
	sub	r7, fp, #44
	add	r7, r7, r3, lsl #2
	add	r1, r1, #36
	cmp	r6, #0
	addeq	r3, r3, #1
	streq	r1, [r7, #-136]
	cmp	r2, lr
	bne	.L474
.L554:
	rsb	lr, r4, r3
	rsb	lr, ip, lr
.L472:
	cmp	r3, #0
	ldr	r2, [fp, #-192]
	beq	.L555
	ldr	r2, [r2, #2636]
	cmp	r2, #0
	str	r2, [fp, #-184]
	bne	.L478
	cmp	ip, #0
	beq	.L479
	sub	r2, fp, #180
	sub	r1, fp, #116
	add	r0, r2, r4, lsl #2
	ldr	r2, [fp, #-184]
.L480:
	add	r2, r2, #1
	ldr	r6, [r0], #4
	cmp	r2, ip
	str	r6, [r1, #4]!
	bne	.L480
.L479:
	cmp	r4, #0
	beq	.L481
	add	r1, ip, #16
	sub	r0, fp, #180
	mov	r2, #0
	add	r1, r0, r1, lsl #2
.L482:
	add	r2, r2, #1
	ldr	r6, [r0], #4
	cmp	r2, r4
	str	r6, [r1, #4]!
	bne	.L482
	add	ip, ip, r2
.L481:
	cmp	lr, #0
	beq	.L483
	add	r1, ip, #16
	sub	r0, fp, #180
	sub	r2, fp, #180
	add	r1, r0, r1, lsl #2
	add	r5, r2, r5, lsl #2
	mov	r2, #0
.L484:
	add	r2, r2, #1
	ldr	r0, [r5], #4
	cmp	r2, lr
	str	r0, [r1, #4]!
	bne	.L484
.L483:
	ldr	r2, [fp, #-192]
	ldr	r4, [r2, #2744]
	ldr	r5, [r2, #2748]
	cmp	r4, #0
	str	r4, [r2, #2736]
	str	r5, [r2, #2740]
	bne	.L513
	b	.L488
.L552:
	ldr	r3, [fp, #-192]
	mov	r0, #0
	str	r0, [r3, #2736]
	str	r0, [r3, #2740]
.L547:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L478:
	ldr	r2, [fp, #-192]
	ldr	r4, [r2, #2744]
	ldr	r5, [r2, #2748]
	cmp	r4, #0
	str	r4, [r2, #2736]
	str	r5, [r2, #2740]
	beq	.L494
.L513:
	add	r2, r9, #45056
	add	r8, r9, #2304
	add	r7, r9, #46848
	add	r8, r8, #12
	ldrb	r10, [r2, #1952]	@ zero_extendqisi2
	add	r7, r7, #164
	str	r5, [fp, #-188]
	mov	r6, #0
	mov	r5, r10
	mov	r10, r4
	mov	r4, r3
.L487:
	cmp	r5, #0
	mov	r1, r4
	mov	r0, r6
	ldrne	r1, [r7]
	bne	.L486
	bl	__aeabi_uidivmod
.L486:
	sub	r3, fp, #44
	add	r6, r6, #1
	add	r1, r3, r1, lsl #2
	cmp	r6, r10
	add	r7, r7, #4
	ldr	r2, [r1, #-136]
	str	r2, [r8, #4]!
	bcc	.L487
	ldr	r2, [fp, #-184]
	mov	r3, r4
	ldr	r5, [fp, #-188]
	cmp	r2, #0
	bne	.L549
.L488:
	cmp	r5, #0
	beq	.L490
	add	r2, r9, #45056
	add	r6, r9, #47104
	add	r6, r6, #36
	add	r7, r9, #2384
	ldrb	r8, [r2, #1953]	@ zero_extendqisi2
	mov	r4, #0
	mov	r10, r3
.L493:
	cmp	r8, #0
	mov	r1, r10
	mov	r0, r4
	ldrne	r1, [r6]
	bne	.L492
	bl	__aeabi_uidivmod
.L492:
	sub	r3, fp, #44
	add	r4, r4, #1
	add	r1, r3, r1, lsl #2
	cmp	r4, r5
	add	r6, r6, #4
	ldr	r3, [r1, #-68]
	str	r3, [r7, #4]!
	bne	.L493
.L549:
	ldr	r3, [fp, #-192]
	ldr	r4, [r3, #2736]
	ldr	r5, [r3, #2740]
	ldr	r3, [r3, #2636]
	str	r3, [fp, #-184]
.L489:
	cmp	r4, #16
	bhi	.L497
.L494:
	add	r3, r4, #576
	add	r1, r9, #2384
	add	r3, r3, #3
	add	r3, r9, r3, lsl #2
.L496:
	ldr	r2, [r9, #2320]
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L496
.L497:
	cmp	r5, #16
	bhi	.L477
	add	r3, r5, #596
	add	r1, r9, #2448
	add	r1, r1, #4
	add	r3, r9, r3, lsl #2
.L498:
	ldr	r2, [r9, #2388]
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L498
.L477:
	ldr	r3, [fp, #-184]
	cmp	r3, #1
	beq	.L501
	cmp	r3, #2
	beq	.L521
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [fp, #-184]
	beq	.L501
	ldr	r2, .L559
	mov	r0, #1
	ldr	r3, [fp, #-184]
	ldr	r1, .L559+4
	ldr	r4, [r2, #68]
	ldr	r2, .L559+8
	blx	r4
.L500:
	ldr	r3, .L559
	mov	r0, #1
	ldr	r1, .L559+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L502:
	ldr	r3, [r9, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	bne	.L510
	mov	r3, #1
	str	r3, [r7]
	ldr	r3, [fp, #-192]
	ldr	r3, [r3, #2068]
	add	r3, r3, #36
	str	r3, [r8]
.L510:
	ldr	r3, [fp, #-184]
	add	r10, r10, #1
	add	r8, r8, #68
	cmp	r10, r3
	bcc	.L512
.L521:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L501:
	add	r3, r9, #43520
	add	r8, r9, #2320
	add	r3, r3, #172
	mov	r10, #0
	mov	r7, r3
.L512:
	ldr	r2, [r7, #4]!
	cmp	r2, #0
	beq	.L502
	ldr	r1, [r8]
	cmp	r1, #0
	bne	.L519
	mov	r0, r8
	mov	r3, r1
	b	.L504
.L506:
	ldr	r5, [r0, #4]!
	cmp	r5, #0
	bne	.L556
.L504:
	add	r3, r3, #1
	cmp	r3, r2
	bne	.L506
	mov	r3, #255
	str	r3, [fp, #-188]
.L505:
	ldr	r3, [r9, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	bne	.L507
	ldr	r3, [fp, #-192]
	ldr	r5, [r3, #2068]
	add	r5, r5, #36
.L503:
	mov	r3, r1
	mov	r6, r8
	mov	r4, #0
	b	.L515
.L509:
	ldr	r3, [r6, #4]!
.L515:
	cmp	r3, #0
	beq	.L557
.L508:
	add	r4, r4, #1
	cmp	r4, r2
	bcc	.L509
	b	.L510
.L557:
	ldr	r3, .L559
	mov	r0, #1
	ldrsb	r2, [fp, #-188]
	str	r4, [sp]
	ldr	r3, [r3, #68]
	ldr	r1, .L559+16
	str	r2, [sp, #4]
	mov	ip, r3
	ldr	r2, .L559+8
	mov	r3, r10
	blx	ip
	str	r5, [r6]
	ldr	r2, [r7]
	b	.L508
.L556:
	uxtb	r3, r3
	str	r3, [fp, #-188]
	cmp	r3, #255
	bne	.L503
	b	.L505
.L555:
	str	r3, [r2, #2736]
	mov	r1, r3
	str	r3, [r2, #2740]
	add	r0, r9, #2320
	ldr	r3, .L559
	mov	r2, #136
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r9, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	beq	.L558
	ldr	r3, [fp, #-192]
	ldr	r3, [r3, #2636]
	str	r3, [fp, #-184]
	b	.L477
.L519:
	mov	r3, #0
	mov	r5, r1
	str	r3, [fp, #-188]
	b	.L503
.L507:
	ldr	r2, .L559
	mov	r3, r10
	ldr	r1, .L559+20
	mov	r0, #1
	ldr	r4, [r2, #68]
	ldr	r2, .L559+8
	blx	r4
	b	.L500
.L516:
	mov	r4, ip
	b	.L466
.L517:
	mov	r5, r4
	b	.L469
.L518:
	mov	r3, r5
	b	.L472
.L558:
	ldr	r1, [fp, #-192]
	mov	r2, #1
	ldr	r3, [r1, #2068]
	str	r2, [r1, #2736]
	add	r3, r3, #36
	str	r3, [r9, #2320]
	ldr	r3, [r1, #2636]
	str	r3, [fp, #-184]
	b	.L477
.L490:
	ldr	r3, .L559
	add	r0, r9, #2384
	mov	r2, #68
	add	r0, r0, #4
	add	r1, r9, #2320
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [fp, #-192]
	ldr	r5, [r3, #2736]
	ldr	r2, [r3, #2636]
	str	r5, [r3, #2740]
	mov	r4, r5
	str	r2, [fp, #-184]
	b	.L489
.L551:
	ldr	ip, .L559
	movw	r3, #7532
	ldr	r2, .L559+24
	mov	r0, #1
	ldr	r1, .L559+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L547
.L560:
	.align	2
.L559:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC53
	.word	.LANCHOR0+136
	.word	.LC56
	.word	.LC55
	.word	.LC54
	.word	.LANCHOR0+120
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_DecList, .-HEVC_DecList
	.align	2
	.global	HEVC_RemoveApcStore
	.type	HEVC_RemoveApcStore, %function
HEVC_RemoveApcStore:
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
	subs	r4, r0, #0
	beq	.L567
	add	r5, r4, r1, lsl #2
	ldr	r2, [r5, #2512]
	ldr	r3, [r2, #28]
	cmp	r3, #16
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r3, r3, #696
	mov	ip, #0
	add	r3, r3, #2
	ldr	lr, .L568
	ldr	r1, .L568+4
	mov	r0, #13
	str	ip, [r4, r3, asl #2]
	ldr	r3, [r2, #28]
	ldr	r6, [lr, #68]
	add	r3, r3, #712
	add	r3, r3, #2
	str	ip, [r4, r3, asl #2]
	ldr	r3, [r2, #28]
	add	r3, r3, #728
	add	r3, r3, #2
	str	ip, [r4, r3, asl #2]
	ldr	r3, [r2, #24]
	add	r3, r3, #524
	add	r3, r4, r3, lsl #2
	str	ip, [r3, #4]
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #28]
	blx	r6
	ldr	r3, [r5, #2512]
	mov	r2, #16
	str	r2, [r3, #28]
	ldr	r3, [r4, #2788]
	sub	r3, r3, #1
	str	r3, [r4, #2788]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L567:
	ldr	ip, .L568
	movw	r3, #7893
	ldr	r2, .L568+8
	mov	r0, #1
	ldr	r1, .L568+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L569:
	.align	2
.L568:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC57
	.word	.LANCHOR0+152
	.word	.LC35
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
	subs	r6, r0, #0
	beq	.L571
	ldr	r2, [r6, #2492]
	cmp	r2, #0
	beq	.L579
	add	r5, r6, #2496
	mov	r4, #0
	add	r5, r5, #12
	b	.L575
.L574:
	add	r4, r4, #1
	cmp	r4, r2
	bcs	.L580
.L575:
	ldr	r3, [r5, #4]!
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L574
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_RemoveApcStore
	ldr	r2, [r6, #2492]
	add	r4, r4, #1
	cmp	r4, r2
	bcc	.L575
.L580:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L579:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L571:
	ldr	ip, .L581
	movw	r3, #7947
	ldr	r2, .L581+4
	mov	r0, #1
	ldr	r1, .L581+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L582:
	.align	2
.L581:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+172
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_RemoveUnusedApcStore, .-HEVC_RemoveUnusedApcStore
	.align	2
	.global	HEVC_ApplyReferencePictureSet
	.type	HEVC_ApplyReferencePictureSet, %function
HEVC_ApplyReferencePictureSet:
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
	subs	r9, r0, #0
	beq	.L621
	add	r3, r9, #40960
	ldr	r2, [r9, #2304]
	movw	r4, #2024
	str	r3, [fp, #-68]
	mov	r1, r3
	ldr	r3, [r9, #2300]
	ldr	r1, [r1, #2652]
	movw	ip, #15788
	ldr	lr, [r9, #2492]
	mov	r0, #1
	mla	r2, r4, r1, r2
	cmp	lr, #0
	ldr	r2, [r2, #32]
	mla	r3, ip, r2, r3
	ldr	r3, [r3, #128]
	mov	r3, r0, asl r3
	str	r3, [fp, #-48]
	beq	.L583
	add	r10, r9, #2512
	add	r7, r9, #45056
	add	r3, r9, #46848
	mov	r2, #0
	add	r3, r3, #28
	str	r2, [fp, #-60]
	str	r3, [fp, #-72]
	str	r0, [fp, #-64]
	str	r9, [fp, #-56]
.L602:
	ldr	r3, [r7, #1768]
	ldr	r1, [r7, #1764]
	ldr	r2, [r7, #1772]
	add	r3, r3, r1
	ldr	r5, [r10]
	cmp	r3, r2
	mov	r8, r3
	movcs	r4, #0
	ldrcs	r2, [r5, #12]
	bcs	.L588
	add	r6, r3, #11712
	ldr	r3, [fp, #-56]
	add	r6, r6, #24
	ldr	r9, [r5, #12]
	mov	r4, #0
	add	r6, r3, r6, lsl #2
.L594:
	ldr	r3, [r6, #-1884]
	cmp	r3, #0
	ldr	r3, [r5, #52]
	beq	.L589
	cmp	r3, #0
	beq	.L590
	ldr	r3, [r6]
	cmp	r3, r9
	beq	.L620
.L590:
	cmp	r4, #0
	bne	.L607
	ldr	r1, [r6]
	mov	r4, r9
	b	.L604
.L589:
	cmp	r3, #0
	beq	.L592
	ldr	r1, [fp, #-48]
	mov	r0, r9
	bl	__aeabi_idivmod
	ldr	r0, [r6]
	str	r1, [fp, #-52]
	ldr	r1, [fp, #-48]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-52]
	cmp	r3, r1
	beq	.L620
.L592:
	cmp	r4, #0
	bne	.L607
	ldr	r3, [r6]
	mov	r0, r9
	ldr	r1, [fp, #-48]
	str	r3, [fp, #-52]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-52]
	mov	r0, r3
	mov	r4, r1
	ldr	r1, [fp, #-48]
	bl	__aeabi_idivmod
.L604:
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	rsb	r4, r1, r4
	clz	r4, r4
	cmp	r3, #0
	mov	r4, r4, lsr #5
	moveq	r4, #0
	cmp	r4, #0
	bne	.L622
.L607:
	mov	r0, r9
.L593:
	ldr	r3, [r7, #1772]
	add	r8, r8, #1
	add	r6, r6, #4
	mov	r9, r0
	cmp	r8, r3
	bcc	.L594
	ldr	r3, [r7, #1768]
	mov	r2, r0
	ldr	r1, [r7, #1764]
	add	r3, r3, r1
.L588:
	cmp	r3, #0
	ldr	r3, [fp, #-68]
	ldrne	r8, [fp, #-72]
	movne	r6, #0
	ldr	r0, [r3, #2624]
	beq	.L596
.L598:
	ldr	r3, [r5, #52]
	add	r6, r6, #1
	cmp	r3, #0
	bne	.L597
	ldr	r3, [r8]
	add	r3, r0, r3
	cmp	r3, r2
	beq	.L623
.L597:
	ldr	r3, [r7, #1768]
	add	r8, r8, #4
	ldr	r1, [r7, #1764]
	add	r3, r3, r1
	cmp	r6, r3
	bcc	.L598
.L596:
	eor	r4, r4, #1
	cmp	r2, r0
	moveq	r2, #0
	andne	r2, r4, #1
	cmp	r2, #0
	beq	.L600
	mov	r3, #0
	strb	r3, [r5, #1]
	ldr	r3, [r10]
	mov	r2, #0
	str	r2, [r3, #52]
	ldr	r3, [r10]
	ldr	r2, [r3, #8]
	cmp	r2, #1
	beq	.L600
	ldr	r1, [r3, #32]
	mov	r2, #0
	ldr	r3, [fp, #-56]
	ldr	r0, [r3, #244]
	bl	FSP_SetRef
.L600:
	ldr	r3, [fp, #-56]
	add	r10, r10, #4
	ldr	r2, [fp, #-60]
	ldr	r3, [r3, #2492]
	add	r2, r2, #1
	str	r2, [fp, #-60]
	cmp	r2, r3
	bcc	.L602
.L583:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L622:
	ldr	r1, [fp, #-64]
	mov	r2, #1
	mov	r4, r2
	strb	r1, [r5, #1]
	ldr	r3, [r10]
	str	r1, [r3, #52]
	ldr	r3, [r10]
	str	r1, [r3, #4]
	ldr	r1, [fp, #-56]
	ldr	r3, [r10]
	ldr	r0, [r1, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldr	r5, [r10]
	ldr	r0, [r5, #12]
	b	.L593
.L620:
	ldr	r1, [fp, #-64]
	mov	r2, #1
	mov	r4, #1
	strb	r1, [r5, #1]
	ldr	r3, [r10]
	str	r1, [r3, #4]
	ldr	r1, [fp, #-56]
	ldr	r3, [r10]
	ldr	r0, [r1, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldr	r5, [r10]
	ldr	r0, [r5, #12]
	b	.L593
.L623:
	ldr	r1, [fp, #-64]
	mov	r2, #1
	mov	r4, r2
	strb	r1, [r5, #1]
	ldr	r3, [r10]
	str	r1, [r3, #4]
	ldr	r1, [fp, #-56]
	ldr	r3, [r10]
	ldr	r0, [r1, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldr	r5, [r10]
	ldr	r3, [fp, #-68]
	ldr	r2, [r5, #12]
	ldr	r0, [r3, #2624]
	b	.L597
.L621:
	ldr	ip, .L624
	movw	r3, #8009
	ldr	r2, .L624+4
	mov	r0, #1
	ldr	r1, .L624+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L625:
	.align	2
.L624:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+200
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_ApplyReferencePictureSet, .-HEVC_ApplyReferencePictureSet
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
	subs	r4, r0, #0
	beq	.L627
	add	r9, r4, #45056
	ldr	r1, [r9, #1764]
	cmp	r1, #0
	moveq	r6, r1
	moveq	r5, r1
	beq	.L629
	add	r8, r4, #46848
	mov	r6, #0
	add	r10, r4, #40960
	mov	r5, r6
	mov	r7, r8
	add	r8, r8, #8
	add	r7, r7, #28
.L636:
	ldrb	r3, [r8, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L630
	ldr	lr, [r4, #2492]
	ldr	ip, [r10, #2624]
	ldr	r3, [r7]
	cmp	lr, #0
	add	ip, ip, r3
	beq	.L630
	ldr	r1, [r4, #2512]
	ldr	r3, [r1, #12]
	cmp	r3, ip
	addne	r2, r4, #2512
	movne	r3, #0
	bne	.L633
	b	.L685
.L635:
	ldr	r1, [r2, #4]!
	ldr	r0, [r1, #12]
	cmp	r0, ip
	beq	.L631
.L633:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L635
.L630:
	ldr	r1, [r9, #1764]
	add	r5, r5, #1
	add	r7, r7, #4
	cmp	r1, r5
	bhi	.L636
.L629:
	ldr	r2, [r4, #2488]
	str	r6, [r4, #2504]
	cmp	r2, r6
	addhi	r3, r6, #644
	movhi	r0, #0
	addhi	r3, r4, r3, lsl #2
	bls	.L641
.L640:
	add	r6, r6, #1
	str	r0, [r3, #4]!
	cmp	r6, r2
	bne	.L640
.L641:
	ldr	r7, [r9, #1768]
	add	r7, r1, r7
	cmp	r7, r5
	movls	r6, #0
	bls	.L639
	add	r8, r5, #11712
	add	r9, r5, #46848
	add	r8, r8, #7
	add	r9, r9, #8
	add	r9, r4, r9
	add	r10, r4, #40960
	add	r8, r4, r8, lsl #2
	mov	r6, #0
.L648:
	ldrb	r3, [r9, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L642
	ldr	lr, [r4, #2492]
	ldr	ip, [r10, #2624]
	ldr	r3, [r8]
	cmp	lr, #0
	add	ip, ip, r3
	beq	.L642
	ldr	r1, [r4, #2512]
	ldr	r3, [r1, #12]
	cmp	r3, ip
	addne	r2, r4, #2512
	movne	r3, #0
	bne	.L645
	b	.L686
.L647:
	ldr	r1, [r2, #4]!
	ldr	r0, [r1, #12]
	cmp	r0, ip
	beq	.L643
.L645:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L647
.L642:
	add	r5, r5, #1
	add	r8, r8, #4
	cmp	r7, r5
	bhi	.L648
.L689:
	ldr	r2, [r4, #2488]
.L639:
	cmp	r2, r6
	str	r6, [r4, #2508]
	bls	.L626
	add	r1, r6, #660
	mov	r3, #0
	add	r1, r1, #1
	add	r4, r4, r1, lsl #2
.L651:
	add	r6, r6, #1
	str	r3, [r4, #4]!
	cmp	r6, r2
	bne	.L651
.L626:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L685:
	mov	r3, #0
.L631:
	add	r3, r4, r3, lsl #2
	mov	r2, #1
	strb	r2, [r1, #1]
	ldr	r1, [r3, #2512]
	ldrb	r0, [r1, #1]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L687
.L634:
	mov	r2, #1
	str	r2, [r1, #56]
	ldr	r1, [r3, #2512]
	mov	r0, #0
	add	r2, r4, r6, lsl #2
	add	r6, r6, #1
	str	r0, [r1, #52]
	ldr	r3, [r3, #2512]
	str	r3, [r2, #2580]
	b	.L630
.L686:
	mov	r3, #0
.L643:
	add	r3, r4, r3, lsl #2
	mov	r2, #1
	strb	r2, [r1, #1]
	ldr	r1, [r3, #2512]
	ldrb	r0, [r1, #1]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L688
.L646:
	mov	r2, #1
	str	r2, [r1, #56]
	ldr	r1, [r3, #2512]
	add	r2, r6, #660
	mov	r0, #0
	add	r5, r5, #1
	add	r2, r2, #2
	cmp	r7, r5
	str	r0, [r1, #52]
	add	r6, r6, #1
	ldr	r3, [r3, #2512]
	add	r8, r8, #4
	str	r3, [r4, r2, asl #2]
	bhi	.L648
	b	.L689
.L687:
	ldr	r1, [r1, #32]
	ldr	r0, [r4, #244]
	str	r3, [fp, #-48]
	bl	FSP_SetRef
	ldr	r3, [fp, #-48]
	ldr	r1, [r3, #2512]
	b	.L634
.L688:
	ldr	r1, [r1, #32]
	ldr	r0, [r4, #244]
	str	r3, [fp, #-48]
	bl	FSP_SetRef
	ldr	r3, [fp, #-48]
	ldr	r1, [r3, #2512]
	b	.L646
.L627:
	ldr	ip, .L690
	movw	r3, #8652
	ldr	r2, .L690+4
	mov	r0, #1
	ldr	r1, .L690+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L691:
	.align	2
.L690:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+232
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_UpdateReflist, .-HEVC_UpdateReflist
	.align	2
	.global	HEVC_UpdateLTReflist
	.type	HEVC_UpdateLTReflist, %function
HEVC_UpdateLTReflist:
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
	cmp	r0, #0
	beq	.L712
	add	r3, r0, #40960
	ldr	r2, [r0, #2304]
	movw	ip, #2024
	add	r10, r0, #45056
	ldr	r3, [r3, #2652]
	movw	r4, #15788
	ldr	lr, [r0, #2300]
	mov	r1, #1
	mla	ip, ip, r3, r2
	ldr	r3, [r10, #1764]
	ldr	r2, [r10, #1768]
	add	r2, r3, r2
	ldr	r3, [r10, #1772]
	sub	r2, r2, #1
	ldr	ip, [ip, #32]
	sub	r9, r3, #1
	cmp	r9, r2
	mla	r2, r4, ip, lr
	ldr	r8, [r2, #128]
	mov	r8, r1, asl r8
	ble	.L705
	add	r7, r3, #11712
	add	r3, r3, #46848
	add	r7, r7, #23
	add	r3, r3, #9
	add	r3, r0, r3
	sub	r8, r8, #1
	add	r7, r0, r7, lsl #2
	mov	r6, #0
	str	r6, [fp, #-48]
	mov	r6, r3
	str	r1, [fp, #-52]
.L700:
	ldrb	r3, [r6, #-1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L695
	ldrb	r4, [r7, #-1884]	@ zero_extendqisi2
	ldr	lr, [r7]
	ldr	r5, [r0, #2492]
	cmp	r4, #0
	andeq	lr, lr, r8
	cmp	r5, #0
	ble	.L695
	add	r1, r0, #2496
	mov	r3, #0
	add	r1, r1, #12
	b	.L699
.L698:
	add	r3, r3, #1
	cmp	r3, r5
	beq	.L695
.L699:
	ldr	ip, [r1, #4]!
	cmp	r4, #0
	ldr	r2, [ip, #12]
	andeq	r2, r2, r8
	cmp	lr, r2
	bne	.L698
	ldr	r1, [fp, #-48]
	add	r3, r0, r3, lsl #2
	ldr	lr, [fp, #-52]
	add	r2, r0, r1, lsl #2
	add	r1, r1, #1
	strb	lr, [ip, #1]
	mov	ip, #0
	str	r1, [fp, #-48]
	ldr	r1, [r3, #2512]
	str	ip, [r1, #56]
	ldr	r1, [r3, #2512]
	str	lr, [r1, #52]
	ldr	r3, [r3, #2512]
	str	r3, [r2, #2716]
.L695:
	ldr	r3, [r10, #1764]
	sub	r9, r9, #1
	ldr	r2, [r10, #1768]
	sub	r7, r7, #4
	add	r3, r3, r2
	sub	r3, r3, #1
	cmp	r3, r9
	blt	.L700
	ldr	r6, [fp, #-48]
	mov	r2, r6
.L694:
	ldr	r3, [r0, #2488]
	str	r2, [r0, #2500]
	cmp	r3, r6
	ble	.L692
	add	r1, r6, #676
	mov	r2, #0
	add	r1, r1, #2
	add	r0, r0, r1, lsl #2
.L703:
	add	r6, r6, #1
	str	r2, [r0, #4]!
	cmp	r6, r3
	bne	.L703
.L692:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L705:
	mov	r2, #0
	mov	r6, r2
	b	.L694
.L712:
	ldr	ip, .L713
	movw	r3, #8750
	ldr	r2, .L713+4
	mov	r0, #1
	ldr	r1, .L713+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L714:
	.align	2
.L713:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+252
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_UpdateLTReflist, .-HEVC_UpdateLTReflist
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
	subs	r6, r0, #0
	mov	r8, r1
	beq	.L726
	ldr	r0, [r6, #244]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L721
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	addne	r4, r0, #216
	addne	r5, r0, #232
	movne	r7, #0
	beq	.L727
.L720:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L719
	ldr	r0, [r6, #244]
	bl	FreeUsdByDec
	str	r7, [r4]
.L719:
	cmp	r4, r5
	bne	.L720
	ldr	r0, [r6, #244]
	mov	r1, r8
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L727:
	ldr	r3, .L728
	mov	r0, #1
	ldr	r1, .L728+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L721:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L726:
	ldr	ip, .L728
	movw	r3, #9072
	ldr	r2, .L728+8
	mov	r0, #1
	ldr	r1, .L728+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L729:
	.align	2
.L728:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC58
	.word	.LANCHOR0+276
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_DECRecycleImage, .-HEVC_DECRecycleImage
	.align	2
	.global	HEVC_CheckFrameStore
	.type	HEVC_CheckFrameStore, %function
HEVC_CheckFrameStore:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r1
	beq	.L751
	ldr	r0, [r0, #244]
	ldr	r1, [r1, #32]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L733
	ldrsb	r2, [r0, #1]
	cmp	r2, #3
	cmpne	r2, #0
	moveq	r0, #1
	movne	r0, #0
	beq	.L752
	ldr	r3, [r4, #8]
	cmp	r3, #1
	beq	.L738
	ldr	r2, [r4, #4]
	ldrb	r1, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L737
	cmp	r1, #1
	beq	.L737
.L748:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L752:
	ldr	r5, .L753
	mov	r0, #13
	ldr	r3, [r4, #32]
	ldr	r1, .L753+4
	str	r2, [sp]
	ldr	r2, .L753+8
	ldr	r6, [r5, #68]
	blx	r6
.L735:
	ldr	r3, [r4, #8]
	cmp	r3, #1
	beq	.L738
	ldr	r5, [r5, #68]
	mov	r0, #1
	ldr	r3, [r4, #12]
	ldr	r2, .L753+8
	ldr	r1, .L753+12
	blx	r5
	mvn	r0, #2
	b	.L748
.L733:
	ldr	r1, [r4, #32]
	mov	r2, r4
	ldr	r3, [r4, #12]
	mov	r0, #1
	ldr	r5, .L753
	str	r1, [sp, #4]
	ldr	ip, [r4, #8]
	ldr	r6, [r5, #68]
	ldr	r1, .L753+16
	str	ip, [sp]
	blx	r6
	b	.L735
.L751:
	ldr	ip, .L753
	movw	r3, #9182
	ldr	r2, .L753+8
	mov	r0, #1
	ldr	r1, .L753+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L748
.L737:
	ldr	ip, .L753
	mov	r3, r4
	str	r1, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	ldr	r1, .L753+24
	ldr	r4, [ip, #68]
	ldr	r2, .L753+8
	blx	r4
	mvn	r0, #0
	b	.L748
.L738:
	mov	r2, #1
	mov	r3, #2
	strb	r2, [r4, #2]
	mvn	r0, #2
	str	r3, [r4, #8]
	b	.L748
.L754:
	.align	2
.L753:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC59
	.word	.LANCHOR0+300
	.word	.LC61
	.word	.LC60
	.word	.LC35
	.word	.LC62
	UNWIND(.fnend)
	.size	HEVC_CheckFrameStore, .-HEVC_CheckFrameStore
	.align	2
	.global	HEVC_GetImagePara
	.type	HEVC_GetImagePara, %function
HEVC_GetImagePara:
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
	cmp	r0, #0
	cmpne	r1, #0
	mov	r4, r1
	ldr	r3, [r1, #16]
	moveq	ip, #1
	movne	ip, #0
	beq	.L775
	ldr	r2, [r1, #232]
	add	lr, r0, #24576
	mov	r1, #25600
	str	r1, [r4, #260]
	bic	r2, r2, #16128
	bic	r2, r2, #3
	str	r2, [r4, #232]
	ldr	r1, [lr, #2600]
	add	r1, r1, #12288
	ldr	r1, [r1, #180]
	bic	r1, r1, #-16777216
	bic	r1, r1, #255
	cmp	r1, #256
	beq	.L757
	mov	ip, #256
	movt	ip, 1
	cmp	r1, ip
	movne	ip, #1
	bne	.L757
	add	r1, r0, #4096
	ldr	ip, [r1, #408]
	subs	ip, ip, #1
	movne	ip, #1
.L757:
	ldr	r1, [lr, #2604]
	ldrb	r1, [r1, #2633]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r1, #3072
	bne	.L776
.L758:
	ldr	lr, [r4, #4]
	and	r3, r3, #3
	orr	r3, r2, r3
	cmp	lr, #0
	orr	r3, r3, #8192
	orr	r3, r3, r1
	ldr	r1, [r4, #32]
	orr	r3, r3, ip, asl #8
	str	r3, [r4, #232]
	ldrne	r3, [r4, #20]
	strne	r3, [r4, #272]
	ldr	r0, [r0, #244]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L778
	mov	r2, #504
	add	r1, r4, #72
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #17
	str	r3, [r5, #384]
	mov	r3, #1
	ldr	r2, [r4, #48]
	strb	r3, [r5, #379]
	cmp	r2, #0
	strb	r3, [r5, #377]
	moveq	r3, #0
	movne	r3, #4
	strb	r3, [r5, #372]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L776:
	ldr	r1, [r4, #576]
	cmp	r1, #1
	cmpne	r1, #11
	moveq	r1, #1024
	bne	.L777
	ldr	ip, [r4, #580]
	clz	ip, ip
	mov	ip, ip, lsr #5
	b	.L758
.L775:
	ldr	ip, .L778
	movw	r3, #9244
	ldr	r2, .L778+4
	mov	r0, #1
	ldr	r1, .L778+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L777:
	ldr	ip, [r4, #580]
	bic	r1, r1, #8
	cmp	r1, #2
	clz	ip, ip
	moveq	r1, #2048
	movne	r1, #3072
	mov	ip, ip, lsr #5
	b	.L758
.L779:
	.align	2
.L778:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+324
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_GetImagePara, .-HEVC_GetImagePara
	.align	2
	.type	HEVC_OutputCurrPic, %function
HEVC_OutputCurrPic:
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
	add	r6, r0, #40960
	add	r1, r0, #43008
	mov	r4, r0
	ldr	r5, [r6, #2068]
	mov	r2, #504
	ldr	r3, [r6, #2056]
	add	r1, r1, #24
	add	r0, r5, #72
	str	r3, [r5, #20]
	bl	memcpy
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_GetImagePara
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L802
	ldr	r2, [r5, #20]
	cmp	r2, #0
	str	r2, [r7, #200]
	bne	.L783
.L788:
	ldrb	r3, [r6, #2016]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L803
.L785:
	mov	r2, #1
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	add	r3, r4, #50944
	ldr	r0, [r4, #244]
	add	r3, r3, #56
	str	r7, [sp]
	mov	r2, r4
	mov	r1, #17
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L804
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r7, #84]
	bcs	.L805
.L792:
	ldr	r2, [r4, #268]
	mov	r0, #0
	ldr	r3, [r4, #260]
	add	r2, r2, #1
	str	r2, [r4, #268]
	add	r3, r3, #1
	str	r3, [r4, #260]
.L782:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L783:
	ldr	r8, [r6, #2028]
	cmp	r8, #0
	beq	.L806
.L786:
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #4]
	cmp	r3, r2
	bcs	.L788
	ldr	r0, [r4, #244]
	mov	r2, #0
	ldr	r1, [r5, #32]
	bl	FSP_SetDisplay
	ldr	r2, [r4, #2308]
	ldr	ip, .L807
	mov	r0, #1
	ldr	r3, [r7, #200]
	ldr	r1, [r2, #4]
	ldr	r4, [ip, #68]
	ldr	r2, .L807+4
	str	r1, [sp]
	ldr	r1, .L807+8
	blx	r4
	mvn	r0, #0
	b	.L782
.L803:
	mov	r2, #1
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetRef
	b	.L785
.L805:
	add	r1, r7, #84
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.isra.11.part.12
	b	.L792
.L806:
	ldr	r3, .L807
	mov	r0, #1
	ldr	r2, .L807+4
	ldr	r1, .L807+12
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, .L807+16
	ldr	r9, [r3]
	cmp	r9, #0
	beq	.L787
	mov	r3, r8
	mov	r2, r8
	mov	r1, #111
	ldr	r0, [r4, #244]
	blx	r9
.L787:
	ldr	r2, [r7, #200]
	cmp	r2, #0
	bne	.L786
	b	.L788
.L804:
	ldr	r3, .L807
	mov	r0, #1
	ldr	r2, .L807+4
	ldr	r1, .L807+20
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r0, [r4, #244]
	ldr	r1, [r5, #32]
	mov	r2, #0
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L782
.L802:
	ldr	r3, .L807
	ldr	r2, .L807+4
	ldr	r1, .L807+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L782
.L808:
	.align	2
.L807:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+344
	.word	.LC66
	.word	.LC64
	.word	g_event_report
	.word	.LC65
	.word	.LC63
	UNWIND(.fnend)
	.size	HEVC_OutputCurrPic, .-HEVC_OutputCurrPic
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
	subs	r6, r0, #0
	beq	.L825
	add	r0, r6, #57088
	mov	r3, #0
	add	r5, r6, #40960
	add	r0, r0, #224
	mov	lr, r3
	strb	r3, [r5, #2017]
.L816:
	ldr	r3, [r0, #4]
	cmp	r3, #0
	bne	.L812
	cmp	r0, #0
	beq	.L822
	ldr	ip, [r6, #2492]
	cmp	ip, #0
	beq	.L822
	ldr	r2, [r6, #2512]
	cmp	r2, r0
	beq	.L812
	add	r2, r6, #2512
	b	.L814
.L815:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	beq	.L812
.L814:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L815
.L822:
	mov	r7, #584
	mov	r4, r0
	mla	r7, r7, lr, r6
	add	r0, r5, #2064
	mov	r3, #1
	mov	r2, #101
	strb	r3, [r5, #2017]
	add	r0, r0, #8
	add	r1, r7, #57344
	str	r2, [r5, #2056]
	add	r1, r1, #40
	mov	r2, #504
	bl	memcpy
	add	r2, r7, #57088
	str	r4, [r5, #2068]
	mov	r3, #0
	str	r3, [r5, #2272]
	str	r3, [r2, #244]
	strb	r3, [r2, #226]
	strb	r3, [r4]
	ldr	r2, [r5, #2068]
	str	r3, [r2, #52]
	ldr	r2, [r5, #2068]
	str	r3, [r2, #56]
	ldr	r2, [r5, #2068]
	str	r3, [r2, #8]
	ldrb	r1, [r5, #2017]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L820
	ldr	r0, [r6, #244]
	bl	FSP_NewLogicFs
	mov	r7, r0
	mov	r1, r0
	ldr	r0, [r6, #244]
	bl	FSP_GetLogicFs
	mvn	r3, r7
	mov	r3, r3, lsr #31
	cmp	r0, #0
	mov	r4, r0
	moveq	r3, #0
	cmp	r3, #0
	beq	.L817
	ldr	r3, [r6, #2308]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L826
.L818:
	ldr	r8, .L827
	add	r1, r4, #8
	ldr	r0, [r5, #2068]
	mov	r2, #504
	ldr	r3, [r8, #52]
	add	r0, r0, #72
	blx	r3
	ldr	r1, [r5, #2068]
	add	r0, r6, #43008
	ldr	r3, [r8, #52]
	add	r1, r1, #72
	mov	r2, #504
	add	r0, r0, #24
	blx	r3
	ldr	r3, [r5, #2068]
	mov	r0, #0
	str	r7, [r3, #32]
	ldrsb	r3, [r4, #4]
	str	r3, [r5, #2052]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L812:
	add	lr, lr, #1
	add	r0, r0, #584
	cmp	lr, #20
	bne	.L816
.L820:
	ldr	r3, .L827
	mov	r0, #0
	ldr	r1, .L827+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L826:
	add	r3, r6, #24576
	ldr	r8, [r0, #200]
	ldr	r0, [r0, #112]
	ldr	r2, [r3, #2604]
	ldr	r3, [r2, #76]
	ldr	r2, [r2, #72]
	mul	r8, r8, r3
	str	r2, [r4, #172]
	str	r3, [r4, #176]
	add	r0, r8, r0
	str	r0, [r4, #116]
	bl	MEM_Phy2Vir
	ldr	r2, [r4, #96]
	ldr	r3, [r4, #128]
	add	r3, r8, r3
	add	r8, r8, r2
	ldr	r2, [r4, #200]
	str	r8, [r4, #100]
	str	r3, [r4, #132]
	add	r8, r8, r2
	str	r8, [r4, #108]
	str	r0, [r4, #44]
	mov	r0, r3
	bl	MEM_Phy2Vir
	str	r0, [r4, #60]
	b	.L818
.L817:
	ldr	r2, .L827
	mov	r0, r3
	strb	r3, [r5, #2017]
	ldr	r1, .L827+8
	ldr	r3, [r2, #68]
	blx	r3
	mvn	r0, #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L825:
	ldr	ip, .L827
	movw	r3, #9393
	ldr	r2, .L827+12
	mov	r0, #1
	ldr	r1, .L827+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L828:
	.align	2
.L827:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC67
	.word	.LC68
	.word	.LANCHOR0+364
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_AllocFrameStore, .-HEVC_AllocFrameStore
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
	subs	r7, r0, #0
	beq	.L845
	ldr	r0, [r7, #244]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L846
.L831:
	add	r5, r7, #57600
	add	r8, r7, #68608
	add	r5, r5, #8
	add	r8, r8, #680
	mov	r6, #0
.L834:
	sub	r4, r5, #16
	strb	r6, [r5, #-295]
	str	r6, [r5, #-292]
.L833:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L832
	ldr	r0, [r7, #244]
	bl	FreeUsdByDec
	str	r6, [r4]
.L832:
	cmp	r4, r5
	bne	.L833
	add	r5, r4, #584
	cmp	r5, r8
	bne	.L834
	ldr	r2, [r7, #180]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r3, #0
	add	r7, r7, #2096
	mov	r1, r3
.L837:
	add	r3, r3, #1
	str	r1, [r7, #4]!
	cmp	r3, r2
	bne	.L837
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L846:
	add	r0, r7, #50944
	add	r0, r0, #56
	bl	ResetVoQueue
	b	.L831
.L845:
	ldr	ip, .L847
	movw	r3, #9537
	ldr	r2, .L847+4
	mov	r0, #1
	ldr	r1, .L847+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L848:
	.align	2
.L847:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+388
	.word	.LC35
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
	subs	r5, r0, #0
	mov	r4, r1
	beq	.L865
	add	r6, r5, r1, lsl #2
	mov	r7, #0
	ldr	r3, [r6, #2512]
	str	r7, [r3, #4]
	ldr	r3, [r6, #2512]
	ldr	r0, [r5, #244]
	ldr	r1, [r3, #32]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L851
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L852
	ldr	r3, [r6, #2512]
	mov	r2, r7
	ldr	r0, [r5, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetDisplay
.L852:
	ldr	r3, [r6, #2512]
	mov	r2, #0
	ldr	r0, [r5, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
.L851:
	ldr	r1, [r5, #2492]
	sub	r1, r1, #1
	cmp	r4, r1
	addls	r3, r4, #628
	addls	r3, r5, r3, lsl #2
	bhi	.L856
.L855:
	add	r4, r4, #1
	ldr	r2, [r3, #4]!
	cmp	r4, r1
	str	r2, [r3, #-4]
	bls	.L855
.L856:
	add	r3, r1, #628
	mov	r2, #0
	str	r2, [r5, r3, asl #2]
	str	r1, [r5, #2492]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L865:
	ldr	ip, .L866
	movw	r3, #9646
	ldr	r2, .L866+4
	mov	r0, #1
	ldr	r1, .L866+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L867:
	.align	2
.L866:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+416
	.word	.LC35
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
	subs	r5, r0, #0
	beq	.L869
	ldr	r1, [r5, #2492]
	cmp	r1, #0
	beq	.L880
	mov	r6, #0
	mov	r4, r6
	mov	r7, r6
	b	.L873
.L872:
	add	r4, r4, #1
	cmp	r4, r1
	mov	r6, r4
	bcs	.L881
.L873:
	add	r3, r4, #628
	ldr	r3, [r5, r3, asl #2]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L872
	mov	r1, r6
	strb	r7, [r3]
	mov	r0, r5
	sub	r4, r4, #1
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	add	r4, r4, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r1, [r5, #2492]
	mov	r6, r4
	cmp	r4, r1
	bcc	.L873
.L881:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L880:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L869:
	ldr	ip, .L882
	movw	r3, #7973
	ldr	r2, .L882+4
	mov	r0, #1
	ldr	r1, .L882+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L883:
	.align	2
.L882:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+444
	.word	.LC35
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
	subs	r4, r0, #0
	beq	.L904
	ldr	r5, [r4, #2492]
	cmp	r5, #0
	beq	.L895
	mov	r6, #0
	mvn	r8, #0
	mov	r10, r6
	mov	r9, r6
	b	.L894
.L906:
	ldrsb	r2, [r0, #1]
	cmp	r2, #0
	cmpne	r2, #3
	ldr	r2, [r7, #2512]
	bne	.L890
	ldr	r0, [r2, #8]
	cmp	r0, #1
	beq	.L890
	str	r8, [r2, #32]
	mov	r3, #1
	ldr	r2, [r7, #2512]
	strb	r1, [r2, #1]
	ldr	r2, [r7, #2512]
	strb	r3, [r2, #2]
	ldr	r2, [r7, #2512]
.L890:
	ldr	r3, [r2]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	addne	r10, r10, #1
	beq	.L905
	add	r9, r9, #1
	cmp	r9, r5
	beq	.L887
.L894:
	add	r7, r4, r10, lsl #2
	ldr	r0, [r4, #244]
	ldr	r2, [r7, #2512]
	ldr	r1, [r2, #32]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L888
	ldrsb	r1, [r0]
	cmp	r1, #0
	beq	.L906
	ldr	r2, [r7, #2512]
	b	.L890
.L888:
	ldr	r2, [r7, #2512]
	ldr	r1, [r2, #8]
	cmp	r1, #1
	beq	.L890
	str	r8, [r2, #32]
	mov	r3, #1
	ldr	r2, [r7, #2512]
	strb	r0, [r2, #1]
	ldr	r2, [r7, #2512]
	strb	r3, [r2, #2]
	ldr	r2, [r7, #2512]
	b	.L890
.L905:
	mov	r1, r10
	mov	r0, r4
	add	r9, r9, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	cmp	r9, r5
	mov	r6, #1
	bne	.L894
.L887:
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L895:
	mov	r6, r5
	b	.L887
.L904:
	ldr	ip, .L907
	movw	r3, #9584
	ldr	r2, .L907+4
	mov	r0, #1
	ldr	r1, .L907+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L908:
	.align	2
.L907:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+468
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_RemoveUnUsedFrameStore, .-HEVC_RemoveUnUsedFrameStore
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
	cmp	r0, #0
	beq	.L910
	ldr	r4, [r0, #2316]
	ldrb	lr, [r4, #1]	@ zero_extendqisi2
	cmp	lr, #0
	moveq	r1, lr
	beq	.L912
	mov	r3, #0
	mov	r2, r4
	mov	r1, r3
.L913:
	add	r3, r3, #1
	ldr	ip, [r2, #48]
	cmp	r3, lr
	add	r2, r2, #28
	add	r1, r1, ip
	bne	.L913
.L912:
	ldr	r2, [r0, #2292]
	mov	r3, lr, asl #5
	sub	lr, r3, lr, asl #2
	add	r4, r4, lr
	ldr	r3, [r2, #24]
	and	r3, r3, #7
	str	r3, [r4, #60]
	ldr	r2, [r0, #2316]
	ldr	r3, [r0, #2292]
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, lr, asl #5
	cmp	ip, #0
	sub	r3, r3, lr, asl #2
	add	r4, ip, #7
	add	r3, r2, r3
	movlt	ip, r4
	ldr	r2, [r3, #52]
	add	r2, r2, ip, asr #3
	rsb	r2, r1, r2
	str	r2, [r3, #64]
	ldr	ip, [r0, #2316]
	ldr	r3, [r0, #2292]
	ldrb	r2, [ip, #1]	@ zero_extendqisi2
	ldr	lr, [r3, #24]
	mov	r3, r2, asl #5
	sub	r2, r3, r2, asl #2
	add	r2, ip, r2
	ldr	r3, [r2, #48]
	add	r3, r1, r3
	rsb	r3, lr, r3, lsl #3
	str	r3, [r2, #56]
	ldr	r2, [r0, #2316]
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #64]
	ldr	r1, [r3, #60]
	and	r2, r2, #3
	add	r2, r1, r2, lsl #3
	str	r2, [r3, #60]
	ldr	r2, [r0, #2316]
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #64]
	bic	r2, r2, #3
	str	r2, [r3, #64]
	ldr	r3, [r0, #2316]
	ldr	r2, [r3, #8]
	sub	ip, r2, #1
	cmp	ip, #1
	bhi	.L929
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	add	lr, r1, #1
	cmp	r2, lr
	movhi	r2, #1
	movls	r2, #0
	cmp	lr, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L915
	add	r1, r1, #2
	mov	ip, #0
.L916:
	sub	r2, r1, #1
	mov	lr, r2, asl #5
	sub	lr, lr, r2, asl #2
	add	r3, r3, lr
	str	ip, [r3, #60]
	ldr	r2, [r0, #2316]
	add	r2, r2, lr
	ldr	r3, [r2, #52]
	str	r3, [r2, #64]
	ldr	r2, [r0, #2316]
	add	r2, r2, lr
	ldr	r3, [r2, #48]
	mov	r3, r3, asl #3
	str	r3, [r2, #56]
	ldr	r3, [r0, #2316]
	add	r3, r3, lr
	ldr	r2, [r3, #64]
	ldr	r4, [r3, #60]
	and	r2, r2, #15
	add	r2, r4, r2, lsl #3
	str	r2, [r3, #60]
	ldr	r2, [r0, #2316]
	add	r3, r2, lr
	ldr	r2, [r3, #64]
	bic	r2, r2, #15
	str	r2, [r3, #64]
	ldr	r3, [r0, #2316]
	ldr	r2, [r3, #8]
	cmp	r1, #1
	cmpls	r1, r2
	add	r1, r1, #1
	movcc	lr, #1
	movcs	lr, #0
	cmp	lr, #0
	bne	.L916
	sub	ip, r2, #1
.L915:
	mov	r1, ip, asl #5
	ldr	lr, [r3, #12]
	sub	ip, r1, ip, asl #2
	add	r3, r3, ip
	ldr	r2, [r3, #56]
	rsb	r2, lr, r2
	str	r2, [r3, #56]
	ldr	r4, [r0, #2316]
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	ldr	lr, [r4, #8]
	cmp	r1, lr
	ldmcsfd	sp, {r4, fp, sp, pc}
	sxth	r3, r1
	add	r0, r0, #40960
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r3, r4, r3
.L920:
	ldr	r2, [r3, #64]
	add	r1, r1, #1
	ldr	ip, [r0, #2048]
	add	r3, r3, #28
	cmp	r2, ip
	strcc	r2, [r0, #2048]
	ldrcc	lr, [r4, #8]
	cmp	lr, r1
	bhi	.L920
	ldmfd	sp, {r4, fp, sp, pc}
.L929:
	ldr	r3, .L930
	mov	r0, #0
	ldr	r1, .L930+4
	ldr	r3, [r3, #68]
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	bx	r3
.L910:
	ldr	ip, .L930
	movw	r3, #9717
	ldr	r2, .L930+8
	mov	r0, #1
	ldr	r1, .L930+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	bx	ip
.L931:
	.align	2
.L930:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC69
	.word	.LANCHOR0+496
	.word	.LC35
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	beq	.L941
	add	r3, r0, #40960
	ldr	r1, [r0, #156]
	ldr	r2, [r3, #2652]
	cmp	r2, r1
	bge	.L942
	movw	r3, #2024
	ldr	r1, [r0, #2304]
	mul	r3, r3, r2
	add	ip, r1, r3
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L943
	ldr	r2, [ip, #32]
	ldr	r3, [r0, #152]
	cmp	r2, r3
	bge	.L944
	ldr	r1, [r0, #2300]
	movw	r3, #15788
	mla	r3, r3, r2, r1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L945
	ldr	r2, [r3, #52]
	ldr	r3, [r0, #148]
	cmp	r2, r3
	bcs	.L946
	movw	r3, #12820
	ldr	r1, [r0, #2296]
	mul	r3, r3, r2
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L947
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L942:
	ldr	r3, .L948
	mov	r0, #1
	ldr	r1, .L948+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L943:
	ldr	r3, .L948
	mov	r0, #1
	ldr	r1, .L948+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L944:
	ldr	r3, .L948
	mov	r0, #1
	ldr	r1, .L948+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L945:
	ldr	r3, .L948
	mov	r0, #1
	ldr	r1, .L948+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L946:
	ldr	r3, .L948
	mov	r0, #1
	ldr	r1, .L948+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L947:
	ldr	r3, .L948
	mov	r0, #1
	ldr	r1, .L948+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L941:
	ldr	ip, .L948
	movw	r3, #9796
	ldr	r2, .L948+28
	mov	r0, #1
	ldr	r1, .L948+32
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L949:
	.align	2
.L948:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC70
	.word	.LC71
	.word	.LC72
	.word	.LC73
	.word	.LC74
	.word	.LC75
	.word	.LANCHOR0+516
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_VpsSpsPpsCheck, .-HEVC_VpsSpsPpsCheck
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
	subs	r4, r0, #0
	beq	.L956
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r0, #0
	beq	.L957
	ldr	r0, [r4, #2292]
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	beq	.L955
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r3, .L958
	ldr	r1, .L958+4
	ldr	r3, [r3, #68]
	mov	r2, r0
	mov	r0, #19
	blx	r3
.L955:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L957:
	ldr	r3, .L958
	mov	r0, #1
	ldr	r1, .L958+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L956:
	ldr	ip, .L958
	movw	r3, #9850
	ldr	r2, .L958+12
	mov	r0, #1
	ldr	r1, .L958+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L959:
	.align	2
.L958:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC77
	.word	.LC76
	.word	.LANCHOR0+536
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_ReadByteAlignment, .-HEVC_ReadByteAlignment
	.align	2
	.global	HEVC_DecPTL
	.type	HEVC_DecPTL, %function
HEVC_DecPTL:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 112
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #116)
	sub	sp, sp, #116
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r2
	str	r3, [fp, #-152]
	moveq	r5, #1
	movne	r5, #0
	mov	r4, r0
	mov	r9, r1
	beq	.L999
	cmp	r2, #0
	bne	.L1000
	mov	r1, #8
	ldr	r0, [r0, #2292]
	bl	BsGet
	ldr	r3, [fp, #-152]
	cmp	r3, #0
	str	r0, [r9, #284]
	ble	.L965
.L977:
	ldr	r2, [fp, #-152]
	add	r6, r9, #42
	add	r8, r2, #42
	mov	r5, r6
	add	r8, r9, r8
	b	.L967
.L966:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r5, #1]!
	cmp	r5, r8
	beq	.L1001
.L967:
	cmp	r7, #0
	beq	.L966
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r5, #-5]
	b	.L966
.L1001:
	ldr	r3, [fp, #-152]
	cmp	r3, #7
	ldrle	r5, [fp, #-152]
	ble	.L970
	b	.L976
.L969:
	cmp	r5, #8
	beq	.L976
.L970:
	mov	r1, #2
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r5, r5, #1
	cmp	r0, #0
	beq	.L969
	ldr	r3, .L1002
	mov	r0, #1
	ldr	r1, .L1002+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1000:
	mov	r1, #2
	ldr	r0, [r0, #2292]
	bl	BsGet
	mov	r1, #1
	ldr	r10, .L1002
	mov	r6, r9
	str	r0, [r9, #276]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r9]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r9, #272]
.L964:
	mov	r3, r5
	ldr	r2, .L1002+8
	mov	r1, #100
	ldr	r8, [r10, #72]
	sub	r0, fp, #144
	add	r5, r5, #1
	blx	r8
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r5, #32
	strb	r0, [r6, #1]!
	bne	.L964
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #33]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #34]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #35]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r9, #36]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #12
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r2, [r9, #272]
	add	r3, r4, #69632
	mov	r1, #8
	str	r2, [r3, #2824]
	ldrb	r2, [r9, #2]	@ zero_extendqisi2
	str	r2, [r3, #2828]
	ldrb	r2, [r9, #3]	@ zero_extendqisi2
	str	r2, [r3, #2832]
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r3, [fp, #-152]
	cmp	r3, #0
	str	r0, [r9, #284]
	bgt	.L977
.L965:
	mov	r0, #0
.L993:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L976:
	add	r8, r9, #360
	add	r3, r9, #48
	mov	r10, #0
	b	.L974
.L973:
	ldr	r3, [fp, #-152]
	add	r10, r10, #1
	add	r8, r8, #4
	cmp	r3, r10
	mov	r3, r5
	ble	.L965
.L974:
	cmp	r7, #0
	beq	.L997
	ldrb	r2, [r6, #-5]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L996
.L997:
	add	r5, r3, #32
.L971:
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L973
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r8]
	b	.L973
.L996:
	mov	r1, #2
	ldr	r0, [r4, #2292]
	str	r3, [fp, #-156]
	bl	BsGet
	ldr	r3, [fp, #-156]
	mov	r1, #1
	add	r5, r3, #32
	mov	r9, r3
	str	r0, [r8, #-72]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r6, #199]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r8, #-48]
.L972:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r9, #1]!
	cmp	r9, r5
	bne	.L972
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #205]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #211]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #217]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r6, #223]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #12
	ldr	r0, [r4, #2292]
	bl	BsGet
	b	.L971
.L999:
	ldr	ip, .L1002
	movw	r3, #9881
	ldr	r2, .L1002+12
	mov	r0, #1
	ldr	r1, .L1002+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L993
.L1003:
	.align	2
.L1002:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC79
	.word	.LC78
	.word	.LANCHOR0+560
	.word	.LC35
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
	subs	r3, r0, #0
	str	r3, [fp, #-52]
	beq	.L1005
	ldr	r9, .L1023
	mov	r6, #0
	add	r10, r3, #2176
	add	r3, r3, #2192
	str	r3, [fp, #-48]
.L1006:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L1014
	ldr	r3, [fp, #-52]
	mov	r8, r6, asl #9
	ldr	r7, [fp, #-48]
	sub	r8, r8, r6, asl #7
	add	r5, r3, #564
	mov	r4, #0
.L1012:
	cmp	r6, #0
	add	r0, r5, r8
	mov	r2, #64
	ldr	r3, [r9, #52]
	beq	.L1021
	cmp	r6, #3
	beq	.L1022
	ldr	ip, .L1023+4
	cmp	r4, #2
	ldr	r1, .L1023+8
	movhi	r1, ip
	blx	r3
.L1008:
	mov	r3, #16
	str	r3, [r7, #4]!
	ldr	r3, [r10]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1012
.L1014:
	add	r6, r6, #1
	ldr	r3, [fp, #-48]
	cmp	r6, #4
	add	r3, r3, #24
	str	r3, [fp, #-48]
	bne	.L1006
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1005:
	ldr	ip, .L1023
	movw	r3, #10161
	ldr	r2, .L1023+12
	mov	r0, #1
	ldr	r1, .L1023+16
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L1022:
	ldr	r0, .L1023+4
	cmp	r4, #0
	ldr	r1, .L1023+8
	mov	r2, #64
	movne	r1, r0
	add	r0, r5, #1152
	blx	r3
	b	.L1008
.L1021:
	mov	r2, #16
	ldr	r1, .L1023+20
	mov	r0, r5
	blx	r3
	b	.L1008
.L1024:
	.align	2
.L1023:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+572
	.word	.LANCHOR3
	.word	.LANCHOR0+636
	.word	.LC35
	.word	.LANCHOR0+664
	UNWIND(.fnend)
	.size	HEVC_SetDefaultScalingList, .-HEVC_SetDefaultScalingList
	.align	2
	.global	HEVC_SetScalingList
	.type	HEVC_SetScalingList, %function
HEVC_SetScalingList:
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
	subs	r5, r0, #0
	beq	.L1045
	add	r6, r5, #24576
	ldr	r2, [r6, #2604]
	ldrb	r3, [r2, #5]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1044
	ldrb	r3, [r2, #6]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r6, #2608]
	bne	.L1028
	ldrb	r4, [r3, #21]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L1046
.L1029:
	ldr	r9, .L1047
	mov	r2, #1536
	mov	r1, #0
	add	r0, r5, #564
	add	r10, r5, #2176
	mov	r7, #0
	ldr	r3, [r9, #48]
	blx	r3
.L1031:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	movne	r8, r7, asl #3
	movne	r4, #0
	subne	r8, r8, r7, asl #1
	beq	.L1035
.L1032:
	add	r0, r8, r4
	ldr	r1, [r6, #2608]
	mov	r3, r4
	mov	r2, r7
	add	r1, r1, r0, lsl #6
	mov	r0, r5
	add	r1, r1, #308
	add	r4, r4, #1
	add	r1, r1, #1
	bl	HEVC_CalScalingList
	ldr	r3, [r10]
	cmp	r4, r3
	bcc	.L1032
.L1035:
	add	r7, r7, #1
	cmp	r7, #4
	bne	.L1031
	ldr	r1, [r6, #2608]
	add	r0, r5, #2192
	add	r0, r0, #4
	ldr	r3, [r9, #52]
	add	r1, r1, #1920
	mov	r2, #96
	add	r1, r1, #8
	blx	r3
.L1044:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1028:
	ldrb	r1, [r3, #21]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1029
	ldr	r9, .L1047
	mov	r2, #1536
	add	r0, r5, #564
	mov	r7, r1
	add	r10, r5, #2176
	ldr	r3, [r9, #48]
	blx	r3
.L1036:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	movne	r8, r7, asl #3
	movne	r4, #0
	subne	r8, r8, r7, asl #1
	beq	.L1040
.L1037:
	add	r0, r8, r4
	ldr	r1, [r6, #2604]
	mov	r3, r4
	mov	r2, r7
	add	r1, r1, r0, lsl #6
	mov	r0, r5
	add	r1, r1, #908
	add	r4, r4, #1
	add	r1, r1, #1
	bl	HEVC_CalScalingList
	ldr	r3, [r10]
	cmp	r4, r3
	bcc	.L1037
.L1040:
	add	r7, r7, #1
	cmp	r7, #4
	bne	.L1036
	ldr	r1, [r6, #2604]
	add	r0, r5, #2192
	ldr	r3, [r9, #52]
	mov	r2, #96
	add	r1, r1, #2528
	add	r0, r0, #4
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1046:
	bl	HEVC_SetDefaultScalingList
	mov	r0, r4
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1045:
	ldr	ip, .L1047
	movw	r3, #10108
	ldr	r2, .L1047+4
	mov	r0, #1
	ldr	r1, .L1047+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1048:
	.align	2
.L1047:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+680
	.word	.LC35
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
	b	.L1050
.L1052:
	.word	.L1056
	.word	.L1054
	.word	.L1054
	.word	.L1055
.L1054:
	ldr	r3, .L1060
	cmp	r1, #2
	add	r0, r3, #64
	movhi	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1056:
	ldr	r0, .L1060+4
	ldmfd	sp, {fp, sp, pc}
.L1055:
	ldr	r3, .L1060
	cmp	r1, #0
	add	r0, r3, #64
	movne	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1050:
	ldr	r3, .L1060+8
	mov	r0, #1
	ldr	r1, .L1060+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1061:
	.align	2
.L1060:
	.word	.LANCHOR3+80
	.word	.LANCHOR3+64
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC80
	UNWIND(.fnend)
	.size	HEVC_GetScalingListDefaultAddress, .-HEVC_GetScalingListDefaultAddress
	.align	2
	.global	HEVC_DecScalingListData
	.type	HEVC_DecScalingListData, %function
HEVC_DecScalingListData:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r8, r0
	mov	r9, r1
	moveq	r3, #1
	movne	r3, #0
	beq	.L1096
	ldr	ip, .L1101
	add	r1, r1, #1264
	add	r0, r9, #1392
	add	r1, r1, #1
	add	r0, r0, #1
	mov	r2, #64
	ldr	r4, [ip, #52]
	add	ip, r9, #1664
	str	r3, [fp, #-48]
	mov	r5, ip
	blx	r4
	add	r3, r5, #4
	str	r3, [fp, #-76]
	add	r3, r8, #2176
	str	r3, [fp, #-52]
	add	r3, r9, #24
	str	r3, [fp, #-68]
	add	r3, r9, #49
	str	r3, [fp, #-72]
.L1065:
	ldr	r2, [fp, #-52]
	ldr	r3, [r2, #4]!
	cmp	r3, #0
	str	r2, [fp, #-52]
	beq	.L1083
	ldr	r2, [fp, #-48]
	ldr	r1, [fp, #-76]
	ldr	r6, [fp, #-72]
	mov	r3, r2, asl #3
	sub	r3, r3, r2, asl #1
	str	r3, [fp, #-80]
	ldr	r3, [fp, #-68]
	str	r1, [fp, #-64]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [fp, #-60]
.L1082:
	mov	r1, #1
	ldr	r0, [r8, #2292]
	bl	BsGet
	ldr	r3, [fp, #-56]
	uxtb	r0, r0
	strb	r0, [r3, #1]!
	str	r3, [fp, #-56]
	ldr	r3, [fp, #-52]
	ldr	r5, [r3, #-1904]
	ldr	r3, [fp, #-48]
	cmp	r5, #64
	movge	r5, #64
	cmp	r3, #0
	beq	.L1066
	cmp	r0, #0
	add	r4, r8, #308
	beq	.L1097
	ldr	r3, [fp, #-48]
	cmp	r3, #1
	bls	.L1089
	ldr	r0, [r8, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #7
	str	r0, [r9, #1660]
	cmp	r3, #254
	bhi	.L1098
	ldr	r3, [fp, #-64]
	add	r7, r0, #8
	str	r7, [r3]
.L1076:
	cmp	r5, #0
	ble	.L1075
	sub	r4, r4, #4
	mov	r10, #0
	b	.L1080
.L1079:
	mov	r7, r7, lsr #24
	ldr	r2, [r4, #4]!
	add	r3, r3, r7
	cmp	r10, r5
	uxtb	r3, r3
	rsb	r7, r7, r3
	strb	r7, [r6, r2]
	beq	.L1075
.L1080:
	ldr	r0, [r8, #2292]
	add	r10, r10, #1
	bl	HEVC_se_v.isra.21
	add	r3, r0, r7
	add	r2, r0, #128
	add	r3, r3, #256
	cmp	r2, #255
	str	r0, [r9, #1664]
	mov	r7, r3, asr #31
	bls	.L1079
	ldr	r3, .L1101
	mov	r0, #1
	ldr	r1, .L1101+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
.L1094:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1084:
	ldr	r0, [r8, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [fp, #-60]
	cmp	r0, r3
	bhi	.L1086
	ldr	r2, [fp, #-56]
	uxtb	r0, r0
	ldr	r3, [fp, #-60]
	strb	r0, [r2, #1560]
	rsb	r0, r0, r3
	uxtb	r3, r0
	strb	r3, [r2, #1584]
.L1070:
	ldr	r2, [fp, #-60]
	cmp	r3, r2
	beq	.L1099
	ldr	r2, [fp, #-80]
	add	r1, r2, r3
	add	r1, r9, r1, lsl #6
	add	r1, r1, #49
.L1073:
	cmp	r1, #0
	beq	.L1100
	ldr	r3, .L1101
	mov	r2, r5
	mov	r0, r6
	ldr	r3, [r3, #52]
	blx	r3
.L1075:
	ldr	r3, [fp, #-52]
	add	r6, r6, #64
	ldr	r2, [fp, #-60]
	ldr	r1, [fp, #-64]
	ldr	r3, [r3]
	add	r2, r2, #1
	add	r1, r1, #4
	str	r2, [fp, #-60]
	cmp	r2, r3
	str	r1, [fp, #-64]
	bcc	.L1082
.L1083:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, #4
	ldr	r3, [fp, #-72]
	add	r2, r2, #6
	str	r2, [fp, #-68]
	add	r3, r3, #384
	str	r3, [fp, #-72]
	ldr	r3, [fp, #-76]
	add	r3, r3, #24
	str	r3, [fp, #-76]
	bne	.L1065
	mov	r0, #0
	b	.L1094
.L1089:
	mov	r7, #8
	b	.L1076
.L1097:
	ldr	r0, [r8, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [fp, #-60]
	cmp	r0, r3
	bhi	.L1086
	ldr	r3, [fp, #-48]
	uxtb	r0, r0
	ldr	r1, [fp, #-60]
	ldr	r2, [fp, #-56]
	cmp	r3, #1
	rsb	r3, r0, r1
	strb	r0, [r2, #1560]
	uxtb	r3, r3
	strb	r3, [r2, #1584]
	bls	.L1070
	cmp	r1, r3
	mov	r2, r1
	ldr	r1, [fp, #-64]
	ldrne	r2, [fp, #-80]
	moveq	r2, #16
	addne	r2, r2, r3
	addne	r2, r9, r2, lsl #2
	ldrne	r2, [r2, #1668]
	str	r2, [r1]
	b	.L1070
.L1099:
	mov	r1, r2
	ldr	r0, [fp, #-48]
	bl	HEVC_GetScalingListDefaultAddress
	mov	r1, r0
	b	.L1073
.L1096:
	ldr	ip, .L1101
	movw	r3, #9981
	ldr	r2, .L1101+8
	mov	r0, #1
	ldr	r1, .L1101+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1094
.L1098:
	ldr	r3, .L1101
	mov	r0, #1
	ldr	r1, .L1101+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1094
.L1086:
	ldr	r3, .L1101
	mov	r0, #1
	ldr	r1, .L1101+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1094
.L1100:
	ldr	r3, .L1101
	mov	r0, #1
	ldr	r1, .L1101+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1094
.L1066:
	cmp	r0, #0
	beq	.L1084
	ldr	r4, .L1101+28
	mov	r7, #8
	b	.L1076
.L1102:
	.align	2
.L1101:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC84
	.word	.LANCHOR0+700
	.word	.LC35
	.word	.LC83
	.word	.LC81
	.word	.LC82
	.word	.LANCHOR4+61624
	UNWIND(.fnend)
	.size	HEVC_DecScalingListData, .-HEVC_DecScalingListData
	.align	2
	.global	HEVC_DecPredWeightTable
	.type	HEVC_DecPredWeightTable, %function
HEVC_DecPredWeightTable:
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
	subs	r8, r0, #0
	beq	.L1170
	add	r4, r8, #40960
	ldr	r3, [r8, #2304]
	movw	r0, #2024
	ldr	r5, [r8, #2300]
	ldr	r2, [r4, #2652]
	ldr	r1, [r4, #2636]
	mla	r3, r0, r2, r3
	cmp	r1, #1
	ldr	r6, [r3, #32]
	beq	.L1171
	cmp	r1, #0
	bne	.L1108
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1108
.L1107:
	ldr	r0, [r8, #2292]
	add	r10, r8, #45056
	bl	HEVC_ue_v.isra.18
	cmp	r0, #7
	str	r0, [r10, #72]
	bhi	.L1172
	movw	r3, #15788
	mla	r9, r3, r6, r5
	ldr	r3, [r9, #64]
	cmp	r3, #0
	ldreq	r3, [r10, #76]
	bne	.L1173
.L1112:
	add	r3, r3, r0
	str	r3, [r10, #1104]
	ldr	r3, [r4, #2744]
	cmp	r3, #0
	beq	.L1113
	add	r5, r8, #45056
	mov	r6, #0
	add	r5, r5, #76
	mov	r7, r5
.L1114:
	mov	r1, #1
	ldr	r0, [r8, #2292]
	bl	BsGet
	add	r6, r6, #1
	str	r0, [r7, #4]!
	ldr	r3, [r4, #2744]
	cmp	r3, r6
	bhi	.L1114
	ldr	r2, [r9, #64]
	cmp	r2, #0
	beq	.L1115
	cmp	r3, #0
	addne	r7, r8, #45056
	movne	r6, #0
	addne	r7, r7, #140
	beq	.L1113
.L1119:
	mov	r1, #1
	ldr	r0, [r8, #2292]
	bl	BsGet
	add	r6, r6, #1
	str	r0, [r7, #4]!
	ldr	r3, [r4, #2744]
	cmp	r3, r6
	bhi	.L1119
.L1115:
	cmp	r3, #0
	beq	.L1113
	add	r7, r8, #45312
	mov	r6, #0
	add	r7, r7, #80
	str	r8, [fp, #-48]
	mov	r8, r5
	mov	r3, r7
	mov	r7, r6
	mov	r6, r3
	b	.L1130
.L1120:
	ldr	r0, [r10, #72]
	mov	r3, #1
	str	ip, [r8, #192]
	mov	r0, r3, asl r0
	str	r0, [r8, #1028]
.L1122:
	ldr	r0, [r9, #64]
	cmp	r0, #0
	beq	.L1124
	ldr	r0, [r8, #64]
	cmp	r0, #0
	bne	.L1125
	ldr	ip, [r10, #1104]
	mov	r3, #1
	str	r0, [r6, #964]
	mov	ip, r3, asl ip
	str	r0, [r6, #968]
	str	ip, [r6, #836]
	str	ip, [r6, #840]
.L1124:
	ldr	r0, [r4, #2744]
	add	r7, r7, #1
	add	r6, r6, #8
	cmp	r0, r7
	bls	.L1174
.L1130:
	ldr	ip, [r8, #4]!
	cmp	ip, #0
	beq	.L1120
	ldr	r3, [fp, #-48]
	ldr	r0, [r3, #2292]
	bl	HEVC_se_v.isra.21
	add	ip, r0, #128
	str	r0, [r8, #128]
	cmp	ip, #255
	bhi	.L1175
	ldr	ip, [r10, #72]
	mov	r3, #1
	add	r0, r0, r3, asl ip
	ldr	r3, [fp, #-48]
	str	r0, [r8, #1028]
	ldr	r0, [r3, #2292]
	bl	HEVC_se_v.isra.21
	add	ip, r0, #128
	str	r0, [r8, #192]
	cmp	ip, #255
	bls	.L1122
	ldr	r3, .L1182
	mov	r2, r0
	ldr	r1, .L1182+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1105
.L1171:
	ldrb	r3, [r3, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1107
.L1108:
	mov	r0, #0
.L1105:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1125:
	add	r2, r6, #960
	add	r1, r6, #128
	add	r3, r6, #832
	str	r9, [fp, #-56]
	ldr	r9, [fp, #-48]
	mov	r0, r6
	str	r7, [fp, #-52]
	mov	r5, #0
	str	r8, [fp, #-60]
	mov	r7, r2
	str	r6, [fp, #-64]
	mov	r8, r1
	str	r4, [fp, #-68]
	mov	r6, r3
	mov	r4, r0
.L1128:
	ldr	r0, [r9, #2292]
	add	r5, r5, #1
	bl	HEVC_se_v.isra.21
	add	r3, r0, #128
	str	r0, [r4]
	cmp	r3, #255
	bhi	.L1176
	ldr	r0, [r9, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #512
	str	r0, [r8], #4
	cmp	r3, #1024
	bcs	.L1177
	ldr	r1, [r10, #1104]
	mov	r3, #1
	ldr	r2, [r4], #4
	add	r3, r2, r3, asl r1
	str	r3, [r6, #4]!
	mov	r3, r3, asl #7
	mov	r3, r3, asr r1
	rsb	r3, r3, #128
	add	r0, r0, r3
	cmp	r0, #127
	movge	r0, #127
	cmn	r0, #128
	mvnlt	r0, #127
	cmp	r5, #2
	str	r0, [r7, #4]!
	bne	.L1128
	sub	r4, fp, #68
	ldr	r7, [fp, #-52]
	ldmia	r4, {r4, r6, r8, r9}
	b	.L1124
.L1174:
	ldr	r8, [fp, #-48]
.L1113:
	ldr	r5, [r4, #2636]
	cmp	r5, #0
	bne	.L1108
	ldr	r3, [r4, #2748]
	cmp	r3, #0
	beq	.L1108
	add	r6, r8, #45568
	add	r6, r6, #76
	mov	r7, r6
.L1131:
	mov	r1, #1
	ldr	r0, [r8, #2292]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r7, #4]!
	ldr	r3, [r4, #2748]
	cmp	r3, r5
	bhi	.L1131
	ldr	r2, [r9, #64]
	cmp	r2, #0
	bne	.L1178
.L1132:
	cmp	r3, #0
	beq	.L1108
	add	r2, r8, #45824
	mov	r7, r6
	add	r2, r2, #80
	mov	r3, #0
	str	r8, [fp, #-48]
	mov	r6, r3
	mov	r8, r7
	mov	r7, r4
	mov	r4, r2
	b	.L1146
.L1136:
	ldr	r0, [r10, #72]
	mov	r3, #1
	str	ip, [r8, #192]
	mov	r0, r3, asl r0
	str	r0, [r8, #836]
.L1138:
	ldr	r0, [r9, #64]
	cmp	r0, #0
	beq	.L1140
	ldr	r0, [r8, #64]
	cmp	r0, #0
	bne	.L1141
	ldr	ip, [r10, #1104]
	mov	r3, #1
	str	r0, [r4, #772]
	mov	ip, r3, asl ip
	str	r0, [r4, #776]
	str	ip, [r4, #644]
	str	ip, [r4, #648]
.L1140:
	ldr	r0, [r7, #2748]
	add	r6, r6, #1
	add	r4, r4, #8
	cmp	r0, r6
	bls	.L1108
.L1146:
	ldr	ip, [r8, #4]!
	cmp	ip, #0
	beq	.L1136
	ldr	r3, [fp, #-48]
	ldr	r0, [r3, #2292]
	bl	HEVC_se_v.isra.21
	add	ip, r0, #128
	str	r0, [r8, #128]
	cmp	ip, #255
	bhi	.L1179
	ldr	ip, [r10, #72]
	mov	r3, #1
	add	r0, r0, r3, asl ip
	ldr	r3, [fp, #-48]
	str	r0, [r8, #836]
	ldr	r0, [r3, #2292]
	bl	HEVC_se_v.isra.21
	add	ip, r0, #128
	str	r0, [r8, #192]
	cmp	ip, #255
	bls	.L1138
	ldr	r3, .L1182
	mov	r0, #1
	ldr	r1, .L1182+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1105
.L1141:
	add	r2, r4, #768
	add	r1, r4, #128
	add	r3, r4, #640
	str	r9, [fp, #-56]
	ldr	r9, [fp, #-48]
	mov	r0, r4
	str	r4, [fp, #-52]
	mov	r5, #0
	str	r8, [fp, #-60]
	mov	r4, r3
	str	r6, [fp, #-64]
	mov	r8, r1
	str	r7, [fp, #-68]
	mov	r6, r0
	mov	r7, r2
.L1144:
	ldr	r0, [r9, #2292]
	add	r5, r5, #1
	bl	HEVC_se_v.isra.21
	add	r3, r0, #128
	str	r0, [r6]
	cmp	r3, #255
	bhi	.L1180
	ldr	r0, [r9, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #512
	str	r0, [r8], #4
	cmp	r3, #1024
	bcs	.L1181
	ldr	r1, [r10, #1104]
	mov	r3, #1
	ldr	r2, [r6], #4
	add	r3, r2, r3, asl r1
	str	r3, [r4, #4]!
	mov	r3, r3, asl #7
	mov	r3, r3, asr r1
	rsb	r3, r3, #128
	add	r0, r0, r3
	cmp	r0, #127
	movge	r0, #127
	cmn	r0, #128
	mvnlt	r0, #127
	cmp	r5, #2
	str	r0, [r7, #4]!
	bne	.L1144
	sub	r6, fp, #64
	ldr	r4, [fp, #-52]
	ldr	r7, [fp, #-68]
	ldmia	r6, {r6, r8, r9}
	b	.L1140
.L1173:
	ldr	r0, [r8, #2292]
	bl	HEVC_se_v.isra.21
	add	r2, r0, #7
	mov	r3, r0
	cmp	r2, #14
	str	r0, [r10, #76]
	bhi	.L1111
	ldr	r0, [r10, #72]
	b	.L1112
.L1176:
	ldr	r3, .L1182
	mov	r0, #1
	ldr	r1, .L1182+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1177:
	ldr	r3, .L1182
	mov	r0, #1
	ldr	r1, .L1182+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1178:
	cmp	r3, #0
	addne	r7, r8, #45568
	movne	r5, #0
	addne	r7, r7, #140
	beq	.L1108
.L1135:
	mov	r1, #1
	ldr	r0, [r8, #2292]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r7, #4]!
	ldr	r3, [r4, #2748]
	cmp	r3, r5
	bhi	.L1135
	b	.L1132
.L1175:
	ldr	r3, .L1182
	mov	r2, r0
	ldr	r1, .L1182+20
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1105
.L1180:
	ldr	r3, .L1182
	mov	r0, #1
	ldr	r1, .L1182+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1105
.L1181:
	ldr	r3, .L1182
	mov	r0, #1
	ldr	r1, .L1182+28
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1105
.L1179:
	ldr	r3, .L1182
	mov	r0, #1
	ldr	r1, .L1182+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1105
.L1172:
	ldr	r3, .L1182
	mov	r0, #1
	ldr	r1, .L1182+36
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1105
.L1170:
	ldr	ip, .L1182
	movw	r3, #10235
	ldr	r2, .L1182+40
	mov	r0, #1
	ldr	r1, .L1182+44
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1105
.L1111:
	ldr	r3, .L1182
	mov	r0, #1
	ldr	r1, .L1182+48
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1105
.L1183:
	.align	2
.L1182:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC88
	.word	.LC92
	.word	.LC89
	.word	.LC90
	.word	.LC87
	.word	.LC93
	.word	.LC94
	.word	.LC91
	.word	.LC85
	.word	.LANCHOR0+724
	.word	.LC35
	.word	.LC86
	UNWIND(.fnend)
	.size	HEVC_DecPredWeightTable, .-HEVC_DecPredWeightTable
	.align	2
	.global	HEVC_DecSliceSegmentHeader
	.type	HEVC_DecSliceSegmentHeader, %function
HEVC_DecSliceSegmentHeader:
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
	UNWIND(.pad #92)
	sub	sp, sp, #92
	subs	r5, r0, #0
	str	r1, [fp, #-92]
	beq	.L1478
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	add	r4, r5, #40960
	ldr	r10, [r4, #2648]
	sub	r3, r10, #16
	cmp	r3, #5
	movhi	r3, #0
	movls	r3, #1
	cmp	r3, #0
	str	r3, [fp, #-72]
	strb	r0, [r4, #2577]
	bne	.L1479
.L1187:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #0
	str	r0, [r4, #2652]
	ldr	r2, [r5, #156]
	blt	.L1189
	cmp	r0, r2
	bge	.L1189
	mov	r0, r5
	bl	HEVC_VpsSpsPpsCheck
	subs	r3, r0, #0
	str	r3, [fp, #-88]
	bne	.L1480
	ldr	r1, [r4, #2652]
	movw	r6, #2024
	ldr	r2, [r5, #2304]
	movw	r7, #15788
	ldr	r3, [r5, #2300]
	mla	r6, r6, r1, r2
	ldrb	r1, [r6, #2]	@ zero_extendqisi2
	ldr	r2, [r6, #32]
	cmp	r1, #0
	mla	r7, r7, r2, r3
	bne	.L1481
.L1194:
	mov	r3, #0
	strb	r3, [r4, #2579]
.L1195:
	ldr	r8, [r7, #160]
	ldr	r3, [r7, #164]
	cmp	r8, #0
	beq	.L1197
	cmp	r3, #0
	beq	.L1197
	ldr	r0, [r7, #76]
	mov	r1, r3
	add	r0, r3, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	mov	r1, r8
	mov	r9, r0
	ldr	r0, [r7, #72]
	add	r0, r8, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	ldr	r8, [r7, #216]
	mov	r3, #1
	mov	r1, #0
	mov	r8, r8, asl r3
	mov	r8, r3, asl r8
	mul	r9, r0, r9
	cmp	r9, r3
	ble	.L1199
.L1200:
	add	r1, r1, #1
	cmp	r9, r3, asl r1
	bgt	.L1200
.L1199:
	ldrb	r3, [r4, #2577]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r2, #0
	beq	.L1482
.L1201:
	mul	r9, r8, r9
	ldrb	r8, [r4, #2579]	@ zero_extendqisi2
	str	r2, [r4, #2728]
	cmp	r8, #0
	str	r9, [r4, #2732]
	ldr	r3, [r5, #188]
	str	r3, [r4, #2624]
	beq	.L1483
.L1204:
	ldr	r3, [r6, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	streq	r3, [r4, #2716]
	bne	.L1484
.L1320:
	ldrb	r3, [r6, #23]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1325
.L1331:
	ldr	r3, [r4, #2728]
	cmp	r3, #0
	bne	.L1485
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1333
	ldr	r2, [fp, #-72]
	cmp	r2, #0
	beq	.L1337
	ldr	r2, [fp, #-92]
	cmp	r2, #0
	strneb	r3, [r5]
	mov	r3, #1
	strb	r3, [r5, #2]
.L1336:
	ldr	r3, [r4, #2624]
	ldr	r2, [fp, #-72]
	cmp	r3, #0
	moveq	r2, #0
	andne	r2, r2, #1
	cmp	r2, #0
	bne	.L1486
.L1337:
	mov	r3, #0
	strb	r3, [r5, #1]
.L1338:
	mov	r0, r5
	bl	HEVC_IsNewPic
	add	r3, r5, #45056
	str	r0, [r3, #68]
	mov	r0, r5
	bl	HEVC_ReadByteAlignment
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L1454:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1485:
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1337
	b	.L1336
.L1481:
	ldrb	r3, [r4, #2577]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1194
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2579]
	b	.L1195
.L1483:
	ldr	r3, [r6, #36]
	cmp	r3, #0
	ldrne	r9, .L1522
	beq	.L1209
.L1208:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r3, [r9, #68]
	ldr	r1, .L1522+4
	add	r8, r8, #1
	mov	r2, r0
	mov	r0, #19
	blx	r3
	ldr	r3, [r6, #36]
	cmp	r3, r8
	bhi	.L1208
.L1209:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #2
	str	r0, [r4, #2636]
	bhi	.L1487
	ldrb	r3, [r6, #4]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r3, #1
	streqb	r3, [r4, #2576]
	bne	.L1488
.L1211:
	sub	r10, r10, #19
	cmp	r10, #1
	bhi	.L1489
	mov	r3, #0
	str	r3, [r4, #2624]
	str	r3, [r5, #188]
	ldr	r3, [r4, #2644]
	cmp	r3, #0
	streq	r3, [r4, #2628]
	streq	r3, [r5, #184]
	ldrb	r3, [r7, #8]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1467
.L1342:
	mov	r8, #0
	strb	r8, [r4, #2583]
	str	r8, [fp, #-96]
.L1340:
	ldr	r3, [r4, #2636]
	cmp	r3, #2
	bne	.L1490
.L1254:
	ldrb	r3, [r4, #2583]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1285
	mov	r3, #1
	strb	r3, [r4, #2587]
	mov	r3, #2
.L1290:
	ldrb	r2, [r6, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1295
	cmp	r3, #1
	beq	.L1298
.L1295:
	ldrb	r2, [r6, #11]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1284
	cmp	r3, #0
	bne	.L1284
.L1298:
	mov	r0, r5
	bl	HEVC_DecPredWeightTable
	cmp	r0, #0
	ldreq	r3, [r4, #2636]
	bne	.L1491
.L1284:
	cmp	r3, #2
	beq	.L1299
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	rsb	r3, r0, #4
	rsb	r2, r0, #5
	cmp	r3, #4
	str	r2, [r4, #2692]
	bhi	.L1492
.L1299:
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	str	r0, [r4, #2696]
	ldr	r2, [r6, #48]
	add	r2, r0, r2
	str	r2, [r4, #2632]
	ldr	r3, [r7, #104]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L1493
	ldrb	r3, [r6, #9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1494
.L1301:
	ldrb	r3, [r6, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1464
	ldrb	r3, [r6, #19]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r4, #2588]
	bne	.L1495
.L1309:
	ldrb	r0, [r6, #20]	@ zero_extendqisi2
	strb	r0, [r4, #2589]
	ldr	r3, [r6, #76]
	str	r3, [r4, #2708]
	ldr	r3, [r6, #80]
	str	r3, [r4, #2712]
.L1306:
	ldrb	r3, [r7, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1312
	ldr	r2, [r4, #2580]
	bic	r3, r2, #-16777216
	bic	r3, r3, #255
	adds	r3, r3, #0
	movne	r3, #1
.L1312:
	ldrb	r2, [r6, #17]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1313
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L1496
.L1313:
	strb	r2, [r4, #2590]
	b	.L1204
.L1479:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2578]
	b	.L1187
.L1482:
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r4, #2656]
	cmp	r0, #0
	ldr	r2, [r7, #244]
	ldr	r3, [r7, #240]
	mul	r3, r3, r2
	blt	.L1203
	cmp	r3, r0
	bls	.L1203
	mul	r2, r8, r0
	b	.L1201
.L1484:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r4, #2716]
	ldr	r3, [r6, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	ldreq	r3, [r7, #244]
	subeq	r3, r3, #1
	beq	.L1316
	cmp	r3, #256
	ldreq	r2, [r6, #68]
	ldreq	r3, [r6, #72]
	ldrne	r3, [r7, #244]
	ldrne	r2, [r6, #68]
	mul	r3, r3, r2
	sub	r3, r3, #1
.L1316:
	cmp	r3, #255
	movcs	r3, #255
	cmp	r0, r3
	bhi	.L1497
	cmp	r0, #0
	beq	.L1320
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #31
	add	r1, r0, #1
	str	r1, [r4, #2640]
	bhi	.L1498
	ldr	r3, [r4, #2716]
	cmp	r3, #0
	addne	r8, r5, #43520
	movne	r7, #0
	addne	r8, r8, #192
	bne	.L1324
	b	.L1320
.L1499:
	ldr	r1, [r4, #2640]
.L1324:
	ldr	r0, [r5, #2292]
	add	r7, r7, #1
	bl	BsGet
	str	r0, [r8, #4]!
	ldr	r3, [r4, #2716]
	cmp	r3, r7
	bhi	.L1499
	ldrb	r3, [r6, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1331
.L1325:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #256
	str	r0, [r4, #2720]
	bhi	.L1500
	ldr	r0, [r5, #2292]
	bl	BsResidBits
	ldr	r3, [r4, #2720]
	cmp	r0, r3
	bcc	.L1329
	cmp	r3, #0
	movne	r6, #0
	beq	.L1331
.L1332:
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r3, [r4, #2720]
	add	r6, r6, #1
	cmp	r3, r6
	str	r0, [r4, #2724]
	bhi	.L1332
	b	.L1331
.L1333:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	strneb	r2, [r5, #2]
	b	.L1337
.L1486:
	ldr	r3, [r4, #2648]
	cmp	r3, #21
	moveq	r3, #1
	streqb	r3, [r5, #1]
	bne	.L1337
	b	.L1338
.L1467:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #2581]
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2582]
	b	.L1342
.L1490:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #2584]
	cmp	r0, #0
	bne	.L1501
	ldr	r8, [r4, #2636]
	ldr	r3, [r6, #40]
	cmp	r8, #0
	str	r3, [r4, #2744]
	bne	.L1260
	ldr	r3, [r6, #44]
	str	r3, [r4, #2748]
.L1261:
	ldr	r3, [fp, #-96]
	cmp	r3, #0
	beq	.L1502
	ldr	r3, [fp, #-96]
	ldr	r2, [r3, #24]
	cmp	r2, #16
	bhi	.L1264
	cmp	r2, #0
	moveq	r8, r2
	beq	.L1266
	ldr	r1, [fp, #-96]
	add	r2, r2, #52
	mov	r8, #0
	add	r3, r1, #52
	add	r2, r1, r2
.L1268:
	ldrb	r1, [r3, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	addne	r8, r8, #1
	cmp	r3, r2
	bne	.L1268
	cmp	r8, #1
	movle	r2, #0
	movgt	r2, #1
.L1266:
	ldrb	r3, [r6, #22]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r2, #0
	andne	r2, r2, #1
	cmp	r2, #0
	beq	.L1503
	add	r9, r5, #46848
	add	r2, r5, #43520
	add	r9, r9, #160
	add	r2, r2, #16
	cmp	r2, #0
	cmpne	r9, #0
	beq	.L1269
	sub	r2, r8, #1
	mov	r10, #1
	movs	r2, r2, asr #1
	beq	.L1270
.L1271:
	movs	r2, r2, asr #1
	add	r10, r10, #1
	bne	.L1271
.L1270:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r8, #1
	movls	r3, #0
	movhi	r3, #1
	uxtb	r0, r0
	str	r3, [fp, #-48]
	cmp	r0, #0
	cmpne	r8, #1
	add	r3, r5, #45056
	str	r3, [fp, #-84]
	strb	r0, [r3, #1952]
	bls	.L1275
	ldr	r2, [r4, #2744]
	cmp	r2, #0
	beq	.L1275
	mov	r8, r9
	mov	r9, #0
.L1276:
	mov	r1, r10
	ldr	r0, [r5, #2292]
	bl	BsGet
	add	r9, r9, #1
	str	r0, [r8, #4]!
	ldr	r3, [r4, #2744]
	cmp	r9, r3
	bcc	.L1276
.L1275:
	ldr	r8, [r4, #2636]
	cmp	r8, #0
	bne	.L1262
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r9, [fp, #-48]
	ldr	r3, [fp, #-84]
	uxtb	r0, r0
	strb	r0, [r3, #1953]
	cmp	r0, #0
	moveq	r9, #0
	andne	r9, r9, #1
	cmp	r9, #0
	beq	.L1465
	ldr	r3, [r4, #2748]
	cmp	r3, #0
	beq	.L1465
	add	r9, r5, #47104
	add	r9, r9, #32
.L1279:
	mov	r1, r10
	ldr	r0, [r5, #2292]
	bl	BsGet
	add	r8, r8, #1
	str	r0, [r9, #4]!
	ldr	r3, [r4, #2748]
	cmp	r8, r3
	bcc	.L1279
.L1465:
	ldr	r8, [r4, #2636]
	cmp	r8, #0
	bne	.L1262
.L1345:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r8, [r4, #2636]
	strb	r0, [r4, #2585]
.L1262:
	cmp	r8, #2
	bne	.L1346
	b	.L1254
.L1464:
	ldrb	r0, [r4, #2589]	@ zero_extendqisi2
	b	.L1306
.L1503:
	ldr	r3, [r4, #2636]
	cmp	r3, #0
	beq	.L1345
.L1346:
	ldrb	r3, [r6, #5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1504
.L1280:
	ldrb	r3, [r4, #2583]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r4, #2636]
	beq	.L1290
	cmp	r3, #0
	beq	.L1505
	cmp	r3, #2
	mov	r3, #1
	strb	r3, [r4, #2587]
	beq	.L1285
.L1288:
	ldr	r3, [r4, #2744]
	cmp	r3, #1
	bls	.L1463
.L1286:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldrb	r2, [r4, #2587]	@ zero_extendqisi2
	cmp	r2, #0
	str	r0, [r4, #2688]
	bne	.L1291
	ldr	r1, [r4, #2684]
	sub	r1, r1, #1
.L1293:
	cmp	r1, r0
	movcs	r3, #0
	movcc	r3, #1
	orrs	r3, r3, r0, lsr #31
	beq	.L1463
	ldr	ip, .L1522
	mov	r3, r0
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L1522+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1489:
	ldr	r1, [r7, #132]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r2, #1
	str	r0, [r4, #2664]
	mov	r9, r0
	ldr	r3, [r7, #128]
	ldr	r8, [r5, #184]
	mov	r3, r2, asl r3
	str	r0, [fp, #-104]
	str	r3, [fp, #-108]
	mov	r1, r3
	mov	r0, r8
	bl	__aeabi_uidivmod
	cmp	r1, r9
	rsb	r3, r1, r8
	bls	.L1213
	ldr	r0, [fp, #-108]
	ldr	r2, [fp, #-104]
	rsb	r2, r2, r1
	cmp	r2, r0, lsr #1
	movcs	r2, r0
	addcs	r3, r3, r2
	bcc	.L1213
.L1214:
	ldr	r1, [r4, #2648]
	ldr	r0, [fp, #-104]
	sub	r2, r1, #16
	cmp	r2, #2
	movls	r3, #0
	add	r3, r3, r0
	str	r3, [r4, #2624]
	str	r3, [r5, #188]
	ldr	r0, [r4, #2644]
	cmp	r0, #0
	bne	.L1216
	cmp	r1, #15
	bls	.L1506
.L1217:
	cmp	r2, #7
	movhi	r2, #0
	movls	r2, #1
.L1218:
	sub	r1, r1, #7
	bics	r1, r1, #2
	andne	r2, r2, #1
	moveq	r2, #0
	cmp	r2, #0
	strne	r3, [r4, #2628]
	strne	r3, [r5, #184]
.L1216:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #2580]
	cmp	r0, #0
	beq	.L1219
	ldr	r3, [r7, #228]
	cmp	r3, #1
	movhi	r1, #0
	movhi	r2, #1
	bls	.L1221
.L1223:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L1223
	cmp	r1, #0
	bne	.L1507
.L1221:
	mov	r1, #0
	str	r1, [r4, #2668]
.L1226:
	mov	r2, #204
	add	r0, r5, #46592
	mla	r1, r2, r1, r7
	add	r0, r0, #212
	str	r0, [fp, #-96]
	add	r1, r1, #2720
	add	r1, r1, #12
	bl	memcpy
.L1222:
	ldrb	r3, [r7, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1227
	add	r3, r5, #45056
	str	r3, [fp, #-84]
	mov	r1, r3
	ldr	r3, [r7, #232]
	ldr	r2, [r1, #1768]
	cmp	r3, #0
	ldr	r3, [r1, #1764]
	add	r3, r2, r3
	str	r3, [fp, #-112]
	bne	.L1228
.L1231:
	mov	r10, #0
.L1229:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	ip, [fp, #-84]
	ldr	r1, [r4, #2672]
	str	r0, [r4, #2676]
	add	r0, r0, r1
	ldr	r2, [ip, #1764]
	ldr	r3, [ip, #1768]
	str	r0, [ip, #1780]
	add	ip, r3, r2
	add	ip, ip, r0
	cmp	ip, #16
	bhi	.L1508
	ldr	r3, [fp, #-112]
	cmp	r0, #0
	sub	r8, r3, #1
	add	r8, r0, r8
	beq	.L1247
	add	r3, r8, #11200
	add	r8, r8, #46848
	add	r3, r3, #49
	add	r8, r8, #9
	add	r8, r5, r8
	str	r8, [fp, #-100]
	mov	r3, r3, asl #2
	add	r9, r5, #44544
	add	ip, r3, #64
	str	ip, [fp, #-52]
	ldr	r8, [fp, #-52]
	add	r0, r5, #44800
	str	r9, [fp, #-48]
	add	lr, r5, #43520
	add	r9, r5, r8
	add	r8, r5, r3
	ldr	r3, [fp, #-48]
	mov	ip, r0
	str	r0, [fp, #-56]
	add	r0, r0, #128
	str	r0, [fp, #-60]
	add	r0, ip, #4
	add	ip, lr, #31
	add	lr, r3, #196
	ldr	r3, [fp, #-56]
	add	r2, r5, #43520
	str	r8, [fp, #-52]
	add	r2, r2, #46
	add	r3, r3, #68
	str	lr, [fp, #-48]
	str	r6, [fp, #-116]
	mov	r6, ip
	mov	lr, r3
	mov	r3, #0
	str	r7, [fp, #-76]
	mov	r8, lr
	str	r10, [fp, #-80]
	mov	r10, r0
	ldr	r7, [fp, #-52]
	str	r4, [fp, #-64]
	str	r5, [fp, #-52]
	mov	r5, r3
	str	r2, [fp, #-120]
	str	r3, [fp, #-68]
	str	r2, [fp, #-56]
	ldr	r4, [fp, #-100]
	b	.L1246
.L1511:
	ldr	r3, [fp, #-80]
	cmp	r3, #0
	ldreq	r0, [fp, #-80]
	bne	.L1509
.L1237:
	ldr	r2, [fp, #-76]
	add	r3, r2, r0
	add	r0, r0, #62
	ldrb	r1, [r3, #16]	@ zero_extendqisi2
	ldr	r3, [r2, r0, asl #2]
	strb	r1, [r4]
.L1240:
	ldr	r2, [fp, #-60]
	mov	r1, #1
	str	r3, [r2, #4]!
	ldr	r3, [fp, #-52]
	str	r2, [fp, #-60]
	ldr	r0, [r3, #2292]
	bl	BsGet
	ldr	r3, [fp, #-56]
	uxtb	r0, r0
	strb	r0, [r3, #1]!
	cmp	r0, #0
	str	r3, [fp, #-56]
	bne	.L1510
	cmp	r5, #0
	streq	r5, [fp, #-68]
	beq	.L1244
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	ldr	r3, [r3, #2672]
	cmp	r3, r5
	moveq	r2, #0
	str	r2, [fp, #-68]
.L1244:
	mov	r3, #0
	str	r3, [r9]
.L1243:
	ldr	r3, [fp, #-84]
	add	r5, r5, #1
	ldr	r2, [fp, #-48]
	sub	r7, r7, #4
	sub	r9, r9, #4
	sub	r4, r4, #1
	ldr	r3, [r3, #1780]
	add	r2, r2, #4
	add	r10, r10, #4
	add	r6, r6, #1
	cmp	r3, r5
	str	r2, [fp, #-48]
	add	r8, r8, #4
	bls	.L1245
	ldr	r3, [fp, #-64]
	ldr	r1, [r3, #2672]
.L1246:
	cmp	r1, r5
	bhi	.L1511
	ldr	r3, [fp, #-76]
	ldr	r1, [r3, #132]
	ldr	r3, [fp, #-52]
	ldr	r0, [r3, #2292]
	bl	BsGet
	ldr	r3, [fp, #-52]
	mov	r1, #1
	str	r0, [r10]
	str	r0, [fp, #-100]
	ldr	r0, [r3, #2292]
	bl	BsGet
	ldr	r3, [fp, #-100]
	uxtb	r0, r0
	strb	r0, [r6]
	strb	r0, [r4]
	b	.L1240
.L1213:
	ldr	r2, [fp, #-104]
	cmp	r1, r2
	bcs	.L1214
	rsb	r1, r1, r2
	ldr	r2, [fp, #-108]
	cmp	r1, r2, lsr #1
	rsbhi	r3, r2, r3
	b	.L1214
.L1488:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2576]
	b	.L1211
.L1189:
	ldr	r1, .L1522
	mov	r3, r0
	str	r2, [sp]
	mov	r0, #1
	ldr	r2, .L1522+12
	ldr	r4, [r1, #68]
	ldr	r1, .L1522+16
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1494:
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #12
	str	r0, [r4, #2700]
	cmp	r3, #24
	bhi	.L1512
	ldr	r3, [r6, #60]
	add	r2, r0, r3
	add	r2, r2, #12
	cmp	r2, #24
	bhi	.L1513
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #12
	str	r0, [r4, #2704]
	cmp	r3, #24
	bhi	.L1514
	ldr	r2, [r6, #64]
	add	r2, r0, r2
	add	r3, r2, #12
	cmp	r3, #24
	bls	.L1301
	ldr	r3, .L1522
	mov	r0, #1
	ldr	r1, .L1522+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1463:
	ldr	r3, [r4, #2636]
	b	.L1290
.L1227:
	ldrb	r3, [r7, #11]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r4, #2583]
	bne	.L1515
.L1252:
	ldrb	r3, [r7, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1340
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #2581]
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2582]
	b	.L1340
.L1504:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2586]
	b	.L1280
.L1260:
	str	r0, [r4, #2748]
.L1259:
	cmp	r8, #2
	bne	.L1261
	b	.L1254
.L1501:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	add	r2, r0, #1
	str	r2, [r4, #2680]
	cmp	r2, #16
	bhi	.L1516
	ldr	r8, [r4, #2636]
	str	r2, [r4, #2744]
	cmp	r8, #0
	movne	r3, #0
	strne	r3, [r4, #2684]
	strne	r3, [r4, #2748]
	bne	.L1259
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	add	r2, r0, #1
	str	r2, [r4, #2684]
	cmp	r2, #16
	strls	r2, [r4, #2748]
	ldrls	r8, [r4, #2636]
	bls	.L1259
	ldr	ip, .L1522
	mov	r3, #16
	ldr	r1, .L1522+24
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1505:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r3, [r4, #2636]
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r4, #2587]
	beq	.L1299
	cmp	r0, #0
	bne	.L1288
	ldr	r2, [r4, #2748]
	cmp	r2, #1
	bhi	.L1286
	b	.L1290
.L1285:
	mov	r3, #2
	b	.L1295
.L1291:
	ldr	r1, [r4, #2680]
	sub	r1, r1, #1
	b	.L1293
.L1506:
	tst	r1, #1
	movne	r2, #1
	bne	.L1218
	b	.L1217
.L1228:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r4, #2672]
	mov	r2, r0
	ldr	r3, [r7, #232]
	cmp	r0, r3
	bhi	.L1517
	cmp	r3, #1
	bls	.L1231
	mov	r10, #0
	mov	r2, #1
.L1232:
	add	r10, r10, #1
	cmp	r3, r2, asl r10
	bhi	.L1232
	str	r10, [fp, #-88]
	b	.L1229
.L1329:
	ldr	ip, .L1522
	mov	r2, r0
	ldr	r1, .L1522+28
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1510:
	ldr	r3, [fp, #-52]
	ldr	r0, [r3, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r5, #0
	str	r0, [r8]
	beq	.L1242
	ldr	r3, [fp, #-64]
	ldr	r3, [r3, #2672]
	cmp	r3, r5
	ldrne	r3, [fp, #-68]
	addne	r0, r0, r3
.L1242:
	str	r0, [r7]
	mov	r3, #1
	str	r0, [fp, #-68]
	str	r3, [r9]
	b	.L1243
.L1509:
	ldr	r3, [fp, #-52]
	ldr	r1, [fp, #-88]
	ldr	r0, [r3, #2292]
	bl	BsGet
	ldr	r3, [fp, #-48]
	cmp	r0, #0
	str	r0, [r3]
	blt	.L1518
	ldr	r3, [fp, #-76]
	ldr	r1, [r3, #232]
	sub	r1, r1, #1
	cmp	r1, r0
	bcs	.L1237
	mov	r8, r5
.L1239:
	ldr	ip, .L1522
	mov	r3, r0
	str	r1, [sp]
	mov	r2, r8
	ldr	r1, .L1522+32
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1197:
	ldr	ip, .L1522
	mov	r2, r8
	ldr	r1, .L1522+36
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1496:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2590]
	b	.L1204
.L1495:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #2588]
	cmp	r0, #0
	beq	.L1309
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #2589]
	cmp	r0, #0
	bne	.L1306
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #2708]
	bhi	.L1519
.L1310:
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #2712]
	bls	.L1464
	ldr	r3, .L1522
	mov	r0, #1
	ldr	r1, .L1522+40
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r6, #80]
	ldrb	r0, [r4, #2589]	@ zero_extendqisi2
	str	r3, [r4, #2712]
	b	.L1306
.L1245:
	ldr	r2, [fp, #-112]
	cmp	r3, #0
	ldr	r6, [fp, #-116]
	add	r2, r2, #11712
	ldr	r7, [fp, #-76]
	ldr	r5, [fp, #-52]
	add	r2, r2, #23
	ldr	r4, [fp, #-64]
	beq	.L1247
	add	r2, r2, r3
	add	ip, r5, #44800
	mov	r8, r6
	add	ip, ip, #132
	mov	lr, #0
	add	r2, r5, r2, lsl #2
	ldr	r9, [fp, #-108]
	ldr	r6, [fp, #-120]
	ldr	r10, [fp, #-104]
	str	r5, [fp, #-48]
	b	.L1250
.L1521:
	ldr	r0, [r4, #2624]
	ldr	r5, [ip]
	rsb	r1, r10, r0
	add	r1, r1, r5
	ldr	r5, [r2, #-1948]
	mls	r1, r5, r9, r1
	rsb	r0, r0, r1
	str	r0, [r2, #-68]
	str	r1, [r2]
.L1249:
	add	lr, lr, #1
	add	ip, ip, #4
	cmp	r3, lr
	sub	r2, r2, #4
	bls	.L1520
.L1250:
	ldrb	r1, [r6, #1]!	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1521
	ldr	r1, [ip]
	str	r1, [r2]
	ldr	r0, [r4, #2624]
	rsb	r1, r0, r1
	str	r1, [r2, #-68]
	b	.L1249
.L1480:
	ldr	r3, [r5, #216]
	mov	r0, r5
	cmp	r3, #0
	ldrne	r3, [r5, #188]
	add	r5, r5, #45056
	str	r3, [r4, #2624]
	bl	HEVC_IsNewPic
	ldr	r3, .L1522
	ldr	r1, .L1522+44
	ldr	r3, [r3, #68]
	str	r0, [r5, #68]
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1520:
	ldr	r5, [fp, #-48]
	mov	r6, r8
.L1235:
	ldr	r2, [fp, #-112]
	add	r2, r3, r2
	ldr	r3, [fp, #-84]
	cmp	r2, #16
	str	r2, [r3, #1772]
	bls	.L1227
	ldr	ip, .L1522
	mov	r3, #16
	ldr	r1, .L1522+48
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1219:
	add	r8, r5, #46592
	add	r0, r5, #2288
	add	r8, r8, #212
	add	r0, r0, #4
	ldr	r3, [r7, #228]
	mov	r1, r7
	mov	r2, r8
	bl	HEVC_DecShortTermRefPicSet.isra.19
	cmp	r0, #0
	streq	r8, [fp, #-96]
	beq	.L1222
	ldr	r3, .L1522
	mov	r0, #1
	ldr	r1, .L1522+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1515:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2583]
	b	.L1252
.L1507:
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r4, #2668]
	cmp	r0, #0
	ldr	r3, [r7, #228]
	mov	r1, r0
	sub	r3, r3, #1
	blt	.L1225
	cmp	r3, r0
	bcs	.L1226
.L1225:
	ldr	ip, .L1522
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L1522+56
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1493:
	ldr	ip, .L1522
	mov	r0, #1
	ldr	r1, .L1522+60
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1203:
	ldr	ip, .L1522
	mov	r2, r0
	ldr	r1, .L1522+64
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1500:
	ldr	r3, .L1522
	mov	r2, r0
	ldr	r1, .L1522+68
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1518:
	ldr	r7, [fp, #-76]
	mov	r8, r5
	ldr	r1, [r7, #232]
	sub	r1, r1, #1
	b	.L1239
.L1478:
	ldr	ip, .L1522
	movw	r3, #4689
	ldr	r2, .L1522+12
	mov	r0, #1
	ldr	r1, .L1522+72
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1487:
	ldr	r3, .L1522
	mov	r2, r0
	ldr	r1, .L1522+76
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1523:
	.align	2
.L1522:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC99
	.word	.LC111
	.word	.LANCHOR0+748
	.word	.LC95
	.word	.LC118
	.word	.LC108
	.word	.LC124
	.word	.LC105
	.word	.LC97
	.word	.LC120
	.word	.LC96
	.word	.LC106
	.word	.LC101
	.word	.LC102
	.word	.LC114
	.word	.LC98
	.word	.LC123
	.word	.LC35
	.word	.LC100
	.word	.LC110
	.word	.LC113
	.word	.LC116
	.word	.LC121
	.word	.LC119
	.word	.LC112
	.word	.LC115
	.word	.LC117
	.word	.LC125
	.word	.LC109
	.word	.LC107
	.word	.LC104
	.word	.LC122
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC103
.L1264:
	ldr	ip, .L1522+132
	mov	r3, #16
	ldr	r1, .L1522+80
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1492:
	ldr	r3, .L1522+132
	mov	r0, #1
	ldr	r1, .L1522+84
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1513:
	ldr	ip, .L1522+132
	mov	r2, r0
	ldr	r1, .L1522+88
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1497:
	ldr	ip, .L1522+132
	mov	r2, r0
	ldr	r1, .L1522+92
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1247:
	mov	r3, #0
	b	.L1235
.L1519:
	ldr	r3, .L1522+132
	mov	r0, #1
	ldr	r1, .L1522+96
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r6, #76]
	str	r3, [r4, #2708]
	b	.L1310
.L1491:
	ldr	r3, .L1522+132
	mov	r0, #1
	ldr	r1, .L1522+100
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1512:
	ldr	r3, .L1522+132
	mov	r2, r0
	ldr	r1, .L1522+104
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1514:
	ldr	r3, .L1522+132
	mov	r2, r0
	ldr	r1, .L1522+108
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1269:
	ldr	r3, .L1522+132
	mov	r0, #1
	ldr	r1, .L1522+112
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1502:
	ldr	r3, .L1522+132
	mov	r0, #1
	ldr	r1, .L1522+116
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1516:
	ldr	ip, .L1522+132
	mov	r3, #16
	ldr	r1, .L1522+120
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1508:
	ldr	lr, .L1522+132
	mov	ip, #16
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1522+124
	ldr	r4, [lr, #68]
	str	ip, [sp, #4]
	blx	r4
	mvn	r0, #0
	b	.L1454
.L1498:
	ldr	r3, .L1522+132
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L1522+128
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1454
.L1517:
	ldr	ip, .L1522+132
	mov	r0, #1
	ldr	r1, .L1522+136
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1454
	UNWIND(.fnend)
	.size	HEVC_DecSliceSegmentHeader, .-HEVC_DecSliceSegmentHeader
	.align	2
	.global	HEVC_DecHrdParam
	.type	HEVC_DecHrdParam, %function
HEVC_DecHrdParam:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r3
	mov	r5, r0
	mov	r9, r1
	beq	.L1546
	cmp	r2, #0
	bne	.L1571
.L1529:
	ldr	r8, .L1579
	mov	r4, r9
	mov	r6, #0
.L1543:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #40]
	cmp	r0, #0
	movne	r3, #1
	strneb	r3, [r4, #41]
	beq	.L1572
.L1531:
	ldrb	r2, [r4, #41]	@ zero_extendqisi2
	mov	r3, #0
	strb	r3, [r4, #42]
	cmp	r2, r3
	str	r3, [r4, #48]
	beq	.L1532
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldrb	r3, [r4, #42]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r4, #44]
	beq	.L1534
.L1575:
	ldr	r2, [r4, #48]
	cmp	r2, #31
	bhi	.L1573
.L1536:
	mov	r2, r4
	mov	r3, #0
.L1545:
	cmp	r3, #0
	beq	.L1574
	cmp	r3, #1
	beq	.L1569
.L1542:
	add	r3, r3, #1
	add	r2, r2, #4
	cmp	r3, #2
	bne	.L1545
.L1541:
	add	r6, r6, #1
	add	r4, r4, #1280
	cmp	r7, r6
	add	r4, r4, #12
	bcs	.L1543
	mov	r0, #0
.L1568:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1532:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r3, r0
	strb	r3, [r4, #42]
	cmp	r3, #0
	bne	.L1575
.L1534:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	mov	r2, r0
	cmp	r2, #31
	str	r0, [r4, #48]
	bls	.L1536
.L1573:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L1579+4
	blx	r3
	mov	r3, #0
	str	r3, [r4, #48]
	b	.L1536
.L1572:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #41]
	b	.L1531
.L1571:
	mov	r1, #1
	ldr	r0, [r0, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r9, #1]
	ldrh	r3, [r9]
	cmp	r3, #0
	beq	.L1529
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r9, #2]
	cmp	r0, #0
	bne	.L1576
.L1527:
	mov	r1, #4
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #4
	str	r0, [r9, #16]
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r9, #20]
	bne	.L1577
.L1528:
	mov	r1, #5
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #28]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #32]
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r9, #36]
	b	.L1529
.L1546:
	mvn	r0, #0
	b	.L1568
.L1577:
	mov	r1, #4
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r9, #24]
	b	.L1528
.L1576:
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #4]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r9, #8]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r9, #3]
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r9, #36]
	b	.L1527
.L1574:
	ldrb	r1, [r9]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1548
	add	r2, r2, #4
	mov	r3, #1
.L1569:
	ldrb	r1, [r9, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1541
.L1548:
	mov	r1, #0
	str	r6, [fp, #-52]
	mov	r10, r2
	str	r3, [fp, #-48]
	mov	r6, r1
	str	r2, [fp, #-56]
	b	.L1559
.L1544:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	add	r10, r10, #8
	str	r0, [r10, #1068]
	ldr	r3, [r4, #48]
	cmp	r3, r6
	bcc	.L1578
.L1559:
	ldr	r0, [r5, #2292]
	add	r6, r6, #1
	bl	HEVC_ue_v.isra.18
	str	r0, [r10, #52]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r10, #308]
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1544
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r10, #564]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r10, #820]
	b	.L1544
.L1578:
	ldr	r3, [fp, #-48]
	ldr	r6, [fp, #-52]
	ldr	r2, [fp, #-56]
	b	.L1542
.L1580:
	.align	2
.L1579:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC126
	UNWIND(.fnend)
	.size	HEVC_DecHrdParam, .-HEVC_DecHrdParam
	.align	2
	.global	HEVC_DecVuiParam
	.type	HEVC_DecVuiParam, %function
HEVC_DecVuiParam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	ip, .L1632
	mov	r5, r0
	mov	r4, r1
	mov	r7, r2
	add	lr, ip, #16
	ldmia	ip, {r0, r1, r2, r3}
	sub	r6, fp, #68
	cmp	r7, #0
	cmpne	r4, #0
	moveq	r8, #1
	movne	r8, #0
	stmia	r6, {r0, r1, r2, r3}
	cmp	r5, #0
	orreq	r8, r8, #1
	ldmia	lr, {r0, r1, r2, r3}
	cmp	r8, #0
	sub	lr, fp, #36
	stmdb	lr, {r0, r1, r2, r3}
	bne	.L1622
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4]
	cmp	r0, #0
	bne	.L1623
.L1585:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #1]
	cmp	r0, #0
	bne	.L1624
.L1587:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3]
	cmp	r0, #0
	bne	.L1625
.L1589:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #6]
	cmp	r0, #0
	bne	.L1626
.L1591:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #8]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #10]
	cmp	r0, #0
	beq	.L1592
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r4, #60]
	ldr	r3, [r7, #64]
	cmp	r3, #3
	bhi	.L1627
	sub	r2, fp, #36
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-32]
	mul	r0, r3, r0
	str	r0, [r4, #60]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	sub	r2, fp, #36
	str	r0, [r4, #64]
	ldr	r3, [r7, #64]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-32]
	mul	r0, r3, r0
	str	r0, [r4, #64]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	sub	r2, fp, #36
	str	r0, [r4, #68]
	ldr	r3, [r7, #64]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-16]
	mul	r0, r3, r0
	str	r0, [r4, #68]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	sub	r2, fp, #36
	str	r0, [r4, #72]
	ldr	r3, [r7, #64]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-16]
	mul	r0, r3, r0
	str	r0, [r4, #72]
.L1592:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #11]
	cmp	r0, #0
	beq	.L1594
	mov	r1, #32
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r4, #76]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #80]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #12]
	cmp	r0, #0
	bne	.L1628
.L1595:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #13]
	cmp	r0, #0
	bne	.L1629
.L1594:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #14]
	cmp	r0, #0
	moveq	r3, r0
	bne	.L1630
.L1583:
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1630:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #15]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #16]
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #17]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #4096
	str	r0, [r4, #88]
	bcs	.L1631
.L1596:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r4, #92]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r4, #96]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r4, #100]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	mov	r3, #0
	str	r0, [r4, #104]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1626:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r4, #52]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r4, #56]
	b	.L1591
.L1625:
	mov	r1, #3
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #36]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #4]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	cmp	r0, #0
	beq	.L1589
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #40]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #44]
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r4, #48]
	b	.L1589
.L1624:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #2]
	b	.L1587
.L1623:
	mov	r1, #8
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #255
	str	r0, [r4, #24]
	bne	.L1585
	mov	r1, #16
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #28]
	ldr	r0, [r5, #2292]
	bl	BsGet
	str	r0, [r4, #32]
	b	.L1585
.L1629:
	ldr	r3, [r7, #56]
	mov	r2, #1
	ldr	r1, .L1632+4
	mov	r0, r5
	bl	HEVC_DecHrdParam
	cmp	r0, #0
	beq	.L1594
	ldr	r3, .L1632+8
	mov	r0, #1
	ldr	r1, .L1632+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L1583
.L1628:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r4, #84]
	b	.L1595
.L1631:
	ldr	r3, .L1632+8
	mov	r0, #1
	ldr	r1, .L1632+16
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1596
.L1622:
	ldr	lr, .L1632+8
	movw	r3, #10442
	add	r2, ip, #32
	ldr	r1, .L1632+20
	mov	r0, #1
	ldr	r4, [lr, #68]
	blx	r4
	mvn	r3, #0
	b	.L1583
.L1627:
	ldr	r3, .L1632+8
	mov	r0, #1
	ldr	r1, .L1632+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L1583
.L1633:
	.align	2
.L1632:
	.word	.LANCHOR0+776
	.word	.LANCHOR5-3464
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC128
	.word	.LC129
	.word	.LC35
	.word	.LC127
	UNWIND(.fnend)
	.size	HEVC_DecVuiParam, .-HEVC_DecVuiParam
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
	subs	r4, r0, #0
	beq	.L1638
	ldr	r0, [r4, #2292]
	bl	BsResidBits
	cmp	r0, #0
	ble	.L1637
	ldr	r3, [r4, #2316]
	ldr	r3, [r3, #12]
	add	r3, r3, #3
	cmp	r0, r3
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1637:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1638:
	ldr	ip, .L1639
	movw	r3, #10674
	ldr	r2, .L1639+4
	mov	r0, #1
	ldr	r1, .L1639+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1640:
	.align	2
.L1639:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+828
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_MoreRbspData, .-HEVC_MoreRbspData
	.align	2
	.type	HEVC_ProcessVPS, %function
HEVC_ProcessVPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 112
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #124)
	sub	sp, sp, #124
	mov	r8, r1
	mov	r7, r0
	mov	r1, #2
	ldr	r0, [r0, #2292]
	bl	BsGet
	cmp	r0, #3
	str	r0, [r8, #12]
	beq	.L1642
	ldr	r3, .L1694
	mov	r2, r0
	ldr	r1, .L1694+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
.L1642:
	mov	r1, #6
	ldr	r0, [r7, #2292]
	bl	BsGet
	cmp	r0, #63
	str	r0, [r8, #16]
	bhi	.L1686
	mov	r1, #3
	ldr	r0, [r7, #2292]
	bl	BsGet
	cmp	r0, #8
	str	r0, [fp, #-152]
	bhi	.L1687
	ldr	r3, [fp, #-152]
	mov	r1, #1
	add	r3, r3, #1
	str	r3, [r8, #20]
	ldr	r0, [r7, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r8, #1]
	ldr	r0, [r7, #2292]
	bl	BsGet
	movw	r3, #65535
	cmp	r0, r3
	str	r0, [r8, #24]
	bne	.L1688
	add	r1, r8, #12416
	ldr	r3, [fp, #-152]
	add	r1, r1, #20
	mov	r2, #1
	mov	r0, r7
	bl	HEVC_DecPTL
	subs	r4, r0, #0
	bne	.L1689
	mov	r1, #1
	ldr	r0, [r7, #2292]
	bl	BsGet
	ldr	r3, [fp, #-152]
	cmp	r3, #0
	addgt	r5, r8, #48
	ldrgt	r6, [fp, #-152]
	strb	r0, [r8, #7]
	bgt	.L1654
	b	.L1652
.L1651:
	add	r4, r4, #1
	cmp	r4, r6
	beq	.L1652
.L1654:
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v.isra.18
	add	r0, r0, #1
	str	r0, [r5, #4]!
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r5, #32]
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r5, #64]
	ldrb	r3, [r8, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1651
	ldr	r0, [fp, #-152]
	add	r2, r4, #1
	cmp	r0, r2
	ble	.L1652
	add	r3, r4, #13
	add	r3, r8, r3, lsl #2
.L1653:
	ldr	r1, [r8, #52]
	add	r2, r2, #1
	cmp	r2, r0
	str	r1, [r3, #4]!
	ldr	r1, [r8, #84]
	str	r1, [r3, #32]
	ldr	r1, [r8, #116]
	str	r1, [r3, #64]
	bne	.L1653
.L1652:
	mov	r1, #6
	ldr	r0, [r7, #2292]
	bl	BsGet
	str	r0, [r8, #28]
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #1024
	str	r0, [r8, #32]
	bhi	.L1690
	cmp	r0, #1
	ble	.L1655
	ldr	r3, [r8, #28]
	add	r6, r8, #148
	ldr	r10, .L1694
	mov	r9, #1
.L1656:
	cmp	r3, #0
	movgt	r5, r6
	movgt	r4, #0
	ble	.L1658
.L1657:
	mov	r3, r9
	str	r4, [sp]
	mov	r1, #100
	ldr	r2, .L1694+8
	ldr	ip, [r10, #72]
	sub	r0, fp, #144
	blx	ip
	mov	r1, #1
	ldr	r0, [r7, #2292]
	add	r4, r4, r1
	bl	BsGet
	str	r0, [r5, #4]!
	ldr	r3, [r8, #28]
	cmp	r3, r4
	bgt	.L1657
.L1658:
	ldr	r2, [r8, #32]
	add	r9, r9, #1
	add	r6, r6, #4
	cmp	r2, r9
	bgt	.L1656
.L1655:
	mov	r1, #1
	ldr	r0, [r7, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #6]
	cmp	r0, #0
	beq	.L1664
	mov	r1, #32
	ldr	r0, [r7, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r8, #36]
	ldr	r0, [r7, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #40]
	ldr	r0, [r7, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #5]
	cmp	r0, #0
	bne	.L1691
.L1662:
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #1024
	str	r0, [r8, #48]
	bcs	.L1692
	cmp	r0, #0
	ble	.L1664
	add	r2, r8, #8192
	mov	r3, #1
	add	r5, r8, #4224
	mov	r4, #0
	str	r3, [r2, #148]
	mov	r6, r2
	ldr	r0, [r7, #2292]
	add	r5, r5, #24
	bl	HEVC_ue_v.isra.18
	add	r3, r8, #4096
	str	r0, [r3, #148]
	ldr	r0, [r6, #148]
	ldr	r6, [fp, #-152]
.L1665:
	uxtb	r2, r0
	mov	r3, r6
	ldr	r1, .L1694+12
	mov	r0, r7
	bl	HEVC_DecHrdParam
	add	r4, r4, #1
	cmp	r0, #0
	bne	.L1693
	ldr	r3, [r8, #48]
	cmp	r3, r4
	ble	.L1664
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r4, #0
	mov	r1, #1
	str	r0, [r5], #4
	ldrle	r0, [r5, #4092]
	ble	.L1665
	ldr	r0, [r7, #2292]
	bl	BsGet
	str	r0, [r5, #4092]
	b	.L1665
.L1664:
	mov	r1, #1
	ldr	r0, [r7, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #3]
	cmp	r0, #0
	bne	.L1681
.L1661:
	mov	r0, #0
.L1644:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1670:
	ldr	r0, [r7, #2292]
	bl	BsGet
	strb	r0, [r8, #4]
.L1681:
	mov	r0, r7
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L1670
	b	.L1661
.L1693:
	ldr	r3, .L1694
	mov	r0, #1
	ldr	r1, .L1694+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1691:
	ldr	r0, [r7, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r8, #44]
	b	.L1662
.L1688:
	ldr	r3, .L1694
	mov	r0, #1
	ldr	r1, .L1694+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1644
.L1686:
	ldr	r3, .L1694
	mov	r0, #1
	ldr	r1, .L1694+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1644
.L1689:
	ldr	r3, .L1694
	mov	r0, #1
	ldr	r1, .L1694+28
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1644
.L1687:
	ldr	r3, .L1694
	mov	r2, r0
	ldr	r1, .L1694+32
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1644
.L1690:
	ldr	ip, .L1694
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L1694+36
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1644
.L1692:
	ldr	ip, .L1694
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L1694+40
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1644
.L1695:
	.align	2
.L1694:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC130
	.word	.LC136
	.word	.LANCHOR5-3464
	.word	.LC138
	.word	.LC133
	.word	.LC131
	.word	.LC134
	.word	.LC132
	.word	.LC135
	.word	.LC137
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
	subs	r4, r0, #0
	beq	.L1703
	mov	r1, #4
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r0, #15
	mov	r6, r0
	bhi	.L1704
	movw	r7, #12820
	ldr	r3, [r4, #2296]
	mul	r5, r7, r0
	add	r2, r3, r5
	ldrb	r9, [r3, r5]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L1705
	str	r0, [r2, #8]
	mov	r0, r4
	ldr	r1, [r4, #2296]
	add	r1, r1, r5
	bl	HEVC_ProcessVPS
	subs	r8, r0, #0
	bne	.L1706
	ldr	r3, [r4, #2296]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2296]
	strb	r2, [r3, r5]
.L1698:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1705:
	ldr	r9, .L1708
	mov	r0, r4
	ldr	r1, .L1708+4
	str	r6, [r9, #-1264]
	bl	HEVC_ProcessVPS
	subs	r8, r0, #0
	bne	.L1707
	ldr	r1, .L1708+8
	mov	r3, #1
	ldr	r0, [r4, #2296]
	mov	r2, r7
	strb	r3, [r9, #-1270]
	ldr	r4, [r1, #56]
	add	r0, r0, r5
	strb	r3, [r9, #-1272]
	ldr	r1, .L1708+4
	blx	r4
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1707:
	ldr	r3, .L1708+8
	mov	r2, r6
	ldr	r1, .L1708+12
	mov	r0, #1
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1698
.L1704:
	ldr	r3, .L1708+8
	mov	r0, #1
	ldr	r1, .L1708+16
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1698
.L1706:
	ldr	r3, .L1708+8
	mov	r2, r6
	ldr	r1, .L1708+20
	mov	r0, #1
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #2296]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2296]
	strb	r9, [r3, r5]
	b	.L1698
.L1703:
	ldr	ip, .L1708+8
	movw	r3, #1549
	ldr	r2, .L1708+24
	mov	r0, #1
	ldr	r1, .L1708+28
	mvn	r8, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L1698
.L1709:
	.align	2
.L1708:
	.word	.LANCHOR6
	.word	.LANCHOR6-1272
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC140
	.word	.LC139
	.word	.LC141
	.word	.LANCHOR0+848
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_DecVPS, .-HEVC_DecVPS
	.align	2
	.type	HEVC_ProcessSPS, %function
HEVC_ProcessSPS:
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
	mov	r5, r0
	ldr	r0, [r0, #2292]
	mov	r4, r1
	bl	HEVC_ue_v.isra.18
	cmp	r0, #1
	mov	r7, r0
	str	r0, [r4, #64]
	beq	.L1711
	cmp	r0, #3
	ldr	r3, .L1898
	bhi	.L1876
	mov	r2, r0
	ldr	r1, .L1898+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
.L1713:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1876:
	ldr	r1, .L1898+8
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1711:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #8192
	str	r0, [r4, #72]
	bhi	.L1877
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #4096
	str	r0, [r4, #76]
	bhi	.L1878
	ldr	r2, [r4, #760]
	ldr	r3, [r4, #72]
	cmp	r2, #120
	mul	r0, r3, r0
	beq	.L1717
	bgt	.L1718
	cmp	r2, #60
	beq	.L1719
	ble	.L1879
	cmp	r2, #90
	beq	.L1722
	cmp	r2, #93
	beq	.L1723
	cmp	r2, #63
	bne	.L1716
	mov	r2, #61440
	mov	r3, #245760
	b	.L1724
.L1718:
	cmp	r2, #156
	beq	.L1725
	bgt	.L1726
	cmp	r2, #150
	beq	.L1725
	cmp	r2, #153
	beq	.L1725
	cmp	r2, #123
	beq	.L1717
.L1716:
	ldr	r3, .L1898
	mov	r0, #1
	ldr	r1, .L1898+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1726:
	cmp	r2, #183
	beq	.L1727
	cmp	r2, #186
	beq	.L1727
	cmp	r2, #180
	bne	.L1716
.L1727:
	mov	r2, #8912896
	mov	r3, #35651584
.L1724:
	cmp	r2, r0
	movcs	r3, #16
	strcs	r3, [r4, #236]
	bcs	.L1729
	cmp	r0, r3, lsr #1
	movls	r3, #12
	strls	r3, [r4, #236]
	bls	.L1729
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, lsr #2
	movls	r3, #8
	movhi	r3, #6
	str	r3, [r4, #236]
.L1729:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #80]
	beq	.L1732
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [r4, #64]
	ldr	r6, .L1898+16
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #860]
	mul	r0, r3, r0
	str	r0, [r4, #84]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #84]
	ldr	r1, [r4, #72]
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #860]
	mul	r0, r3, r0
	add	r2, r0, r2
	cmp	r1, r2
	str	r0, [r4, #88]
	bcc	.L1880
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [r4, #64]
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #876]
	mul	r0, r3, r0
	str	r0, [r4, #92]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #92]
	ldr	r1, [r4, #76]
	add	r6, r6, r3, lsl #2
	ldr	r3, [r6, #876]
	mul	r0, r3, r0
	add	r2, r0, r2
	cmp	r1, r2
	str	r0, [r4, #96]
	bcc	.L1881
.L1732:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, .L1898
	add	r2, r0, #8
	str	r2, [r4, #100]
	cmp	r2, #8
	streq	r3, [fp, #-56]
	beq	.L1735
	cmp	r0, #6
	bhi	.L1882
	str	r3, [fp, #-56]
	mov	r0, #1
	ldr	r3, [r3, #68]
	ldr	r1, .L1898+20
	blx	r3
	ldr	r3, .L1898+24
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L1735
	ldr	r0, [r4, #100]
	mov	r2, #0
	mov	r3, #8
	str	r2, [fp, #-52]
	mov	r1, #119
	sub	r2, fp, #52
	str	r0, [fp, #-48]
	ldr	r0, [r5, #244]
	blx	r6
.L1735:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	add	r2, r0, #8
	str	r2, [r4, #108]
	cmp	r2, #8
	beq	.L1739
	ldr	r3, [fp, #-56]
	cmp	r0, #6
	ldr	r3, [r3, #68]
	bhi	.L1883
	ldr	r1, .L1898+28
	mov	r0, #1
	blx	r3
	ldr	r3, .L1898+24
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L1739
	ldr	r0, [r4, #108]
	mov	r2, #0
	mov	r3, #8
	str	r2, [fp, #-52]
	mov	r1, #119
	sub	r2, fp, #52
	str	r0, [fp, #-48]
	ldr	r0, [r5, #244]
	blx	r6
.L1739:
	ldr	r3, [r4, #100]
	str	r3, [r5, #192]
	ldr	r3, [r4, #108]
	str	r3, [r5, #196]
	ldr	r0, [r4, #100]
	ldr	r1, [r4, #108]
	mov	r2, r0, asl #3
	mov	r3, r1, asl #3
	sub	r2, r2, r0, asl #1
	sub	r3, r3, r1, asl #1
	sub	r2, r2, #48
	sub	r3, r3, #48
	str	r2, [r4, #104]
	str	r3, [r4, #112]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #12
	bhi	.L1884
	add	r0, r0, #4
	mov	r1, #1
	str	r0, [r4, #128]
	mov	r6, r4
	str	r0, [r4, #132]
	mov	r10, #0
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #3]
	b	.L1749
.L1743:
	ldr	r2, [r4, #56]
	add	r10, r10, #1
	cmp	r2, r10
	bcc	.L1748
.L1749:
	ldr	r0, [r5, #2292]
	add	r6, r6, #4
	bl	HEVC_ue_v.isra.18
	add	r0, r0, #1
	str	r0, [r6, #376]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r8, [r6, #376]
	str	r0, [r6, #408]
	ldr	r0, [r5, #2292]
	ldr	r9, [r4, #380]
	bl	HEVC_ue_v.isra.18
	str	r0, [r6, #440]
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1743
	ldr	r0, [r4, #56]
	add	r2, r10, #1
	cmp	r2, r0
	addls	r3, r10, #95
	addls	r3, r4, r3, lsl #2
	bhi	.L1748
.L1747:
	ldr	r1, [r4, #380]
	add	r2, r2, #1
	cmp	r2, r0
	str	r1, [r3, #4]!
	ldr	r1, [r4, #412]
	str	r1, [r3, #32]
	ldr	r1, [r4, #444]
	str	r1, [r3, #64]
	bls	.L1747
.L1748:
	ldr	r3, [r4, #236]
	cmp	r8, r9
	movcc	r8, r9
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r4, #236]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #3
	str	r0, [r4, #136]
	bhi	.L1885
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #3
	str	r0, [r4, #144]
	bhi	.L1886
	ldr	r3, [r4, #136]
	add	r3, r3, #3
	str	r3, [r4, #140]
	add	r0, r0, r3
	str	r0, [r4, #148]
	sub	r2, r0, #4
	cmp	r2, #2
	bhi	.L1887
	mov	r2, #1
	ldr	r8, [r4, #72]
	mov	r6, r2, asl r0
	mov	r3, r2, asl r3
	str	r6, [r4, #156]
	str	r6, [r4, #160]
	mov	r1, r6
	str	r6, [r4, #164]
	mov	r0, r8
	str	r3, [r4, #152]
	bl	__aeabi_uidivmod
	mov	r0, r8
	cmp	r1, #0
	mov	r1, r6
	beq	.L1752
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L1753:
	ldr	r8, [r4, #76]
	mov	r1, r6
	str	r0, [r4, #240]
	mov	r0, r8
	bl	__aeabi_uidivmod
	mov	r0, r8
	cmp	r1, #0
	mov	r1, r6
	beq	.L1754
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L1755:
	str	r0, [r4, #244]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #3
	str	r0, [r4, #168]
	bhi	.L1888
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #3
	str	r0, [r4, #176]
	bhi	.L1889
	ldr	r3, [r4, #168]
	ldr	r2, [r4, #140]
	add	r3, r3, #2
	str	r3, [r4, #172]
	cmp	r3, r2
	bcs	.L1890
	add	r0, r0, r3
	str	r0, [r4, #180]
	cmp	r0, #5
	bhi	.L1759
	ldr	r3, [r4, #148]
	cmp	r0, r3
	bhi	.L1759
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [r4, #148]
	ldr	r2, [r4, #172]
	rsb	r3, r2, r3
	cmp	r0, r3
	str	r0, [r4, #200]
	bhi	.L1891
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [r4, #148]
	ldr	r2, [r4, #172]
	rsb	r3, r2, r3
	cmp	r0, r3
	str	r0, [r4, #208]
	bhi	.L1892
	ldr	r3, [r4, #200]
	add	r0, r0, #1
	mov	ip, #0
	str	r0, [r4, #212]
	add	r3, r3, #1
	str	r3, [r4, #204]
	str	ip, [r5, #228]
	mov	r2, #1
	ldr	r3, [r4, #172]
	ldr	r0, [r4, #160]
	ldr	r1, [r4, #144]
	mov	r3, r2, asl r3
	cmp	r3, r0, lsr r1
	bcs	.L1798
	mov	lr, r2
	b	.L1764
.L1799:
	mov	r2, ip
.L1764:
	str	r2, [r5, #228]
	add	ip, r2, #1
	ldr	r3, [r4, #172]
	ldr	r0, [r4, #160]
	add	r3, r2, r3
	ldr	r1, [r4, #144]
	mov	r3, lr, asl r3
	cmp	r3, r0, lsr r1
	bcc	.L1799
.L1763:
	mov	r6, #1
	add	r2, r2, r1
	str	r6, [r4, #224]
	mov	r3, #0
	str	r2, [r4, #216]
	mov	r1, r6
	str	r3, [r4, #220]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	cmp	r0, #0
	beq	.L1765
	mov	r1, r6
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #6]
	cmp	r0, #0
	bne	.L1893
.L1765:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #8]
	cmp	r6, #0
	bne	.L1766
	ldr	r2, [r4, #76]
	cmp	r2, #64
	bls	.L1894
.L1766:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #116]
	beq	.L1767
	mov	r1, #4
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #4
	add	r0, r0, #1
	str	r0, [r4, #120]
	ldr	r0, [r5, #2292]
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r4, #124]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #2
	str	r0, [r4, #184]
	bhi	.L1895
.L1768:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #2
	str	r0, [r4, #192]
	bhi	.L1896
.L1769:
	ldr	r2, [r4, #184]
	add	r2, r2, #3
	str	r2, [r4, #188]
	add	r0, r0, r2
	str	r0, [r4, #196]
	cmp	r0, #5
	bhi	.L1770
	ldr	r3, [r4, #148]
	cmp	r0, r3
	bhi	.L1770
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #9]
.L1767:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #64
	str	r0, [r4, #228]
	bhi	.L1772
	cmp	r0, #0
	beq	.L1778
	add	r9, r5, #2288
	add	r8, r4, #2720
	add	r9, r9, #4
	add	r8, r8, #12
	mov	r6, #0
	b	.L1777
.L1776:
	ldr	r3, [r4, #228]
	cmp	r3, r6
	bls	.L1778
.L1777:
	mov	r3, r6
	mov	r2, r8
	mov	r1, r4
	mov	r0, r9
	bl	HEVC_DecShortTermRefPicSet.isra.19
	add	r6, r6, #1
	add	r8, r8, #204
	cmp	r0, #0
	beq	.L1776
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1723:
	mov	r2, #245760
	mov	r3, #983040
	b	.L1724
.L1754:
	bl	__aeabi_uidiv
	b	.L1755
.L1752:
	bl	__aeabi_uidiv
	b	.L1753
.L1778:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #10]
	cmp	r0, #0
	beq	.L1775
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #32
	str	r0, [r4, #232]
	bhi	.L1781
	cmp	r0, #0
	addne	r9, r4, #244
	addne	r8, r4, #15
	movne	r6, #0
	beq	.L1775
.L1783:
	ldr	r1, [r4, #128]
	add	r6, r6, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r9, #4]!
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r8, #1]!
	ldr	r3, [r4, #232]
	cmp	r3, r6
	bhi	.L1783
.L1775:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #13]
	cmp	r0, #0
	beq	.L1780
	mov	r2, r4
	add	r1, r4, #2624
	mov	r0, r5
	bl	HEVC_DecVuiParam
	cmp	r0, #0
	bne	.L1897
.L1780:
	ldr	r3, [r4, #2648]
	ldr	r0, [r4, #2652]
	cmp	r3, #0
	ldr	r1, [r4, #2656]
	ldr	r8, [r4, #72]
	ldr	r9, [r4, #76]
	ble	.L1802
	subs	ip, r3, #255
	movne	ip, #1
	cmp	r3, #16
	movle	lr, #0
	andgt	lr, ip, #1
	cmp	lr, #0
	bne	.L1802
	cmp	r0, #0
	cmpne	r1, #0
	moveq	r2, #1
	movne	r2, #0
	cmp	r3, #255
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r2, #0
	bne	.L1803
	cmp	r3, #1
	moveq	r7, #5
	moveq	r2, r7
	beq	.L1784
	cmp	ip, #0
	ldrne	r2, .L1898+16
	addne	r3, r2, r3, lsl #3
	ldrne	r0, [r3, #892]
	ldrne	r1, [r3, #896]
	mov	r0, r0, asl #10
	bl	__aeabi_idiv
	mov	r1, r9
	mov	r6, r0
	mov	r0, r8, asl #10
	bl	__aeabi_idiv
	movw	r2, #2405
	mul	r0, r0, r6
	add	r3, r0, #1020
	cmp	r0, #0
	add	r3, r3, #3
	movlt	r0, r3
	mov	r3, r0, asr #10
	cmp	r3, r2
	movw	r2, #2262
	rsble	r1, r3, #2400
	subgt	r1, r3, #2400
	addle	r1, r1, #6
	subgt	r1, r1, #6
	cmp	r3, r2
	bgt	.L1788
	rsb	r2, r3, #2256
	add	r2, r2, #7
	cmp	r2, r1
	ble	.L1789
.L1806:
	mov	r7, #4
	mov	r2, r7
.L1784:
	ldr	r3, [fp, #-56]
	mov	r0, #22
	ldr	r1, .L1898+36
	ldr	r3, [r3, #68]
	blx	r3
	str	r7, [r4, #2644]
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #14]
	cmp	r0, #0
	bne	.L1871
.L1796:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r4]
	b	.L1713
.L1795:
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #15]
.L1871:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L1795
	b	.L1796
.L1879:
	cmp	r2, #0
	beq	.L1721
	cmp	r2, #30
	bne	.L1716
.L1721:
	mov	r2, #9216
	mov	r3, #36864
	b	.L1724
.L1894:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+40
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, .L1898+24
	ldr	r4, [r3]
	cmp	r4, #0
	mvneq	r0, #0
	beq	.L1713
	ldr	r0, [r5, #244]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	b	.L1713
.L1722:
	mov	r2, #138240
	mov	r3, #552960
	b	.L1724
.L1725:
	mov	r2, #2228224
	mov	r3, #8912896
	b	.L1724
.L1719:
	mov	r2, #30720
	mov	r3, #122880
	b	.L1724
.L1717:
	mov	r2, #557056
	mov	r3, #2228224
	b	.L1724
.L1802:
	mov	r7, #0
	mov	r2, r7
	b	.L1784
.L1893:
	add	r1, r4, #860
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	beq	.L1765
	ldr	r3, [fp, #-56]
	mov	r0, r6
	ldr	r1, .L1898+44
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1759:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+48
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1896:
	ldr	r3, [fp, #-56]
	mov	r2, r0
	ldr	r1, .L1898+52
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r0, [r4, #192]
	b	.L1769
.L1895:
	ldr	r3, [fp, #-56]
	mov	r2, r0
	ldr	r1, .L1898+56
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1768
.L1798:
	mov	r2, ip
	b	.L1763
.L1877:
	ldr	r3, .L1898
	mov	r0, r7
	ldr	r1, .L1898+60
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1884:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+64
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1885:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+68
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1882:
	ldr	r1, .L1898+72
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1883:
	ldr	r1, .L1898+76
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1888:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+80
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1788:
	sub	r2, r3, #2256
	sub	r2, r2, #7
	cmp	r2, r1
	bgt	.L1806
.L1789:
	movw	r1, #1819
	cmp	r3, r1
	bgt	.L1790
	rsb	r1, r3, #1808
	add	r1, r1, #12
	cmp	r1, r2
	ble	.L1791
.L1808:
	mov	r7, #3
	mov	r2, r7
	b	.L1784
.L1770:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+84
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1891:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+88
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1803:
	mov	r7, lr
	mov	r2, lr
	b	.L1784
.L1880:
	ldr	r3, .L1898
	mov	r0, #1
	ldr	r1, .L1898+92
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1878:
	ldr	r3, .L1898
	mov	r0, r7
	ldr	r1, .L1898+96
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1887:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+100
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1886:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+104
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1890:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+108
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1889:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+112
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1892:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+116
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1790:
	sub	r1, r3, #1808
	sub	r1, r1, #12
	cmp	r1, r2
	bgt	.L1808
.L1791:
	movw	r2, #1364
	cmp	r3, r2
	rsble	r3, r3, #1360
	subgt	r3, r3, #1360
	addle	r3, r3, #5
	subgt	r3, r3, #5
	cmp	r1, r3
	movge	r2, #1
	movlt	r7, #2
	movlt	r2, r7
	b	.L1784
.L1881:
	ldr	r3, .L1898
	mov	r0, #1
	ldr	r1, .L1898+120
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1772:
	ldr	r3, [fp, #-56]
	mov	r2, #64
	ldr	r1, .L1898+124
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1781:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+128
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1897:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1898+132
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1713
.L1899:
	.align	2
.L1898:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC143
	.word	.LC142
	.word	.LC146
	.word	.LANCHOR0
	.word	.LC150
	.word	g_event_report
	.word	.LC152
	.word	.LC169
	.word	.LC172
	.word	.LC164
	.word	.LC163
	.word	.LC160
	.word	.LC166
	.word	.LC165
	.word	.LC144
	.word	.LC153
	.word	.LC154
	.word	.LC149
	.word	.LC151
	.word	.LC157
	.word	.LC167
	.word	.LC161
	.word	.LC147
	.word	.LC145
	.word	.LC156
	.word	.LC155
	.word	.LC159
	.word	.LC158
	.word	.LC162
	.word	.LC148
	.word	.LC168
	.word	.LC170
	.word	.LC171
	UNWIND(.fnend)
	.size	HEVC_ProcessSPS, .-HEVC_ProcessSPS
	.align	2
	.global	HEVC_DecSPS
	.type	HEVC_DecSPS, %function
HEVC_DecSPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #404)
	sub	sp, sp, #404
	subs	r4, r0, #0
	beq	.L1912
	ldr	r5, .L1920
	movw	r2, #15788
	mov	r1, #0
	ldr	r0, .L1920+4
	ldr	r9, .L1920+8
	ldr	r3, [r5, #48]
	blx	r3
	mov	r2, #384
	ldr	r3, [r5, #48]
	mov	r1, #0
	sub	r0, fp, #428
	blx	r3
	mov	r1, #4
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r2, [r4, #148]
	cmp	r2, r0
	mov	r10, r0
	bls	.L1913
	mov	r1, #3
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r0, #8
	mov	r8, r0
	bhi	.L1914
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r3, r8
	mov	r2, #1
	sub	r1, fp, #428
	str	r0, [fp, #-440]
	mov	r0, r4
	bl	HEVC_DecPTL
	cmp	r0, #0
	bne	.L1915
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r2, [r4, #152]
	cmp	r0, r2
	mov	r7, r0
	bcs	.L1916
	movw	r3, #15788
	ldr	r2, [r4, #2300]
	mul	r6, r3, r0
	ldrb	r0, [fp, #-440]	@ zero_extendqisi2
	add	r2, r2, r6
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1917
	str	r10, [r2, #52]
	sub	r1, fp, #428
	ldr	ip, [r4, #2300]
	mov	r2, #384
	str	r3, [fp, #-440]
	add	ip, ip, r6
	str	r8, [ip, #56]
	ldr	ip, [r4, #2300]
	add	ip, ip, r6
	strb	r0, [ip, #2]
	ldr	r0, [r4, #2300]
	ldr	r8, [r5, #52]
	add	r0, r0, r6
	add	r0, r0, #476
	blx	r8
	ldr	r2, [r4, #2300]
	mov	r0, r4
	add	r2, r2, r6
	str	r7, [r2, #60]
	ldr	r1, [r4, #2300]
	add	r1, r1, r6
	bl	HEVC_ProcessSPS
	subs	r8, r0, #0
	bne	.L1918
	ldr	ip, [r4, #2300]
	mov	r1, #1
	add	r0, r4, #27136
	movw	r2, #15788
	add	r0, r0, #52
	strb	r1, [ip, r6]
	ldr	r3, [r4, #2300]
	add	r3, r3, r6
	strb	r1, [r3, #1]
	ldr	r1, [r4, #2300]
	ldr	r3, [r5, #52]
	add	r1, r1, r6
	blx	r3
.L1902:
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1917:
	sub	r1, fp, #428
	str	r8, [r9, #-1216]
	mov	r2, #384
	strb	r0, [r9, #-1270]
	ldr	r8, [r5, #52]
	sub	r0, r9, #796
	str	r10, [r9, #-1220]
	blx	r8
	ldr	r1, .L1920+4
	mov	r0, r4
	str	r7, [r9, #-1212]
	bl	HEVC_ProcessSPS
	subs	r8, r0, #0
	bne	.L1919
	ldr	r0, [r4, #2300]
	mov	r1, #1
	ldr	r7, [r5, #56]
	movw	r2, #15788
	strb	r1, [r9, #-1272]
	add	r0, r0, r6
	strb	r1, [r9, #-1271]
	ldr	r1, .L1920+4
	blx	r7
	ldr	r1, [r4, #2300]
	add	r0, r4, #27136
	movw	r2, #15788
	ldr	r4, [r5, #52]
	add	r1, r1, r6
	add	r0, r0, #52
	blx	r4
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1916:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L1920+12
	blx	r3
	ldr	r2, [r4, #152]
	cmp	r7, r2
	bcc	.L1911
	ldr	r3, .L1920+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L1911
	str	r2, [fp, #-432]
	mov	r3, #8
	str	r7, [fp, #-436]
	sub	r2, fp, #436
	ldr	r0, [r4, #244]
	mov	r1, #109
	blx	r5
	mvn	r8, #0
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1911:
	mvn	r8, #0
	b	.L1902
.L1913:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L1920+20
	mvn	r8, #0
	blx	r3
	b	.L1902
.L1914:
	ldr	r3, [r5, #68]
	mov	r2, #8
	ldr	r1, .L1920+24
	mov	r0, #1
	blx	r3
	mvn	r8, #0
	b	.L1902
.L1915:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L1920+28
	mvn	r8, #0
	blx	r3
	b	.L1902
.L1918:
	mov	r2, r7
	ldr	r1, .L1920+32
	ldr	r5, [r5, #68]
	mov	r0, #1
	blx	r5
	ldr	r1, [r4, #2300]
	mov	r2, #1
	ldr	r3, [fp, #-440]
	mvn	r8, #0
	strb	r2, [r1, r6]
	ldr	r2, [r4, #2300]
	add	r6, r2, r6
	strb	r3, [r6, #1]
	b	.L1902
.L1919:
	ldr	r1, [r4, #2300]
	add	r0, r4, #27136
	ldr	r3, [r5, #52]
	movw	r2, #15788
	add	r1, r1, r6
	add	r0, r0, #52
	blx	r3
	ldr	r3, [r5, #68]
	mov	r2, r7
	ldr	r1, .L1920+36
	mov	r0, #1
	mvn	r8, #0
	blx	r3
	b	.L1902
.L1912:
	ldr	ip, .L1920
	movw	r3, #2276
	ldr	r2, .L1920+40
	mov	r0, #1
	ldr	r1, .L1920+44
	mvn	r8, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L1902
.L1921:
	.align	2
.L1920:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR6-1272
	.word	.LANCHOR6
	.word	.LC176
	.word	g_event_report
	.word	.LC173
	.word	.LC174
	.word	.LC175
	.word	.LC178
	.word	.LC177
	.word	.LANCHOR0+1028
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_DecSPS, .-HEVC_DecSPS
	.align	2
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
	mov	r7, #1
	mov	r5, r0
	strb	r7, [r1, #16]
	str	r7, [r1, #68]
	mov	r4, r1
	str	r7, [r1, #72]
	ldr	r0, [r0, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #0
	str	r0, [r4, #32]
	blt	.L1923
	ldr	r3, [r5, #152]
	cmp	r0, r3
	bge	.L1923
	ldr	r3, [r5, #2300]
	movw	r6, #15788
	mla	r6, r6, r0, r3
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2030
	mov	r1, r7
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #2]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #4]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	str	r0, [r4, #36]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #3]
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	add	r0, r0, #1
	str	r0, [r4, #40]
	cmp	r0, #15
	bhi	.L2031
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	add	r0, r0, #1
	str	r0, [r4, #44]
	cmp	r0, #15
	bhi	.L2032
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	add	r2, r0, #26
	str	r2, [r4, #48]
	ldr	r3, [r6, #104]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L2033
	mov	r1, r7
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #6]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	streq	r0, [r4, #52]
	bne	.L2034
.L1932:
	str	r0, [r4, #56]
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #12
	str	r0, [r4, #60]
	cmp	r3, #24
	bhi	.L2035
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #12
	str	r0, [r4, #64]
	cmp	r3, #24
	bhi	.L2036
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #13]
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #14]
	bne	.L2037
	ldr	r3, [r6, #240]
	strh	r3, [r4, #176]	@ movhi
	ldr	r3, [r6, #244]
	strh	r3, [r4, #216]	@ movhi
.L1971:
	ldr	r0, [r4, #68]
	cmp	r0, #0
	ble	.L1976
.L1970:
	ldr	ip, [r6, #160]
	add	r1, r4, #174
	mov	r3, #0
.L1975:
	ldrsh	r2, [r1, #2]!
	add	r3, r3, #1
	mul	r2, ip, r2
	cmp	r2, #64
	bhi	.L1974
	ldr	lr, [r6, #72]
	cmp	lr, #64
	bhi	.L2038
.L1974:
	cmp	r3, r0
	blt	.L1975
.L1976:
	ldr	r1, [r4, #72]
	cmp	r1, #0
	ble	.L1973
	ldr	r0, [r6, #160]
	ldrsh	r2, [r4, #216]
	mul	r2, r0, r2
	cmp	r2, #63
	addhi	r1, r1, #107
	addhi	r3, r4, #216
	addhi	r1, r4, r1, lsl #1
	bhi	.L1979
	b	.L1977
.L1980:
	ldrsh	r2, [r3, #2]!
	mul	r2, r0, r2
	cmp	r2, #63
	bls	.L1977
.L1979:
	cmp	r3, r1
	bne	.L1980
.L1973:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #17]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #18]
	cmp	r0, #0
	bne	.L2039
.L1982:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #21]
	cmp	r0, #0
	beq	.L1985
	add	r1, r4, #260
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	bne	.L2040
.L1985:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #22]
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	add	r2, r0, #2
	str	r2, [r4, #84]
	cmp	r2, #1
	ble	.L1986
	ldr	r3, [r6, #148]
	cmp	r2, r3
	bhi	.L1986
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #23]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #24]
	cmp	r0, #0
	bne	.L2017
	b	.L1990
.L1989:
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #25]
.L2017:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L1989
.L1990:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2034:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #3
	str	r0, [r4, #52]
	bls	.L1932
	ldr	r3, .L2051
	mov	r0, r7
	ldr	r1, .L2051+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2018
.L2037:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #19
	add	r2, r0, #1
	str	r2, [r4, #68]
	bhi	.L2041
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #21
	add	r3, r0, #1
	str	r3, [r4, #72]
	bhi	.L2042
	ldr	r2, [r4, #68]
	cmp	r2, #10
	bgt	.L2043
	cmp	r3, #11
	ble	.L1940
	ldr	ip, .L2051
	mov	r2, #11
	ldr	r1, .L2051+8
.L2027:
	ldr	r4, [ip, #68]
	mov	r0, #1
	blx	r4
	ldr	r3, .L2051+12
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2022
.L2024:
	mov	r3, #0
	ldr	r0, [r5, #244]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
.L2018:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1977:
	ldr	r3, .L2051
	ldr	r1, .L2051+16
.L2026:
	ldr	r3, [r3, #68]
	mov	r0, #1
	blx	r3
	ldr	r3, .L2051+12
	ldr	r4, [r3]
	cmp	r4, #0
	bne	.L2024
.L2022:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2038:
	ldr	r3, .L2051
	ldr	r1, .L2051+20
	b	.L2026
.L2033:
	ldr	ip, .L2051
	mov	r0, r7
	ldr	r1, .L2051+24
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2018
.L1940:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	ldr	r7, [r4, #68]
	uxtb	r0, r0
	strb	r0, [r4, #15]
	cmp	r0, #0
	bne	.L1954
	cmp	r7, #1
	addgt	r9, r4, #90
	movgt	r8, r0
	bgt	.L1952
	b	.L2044
.L2046:
	cmp	r3, r2
	bhi	.L1950
	ldr	r7, [r4, #68]
	add	r8, r8, #1
	sub	r3, r7, #1
	cmp	r3, r8
	ble	.L2045
.L1952:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r9, #2]!	@ movhi
	ldr	r2, [r6, #240]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2046
.L1950:
	ldr	ip, .L2051
	mov	r0, #1
	str	r2, [sp]
	mov	r2, r8
	ldr	r1, .L2051+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2018
.L2043:
	mov	r3, r2
	ldr	ip, .L2051
	mov	r2, #10
	ldr	r1, .L2051+32
	b	.L2027
.L2039:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #19]
	ldr	r0, [r5, #2292]
	bl	BsGet
	uxtb	r7, r0
	strb	r7, [r4, #20]
	cmp	r7, #0
	bne	.L1982
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #76]
	bhi	.L2047
.L1984:
	ldr	r0, [r5, #2292]
	bl	HEVC_se_v.isra.21
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #80]
	bls	.L1982
	ldr	r3, .L2051
	mov	r0, #1
	ldr	r1, .L2051+36
	ldr	r3, [r3, #68]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #80]
	b	.L1982
.L1954:
	cmp	r7, #0
	addgt	r3, r4, #174
	movgt	r8, #0
	ble	.L1944
.L1962:
	ldr	r10, [r6, #240]
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
	bne	.L1962
.L1944:
	ldr	r10, [r4, #72]
	cmp	r10, #0
	addgt	r3, r4, #214
	movgt	r8, #0
	ble	.L1961
.L1963:
	ldr	r2, [r6, #244]
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
	bne	.L1963
.L1961:
	cmp	r7, #1
	bne	.L1969
	ldr	r0, [r4, #72]
	cmp	r0, #1
	beq	.L1970
.L1969:
	mov	r1, #1
	ldr	r0, [r5, #2292]
	bl	BsGet
	strb	r0, [r4, #16]
	b	.L1971
.L1923:
	ldr	r3, .L2051
	mov	r2, r0
	ldr	r1, .L2051+40
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2018
.L2030:
	ldr	r3, .L2051
	mov	r2, r0
	ldr	r1, .L2051+44
	mov	r0, r7
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2018
.L2031:
	ldr	r3, .L2051
	mov	r0, r7
	ldr	r1, .L2051+48
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2018
.L2032:
	ldr	r3, .L2051
	mov	r0, r7
	ldr	r1, .L2051+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2018
.L2035:
	ldr	r3, .L2051
	mov	r0, #1
	ldr	r1, .L2051+56
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2018
.L2036:
	ldr	r3, .L2051
	mov	r0, #1
	ldr	r1, .L2051+60
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2018
.L1986:
	ldr	r3, .L2051
	mov	r0, #1
	ldr	r1, .L2051+64
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2022
.L2045:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	ble	.L1948
.L1947:
	add	r8, r4, #130
	mov	r7, #0
	b	.L1959
.L2049:
	cmp	r3, r2
	bhi	.L1957
	ldr	r3, [r4, #72]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L2048
.L1959:
	ldr	r0, [r5, #2292]
	bl	HEVC_ue_v.isra.18
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #244]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2049
.L1957:
	ldr	ip, .L2051
	mov	r0, #1
	str	r2, [sp]
	mov	r2, r7
	ldr	r1, .L2051+68
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2018
.L2041:
	ldr	ip, .L2051
	mov	r3, #20
	ldr	r1, .L2051+72
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2018
.L2047:
	ldr	r3, .L2051
	mov	r0, #1
	ldr	r1, .L2051+76
	ldr	r3, [r3, #68]
	blx	r3
	str	r7, [r4, #76]
	b	.L1984
.L2048:
	ldr	r7, [r4, #68]
.L1948:
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1954
.L1955:
	sub	r2, r7, #1
	ldrh	r3, [r6, #240]
	add	ip, r4, r7, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #174]	@ movhi
	ble	.L1964
	add	r8, r7, #44
	add	r1, r4, #90
	add	lr, r4, #174
	add	r8, r4, r8, lsl #1
.L1965:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #174]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #174]	@ movhi
	bne	.L1965
.L1964:
	sxth	r3, r3
	cmp	r3, #0
	ble	.L2050
	ldr	r1, [r4, #72]
	ldrh	r3, [r6, #244]
	sub	r2, r1, #1
	add	ip, r4, r1, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #214]	@ movhi
	ble	.L1967
	add	r8, r1, #64
	add	lr, r4, #214
	add	r1, r4, #130
	add	r8, r4, r8, lsl #1
.L1968:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #214]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #214]	@ movhi
	bne	.L1968
.L1967:
	sxth	r3, r3
	cmp	r3, #0
	bgt	.L1961
	ldr	ip, .L2051
	mov	r0, #1
	ldr	r1, .L2051+80
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2018
.L2042:
	ldr	ip, .L2051
	mov	r2, r3
	ldr	r1, .L2051+84
	mov	r3, #22
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2018
.L2040:
	ldr	r3, .L2051
	mov	r0, #1
	ldr	r1, .L2051+88
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2018
.L2044:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	bgt	.L1947
	b	.L1955
.L2050:
	ldr	ip, .L2051
	mov	r0, #1
	ldr	r1, .L2051+92
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2018
.L2052:
	.align	2
.L2051:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC184
	.word	.LC190
	.word	g_event_report
	.word	.LC196
	.word	.LC195
	.word	.LC183
	.word	.LC191
	.word	.LC189
	.word	.LC198
	.word	.LC179
	.word	.LC180
	.word	.LC181
	.word	.LC182
	.word	.LC185
	.word	.LC186
	.word	.LC200
	.word	.LC192
	.word	.LC187
	.word	.LC197
	.word	.LC194
	.word	.LC188
	.word	.LC199
	.word	.LC193
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	beq	.L2060
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	ldr	r3, [r4, #156]
	cmp	r0, r3
	mov	r6, r0
	bcs	.L2061
	movw	r7, #2024
	ldr	r3, [r4, #2304]
	mul	r5, r7, r0
	add	r2, r3, r5
	ldrb	r9, [r3, r5]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L2062
	str	r0, [r2, #28]
	mov	r0, r4
	ldr	r1, [r4, #2304]
	add	r1, r1, r5
	bl	HEVC_ProcessPPS
	subs	r8, r0, #0
	bne	.L2063
	ldr	r3, [r4, #2304]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2304]
	strb	r2, [r3, r5]
.L2055:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2062:
	ldr	r9, .L2065
	mov	r0, r4
	ldr	r1, .L2065+4
	str	r6, [r9, #-1244]
	bl	HEVC_ProcessPPS
	subs	r8, r0, #0
	bne	.L2064
	ldr	r1, .L2065+8
	mov	r3, #1
	ldr	r0, [r4, #2304]
	mov	r2, r7
	strb	r3, [r9, #-1271]
	ldr	r4, [r1, #56]
	add	r0, r0, r5
	strb	r3, [r9, #-1272]
	ldr	r1, .L2065+4
	blx	r4
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2064:
	ldr	r3, .L2065+8
	mov	r2, r6
	ldr	r1, .L2065+12
	mov	r0, #1
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2055
.L2061:
	ldr	ip, .L2065+8
	mov	r2, r0
	ldr	r1, .L2065+16
	mov	r0, #1
	mvn	r8, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L2055
.L2063:
	ldr	r3, .L2065+8
	mov	r2, r6
	ldr	r1, .L2065+12
	mov	r0, #1
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #2304]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2304]
	strb	r9, [r3, r5]
	b	.L2055
.L2060:
	ldr	ip, .L2065+8
	movw	r3, #2703
	ldr	r2, .L2065+20
	mov	r0, #1
	ldr	r1, .L2065+24
	mvn	r8, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L2055
.L2066:
	.align	2
.L2065:
	.word	.LANCHOR6
	.word	.LANCHOR6-1272
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC202
	.word	.LC201
	.word	.LANCHOR0+1040
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_DecPPS, .-HEVC_DecPPS
	.align	2
	.global	HEVC_SeiMessage
	.type	HEVC_SeiMessage, %function
HEVC_SeiMessage:
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
	clz	r7, r0
	cmp	r2, #0
	cmpne	r1, #0
	mov	r4, r0
	mov	r7, r7, lsr #5
	mov	r6, r1
	moveq	r5, #1
	movne	r5, #0
	orrs	r5, r7, r5
	mov	r8, r2
	beq	.L2069
	b	.L2256
.L2071:
	add	r5, r5, #255
	bl	BsSkip
.L2069:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2292]
	beq	.L2071
	bl	BsGet
	mov	r9, #0
	str	r0, [r6]
	add	r5, r0, r5
	b	.L2072
.L2073:
	add	r9, r9, #255
	bl	BsSkip
.L2072:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2292]
	beq	.L2073
	bl	BsGet
	str	r0, [r6, #4]
	add	r9, r0, r9
	ldr	r3, [r4, #2316]
	ldr	r3, [r3, #16]
	cmp	r3, #39
	beq	.L2257
	cmp	r5, #5
	beq	.L2163
	cmp	r5, #132
	beq	.L2164
	cmp	r9, #0
	movne	r5, #0
	beq	.L2093
.L2172:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r5, r9
	bne	.L2172
	b	.L2093
.L2163:
	add	r1, r6, #3136
	add	r0, r4, #2288
	add	r1, r1, #12
	add	r0, r0, #4
	mov	r2, r9
	bl	HEVC_Sei_User_Data_Unregistered.isra.14
	cmp	r0, #0
	bne	.L2253
.L2093:
	ldr	r2, [r4, #2292]
	mov	r9, r9, asl #3
	ldr	r3, [r2, #24]
	mov	r0, r2
	ldr	r5, [r2, #28]
	rsb	r5, r5, r3
	bl	BsIsByteAligned
	cmp	r0, #0
	cmpne	r5, r9
	beq	.L2258
.L2173:
	mov	r0, #0
.L2244:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2258:
	ldr	r3, .L2280
	mov	r2, #32
	ldr	r1, [r4, #2292]
	sub	r0, fp, #76
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-48]
	rsb	r3, r2, r3
	cmp	r9, r3
	bhi	.L2259
.L2178:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #12]
	b	.L2179
.L2180:
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #16]
.L2179:
	ldr	r0, [r4, #2292]
	bl	BsIsByteAligned
	mov	r1, #1
	cmp	r0, #0
	beq	.L2180
	b	.L2173
.L2257:
	cmp	r5, #47
	beq	.L2076
	bls	.L2260
	cmp	r5, #130
	beq	.L2085
	bls	.L2261
	cmp	r5, #133
	beq	.L2089
	cmp	r5, #134
	beq	.L2090
	cmp	r5, #131
	beq	.L2091
.L2075:
	cmp	r9, #0
	movne	r5, #0
	beq	.L2093
.L2161:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r5, r9
	bne	.L2161
	b	.L2093
.L2164:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r5, r6, #23552
	add	r10, r6, #20480
	mov	r8, r5
	add	r5, r5, #123
	add	r8, r8, #171
	mov	r3, r0
	cmp	r3, #0
	str	r0, [r10, #3244]
	str	r0, [r10, #3248]
	bne	.L2166
.L2262:
	add	r7, r5, #16
.L2167:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r5, #1]!
	cmp	r7, r5
	bne	.L2167
.L2168:
	cmp	r7, r8
	mov	r5, r7
	beq	.L2093
	ldr	r3, [r10, #3248]
	cmp	r3, #0
	beq	.L2262
.L2166:
	cmp	r3, #1
	beq	.L2263
	cmp	r3, #2
	addne	r7, r5, #16
	bne	.L2168
	mov	r1, #32
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r7, r5, #16
	mov	r3, r0, lsr #24
	strb	r0, [r5, #4]
	strb	r3, [r5, #1]
	mov	r3, r0, lsr #16
	mov	r0, r0, lsr #8
	strb	r3, [r5, #2]
	strb	r0, [r5, #3]
	b	.L2168
.L2260:
	cmp	r5, #5
	beq	.L2163
	bls	.L2264
	cmp	r5, #23
	beq	.L2082
	cmp	r5, #45
	beq	.L2083
	cmp	r5, #6
	bne	.L2075
	cmn	r6, #3264
	movne	r3, #0
	moveq	r3, #1
	orrs	r3, r7, r3
	bne	.L2253
	ldr	r0, [r4, #2292]
	bl	HEVC_se_v.isra.21
	mov	r1, #1
	str	r0, [r6, #3268]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3264]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r6, #3265]
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	b	.L2093
.L2259:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsShow
	cmp	r0, #0
	bne	.L2265
.L2184:
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r6, #8]
	b	.L2178
.L2265:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsSkip
	ldr	r3, [fp, #-52]
	ldr	r5, [fp, #-48]
	rsb	r5, r5, r3
	b	.L2176
.L2177:
	bl	BsSkip
	ldr	r3, [fp, #-52]
	ldr	r5, [fp, #-48]
	rsb	r5, r5, r3
.L2176:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsShow
	cmp	r9, r5
	mov	r1, #1
	movls	r3, #0
	movhi	r3, #1
	cmp	r0, #0
	movne	r2, #0
	andeq	r2, r3, #1
	sub	r0, fp, #76
	cmp	r2, #0
	bne	.L2177
	cmp	r3, #0
	beq	.L2178
	b	.L2184
.L2089:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r10, r6, #20480
	mov	r1, #1
	strb	r0, [r10, #2408]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	uxtb	r0, r0
	strb	r0, [r10, #2409]
	cmp	r0, #0
	ldr	r0, [r4, #2292]
	beq	.L2152
	bl	BsGet
	strb	r0, [r10, #2410]
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #63
	str	r0, [r10, #2416]
	bhi	.L2266
	ldrb	r7, [r10, #2410]	@ zero_extendqisi2
	cmp	r0, r7
	addcs	r5, r7, #5696
	addcs	r5, r5, #28
	addcs	r5, r6, r5, lsl #2
	bcc	.L2157
.L2156:
	mov	r1, #3
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r7, r7, #1
	str	r0, [r5, #4]!
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r5, #256]
	ldr	r3, [r10, #2416]
	cmp	r7, r3
	bls	.L2156
.L2157:
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	mov	r3, #0
	strb	r3, [r10, #2412]
	b	.L2155
.L2160:
	bl	HEVC_MoreRbspData
	cmp	r0, #0
	beq	.L2093
.L2155:
	mov	r2, r8
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	mov	r0, r4
	beq	.L2160
	ldr	r4, .L2280
	mov	r0, #1
	ldr	r1, .L2280+4
	ldr	r3, [r4, #68]
	blx	r3
.L2095:
	ldr	r3, [r4, #68]
	mov	r0, #1
	ldr	r1, .L2280+8
	blx	r3
	mvn	r0, #0
	b	.L2244
.L2082:
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	mov	r1, #1
	str	r0, [r6, #3340]
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #3336]
	cmp	r0, #0
	ldrne	r3, [r6, #3352]
	beq	.L2267
.L2120:
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L2093
.L2183:
	.word	.L2121
	.word	.L2123
	.word	.L2124
	.word	.L2128
	.word	.L2133
.L2133:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r0, #255
	str	r0, [r6, #3372]
	beq	.L2268
.L2134:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r6, #3338]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #3388]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #3392]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #3396]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #3400]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #3404]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #3408]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #3388]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #3412]
	b	.L2093
.L2128:
	mov	r1, #16
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r0, #256
	str	r0, [r6, #3416]
	bhi	.L2129
	cmp	r0, #0
	addne	r5, r6, #3408
	movne	r7, #0
	addne	r5, r5, #8
	beq	.L2093
.L2132:
	ldr	r1, [r6, #3344]
	add	r7, r7, #1
	ldr	r0, [r4, #2292]
	add	r1, r1, #7
	bic	r1, r1, #7
	bl	BsGet
	str	r0, [r5, #4]!
	ldr	r1, [r6, #3348]
	ldr	r0, [r4, #2292]
	add	r1, r1, #7
	bic	r1, r1, #7
	bl	BsGet
	str	r0, [r5, #1024]
	ldr	r3, [r6, #3416]
	cmp	r7, r3
	bcc	.L2132
	b	.L2093
.L2124:
	ldr	r3, [r6, #3348]
	mov	r5, #1
	movs	r5, r5, asl r3
	addne	r8, r6, #5440
	movne	r7, #0
	addne	r8, r8, #24
	beq	.L2127
.L2126:
	ldr	r1, [r6, #3344]
	add	r7, r7, #1
	ldr	r0, [r4, #2292]
	add	r1, r1, #7
	bic	r1, r1, #7
	bl	BsGet
	cmp	r5, r7
	str	r0, [r8, #4]!
	bne	.L2126
.L2127:
	add	r3, r5, #532
	ldr	r1, [r6, #3344]
	mov	r2, #1
	add	r3, r6, r3, lsl #2
	mov	r2, r2, asl r1
	str	r2, [r3, #3340]
	b	.L2093
.L2121:
	mov	r1, #32
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #3356]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #3360]
	b	.L2093
.L2123:
	mov	r1, #32
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #3364]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #3368]
	b	.L2093
.L2263:
	mov	r1, #16
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r7, r5, #16
	mov	r3, r0, lsr #8
	strb	r0, [r5, #2]
	strb	r3, [r5, #1]
	b	.L2168
.L2261:
	cmp	r5, #128
	beq	.L2087
	cmp	r5, #129
	bne	.L2075
	mov	r1, #4
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #3176]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3172]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r6, #3173]
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #15
	str	r0, [r6, #3180]
	bgt	.L2145
	cmp	r0, #0
	addge	r7, r6, #3168
	movge	r5, #0
	addge	r7, r7, #12
	blt	.L2251
.L2147:
	ldr	r0, [r4, #2292]
	add	r5, r5, #1
	bl	HEVC_ue_v.isra.18
	str	r0, [r7, #4]!
	ldr	r3, [r6, #3180]
	cmp	r5, r3
	ble	.L2147
.L2251:
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	b	.L2093
.L2264:
	cmp	r5, #0
	beq	.L2080
	cmp	r5, #1
	bne	.L2075
	ldrb	r3, [r8, #2633]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2269
.L2109:
	ldr	r5, .L2280+12
	sub	r3, r5, #3456
	ldrh	r3, [r3, #-8]
	cmp	r3, #0
	beq	.L2251
	ldr	r1, [r5, #-3432]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r5, #-3428]
	add	r1, r1, #1
	add	r0, r0, #1
	str	r0, [r6, #1080]
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldrb	r3, [r5, #-3462]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r6, #1084]
	beq	.L2251
	ldr	r1, [r5, #-3452]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r5, #-3462]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r6, #1088]
	beq	.L2251
	ldrb	r3, [r5, #-3461]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2251
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	mov	r1, #1
	str	r0, [r6, #1092]
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #1069]
	cmp	r0, #0
	bne	.L2270
.L2112:
	ldr	r3, [r6, #1092]
	cmp	r3, #255
	bhi	.L2182
	add	r7, r6, #1088
	mov	r8, #0
	add	r7, r7, #8
	b	.L2114
.L2113:
	ldr	r3, [r6, #1092]
	cmp	r8, r3
	bhi	.L2251
.L2114:
	ldr	r0, [r4, #2292]
	add	r8, r8, #1
	bl	HEVC_ue_v.isra.18
	str	r0, [r7, #4]!
	ldrb	r3, [r6, #1069]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2113
	ldr	r1, [r5, #-3456]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r7, #1024]
	b	.L2113
.L2256:
	ldr	ip, .L2280
	movw	r3, #3575
	ldr	r2, .L2280+16
	mov	r0, #1
	ldr	r1, .L2280+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2244
.L2076:
	add	r3, r6, #3312
	add	r3, r3, #4
	cmp	r3, #0
	movne	r3, r7
	orreq	r3, r7, #1
	cmp	r3, #0
	bne	.L2253
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #3318]
	cmp	r0, #0
	bne	.L2251
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3316]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r6, #3317]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #3320]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r6, #3319]
	b	.L2251
.L2083:
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	mov	r1, #1
	str	r0, [r6, #3284]
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #3272]
	cmp	r0, #0
	bne	.L2135
	mov	r1, #7
	ldr	r0, [r4, #2292]
	bl	BsGet
	sub	r3, r0, #3
	mov	r2, r0
	cmp	r3, #2
	str	r0, [r6, #3288]
	bhi	.L2271
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #6
	strb	r0, [r6, #3273]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #3292]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3274]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3275]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3276]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3277]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3278]
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldrb	r3, [r6, #3273]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r6, #3279]
	bne	.L2137
	ldr	r3, [r6, #3288]
	cmp	r3, #5
	beq	.L2137
	mov	r1, #4
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #4
	str	r0, [r6, #3296]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #4
	str	r0, [r6, #3300]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #4
	str	r0, [r6, #3304]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #3308]
.L2137:
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #3312]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r6, #3280]
.L2135:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r6, #3281]
	b	.L2251
.L2253:
	ldr	r4, .L2280
	b	.L2095
.L2091:
	add	r3, r6, #3312
	add	r3, r3, #12
	cmp	r3, #0
	movne	r3, r7
	orreq	r3, r7, #1
	cmp	r3, #0
	bne	.L2253
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #3324]
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #3328]
	ldr	r0, [r4, #2292]
	bl	BsToNextByte
	b	.L2093
.L2090:
	add	r3, r6, #3328
	add	r3, r3, #4
	cmp	r3, #0
	orreq	r7, r7, #1
	cmp	r7, #0
	bne	.L2253
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r6, #3332]
	b	.L2093
.L2080:
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #15
	mov	r2, r0
	str	r0, [r6, #28]
	bhi	.L2272
	ldr	r5, .L2280+12
	ldrb	r3, [r5, #-3462]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2096
	ldrb	r0, [r6, #24]	@ zero_extendqisi2
.L2097:
	cmp	r0, #0
	bne	.L2273
.L2098:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	ldr	r7, .L2280+12
	strb	r0, [r6, #25]
	ldr	r1, [r5, #-3432]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r6, #40]
	ldr	r2, [r5, #-3416]
	cmp	r2, #31
	bhi	.L2274
.L2099:
	mov	r7, #1
	subs	r3, r7, #1
	mov	r10, r6
	ldr	r2, .L2280+12
	beq	.L2275
.L2100:
	cmp	r3, #1
	beq	.L2276
.L2104:
	cmp	r7, #1
	bhi	.L2251
.L2102:
	add	r7, r7, #1
	add	r10, r10, #16
	subs	r3, r7, #1
	bne	.L2100
.L2275:
	ldrb	r1, [r5, #-3464]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L2104
	ldr	r1, [r2, #-3416]
	cmn	r1, #1
	movne	r8, r10
	bne	.L2219
	b	.L2102
.L2087:
	add	r3, r6, #4096
	ldr	r0, [r4, #2292]
	str	r3, [fp, #-80]
	mov	r5, r3
	bl	HEVC_ue_v.isra.18
	str	r0, [r5, #2400]
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #1024
	str	r0, [r5, #2404]
	bhi	.L2139
	cmp	r0, #0
	beq	.L2251
	add	r5, r6, #6464
	add	r7, r6, #10560
	add	r8, r6, #18688
	add	r5, r5, #36
	add	r7, r7, #40
	add	r8, r8, #104
	mov	r10, #0
	b	.L2143
.L2142:
	ldr	r3, [fp, #-80]
	add	r8, r8, #4
	ldr	r2, [r3, #2404]
	cmp	r10, r2
	bcs	.L2251
.L2143:
	mov	r1, #6
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #4]!
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r7], #4
	ldr	r2, [r5]
	sub	r2, r2, #19
	cmp	r2, #1
	bls	.L2141
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	str	r0, [r7, #4092]
.L2141:
	cmp	r10, #0
	add	r10, r10, #1
	beq	.L2142
	ldr	r0, [r4, #2292]
	bl	HEVC_se_v.isra.21
	str	r0, [r8]
	b	.L2142
.L2085:
	ldr	r3, .L2280+24
	ldr	r5, .L2280+12
	cmn	r6, #3248
	cmpne	r3, #0
	moveq	r3, #1
	movne	r3, #0
	orrs	r3, r7, r3
	bne	.L2253
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	ldrb	r3, [r5, #-3461]	@ zero_extendqisi2
	cmp	r3, #0
	streq	r3, [r6, #3256]
	str	r0, [r6, #3252]
	bne	.L2277
.L2150:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #3248]
	cmp	r0, #0
	beq	.L2251
	ldr	r1, [r5, #-3452]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #3260]
	b	.L2251
.L2152:
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r10, #2411]
	cmp	r0, #0
	bne	.L2157
	mov	r1, #3
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r10, #2932]
	ldr	r0, [r4, #2292]
	bl	HEVC_ue_v.isra.18
	cmp	r0, #63
	str	r0, [r10, #2936]
	addls	r5, r6, #23296
	movls	r7, #0
	addls	r5, r5, #120
	bhi	.L2278
.L2159:
	mov	r1, #6
	ldr	r0, [r4, #2292]
	bl	BsGet
	add	r7, r7, #1
	str	r0, [r5, #4]!
	ldr	r3, [r10, #2936]
	cmp	r7, r3
	bls	.L2159
	b	.L2157
.L2269:
	mov	r1, #4
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #2
	str	r0, [r6, #1072]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, r5
	str	r0, [r6, #1076]
	ldr	r0, [r4, #2292]
	bl	BsGet
	strb	r0, [r6, #1068]
	b	.L2109
.L2267:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r6, #3337]
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r1, #8
	str	r0, [r6, #3344]
	ldr	r0, [r4, #2292]
	bl	BsGet
	cmp	r0, #8
	mov	r2, r0
	str	r0, [r6, #3348]
	bhi	.L2279
	mov	r1, #8
	ldr	r0, [r4, #2292]
	bl	BsGet
	mov	r3, r0
	str	r0, [r6, #3352]
	b	.L2120
.L2277:
	ldr	r1, [r5, #-3456]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #3256]
	b	.L2150
.L2274:
	ldr	r3, .L2280
	mov	r0, #1
	ldr	r1, .L2280+28
	ldr	r3, [r3, #68]
	blx	r3
	mov	r3, #0
	str	r3, [r7, #-3416]
	b	.L2099
.L2273:
	ldr	r1, [r5, #-3432]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #32]
	ldr	r1, [r5, #-3428]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #36]
	b	.L2098
.L2096:
	mov	r1, #1
	ldr	r0, [r4, #2292]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #24]
	b	.L2097
.L2272:
	ldr	r4, .L2280
	mov	r0, #1
	ldr	r1, .L2280+32
	ldr	r3, [r4, #68]
	blx	r3
	b	.L2095
.L2276:
	ldrb	r3, [r5, #-3463]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2251
	ldr	r3, [r2, #-3416]
	cmn	r3, #1
	beq	.L2251
	mov	r8, r10
	mov	r3, #0
.L2219:
	ldr	r1, [r5, #-3436]
	add	r3, r3, #1
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	str	r2, [fp, #-84]
	str	r3, [fp, #-80]
	str	r3, [fp, #-88]
	bl	BsGet
	str	r0, [r8, #44]
	ldr	r1, [r5, #-3436]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	ldr	r3, [fp, #-80]
	ldr	r2, [fp, #-84]
	str	r0, [r8, #48]
	ldrb	r1, [r5, #-3462]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2106
	ldrb	r1, [r6, #24]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L2107
.L2106:
	ldr	r1, [r5, #-3436]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	str	r2, [fp, #-84]
	str	r3, [fp, #-80]
	bl	BsGet
	str	r0, [r8, #52]
	ldr	r1, [r5, #-3436]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	ldr	r2, [fp, #-84]
	ldr	r3, [fp, #-80]
	str	r0, [r8, #56]
.L2107:
	ldr	r1, [r5, #-3416]
	add	r8, r8, #32
	add	r1, r1, #1
	cmp	r3, r1
	bcc	.L2219
	b	.L2104
.L2145:
	ldr	r4, .L2280
	mov	r0, #1
	ldr	r1, .L2280+36
	ldr	r3, [r4, #68]
	blx	r3
	b	.L2095
.L2278:
	ldr	r4, .L2280
	mov	r0, #1
	ldr	r1, .L2280+40
	ldr	r3, [r4, #68]
	blx	r3
	b	.L2095
.L2139:
	ldr	r4, .L2280
	mov	r0, #1
	ldr	r1, .L2280+44
	ldr	r3, [r4, #68]
	blx	r3
	b	.L2095
.L2271:
	ldr	r4, .L2280
	mov	r0, #1
	ldr	r1, .L2280+48
	ldr	r3, [r4, #68]
	blx	r3
	b	.L2095
.L2182:
	ldr	r4, .L2280
	mov	r0, #1
	ldr	r1, .L2280+52
	ldr	r3, [r4, #68]
	blx	r3
	b	.L2095
.L2270:
	ldr	r1, [r5, #-3456]
	ldr	r0, [r4, #2292]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #1096]
	b	.L2112
.L2268:
	mov	r1, #32
	ldr	r0, [r4, #2292]
	bl	BsGet
	str	r0, [r6, #3376]
	b	.L2134
.L2129:
	ldr	r4, .L2280
	mov	r0, #1
	ldr	r1, .L2280+56
	ldr	r3, [r4, #68]
	blx	r3
	b	.L2095
.L2266:
	ldr	r4, .L2280
	mov	r2, #64
	ldr	r1, .L2280+60
	mov	r0, #1
	ldr	r3, [r4, #68]
	blx	r3
	b	.L2095
.L2279:
	ldr	r4, .L2280
	mov	r0, #1
	ldr	r1, .L2280+64
	ldr	r3, [r4, #68]
	blx	r3
	b	.L2095
.L2281:
	.align	2
.L2280:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC213
	.word	.LC214
	.word	.LANCHOR5
	.word	.LANCHOR0+1052
	.word	.LC35
	.word	.LANCHOR5-3464
	.word	.LC204
	.word	.LC203
	.word	.LC210
	.word	.LC212
	.word	.LC209
	.word	.LC208
	.word	.LC205
	.word	.LC207
	.word	.LC211
	.word	.LC206
	UNWIND(.fnend)
	.size	HEVC_SeiMessage, .-HEVC_SeiMessage
	.align	2
	.global	HEVC_More_Rbsp_Data
	.type	HEVC_More_Rbsp_Data, %function
HEVC_More_Rbsp_Data:
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
	beq	.L2286
	ldr	r0, [r4, #2292]
	ldr	r2, [r0, #16]
	ldr	r3, [r0, #24]
	mov	r2, r2, asl #3
	cmp	r2, r3
	ble	.L2287
	mov	r1, #8
	bl	BsShow
	subs	r0, r0, #128
	movne	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2287:
	ldr	ip, .L2288
	mov	r0, #1
	ldr	r1, .L2288+4
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2286:
	ldr	ip, .L2288
	movw	r3, #10692
	ldr	r2, .L2288+8
	mov	r0, #1
	ldr	r1, .L2288+12
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2289:
	.align	2
.L2288:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC215
	.word	.LANCHOR0+1068
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_More_Rbsp_Data, .-HEVC_More_Rbsp_Data
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
	subs	r4, r0, #0
	addne	r6, r4, #3424
	addne	r5, r4, #27136
	addne	r6, r6, #4
	addne	r5, r5, #52
	bne	.L2295
	b	.L2300
.L2293:
	ldr	r0, [r4, #2292]
	bl	BsIsByteAligned
	cmp	r0, #0
	mov	r0, r4
	beq	.L2301
	bl	HEVC_More_Rbsp_Data
	subs	r7, r0, #0
	beq	.L2302
.L2295:
	mov	r2, r5
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	beq	.L2293
	ldr	r3, .L2303
	mov	r0, #1
	ldr	r1, .L2303+4
	mvn	r7, #0
	ldr	r3, [r3, #68]
	blx	r3
.L2292:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2301:
	ldr	r3, .L2303
	mvn	r7, #0
	ldr	r1, .L2303+8
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2302:
	ldr	r0, [r4, #2292]
	mov	r1, #8
	bl	BsGet
	cmp	r0, #128
	beq	.L2292
	ldr	r3, .L2303
	mov	r2, r0
	ldr	r1, .L2303+12
	mov	r0, #1
	mvn	r7, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2292
.L2300:
	ldr	ip, .L2303
	movw	r3, #3618
	ldr	r2, .L2303+16
	mov	r0, #1
	ldr	r1, .L2303+20
	mvn	r7, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L2292
.L2304:
	.align	2
.L2303:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC213
	.word	.LC216
	.word	.LC217
	.word	.LANCHOR0+1088
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_DecSEI, .-HEVC_DecSEI
	.align	2
	.global	HEVC_ReleaseNAL
	.type	HEVC_ReleaseNAL, %function
HEVC_ReleaseNAL:
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
	cmp	r0, #15
	mov	r6, r0
	mov	r5, r1
	bhi	.L2315
	cmp	r1, #0
	beq	.L2316
	ldr	r7, .L2317
	add	r8, r1, #56
	mov	r4, r1
	mov	r3, #0
	str	r3, [r1, #36]
	str	r3, [r1, #40]
.L2309:
	ldr	r3, [r4, #44]
	mov	r0, r6
	cmp	r3, #0
	beq	.L2308
	ldr	r1, [r4, #68]
	bl	SM_ReleaseStreamSeg
	ldr	r1, [r4, #48]
	ldr	r3, [r4, #44]
	mov	r0, #7
	ldr	r9, [r7, #68]
	str	r1, [sp]
	ldr	r2, .L2317+4
	ldr	r1, .L2317+8
	blx	r9
	mov	r3, #0
	str	r3, [r4, #44]
	str	r3, [r4, #60]
	str	r3, [r4, #48]
.L2308:
	add	r4, r4, #28
	cmp	r4, r8
	bne	.L2309
	ldr	r3, [r7, #48]
	mov	r0, r5
	mov	r2, #100
	mov	r1, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L2315:
	ldr	ip, .L2317
	movw	r3, #10847
	ldr	r2, .L2317+4
	mov	r0, #1
	ldr	r1, .L2317+12
.L2314:
	ldr	ip, [ip, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L2316:
	mov	r0, r1
	ldr	ip, .L2317
	movw	r3, #10848
	ldr	r2, .L2317+16
	ldr	r1, .L2317+20
	b	.L2314
.L2318:
	.align	2
.L2317:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1100
	.word	.LC220
	.word	.LC35
	.word	.LC218
	.word	.LC219
	UNWIND(.fnend)
	.size	HEVC_ReleaseNAL, .-HEVC_ReleaseNAL
	.align	2
	.type	Hevc_InitDecBuffers, %function
Hevc_InitDecBuffers:
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
	add	r3, r0, #24576
	mov	r8, r0
	add	r0, r0, #2704
	add	r1, r8, #2640
	ldr	r3, [r3, #2604]
	add	r2, r8, #2496
	mov	lr, #0
	add	r1, r1, #4
	add	r2, r2, #12
	add	ip, r8, #2576
	ldr	r3, [r3, #236]
	mov	r6, #17
	add	r3, r3, #1
	cmp	r3, #17
	movhi	r3, #17
	str	r3, [r0, #-216]
	add	r0, r0, #8
	mov	r3, lr
	str	lr, [r8, #2492]
	str	lr, [r8, #2504]
	str	lr, [r8, #2508]
	str	lr, [r8, #2500]
	str	lr, [r8, #2496]
.L2322:
	subs	r6, r6, #1
	str	r3, [r0, #4]!
	str	r3, [ip, #4]!
	str	r3, [r1, #4]!
	str	r3, [r2, #4]!
	bne	.L2322
	add	r4, r8, #57344
	ldr	r10, .L2345
	add	r4, r4, #40
	mov	r7, r6
.L2323:
	ldr	r3, [r10, #48]
	mov	r2, #504
	mov	r0, r4
	mov	r1, #0
	blx	r3
	str	r7, [r4, #196]
	add	r7, r7, #1
	mov	r5, #0
	cmp	r7, #20
	sub	r3, r4, #72
	strb	r5, [r4, #-72]
	mov	r2, #20
	str	r3, [r4, #-4]
	mov	r9, #16
	str	r5, [r4, #-68]
	add	r4, r4, #584
	strb	r5, [r4, #-655]
	str	r5, [r4, #-644]
	strb	r5, [r4, #-654]
	str	r5, [r4, #-608]
	str	r2, [r4, #-632]
	str	r9, [r4, #-628]
	ldr	r3, .L2345
	bne	.L2323
	ldr	r3, [r3, #48]
	mov	r2, #200
	mov	r1, r5
	add	r0, r8, #2784
	blx	r3
	add	r2, r8, #2304
	add	r2, r2, #12
	add	r3, r8, #2384
	mov	r1, r5
	str	r9, [r8, #2784]
	str	r5, [r8, #2788]
.L2324:
	str	r1, [r2, #4]!
	cmp	r2, r3
	mov	r0, #0
	bne	.L2324
	add	r1, r8, #2448
	add	lr, r8, #40960
	add	r1, r1, #4
	mov	ip, r0
	str	r0, [lr, #2736]
.L2325:
	str	ip, [r3, #4]!
	cmp	r3, r1
	mov	r2, #0
	bne	.L2325
	str	r2, [lr, #2740]
	ldr	r1, [r8, #180]
	cmp	r1, r2
	movne	r3, r2
	addne	r2, r8, #2096
	movne	r0, r3
	beq	.L2330
.L2329:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L2329
.L2330:
	ldr	r2, [r8, #160]
	cmp	r2, #0
	beq	.L2344
	mov	r4, #0
	add	r7, r8, #53248
	mov	r5, r4
.L2332:
	ldr	r3, [r7, #4056]
	add	r4, r4, #1
	add	r3, r3, r6
	ldr	r3, [r3, #24]
	cmp	r3, #0
	mov	r1, r3
	beq	.L2331
	ldr	r0, [r8, #2316]
	cmp	r3, r0
	beq	.L2331
	ldr	r0, [r8, #244]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r7, #4056]
	add	r3, r3, r6
	str	r5, [r3, #24]
	ldr	r2, [r8, #160]
.L2331:
	cmp	r2, r4
	add	r6, r6, #28
	bhi	.L2332
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2344:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2346:
	.align	2
.L2345:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Hevc_InitDecBuffers, .-Hevc_InitDecBuffers
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
	beq	.L2358
	ldr	ip, [r6, #2492]
	add	r8, r6, #2496
	cmp	ip, #0
	addne	r8, r8, #12
	movne	r3, #0
	movne	lr, #1
	movne	r1, r8
	beq	.L2373
.L2352:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	streqb	lr, [r2, #2]
	ldreq	ip, [r6, #2492]
	cmp	ip, r3
	bhi	.L2352
.L2353:
	mov	r4, r6
	mov	r7, #17
	mov	r5, #0
	mov	r3, #-2147483647
	str	r3, [r6, #212]
.L2350:
	ldr	r3, [r8, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L2354
	ldr	r1, [r3, #32]
	ldr	r0, [r6, #244]
	bl	FSP_ClearLogicFs
.L2354:
	ldr	r3, [r4, #2580]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2355
	ldr	r1, [r3, #32]
	ldr	r0, [r6, #244]
	bl	FSP_ClearLogicFs
.L2355:
	ldr	r3, [r4, #2648]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2356
	ldr	r1, [r3, #32]
	ldr	r0, [r6, #244]
	bl	FSP_ClearLogicFs
.L2356:
	ldr	r3, [r4, #2716]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2357
	ldr	r1, [r3, #32]
	ldr	r0, [r6, #244]
	bl	FSP_ClearLogicFs
.L2357:
	subs	r7, r7, #1
	str	r5, [r4, #2716]
	str	r5, [r4, #2648]
	add	r4, r4, #4
	str	r5, [r4, #2576]
	str	r5, [r4, #2508]
	bne	.L2350
	mov	r0, r6
	bl	Hevc_InitDecBuffers
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2373:
	add	r8, r8, #12
	b	.L2353
.L2358:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_EmptyFrmFromDPB, .-HEVC_EmptyFrmFromDPB
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
	subs	r4, r0, #0
	beq	.L2379
	ldr	r1, [r4, #2316]
	cmp	r1, #0
	beq	.L2378
	ldr	r0, [r4, #244]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2316]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2378:
	mov	r0, r1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2379:
	ldr	ip, .L2380
	movw	r3, #11319
	ldr	r2, .L2380+4
	mov	r0, #1
	ldr	r1, .L2380+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2381:
	.align	2
.L2380:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1116
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_ClearCurrNal, .-HEVC_ClearCurrNal
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
	cmp	r0, #0
	beq	.L2385
	bl	HEVC_ClearCurrNal
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2385:
	ldr	ip, .L2386
	movw	r3, #11350
	ldr	r2, .L2386+4
	mov	r0, #1
	ldr	r1, .L2386+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2387:
	.align	2
.L2386:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1136
	.word	.LC35
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r7, r0, #0
	beq	.L2389
	ldr	r2, [r7, #160]
	cmp	r2, #0
	addne	r8, r7, #53248
	movne	r4, #0
	movne	r5, r4
	movne	r6, r4
	beq	.L2394
.L2393:
	ldr	r3, [r8, #4056]
	add	r5, r5, #1
	add	r3, r3, r4
	ldr	r1, [r3, #24]
	cmp	r1, #0
	beq	.L2392
	ldr	r0, [r7, #244]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r8, #4056]
	add	r3, r3, r4
	str	r6, [r3, #24]
	ldr	r2, [r7, #160]
.L2392:
	cmp	r2, r5
	add	r4, r4, #28
	bhi	.L2393
.L2394:
	mov	r3, #0
	mov	r2, #2
	str	r3, [r7, #208]
	mov	r0, r3
	str	r3, [r7, #224]
	str	r3, [r7, #216]
	str	r2, [r7, #172]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2389:
	ldr	ip, .L2399
	movw	r3, #11360
	ldr	r2, .L2399+4
	mov	r0, #1
	ldr	r1, .L2399+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2400:
	.align	2
.L2399:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1156
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_ClearAllSlice, .-HEVC_ClearAllSlice
	.align	2
	.global	HEVC_InitDPB
	.type	HEVC_InitDPB, %function
HEVC_InitDPB:
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
	subs	r5, r0, #0
	mov	r8, r1
	beq	.L2454
	bl	HEVC_ClearAllSlice
	add	r9, r5, #2496
	add	r9, r9, #12
	mov	r4, r5
	mov	r6, #17
	mov	r7, #0
.L2408:
	ldr	r3, [r9, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L2404
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
.L2404:
	ldr	r3, [r4, #2580]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2405
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
.L2405:
	ldr	r3, [r4, #2648]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2406
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
.L2406:
	ldr	r3, [r4, #2716]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2407
	ldr	r1, [r3, #32]
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
.L2407:
	subs	r6, r6, #1
	str	r7, [r4, #2716]
	str	r7, [r4, #2648]
	add	r4, r4, #4
	str	r7, [r4, #2576]
	str	r7, [r4, #2508]
	bne	.L2408
	add	r7, r5, #24576
	ldr	r4, .L2457
	mov	r9, #0
	mov	r2, #200
	ldr	r3, [r7, #2604]
	mov	r1, r9
	add	r0, r5, #2784
	ldr	r3, [r3, #236]
	str	r9, [r5, #2492]
	add	r3, r3, #1
	str	r9, [r5, #2504]
	cmp	r3, #17
	str	r9, [r5, #2508]
	str	r9, [r5, #2500]
	movhi	r3, #17
	str	r9, [r5, #2496]
	str	r3, [r5, #2488]
	ldr	r3, [r4, #48]
	blx	r3
	add	r2, r5, #2304
	add	r2, r2, #12
	add	r3, r5, #2384
	mov	r0, r9
	mov	r1, #16
	str	r9, [r5, #2788]
	str	r1, [r5, #2784]
.L2411:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L2411
	add	r2, r5, #2448
	add	ip, r5, #40960
	add	r2, r2, #4
	mov	r0, r1
	str	r1, [ip, #2736]
.L2412:
	str	r0, [r3, #4]!
	cmp	r3, r2
	mov	r1, #0
	bne	.L2412
	cmp	r8, r1
	str	r1, [ip, #2740]
	bne	.L2413
	ldr	r3, [r5, #2308]
	ldr	r3, [r3, #908]
	cmp	r3, #1
	beq	.L2413
.L2414:
	ldr	r1, [r5, #180]
	cmp	r1, #0
	addne	r2, r5, #2096
	movne	r3, #0
	movne	r0, r3
	beq	.L2424
.L2423:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L2423
.L2424:
	ldr	r2, [r5, #160]
	cmp	r2, #0
	addne	r8, r5, #53248
	movne	r4, #0
	movne	r7, r4
	beq	.L2422
.L2426:
	ldr	r3, [r8, #4056]
	add	r4, r4, #1
	add	r3, r3, r6
	ldr	r3, [r3, #24]
	cmp	r3, #0
	mov	r1, r3
	beq	.L2425
	ldr	r0, [r5, #2316]
	cmp	r3, r0
	beq	.L2425
	ldr	r0, [r5, #244]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r8, #4056]
	add	r3, r3, r6
	str	r7, [r3, #24]
	ldr	r2, [r5, #160]
.L2425:
	cmp	r4, r2
	add	r6, r6, #28
	bcc	.L2426
.L2422:
	mov	r0, #0
.L2452:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2413:
	mov	r8, #20
	str	r8, [r5, #176]
	str	r8, [r5, #180]
	mov	r2, #32
	ldr	r3, [r7, #2604]
	sub	r0, fp, #76
	ldr	r10, [r4, #48]
	mov	r1, #0
	ldr	r7, [r3, #240]
	ldr	r9, [r3, #244]
	ldr	ip, [r3, #148]
	mov	r7, r7, asl ip
	mov	r9, r9, asl ip
	blx	r10
	ldr	r2, [r5, #2308]
	str	r9, [fp, #-48]
	mov	r3, #0
	str	r7, [fp, #-68]
	ldr	r2, [r2, #28]
	str	r9, [fp, #-64]
	cmp	r2, #24
	str	r7, [fp, #-60]
	str	r9, [fp, #-56]
	str	r7, [fp, #-52]
	strb	r3, [fp, #-76]
	strb	r3, [fp, #-75]
	beq	.L2415
	ldr	r2, [r5, #2488]
	strb	r3, [fp, #-71]
	mov	r3, #5
	strb	r3, [fp, #-70]
	strb	r2, [fp, #-72]
.L2427:
	sub	r1, fp, #76
	ldr	r0, [r5, #244]
	mov	r3, #0
	strb	r8, [fp, #-69]
	mov	r7, #1
	strb	r3, [fp, #-73]
	strb	r7, [fp, #-74]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L2416
	ldr	r1, [r5, #2308]
	sub	r3, fp, #80
	ldr	r0, [r5, #244]
	ldr	r2, [r1, #24]
	ldr	r1, [r1, #20]
	bl	FSP_PartitionFsMemory
	cmp	r0, #0
	bne	.L2455
	ldr	r3, [r5, #2308]
	ldr	r3, [r3, #908]
	cmp	r3, #1
	beq	.L2430
	ldr	r0, [r5, #244]
	bl	FSP_GetTotalValidFsNum
	cmp	r0, #20
	movgt	r0, #20
	ble	.L2456
.L2419:
	str	r0, [r5, #176]
	b	.L2414
.L2415:
	mov	r8, #1
	strb	r3, [fp, #-71]
	strb	r8, [fp, #-72]
	mov	r3, #5
	strb	r3, [fp, #-70]
	b	.L2427
.L2456:
	ldr	r0, [r5, #244]
	bl	FSP_GetTotalValidFsNum
	b	.L2419
.L2416:
	mov	r0, r7
	ldr	r3, [r4, #68]
	ldr	r1, .L2457+4
	blx	r3
.L2418:
	ldr	r3, [r5, #2308]
	ldr	r3, [r3, #908]
	cmp	r3, #1
	beq	.L2430
	ldr	r3, [r4, #68]
	mov	r0, #0
	ldr	r2, .L2457+8
	ldr	r1, .L2457+12
	blx	r3
	mvn	r0, #4
	b	.L2452
.L2430:
	mvn	r0, #1
	b	.L2452
.L2454:
	ldr	ip, .L2457
	movw	r3, #7649
	ldr	r2, .L2457+8
	mov	r0, #1
	ldr	r1, .L2457+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2452
.L2455:
	mov	r0, r7
	ldr	r3, [r4, #68]
	ldr	r1, .L2457+20
	blx	r3
	b	.L2418
.L2458:
	.align	2
.L2457:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC222
	.word	.LANCHOR0+1176
	.word	.LC223
	.word	.LC35
	.word	.LC221
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
	subs	r7, r0, #0
	beq	.L2460
	ldr	r2, [r7, #160]
	cmn	r2, #1
	addne	r6, r7, #53248
	movne	r4, #0
	movne	r5, r4
	bne	.L2464
	b	.L2465
.L2463:
	add	r3, r2, #1
	cmp	r3, r5
	bls	.L2465
.L2464:
	ldr	r1, [r6, #3252]
	add	r5, r5, #1
	add	r1, r1, r4
	add	r4, r4, #100
	ldr	r3, [r1, #36]
	cmp	r3, #1
	bne	.L2463
	ldr	r0, [r7, #244]
	bl	HEVC_ReleaseNAL
	ldr	r2, [r7, #160]
	add	r3, r2, #1
	cmp	r3, r5
	bhi	.L2464
.L2465:
	mov	r0, #0
	strb	r0, [r7, #4]
	str	r0, [r7, #140]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2460:
	ldr	ip, .L2467
	movw	r3, #11384
	ldr	r2, .L2467+4
	mov	r0, #1
	ldr	r1, .L2467+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2468:
	.align	2
.L2467:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1192
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_ClearAllNal, .-HEVC_ClearAllNal
	.align	2
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
	ldr	r8, .L2482
	mov	r7, r0
	ldr	r1, .L2482+4
	mov	r0, #22
	add	r4, r7, #57344
	mov	r6, #0
	ldr	r3, [r8, #68]
	add	r4, r4, #40
	blx	r3
	mov	r3, #-2147483647
	mov	r0, r7
	str	r3, [r7, #212]
	bl	HEVC_ClearAllNal
	add	r0, r7, #50944
	add	r0, r0, #56
	mov	r5, r6
	bl	ResetVoQueue
	mov	r9, #20
.L2470:
	strb	r5, [r4, #-72]
	mov	r3, #16
	str	r5, [r4, #-68]
	mov	r0, r4
	strb	r5, [r4, #-71]
	mov	r2, #504
	str	r5, [r4, #-60]
	mov	r1, #0
	strb	r5, [r4, #-70]
	str	r9, [r4, #-48]
	str	r3, [r4, #-44]
	ldr	r3, [r8, #48]
	blx	r3
	str	r6, [r4, #196]
	add	r6, r6, #1
	sub	r3, r4, #72
	cmp	r6, #20
	str	r5, [r4, #-24]
	str	r3, [r4, #-4]
	add	r4, r4, #584
	bne	.L2470
	add	r3, r7, #2096
	add	r1, r7, #2176
	mov	r2, #0
.L2471:
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L2471
	ldr	r3, [r7, #160]
	cmp	r3, #0
	addne	ip, r7, #53248
	movne	r3, #0
	movne	r0, r3
	movne	r1, r3
	beq	.L2475
.L2474:
	ldr	r2, [ip, #4056]
	add	r0, r0, #1
	str	r1, [r2, r3]
	ldr	r2, [ip, #4056]
	add	r2, r2, r3
	str	r1, [r2, #20]
	ldr	r2, [ip, #4056]
	add	r2, r2, r3
	add	r3, r3, #28
	str	r1, [r2, #24]
	ldr	r2, [r7, #160]
	cmp	r2, r0
	bhi	.L2474
.L2475:
	ldr	r3, [r8, #48]
	mov	r2, #200
	mov	r1, #0
	add	r0, r7, #2784
	blx	r3
	add	ip, r7, #2704
	add	r0, r7, #2640
	add	r1, r7, #2496
	add	ip, ip, #8
	add	r0, r0, #4
	add	r1, r1, #12
	add	lr, r7, #2576
	mov	r3, #16
	mov	r2, #17
	str	r3, [r7, #2784]
	mov	r3, #0
.L2473:
	subs	r2, r2, #1
	str	r3, [ip, #4]!
	str	r3, [r0, #4]!
	str	r3, [lr, #4]!
	str	r3, [r1, #4]!
	bne	.L2473
	add	r1, r7, #2304
	add	ip, r7, #2448
	add	r1, r1, #12
	add	ip, ip, #4
	add	r3, r7, #2384
	mov	r0, r2
	mov	lr, #17
	str	r2, [r7, #2492]
	str	r2, [r7, #2496]
	str	r2, [r7, #2500]
	str	r2, [r7, #2504]
	str	r2, [r7, #2508]
	str	lr, [r7, #2488]
.L2476:
	str	r0, [r3, #4]!
	cmp	r3, ip
	str	r0, [r1, #4]!
	mov	r4, #0
	bne	.L2476
	add	r0, r7, #43520
	mov	r6, #2
	mov	r1, r4
	str	r4, [r7, #2316]
	str	r4, [r7, #208]
	movw	r2, #3732
	str	r4, [r7, #224]
	add	r0, r0, #16
	str	r4, [r7, #216]
	add	r5, r7, #2448
	str	r6, [r7, #172]
	add	r5, r5, #8
	ldr	r3, [r8, #48]
	blx	r3
	add	r1, r7, #40960
	add	r2, r7, #45056
	mov	lr, #32
	str	r6, [r1, #2636]
	mov	r3, #1
	mov	ip, #20
	str	r3, [r2, #68]
	mov	r1, r4
	strb	r3, [r7]
	strb	r3, [r7, #2]
	mov	r2, lr
	mov	r3, #8
	str	r6, [r7, #2192]
	strb	r4, [r7, #3]
	mov	r0, r5
	strb	r4, [r7, #1]
	mov	r6, #64
	strb	r4, [r7, #7]
	str	r4, [r7, #168]
	str	lr, [r7, #304]
	mvn	lr, #-2147483648
	str	ip, [r7, #176]
	str	ip, [r7, #180]
	mov	ip, #16
	str	r3, [r7, #192]
	str	r3, [r7, #196]
	str	r3, [r7, #296]
	mov	r3, #256
	str	lr, [r7, #200]
	movw	lr, #1025
	str	ip, [r7, #276]
	str	ip, [r7, #300]
	mov	ip, #4
	str	r3, [r7, #284]
	mov	r3, #6
	ldr	r4, [r8, #48]
	str	r6, [r7, #280]
	str	lr, [r7, #288]
	str	ip, [r7, #292]
	str	r3, [r7, #2180]
	str	r3, [r7, #2184]
	str	r3, [r7, #2188]
	blx	r4
	str	r5, [r7, #2292]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2483:
	.align	2
.L2482:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC224
	UNWIND(.fnend)
	.size	HEVC_InitDecPara, .-HEVC_InitDecPara
	.align	2
	.global	HEVCDEC_Init
	.type	HEVCDEC_Init, %function
HEVCDEC_Init:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r1
	str	r0, [fp, #-60]
	moveq	r5, #1
	movne	r5, #0
	beq	.L2533
	ldr	r8, [fp, #-60]
	movw	r2, #6936
	mov	r1, r5
	movt	r2, 1
	add	r3, r8, #49152
	str	r3, [fp, #-76]
	ldr	r6, [r3, #2192]
	mov	r7, r3
	ldr	r3, .L2538
	ldr	r3, [r3, #48]
	blx	r3
	str	r6, [r7, #2192]
	str	r4, [r8, #2308]
	str	r5, [r8, #2312]
	ldr	r3, [r4, #28]
	cmp	r3, #25
	beq	.L2534
	ldr	r0, [fp, #-60]
	mov	r3, #17
	mov	r1, #65
	mov	r2, #200
	str	r3, [r0, #148]
	str	r3, [r0, #152]
	mov	r3, #210
	str	r1, [r0, #156]
	str	r2, [r0, #144]
	str	r3, [r0, #160]
	ldr	r0, [r4, #668]
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L2535
.L2489:
	ldr	r6, [fp, #-60]
	movw	r2, #12820
	movw	lr, #15788
	mov	r9, #1360
	add	r5, r6, #53248
	ldr	r0, [r6, #2308]
	ldr	r8, [r6, #148]
	ldr	r3, [r6, #152]
	ldr	r0, [r0, #664]
	ldr	ip, [r6, #156]
	mul	r2, r2, r8
	add	r0, r1, r0
	mul	r3, lr, r3
	movw	r1, #2024
	mul	r1, r1, ip
	add	ip, r0, r2
	add	lr, ip, r3
	str	r0, [r6, #2296]
	str	ip, [r6, #2300]
	str	lr, [r6, #2304]
	add	r10, lr, r1
	str	r10, [r5, #3248]
	ldr	r7, [r6, #144]
	mla	r7, r9, r7, r10
	mov	r9, #100
	str	r7, [r5, #3252]
	ldr	r6, [r6, #160]
	mla	r6, r6, r9, r9
	add	r7, r7, r6
	str	r7, [r5, #4056]
	ldr	r4, [r4, #688]
	cmp	r4, #0
	bne	.L2490
	ldr	r3, .L2538
	mov	r1, r4
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r6, [fp, #-60]
	mov	r2, #1
	movw	ip, #15788
	mov	r1, r4
	ldr	r3, [r6, #2296]
	strb	r2, [r3]
	ldr	r3, .L2538
	ldr	r2, [r6, #152]
	ldr	r0, [r6, #2300]
	ldr	r3, [r3, #48]
	mul	r2, ip, r2
	blx	r3
	ldr	r2, [r6, #156]
	ldr	r3, .L2538
	movw	ip, #2024
	mov	r1, r4
	ldr	r0, [r6, #2304]
	mul	r2, ip, r2
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r2, [r6, #144]
	ldr	r3, .L2538
	mov	ip, #1360
	mov	r1, r4
	ldr	r0, [r5, #3248]
	mul	r2, ip, r2
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r2, [r6, #160]
	ldr	r3, .L2538
	mov	r1, r4
	ldr	r0, [r5, #3252]
	mla	r2, r2, r9, r9
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6, #160]
	ldr	r2, .L2538
	mov	r1, r4
	ldr	r0, [r5, #4056]
	ldr	r4, [r2, #48]
	mov	r2, r3, asl #5
	sub	r2, r2, r3, asl #2
	blx	r4
	ldr	r8, [r6, #148]
	ldr	r3, [r6, #152]
	movw	r2, #12820
	movw	r4, #15788
	ldr	r1, [r6, #156]
	mul	r2, r2, r8
	movw	lr, #2024
	mul	r3, r4, r3
	ldr	r0, [r6, #2296]
	mul	r1, lr, r1
	ldr	ip, [r6, #2300]
	ldr	lr, [r6, #2304]
.L2490:
	sub	r2, r2, #12800
	sub	r1, r1, #2016
	sub	r2, r2, #20
	sub	r3, r3, #15744
	add	r0, r0, r2
	ldr	r2, [fp, #-60]
	sub	r1, r1, #8
	sub	r3, r3, #44
	add	r4, r2, #24576
	add	r1, lr, r1
	mov	lr, r2
	add	ip, ip, r3
	str	r1, [r4, #2608]
	add	r3, r2, #7
	str	r0, [r4, #2600]
	add	r1, r2, #136
	str	ip, [r4, #2604]
	mvn	r2, #0
	str	r8, [r0, #8]
	ldr	r0, [r4, #2608]
	ldr	ip, [lr, #152]
	str	ip, [r0, #28]
	ldr	r0, [r4, #2604]
	ldr	ip, [lr, #156]
	str	ip, [r0, #60]
.L2491:
	strb	r2, [r3, #1]!
	cmp	r3, r1
	bne	.L2491
	ldr	r2, [fp, #-60]
	mov	r3, #2
	mov	r10, r3
	add	r1, r2, #308
	str	r1, [fp, #-72]
	strb	r3, [r2, #24]
	ldr	r3, .L2538+4
	mov	r5, r3
	mov	r3, #0
	strb	r3, [r2, #12]
	mov	r3, #1
	strb	r3, [r2, #16]
	mov	r3, #3
	strb	r3, [r2, #40]
	mov	r3, #4
	strb	r3, [r2, #72]
.L2503:
	cmp	r10, #15
	bgt	.L2492
	cmp	r10, #8
	mul	r9, r10, r10
	beq	.L2536
	cmp	r9, #0
	movne	r3, r5
	beq	.L2492
.L2494:
	mov	r6, #0
	rsb	r7, r10, #1
	str	r5, [fp, #-48]
	mov	r8, r6
	mov	r5, r3
.L2500:
	cmp	r8, r10
	blt	.L2515
	rsb	r4, r10, r8
	sub	r2, r10, #1
	add	r4, r4, #1
.L2501:
	cmp	r4, r10
	mvn	r3, r2
	mov	r3, r3, lsr #31
	movge	r3, #0
	cmp	r3, #0
	beq	.L2498
	mla	r0, r10, r2, r4
	add	ip, r5, r6, lsl #2
	mov	r1, r6
.L2499:
	add	r1, r1, #1
	sub	r2, r2, #1
	rsb	r3, r6, r1
	str	r0, [ip], #4
	add	r3, r3, r4
	mvn	lr, r2
	cmp	r3, r10
	mov	lr, lr, lsr #31
	add	r0, r0, r7
	movge	lr, #0
	cmp	lr, #0
	bne	.L2499
	mov	r6, r1
.L2498:
	cmp	r9, r6
	add	r8, r8, #1
	bhi	.L2500
	ldr	r5, [fp, #-48]
.L2492:
	cmp	r10, #4
	ble	.L2497
	mov	r3, r10, asr #2
	ldr	r1, [fp, #-60]
	str	r3, [fp, #-64]
	mov	r2, r3
	add	r3, r1, r3
	mul	r2, r2, r2
	ldrsb	r3, [r3, #8]
	add	r3, r3, #1
	cmp	r2, #0
	str	r2, [fp, #-68]
	beq	.L2497
.L2496:
	ldr	r2, .L2538+4
	rsb	r4, r10, #1
	add	r3, r2, r3, lsl #16
	sub	r3, r3, #4
	str	r3, [fp, #-56]
	ldr	r3, [fp, #-72]
	str	r3, [fp, #-52]
	mov	r3, #0
	str	r3, [fp, #-48]
.L2512:
	ldr	r3, [fp, #-56]
	cmp	r10, #32
	ldr	r8, [fp, #-64]
	ldr	r6, [r3, #4]!
	mov	r1, r8
	str	r3, [fp, #-56]
	ldreq	r3, [fp, #-52]
	ldreq	r6, [r3]
	mov	r0, r6
	bl	__aeabi_uidiv
	ldr	ip, [fp, #-48]
	mov	r3, #0
	mov	r7, r3
	mov	r2, r3
	mov	r9, ip, asl #4
	mov	lr, r3
	mla	r1, r10, r0, r6
	mls	r1, r8, r0, r1
	mov	r8, r1, asl #2
.L2506:
	cmp	lr, #3
	mvn	r1, r2
	mov	r1, r1, lsr #31
	movgt	r1, #0
	cmp	r1, #0
	beq	.L2507
	mla	r1, r10, r2, lr
	add	r0, r3, r9
	rsb	lr, r3, lr
	add	r0, r5, r0, lsl #2
	add	r1, r1, r8
.L2508:
	add	r3, r3, #1
	sub	r2, r2, #1
	add	r6, lr, r3
	str	r1, [r0], #4
	cmp	r6, #3
	mvn	ip, r2
	mov	ip, ip, lsr #31
	add	r1, r1, r4
	movgt	ip, #0
	cmp	ip, #0
	bne	.L2508
.L2507:
	cmp	r3, #15
	add	r7, r7, #1
	bhi	.L2509
	cmp	r7, #3
	movle	r2, r7
	movle	lr, #0
	subgt	lr, r7, #3
	movgt	r2, #3
	b	.L2506
.L2509:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r2, r2, #4
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L2512
.L2497:
	ldr	r3, .L2538+8
	add	r5, r5, #65536
	mov	r10, r10, asl #1
	cmp	r5, r3
	bne	.L2503
	ldr	r4, [fp, #-60]
	mov	r2, #1
	add	r3, r4, #69632
	mov	r0, r4
	str	r2, [r3, #2836]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #244]
	beq	.L2537
	ldr	r4, [fp, #-60]
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	bl	HEVC_InitDecPara
	ldr	r3, [fp, #-76]
	mov	r0, #0
	movw	r2, #9999
	str	r0, [r3, #2200]
	ldr	r3, [r4, #156]
	str	r2, [r4, #252]
	str	r3, [r4, #272]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2515:
	mov	r2, r8
	mov	r4, #0
	b	.L2501
.L2536:
	cmp	r9, #0
	ldr	r3, [fp, #-72]
	bne	.L2494
	ldr	r3, [fp, #-60]
	mov	r2, #2
	str	r2, [fp, #-64]
	mov	r2, #4
	str	r2, [fp, #-68]
	ldrsb	r3, [r3, #10]
	add	r3, r3, #1
	b	.L2496
.L2534:
	ldr	r3, [r4, #748]
	ldr	r1, [fp, #-60]
	str	r3, [r1, #148]
	ldr	r3, [r4, #752]
	str	r3, [r1, #152]
	ldr	r3, [r4, #756]
	str	r3, [r1, #156]
	ldr	r3, [r4, #744]
	add	r2, r3, #5
	str	r2, [r1, #160]
	str	r3, [r1, #144]
	ldr	r0, [r4, #668]
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	bne	.L2489
.L2535:
	ldr	r3, .L2538
	ldr	r2, .L2538+12
	ldr	r1, .L2538+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #19
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2533:
	ldr	ip, .L2538
	movw	r3, #11178
	ldr	r2, .L2538+12
	mov	r0, #1
	ldr	r1, .L2538+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2537:
	ldr	r3, .L2538
	mov	r0, #0
	ldr	r2, .L2538+12
	ldr	r1, .L2538+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #19
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2539:
	.align	2
.L2538:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR4-3912
	.word	.LANCHOR4+454840
	.word	.LANCHOR0+1212
	.word	.LC225
	.word	.LC35
	.word	.LC226
	UNWIND(.fnend)
	.size	HEVCDEC_Init, .-HEVCDEC_Init
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
	subs	r5, r0, #0
	beq	.L2547
	add	r4, r5, #40960
	bl	HEVC_ClearAllSlice
	ldr	r3, [r4, #2068]
	cmp	r3, #0
	beq	.L2543
	ldr	r1, [r3, #32]
	mov	r2, #1
	ldr	r0, [r5, #244]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #2068]
	mov	r3, #0
	str	r3, [r2, #4]
	str	r3, [r4, #2068]
.L2543:
	mov	r0, #0
	strb	r0, [r4, #2017]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2547:
	ldr	ip, .L2548
	movw	r3, #11406
	ldr	r2, .L2548+4
	mov	r0, #1
	ldr	r1, .L2548+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2549:
	.align	2
.L2548:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1228
	.word	.LC35
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
	subs	r4, r0, #0
	mov	r5, r1
	beq	.L2555
	bl	HEVC_ClearCurrPic
	mov	r1, #0
	mov	r0, r4
	bl	HEVC_InitDPB
	cmp	r5, #0
	bne	.L2556
	add	r0, r4, #50944
	add	r0, r0, #56
	bl	ResetVoQueue
	ldr	r0, [r4, #244]
	bl	FSP_EmptyInstance
.L2554:
	mov	r0, r4
	bl	HEVC_InitDecPara
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2556:
	add	r1, r4, #50944
	ldr	r0, [r4, #244]
	add	r1, r1, #56
	bl	FSP_ClearNotInVoQueue
	b	.L2554
.L2555:
	ldr	ip, .L2557
	movw	r3, #11151
	ldr	r2, .L2557+4
	mov	r0, #1
	ldr	r1, .L2557+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2558:
	.align	2
.L2557:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1248
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_ClearAll, .-HEVC_ClearAll
	.align	2
	.global	HEVC_InitPic
	.type	HEVC_InitPic, %function
HEVC_InitPic:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	subs	r5, r0, #0
	beq	.L2626
	add	r6, r5, #24576
	add	r4, r5, #40960
	ldr	r1, [r6, #2584]
	ldr	r3, [r6, #2604]
	ldr	r2, [r4, #2652]
	str	r1, [fp, #-60]
	ldr	r1, [r6, #2588]
	cmp	r2, #0
	str	r1, [fp, #-52]
	ldr	r1, [r3, #100]
	str	r1, [fp, #-68]
	ldr	r1, [r3, #108]
	str	r1, [fp, #-72]
	ldr	r1, [r6, #2592]
	str	r1, [fp, #-56]
	ldr	r1, [r6, #2596]
	str	r1, [fp, #-76]
	blt	.L2595
	ldr	r1, [r5, #156]
	cmp	r2, r1
	bge	.L2595
	ldr	ip, [r5, #2304]
	movw	lr, #2024
	movw	r0, #15788
	ldr	r10, [r5, #2300]
	ldr	r7, [r5, #2296]
	movw	r1, #12820
	mla	r2, lr, r2, ip
	mov	ip, r2
	str	r2, [fp, #-48]
	ldr	r9, [ip, #32]
	ldr	r2, [r6, #2600]
	mul	r9, r0, r9
	ldr	r2, [r2, #8]
	add	r8, r10, r9
	ldr	r0, [r8, #52]
	mla	r1, r1, r0, r7
	ldr	r0, [r1, #8]
	cmp	r2, r0
	bne	.L2562
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2627
.L2562:
	mov	r3, #0
	strb	r3, [r1, #2]
	ldr	r0, [r5, #148]
	movw	r7, #12820
	ldr	r3, .L2635
	mov	r2, r7
	ldr	ip, [r5, #2296]
	mul	r0, r7, r0
	ldr	r3, [r3, #52]
	sub	r0, r0, #12800
	sub	r0, r0, #20
	add	r0, ip, r0
	blx	r3
	ldr	r1, [r5, #148]
	ldr	r3, [r6, #2604]
	ldr	r2, [r5, #2296]
	mul	r7, r7, r1
	sub	r7, r7, #12800
	sub	r7, r7, #20
	add	r7, r2, r7
	str	r7, [r6, #2600]
.L2563:
	ldr	r1, [r3, #60]
	ldr	r2, [r8, #60]
	cmp	r1, r2
	bne	.L2564
	ldrb	r2, [r10, r9]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2628
.L2564:
	mov	r3, #0
	strb	r3, [r10, r9]
	ldr	r0, [r5, #152]
	movw	r7, #15788
	ldr	r3, .L2635
	mov	r2, r7
	ldr	ip, [r5, #2300]
	mov	r1, r8
	mul	r0, r7, r0
	ldr	r3, [r3, #52]
	sub	r0, r0, #15744
	sub	r0, r0, #44
	add	r0, ip, r0
	blx	r3
	ldr	r2, [r5, #152]
	ldr	r3, [r5, #2300]
	mul	r7, r7, r2
	sub	r7, r7, #15744
	sub	r7, r7, #44
	add	r3, r3, r7
	str	r3, [r6, #2604]
	ldr	r2, [r3, #60]
	str	r2, [r6, #2584]
	ldr	r2, [r3, #72]
	str	r2, [r6, #2588]
	ldr	r2, [r3, #76]
	str	r2, [r6, #2592]
	ldr	r2, [r3, #148]
	str	r2, [r6, #2596]
	ldr	r1, [r8, #236]
	ldr	r2, [r3, #236]
	subs	r2, r1, r2
	movne	r2, #1
	str	r2, [fp, #-64]
.L2565:
	ldr	r2, [r3, #108]
	ldr	r3, [r3, #100]
	ldr	r1, [r5, #2308]
	cmp	r2, r3
	movcc	r2, r3
	ldr	r3, [fp, #-48]
	str	r2, [r1, #912]
	ldr	r2, [r6, #2608]
	ldr	r3, [r3, #28]
	ldr	r2, [r2, #28]
	cmp	r2, r3
	beq	.L2629
.L2566:
	ldr	r2, [fp, #-48]
	mov	r7, #0
	ldrb	r3, [r2, #13]	@ zero_extendqisi2
	strb	r7, [r2, #1]
	cmp	r3, r7
	beq	.L2568
	ldrb	r3, [r2, #15]	@ zero_extendqisi2
	cmp	r3, r7
	beq	.L2569
	ldr	r10, [r2, #68]
	cmp	r10, r7
	ble	.L2574
	ldr	r3, [fp, #-48]
	str	r4, [fp, #-80]
	add	r2, r3, #174
	str	r5, [fp, #-76]
	mov	r4, r2
.L2573:
	ldr	r5, [r8, #240]
	add	r7, r7, #1
	mov	r1, r10
	mul	r0, r5, r7
	bl	__aeabi_uidiv
	mov	r1, r10
	mov	r9, r0
	sub	r0, r7, #1
	mul	r0, r0, r5
	bl	__aeabi_uidiv
	cmp	r7, r10
	rsb	r0, r0, r9
	strh	r0, [r4, #2]!	@ movhi
	bne	.L2573
	ldr	r5, [fp, #-76]
	ldr	r4, [fp, #-80]
.L2574:
	ldr	r3, [fp, #-48]
	ldr	r10, [r3, #72]
	cmp	r10, #0
	ble	.L2575
	ldr	r3, [fp, #-48]
	mov	r7, #0
	str	r4, [fp, #-80]
	add	r2, r3, #214
	str	r5, [fp, #-76]
	mov	r4, r2
.L2576:
	ldr	r5, [r8, #244]
	add	r7, r7, #1
	mov	r1, r10
	mul	r0, r5, r7
	bl	__aeabi_uidiv
	mov	r1, r10
	mov	r9, r0
	sub	r0, r7, #1
	mul	r0, r5, r0
	bl	__aeabi_uidiv
	cmp	r7, r10
	rsb	r0, r0, r9
	strh	r0, [r4, #2]!	@ movhi
	bne	.L2576
	ldr	r5, [fp, #-76]
	ldr	r4, [fp, #-80]
	b	.L2575
.L2595:
	mov	r0, #0
.L2619:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2568:
	ldr	r3, [r8, #240]
	ldr	r2, [fp, #-48]
	strh	r3, [r2, #176]	@ movhi
	ldr	r3, [r8, #244]
	strh	r3, [r2, #216]	@ movhi
.L2575:
	ldr	r0, [r5, #156]
	movw	r7, #2024
	ldr	r3, .L2635
	mov	r2, r7
	ldr	ip, [r5, #2304]
	mul	r0, r7, r0
	ldr	r3, [r3, #52]
	ldr	r1, [fp, #-48]
	sub	r0, r0, #2016
	sub	r0, r0, #8
	add	r0, ip, r0
	blx	r3
	ldr	r2, [r5, #156]
	ldr	r3, [r5, #2304]
	mul	r7, r7, r2
	sub	r7, r7, #2016
	sub	r7, r7, #8
	add	r7, r3, r7
	str	r7, [r6, #2608]
.L2567:
	ldr	r3, [r8, #60]
	ldr	r2, [fp, #-64]
	ldr	r1, [fp, #-60]
	cmp	r1, r3
	orrne	r2, r2, #1
	cmp	r2, #0
	bne	.L2625
	ldr	r3, [r5, #168]
	cmp	r3, #0
	bne	.L2630
.L2625:
	ldr	r2, [r5, #2308]
.L2582:
	ldr	r0, [r5, #2304]
	movw	ip, #2024
	ldr	r3, [r4, #2652]
	movw	r1, #15788
	ldr	lr, [r5, #2300]
	mla	r3, ip, r3, r0
	ldr	ip, [fp, #-52]
	ldr	r3, [r3, #32]
	mla	r1, r1, r3, lr
	ldr	r3, [r1, #72]
	ldr	r0, [r1, #76]
	ldr	r1, [fp, #-56]
	cmp	ip, r3
	cmpeq	r1, r0
	ldr	r1, [fp, #-64]
	movne	r3, #1
	moveq	r3, #0
	orrs	r3, r1, r3
	beq	.L2584
	ldr	r3, [r2, #916]
.L2585:
	cmp	r3, #1
	beq	.L2631
.L2588:
	add	r3, r5, #69632
	ldr	r3, [r3, #2836]
	cmp	r3, #1
	beq	.L2632
.L2589:
	mov	r1, #1
	mov	r0, r5
	bl	HEVC_InitDPB
	cmn	r0, #2
	beq	.L2619
	cmp	r0, #0
	ldreq	r2, [r5, #2308]
	bne	.L2633
.L2593:
	mov	r3, #0
	str	r3, [r2, #916]
.L2583:
	mov	r0, r5
	bl	HEVC_AllocFrameStore
	subs	r7, r0, #0
	bne	.L2634
	ldr	ip, [r4, #2648]
	mov	r0, #1
	ldr	r3, [r4, #2624]
	mvn	r2, #0
	ldr	r1, [r4, #2068]
	movw	r10, #43040
	str	ip, [r4, #2020]
	add	ip, r5, #43008
	strb	r0, [r4, #2017]
	movw	lr, #43056
	str	r3, [r4, #2024]
	add	r0, ip, #24
	str	r3, [r1, #12]
	str	r2, [r4, #2048]
	ldr	r3, [r6, #2604]
	ldr	r2, [r3, #72]
	str	r2, [r4, #2032]
	ldr	r2, [r3, #76]
	str	r2, [r4, #2036]
	mvn	r2, #0
	ldr	r1, [r3, #240]
	ldr	r3, [r3, #244]
	str	r7, [r4, #2044]
	mul	r1, r3, r1
	mvn	r3, #0
	str	r1, [r4, #2040]
	ldr	r1, [r5, #2308]
	ldrd	r8, [r1, #48]
	strd	r8, [r5, r10]
	ldrd	r8, [r1, #64]
	strd	r8, [ip, #40]
	ldrd	r8, [r1, #80]
	strd	r8, [r5, lr]
	ldr	ip, [r1, #96]
	str	ip, [r4, #2140]
	ldr	ip, [r1, #100]
	str	ip, [r4, #2144]
	ldr	ip, [r1, #104]
	str	ip, [r4, #2148]
	ldr	ip, [r1, #120]
	str	ip, [r4, #2152]
	strd	r2, [r1, #48]
	ldr	r2, [r6, #2604]
	ldr	r3, [r2, #72]
	str	r3, [r4, #2236]
	ldr	r3, [r2, #76]
	str	r3, [r4, #2240]
	ldr	r3, [r2, #2660]
	ldr	r1, [r2, #64]
	mov	r3, r3, asl #5
	subs	r1, r1, #1
	uxtb	r3, r3
	movne	r1, #1
	orr	r3, r3, r1, asl #2
	str	r3, [r4, #2232]
	ldr	r1, [r2, #2644]
	and	r1, r1, #7
	bl	SetAspectRatio
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2232]
	str	r7, [r4, #2220]
	str	r2, [r3, #232]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2220]
	str	r2, [r3, #220]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2136]
	str	r2, [r3, #136]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2132]
	str	r2, [r3, #132]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2236]
	str	r2, [r3, #236]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2240]
	str	r2, [r3, #240]
	ldr	r3, [r4, #2068]
	ldr	r0, [r5, #244]
	ldr	r1, [r3, #32]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L2592
	ldr	r3, [r4, #2220]
	mov	r1, r7
	ldr	r2, [r0, #4]
	adds	r3, r3, #0
	ldr	r0, [r5, #244]
	movne	r3, #1
	bl	FSP_SetStoreType
.L2592:
	ldr	ip, [r6, #2604]
	mov	r5, #0
	ldr	lr, [r4, #2068]
	mov	r0, r5
	ldr	r3, [ip, #84]
	str	r3, [r4, #2412]
	ldr	r7, [ip, #88]
	str	r7, [r4, #2416]
	ldr	r2, [ip, #92]
	str	r2, [r4, #2420]
	ldr	r6, [ip, #96]
	str	r6, [r4, #2424]
	ldr	r1, [ip, #72]
	rsb	r3, r3, r1
	rsb	r3, r7, r3
	str	r3, [r4, #2244]
	ldr	r1, [ip, #76]
	rsb	r2, r2, r1
	rsb	r2, r6, r2
	str	r2, [r4, #2248]
	ldr	r2, [ip, #64]
	str	r2, [r4, #2300]
	ldr	r2, [ip, #100]
	str	r2, [r4, #2304]
	ldr	r2, [ip, #108]
	str	r2, [r4, #2308]
	ldr	r2, [lr, #252]
	str	r2, [r4, #2252]
	ldr	r2, [lr, #256]
	str	r2, [r4, #2256]
	str	r3, [lr, #244]
	ldr	r2, [r4, #2248]
	ldr	r3, [r4, #2068]
	str	r2, [r3, #248]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2252]
	str	r2, [r3, #252]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2256]
	str	r2, [r3, #256]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2304]
	str	r2, [r3, #304]
	ldr	r3, [r4, #2068]
	ldr	r2, [r4, #2308]
	str	r2, [r3, #308]
	str	r5, [r4, #2028]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2569:
	ldr	r2, [fp, #-48]
	ldr	r3, [r8, #240]
	ldr	lr, [r2, #68]
	cmp	lr, #1
	add	r0, r2, lr, lsl #1
	strh	r3, [r0, #174]	@ movhi
	ble	.L2580
	ldr	r3, [fp, #-48]
	add	lr, lr, #44
	add	r1, r3, #90
	add	ip, r3, #174
	add	lr, r3, lr, lsl #1
.L2579:
	ldrh	r2, [r1, #2]!
	cmp	r1, lr
	strh	r2, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #174]
	rsb	r3, r2, r3
	strh	r3, [r0, #174]	@ movhi
	bne	.L2579
.L2580:
	ldr	r2, [fp, #-48]
	ldr	r3, [r8, #244]
	ldr	lr, [r2, #72]
	cmp	lr, #1
	add	r0, r2, lr, lsl #1
	strh	r3, [r0, #214]	@ movhi
	ble	.L2575
	ldr	r3, [fp, #-48]
	add	lr, lr, #64
	add	r1, r3, #130
	add	ip, r3, #214
	add	lr, r3, lr, lsl #1
.L2581:
	ldrh	r2, [r1, #2]!
	cmp	r1, lr
	strh	r2, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #214]
	rsb	r3, r2, r3
	strh	r3, [r0, #214]	@ movhi
	bne	.L2581
	b	.L2575
.L2628:
	ldr	r1, [r5, #168]
	cmp	r1, #0
	beq	.L2564
	ldr	r1, [r8, #72]
	ldr	r0, [fp, #-52]
	cmp	r0, r1
	bne	.L2564
	ldr	r1, [r8, #76]
	ldr	r0, [fp, #-56]
	cmp	r0, r1
	bne	.L2564
	ldr	r1, [r8, #148]
	ldr	r0, [fp, #-76]
	cmp	r0, r1
	streq	r2, [fp, #-64]
	bne	.L2564
	b	.L2565
.L2627:
	ldr	r2, [r5, #168]
	cmp	r2, #0
	bne	.L2563
	b	.L2562
.L2634:
	ldr	r3, .L2635
	mov	r0, #1
	ldr	r1, .L2635+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2629:
	ldr	r3, [fp, #-48]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2566
	ldr	r3, [r5, #168]
	cmp	r3, #0
	beq	.L2566
	ldr	r3, [r8, #72]
	ldr	r2, [fp, #-52]
	cmp	r2, r3
	bne	.L2566
	ldr	r3, [r8, #76]
	ldr	r2, [fp, #-56]
	cmp	r2, r3
	bne	.L2566
	ldr	r3, [r8, #148]
	ldr	r2, [fp, #-76]
	cmp	r2, r3
	bne	.L2566
	b	.L2567
.L2584:
	ldr	r3, [r5, #168]
	cmp	r3, #0
	ldr	r3, [r2, #916]
	beq	.L2585
	cmp	r3, #0
	bne	.L2585
	ldr	r3, [r2, #908]
	cmp	r3, #1
	bne	.L2593
	b	.L2588
.L2630:
	ldr	r3, [r8, #72]
	ldr	r2, [fp, #-52]
	cmp	r2, r3
	bne	.L2625
	ldr	r2, [fp, #-56]
	ldr	r3, [r8, #76]
	cmp	r2, r3
	ldr	r2, [r5, #2308]
	bne	.L2582
	ldr	r3, [r2, #908]
	cmp	r3, #1
	bne	.L2583
	b	.L2582
.L2632:
	mov	r0, r5
	bl	HEVC_GetBackPicFromVOQueue
	b	.L2589
.L2631:
	ldr	ip, [r8, #108]
	mov	r0, #31
	ldr	r1, .L2635
	ldr	lr, [fp, #-72]
	ldr	r3, [r8, #100]
	ldr	r2, [fp, #-68]
	str	lr, [sp]
	str	ip, [sp, #4]
	ldr	r7, [r1, #68]
	ldr	r1, .L2635+8
	blx	r7
	b	.L2588
.L2633:
	ldr	r3, .L2635
	mov	r2, r0
	ldr	r1, .L2635+12
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	mov	r1, #0
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L2619
.L2626:
	ldr	ip, .L2635
	movw	r3, #7006
	ldr	r2, .L2635+16
	mov	r0, #1
	ldr	r1, .L2635+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2619
.L2636:
	.align	2
.L2635:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC229
	.word	.LC227
	.word	.LC228
	.word	.LANCHOR0+1264
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_InitPic, .-HEVC_InitPic
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r6, r1
	moveq	r5, #1
	movne	r5, #0
	beq	.L2646
	bl	HEVC_GetImagePara
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r7, r0, #0
	beq	.L2647
	cmn	r7, #3
	moveq	r0, r5
	bne	.L2648
.L2639:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2647:
	mov	r2, #1
	ldr	r1, [r6, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	ldr	r1, [r6, #32]
	ldr	r0, [r4, #244]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L2649
	add	r3, r4, #50944
	ldr	r0, [r4, #244]
	add	r3, r3, #56
	str	r5, [sp]
	mov	r2, r4
	mov	r1, #17
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L2650
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	strcc	r7, [r5, #84]
	bcs	.L2651
.L2644:
	ldr	r2, [r4, #268]
	mov	r0, #0
	ldr	r3, [r4, #260]
	add	r2, r2, #1
	str	r2, [r4, #268]
	add	r3, r3, #1
	str	r3, [r4, #260]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2651:
	add	r1, r5, #84
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.isra.11.part.12
	b	.L2644
.L2646:
	ldr	ip, .L2652
	movw	r3, #9118
	ldr	r2, .L2652+4
	mov	r0, #1
	ldr	r1, .L2652+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2639
.L2648:
	ldr	ip, .L2652
	mov	r3, r7
	movw	r2, #9159
	ldr	r1, .L2652+12
	mov	r0, #1
	ldr	r5, [ip, #68]
	blx	r5
	ldr	r1, [r6, #268]
	mov	r0, r4
	bl	HEVC_DECRecycleImage
	mvn	r0, #0
	b	.L2639
.L2650:
	ldr	r3, .L2652
	mov	r2, r0
	ldr	r1, .L2652+16
	mov	r0, r7
	ldr	r3, [r3, #68]
	blx	r3
	mov	r2, r7
	ldr	r1, [r6, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L2639
.L2649:
	ldr	r3, .L2652
	ldr	r2, .L2652+4
	ldr	r1, .L2652+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2639
.L2653:
	.align	2
.L2652:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1280
	.word	.LC35
	.word	.LC232
	.word	.LC231
	.word	.LC230
	UNWIND(.fnend)
	.size	HEVC_OutputFrmToVO, .-HEVC_OutputFrmToVO
	.align	2
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
	ldr	r3, [r4, #2512]
	strb	r2, [r3, #2]
	ldr	r1, [r4, #2512]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r4, #2512]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r7, r0
	bne	.L2655
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
.L2655:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_OutputOneFrmFromDPB, .-HEVC_OutputOneFrmFromDPB
	.align	2
	.global	HEVC_OutputFrmFromDPB
	.type	HEVC_OutputFrmFromDPB, %function
HEVC_OutputFrmFromDPB:
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
	subs	r6, r0, #0
	beq	.L2657
	ldr	r0, [r6, #2492]
	cmp	r0, #0
	moveq	r8, r0
	beq	.L2659
	add	r5, r6, #2496
	ldr	r2, [r6, #212]
	add	r5, r5, #12
	mov	r7, #0
	mov	r3, r7
	mov	ip, r5
.L2662:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldrb	lr, [r1, #2]	@ zero_extendqisi2
	cmp	lr, #0
	bne	.L2661
	ldr	r1, [r1, #12]
	cmp	r1, r2
	addgt	r7, r7, #1
.L2661:
	cmp	r3, r0
	bne	.L2662
	ldr	r9, .L2676
	mov	r4, #0
	mov	r8, r4
.L2667:
	ldr	r3, [r5, #4]!
	ldrb	r1, [r3, #2]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2664
	ldr	r1, [r3, #12]
	cmp	r1, r2
	ble	.L2664
	add	lr, r6, #40960
	add	ip, r6, #24576
	ldr	r10, [lr, #2644]
	ldr	ip, [ip, #2604]
	add	ip, ip, r10, lsl #2
	ldr	ip, [ip, #412]
	cmp	ip, r7
	bcs	.L2664
	ldr	ip, [lr, #2624]
	cmp	r1, ip
	blt	.L2665
	ldrb	r1, [r6, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2665
.L2664:
	cmp	r2, #0
	bne	.L2666
	ldr	r1, [r3, #12]
	cmp	r1, #0
	blt	.L2674
.L2666:
	add	r4, r4, #1
	cmp	r0, r4
	bls	.L2659
.L2675:
	ldr	r2, [r6, #212]
	b	.L2667
.L2665:
	mov	r2, #1
	mov	r0, r6
	strb	r2, [r3, #2]
	add	r4, r4, #1
	ldr	r1, [r5]
	sub	r7, r7, #1
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r5]
	ldr	r3, [r3, #12]
	str	r3, [r6, #212]
	mov	r8, r0
	ldr	r0, [r6, #2492]
	cmp	r0, r4
	bhi	.L2675
.L2659:
	mov	r0, r8
.L2660:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2674:
	ldr	r1, [r3, #32]
	ldr	r0, [r6, #244]
	bl	FSP_SetDisplay
	ldr	r2, [r5]
	ldr	r3, [r6, #212]
	mov	r0, #31
	ldr	r10, [r9, #68]
	ldr	ip, [r2, #12]
	ldr	r1, .L2676+4
	ldr	r2, .L2676+8
	str	ip, [sp]
	blx	r10
	ldr	r0, [r6, #2492]
	b	.L2666
.L2657:
	ldr	ip, .L2676
	movw	r3, #8914
	ldr	r2, .L2676+8
	mov	r0, #1
	ldr	r1, .L2676+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2660
.L2677:
	.align	2
.L2676:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC233
	.word	.LANCHOR0+1300
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_OutputFrmFromDPB, .-HEVC_OutputFrmFromDPB
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
	beq	.L2687
	ldr	r3, [r4, #2492]
	cmp	r3, #0
	addne	r5, r4, #2496
	movne	r6, #0
	addne	r5, r5, #12
	movne	r8, #1
	bne	.L2685
	b	.L2686
.L2693:
	strb	r8, [r3, #2]
	ldr	r1, [r5]
	bl	HEVC_OutputFrmToVO
	cmn	r0, #1
	mov	r9, r0
	beq	.L2692
.L2683:
	ldr	r3, [r4, #2492]
	cmp	r3, r6
	bls	.L2686
.L2685:
	ldr	r3, [r5, #4]!
	mov	r2, #0
	ldr	r0, [r4, #244]
	add	r6, r6, #1
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldr	r3, [r5]
	mov	r0, r4
	ldrb	r7, [r3, #2]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L2693
	ldr	r1, [r3, #32]
	ldr	r0, [r4, #244]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L2683
	ldr	r3, [r5]
	ldr	r0, [r4, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #2492]
	cmp	r3, r6
	bhi	.L2685
.L2686:
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	mov	r9, #0
	bl	Hevc_InitDecBuffers
.L2679:
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2692:
	ldr	r3, .L2694
	mov	r0, r7
	ldr	r2, .L2694+4
	ldr	r1, .L2694+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2687:
	mvn	r9, #0
	b	.L2679
.L2695:
	.align	2
.L2694:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1324
	.word	.LC234
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r10, r1
	moveq	r2, #1
	movne	r2, #0
	beq	.L2739
	add	r6, r0, #69632
	str	r2, [r6, #2816]
	ldr	r5, [r0, #2316]
	cmp	r5, #0
	beq	.L2740
	ldrb	r2, [r1]	@ zero_extendqisi2
	str	r2, [r5, #40]
	ldr	r2, [r0, #2308]
	ldr	r1, [r2, #868]
	cmp	r1, #1
	beq	.L2741
.L2708:
	ldrb	r2, [r10]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L2709
	ldr	r2, [r4, #2316]
	ldr	r1, [r2, #8]
	cmp	r1, #1
	bls	.L2710
	ldr	r0, [r2, #40]
	cmp	r0, #1
	beq	.L2709
.L2710:
	ldr	r0, [r10, #12]
	cmp	r0, #0
	ble	.L2711
	ldr	r0, [r10, #4]
	cmp	r0, #0
	beq	.L2711
	ldr	ip, [r10, #8]
	cmp	ip, #0
	bne	.L2742
.L2711:
	mov	r1, #1
	str	r1, [r2, #40]
	ldr	r1, [r10, #16]
	ldr	r0, [r4, #244]
	bl	SM_ReleaseStreamSeg
.L2738:
	ldr	r0, [r4, #2316]
.L2707:
	ldr	r0, [r0, #40]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
.L2737:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2741:
	ldr	r2, [r2, #908]
	cmp	r2, #0
	bne	.L2738
	b	.L2708
.L2742:
	mov	ip, r1, asl #5
	mov	r5, #0
	sub	r1, ip, r1, asl #2
	add	r2, r2, r1
	str	r0, [r2, #44]
	ldr	r2, [r4, #2316]
	ldr	ip, [r10, #12]
	ldr	r0, [r2, #8]
	mov	r1, r0, asl #5
	sub	r1, r1, r0, asl #2
	add	r2, r2, r1
	str	ip, [r2, #48]
	ldr	r2, [r4, #2316]
	ldr	ip, [r10, #8]
	ldr	r0, [r2, #8]
	mov	r1, r0, asl #5
	sub	r1, r1, r0, asl #2
	add	r2, r2, r1
	str	ip, [r2, #52]
	ldr	r2, [r4, #2316]
	ldr	r0, [r10, #16]
	ldr	r1, [r2, #8]
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r2, r2, r3
	str	r0, [r2, #68]
	ldr	r3, [r4, #2316]
	ldr	r1, [r3, #8]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	r5, [r3, #60]
	ldr	r2, [r4, #2316]
	ldr	r3, [r2, #8]
	add	r3, r3, #1
	str	r3, [r2, #8]
	ldr	r0, [r4, #2316]
	cmp	r0, r5
	beq	.L2743
	ldr	r3, [r0, #48]
	cmp	r3, #4096
	bcs	.L2713
	ldr	r7, .L2744
	mov	r0, #7
	ldr	r1, .L2744+4
	ldr	r3, [r7, #68]
	blx	r3
	ldr	r3, [r4, #2316]
	ldr	r7, [r7, #52]
	ldr	r2, [r3, #48]
	ldr	r0, [r3, #72]
	ldr	r1, [r3, #44]
	rsb	r0, r2, r0
	blx	r7
	ldr	r3, [r4, #2316]
	mov	r0, #1
	ldr	r2, [r3, #96]
	ldr	r1, [r3, #68]
	str	r2, [r3, #68]
	ldr	r3, [r4, #2316]
	str	r5, [r3, #60]
	ldr	r3, [r4, #2316]
	ldr	ip, [r3, #48]
	ldr	r2, [r3, #72]
	rsb	r2, ip, r2
	str	r2, [r3, #44]
	ldr	r3, [r4, #2316]
	ldr	ip, [r3, #48]
	ldr	r2, [r3, #80]
	rsb	r2, ip, r2
	str	r2, [r3, #52]
	ldr	r3, [r4, #2316]
	ldr	r2, [r3, #48]
	ldr	ip, [r3, #76]
	add	r2, r2, ip
	str	r2, [r3, #48]
	ldr	r3, [r4, #2316]
	str	r0, [r3, #8]
	ldr	r0, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #2316]
	str	r5, [r3, #72]
	ldr	r3, [r4, #2316]
	str	r5, [r3, #88]
	ldr	r3, [r4, #2316]
	str	r5, [r3, #76]
	ldr	r0, [r4, #2316]
.L2713:
	mov	r3, #1
	str	r3, [r6, #2816]
	b	.L2707
.L2740:
	ldr	r2, [r1, #12]
	cmp	r2, #0
	ble	.L2700
	ldr	r2, [r1, #4]
	cmp	r2, #0
	beq	.L2700
	ldr	r2, [r1, #8]
	cmp	r2, #0
	beq	.L2700
	ldr	r8, [r0, #160]
	ldr	r2, [r0, #140]
	cmp	r8, #0
	blt	.L2701
	add	r9, r8, #1
	add	r3, r0, #53248
	mov	r0, r2
	str	r3, [fp, #-48]
	mov	r1, r9
	mov	r6, r3
	bl	__aeabi_uidivmod
	ldr	r6, [r6, #3252]
	mov	r7, #100
	mov	r2, r1
	mla	r1, r7, r1, r6
	ldr	r1, [r1, #36]
	cmp	r1, #0
	bne	.L2704
	b	.L2702
.L2705:
	bl	__aeabi_uidivmod
	mov	r2, r1
	mla	r1, r7, r1, r6
	ldr	r1, [r1, #36]
	cmp	r1, #0
	beq	.L2702
.L2704:
	add	r5, r5, #1
	mov	r1, r9
	cmp	r5, r8
	add	r0, r2, r5
	ble	.L2705
.L2701:
	str	r2, [r4, #140]
.L2714:
	ldr	r3, .L2744
	mov	r0, #0
	ldr	r1, .L2744+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L2737
.L2702:
	cmp	r9, r2
	str	r2, [r4, #140]
	bls	.L2714
	mov	r1, #100
	cmn	r2, #1
	mul	r2, r1, r2
	mov	ip, #1
	add	r6, r6, r2
	str	ip, [r6, #36]
	beq	.L2714
	ldr	r3, [fp, #-48]
	mov	r0, #0
	ldr	r1, [r3, #3252]
	add	r2, r1, r2
	str	r2, [r4, #2316]
	ldr	r1, [r10, #4]
	str	r1, [r2, #44]
	ldr	r2, [r4, #2316]
	ldr	r1, [r10, #12]
	str	r1, [r2, #48]
	ldr	r2, [r4, #2316]
	ldr	r1, [r10, #16]
	str	r1, [r2, #68]
	ldr	r2, [r4, #2316]
	ldr	r1, [r10, #8]
	str	r1, [r2, #52]
	ldr	r2, [r4, #2316]
	str	r0, [r2, #60]
	ldr	r2, [r4, #2316]
	str	ip, [r2, #8]
	ldr	r2, [r4, #2316]
	strb	r0, [r2, #1]
	ldrb	r2, [r10]	@ zero_extendqisi2
	ldr	r3, [r4, #2316]
	str	r2, [r3, #40]
	ldr	r0, [r4, #2316]
	b	.L2707
.L2709:
	ldr	r3, .L2744
	mov	r0, #1
	ldr	r1, .L2744+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2737
.L2739:
	ldr	ip, .L2744
	movw	r3, #10931
	ldr	r2, .L2744+16
	mov	r0, #1
	ldr	r1, .L2744+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2737
.L2700:
	ldr	r3, .L2744
	mov	r0, #1
	ldr	r1, .L2744+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2737
.L2743:
	ldr	r3, .L2744
	ldr	r1, .L2744+28
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r0, [r4, #2316]
	b	.L2713
.L2745:
	.align	2
.L2744:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC239
	.word	.LC235
	.word	.LC237
	.word	.LANCHOR0+1352
	.word	.LC35
	.word	.LC236
	.word	.LC238
	UNWIND(.fnend)
	.size	HEVC_ReceivePacket, .-HEVC_ReceivePacket
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
	cmp	r1, #0
	cmpne	r0, #0
	moveq	r2, #1
	movne	r2, #0
	beq	.L2748
	strb	r2, [r1, #1]
	ldr	r1, [r1, #32]
	ldr	r0, [r0, #244]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetRef
.L2748:
	ldr	ip, .L2749
	movw	r3, #11469
	ldr	r2, .L2749+4
	mov	r0, #1
	ldr	r1, .L2749+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L2750:
	.align	2
.L2749:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1372
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_UnMarkFrameStoreRef, .-HEVC_UnMarkFrameStoreRef
	.align	2
	.global	HEVC_FlushDPB
	.type	HEVC_FlushDPB, %function
HEVC_FlushDPB:
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
	subs	r4, r0, #0
	beq	.L2752
	ldr	r2, [r4, #2492]
	cmp	r2, #0
	addne	r6, r4, #2496
	movne	r5, #0
	addne	r6, r6, #12
	bne	.L2757
	b	.L2754
.L2756:
	cmp	r2, r5
	bls	.L2754
.L2757:
	ldr	r1, [r6, #4]!
	add	r5, r5, #1
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2756
	mov	r0, r4
	bl	HEVC_UnMarkFrameStoreRef
	ldr	r2, [r4, #2492]
	cmp	r2, r5
	bhi	.L2757
.L2754:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L2759
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L2754
	b	.L2759
.L2760:
	bl	HEVC_GetMinPOC
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	beq	.L2755
.L2759:
	ldr	r3, [r4, #2492]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	bne	.L2760
	mov	r0, r3
.L2755:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2752:
	ldr	ip, .L2768
	movw	r3, #11430
	ldr	r2, .L2768+4
	mov	r0, #1
	ldr	r1, .L2768+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2755
.L2769:
	.align	2
.L2768:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1400
	.word	.LC35
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
	subs	r4, r0, #0
	beq	.L2777
	bl	HEVC_FlushDPB
	subs	r3, r0, #0
	bne	.L2778
.L2773:
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2778:
	ldr	ip, .L2779
	mov	r0, #0
	ldr	r2, .L2779+4
	ldr	r1, .L2779+8
	ldr	r5, [ip, #68]
	blx	r5
	b	.L2773
.L2777:
	ldr	ip, .L2779
	movw	r3, #11334
	ldr	r2, .L2779+4
	mov	r0, #1
	ldr	r1, .L2779+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2780:
	.align	2
.L2779:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1416
	.word	.LC240
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_ClearDPB, .-HEVC_ClearDPB
	.align	2
	.global	HEVC_DecVDM
	.type	HEVC_DecVDM, %function
HEVC_DecVDM:
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
	cmp	r0, #0
	mov	r7, r0
	ldr	r3, [r0, #172]
	beq	.L2849
	cmp	r3, #2
	bls	.L2850
	ldr	r3, [r0, #264]
	add	r10, r0, #40960
	ldr	r2, [r0, #268]
	movw	r1, #2024
	add	r3, r3, #1
	ldr	lr, [r0, #2308]
	cmp	r3, r2
	add	ip, r7, #45056
	movw	r0, #15788
	str	ip, [fp, #-56]
	movlt	r3, r2
	str	r3, [r7, #264]
	str	r3, [lr, #600]
	mov	r4, ip
	ldr	r3, [r7, #268]
	mov	ip, #1
	ldr	r2, [r7, #264]
	rsb	r2, r3, r2
	str	r2, [lr, #604]
	ldr	r2, [r10, #2652]
	ldr	lr, [r7, #2304]
	ldr	r3, [r7, #2300]
	mla	r1, r1, r2, lr
	ldr	lr, [r4, #1768]
	ldr	r2, [r4, #1764]
	add	r2, lr, r2
	ldr	lr, [r4, #1772]
	ldr	r1, [r1, #32]
	cmp	r2, lr
	mla	r3, r0, r1, r3
	ldr	r9, [r3, #128]
	mov	r9, ip, asl r9
	bcs	.L2811
	add	r4, r2, #11712
	ldr	r3, [r10, #2024]
	add	r4, r4, #23
	str	r7, [fp, #-64]
	mov	r5, r2
	str	r2, [fp, #-60]
	add	r4, r7, r4, lsl #2
	mov	r8, lr
	mov	r7, r3
	str	r10, [fp, #-68]
	b	.L2788
.L2852:
	cmp	r5, r8
	bcs	.L2851
.L2788:
	ldr	r6, [r4, #4]!
	mov	r1, r9
	mov	r0, r7
	mov	r10, r7
	ldr	ip, [r4, #-1884]
	cmp	ip, #0
	bne	.L2787
	bl	__aeabi_idivmod
	mov	r0, r6
	mov	r10, r1
	mov	r1, r9
	bl	__aeabi_idivmod
	mov	r6, r1
.L2787:
	cmp	r10, r6
	add	r5, r5, #1
	bne	.L2852
	ldr	r2, [fp, #-60]
	mov	r3, #1
	ldr	r7, [fp, #-64]
	ldr	r10, [fp, #-68]
.L2786:
	cmp	r2, #0
	beq	.L2789
	ldr	r1, [fp, #-56]
	ldr	r4, [r10, #2624]
	ldr	lr, [r10, #2024]
	ldr	r1, [r1, #1820]
	add	r1, r4, r1
	cmp	lr, r1
	beq	.L2815
	add	ip, r7, #46848
	mov	r0, #0
	add	ip, ip, #28
	b	.L2790
.L2791:
	ldr	r1, [ip, #4]!
	add	r1, r4, r1
	cmp	r1, lr
	beq	.L2815
.L2790:
	add	r0, r0, #1
	cmp	r2, r0
	bne	.L2791
.L2789:
	strb	r3, [r10, #2016]
	ldr	r4, [r7, #232]
	ldr	r2, [r7, #248]
	ubfx	r4, r4, #16, #3
	cmp	r4, r2
	beq	.L2792
	sub	r1, r2, #2
	cmp	r1, #1
	movhi	r1, #0
	movls	r1, #1
	cmp	r4, #2
	moveq	r1, #0
	cmp	r1, #0
	beq	.L2792
	cmp	r4, #4
	cmpne	r4, #1
	bls	.L2853
.L2792:
	cmp	r4, #2
	str	r4, [r7, #248]
	beq	.L2794
	cmp	r4, #3
	beq	.L2795
	cmp	r4, #1
	beq	.L2854
	ldr	r2, [r7, #216]
	cmp	r2, #0
	beq	.L2846
	cmp	r4, #4
	beq	.L2855
.L2799:
	ldr	r2, [r10, #2028]
.L2800:
	cmp	r2, #2
	beq	.L2856
	cmp	r2, #1
	streqb	r2, [r7, #3]
.L2805:
	ldr	r5, .L2858
	mov	r0, #2
	ldr	r2, [r7, #220]
	ldr	r1, .L2858+4
	ldr	r3, [r5, #68]
	sub	r2, r2, #1
	blx	r3
	ldr	r4, [r7, #208]
	cmp	r4, #0
	beq	.L2857
	ldr	r1, [r10, #2044]
	add	r3, r7, #49152
	add	r0, r7, #53248
	clz	r2, r1
	mov	r2, r2, lsr #5
	str	r2, [r3, #3520]
	ldr	r2, [r10, #2048]
	str	r2, [r3, #3512]
	str	r4, [r0, #524]
	ldr	r3, [r7, #220]
	cmp	r3, #0
	beq	.L2845
	add	r3, r7, #51200
	add	r1, r1, #1
	add	r3, r3, #156
	str	r3, [r7, #2312]
	ldr	r3, [r10, #2060]
	str	r3, [r0, #3240]
	ldr	r3, [r10, #2064]
	str	r3, [r0, #3244]
	ldr	ip, [r10, #2028]
	str	r1, [r10, #2044]
	cmp	ip, #0
	bne	.L2845
	ldr	r1, [r0, #528]
	cmp	r1, #0
	beq	.L2816
.L2810:
	ldr	r3, [r1]
	ldr	r2, [r1, #4]
	ldr	r1, [r1, #1356]
	add	r3, r3, r2
	add	r3, r3, #7
	cmp	r1, #0
	add	ip, ip, r3, lsr #3
	bne	.L2810
.L2809:
	ldr	r3, .L2858+8
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2845
	sub	r2, fp, #44
	ldr	r0, [r7, #244]
	mov	r3, #4
	mov	r1, #20
	str	ip, [r2, #-4]!
	blx	r4
.L2845:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2850:
	bl	HEVC_ClearCurrPic
	ldr	r3, [r7, #224]
	mov	r0, #0
	cmp	r3, #524288
	ldr	r3, .L2858
	bls	.L2785
	ldr	r1, .L2858+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #7
.L2843:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2785:
	ldr	r1, .L2858+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2815:
	mov	r3, #1
	b	.L2789
.L2851:
	ldr	r2, [fp, #-60]
	mov	r3, #0
	ldr	r7, [fp, #-64]
	ldr	r10, [fp, #-68]
	b	.L2786
.L2854:
	ldr	r1, [r10, #2028]
	eor	r2, r3, #1
	cmp	r1, #2
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r2, #0
	bne	.L2846
.L2797:
	ldr	r2, [r7, #216]
	cmp	r2, #0
	bne	.L2799
	b	.L2846
.L2853:
	ldr	ip, .L2858
	mov	r3, r4
	ldr	r1, .L2858+20
	mov	r0, #1
	ldr	r5, [ip, #68]
	blx	r5
	str	r4, [r7, #248]
.L2795:
	mov	r0, r7
	bl	HEVC_ClearCurrPic
	mov	r0, r7
	bl	HEVC_ClearDPB
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2794:
	ldr	r2, [r10, #2028]
	cmp	r2, #0
	beq	.L2797
	b	.L2846
.L2856:
	ldrb	r2, [r7, #3]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L2805
	ldr	r2, [r7, #2308]
	ldr	r2, [r2, #12]
	cmp	r2, #0
	bne	.L2805
	ldr	r2, .L2858+24
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L2805
	ldr	ip, .L2858
	mov	r0, #1
	ldr	r2, [r10, #2024]
	ldr	r1, .L2858+28
	ldr	r4, [ip, #68]
	blx	r4
.L2846:
	mov	r0, r7
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L2843
.L2855:
	ldr	r2, [r10, #2028]
	cmp	r2, #0
	moveq	r3, #2
	streqb	r3, [r7, #3]
	beq	.L2805
	b	.L2800
.L2811:
	mov	r3, #0
	b	.L2786
.L2816:
	mov	ip, r1
	b	.L2809
.L2857:
	mov	r0, r7
	bl	HEVC_ClearCurrPic
	ldr	r3, [r5, #68]
	mov	r0, r4
	ldr	r2, .L2858+32
	ldr	r1, .L2858+36
	blx	r3
	mvn	r0, #0
	b	.L2843
.L2849:
	ldr	ip, .L2858
	movw	r3, #6791
	ldr	r2, .L2858+32
	mov	r0, #1
	ldr	r1, .L2858+40
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2843
.L2859:
	.align	2
.L2858:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC245
	.word	g_event_report
	.word	.LC241
	.word	.LC242
	.word	.LC243
	.word	g_allow_B_before_P
	.word	.LC244
	.word	.LANCHOR0+1432
	.word	.LC246
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_DecVDM, .-HEVC_DecVDM
	.align	2
	.global	HEVC_InsertFrmInDPB
	.type	HEVC_InsertFrmInDPB, %function
HEVC_InsertFrmInDPB:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	cmp	r2, #0
	cmpne	r0, #0
	mov	r8, r1
	mov	r5, r0
	moveq	r4, #1
	movne	r4, #0
	mov	r6, r2
	beq	.L2882
	cmp	r1, #16
	bhi	.L2883
	ldr	r3, [r2, #52]
	add	r7, r0, r1, lsl #2
	mov	r1, #1
	mov	r2, r1
	str	r3, [r7, #2512]
	str	r1, [r3, #4]
	ldr	r3, [r7, #2512]
	ldr	r0, [r0, #244]
	ldr	r1, [r3, #32]
	bl	FSP_SetRef
	ldrb	r3, [r6]	@ zero_extendqisi2
	ldr	r0, [r7, #2512]
	mov	r2, #504
	adds	r3, r3, #0
	add	r1, r6, #56
	movne	r3, #1
	strb	r3, [r0, #1]
	ldr	r3, [r7, #2512]
	ldr	r0, [r6, #36]
	str	r0, [r3, #24]
	ldr	r0, [r7, #2512]
	add	r0, r0, #72
	bl	memcpy
	ldr	r0, [r7, #2512]
	ldr	ip, [r6, #40]
	add	r1, r8, #1
	ldr	r3, .L2885
	mov	r2, #4
	str	ip, [r0, #40]
	str	ip, [r0, #20]
	add	r0, r5, #2512
	ldr	ip, [r7, #2512]
	ldr	lr, [r6, #52]
	str	lr, [ip, #68]
	ldr	ip, [r7, #2512]
	ldr	lr, [r6, #12]
	str	lr, [ip, #44]
	str	lr, [ip, #16]
	ldr	ip, [r7, #2512]
	ldr	lr, [r6, #8]
	str	lr, [ip, #12]
	ldr	ip, [r7, #2512]
	ldr	lr, [r6, #8]
	str	lr, [ip, #36]
	bl	qsort
	ldr	r3, [r5, #2492]
	add	r3, r3, #1
	str	r3, [r5, #2492]
	ldr	r7, [r6, #52]
	cmp	r7, #0
	beq	.L2864
	ldr	r1, [r5, #2784]
	cmp	r1, #0
	beq	.L2880
	ldr	r3, [r5, #2792]
	cmp	r3, #0
	addne	r3, r5, #2784
	addne	r3, r3, #8
	bne	.L2868
	b	.L2884
.L2871:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L2866
.L2868:
	add	r4, r4, #1
	cmp	r4, r1
	bne	.L2871
.L2880:
	ldr	r4, .L2885+4
.L2865:
	mvn	r3, #6
	ldr	r2, .L2885+8
	ldr	r1, .L2885+12
	mov	r0, #0
	ldr	r4, [r4, #68]
	blx	r4
	mov	r0, r5
	bl	HEVC_PrintDPBState
	mov	r0, r5
	bl	HEVC_ClearDPB
	mvn	r0, #6
.L2877:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2884:
	mov	r4, r3
.L2866:
	ldr	r1, [r7, #32]
	ldr	r0, [r5, #244]
	bl	FSP_GetLogicFs
	subs	r1, r0, #0
	beq	.L2869
	ldr	r3, [r1, #520]
	cmp	r3, #0
	beq	.L2869
	add	r2, r5, r4, lsl #2
	mov	r0, #1
	ldr	ip, .L2885+4
	mov	r3, r4
	str	r0, [r2, #2792]
	mov	r0, #13
	ldr	r1, [r1, #520]
	ldr	r8, [ip, #68]
	ldr	ip, [r1, #4]
	ldr	r1, .L2885+16
	str	ip, [r2, #2856]
	ldr	ip, [r7, #12]
	str	ip, [r2, #2920]
	ldr	r2, [r5, #2788]
	add	r2, r2, #1
	str	r2, [r5, #2788]
	ldr	r2, [r7, #268]
	blx	r8
	mov	r3, #0
	str	r4, [r7, #28]
	mov	r0, r3
	strb	r3, [r6, #1]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2883:
	ldr	ip, .L2885+4
	mov	r3, r1
	mov	r0, r4
	ldr	r2, .L2885+8
	ldr	r1, .L2885+20
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	bl	HEVC_ClearDPB
	mvn	r0, #0
	b	.L2877
.L2882:
	ldr	ip, .L2885+4
	movw	r3, #8852
	ldr	r2, .L2885+8
	mov	r0, #1
	ldr	r1, .L2885+24
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2877
.L2869:
	ldrb	ip, [r7, #1]	@ zero_extendqisi2
	mov	r0, #0
	ldr	r4, .L2885+4
	ldr	r2, [r7, #32]
	ldr	r3, [r7, #12]
	ldr	r6, [r4, #68]
	str	r1, [sp, #4]
	str	ip, [sp]
	str	r0, [sp, #8]
	ldr	r1, .L2885+28
	blx	r6
	b	.L2865
.L2864:
	ldr	r4, .L2885+4
	mov	r0, r7
	movw	r3, #8808
	ldr	r2, .L2885+32
	ldr	r1, .L2885+36
	ldr	r6, [r4, #68]
	blx	r6
	b	.L2865
.L2886:
	.align	2
.L2885:
	.word	compare_pic_by_poc_asc
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1444
	.word	.LC250
	.word	.LC248
	.word	.LC247
	.word	.LC35
	.word	.LC249
	.word	.LC218
	.word	.LC219
	UNWIND(.fnend)
	.size	HEVC_InsertFrmInDPB, .-HEVC_InsertFrmInDPB
	.align	2
	.type	HEVC_CreateLostPicture, %function
HEVC_CreateLostPicture:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 560
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #560)
	sub	sp, sp, #560
	mov	r4, r0
	add	r0, r0, #57088
	mov	r5, r1
	add	r0, r0, #224
	mov	r6, #0
.L2892:
	ldr	r3, [r0, #4]
	cmp	r3, #0
	bne	.L2888
	cmp	r0, #0
	beq	.L2909
	ldr	ip, [r4, #2492]
	cmp	ip, #0
	beq	.L2909
	ldr	r2, [r4, #2512]
	cmp	r0, r2
	beq	.L2888
	add	r2, r4, #2512
	b	.L2890
.L2891:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	beq	.L2888
.L2890:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L2891
.L2909:
	mov	r8, #584
	mov	r7, r0
	mla	r8, r8, r6, r4
	mov	r2, #504
	sub	r0, fp, #540
	mov	r9, #1
	mov	r3, #101
	str	r5, [fp, #-588]
	add	r1, r8, #57344
	str	r3, [fp, #-556]
	add	r1, r1, #40
	strb	r9, [fp, #-595]
	strb	r9, [fp, #-596]
	bl	memcpy
	add	r3, r8, #57088
	cmp	r6, #19
	movw	r1, #57320
	movw	r2, #57312
	mov	r6, #0
	strb	r9, [r3, #226]
	str	r7, [fp, #-544]
	str	r6, [r8, r1]
	str	r6, [fp, #-340]
	strb	r9, [r8, r2]
	bgt	.L2893
	ldr	r0, [r4, #2492]
	cmp	r0, #0
	beq	.L2895
	add	r1, r4, #2496
	mov	ip, r6
	add	r1, r1, #12
	mvn	r2, #-2147483648
	mov	r8, r1
.L2898:
	ldr	lr, [r8, #4]!
	add	ip, ip, #1
	ldr	r3, [lr, #12]
	rsb	r3, r5, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bge	.L2897
	ldrb	lr, [lr, #1]	@ zero_extendqisi2
	cmp	lr, #0
	movne	r2, r3
	movne	r6, #1
.L2897:
	cmp	ip, r0
	bne	.L2898
	cmp	r6, #0
	beq	.L2895
	mov	r6, #0
	b	.L2899
.L2900:
	add	r6, r6, #1
	cmp	r6, r0
	beq	.L2930
.L2899:
	ldr	ip, [r1, #4]!
	ldr	r3, [ip, #12]
	rsb	r3, r5, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bne	.L2900
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2900
	ldr	r1, [ip, #32]
	add	r6, r6, #628
	ldr	r0, [r4, #244]
	bl	FSP_GetLogicFs
	ldr	r9, .L2933
	ldr	r2, [r4, r6, asl #2]
	mov	r3, r5
	ldr	r1, .L2933+4
	ldr	r6, [r9, #68]
	ldr	r2, [r2, #12]
	mov	r7, r0
	mov	r0, #1
	blx	r6
	cmp	r7, #0
	beq	.L2901
	ldr	r0, [r7, #520]
	cmp	r0, #0
	beq	.L2931
	mov	r1, #0
	ldr	r0, [r4, #244]
	bl	FSP_NewLogicFs
	mov	r8, r0
	mov	r1, r0
	ldr	r0, [r4, #244]
	bl	FSP_GetLogicFs
	mvn	r2, r8
	mov	r2, r2, lsr #31
	cmp	r0, #0
	mov	r3, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L2904
	ldr	r1, [fp, #-544]
	sub	r2, fp, #596
	mov	r0, r4
	str	r8, [r1, #32]
	ldr	r1, [r7, #520]
	str	r1, [r3, #520]
	ldr	r1, [r7, #524]
	str	r1, [r3, #524]
	ldr	r1, [r7, #528]
	str	r1, [r3, #528]
	ldrsb	r3, [r7, #4]
	ldr	r1, [r4, #2492]
	str	r3, [fp, #-560]
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L2932
	ldr	r0, [r4, #244]
	mov	r1, r8
	mov	r2, r6
	bl	FSP_SetDisplay
	ldr	r3, [r4, #200]
	mov	r0, r6
	cmn	r3, #-2147483647
	streq	r5, [r4, #200]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2888:
	add	r6, r6, #1
	add	r0, r0, #584
	cmp	r6, #20
	bne	.L2892
.L2893:
	ldr	r3, .L2933
	mov	r0, #0
	ldr	r1, .L2933+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
.L2925:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2930:
	ldr	r9, .L2933
.L2901:
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L2933+12
	blx	r3
	mvn	r0, #3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2904:
	ldr	r3, [fp, #-544]
	mov	r0, r2
	ldr	r1, .L2933+16
	strb	r2, [r3]
	ldr	r3, [r9, #68]
	blx	r3
	mvn	r0, #3
	b	.L2925
.L2932:
	ldr	r3, [fp, #-544]
	mov	r1, r8
	mov	r5, #0
	mov	r2, #1
	strb	r5, [r3]
	ldr	r0, [r4, #244]
	bl	FSP_ClearLogicFs
	mov	r0, r5
	ldr	r3, [r9, #68]
	ldr	r1, .L2933+20
	blx	r3
	mvn	r0, #0
	b	.L2925
.L2895:
	ldr	r2, .L2933
	mov	r3, #0
	mov	r0, r3
	strb	r3, [r7]
	ldr	r1, .L2933+24
	ldr	r3, [r2, #68]
	blx	r3
	mvn	r0, #0
	b	.L2925
.L2931:
	ldr	r3, [r9, #68]
	ldr	r1, .L2933+28
	blx	r3
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #3
	b	.L2925
.L2934:
	.align	2
.L2933:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC254
	.word	.LC251
	.word	.LC252
	.word	.LC256
	.word	.LC257
	.word	.LC253
	.word	.LC255
	UNWIND(.fnend)
	.size	HEVC_CreateLostPicture, .-HEVC_CreateLostPicture
	.align	2
	.global	HEVC_DecSlice
	.type	HEVC_DecSlice, %function
HEVC_DecSlice:
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
	subs	r3, r0, #0
	str	r3, [fp, #-64]
	beq	.L3110
	ldr	r0, [fp, #-64]
	add	r10, r0, #40960
	ldr	r2, [r0, #2316]
	ldr	r3, [r2, #16]
	sub	r1, r3, #16
	str	r3, [r10, #2648]
	cmp	r1, #4
	ldr	r2, [r2, #32]
	str	r2, [r10, #2644]
	bls	.L2938
	ldr	r1, [r10, #2028]
	ldr	r2, [r0, #2308]
	cmp	r1, #0
	beq	.L3111
.L2939:
	cmp	r3, #21
	beq	.L3112
.L2941:
	ldr	r3, [fp, #-64]
	ldrb	r4, [r3, #1]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L3113
.L2942:
	ldr	r3, [fp, #-64]
	ldr	r2, [r3, #208]
	ldr	r3, [r3, #144]
	cmp	r2, r3
	bcs	.L3114
	ldr	r3, [fp, #-64]
	add	r3, r3, #45056
	str	r3, [fp, #-88]
	ldr	r3, [r3, #68]
	cmp	r3, #1
	beq	.L3115
.L2945:
	ldrb	r3, [r10, #2017]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3116
	ldr	r3, [r10, #2648]
	sub	r2, r3, #16
	cmp	r2, #5
	bls	.L2983
	ldr	r3, [r10, #2020]
	sub	r3, r3, #16
	cmp	r3, #5
	bls	.L2985
	ldr	r3, [r10, #2636]
	cmp	r3, #1
	beq	.L2986
	cmp	r3, #2
	beq	.L2987
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [r10, #2028]
.L2985:
	ldr	r0, [fp, #-64]
	bl	HEVC_CalcStreamBits
	ldr	r3, [fp, #-88]
	ldr	r3, [r3, #68]
	cmp	r3, #2
	beq	.L2989
	ldrb	r3, [r10, #2579]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2990
	ldr	r0, [fp, #-64]
	bl	HEVC_DecList
	subs	r2, r0, #0
	bne	.L3117
	ldr	r3, [r10, #2736]
	cmp	r3, #0
	beq	.L2990
	ldr	r1, [fp, #-64]
	ldr	r4, [r1, #2320]
	cmp	r4, #0
	beq	.L2993
	ldr	r1, [r4, #32]
	cmp	r1, #0
	beq	.L3118
	ldr	r3, [fp, #-64]
	mov	r4, r2
	add	r5, r3, #2320
	mov	r6, r3
	b	.L2998
.L2999:
	ldr	r3, [r0, #520]
	cmp	r3, #0
	beq	.L3000
	ldr	r3, [r10, #2736]
	add	r4, r4, #1
	cmp	r3, r4
	bls	.L3119
	ldr	r2, [r5, #4]!
	cmp	r2, #0
	beq	.L2993
	ldr	r1, [r2, #32]
	cmp	r1, #0
	beq	.L2994
.L2998:
	ldr	r1, [r1, #32]
	ldr	r0, [r6, #244]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L2999
.L3000:
	mov	ip, r0
	ldr	r0, [fp, #-64]
	add	r3, r4, #580
	ldr	r5, .L3132
	mov	r2, r4
	ldr	r1, .L3132+4
	ldr	r3, [r0, r3, asl #2]
	mov	r0, #1
	ldr	r4, [r5, #68]
	ldr	r3, [r3, #32]
	str	ip, [sp]
	blx	r4
.L2997:
	ldr	r0, [fp, #-64]
	bl	HEVC_PrintDPBState
	ldr	r3, [r5, #68]
	ldr	r1, .L3132+8
	mov	r0, #1
	blx	r3
.L3104:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3111:
	ldr	r1, [r2, #708]
	cmp	r1, #1
	bne	.L2939
	ldr	r1, [r2, #704]
	cmp	r1, #0
	bne	.L2939
	ldr	r1, [r2, #712]
	cmp	r1, #0
	bne	.L2939
	ldr	r2, [r2, #684]
	add	r2, r2, #1024
	cmp	r2, #2048
	bls	.L2939
.L2938:
	ldr	r0, [fp, #-64]
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L3105
	ldr	r3, [r10, #2648]
	cmp	r3, #21
	bne	.L2941
.L3112:
	ldr	r3, [fp, #-64]
	ldr	r2, [r3, #204]
	ldr	r3, [r3, #252]
	cmp	r2, r3
	bcs	.L2941
	ldr	r0, [fp, #-64]
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	beq	.L2941
.L3105:
	ldr	r3, .L3132
	mov	r0, #1
	ldr	r2, .L3132+12
	ldr	r1, .L3132+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3094
.L2983:
	str	r3, [r10, #2020]
	mov	r3, #0
	str	r3, [r10, #2028]
	b	.L2985
.L2990:
	ldr	r0, [fp, #-64]
	bl	HEVC_WriteSliceMsg
	cmp	r0, #0
	bne	.L3120
.L3011:
	ldr	r2, [r10, #2652]
	mov	r1, #1
	ldr	ip, [fp, #-64]
	mov	r0, #0
	add	r3, ip, #4096
	str	r2, [ip, #272]
	ldr	r2, [r10, #2624]
	str	r1, [ip, #168]
	str	r2, [ip, #252]
	ldr	r2, [r3, #404]
	str	r2, [r10, #2060]
	ldr	r3, [r3, #408]
	str	r3, [r10, #2064]
.L3094:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3115:
	ldr	r1, [fp, #-64]
	ldr	r2, [r1, #2308]
	ldr	r3, [r1, #220]
	add	r3, r3, #1
	str	r3, [r1, #220]
	ldr	r3, [r2, #8]
	cmp	r3, #2
	beq	.L2946
	ldr	r3, [r2, #12]
	cmp	r3, #2
	beq	.L3121
	ldr	r4, [fp, #-64]
	add	r3, r4, #46848
	mov	r0, r4
	mov	r5, r3
	bl	HEVC_RemoveDummyFrame
	mov	r0, r4
	bl	HEVC_ApplyReferencePictureSet
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	add	r3, r5, #28
	str	r3, [fp, #-100]
	add	r3, r5, #9
	str	r3, [fp, #-104]
.L2948:
	ldr	r3, [r10, #2648]
	sub	r3, r3, #19
	cmp	r3, #2
	bls	.L2950
	ldr	lr, [fp, #-64]
	movw	ip, #2024
	ldr	r3, [r10, #2652]
	movw	r0, #15788
	ldr	r4, [fp, #-88]
	ldr	r1, [lr, #2304]
	ldr	r2, [lr, #2300]
	mla	r1, ip, r3, r1
	ldr	ip, [r4, #1768]
	ldr	r3, [r4, #1764]
	add	r3, ip, r3
	str	r3, [fp, #-92]
	ldr	r1, [r1, #32]
	mov	ip, r3
	ldr	r3, [r4, #1772]
	mla	r2, r0, r1, r2
	mov	r1, #1
	cmp	ip, r3
	ldr	r2, [r2, #128]
	mov	r2, r1, asl r2
	mov	r4, r2
	bcs	.L2951
	add	r9, ip, #11712
	add	r2, ip, #46848
	add	r9, r9, #24
	add	r2, r2, #9
	ldr	r6, [lr, #2492]
	add	r3, r3, #46848
	add	r9, lr, r9, lsl #2
	mov	r1, r2
	add	r3, r3, #9
	str	r2, [fp, #-96]
	str	r10, [fp, #-84]
	mov	r2, #0
	mov	r10, r4
	add	r3, lr, r3
	mov	r0, r2
	str	r3, [fp, #-72]
	str	r2, [fp, #-76]
	add	r3, lr, r1
	str	r0, [fp, #-80]
	str	r3, [fp, #-68]
.L2952:
	cmp	r6, #0
	beq	.L2958
	ldr	r8, [r9, #-1884]
	mov	r3, #0
	ldr	r2, [fp, #-64]
	mov	r5, r3
	str	r3, [fp, #-60]
	mov	r3, r6
	add	r4, r2, #2512
	mov	r6, r8
	mov	r8, r3
	b	.L2955
.L3123:
	ldr	r3, [r4]
	ldr	r1, [r3, #52]
	cmp	r1, #0
	beq	.L2954
	ldr	r0, [r3, #12]
	ldr	r1, [r9]
	cmp	r0, r1
	ldreqb	r3, [r3, #1]	@ zero_extendqisi2
	beq	.L3102
.L2954:
	add	r5, r5, #1
	add	r4, r4, #4
	cmp	r5, r8
	beq	.L3122
.L2955:
	cmp	r6, #0
	bne	.L3123
	ldr	r7, [r4]
	mov	r1, r10
	ldr	r3, [r7, #52]
	cmp	r3, #0
	beq	.L2954
	ldr	r0, [r7, #12]
	bl	__aeabi_idivmod
	ldr	r0, [r9]
	str	r1, [fp, #-56]
	mov	r1, r10
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-56]
	cmp	r3, r1
	bne	.L2954
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
.L3102:
	cmp	r3, #0
	add	r5, r5, #1
	ldr	r3, [fp, #-60]
	add	r4, r4, #4
	movne	r3, #1
	cmp	r5, r8
	str	r3, [fp, #-60]
	bne	.L2955
.L3122:
	ldr	r3, [fp, #-60]
	mov	r6, r8
	cmp	r3, #0
	beq	.L2958
.L2956:
	ldr	r3, [fp, #-68]
	add	r9, r9, #4
	ldr	r2, [fp, #-72]
	add	r3, r3, #1
	str	r3, [fp, #-68]
	cmp	r3, r2
	bne	.L2952
	ldr	r3, [fp, #-92]
	ldr	r10, [fp, #-84]
	cmp	r3, #0
	beq	.L2959
.L3013:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-96]
	ldr	lr, [fp, #-100]
	ldr	r5, [fp, #-104]
	add	r7, r3, r2
	ldr	r1, [fp, #-80]
	mov	r8, r3
	ldr	r9, [fp, #-76]
.L2960:
	cmp	r6, #0
	beq	.L2964
	add	ip, r8, #2496
	mov	r4, #0
	add	ip, ip, #12
	mov	r3, r4
	str	r1, [fp, #-56]
	b	.L2962
.L2961:
	cmp	r3, r6
	beq	.L3124
.L2962:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	ldr	r0, [r2, #52]
	cmp	r0, #0
	bne	.L2961
	ldr	r1, [lr]
	ldr	r0, [r10, #2624]
	add	r0, r0, r1
	ldr	r1, [r2, #12]
	cmp	r1, r0
	bne	.L2961
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r4, #1
	cmp	r3, r6
	bne	.L2962
.L3124:
	cmp	r4, #0
	ldr	r1, [fp, #-56]
	beq	.L2964
.L2963:
	add	r5, r5, #1
	add	lr, lr, #4
	cmp	r5, r7
	bne	.L2960
	str	r1, [fp, #-80]
	str	r9, [fp, #-76]
.L2959:
	ldr	r3, [fp, #-80]
	cmp	r3, #0
	beq	.L2950
	ldr	r3, .L3132
	mov	r0, #1
	ldr	r2, [fp, #-76]
	ldr	r1, .L3132+20
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [fp, #-64]
	ldr	r1, .L3132
	ldr	r3, [r3, #2308]
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L3125
	ldr	r1, [fp, #-76]
	ldr	r0, [fp, #-64]
	bl	HEVC_CreateLostPicture
	cmp	r0, #0
	beq	.L2948
	ldr	r0, [fp, #-64]
	bl	HEVC_RemoveDummyFrame
	b	.L3104
.L3113:
	ldr	r3, [r3, #2492]
	cmp	r3, #0
	beq	.L2942
	ldr	r0, [fp, #-64]
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L2942
	ldr	r3, .L3132
	mov	r0, r4
	ldr	r2, .L3132+12
	ldr	r1, .L3132+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3094
.L2975:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r2, .L3132+28
	ldr	r1, .L3132+32
	blx	r3
.L2972:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r2, .L3132+36
	ldr	r1, .L3132+40
	blx	r3
.L2978:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r2, .L3132+44
	ldr	r1, .L3132+48
	blx	r3
	ldr	r4, [fp, #-64]
	mov	r0, r4
	bl	HEVC_PrintDPBState
	mov	r0, r4
	bl	HEVC_ClearDPB
.L2946:
	ldr	r0, [fp, #-64]
	bl	HEVC_InitPic
	cmn	r0, #2
	beq	.L3094
	cmp	r0, #0
	bne	.L3126
	ldr	r4, [fp, #-64]
	mov	r0, r4
	bl	HEVC_SetScalingList
	mov	r0, r4
	bl	HEVC_WritePicMsg
	cmp	r0, #0
	beq	.L2945
	ldr	r3, .L3132
	mov	r0, #1
	ldr	r1, .L3132+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3094
.L3121:
	mov	r4, r1
	mov	r0, r1
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	b	.L2946
.L2964:
	ldr	r3, [r10, #2624]
	ldr	r0, [lr]
	ldr	r2, [r8, #200]
	add	r3, r3, r0
	cmp	r3, r2
	blt	.L2963
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r9, r3
	movne	r1, #1
	b	.L2963
.L2958:
	ldr	r3, [fp, #-84]
	ldr	r2, [fp, #-64]
	ldr	r1, [r9, #-68]
	ldr	r3, [r3, #2624]
	ldr	r2, [r2, #200]
	add	r3, r3, r1
	cmp	r3, r2
	blt	.L2956
	ldr	r2, [fp, #-68]
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [fp, #-76]
	movne	r2, r3
	ldr	r3, [fp, #-80]
	str	r2, [fp, #-76]
	movne	r3, #1
	str	r3, [fp, #-80]
	b	.L2956
.L2950:
	ldr	r7, [fp, #-64]
	ldr	r5, .L3132
	add	r4, r7, #2480
	mov	r0, r7
	add	r4, r4, #8
	bl	HEVC_UpdateReflist
	mov	r0, r7
	bl	HEVC_UpdateLTReflist
	b	.L2967
.L2969:
	str	lr, [sp]
	ldr	r8, [r5, #68]
	blx	r8
	mov	r1, r4
	ldr	r0, [r7, #244]
	bl	HEVC_IncreaseDPBSize.isra.28
	cmp	r0, #0
	bne	.L3127
.L2967:
	ldr	ip, [r7, #2492]
	mov	r0, #13
	ldr	lr, [r7, #2488]
	ldr	r2, .L3132+44
	cmp	ip, lr
	ldr	r1, .L3132+56
	ldr	r6, .L3132
	mov	r3, ip
	bcs	.L2969
.L2968:
	ldr	r7, .L3132
	mov	r3, ip
	ldr	r6, [fp, #-64]
.L2977:
	cmp	r3, lr
	bcc	.L2946
	str	lr, [sp]
	mov	r0, #1
	ldr	r4, [r7, #68]
	ldr	r2, .L3132+44
	ldr	r1, .L3132+60
	blx	r4
	ldr	r3, [r6, #2492]
	ldr	r5, .L3132
	cmp	r3, #16
	bhi	.L2970
	cmp	r3, #0
	beq	.L2975
	add	r9, r6, #2496
	mvn	r8, #0
	add	r9, r9, #12
	mvn	r0, #-2147483648
	mov	r4, #0
	b	.L2974
.L2973:
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L3128
.L2974:
	ldr	r2, [r9, #4]!
	ldr	r1, [r2, #12]
	cmp	r1, r0
	bge	.L2973
	ldr	r2, [r2]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	bne	.L2973
	ldr	r3, [r7, #112]
	mov	r8, r4
	blx	r3
	ldr	r3, [r6, #2492]
	ldr	r2, [r9]
	add	r4, r4, #1
	cmp	r4, r3
	ldr	r0, [r2, #12]
	bcc	.L2974
.L3128:
	cmn	r8, #1
	beq	.L2975
	str	r0, [sp]
	mov	r3, r8
	ldr	r2, .L3132+28
	mov	r0, #1
	ldr	r1, .L3132+64
	ldr	r4, [r7, #68]
	blx	r4
	mov	r1, r8
	mov	r0, r6
	bl	HEVC_OutputOneFrmFromDPB
	ldr	r3, .L3132
	cmp	r0, #0
	bne	.L2976
	ldr	r3, [r6, #2492]
	ldr	lr, [r6, #2488]
	b	.L2977
.L3119:
	cmp	r3, #0
	beq	.L2990
	ldr	r2, [r10, #2740]
	cmp	r2, #0
	beq	.L2990
	ldr	r2, [fp, #-64]
	ldr	r4, [r2, #2388]
	cmp	r4, #0
	beq	.L3003
	ldr	r2, [r4, #32]
	cmp	r2, #0
	beq	.L3129
	ldr	r3, [fp, #-64]
	mov	r4, #0
	add	r5, r3, #2384
	add	r5, r5, #4
	mov	r6, r3
	b	.L3007
.L3008:
	ldr	r2, [r0, #520]
	cmp	r2, #0
	beq	.L3009
	ldr	r3, [r10, #2740]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L2990
	ldr	r3, [r5, #4]!
	cmp	r3, #0
	beq	.L3130
	ldr	r2, [r3, #32]
	cmp	r2, #0
	beq	.L3131
.L3007:
	ldr	r1, [r2, #32]
	ldr	r0, [r6, #244]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L3008
.L3009:
	ldr	r5, .L3132
	mov	r3, r0
	mov	r2, r4
	ldr	r1, .L3132+68
	mov	r0, #1
	ldr	r4, [r5, #68]
	blx	r4
	b	.L2997
.L2987:
	ldr	r3, [r10, #2028]
	sub	r3, r3, #1
	cmp	r3, #1
	bls	.L2985
	mov	r3, #0
.L3103:
	str	r3, [r10, #2028]
	b	.L2985
.L2986:
	ldr	r2, [r10, #2028]
	cmp	r2, #2
	bne	.L3103
	b	.L2985
.L2989:
	ldr	r0, [fp, #-64]
	bl	HEVC_ClearCurrNal
	b	.L3011
.L2951:
	ldr	r3, [fp, #-92]
	cmp	r3, #0
	beq	.L2950
	ldr	r3, [fp, #-92]
	ldr	r2, [fp, #-64]
	add	r3, r3, #46848
	add	r3, r3, #9
	str	r3, [fp, #-96]
	ldr	r6, [r2, #2492]
	mov	r3, #0
	str	r3, [fp, #-76]
	str	r3, [fp, #-80]
	b	.L3013
.L3125:
	ldr	r0, [fp, #-76]
	ldr	r3, [r10, #2624]
	str	r0, [sp]
	mov	r0, #1
	ldr	r4, [r1, #68]
	ldr	r1, .L3132+72
	blx	r4
	b	.L3104
.L3118:
	mov	r4, r1
.L2994:
	ldr	r5, .L3132
	mov	r2, r4
	ldr	r1, .L3132+76
	mov	r0, #1
	ldr	r4, [r5, #68]
	blx	r4
	b	.L2997
.L3116:
	ldr	r3, .L3132
	mov	r0, #1
	ldr	r1, .L3132+80
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3094
.L2993:
	ldr	r5, .L3132
	mov	r2, r4
	ldr	r1, .L3132+84
	mov	r0, #1
	ldr	r4, [r5, #68]
	blx	r4
	b	.L2997
.L3127:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r2, .L3132+44
	ldr	r1, .L3132+88
	blx	r3
	ldr	r3, [fp, #-64]
	ldr	ip, [r3, #2492]
	ldr	lr, [r3, #2488]
	b	.L2968
.L2976:
	ldr	r3, [r3, #68]
	mov	r0, #1
	ldr	r2, .L3132+36
	ldr	r1, .L3132+48
	blx	r3
	b	.L2978
.L2970:
	ldr	r4, [r5, #68]
	mov	r0, #1
	ldr	r2, .L3132+28
	ldr	r1, .L3132+92
	blx	r4
	b	.L2972
.L3130:
	ldr	r3, [r10, #2736]
.L3003:
	ldr	r5, .L3132
	mov	r2, r4
	ldr	r1, .L3132+96
	mov	r0, #1
	ldr	r4, [r5, #68]
	blx	r4
	b	.L2997
.L3120:
	ldr	r3, .L3132
	mov	r0, #1
	ldr	r1, .L3132+100
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3094
.L3117:
	ldr	r3, .L3132
	mov	r0, #1
	ldr	r1, .L3132+104
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3094
.L3126:
	ldr	r3, .L3132
	mov	r0, #1
	ldr	r1, .L3132+108
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3094
.L3114:
	ldr	r5, .L3132
	mov	r0, #0
	ldr	r1, .L3132+112
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r0, [fp, #-64]
	ldr	r3, [r0, #208]
	ldr	r2, [r0, #144]
	cmp	r3, r2
	bcc	.L2944
	ldr	r1, .L3132+116
	ldr	r4, [r1]
	cmp	r4, #0
	beq	.L2944
	str	r3, [fp, #-52]
	mov	r1, #108
	str	r2, [fp, #-48]
	mov	r3, #8
	sub	r2, fp, #52
	ldr	r0, [r0, #244]
	blx	r4
.L2944:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L3132+120
	blx	r3
	ldr	r0, [fp, #-64]
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L3094
.L3131:
	ldr	r3, [r10, #2736]
.L3004:
	ldr	r5, .L3132
	mov	r2, r4
	ldr	r1, .L3132+124
	mov	r0, #1
	ldr	r4, [r5, #68]
	blx	r4
	b	.L2997
.L3129:
	mov	r4, r2
	b	.L3004
.L3110:
	ldr	ip, .L3132
	movw	r3, #4271
	ldr	r2, .L3132+12
	mov	r0, #1
	ldr	r1, .L3132+128
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L3094
.L3133:
	.align	2
.L3132:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC277
	.word	.LC283
	.word	.LANCHOR0+1464
	.word	.LC258
	.word	.LC263
	.word	.LC259
	.word	.LANCHOR0+1504
	.word	.LC267
	.word	.LANCHOR0+1532
	.word	.LC282
	.word	.LANCHOR0+1480
	.word	.LC270
	.word	.LC272
	.word	.LC264
	.word	.LC266
	.word	.LC269
	.word	.LC280
	.word	.LC262
	.word	.LC276
	.word	.LC273
	.word	.LC275
	.word	.LC265
	.word	.LC268
	.word	.LC278
	.word	.LC281
	.word	.LC274
	.word	.LC271
	.word	.LC260
	.word	g_event_report
	.word	.LC261
	.word	.LC279
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_DecSlice, .-HEVC_DecSlice
	.align	2
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
	ldr	ip, [r0, #2316]
	mov	r4, r0
	ldr	r3, [ip, #8]
	cmp	r3, #0
	ldrne	r1, [r0, #224]
	movne	r2, ip
	movne	r3, #0
	beq	.L3139
.L3138:
	ldr	r0, [r2, #48]
	add	r3, r3, #1
	add	r2, r2, #28
	add	r1, r1, r0
	str	r1, [r4, #224]
	ldr	r0, [ip, #8]
	cmp	r0, r3
	bhi	.L3138
.L3139:
	mov	r3, #0
	strb	r3, [ip, #1]
	ldr	r3, [r4, #2316]
	ldr	r2, [r3, #16]
	sub	r2, r2, #36
	cmp	r2, #1
	bls	.L3240
.L3137:
	ldr	r2, [r3, #4]
	add	r2, r2, #16
	str	r2, [r3, #4]
	ldr	r3, [r4, #2316]
	ldr	r2, [r3, #16]
	cmp	r2, #49
	ldrls	pc, [pc, r2, asl #2]
	b	.L3140
.L3142:
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3141
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3143
	.word	.L3144
	.word	.L3145
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3146
	.word	.L3146
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3140
	.word	.L3147
	.word	.L3148
.L3240:
	mov	r2, #1
	strb	r2, [r4]
	b	.L3137
.L3148:
	add	r5, r4, #2448
	mov	r1, #32
	add	r5, r5, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #32
	mov	r6, r0
	mov	r0, r5
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r6, r3
	bne	.L3160
	ldr	r6, .L3242
	mov	r3, #1
	strb	r3, [r4, #6]
	ldr	r5, [r6]
	cmp	r5, #0
	beq	.L3159
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #244]
	blx	r5
.L3159:
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L3160
.L3238:
	ldr	r5, [r6]
	cmp	r5, #0
	beq	.L3227
.L3229:
	mov	r3, #0
	ldr	r0, [r4, #244]
	mov	r2, r3
	mov	r1, #113
	blx	r5
.L3227:
	mvn	r0, #0
.L3150:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3141:
	mov	r0, r4
	bl	HEVC_DecSlice
	cmn	r0, #2
	beq	.L3150
	cmp	r0, #0
	bne	.L3241
.L3231:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3143:
	mov	r0, r4
	bl	HEVC_DecVPS
	mov	r5, r0
	mov	r0, r4
	bl	HEVC_ClearCurrNal
	cmp	r5, #0
	beq	.L3231
	ldr	r3, .L3242+4
	mov	r0, #1
	ldr	r6, .L3242
	ldr	r1, .L3242+8
	b	.L3236
.L3144:
	mov	r0, r4
	bl	HEVC_DecSPS
	mov	r5, r0
	mov	r0, r4
	bl	HEVC_ClearCurrNal
	cmp	r5, #0
	beq	.L3231
	ldr	r3, .L3242+4
	mov	r0, #1
	ldr	r6, .L3242
	ldr	r1, .L3242+12
	b	.L3236
.L3145:
	mov	r0, r4
	bl	HEVC_DecPPS
	mov	r5, r0
	mov	r0, r4
	bl	HEVC_ClearCurrNal
	cmp	r5, #0
	beq	.L3231
	ldr	r3, .L3242+4
	mov	r0, #1
	ldr	r6, .L3242
	ldr	r1, .L3242+16
.L3236:
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r7, [r6]
	cmp	r7, #0
	beq	.L3227
	sub	r2, fp, #28
	mvn	r5, #0
	mov	r3, #4
	mov	r1, #100
	str	r5, [r2, #-4]!
	ldr	r0, [r4, #244]
	blx	r7
	ldr	r6, [r6]
	cmp	r6, #0
	beq	.L3227
	mov	r3, #0
	ldr	r0, [r4, #244]
	mov	r2, r3
	mov	r1, #113
	blx	r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3146:
	mov	r0, r4
	bl	HEVC_DecSEI
	mov	r5, r0
	mov	r0, r4
	bl	HEVC_ClearCurrNal
	cmp	r5, #0
	beq	.L3231
	ldr	r3, .L3242+4
	mov	r0, #1
	ldr	r1, .L3242+20
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, .L3242
	ldr	r5, [r3]
	cmp	r5, #0
	bne	.L3229
	b	.L3227
.L3147:
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3156
	mov	r0, r4
	bl	HEVC_ClearCurrNal
	add	r3, r4, #40960
	ldrb	r3, [r3, #2017]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3231
.L3156:
	add	r6, r4, #2448
	mov	r1, #32
	add	r6, r6, #8
	mov	r5, #0
	strb	r5, [r4, #5]
	mov	r0, r6
	bl	BsGet
	mov	r1, #32
	mov	r7, r0
	mov	r0, r6
	bl	BsGet
	ldr	r2, .L3242+24
	rev	lr, r7
	ldrb	r1, [r2, #1574]	@ zero_extendqisi2
	ldrb	r3, [r2, #1573]	@ zero_extendqisi2
	ldrb	r6, [r2, #1570]	@ zero_extendqisi2
	ldrb	ip, [r2, #1575]	@ zero_extendqisi2
	orr	r3, r3, r1, asl #8
	ldrb	r1, [r2, #1569]	@ zero_extendqisi2
	ldrb	r7, [r2, #1571]	@ zero_extendqisi2
	orr	r1, r1, r6, asl #8
	orr	ip, r3, ip, asl #16
	ldrb	r6, [r2, #1576]	@ zero_extendqisi2
	ldrb	r3, [r2, #1572]	@ zero_extendqisi2
	orr	r2, r1, r7, asl #16
	orr	r1, ip, r6, asl #24
	orr	r2, r2, r3, asl #24
	rev	r0, r0
	cmp	r0, r1
	cmpeq	lr, r2
	bne	.L3231
	ldr	r6, .L3242
	ldr	r7, [r6]
	cmp	r7, #0
	beq	.L3157
	mov	r3, r5
	mov	r2, r5
	mov	r1, #112
	ldr	r0, [r4, #244]
	blx	r7
.L3157:
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	bne	.L3238
	b	.L3231
.L3140:
	ldr	r3, .L3242+4
	mov	r0, #22
	ldr	r1, .L3242+28
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #2316]
	ldr	r3, [r3, #16]
	cmp	r3, #63
	bls	.L3160
	ldr	r6, .L3242
	ldr	r5, [r6]
	cmp	r5, #0
	beq	.L3161
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r4, #244]
	blx	r5
.L3161:
	mov	r0, r4
	bl	HEVC_ClearCurrNal
	ldr	r5, [r6]
	cmp	r5, #0
	beq	.L3231
	mov	r3, #0
	ldr	r0, [r4, #244]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L3231
.L3160:
	mov	r0, r4
	bl	HEVC_ClearCurrNal
	mov	r0, #0
	b	.L3150
.L3241:
	mov	r0, r4
	bl	HEVC_ClearCurrSlice
	ldr	r3, .L3242
	ldr	r5, [r3]
	cmp	r5, #0
	bne	.L3229
	b	.L3227
.L3243:
	.align	2
.L3242:
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC284
	.word	.LC285
	.word	.LC286
	.word	.LC287
	.word	.LANCHOR0
	.word	.LC288
	UNWIND(.fnend)
	.size	HEVC_DecOneNal, .-HEVC_DecOneNal
	.align	2
	.global	HEVCDEC_VDMPostProc
	.type	HEVCDEC_VDMPostProc, %function
HEVCDEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
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
	cmp	r3, #0
	cmpne	r0, #0
	mov	r4, r0
	beq	.L3333
	ldr	r3, [fp, #8]
	cmp	r3, #0
	bne	.L3334
	ldr	r3, [fp, #4]
	add	r5, r0, #40960
	cmp	r3, #0
	str	r1, [r5, #2056]
	beq	.L3248
	ldr	r3, .L3354
	ldr	r3, [r3, #52]
	cmp	r3, #3
	beq	.L3335
	cmp	r3, #1
	beq	.L3248
.L3250:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	ldrb	r3, [r5, #2017]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3336
	ldr	r3, [r4, #2308]
	ldr	r2, [r5, #2056]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	bhi	.L3337
	ldr	r3, [r4, #2312]
	ldr	r2, [r5, #2068]
	add	r3, r3, #4096
	ldr	r3, [r3, #1036]
	str	r3, [r2, #576]
	ldr	r3, [r4, #2312]
	ldr	r2, [r5, #2068]
	add	r3, r3, #4096
	ldr	r3, [r3, #1040]
	str	r3, [r2, #580]
	ldr	r3, [r4, #248]
	cmp	r3, #2
	beq	.L3338
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	beq	.L3339
	cmp	r3, #1
	beq	.L3340
	cmp	r3, #0
	beq	.L3285
	ldr	r7, .L3354+4
.L3286:
	mov	r0, r4
	mvn	r6, #0
	bl	HEVC_ClearCurrPic
	ldr	r3, [r7, #68]
	ldr	r2, .L3354+8
	mov	r0, #1
	ldr	r1, .L3354+12
	blx	r3
	mov	r3, #0
	strb	r3, [r5, #2017]
.L3282:
	ldr	r3, [r7, #68]
	mov	r2, r6
	ldr	r1, .L3354+16
	mov	r0, #0
	blx	r3
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3334:
	ldr	ip, .L3354+4
	movw	r3, #11026
.L3332:
	ldr	r2, .L3354+20
	mov	r0, #1
	ldr	r1, .L3354+24
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
.L3329:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3333:
	ldr	ip, .L3354+4
	movw	r3, #11025
	b	.L3332
.L3248:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	b	.L3250
.L3340:
	ldr	r1, [r4, #2492]
	ldr	r3, [r4, #2488]
	cmp	r1, r3
	bcs	.L3341
.L3268:
	add	r2, r4, #42752
	mov	r0, r4
	add	r2, r2, #224
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L3342
	ldr	r1, [r5, #2068]
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	beq	.L3343
	cmn	r0, #3
	beq	.L3273
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3344
.L3273:
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #0
	bne	.L3280
.L3285:
	add	r6, r4, #49152
	ldr	r3, [r6, #2200]
	cmp	r3, #1
	beq	.L3274
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3345
	ldr	r2, [r5, #2068]
	mov	r3, #1
	mov	r1, #2
	str	r1, [r2, #8]
	str	r3, [r6, #2200]
	ldr	r2, [r5, #2024]
	str	r2, [r4, #212]
	ldr	r2, [r5, #2068]
	strb	r3, [r2, #2]
.L3274:
	ldr	r1, [r4, #2492]
	ldr	r3, [r4, #2488]
	cmp	r1, r3
	bcs	.L3346
.L3277:
	add	r2, r4, #42752
	mov	r0, r4
	add	r2, r2, #224
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L3347
	ldr	r3, [r4, #2492]
	cmp	r3, #0
	bne	.L3348
.L3280:
	mov	r6, #0
.L3281:
	cmp	r6, #0
	mov	r3, #0
	strb	r3, [r5, #2017]
	beq	.L3283
	ldr	r7, .L3354+4
	b	.L3282
.L3336:
	ldr	r3, .L3354+4
	mov	r0, #1
	ldr	r2, .L3354+8
	ldr	r1, .L3354+28
	ldr	r3, [r3, #68]
	blx	r3
.L3283:
	mov	r3, #1
	mov	r0, #0
	str	r3, [r4, #168]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3335:
	bl	HEVC_ClearAllSlice
	ldr	r0, [fp, #8]
	b	.L3329
.L3337:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, [r4, #2308]
	ldr	r1, .L3354+4
	mov	r0, #1
	ldr	r2, [r5, #2056]
	ldr	r3, [r3, #4]
	ldr	r5, [r1, #68]
	ldr	r1, .L3354+32
	blx	r5
	b	.L3283
.L3338:
	ldr	r8, [r5, #2068]
	mov	r9, #0
	mov	ip, #1
	add	r1, r5, #2064
	add	r1, r1, #8
	mov	r2, #504
	strb	ip, [r8, #2]
	add	r0, r8, #72
	str	r3, [r8, #4]
	strb	r9, [r8, #1]
	ldr	r3, [r5, #2028]
	ldr	r7, .L3354+4
	str	r3, [r8, #16]
	ldr	r3, [r5, #2056]
	str	r3, [r8, #20]
	bl	memcpy
	str	r9, [r8, #48]
	ldr	r3, [r5, #2056]
	mov	r2, r9
	ldr	r1, [r8, #32]
	str	r3, [r8, #40]
	ldr	r0, [r4, #244]
	bl	FSP_SetRef
	mov	r1, r8
	mov	r0, r4
	bl	HEVC_OutputFrmToVO
	str	r9, [r8, #4]
	mov	r2, #560
	ldr	r3, [r7, #48]
	mov	r1, r9
	mov	r6, r0
	add	r0, r4, #42752
	add	r0, r0, #224
	blx	r3
	ldr	r3, [r5, #2052]
	ldr	r2, [r4, #180]
	cmp	r3, r2
	addne	r3, r3, #524
	addne	r3, r4, r3, lsl #2
	strne	r9, [r3, #4]
	strne	r2, [r5, #2052]
	cmp	r6, #0
	bne	.L3349
.L3256:
	ldr	r8, [r7, #68]
	movw	r3, #8575
	mov	r2, r6
	ldr	r1, .L3354+36
	mov	r0, #14
	blx	r8
.L3257:
	cmn	r6, #1
	bne	.L3281
	b	.L3286
.L3339:
	ldrb	r2, [r5, #2016]	@ zero_extendqisi2
	cmp	r2, #0
	ldreq	r2, [r5, #2068]
	streq	r3, [r2, #4]
	bne	.L3350
.L3263:
	ldr	r3, [r5, #2068]
	mov	r2, #1
	mov	r0, r4
	strb	r2, [r3, #2]
	ldr	r1, [r5, #2068]
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r6, r0
	beq	.L3351
	cmn	r0, #3
	beq	.L3266
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3352
.L3266:
	ldr	r7, .L3354+4
	mov	r6, #0
.L3284:
	ldr	r8, [r7, #68]
	movw	r3, #8590
	mov	r2, r6
	ldr	r1, .L3354+36
	mov	r0, #14
	blx	r8
	b	.L3257
.L3348:
	mov	r0, r4
	bl	HEVC_OutputFrmFromDPB
	cmp	r0, #0
	beq	.L3280
	ldr	r7, .L3354+4
	mov	r0, #1
	ldr	r2, .L3354+40
	ldr	r1, .L3354+44
	ldr	r3, [r7, #68]
	blx	r3
.L3276:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r2, .L3354+8
	ldr	r1, .L3354+48
	blx	r3
	b	.L3286
.L3346:
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3331
	ldr	r7, .L3354+4
	mov	r0, #0
	ldr	r1, .L3354+52
	ldr	r3, [r7, #68]
	blx	r3
.L3331:
	ldr	r1, [r4, #2492]
	b	.L3277
.L3349:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r2, .L3354+8
	ldr	r1, .L3354+56
	blx	r3
	b	.L3256
.L3350:
	ldr	r1, [r4, #2492]
	ldr	r3, [r4, #2488]
	cmp	r1, r3
	bcc	.L3260
	cmp	r3, #15
	bhi	.L3262
	add	r1, r4, #2480
	ldr	r0, [r4, #244]
	add	r1, r1, #8
	bl	HEVC_IncreaseDPBSize.isra.28
	cmp	r0, #0
	beq	.L3353
.L3262:
	ldr	r1, [r4, #2512]
	mov	r0, r4
	bl	HEVC_UnMarkFrameStoreRef
	mov	r1, #0
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	mov	r1, #0
	mov	r0, r4
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r1, [r4, #2492]
.L3260:
	add	r2, r4, #42752
	mov	r0, r4
	add	r2, r2, #224
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	beq	.L3263
	ldr	r7, .L3354+4
	movw	r3, #8294
	str	r0, [sp]
	mov	r0, #0
	ldr	r2, .L3354+60
	mvn	r6, #6
	ldr	r8, [r7, #68]
	ldr	r1, .L3354+64
	blx	r8
.L3264:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r2, .L3354+8
	ldr	r1, .L3354+68
	blx	r3
	b	.L3284
.L3341:
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3330
	ldr	r7, .L3354+4
	mov	r0, #0
	ldr	r2, .L3354+72
	ldr	r1, .L3354+76
	ldr	r3, [r7, #68]
	blx	r3
.L3330:
	ldr	r1, [r4, #2492]
	b	.L3268
.L3345:
	ldr	r7, .L3354+4
	mov	r0, #1
	ldr	r2, .L3354+80
	ldr	r1, .L3354+84
	ldr	r3, [r7, #68]
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r2, .L3354+40
	mov	r0, #0
	ldr	r1, .L3354+88
	blx	r3
	b	.L3276
.L3353:
	ldr	r1, [r4, #2492]
	b	.L3260
.L3342:
	ldr	r7, .L3354+4
	mov	r0, #0
	ldr	r2, .L3354+72
	ldr	r1, .L3354+92
	ldr	r3, [r7, #68]
	blx	r3
.L3271:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r2, .L3354+8
	ldr	r1, .L3354+96
	blx	r3
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #12]
	cmp	r3, #0
	bne	.L3286
	b	.L3285
.L3347:
	ldr	r7, .L3354+4
	mov	r2, r0
	ldr	r1, .L3354+100
	mov	r0, #0
	ldr	r3, [r7, #68]
	blx	r3
	b	.L3276
.L3352:
	ldr	r7, .L3354+4
	mov	r0, #0
	ldr	r2, .L3354+60
	mvn	r6, #0
	ldr	r1, .L3354+84
	ldr	r3, [r7, #68]
	blx	r3
	b	.L3264
.L3344:
	ldr	r7, .L3354+4
	mov	r0, r6
	ldr	r2, .L3354+72
	ldr	r1, .L3354+84
	ldr	r3, [r7, #68]
	blx	r3
	b	.L3271
.L3343:
	ldr	r7, .L3354+4
	mov	r0, r6
	ldr	r2, .L3354+72
	ldr	r1, .L3354+104
	ldr	r3, [r7, #68]
	blx	r3
	b	.L3271
.L3351:
	ldr	r7, .L3354+4
	mov	r0, #0
	ldr	r2, .L3354+60
	ldr	r1, .L3354+104
	ldr	r3, [r7, #68]
	blx	r3
	b	.L3264
.L3355:
	.align	2
.L3354:
	.word	g_VdmDrvParam
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1608
	.word	.LC302
	.word	.LC303
	.word	.LANCHOR0+1588
	.word	.LC35
	.word	.LC289
	.word	.LC290
	.word	.LC292
	.word	.LANCHOR0+1700
	.word	.LC301
	.word	.LC306
	.word	.LC299
	.word	.LC291
	.word	.LANCHOR0+1628
	.word	.LC293
	.word	.LC304
	.word	.LANCHOR0+1652
	.word	.LC296
	.word	.LANCHOR0+1676
	.word	.LC295
	.word	.LC298
	.word	.LC297
	.word	.LC305
	.word	.LC300
	.word	.LC294
	UNWIND(.fnend)
	.size	HEVCDEC_VDMPostProc, .-HEVCDEC_VDMPostProc
	.align	2
	.global	HEVCDEC_GetImageBuffer
	.type	HEVCDEC_GetImageBuffer, %function
HEVCDEC_GetImageBuffer:
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
	subs	r8, r0, #0
	mov	r3, #0
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	beq	.L3397
	ldr	r3, [r8, #176]
	cmp	r3, #0
	beq	.L3360
	add	r3, r8, #40960
	ldrb	r3, [r3, #2017]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3360
	add	r7, r8, #57088
	add	lr, r8, #68608
	add	r7, r7, #224
	add	lr, lr, #384
	mov	r2, r7
.L3368:
	ldr	r3, [r2, #4]
	cmp	r3, #0
	bne	.L3361
	cmp	r2, #0
	beq	.L3362
	ldr	ip, [r8, #2492]
	cmp	ip, #0
	beq	.L3362
	ldr	r1, [r8, #2512]
	cmp	r1, r2
	beq	.L3361
	add	r1, r8, #2512
	b	.L3363
.L3364:
	ldr	r0, [r1, #4]!
	cmp	r0, r2
	beq	.L3361
.L3363:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L3364
.L3362:
	ldr	r0, [r8, #244]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L3360
	cmn	r0, #1
	beq	.L3398
	add	r0, r8, #50944
	add	r0, r0, #56
	bl	IsVoQueueEmpty
	cmp	r0, #1
	beq	.L3399
.L3395:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3360:
	mov	r0, #1
.L3391:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3361:
	add	r2, r2, #584
	cmp	r2, lr
	bne	.L3368
	ldr	r9, .L3400
	add	r0, r8, #50944
	add	r0, r0, #56
	sub	r2, fp, #48
	sub	r1, fp, #52
	bl	GetQueueImgNum
	ldr	r3, [r9, #68]
	ldr	r1, .L3400+4
	mov	r0, #1
	blx	r3
	ldr	r3, [r8, #176]
	cmp	r3, #0
	movne	r10, #0
	movne	r6, r9
	beq	.L3373
.L3369:
	ldrb	ip, [r7, #2]	@ zero_extendqisi2
	mov	r3, r7
	mov	r2, r10
	ldr	r1, .L3400+8
	mov	r0, #1
	add	r5, r7, #280
	str	ip, [sp, #8]
	mov	r4, #0
	ldrb	ip, [r7, #1]	@ zero_extendqisi2
	str	ip, [sp, #4]
	ldr	ip, [r7, #4]
	str	ip, [sp]
	ldr	ip, [r9, #68]
	blx	ip
.L3372:
	mov	r2, r4
	ldr	r3, [r5, #4]!
	add	r4, r4, #1
	ldr	r1, .L3400+12
	mov	r0, #1
	ldr	ip, [r9, #68]
	blx	ip
	cmp	r4, #4
	bne	.L3372
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L3400+16
	add	r10, r10, r0
	blx	r3
	ldr	r3, [r8, #176]
	add	r7, r7, #584
	cmp	r10, r3
	bcc	.L3369
.L3373:
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r1, .L3400+20
	blx	r3
	ldr	r3, [r9, #68]
	ldr	r1, .L3400+24
	mov	r0, #0
	blx	r3
	mov	r0, r8
	bl	HEVC_PrintDPBState
	ldr	r2, [r8, #176]
	ldr	r0, [r8, #2492]
	ldr	r3, [fp, #-52]
	sub	r2, r2, #2
	ldr	r1, [fp, #-48]
	rsb	r2, r0, r2
	ldr	ip, .L3400
	add	r0, r3, r1
	cmp	r0, r2
	bge	.L3395
	str	r1, [sp]
	mov	r0, #0
	ldr	r4, [ip, #68]
	ldr	r2, .L3400+28
	ldr	r1, .L3400+32
	blx	r4
	mov	r0, r8
	mov	r1, #1
	bl	HEVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3398:
	add	r1, r8, #50944
	ldr	r0, [r8, #244]
	add	r1, r1, #56
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	b	.L3391
.L3399:
	ldr	r4, .L3400
	mov	r0, #0
	ldr	r1, .L3400+36
	ldr	r3, [r4, #68]
	blx	r3
	mov	r0, r8
	bl	HEVC_PrintDPBState
	mov	r0, r8
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r8
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3367
	ldr	r3, [r4, #68]
	mov	r0, #0
	ldr	r1, .L3400+40
	blx	r3
	mov	r0, r8
	bl	HEVC_ClearDPB
	mov	r0, #0
	b	.L3391
.L3397:
	ldr	ip, .L3400
	movw	r3, #11077
	ldr	r2, .L3400+28
	mov	r0, #1
	ldr	r1, .L3400+44
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r8
	b	.L3391
.L3367:
	ldr	r4, [r4, #68]
	mov	r0, #0
	ldr	r3, [r8, #2488]
	ldr	r2, [r8, #2492]
	ldr	r1, .L3400+48
	blx	r4
	b	.L3395
.L3401:
	.align	2
.L3400:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC310
	.word	.LC313
	.word	.LC314
	.word	.LC8
	.word	.LC311
	.word	.LC312
	.word	.LANCHOR0+1724
	.word	.LC315
	.word	.LC307
	.word	.LC308
	.word	.LC35
	.word	.LC309
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageBuffer, .-HEVCDEC_GetImageBuffer
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r7, r1
	mov	r6, r2
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	r4, r0
	cmp	r3, #0
	bne	.L3426
	ldr	r8, .L3431
	add	r0, r0, #43520
	str	r3, [r2]
	mov	r1, r3
	str	r3, [r7]
	movw	r2, #3732
	ldr	r3, [r8, #48]
	add	r0, r0, #16
	blx	r3
	ldr	r3, [r4, #2316]
	add	r5, r4, #40960
	mov	r1, #1
	mov	r0, r4
	ldr	r2, [r3, #16]
	str	r2, [r5, #2648]
	ldr	r3, [r3, #32]
	str	r3, [r5, #2644]
	bl	HEVC_DecSliceSegmentHeader
	cmp	r0, #0
	bne	.L3427
	add	r2, r4, #45056
	movw	r1, #2024
	add	r0, r4, #24576
	movw	lr, #15788
	ldr	r2, [r2, #68]
	sub	r2, r2, #1
	clz	r2, r2
	mov	r2, r2, lsr #5
	str	r2, [r7]
	ldr	r2, [r5, #2652]
	ldr	r5, [r4, #2304]
	ldr	ip, [r0, #2604]
	ldr	r3, [r4, #2300]
	mla	r1, r1, r2, r5
	ldr	r9, [ip, #72]
	ldr	r2, [ip, #236]
	ldr	r8, [ip, #76]
	ldr	r5, [r4, #2308]
	ldr	ip, [r1, #32]
	ldr	r7, [r5, #868]
	mla	r3, lr, ip, r3
	ldr	r1, [r3, #236]
	ldr	lr, [r3, #72]
	subs	r1, r1, r2
	ldr	ip, [r3, #76]
	movne	r1, #1
	cmp	r7, #1
	beq	.L3428
.L3406:
	cmp	lr, r9
	moveq	r2, r1
	orrne	r2, r1, #1
	cmp	ip, r8
	moveq	r3, r2
	orrne	r3, r2, #1
	cmp	r3, #0
	beq	.L3429
.L3408:
	mov	r3, #1
	str	r3, [r6]
.L3409:
	ldr	r3, [r4, #220]
	cmp	r3, #0
	beq	.L3425
	ldr	r3, .L3431+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3425
	mov	r3, #0
	ldr	r0, [r4, #244]
	mov	r2, r3
	mov	r1, #120
	blx	r5
.L3425:
	mov	r0, #0
.L3404:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3427:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L3431+8
	blx	r3
	ldr	r3, .L3431+4
	ldr	r5, [r3]
	cmp	r5, #0
	mvneq	r0, #0
	beq	.L3404
	sub	r2, fp, #36
	ldr	r0, [r4, #244]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	r5
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3428:
	ldr	r2, [r3, #108]
	ldr	r3, [r3, #100]
	cmp	r2, r3
	movcc	r2, r3
	str	r2, [r5, #912]
	ldr	r2, [r0, #2604]
	ldr	r0, [r4, #2308]
	ldr	r3, [r2, #108]
	ldr	r2, [r2, #100]
	ldr	r5, [r0, #912]
	cmp	r3, r2
	movcc	r3, r2
	cmp	r3, #8
	movls	r2, #0
	movhi	r2, #1
	cmp	r5, #8
	movne	r2, #0
	cmp	r2, #0
	beq	.L3430
.L3407:
	cmp	lr, r9
	moveq	r2, r1
	orrne	r2, r1, #1
	mov	r1, #1
	cmp	ip, r8
	moveq	r3, r2
	orrne	r3, r2, #1
	str	r1, [r0, #916]
	cmp	r3, #0
	str	r1, [r6]
	bne	.L3408
	b	.L3409
.L3429:
	ldr	r3, [r6]
	cmp	r3, #1
	bne	.L3425
	b	.L3409
.L3430:
	sub	r3, r3, #8
	cmp	r5, #8
	clz	r3, r3
	mov	r3, r3, lsr #5
	movle	r3, #0
	cmp	r3, #0
	beq	.L3406
	b	.L3407
.L3426:
	ldr	ip, .L3431
	movw	r3, #11488
	ldr	r2, .L3431+12
	mov	r0, #1
	ldr	r1, .L3431+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L3404
.L3432:
	.align	2
.L3431:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC316
	.word	.LANCHOR0+1748
	.word	.LC35
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
	subs	r4, r0, #0
	beq	.L3438
	ldr	r0, [r4, #208]
	cmp	r0, #0
	bne	.L3436
	add	r3, r4, #40960
	ldrb	r3, [r3, #2017]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3439
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3436:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3439:
	ldr	r3, .L3440
	ldr	r2, .L3440+4
	ldr	r1, .L3440+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3438:
	ldr	ip, .L3440
	movw	r3, #11558
	ldr	r2, .L3440+4
	mov	r0, #1
	ldr	r1, .L3440+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3441:
	.align	2
.L3440:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1776
	.word	.LC317
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_HaveSliceToDec, .-HEVC_HaveSliceToDec
	.align	2
	.global	HEVCDEC_DecodePacket
	.type	HEVCDEC_DecodePacket, %function
HEVCDEC_DecodePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	subs	r4, r0, #0
	mov	ip, #0
	str	ip, [fp, #-48]
	str	ip, [fp, #-44]
	str	ip, [fp, #-40]
	beq	.L3480
	cmp	r1, #0
	beq	.L3481
	ldr	r2, [r4, #2308]
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	cmp	r0, #1
	mov	r3, r3, asl #16
	and	r3, r3, #458752
	str	r3, [r4, #232]
	ldr	r3, [r2]
	str	r3, [r4, #236]
	ldr	r3, [r2, #4]
	str	r3, [r4, #240]
	beq	.L3446
	ldr	r3, [r2, #868]
	cmp	r3, #1
	addne	r6, r4, #69632
	beq	.L3482
.L3447:
	mov	r0, r4
	bl	HEVC_ReceivePacket
	ldr	r3, [r4, #2316]
	str	r3, [r6, #2820]
	mov	r5, r0
.L3448:
	cmp	r5, #0
	mov	r3, #0
	strb	r3, [r4, #4]
	beq	.L3449
.L3461:
	mov	r0, #0
.L3444:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3482:
	ldr	r3, [r2, #908]
	add	r6, r4, #69632
	cmp	r3, #1
	bne	.L3447
	ldr	r3, [r6, #2816]
	cmp	r3, #1
	bne	.L3447
	ldr	r3, [r6, #2820]
	mov	r0, ip
	str	r3, [r4, #2316]
	str	ip, [r6, #2816]
	strb	ip, [r4, #4]
	b	.L3444
.L3449:
	ldr	r3, [r4, #2316]
	str	r5, [r3, #4]
	ldr	r3, [r4, #2316]
	ldr	r0, [r4, #2292]
	ldr	r1, [r3, #44]
	ldr	r2, [r3, #48]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2292]
	bl	BsSkip
	mov	r1, #1
	ldr	r0, [r4, #2292]
	ldr	r6, [r4, #2316]
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #24]
	ldr	r0, [r4, #2292]
	ldr	r6, [r4, #2316]
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #16]
	ldr	r0, [r4, #2292]
	ldr	r6, [r4, #2316]
	bl	BsGet
	mov	r1, #3
	str	r0, [r6, #28]
	ldr	r0, [r4, #2292]
	ldr	r6, [r4, #2316]
	bl	BsGet
	sub	r0, r0, #1
	str	r0, [r6, #32]
	ldr	r6, [r4, #2316]
	ldr	r0, [r6, #16]
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	mov	r7, r0
	beq	.L3483
.L3450:
	mov	r3, #0
	str	r3, [r6, #4]
	ldr	r3, [r4, #2316]
	add	r0, r4, #2448
	add	r0, r0, #8
	ldr	r1, [r3, #44]
	ldr	r2, [r3, #48]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2292]
	bl	BsSkip
	mov	r1, #1
	ldr	r0, [r4, #2292]
	ldr	r5, [r4, #2316]
	bl	BsGet
	mov	r1, #6
	str	r0, [r5, #24]
	ldr	r0, [r4, #2292]
	ldr	r5, [r4, #2316]
	bl	BsGet
	mov	r1, #6
	str	r0, [r5, #16]
	ldr	r0, [r4, #2292]
	ldr	r5, [r4, #2316]
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #28]
	ldr	r0, [r4, #2292]
	ldr	r5, [r4, #2316]
	bl	BsGet
	sub	r0, r0, #1
	str	r0, [r5, #32]
.L3460:
	mov	r0, r4
	bl	HEVC_DecOneNal
	cmn	r0, #2
	beq	.L3444
	cmp	r0, #0
	beq	.L3461
	ldr	r3, .L3488
	mov	r0, #22
	ldr	r1, .L3488+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3444
.L3446:
	ldr	r3, [r4, #2316]
	cmp	r3, #0
	movne	r5, #0
	mvneq	r5, #0
	cmp	r3, #0
	bne	.L3448
	ldr	r3, .L3488
	mov	r0, ip
	ldr	r1, .L3488+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	b	.L3444
.L3483:
	sub	r2, fp, #32
	sub	r1, fp, #36
	mov	r0, r4
	bl	HEVC_InquireSliceProperty
	cmp	r0, #0
	bne	.L3451
	ldr	r6, [fp, #-36]
	cmp	r6, #1
	beq	.L3484
.L3452:
	ldr	r5, [fp, #-32]
	cmp	r5, #1
	beq	.L3485
.L3453:
	ldr	r6, [r4, #2316]
	ldr	r0, [r6, #16]
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	beq	.L3460
	b	.L3450
.L3451:
	ldr	r3, .L3488
	mov	r0, r7
	ldr	r1, .L3488+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	bl	HEVC_ClearCurrNal
	ldr	r3, .L3488+16
	ldr	r6, [r3]
	cmp	r6, #0
	mvneq	r0, #0
	beq	.L3444
	ldr	r0, [r4, #244]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r6
	mvn	r0, #0
	b	.L3444
.L3485:
	add	r3, r4, #40960
	ldr	r3, [r3, #2648]
	sub	r3, r3, #16
	cmp	r3, #4
	bls	.L3486
.L3455:
	ldrb	r5, [r4, #1]	@ zero_extendqisi2
	cmp	r5, #1
	beq	.L3487
.L3458:
	ldr	r0, [r4, #244]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L3453
	sub	r3, fp, #40
	sub	r2, fp, #44
	sub	r1, fp, #48
	ldr	r0, [r4, #244]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #776]
	cmp	r3, #1
	bne	.L3453
	ldr	r2, [fp, #-44]
	ldr	r1, [fp, #-40]
	add	r2, r2, r1
	cmp	r2, #0
	strgtb	r3, [r4, #4]
	mvngt	r0, #1
	ble	.L3453
	b	.L3444
.L3484:
	mov	r0, r4
	bl	HEVC_HaveSliceToDec
	cmp	r0, #0
	bne	.L3452
	ldr	r3, [r4, #2316]
	add	r0, r4, #2448
	mov	r2, #21
	add	r0, r0, #8
	ldr	r1, .L3488+20
	str	r5, [r3, #4]
	bl	BsInit
	mov	r1, #40
	ldr	r0, [r4, #2292]
	bl	BsSkip
	ldr	r3, [r4, #2316]
	mov	r2, #48
	mov	r0, r4
	str	r2, [r3, #16]
	strb	r6, [r4, #5]
	bl	HEVC_DecOneNal
	ldr	r3, [r4, #256]
	strb	r6, [r4, #4]
	mvn	r0, #1
	add	r3, r3, #1
	str	r3, [r4, #256]
	b	.L3444
.L3486:
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	beq	.L3455
	ldr	r3, .L3488
	mov	r0, r5
	ldr	r2, .L3488+24
	ldr	r1, .L3488+28
	ldr	r3, [r3, #68]
	blx	r3
	b	.L3455
.L3481:
	ldr	r3, .L3488
	mov	r0, r1
	ldr	r1, .L3488+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3444
.L3480:
	ldr	ip, .L3488
	movw	r3, #1026
	ldr	r2, .L3488+24
	mov	r0, #1
	ldr	r1, .L3488+36
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L3444
.L3487:
	mov	r0, r4
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L3458
	ldr	r3, .L3488
	mov	r0, r5
	ldr	r2, .L3488+24
	ldr	r1, .L3488+40
	ldr	r3, [r3, #68]
	blx	r3
	b	.L3458
.L3489:
	.align	2
.L3488:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC321
	.word	.LC319
	.word	.LC320
	.word	g_event_report
	.word	.LANCHOR0+1564
	.word	.LANCHOR0+1796
	.word	.LC258
	.word	.LC318
	.word	.LC35
	.word	.LC259
	UNWIND(.fnend)
	.size	HEVCDEC_DecodePacket, .-HEVCDEC_DecodePacket
	.align	2
	.global	HEVCDEC_GetRemainImg
	.type	HEVCDEC_GetRemainImg, %function
HEVCDEC_GetRemainImg:
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
	subs	r4, r0, #0
	beq	.L3491
	ldr	r3, [r4, #2492]
	cmp	r3, #0
	beq	.L3503
	add	r7, r4, #50944
	ldr	r10, .L3515
	add	r7, r7, #56
	mvn	r6, #0
	b	.L3502
.L3494:
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	ldr	r1, [fp, #-52]
	mov	r0, r4
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r3, [r4, #2492]
	cmp	r3, #0
	beq	.L3511
.L3502:
	sub	r1, fp, #48
	sub	r2, fp, #52
	mov	r0, r4
	bl	HEVC_GetMinPOC
	ldr	r1, [fp, #-52]
	add	r3, r1, #628
	ldr	r5, [r4, r3, asl #2]
	cmp	r5, #0
	beq	.L3494
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3494
	mov	r1, r5
	mov	r0, r4
	mov	r8, #1
	strb	r8, [r5, #2]
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r6, r0, #0
	beq	.L3512
.L3501:
	ldr	r1, [fp, #-52]
	b	.L3494
.L3511:
	cmp	r6, #0
	bne	.L3503
	mov	r0, r6
.L3493:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3512:
	mov	r2, r8
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_SetDisplay
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	bl	FSP_GetFsImagePtr
	subs	r9, r0, #0
	beq	.L3513
	ldr	r3, [r4, #2492]
	mov	r2, r4
	mov	r1, #17
	cmp	r3, #1
	streq	r3, [r9, #244]
	mov	r3, r7
	ldr	r0, [r4, #244]
	str	r9, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r8, r0
	beq	.L3498
	mov	r3, r0
	ldr	r2, .L3515+4
	ldr	r1, .L3515+8
	mov	r0, #0
	ldr	ip, [r10, #68]
	mvn	r8, #0
	blx	ip
	ldr	r1, [r5, #32]
	ldr	r0, [r4, #244]
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r1, #1
	mov	r0, r4
	bl	HEVC_ClearAll
.L3498:
	ldr	r3, [r4, #2308]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r9, #84]
	bcs	.L3514
.L3500:
	ldr	r3, [r4, #2492]
	ldr	r2, [r4, #268]
	cmp	r3, #1
	ldr	r3, [r4, #260]
	add	r2, r2, #1
	str	r2, [r4, #268]
	add	r3, r3, #1
	str	r3, [r4, #260]
	beq	.L3501
	mov	r6, r8
	ldr	r1, [fp, #-52]
	b	.L3494
.L3503:
	add	r0, r4, #50944
	add	r0, r0, #56
	bl	GetVoLastImageID
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3514:
	add	r1, r9, #84
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.isra.11.part.12
	b	.L3500
.L3513:
	ldr	r1, .L3515+12
	mvn	r6, #0
	ldr	r3, [r10, #68]
	ldr	r2, .L3515+4
	blx	r3
	ldr	r1, [fp, #-52]
	b	.L3494
.L3491:
	ldr	ip, .L3515
	movw	r3, #11587
	ldr	r2, .L3515+4
	mov	r0, #1
	ldr	r1, .L3515+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L3493
.L3516:
	.align	2
.L3515:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1820
	.word	.LC323
	.word	.LC322
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.align	2
	.global	HEVCDEC_GetImageWidth
	.type	HEVCDEC_GetImageWidth, %function
HEVCDEC_GetImageWidth:
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
	beq	.L3520
	add	r4, r4, #24576
	ldr	r3, [r4, #2604]
	ldr	r2, [r3, #152]
	ldr	r0, [r3, #72]
	rsb	r3, r2, #0
	add	r0, r2, r0
	sub	r0, r0, #1
	and	r0, r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3520:
	ldr	ip, .L3521
	movw	r3, #11662
	ldr	r2, .L3521+4
	mov	r0, #1
	ldr	r1, .L3521+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3522:
	.align	2
.L3521:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1844
	.word	.LC35
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	beq	.L3526
	add	r4, r4, #24576
	ldr	r3, [r4, #2604]
	ldr	r2, [r3, #152]
	ldr	r0, [r3, #76]
	rsb	r3, r2, #0
	add	r0, r2, r0
	sub	r0, r0, #1
	and	r0, r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3526:
	ldr	ip, .L3527
	movw	r3, #11670
	ldr	r2, .L3527+4
	mov	r0, #1
	ldr	r1, .L3527+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3528:
	.align	2
.L3527:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1868
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageHeight, .-HEVCDEC_GetImageHeight
	.global	g_IsDeced
	.global	g_TsToRsMap
	.global	g_hrd_parameters
	.global	s_TmpParam
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13925, %object
	.size	__func__.13925, 14
__func__.13925:
	.ascii	"HEVC_IsNewPic\000"
	.space	2
	.type	__func__.13815, %object
	.size	__func__.13815, 21
__func__.13815:
	.ascii	"HEVC_IncreaseDPBSize\000"
	.space	3
	.type	__func__.14121, %object
	.size	__func__.14121, 17
__func__.14121:
	.ascii	"HEVC_CalcTileMap\000"
	.space	3
	.type	__func__.14140, %object
	.size	__func__.14140, 17
__func__.14140:
	.ascii	"HEVC_WritePicMsg\000"
	.space	3
	.type	__func__.13398, %object
	.size	__func__.13398, 18
__func__.13398:
	.ascii	"HEVC_CalcTileInfo\000"
	.space	2
	.type	__func__.14186, %object
	.size	__func__.14186, 19
__func__.14186:
	.ascii	"HEVC_WriteSliceMsg\000"
	.space	1
	.type	__func__.14370, %object
	.size	__func__.14370, 13
__func__.14370:
	.ascii	"HEVC_DecList\000"
	.space	3
	.type	__func__.14315, %object
	.size	__func__.14315, 16
__func__.14315:
	.ascii	"HEVC_RepairList\000"
	.type	__func__.14446, %object
	.size	__func__.14446, 20
__func__.14446:
	.ascii	"HEVC_RemoveApcStore\000"
	.type	__func__.14454, %object
	.size	__func__.14454, 26
__func__.14454:
	.ascii	"HEVC_RemoveUnusedApcStore\000"
	.space	2
	.type	__func__.14478, %object
	.size	__func__.14478, 30
__func__.14478:
	.ascii	"HEVC_ApplyReferencePictureSet\000"
	.space	2
	.type	__func__.14539, %object
	.size	__func__.14539, 19
__func__.14539:
	.ascii	"HEVC_UpdateReflist\000"
	.space	1
	.type	__func__.14571, %object
	.size	__func__.14571, 21
__func__.14571:
	.ascii	"HEVC_UpdateLTReflist\000"
	.space	3
	.type	__func__.14634, %object
	.size	__func__.14634, 21
__func__.14634:
	.ascii	"HEVC_DECRecycleImage\000"
	.space	3
	.type	__func__.14652, %object
	.size	__func__.14652, 21
__func__.14652:
	.ascii	"HEVC_CheckFrameStore\000"
	.space	3
	.type	__func__.14661, %object
	.size	__func__.14661, 18
__func__.14661:
	.ascii	"HEVC_GetImagePara\000"
	.space	2
	.type	__func__.14502, %object
	.size	__func__.14502, 19
__func__.14502:
	.ascii	"HEVC_OutputCurrPic\000"
	.space	1
	.type	__func__.14671, %object
	.size	__func__.14671, 21
__func__.14671:
	.ascii	"HEVC_AllocFrameStore\000"
	.space	3
	.type	__func__.14680, %object
	.size	__func__.14680, 27
__func__.14680:
	.ascii	"HEVC_GetBackPicFromVOQueue\000"
	.space	1
	.type	__func__.14708, %object
	.size	__func__.14708, 28
__func__.14708:
	.ascii	"HEVC_RemoveFrameStoreOutDPB\000"
	.type	__func__.14462, %object
	.size	__func__.14462, 22
__func__.14462:
	.ascii	"HEVC_RemoveDummyFrame\000"
	.space	2
	.type	__func__.14698, %object
	.size	__func__.14698, 28
__func__.14698:
	.ascii	"HEVC_RemoveUnUsedFrameStore\000"
	.type	__func__.14727, %object
	.size	__func__.14727, 20
__func__.14727:
	.ascii	"HEVC_CalcStreamBits\000"
	.type	__func__.14743, %object
	.size	__func__.14743, 20
__func__.14743:
	.ascii	"HEVC_VpsSpsPpsCheck\000"
	.type	__func__.14749, %object
	.size	__func__.14749, 23
__func__.14749:
	.ascii	"HEVC_ReadByteAlignment\000"
	.space	1
	.type	__func__.14760, %object
	.size	__func__.14760, 12
__func__.14760:
	.ascii	"HEVC_DecPTL\000"
	.type	quant8_inter_default, %object
	.size	quant8_inter_default, 64
quant8_inter_default:
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
	.type	__func__.14840, %object
	.size	__func__.14840, 27
__func__.14840:
	.ascii	"HEVC_SetDefaultScalingList\000"
	.space	1
	.type	quant_ts_default, %object
	.size	quant_ts_default, 16
quant_ts_default:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	__func__.14822, %object
	.size	__func__.14822, 20
__func__.14822:
	.ascii	"HEVC_SetScalingList\000"
	.type	__func__.14791, %object
	.size	__func__.14791, 24
__func__.14791:
	.ascii	"HEVC_DecScalingListData\000"
	.type	__func__.14868, %object
	.size	__func__.14868, 24
__func__.14868:
	.ascii	"HEVC_DecPredWeightTable\000"
	.type	__func__.13990, %object
	.size	__func__.13990, 27
__func__.13990:
	.ascii	"HEVC_DecSliceSegmentHeader\000"
	.space	1
.LC0:
	.word	1
	.word	2
	.word	2
	.word	1
.LC1:
	.word	1
	.word	2
	.word	1
	.word	1
	.type	__func__.14907, %object
	.size	__func__.14907, 17
__func__.14907:
	.ascii	"HEVC_DecVuiParam\000"
	.space	3
	.type	__func__.14931, %object
	.size	__func__.14931, 18
__func__.14931:
	.ascii	"HEVC_MoreRbspData\000"
	.space	2
	.type	__func__.13443, %object
	.size	__func__.13443, 12
__func__.13443:
	.ascii	"HEVC_DecVPS\000"
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
	.type	SarTable.13275, %object
	.size	SarTable.13275, 136
SarTable.13275:
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
	.type	__func__.13545, %object
	.size	__func__.13545, 12
__func__.13545:
	.ascii	"HEVC_DecSPS\000"
	.type	__func__.13586, %object
	.size	__func__.13586, 12
__func__.13586:
	.ascii	"HEVC_DecPPS\000"
	.type	__func__.13772, %object
	.size	__func__.13772, 16
__func__.13772:
	.ascii	"HEVC_SeiMessage\000"
	.type	__func__.14935, %object
	.size	__func__.14935, 20
__func__.14935:
	.ascii	"HEVC_More_Rbsp_Data\000"
	.type	__func__.13786, %object
	.size	__func__.13786, 12
__func__.13786:
	.ascii	"HEVC_DecSEI\000"
	.type	__func__.14950, %object
	.size	__func__.14950, 16
__func__.14950:
	.ascii	"HEVC_ReleaseNAL\000"
	.type	__func__.15004, %object
	.size	__func__.15004, 18
__func__.15004:
	.ascii	"HEVC_ClearCurrNal\000"
	.space	2
	.type	__func__.15013, %object
	.size	__func__.15013, 20
__func__.15013:
	.ascii	"HEVC_ClearCurrSlice\000"
	.type	__func__.15018, %object
	.size	__func__.15018, 19
__func__.15018:
	.ascii	"HEVC_ClearAllSlice\000"
	.space	1
	.type	__func__.14398, %object
	.size	__func__.14398, 13
__func__.14398:
	.ascii	"HEVC_InitDPB\000"
	.space	3
	.type	__func__.15026, %object
	.size	__func__.15026, 17
__func__.15026:
	.ascii	"HEVC_ClearAllNal\000"
	.space	3
	.type	__func__.14996, %object
	.size	__func__.14996, 13
__func__.14996:
	.ascii	"HEVCDEC_Init\000"
	.space	3
	.type	__func__.15033, %object
	.size	__func__.15033, 18
__func__.15033:
	.ascii	"HEVC_ClearCurrPic\000"
	.space	2
	.type	__func__.14989, %object
	.size	__func__.14989, 14
__func__.14989:
	.ascii	"HEVC_ClearAll\000"
	.space	2
	.type	__func__.14288, %object
	.size	__func__.14288, 13
__func__.14288:
	.ascii	"HEVC_InitPic\000"
	.space	3
	.type	__func__.14644, %object
	.size	__func__.14644, 19
__func__.14644:
	.ascii	"HEVC_OutputFrmToVO\000"
	.space	1
	.type	__func__.14603, %object
	.size	__func__.14603, 22
__func__.14603:
	.ascii	"HEVC_OutputFrmFromDPB\000"
	.space	2
	.type	__func__.14614, %object
	.size	__func__.14614, 27
__func__.14614:
	.ascii	"HEVC_FlushOutputFrmFromDPB\000"
	.space	1
	.type	__func__.14963, %object
	.size	__func__.14963, 19
__func__.14963:
	.ascii	"HEVC_ReceivePacket\000"
	.space	1
	.type	__func__.15055, %object
	.size	__func__.15055, 25
__func__.15055:
	.ascii	"HEVC_UnMarkFrameStoreRef\000"
	.space	3
	.type	__func__.15041, %object
	.size	__func__.15041, 14
__func__.15041:
	.ascii	"HEVC_FlushDPB\000"
	.space	2
	.type	__func__.15009, %object
	.size	__func__.15009, 14
__func__.15009:
	.ascii	"HEVC_ClearDPB\000"
	.space	2
	.type	__func__.14248, %object
	.size	__func__.14248, 12
__func__.14248:
	.ascii	"HEVC_DecVDM\000"
	.type	__func__.14596, %object
	.size	__func__.14596, 20
__func__.14596:
	.ascii	"HEVC_InsertFrmInDPB\000"
	.type	__func__.13915, %object
	.size	__func__.13915, 14
__func__.13915:
	.ascii	"HEVC_DecSlice\000"
	.space	2
	.type	__func__.13834, %object
	.size	__func__.13834, 23
__func__.13834:
	.ascii	"HEVC_RecoverDPBProcess\000"
	.space	1
	.type	__func__.13807, %object
	.size	__func__.13807, 27
__func__.13807:
	.ascii	"HEVC_GetUnRefPicWithMinPoc\000"
	.space	1
	.type	__func__.13829, %object
	.size	__func__.13829, 30
__func__.13829:
	.ascii	"HEVC_OutputUnRefPicWithMinPoc\000"
	.space	2
	.type	g_HEVCNalTypeEOPIC, %object
	.size	g_HEVCNalTypeEOPIC, 21
g_HEVCNalTypeEOPIC:
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
	.type	__func__.14973, %object
	.size	__func__.14973, 20
__func__.14973:
	.ascii	"HEVCDEC_VDMPostProc\000"
	.type	__func__.14528, %object
	.size	__func__.14528, 19
__func__.14528:
	.ascii	"HEVC_StorePicInDPB\000"
	.space	1
	.type	__func__.14512, %object
	.size	__func__.14512, 22
__func__.14512:
	.ascii	"HEVC_SimpleDPBProcess\000"
	.space	2
	.type	__func__.14517, %object
	.size	__func__.14517, 21
__func__.14517:
	.ascii	"HEVC_DecOrderProcess\000"
	.space	3
	.type	__func__.14507, %object
	.size	__func__.14507, 23
__func__.14507:
	.ascii	"HEVC_FirstFrameFastOut\000"
	.space	1
	.type	__func__.14522, %object
	.size	__func__.14522, 22
__func__.14522:
	.ascii	"HEVC_DispOrderProcess\000"
	.space	2
	.type	__func__.14981, %object
	.size	__func__.14981, 23
__func__.14981:
	.ascii	"HEVCDEC_GetImageBuffer\000"
	.space	1
	.type	__func__.15070, %object
	.size	__func__.15070, 26
__func__.15070:
	.ascii	"HEVC_InquireSliceProperty\000"
	.space	2
	.type	__func__.15075, %object
	.size	__func__.15075, 20
__func__.15075:
	.ascii	"HEVC_HaveSliceToDec\000"
	.type	__func__.13383, %object
	.size	__func__.13383, 21
__func__.13383:
	.ascii	"HEVCDEC_DecodePacket\000"
	.space	3
	.type	__func__.15084, %object
	.size	__func__.15084, 21
__func__.15084:
	.ascii	"HEVCDEC_GetRemainImg\000"
	.space	3
	.type	__func__.15092, %object
	.size	__func__.15092, 22
__func__.15092:
	.ascii	"HEVCDEC_GetImageWidth\000"
	.space	2
	.type	__func__.15097, %object
	.size	__func__.15097, 23
__func__.15097:
	.ascii	"HEVCDEC_GetImageHeight\000"
	.data
	.align	2
.LANCHOR3 = . + 0
	.type	quant8_intra_default, %object
	.size	quant8_intra_default, 64
quant8_intra_default:
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
	.type	g_quantTSDefault4x4, %object
	.size	g_quantTSDefault4x4, 16
g_quantTSDefault4x4:
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
	.type	g_quantInterDefault8x8, %object
	.size	g_quantInterDefault8x8, 64
g_quantInterDefault8x8:
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
	.type	g_quantIntraDefault8x8, %object
	.size	g_quantIntraDefault8x8, 64
g_quantIntraDefault8x8:
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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC2:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, n" )
	ASCII(.ascii	"al_unit_type = %d, should skip this frame\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d," )
	ASCII(.ascii	" nal_unit_type = %d, should skip this frame\012\000" )
.LC4:
	ASCII(.ascii	"%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocC" )
	ASCII(.ascii	"RA = %d, nal_unit_type = %d, should skip this frame" )
	ASCII(.ascii	"\012\000" )
.LC5:
	ASCII(.ascii	"%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), err" )
	ASCII(.ascii	"or resilence.\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	"--------------- PrintDPBState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"DPB: size:%d, used_size:%d, negative:%d, positive:%" )
	ASCII(.ascii	"d, longterm:%d\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"fs[%d]:%p non_existing:%d state:%d is_ref:%d displa" )
	ASCII(.ascii	"yed:%d poc:%d long_term:%d LogicFs:%p, fsp_ref:%d f" )
	ASCII(.ascii	"sp_disp:%d logic_id:%d img_id:%d\012\000" )
.LC10:
	ASCII(.ascii	"--------------- PrintDPBState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC11:
	ASCII(.ascii	"fs[%d]\011\000" )
.LC12:
	ASCII(.ascii	"LogicFs:%p\011\000" )
.LC13:
	ASCII(.ascii	"LogicTick:%d\011\000" )
	.space	2
.LC14:
	ASCII(.ascii	"IsRef:%d\011\000" )
	.space	2
.LC15:
	ASCII(.ascii	"s32DispState:%d\011\000" )
	.space	3
.LC16:
	ASCII(.ascii	"LogicFs:Null\011\000" )
	.space	2
.LC17:
	ASCII(.ascii	"DecFs:%p\011\000" )
	.space	2
.LC18:
	ASCII(.ascii	"DecTick:%d\011\000" )
.LC19:
	ASCII(.ascii	"DecFs:Null\011\000" )
.LC20:
	ASCII(.ascii	"DispFs:%p\011\000" )
	.space	1
.LC21:
	ASCII(.ascii	"DispTick:%d\011\000" )
	.space	3
.LC22:
	ASCII(.ascii	"DispFs:Null\011\000" )
	.space	3
.LC23:
	ASCII(.ascii	"HEVC_Sei_User_Data_Unregistered payloadSize < 16\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC24:
	ASCII(.ascii	"HEVC_ue_v ERROR: LeadingZeros (%d) >= 32, return 0x" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"delta_idx(%d) > idx(%d).\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"rIdx(%d) > (idx-1)(%d) or < 0).\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"pTempRPset->num_of_pics(%d) out of range(0,15).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC28:
	ASCII(.ascii	"num_of_pics out of range(0,15).\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"pTempRPset->num_negative_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"pTempRPset->num_positive_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"pShortTermRpset->num_of_pics(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"%s DPB.size(%d) already reached max(%d).\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"%s increase DPB size to %d\012\000" )
.LC34:
	ASCII(.ascii	"%s no enough fs(total_fs_num=%d) to increase DPB si" )
	ASCII(.ascii	"ze.\012\000" )
.LC35:
	ASCII(.ascii	"[%s %d]assert warning\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	"image_id=%d, pmv_idc=%d\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"%s num_tile_columns(%d) out of range(0, %d].\012\000" )
	.space	2
.LC39:
	ASCII(.ascii	"%s num_tile_rows(%d) out of range(0, %d].\012\000" )
	.space	1
.LC40:
	ASCII(.ascii	"%s 0 idx(%d) out of range(0, 512).\012\000" )
.LC41:
	ASCII(.ascii	"%s 1 idx(%d) out of range(0, 512).\012\000" )
.LC42:
	ASCII(.ascii	"logic frame id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"%s call HEVC_CalcTileInfo failed.\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"ListX ERROR: list0size >= %d\012\000" )
	.space	2
.LC46:
	ASCII(.ascii	"ListX ERROR: list1size >= %d\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"pListX[0][%d] = NULL\012\000" )
	.space	2
.LC48:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL\012\000" )
	.space	1
.LC49:
	ASCII(.ascii	"pListX[1][%d] = NULL\012\000" )
	.space	2
.LC50:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL\012\000" )
	.space	1
.LC51:
	ASCII(.ascii	"NumSlicePara(%d) >= MaxSliceNum(%d)\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"TileWidthInCtb is 0\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"%s unkown slice type(%d).\012\000" )
	.space	1
.LC54:
	ASCII(.ascii	"%s pListX[%d] no available pic to repair.\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"%s: pListX[%d][%d] = NULL, repair it with pos(%d).\012" )
	ASCII(.ascii	"\000" )
.LC56:
	ASCII(.ascii	"HEVC_RepairList error.\012\000" )
.LC57:
	ASCII(.ascii	"release(apc=%d, pmvIdc=%d)\011\000" )
.LC58:
	ASCII(.ascii	"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STA" )
	ASCII(.ascii	"TE_NOT_USED\012\000" )
.LC59:
	ASCII(.ascii	"%s frame logic_fs_id=%d, state=%d\012\000" )
	.space	1
.LC60:
	ASCII(.ascii	"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null," )
	ASCII(.ascii	" logic_fs_id = %d\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"%s frame poc=%d, is already output\012\000" )
.LC62:
	ASCII(.ascii	"%s frame(%p) invalid, state:%d, non_existing:%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC63:
	ASCII(.ascii	"%s: pImg is NULL!\012\000" )
	.space	1
.LC64:
	ASCII(.ascii	"%s, REPORT_IFRAME_ERR\012\000" )
	.space	1
.LC65:
	ASCII(.ascii	"%s: InsertImgToVoQueue failed!\012\000" )
.LC66:
	ASCII(.ascii	"%s: ImgErrorLevel = %d, OutErrThr:%d, discarded!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC67:
	ASCII(.ascii	"FS_ALLOC_ERR, ClearAll\012\000" )
.LC68:
	ASCII(.ascii	"Can not new logic fs! ClearAll\012\000" )
.LC69:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC70:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC71:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC72:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC73:
	ASCII(.ascii	"sps with this seq_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC74:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck video_parameter_set_id out of r" )
	ASCII(.ascii	"ange\012\000" )
	.space	3
.LC75:
	ASCII(.ascii	"vps with this video_parameter_set_id = %d havn't be" )
	ASCII(.ascii	" decoded\012\000" )
	.space	3
.LC76:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code should not be zero.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC77:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code:%d\012\000" )
	.space	3
.LC78:
	ASCII(.ascii	"general_profile_compatibility_flag[][%d]\000" )
	.space	3
.LC79:
	ASCII(.ascii	"reserved_zero_2bits not equal 0.\012\000" )
	.space	2
.LC80:
	ASCII(.ascii	"HEVC_GetScalingListDefaultAddress NULL.\012\000" )
	.space	3
.LC81:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta out of range(0,ma" )
	ASCII(.ascii	"trixId).\012\000" )
	.space	3
.LC82:
	ASCII(.ascii	"HEVC_DecScalingListData pMatrixAddress NULL.\012\000" )
	.space	2
.LC83:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-7,247).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC84:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-128,127)." )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC85:
	ASCII(.ascii	"luma_log2_weight_denom out of range(0,7).\012\000" )
	.space	1
.LC86:
	ASCII(.ascii	"delta_chroma_log2_weight_denom out of range(-7,7).\012" )
	ASCII(.ascii	"\000" )
.LC87:
	ASCII(.ascii	"delta_luma_weight_l0(%d) out of range(-128,127).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC88:
	ASCII(.ascii	"luma_offset_l0(%d) out of range(-128,127).\012\000" )
.LC89:
	ASCII(.ascii	"delta_chroma_weight_l0 out of range(-128,127).\012\000" )
.LC90:
	ASCII(.ascii	"delta_chroma_offset_l0 out of range(-512,511).\012\000" )
.LC91:
	ASCII(.ascii	"delta_luma_weight_l1 out of range(-128,127).\012\000" )
	.space	2
.LC92:
	ASCII(.ascii	"luma_offset_l1 out of range(-128,127).\012\000" )
.LC93:
	ASCII(.ascii	"delta_chroma_weight_l1 out of range(-128,127).\012\000" )
.LC94:
	ASCII(.ascii	"delta_chroma_offset_l1 out of range(-512,511).\012\000" )
.LC95:
	ASCII(.ascii	"%s: pic_parameter_set_id(%d) out of range(0 %d)!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC96:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\012\000" )
.LC97:
	ASCII(.ascii	"max_cu_width(%d)/max_cu_height(%d) = 0\012\000" )
.LC98:
	ASCII(.ascii	"slice_segment_address(%d) out of range(0,%d).\012\000" )
	.space	1
.LC99:
	ASCII(.ascii	"slice_reserved_flag: %d\012\000" )
	.space	3
.LC100:
	ASCII(.ascii	"slice_type(%d) out of range(0,2].\012\000" )
	.space	1
.LC101:
	ASCII(.ascii	"SH HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	2
.LC102:
	ASCII(.ascii	"short_term_ref_pic_set_idx(%d) out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
.LC103:
	ASCII(.ascii	"num_long_term_sps(%d) out of range[0,%d].\012\000" )
	.space	1
.LC104:
	ASCII(.ascii	"SH ERROR: (num_negative_pics(%d) + num_positive_pic" )
	ASCII(.ascii	"s(%d) + num_of_longterm_pics(%d)) > %d\012\000" )
	.space	1
.LC105:
	ASCII(.ascii	"lt_idx_sps[%d] = %d, but out of range[0,%d].\012\000" )
	.space	2
.LC106:
	ASCII(.ascii	"ERROR: pRPS->num_of_pics(%d) > %d.\012\000" )
.LC107:
	ASCII(.ascii	"num_ref_idx_l0_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC108:
	ASCII(.ascii	"num_ref_idx_l1_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC109:
	ASCII(.ascii	"pRPS is null.\012\000" )
	.space	1
.LC110:
	ASCII(.ascii	"pRPS->num_of_pics out(%d) of range(0,%d).\012\000" )
	.space	1
.LC111:
	ASCII(.ascii	"collocated_from_l0_flag=%d, collocated_ref_idx(%d) " )
	ASCII(.ascii	"out of range(0,%d).\012\000" )
.LC112:
	ASCII(.ascii	"SH HEVC_DecPredWeightTable error.\012\000" )
	.space	1
.LC113:
	ASCII(.ascii	"SH max_num_merge_cand(%d) out of range(1,5).\012\000" )
	.space	2
.LC114:
	ASCII(.ascii	"SH slice_qp(%d) out of range [-%d,51].\012\000" )
.LC115:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC116:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out " )
	ASCII(.ascii	"of range[-12,12].\012\000" )
	.space	2
.LC117:
	ASCII(.ascii	"SH slice_cr_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC118:
	ASCII(.ascii	"SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) ou" )
	ASCII(.ascii	"t of range[-12,12].\012\000" )
.LC119:
	ASCII(.ascii	"SH slice_beta_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC120:
	ASCII(.ascii	"SH slice_tc_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC121:
	ASCII(.ascii	"CurrSlice.num_entry_point_offsets(%d) out of range[" )
	ASCII(.ascii	"0,%d].\012\000" )
	.space	1
.LC122:
	ASCII(.ascii	"CurrSlice.offset_len(%d) out of range[1,32].\012\000" )
	.space	2
.LC123:
	ASCII(.ascii	"slice_segment_header_extension_length(%d) out of ra" )
	ASCII(.ascii	"nge [0,256]\012\000" )
.LC124:
	ASCII(.ascii	"bitsLeft(%d) < slice_segment_header_extension_lengt" )
	ASCII(.ascii	"h(%d)\012\000" )
	.space	2
.LC125:
	ASCII(.ascii	"SH HEVC_DecRefPicListsModification error.\012\000" )
	.space	1
.LC126:
	ASCII(.ascii	"cpb_cnt_minus1(%d) out of range(0,31).\012\000" )
.LC127:
	ASCII(.ascii	"VUI pSps->chroma_format_idc out of range(0,3).\012\000" )
.LC128:
	ASCII(.ascii	"VUI HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC129:
	ASCII(.ascii	"VUI min_spatial_segmentation_idc out of range(0,409" )
	ASCII(.ascii	"5).\012\000" )
.LC130:
	ASCII(.ascii	"vps_reserved_three_2bits(%d) not equal 0x3.\012\000" )
	.space	3
.LC131:
	ASCII(.ascii	"vps_max_layers_minus1 out of range(0,63).\012\000" )
	.space	1
.LC132:
	ASCII(.ascii	"vps_max_sub_layers_minus1=%d\012\000" )
	.space	2
.LC133:
	ASCII(.ascii	"vps_reserved_0xffff_16bits not equal 0xffff.\012\000" )
	.space	2
.LC134:
	ASCII(.ascii	"VPS HEVC_DecPTL error.\012\000" )
.LC135:
	ASCII(.ascii	"vps_num_layer_sets_minus1(%d) out of range(0,%d).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC136:
	ASCII(.ascii	"layer_id_included_flag[%d][%d]\000" )
	.space	1
.LC137:
	ASCII(.ascii	"vps_num_hrd_parameters(%d) out of range(0,%d).\012\000" )
.LC138:
	ASCII(.ascii	"VPS HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC139:
	ASCII(.ascii	"pVPS->vps_video_parameter_set_id out of range(0,15)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC140:
	ASCII(.ascii	"VPS[%d] decode error0.\012\000" )
.LC141:
	ASCII(.ascii	"VPS[%d] decode error1.\012\000" )
.LC142:
	ASCII(.ascii	"pSPS->chroma_format_idc out of range(0,3).\012\000" )
.LC143:
	ASCII(.ascii	"pSPS->chroma_format_idc not equal(%d) 1.\012\000" )
	.space	2
.LC144:
	ASCII(.ascii	"pic_width_in_luma_samples out of range(0,8192).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC145:
	ASCII(.ascii	"pic_height_in_luma_samples out of range(0,4096).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC146:
	ASCII(.ascii	"ERROR Unkown level: %d\012\000" )
.LC147:
	ASCII(.ascii	"conf_win_left_offset+conf_win_right_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC148:
	ASCII(.ascii	"conf_win_top_offset+conf_win_bottom_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC149:
	ASCII(.ascii	"bit_depth_luma(%d) out of range(8,14).\012\000" )
.LC150:
	ASCII(.ascii	"bit_depth_luma(%d) not equal 8.\012\000" )
	.space	3
.LC151:
	ASCII(.ascii	"bit_depth_chroma(%d) out of range[8,14].\012\000" )
	.space	2
.LC152:
	ASCII(.ascii	"bit_depth_chroma(%d) not equal 8.\012\000" )
	.space	1
.LC153:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4 out of range[0,12" )
	ASCII(.ascii	"].\012\000" )
	.space	1
.LC154:
	ASCII(.ascii	"log2_min_luma_coding_block_size_minus3 out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC155:
	ASCII(.ascii	"log2_diff_max_min_luma_coding_block_size out of ran" )
	ASCII(.ascii	"ge(0,3).\012\000" )
	.space	3
.LC156:
	ASCII(.ascii	"log2_ctb_sizeY out of range(4,6).\012\000" )
	.space	1
.LC157:
	ASCII(.ascii	"log2_min_transform_block_size_minus2 out of range(0" )
	ASCII(.ascii	",3).\012\000" )
	.space	3
.LC158:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC159:
	ASCII(.ascii	"quadtree_tu_log2_min_size not less than log2_min_cb" )
	ASCII(.ascii	"_sizeY.\012\000" )
.LC160:
	ASCII(.ascii	"quadtree_tu_log2_max_size greater than Min( CtbLog2" )
	ASCII(.ascii	"SizeY, 5 ).\012\000" )
.LC161:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC162:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC163:
	ASCII(.ascii	"SPS HEVC_DecScalingListData error.\012\000" )
.LC164:
	ASCII(.ascii	"SPS sao is off and pic height(%d) is too small.(Log" )
	ASCII(.ascii	"ic Unsupported).\012\000" )
	.space	3
.LC165:
	ASCII(.ascii	"log2_min_pcm_coding_block_size_minus3(%d) out of ra" )
	ASCII(.ascii	"nge[0,2].\012\000" )
	.space	2
.LC166:
	ASCII(.ascii	"log2_diff_max_min_pcm_coding_block_size(%d) out of " )
	ASCII(.ascii	"range[0,2].\012\000" )
.LC167:
	ASCII(.ascii	"pcm_log2_max_size greater than Min( CtbLog2SizeY, 5" )
	ASCII(.ascii	" ).\012\000" )
.LC168:
	ASCII(.ascii	"num_short_term_ref_pic_sets out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC169:
	ASCII(.ascii	"SPS HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	1
.LC170:
	ASCII(.ascii	"num_long_term_ref_pic_sps out of range[0,32].\012\000" )
	.space	1
.LC171:
	ASCII(.ascii	"SPS HEVC_DecVuiParam error.\012\000" )
	.space	3
.LC172:
	ASCII(.ascii	"dar=%d\012\000" )
.LC173:
	ASCII(.ascii	"sps_video_parameter_set_id out of range(0,%d).\012\000" )
.LC174:
	ASCII(.ascii	"sps_max_sub_layers_minus1 out of range(0,%d).\012\000" )
	.space	1
.LC175:
	ASCII(.ascii	"SPS HEVC_DecPTL error.\012\000" )
.LC176:
	ASCII(.ascii	"sps_seq_parameter_set_id out of range(0,%d).\012\000" )
	.space	2
.LC177:
	ASCII(.ascii	"SPS[%d] decode error0.\012\000" )
.LC178:
	ASCII(.ascii	"SPS[%d] decode error.\012\000" )
	.space	1
.LC179:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range[0,15].\012\000" )
	.space	2
.LC180:
	ASCII(.ascii	"SPS(%d) haven't decode.\012\000" )
	.space	3
.LC181:
	ASCII(.ascii	"num_ref_idx_l0_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC182:
	ASCII(.ascii	"num_ref_idx_l1_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC183:
	ASCII(.ascii	"pic_init_qp(%d) out of range[-%d,51].\012\000" )
	.space	1
.LC184:
	ASCII(.ascii	"diff_cu_qp_delta_depth out of range[0,3].\012\000" )
	.space	1
.LC185:
	ASCII(.ascii	"pic_cb_qp_offset out of range[-12,12].\012\000" )
.LC186:
	ASCII(.ascii	"pic_cr_qp_offset out of range[-12,12].\012\000" )
.LC187:
	ASCII(.ascii	"num_tile_columns(%d) out of range(0,%d).\012\000" )
	.space	2
.LC188:
	ASCII(.ascii	"num_tile_rows out(%d) of range(0,%d).\012\000" )
	.space	1
.LC189:
	ASCII(.ascii	"Logic limit(%d), num_tile_columns(%d) exceed.\012\000" )
	.space	1
.LC190:
	ASCII(.ascii	"Logic limit(%d), num_tile_rows(%d) exceed.\012\000" )
.LC191:
	ASCII(.ascii	"column_width[%d](%d) out of range (0 %d)\012\000" )
	.space	2
.LC192:
	ASCII(.ascii	"row_height[%d](%d) out of range (0 %d)\012\000" )
.LC193:
	ASCII(.ascii	"column_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	2
.LC194:
	ASCII(.ascii	"row_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	1
.LC195:
	ASCII(.ascii	"PPS tile width(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC196:
	ASCII(.ascii	"PPS tile height(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
.LC197:
	ASCII(.ascii	"pps_beta_offset_div2(%d) out of range(-6,6).\012\000" )
	.space	2
.LC198:
	ASCII(.ascii	"pps_tc_offset_div2(%d) out of range(-6,6).\012\000" )
.LC199:
	ASCII(.ascii	"PPS HEVC_DecScalingListData error.\012\000" )
.LC200:
	ASCII(.ascii	"log2_parallel_merge_level(%d) out of range(2,log2_c" )
	ASCII(.ascii	"tb_sizeY).\012\000" )
	.space	1
.LC201:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range(0,%d).\012\000" )
	.space	2
.LC202:
	ASCII(.ascii	"PPS[%d] decode error.\012\000" )
	.space	1
.LC203:
	ASCII(.ascii	"Wrong bp_seq_parameter_set_id = %d, should be 0 to " )
	ASCII(.ascii	"15!\012\000" )
.LC204:
	ASCII(.ascii	"HEVC_Sei_Buf_Period cpb_cnt_minus1(%d) out of range" )
	ASCII(.ascii	"(0,31).\012\000" )
.LC205:
	ASCII(.ascii	"pPic->num_decoding_units_minus1 > 255\012\000" )
	.space	1
.LC206:
	ASCII(.ascii	"Unsupport: target_bit_depth(%d) > 8\012\000" )
	.space	3
.LC207:
	ASCII(.ascii	"pTon->num_pivots > 256\012\000" )
.LC208:
	ASCII(.ascii	"frame_packing_arrangement_type(%d) out of range\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC209:
	ASCII(.ascii	"num_entries_in_sop_minus1 out of range(0,1024)\012\000" )
.LC210:
	ASCII(.ascii	"pAct->num_sps_ids_minus1 > 15\012\000" )
	.space	1
.LC211:
	ASCII(.ascii	"nesting_num_ops_minus1 out of range(0,%d)\012\000" )
	.space	1
.LC212:
	ASCII(.ascii	"nesting_num_layers_minus1 out of range(0,63)\012\000" )
	.space	2
.LC213:
	ASCII(.ascii	"SEI HEVC_SeiMessage error.\012\000" )
.LC214:
	ASCII(.ascii	"HEVC_SeiMessage HEVC_Sei_Payload error.\012\000" )
	.space	3
.LC215:
	ASCII(.ascii	"Error, BsLen: 0x%x, TotalPos: 0x%x\012\000" )
.LC216:
	ASCII(.ascii	"SEI BsIsByteAligned error.\012\000" )
.LC217:
	ASCII(.ascii	"SEI rbsp_trailing_bits(%d) not equal 0x80.\012\000" )
.LC218:
	ASCII(.ascii	"firmware/common/syntax/hevc.c\000" )
	.space	2
.LC219:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC220:
	ASCII(.ascii	"%s release streambuff=%p, bitstream_length=%d\012\000" )
	.space	1
.LC221:
	ASCII(.ascii	"hevc partition fs memory fail!\012\000" )
.LC222:
	ASCII(.ascii	"ERROR: HEVC FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC223:
	ASCII(.ascii	"%s arrange mem failed.\012\000" )
.LC224:
	ASCII(.ascii	"Init dec para\012\000" )
	.space	1
.LC225:
	ASCII(.ascii	"%s: Get context addr failed!\012\000" )
	.space	2
.LC226:
	ASCII(.ascii	"%s: VCTRL_GetChanIDByCtx() return -1!\012\000" )
	.space	1
.LC227:
	ASCII(.ascii	"BitDepthChange ReRange FS Luma(%d-->%d),Chroma(%d -" )
	ASCII(.ascii	"->%d)\012\000" )
	.space	2
.LC228:
	ASCII(.ascii	"HEVC_InitDPB error, return %d\012\000" )
	.space	1
.LC229:
	ASCII(.ascii	"HEVC_AllocFrameStore error\012\000" )
.LC230:
	ASCII(.ascii	"%s: pstLogicFsImage is NULL!\012\000" )
	.space	2
.LC231:
	ASCII(.ascii	"HEVC InsertVO Failed return %d, ClearAll\012\000" )
	.space	2
.LC232:
	ASCII(.ascii	"HEVC.c line %d: frame para err(ret=%d), recycle ima" )
	ASCII(.ascii	"ge self\012\000" )
.LC233:
	ASCII(.ascii	"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\012\000" )
.LC234:
	ASCII(.ascii	"%s: HEVC_OutputFrmToVO err!\012\000" )
	.space	3
.LC235:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC236:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC237:
	ASCII(.ascii	"nal_release_err\012\000" )
	.space	3
.LC238:
	ASCII(.ascii	"HEVC_CombinePacket FATAL: pCurrNal=NULL!\012\000" )
	.space	2
.LC239:
	ASCII(.ascii	"END of the bit buffer, copy the first packet!\012\000" )
	.space	1
.LC240:
	ASCII(.ascii	"%s: flush dpb failed, return %d\012\000" )
	.space	3
.LC241:
	ASCII(.ascii	"DecVDM no slice and needn't start VDM, but MaxBytes" )
	ASCII(.ascii	"Received exceed threshold!\012\000" )
	.space	1
.LC242:
	ASCII(.ascii	"DecVDM no slice and needn't start VDM\012\000" )
	.space	1
.LC243:
	ASCII(.ascii	"IPBDecMode Changed (%d -> %d)\012\000" )
	.space	1
.LC244:
	ASCII(.ascii	"Discard this B(poc=%d) before P, is_ref_idc=%d.\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC245:
	ASCII(.ascii	"VDM start, TotalPicNum=%d.\012\000" )
.LC246:
	ASCII(.ascii	"%s no correct slice in the pic\012\000" )
.LC247:
	ASCII(.ascii	"%s with invalid pos(%d)\012\000" )
	.space	3
.LC248:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC249:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%" )
	ASCII(.ascii	"d, logic_fs=%p, dec_fs=%p)\012\000" )
	.space	1
.LC250:
	ASCII(.ascii	"%s get APC error, ret %d\012\000" )
	.space	2
.LC251:
	ASCII(.ascii	"No frame store for lost pic.\012\000" )
	.space	2
.LC252:
	ASCII(.ascii	"DPB ERROR: Can not get ref_fs!\012\000" )
.LC253:
	ASCII(.ascii	"DPB no suited fs for lost pic.\012\000" )
.LC254:
	ASCII(.ascii	"Take poc(%d) to creat lost poc(%d).\012\000" )
	.space	3
.LC255:
	ASCII(.ascii	"DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\012\000" )
	.space	1
.LC256:
	ASCII(.ascii	"ERROR: Can not new logic fs!\012\000" )
	.space	2
.LC257:
	ASCII(.ascii	"Lost pic insert in DPB Failed!\012\000" )
.LC258:
	ASCII(.ascii	"%s call HEVC_FlushOutputFrmFromDPB failed\012\000" )
	.space	1
.LC259:
	ASCII(.ascii	"%s call HEVC_EmptyFrmFromDPB failed\012\000" )
	.space	3
.LC260:
	ASCII(.ascii	"Start Reason: SliceParaNum= %d, \012\000" )
	.space	2
.LC261:
	ASCII(.ascii	"Too many slice , err!\012\000" )
	.space	1
.LC262:
	ASCII(.ascii	"s32OutErrThr = %d,drop poc %d because lost ref fram" )
	ASCII(.ascii	"e(pod %d)\012\000" )
	.space	2
.LC263:
	ASCII(.ascii	"Ref frame(poc %d) lost.\012\000" )
	.space	3
.LC264:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), need to incr" )
	ASCII(.ascii	"ease DPB size.\012\000" )
	.space	1
.LC265:
	ASCII(.ascii	"%s call HEVC_IncreaseDPBSize failed\012\000" )
	.space	3
.LC266:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), output minpo" )
	ASCII(.ascii	"c frame.\012\000" )
	.space	3
.LC267:
	ASCII(.ascii	"%s can't find such pic.\012\000" )
	.space	3
.LC268:
	ASCII(.ascii	"%s DPB.used_size(%d) >= 17.\012\000" )
	.space	3
.LC269:
	ASCII(.ascii	"%s find pos=%d, poc=%d.\012\000" )
	.space	3
.LC270:
	ASCII(.ascii	"%s call HEVC_OutputOneFrmFromDPB failed\012\000" )
	.space	3
.LC271:
	ASCII(.ascii	"Init pic err, exit\012\000" )
.LC272:
	ASCII(.ascii	"HEVC_WritePicMsg failed!\012\000" )
	.space	2
.LC273:
	ASCII(.ascii	"Cur pic not init yet, discard this slice!\012\000" )
	.space	1
.LC274:
	ASCII(.ascii	"Dec List error, ret=%d\012\000" )
.LC275:
	ASCII(.ascii	"pListX[0][%d] = NULL, listXsize[0] = %d\012\000" )
	.space	3
.LC276:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL, listXsize[0] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC277:
	ASCII(.ascii	"pListX[0][%d] frame_store(%p), pstLogicFs(%p) inval" )
	ASCII(.ascii	"id\012\000" )
	.space	1
.LC278:
	ASCII(.ascii	"pListX[1][%d] = NULL, listXsize[1] = %d\012\000" )
	.space	3
.LC279:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL, listXsize[1] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC280:
	ASCII(.ascii	"pListX[i][%d] pstLogicFs(%p) invalid\012\000" )
	.space	2
.LC281:
	ASCII(.ascii	"HEVC_WriteSliceMsg err.\012\000" )
	.space	3
.LC282:
	ASCII(.ascii	"%s call HEVC_GetUnRefPicWithMinPoc failed\012\000" )
	.space	1
.LC283:
	ASCII(.ascii	"Ref List is Wrong!\012\000" )
.LC284:
	ASCII(.ascii	"VPS decode error.\012\000" )
	.space	1
.LC285:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC286:
	ASCII(.ascii	"PPS decode error.\012\000" )
	.space	1
.LC287:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC288:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d\012\000" )
.LC289:
	ASCII(.ascii	"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_" )
	ASCII(.ascii	"NORMAL\012\000" )
	.space	1
.LC290:
	ASCII(.ascii	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\012\000" )
	.space	1
.LC291:
	ASCII(.ascii	"%s call HEVC_IModeProcess Failed\012\000" )
	.space	2
.LC292:
	ASCII(.ascii	"HEVC_StorePicInDpb return(%d) from L%d\012\000" )
.LC293:
	ASCII(.ascii	"%s %d: InsertFrmInDPB failed, return %d\012\000" )
	.space	3
.LC294:
	ASCII(.ascii	"%s call HEVC_CheckFrameStore failed!\012\000" )
	.space	2
.LC295:
	ASCII(.ascii	"%s output current picture failed\012\000" )
	.space	2
.LC296:
	ASCII(.ascii	"%s call HEVC_RemoveUnUsedFrameStore Failed.\012\000" )
	.space	3
.LC297:
	ASCII(.ascii	"%s call HEVC_InsertFrmInDPB Failed.\012\000" )
	.space	3
.LC298:
	ASCII(.ascii	"%s call HEVC_FirstFrameFastOut Failed\012\000" )
	.space	1
.LC299:
	ASCII(.ascii	"DPB.used_size may bigger than DPB.size\012\000" )
.LC300:
	ASCII(.ascii	"HEVC_InsertFrmInDPB Failed, ret = %d\012\000" )
	.space	2
.LC301:
	ASCII(.ascii	"%s call HEVC_OutputFrmFromDPB failed\012\000" )
	.space	2
.LC302:
	ASCII(.ascii	"%s return HEVC_DEC_ERR\012\000" )
.LC303:
	ASCII(.ascii	"HEVC_StorePicInDPB failed, ret = %d\012\000" )
	.space	3
.LC304:
	ASCII(.ascii	"%s call HEVC_SimpleDPBProcess Failed\012\000" )
	.space	2
.LC305:
	ASCII(.ascii	"%s call HEVC_DecOrderProcess Failed\012\000" )
	.space	3
.LC306:
	ASCII(.ascii	"%s call HEVC_DispOrderProcess Failed\012\000" )
	.space	2
.LC307:
	ASCII(.ascii	"Unkown Error: No available fs, try to remove unused" )
	ASCII(.ascii	" fs!\012\000" )
	.space	3
.LC308:
	ASCII(.ascii	"Remove failed, clear DPB!\012\000" )
	.space	1
.LC309:
	ASCII(.ascii	"Remove success! DPB: used %d, size %d.\012\000" )
.LC310:
	ASCII(.ascii	"--------------- PrintFrameStoreState START --------" )
	ASCII(.ascii	"-------\012\000" )
.LC311:
	ASCII(.ascii	"--------------- PrintFrameStoreState END ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC312:
	ASCII(.ascii	"No frame store available!\012\000" )
	.space	1
.LC313:
	ASCII(.ascii	"Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displa" )
	ASCII(.ascii	"yed=%d \000" )
	.space	1
.LC314:
	ASCII(.ascii	"p_usrdat[%d]=%p \000" )
	.space	3
.LC315:
	ASCII(.ascii	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak" )
	ASCII(.ascii	", ClearAll!\012\000" )
.LC316:
	ASCII(.ascii	"HEVC_DecSliceSegmentHeader dec err\012\000" )
.LC317:
	ASCII(.ascii	"%s last frame fs unrelease, fix it!\012\000" )
	.space	3
.LC318:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pPacket!\012\000" )
	.space	1
.LC319:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC320:
	ASCII(.ascii	"HEVC_InquireSliceProperty error.\012\000" )
	.space	2
.LC321:
	ASCII(.ascii	"HEVC_DecOneNal ERR\012\000" )
.LC322:
	ASCII(.ascii	"%s pstLogicFsImage is NULL!\012\000" )
	.space	3
.LC323:
	ASCII(.ascii	"%s InsertVO err:%d, ClearAll\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
.LANCHOR2 = . + 147312
.LANCHOR4 = . + 188232
.LANCHOR5 = . + 646536
.LANCHOR6 = . + 654720
	.type	g_TsToRsMap, %object
	.size	g_TsToRsMap, 147456
g_TsToRsMap:
	.space	147456
	.type	g_IsDeced, %object
	.size	g_IsDeced, 36864
g_IsDeced:
	.space	36864
	.type	s_auiSigLastScan, %object
	.size	s_auiSigLastScan, 458752
s_auiSigLastScan:
	.space	458752
	.type	g_hrd_parameters, %object
	.size	g_hrd_parameters, 10376
g_hrd_parameters:
	.space	10376
	.type	s_TmpParam, %object
	.size	s_TmpParam, 15788
s_TmpParam:
	.space	15788
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
