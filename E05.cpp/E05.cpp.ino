int led = 4;
int bt_1 = 6;
bool bt = LOW;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(bt_1, INPUT);
  
}

void loop()
{
  bool bt_state = digitalRead(bt_1);
  
  if(bt_state == HIGH){
    for(int i=0; i<5555;i+=555){
      digitalWrite(led, HIGH);
      delay(1000+i);
      digitalWrite(led, LOW);
      delay(1000+i);
      digitalWrite(led, HIGH);
    
    }
    for(int j=3333; j<100; j-=333){
      digitalWrite(led, HIGH);
      delay(1000+j);
      digitalWrite(led, LOW);
      delay(1000+j);
      digitalWrite(led, HIGH);
    
    }
    
 
  
  }else{
  
  }
  
  
  
  
}