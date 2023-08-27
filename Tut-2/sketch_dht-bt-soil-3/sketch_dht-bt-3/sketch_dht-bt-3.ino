#include <string.h>
#include "DHT.h"

#define DHTPIN 21 // Teensy 2.0 uses digital pin 21 for DHT sensor module

#define DHTTYPE DHT11 // DHTType is 11 for Teensy 2.0

#define LedPin 11 // LED PIN is 11 for Teensy 2.0

#define keyPin 9

#define soilPin 20

void printDivider(void);

DHT dht(DHTPIN,DHTTYPE);

void setup() {
  // put your setup code here, to run once:
//  pinMode(keyPin, OUTPUT);
//  digitalWrite(keyPin, HIGH);
  Serial.begin(9600);
  pinMode(DHTPIN, INPUT);
  dht.begin();
  pinMode(LedPin, OUTPUT);
  Serial.print("Let's goowww...");
  Serial1.begin(9600);
  Serial1.print("Receiving data from Humidity Sensor...\n");

}

void loop() {
//   put your main code here, to run repeatedly:
  delay(2000);
  float humidity=dht.readHumidity(), tempInCelsius=dht.readTemperature(), tempInFarenheit=dht.readTemperature(true);
  if(isnan(humidity) || isnan(tempInCelsius) || isnan(tempInFarenheit)){
    Serial.println("Could not connect to the DHT11 sensor module, make sure it is connected...");
    return; //Exit the program on error
  }
  digitalWrite(LedPin,HIGH);
//  delay(0);
  /**
   * Playing around with converting floats to strings
   * Apparently, floats cannot be formatted using sprintf straight away!
   * Arduino expects the type to be a double for %f!!
  */
  char s_humidity[6], s_tempInC[6], s_tempInF[6], heatIndexCelsius[6], heatIndexFarenheit[6];
  dtostrf(humidity, 4, 2, s_humidity);
  dtostrf(tempInCelsius, 4, 2, s_tempInC);
  dtostrf(tempInFarenheit,  4, 2, s_tempInF);
  dtostrf(dht.computeHeatIndex(tempInCelsius, humidity, false), 4, 2, heatIndexCelsius);
  dtostrf(dht.computeHeatIndex(tempInFarenheit, humidity), 4, 2, heatIndexFarenheit);
  printDivider();
  char outputBuffer[200];
  char rpiResponse[200];
  sprintf(outputBuffer, "\nHeat index: %s°C / %s°F \nHumidity: %s \nTemp: %s°C / %s°F\n", heatIndexCelsius, heatIndexFarenheit, s_humidity, s_tempInC, s_tempInF);
  Serial.println(outputBuffer);
//  Serial1.write(outputBuffer);
  int soilReading=analogRead(soilPin);
  char soilRead[120];
  sprintf(soilRead, "Soil Reading: %d\n", soilReading);
  Serial.println(soilRead);

  /**
   * Prepare and send the readings repsone to Rpi.
   * Rpi should be able to serialize this data into usable format.
   */
  sprintf(rpiResponse, "heat_index: %s°C / %s°F | humidity: %s | temperature: %s°C / %s°F | soil_moisture: %d \n", heatIndexCelsius, heatIndexFarenheit, s_humidity, s_tempInC, s_tempInF, soilReading);
  Serial1.write(rpiResponse);
  
  printDivider();
  
  delay(1000);
  digitalWrite(LedPin, LOW);
  if(Serial1.available()){
    /**
     * So that instead of single character being read in each loop() iteration, 
     * read the entire string write it to the Serail until entire string has been written
     * within the current loop()'s iteration
     */
    String buff1=Serial1.readString();
    for(int i=0; i<buff1.length(); i++){
      Serial.write(buff1[i]);
    }
    
  }
  if(Serial.available()){
    String buff2=Serial.readString();
    int l=0;
    while(l<buff2.length()){
      Serial1.write(buff2[l]);
      l++;
    }
  }
}


void printDivider(void){
  for(int i=0; i<30; i++){
    Serial.print("-");  
  }
  Serial.println("");
}
