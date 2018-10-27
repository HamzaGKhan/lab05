#include <wiringPi.h>
#include <stdio.h>
#include <curl/curl.h>
#include "ifttt.h"
#include <time.h> 

int main(int argc, char *argv[])
{
  /*clock_t start_t, end_t, total_t; */
  int state ;
  wiringPiSetup() ;
  pinMode (1, OUTPUT) ;/*LED 1*/
  pinMode (2, OUTPUT) ;/* LED 2*/
  pinMode (4, INPUT) ;/*Button */
  pullUpDnControl(1,PUD_UP);
  pinMode (5, OUTPUT); /*Buzzer */
  state = state0();
  while (1) 
 {
  state = state0(); /*Sets to Alarm OFF */
  state = state1(); /*Sets to Alarm Arming*/
  state = state2(); /*Sets to Alarm Armed */
  
  if(state == state3()){
    state = state3();
    printf("Alarm_Triggered ");
  }
  if (state == state4()) {
   state = state4();
   printf("Alarm_Sounding");
  }
 }
  return 0;   
}


/* sets the state to alarm_Off */
int state0 ()
{
  wiringPiSetup();
  while (digitalRead(1) == 1)
  {
     digitalWrite(1,HIGH); /*sets LED 1 ON */
     delay(1000);         
     digitalWrite(2,LOW); /*sets LED 2 OFF */
    delay(1000);
    digitalWrite(5,LOW); /*mutes the buzzer */
    delay(1000);
    break;
  }
    printf("Alarm_Off");
    return 0;
} 

/*sets the state to Alarm_Arming */
int state1 ()
{
 wiringPiSetup();
 while (digitalRead(1) == 1)
 {
 digitalWrite(5,LOW); /*mutes the buzzer */
  digitalWrite(1,HIGH); /*sets LED 1 ON */
  delay(1000);         
  digitalWrite(1,LOW);/*sets LED 1 OFF */
  delay(1000) ; 
  delay(10000);
  digitalWrite(2,HIGH); /*sets LED 2 ON */
 }
 printf("ALARM_ARMING ");
 return 1;
}


/*sets state to Alarm Armed*/
int state2 ()
{
  wiringPiSetup();
  for (;;) 
   {
  digitalWrite(1,LOW);/*sets LED 1 OFF */
  digitalWrite(2,HIGH); /*sets LED 2 ON */
  digitalWrite(5,LOW); /*mutes the buzzer */
  
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
  wiringPiSetup();
  digitalWrite(5,LOW); /*mutes the buzzer */
  digitalWrite(1,HIGH);/*sets LED 1 ON */
  digitalWrite(2,HIGH); /*sets LED 2 ON */
  delay(10000);
  digitalWrite(1,LOW);/*sets LED 1 OFF */
  digitalWrite(2,LOW); /*sets LED 2 OFF*/
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
 wiringPiSetup();
 for(;;)
 {
  digitalWrite(1,HIGH);/*sets LED 1 ON */
  digitalWrite(2,HIGH); /*sets LED 2 ON */
  digitalWrite(5,HIGH); /*plays the buzzer */
  delay(2000);
  digitalWrite(1,LOW);/*sets LED 1 OFF */
  digitalWrite(2,LOW); /*sets LED 2 OFF*/
  delay(2000);
  printf("INTRUDER ALERT!");
  if (digitalRead(4) == 0)
   return state0(); 
 }
}

 
