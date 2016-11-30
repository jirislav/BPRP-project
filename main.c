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

#define MAIN_LOOP_NANO_SLEEP 1e9

#define DATA_READ_LOOP_NANO_SLEEP 1e8
#define DRIVER_LOOP_NANO_SLEEP 1e8

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <wiringPi.h>

#include "logging.h"
//#include "communication.h"
#include "led_direction.h"
#include "ramp.h"
#include "dataRead.h"

#include "ad799x.h"
#include "i2c.h"
#include "km2.h"


void start_driving() {
    
    while(1) {
        
        short direction = led_dir();
    
        // Write to the ramp
        nanosleep(DRIVER_LOOP_NANO_SLEEP);
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
    
    log_msg(INFO, "APP IS STARTING");
    
    run_dataRead();
    //run_ramp();
    run_driver();
    
    while(1)
    {
        nanosleep(MAIN_LOOP_NANO_SLEEP);
    }

    return (EXIT_SUCCESS);
}