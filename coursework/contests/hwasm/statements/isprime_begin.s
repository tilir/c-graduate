	.intel_syntax noprefix
	.text
	.globl	is_prime
	.type	is_prime, @function
is_prime:
        mov     eax, 0
        cmp     edi, 1
        jbe     composite
        cmp     edi, 3
        jbe     prime
        test    dil, 1
        je      composite
        mov     ecx, 2
loop:
