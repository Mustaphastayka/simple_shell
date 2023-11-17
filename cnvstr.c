#include "shell.h"

int ModeIntera(t__info *info)
{
	return (isatty(STDIN_FILENO) && info->FdReadinp <= 2);
}

int DelimCheck(char ch, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == ch)
			return (1);
	return (0);
}


int AlphaCheck(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

int StrToIn(char *strconv)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; strconv[i] != '\0' && flag != 2; i++)
	{
		if (strconv[i] == '-')
			sign *= -1;

		if (strconv[i] >= '0' && strconv[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (strconv[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
