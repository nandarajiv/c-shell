#include "../headers.h"

int activities_sort_fn(const void *file1, const void *file2)
{
    struct bg_process *f1 = (struct bg_process *)file1;
    struct bg_process *f2 = (struct bg_process *)file2;
    return ((f1)->pid - (f2)->pid);
}