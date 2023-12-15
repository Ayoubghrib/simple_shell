#include "shell.h"

/**
 * exitShell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 *         (0) if info->argv[0] != "exit"
 */
int exitShell(info_t *info)
{
	int exitStatus;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exitStatus = _erratoi(info->argv[1]);
		if (exitStatus == -1)
		{
			info->status = 2;
			printError(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return 1;
		}
		info->err_num = exitStatus;
		return -2;
	}

	info->err_num = -1;
	return -2;
}

/**
 * changeDirectory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int changeDirectory(info_t *info)
{
	char *currentDir, *targetDir, buffer[1024];
	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		targetDir = _getenv(info, "HOME=");
		if (!targetDir)
			chdirResult = chdir((targetDir = _getenv(info, "PWD=")) ? targetDir : "/");
		else
			chdirResult = chdir(targetDir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return 1;
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirResult = chdir((targetDir = _getenv(info, "OLDPWD=")) ? targetDir : "/");
	}
	else
		chdirResult = chdir(info->argv[1]);

	if (chdirResult == -1)
	{
		printError(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * displayHelp - displays help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int displayHelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray); /* temp att_unused workaround */
	return 0;
}

