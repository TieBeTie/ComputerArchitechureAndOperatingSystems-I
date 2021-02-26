/*
Реализуйте на языке Си программу, которая копирует содержимое потока ввода на поток вывода.

Использование стандартной библиотеки Си запрещено, единственная доступная функция - это syscall(2).

Точка входа в программу - функция _start.

Для использования syscall можно включить в текст программы следующее объявление:
 */

#include <sys/syscall.h>
#include <inttypes.h>

long syscall(long number, ...);
void _start() {
  char text[] = "";
  for (long call = syscall(SYS_read, 0, text, 1); call != 0;
       call = syscall(SYS_read, 0, text, 1)) {
    syscall(SYS_write, 1, text, 1);
  }
  syscall(SYS_exit, 0);
}