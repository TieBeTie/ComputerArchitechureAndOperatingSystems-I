/*
Программе в аргументе командной строки передается имя файла с бинарными данными в Little-Endian.

Файл хранит внутри себя односвязный список элементов:

struct Item {
  int value;
  uint32_t next_pointer;
};
Поле value храние значение элемента списка, поле next_pointer - позицию в файле (в байтах), указывающую на следующий элемент. Признаком последнего элемента является значение next_pointer, равное 0.

Расположение первого элемента списка (если он существует) - строго в нулевой позиции в файле, расположение остальных - случайным образом.

Выведите на экран значения элементов в списке в текстовом представлении.

Используйте отображение содержимого файла на память.
*/


#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc, char *argv[]) {
  int input = open(argv[1], O_RDONLY);
  if (input == -1) {
    close(input);
    return 0;
  }

  struct stat st;
  fstat(input, &st);
  if (st.st_size < 1) {
    close(input);
    return 0;
  }

  struct Item *data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, input, 0);
  if (data == MAP_FAILED) {
    close(input);
    return 0;
  }
  struct Item item = data[0];
  printf("%d ", item.value);

  while (item.next_pointer != 0) {
    item = data[item.next_pointer / 8]; //int + uint32_t
    printf("%d ", item.value);
  }

  munmap(data, st.st_size); /* освободить отображение */
  close(input);
  return 0;
}