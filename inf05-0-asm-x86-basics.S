/*
Реализуйте две функции на языке ассемблера x86 (IA-32) или x86-64 с сигнатурами:

extern int N;
extern int *A;
extern int *B;
extern int *R;

extern void summ();
extern void everyday795(int X, int Y);

Первая функция вычисляет значения Ri=Ai+Bi для всех i от 0 до N.

Вторая функция:

вводит с клавиатуры знаковое целое число;
умножает его на X;
прибавляет к нему Y;
выводит результат на экран.
*/

  .intel_syntax noprefix
  .globl summ
  .globl everyday795
  .text

summ:
  mov ecx, N
.loop:
  cmp ecx, 0
  jle end_loop  //while
  dec ecx

  mov edx, A
  mov eax, [edx + 4*ecx] //tmp = A[i]

  mov edx, B
  add eax, [edx + 4*ecx] //tmp += B[i]

  mov edx, R
  mov [edx + 4*ecx], eax //R[i] = tmp
  jmp .loop
end_loop:
  ret

everyday795:
  push ebp
  mov ebp, esp
  sub esp, 4

  push esp
  push scanf_fmt_ptr
  call scanf
  mov eax, [ebp - 4]
  add esp, 8
  mov ecx, [ebp + 8]
  imul ecx
  add eax, [ebp + 12]

  push eax
  mov ecx, offset printf_fmt
  push ecx
  call printf
  add esp, 8

  add esp, 4
  pop ebp
  ret
scanf_fmt:
  .string "%d"
scanf_fmt_ptr:
  .long scanf_fmt
printf_fmt:
  .string "%d\n"