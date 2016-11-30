/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dataRead.h
 * Author: LH
 *
 * Created on 22. listopadu 2016, 23:23
 */

#ifndef DATAREAD_H
#define DATAREAD_H

#ifdef __cplusplus
extern "C" {
#endif

void run_dataRead();
int detectWhiteBlack();

char* detect_color(int color);

extern int sensor_color[4];


// This is optimalized, it shouldn't be changed unless we change hardware
#define SENSOR_READ_SLEEP 1e3

// Lock number to respect
#define DATA_READ_LOCK_NO 1

#define DATA_READ_LOOP_NANO_SLEEP 1e4

#ifdef __cplusplus
}
#endif

#endif /* DATAREAD_H */

