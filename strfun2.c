#include "shell.h"
/**
 **CopyString - copies a string
 *@destina: the destination string to be copied to
 *@sourc: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *CopyString(char *destina, char *sourc, int n)
{
	int i, j;
	char *s = destina;

	i = 0;
	while (sourc[i] != '\0' && i < n - 1)
	{
		destina[i] = sourc[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destina[j] = '\0';
			j++;
		}
	}
	return (s);
}
/**
 **Con2String - concatenates two strings
 *@destina: the first string
 *@sourc: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *Con2String(char *destina, char *sourc, int n)
{
	int i, j;
	char *s = destina;

	i = 0;
	j = 0;
	while (destina[i] != '\0')
		i++;
	while (sourc[j] != '\0' && j < n)
	{
		destina[i] = sourc[j];
		i++;
		j++;
	}
	if (j < n)
		destina[i] = '\0';
	return (s);
}
/**
 **FoundCharInString - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *FoundCharInString(char *s, char c)
{
	do	{
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
