#ifndef SYSCALL_DISPATCHER_H
#define SYSCALL_DISPATCHER_H

#define STDOUT 1
#define STDIN 0

/*arreglo de de system calls*/
typedef uint64_t (* syscall)(uint64_t p, uint64_t q, uint64_t r);

uint64_t syscallDispatcher(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx);
uint64_t write(uint64_t fd, uint64_t buffer, uint64_t count);
uint64_t read(uint64_t fd, uint64_t buffer, uint64_t count);



#endif