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
#include <error.h>

typedef unsigned char BYTE;
// defined constants in header file!!
void spust_rampu()
{
    piThreadCreate(ramp_thread);
}

PI_THREAD (ramp_thread)
{
    ramp(RAMP_DELAY, 1, 1)
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
    piLock(mutexlock)
    // global variable to read - desired speed
    piUnlock(mutexlock)
            
    // i2c read current speed
    
    read_motors_speed(speed);
    // i2c modify current speed
    if (speed[0] != mutex_L) // required and set speed are not equal
    {    
        // do ramp, else do nothing
    }
    if (speed[1] != mutex_R) // required and set speed are not equal
    {    
        // do ramp, else do nothing
    }
     
    
    // if speed is different
    if (set_motors_speed(l,r)<0)
    {
        // write failed
    }
    //else if speed is same - do nothing
    //else if speed is zero - turn power off?
    
    // sleep 
    speed = {0};
    usleep(RAMP_DELAY)
    }
    
    close(fd)
}



void read_motors_speed(uint16_t *speed)
{
    
    BYTE spd[10]={0}; // create storage for read bytes
    
    if ((int numb=read(fd,spd,5))!=5)
    {    // failed to read the correct number of bytes
    }   
    // if load order is B 0 LL LH RL RH then build the numbers
      *speed[0] = spd[1] | spd[2] << 8; // speed left
      *speed[1] = spd[3] | spd[4] << 8; // speed right
      printf("read_motors_speed reading l_spd: %d, r_spd: %d\r\n", *speed[0],*speed[1]); 
      
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


