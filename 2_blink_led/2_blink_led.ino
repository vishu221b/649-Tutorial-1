#define ledpin 10 // default led pin for teensy 2.0

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
    char *_final;
    if(i == 0){
      _final="st";
    }else if(i==1){
      _final="nd";
    }else if(i==2){
      _final="rd";
    }else{
      _final="th";
    }
    Serial.printf("Executing %i%s blink...\n", i+1, _final);
    blinkLed(_delay);
  }
}

void blinkLed(long _delay){
  digitalWrite(ledpin, HIGH);
  delay(_delay);
  digitalWrite(ledpin, LOW);
  delay(_delay);
}
