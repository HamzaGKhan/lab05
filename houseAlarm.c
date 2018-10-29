#include <wiringPi.h>
#include <stdio.h>
#include <curl/curl.h>
#include "ifttt.h"
#include <time.h> 

int state0(int state);
int state1(int state);
int state2(int state);
int state3(int state);
int state4(int state);


int main(int argc, char *argv[])
{
  /*clock_t start_t, end_t, total_t; */
  int state ;
  wiringPiSetup() ;
  pinMode (1, OUTPUT) ;/*LED 1*/
  pinMode (2, OUTPUT) ;/* LED 2*/
  pinMode (3,INPUT); /*Button*/
  pinMode (4, INPUT) ;/*Buzzer */
  pullUpDnControl(3,PUD_UP);
  pinMode (5, OUTPUT); /*IR Scanner */
  state = 1;
  while (1) 
 {
  state = state0(state); /*Sets to Alarm OFF */
  state = state1(state); /*Sets to Alarm Arming*/
  state = state2(state); /*Sets to Alarm Armed */
  
  if(state == 4){
    state = state3(state);
    printf("Alarm_Triggered ");
  }
  if (state == 5) {
   state = state4(state);
   printf("Alarm_Sounding");
  }
 }
  return 0;   
}


/* sets the state to alarm_Off */
int state0 (int state)
{
  wiringPiSetup();
  if (state == 1)
  {
  printf("ALARM_OFF");
  delay(5000); 
   while (1)
   {
     printf("Alarm 0\n");
     digitalWrite(1,HIGH); /*sets LED 1 ON */
     /* delay(1000); */        
     digitalWrite(2,LOW); /*sets LED 2 OFF */
     /*delay(1000);*/
     digitalWrite(4,LOW); /*mutes the buzzer */
    /* delay(1000);*/
    if (digitalRead(3) == 0){
      printf("Alarm_Arming");
      return 2;
     }
   }
}
    return 0;
} 

/*sets the state to Alarm_Arming */
int state1 (int state)
{
 int i;
 wiringPiSetup();
 if (state == 2)
 {
  printf("Alarm_Arming");
  digitalWrite(4,LOW); /*mutes the buzzer */
  for (i = 0; i<5; i++)
  {        
  digitalWrite(2,LOW); delay(1000);/*sets LED 2 OFF */
  digitalWrite(2,HIGH);delay(1000); /*sets LED 2 ON */
   }
  return 2;
 }
 return 0;
}


/*sets state to Alarm Armed*/
int state2 (int state)
{
  wiringPiSetup();
 if (state == 3) {
  printf("ALARM ARMED\n");
  for (;;) 
    {
     printf("VALUE OF TRIGGER Alarm: %d\n",digitalRead(5));
     digitalWrite(1,LOW);/*sets LED 1 OFF */
     digitalWrite(2,HIGH); /*sets LED 2 ON */
     digitalWrite(4,LOW); /*mutes the buzzer */
  
     if (digitalRead(3) == 0) /* If the button is pressed */
     {
         printf("ALARM IS OFF\n");
         return 1;
     }
     if (digitalRead (0) == 1) /*if the alarm is triggered */
      {
        printf("Alarm_TRIGGERED");
        return 4;
      }
   }
  return 0;
}

/*sets state to alarm triggered*/
int state3(int state)
{
  int i;
  wiringPiSetup();
  digitalWrite(4,LOW); /*mutes the buzzer */
  for (i=0;(i<5) && (digitalRead(3) == 1); i++){ 
  printf("ALARM_TRIGGERED");
  digitalWrite(1,HIGH);/*sets LED 1 ON */
  digitalWrite(2,HIGH); /*sets LED 2 ON */
  delay(1000);
  digitalWrite(1,LOW);/*sets LED 1 OFF */
  digitalWrite(2,LOW); /*sets LED 2 OFF*/
  delay(1000);
  }
  if (i == 5)
    return 5;
  return 1;
}

/*sets state to alarm sounding */
int state4(int state)
{
 wiringPiSetup();
 iffft("https://maker.ifttt.com/trigger/alarm_triggered/with/key/nAtR0mlz6FSWp52xT1BGw");
 printf("ALARM SOUNDING\n");
 for(;;)
 {
  digitalWrite(1,HIGH);/*sets LED 1 ON */
  digitalWrite(2,HIGH); /*sets LED 2 ON */
  digitalWrite(4,HIGH); /*plays the buzzer */
  delay(2000);
  digitalWrite(1,LOW);/*sets LED 1 OFF */
  digitalWrite(2,LOW); /*sets LED 2 OFF*/
  digitalWrite(4,LOW); /*mutes the buzzer */
  delay(2000);
  printf("INTRUDER ALERT!");
  if (digitalRead(3) == 0)
   return 1; 
  }
 }
}
