#include "sshell.h"
#include "stdio.h"
/**
 * _strlen - This is a function that determines the length of input string
 * @s: It address og string to be measured
 *
 * Return: Length of string
 */
int _strlen(const char *s)
{
	int a = 0;

	while (s[a] != '\0')
		a++;
	return (a);
}
/**
 * _putchar - The character c is being statedto stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _puts - This function prints inputed string to stdout
 * @str: String to to printed
 */
void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
	_putchar('\n');
}
/**
 * _strdup - The value of a string is being copied
 * to a newly allocated memory space
 * @str: Pointer to  string to be copied
 *
 * Return: Pointer to new duplicate string, NULL if failed to create space
 */
char *_strdup(char *str)
{
	char *ptr;
	int a, len = 0;

	if (str == NULL)
		return (NULL);
	while (*(str + len))
		len++;
	ptr = malloc((len + 1) * sizeof(*ptr));
	if (ptr == NULL)
		return (NULL);
	for (a = 0; a < len; a++)
		*(ptr + a) = *(str + a);
	*(ptr + a) = '\0';
	return (ptr);
}
/**
 * make_copy - This function make a copy of string passed into it
 * @str: Pointer to string to be copied
 *
 * Return: Pointer to address of the copy if succesful
 */
char *make_copy(char *str)
{
	char *ptr = NULL;

	ptr = _strdup(str);

	if (ptr == NULL)
	{
		_puts("Unable to allocate duplicate string");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
