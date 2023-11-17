#include "shell.h"

int RetuStrlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

int ComparStr(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

char *StartWHay(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
char *StringConc(char *destina, char *sourc)
{
	char *ret = destina;

	while (*destina)
		destina++;
	while (*sourc)
		*destina++ = *sourc++;
	*destina = *sourc;
	return (ret);
}
