//Use 485 over Serial by https://github.com/mathertel/DMXSerial
#include <DMXSerial.h>


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
