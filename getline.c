#include "shell.h"

/**
 * bufferChainedInput - buffers chained commands
 * @information: parameter struct
 * @commandBuffer: address of buffer
 * @bufferLength: address of length var
 *
 * Return: bytes read
 */
ssize_t bufferChainedInput(info_t *information, char **commandBuffer, size_t *bufferLength)
{
    ssize_t bytesRead = 0;
    size_t lengthRead = 0;

    if (!*bufferLength) /* if nothing left in the buffer, fill it */
    {
        free(*commandBuffer);
        *commandBuffer = NULL;
        signal(SIGINT, handleSIGINT);
#if USE_GETLINE
        bytesRead = getline(commandBuffer, &lengthRead, stdin);
#else
        bytesRead = _getline(information, commandBuffer, &lengthRead);
#endif
        if (bytesRead > 0)
        {
            if ((*commandBuffer)[bytesRead - 1] == '\n')
            {
                (*commandBuffer)[bytesRead - 1] = '\0'; /* remove trailing newline */
                bytesRead--;
            }
            information->lineCountFlag = 1;
            removeComments(*commandBuffer);
            buildHistoryList(information, *commandBuffer, information->historyCount++);
            *bufferLength = bytesRead;
            information->commandBuffer = commandBuffer;
        }
    }
    return bytesRead;
}

/**
 * getInput - gets a line minus the newline
 * @information: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(info_t *information)
{
    static char *commandBuffer; /* the ';' command chain buffer */
    static size_t currentIndex, j, bufferLength;
    ssize_t bytesRead = 0;
    char **bufferPointer = &(information->arguments), *currentPointer;

    _putchar(BUF_FLUSH);
    bytesRead = bufferChainedInput(information, &commandBuffer, &bufferLength);
    if (bytesRead == -1) /* EOF */
        return -1;
    if (bufferLength) /* we have commands left in the chain buffer */
    {
        j = currentIndex; /* init new iterator to the current buffer position */
        currentPointer = commandBuffer + currentIndex; /* get pointer for return */

        checkChain(information, commandBuffer, &j, currentIndex, bufferLength);
        while (j < bufferLength) /* iterate to semicolon or end */
        {
            if (isChain(information, commandBuffer, &j))
                break;
            j++;
        }

        currentIndex = j + 1; /* increment past nulled ';'' */
        if (currentIndex >= bufferLength) /* reached end of buffer? */
        {
            currentIndex = bufferLength = 0; /* reset position and length */
            information->commandBufferType = CMD_NORMAL;
        }

        *bufferPointer = currentPointer; /* pass back pointer to the current command position */
        return _strlen(currentPointer); /* return length of the current command */
    }

    *bufferPointer = commandBuffer; /* else not a chain, pass back buffer from _getline() */
    return bytesRead; /* return length of buffer from _getline() */
}

/**
 * readBuffer - reads a buffer
 * @information: parameter struct
 * @buffer: buffer
 * @currentIndex: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *information, char *buffer, size_t *currentIndex)
{
    ssize_t bytesRead = 0;

    if (*currentIndex)
        return 0;
    bytesRead = read(information->readfd, buffer, READ_BUF_SIZE);
    if (bytesRead >= 0)
        *currentIndex = bytesRead;
    return bytesRead;
}

/**
 * _getline - gets the next line of input from STDIN
 * @information: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated pointer buffer if not NULL
 *
 * Return: size
 */
int _getline(info_t *information, char **pointer, size_t *length)
{
    static char buffer[READ_BUF_SIZE];
    static size_t currentIndex, lengthRead;
    size_t k;
    ssize_t bytesRead = 0, size = 0;
    char *p = NULL, *newPointer = NULL, *c;

    p = *pointer;
    if (p && length)
        size = *length;
    if (currentIndex == lengthRead)
        currentIndex = lengthRead = 0;

    bytesRead = readBuffer(information, buffer, &lengthRead);
    if (bytesRead == -1 || (bytesRead == 0 && lengthRead == 0))
        return -1;

    c = _strchr(buffer + currentIndex, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : lengthRead;
    newPointer = _realloc(p, size, size ? size + k : k + 1);
    if (!newPointer) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (size)
        _strncat(newPointer, buffer + currentIndex, k - currentIndex);
    else
        _strncpy(newPointer, buffer + currentIndex, k - currentIndex + 1);

    size += k - currentIndex;
    currentIndex = k;
    p = newPointer;

    if (length)
        *length = size;
    *pointer = p;
    return size;
}

/**
 * handleSIGINT - blocks ctrl-C
 * @signalNumber: the signal number
 *
 * Return: void
 */
void handleSIGINT(__attribute__((unused))int signalNumber)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

