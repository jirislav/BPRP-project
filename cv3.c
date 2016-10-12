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

/*
 * FIXME: Declare constants using "declare" keyword &export to a header
 */
// Path to I2C device
const I2C_DEVICE = "/dev/i2c-1";

// Run "i2cdetect -y 1"
const I2C_ADDRESS = 0x27;

const OLATA_REG = 0x14;
const IODIRA_REG = 0x00;

// Delay in ms
const DELAY = 100;

int fd;

/**
 *  Set IODIRA register to 0 0 0 0 0 0 0
 */
int setOutput() {
    char data_write[] = {IODIRA_REG, 0x00};
    return write(fd, data_write, 2);
}

/**
 *  Set OLATA register to 1 1 1 1 1 1 1
 */
int setHigh() {
    char data_write[] = {OLATA_REG, 0xff};
    return write(fd, data_write, 2);
}

/**
 *  Set OLATA register to 0 0 0 0 0 0 0
 */
int setLow() {
    char data_write[] = {OLATA_REG, 0x00};
    return write(fd, data_write, 2);
}

/*
 * 
 */
int main(int argc, char** argv) {

    fd = open(I2C_DEVICE, O_RDWR);

    int ioctl_result = ioctl(fd, I2C_SLAVE, I2C_ADDRESS);

    printf("setOutput returned \t%d\n", setOutput());
    
    int i = 0;
    for (; i < DELAY; ++i) {
        int low_result = setLow();
        if (low_result < 0) {
            error(EXIT_FAILURE, low_result, "Error setting low");
        }
        delay(DELAY - i);
        int high_result = setHigh();
        if (high_result < 0) {
            error(EXIT_FAILURE, high_result, "Error setting high");
        }
        delay(DELAY - i);
    }

    close(fd);
    return 0;
}