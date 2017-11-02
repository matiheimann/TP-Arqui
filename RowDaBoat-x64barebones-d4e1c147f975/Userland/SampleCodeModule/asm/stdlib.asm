GLOBAL print
GLOBAL scan
GLOBAL clearScreen

EXTERN printInt

print:
	
	push rbp
	mov rbp, rsp

	mov rax, 4
	mov rbx, 1
	mov rcx, rdi
	mov rdx, rsi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

scan:

	push rbp
	mov rbp, rsp

	mov rax, 3
	mov rbx, 0
	mov rcx, rdi
	mov rdx, rsi
	int 80h


	mov rsp, rbp
	pop rbp
	ret

clearScreen

	push rbp
	mov rbp, rsp

	mov rax, 5
	int 80h

	mov rsp, rbp
	pop rbp
	ret

