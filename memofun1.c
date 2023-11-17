#include "shell.h"

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
