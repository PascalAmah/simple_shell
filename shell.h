#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

int main(void);
void shell_loop(void);
char *read_input(void);
int exec_command(char *cmd);

#endif /* SHELL_H */
