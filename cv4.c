/* 
 * File:   cv3.c
 * Author: student
 *
 * Created on 12. října 2016, 10:22
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
/*
 * FIXME: Declare constants using "declare" keyword &export to a header
 */
// Path to I2C device
char I2C_DEVICE[] = "/dev/i2c-1";

// Run "i2cdetect -y 1"
const I2C_ADDRESS = 0x70;

// Delay in ms
const DELAY = 10;

int fd;

int set_motors_speed(int left, int right) {
    
    BYTE left_low = left & 0xff;
    BYTE left_high = left >> 8;
    
    BYTE right_low = right & 0xff;
    BYTE right_high = right >> 8;
    
    BYTE data[] = { 0, left_low, left_high, right_low, right_high };
    
    printf("set_motors_speed writing ll: %d, lh: %d, rl: %d, rh: %d\r\n", left_low, left_high, right_low, right_high); 
    return write(fd, data, 5);
}

/*
 * 
 */
int main(int argc, char** argv) {

    fd = open(I2C_DEVICE, O_RDWR);

    int ioctl_result = ioctl(fd, I2C_SLAVE, I2C_ADDRESS);
    
    int i = 0;
    for (;i < 65535; ++i) {

        printf("set_motors_speed returned \t%d", set_motors_speed(i,i));
        delay(DELAY);
    }
    delay(10000);
    for (;i >= 0; --i) {

        printf("set_motors_speed returned \t%d", set_motors_speed(i,i));
        delay(DELAY);
    }
    

    close(fd);
    return 0;
}