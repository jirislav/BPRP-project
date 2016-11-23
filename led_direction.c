#include "logging.h"

#include "dataRead.h"
#include <wiringPi.h>

#include "ad799x.h"
#include "i2c.h"
#include "km2.h"
//#include "led_direction.h"

/* 
 * File:   led_direction.c
 * Author: Daired
 *
 * Created on November 17, 2016, 10:02 AM
 * 
 * This lib is used for processing output from led sensors which are tracking
 * line on the floor.
 * Input - array of short(bool) values pole_barva[4]. Each value represents detecting black line (0)
 *  or white floor (1).
 * Output -  short int number <-1;4> . This value represents supposed direction
 * of robot (-1 = left ; 0 = forward ; 1 = right)
 * 
 * sensor numbering:        1 --- 2 --- 3
 *                                |
 *                                |
 *                                4
 * 
 *  return values:
 * -1=left; 0=forward; 1=right; 2=slow down; 3=dont move;4=error
 */

short led_dir(){
        piLock(1);
    /* TODO: fix this .. 
     * if(sizeof(pole_barva)*sizeof(pole_barva*) != 8)
    {
        log_msg(ERROR,"pole_barva received wrong number of elements! return value 4");
        return 4;
    }*/
    for(int i=0;i<4;++i)
    {
        if((pole_barva[i] != 0) && (pole_barva[i] != 1)) {
            printf("pole_barva[%d] = %d (received wrong value within interval <-1;1>_! return value 4\n", i, pole_barva[i]);
            return 4;
        }
    }
    
    if((pole_barva[0] == 0)&&(pole_barva[1] == 1)&&(pole_barva[2] == 0)&&(pole_barva[3] == 1))
        return 0; //forward
    else if((pole_barva[0] == 1)&&(pole_barva[1] == 0)&&(pole_barva[2] == 0)&&(pole_barva[3] == 1))
        return -1;  //left
    else if((pole_barva[0] == 0)&&(pole_barva[1] == 0)&&(pole_barva[2] == 1)&&(pole_barva[3] == 1))
        return 1;       //right
    else if((pole_barva[0] == 0)&&(pole_barva[1] == 0)&&(pole_barva[2] == 0)&&(pole_barva[3] == 1))
        return 2;   //slow down
    else 
        return 3;   //don't move
    
    piUnlock(1);   

}