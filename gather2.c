#include "shell.h"

/**
 * _bfrch - commands
 * @noti: structure
 * @bfr: buffer
 * @dist: variable's longitude's pointer
 * Return: size
 * Author: Kelvin Njuiri and Bismark Kete
 */
ssize_t _bfrch(info_t *noti, char **bfr, size_t *dist)
{
	size_t dist_p = 0;
	ssize_t x = 0;

	if (!*dist)
	{
		free(*bfr);
		*bfr = NULL;
		signal(SIGINT, _manipulator);
#if FNC_GT
		x = _brnln(bfr, &dist_p, stdin);
#else
		x = _brnln(noti, bfr, &dist_p);
#endif
		if (x > 0)
		{
			if ((*bfr)[x - 1] == '\n')
			{
				(*bfr)[x - 1] = '\0';
				x--;
			}
			noti->linecount_flag = 1;
			_igncmt(*bfr);
			_fnlspast(noti, *bfr, noti->histcount++);
			{
				*dist = x;
				noti->cmd_buf = bfr;
			}
		}
	}
	return (x);
}

/**
 * _gtentered - gets a line minus the newline
 * @noti: structure
 * Return: size
 */
ssize_t _gtentered(info_t *noti)
{
	char *ptr, **bfr_ptr = &(noti->arg);
	static char *bfr;
	ssize_t x = 0;
	static size_t index, index2, dist;

	_chprnt(FLS_BFR);
	x = _bfrch(noti, &bfr, &dist);
	if (x == -1)
		return (-1);
	if (dist)
	{
		index2 = index;
		ptr = bfr + index;

		cnt_chn(noti, bfr, &index2, index, dist);
		while (index2 < dist)
		{
			if (_bfrchn(noti, bfr, &index2))
				break;
			index2++;
		}

		index = index2 + 1;
		if (index >= dist)
		{
			index = dist = 0;
			noti->cmd_buf_type = CMD_NORM;
		}

		*bfr_ptr = ptr;
		return (_lngthstr(ptr));
	}

	*bfr_ptr = bfr;
	return (x);
}

/**
 * _bfrout - displays the contents of the buffer
 * @noti: structure
 * @bfr: buffer
 * @sz: size
 * Return: x
 */
ssize_t _bfrout(info_t *noti, char *bfr, size_t *sz)
{
	ssize_t x;

	x = 0;
	if (*sz)
		return (0);
	x = read(noti->readfd, bfr, BFR_SZ_DSP);
	if (x >= 0)
		*sz = x;
	return (x);
}

/**
 * _brnln - takes the next line of input
 * @noti: structure
 * @p: buffer's pointer
 * @dist: pointer of size
 * Return: sz
 */
int _brnln(info_t *noti, char **p, size_t *dist)
{
	size_t m;
	static char bfr[BFR_SZ_DSP];
	char *fresh_ptr = NULL, *ptr = NULL, *clm;
	static size_t j, dt;
	ssize_t x = 0, st = 0;

	ptr = *p;
	if (dist && ptr)
		st = *dist;
	if (dt == j)
		j = dt = 0;

	x = _bfrout(noti, bfr, &dt);
	if ((x == 0 && dt == 0) || x == -1)
		return (-1);

	clm = _fndch(bfr + j, '\n');
	m = clm ? 1 + (unsigned int)(clm - bfr) : dt;
	fresh_ptr = r_alc(ptr, st, st ? st + m : m + 1);
	if (!fresh_ptr)
		return (ptr ? free(ptr), -1 : -1);

	if (st)
		_cnstr(fresh_ptr, bfr + j, m - j);
	else
		_cpstr(fresh_ptr, bfr + j, m - j + 1);

	st += m - j;
	j = m;
	ptr = fresh_ptr;

	if (dist)
		*dist = st;
	*p = ptr;
	return (st);
}

/**
 * _manipulator - makes the key combination(Ctrl + C) not to work
 * @_rep: number
 * Return: nothing
 */
void _manipulator(__attribute__((unused))int _rep)
{
	_prnt("\n");
	_prnt("$ ");
	_chprnt(FLS_BFR);
}
