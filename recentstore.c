#include "shell.h"

/**
 * _spast - bring out the file storing the recent commands
 * @noti: structure
 * Return: the name of the file
 * Authors: Kelvin Njuiri and Bismark Kete
 */

char *_spast(info_t *noti)
{
	char *fld;
	char *bfr;

	fld = _gt_env(noti, "HOME=");
	if (!fld)
		return (NULL);
	bfr = malloc((_lngthstr(fld) + _lngthstr(PAST_FL) + 2) * sizeof(char));
	if (!bfr)
		return (NULL);
	bfr[0] = 0;
	_cpst(bfr, fld);
	_strcnct(bfr, "/");
	_strcnct(bfr, PAST_FL);

	return (bfr);
}

/**
 * _crtpast - makes a new file showing the recent commands or adds to it
 * @noti: structure
 * Return: -1 (Otherwise), 1 (Success)
 */
int _crtpast(info_t *noti)
{
	list_t *n = NULL;
	ssize_t desc;
	char *identity = _spast(noti);

	if (!identity)
		return (-1);

	desc = open(identity, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(identity);
	if (desc == -1)
		return (-1);
	for (n = noti->history; n; n = n->next)
	{
		_wtdsc(n->str, desc);
		_w_dsc('\n', desc);
	}
	_w_dsc(FLS_BFR, desc);
	close(desc);

	return (1);
}

/**
 * _thrpast - brings out the content of the past file
 * @noti: structure
 * Return: number of recent commands (Success) or 0 (otherwise)
 */
int _thrpast(info_t *noti)
{
	char *identity = _spast(noti), *bfr = NULL;
	struct stat strt;
	ssize_t desc, weight = 0, _chkdst;
	int end = 0, cnt = 0, index;

	if (!identity)
		return (0);

	desc = open(identity, O_RDONLY);
	free(identity);
	if (desc == -1)
		return (0);
	if (!fstat(desc, &strt))
		weight = strt.st_size;
	if (weight < 2)
		return (0);
	bfr = malloc((weight + 1) * sizeof(char));
	if (!bfr)
		return (0);
	_chkdst = read(desc, bfr, weight);
	bfr[weight] = 0;
	if (_chkdst <= 0)
		return (free(bfr), 0);
	close(desc);
	for (index = 0; index < weight; index++)
		if (bfr[index] == '\n')
		{
			bfr[index] = 0;
			_fnlspast(noti, bfr + end, cnt++);
			end = index + 1;
		}
	if (end != index)
		_fnlspast(noti, bfr + end, cnt++);
	free(bfr);
	noti->histcount = cnt;
	while (noti->histcount-- >= PAST_M)
		_rmnd(&(noti->history), 0);
	_rpast(noti);
	return (noti->histcount);
}

/**
 * _fnlspast - appends to the list
 * @noti: struct
 * @bfr: area
 * @cnt: number of elements
 * Return: Always 0 (Success)
 */
int _fnlspast(info_t *noti, char *bfr, int cnt)
{
	list_t *n = NULL;

	if (!noti->history)
		noti->history = n;

	if (noti->history)
		n = noti->history;
	_down_ad(&n, bfr, cnt);

	return (0);
}

/**
 * _rpast - freshly numerate the file
 * @noti: structure
 * Return: the number of file contents
 */
int _rpast(info_t *noti)
{
	int index;
	list_t *n = noti->history;

	index = 0;
	while (n)
	{
		n->num = index++;
		n = n->next;
	}
	return (noti->histcount = index);
}
