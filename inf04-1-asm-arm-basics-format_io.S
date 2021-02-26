/*
Реализуйте программу, которая вычисляет сумму двух целых десятичных чисел. Размер типа равен размеру машинного слова.

Можно использовать функции стандартной библиотеки языка Си scanf и printf.

В качестве точки входа можно считать функцию main.
*/

  .text
  .global main
main:
  push {lr} // save

  sub sp, #8 //pointer to stack
  ldr r0, =frm_scanf //pointer to format scanf
  mov r1, sp  //pointer to first param
  add r2, sp, #4 //pointer to second param
  bl scanf //run

  ldr r1, [sp] //first param
  ldr r2, [sp, #4] //second param
  add sp, #8 //go back stack

  ldr r0, =frm_printf //pointer to format printf
  add r1, r1, r2 //summ and output to r1
  bl printf //run

  pop {lr} //link register go back
  bx lr //return link
frm_scanf:
  .ascii "%d%d\0"
frm_printf:
  .ascii "%d\0"