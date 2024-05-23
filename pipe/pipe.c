#include "../headers.h"

void execute_pipe(char *cmd_og, char *dir_from_which_shell_is_called, char *previous_dir)
{
    // printf("%shihi\n", cmd_og);
    int originalIn = dup(STDIN_FILENO);
    int originalOut = dup(STDOUT_FILENO);

    char *store = (char *)malloc(sizeof(char) * 1000);
    strcpy(store, cmd_og);

    int num_pipes = 0;
    char *count;
    char commands[100][1000];

    while (count = strtok_r(store, "|", &store))
    {
        strcpy(commands[num_pipes], count);
        num_pipes++;
    }

    // for (int i = 0; i < num_pipes; i++)
    // {
    //     printf("%s\n", commands[i]);
    // }

    // printf("\n\n");

    int pipes[num_pipes - 1][2];

    for (int i = 0; i < num_pipes; i++)
    {
        // printf("i is %d\n", i);
        if (i != num_pipes - 1)
        {
            pipe(pipes[i]);
        }

        if (i != 0)
        {
            dup2(pipes[i - 1][0], STDIN_FILENO);
        }
        else
        {
            dup2(originalIn, STDIN_FILENO);
        }

        if (i == num_pipes - 1)
        {
            dup2(originalOut, STDOUT_FILENO);
        }
        else
            dup2(pipes[i][1], STDOUT_FILENO);

        char *ptr = NULL;
        char *token = strtok_r(commands[i], " ", &ptr);

        if (strcmp(token, "exit") == 0)
        {
            printf("bye :)\n");
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(token, "warp") == 0)
        {
            warp(commands[i], dir_from_which_shell_is_called, previous_dir);
        }
        else if (strcmp(token, "peek") == 0)
        {
            peek(commands[i], dir_from_which_shell_is_called, previous_dir);
        }
        else if (strcmp(token, "seek") == 0)
        {
            seek(commands[i], dir_from_which_shell_is_called);
        }
        else if (strcmp(token, "proclore") == 0)
        {
            proclore(commands[i]);
        }
        else if (strcmp(token, "ping") == 0)
        {
            ping(commands[i]);
        }
        else if (strcmp(token, "activities") == 0)
        {
            activities();
        }
        else if (strcmp(token, "iMan") == 0)
        {
            iman(commands[i]);
        }
        else if (strcmp(token, "neonate") == 0)
        {
            neonate(commands[i]);
        }
        else if (strcmp(token, "fg") == 0)
        {
            fg(commands[i]);
        }
        else if (strcmp(token, "bg") == 0)
        {
            bg(commands[i]);
        }
        else
        {
            tok_exec(commands[i]);
        }

        // if (i != num_pipes - 1)
        // {
            close(pipes[i][1]);
            close(pipes[i - 1][0]);
        // }
    }
    dup2(originalIn, STDIN_FILENO);
    dup2(originalOut, STDOUT_FILENO);

    return;
}

// void execute_pipe(char *cmd_og, char *dir_from_which_shell_is_called, char *previous_dir)
// {
//     // printf("%shihi\n", cmd_og);
//     int originalIn = dup(STDIN_FILENO);
//     int originalOut = dup(STDOUT_FILENO);

//     char *store = (char *)malloc(sizeof(char) * 1000);
//     strcpy(store, cmd_og);

//     int num_pipes = 0;
//     char *count;
//     char commands[100][1000];

//     while (count = strtok_r(store, "|", &store))
//     {
//         strcpy(commands[num_pipes], count);
//         num_pipes++;
//     }

//     // for (int i = 0; i < num_pipes; i++)
//     // {
//     //     printf("%s\n", commands[i]);
//     // }

//     // printf("\n\n");

//     int pipes[num_pipes - 1][2];

//     for (int i = 0; i < num_pipes; i++)
//     {
//         // printf("i is %d\n", i);
//         if (i != num_pipes - 1)
//         {
//             pipe(pipes[i]);
//             dup2(pipes[i][1], STDOUT_FILENO);
//         }
//         else
//         {
//             dup2(originalOut, STDOUT_FILENO);
//         }
//         if (i != 0)
//         {
//             dup2(pipes[i - 1][0], STDIN_FILENO);
//         }

//         dup2(pipes[i][1], STDOUT_FILENO);
//         // else
//         // {
//         //     dup2(originalIn, STDIN_FILENO);
//         // }
//         char *ptr = NULL;
//         char *token = strtok_r(commands[i], " ", &ptr);
//         // printf("%s\n", token);
//         // printf("i is %d, %s\n", i, commands[i]);

//         // execute_non_pe_func_piped(token, commands[i], dir_from_which_shell_is_called, previous_dir, num_pipes, i);
//         if (strcmp(token, "exit") == 0)
//         {
//             printf("bye :)\n");
//             exit(EXIT_SUCCESS);
//         }
//         else if (strcmp(token, "warp") == 0)
//         {
//             warp(commands[i], dir_from_which_shell_is_called, previous_dir);
//         }
//         else if (strcmp(token, "peek") == 0)
//         {
//             peek(commands[i], dir_from_which_shell_is_called, previous_dir);
//         }
//         else if (strcmp(token, "seek") == 0)
//         {
//             seek(commands[i], dir_from_which_shell_is_called);
//         }
//         else if (strcmp(token, "proclore") == 0)
//         {
//             proclore(commands[i]);
//         }
//         else if (strcmp(token, "ping") == 0)
//         {
//             ping(commands[i]);
//         }
//         else if (strcmp(token, "activities") == 0)
//         {
//             activities();
//         }
//         else if (strcmp(token, "iMan") == 0)
//         {
//             iman(commands[i]);
//         }
//         else if (strcmp(token, "neonate") == 0)
//         {
//             neonate(commands[i]);
//         }
//         else if (strcmp(token, "fg") == 0)
//         {
//             fg(commands[i]);
//         }
//         else if (strcmp(token, "bg") == 0)
//         {
//             bg(commands[i]);
//         }
//         else
//         {
//             // system(token_semi);
//             // fg_pid = getpid();
//             tok_exec(commands[i]);
//             // printf("%s\n", commands[i]);

//             // if (num_pipes == 1)
//             // {
//             //     dup2(originalOut, STDOUT_FILENO);
//             // }
//             // else
//             // {
//             //     dup2(pipes[i][1], STDOUT_FILENO);
//             // }
//         }

//         close(pipes[i][1]);
//         close(pipes[i - 1][0]);
//     }
//     dup2(originalIn, STDIN_FILENO);
//     dup2(originalOut, STDOUT_FILENO);

//     return;
// }
