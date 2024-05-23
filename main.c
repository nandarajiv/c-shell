#include "headers.h"

// struct bg_process *bg_process_array;
struct bg_process bg_process_array[1000];
int bg_process_count = 0;
int shell_pid = 0;
int is_fg_running = 0;
int fg_pid = 0;
char fg_proc[200];
// int bg_process_i = 0;

void print_bg_process_exit()
{
    for (int i = 0; i < bg_process_count; i++)
    {
        if (bg_process_array[i].running == 0)
            continue;
        if ((waitpid(bg_process_array[i].pid, NULL, WNOHANG)) == 0)
            continue;
        else
        {
            bg_process_array[i].running = 0;
            printf("%s exited normally (%d)\n", bg_process_array[i].command, bg_process_array[i].pid);
            // bg_process_i++;
        }
    }
}

int main()
{
    shell_pid = getpid();
    // bg_process_array = (struct bg_process *)malloc(100 * sizeof(struct bg_process));
    char dir_from_which_shell_is_called[4096];
    if (getcwd(dir_from_which_shell_is_called, sizeof(dir_from_which_shell_is_called)) == NULL)
        perror("getcwd");

    char previous_dir[4096];
    strcpy(previous_dir, dir_from_which_shell_is_called);

    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrl_z);

    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(dir_from_which_shell_is_called);
    after_time:
        char input[4096];
        char *s = (char *)malloc(sizeof(char) * 4096);
        s = fgets(input, 4096, stdin);

        if (s == NULL)
        {
            ctrl_d();
        }

        print_bg_process_exit(); // if any

        char *input_tok_semi = (char *)malloc(sizeof(char) * (strlen(input) + 3));
        strcpy(input_tok_semi, input);
        char *tokenize_ptr_semi = NULL;

        if (strstr(input_tok_semi, "pastevents") == NULL)
            write_pastevents(input_tok_semi, dir_from_which_shell_is_called);
    here:
        char *token_semi = strtok_r(input_tok_semi, ";\n", &tokenize_ptr_semi);

        while (token_semi != NULL)
        {
            char *input_tok_tok = (char *)malloc(sizeof(char) * (strlen(token_semi) + 3));
            strcpy(input_tok_tok, token_semi);
            int count_amp = 0;

            for (int i = 0; i < strlen(input_tok_tok); i++)
                if (input_tok_tok[i] == '&')
                    count_amp++;

            char *tokenize_ptr_amp = NULL;

            char *token_amp = strtok_r(input_tok_tok, "&\n", &tokenize_ptr_amp);

            while (token_amp != NULL)
            {
                if (count_amp != 0)
                {
                    char *token_amp_copy_to_count = (char *)malloc((strlen(token_amp) + 1) * sizeof(char));
                    strcpy(token_amp_copy_to_count, token_amp);
                    char *child_tokenizer_to_count = NULL;
                    char *child_token_to_count = strtok_r(token_amp_copy_to_count, " \t\n", &child_tokenizer_to_count);
                    int count_tokens = 0;
                    while (child_token_to_count != NULL)
                    {
                        // printf("this is child_token_to_count %s", child_token_to_count);
                        count_tokens++;
                        child_token_to_count = strtok_r(NULL, " \t\n", &child_tokenizer_to_count);
                    }
                    free(child_token_to_count);

                    // char array_of_tokens[count_tokens][100];
                    char *array_of_tokens[count_tokens + 1];
                    for (int i = 0; i < count_tokens; i++)
                        array_of_tokens[i] = (char *)malloc(sizeof(char) * 100);

                    char *token_amp_copy = (char *)malloc((strlen(token_amp) + 1) * sizeof(char));
                    strcpy(token_amp_copy, token_amp);
                    char *child_tokenizer = NULL;
                    char *child_token = strtok_r(token_amp_copy, " \t\n", &child_tokenizer);
                    // printf("hi i am working\n");
                    for (int i = 0; i < count_tokens; i++)
                    {
                        strcpy(array_of_tokens[i], child_token);
                        child_token = strtok_r(NULL, " \t\n", &child_tokenizer);
                    }

                    // printf("\nhi i am trying to print the array of tokens\n");
                    // for (int i = 0; i < count_tokens; i++)
                    // {
                    //     printf("%s\n", array_of_tokens[i]);
                    // }

                    // printf("\n\n\n");
                    // do the bg process protocol
                    int pid = fork();
                    if (pid == -1)
                        printf("fork fail");
                    else if (pid == 0) // it is child
                    {
                        setpgid(0, 0);
                        array_of_tokens[count_tokens] = NULL;
                        execvp(array_of_tokens[0], array_of_tokens);
                    }
                    else // it is parent
                    {
                        bg_process_array[bg_process_count].pid = pid;
                        bg_process_array[bg_process_count].command = (char *)malloc(sizeof(char) * (strlen(token_amp) + 1));
                        bg_process_array[bg_process_count].running = 1;
                        strcpy(bg_process_array[bg_process_count].command, token_amp);
                        bg_process_count++;
                    }
                    printf("%d\n", pid);
                    token_amp = strtok_r(NULL, "&\n", &tokenize_ptr_amp);
                }
                else
                {
                    is_fg_running = 1;
                    strcpy(fg_proc, token_amp);

                    time_t start, end;
                    start = time(NULL);
                    char *input_tok = (char *)malloc(sizeof(char) * (strlen(token_amp) + 3));
                    strcpy(input_tok, token_amp);

                    char *tokenize_ptr = NULL;

                    char *token = strtok_r(input_tok, " \t\n", &tokenize_ptr);

                    char *token_copy_for_time = (char *)malloc(sizeof(char) * (strlen(token) + 3));
                    strcpy(token_copy_for_time, token);

                    if (token == NULL)
                        break;

                    int is_there_piping = 0;
                    for (int i = 0; i < strlen(token_amp); i++)
                    {
                        if (token_amp[i] == '|')
                        {
                            is_there_piping = 1;
                            break;
                        }
                    }

                    if (strcmp(token, "pastevents") == 0)
                    {
                        token = strtok_r(NULL, " \t\n", &tokenize_ptr);

                        if (token == NULL)
                        {
                            print_pastevents(dir_from_which_shell_is_called);
                            token_amp = strtok_r(NULL, ";", &tokenize_ptr_amp);
                            continue;
                        }
                        if (strcmp(token, "purge") == 0)
                        {
                            clear_pastevents(dir_from_which_shell_is_called);
                            token_amp = strtok_r(NULL, ";", &tokenize_ptr_amp);
                            continue;
                        }
                        if (strcmp(token, "execute") == 0)
                        {
                            int n = atoi(strtok_r(NULL, " \t\n", &tokenize_ptr));
                            char *command = (char *)malloc(sizeof(char) * 1000);
                            command[0] = '\0';
                            exec_pastevents(command, n, dir_from_which_shell_is_called);
                            if (command == NULL)
                            {
                                printf("No such command exists\n");
                                token_amp = strtok_r(NULL, ";", &tokenize_ptr_amp);
                                continue;
                            }
                            strcpy(token_semi, command);
                            free(command);
                            goto here;
                        }
                    }
                    else if (is_there_piping == 0)
                        execute_non_pe_func(token, token_amp, dir_from_which_shell_is_called, previous_dir);
                    else if (is_there_piping == 1)
                        execute_pipe(token_amp, dir_from_which_shell_is_called, previous_dir);

                    token_amp = strtok_r(NULL, "&\n", &tokenize_ptr_amp);
                    free(input_tok);
                    end = time(NULL);

                    if (end - start > 2)
                    {
                        prompt(dir_from_which_shell_is_called);
                        printf("<%s : %ld> ", token_copy_for_time, end - start);
                        goto after_time;
                    }

                    is_fg_running = 0;
                }
                count_amp--;
            }
            token_semi = strtok_r(NULL, ";\n", &tokenize_ptr_semi);
            free(input_tok_tok);
        }
        free(input_tok_semi);
    }
}
