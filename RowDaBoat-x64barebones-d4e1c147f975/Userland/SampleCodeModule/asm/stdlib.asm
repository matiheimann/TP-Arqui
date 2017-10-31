GLOBAL print
GLOBAL scan

print:
	
	push rbp
	mov rsp, rbp

	mov rax, 4
	mov rbx, 1
	mov rcx, rdi
	mov rdx, rsi
	int 80h

	leave

	ret

scan:

	push rbp
	mov rsp, rbp

	mov rax, 3
	mov rbx, 0
	mov rcx, rdi
	mov rdx, rsi
	int 80h

	leave

	ret

