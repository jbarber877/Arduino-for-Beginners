/*
Jared Barber  - Asignment 11
-----------------------------
Address the 'button bounce' problem by setting a time delay when the button is pressed.
If the button is pressed, toggle LED2 and LED3 on/off. Also, blink LED1 every 1 second.

https://www.tinkercad.com/things/hbDDxiNG6cK-button-bounce
*/

#define LED1 12
#define LED2 11
#define LED3 10
#define BUTTON 2

unsigned long lastButtonPress = millis();
unsigned long lastBlink = millis();
int buttonDelay = 50;
int buttonState = 0;
int led1State = LOW;
int led2State = LOW;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  // if button pressed, toggle LED2 and LED3  
  unsigned long timeNow = millis();
  if (timeNow - lastButtonPress > buttonDelay){
    int newButtonState = digitalRead(BUTTON);
    if (newButtonState != buttonState){
      led2State = (led2State == HIGH)? LOW : HIGH;
      lastButtonPress = timeNow;
    }
  }

  digitalWrite(LED2, led2State);
  digitalWrite(LED3, !led2State);

  
  // make LED1 blink every 1 second
  if (millis() - lastBlink > 1000){
    led1State = (led1State == LOW)? HIGH : LOW;
    lastBlink += 1000;
  }

  digitalWrite(LED1, led1State);

}
