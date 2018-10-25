#include <wiringPi.h>
#include <stdio.h>
#include <curl/curl.h>
#include "ifttt.h"
#include <time.h> 
void countT(int number_of_seconds) 
{ 
    /* Converting time into milli_seconds */
    int milli_seconds = 1000 * number_of_seconds; 
  
    /*Stroing start time */
    clock_t start_time = clock(); 
  
    /* looping till required time is not acheived */ 
    while (clock() < start_time + milli_seconds) 
        ; 
} 
int main(int argc, char *argv[])
{
  /*clock_t start_t, end_t, total_t; */
  int state = 0;
  wiringPiSetup () ;
  pinMode (1, OUTPUT) ;/*LED 1*/
  pinMode (2, OUTPUT) ;/* LED 2*/
  pinMode (4, INPUT) ;/*Button */
  pinMode (5, OUTPUT); /*Buzzer */
  
switch (state) {
  case '0': 
     printf("ALARM_OFF ");
      for (;;) {
        digitalWrite (1, HIGH) ; /*sets LED 1 ON */ 
        /* digitalWrite (1,  LOW) ; delay (500) ; */
       digitalWrite (2,  LOW) ; /*sets LED 2 OFF */
      }
    digitalWrite (5, LOW) ; /*mutes the buzzer */
    state = digitalRead(1); 
    break;
  case '1':
    printf("ALARM_ARMING");
    digitalWrite (5, LOW) ; /*mutes the buzzer */
    countT(10);
    break;   
}






 return 0;

}
