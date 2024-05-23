#ifndef NEONATE_H
#define NEONATE_H

#include <termios.h>
#include <ctype.h>
#include <sys/select.h>

void die(const char *s);
void disableRawMode();
void enableRawMode();
void neonate(char* input_full);

#endif