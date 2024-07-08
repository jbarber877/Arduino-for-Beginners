#define LED1_PIN 12
#define LED2_PIN 11
#define LED3_PIN 10
#define BUTTON_PIN 2
#define POT A2

int blinkDelay = 500;
int LEDState = LOW;
int lastBlink = millis();

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);


}

void loop() {
  if (Serial.available() > 0) {
    int data = Serial.parseInt();
    if ((data >= 100) && (data <= 4000)) {
      blinkDelay = data;
      Serial.println(blinkDelay);
    }
  }

  if(millis()-lastBlink > blinkDelay){
    if (LEDState == LOW) {
      LEDState = HIGH;
    }
    else {
      LEDState = LOW;
  }
  lastBlink += blinkDelay;
  }

  digitalWrite(LED1_PIN, LEDState);

  // set LED2 from potentiometer
  analogWrite(LED2_PIN, analogRead(A2)/4);

  // power on LED3 when button is pressed
  if (digitalRead(BUTTON_PIN) == HIGH){
    digitalWrite(LED3_PIN, HIGH);
  }
  else {
    digitalWrite(LED3_PIN, LOW);
  }
  
}
