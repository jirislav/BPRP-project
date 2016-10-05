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
    softwarePWM(2, 1000000, 50, 0, 10);
}

PI_THREAD(myThread2) {
    softwarePWM(3, 500000, 75, 0, 10);
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

    while (1) {
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
    int unsigned start_duration, start_duration_low;

    pinMode(pin, OUTPUT);

    if (duty > 100) {
        duty = 100;
    }

    int duration_high = (duty * period) / 100;
    int duration_low = period - duration_high;

    while (1) {

        start_duration = micros();

        digitalWrite(pin, HIGH);
        delayMicroseconds(duration_high);

        digitalWrite(pin, LOW);
        delayMicroseconds(duration_low);

        unsigned int curr_time = micros();
        unsigned int real_duration = (curr_time - start_duration);

        // microsecs
        int abs_diff = real_duration - (duration_high + duration_low);

        // percent
        int rel_diff = 100 * abs_diff / period;

        if (rel_diff >= error) {
            printf("%d - softwarePWM - maximální přípustná relativní chyba časování v procentech byla překročena", curr_time);
        } else {
            printf("%d - softwarePWM - vše je OK !! :)", curr_time);
        }
        
        printf("\n MaxDiff: %d%\n RelDiff: %d%\n AbsDiff: %d\n RealDur: %d\n", error, rel_diff, abs_diff, real_duration);
        fflush(stdout); /* force it to go out */


        if (runtime && micros() > (start_time + runtime))
            break;
    }

}