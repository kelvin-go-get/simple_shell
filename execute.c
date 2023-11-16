#include "shell.h"

/**
 * _isexc - checks the "executability" of a file
 * @noti: structure
 * @flpth: file's direction
 *
 * Return: 1 if the file is executable, 0 otherwise
 * Authors: Kelvin Njuiri and Bismark Kete
 */
int _isexc(info_t *noti, char *flpth)
{
	struct stat wd;

	(void)noti;
	if (stat(flpth, &wd) || !flpth)
		return (0);

	if (wd.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _chrdp - duplicates characters
 * @stpth: the PATH string
 * @begin: beginning
 * @end: ending
 *
 * Return: pointer
 */
char *_chrdp(char *stpth, int begin, int end)
{
	int index, x;
	static char bfr[1024];

	index = 0;
	x = 0;
	for (x = 0, index = begin; index < end; index++)
		if (stpth[index] != ':')
			bfr[x++] = stpth[index];
	bfr[x] = 0;
	return (bfr);
}

/**
 * _fdpth - located a command in the string
 * @noti: structure
 * @stpth: the string location
 * @exc: what we are trying to locate
 * Return: the location or NULL, otherwise
 */
char *_fdpth(info_t *noti, char *stpth, char *exc)
{
	char *loc;
	int now = 0, index = 0;

	if (!stpth)
		return (NULL);
	if ((_lngthstr(exc) > 2) && _wtstr(exc, "./"))
	{
		if (_isexc(noti, exc))
			return (exc);
	}
	while (1)
	{
		if (stpth[index] == ':' || !stpth[index])
		{
			loc = _chrdp(stpth, now, index);
			if (!*loc)
				_strcnct(loc, exc);
			else
			{
				_strcnct(loc, "/");
				_strcnct(loc, exc);
			}
			if (_isexc(noti, loc))
				return (loc);
			if (!stpth[index])
				break;
			now = index;
		}
		index++;
	}
	return (NULL);
}

