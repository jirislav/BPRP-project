//#include <sys/types.h>
//#include <sys/stat.h>
//#include <sys/ioctl.h>
//#include <fcntl.h>
//#include <linux/i2c-dev.h>
#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>
//#include <error.h>


#include <stdlib.h>
#include <wiringPi.h>

#include "ad799x.h"
#include "i2c.h"
#include "km2.h"

#define RESOLUTION (3.3f / 1024)

int pole[4] = {0,0,0,0};
int pole_barva[4] = {0,0,0,0};


int main() {
	// inicializace i2c
	int bus = i2c_init(1);

	// precteni
        int16_t value;
	int16_t value1;
        int16_t value2;
        int16_t value3;
      
        
        

        while (1) {
            i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(0), &value);
            //i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(2), &value1);
            //i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(4), &value2);
            //i2c_read_beint16(bus, ADDR_AD799X_3_F, AD799X_RESULT_CH(6), &value3);
            
            pole[0] = value & AD799X_RESULT_VALUE;
            pole[1] = value1 & AD799X_RESULT_VALUE;
            pole[2] = value2 & AD799X_RESULT_VALUE;
            pole[3] = value3 & AD799X_RESULT_VALUE;
            
            
            jaka_barva();
            
            printf("value: %d                     ", value);
            printf("         (HEXA)AD(%d): %d", (value & AD799X_RESULT_CHAN) >> 12, (value & AD799X_RESULT_VALUE));
            printf("         Barva: %i", pole_barva[0]);
            
            printf("        pole0 %d, pole1 %d, pole2 %d, pole3 %d", pole[0], pole[1], pole[2], pole[3]);
             printf("       poleBarva0 %d, poleBarva1 %d, poleBarva2 %d, poleBarva3 %d", pole_barva[0], pole_barva[1], pole_barva[2], pole_barva[3]);
            
            if(pole_barva[0] == 1)
                printf("    White");
            else if(pole_barva[0] == 0)
                printf("    Black");
            else if(pole_barva[0] == 2)
                printf("    Error");
            else
                printf("Different number");
            
            
            printf("\r");  
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

int jaka_barva()
{
    for(int i=0;i<4;++i)
    {
        if(pole[i]>3000 && pole[i]<4000)
            pole_barva[i] = 1;
        else if(pole[i]>0 && pole[i]<1000)
            pole_barva[i] = 0;
        else
            pole_barva[i] = 2;
    }
}
