void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Begun main serial!");
  Serial1.begin(9600);
  Serial1.println("Beginning Serial1...!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    // while(Serial.read()){
      Serial1.write(Serial.read());
    // }
  }
  if (Serial1.available()){
    // while(Serial1.read()){
     Serial.write(Serial1.read());
    // }
  }
}
