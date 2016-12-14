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

#define DATA_READ_LOOP_MICRO_SLEEP 5e5
#define DRIVER_LOOP_MICRO_SLEEP 5e5

#define DRIVER_LOCK_NO 0

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
  
    int maxspeed = MAX_SPEED;
    int mediumspeed = MAX_SPEED/2; 
    int stopspeed = 0;
    
    while(1) {
        
        piLock(DRIVER_LOCK_NO);
        short direction = led_dir();
      
        // Write to the ramp   
        switch(direction)
        {
                case 0:
                    L_speed = maxspeed;
                    R_speed = maxspeed;
                    break;
                case 1:
                    L_speed = maxspeed;
                    R_speed = mediumspeed;
                    break;
                case -1:
                    L_speed = mediumspeed;
                    R_speed = maxspeed;
                    break;
                case 2:
                    L_speed = mediumspeed;
                    R_speed = mediumspeed;
                    break;
                case 3:
                    L_speed = stopspeed;
                    R_speed = stopspeed;
                    break;
            default:
                log_msg(ERROR, "driver got direction %d (out of bounds)", direction);
        }    
        piUnlock(DRIVER_LOCK_NO);
      
        log_msg(DEBUG, "driver_says: l:%d r:%d dir:%d", L_speed, R_speed, direction);
        
        
        sleep_micro(DRIVER_LOOP_MICRO_SLEEP);
    }
}

PI_THREAD (driver) {
    log_msg(DEBUG, "driver starting...");
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