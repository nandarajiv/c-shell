#ifndef SEEK_H
#define SEEK_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

void seek(char *input_full, char* dir_from_where_shell_is_called);

#endif