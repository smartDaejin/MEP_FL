#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softTone.h>
 
#define TRUE 1
#define TRIG 5
#define ECHO 6
#define BUZZER_PIN 4

#define TOTAL  32
 
void setup() {
    if  (wiringPiSetup() == -1) {
        fprintf(stderr, "Wpi setup failed.\n");
        exit(0);
    }

        pinMode(TRIG, OUTPUT);
        pinMode(ECHO, INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(30);
}
 
int getCM() {
        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);
 
        //Wait for echo start
        while(digitalRead(ECHO) == LOW) {
            continue;
        }
 
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH) {
            continue;
        }
        long travelTime = micros() - startTime;
 
        //Get distance in cm
        int distance = travelTime / 58;
 
        return distance;
}
 
int main(void) {
        setup();
        softToneCreate(BUZZER_PIN); 

        while(1) {
            int dist = getCM();
            int random = 0; 

            fprintf(stderr, "Distance: %dcm\n", dist);

            if (dist < 10)  {
                random = (rand()%200)+100;
                dist += random;
                delay(200);
            }
            if (dist <= 20)  {
                random = (rand()%300)+200;
                dist += random;
                delay(500);
            }
            if (dist <= 30)  {
                random = (rand()%400)+300;
                dist += random;
            } 
            else {
                random = (rand()%500)+400;
                dist += random;
                delay(1000);
            }

            softToneWrite(BUZZER_PIN, dist+100);
            delay(1000);
        }
 
        return 0;
}