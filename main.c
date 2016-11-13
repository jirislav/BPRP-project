/* 
 * File:   main.c
 * Author: student
 *
 * Created on 26. října 2016, 10:57
 */

#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "communication.h"

/*
 * 
 */
int main(int argc, char** argv) {
    int r=1;
    log_msg(INFO,"APP IS STARTING %d",r);
    
    vytvor_prijem();
    socket_vysilani();
   
    return (EXIT_SUCCESS);
}

