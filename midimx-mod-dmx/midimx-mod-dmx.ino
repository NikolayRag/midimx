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
#include <DMXSerial.h> //485 over Serial, https://github.com/mathertel/DMXSerial

int devChannel = 1;
int devMode =   devChannel +0;
int devLamp =   devChannel +3;
int devRed =    devChannel +4;
int devGreen =  devChannel +5;
int devBlue =   devChannel +6;
int devWhite =  devChannel +7;



#include <Wire.h>


void i2cRequestCB() {
  Serial.print("req\n");
//  Wire.write(); //template memo
}


void i2cRecieveCB(int bytes) {
  Serial.print("in ");
  byte c;
  while (Wire.available()) {
    c = Wire.read();
    Serial.print(c);
    Serial.print(',');
  }
  Serial.print("\n");


  DMXSerial.write(devRed, c*2);
  DMXSerial.write(devGreen, c*2);
  DMXSerial.write(devBlue, c*2);
  DMXSerial.write(devWhite, 0);
  DMXSerial.write(devLamp, 255);
}


void setup() {
  Serial.begin(115200);

  
  Wire.begin(0x01);
  Wire.onReceive(i2cRecieveCB);
  Wire.onRequest(i2cRequestCB);


  DMXSerial.init(DMXController);

  DMXSerial.write(devMode, 0);


  Serial.print("Init\n");
}


void loop() {
}
