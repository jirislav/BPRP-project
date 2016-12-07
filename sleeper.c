#include <unistd.h>

#include "sleeper.h"

void sleep_micro(long time) {
    
    long remaining = time;
    
    do {
        
        remaining -= MAX_USLEEP;
        
        if (remaining > 0)
            usleep(MAX_USLEEP);
        else {
            usleep(MAX_USLEEP + remaining);
        }
        
    } while (remaining > 0);
}
