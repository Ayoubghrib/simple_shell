#include "shell.h"

/**
 * is_command - Checks if a file is an executable command.
 * @info: Pointer to the info struct.
 * @file_path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_command(info_t *info, char *file_path)
{
	struct stat file_stat;

	(void)info;
	if (!file_path || stat(file_path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - Duplicates characters.
 * @path_str: The PATH string.
 * @start_index: Starting index.
 * @stop_index: Stopping index.
 *
 * Return: Pointer to a new buffer.
 */
char *duplicate_chars(char *path_str, int start_index, int stop_index)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start_index; i < stop_index; i++)
		if (path_str[i] != ':')
			buffer[k++] = path_str[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_command_path - Finds the command in the PATH string.
 * @info: Pointer to the info struct.
 * @path_str: The PATH string.
 * @command: The command to find.
 *
 * Return: Full path of command if found or NULL.
 */
char *find_command_path(info_t *info, char *path_str, char *command)
{
	int i = 0, curr_pos = 0;
	char *full_path;

	if (!path_str)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_command(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			full_path = duplicate_chars(path_str, curr_pos, i);
			if (!*full_path)
				_strcat(full_path, command);
			else
			{
				_strcat(full_path, "/");
				_strcat(full_path, command);
			}
			if (is_command(info, full_path))
				return (full_path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

