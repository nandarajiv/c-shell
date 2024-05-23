#include "../headers.h"

int tokenize_and_get_pid(char* input_full)
{
    char *ptr = NULL;
    char *token = strtok_r(input_full, " \t\n", &ptr);
    token = strtok_r(NULL, " \t\n", &ptr);
    int pid;
    if (token == NULL)
    {
        printf("No pid given\n");
        return -1;
    }
    else
    {
        pid = atoi(token);
    }
    return pid;
}

void fg(char *input_full)
{
    // char *ptr = NULL;
    // char *token = strtok_r(input_full, " \t\n", &ptr);
    // token = strtok_r(NULL, " \t\n", &ptr);
    // int pid;
    // if (token == NULL)
    // {
    //     printf("No pid given\n");
    //     return;
    // }
    // else
    // {
    //     pid = atoi(token);
    // }
    int pid = tokenize_and_get_pid(input_full);
    int check_if_present = 0;
    for (int i = 0; i < bg_process_count; i++)
    {
        if (bg_process_array[i].pid == pid)
        {
            check_if_present = 1;
            break;
        }
    }
    if (check_if_present == 0)
    {
        printf("No such process found.\n");
        return;
    }

    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);

    int t = tcsetpgrp(0, pid);
    if (t == -1)
        perror("tcsetpgrp");

    is_fg_running = 1;
    int k = kill(pid, SIGCONT);
    if (k == -1)
        perror("kill");

    int stat;
    // printf("here\n");
    int w = waitpid(pid, &stat, WUNTRACED);
    is_fg_running = 0;

    if (w == -1)
        perror("waitpid");

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);

    int t1 = tcsetpgrp(0, shell_pid);
    // printf("here2\n");
    if (t1 == -1)
        perror("tcsetpgrp");

    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);

    return;
}

void bg(char* input_full)
{
    int pid = tokenize_and_get_pid(input_full);
    int check_if_present = 0;

    for (int i = 0 ; i < bg_process_count; i++)
    {
        if (bg_process_array[i].pid == pid)
        {
            check_if_present = 1;
            int k = kill(pid, SIGCONT);
            if (k == -1)
                perror("kill");
            return;
        }
    }
    if (check_if_present == 0)
    {
        printf("No such process found.\n");
        return;
    }
    return;

}