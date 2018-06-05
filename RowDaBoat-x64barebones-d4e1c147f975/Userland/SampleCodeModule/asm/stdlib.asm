GLOBAL print
GLOBAL scan
GLOBAL clearScreen
GLOBAL paintPixelAt
GLOBAL XResolution
GLOBAL YResolution
GLOBAL displayTimeData
GLOBAL memoryAllocation
GLOBAL memoryFree
GLOBAL leaveProcess
GLOBAL createProcess
GLOBAL getProcessPid
GLOBAL getProcessesInfo
GLOBAL generateMutex
GLOBAL getMutex
GLOBAL deleteMutex
GLOBAL blockMutex
GLOBAL unlockMutex
GLOBAL generateMessageHolder
GLOBAL getMessageHolder
GLOBAL deleteMessageHolder
GLOBAL send
GLOBAL receive
GLOBAL waitProcess
GLOBAL fileOpen
GLOBAL fileClose
GLOBAL fileRead
GLOBAL fileWrite
GLOBAL fileAppend
GLOBAL waitThread
GLOBAL killThread
GLOBAL createThread
GLOBAL filesShow

EXTERN printf

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

leaveProcess:
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
	mov rcx, rsi
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

getProcessesInfo:
	push rbp
	mov rbp, rsp
	mov rax, 15
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

	generateMutex:

	push rbp
	mov rbp, rsp

	mov rax, 16
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

getMutex:

	push rbp
	mov rbp, rsp

	mov rax, 17
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

deleteMutex:

	push rbp
	mov rbp, rsp

	mov rax, 18
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

blockMutex:

	push rbp
	mov rbp, rsp

	mov rax, 19
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

unlockMutex:

	push rbp
	mov rbp, rsp

	mov rax, 20
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

generateMessageHolder:

	push rbp
	mov rbp, rsp

	mov rax, 21
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

getMessageHolder:

	push rbp
	mov rbp, rsp

	mov rax, 22
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

deleteMessageHolder:

	push rbp
	mov rbp, rsp

	mov rax, 23
	mov rbx, rdi
	int 80h

	mov rsp, rbp
	pop rbp
	ret

send:

	push rbp
	mov rbp, rsp

	mov rax, 24
	mov rbx, rdi
	mov rcx, rsi
	mov rdx, rdx
	int 80h

	mov rsp, rbp
	pop rbp
	ret

receive:

	push rbp
	mov rbp, rsp

	mov rax, 25
	mov rbx, rdi
	mov rcx, rsi
	mov rdx, rdx
	int 80h

	mov rsp, rbp
	pop rbp
	ret


waitProcess:
	push rbp
	mov rbp, rsp

	mov rax, 26
	mov rbx, rdi

	int 80h

	mov rsp, rbp
	pop rbp
	ret

fileOpen:
	push rbp
	mov rbp, rsp

	mov rax, 27
	mov rbx, rdi

	int 80h

	mov rsp, rbp
	pop rbp
	ret

fileClose:
	push rbp
	mov rbp, rsp

	mov rax, 28
	mov rbx, rdi

	int 80h

	mov rsp, rbp
	pop rbp
	ret

fileRead:
	push rbp
	mov rbp, rsp

	mov rax, 29
	mov rbx, rdi

	int 80h

	mov rsp, rbp
	pop rbp
	ret

fileWrite:
	push rbp
	mov rbp, rsp

	mov rax, 30
	mov rbx, rdi
	mov rcx, rsi

	int 80h

	mov rsp, rbp
	pop rbp
	ret

fileAppend:
	push rbp
	mov rbp, rsp

	mov rax, 31
	mov rbx, rdi
	mov rcx, rsi

	int 80h

	mov rsp, rbp
	pop rbp
	ret


waitThread:
	push rbp
	mov rbp, rsp

	mov rax, 32
	mov rbx, rdi
	mov rcx, rsi

	int 80h

	mov rsp, rbp
	pop rbp
	ret

killThread:
	push rbp
	mov rbp, rsp

	mov rax, 33
	mov rbx, rdi
	mov rcx, rsi

	int 80h

	mov rsp, rbp
	pop rbp
	ret

createThread:
	push rbp
	mov rbp, rsp

	mov rax, 34
	mov rbx, rdi
	mov rcx, rsi
	mov rdx, rdx

	int 80h

	mov rsp, rbp
	pop rbp
	ret

filesShow:
	push rbp
	mov rbp, rsp

	mov rax, 35

	int 80h

	mov rsp, rbp
	pop rbp
	ret	