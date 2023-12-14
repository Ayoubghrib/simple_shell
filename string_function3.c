#include "shell.h"

/**
 * custom_strncpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @num: The amount of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *custom_strncpy(char *dest, char *src, int num)
{
    int srcIndex = 0, destIndex;
    char *result = dest;

    destIndex = 0;
    while (src[srcIndex] != '\0' && srcIndex < num - 1)
    {
        dest[destIndex] = src[srcIndex];
        srcIndex++;
        destIndex++;
    }

    if (srcIndex < num)
    {
        int j = srcIndex;
        while (j < num)
        {
            dest[j] = '\0';
            j++;
        }
    }
    return result;
}

/**
 * custom_strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @num: The amount of bytes to be maximally used.
 *
 * Return: The concatenated string.
 */
char *custom_strncat(char *dest, char *src, int num)
{
    int destIndex = 0, srcIndex = 0;
    char *result = dest;

    while (dest[destIndex] != '\0')
        destIndex++;

    while (src[srcIndex] != '\0' && srcIndex < num)
    {
        dest[destIndex] = src[srcIndex];
        destIndex++;
        srcIndex++;
    }

    if (srcIndex < num)
        dest[destIndex] = '\0';

    return result;
}

/**
 * custom_strchr - Locates a character in a string.
 * @str: The string to be parsed.
 * @character: The character to look for.
 *
 * Return: A pointer to the memory area str.
 */
char *custom_strchr(char *str, char character)
{
    do
    {
        if (*str == character)
            return (str);
    } while (*str++ != '\0');

    return NULL;
}

