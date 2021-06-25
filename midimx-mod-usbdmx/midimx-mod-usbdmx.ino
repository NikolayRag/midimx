/*
Midimx USBMIDI to DMX playground.


*/



#include "MIDIUSB.h"



#include <DMXSerial.h> //485 over Serial, https://github.com/mathertel/DMXSerial

int devChannel = 1;
int devMode =   devChannel +0;
int devLamp =   devChannel +3;
int devRed =    devChannel +4;
int devGreen =  devChannel +5;
int devBlue =   devChannel +6;
int devWhite =  devChannel +7;



void setup() {
  DMXSerial.init(DMXController);

  DMXSerial.write(devMode, 0);
}

void loop() {
    midiEventPacket_t rx = MidiUSB.read();
    if (rx.header != 0) {

  if (
    (rx.header != 11 )
    || (rx.byte1 !=176) //controller at channel 1
  )
    return;
    
  if (rx.byte2 == 0)
    DMXSerial.write(devRed, rx.byte3 *2);
  if (rx.byte2 == 1)
    DMXSerial.write(devGreen, rx.byte3 *2);
  if (rx.byte2 == 2)
    DMXSerial.write(devBlue, rx.byte3 *2);

  DMXSerial.write(devWhite, 0);
  DMXSerial.write(devLamp, 255);
        
    }
}
