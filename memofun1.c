#include "shell.h"
/**
 * PoinFree - frees a pointer and NULLs the address
 * @pntfree: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int PoinFree(void **pntfree)
{
	if (pntfree && *pntfree)
	{
		free(*pntfree);
		*pntfree = NULL;
		return (1);
	}
	return (0);
}
