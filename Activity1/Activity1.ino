/*
Jared Barber | Activity 1
-------------------------
Blink an LED on and off

https://www.tinkercad.com/things/iU0CxKjjm1e-activity-1
*/

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  Serial.println("LED ON");
  delay(2000);
  digitalWrite(13, LOW);
  Serial.println("LED OFF");
  delay(1000);
}
