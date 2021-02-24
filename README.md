# Project 1: System Inspector

## About the Project
This is a Unix utility that is used to inspect the system that it runs and create summarized report for the user. The summarized report includes information such as Hostname, Kernel Version, Type of CPU, Uptime, Load Average, CPU Usage, Memory Usage, Number of Tasks, Type of Tasks, and Statistics on the Tasks. The information is obtained by using proc, the process information pseudo-filesystem.

### Command Line Options
This options below are used to change the type of information that is display. Here is what it looks like to display the help/usage information:
```bash
[vmohan2@jar-jar-vm:~/P1-venkatrajm815]$ ./inspector -h
Usage: ./inspector [-ho] [-i interval] [-p procfs_dir]

Options:
    * -h              Display help/usage information
    * -i interval     Set the update interval (default: 1000ms)
    * -p procfs_dir   Set the expected procfs mount point (default: /proc)
    * -o              Operate in one-shot mode (no curses or live updates)
```
To compile and run:

```bash
make
./inspector
```
### How It Works
  * The system and hardware information that we get is from /proc directory. By simplying opening a specific path in the directory that contains the information, we can obtain the information we need by reading line by line using a file descriptor. Each function in procfs.c performs an unique method to get the right information from right location. 
  * Some functions are given special keywords to search in a line and are expected to return a value found on that line that corresponds to the information being searched for. Some built in String functions such ststr, strncmp, strcspn, strcat are used to locate the right index or check if a string matches what we are looking for. Tokens are utilized in some functions to allow us to obtain information quicker as we used char arrays to store tokens. For example, we use tokens to find the load average as the path /proc/loadavg contains multiple different numbers on one line. 
  * To find out more information on the /proc directory, you can check out 'man proc' which will require you to have installed man pages: pacman -Sy man-pages. Lots of the information that are displayed through this project can be displayed on your system individually by just doing a simple 'cat /proc/...' You can get information about your CPU by doing cat /proc/cpuinfo or information about memory usage by doing cat /proc/meminfo.

### The Files Included
There are 5 files included:
  * Makefile: This is what we use to compile each program together and make sure there are no errors.
  * procfs.c: This file has all the functions that contains information the System and the hardware such Hostname, Kernel Version, Type of CPU, Uptime, Load Average, CPU Usage, Memory Usage, Number of Tasks, Type of Tasks, and Statistics on the Tasks.
  * util.c: This file contains all the helper functions taht are used in procfs.c such functions that open a path, retrieve the next token, read a line from file descriptor, draw percentage bar for CPU and memory usage, and finding username from uid.
  * inspector.c: This is the main driver program which we use to print information to the user such as the example we saw above. It contains different types of options that you can toggle to get the type of output you are looking for.
  * display.c: This is where we display the information that we have found about the system. It makes function calls to the functions in procfs.c to get the information and then displays it.
    
## How To Build 
The first thing you need to build the project is get the Ubuntu Terminal for Windows 10 installed.
https://tutorials.ubuntu.com/tutorial/tutorial-ubuntu-on-windows#0
After doing that, you will have to Install WSL 2 which will allow you have the Linux environment on Windows.
Once you have you everything set up, you can clone this repository using either HTTPS or SSH.
```bash
# Compile all the files
make

# Run the inspector which will display the information on the system
./inspector
You can add extra flags/options to have it display what you want.
```

### Program Output
The project is still work in progress. Everything besides Tasks and Task Statistics are working.
```bash
Hostname: jar-jar-vm | Kernel Version: 5.10.11
CPU: AMD EPYC Processor (with IBPB), Processing Units: 2 
Uptime: 21 days, 10 hours, 8 minutes, 56 seconds 
Load Average (1/5/15 min): 0.00 0.00 0.00
CPU Usage:    [--------------------] 0.0%                                                                 
Memory Usage: [###-----------------] 16.8% (0.2 / 1.4 GB)                                                                         Tasks: 0 total
0 running, 0 waiting, 0 sleeping, 0 stopped, 0 zombie                                                                                   PID |                 Task Name |        State |            User  
----------+---------------------------+--------------+-----------------  
```

## Testing

To execute the test cases, use `make test`. To pull in updated test cases, run `make testupdate`. You can also run a specific test case instead of all of them:

```
# Run all test cases:
make test

# Run a specific test case:
make test run=4

# Run a few specific test cases (4, 8, and 12 in this case):
make test run='4 8 12'
```
