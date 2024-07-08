/*
Jared Barber  - Activity 15
---------------------------
Practice using the LCD to read from Serial Monitor and print to the LCD screen.
Printing should alternate between top and bottom rows.
Input should not be more than 16 characters long.
*/

#include <LiquidCrystal.h>

#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9

int counter = -1;

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN,
                  LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

void setup(){
  lcd.begin(16,2);
  lcd.print("Hello World!");
  Serial.begin(115200);
}

void loop(){
if (Serial.available()){
  String input = Serial.readStringUntil('\n');
  if (input.length()<=16){
    counter++;
    lcd.clear();
    lcd.setCursor(0, (counter)%2);
    lcd.print(input);
  }
  else{
    Serial.println("Input must be <= 16 characters long");
  }
}

}