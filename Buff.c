#include "shell.h"
/**
 * Chains - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @addpbu: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int Chains(t__info *info, char *buffer, size_t *addpbu)
{
	size_t j = *addpbu;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->BufCmdType = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->BufCmdType = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		info->BufCmdType = CMD_CHAIN;
	}
	else
		return (0);
	*addpbu = j;
	return (1);
}
/**
 * ChainCheck - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buffer: the char buffer
 * @addpbu: address of current position in buf
 * @i: starting position in buf
 * @buflen: length of buf
 *
 * Return: Void
 */
void ChainCheck(t__info *info, char *buffer, size_t *addpbu, size_t i, size_t buflen)
{
	size_t j = *addpbu;

	if (info->BufCmdType == CMD_AND)
	{
		if (info->statuus_)
		{
			buffer[i] = 0;
			j = buflen;
		}
	}
	if (info->BufCmdType == CMD_OR)
	{
		if (!info->statuus_)
		{
			buffer[i] = 0;
			j = buflen;
		}
	}

	*addpbu = j;
}
/**
 * AliasReplac - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int AliasReplac(t__info *info)
{
	int i;
	t__liste *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = NodePrefStart(info->Alias, info->ArrArg[0], '=');
		if (!node)
			return (0);
		free(info->ArrArg[0]);
		p = FoundCharInString(node->str, '=');
		if (!p)
			return (0);
		p = DuplString(p + 1);
		if (!p)
			return (0);
		info->ArrArg[0] = p;
	}
	return (1);
}
/**
 * VarsReplac - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int VarsReplac(t__info *info)
{
	int i = 0;
	t__liste *node;

	for (i = 0; info->ArrArg[i]; i++)
	{
		if (info->ArrArg[i][0] != '$' || !info->ArrArg[i][1])
			continue;

		if (!ComparStr(info->ArrArg[i], "$?"))
		{
			StrReplace(&(info->ArrArg[i]),
								DuplString(NumberConver(info->statuus_, 10, 0)));
			continue;
		}
		if (!ComparStr(info->ArrArg[i], "$$"))
		{
			StrReplace(&(info->ArrArg[i]),
								DuplString(NumberConver(getpid(), 10, 0)));
			continue;
		}
		node = NodePrefStart(info->EnvirList, &info->ArrArg[i][1], '=');
		if (node)
		{
			StrReplace(&(info->ArrArg[i]),
								DuplString(FoundCharInString(node->str, '=') + 1));
			continue;
		}
		StrReplace(&info->ArrArg[i], DuplString(""));
	}
	return (0);
}
/**
 * StrReplace - replaces string
 * @o_str: address of old string
 * @n_str: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int StrReplace(char **o_str, char *n_str)
{
	free(*o_str);
	*o_str = n_str;
	return (1);
}
