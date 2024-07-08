/*
Improve the previous project using functions and arrays to toggle LEDs on/off using a button
*/

#define SIZE 3
#define LED_1_PIN 12 
#define LED_2_PIN 11 
#define LED_3_PIN 10 
#define BUTTON_PIN 2 

byte LED_ARRAY[SIZE] = {LED_1_PIN, LED_2_PIN, LED_3_PIN};

int LEDBlinkState = 1;

void setup() {
  pinMode(BUTTON_PIN, INPUT);

  for (auto LED : LED_ARRAY) {
    pinMode(LED, OUTPUT);
  }

  for (auto LED : LED_ARRAY) {
    digitalWrite(LED, LOW);
  }
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    LEDBlinkState = toggleLEDS(LED_ARRAY, LEDBlinkState);
    delay(300);
  }
}

int toggleLEDS(byte LEDs[], int state) {
  if (state == 1){
    digitalWrite(LED_1_PIN, HIGH);
    digitalWrite(LED_2_PIN, LOW);
    digitalWrite(LED_3_PIN, HIGH);
    return 2;
  }
  else {
    digitalWrite(LED_1_PIN, LOW);
    digitalWrite(LED_2_PIN, HIGH);
    digitalWrite(LED_3_PIN, LOW);
    return 1;
  }
}

