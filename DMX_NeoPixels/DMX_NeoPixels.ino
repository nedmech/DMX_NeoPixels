/*
 Name:		DMX_NeoPixels.ino
 Created:	12/18/2015
 Author:	Nathan Durnan
*/

#include <Conceptinetics.h>
#include <Adafruit_NeoPixel.h>
#include "Fixture.h"


const int StatusPin = LED_BUILTIN;

#define DMX_ADDRESS 33	// Starting address for DMX Fixture

#define PIN_PIXELS 6
#define NUM_PIXELS 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel((2 * NUM_PIXELS), PIN_PIXELS, (NEO_GRB + NEO_KHZ800));

fixture fixture_left  = fixture( 1, NUM_PIXELS);
fixture fixture_right = fixture(33, NUM_PIXELS);
DMX_Slave dmx_slave(64);

/*----------------------------------------
----------------------------------------*/
void setup() {
	pinMode(StatusPin, OUTPUT);
	dmx_slave.setStartAddress(DMX_ADDRESS);
	dmx_slave.enable();
	pixels.begin();
	fixture_left .init();
	fixture_right.init();
}

/*----------------------------------------
----------------------------------------*/
void loop() {
	fixture_left .update(&dmx_slave);
	fixture_right.update(&dmx_slave);
	if (fixture_right.getLevel() > 127) {
		digitalWrite(StatusPin, HIGH);
	}
	else {
		digitalWrite(StatusPin, LOW);
	}
	dmx_slave.disable();
	delay(5);
	fixture_left .updateOutput(&pixels, 0);
	fixture_right.updateOutput(&pixels, 8);
	dmx_slave.enable();
	delay(25);
}
