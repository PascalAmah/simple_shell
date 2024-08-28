#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - Entry point for the shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	shell_loop();
	return (0);
}

/**
 * shell_loop - Runs the shell loop, reading and executing commands
 */
void shell_loop(void)
{
	char *input;
	int status = 1;

	do {
		printf("$ ");
		fflush(stdout);

		input = read_input();
		if (input == NULL)
		{
			free(input);
			exit(0);
		}

		if (input[0] != '\0')
		{
			status = exec_command(input);
		}

		free(input);
	} while (status);
}

/**
 * read_input - Reads input from stdin
 *
 * Return: The input string
 */
char *read_input(void)
{
	char *input = NULL;
	size_t bufsize = 0;

	if (getline(&input, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(input);
			exit(0);
		}
		else
		{
			perror("read_input");
			free(input);
			exit(EXIT_FAILURE);
		}
	}

	input[strlen(input) - 1] = '\0';
	return (input);
}

/**
 * exec_command - Forks a child process to execute the command
 * @cmd: The command to be executed
 *
 * Return: 1 to continue the loop, 0 to exit
 */
int exec_command(char *cmd)
{
	char *args[2];
	int status;

	args[0] = cmd;
	args[1] = NULL;

	if (fork() == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	return (1);
}
