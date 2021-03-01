/*
Программе в аргументах командной строки передаются три имени файла. Первый аргумент - входной файл, два остальных - выходные.

Реализуйте программу, которая читает символы из первого файла, во второй файл записывает только цифры, а в третий - всё остальное.

Разрешается использовать только низкоуровневый ввод-вывод POSIX.

Если входной файл не существует, то нужно завершить работу с кодом 1.

Если не возможно создать один из выходных файлов, то завершить работу с кодом 2.

При возникновении других ошибок ввода-вывода - завершить работу с кодом 3.
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