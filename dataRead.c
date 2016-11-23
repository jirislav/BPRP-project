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

#include "dataRead.h"

int pole[4] = {0,0,0,0};

int pole_barva[4] = {1,0,0,1};

PI_THREAD(ReadData)
{
    int bus = i2c_init(1);

	// precteni
        int16_t value;
	int16_t value1;
        int16_t value2;
        int16_t value3;
        

        while (1) {
            int read_sleep = 1e3;
            
            i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(0), &value);
            
            usleep(read_sleep);
            i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(2), &value1);
            
            usleep(read_sleep);
            i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(4), &value2);
            
            usleep(read_sleep);
            i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(6), &value3);
            
            pole[0] = value & AD799X_RESULT_VALUE;
            pole[1] = value1 & AD799X_RESULT_VALUE;
            pole[2] = value2 & AD799X_RESULT_VALUE;
            pole[3] = value3 & AD799X_RESULT_VALUE;
            
            whatColor();
                 /*
            printf("value: %d                     ", value);
            printf("         (HEXA)AD(%d): 0x%04x", (value & AD799X_RESULT_CHAN) >> 12, (value & AD799X_RESULT_VALUE));
            printf("         Barva: %i", pole_barva[0]);
            */
            
            printf("0: 0x%04x => %d => %d => \t%s\n", (value & AD799X_RESULT_CHAN) >> 12, pole[0], pole_barva[0], detect_color(pole_barva[0]));
            printf("1: 0x%04x => %d => %d => \t%s\n", (value1 & AD799X_RESULT_CHAN) >> 12, pole[1], pole_barva[1], detect_color(pole_barva[1]));
            printf("2: 0x%04x => %d => %d => \t%s\n", (value2 & AD799X_RESULT_CHAN) >> 12, pole[2], pole_barva[2], detect_color(pole_barva[2]));
            printf("3: 0x%04x => %d => %d => \t%s\n", (value3 & AD799X_RESULT_CHAN) >> 12, pole[3], pole_barva[3], detect_color(pole_barva[3]));
           
            
            //printf("pole0 %d, pole1 %d, pole2 %d, pole3 %d", pole[0], pole[1], pole[2], pole[3]);
            //printf("poleBarva0 %d, poleBarva1 %d, poleBarva2 %d, poleBarva3 %d", pole_barva[0], pole_barva[1], pole_barva[2], pole_barva[3]);
           
            
            
            //printf("\r");
            printf("\n");
            fflush(stdout);                     //vymaže buffer
            //float voltage = RESOLUTION * ((value & AD799X_RESULT_VALUE) >> 2);
            
            /*
             * battery calibration info
             * 11,93 V = 0x0ae8
             */
            //float voltage = (value1 & AD799X_RESULT_VALUE) * 11.93f / 0x0ae8;
            
            //printf("Voltage is %.3f V\n", voltage);
            
            usleep(500000);
        }
        
       

	// uzavreni i2c
	i2c_close(bus);
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

void spust_dataRead()
{
    auto x = piThreadCreate(ReadData);
    if (x != 0)
        printf ("dataRead didn't start\n");
}

int whatColor()
{
    
    piLock(1);
    for(int i=0;i<4;++i)
    {
        if(pole[i]>2500 && pole[i]<5000)
            pole_barva[i] = 1;
        else if(pole[i]>0 && pole[i]<1500)
            pole_barva[i] = 0;
        else
            pole_barva[i] = 2;
    }
    piUnlock(1);
}
