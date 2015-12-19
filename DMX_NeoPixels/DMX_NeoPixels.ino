/*
 Name:		DMX_NeoPixels.ino
 Created:	12/18/2015
 Author:	Nathan Durnan
*/

#include <Conceptinetics.h>
#include <Adafruit_NeoPixel.h>
#include "fixture.h"


const int StatusPin = 13;

#define DMX_ADDRESS 1	// Starting address for DMX Fixture

#define PIN_PIXELS  6
#define NUM_PIXELS 8

DMX_Slave dmx_slave ((NUM_PIXELS * 3)+2);

fixture myFixture = fixture(NUM_PIXELS, PIN_PIXELS, (NEO_GRB + NEO_KHZ800));

/*----------------------------------------
----------------------------------------*/
void setup() {
  pinMode(StatusPin, OUTPUT);
  dmx_slave.enable();
  dmx_slave.setStartAddress(DMX_ADDRESS);
	myFixture.init();

}

/*----------------------------------------
----------------------------------------*/
void loop() {
	myFixture.update(&dmx_slave);
  if (myFixture.getLevel() > 127) {
    digitalWrite(StatusPin, HIGH);
  }
  else {
    digitalWrite(StatusPin, LOW);
  }
  dmx_slave.disable();
  delay(5);
  myFixture.updateOutput();
  dmx_slave.enable();
  delay(25);
}
