// #include <IRremote.h>
// #define IR_PIN A3

// void setup() {
//   Serial.begin(9600);
//   IrReciever.begin(IR_PIN);

// }

#include <IRremote.h>

int RECV_PIN = A3;
IRrecv irrecv(RECV_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode()){
    irrecv.resume();
    Serial.println(irrecv.decodedIRData.command);
  }
// if(IrReciever.decode()){
//   IrReciever.resume();
//   Serial.println(IrReciever.decodedIRData.command);


}
