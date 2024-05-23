#include "../headers.h"

void ctrl_d()
{
    if (getpid() != shell_pid)
        printf("You are not calling this from inside the shell.\n");
    for (int i = 0; i < bg_process_count; i++)
    {
        kill(bg_process_array[i].pid, SIGKILL);
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}

void ctrl_z()
{
    if (getpid() != shell_pid)
        printf("You are not calling this from inside the shell.\n");
    if (!is_fg_running)
        return;
    if (fg_pid == shell_pid)
        return;
    int pid = fg_pid;
    // printf("%d, %d\n", pid, shell_pid);
    int k = kill(pid, SIGTSTP);

    setpgid(pid, pid);

    if (k == -1)
        perror("kill");
    bg_process_array[bg_process_count].pid = getpid();

    char *fg_proc_copy = malloc(sizeof(char) * (strlen(fg_proc) + 1));
    strcpy(fg_proc_copy, fg_proc);
    // printf("%s\n", fg_proc);
    bg_process_array[bg_process_count].command = (char *)malloc(sizeof(char) * (strlen(fg_proc) + 1));
    // strcpy(bg_process_array[bg_process_count].command, fg_proc);
    bg_process_array[bg_process_count].command = fg_proc_copy;
    bg_process_array[bg_process_count].running = 1;
    bg_process_count++;
    is_fg_running = 0;
    return;
}

void ctrl_c()
{
    if (getpid() != shell_pid)
        printf("You are not calling this from inside the shell.\n");
    if (is_fg_running)
    {
        kill(getpid(), SIGINT);
        is_fg_running = 0;
    }

    return;
}