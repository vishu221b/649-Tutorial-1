#include "DHT.h"

#define DHTPIN 21
#define DHTTYPE DHT11
#define ledPin 11

DHT dht(DHTPIN, DHTTYPE);

unsigned long _timestamp=1000;

void readDHTData();

void setup() {
  // Start Serial for Teensy 2.0
  Serial.begin(9600);
  Serial.println("Beginning Serial at " + String(_timestamp) + "...");
  delay(2000);
  pinMode(DHTPIN, INPUT);
  dht.begin();
  pinMode(ledPin, OUTPUT);

  // Start Serial for Bluetooth
  Serial1.begin(9600);
  Serial1.println("Beginning Serial1...");
}


unsigned long current_timestamp=0l;

void loop() {
  if(Serial1.available() > 0){
    processControllerCommands(Serial1.readString());
  }
  if(Serial.available() > 0){
    Serial1.write(Serial.read());
  }
  current_timestamp=millis();
  /**
  * Capturing sensor data every 2 seconds
  */
  if((current_timestamp/1000 - _timestamp/1000) > 2){
    readDHTData();
    _timestamp=current_timestamp;
    delay(1000);
  }
}

void readDHTData(){
  float humidity=dht.readHumidity(), tempInC=dht.readTemperature(), tempInF=dht.readTemperature(true);
  char dataMessage[256];
  if(isnan(humidity) || isnan(tempInC) || isnan(tempInF)){
    sprintf(dataMessage, "Unable to read data from DHT sensor, please check the connection and try again!");
    Serial1.write(dataMessage);
    Serial.write(dataMessage);
  }else{
    float heatIndexInC=dht.computeHeatIndex(tempInC, humidity, false);
    float heatIndexInF=dht.computeHeatIndex(tempInF, humidity, true);

    /**
    * Create char to store the conversions from float
    */
    char sHumidity[6], sTempInC[6], sTempInF[6], sHeatIndexC[6], sHeatIndexF[6];
    dtostrf(humidity, 4, 2, sHumidity); 
    dtostrf(tempInC, 4, 2, sTempInC); 
    dtostrf(tempInF, 4, 2, sTempInF); 
    dtostrf(heatIndexInC, 4, 2, sHeatIndexC); 
    dtostrf(heatIndexInF, 4, 2, sHeatIndexF);

    /**
    * Write data to the message buffer
    */ 
    sprintf(dataMessage, "{'Humidity': '%s','Temperature': '%s℃/%s℉','Heat Index': '%s℃/%s℉'}\n", sHumidity, sTempInC, sTempInF, sHeatIndexC, sHeatIndexF);
    Serial1.write(dataMessage);
    Serial.write(dataMessage);
  }
}

void processControllerCommands(String command){
  if(command.startsWith("C_")){
    Serial.println("Processing command: " + command);
    if(command.substring(2) == "LED_ON"){
      digitalWrite(ledPin, HIGH);
    }
    if(command.substring(2) == "LED_OFF"){
      digitalWrite(ledPin, LOW);
    }
  }else{
    Serial.println(command);
  }
}
