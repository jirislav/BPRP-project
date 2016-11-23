/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * sleep - time to sleep between steps - [us]
 * stepsize - how large increment should be
 * mutex which number to lock
 * DO ME: casting to unit16 instead of ints for byte ops
 * 
 * 
 *  */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <error.h>
#include "ramp.h"

#include <wiringPi.h>

#include "ad799x.h"
#include "i2c.h"
#include "km2.h"


typedef unsigned char BYTE;
// defined constants in header file!!



PI_THREAD (ramp_thread)
{
    ramp(RAMP_DELAY, 1, 1);
}

void spust_rampu()
{
    auto x = piThreadCreate(ramp_thread);
    if (x != 0)
        printf ("ramp didn't start\n");
}

void ramp(unsigned int sleep, unsigned int stepsize, unsigned int mutexlock)
{
    // fction init
    int fd;
    
    // open device comm
    fd = open(RAMP_I2C_DEVICE, O_RDWR);
    // startup
    int ioctl_result = ioctl(fd, I2C_SLAVE, RAMP_I2C_ADDRESS);
    
    uint16_t * speed[2];
    
    // endless thread
    while(1) 
    {
        piLock(mutexlock);
        
        int mutex_L = 0;
        
        int mutex_R = 0;
        
        // global variable to read - desired speed
        piUnlock(mutexlock);
            
        // i2c read current speed
    
        read_motors_speed( fd,&speed);
        // i2c modify current speed
        
        int l = *speed[0], r = *speed[1];
        
        if (*speed[0] != mutex_L) // required and set speed are not equal
        {    
            if (mutex_L > l)
                l += stepsize;
            else if (mutex_L < l)
                l -= stepsize;
        }
        if (*speed[1] != mutex_R) // required and set speed are not equal
        {    
            if (mutex_R > r)
                r += stepsize;
            else if (mutex_R < r)
                r -= stepsize;
        }
        
        
        // if speed is different
        if (set_motors_speed(fd, l, r) < 0)
        {   
            // write failed
        }
        //else if speed is same - do nothing
        //else if speed is zero - turn power off?
        
        // sleep 
        speed[0] = 0;
        speed[1] = 0;
        
        usleep(RAMP_DELAY);
    }
    
    close(fd);
}


void read_motors_speed(int fd, uint16_t **speed)
{
    
    BYTE spd[10] = {0}; // create storage for read bytes
    int numb = read(fd, spd, 5);
    if (numb != 5)
    {    // failed to read the correct number of bytes
    }   
    // if load order is B 0 LL LH RL RH then build the numbers
      *speed[0] = spd[1] | spd[2] << 8; // speed left
      *speed[1] = spd[3] | spd[4] << 8; // speed right
      printf("read_motors_speed reading l_spd: %d, r_spd: %d\r\n", speed[0], speed[1]); 
      
}

int set_motors_speed(int fd, uint16_t left, uint16_t right) {
    
    BYTE left_low = left & 0xff;
    BYTE left_high = left >> 8;
    
    BYTE right_low = right & 0xff;
    BYTE right_high = right >> 8;
    
    BYTE data[] = { 0, left_low, left_high, right_low, right_high };
    
    printf("set_motors_speed writing ll: %d, lh: %d, rl: %d, rh: %d\r\n", left_low, left_high, right_low, right_high); 
    return write(fd, data, 5);
}


