/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ramp.h
 * Author: kubasik
 *
 * Created on November 17, 2016, 12:11 PM

 */
#ifndef RAMP_H
#define RAMP_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdint.h>
// Path to I2C device
#define RAMP_I2C_DEVICE "/dev/i2c-1"

// Run "i2cdetect -y 1"
#define RAMP_I2C_ADDRESS 0x70

// Delay for 50 ms (5e7)
#define RAMP_LOOP_NANO_SLEEP 5e7
    
// Lock number to respect
#define RAMP_LOCK_NO 2
    
// 
#define RAMP_STEP_SIZE 1

int set_motors_speed(int fd, uint16_t left, uint16_t right);
void read_motors_speed(int fd, uint16_t *speed);

void run_ramp(); // spusti thread

#ifdef __cplusplus
}
#endif

#endif /* RAMP_H */

