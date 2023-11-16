#include "shell.h"

/**
 * _envg - function that returns the string copied in our environment
 * @noti: structure
 * Return: Always 0 (Success)
 * Authors: Kelvin Njuiri and Bismark Kete
 */
char **_envg(info_t *noti)
{
	if (!noti->environ || noti->env_changed)
	{
		noti->environ = _strlt(noti->env);
		noti->env_changed = 0;
	}

	return (noti->environ);
}

/**
 * _usenv - displaces a variable of an environment
 * @noti: structure
 * @kw: variable
 *  Return: 1 (Success) or 0 (Otherwise)
 */
int _usenv(info_t *noti, char *kw)
{
	char *ptr;
	size_t index;
	list_t *n = noti->env;

	index = 0;
	if (!kw || !n)
		return (0);

	while (n)
	{
		ptr = _wtstr(n->str, kw);
		if (ptr && *ptr == '=')
		{
			noti->env_changed = _rmnd(&(noti->env), index);
			index = 0;
			n = noti->env;
			continue;
		}
		n = n->next;
		index++;
	}
	return (noti->env_changed);
}

/**
 * _senv - modify a new environment variable or make a new one
 * @noti: structure
 * @equi: variable's value
 * @kw: variable
 *  Return: Always 0 (Success)
 */
int _senv(info_t *noti, char *kw, char *equi)
{
	char *ptr;
	list_t *n = NULL;
	char *bfr = NULL;

	if (!equi || !kw)
		return (0);

	bfr = malloc(_lngthstr(kw) + _lngthstr(equi) + 2);
	if (!bfr)
		return (1);
	_cpst(bfr, kw);
	_strcnct(bfr, "=");
	_strcnct(bfr, equi);
	n = noti->env;
	while (n)
	{
		ptr = _wtstr(n->str, kw);
		if (ptr && *ptr == '=')
		{
			free(n->str);
			n->str = bfr;
			noti->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	_down_ad(&(noti->env), bfr, 0);
	free(bfr);
	noti->env_changed = 1;

	return (0);
}
