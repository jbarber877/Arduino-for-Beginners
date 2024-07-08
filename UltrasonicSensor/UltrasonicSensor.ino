#define ECHO 11
#define TRIG 4

unsigned long lastTrigger = millis();
unsigned long triggerDelay = 50;
unsigned long distance = 10;

void triggerUltrasonicSensor()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
}

double getUltrasonicDistance()
{
  double durationMicros = pulseIn(ECHO, HIGH);
  double distance = durationMicros / 58.0;
  return distance;
}

void lock(){

}

void setup()
{
  Serial.begin(115200);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

  Serial.println("NEW ATTEMPT");
}

void loop()
{
  unsigned long timeNow = millis();

  if (timeNow - lastTrigger > triggerDelay){
    triggerUltrasonicSensor();
    distance = getUltrasonicDistance();



    Serial.println(distance);
  }
}





