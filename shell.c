#include "sshell.h"

/**
 * main - A function that shows the point of entry of simple shell execution
 * @ac: Number of arguments passed to program
 * @av: Array of Arguments strings that is passed to the program
 *
 * Return: 0 on success, -1 on failure, Errno is set appropriately
 */
int main(int ac, char **av)
{
	char *lineptr, *path, **path_ev, *x, *y;
	size_t num = 0;
	int count = 0, count_2 = 0, chk, ret = 0, ret_2;
	struct stat st;

	(void) ac;
	x = av[0];
	while (1)
	{
		start_prompt(&lineptr);
		ret = getline(&lineptr, &num, stdin);
		if (ret == -1)
			break;
		ret_2 = 0;
		count = count_tokens(lineptr);
		av = create_token_array(lineptr, count);
		chk = checking_built(av);
		if (chk == 1)
		{
			path = _getenv("PATH");
			count_2 = count_path_tokens(pat);
			path_ev = path_list(path, count_2);
			if (stat(av[0], &st) == 0)
				run_exe(av, path);
			else
			{
				y = make_copy(av[0]);
				av[0] = check_command(av[0], path_ev);
				if (av[0] != NULL)
					run_exe(av, path);
				else
					ret_2 = print_error(x, y, av);
				free(y);
			}
			free_safe_2(path_ev);
		}
		free(lineptr);
	}
	end_prompt(lineptr, ret_2);
	return (0);
}

/**
 * count_tokens - A function that counts the number of tokens in a string
 * @str: A pointer to the string
 *
 * Return: The number of tokens in string
 */
int count_tokens(char *str)
{
	int count = 0;
	char *token, *ptr = NULL;

	if (str == NULL)
		exit(EXIT_FAILURE);

	ptr = make_copy(str);
	token = strtok(ptr, " \t\n");
	if (token == NULL)
	{
		if (*str == '\n' || *str == ' ')
		{
			free(ptr);
			return (1);
		}
	}
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}
	free(ptr);
	return (count);
}

/**
 * create_token_array - A function to creates an array of tokens from a string
 * @str: A pointer to the string
 * @count: Number of tokens in the string
 *
 * Return: POinter to array of tokens created
 */
char **create_token_array(char *str, int count)
{
	char **av =  NULL, *token = NULL, *ptr;
	int a = 0;

	av = malloc(sizeof(char *) * (count + 1));
	if (av == NULL)
	{
		_puts("Unable to allocate memory space");
		exit(EXIT_FAILURE);
	}
	ptr = make_copy(str);
	token = strtok(ptr, " \t\n");
	if (token == NULL)
	{
		if (*str == '\n' || *str == ' ')
		{
			av[a] = "\n";
			av[a + 1] = NULL;
			free(ptr);
			return (av);
		}
	}
	while (token != NULL)
	{
		av[a] = make_copy(token);
		token = strtok(NULL, " \t\n");
		a++;
	}
	av[a] = NULL;
	free(ptr);
	return (av);
}

/**
 * count_path_tokens - A function that counts the number of token,
 * paths in path string
 * @str: A pointer to the string
 *
 * Return: Number of tokens in path string counted
 */
int count_path_tokens(char *str)
{
	int count = 0;
	char *token, *ptr = NULL;

	if (str == NULL)
	{
		_puts("PATH Environment Unavailable");
		exit(EXIT_FAILURE);
	}
	ptr = make_copy(str);
	token = strtok(ptr, "=:\n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, ":\n");
	}
	free(ptr);
	return (count);
}

/**
 * path_list - A function that creates an array of tokens,
 * path string from path environment string
 * @str: A pointer to the string
 * @count: Number of tokens in path
 *
 * Return: Pointer to array of strings in path
 */
char **path_list(char *str, int count)
{
	char **av = NULL, *token = NULL, *ptr;
	int a = 0;

	av = malloc(sizeof(char *) * (count));
	if (av == NULL)
	{
		_puts("Unable to allocate memory space");
		exit(EXIT_FAILURE);
	}
	ptr = make_copy(str);
	token = strtok(ptr, "=:\n");
	token = strtok(NULL, ":\n");
	while (token != NULL)
	{
		av[a] = make_copy(token);
		token = strtok(NULL, ":\n");
		a++;
	}
	av[a] = NULL;
	free(ptr);
	return (av);
}

