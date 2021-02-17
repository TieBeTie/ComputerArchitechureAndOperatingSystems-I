/*
Реализуйте на языке ассемблера ARM функцию с сигнатурой:

int summ(int x0, int N, int *X)
Функция должна вычислять значение x0+∑xi, где 0≤i<N
*/

  .text
  .global summ

summ:
  push {r4}
  mov r3, #0
  .loop:
    ldr r4, [r2], #4
    add r0, r4
    add r3, #1
    cmp r3, r1
  bne .loop
  pop {r4}
  bx lr