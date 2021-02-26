/*
Реализуйте на языке Си программу, которая выводит "Hello, World!".

Использование стандартной библиотеки Си запрещено, единственная доступная функция - это syscall(2).

Точка входа в программу - функция _start.

Для использования syscall можно включить в текст программы следующее объявление:

long syscall(long number, ...);
Для локального тестирования можно взять реализацию syscall здесь: syscall.S.
*/

#include <sys/syscall.h>
long syscall(long number, ...);
void _start() {
  char text[] = "Hello, World!";
  syscall(SYS_write, 1, text, sizeof(text) - 1);
  syscall(SYS_exit, 0);
}