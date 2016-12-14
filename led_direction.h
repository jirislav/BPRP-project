/* 
 * File:   led_direction.h
 * Author: Daired
 *
 * Created on November 17, 2016, 10:02 AM
 * 
 * This lib is used for processing output from led sensors which are tracking
 * line on the floor.
 * Input - array of bool values. Each value represents detecting black line (0)
 *  or white floor (1).
 * Output -  short int number <-1;1> . This value represents supposed direction
 * of robot (-1 = left ; 0 = forward ; 1 = right)
 */

#ifndef LED_DIRECTION_H
#define LED_DIRECTION_H

#ifdef __cplusplus
extern "C" {
#endif

short led_dir();

#define BLACK 0
#define WHITE 1

#define LED_DIRECTION_LOCK_NO 3


#ifdef __cplusplus
}
#endif

#endif /* LED_DIRECTION_H */

