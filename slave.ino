#include <dht.h>
#include "nRF24L01.h"
#include "RF24.h"
struct transmit
{
 int e=0;
 int temp=0;
 int humid=0;
int flame=0;
};
dht DHT;
RF24 slv1(9,10);
const uint64_t pip =00002;
int pin1=7;
int led=6;
int pin3=A0;
int k;
int e[2]={0,0};
int t=0;
transmit tm;
#define DHT11_PIN 7
void setup(){
 Serial.begin(9600);
 pinMode(pin1,INPUT);
 pinMode(pin3,INPUT);
 pinMode(led,OUTPUT);
 slv1.begin();
 slv1.openWritingPipe(pip);
 slv1.setDataRate(RF24_1MBPS);
 slv1.setCRCLength(RF24_CRC_16);
 slv1.setPALevel(RF24_PA_HIGH);
}
void loop()
{

 int chk = DHT.read11(DHT11_PIN);
 Serial.print("Temperature = ");
 Serial.println(DHT.temperature);
 t=DHT.temperature;
 Serial.print("Humidity = ");
 Serial.println(DHT.humidity);
 k=analogRead(pin3);
 Serial.println(k);
 slv1.stopListening();
 if(k<=50 || t>50 )
 {
 digitalWrite(led,HIGH);
 tm.e=1;
 tm.temp=DHT.temperature;
 tm.humid=DHT.humidity;
 tm.flame=k;
 slv1.write(&tm, sizeof(tm));
 delay(500);
 }
 else
 {
 digitalWrite(led,LOW);
 tm.e=0;
 tm.temp=DHT.temperature;
 tm.humid=DHT.humidity;
 tm.flame=k;
 slv1.write(&tm, sizeof(tm));
 delay(500);
 }
}
