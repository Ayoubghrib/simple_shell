#include "shell.h"

/**
 * printEnvironment - prints the current environment
 * @environment: Structure representing the environment variables
 * Return: Always 0
 */
int printEnvironment(environment_t *environment)
{
    printListStr(environment->variables);
    return (0);
}

/**
 * getEnvironmentVariable - gets the value of an environment variable
 * @environment: Structure representing the environment variables
 * @name: env var name
 * Return: the value
 */
char *getEnvironmentVariable(environment_t *environment, const char *name)
{
    list_t *node = environment->variables;
    char *p;

    while (node)
    {
        p = startsWith(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable,
 *             or modify an existing one
 * @environment: Structure representing the environment variables
 * @name: Variable name
 * @value: Variable value
 * Return: Always 0
 */
int setEnvironmentVariable(environment_t *environment, const char *name, const char *value)
{
    // Implement your logic to set the environment variable
    // You may need to modify this function based on your requirements
    return (0);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @environment: Structure representing the environment variables
 * @name: Variable name to unset
 * Return: Always 0
 */
int unsetEnvironmentVariable(environment_t *environment, const char *name)
{
    // Implement your logic to unset the environment variable
    // You may need to modify this function based on your requirements
    return (0);
}

/**
 * populateEnvironment - populates environment structure with linked list
 * @environment: Structure representing the environment variables
 * Return: Always 0
 */
int populateEnvironment(environment_t *environment)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);
    environment->variables = node;
    return (0);
}

