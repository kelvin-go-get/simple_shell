#include "shell.h"

/**
 * _env - function that prints the current working directory
 * @noti: structure
 * Return: Always 0 (Success)
 * Authors: Kelvin Njuiri and Bismark Kete
 */
int _env(info_t *noti)
{
	_lstrprnt(noti->env);

	return (0);
}

/**
 * _gt_env - takes the value of the environment variable
 * @noti: structure
 * @idn: variable's identity
 *
 * Return: variable's value
 */
char *_gt_env(info_t *noti, const char *idn)
{
	char *ptr;
	list_t *n = noti->env;

	while (n)
	{
		ptr = _wtstr(n->str, idn);
		if (ptr && *ptr)
			return (ptr);
		n = n->next;
	}
	return (NULL);
}

/**
 * _setenv - changes an env variable or makes a new one
 * @noti: structure
 *  Return: Always 0 (Success)
 */
int _setenv(info_t *noti)
{
	if (noti->argc != 3)
	{
		_errp("Incorrect number of arguements\n");
		return (1);
	}
	if (_senv(noti, noti->argv[1], noti->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv - deletes a variable
 * @noti: structure
 *  Return: Always 0 (Success)
 */
int _unsetenv(info_t *noti)
{
	int index;

	if (noti->argc == 1)
	{
		_errp("Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= noti->argc; index++)
		_usenv(noti, noti->argv[index]);

	return (0);
}

/**
 * _envlt - fills the linked list of the env
 * @noti: Structure
 * Return: Always 0 (Success)
 */
int _envlt(info_t *noti)
{
	size_t index;
	list_t *n = NULL;

	for (index = 0; environ[index]; index++)
		_down_ad(&n, environ[index], 0);
	noti->env = n;

	return (0);
}
