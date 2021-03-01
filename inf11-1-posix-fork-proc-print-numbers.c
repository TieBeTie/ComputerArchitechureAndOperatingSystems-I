/*
Определите экспериментальным способом, какое максимальное колчичество процессов можно запустить с установленными в ejudge лимитами.

Запрещается использовать getrlimit, и другие явные способы определения ограничений.
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  pid_t pid;

  for (int i = 1; i < n; ++i) {
    printf("%d ", i);
    fflush(stdout);

    pid = fork();
    if (pid != 0) {
      int status;
      waitpid(pid, &status, 0);
      return 0;
    }
  }

  printf("%d\n", n);
  return 0;
}