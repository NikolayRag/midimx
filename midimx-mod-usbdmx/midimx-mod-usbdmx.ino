/*
Midimx USBMIDI to DMX playground.


*/



#include "MIDIUSB.h"



#include <DMXSerial.h> //485 over Serial, https://github.com/mathertel/DMXSerial




void setup() {
  DMXSerial.init(DMXController);
}

void loop() {
    midiEventPacket_t rx = MidiUSB.read();

    if (
      (rx.header != 11 )
      || (rx.byte1 !=176) //controller at channel 1
    )
      return;
    
    DMXSerial.write(rx.byte2, rx.byte3 *2);

}
