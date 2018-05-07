
GLOBAL enter_region
GLOBAL leave_region

section .text

enter_region:
	push rbp
	mov rbp, rsp

_repeat:
  mov al, 0
	mov cl, 1
	lock cmpxchg [rdi], cl
	cmp al, 0
	jne _repeat

	mov rsp, rbp
	pop rbp
	ret

leave_region:
	push rbp
	mov rbp, rsp

	mov BYTE [rdi], 0

	mov rsp, rbp
	pop rbp
	ret
