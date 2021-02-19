#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "logger.h"
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open_path(char *proc_dir, char *path)
{
    LOG("Opening path: %s/%s\n", proc_dir, path);
    if(proc_dir == NULL || path == NULL){
	    errno = EINVAL;
	    return -1;
    }
    size_t path_len = strlen(proc_dir) + strlen(path) + 2;
    char *full_path = malloc( path_len * sizeof(char) );
    if(full_path == NULL){
	    return -1;
    }
    snprintf(full_path, path_len, "%s/%s", proc_dir, path);

    int fd = open(full_path, O_RDONLY);
    free(full_path);

    return fd;

}

char *next_token(char **str_ptr, const char *delim)
{
    if(*str_ptr == NULL){
	    return NULL;
    }
    size_t tok_start = strspn(*str_ptr, delim);
    size_t tok_end = strcspn(*str_ptr + tok_start, delim);

	   
    if (tok_end  == 0) {
	 *str_ptr = NULL;
	  return NULL;
    }
   
    char *current_ptr = *str_ptr + tok_start;

    *str_ptr += tok_start + tok_end;

    if (**str_ptr == '\0') {
	 *str_ptr = NULL;
    } else{
	 **str_ptr ='\0';
	 (*str_ptr)++;
    }
    return current_ptr;
}

ssize_t lineread(int fd, char *buf, size_t sz)
{ 
    size_t count = 0;    
    char c; 
		  
    while(count < sz){
	ssize_t read_l = read(fd, &c, 1);
	if(read_l < 0){
	    return read_l;
	}else{
	    buf[count] = c;
	    count += read_l;
	    if(c == '\n'){
		return count;
	    }
	}
    }
    return count;
}


void draw_percbar(char *buf, double frac)
{

}

void uid_to_uname(char *name_buf, uid_t uid)
{
    strcpy(name_buf, "(UNKNOWN)");
}
