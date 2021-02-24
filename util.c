#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "logger.h"
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * This function opens the path in the proc directory
 * @param proc_dir This is the path to /proc
 * @param path     This is the path we use to check within the proc directory
 *
 * @returns        Returns a non-negative integer unless there was an error, where it would return -1
 *
 */
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

/**
 * Retrieves the next token from a string.
 *
 * @param str_ptr Maintains context in the string, i.e., where the next token in the string will be. If the function returns token N, then str_ptr will be updated to point to token N+1. To initialize, declare a char * that points to the string being tokenized. The pointer will be updated after each successive call to next_token.
 * @param delim   the set of characters to use as delimiters
 *
 * @returns       char pointer to the next token in the string.
 *
 */

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

/**
 * Reads a line from a file descriptor and copies its contents into a buffer
 *
 * @param fd the file descriptor to read from
 * @param buf where data being read will be copied
 * @param sz the maximum number of bytes to read
 *
 * @return number of bytes read, 0 if EOF is reached, -1 on error
 */
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

/**
 * Draws a percentage bar by adding to the buffer and using the frac to fill out the bar
 * 
 * @param buf  Destination buffer to copy the bar contents
 * @param frac the percentage in fraction form that shows how much of the bar to fill out       
 */
void draw_percbar(char *buf, double frac)
{
    buf[0] = '\0';
    int num_signs = 0;
    LOG("Frac before: %f\n", frac);  
    char percentage[30];
    double frac_perc = 100 * frac;
 
    if(frac <= 0.0 || isnan(frac)){
	 num_signs = 0;
	 frac_perc = 0.0;
    }else if(frac >= 1.0){
	 num_signs = round(1.0 * 100);
         frac_perc = 100.0;
    }else{
	 num_signs = round(frac * 100);
    }

    LOG("Frac after: %i\n", num_signs);  

    strcat(buf, "["); 
    for(int i = 1 ; i <= 20 ; i++){
	   if(i * 5 <= num_signs){
	  	strcat(buf, "#");	
	   }else{
           	strcat(buf, "-");
	   }
    } 
    strcat(buf, "]");

    snprintf(percentage, 30, "%.1f", frac_perc);
   
    strcat(buf, " ");
    strcat(buf, percentage);
    strcat(buf, "%");
    
    buf[strlen(buf) + 1] = '\0';

}

/**
 * Finds the username associated with UID, if not found stores the UID as the username
 *
 * @param name_buf The buffer we use to copy the username contents found by the uid
 * @param uid      The identification that we use to locate the username in /etc/passwd
 *
 */
void uid_to_uname(char *name_buf, uid_t uid)
{
    int fd = open("/etc/passwd",O_RDONLY);
    if(fd == -1){
	    perror("Error Opening File");
    }

    char line[512] = { 0 };
    name_buf[0] = '\0'; 
    ssize_t read_sz;
    
    char *search = malloc(30);
    //LOG("The UID is : %u", uid);
    sprintf(search, "%u", uid);
     
    while((read_sz = lineread(fd, line, 512)) > 0){
   	 char *next;
  	 char *first_tok;
	 char *third_tok;

         next = line;
	 first_tok = next_token(&next,":");
	 next_token(&next,":");
	 third_tok = next_token(&next,":");

	 if(strcmp(search, third_tok) == 0){
	      LOG("Found it! The username is : %s\n", first_tok);
	      first_tok[15] = '\0';
	      strcpy(name_buf, first_tok);
	      break;
	 }
    }
    if(name_buf[0] == '\0'){
	   strcpy(name_buf,search);
    } 
    free(search); 
    close(fd);
}
