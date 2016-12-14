#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

#include "logging.h"

struct timeval tp;

static char* level_type[] = {"I",
    "D",
    "W",
    "E"};

int log_msg(int level, const char* fmt, ...) {
    if ((level > 3) || (level < 0)) {
        level = 3;
    }

    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, 256, fmt, args);
    va_end(args);

    gettimeofday(&tp, NULL);

    printf("%s:%lu.%.6lu:%s\r\n", level_type[level], (unsigned long)(tp.tv_sec), (unsigned long)(tp.tv_usec), buffer);
    fflush(stdout);

}


