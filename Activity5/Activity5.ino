/*
Jared Barber  Activity 5
------------------------
Use a button to toggle LEDs on and off. If the button is on, the yellow led is on. 
Else, red and green LED are on.
*/

#define RED_LED 12
#define YELLOW_LED 11
#define GREEN_LED 10
#define BUTTON 2

int LEDBlinkState = 1;

void setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop()
{
  if (digitalRead(BUTTON) == LOW)
  {
    if (LEDBlinkState == 1)
    {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      LEDBlinkState = 2;
    }
    else
    {
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      LEDBlinkState = 1;
    }
    delay(300);



}