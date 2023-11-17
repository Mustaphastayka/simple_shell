#include "shell.h"

int StrToIn2(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

void ErrorMessPrint(t__info *info, char *errorstr)
{
	StrPut(info->NameFile);
	StrPut(": ");
	DecNumPrint(info->countofline, STDERR_FILENO);
	StrPut(": ");
	StrPut(info->ArrArg[0]);
	StrPut(": ");
	StrPut(errorstr);
}

int DecNumPrint(int input, int filedes)
{
	int (*_WrCharPutC)(char) = WrCharPutC;
	int i, count = 0;
	unsigned int _abs_, current;

	if (filedes == STDERR_FILENO)
		_WrCharPutC = WrCharC;
	if (input < 0)
	{
		_abs_ = -input;
		_WrCharPutC('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_WrCharPutC('0' + current / i);
			count++;
		}
		current %= i;
	}
	_WrCharPutC('0' + current);
	count++;

	return (count);
}

char *NumberConver(long int number, int basee, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flag & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % basee];
		n /= basee;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

void CommRemover(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
