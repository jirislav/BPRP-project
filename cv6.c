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

#include "ad799x.h"
#include "i2c.h"
#include "km2.h"

#define RESOLUTION (3.3f / 1024)


int main() {
	// inicializace i2c
	int bus = i2c_init(1);

	// precteni
	int16_t value;

        while (1) {
            i2c_read_beint16(bus, ADDR_AD799X_0_F, AD799X_RESULT_CH(0), &value);
        
            printf("AD(%d): 0x%04x\n", (value & AD799X_RESULT_CHAN) >> 12, (value & AD799X_RESULT_VALUE));
            
            //float voltage = RESOLUTION * ((value & AD799X_RESULT_VALUE) >> 2);
            
            /*
             * battery calibration info
             * 11,93 V = 0x0ae8
             */
            float voltage = (value & AD799X_RESULT_VALUE) * 11.93f / 0x0ae8;
            
            //printf("Voltage is %.3f V\n", voltage);
            
            usleep(5e5);
        }
        
       

	// uzavreni i2c
	i2c_close(bus);
}
