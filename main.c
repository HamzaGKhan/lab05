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
  pinMode (3,INPUT); /*ir scanner*/
  pinMode (4, INPUT) ;/*Button */
  pullUpDnControl(3,PUD_UP);
  pinMode (5, OUTPUT); /*Buzzer */
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

