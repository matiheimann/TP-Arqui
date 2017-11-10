GLOBAL generate_overflow
GLOBAL generate_inavlid_opcode
GLOBAL generate_divide_by_cero

generate_overflow:
	push rbp
    mov rbp, rsp

	mov ax, 1000h
    mov bl, 10h
    div bl

    leave
    ret 

generate_inavlid_opcode:
	push rbp
	mov rbp, rsp

	UD2

	leave
	ret

generate_divide_by_cero:
	push rbp
	mov rbp, rsp

	mov ax, 1
	mov bl, 0
	div bl

	leave
	ret

