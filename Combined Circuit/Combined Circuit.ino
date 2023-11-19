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

int limit = 700;
int soilmois;
int moisturelcd;
int rain;
void setup() {
  // put your setup code here, to run once:
  pinMode(rainsensor, INPUT);
  pinMode(valve, OUTPUT);
  Serial.begin(9600);
  pinMode(valve,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
     soilmois = analogRead(A5); 
     lcd.begin(16, 2);
     lcd.print("Moisture ");
     soilmois=(soilmois/1023)*100;
     rain=analogRead(A1);
     lcd.begin(16, 2);
     lcd.print("Moisture ");
     lcd.print(soilmois);
     lcd.print("%");
     delay(2000);
     if(rain>=300){
          lcd.clear();
          lcd.begin(16, 2);
          lcd.print("Not Raining");
          lcd.setCursor(0,1);
          lcd.print("Value: ");
          lcd.print(rain);
          delay(2000);
     }
     else if(rain<300){
          lcd.clear();
          lcd.begin(16, 2);
          lcd.print("Raining");
          lcd.setCursor(0,1);
          lcd.print("Value: ");
          lcd.print(rain);
          delay(2000);
   
     }

      //Logic for manual or automatic
      if(!digitalRead(manualbutton))
      {
        manual=!manual;
      }
      
      //Manual program
      if (manual){
      digitalWrite(manualindication,HIGH);
       lcd.clear();
          lcd.begin(16, 2);
          lcd.print("Manual Mode");
          delay(2000);
      delay(5);
      
      if(!digitalRead(pushbutton1))
      {
          on1=!on1;
          if (on1)
          {
           digitalWrite(valve, HIGH);
           lcd.clear();
          lcd.begin(16, 2);
          lcd.print("Valve Open");
          delay(2000);
          delay(200);
          }
           
          if(!on1)
          {
            digitalWrite(valve, LOW);
          lcd.clear();
          lcd.begin(16, 2);
          lcd.print("Valve Shut");
          delay(2000);
          delay(500);
          }

      
      }
     //Automatic Program
  if(!manual){
  digitalWrite(manualindication,LOW);
   lcd.clear();
          lcd.begin(16, 2);
          lcd.print("Automatic mode");
          delay(2000);
  delay(5);
      
 if (soilmois >= limit ) {

    digitalWrite(valve, LOW);
       lcd.clear();
          lcd.begin(16, 2);
          lcd.print("Valve Shut");
          delay(2000);
    delay(500);
  }
  if (rain<300) {
   
    digitalWrite(valve, LOW);
       lcd.clear();
          lcd.begin(16, 2);
          lcd.print("Valve Shut");
          delay(2000);
    delay(200);
  }
  if (soilmois < limit && rain>=300) {
    
    digitalWrite(valve, HIGH);
       lcd.clear();
          lcd.begin(16, 2);
          lcd.print("Valve Open");
          delay(2000);
    delay(200);
  }
}
}
}