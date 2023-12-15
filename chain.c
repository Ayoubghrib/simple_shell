#include "shell.h"

/**
 * isChain - test if the current character in the buffer is a chain delimiter
 * @info: the parameter struct
 * @buffer: the character buffer
 * @position: address of the current position in buffer
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int isChain(info_t *info, char *buffer, size_t *position)
{
    size_t j = *position;

    if (buffer[j] == '|' && buffer[j + 1] == '|')
    {
        buffer[j] = 0;
        j++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buffer[j] == '&' && buffer[j + 1] == '&')
    {
        buffer[j] = 0;
        j++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buffer[j] == ';') /* found the end of this command */
    {
        buffer[j] = 0; /* replace semicolon with null */
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return (0);
    }
    *position = j;
    return (1);
}

/**
 * checkChain - checks if we should continue chaining based on the last status
 * @info: the parameter struct
 * @buffer: the character buffer
 * @position: address of the current position in buffer
 * @start: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void checkChain(info_t *info, char *buffer, size_t *position, size_t start, size_t length)
{
    size_t j = *position;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buffer[start] = 0;
            j = length;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buffer[start] = 0;
            j = length;
        }
    }

    *position = j;
}

/**
 * replaceAlias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = nodeStartsWith(info->alias, info->argv[0], '=');
        if (!node)
        {
            return (0);
        }
        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
        {
            return (0);
        }
        p = _strdup(p + 1);
        if (!p)
        {
            return (0);
        }
        info->argv[0] = p;
    }
    return (1);
}

/**
 * replaceVars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVars(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
        {
            continue;
        }

        if (!_strcmp(info->argv[i], "$?"))
        {
            replaceString(&(info->argv[i]), _strdup(convertNumber(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replaceString(&(info->argv[i]), _strdup(convertNumber(getpid(), 10, 0)));
            continue;
        }
        node = nodeStartsWith(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replaceString(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replaceString(&info->argv[i], _strdup(""));
    }
    return (0);
}

/**
 * replaceString - replaces string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}

