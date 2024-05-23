#include "../headers.h"

// base code given, expanding on that for this function
// called from main inside while(1)
void prompt(char *dir_from_which_shell_is_called)
{
    // Do not hardcode the prmopt

    char system_name[256];
    char username[256];
    char path[4096];

    // Get system name
    if (gethostname(system_name, sizeof(system_name)) == -1)
        perror("gethostname");

    // Get username
    if (getlogin_r(username, sizeof(username)) == -1)
        perror("getlogin");

    // Get current working directory
    if (getcwd(path, sizeof(path)) == NULL)
        perror("getcwd");

    // printf("<Everything is a file> ");
    // printf("check: %s", dir_from_which_shell_is_called);

    if (strlen(path) == strlen(dir_from_which_shell_is_called))
    {
        // printf("home dir\n");
        printf("<\033[1;36m%s\033[0m@\033[1;35m%s\033[0m:~> ", username, system_name);
        return;
    }
    else if (strlen(path) < strlen(dir_from_which_shell_is_called))
    {
        // printf("behind home dir\n");
        printf("<\033[1;36m%s\033[0m@\033[1;35m%s\033[0m:%s> ", username, system_name, path);
        return;
    }
    else if (strlen(path) > strlen(dir_from_which_shell_is_called))
    {
        char *check_if_front_of_home = strstr(path, dir_from_which_shell_is_called);
        if (check_if_front_of_home != NULL)
        {
            long unsigned int length_of_home_dir = strlen(dir_from_which_shell_is_called);
            char temp[strlen(path) - length_of_home_dir + 1];
            int j = 0;
            for (int i = length_of_home_dir; i < strlen(path); i++)
            {
                temp[j] = path[i];
                j++;
            }
            temp[j] = '\0';
            printf("<\033[1;36m%s\033[0m@\033[1;35m%s\033[0m:~%s> ", username, system_name, temp);
            return;
        }
    }
    return;
}