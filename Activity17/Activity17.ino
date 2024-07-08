/*
Jared Barber | Activity 17 | 6/17/2024
---------------------------------------
Practice using an ultrasonic sensor and LCD. Print the distance from an obstacle in front of the sensor to the LCD.

TODO: the code runs, but it is very slow. Is this just because of the print functionality, or can performance be improved?
*/


#include <LiquidCrystal.h>

#define ECHO_PIN 2
#define TRIGGER_PIN 4

#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9

unsigned long lastTimeUltrasonicTrigger = 0;
unsigned long ultrasonicTriggerDelay = 100;
volatile unsigned long pulseBegin = 0, pulseEnd = 0;
volatile bool newDistance = false;

double currentDistance = 0;

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN,
                  LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

void echoInterrupt() {
  if (digitalRead(ECHO_PIN) == HIGH) {
    pulseBegin = micros();
  } else {
    pulseEnd = micros();
    newDistance = true;
  }
}

void triggerUltrasonicSensor() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);  // Corrected to 10 microseconds
  digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance() {
  double durationMicros = pulseEnd - pulseBegin;
  if (durationMicros < 0) { // Check for negative values
    durationMicros = 0;
  }
  double distance = durationMicros / 58.0; 
  return distance;
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16,2);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoInterrupt, CHANGE);
}

void loop() {
  unsigned long timeNow = millis();
  
  if (timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay) {
    lastTimeUltrasonicTrigger = timeNow;  // Update with the current time
    triggerUltrasonicSensor();
  }

  if (newDistance) {
    newDistance = false;
    double distance = getUltrasonicDistance();
    if (distance > 2 & distance < 400){
      currentDistance = distance;
    }

    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print(currentDistance);
    //delay(500);
  }
}
