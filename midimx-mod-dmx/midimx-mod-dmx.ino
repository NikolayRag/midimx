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
//Uncomment to enable Serial.print. Using it can interfere with 485 over Serial
//#define SPRINT


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
#ifdef SPRINT
  Serial.print("req\n");
#endif

//  Wire.write(); //template memo
}


void i2cRecieveCB(int bytes) {
#ifdef SPRINT
  Serial.print("in ");
#endif

#define IN_MARKER 0
#define IN_CHANNEL 1
#define IN_TYPE 2
#define IN_BYTE1 3
#define IN_BYTE2 4
#define IN_MAX_LEN 5
  byte i2cIn[IN_MAX_LEN];
  int i = 0;
  while (Wire.available()) {
    byte v = Wire.read();
#ifdef SPRINT
    Serial.print(v);
    Serial.print(',');
#endif

    if (i >= IN_MAX_LEN)
      continue;
    i2cIn[i++] = v;
  }
#ifdef SPRINT
  Serial.print("\n");
#endif

  if (i2cIn[IN_MARKER] != 77)
    return;

  if (
    (i2cIn[IN_CHANNEL] !=1)
    || (i2cIn[IN_TYPE] !=176)
  )
    return;
    
  if (i2cIn[IN_BYTE1] == 0)
    DMXSerial.write(devRed, i2cIn[IN_BYTE2]*2);
  if (i2cIn[IN_BYTE1] == 1)
    DMXSerial.write(devGreen, i2cIn[IN_BYTE2]*2);
  if (i2cIn[IN_BYTE1] == 2)
    DMXSerial.write(devBlue, i2cIn[IN_BYTE2]*2);

  DMXSerial.write(devWhite, 0);
  DMXSerial.write(devLamp, 255);
}


void setup() {
#ifdef SPRINT
  Serial.begin(115200);
#endif
  
  Wire.begin(0x01);
  Wire.onReceive(i2cRecieveCB);
  Wire.onRequest(i2cRequestCB);


  DMXSerial.init(DMXController);

  DMXSerial.write(devMode, 0);


#ifdef SPRINT
  Serial.print("Init\n");
#endif
}


void loop() {
}
