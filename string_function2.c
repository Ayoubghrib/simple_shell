#include "shell.h"

/**
 * custom_copy_string - Copies a string.
 * @destination: The destination.
 * @source: The source.
 *
 * Return: Pointer to destination.
 */
char *custom_copy_string(char *destination, char *source)
{
    int index = 0;

    if (destination == source || source == NULL)
        return (destination);

    while (source[index])
    {
        destination[index] = source[index];
        index++;
    }

    destination[index] = '\0';
    return (destination);
}

/**
 * custom_duplicate_string - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *custom_duplicate_string(const char *str)
{
    int length = 0;
    char *result;

    if (str == NULL)
        return (NULL);

    while (*str++)
        length++;

    result = malloc(sizeof(char) * (length + 1));

    if (!result)
        return (NULL);

    for (length++; length--;)
        result[length] = *--str;

    return (result);
}

/**
 * custom_print_string - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void custom_print_string(char *str)
{
    int index = 0;

    if (!str)
        return;

    while (str[index] != '\0')
    {
        custom_putchar(str[index]);
        index++;
    }
}

/**
 * custom_putchar - Writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char c)
{
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
    {
        write(1, buffer, index);
        index = 0;
    }

    if (c != BUF_FLUSH)
        buffer[index++] = c;

    return (1);
}

