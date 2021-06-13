/*
DMX board.
Map incoming data over i2c to DMX

Shield used is Iskra RS485, connected to:
    RO -> TX
    ^v (dir) -> Gnd (low to transmit)
    DI -> --

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

int dmxV = 0;

void setup() {
  DMXSerial.init(DMXController);

  DMXSerial.write(devMode, 0);
  DMXSerial.write(devLamp, 255);
}


void loop() {
  DMXSerial.write(devRed, 127);
  DMXSerial.write(devGreen, dmxV%256);
  DMXSerial.write(devBlue, 255-(dmxV%256) );
  DMXSerial.write(devWhite, 0);

  dmxV++;
  
  delay(5);
}
