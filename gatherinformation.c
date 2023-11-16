#include "shell.h"

/**
 * _inistrt - initiates structs
 * @noti: location or address of the structure
 * Authors: Kelvin Njuir and Bismark Kete
 */
void _inistrt(info_t *noti)
{
	noti->arg = NULL;
	noti->argv = NULL;
	noti->path = NULL;
	noti->argc = 0;
}

/**
 * _s_strt - sets structure
 * @noti: structure
 * @arg_vct: other argv
 */
void _s_strt(info_t *noti, char **arg_vct)
{
	int index;

	index = 0;
	noti->fname = arg_vct[0];
	if (noti->arg)
	{
		noti->argv = _dvst(noti->arg, " \t");
		if (!noti->argv)
		{
			noti->argv = malloc(2 * sizeof(char *));
			if (noti->argv)
			{
				noti->argv[0] = _mulst(noti->arg);
				noti->argv[1] = NULL;
			}
		}
		for (index = 0; noti->argv && noti->argv[index]; index++)
			;
		noti->argc = index;

		_rp_alsknw(noti);
		_rplv(noti);
	}
}

/**
 * _fr_strt - frees structure
 * @noti: structure
 * @every: fields
 */
void _fr_strt(info_t *noti, int every)
{
	set_fr(noti->argv);
	noti->argv = NULL;
	noti->path = NULL;
	if (every)
	{
		if (!noti->cmd_buf)
			free(noti->arg);
		if (noti->env)
			_allwlt(&(noti->env));
		if (noti->history)
			_allwlt(&(noti->history));
		if (noti->alias)
			_allwlt(&(noti->alias));
		set_fr(noti->environ);
			noti->environ = NULL;
		fr_mem((void **)noti->cmd_buf);
		if (noti->readfd > 2)
			close(noti->readfd);
		_chprnt(FLS_BFR);
	}
}
