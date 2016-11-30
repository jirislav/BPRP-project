#include <stdio.h>
#include <stdarg.h>

#include"logging.h"

static char* level_type[] = {"INFO",
                             "DEBUG",
                             "WARNING",
                             "ERROR"};


int log_msg(int level,const char* fmt,...)
{
    if((level>3) || (level<0))
    {
        level=3;
    }
    
  char buffer[256];
  va_list args;
  va_start (args, fmt);
  vsnprintf (buffer,256,fmt, args);
  va_end (args);
  
  printf("%s : %s\n", level_type[level], buffer);


}


