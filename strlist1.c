#include "shell.h"
/**
 * LengthLists - determines length of linked list
 * @pnfn: pointer to first node
 *
 * Return: size of list
 */
size_t LengthLists(const t__liste *pnfn)
{
	size_t i = 0;

	while (pnfn)
	{
		pnfn = pnfn->next_node;
		i++;
	}
	return (i);
}
/**
 * AListeToStr - returns an array of strings of the list->str
 * @pnfna: pointer to first node
 *
 * Return: array of strings
 */
char **AListeToStr(t__liste *pnfna)
{
	t__liste *node = pnfna;
	size_t i = LengthLists(pnfna), j;
	char **strs;
	char *str;

	if (!pnfna || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next_node, i++)
	{
		str = malloc(RetuStrlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = CpString(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * PrintListsCon - prints all elements of a list_t linked list
 * @pnfn: pointer to first node
 *
 * Return: size of list
 */
size_t PrintListsCon(const t__liste *pnfn)
{
	size_t i = 0;

	while (pnfn)
	{
		InpStrPrint(NumberConver(pnfn->number, 10, 0));
		WrCharPutC(':');
		WrCharPutC(' ');
		InpStrPrint(pnfn->str ? pnfn->str : "(nil)");
		InpStrPrint("\n");
		pnfn = pnfn->next_node;
		i++;
	}
	return (i);
}
/**
 * NodePrefStart - returns node whose string starts with prefix
 * @potolh: pointer to list head
 * @strtm: string to match
 * @nch: the next character after prefix to match
 *
 * Return: match node or null
 */
t__liste *NodePrefStart(t__liste *potolh, char *strtm, char nch)
{
	char *p = NULL;

	while (potolh)
	{
		p = StartWHay(potolh->str, strtm);
		if (p && ((nch == -1) || (*p == nch)))
			return (potolh);
		potolh = potolh->next_node;
	}
	return (NULL);
}
/**
 * IndexNodeGet - gets the index of a node
 * @header: pointer to list head
 * @ptnode: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t IndexNodeGet(t__liste *header, t__liste *ptnode)
{
	size_t i = 0;

	while (header)
	{
		if (header == ptnode)
			return (i);
		header = header->next_node;
		i++;
	}
	return (-1);
}
