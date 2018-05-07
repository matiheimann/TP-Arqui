
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _exception0Handler
GLOBAL _exception4Handler
GLOBAL _exception6Handler
GLOBAL _syscallHandler
GLOBAL _reset_rip

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallDispatcher
EXTERN schedule
EXTERN printInt
EXTERN printStack

SECTION .text

%macro pushaq 0
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
	push fs
	push gs
%endmacro

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

%macro pushStateWithoutRax 0
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

%macro popaq 0
	pop gs
	pop fs
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro popStateWithoutRax 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
%endmacro

%macro irqHandlerMaster 1
	pushState
	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState

	iretq
%endmacro


%macro exceptionHandler 1

	;Guardo el valor de los registros
	mov [raxReg], rax
	mov [rbxReg], rbx
	mov [rcxReg], rcx
	mov [rdxReg], rdx
	mov [rsiReg], rsi
	mov [rdiReg], rdi

	;Paso los parametros a exceptionDispatcher
	mov rdi, %1 
	mov rsi, rsp
	mov rdx, [raxReg]
	mov rcx, [rbxReg]
	mov r8,  [rcxReg]
	mov r9,  [rdxReg]
	push qword [rdiReg]
	push qword [rsiReg]

	call exceptionDispatcher

	;Restauro rsp a como estaba antes de llamar a exceptionDispatcher
	add rsp, 16

	;Pusheo la direccion de la terminal de Userland para devolver el control al retornar del handler
	mov qword [rsp], 0x0000000000400000
	iretq
%endmacro

_hlt:
	sti
	hlt
	ret

_cli:
	push rbp
    mov rbp, rsp
	cli
	leave
	ret


_sti:
	push rbp
    mov rbp, rsp
	sti
	leave
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	
	pushaq
	mov rdi, rsp
	call schedule
	mov rsp, rax
	popaq
	
	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al
	
	iretq
	

;Keyboard
_irq01Handler:
	cli
	irqHandlerMaster 1
	sti
;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Overflow Exception
_exception4Handler:
	exceptionHandler 4

;Invalid Opcode Exception
_exception6Handler:
	exceptionHandler 6

;int 80h software interruption
_syscallHandler:
	pushStateWithoutRax
	
	mov rdi, rax
	mov rsi, rbx
	mov rax, rdx
	mov rdx, rcx
	mov rcx, rax 
	
	call syscallDispatcher

	popStateWithoutRax
	iretq



haltcpu:
	cli
	hlt
	ret



SECTION .bss
	raxReg resb 8
	rbxReg resb 8
	rcxReg resb 8
	rdxReg resb 8
	rsiReg resb 8
	rdiReg resb 8

SECTION .data
