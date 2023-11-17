#include "shell.h"

t__liste *StartAddNote(t__liste **header, const char *str, int number)
{
	t__liste *new_header;

	if (!header)
		return (NULL);
	new_header = malloc(sizeof(t__liste));
	if (!new_header)
		return (NULL);
	MemoFileC((void *)new_header, 0, sizeof(t__liste));
	new_header->number = number;
	if (str)
	{
		new_header->str = DuplString(str);
		if (!new_header->str)
		{
			free(new_header);
			return (NULL);
		}
	}
	new_header->next_node = *header;
	*header = new_header;
	return (new_header);
}

t__liste *EndAddNote(t__liste **header, const char *str, int number)
{
	t__liste *new_node, *node;

	if (!header)
		return (NULL);

	node = *header;
	new_node = malloc(sizeof(t__liste));
	if (!new_node)
		return (NULL);
	MemoFileC((void *)new_node, 0, sizeof(t__liste));
	new_node->number = number;
	if (str)
	{
		new_node->str = DuplString(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next_node)
			node = node->next_node;
		node->next_node = new_node;
	}
	else
		*header = new_node;
	return (new_node);
}

size_t StringListPrintOnly(const t__liste *pnfn)
{
	size_t i = 0;

	while (pnfn)
	{
		InpStrPrint(pnfn->str ? pnfn->str : "(nil)");
		InpStrPrint("\n");
		pnfn = pnfn->next_node;
		i++;
	}
	return (i);
}

int NodeIndexDeleted(t__liste **header, unsigned int index)
{
	t__liste *node, *prev_node;
	unsigned int i = 0;

	if (!header || !*header)
		return (0);

	if (!index)
	{
		node = *header;
		*header = (*header)->next_node;
		free(node->str);
		free(node);
		return (1);
	}
	node = *header;
	while (node)
	{
		if (i == index)
		{
			prev_node->next_node = node->next_node;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next_node;
	}
	return (0);
}

void FreesLists(t__liste **header_ptr)
{
	t__liste *node, *next_node, *head;

	if (!header_ptr || !*header_ptr)
		return;
	head = *header_ptr;
	node = head;
	while (node)
	{
		next_node = node->next_node;
		free(node->str);
		free(node);
		node = next_node;
	}
	*header_ptr = NULL;
}
