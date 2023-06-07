#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include<WifiClient.h>
#include <ThingSpeak.h>
 
// Data wire is connected to digital pin 7 on the Arduino
#define ONE_WIRE_BUS 4

const char* ssid = "Des11";
const char* password ="12345678";

WiFiClient client;

unsigned long myChannelNumber = 2117219;
const char *myWriteAPIKey= "IQHC1ATP4VNX5C0E";



 
// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);	
 
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

  float sum = 0 ;
  int count = 1;
  float avg,M;  
void setup(void)
{
  sensors.begin();	// Start up the library
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  ThingSpeak.begin(client);
}
 
void loop(void)
{ 
 // Send the command to get temperatures
  sensors.requestTemperatures(); 
 
  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  //shows degrees character
  Serial.println("°C");
  

 float temp = sensors.getTempCByIndex(0);  
  sum = sum+temp+10;
  avg = sum/count;
  M = avg*count;
Serial.println(M); 
  delay(100);
count += 1;
ThingSpeak.writeField(myChannelNumber,1,temp,myWriteAPIKey);
ThingSpeak.writeField(myChannelNumber,2,M,myWriteAPIKey);
//delay(143800); //for 1 hour delay  
}
