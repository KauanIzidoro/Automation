int green = 5;
int yellow = 4;
int 
int time_setup = 2000;

void setup(){
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);


}

void loop(){
  default_green(1);
  delay(time_setup + 1000);
  default_green(0);
  delay(1000);
  default_yellow(1);
  delay(time_setup + 1000);
  default_yellow(0);
  delay(time_setup + 1000);
  default_red(1);
  delay(time_setup + 1000);
  default_red(0);

}
 
int default_green(int, satate){

  digitalWrite(green, state);
}
int default_yellow(int state){
  digitalWrite(yellow, state);
}
int default_red(int state){
  digitalWrite(red, state);
}