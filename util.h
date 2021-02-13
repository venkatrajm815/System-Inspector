#ifndef _UTIL_H_
#define _UTIL_H_

#include <sys/types.h>

int open_path(char *proc_dir, char *path);
ssize_t lineread(int fd, char *buf, size_t sz);
void draw_percbar(char *buf, double frac);
void uid_to_uname(char *name_buf, uid_t uid);

#endif
