#ifndef EXECUTE_H
#define EXECUTE_H

#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>

void execute_non_pe_func(char *token, char *token_semi, char *dir_from_which_shell_is_called, char *previous_dir);
// void execute_non_pe_func_piped(char *token, char *token_semi, char *dir_from_which_shell_is_called, char *previous_dir, int pipes, int originalOut, int i);

#endif