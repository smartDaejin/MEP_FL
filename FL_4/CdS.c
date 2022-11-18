#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define CDS 0 /* wiringPi 0, GPIO17 */
#define LED 1 /* wiringPI 1, GPIO18 */

int cdsControl()
{
    printf("CALL cds func\n");
    int i;

    pinMode(CDS, INPUT);  /* Pin 모드를 입력으로 설정 */
    pinMode(LED, OUTPUT); /*   Pin 모드를 출력으로 설정 */

    for (i = 0; i < 10000000; i++)
    {
        if (digitalRead(CDS) == HIGH) /* 빛이 감지되면(HIGH) */
        {
            digitalWrite(LED, HIGH); /*   LED   On   */
            delay(1000);
            digitalWrite(LED, LOW); /*   LED   Off   */
        }
        else
            printf(CDS);
    };
    printf("CDS -> " + digitalRead(CDS));
    return 0;
}

int main()
{
    if (wiringPiSetup() == -1)
    {
        fprintf(stderr, "WiringPi setup failed....\n");
        exit(0);
    }

    cdsControl();

    return 0;
}