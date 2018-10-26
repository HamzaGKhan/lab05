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

/* sets the state to alarm_Off
int state0 ()
{
  while (digitalRead(1) == 1)
  {
     digitalWrite(1,HIGH) ; /*sets LED 1 ON */
     countT(1);         
     /* digitalWrite(1,LOW) ; delay (500) ;*/
     digitalWrite(2,LOW) ; /*sets LED 2 OFF */
    countT(1);
    digitalWrite(5,LOW) ; /*mutes the buzzer */
    countT(1);
  }
    printf("Alarm_Off");
    return 1;
} 

/*sets the state to Alarm_Arming */
int state1 ()
{
while (digitalRead(1) == 1)
 {
 digitalWrite(5,LOW) ; /*mutes the buzzer */
  digitalWrite(1,HIGH) ; /*sets LED 1 ON */
  countT(1);         
  digitalWrite(1,LOW) ;/*sets LED 1 OFF */
  timeT (1) ; 
  countT(10);
  digitalWrite(2,HIGH) ; /*sets LED 2 ON */
 }
 printf("ALARM_ARMING ");
 return 1;
}


/*sets state to Alarm Armed*/
int state2 ()
{
  for (;;) 
   {
  digitalWrite(1,LOW) ;/*sets LED 1 OFF */
  digitalWrite(2,HIGH) ; /*sets LED 2 ON */
  digitalWrite(5,LOW) ; /*mutes the buzzer */
  
  if (digitalRead(4) == 0) /* If the button is pressed */
     return state0();
  if (digitalRead (0) == 0) /*if the alarm is triggered */
     return state3();
  printf("Alarm_Armed");
  }
}

/*sets state to alarm triggered*/
int state3()
{
  digitalWrite(5,LOW) ; /*mutes the buzzer */
  digitalWrite(1,HIGH) ;/*sets LED 1 ON */
  digitalWrite(2,HIGH) ; /*sets LED 2 ON */
  timeT(10);
  digitalWrite(1,LOW) ;/*sets LED 1 OFF */
  digitalWrite(2,LOW) ; /*sets LED 2 OFF*/
  if (digitalRead(4) == 0)
   return state0();
  else
   {
   printf("ALARM_TRIGGERED");
   return state4();
  }
}

int state4()
{
 for(;;)
 {
  digitalWrite(1,HIGH) ;/*sets LED 1 ON */
  digitalWrite(2,HIGH) ; /*sets LED 2 ON */
  digitalWrite(5,HIGH) ; /*plays the buzzer */
  timeT(2);
  digitalWrite(1,LOW) ;/*sets LED 1 OFF */
  digitalWrite(2,LOW) ; /*sets LED 2 OFF*/
  timeT(2);
  printf("INTRUDER ALERT!");
  if (digitalRead(4) == 0)
   return state0(); 
 }
}

int main(int argc, char *argv[])
{
  /*clock_t start_t, end_t, total_t; */
  int state = 0;
  wiringPiSetup () ;
  pinMode(0, INPUT); /*Motion Sensor */
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
