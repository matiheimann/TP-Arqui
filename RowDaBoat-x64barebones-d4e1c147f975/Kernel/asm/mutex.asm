
GLOBAL enter_region
GLOBAL leave_region

EXTERN addCurrentThreadToWaitingQueue
EXTERN dequeueWaitingThread

section .text

enter_region:
	push rbp
	mov rbp, rsp

_repeat:
  mov al, 0
	mov cl, 1
	lock cmpxchg [rdi], cl
	cmp al, 0
	jne _addCurrentProcessToQueue

_continue:

	mov rsp, rbp
	pop rbp
	ret

_addCurrentProcessToQueue:
	call addCurrentThreadToWaitingQueue
	jmp _continue

leave_region:
	push rbp
	mov rbp, rsp

	mov BYTE [rdi], 0
	call dequeueWaitingThread

	mov rsp, rbp
	pop rbp
	ret
