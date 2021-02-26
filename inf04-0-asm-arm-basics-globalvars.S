/*
Реализуйте функцию calculate,
которая вычисляет значение выражения:
R=(A*B)+(C*D), где A, B, C, и D - это глобальные переменные
типа uint32_t, объявленные во внешнем модуле компиляции,
а R, - глобальная переменная типа uint32_t в текущем модуле компиляции.
*/

  .data
  .global R
  .text
  .global calculate
calculate:
  ldr r0, =A
  ldr r0, [r0]
  ldr r1, =B
  ldr r1, [r1]
  ldr r2, =C
  ldr r2, [r2]
  ldr r3, =D
  ldr r3, [r3]

  mul r2, r3, r2      //C = C*D
  mla r2, r0, r1, r2  //C = A*B + C

  .comm R, 4, 4
  ldr r1, =R
  str r2, [r1]
  bx lr
