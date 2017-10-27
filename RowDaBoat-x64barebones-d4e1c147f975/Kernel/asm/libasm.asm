GLOBAL cpuVendor
GLOBAL read_port

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

read_port:
	push rbp
	mov rbp, rsp

	xor al, al
	xor rdx, rdx
	mov rdx, rdi
	in al, dx

	mov rsp, rbp
	pop rbp
	ret
