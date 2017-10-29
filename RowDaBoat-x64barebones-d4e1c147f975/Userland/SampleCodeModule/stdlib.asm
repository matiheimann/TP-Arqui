GLOBAL print

print:
	mov rax, 4
	mov rbx, 0
	mov rcx, rdi
	mov rdx, 10
	int 80h
	ret
	