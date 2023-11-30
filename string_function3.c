#include "shell.h"

/**
 * _strncpy - Copies a string.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @num: The amount of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *_strncpy(char *destination, char *source, int num)
{
	int indexSource = 0, indexDestination;
	char *result = destination;

	indexDestination = 0;
	while (source[indexSource] != '\0' && indexSource < num - 1)
	{
		destination[indexDestination] = source[indexSource];
 The character to look for.
 *
 * Return: A pointer to the memory area str.
 */
char *_strchr(char *str, char character)
{
	do {
		if (*str == character)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
ndexSource++;
		indexDestination++;
			}
	if (indexSource < num)
		{
					int j = indexSource;
							while (j < num)
										{
														destination[j] = '\0';
																	j++;
																			}
								}
	return (result);
	}

/**
 *  * _strncat - Concatenates two strings.
 *   * @destination: The first string.
 *    * @source: The second string.
 *     * @num: The amount of bytes to be maximally used.
 *      *
 *       * Return: The concatenated string.
 *        */
char *_strncat(char *destination, char *source, int num)
{
		int indexDestination = 0, indexSource = 0;
			char *result = destination;

				while (destination[indexDestination] != '\0')
							indexDestination++;
					while (source[indexSource] != '\0' && indexSource < num)
							{
										destination[indexDestination] = source[indexSource];
												indexDestination++;
														indexSource++;
															}
						if (indexSource < num)
									destination[indexDestination] = '\0';
							return (result);
}

/**
 *  * _strchr - Locates a character in a string.
 *   * @str: The string to be parsed.
 *    * @character:
