#include "shell.h"

/**
 * isInteractiveMode - Checks if the shell is in interactive mode.
 * @info: Pointer to info struct.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int isInteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - Checks if a character is a delimiter.
 * @character: The character to check.
 * @delimiterString: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int isDelimiter(char character, char *delimiterString)
{
	while (*delimiterString)
		if (*delimiterString++ == character)
			return (1);
	return 0;
}

/**
 * stringToInteger - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in the string, converted number otherwise.
 */
int stringToInteger(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return output;
}

/**
 * isAlphabetic - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int isAlphabetic(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}

