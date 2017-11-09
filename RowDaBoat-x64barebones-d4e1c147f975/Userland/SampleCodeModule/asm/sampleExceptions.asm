GLOBAL generate_overflow
GLOBAL generate_inavlid_opcode

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
