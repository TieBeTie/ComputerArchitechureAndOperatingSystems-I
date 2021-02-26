/*
Реализуйте на языке ассемблера x86 (IA-32) или x86-64 две функции с сигнатурами:

extern double
calc(double A, double B, double C, int D);

extern void
vector_sum(int N, const float *A, const float *B, float *R);
Первая функция вычисляет значение выражения (A+B)/(C+D) и возвращает результат. Можно использовать как вычисления с помощью i387 FPU (только x86), так и с помощью инструкций SSE (x86 и x86-64).

Вторая функция вычисляет поэлементную сумму R[i]=A[i]+B[i]. Гарантируется, что число N больше нуля и кратно 4, а адреса массивов выровнены в памяти по границе 32 байта. Используйте векторные инструкции для вычисления.
*/

  .global calc
  .global vector_sum
  .intel_syntax noprefix
  .text
calc:
  push ebp
  mov ebp, esp
  sub esp, 8

  movsd xmm0, [ebp+8]  //копирует двойное слово
  addsd xmm0, [ebp+16] //добавляет двойное слово A + B
  cvtsi2sd xmm1, [ebp+32] //конвертирует двойное слово в значение с плавающей запятой двойной точности
  addsd xmm1, [ebp+24] //добавляет двойное слово C + D
  divsd xmm0, xmm1 //(A + B) / (C + D)

  movsd [ebp-8], xmm0  //запись в ответ
  fld qword ptr [ebp-8] //загрузить в стек

  leave  //Set SP to BP, then pop BP.
  ret

vector_sum:
  push ebp
  mov ebp, esp

  push esi
  push edi
  push ebx

  mov ecx, [ebp+8] //N
  mov esi, [ebp+12] //*A
  mov edi, [ebp+16] //*B
  mov ebx, [ebp+20] //*R
  mov eax, 0

loop:
  movaps xmm0, [esi+eax*4] //служит для пересылки 128-битных данных между SIMD-регистрами общего назначения
  movaps xmm1, [edi+eax*4]

  addps xmm0, xmm1 //cложить упакованные значения

  movaps [ebx+eax*4], xmm0 //переместить в R
  add eax, 4    //++i
  cmp eax, ecx //if (i == N) break
  jl loop

  pop ebx
  pop edi
  pop esi

  leave
  ret