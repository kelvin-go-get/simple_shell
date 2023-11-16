#include "shell.h"

/**
 * main - the starting line
 * @cntarg: counts of argument passed
 * @vctarg: vector of argument
 *
 * Return: 1 (Error) or 0 (Success)
 */
int main(int cntarg, char **vctarg)
{
	int xc;
	info_t noti[] = { NOTI_INIT };

	xc = 2;
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (xc)
		: "r" (xc));

	if (cntarg == 2)
	{
		xc = open(vctarg[1], O_RDONLY);
		if (xc == -1)
		{
			if (errno == ENOENT)
			{
				_errp(vctarg[0]);
				_errp(": 0: Can't open ");
				_errp(vctarg[1]);
				_errptch('\n');
				_errptch(FLS_BFR);
				exit(127);
			}
			if (errno == EACCES)
				exit(126);

			return (EXIT_FAILURE);
		}
		noti->readfd = xc;
	}
	_envlt(noti);
	_thrpast(noti);
	_mnshl(noti, vctarg);

	return (EXIT_SUCCESS);
}
