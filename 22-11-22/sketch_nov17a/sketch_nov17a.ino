int valve=12;//Digital Output
int pushbuttonon=8;//Digital Input
int pushbuttonoff=9;//Digital Input
int soilmoisturesensor=A0;//Analog Input
int value;//The value of soil moisture
int manualbutton=10;

//--------------------------------------------------------------------------------------------------------------------------------
//Boolean variables
bool buttonstateon=false;
bool buttonstateoff=false;
bool moisture=false;
bool manual=true;
//--------------------------------------------------------------------------------------------------------------------------------

int soilmoisturelimit=480;   //THIS IS THE LIMIT SET


void setup() {
  // put your setup code here, to run once:
    pinMode(valve,OUTPUT);
    pinMode(pushbuttonon,INPUT);
    pinMode(pushbuttonoff,INPUT);
    pinMode(soilmoisturesensor,INPUT);
    pinMode(manualbutton,INPUT);
}

void loop() {

      //Reading Sensor Value
       value=analogRead(soilmoisturesensor);
       Serial.println("analog value:");
       Serial.println(value);
       delay(1000);

      //Logic for control

      if(value > soilmoisturelimit)
      {
        moisture=true;
      }
      
      if(value <= soilmoisturelimit)
      {
        moisture=false;
      }
      //Logic for manual or automatic

      if(!digitalRead(manualbutton))
      {
        manual=!manual;
      }
      
      //Manual program
      if (manual)
      buttonstateon=!digitalRead(pushbuttonon);
      if(buttonstateon)
      {

           digitalWrite(valve,HIGH);
           delay(1000);
           
      
      }
      buttonstateoff=!digitalRead(pushbuttonoff);
       if(buttonstateoff)
        {
           digitalWrite(valve,LOW);
           delay(1000);             
            
        
      }

      //Automatic Program
      if(!manual)
      {

        if(value>soilmoisturelimit)
        {
          digitalWrite(valve,HIGH);
          delay(1000);
        }
        if(value<soilmoisturelimit)
        {
          digitalWrite(valve,LOW);
          delay(1000);
        }


      }
      

     


}
