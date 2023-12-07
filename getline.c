#include "shell.h"

/**
 * bufferInput - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t lengthRead = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytesRead = getline(buffer, &lengthRead, stdin);
#else
		bytesRead = _getline(info, buffer, &lengthRead);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0'; /* remove trailing newline */
				bytesRead--;
			}
			info->linecount_flag = 1;
			removeComments(*buffer);
			buildHistoryList(info, *buffer, info->histcount++);
			*length = bytesRead;
			info->cmdBuffer = buffer;
		}
	}
	return bytesRead;
}

/**
 * getInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t currentIndex, j, length;
	ssize_t bytesRead = 0;
	char **bufferPtr = &(info->arg), *currentPointer;

	_putchar(BUF_FLUSH);
	bytesRead = bufferInput(info, &buffer, &length);
	if (bytesRead == -1) /* EOF */
		return -1;
	if (length) /* we have commands left in the chain buffer */
	{
		j = currentIndex; /* init new iterator to the current buffer position */
		currentPointer = buffer + currentIndex; /* get pointer for return */

		checkChain(info, buffer, &j, currentIndex, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (isChain(info, buffer, &j))
				break;
			j++;
		}

		currentIndex = j + 1; /* increment past nulled ';'' */
		if (currentIndex >= length) /* reached end of buffer? */
		{
			currentIndex = length = 0; /* reset position and length */
			info->cmdBufferType = CMD_NORM;
		}

		*bufferPtr = currentPointer; /* pass back pointer to the current command position */
		return _strlen(currentPointer); /* return length of the current command */
	}

	*bufferPtr = buffer; /* else not a chain, pass back buffer from _getline() */
	return bytesRead; /* return length of buffer from _getline() */
}

/**
 * readBuffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @currentIndex: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *currentIndex)
{
	ssize_t bytesRead = 0;

	if (*currentIndex)
		return 0;
	bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*currentIndex = bytesRead;
	return bytesRead;
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated pointer buffer if not NULL
 *
 * Return: size
 */
int _getline(info_t *info, char **pointer, size_t *length)
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

	bytesRead = readBuffer(info, buffer, &lengthRead);
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
 * sigintHandler - blocks ctrl-C
 * @signalNumber: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signalNumber)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

