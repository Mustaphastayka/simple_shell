#include "shell.h"

int ShellExit(t__info *info)
{
	int checkext;

	if (info->ArrArg[1])
	{
		checkext = StrToIn2(info->ArrArg[1]);
		if (checkext == -1)
		{
			info->statuus_ = 2;
			ErrorMessPrint(info, "Illegal number: ");
			StrPut(info->ArrArg[1]);
			WrCharC('\n');
			return (1);
		}
		info->number_error = StrToIn2(info->ArrArg[1]);
		return (-2);
	}
	info->number_error = -1;
	return (-2);
}

int ChangeDir(t__info *info)
{
	char *s, *dek, buffer[1024];
	int retchdir;

	s = getcwd(buffer, 1024);
	if (!s)
		InpStrPrint("TODO: >>getcwd failure emsg here<<\n");
	if (!info->ArrArg[1])
	{
		dek = EnvironGet(info, "HOME=");
		if (!dek)
			retchdir =
					chdir((dek = EnvironGet(info, "PWD=")) ? dek : "/");
		else
			retchdir = chdir(dek);
	}
	else if (ComparStr(info->ArrArg[1], "-") == 0)
	{
		if (!EnvironGet(info, "OLDPWD="))
		{
			InpStrPrint(s);
			WrCharPutC('\n');
			return (1);
		}
		InpStrPrint(EnvironGet(info, "OLDPWD=")), WrCharPutC('\n');
		retchdir =
				chdir((dek = EnvironGet(info, "OLDPWD=")) ? dek : "/");
	}
	else
		retchdir = chdir(info->ArrArg[1]);
	if (retchdir == -1)
	{
		ErrorMessPrint(info, "can't cd to ");
		StrPut(info->ArrArg[1]), WrCharC('\n');
	}
	else
	{
		EnvSetNew(info, "OLDPWD", EnvironGet(info, "PWD="));
		EnvSetNew(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

int ChangeHelp(t__info *info)
{
	char **_array;

	_array = info->ArrArg;
	InpStrPrint("help call works. Function not yet implemented \n");
	if (0)
		InpStrPrint(*_array);
	return (0);
}

