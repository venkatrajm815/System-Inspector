#ifndef _UTIL_H_
#define _UTIL_H_

#include <sys/types.h>

/**
 * This function opens the path in the proc directory
 *
 * @param proc_dir This is the path to /proc
 * @param path     This is the path we use to check within the proc directory
 *
 *
 * @returns        Returns a non-negative integer unless there was an error, where it would return -1
 *
 */
int open_path(char *proc_dir, char *path);

/**
 *  Retrieves the next token from a string.
 *
 *  @param str_ptr Maintains context in the string, i.e., where the next token in the string will be. If the function returns token N, then str_ptr will be updated to point to token N+1. To initialize, declare a char * that points to the string being tokenized. The pointer will be updated after each successive call to next_token.
 *  @param delim   the set of characters to use as delimiters
 *
 *  @returns       char pointer to the next token in the string.
 *
 */        
char *next_token(char **str_ptr, const char *delim);

/**
 * Reads a line from a file descriptor and copies its contents into a buffer
 *
 * @param fd the file descriptor to read from
 * @param buf where data being read will be copied
 * @param sz the maximum number of bytes to read
 *
 * @returns number of bytes read, 0 if EOF is reached, -1 on error
 *
 */
ssize_t lineread(int fd, char *buf, size_t sz);

/**
 * Draws a percentage bar by adding to the buffer and using the frac to fill out the bar
 *
 * @param buf  Destination buffer to copy the bar contents
 * @param frac the percentage in fraction form that shows how much of the bar to fill out
 *
 */       
void draw_percbar(char *buf, double frac);

/**
 * Finds the username associated with UID, if not found stores the UID as the username
 *
 * @param name_buf The buffer we use to copy the username contents found by the uid
 * @param uid      The identification that we use to locate the username in /etc/passwd
 *
 */
void uid_to_uname(char *name_buf, uid_t uid);

#endif
