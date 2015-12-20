/*
	Name:		Fixture.cpp
	Created:	12/18/2015
	Author:		Nathan Durnan
*/

#include "Fixture.h"

/*----------------------------------------
Constructor - assign:
* a = DMX Address
* n = Number of Pixels
* p = NeoPixel output pin
* t = NeoPixel configuration type
----------------------------------------*/
fixture::fixture(uint16_t a, uint16_t n) {
	_address = a;
	_channels = n;
	_channel = (fixtureChannelStruct*)malloc(_channels * sizeof(fixtureChannelStruct));
}

/*----------------------------------------
Destructor - free memory allocations
----------------------------------------*/
fixture::~fixture() {
	free(_channel);
	_channel = NULL;
}


/*----------------------------------------
Initialize the object
----------------------------------------*/
void fixture::init(void) {
	_level = DMX_OFF;
	_strobe = DMX_OFF;
	for (uint16_t i = 0; i < _channels; i++) {
		_channel[i].init();
	}
	return;
}


/*----------------------------------------
Read new values from specified DMX source
----------------------------------------*/
void fixture::update(DMX_Slave* myDMX) {
	_level = myDMX->getChannelValue(_address);
	for (uint16_t i = 0; i < _channels; i++) {
		uint16_t chOffset = _address + (i * 3);
		_channel[i].r = myDMX->getChannelValue(chOffset + 1);
		_channel[i].g = myDMX->getChannelValue(chOffset + 2);
		_channel[i].b = myDMX->getChannelValue(chOffset + 3);
	}
	_strobe = myDMX->getChannelValue(_address + (_channels * 3) + 1);
}


/*----------------------------------------
Update the NeoPixel output values
----------------------------------------*/
void fixture::updateOutput(Adafruit_NeoPixel* myPixels, uint8_t startPixel) {
	for (uint16_t i = 0; i < _channels; i++){
		myPixels->setPixelColor((i + startPixel)
			, uint8_t((double)_channel[i].r * ((double)_level / 255.0))
			, uint8_t((double)_channel[i].g * ((double)_level / 255.0))
			, uint8_t((double)_channel[i].b * ((double)_level / 255.0))
			);
	}
	myPixels->show();
	return;
}

uint16_t fixture::getLevel(void) {
	return(_level);
}

