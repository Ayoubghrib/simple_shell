#include "shell.h"

/**
 * getHistoryFile - Retrieves the history file path
 * @info: Parameter struct
 *
 * Return: Allocated string containing the history file path
 */
char *getHistoryFile(info_t *info) {
    char *homeDir = _getenv(info, "HOME=");
    if (!homeDir)
        return NULL;

    char *historyFile = malloc(_strlen(homeDir) + _strlen(HIST_FILE) + 2);
    if (!historyFile) {
        free(homeDir);
        return NULL;
    }

    historyFile[0] = '\0';
    _strcpy(historyFile, homeDir);
    _strcat(historyFile, "/");
    _strcat(historyFile, HIST_FILE);

    free(homeDir);
    return historyFile;
}

/**
 * writeHistory - Writes the history to a file
 * @info: The parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int writeHistory(info_t *info) {
    char *filename = getHistoryFile(info);
    if (!filename)
        return -1;

    ssize_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    list_t *node = info->history;
    while (node) {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
        node = node->next;
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);

    return 1;
}

/**
 * readHistory - Reads history from a file
 * @info: The parameter struct
 *
 * Return: Histcount on success, 0 otherwise
 */
int readHistory(info_t *info) {
    char *filename = getHistoryFile(info);
    if (!filename)
        return 0;

    int fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    struct stat st;
    if (fstat(fd, &st) == -1 || st.st_size < 2) {
        close(fd);
        return 0;
    }

    char *buf = malloc(st.st_size + 1);
    if (!buf) {
        close(fd);
        return 0;
    }

    ssize_t rdlen = read(fd, buf, st.st_size);
    buf[st.st_size] = '\0';
    close(fd);

    if (rdlen <= 0) {
        free(buf);
        return 0;
    }

    int linecount = 0, last = 0;
    for (int i = 0; i < st.st_size; i++) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            buildHistoryList(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != st.st_size)
        buildHistoryList(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);
    return info->histcount;
}

/**
 * buildHistoryList - Adds entry to a history linked list
 * @info: Structure containing potential arguments
 * @buf: Buffer
 * @linecount: The history line count
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int linecount) {
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumberHistory - Renumbers the history linked list after changes
 * @info: Structure containing potential arguments
 *
 * Return: The new histcount
 */
int renumberHistory(info_t *info) {
    list_t *node = info->history;
    int i = 0;

    while (node) {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}

