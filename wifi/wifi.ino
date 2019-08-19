/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

//for input-output
SoftwareSerial NodeMCU(D2,D3);
//SoftwareSerial NodeMCU(D3,D2);

/*
 * HTTP Client POST Request
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>



/* Set these to your desired credentials. */
//char* ssid = "AndroidAP";
//const char* password =  "olrv4095";
char* ssid = "Ess";
const char* password =  "0524600066";
//char* ssid = "Student";
//const char* password =  "Aa123456";



//Web/Server address to read/write from 
const char *host = "10.100.102.131";   //https://circuits4you.com website or IP address of server

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(9600);
  //for connect with arduino
  NodeMCU.begin(4800);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
   
 
  
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {

 
  
 //receiving a value from the arduino
 
  while(NodeMCU.available()>0){ 
  int val  = NodeMCU.read();
  Serial.println("the wifi receive from the arduino val is: ");
  Serial.println(val);
  if(val == 1){

  
  HTTPClient http;    //Declare object of class HTTPClient

  String ADCData, station, postData;
  //int adcvalue=analogRead(A0);  //Read Analog value of LDR
  //ADCData = String(adcvalue);   //String to interger conversion
  station = "A";

  //Post Data
  postData = "{\"usr\":\"asaf\",\"sig\":1}" ;
  
  http.begin("http://10.100.102.13:3000/api/pluse");              //Specify request destination
  http.addHeader("Content-Type", "application/json");    //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
  
  delay(500);  //Post Data at every 5 seconds
  }
  else{
   Serial.println("no cigares for today - well done ! :)");  }
   }
}
