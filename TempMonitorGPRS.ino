#include <Time.h>
#include <TimeLib.h>

#include "SIM900.h"
#include <SoftwareSerial.h>

#include <TimeAlarms.h>
#include "inetGSM.h"
#include <dht.h>
#include "sms.h"
#include "call.h" //Acceso a funciones de llamada
CallGSM call; //Creamos un objeto de llamada


dht DHT;
#define DHT11_PIN 5

SMSGSM sms;
char number[]="+50494505578";
boolean started=false;

//SoftwareSerial sim900(2,3); //sim900

void setup(){
  Serial.begin(9600);
  //Alarm.timerRepeat(15, MainAlarm); //Every 1 hour
  makeCall();
}

void makeCall() {

  if (gsm.begin(9600)) {
    Serial.println("\nstatus=READY");
    started=true;
  } else {
    Serial.println("\nstatus=IDLE");
  }
  
  if(started) {
  
    if(call.CallStatus()!= CALL_ACTIVE_VOICE){
      Serial.println("Calling...");
      call.Call(number); //Llamamos usando call.Call()
    }
  }
  
}

void loop(){
  Alarm.delay(10); // wait one second between clock display

}

void MainAlarm(){
  Serial.println("Main Alarm...");
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  double temp = DHT.temperature;
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  double hum = DHT.humidity;
  Serial.println(DHT.humidity);
  sendData(temp,hum);
}

void sendData(double temp, double hum){
  
  if (gsm.begin(9600)) {
    Serial.println("\nstatus=READY");
    started=true;
  } else {
    Serial.println("\nstatus=IDLE");
  }
  
  if(started) {
    //Enable this two lines if you want to send an SMS.
    if (sms.SendSMS(number, "Wtf2"))
      Serial.println("\nSMS sent OK");
   }
}

