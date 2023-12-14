#include "shell.h"

/**
 * freeAndNull - Frees a pointer and sets it to NULL.
 * @ptrToPointer: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int freeAndNull(void **ptrToPointer)
{
    if (ptrToPointer && *ptrToPointer)
    {
        free(*ptrToPointer);
        *ptrToPointer = NULL;
        return 1;
    }
    return 0;
}
