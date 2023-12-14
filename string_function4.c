#include "shell.h"

/**
 * strtow - Splits a string into words. Repeat delimiters are ignored.
 * @input_str: The input string.
 * @delimiters: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *input_str, char *delimiters)
{
	int i, j, k, m, num_words = 0;
	char **result_array;

	if (input_str == NULL || input_str[0] == '\0')
		return (NULL);

	if (!delimiters)
		delimiters = " ";

	for (i = 0; input_str[i] != '\0'; i++)
		if (!is_delim(input_str[i], delimiters) &&
		    (is_delim(input_str[i + 1], delimiters) || input_str[i + 1] == '\0'))
			num_words++;

	if (num_words == 0)
		return (NULL);

	result_array = malloc((1 + num_words) * sizeof(char *));
	if (!result_array)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(input_str[i], delimiters))
			i++;

		k = 0;
		while (!is_delim(input_str[i + k], delimiters) && input_str[i + k])
			k++;

		result_array[j] = malloc((k + 1) * sizeof(char));
		if (!result_array[j])
		{
			for (k = 0; k < j; k++)
				free(result_array[k]);
			free(result_array);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			result_array[j][m] = input_str[i++];

		result_array[j][m] = '\0';
	}

	result_array[j] = NULL;
	return (result_array);
}

