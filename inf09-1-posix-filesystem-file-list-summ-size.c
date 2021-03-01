/*
Задача inf09-1: posix/filesystem/file-list-summ-size
Программе на стандартном потоке ввода передаётся список имён файлов.

Необходимо посчитать суммарный размер в байтах всех файлов, которые являются регулярными.
 */


#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memchr
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char file_name[PATH_MAX];
  uint64_t result = 0;

  struct stat s;
  char *last;

  while (fgets(file_name, sizeof(file_name), stdin)) {
    last = memchr(file_name, '\n', sizeof(file_name));
    if (last) {
      *last = '\0';
    }
    if (lstat(file_name, &s) != -1) { //lstat чтобы парсило ссылки
      if (S_ISREG(s.st_mode)) {
        result += s.st_size;
      }
    }
  }

  printf("%" PRIu64 "\n", result);
}