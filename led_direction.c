#include "logging.h"

#include "dataRead.h"
#include <wiringPi.h>

#include "ad799x.h"
//#include "km2.h"
#include "led_direction.h"

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
 * -1=left; 0=forward; 1=right; 2=slow down; 3=continue moving, 4=dont move;5=error
 */

short led_dir(){

    //piLock(LED_DIRECTION_LOCK_NO);
    
    if((sizeof(sensor_color)/sizeof(*sensor_color)) != 4) {
        log_msg(ERROR, "sensor_color received wrong number of elements! return value 4");
        return MOVE_DECISION_ERROR;
    }
    
    for(int i=0;i<4;++i)
    {
        if(sensor_color[i] == ERROR_COLOR) {
            log_msg(ERROR, "sensor_color[%d] == ERROR_COLOR !! Cannot go anywhere", i, sensor_color[i]);
            return MOVE_DECISION_ERROR;
        }
    }
    
    //log_msg(DEBUG, "led_dir_col_sens_0-3:%d,%d,%d,%d", sensor_color[0], sensor_color[1], sensor_color[2], sensor_color[3]);
    if((sensor_color[0] == WHITE)&&(sensor_color[1] == BLACK)&&(sensor_color[2] == WHITE))
        return FORWARD;
    else if((sensor_color[0] == BLACK)&&(sensor_color[1] == WHITE)&&(sensor_color[2] == WHITE))
        return LEFT;
    else if((sensor_color[0] == WHITE)&&(sensor_color[1] == WHITE)&&(sensor_color[2] == BLACK))
        return RIGHT;
    else if((sensor_color[0] == WHITE)&&(sensor_color[1] == WHITE)&&(sensor_color[2] == WHITE)&&(sensor_color[3] == BLACK))
        return SLOW_DOWN;
    else 
        return MOVE_DECISION_ERROR; //error - cant decide
    
    //piUnlock(LED_DIRECTION_LOCK_NO);   

}