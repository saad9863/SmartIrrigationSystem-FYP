int valve=12;//Digital Output
int pushbuttonon=8;//Digital Input
int pushbuttonoff=9;//Digital Input
int soilmoisturesensor=A0;//Analog Input
int manualbutton=10;//Digital Input
int value;//The value of soil moisture

//--------------------------------------------------------------------------------------------------------------------------------
//Boolean variables
bool buttonstateon=false;
bool buttonstateoff=false;
bool on = false;
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

      

      
    //CODE FOR READING MOISTURE SENSOR DATA 
       value=analogRead(soilmoisturesensor);
       Serial.println("analog value:");
       Serial.println(value);
       delay(1000);

     
     //ManualButton
    if(!digitalRead(manualbutton)){
        manual=!manual;
     }

    //LOGIC FOR TESTING MOISTURE CONTENT
     if(value > soilmoisturelimit)
      {
        moisture=true;
      }
      
      else if(value <= soilmoisturelimit)
      {
        moisture=false;
      }


      

    if (manual){
      buttonstateon=!digitalRead(pushbuttonon);
      if(buttonstateon)
      {

      
        on=true;

        while(on){

           digitalWrite(valve,HIGH);
           delay(1000);

            buttonstateoff=!digitalRead(pushbuttonoff);
          if(buttonstateoff)
           {
             
             digitalWrite(valve,LOW);
             delay(1000);
             
             on=false;
           }
        
          
        }
      }
     
     }
     //IF AUTOMATIC
    else
     {
       if(value>soilmoisturelimit)
         {
           digitalWrite(valve,HIGH);
           delay(1000);
         }
        else if(value<=soilmoisturelimit)
        {
           digitalWrite(valve,LOW);
           delay(1000);
        }


     }
      

     


}
