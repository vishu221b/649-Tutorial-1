#define keyPin 9

void setup() {
  // put your setup code here, to run once:
//  pinMode(keyPin, OUTPUT);
//  digitalWrite(keyPin, HIGH);
  Serial.begin(9600);
  Serial.print("Enter AT Commands:");
//  Serial1.begin(38400);
  Serial1.begin(9600);
//  Serial1.print("Enter AT Commands:");

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()){
    Serial.write(Serial1.read());
  }
  if(Serial.available()){
    Serial1.write(Serial.read());
  }
}
