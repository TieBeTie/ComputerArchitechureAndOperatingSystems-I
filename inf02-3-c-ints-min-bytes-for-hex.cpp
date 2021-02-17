/*
В аргументах командной строки задаются целые неотрицательные числа в шетнадцатеричной системе исчисления в синтаксисе языка Си.

Для каждого числа определить минимально необходимое количество байт, которое требуется для того, чтобы можно было хранить эти числа.

Examples
Input
0xFF 0xABCD 0xFFFFFFFF
Output
1 2 4
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[]){
  uint32_t len;
  int ch = 0;

  for (uint32_t hex = 1; hex < argc; ++hex) {
    for (ch = 2; argv[hex][ch] == '0'; ++ch);
    len = strlen(argv[hex]);
    if (ch == len) {
      len = 1;
    } else {
      len = (strlen(argv[hex]) + 1 - ch) / 2;
    }
    hex < argc - 1 ? printf("%d ", len) : printf("%d", len);
  }
}
