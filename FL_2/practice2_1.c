#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define LED1 4
#define LED2 5

void state(int delay_t, unsigned short port1, unsigned short Port2)
{
    digitalWrite(LED1, port1);
    digitalWrite(LED2, Port2);
    delay(delay_t * 1000);
}

void main(void)
{
    int     i=0;
    if (wiringPiSetup() < 0) {
        exit(0);
    }
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    while (i<10) {
        state(1, 1, 0);
        state(1, 1, 1);
        state(1, 0, 1);
        state(1, 0, 0);
        i++;
    }
}