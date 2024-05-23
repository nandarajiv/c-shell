#include "../headers.h"

void ping(char *input_full)
{
    char *ptr = NULL;
    char *token = strtok_r(input_full, " \t\n", &ptr);
    // printf("%s\n", token); // ping
    token = strtok_r(NULL, " \t\n", &ptr);
    if (token == NULL)
    {
        printf("ping: pid not specified\n");
        return;
    }
    // printf("%s\n", token); // pid
    int pid = atoi(token);
    token = strtok_r(NULL, " \t\n", &ptr);
    if (token == NULL)
    {
        printf("ping: signal not specified\n");
        return;
    }
    // printf("%s\n", token); // sig
    int sig_raw = atoi(token);
    int sig = sig_raw % 32;

    // printf("%d %d\n", pid, sig);
    printf("Sent signal %d to process with pid %d\n", sig, pid);
    kill(pid, sig);

    return;
}