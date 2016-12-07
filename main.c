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

#define MAIN_LOOP_MICRO_SLEEP 1e6

#define DATA_READ_LOOP_MICRO_SLEEP 5e4
#define DRIVER_LOOP_MICRO_SLEEP 5e4

#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

#include <wiringPi.h>

#include "logging.h"
//#include "communication.h"
#include "led_direction.h"
#include "ramp.h"
#include "dataRead.h"

#include "sleeper.h"
#include "ad799x.h"
#include "i2c.h"
#include "km2.h"

int L_speed,R_speed;

void start_driving() {
    
    while(1) {
        
        short direction = led_dir();
      
        // Write to the ramp   
        piLock(RAMP_LOCK_NO);
        switch(direction)
        {
                case 0:
                    L_speed = 10;
                    R_speed = 10;
                case 1:
                    L_speed = 10;
                    R_speed = 5;
                case -1:
                    L_speed = 5;
                    R_speed = 10;
                case 2:
                    L_speed = 5;
                    R_speed = 5;
                case 3:
                    L_speed = 0;
                    R_speed = 0;
            default:
                log_msg(ERROR, "direction = %d, out of bounds, yo", direction);
        }    
        piUnlock(RAMP_LOCK_NO);
      
        sleep_micro(DRIVER_LOOP_MICRO_SLEEP);
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
    
    wiringPiSetupSys();
            
    run_dataRead();
    run_ramp();
    run_driver();
    
    while(1)
    {
        sleep_micro(MAIN_LOOP_MICRO_SLEEP);
    }

    return (EXIT_SUCCESS);
}