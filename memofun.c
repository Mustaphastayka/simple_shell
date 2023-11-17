#include "shell.h"

char *MemoFileC(char *pn, char by, unsigned int byf)
{
	unsigned int i;

	for (i = 0; i < byf; i++)
		pn[i] = by;
	return (pn);
}

void StrFFree(char **sos)
{
	char **a = sos;

	if (!sos)
		return;
	while (*sos)
		free(*sos++);
	free(a);
}

void *RealloBlMem(void *ptrmb, unsigned int o_size, unsigned int n_size)
{
	char *p;

	if (!ptrmb)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptrmb), NULL);
	if (n_size == o_size)
		return (ptrmb);

	p = malloc(n_size);
	if (!p)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		p[o_size] = ((char *)ptrmb)[o_size];
	free(ptrmb);
	return (p);
}
