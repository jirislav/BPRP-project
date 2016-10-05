/* 
 * File:   main.c
 * Author: student
 *
 * Created on 5. října 2016, 10:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

PI_THREAD(myThread1) {
    softwarePWM(2, 1000000, 50, 0, 0);
}

PI_THREAD(myThread2) {
    softwarePWM(3, 500000, 75, 0, 0);
}

/*
 * 
 */
int main(int argc, char** argv) {
    wiringPiSetup();

    int x = piThreadCreate(myThread1);

    if (x != 0) {
        printf("it didn't start");
    }
    
    x = piThreadCreate(myThread2);

    if (x != 0) {
        printf("it didn't start");
    }

    while(1) {
        delay(500);
    }
    
    return 0;
}

/**
 * 
 * @param pin
 *      - číslo pinu, kde má být SW PWM realizováno
 * @param period
 *      - perioda signálu v mikrosekundách
 * @param duty
 *      - relativní šířka pulzu v procentech
 * @param runtime
 *      - doba běhu v milisekundách, 0 pro nekonečno
 * @param error
 *      - maximální přípustná relativní chyba časování v procentech
 * @return int
 */
int softwarePWM(int pin, int period, unsigned int duty, unsigned int runtime, int error) {

    int unsigned start_time = micros();

    pinMode(pin, OUTPUT);

    if (duty > 100) {
        duty = 100;
    }

    int duration_high = (duty * period) / 100;
    int duration_low = period - duration_high;

    while (1) {

        digitalWrite(pin, HIGH);
        delayMicroseconds(duration_high);

        digitalWrite(pin, LOW);
        delayMicroseconds(duration_low);

        if (runtime && micros() > (start_time + runtime))
            break;
    }

}