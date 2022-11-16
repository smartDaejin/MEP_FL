/*
 *  온습도 센서 실험실습
 *
 * 	목표:
 *		DHT11 센서로 온도와 습도를 측정하여 화면에 표시
 *	구성:
 *		DHT11 센서 모듈로부터 온도, 습도 데이터를 반복적으로 수집
 *  	read_dht11()과 main()으로 구성
 *  	습도 %로 표시, 온도는 Celsius와 Fahrenheit의 2가지로 표시
 *	작성자:
 *		서민원	<20202170>
 *		조윤준	<20202177>
 */

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXTIMINGS    85
#define DHTPIN        7
 
int DHT11[5] = { 0, 0, 0, 0, 0 };


/*
 *  read_dht()	-	DHT11 모듈로부터 온도, 습도 데이터를 반복적으로 수집
 *
 *	구성:
 *		1초마다 온도 습도 데이터 읽기
 *  	255번 읽을 때마다 다시 반복
 *  	섭씨와 화씨를 모두 표시하도록 화씨 계산 사용
 *		DTH11[0], DTH11[1]	:	습도 정보
 *		DTH11[2], DTH11[3]	:	온도 정보
 */
void read_dht11()
{
    uint8_t laststate	=	HIGH;
    uint8_t counter	=	0;
    uint8_t j	=	0,	i;
    float	f; 
 
    DHT11[0] = DHT11[1] = DHT11[2] = DHT11[3] = DHT11[4] = 0;
 
    pinMode( DHTPIN, OUTPUT );			/*	DHTPIN의 출력 설정*/
    digitalWrite( DHTPIN, LOW );		/*	LOW(0) 값을 출력:	DHT11 끄기	*/
    delay( 18 );						/*	00.18초(18밀리초) 동안 대기	*/
    digitalWrite( DHTPIN, HIGH );		/*	HIGH(1) 값을 출력:	DHT11 켜기	*/
    delayMicroseconds( 40 );
    pinMode( DHTPIN, INPUT );			/*	DHTPIN 모드 입력으로 설정	*/
 
    for ( i = 0; i < MAXTIMINGS; i++ )
    {
        counter = 0;
        while ( digitalRead( DHTPIN ) == laststate )	/*	DHT11이 켜져 있는가?	*/
        {
            counter++;
            delayMicroseconds( 1 );
            if ( counter == 255 )
            {
                break;
            }
        }
        laststate = digitalRead( DHTPIN );	/*	DHT11상태 laststate에 저장	*/
 
        if ( counter == 255 )
            break;
 
        if ( (i >= 4) && (i % 2 == 0) )
        {
            DHT11[j / 8] <<= 1;
            if ( counter > 50 )
                DHT11[j / 8] |= 1;
            j++;
        }
    }
 
    if ( (j >= 40) &&
         (DHT11[4] == ( (DHT11[0] + DHT11[1] + DHT11[2] + DHT11[3]) & 255) ) )		/*	DHT11 측정된 값이 40보다 크거나 같고 255보다 작은가?	*/
    {
        f = DHT11[2] * 9. / 5. + 32;
        printf("습기 = %d.%d %% 온도 = %d.%d C (%.1f F)\n",
            DHT11[0], DHT11[1], DHT11[2], DHT11[3], f);
    }else  {
        printf("온습도가 측정되지 않았습니다.\n");
    }
}
 
int main( void )
{
    printf("DHT11 - 온습도 센서 측정 시작!\n");
    
    wiringPiSetup();
 
    while ( 1 )
    {
        read_dht11();
        delay( 2000 ); 
    }
 
    return(0);
}