#include "shell.h"

/**
 * _q_ext - exits the shell
 * @noti: structure
 *  Return: a certain exist status
 *	Authors: Kelvin Njuiri and Bismark Kete
 */
int _q_ext(info_t *noti)
{
	int assess;

	if (noti->argv[1])
	{
		assess = _estoi(noti->argv[1]);
		if (assess == -1)
		{
			noti->status = 2;
			_errout(noti, "Illegal number: ");
			_errp(noti->argv[1]);
			_errptch('\n');
			return (1);
		}
		noti->err_num = _estoi(noti->argv[1]);
		return (-2);
	}
	noti->err_num = -1;
	return (-2);
}

/**
 * _cdchn - move from one directory to another
 * @noti: structure
 *  Return: Always 0 (Success)
 */
int _cdchn(info_t *noti)
{
	int fldchn;
	char bfr[1024], *x, *fld;

	x = getcwd(bfr, 1024);
	if (!x)
		_prnt("TODO: >>getcwd failure emsg here<<\n");
	if (!noti->argv[1])
	{
		fld = _gt_env(noti, "HOME=");
		if (!fld)
			fldchn = chdir((fld = _gt_env(noti, "PWD=")) ? fld : "/");
		else
			fldchn = chdir(fld);
	}
	else if (_compstr(noti->argv[1], "-") == 0)
	{
		if (!_gt_env(noti, "OLDPWD="))
		{
			_prnt(x);
			_chprnt('\n');
			return (1);
		}
		_prnt(_gt_env(noti, "OLDPWD=")), _chprnt('\n');
		fldchn = chdir((fld = _gt_env(noti, "OLDPWD=")) ? fld : "/");
	}
	else
		fldchn = chdir(noti->argv[1]);
	if (fldchn == -1)
	{
		_errout(noti, "can't cd to ");
		_errp(noti->argv[1]), _errptch('\n');
	}
	else
	{
		_senv(noti, "OLDPWD", _gt_env(noti, "PWD="));
		_senv(noti, "PWD", getcwd(bfr, 1024));
	}
	return (0);
}

/**
 * _help - new directory for the work
 * @noti: structure
 *  Return: Always 0 (Success)
 */
int _help(info_t *noti)
{
	char **ag_ar;

	ag_ar = noti->argv;
	_prnt("help call works. Function not yet implemented \n");
	if (0)
		_prnt(*ag_ar);
	return (0);
}
