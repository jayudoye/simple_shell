#include "sshell.h"
#include "stdio.h"
/**
 * print_number - It prints an integer n
 *@n: integer to be printed
 */
void print_number(int n)
{
	unsigned int j1;

	if (n < 0)
	{
		j1 = -n;
		_putchar('-');
	}
	else
	{
		j1 = n;
	}
	if (j1 / 10)
		print_number(j1 / 10);
	_putchar((j1 % 10) + '0');
}
