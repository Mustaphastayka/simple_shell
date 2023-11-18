#include "shell.h"
/**
 * CpString - copies a string
 * @destina: the destination
 * @sourc: the source
 *
 * Return: pointer to destination
 */
char *CpString(char *destina, char *sourc)
{
	int i = 0;

	if (destina == sourc || sourc == 0)
		return (destina);
	while (sourc[i])
	{
		destina[i] = sourc[i];
		i++;
	}
	destina[i] = 0;
	return (destina);
}
/**
 * DuplString - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *DuplString(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
/**
 *InpStrPrint - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void InpStrPrint(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		WrCharPutC(str[i]);
		i++;
	}
}
/**
 * WrCharPutC - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int WrCharPutC(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
