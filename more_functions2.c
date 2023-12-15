#include "shell.h"

/**
 * safe_string_to_integer - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise
 *        -1 on error
 */
int safe_string_to_integer(char *str)
{
    int index = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;
    for (index = 0; str[index] != '\0'; index++)
    {
        if (str[index] >= '0' && str[index] <= '9')
        {
            result *= 10;
            result += (str[index] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 * @number: the number
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */
int print_decimal(int number, int fd)
{
    int (*custom_putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int absolute_value, current;

    if (fd == STDERR_FILENO)
        custom_putchar = _eputchar;
    if (number < 0)
    {
        absolute_value = -number;
        custom_putchar('-');
        count++;
    }
    else
        absolute_value = number;

    current = absolute_value;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absolute_value / i)
        {
            custom_putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    custom_putchar('0' + current);
    count++;

    return (count);
}

/**
 * convert_to_base - converts a number to a string representation
 * @num: the number
 * @base: the base
 * @flags: argument flags
 * Return: string representation of the number
 */
char *convert_to_base(long int num, int base, int flags)
{
    static char *digit_array;
    static char result_buffer[50];
    char sign = 0;
    char *result_ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    digit_array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    result_ptr = &result_buffer[49];
    *result_ptr = '\0';

    do
    {
        *--result_ptr = digit_array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--result_ptr = sign;
    return (result_ptr);
}

/**
 * remove_comments - replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 */
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}

