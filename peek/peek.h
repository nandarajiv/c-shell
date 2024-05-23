#ifndef PEEK_H
#define PEEK_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void peek(char *input_full, char *dir_from_which_shell_is_called, char *previous_dir);

#endif