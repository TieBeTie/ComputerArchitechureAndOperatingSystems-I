/*
Программе передаются два аргумента: имя файла, и строка для поиска.

Необходимо найти все вхождения строки в текстовом файле, используя отображение на память с помощью системного вызова mmap.

На стандартный поток вывода вывести список всех позиций (с нуля) в файле, где втречаются строка.
*/


#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>

int main(int arc, char *argv[]) {
  char *pattern = argv[2];
  int fd = open(argv[1], O_RDONLY);
  struct stat st;
  fstat(fd, &st);
  char *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  char *entry = map;

  int64_t len = st.st_size;
  while (NULL != (entry = memmem(entry, len, pattern, strlen(pattern)))) {
    int64_t difference = entry - map;
    len = st.st_size - difference;
    printf("%lu\n", difference);
    ++entry;
  }

  munmap(map, st.st_size);
  close(fd);
  return 0;
}