/*
Use a photoresistor to control an LED
*/

#define PHOTO_RESISTOR A0
#define LED1 12
#define LED2 10

int threshold = 255; // 25% of max luminosity
int luminosity = 1024;

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  // read photoresistor value
  luminosity = analogRead(PHOTO_RESISTOR);
  // if light in the environment falls below threshold, turn LED1 on
  digitalWrite(LED1, (luminosity < threshold));
  // light LED2 proportional to the light in the environment
  analogWrite(LED2, (255-(luminosity/2)));
}
