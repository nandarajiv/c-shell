#include "../headers.h"

// called from main
void warp(char *input_full, char *dir_from_which_shell_is_called, char *previous_dir)
{
    char *where_to_warp_to = strtok(input_full, " \t\n");
    where_to_warp_to = strtok(NULL, " \t\n");

    char full_path[4096];
    getcwd(full_path, sizeof(full_path));

    if (where_to_warp_to == NULL || where_to_warp_to[0] == '\n' || where_to_warp_to[0] == '\t' || where_to_warp_to[0] == ' ')
    {
        strcpy(previous_dir, full_path);
        chdir("/");
        getcwd(full_path, sizeof(full_path));
        printf("%s\n", full_path);
        return;
    }

    else
    {
        while (where_to_warp_to != NULL)
        {
            // printf("%s\n", where_to_warp_to);
            if (strcmp(where_to_warp_to, "..") == 0)
            {
                strcpy(previous_dir, full_path);
                chdir("..");
                getcwd(full_path, sizeof(full_path));
                printf("%s\n", full_path);
            }

            else if (strcmp(where_to_warp_to, ".") == 0) // || strncmp(where_to_warp_to, ". ") == 0 || strncmp(where_to_warp_to, ".\t", 2) == 0)
            {
                strcpy(previous_dir, full_path);
                getcwd(full_path, sizeof(full_path));
                printf("%s\n", full_path);
            }

            else if (strncmp(where_to_warp_to, "~", 1) == 0)
            {
                strcpy(previous_dir, full_path);
                chdir(dir_from_which_shell_is_called);
                if (where_to_warp_to[1] == '/')
                {
                    // char temp[4096];
                    char *temp = (char *)malloc((strlen(where_to_warp_to) + 2) * sizeof(char));
                    strcpy(temp, where_to_warp_to + 1);
                    strcpy(where_to_warp_to, temp);
                    // free(temp);
                    goto hi;
                }
                getcwd(full_path, sizeof(full_path));
                printf("%s\n", full_path);
            }

            else if (strcmp(where_to_warp_to, "-") == 0)
            {
                // char temp_previous_dir[4096];
                char *temp_previous_dir = (char *)malloc((strlen(full_path) + 2) * sizeof(char));
                strcpy(temp_previous_dir, full_path);
                chdir(previous_dir);
                strcpy(previous_dir, temp_previous_dir);
                free(temp_previous_dir);
                getcwd(full_path, sizeof(full_path));
                printf("%s\n", full_path);
            }

            else
            {
            hi:
                strcpy(previous_dir, full_path);
                // printf("%s\n", where_to_warp_to);
                // char temp[4096];
                char *temp = (char *)malloc((strlen(where_to_warp_to) + 5) * sizeof(char));
                if (where_to_warp_to[0] != '/')
                {
                    strcpy(temp, "./");
                    strcat(temp, where_to_warp_to);
                }
                else
                {
                    // strcpy(temp, "/");
                    strcpy(temp, where_to_warp_to);
                }
                // printf("%s\n", temp);
                // printf("%s\n", temp);
                // printf("%c\n", temp[strlen(temp) - 1]);
                if (temp[strlen(temp) - 1] == '\n')
                {
                    // printf("hi");
                    temp[strlen(temp) - 1] = '\0';
                }
                else
                {
                    // printf("there");
                    temp[strlen(temp)] = '\0';
                }
                // printf("hi %shi", temp);
                // printf("%c", temp[strlen(temp) - 1]);
                if (chdir(temp) != -1)
                {
                    getcwd(full_path, sizeof(full_path));
                    printf("%s\n", full_path);
                }
                else
                {
                    printf("No such file or directory.\n");
                }
                free(temp);
            }
            where_to_warp_to = strtok(NULL, " \t\n");
        }
    }

    return;
}