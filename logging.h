/* 
 * File:   logging.h
 * Author: student
 *
 * Created on 26. října 2016, 10:35
 */

#ifndef LOGGING_H
#define	LOGGING_H

#define INFO 0
#define DEBUG 1
#define WARNING 2
#define ERROR  3

int log_msg(int level,const char* frm,...);




#endif	/* LOGGING_H */

