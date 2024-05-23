#ifndef PASTEVENTS_H
#define PASTEVENTS_H

#include <stdlib.h>
#include <stdio.h>

// passing dir_from_which_shell_is_called because it is needed to get relative path of pastevents.txt
void print_pastevents(char *dir_from_which_shell_is_called);
void write_pastevents(char *command, char *dir_from_which_shell_is_called);
void clear_pastevents(char *dir_from_which_shell_is_called);
void exec_pastevents(char *cmd, int n, char *dir_from_which_shell_is_called);

#endif
