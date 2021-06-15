/*
DMX board.
Map incoming data over i2c to DMX

Shield used is Iskra RS485, connected to:
    DI -> TX
    ^v (dir) -> +5 (high to transmit)
    RO -> --

    out A -> XLR 3
    out B -> XLR 2
    out G -> XLR 1
*/

#include <Wire.h>


void i2cRequestCB() {
  Serial.print("req\n");
//  Wire.write(); //template memo
}


void i2cRecieveCB(int bytes) {
  Serial.print("in ");
  while (Wire.available()) {
    byte c = Wire.read();
    Serial.print(c);
    Serial.print(',');
  }
  Serial.print("\n");
}


void setup() {
  Serial.begin(115200);

  
  Wire.begin(0x01);
  Wire.onReceive(i2cRecieveCB);
  Wire.onRequest(i2cRequestCB);

  Serial.print("Init\n");
}


void loop() {
}
