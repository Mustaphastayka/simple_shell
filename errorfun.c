#include "shell.h"
/**
 *StrPut - prints an input string
 * @strprt: the string to be printed
 *
 * Return: Nothing
 */
void StrPut(char *strprt)
{
	int i = 0;

	if (!strprt)
		return;
	while (strprt[i] != '\0')
	{
		WrCharC(strprt[i]);
		i++;
	}
}
/**
 * WrCharC - writes the character c to stderr
 * @cht: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int WrCharC(char cht)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cht == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (cht != BUF_FLUSH)
		buf[i++] = cht;
	return (1);
}
/**
 * WrCharCtoFD - writes the character c to given fd
 * @cht: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int WrCharCtoFD(char cht, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cht == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (cht != BUF_FLUSH)
		buf[i++] = cht;
	return (1);
}
/**
 *StrPrint - prints an input string
 * @strprt: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int StrPrint(char *strprt, int fd)
{
	int i = 0;

	if (!strprt)
		return (0);
	while (*strprt)
	{
		i += WrCharCtoFD(*strprt++, fd);
	}
	return (i);
}
