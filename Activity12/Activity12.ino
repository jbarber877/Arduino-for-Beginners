/*
Jared Barber - Activity 12
--------------------------
Practice using interrupts by counting the number of times a button is pressed and printing to the console
*/

#define BUTTON 2

volatile bool flag = false;
int counter = 0;

void buttonInterrupt (){
  flag = true;
}

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonInterrupt, RISING);
}

void loop() {
  if (flag == true){
    Serial.println(++counter);
    flag = false;
  }

}
