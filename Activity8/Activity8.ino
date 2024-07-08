/*
Jared Barber - Activity 8
-------------------------
Practice using the serial function to set the rate for an LED to blink
*/

#define LED_PIN 12

int delayTime = 300;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  digitalWrite(LED_PIN, HIGH);

  if (Serial.available() > 0){
    int input = Serial.parseInt();
    delayTime = (input >= 100 && input <= 1000)? input : delayTime;

    if (input != delayTime){
      Serial.println("Input must be an integer between 100 and 1000");
    }
  }

  delay(delayTime);
  digitalWrite(LED_PIN, LOW);
  delay(delayTime);
}
