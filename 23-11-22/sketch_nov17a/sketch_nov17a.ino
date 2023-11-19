const int valve=12;//Digital Output
const int pushbuttonon=8;//Digital Input
const int pushbuttonoff=9;

const int manualbutton=10;
const int manualindication=11;
//--------------------------------------------------------------------------------------------------------------------------------
//Boolean variables
bool buttonstateon=false;
bool buttonstateoff=false;
bool moisture=false;
bool manual=true;
//--------------------------------------------------------------------------------------------------------------------------------
int sensorPin = A0; 
int sensorValue;  
int limit = 300;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(valve,OUTPUT);
    pinMode(pushbuttonon,INPUT);
    pinMode(pushbuttonoff,INPUT);
    //pinMode(soilmoisturesensor,INPUT);
    pinMode(manualbutton,INPUT);
    pinMode(manualindication,OUTPUT);
}
void loop() {

      //Reading Sensor Value
      
      sensorValue = analogRead(A5); 
      Serial.println("Analog Value : ");
      Serial.println(sensorValue);
      

      //Logic for control

      if(sensorValue > limit)
      {
        moisture=true;
      }
      
      if(sensorValue <= limit)
      {
        moisture=false;
      }
      //Logic for manual or automatic

      if(!digitalRead(manualbutton))
      {
        manual=!manual;
      }
      
      //Manual program
      if (manual){
      digitalWrite(manualindication,HIGH);
      delay(5);
      buttonstateon=!digitalRead(pushbuttonon);
      if(buttonstateon)
      {

           digitalWrite(valve,HIGH);
           delay(10);
           
      
      }
      buttonstateoff=!digitalRead(pushbuttonoff);
       if(buttonstateoff)
        {
           digitalWrite(valve,LOW);
           delay(10);             
            
        
      }
      }

      //Automatic Program
      if(!manual)
      {
      
      

      digitalWrite(manualindication,LOW);
      delay(5);
        if(sensorValue > limit)
        {
          digitalWrite(valve,HIGH);
          delay(5);
        }
        if(sensorValue < limit)
        {
          digitalWrite(valve,LOW);
          delay(5);
        }


      }
      


}
     


