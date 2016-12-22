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

#define DATA_READ_LOOP_MICRO_SLEEP 6e3
#define DRIVER_LOOP_MICRO_SLEEP 6e3

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
    
    int L_speed_memory = 0;
    int R_speed_memory = 0;
    while(1) {
        
        piLock(DRIVER_LOCK_NO);
        short direction = led_dir();
      
        // Write to the ramp   
        switch(direction)
        {
                case FORWARD:
                    L_speed = maxspeed;
                    R_speed = maxspeed;
                    
                    L_speed_memory = L_speed;
                    R_speed_memory = R_speed;
                    
                    break;
                case RIGHT:
                    L_speed = maxspeed * 2;
                    R_speed = mediumspeed;
                    
                    L_speed_memory = L_speed;
                    R_speed_memory = R_speed;
                    
                    break;
                case LEFT:
                    L_speed = mediumspeed;
                    R_speed = maxspeed * 2;
                    
                    L_speed_memory = L_speed;
                    R_speed_memory = R_speed;
                    
                    break;
                case SLOW_DOWN:
                    L_speed = .5 * L_speed_memory;
                    R_speed = .5 * R_speed_memory;
                    
                    break;
            default:
                    L_speed = L_speed_memory;
                    R_speed = R_speed_memory;
                    break;
                //log_msg(ERROR, "driver got direction %d (continuing with those speeds: %d, %d)", direction, L_speed_memory, R_speed_memory);
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