

//for wifi
#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(3,2);

//for sensors - smoke and air flow
//#include <SPI.h>
#define echoPin 7
#define trigPin 8
#define echo2Pin 12
#define trig2Pin 11

/*for smoke*/

int buzzer = 10;
int smokeA0 = A5;
int sensorThres =400;
int pivot = 0;
float total_smoke = 0;

/*for flow air*/

float duration;
float duration2;
float distance;
float distance2;


float ultra1(){
  
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  return distance;
}


float ultra2(){
  digitalWrite(trig2Pin, LOW);
  digitalWrite(trig2Pin, HIGH);

  duration2 = pulseIn(echo2Pin, HIGH);
  distance2 = duration2/58.2;
  return distance2;
}

void smokeSensor(){
    /*for smoke*/
    int analogSensor = analogRead(smokeA0);
    if(analogSensor >=(pivot+300)){
        //send to wifi the 1 air flow of cigare
        Serial.print("Sending to wifi 1 cigare ");
        ArduinoUno.write(1);
        
        Serial.print("total smoke calc: ");
        total_smoke+=((ultra1()+ultra2())/2.0);
        Serial.println(total_smoke);
   
    } 
    
    // Checks if it has reached the threshold value
    if (analogSensor > sensorThres){
        tone(buzzer, 1000, 200);
    } else {
        noTone(buzzer);
    }  
}



void setup(){

  
  //for wifi	
  	Serial.begin(9600);
  	ArduinoUno.begin(4800);

    /*for air flow*/
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echo2Pin, INPUT);
    pinMode(trig2Pin, OUTPUT);
    
  
    /*for smoke*/
    
    pinMode(buzzer, OUTPUT);
    pinMode(smokeA0, INPUT);
    pivot=analogRead(smokeA0);
    delayMicroseconds(100000);

    char data[100];  
    
}

void loop(){

/*
// sendiing the value to wifi
   int val =10;
   Serial.println("the val arduino is: ");
   Serial.println(val);
   ArduinoUno.write(val);
   */
   

   /*for air flow*/
     Serial.print("ultra 1 is : ");
     float ult1 = ultra1();
     Serial.println(ult1);
     Serial.print("ultra 2 is : ");
     float ult2 = ultra2();
     Serial.println(ult2);
     
    /*for smoke sensor*/
    smokeSensor();
 
 delay(300);
}
