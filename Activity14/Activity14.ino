/*
Use an ultrasonic sensor to measure distance to an object
*/

#define ECHO_PIN 2
#define TRIGGER_PIN 12

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;

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
  unsigned long timeBegin = micros();
  double durationMicros = pulseIn(ECHO_PIN, HIGH, 2500000);
  unsigned long timeEnd = micros();
  unsigned long codeDuration = timeEnd - timeBegin;
  Serial.print("Duration :");
  Serial.println(codeDuration);
  double distance = durationMicros / 58.0; // cm (148.0: inches)
  return distance;
}

void setup() {
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);

  Serial.println("NEW ATTEMPT");
}

void loop() {
  unsigned long timeNow = millis();
  
  if (timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay) {
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
    Serial.println(getUltrasonicDistance());
  }
}
