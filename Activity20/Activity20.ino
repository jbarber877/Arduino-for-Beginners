/*
Jared Barber | Activity 20
--------------------------
Compute the average brightness in the area over a period of time (5 seconds).
Compute the average using an array, NOT a running sum.
*/

#define PHOTO_RESISTOR A0
using namespace std;

unsigned int samples[100];
unsigned int counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (counter < 100){
    // sample the brightness in the environment every 50 ms
    samples[counter++] = analogRead(PHOTO_RESISTOR);
    delay(50);    
  }
  counter = 0;

  for(int i: samples)
    counter+= i;
  
  // print the average
  Serial.println(counter/100);
  counter = 0;
}
