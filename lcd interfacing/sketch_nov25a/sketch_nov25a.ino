#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int pushbutton1=9;//Digital Input
const int manualbutton=10;
const int manualindication=11;
const int valve = 12;
const int rainsensor = 13;
//--------------------------------------------------------------------------------------------------------------------------------
//Boolean variables

bool buttonstateoff=false;
bool moisture=false;
bool manual=true;
bool on1=false;
//-------------------
int sensorPin = A5; 

int limit = 50;
int sensorValue;
int moisturelcd;
void setup() {
  // put your setup code here, to run once:
  pinMode(rainsensor, INPUT);
  pinMode(valve, OUTPUT);
  Serial.begin(9600);
  pinMode(valve,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
     sensorValue = analogRead(A5); 
     sensorValue=map(sensorValue,550,0,0,100);
     lcd.begin(16, 2);
     lcd.print("Moisture ");
     lcd.print(sensorValue);
     lcd.print("%");
     delay(500);

      //Logic for manual or automatic
      if(!digitalRead(manualbutton))
      {
        manual=!manual;
      }
      
      //Manual program
      if (manual){
      digitalWrite(manualindication,HIGH);
      delay(5);
      
      if(!digitalRead(pushbutton1))
      {
          on1=!on1;
          if (on1)
          {
           digitalWrite(valve,HIGH);
           delay(10);
          }
           
          if(!on1)
          {
           digitalWrite(valve,LOW);
           delay(10);            
          }
      }

      
      }
     //Automatic Program
  if(!manual){
  if (sensorValue >= limit ) {
    digitalWrite(valve, LOW);
    delay(500);
  }
  if (digitalRead(rainsensor)) {
    lcd.begin(16, 2);
    lcd.print("Raining");
    digitalWrite(valve, LOW);
    delay(200);
  }
  if (sensorValue < limit && !digitalRead(rainsensor)) {
    lcd.begin(16, 2);
    lcd.print("Not Raining");
    digitalWrite(valve, HIGH);
    delay(200);
  }
}
}