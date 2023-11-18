#include "shell.h"
/**
 * main - entry point
 * @arc: arg count
 * @arv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arc, char **arv)
{
	t__info info[] = {INFO_INIT};
	int fd = 2;

	asm("mov %1, %0\n\t"
			"add $3, %0"
			: "=r"(fd)
			: "r"(fd));

	if (arc == 2)
	{
		fd = open(arv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				StrPut(arv[0]);
				StrPut(": 0: Can't open ");
				StrPut(arv[1]);
				WrCharC('\n');
				WrCharC(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->FdReadinp = fd;
	}
	EnvLinkedList(info);
	HistoryRead(info);
	hsh(info, arv);
	return (EXIT_SUCCESS);
}
