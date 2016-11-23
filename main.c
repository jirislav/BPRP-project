/* 
 * File:   main.c
 * Author: student
 *
 * Created on 26. října 2016, 10:57
 */

#include <stdio.h>
#include <stdlib.h>

#include "logging.h"
//#include "communication.h"
#include "led_direction.h"
#include "ramp.h"
#include "dataRead.h"

#include <wiringPi.h>

#include "ad799x.h"
#include "i2c.h"
#include "km2.h"


PI_THREAD (ridic) {
    rid_to();
}

void rid_to() {
    
    while(1) {
        //memcpy(led_statuses, pole_barva, 4*sizeof(int));
        short kam_jet = led_dir();
    
        usleep(500000);
    }
}

void zacni_ridit() {
    auto x = piThreadCreate(ridic);
    if (x != 0)
        printf ("ridic didn't start\n");
}

/*
 * 
 */
int main(int argc, char** argv) {
    int r=1;
    
    log_msg(INFO,"APP IS STARTING %d",r);
    
    spust_dataRead();
    zacni_ridit();
    
    while(1)
    {
        usleep(1000);
    }
    
    /*
        vytvor_prijem();
        socket_vysilani();
    */
    return (EXIT_SUCCESS);
}