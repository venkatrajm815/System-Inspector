#include "logger.h"
#include "procfs.h"
#include "util.h"
#include "string.h"

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
    return 0;
}

double pfs_uptime(char *proc_dir)
{
    return 0.0;
}

int pfs_format_uptime(double time, char *uptime_buf)
{
    return -1;
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
    return NULL;
}

void pfs_destroy_tstats(struct task_stats *tstats)
{

}

int pfs_tasks(char *proc_dir, struct task_stats *tstats)
{
    return -1;
}

