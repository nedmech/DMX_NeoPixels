/*
 Name:		DMX_NeoPixels.ino
 Created:	12/18/2015
 Author:	Nathan Durnan
*/

#include <DMXSerial.h>
#include <Adafruit_NeoPixel.h>
#include "fixture.h"


#define DMX_ADDRESS 1	// Starting address for DMX Fixture

#define PIN_PIXELS  6
#define NUM_PIXELS 8

fixture myFixture = fixture(DMX_ADDRESS, NUM_PIXELS, PIN_PIXELS, (NEO_RGB + NEO_KHZ800));

/*----------------------------------------
----------------------------------------*/
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	DMXSerial.init(DMXReceiver);
	myFixture.init();

}

/*----------------------------------------
----------------------------------------*/
void loop() {
	unsigned long lastDMXPacket = DMXSerial.noDataSince();
	if (lastDMXPacket < 5000) {
		myFixture.update(&DMXSerial);
	}
	else {
		// revert to a default state
	}


}
