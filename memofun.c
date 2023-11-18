#include "shell.h"
/**
 **MemoFileC - fills memory with a constant byte
 *@pn: the pointer to the memory area
 *@by: the byte to fill *s with
 *@byf: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *MemoFileC(char *pn, char by, unsigned int byf)
{
	unsigned int i;

	for (i = 0; i < byf; i++)
		pn[i] = by;
	return (pn);
}
/**
 * StrFFree - frees a string of strings
 * @sos: string of strings
 */
void StrFFree(char **sos)
{
	char **a = sos;

	if (!sos)
		return;
	while (*sos)
		free(*sos++);
	free(a);
}
/**
 * RealloBlMem - reallocates a block of memory
 * @ptrmb: pointer to previous malloc'ated block
 * @o_size: byte size of previous block
 * @n_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
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
