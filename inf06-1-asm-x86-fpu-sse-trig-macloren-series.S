/*
Реализуйте на языке ассемблера x86 (IA-32) или x86-64 функцию с сигнатурой:

extern double my_sin(double x)
которая вычисляет значение sin(x).

Запрещено использовать встроенные тригонометрические инструкции.

Для вычислений используйте известный вам из курса Математического анализа способ разложения функции в ряд. Точность результата должна быть маскимально возможной для типа данных double.
*/

//E (-1)^n * x^(2n + 1) / (2n + 1)!
  .global my_sin
  .intel_syntax noprefix
  .text

my_sin:
  push ebp
  mov ebp, esp
  sub esp, 8
  push ebx
  push ecx

  movsd xmm0, [ebp+8] //достаём x
  mov ebx, 0

  movsd xmm1, xmm0    //x^k
  cvtsi2sd xmm2, ebx //сумма = 0.0
  cvtsi2sd xmm3, ebx //предыдущая тоже = 0.0
  mov ecx, 1 //счетчик

  mov ebx, -1
  cvtsi2sd xmm4, ebx // -1.0
  mov eax, 2

.loop:
  movsd xmm3, xmm2 //сохранение суммы

  addsd xmm2, xmm1 // += x^i
  mulsd xmm1, xmm4 // (-1) * x^i
  mulsd xmm1, xmm0
  mulsd xmm1, xmm0 // x ^ (i + 2)

  mov eax, 1
  mov ebx, 2
  mov eax, 2

  mul ecx // eax = 2i
  cvtsi2sd xmm5, eax //(2i).
  divsd xmm1, xmm5 // summ /= (2i).

  add eax, 1 // 2i + 1
  cvtsi2sd xmm5, eax // (2i + 1).
  divsd xmm1, xmm5  # summ /= (2*i + 1).

  add ecx, 1 // ++i
  comisd xmm2, xmm3 //если эта сумма равна предыдущей, то точность найдена
  jne .loop

  movsd [ebp-8], xmm2
  fld qword ptr [ebp-8] //загрузка ответа

  pop ecx
  pop ebx

  leave
  ret