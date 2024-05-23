#include "../headers.h"

// for printing when the -l flag is on, which gives details about the file
void print_lol(struct dirent *ent, struct stat file_stat)
{
    // permissions stuff
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    // number of links to file
    printf(" %3ld\t", file_stat.st_nlink);

    // owner of file
    int temp = file_stat.st_uid;
    struct passwd *pw = getpwuid(temp);
    printf("%s ", pw->pw_name);

    // group of a file
    temp = file_stat.st_gid;
    struct group *gr = getgrgid(temp);
    printf("%s ", gr->gr_name);

    // size of file
    printf("%7ld ", file_stat.st_size);
    struct tm* tm = localtime(&file_stat.st_mtime);
    printf("\t%d-%02d-%02d %02d:%02d  ", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);

    // file name
    if (S_ISDIR(file_stat.st_mode))
    {
        printf("\033[0;34m%s\033[0m\n", ent->d_name);
    }
    else if (S_IXUSR & file_stat.st_mode)
    {
        printf("\033[0;32m%s\033[0m\n", ent->d_name);
    }
    else
    {
        printf("%s\n", ent->d_name);
    }
}

// to pass into qsort for sorting into lexicographical order
int sort_fn(const void *file1, const void *file2)
{
    const struct dirent **f1 = (const struct dirent **)file1;
    const struct dirent **f2 = (const struct dirent **)file2;

    return strcmp((*f1)->d_name, (*f2)->d_name);
}

// get path
char *get_path(char *token, char *name)
{
    char *path = (char *)malloc((strlen(token) + 400) * sizeof(char));
    strcpy(path, token);
    strcat(path, "/");
    strcat(path, name);
    return path;
}

// printing output - this may or may not call print_lol in case of flags
void printing_the_print(struct dirent *ent, struct dirent **array_of_ents, DIR *dir, char *token, short a_flag, short l_flag, struct stat file_stat)
{
    if ((dir = opendir(token)) != NULL)
    {
        int i = 0;
        while ((ent = readdir(dir)) != NULL)
        {
            array_of_ents[i] = ent;
            i++;
        }
        // sort the array
        qsort(array_of_ents, i, sizeof(struct dirent *), sort_fn);
        for (int j = 0; j < i; j++)
        {
            if (array_of_ents[j]->d_name[0] == '.' && a_flag == 0)
                continue;
            // if (stat(array_of_ents[j]->d_name, file_stat) == 0)
            if (stat(get_path(token, array_of_ents[j]->d_name), &file_stat) == 0)
            {
                // stat("/home/nandarajiv/Public/nanda/iiit", file_stat);
                if (l_flag == 1)
                {
                    print_lol(array_of_ents[j], file_stat);
                }
                else
                {
                    if (S_ISDIR(file_stat.st_mode))
                    {
                        printf("\033[0;34m%s\033[0m\n", array_of_ents[j]->d_name);
                    }
                    else if (S_IXUSR & file_stat.st_mode)
                    {
                        printf("\033[0;32m%s\033[0m\n", array_of_ents[j]->d_name);
                    }
                    else
                    {
                        printf("%s\n", array_of_ents[j]->d_name);
                    }
                }
            }
            else
            {
                perror("stat");
            }
        }
    }
    else
    {
        perror("opendir");
    }
}

// main peek function which is called from main
void peek(char *input_full, char *dir_from_which_shell_is_called, char *previous_dir)
{
    char *ptr = NULL;
    char *token = strtok_r(input_full, " \t\n", &ptr);
    token = strtok_r(NULL, " \t\n", &ptr);

    DIR *dir;
    struct dirent *ent;
    struct stat file_stat;

    struct dirent **array_of_ents = (struct dirent **)malloc(500 * sizeof(struct dirent *));
    // struct dirent **array_of_ents;

    if (token == NULL)
    {
        // printf("case of just peek\n");
        printing_the_print(ent, array_of_ents, dir, ".", 0, 0, file_stat);
        return;
    }

    short a_flag = 0;
    short l_flag = 0;

    while (token != NULL && token[0] == '-')
    {
        if (strlen(token) == 1)
        {
            // printf("case of peek -\n");
            printing_the_print(ent, array_of_ents, dir, previous_dir, a_flag, l_flag, file_stat);
            return;
        }

        if (token[1] == 'a')
        {
            a_flag = 1;
            if (token[2] == 'l')
                l_flag = 1;
        }
        else if (token[1] == 'l')
        {
            l_flag = 1;
            if (token[2] == 'a')
                a_flag = 1;
        }
        else
            printf("Invalid flag, continuing regardless\n");
        token = strtok_r(NULL, " \t\n", &ptr);
    }

    if (token == NULL)
    {
        // printf("case of peek -flag\n");
        printing_the_print(ent, array_of_ents, dir, ".", a_flag, l_flag, file_stat);
        return;
    }

    if (strcmp(token, "~") == 0)
    {
        // printf("case of peek ~\n");
        printing_the_print(ent, array_of_ents, dir, dir_from_which_shell_is_called, a_flag, l_flag, file_stat);
        return;
    }

    // printf("%s\n", token);

    // printf("case of with some directory");
    printing_the_print(ent, array_of_ents, dir, token, a_flag, l_flag, file_stat);
    return;
}