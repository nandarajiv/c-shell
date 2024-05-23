#include "../headers.h"

void getIO(char *token_semi, char *command, int *write_flag, int *append_flag, int *inp_redir_flag, char *inp_file, char *out_file)
{
    int i = 0;
    // for (; token_semi[i] != '\0'; i++)
    while (token_semi[i] != '\0')
    {
        if (token_semi[i] == '\t')
            continue;
        if (token_semi[i] == '>')
        {
            *write_flag = 1;
            if (token_semi[i + 1] == '>')
            {
                *append_flag = 1;
                i++;
            }
            break;
        }
        else if (token_semi[i] == '<')
        {
            *inp_redir_flag = 1;
            break;
        }
        command[i] = token_semi[i];
        i++;
    }
    // printf("i is %d\n", i);
    // char * ptr = strchr(command, '>');
    // *ptr = '\0';
    // if (command[i - 2] == ' ')
    //     command[i - 2] = '\0';
    if (command[i - 1] == ' ')
        command[i - 1] = '\0';
    else
        command[i] = '\0';

    if (*inp_redir_flag == 1)
    {
    in:;

        int j = 0;
        for (i = i + 1; token_semi[i] != '\0'; i++)
        {
            if (token_semi[i] == '>')
            {
                *write_flag = 1;
                goto out;
            }
            if (token_semi[i] == ' ')
            {
                continue;
            }
            if (token_semi[i] == '\t')
                continue;
            inp_file[j++] = token_semi[i];
        }

        inp_file[i - 1] = '\0';
    }

    else if (*write_flag == 1 || *append_flag == 1)
    {
    out:;
        int j = 0;
        for (i = i + 1; token_semi[i] != '\0'; i++)
        {
            if (token_semi[i] == '<')
            {
                *inp_redir_flag = 1;
                goto in;
            }
            if (token_semi[i] == ' ')
            {
                continue;
            }
            if (token_semi[i] == '\t')
                continue;
            out_file[j++] = token_semi[i];
        }
    }
    out_file[i - 1] = '\0';
}

// call from main
void execute_non_pe_func(char *token, char *token_semi, char *dir_from_which_shell_is_called, char *previous_dir)
{
    int write_flag = 0, append_flag = 0, inp_redir_flag = 0;
    char inp_file[200], out_file[200];

    char *command = (char *)malloc(sizeof(char) * (strlen(token_semi) + 1));

    getIO(token_semi, command, &write_flag, &append_flag, &inp_redir_flag, inp_file, out_file);
    // executePipe(token_semi, &append_flag, &inp_redir_flag, &write_flag, inp_file, out_file);

    // printf("command: %s\n", command);
    // printf("inp_file: %s\n", inp_file);
    // printf("out_file: %s\n", out_file);
    // printf("write_flag: %d\n", write_flag);
    // printf("append_flag: %d\n", append_flag);
    // printf("inp_redir_flag: %d\n", inp_redir_flag);

    int stdin_dup = dup(STDIN_FILENO);
    int stdout_dup = dup(STDOUT_FILENO);

    if (inp_redir_flag == 1)
    {
        if (access(inp_file, F_OK) == -1)
        {
            printf("File does not exist\n");
            return;
        }
        close(STDIN_FILENO);
        int fd = open(inp_file, O_RDONLY);
        if (fd == -1)
        {
            printf("inp_redir_flag");
            perror("open");
            return;
        }
    }
    if (append_flag == 1)
    {
        close(STDOUT_FILENO);
        int fd = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            printf("append_flag");
            perror("open");
            return;
        }
    }
    else if (write_flag == 1)
    {
        close(STDOUT_FILENO);
        int fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            printf("write_flag");
            perror("open");
            return;
        }
    }

    if (strcmp(token, "exit") == 0)
    {
        printf("bye :)\n");
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(token, "warp") == 0)
    {
        warp(command, dir_from_which_shell_is_called, previous_dir);
    }
    else if (strcmp(token, "peek") == 0)
    {
        peek(command, dir_from_which_shell_is_called, previous_dir);
    }
    else if (strcmp(token, "seek") == 0)
    {
        seek(command, dir_from_which_shell_is_called);
    }
    else if (strcmp(token, "proclore") == 0)
    {
        proclore(command);
    }
    else if (strcmp(token, "ping") == 0)
    {
        ping(command);
    }
    else if (strcmp(token, "activities") == 0)
    {
        activities();
    }
    else if (strcmp(token, "iMan") == 0)
    {
        iman(command);
    }
    else if (strcmp(token, "neonate") == 0)
    {
        neonate(command);
    }
    else if (strcmp(token, "fg") == 0)
    {
        fg(command);
    }
    else if (strcmp(token, "bg") == 0)
    {
        bg(command);
    }
    else
    {
        // system(token_semi);
        // fg_pid = getpid();
        tok_exec(command);
    }

    if (inp_redir_flag == 1)
    {
        close(STDIN_FILENO);
        dup2(stdin_dup, STDIN_FILENO);
    }
    if (write_flag == 1 || append_flag == 1)
    {
        fsync(STDOUT_FILENO);
        close(STDOUT_FILENO);
        dup2(stdout_dup, STDOUT_FILENO);
    }

    return;
}