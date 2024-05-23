#include "../headers.h"

void activities()
{
    char proc_status[20];
    struct bg_process sorted_bg_process_array[bg_process_count];
    for (int i = 0; i < bg_process_count; i++)
    {
        sorted_bg_process_array[i] = bg_process_array[i];
    }
    qsort(sorted_bg_process_array, bg_process_count, sizeof(struct bg_process), activities_sort_fn);

    int status = 0;
    for (int i = 0; i < bg_process_count; i++)
    {
        if (sorted_bg_process_array[i].running == 0)
            continue;
        waitpid(sorted_bg_process_array[i].pid, &status, WNOHANG | WUNTRACED);
        if (WIFSTOPPED(status))
            strcpy(proc_status, "Stopped");
        else
            strcpy(proc_status, "Running");

        printf("%d : %s %s\n", sorted_bg_process_array[i].pid, sorted_bg_process_array[i].command, proc_status);
    }
    return;
}