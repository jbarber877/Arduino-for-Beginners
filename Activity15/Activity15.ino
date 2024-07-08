/*
Jared Barber - Activity 15
--------------------------
Practice using interrupts to measure distances with an ultrasonic sensor. Light up the
corresponding LED based on the distance. If the nearest obstacle is > 100 cm away, blue;
if obstacle is > 15 cm and < 100 cm away, green; if obstacle is < 15 cm away, red.
*/
#define ECHO_PIN 2
#define TRIGGER_PIN 4
#define RED 12
#define GREEN 11
#define BLUE 10

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;
volatile unsigned long pulseBegin, pulseEnd;
volatile bool newDistance = false;

void echoInterrupt(){
  if (digitalRead(ECHO_PIN) == HIGH){
    pulseBegin = micros();
  }
  else {
    pulseEnd = micros();
    newDistance = true;
  }
}

void triggerUltrasonicSensor()
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance()
{
  double durationMicros = pulseEnd - pulseBegin;
  double distance = durationMicros / 58.0; // cm (148.0: inches)
  return distance;
}

void setup() {
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoInterrupt, CHANGE);
}

void loop() {
  unsigned long timeNow = millis();
  
  if (timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay) {
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
  }

  if (newDistance){
    newDistance = false;
    double distance = getUltrasonicDistance();
    Serial.println(distance);

    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);

    if (distance > 100){
      digitalWrite(BLUE, HIGH);
    }
    else if (distance > 15){
      digitalWrite(GREEN, HIGH);
      }
    else{
        digitalWrite(RED, HIGH);
    }

  }
}
