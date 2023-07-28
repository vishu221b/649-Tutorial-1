#define ledpin 11 // default led pin for teensy 2.0

void blinkLed(long _delay);

void setup() {
  pinMode(ledpin, OUTPUT);
}

int _delay=250;

void loop() {
  for(int i=0; i<100;i++){
    if(i > 10 && i < 20){
      _delay=200;
    }else if(i > 95){
      _delay=1500;
    }else if(i > 60){
      _delay=60;
    }else if(i > 40){
      _delay=80;
    }else if(i > 20){
      _delay=100;
    }
    Serial.printf("Executing %i th blink...\n", i);
    blinkLed(_delay);
  }
}

void blinkLed(long _delay){
  digitalWrite(ledpin, HIGH);
  delay(_delay);
  digitalWrite(ledpin, LOW);
  delay(_delay);
}
