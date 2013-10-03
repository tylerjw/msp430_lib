	.file	"regptr_test.c"
	.arch msp430g2553
	.cpu 430
	.mpy none

	.section	.init9,"ax",@progbits
	.p2align 1,0
.global	main
	.type	main,@function
/***********************
 * Function `main' 
 ***********************/
main:
	mov	r1, r4
	add	#2, r4
	add	#llo(-20), r1
	mov	#1, r12
	mov	#0, r13
	mov	#1, r14
	mov	r4, r15
	add	#llo(-22), r15
	call	#gpio_init
	mov	r4, r15
	add	#llo(-12), r15
	mov	#0, r12
	mov	#3, r13
	mov	#1, r14
	call	#gpio_init
	mov	#23168, &__WDTCTL
	mov	-6(r4), r15
	mov	-6(r4), r14
	mov.b	@r14, r13
	mov.b	-12(r4), r14
	bis.b	r13, r14
	mov.b	r14, @r15
	nop
.L2:
	mov	-8(r4), r15
	mov.b	@r15, r14
	mov.b	-12(r4), r15
	and.b	r14, r15
	jne	.L2
	mov	-20(r4), r15
	mov	-20(r4), r14
	mov.b	@r14, r14
	mov.b	r14, r13
	mov.b	-22(r4), r14
	inv.b	r14
	and.b	r13, r14
	mov.b	r14, @r15
	nop
.L3:
	mov	-8(r4), r15
	mov.b	@r15, r14
	mov.b	-12(r4), r15
	and.b	r14, r15
	jeq	.L3
	mov	-20(r4), r15
	mov	-20(r4), r14
	mov.b	@r14, r13
	mov.b	-22(r4), r14
	bis.b	r13, r14
	mov.b	r14, @r15
	nop
	jmp	.L2
.Lfe1:
	.size	main,.Lfe1-main
;; End of function 

	.text
	.p2align 1,0
.global	gpio_init
	.type	gpio_init,@function
/***********************
 * Function `gpio_init' 
 ***********************/
gpio_init:
	push	r4
	mov	r1, r4
	add	#2, r4
	sub	#8, r1
	mov	r15, -10(r4)
	mov	r14, -8(r4)
	mov	r13, -6(r4)
	mov	r12, -4(r4)
	cmp	#0, -10(r4)
	jne	.L6
	mov	#0, r15
	jmp	.L7
.L6:
	cmp	#1, -8(r4)
	jl	.L8
	cmp	#3, -8(r4)
	jl	.L9
.L8:
	mov	#0, r15
	jmp	.L7
.L9:
	cmp	#0, -6(r4)
	jl	.L10
	cmp	#8, -6(r4)
	jl	.L11
.L10:
	mov	#0, r15
	jmp	.L7
.L11:
	mov	#1, r15
	mov	-6(r4), r14
	tst	r14
	jz	.Lsend106
.Lsst106:
	rla	r15
	dec	r14
	jnz	.Lsst106
.Lsend106:
	mov.b	r15, r14
	mov	-10(r4), r15
	mov.b	r14, @r15
	cmp	#0, -4(r4)
	jeq	.L12
	mov	#1, r15
	mov	-6(r4), r14
	tst	r14
	jz	.Lsend114
.Lsst114:
	rla	r15
	dec	r14
	jnz	.Lsst114
.Lsend114:
	mov.b	r15, -4(r4)
	mov.b	#0, -3(r4)
.L12:
	cmp	#1, -8(r4)
	jne	.L13
	mov	-10(r4), r15
	mov	#__P1DIR, 8(r15)
	mov	-10(r4), r15
	mov	#__P1OUT, 2(r15)
	mov	-10(r4), r15
	mov	#__P1IN, 4(r15)
	mov	-10(r4), r15
	mov	#__P1REN, 6(r15)
	mov	-10(r4), r15
	mov.b	@r15, r15
	inv.b	r15
	mov.b	r15, r14
	mov.b	&__P1SEL, r15
	and.b	r14, r15
	mov.b	r15, &__P1SEL
	mov	-10(r4), r15
	mov.b	@r15, r15
	inv.b	r15
	mov.b	r15, r14
	mov.b	&__P1SEL2, r15
	and.b	r14, r15
	mov.b	r15, &__P1SEL2
	jmp	.L14
.L13:
	mov	-10(r4), r15
	mov	#__P2DIR, 8(r15)
	mov	-10(r4), r15
	mov	#__P2OUT, 2(r15)
	mov	-10(r4), r15
	mov	#__P2IN, 4(r15)
	mov	-10(r4), r15
	mov	#__P2REN, 6(r15)
	mov	-10(r4), r15
	mov.b	@r15, r15
	inv.b	r15
	mov.b	r15, r14
	mov.b	&__P2SEL, r15
	and.b	r14, r15
	mov.b	r15, &__P2SEL
	mov	-10(r4), r15
	mov.b	@r15, r15
	inv.b	r15
	mov.b	r15, r14
	mov.b	&__P2SEL2, r15
	and.b	r14, r15
	mov.b	r15, &__P2SEL2
.L14:
	mov	-10(r4), r15
	mov	2(r15), r15
	mov	-10(r4), r14
	mov	2(r14), r14
	mov.b	@r14, r14
	mov.b	r14, r13
	mov	-10(r4), r14
	mov.b	@r14, r14
	inv.b	r14
	and.b	r13, r14
	mov.b	r14, @r15
	mov	-10(r4), r15
	mov	8(r15), r15
	mov	-10(r4), r14
	mov	8(r14), r14
	mov.b	@r14, r14
	mov.b	r14, r13
	cmp	#0, -4(r4)
	jeq	.L15
	mov	-10(r4), r14
	mov.b	@r14, r14
	jmp	.L16
.L15:
	mov.b	#0, r14
.L16:
	bis.b	r13, r14
	mov.b	r14, @r15
	mov	-10(r4), r15
.L7:
	add	#8, r1
	pop	r4
	ret
.Lfe2:
	.size	gpio_init,.Lfe2-gpio_init
;; End of function 

