/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dataRead.h
 * Author: LH
 *
 * Created on 22. listopadu 2016, 23:23
 */

#ifndef DATAREAD_H
#define DATAREAD_H

#ifdef __cplusplus
extern "C" {
#endif

void spust_dataRead();
int whatColor();

char* detect_color(int color);

extern int pole_barva[4];

#ifdef __cplusplus
}
#endif

#endif /* DATAREAD_H */

