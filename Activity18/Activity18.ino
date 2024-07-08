/*
Jared Barber | Activity 18 | 6/19/24
------------------------------------
Practice using IR remote to control different circuit components and an LCD screen to monitor
outputs. Buttons 1, 2, and 3 should toggle the LEDs on pins 12, 11, and 10 on/off. Button 0
turns off all LEDs, FUNC/STOP clears the LCD display.
*/

#include <IRremote.h>
#include <LiquidCrystal.h>

// define and set up lcd screen
#define LCD_RS A5
#define LCD_E  A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// define and set up IR reciever
#define IR_0 22
#define IR_1 12
#define IR_2 24
#define IR_3 94
#define IR_STOP 71

#define RECV_PIN A3
IRrecv irrecv(RECV_PIN);

byte LEDS[3] = {12, 11, 10};
unsigned long lastInput = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  irrecv.enableIRIn();
}

void loop() {

  if(irrecv.decode()){
    // button bounce - ignore signals due to user or mechanical error
    if (millis()-lastInput < 100)
      return; // continue loop

    irrecv.resume();
    int command = irrecv.decodedIRData.command;

    // print the command received from remote on first line of lcd
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(command);
    lcd.setCursor(0,1);

    // control logic
    switch(command){
      case IR_0:
        lcd.print("Clear all leds");
        clearLEDS();
        break;
      case IR_1:
        lcd.print("Toggle LED");
        toggleLEDS(LEDS[0]);
        break;
      case IR_2:
        lcd.print("Toggle LED");
        toggleLEDS(LEDS[1]);
        break;
      case IR_3:
        lcd.print("Toggle LED");
        toggleLEDS(LEDS[2]);
        break;
      case IR_STOP:
        lcd.clear();
        break;
      default:
        // print an error message
        lcd.print("Not recognized");
    }
  }
}

void clearLEDS(){
  // turn off all leds
  for(byte b : LEDS){
    digitalWrite(b, LOW);
  }
}

void toggleLEDS(int pin){
  // toggle selected led
  byte state = digitalRead(pin);
  digitalWrite(pin, !state);
}