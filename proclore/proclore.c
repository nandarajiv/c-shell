#include "../headers.h"

// called from main
void proclore(char *input_full)
{
    char *ptr = NULL;
    char *token = strtok_r(input_full, " \t\n", &ptr);
    // printf("%s\n", token);
    token = strtok_r(NULL, " \t\n", &ptr);
    int pid;
    if (token == NULL)
        pid = getpid();
    else
    {
        // printf("%s\n", token);
        pid = atoi(token);
    }
    // printf("%d\n", pid);
    char proc_path[500];
    sprintf(proc_path, "/proc/%d/stat", pid);

    FILE *fp = fopen(proc_path, "r");
    if (fp == NULL)
    {
        perror("No such process currently");
        return;
    }
    int vm_size, group_pid, fg_id;
    char proc_state;

    fscanf(fp, "%*s %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d", &proc_state, &group_pid, &fg_id, &vm_size);

    // char line[1024];
    printf("Pid: %d\n", pid);
    printf("State: %c", proc_state);

    int pgid = getpgid(pid);
    // printf("%d %d", pgid, group_pid);

    // get whether a process is foreground or background - foreground means + symbol is there
    // struct termios oldTermios;
    // tcgetattr(STDIN_FILENO, &oldTermios);
    // tcsetpgrp(STDIN_FILENO, pgid);
    // pid_t tgrp = tcgetpgrp(STDIN_FILENO);
    // tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
    // printf("State: %c", proc_state);
    // above code was giving bugs

    if (fg_id == group_pid)
        printf("+\n");
    else
        printf("\n");

    printf("Process Group: %d\n", getpgid(pid));

    printf("Virtual Memory: %d\n", vm_size);

    fclose(fp);

    char exe_path[1024];
    sprintf(exe_path, "/proc/%d/exe", pid);

    char resolve_path[1024];
    ssize_t len = readlink(exe_path, resolve_path, sizeof(resolve_path) - 1);
    if (len != -1)
        resolve_path[len] = '\0';
    else
        return;

    printf("Executable Path: %s\n", resolve_path);

    return;
}
