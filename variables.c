#include "shell.h"

/**
 * _bfrchn - checking to see if the character in buffer
 * @noti: structure
 * @bfr: the buffer's character
 * @p: buffer's address
 *
 * Return: 1 (Success), or 0 (Otherwise)
 * Authors: Kelvin Njuiri and Bismark Kete
 */
int _bfrchn(info_t *noti, char *bfr, size_t *p)
{
	size_t pos = *p;

	if (bfr[pos + 1] == '|' && bfr[pos] == '|')
	{
		bfr[pos] = 0;
		pos++;
		noti->cmd_buf_type = COMMAND_R;
	}
	else if (bfr[pos] == ';')
	{
		bfr[pos] = 0;
		noti->cmd_buf_type = COMMAND_C;
	}
	else if (bfr[pos + 1] == '&' && bfr[pos] == '&')
	{
		bfr[pos] = 0;
		pos++;
		noti->cmd_buf_type = COMMAND_A;
	}
	else
		return (0);
	*p = pos;
	return (1);
}

/**
 * cnt_chn - function that tests to see if we should chain continuously
 * @noti: structure
 * @bfr: character's buffer
 * @p: active address
 * @j: beginning
 * @lngth: buffer's length
 * Return: nothing
 */
void cnt_chn(info_t *noti, char *bfr, size_t *p, size_t j, size_t lngth)
{
	size_t pos = *p;

	if (noti->cmd_buf_type == COMMAND_A)
	{
		if (noti->status)
		{
			bfr[j] = 0;
			pos = lngth;
		}
	}
	if (noti->cmd_buf_type == COMMAND_R)
	{
		if (!noti->status)
		{
			bfr[j] = 0;
			pos = lngth;
		}
	}

	*p = pos;
}

/**
 * _rp_alsknw - function that replaces strings
 * @noti: structure
 *
 * Return: 1 (Success), 0 (Otherwise)
 */
int _rp_alsknw(info_t *noti)
{
	char *p;
	int index;
	list_t *n;

	for (index = 0; index < 10; index++)
	{
		n = _ndstw(noti->alias, noti->argv[0], '=');
		if (!n)
			return (0);
		free(noti->argv[0]);
		p = _fndch(n->str, '=');
		if (!p)
			return (0);
		p = _mulst(p + 1);
		if (!p)
			return (0);
		noti->argv[0] = p;
	}
	return (1);
}

/**
 * _rplv - changes the variables in a string(token)
 * @noti: structure
 * Return: 1 on success, 0 (Otherwise)
 */
int _rplv(info_t *noti)
{
	int index;
	list_t *n;

	index = 0;
	for (index = 0; noti->argv[index]; index++)
	{
		if (!noti->argv[index][1] || noti->argv[index][0] != '$')
			continue;

		if (!_compstr(noti->argv[index], "$$"))
		{
			_rpstr(&(noti->argv[index]),
				_mulst(cnvntoa(getpid(), 10, 0)));
			continue;
		}
		if (!_compstr(noti->argv[index], "$?"))
		{
			_rpstr(&(noti->argv[index]),
				_mulst(cnvntoa(noti->status, 10, 0)));
			continue;
		}
		n = _ndstw(noti->env, &noti->argv[index][1], '=');
		if (n)
		{
			_rpstr(&(noti->argv[index]),
				_mulst(_fndch(n->str, '=') + 1));
			continue;
		}
		_rpstr(&noti->argv[index], _mulst(""));

	}
	return (0);
}

/**
 * _rpstr - modifies a string
 * @last: initial
 * @recent: final
 *
 * Return: 1 on success, 0 on failure
 */
int _rpstr(char **last, char *recent)
{
	free(*last);
	*last = recent;
	return (1);
}
