#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "./prompt/prompt.h"
#include "./peek/peek.h"
#include "./seek/seek.h"
#include "./warp/warp.h"
#include "./pastevents/pastevents.h"
#include "./proclore/proclore.h"
#include "./execute_non_pe/execute.h"
#include "./iman/iman.h"
#include "./activities_sort/activities_sort.h"
#include "./ping/ping.h"
#include "./signals/signals.h"
#include "./tokenize_and_exec/tokenize_and_exec.h"
#include "./activities/activities.h"
#include "./neonate/neonate.h"
#include "./fg_bg/fg_bg.h"

struct bg_process
{
    int pid;
    char *command;
    short running;
};

extern struct bg_process bg_process_array[1000];
extern int bg_process_count;

extern int shell_pid;
extern int is_fg_running;
extern char fg_proc[200];
extern int fg_pid;

extern int pipes[100][2];

void executePipe(char *cmd, int *apflag, int *inflag, int *outflag, char *inputFile, char *outputFile);
void execute_pipe(char *cmd_og, char *dir_from_which_shell_is_called, char *previous_dir);

#endif