GLOBAL cpuVendor
GLOBAL read_port
GLOBAL get_rtc_data
GLOBAL create_new_stack
EXTERN printInt
EXTERN printChar
EXTERN printStack
section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro	

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

	xor rax, rax
	xor rdx, rdx
	mov rdx, rdi
	in al, dx

	mov rsp, rbp
	pop rbp
	ret

get_rtc_data:
	push rbp
	mov rbp, rsp

	xor rax, rax
	mov rax, rdi
	out 70h, al
	in 	al, 71h

	mov rsp, rbp
	pop rbp
	ret

create_new_stack:
	push rbp
	mov rbp, rsp
	
	mov rsp, rdi
	
	mov rax, 518
	
	mov rdi, rsp
	call printInt
	mov rdi, 32
	call printChar
	
	push rsi

	mov rdi, rsp
	call printInt
	mov rdi, 32
	call printChar

	push rax

	mov rdi, rsp
	call printInt
	mov rdi, 32
	call printChar
	
	pushState

	mov rdi, rsp
	call printInt
	mov rdi, 32
	call printChar

	mov rdi, rsp
	call printStack


	mov rax, rsp


	mov rsp, rbp
	pop rbp
	ret