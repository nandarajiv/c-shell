#ifndef WARP_H_
#define WARP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void warp(char *input_full, char *dir_from_which_shell_is_called, char *previous_dir);

#endif