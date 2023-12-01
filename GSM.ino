
#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
SoftwareSerial gprsSerial(2,3); //RX.TX


#include <String.h>
#include <DHT.h>
#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
#define DHTPIN A2
 
DHT dht(DHTPIN, DHT22);
const int rainsensor = A1;


float h;
float t;

int soilmoispin = A0; 
int rain;



int soilmois;

int smoisreq=55;            // required soil moisture

void setup()
{
  gprsSerial.begin(9600); // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  dht.begin();
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  delay(1000);
}
 
void loop()
{

      float humi = dht.readHumidity();
      float temp = dht.readTemperature(); 
      // soilmois = analogRead(A0); 
     // int soil=analogRead(A0);
     // map(j,0,982,148,0)
       soilmois=map(analogRead(A0),0,1023,100,0);
      //soilmois = soilmois/100.0; 
      //soilmois = (soilmois/1023)*100.0;
      //soilmois= ( 100 - ( (analogRead(A0)/1023.00) * 100 ) );
      
      rain=analogRead(A1);
      delay(100);   
      int rainper=map(rain,0,1023,100,0);

      if(!isnan(humi)){
        h=humi;
      }
      
      if(!isnan(temp)){
        t=temp;
      }
         
      Serial.print("Temperature = ");
      Serial.print(t);
      Serial.println(" °C");
      Serial.print("Humidity = ");
      Serial.print(h);
      Serial.println(" %");   
      Serial.print("CurrentRain = ");
      Serial.print(rainper);
      Serial.println(" %");
      Serial.print("Soil Moisture Content = ");
      Serial.print(soilmois);
      Serial.println(" %"); 

      bool rain=false;
      if(rainper>50)
      {
        rain=true;

      }
      
        
      

//Code to control proportional solenoid valve

    int servo_pos;                                           // servo position
    int vp;                                                 // valve percentage
    
    if (soilmois < smoisreq/4 && !rain) {
    servo_pos = 30; //100% open
    vp=100;
    } else if (soilmois < smoisreq/3 && !rain)  {
    servo_pos = 15; //75% open
    vp=75;
    } else if (soilmois < smoisreq/2 && !rain) {
    servo_pos = 0; //50% open
    vp=50;
    } else if (soilmois < smoisreq && !rain) {
    servo_pos = 60 ;//30% open
    vp=25;
    } else {
    servo_pos = 100; //0% open
    vp=0;
    }
    

myservo.write(servo_pos);
delay(1000);
 
 
/*
      Serial.print("Soil Moisture");
      Serial.print(soilmois);
      Serial.println(" °C");

      Serial.print("Rain = ");
      Serial.print(rainper);
      Serial.println(" %");    
*/
     lcd.begin(16, 2);
     lcd.print("SM: ");
     lcd.print(soilmois);
     lcd.print("%");
     lcd.print("H: ");
     lcd.print(humi);
     lcd.print("%");
     
     lcd.setCursor(0,1);
     lcd.print("T: ");
     lcd.print(temp);
     lcd.print("*C");
     
     lcd.print("Rain");
     lcd.print(rainper);
     lcd.print("%");
     delay(2000);
      

  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
  
  gprsSerial.println("AT");
  delay(1000);
 
  gprsSerial.println("AT+CPIN?");
  delay(1000);
 
  gprsSerial.println("AT+CREG?");
  delay(1000);
 
  gprsSerial.println("AT+CGATT?");
  delay(1000);
 
  gprsSerial.println("AT+CIPSHUT");
  delay(1000);
 
  gprsSerial.println("AT+CIPSTATUS");
  delay(2000);
 
  gprsSerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"ufone.pinternet\"");//start task and setting the APN,//ufone.pinternet//zonginternet
  delay(1000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=[THING SPEAK API KEY]&field3=" + String(t) + "&field4="+String(h) + "&field3="+String(t) + "&field1="+String(soilmois)+ "&field2="+String(rainper)+ "&field5="+String(vp);
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  
  delay(4000);
  ShowSerialData();
 
  gprsSerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  
} 



void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(5000); 
  
}

