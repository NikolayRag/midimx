/*
MIDI listener board.
Listen incoming events and poke DMX board over i2c

MIDI IN shield tested is Iskra MIDI IN, connected [S -> RX]
*/

//Uncomment to enable Serial.print. Using it can (will) interfere with MIDI over Serial
//#define SPRINT


#include <MIDI.h> //standart MIDI lib, https://github.com/FortySevenEffects/arduino_midi_library

MIDI_CREATE_DEFAULT_INSTANCE();
//MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); //nano pro if used with SPRINT


#include <Wire.h>
#define DMXI2C 0x01



void setup() {
#ifdef SPRINT
  Serial.begin(115200);
#endif
  
  Wire.begin();
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
    if (MIDI.read()) {
        Wire.beginTransmission(DMXI2C);   
        Wire.write("M");   
        Wire.write(MIDI.getChannel());   
        Wire.write(MIDI.getType());   
        Wire.write(MIDI.getData1());   
        Wire.write(MIDI.getData2());              
        Wire.endTransmission();     


#ifdef SPRINT
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
