#define _POSIX_SOURCE
#include "shell_truby.h"

// определяет терминал

int main() {
  char *ret, tty[40];

  if ((ret = ttyname(STDIN_FILENO)) == NULL)
    perror("ttyname() error");
  else {
    printf("The ttyname asSsociated with my stdin is %s\n", ret);
  }
}