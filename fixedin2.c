#include "shell.h"

/**
 * _shwhstry - prints out the past commands
 * @noti: structure
 *  Return: Always 0 (Success)
 *	Authors: Kelvin Njuir and Bismark Kwaku
 */
int _shwhstry(info_t *noti)
{
	_lsprnt(noti->history);
	return (0);
}

/**
 * _rm_alsknw - creates another name for a string
 * @noti: structure
 * @s: string
 * Return: 1 (Error) and 0 (Success)
 */
int _rm_alsknw(info_t *noti, char *s)
{
	int brn;
	char *ptr, ch;

	ptr = _fndch(s, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	brn = _rmnd(&(noti->alias),
		_gni(noti->alias, _ndstw(noti->alias, s, -1)));
	*ptr = ch;

	return (brn);
}

/**
 * _crt_alsknw - creates another name for a string
 * @noti: structure
 * @s: string alias
 *
 * Return: 1 (Error) and 0 (Success)
 */
int _crt_alsknw(info_t *noti, char *s)
{
	char *ptr;

	ptr = _fndch(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (_rm_alsknw(noti, s));

	_rm_alsknw(noti, s);

	return (_down_ad(&(noti->alias), s, 0) == NULL);
}

/**
 * out_alsknw - ouputs the other name for a string
 * @nd: node
 *
 * Return: 1 (Error) and 0 (Success)
 */
int out_alsknw(list_t *nd)
{
	char *f = NULL, *ptr = NULL;

	if (nd)
	{
		ptr = _fndch(nd->str, '=');
		for (f = nd->str; f <= ptr; f++)
			_chprnt(*f);

		_chprnt('\'');
		_prnt(ptr + 1);
		_prnt("'\n");
		return (0);
	}

	return (1);
}

/**
 * _alsknw - imitates the default alias
 * @noti: structure
 *  Return: Always 0 (Success)
 */
int _alsknw(info_t *noti)
{
	list_t *nd;
	int index;
	char *ptr = NULL;

	index = 0;
	if (noti->argc == 1)
	{
		nd = noti->alias;
		while (nd)
		{
			out_alsknw(nd);
			nd = nd->next;
		}

		return (0);
	}
	for (index = 1; noti->argv[index]; index++)
	{
		ptr = _fndch(noti->argv[index], '=');
		if (ptr)
			_crt_alsknw(noti, noti->argv[index]);
		else
			out_alsknw(_ndstw(noti->alias, noti->argv[index], '='));
	}

	return (0);
}
