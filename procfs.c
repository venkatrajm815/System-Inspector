#include "logger.h"
#include "procfs.h"
#include "util.h"
#include "string.h"
#include <stdlib.h>

int pfs_hostname(char *proc_dir, char *hostname_buf, size_t buf_sz)
{
    int fd = open_path(proc_dir, "sys/kernel/hostname");
    if(fd == -1){
	    perror("open_path");
	    return -1;
    }
    ssize_t read_sz = lineread(fd, hostname_buf, buf_sz);
    if(read_sz == -1){
	    return -1;
    }
    close(fd);
    hostname_buf[read_sz - 1] = '\0';
    return 0;
}

int pfs_kernel_version(char *proc_dir, char *version_buf, size_t buf_sz)
{
    int fd = open_path(proc_dir, "sys/kernel/osrelease");
    if(fd == -1){
	    perror("open_path");
	    return -1;
    }
    ssize_t read_sz = lineread(fd, version_buf, buf_sz);
    if(read_sz == -1){
	    return -1;
    }
    close(fd);
    size_t dash_loc = strcspn(version_buf, "-");
    version_buf[dash_loc] = '\0';
    return 0;

}

int pfs_cpu_model(char *proc_dir, char *model_buf, size_t buf_sz)
{
    int fd = open_path(proc_dir, "cpuinfo");
    if(fd == -1){
	    perror("open_path");
	    return -1;
    }
    /* Model buf is going to be 128 characters display.c so we'll use that plus a little extra */
    char line[256] = { 0 };
    
    ssize_t read_sz;
  
    char *search = "model name";
    while((read_sz = lineread(fd, line, 256)) > 0){
	if(strncmp(line, search, strlen(search)) == 0){
    	    //LOG("Found it !-> %s\n", line);
	    size_t model_loc = strcspn(line, ":") + 2;
	    size_t newline_loc = strcspn(&line[model_loc], "\n");
	    if(newline_loc > buf_sz){
		newline_loc = buf_sz;
	    }
	    strncpy(model_buf, &line[model_loc], newline_loc);
	    break;
	}

    }
    if(read_sz == -1){
	return -1;
    }
    close(fd); 
    return 0;
}

int pfs_cpu_units(char *proc_dir)
{
    int fd = open_path(proc_dir, "cpuinfo");
    if(fd == -1){
	    perror("open_path");
	    return -1;
    }
    /* Model buf is going to be 128 characters display.c so we'll use that plus a little extra */
    char line[256] = { 0 };
    
    ssize_t read_sz;
  
    char *search = "siblings";
    while((read_sz = lineread(fd, line, 256)) > 0){
	if(strncmp(line, search, strlen(search)) == 0){
	    size_t model_loc = strcspn(line, ":") + 2;
	    return atoi(&line[model_loc]) * 2;
	}
    }
    if(read_sz == -1){
	return -1;
    }
    close(fd);
    return 0;
}

double pfs_uptime(char *proc_dir)
{
    int fd = open_path(proc_dir, "uptime");
    if(fd == -1){
	    perror("open_path");
	    return -1;
    }
    char *next;
    char *first_tok; 
    char line[512] = { 0 };

    lineread(fd, line, 512);
    next = line;
    first_tok = next_token(&next," ");
    double uptime = atof(first_tok);

    close(fd);
    return uptime;
     
}

int pfs_format_uptime(double time, char *uptime_buf)
{
    int years = (int)time / (3600 * 365 * 24);
    time = (int)time % (3600 * 365 * 24);

    int days = (int)time / (3600 * 24);
    time = (int)time % (3600 * 24);

    int hours = (int)time / (3600);
    time = (int)time % (3600);

    int minutes = (int)time / (60);
    time = (int)time % (60);

    int seconds = (int)time; 

    char time_buf[512] = { 0 };
    char temp_num[256] = { 0 };
      

    if(years > 0){
	    sprintf(temp_num, "%d", years);
	    strcat(time_buf, temp_num); 
	    strcat(time_buf, " years,");
    }
    if(days > 0){
	    sprintf(temp_num, "%d", days);
	    strcat(time_buf, temp_num);
	    strcat(time_buf, " days, ");

    }
    if(hours > 0){
	    sprintf(temp_num, "%d", hours);
	    strcat(time_buf, temp_num);
	    strcat(time_buf, " hours, ");
    }

    //Minutes
    sprintf(temp_num, "%d", minutes);
    strcat(time_buf, temp_num); 
    strcat(time_buf, " minutes, ");
 
    //Seconds
    sprintf(temp_num, "%d", seconds);
    strcat(time_buf, temp_num); 
    strcat(time_buf, " seconds");
    
    //Zeroing out to remove garbage values
    uptime_buf[0] = '\0';

    strcat(uptime_buf, time_buf);

    return 0;
}

struct load_avg pfs_load_avg(char *proc_dir)
{
   struct load_avg lavg = { 0 };
   return lavg;
}

double pfs_cpu_usage(char *proc_dir, struct cpu_stats *prev, struct cpu_stats *curr)
{
    return 0.0;
}

struct mem_stats pfs_mem_usage(char *proc_dir)
{
    struct mem_stats mstats = { 0 };
    return mstats;
}

struct task_stats *pfs_create_tstats()
{
    struct task_stats *ts = calloc(1, sizeof(struct task_stats));
    if(ts != NULL){
	ts->active_tasks = calloc(100, sizeof(struct task_info));
    }	
    return ts;
}

void pfs_destroy_tstats(struct task_stats *tstats)
{

}

int pfs_tasks(char *proc_dir, struct task_stats *tstats)
{
    return -1;
}

