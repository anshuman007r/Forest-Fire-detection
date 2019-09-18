#include <dht.h>
#include "nRF24L01.h"
#include "RF24.h"
struct interface1
{
 int e[2]={0,0};
 int temp[2]={0,0};
 int humid[2]={0,0};
 int flame[2]={0,0};
};
struct transmit2
{
 int e=0;
 int temp=0;
 int humid=0;
 int flame=0;
};
interface1 in;
transmit2 tm;
dht DHT;
RF24 slv2(9,10);
const uint8_t p[2] = {00002,00003};
int pin1=7;
int led=6;
int pin3=A0;
int k=0;
int t=0;
#define DHT11_PIN 7
void setup(){
 Serial.begin(9600);
 pinMode(pin1,INPUT);
 pinMode(pin3,INPUT);
 pinMode(led,OUTPUT);
 slv2.begin();
 slv2.openReadingPipe(1,p[0]);
 slv2.openWritingPipe(p[1]);
 slv2.setDataRate(RF24_1MBPS);
 slv2.setPALevel(RF24_PA_HIGH);
 slv2.setCRCLength(RF24_CRC_16);
}
void loop()
{
 slv2.startListening();
 if(slv2.available())
 {
 slv2.read(&tm, sizeof(tm));
 Serial.println(1);
 in.e[0]=tm.e;
 in.temp[0]=tm.temp;
 in.humid[0]=tm.humid;;
 in.flame[0]=tm.flame;
 }
 delay(5);
 slv2.stopListening();
 int chk = DHT.read11(DHT11_PIN);
 Serial.print("Temperature = ");
 Serial.println(DHT.temperature);
 Serial.print("Humidity = ");
 Serial.println(DHT.humidity);
 k=analogRead(pin3);
 Serial.println(k);
 if(k<=50|| t>50)
 {
 digitalWrite(led,HIGH);
 in.e[1]=1;
 in.temp[1]=DHT.temperature;
 in.humid[1]=DHT.humidity;
 in.flame[1]=k;
 slv2.write(&in, sizeof(in));
 }
 else
 {
 digitalWrite(led,LOW);
 in.e[1]=0;
 in.temp[1]=DHT.temperature;
 in.humid[1]=DHT.humidity;
 in.flame[1]=k;
 slv2.write(&in,sizeof(in));
 }
 delay(500);
}
