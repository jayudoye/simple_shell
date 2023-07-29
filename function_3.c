#include "sshell.h"

/**
 * run_exe - A function that executes the command passed in
 * @av: A pointer to the array of commands and arguments
 * @path: Pointer to path string
 */
void run_exe(char **av, char *path)
{
	char *env[2];
	int wstat;
	pid_t yl;

	env[0] = path;
	env[1] = NULL;
	yl = fork();
	if (yl == -1)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	if (yl == 0)
	{
		if (execve(av[0], av, env) == -1)
			perror("Error:");
	}
	else
	{
		wait(&wstat);
		free_safe_2(av);
	}
}

/**
 * check_command - A function that checks if a string is a command
 * in PATH executables
 * @cmd: A command string to check
 * @paths: Array of strings in environment path variable
 *
 * Return: path of command string
 */
char *check_command(char *cmd, char **paths)
{
	struct stat jt;
	char *full_path;
	int x, y, z = 0;

	while (paths[z] != NULL)
	{
		full_path = NULL;
		x = _strlen(cmd);
		y = _strlen(paths[z]);
		full_path = make_full_path(paths[z], cmd, x, y);
		if (stat(full_path, &jt) == 0)
		{
			free(cmd);
			return (full_path);
		}
		z++;
		free(full_path);
	}
	free(cmd);
	return (NULL);
}

/**
 * make_full_path - A function that appends a command to path string
 * @a: A pointer to the path string
 * @b: A pointer to the command
 * @c: length of command string
 * @d: leanth of pth string
 *
 * Return: A pointer to the appended full path string
 */
char *make_full_path(char *a, char *b, int c, int d)
{
	char *ptr = NULL;
	int x, y;

	ptr = malloc(sizeof(char) * c + d + 2);
	if (ptr == NULL)
		exit(EXIT_FAILURE);
	for (x = 0; a[x]; x++)
		ptr[x] = a[x];
	ptr[x++] = '/';
	for (y = 0; b[y]; x++, y++)
		ptr[x] = b[y];
	ptr[x] = '\0';
	return (ptr);
}

/**
 * _getenv - A function that checks to find specific environment variable
 * @name: Path variable to get
 *
 * Return: Path environment variable
 */
char *_getenv(const char *name)
{
	int len = 0, ret = 0;

	len = _strlen(name);
	ret  = find_var(name, len);
	if (ret >= 0)
		return (environ[ret]);
	return (NULL);
}

/**
 * find_var - A function that compares word search with environment variables
 * @name: Path environment name
 * @len: length of path name
 *
 * Return: Position of path in environment variable list
 */
int find_var(const char *name, int len)
{
	int x = 0, y = 0, z = 0, diff;

	while (environ[x])
	{
		while (environ[x][y] && name[z] && (y < len))
		{
			diff = environ[x][y] - name[z];
			if (diff != 0)
				break;
			y++;
			z++;
		}
		if (diff == 0)
			return (x);
		x++;
	}
	return (-1);
}
