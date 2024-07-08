/*
Jared Barber | Activity 2
-------------------------
Make an LED fade in and out

https:
*/

#define LED_PIN 11

void setup()
{
  pinMode(12, OUTPUT);
  analogWrite(LED_PIN, 0);
}

int i = 0;
int toggle = 1;

void loop()
{
    analogWrite(LED_PIN, i);
    delay(5);

    if (i == 255){
      toggle = -1;
    }
    if (i == 0){
      toggle = 1;
    }

    i += toggle;

}