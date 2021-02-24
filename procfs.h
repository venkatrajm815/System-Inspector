/**
 * @file
 *
 * Retrieves raw information from procfs, parses it, and provides easy-to-use
 * functions for displaying the data.
 */

#ifndef _PROCFS_H_
#define _PROCFS_H_

#include <sys/types.h>

/**
 * Struct of doubles used to store the load average 
 */
struct load_avg {
    double one;
    double five;
    double fifteen;
};

/**
 * Struct of long integers that store idle and total time
 */
struct cpu_stats {
    long idle;
    long total;
};

/**
 * Struct of doubles that store used and total memory
 */
struct mem_stats {
    double used;
    double total;
};

/**
 * Struct of unsigned integers for numbers of tasks and nested struct for active tasks
 */
struct task_stats {
    unsigned int total;
    unsigned int running;
    unsigned int waiting;
    unsigned int sleeping;
    unsigned int stopped;
    unsigned int zombie;

    struct task_info *active_tasks;
};

/**
 * Struct with Information on tasks such as pid,uid, name of task, and the state of the task
 */
struct task_info {
    pid_t pid;
    uid_t uid;
    char name[26];
    char state[13];
};

/**
 * Finds hostname using the proc directory
 */
int pfs_hostname(char *proc_dir, char *hostname_buf, size_t buf_sz);

/**
 * Finds kernel version using the proc directory
 */
int pfs_kernel_version(char *proc_dir, char *version_buf, size_t buf_sz);

/**
 * Finds CPU Model by using the proc directory
 */
int pfs_cpu_model(char *proc_dir, char *model_buf, size_t buf_sz);

/**
 * Finds the number of processing units on the CPU
 */
int pfs_cpu_units(char *proc_dir);

/**
 * Finds the uptime of the machine 
 */
double pfs_uptime(char *proc_dir);

/**
 * Function that formats the uptime into years, months, days, hours, and seconds
 */
int pfs_format_uptime(double time, char *uptime_buf);

/**
 * Function that finds the load average of the machine
 */
struct load_avg pfs_load_avg(char *proc_dir);
/* Note: 'prev' is an input that represents the *last* CPU usage state. 'curr'
 * is an *output* that represents the current CPU usage state, and will be
 * passed back in to pfs_load_avg on its next call. */

/**
 * Calculates the CPU Usage by sampling over a period of time
 */
double pfs_cpu_usage(
        char *procfs_dir, struct cpu_stats *prev, struct cpu_stats *curr);

/**
 * Calculates the memory usage by finding the total and available memory
 */
struct mem_stats pfs_mem_usage(char *procfs_dir);

/**
 *  Function that creates task_stats structs
 */
/* Note: these two functions create and destroy task_stats structs. Depending on
 * your implementation, this might just be a malloc/free. */
struct task_stats *pfs_create_tstats();

/**
 *  Function that destroys task_stats structs
 */
void pfs_destroy_tstats(struct task_stats *tstats);

/**
 *  Function that finds that stats of the different tasks
 */
int pfs_tasks(char *proc_dir, struct task_stats *tstats);

#endif
