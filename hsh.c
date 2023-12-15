#include "shell.h"

/**
 * mainShellLoop - main shell loop
 * @information: the parameter & return information struct
 * @argumentVector: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int mainShellLoop(info_t *information, char **argumentVector)
{
    ssize_t readStatus = 0;
    int builtinReturn = 0;

    while (readStatus != -1 && builtinReturn != -2)
    {
        clearInformation(information);
        if (interactiveMode(information))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        readStatus = getInput(information);
        if (readStatus != -1)
        {
            setInformation(information, argumentVector);
            builtinReturn = findBuiltin(information);
            if (builtinReturn == -1)
                findCommand(information);
        }
        else if (interactiveMode(information))
            _putchar('\n');
        freeInformation(information, 0);
    }
    writeHistory(information);
    freeInformation(information, 1);
    if (!interactiveMode(information) && information->status)
        exit(information->status);
    if (builtinReturn == -2)
    {
        if (information->errorNumber == -1)
            exit(information->status);
        exit(information->errorNumber);
    }
    return (builtinReturn);
}

/**
 * findBuiltin - finds a builtin command
 * @information: the parameter & return information struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int findBuiltin(info_t *information)
{
    int i, builtinReturn = -1;
    builtinTable builtinTable[] = {
        {"exit", myExit},
        {"env", myEnv},
        {"help", myHelp},
        {"history", myHistory},
        {"setenv", mySetenv},
        {"unsetenv", myUnsetenv},
        {"cd", myCd},
        {"alias", myAlias},
        {NULL, NULL}};

    for (i = 0; builtinTable[i].type; i++)
        if (_strcmp(information->argumentsVector[0], builtinTable[i].type) == 0)
        {
            information->lineCount++;
            builtinReturn = builtinTable[i].func(information);
            break;
        }
    return (builtinReturn);
}

/**
 * findCommand - finds a command in PATH
 * @information: the parameter & return information struct
 *
 * Return: void
 */
void findCommand(info_t *information)
{
    char *path = NULL;
    int i, numArgs;

    information->executablePath = information->argumentsVector[0];
    if (information->lineCountFlag == 1)
    {
        information->lineCount++;
        information->lineCountFlag = 0;
    }
    for (i = 0, numArgs = 0; information->arguments[i]; i++)
        if (!isDelimiter(information->arguments[i], " \t\n"))
            numArgs++;
    if (!numArgs)
        return;

    path = findPath(information, _getenv(information, "PATH="), information->argumentsVector[0]);
    if (path)
    {
        information->executablePath = path;
        forkCommand(information);
    }
    else
    {
        if ((interactiveMode(information) || _getenv(information, "PATH=") || information->argumentsVector[0][0] == '/') &&
            isCommand(information, information->argumentsVector[0]))
            forkCommand(information);
        else if (*(information->arguments) != '\n')
        {
            information->status = 127;
            printError(information, "not found\n");
        }
    }
}

/**
 * forkCommand - forks an exec thread to run command
 * @information: the parameter & return information struct
 *
 * Return: void
 */
void forkCommand(info_t *information)
{
    pid_t childPid;

    childPid = fork();
    if (childPid == -1)
    {
        perror("Error:");
        return;
    }
    if (childPid == 0)
    {
        if (execve(information->executablePath, information->argumentsVector, getEnviron(information)) == -1)
        {
            freeInformation(information, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(information->status));
        if (WIFEXITED(information->status))
        {
            information->status = WEXITSTATUS(information->status);
            if (information->status == 126)
                printError(information, "Permission denied\n");
        }
    }
}

