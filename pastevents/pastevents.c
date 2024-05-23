#include "../headers.h"

// this is for when 'pastevents' is called - just prints the entire contents of the file
void print_pastevents(char *dir_from_which_shell_is_called)
{
    char path[4096];
    strcpy(path, dir_from_which_shell_is_called);
    strcat(path, "/pastevents/pastevents.txt");
    // printf("%s\n", path);

    FILE *fp;
    fp = fopen(path, "r+");
    if (fp == NULL)
    {
        printf("No commands yet on the shell!\n"); // this occurs if the file's never been created before, which occurs when shell hasn't received any commands
        return;
    }
    char line[100];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    fclose(fp);

    return;
}

// when any non pastevents command is called, has to be written in pastevents.txt, including & ; containing commands
void write_pastevents(char *command, char *dir_from_which_shell_is_called)
{
    char path[4096];
    strcpy(path, dir_from_which_shell_is_called);
    strcat(path, "/pastevents/pastevents.txt");
    // printf("%s\n", path);

    char path_temp[4096];
    strcpy(path_temp, dir_from_which_shell_is_called);
    strcat(path_temp, "/pastevents/temp.txt");

    // printf("%s\n", command);

    if (strcmp(command, "\n") == 0)
        return;
    FILE *fp;
    fp = fopen(path, "a+");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }
    int lines = 0;
    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        lines++;
    }
    for (int i = 0; i < lines; i++)
    {
        fgets(line, sizeof(line), fp);
    }
    fgets(line, sizeof(line), fp);

    // printf("%s", line);
    if (strcmp(line, command) == 0)
    {
        // printf("same command\n");
        fclose(fp);
        return;
    }
    if (lines == 15)
    {
        // printf("at limit\n");
        fseek(fp, 0, SEEK_SET);
        FILE *fp_temp;
        fp_temp = fopen(path_temp, "w+");
        if (fp_temp == NULL)
        {
            perror("fopen");
            return;
        }
        fgets(line, sizeof(line), fp);

        while (fgets(line, sizeof(line), fp) != NULL)
        {
            fprintf(fp_temp, "%s", line);
        }
        fclose(fp);
        fprintf(fp_temp, "%s", command);
        fclose(fp_temp);
        rename(path_temp, path);

        return;
    }

    fprintf(fp, "%s", command);
    fclose(fp);
    return;
}

// for pastevents purge command, to empty the existing pastevents.txt file
void clear_pastevents(char *dir_from_which_shell_is_called)
{

    char path[4096];
    strcpy(path, dir_from_which_shell_is_called);
    strcat(path, "/pastevents/pastevents.txt");
    // printf("%s\n", path);

    FILE *fp;
    fp = fopen(path, "w+");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }
    fclose(fp);
    return;
}

// for pastevents execute <number>, sets the char *cmd to the old command that is required to be redone
void exec_pastevents(char *cmd, int n, char *dir_from_which_shell_is_called)
{
    char path[4096];
    strcpy(path, dir_from_which_shell_is_called);
    strcat(path, "/pastevents/pastevents.txt");
    // printf("%s\n", path);

    FILE *fp;
    fp = fopen(path, "r+");

    if (fp == NULL)
    {
        perror("fopen");
        return;
    }

    int lines = 0;
    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        lines++;
    }

    fclose(fp);
    fp = fopen(path, "r+");
    char line_2[100];

    for (int i = 0; i < lines - n; i++)
    {
        fgets(line_2, sizeof(line_2), fp);
    }

    fgets(line, sizeof(line_2), fp);
    strcpy(cmd, line);
    fclose(fp);

    return;
}