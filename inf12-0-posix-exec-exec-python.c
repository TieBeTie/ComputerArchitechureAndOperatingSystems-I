/*
Программе на стандартный поток ввода задается некоторое арифметическое выражение в синтаксисе языка python3.

Необходимо вычислисть это выражение, и вывести результат.

Использовать дополнительные процессы запрещено.
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
  char expression[10000];
  fgets(expression, sizeof(expression), stdin);
  char* slash_place = strchr(expression, '\n');
  if (slash_place) {
    *slash_place = '\0';
  }
  if (strnlen(expression, sizeof(expression)) == 0) {
    return 0;
  }

  char program[10000];
  snprintf(
          program, sizeof(program), "answer = %s; print(answer)", expression);
  execlp("python3", "python3", "-c", program, NULL);
  perror("exec");
  return 1;
}