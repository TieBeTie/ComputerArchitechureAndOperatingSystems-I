/*
Напишите программу, которая читает со стандартного потока ввода последовательность символов, и выводит только те из них, которые являются десятичными цифрами от 0 до 9.

Можно использовать функции стандартной библиотеки языка Си: fgetc и fputc.

В качестве точки входа можно считать функцию main.
*/

  .text
  .global main
main:
  push {lr}
loop:
  ldr r0, =stdin //pointer to in
  ldr r0, [r0]   //demining pointer for fgetc
  bl fgetc

  cmp r0, #-1 //exit signal
  beq exit

  cmp r0, #48 //from 0
  blo loop

  cmp r0, #57 //to 9
  bhi loop

  ldr r1, =stdout //pointer to out
  ldr r1, [r1]    //demining pointer for fputc
  bl fputc

  b loop
exit:
  pop {lr}
  bx lr