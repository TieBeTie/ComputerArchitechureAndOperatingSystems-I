/*
Реализуйте на языке ассемблера x86_64 программу, которая копирует содержимое со стандартного потока ввода на стандартный поток вывода.

Использование стандартной библиотеки Си запрещено.

Точка входа в программу - функция _start.
*/

.intel_syntax noprefix
#include <sys/syscall.h>
.global start
.text

        _start:
mov rax, SYS_read
mov rdi, 0
mov rsi, rsp
mov rdx, 1
syscall

        cmp rax, 0
je loop_end

mov rax, SYS_write
mov rdi, 1
mov rsi, rsp
mov rdx, 1
syscall

        jmp _start
        loop_end:
mov rax, SYS_exit
mov rdi, 0
syscall
