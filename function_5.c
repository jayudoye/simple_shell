#include "sshell.h"

/**
 * start_prompt - A function that starts the shell prompt
 * @s: Pointer to get line input
 */
void start_prompt(char **s)
{
	*s = NULL;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * print_error - A function that prints error message if command is unrecgnised
 * @pg: The program name
 * @cmd: The command typed
 * @av: An array of command arguments
 *
 * Return: Always return an integer
 */
int print_error(char *pg, char *cmd, char **av)
{
	static int a = 1;

	_puts2(pg);
	_puts2(": ");
	print_number(a);
	_puts2(": ");
	_puts2(cmd);
	_puts2(": not found");
	_putchar('\n');
	a++;
	free_safe_2(av);
	return (127);
}

/**
 * _puts2 - A function that prints inputed string to stdout without a newline
 * @str: The string to be printed
 */
void _puts2(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
}

/**
 * end_prompt - A function that ends shell prompt
 * @p: A pointer to line input string
 * @q: var to take value of exit
 */
void end_prompt(char *p, int q)
{
	free(p);
	if (isatty(STDIN_FILENO))
		_putchar('\n');
	if (q == 127)
		exit(127);
}

/**
 * _atoi - A function that converts an integar string into an integar
 * @s: Integer string to be converted
 *
 * Return: 0 if no integer string found else, return integer number
 */
int _atoi(char *s)
{
	int sign = 1, num_end = 0;
	unsigned int result = 0;

	while (*s != '\0')
	{
		if (*s == '-')
			sign *= -1;

		if (*s >= '0' && *s <= '9')
		{
			num_end = 1;
			result = result * 10 + *s - '0';
		}
		else if (num_end)
			break;
		s++;
	}

	if (sign < 0)
		result = (-result);

	return (result);
}
