#include "../headers.h"

int count = 0; // for printing only if there is one match and e flag

char *get_path_seek(char *token, char *name)
{
    char *path = (char *)malloc(4096 * sizeof(char));
    strcpy(path, token);
    strcat(path, "/");
    strcat(path, name);
    return path;
}

void my_func_w_e_flag(char *file_name, char *dir_name, short e_flag, short f_flag, short d_flag)
{
    DIR *dir;
    struct dirent *ent;
    struct stat file_stat;

    if ((dir = opendir(dir_name)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] != '.' && stat(get_path_seek(dir_name, ent->d_name), &file_stat) == 0)
            {
                if (S_ISDIR(file_stat.st_mode))
                {
                    my_func_w_e_flag(file_name, get_path_seek(dir_name, ent->d_name), e_flag, f_flag, d_flag);
                }
                // if (strcmp(ent->d_name, file_name) == 0) // it is there
                if ((strncmp(ent->d_name, file_name, strlen(file_name)) == 0 && (ent->d_name[strlen(file_name)] == '\0' || ent->d_name[strlen(file_name)] == '.')))
                {
                    if (S_ISDIR(file_stat.st_mode))
                    {
                        chdir(get_path_seek(dir_name, ent->d_name));
                    }
                    else
                    {
                        FILE *fp;
                        fp = fopen(get_path_seek(dir_name, ent->d_name), "r");
                        if (fp == NULL)
                        {
                            // printf("error");
                            perror("fopen");
                            return;
                        }
                        char ch;
                        while ((ch = fgetc(fp)) != EOF)
                        {
                            printf("%c", ch);
                        }
                        fclose(fp);
                    }
                }
            }
        }
    }
    return;
}

void my_func_rec(char *file_name, char *dir_name, short e_flag, short f_flag, short d_flag)
{
    DIR *dir;
    struct dirent *ent;
    struct stat file_stat;

    if ((dir = opendir(dir_name)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] != '.' && stat(get_path_seek(dir_name, ent->d_name), &file_stat) == 0)
            {
                if (S_ISDIR(file_stat.st_mode))
                {
                    my_func_rec(file_name, get_path_seek(dir_name, ent->d_name), e_flag, f_flag, d_flag);
                }
                // if (strcmp(ent->d_name, file_name) == 0) // it is there
                if ((strncmp(ent->d_name, file_name, strlen(file_name)) == 0 && (ent->d_name[strlen(file_name)] == '\0' || ent->d_name[strlen(file_name)] == '.')))
                {
                    if (S_ISDIR(file_stat.st_mode))
                    {
                        printf("\033[0;34m./%s\033[0m\n", get_path_seek(dir_name, ent->d_name));
                        count++;
                    }
                    else
                    {
                        printf("\033[0;32m./%s\033[0m\n", get_path_seek(dir_name, ent->d_name));
                        count++;
                    }
                }
            }
        }
    }
    return;
}

void my_func(char *file_name, char *dir_name, short e_flag, short f_flag, short d_flag)
{
    DIR *dir;
    struct dirent *ent;
    struct stat file_stat;

    if ((dir = opendir(dir_name)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] != '.' && stat(get_path_seek(dir_name, ent->d_name), &file_stat) == 0)
            {
                if (S_ISDIR(file_stat.st_mode))
                {
                    my_func(file_name, get_path_seek(dir_name, ent->d_name), e_flag, f_flag, d_flag);
                }
                // if (strcmp(ent->d_name, file_name) == 0) // it is there
                if ((strncmp(ent->d_name, file_name, strlen(file_name)) == 0 && (ent->d_name[strlen(file_name)] == '\0' || ent->d_name[strlen(file_name)] == '.')))
                {
                    if (!f_flag & (S_ISDIR(file_stat.st_mode)))
                    {
                        printf("\033[0;34m%s\033[0m\n", get_path_seek(dir_name, ent->d_name));
                        count++;
                    }
                    else if (!d_flag & !(S_ISDIR(file_stat.st_mode)))
                    {
                        printf("\033[0;32m%s\033[0m\n", get_path_seek(dir_name, ent->d_name));
                        count++;
                    }
                }
            }
        }
    }
    return;
}

void my_func_home(char *file_name, char *dir_name, short e_flag, short f_flag, short d_flag)
{
    DIR *dir;
    struct dirent *ent;
    struct stat file_stat;

    if ((dir = opendir(dir_name)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] != '.' && stat(get_path_seek(dir_name, ent->d_name), &file_stat) == 0)
            {
                if (S_ISDIR(file_stat.st_mode))
                {
                    my_func_home(file_name, get_path_seek(dir_name, ent->d_name), e_flag, f_flag, d_flag);
                }
                // if (strcmp(ent->d_name, file_name) == 0) // it is there
                if ((strncmp(ent->d_name, file_name, strlen(file_name)) == 0 && (ent->d_name[strlen(file_name)] == '\0' || ent->d_name[strlen(file_name)] == '.')))
                {
                    if (!f_flag & (S_ISDIR(file_stat.st_mode)))
                    {
                        printf("\033[0;34m%s\033[0m\n", get_path_seek(dir_name, ent->d_name));
                        count++;
                    }
                    else if (!d_flag & !(S_ISDIR(file_stat.st_mode)))
                    {
                        printf("\033[0;32m%s\033[0m\n", get_path_seek(dir_name, ent->d_name));
                        count++;
                    }
                }
            }
        }
    }
    return;
}

// called from main
void seek(char *input, char *dir_from_which_shell_is_called)
{
    char input_full[strlen(input) + 1];
    strcpy(input_full, input);

    char *ptr = NULL;
    char *token = strtok_r(input_full, " \t\n", &ptr);
    token = strtok_r(NULL, " \t\n", &ptr);

    int count_of_arguments = 0;
    short count_of_flags = 0;

    while (token != NULL)
    {
        count_of_arguments++;
        if ((token[0] == '-') && (token[1] == 'e' || token[1] == 'd' || token[1] == 'f'))
            count_of_flags++;
        token = strtok_r(NULL, " \t\n", &ptr);
    }
    free(token);

    int count_of_non_flag_args = count_of_arguments - count_of_flags;

    char *ptr_2 = NULL;
    strcpy(input_full, input);
    char *token_2 = strtok_r(input_full, " \t\n", &ptr_2);
    token_2 = strtok_r(NULL, " \t\n", &ptr_2);

    short e_flag = 0;
    short d_flag = 0;
    short f_flag = 0;

    while (token_2 != NULL && count_of_flags > 0)
    {
        if (token_2[0] == '-')
        { // flag

            if (strlen(token_2) == 1 || strlen(token_2) > 3)
            {
                printf("Invalid flag!\n");
                return;
            }
            if (token_2[1] == 'e')
            {
                e_flag = 1;
                if (token_2[2] == 'd')
                    d_flag = 1;
                else if (token_2[2] == 'f')
                    f_flag = 1;
            }
            else if (token_2[1] == 'd')
            {
                d_flag = 1;
                if (token_2[2] == 'e')
                    e_flag = 1;
                if (token_2[2] == 'f')
                    f_flag = 1;
            }
            else if (token_2[1] == 'f')
            {
                f_flag = 1;
                if (token_2[2] == 'e')
                    e_flag = 1;
                if (token_2[2] == 'd')
                    d_flag = 1;
            }
            else
            {
                printf("Invalid flag!\n");
                return;
            }
        }
        else
        {
            break;
        }
        count_of_flags--;
        token_2 = strtok_r(NULL, " \t\n", &ptr_2);
    }

    if (d_flag && f_flag)
    {
        printf("Invalid flags!\n");
        return;
    }

    if (count_of_non_flag_args == 1)
    {
        // DIR *dir;
        // struct dirent *ent;
        // struct stat file_stat;

        my_func(token_2, ".", e_flag, f_flag, d_flag);
        // printf("%d", count);
        if (count == 1 && e_flag)
            my_func_w_e_flag(token_2, ".", e_flag, f_flag, d_flag);
    }

    else if (count_of_non_flag_args == 2)
    {
        char file_name[strlen(token_2)];
        strcpy(file_name, token_2);
        token_2 = strtok_r(NULL, " \t\n", &ptr_2);
        char dir_name[strlen(token_2)];
        strcpy(dir_name, token_2);

        if (dir_name[0] == '~')
        {
            // if (count == 1 && e_flag)
            //     printf("hi");
            //     // my_func_w_e_flag(file_name, dir_from_which_shell_is_called, e_flag, f_flag, d_flag);
            // else
                my_func(file_name, dir_from_which_shell_is_called, e_flag, f_flag, d_flag);
        }
        if (dir_name[0] == '.' && dir_name[1] != '.')
        {
            // my_func_home(file_name, ".", e_flag, f_flag, d_flag);
            my_func(file_name, ".", e_flag, f_flag, d_flag);
            printf("%d", count);

            // if (count == 1 && e_flag)
            //     // printf("hi");
            //     my_func_w_e_flag(file_name, ".", e_flag, f_flag, d_flag);
        }

        else
            my_func_rec(file_name, dir_name, e_flag, f_flag, d_flag);

        if (count == 1 && e_flag)
            my_func_w_e_flag(file_name, dir_name, e_flag, f_flag, d_flag);
    }

    else
    {
        printf("Invalid arguments!\n");
        return;
    }
    // printf("%d %d %d\n", e_flag, f_flag, d_flag);

    if (count == 0)
        printf("No matches found!\n");

    count = 0;

    return;
}