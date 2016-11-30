/* 
 * File:   main.c
 * Author: student
 *
 * Created on 26. října 2016, 10:57
 * 
 * HOWTO wire it up ..
 * 
 * SDA.1 = orange wire
 * SCL.1 = green wire
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "logging.h"
//#include "communication.h"
#include "led_direction.h"
#include "ramp.h"
#include "dataRead.h"

#include <wiringPi.h>

#include "ad799x.h"
#include "i2c.h"
#include "km2.h"

#define MAIN_LOOP_USLEEP 1e5
#define DRIVER_LOOP_USLEEP 1e4


void start_driving() {
    
    while(1) {
        
        short kam_jet = led_dir();
    
        usleep(DRIVER_LOOP_USLEEP);
    }
}

PI_THREAD (driver) {
    start_driving();
}

void run_driver() {
    int x = piThreadCreate(driver);
    if (x != 0)
        log_msg(ERROR, "Driver didn't start");
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    log_msg(INFO,"APP IS STARTING");
    
    run_dataRead();
    run_driver();
    run_ramp();
    
    while(1)
    {
        usleep(MAIN_LOOP_USLEEP);
    }
    
    /*
        vytvor_prijem();
        socket_vysilani();
    */
    return (EXIT_SUCCESS);
}