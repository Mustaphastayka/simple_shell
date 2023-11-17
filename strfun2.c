#include "shell.h"
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

char *FoundCharInString(char *s, char c)
{
	do	{
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
