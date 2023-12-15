#include "shell.h"

/**
 * get_list_length - determines the length of the linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t get_list_length(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        head = head->next;
        count++;
    }
    return (count);
}

/**
 * list_to_strings - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
    list_t *current_node = head;
    size_t length = get_list_length(head), index;
    char **strings_array;
    char *string;

    if (!head || !length)
        return (NULL);

    strings_array = malloc(sizeof(char *) * (length + 1));
    if (!strings_array)
        return (NULL);

    for (index = 0; current_node; current_node = current_node->next, index++)
    {
        string = malloc(_strlen(current_node->str) + 1);
        if (!string)
        {
            for (size_t j = 0; j < index; j++)
                free(strings_array[j]);
            free(strings_array);
            return (NULL);
        }

        string = _strcpy(string, current_node->str);
        strings_array[index] = string;
    }
    strings_array[index] = NULL;
    return (strings_array);
}

/**
 * print_list_elements - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list_elements(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(convert_number(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }
    return (count);
}

/**
 * find_node_with_prefix - returns a node whose string starts with the prefix
 * @head: pointer to the list head
 * @prefix: string to match
 * @next_char: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_with_prefix(list_t *head, char *prefix, char next_char)
{
    char *result = NULL;

    while (head)
    {
        result = starts_with(head->str, prefix);
        if (result && ((next_char == -1) || (*result == next_char)))
            return (head);
        head = head->next;
    }
    return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return (index);
        head = head->next;
        index++;
    }
    return (-1);
}

