/*
Реализуйте функцию

extern void normalize_path(char * path);
которая обрабатывает строки, представляющие пути к файлам (заканчиваются на любой символ, отличный от /) или каталогам (заканчиваются на символ /).

Функция должна привести текст в каноническую форму:

убрать дублирование подряд идущих символов /
обработать фрагменты ./ и ../
Запрещается использовать библиотечные строковые функции.

Запрещается выделять память под новую строку, - используйте уже существующую, аргумент не является константной строкой.

Используйте арифметику указателей.

Примеры
Входные данные
abrakadabra///abc
Результат работы
abrakadabra/abc
Входные данные
/var/log/../lib/./ejexec
Результат работы
/var/lib/ejexec
 */

#include <stdio.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>


extern void normalize_path(char * path) {
  char* tmp;
  bool point = false;
  bool double_point = false;
  for (char* head = path; *head != '\0'; ++head) {
    if (*(head - 1) == '/' && *head == '/') {
      tmp = head;
      while (*head != '\0') {
        *(head - 1) = *head;
        head++;
      }
      *(head - 1) = *head;
      head = tmp - 1;
    } else if (*(head - 2) == '/' && *(head - 1) == '.' && *head == '/') {
      tmp = head;
      while (*head != '\0') {
        *(head - 2) = *head;
        head++;
      }
      *(head - 2) = *head;
      head = tmp - 2;
    } else if (*(head - 3) == '/' && *(head - 2) == '.' && *(head - 1) == '.' && *head == '/') {
      tmp = head;
      int shift = 0;
      for (head = head - 4; *head != '/'; --head) {
        shift++;
      }
      shift += 4;
      while (*head != '\0') {
        *head = *(head + shift);
        head++;
      }
      *head = *(head + shift);
      head = tmp - shift;
    }
  }
}}