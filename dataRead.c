/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "ad799x.h"
#include "i2c.h"
#include "km2.h"

#include "logging.h"
#include "dataRead.h"

int pole[4] = {0, 0, 0, 0};

int sensor_color[4] = {1, 0, 0, 1};

int detectWhiteBlack(int bus, int16_t* value, int16_t* value1, int16_t* value2, int16_t* value3) {

    /* 
     * Read from all sensors with SENSOR_READ_SLEEP between 
     * each read so that capacitors can load up
     */
    i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(0), value);

    usleep(SENSOR_READ_SLEEP);
    i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(2), value1);

    usleep(SENSOR_READ_SLEEP);
    i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(4), value2);

    usleep(SENSOR_READ_SLEEP);
    i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(6), value3);

    // Cut the values read from the sensor
    pole[0] = *value & AD799X_RESULT_VALUE;
    pole[1] = *value1 & AD799X_RESULT_VALUE;
    pole[2] = *value2 & AD799X_RESULT_VALUE;
    pole[3] = *value3 & AD799X_RESULT_VALUE;

    // Write the black & white detection
    piLock(DATA_READ_LOCK_NO);
    for (int i = 0; i < 4; ++i) {
        if (pole[i] > 2500 && pole[i] < 5000)
            sensor_color[i] = 1;
        else if (pole[i] > 0 && pole[i] < 1500)
            sensor_color[i] = 0;
        else
            sensor_color[i] = 2;
    }
    piUnlock(DATA_READ_LOCK_NO);

    log_msg(DEBUG, "0: 0x%04x => %d => %d => \t%s\n", (*value & AD799X_RESULT_CHAN) >> 12, pole[0], sensor_color[0], detect_color(sensor_color[0]));
    log_msg(DEBUG, "1: 0x%04x => %d => %d => \t%s\n", (*value1 & AD799X_RESULT_CHAN) >> 12, pole[1], sensor_color[1], detect_color(sensor_color[1]));
    log_msg(DEBUG, "2: 0x%04x => %d => %d => \t%s\n", (*value2 & AD799X_RESULT_CHAN) >> 12, pole[2], sensor_color[2], detect_color(sensor_color[2]));
    log_msg(DEBUG, "3: 0x%04x => %d => %d => \t%s\n", (*value3 & AD799X_RESULT_CHAN) >> 12, pole[3], sensor_color[3], detect_color(sensor_color[3]));

}

char* detect_color(int color) {
    switch (color) {
        case 0:
            return "Black";
            break;
        case 1:
            return "White";
            break;
        case 2:
            return "Error";
            break;
    }

    return "Different number";
}

PI_THREAD(ReadData) {
    int bus = i2c_init(1);

    int16_t value;
    int16_t value1;
    int16_t value2;
    int16_t value3;

    while (1) {

        detectWhiteBlack(bus, &value, &value1, &value2, &value3);
        usleep(DATA_READ_LOOP_USLEEP);
    }

    // uzavreni i2c
    i2c_close(bus);
}

void run_dataRead() {
    int x = piThreadCreate(ReadData);
    if (x != 0)
        log_msg(ERROR, "Data read thread couldn't be started");
}
