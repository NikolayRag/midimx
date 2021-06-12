#include <MIDI.h> //standart MIDI lib, https://github.com/FortySevenEffects/arduino_midi_library
MIDI_CREATE_DEFAULT_INSTANCE();


void setup() {
  Serial.begin(115200);

  MIDI.begin();

  Serial.print("Init\n");
}

void loop() {
    if (MIDI.read()) {
        Serial.print("MIDI: ");
        Serial.print(MIDI.getType());
        Serial.print(", ");
        Serial.print(MIDI.getData1());
        Serial.print(", ");
        Serial.print(MIDI.getData2());
        Serial.print("\n");
    }
}

/*
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
*/
