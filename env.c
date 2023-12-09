#include "shell.h"

/**
 * print_environment - prints the current environment
 * @env: Structure representing the environment variables
 * Return: Always 0
 */
int print_environment(environment_t *env)
{
	print_list_str(env->variables);
	return (0);
}

/**
 * get_environment_variable - gets the value of an environment variable
 * @env: Structure representing the environment variables
 * @name: env var name
 * Return: the value
 */
char *get_environment_variable(environment_t *env, const char *name)
{
	list_t *node = env->variables;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environment_variable - Initialize a new environment variable,
 *             or modify an existing one
 * @env: Structure representing the environment variables
 * @name: Variable name
 * @value: Variable value
 * Return: Always 0
 */
int set_environment_variable(environment_t *env, const char *name, const char *value)
{
	// Implement your logic to set the environment variable
	// You may need to modify this function based on your requirements
	return (0);
}

/**
 * unset_environment_variable - Remove an environment variable
 * @env: Structure representing the environment variables
 * @name: Variable name to unset
 * Return: Always 0
 */
int unset_environment_variable(environment_t *env, const char *name)
{
	// Implement your logic to unset the environment variable
	// You may need to modify this function based on your requirements
	return (0);
}

/**
 * populate_environment - populates environment structure with linked list
 * @env: Structure representing the environment variables
 * Return: Always 0
 */
int populate_environment(environment_t *env)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	env->variables = node;
	return (0);
}

