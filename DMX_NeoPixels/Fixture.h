/*
	Name:		Fixture.h
	Created:	12/18/2015
	Author:		Nathan Durnan
*/


#ifndef _FIXTURE_h
#define _FIXTURE_h

#include "arduino.h"
#include <Conceptinetics.h>
#include <Adafruit_NeoPixel.h>


/*----------------------------------------
DMX Output values
----------------------------------------*/
enum {
	DMX_ON = 255,
	DMX_OFF = 0
};


/*----------------------------------------
Structure for individual channel/pixel RGB data
----------------------------------------*/
struct fixtureChannelStruct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	void init(void){
		r = DMX_OFF;
		g = DMX_OFF;
		b = DMX_OFF;
		return;
	}
};

/*----------------------------------------
Represents a DMX fixture with multiple RGB channels/pixels
----------------------------------------*/
class fixture
{
private:
	uint16_t _address;
	uint16_t _channels;
	uint8_t _level;
	fixtureChannelStruct* _channel;
	uint8_t _strobe;

public:
	fixture(uint16_t a = 1, uint16_t n = 8);
	~fixture();
	void init(void);
	void update(DMX_Slave* myDMX);
	void updateOutput(Adafruit_NeoPixel* myPixels, uint8_t startPixel);
	uint16_t getLevel(void);
};


#endif

