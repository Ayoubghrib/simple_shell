#include "shell.h"

/**
 * initializeInfo - initializes information in info_t struct
 * @information: struct address
 */
void initializeInfo(info_t *information)
{
    information->arguments = NULL;
    information->argumentsVector = NULL;
    information->executablePath = NULL;
    information->argumentCount = 0;
}

/**
 * populateInfo - populates information in info_t struct
 * @information: struct address
 * @argumentVector: argument vector
 */
void populateInfo(info_t *information, char **argumentVector)
{
    int index = 0;

    information->filename = argumentVector[0];
    if (information->arguments)
    {
        information->argumentsVector = strtow(information->arguments, " \t");
        if (!information->argumentsVector)
        {
            information->argumentsVector = malloc(sizeof(char *) * 2);
            if (information->argumentsVector)
            {
                information->argumentsVector[0] = _strdup(information->arguments);
                information->argumentsVector[1] = NULL;
            }
        }
        for (index = 0; information->argumentsVector && information->argumentsVector[index]; index++)
            ;
        information->argumentCount = index;

        replaceAlias(information);
        replaceVariables(information);
    }
}

/**
 * releaseInformation - frees allocated memory in info_t struct
 * @information: struct address
 * @freeAll: true if freeing all fields
 */
void releaseInformation(info_t *information, int freeAll)
{
    ffree(information->argumentsVector);
    information->argumentsVector = NULL;
    information->executablePath = NULL;
    if (freeAll)
    {
        if (!information->commandBuffer)
            free(information->arguments);
        if (information->environmentVariables)
            freeList(&(information->environmentVariables));
        if (information->commandHistory)
            freeList(&(information->commandHistory));
        if (information->aliases)
            freeList(&(information->aliases));
        ffree(information->environment);
        information->environment = NULL;
        bfree((void **)information->commandBuffer);
        if (information->readFileDescriptor > 2)
            close(information->readFileDescriptor);
        _putchar(BUF_FLUSH);
    }
}

