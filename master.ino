#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include<LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
struct reciver
{
 int e[2]={0,0};
 int temp[2]={0,0};
 int humid[2]={0,0};
 int flame[2]={0,0};
};
int led1=8;
RF24 mast(9,10);
const uint8_t p =00003;
int k[2]={0,0};
reciver r;
void setup()
{
 Serial.begin(9600);
 lcd.begin(16,2);
 mast.begin();
 mast.openReadingPipe(1, p);
 mast.setDataRate(RF24_1MBPS);
 mast.setPALevel(RF24_PA_LOW);
 mast.setCRCLength(RF24_CRC_16);
 mast.startListening();
}
void loop()
{
 String str;
 char buf[50];
if(mast.available())
{
 mast.read(&r, sizeof(r));
 //Serial.print("Temperature1 = ");
 //Serial.println(r.temp[0]);
 //Serial.print("Humidity1 = ");
 //Serial.println(r.humid[0]);
 //Serial.print("flame1 = ");
 //Serial.println(r.flame[0]);
 //Serial.print("Temperature2 = ");
 //Serial.println(r.temp[1]);
 //Serial.print("Humidity2 = ");
 //Serial.println(r.humid[1]);
 //Serial.print("flame2 = ");
 //Serial.println(r.flame[1]);
if (r.e[0]==1 && r.e[1]==1) {
 digitalWrite(led1, HIGH);
 lcd.clear();
 lcd.print("Fire Detector");
 lcd.setCursor(0,1);
 lcd.print("Fire in both loc");
 }
else if(r.e[0]==1 && r.e[1]==0)
 {
 digitalWrite(led1, HIGH);
 lcd.clear();
 lcd.print("Fire Detector");
 lcd.setCursor(0,1);
 lcd.print("Fire in loc. 2");
 //Serial.print("Fire in loc. 2");
 }
else if(r.e[0]==0 && r.e[1]==1)
 {
 digitalWrite(led1, HIGH);
 lcd.clear();
 lcd.print("Fire Detector");
 lcd.setCursor(0,1);
 lcd.print("Fire in loc. 1");
 //Serial.print("Fire in loc. 1");
 }
else
{
 digitalWrite(led1, LOW);
 lcd.clear();
 lcd.print("Fire Detector");
 lcd.setCursor(0,1);
 lcd.print("No fire detected");
}
}
else
{
 digitalWrite(led1, LOW);
 lcd.clear();
 lcd.print("Fire Detector");
 lcd.setCursor(0,1);
 lcd.print("No fire detected");
}
str = str + 1 + ',' +
r.temp[1]+','+r.humid[1]+','+r.flame[1]+'#'+2 + ',' +
r.temp[0]+','+r.humid[0]+','+r.flame[0]+'\n';
str.toCharArray(buf,50);
Serial.write(buf);
delay(2000);
}
