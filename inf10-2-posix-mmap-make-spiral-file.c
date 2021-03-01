/*
Задача inf10-2: posix/mmap/make-spiral-file
Программе передаются три аргумента: имя файла, положительное целое число N - размер квадратной матрицы, и положительное число W - ширина клетки матицы в символах.

Необходимо в указанном файле сформировать текст, который содержит матрицу, состоящую из чисел от 1 до N2, таким образом, чтобы числа заполняли её по спирали, по часовой стрелке.

Числа должны быть выровнены по правой границе ячейки матрицы.

Используйте mmap для записи в файл.

Можно использовать функции форматного вывода для преобразования числа в строку.

Примеры
Входные данные
N=5, W=5
Результат работы в файле out.txt
    1    2    3    4    5
   16   17   18   19    6
   15   24   25   20    7
   14   23   22   21    8
   13   12   11   10    9
*/


#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>

void Add(char *place, uint32_t number, uint32_t W) {
  char a = place[W];
  sprintf(place, "%*d", W, number);
  place[W] = a;
}

void FillMatrix(uint32_t W, uint32_t N, uint32_t n, uint32_t shift, uint32_t x, char *data) {
  if (n == 1) {
    Add(data + W * (N * shift + shift) + shift, x, W);
  } else if (n == 2) {
    Add(data + W * (N * shift + shift) + shift, x, W);
    Add(data + W * (N * shift + shift + 1) + shift, x + 1, W);
    Add(data + W * (N * (shift + 1) + shift + 1) + 1 + shift, x + 2, W);
    Add(data + W * (N * (shift + 1) + shift) + 1 + shift, x + 3, W);
  } else {
    for (int i = 0; i < n; i++) {
      Add(data + W * (N * shift + shift + i) + shift,
          x + i, W);
    }
    for (int i = 0; i < n - 2; i++) {
      Add(data + W * (N * (shift + 1 + i) + shift + n - 1) + 1 + i + shift,
          x + n + i, W);
    }
    for (int i = 0; i < n; i++) {
      Add(data + W * (N * (shift + n - 1) + shift + i) + n - 1 + shift,
          x + 3 * (n - 1) - i, W);
    }
    for (int i = 0; i < n - 2; i++) {
      Add(data + W * (N * (shift + 1 + i) + shift) + 1 + i + shift,
          x + 4 * (n - 1) - 1 - i, W);
    }
    FillMatrix(W, N, n - 2, shift + 1, x + 4 * (n - 1), data);
  }
}

void Fill(uint32_t N, uint32_t W, char *data) {
  FillMatrix(W, N, N, 0, 1, data);
  for (int i = 0; i < N; i++) {
    data[W * (N * (i + 1)) + i] = '\n';
  }
}

int main(int argc, char *argv[]) {
  int fd = open(argv[1], O_RDWR | O_CREAT, 0640);
  uint32_t N = strtol(argv[2], NULL, 10);
  uint32_t W = strtol(argv[3], NULL, 10);

  ftruncate(fd, (W * N + 1) * N); //обрезать файл, +1 ('\n')
  char *map =
          mmap(NULL, (W * N + 1) * N, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  Fill(N, W, map);
  msync(map, (W * N + 1) * N, MS_SYNC);

  munmap(map, (W * N + 1) * N); /* освободить отображение */
  close(fd);
  return 0;
}