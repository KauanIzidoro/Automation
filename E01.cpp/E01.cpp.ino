int led = 4;
int bt = 6;

void setup() {

  pinMode(led, OUTPUT);
  pinMode(bt, INPUT);

  
}

void loop() {

  if(digitalRead(bt) == HIGH){
    digitalWrite(led, HIGH);
  }else {
    digitalWrite(led, LOW);
  }

  
  
}
