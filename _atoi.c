#include "shell.h"

/**
 * _comint - if the shell enters the collaborative mode, returns true
 * @noti: struct address
 * Return: if in collaborative mode, 1 or 0, otherwise
 * Authors: Kelvin and Bismark
 */
int _comint(info_t *noti)
{
	return (isatty(STDIN_FILENO) && noti->readfd <= 2);
}

/**
 * _delimeter - function to check if the character is a delimeter
 * @ch: the character expected to be checked
 * @strdlm: the string with the delimeter
 * Return: if false, 0 and if true, 1
 */
int _delimeter(char ch, char *strdlm)
{
	while (*strdlm)
		if (*strdlm++ == ch)
			return (1);
	return (0);
}

/**
 * _Alph - check to see if an the character is alphabetic character
 * @ch: expected character to be inputted
 * Return: if character is an alphabet, 1 and 0, otherwise
 */

int _Alph(int ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - this function converts strings to integers
 *@str: expected string to be converted into integers
 *Return: 0 if no numeral in string, the integer gotten otherwise
 */

int _atoi(char *str)
{
	unsigned int rst = 0;
	int prf = 1, ind, opt, flg = 0;

	for (ind = 0;  flg != 2 && str[ind] != '\0'; ind++)
	{
		if (str[ind] == '-')
			prf *= -1;

		if (str[ind] <= '9' && str[ind] >= '0')
		{
			flg = 1;
			rst = rst * 10;
			rst += (str[ind] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (prf == -1)
		opt = -rst;
	else
		opt = rst;

	return (opt);
}

