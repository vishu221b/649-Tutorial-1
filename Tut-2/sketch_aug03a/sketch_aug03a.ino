const int ledPin=11;
const int ledPin2=10;
const int soilPin = 20;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9800);
  digitalWrite(ledPin2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  int soilRead = analogRead(soilPin);
  Serial.println("Soil:" + String(soilRead));
  digitalWrite(ledPin, HIGH);
  delay(1000);
//  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin, LOW);
  delay(1000);

}
