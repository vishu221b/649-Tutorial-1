/**
 * This program blinks the Teensy led on each serial print of the humidity and the temperature readings
*/

#include "DHT.h"

#define DHTPIN 21 // Teensy 2.0 uses digital pin 21 for DHT sensor module

#define DHTTYPE DHT11 // DHTType is 11 for Teensy 2.0

#define LedPin 11 // LED PIN is 11 for Teensy 2.0

DHT dht(DHTPIN, DHTTYPE);

void printDivider(void);

void setup() {
  Serial.begin(9600);
  pinMode(DHTPIN, INPUT);
  dht.begin();
  pinMode(LedPin, OUTPUT);
}

void loop() {
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
  sprintf(outputBuffer, "Heat index: %s°C / %s°F \nHumidity: %s \nTemp: %s°C / %s°F", heatIndexCelsius, heatIndexFarenheit, s_humidity, s_tempInC, s_tempInF);
  Serial.println(outputBuffer);
  printDivider();
  delay(1000);
  digitalWrite(LedPin, LOW);
}

void printDivider(void){
  for(int i=0; i<30; i++){
    Serial.print("-");  
  }
  Serial.println("");
}
