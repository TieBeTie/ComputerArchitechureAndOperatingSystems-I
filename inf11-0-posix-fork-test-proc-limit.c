/*
Определите экспериментальным способом, какое максимальное колчичество процессов можно запустить с установленными в ejudge лимитами.

Запрещается использовать getrlimit, и другие явные способы определения ограничений.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sched.h>

int main() {
  int i = 1;
  pid_t pid = 8;
  while (pid != -1) {
    pid = fork();
    if (pid != -1) {
      i++;
    }
    if (pid != 0 && pid != -1) {
      int status;
      waitpid(pid, &status, 0);
      return 0;
    }
  }
  printf("%d", i);
}