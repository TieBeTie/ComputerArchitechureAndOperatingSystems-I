/*
Реализуйте программу, которая считывает символы со стандартного потока ввода, а затем выводит их в обратном порядке.

Можно использовать функции стандартной библиотеки языка Си: fgetc, fputc, realloc и free.

В качестве точки входа можно считать функцию main.
*/

  .text
  .global main
main:
  push {r4, r5, r6, lr}
  mov r0, #0 //null
  mov r1, #4 //start buffer_size = 4
  bl realloc //r0 - array

  mov r4, r0 //responsible to array r4
  mov r5, #0 //size
  mov r6, #4 //buffer_size
loop:
  ldr r0, =stdin //pointer to in
  ldr r0, [r0]   //dereferencing a pointer
  bl fgetc       //read symbol

  cmp r0, #-1 //  == exit signal
  beq reverse_order

  cmp r0, #10 // without newline
  beq loop

  str r0, [r4, r5]  //text[i] = symbol, [r4, r5], #1 doesn't work
  add r5, r5, #1    //r5 += 1
  cmp r5, r6        //if (r5 >= r6) #end of array then bigger him
  blo loop

  mov r0, #2
  mul r1, r6, r0 // r1 = buffer_size * 2
  mov r6, r1 //r6 = new_buffer_size
  mov r0, r4  //r0 = r4 recognize reference
  bl realloc  //bigger

  mov r4, r0 //responsible to array r4
  b loop
reverse_order:
  cmp r5, #0 //if stack pointer came back
  beq end     // clean

  sub r5, r5, #1 // r5 -= 1
  ldr r1, =stdout //pointer to out
  ldr r1, [r1]  //dereferencing a pointer
  ldr r0, [r4, r5] // symbol = text[i]
  bl fputc //go to fputc
  b reverse_order //and again to r5 = 0
end:
  mov r0, r4 //array clean
  bl free //clean
  pop {r4, r5, r6, lr}
  bx lr