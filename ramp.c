/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * sleep - time to sleep between steps - [us]
 * stepsize - how large increment should be
 * mutex which number to lock
 */
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

void ramp(unsigned int sleep, unsigned int stepsize, unsigned int mutexlock)
{
    // thread init
    int fd;
    
    // open device comm
    fd = open(RAMP_I2C_DEVICE, O_RDWR);
    // startup
    int ioctl_result = ioctl(fd, I2C_SLAVE, RAMP_I2C_ADDRESS);
    
    
    
    // endless thread
    while(1) 
    {
    piLock(mutexlock)
    // global variable to read - desired speed
    piUnlock(mutexlock)
            
    // i2c read current speed
    int[]* spd[2];
    read_motors_speed(spd);
    // i2c modify current speed
    // if speed is different
    if (set_motors_speed(l,r)<0)
    {
        // write failed
    }
    //else if speed is same - do nothing
    //else if speed is zero - turn power off?
    
    // sleep 
    usleep(RAMP_DELAY)
    }
    
    close(fd)
}






int set_motors_speed(int left, int right) {
    
    BYTE left_low = left & 0xff;
    BYTE left_high = left >> 8;
    
    BYTE right_low = right & 0xff;
    BYTE right_high = right >> 8;
    
    BYTE data[] = { 0, left_low, left_high, right_low, right_high };
    
    printf("set_motors_speed writing ll: %d, lh: %d, rl: %d, rh: %d\r\n", left_low, left_high, right_low, right_high); 
    return write(fd, data, 5);
}


