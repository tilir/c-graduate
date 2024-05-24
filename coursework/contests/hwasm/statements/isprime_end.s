
.line 100
	jne	loop
composite:
	mov	eax, 0
	ret
prime:
	mov	eax, 1
	ret
	.size	is_prime, .-is_prime
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d"
.LC1:
	.string	"isprime.c"
.LC2:
	.string	"res == 1"
.LC3:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
	sub	rsp, 24
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 8[rsp], rax
	xor	eax, eax
	lea	rsi, 4[rsp]
	lea	rdi, .LC0[rip]
	call	__isoc99_scanf@PLT
	cmp	eax, 1
	jne	.L14
	mov	edi, DWORD PTR 4[rsp]
	call	is_prime
	mov	edx, eax
	lea	rsi, .LC3[rip]
	mov	edi, 1
	mov	eax, 0
	call	__printf_chk@PLT
	mov	rax, QWORD PTR 8[rsp]
	xor	rax, QWORD PTR fs:40
	jne	.L15
	mov	eax, 0
	add	rsp, 24
	ret
.L14:
	mov	edx, 15
	lea	rsi, .LC1[rip]
	lea	rdi, .LC2[rip]
	call	__assert_fail@PLT
.L15:
	.size	main, .-main
