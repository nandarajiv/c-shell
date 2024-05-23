#include "../headers.h"

void tok_exec(char* token_amp)
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
    array_of_tokens[count_tokens] = NULL;

    int pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        int k = execvp(array_of_tokens[0], array_of_tokens);
        if (k < 0)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        fg_pid = getpid();
    }
    else
    {
        is_fg_running = 1;
        int status;
        waitpid(pid, &status, WUNTRACED);
        if (WIFEXITED(status))
        {
            // printf("hi i am working\n");
            if (WEXITSTATUS(status) == EXIT_FAILURE)
            {
                printf("Command not found\n");
            }
        }
        is_fg_running = 0;

    }
}