#include "led_direction.h"
#include "logging.h"
/* 
 * File:   led_direction.c
 * Author: Daired
 *
 * Created on November 17, 2016, 10:02 AM
 * 
 * This lib is used for processing output from led sensors which are tracking
 * line on the floor.
 * Input - array of short(bool) values led_array[4]. Each value represents detecting black line (0)
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

short led_dir(short* led_array){
    if(sizeof(led_array)*sizeof(led_array*) != 8)
    {
        log_msg(ERROR,"led_array received wrong number of elements! return value 4");
        return 4;
    }
    for(int i=0;i<4;++i)
    {
        if((led_array !=0) || (led_array !=1)) 
        log_msg(ERROR,"led_array[%d] = %s (received wrong value within interval <-1;1>_! return value 4",i,led array[i]);
        return 4;
    }
    
    if((led_array[0] == 0)&&(led_array[1] == 1)&&(led_array[2] == 0)&&(led_array[3] == 1))
        return 0; //forward
    else if((led_array[0] == 1)&&(led_array[1] == 0)&&(led_array[2] == 0)&&(led_array[3] == 1))
        return -1;  //left
    else if((led_array[0] == 0)&&(led_array[1] == 0)&&(led_array[2] == 1)&&(led_array[3] == 1))
        return 1;       //right
    else if((led_array[0] == 0)&&(led_array[1] == 0)&&(led_array[2] == 0)&&(led_array[3] == 1))
        return 2;   //slow down
    else 
        return 3;   //don't move
    

}