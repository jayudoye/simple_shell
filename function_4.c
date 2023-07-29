#include "sshell.h"
#include "stdio.h"
/**
 * checking_built - This function help to check command passed
 * for special buitlins commands
 * @arr: Pointer to commands & arguments passed
 *
 * Return: 0 if command find succesful, -1 if failed
 */
int checking_built(char **arr)
{
	int a, k, len_input;
	builtins_f check[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"\n", print_newprompt},
		{NULL, NULL}
	};
	a = k = 0;
	for (len_input = 0; arr[0][len_input] != '\0'; len_input++)
		;
	while (check[a].command != NULL)
	{
		k = 0;
		while (k < len_input)
		{
			if (check[a].command[k] != arr[0][k])
				break;
			k++;
		}
		if (check[a].command[k] == arr[0][k])
		{
			check[a].ptr(arr);
			return (0);
		}
		a++;
	}
	/*free_safe_2(arr);*/
	return (1);
}
/**
 * exit_shell - The command help to exits the shell upon exit command
 * @arr: Pointer to command & arguments passed
 */
void exit_shell(char **arr)
{
	int num = 0;

	if (arr[1]  == NULL)
	{
		free_safe_2(arr);
		exit(EXIT_SUCCESS);
	}
	num = _atoi(arr[1]);
	free_safe_2(arr);
	exit(num);
}
/**
 * print_env - This function prints enviroment variables upon "env" command
 * @arr: Pointer to command & arguments passed
 */
void print_env(char **arr)
{
	int a = 0;
	(void)arr;
	while (environ[a])
	{
		_puts(environ[a]);
		a++;
	}
	free_safe_2(arr);
}
/**
 * print_newprompt - This function prints a new shell prompt
 * @arr: It points to array of string
 */
void print_newprompt(char **arr)
{
	free(arr);
}
/**
 * free_safe_2 - This is the free array of malloc'd spaces
 * @pointer: It points to the array of malloc'd spaces
 */
void free_safe_2(char **pointer)
{
	int a = 0;

	if (pointer != NULL)
	{
		while (pointer[a] != NULL)
		{
			free(pointer[a]);
			a++;
		}
		free(pointer[a]);
		free(pointer);
		pointer = NULL;
	}
}
