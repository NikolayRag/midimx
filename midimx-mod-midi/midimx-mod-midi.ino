/*
MIDI listener board.
Listen incoming events and poke DMX over i2c

MIDI IN shields is Iskra MIDI IN, connected [S -> RX]
*/

//Uncomment to enable Serial.print
//#define PRINT


#include <MIDI.h> //standart MIDI lib, https://github.com/FortySevenEffects/arduino_midi_library

MIDI_CREATE_DEFAULT_INSTANCE();
//MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); //nano pro


#include <Wire.h>



void setup() {
#ifdef PRINT
  Serial.begin(115200);
#endif
  
  Wire.begin();
  
  MIDI.begin();
}

void loop() {
    if (MIDI.read()) {
        Wire.beginTransmission(0x01);   
        Wire.write(MIDI.getData1());   
        Wire.write(MIDI.getData2());              
        Wire.endTransmission();     


#ifdef PRINT
        Serial.print("MIDI: ");
        Serial.print(MIDI.getType());
        Serial.print(", ");
        Serial.print(MIDI.getData1());
        Serial.print(", ");
        Serial.print(MIDI.getData2());
        Serial.print("\n");
#endif
    }
}
