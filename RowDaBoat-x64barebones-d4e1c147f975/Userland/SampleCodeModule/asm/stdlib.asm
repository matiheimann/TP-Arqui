GLOBAL print
GLOBAL scan
GLOBAL clearScreen
GLOBAL paintPixelAt
GLOBAL XResolution
GLOBAL YResolution
GLOBAL displayTimeData
GLOBAL memoryAllocation
GLOBAL memoryFree
GLOBAL exitProcess
GLOBAL createProcess
GLOBAL getProcessPid

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

clearScreen:

	push rbp
	mov rbp, rsp

	mov rax, 5
	int 80h

	mov rsp, rbp
	pop rbp
	ret

paintPixelAt:
	
	push rbp
	mov rbp, rsp
	mov rax, 6
	mov rbx, rdi
	mov rcx, rsi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

XResolution:
	push rbp
	mov rbp, rsp
	mov rax, 7
	int 80h

	mov rsp, rbp
	pop rbp
	ret

YResolution:
	push rbp
	mov rbp, rsp
	mov rax,8
	int 80h

	mov rsp, rbp
	pop rbp
	ret

displayTimeData:
	push rbp
	mov rbp, rsp
	mov rax,9
	int 80h

	mov rsp, rbp
	pop rbp
	ret

memoryAllocation:
	push rbp
	mov rbp, rsp
	mov rax, 10
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

memoryFree:
	push rbp
	mov rbp, rsp
	mov rax, 11
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

exitProcess:
	push rbp
	mov rbp, rsp
	mov rax, 12
	int 80h

	mov rsp, rbp
	pop rbp
	ret

createProcess:
	push rbp
	mov rbp, rsp
	mov rax, 13
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

getProcessPid:
	push rbp
	mov rbp, rsp
	mov rax, 14
	int 80h

	mov rsp, rbp
	pop rbp
	ret