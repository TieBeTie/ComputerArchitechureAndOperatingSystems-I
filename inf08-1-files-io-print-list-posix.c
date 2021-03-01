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

Для работы с файлом использовать только низкоуровневый ввод-вывод POSIX.
 */

#include <sys/types.h> // для открытия файла
#include <unistd.h> // для чтения и записи
#include <fcntl.h>
#include <sys/stat.h>

void end(int input, int digits_output, int other_output) {
  close(input);
  close(digits_output);
  close(other_output);
}

int main(int argc, char *argv[]) {
  int input = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

  if (input == -1) {
    end(input, 0, 0);
    return 1;
  }

  int digits_output = open(argv[2], O_WRONLY | O_CREAT, 0640);
  int other_output = open(argv[3], O_WRONLY | O_CREAT, 0640);
  if (digits_output == -1 || other_output == -1) {
    end(input, digits_output, other_output);
    return 2;
  }

  ssize_t count;
  ssize_t digits_count = 0;
  ssize_t other_count = 0;
  char buffer[4096];
  char digits[4096];
  char other[4096];
  while ((count = read(input, &buffer, sizeof(buffer))) > 0) {
    digits_count = 0;
    other_count = 0;
    for (int i = 0; i < count; i++) {
      if ('0' <= buffer[i] && buffer[i] <= '9') {
        digits[digits_count++] = buffer[i];
      } else {
        other[other_count++] = buffer[i];
      }
    }
    if (write(digits_output, &digits, digits_count) == -1) {
      end(input, digits_output, other_output);
      return 3;
    }
    if (write(other_output, &other, other_count) == -1) {
      end(input, digits_output, other_output);
      return 3;
    }
  }

  if (count == -1) {
    end(input, digits_output, other_output);
    return 3;
  }

  end(input, digits_output, other_output);
  return 0;
}
