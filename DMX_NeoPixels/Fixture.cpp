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
fixture::fixture(uint16_t n, uint8_t p, neoPixelType t){
  _address = 1;
  _channels = n;
	_channel = (fixtureChannelStruct*)malloc(_channels * sizeof(fixtureChannelStruct));
	_pixels.updateLength(n);
	_pixels.setPin(p);
	_pixels.updateType(t);
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
	_pixels.begin();
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
void fixture::updateOutput(void) {
	for (uint16_t i = 0; i < _channels; i++){
		_pixels.setPixelColor(i, _channel[i].r, _channel[i].g, _channel[i].b);
		_pixels.setBrightness(_level);
		_pixels.show();
	}
	return;
}

uint16_t fixture::getLevel(void) {
  return(_level);
}

