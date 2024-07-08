/*
Jared Barber  | Interactive Obstacle Detection  | July 2024
------------------------------------------------------------
https://www.tinkercad.com/things/350uarEVLZG-interactive-obstacle-detection
*/

#include<LiquidCrystal.h>
#include<IRremote.h>
#include<EEPROM.h>

// Ultrasonic Sensor
#define ECHO 7
#define TRIG 6

// LCD Screen
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

// IR REMOTE
#define RECV_PIN A5
#define FUNC 2 // FUNC/STOP irrecv.decodedIRData.command 
IRrecv irrecv(RECV_PIN);

// LEDS
#define RED 12
#define GREEN 11
#define YELLOW 10

#define BUTTON A2

// EEPROM
#define EEPROM_ADDR 50

// Global variables
unsigned long lastTrigger = millis();
unsigned long lastReading = millis();
unsigned long triggerDelay = 60;
unsigned long distance = 10;

int luminosity = 100;
unsigned int lcdDisplay = 1;

byte units = 0;


void setup()
{
 // Serial Monitor
 Serial.begin(9600);
  
 // Ultrasonic Sensor
 pinMode(ECHO, INPUT);
 pinMode(TRIG, OUTPUT);
  
 // LCD Screen
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("Starting...");
  
 // IR Sensor
 irrecv.enableIRIn();
 
 // Button
 pinMode(BUTTON, INPUT);
  
 //EEPROM
  if(EEPROM.read(EEPROM_ADDR)> 1){
   EEPROM.write(EEPROM_ADDR, 0);
  }
  else{
    units = EEPROM.read(EEPROM_ADDR);
  } 
}


void loop()
{  
 // current time
 unsigned long timeNow = millis();

 // trigger the sensor every 100 ms
 if (timeNow - lastTrigger > triggerDelay){
   triggerUltrasonicSensor();
   distance = getUltrasonicDistance();
   lastTrigger = timeNow;
   //Serial.println(distance);
  }
  
  // if sensor detects an object < 10 cm away, lock the application
  if (distance < 10){
    lock();
  }
  
  // listen for remote event  
  if(irrecv.decode()){
   irrecv.resume();
   remoteEvent(irrecv.decodedIRData.command);
  }
  
  // display message on lcd screen
  printToLCD(lcdDisplay);
  
  // If application is not locked, LED 1 is off
  digitalWrite(12, LOW);
  
  // If application is not locked, LED 2 blinks proportionally to 
  // the distance read by sensor
  blinkLED(GREEN, distance);
  
  // If application is not locked, LED 3 brightness is inversely proportional
  // to the ambient light in the room (measured every 100 ms)
  if (timeNow - lastReading > 100){
    luminosity = analogRead(A0);
    analogWrite(YELLOW, 255-(analogRead(A0)/4));
  } 
}

void lock(){
  // print an error message to LCD screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ERROR! OBSTACLE");
  lcd.setCursor(0,1);
  lcd.print("TOO CLOSE!");
  
  // the application is locked until user acknowledges error
  while (true){    
    blinkLED(RED, 300);
    blinkLED(GREEN, 300);

    // if user presses play, they acknowledge error and app is reset
     if(irrecv.decode()){
     	irrecv.resume();
       if(irrecv.decodedIRData.command == 5){
         return; //break;
       }
     }
    
    // if user hits the button, they acknowledge error and app is reset 
    int state = digitalRead(BUTTON);
  	if (state == HIGH){
    	return;
    }  
  }
}

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

void blinkLED(int pin, int time){
  // blink an LED for a given amount of time
  digitalWrite(pin, HIGH);
  delay(time);
  digitalWrite(pin, LOW);
  delay(time);
}

void remoteEvent(int action){
  // controller responds to signal from remote controller
  
    if(action == 8){
      // if up arrow, toggle lcd display
      lcdDisplay++;
    }
    if(action == 10){
      // if down arrow, toggle lcd display
      lcdDisplay--;
    }
    if(action == 0){
      // if off btn, reset all settings
      lcdDisplay = 1;
      units = EEPROM.read(EEPROM_ADDR);
    }
    if (action == 13){
      // if EQ, change units from cm to inches or vice versa
      units = (units + 1) % 2;
      EEPROM.write(EEPROM_ADDR, units);                 
    }  
}

void printToLCD(int option){
  // print a message to lcd screen based on user choice
  
  lcd.clear();
  lcd.setCursor(0,0);
  
  // Option 1 - print distance from sensor. Print a warning if < 50 cm
  if(option % 2 == 1){
    
    
    if(units == 0){
      // units == 0 signifies centimeters
      lcd.print(distance);
      lcd.print(" cm"); 
    }
    if(units == 1){
      // units == 1 signifies inches
      lcd.print((distance/2.54));
      lcd.print(" in"); 
    }   
        
    if (distance < 50){
      lcd.setCursor(0,1);
      lcd.print("Object Incoming");
    }
  }
  
  // Option 2 - print luminosity
  else {
    lcd.print("luminosity ");
    lcd.print(luminosity);
  } 
}

