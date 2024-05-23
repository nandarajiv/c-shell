#include "../headers.h"

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

int kbhit()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void disableRawMode()
{
    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrl_z);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void neonate(char *input_full)
{
    char *ptr = NULL;
    char *token = strtok_r(input_full, " \t\n", &ptr);
    token = strtok_r(NULL, " \t\n", &ptr);
    if (token == NULL)
    {
        printf("Incorrect call of neonate\n");
        return;
    }
    token = strtok_r(NULL, " \t\n", &ptr);
    if (token == NULL)
    {
        printf("Incorrect call of neonate\n");
        return;
    }
    int time_arg = atoi(token);
    if (time_arg < 0)
    {
        printf("Invalid time arg\n");
        return;
    }

    enableRawMode();
    int most_recent_pid = 0;
    char c = 'h';
    char *inp = malloc(sizeof(char) * 100);
    memset(inp, '\0', 100);
    char proc_path[100] = "/proc/loadavg";
    while (1)
    {
        FILE *fp = fopen(proc_path, "r");
        if (fp == NULL)
        {
            perror("No such process currently");
            disableRawMode();
            return;
        }
        fscanf(fp, "%*s %*s %*s %*s %d", &most_recent_pid);
        fclose(fp);
        printf("%d\n", most_recent_pid);

        if (kbhit())
        {
            c = getchar();
            // printf("%c\n", c);
            if (c == 'x')
            {
                disableRawMode();
                return;
            }
            else
                sleep(time_arg);
        }
        else
            sleep(time_arg);
    }
}