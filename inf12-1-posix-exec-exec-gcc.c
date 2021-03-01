/*
Программе на стандартном потоке ввода задается выражение в синтаксисе языка Си.

Необходимо вычислить значение этого выражения (итоговый результат представим типом int) и вывести его на стандартный поток вывода.
 */


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
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

  char* code = "#include <stdio.h>\n"
               "int main() { \n"
               "int answer = (%s);\n"
               "printf(\"%%d\\n\", answer); \n"
               "return 0;\n"
               "}\n";

  char program[10000];
  sprintf(program, code, expression);
  int fd = open("TieBeTie.c", O_CREAT | O_TRUNC | O_WRONLY, 0666);
  write(fd, program, strnlen(program, sizeof(program)));
  close(fd);

  pid_t pid = fork();
  if (pid == 0) {
    execlp("gcc", "gcc", "TieBeTie.c", "-o", "TieBeTie", NULL);
    return 0;
  } else {
    int status;
    waitpid(pid, &status, 0);
    execlp("./TieBeTie", "./TieBeTie", NULL);
    exit(1);
  }
  return 0;
}