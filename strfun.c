#include "shell.h"
/**
 * RetuStrlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int RetuStrlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
/**
 * ComparStr - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
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
/**
 * StartWHay - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *StartWHay(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * StringConc - concatenates two strings
 * @destina: the destination buffer
 * @sourc: the source buffer
 *
 * Return: pointer to destination buffer
 */
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
