/*
  Arduino For Beginners -2024 Complete Course | Udemy
  https://www.tinkercad.com/things/1JO4wm3F0Pt-push-button

  Power on an LED when the button is pushed
*/

#define LED_PIN 11
#define BUTTON_PIN 2

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }

  Serial.println(digitalRead(BUTTON_PIN));
}
