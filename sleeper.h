/* 
 * File:   sleeper.h
 * Author: student
 *
 * Created on 7. prosince 2016, 11:59
 */

#ifndef SLEEPER_H
#define	SLEEPER_H

#ifdef	__cplusplus
extern "C" {
#endif

#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */
    
#define MAX_USLEEP 1000000

void sleep_micro(long time);

#ifdef	__cplusplus
}
#endif

#endif	/* SLEEPER_H */

