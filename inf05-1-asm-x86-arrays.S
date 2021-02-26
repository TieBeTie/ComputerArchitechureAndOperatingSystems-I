/*
Реализуйте функцию на языке ассемблера x86 (IA-32) или x86-64 с сигнатурой:

extern void summ(int N, const int *A, const int *B, int *R);

Функция вычисляет значения Ri=Ai+Bi для всех i от 0 до N.

Память для хранения массива-результата уже выделена.
*/

  .intel_syntax noprefix
  .global summ
  .text

summ:
  push ebp
  mov ebp, esp

  push ebx
  mov ecx, [ebp + 8]
.loop:
  mov ebx, ecx
  dec ebx

  mov edx, [ebp + 12]
  mov eax, [edx + 4 * ebx]

  mov edx, [ebp + 16]
  add eax, [edx + 4 * ebx]

  mov edx, [ebp + 20]
  mov [edx + 4 * ebx], eax
  loop .loop //--ecx if != 0

  pop ebx
  pop ebp

  ret