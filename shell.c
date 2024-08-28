#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/**
 * main - Simple UNIX command line interpreter.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}

			perror("getline");
			continue;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strlen(line) > 0)
			exec_command(line);
	}

	free(line);
	return (0);
}

/**
 * exec_command - Forks a child process to execute the command.
 * @cmd: The command to be executed.
 *
 * Return: 0 on success, -1 on failure.
 */
int exec_command(char *cmd)
{
	char *args[2];
	int status;

	args[0] = cmd;
	args[1] = NULL;

	if (fork() == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	return (0);
}
