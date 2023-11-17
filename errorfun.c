#include "shell.h"

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
