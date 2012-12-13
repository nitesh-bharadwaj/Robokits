#ifndef Robokits_h
#define Robokits_h

#if ARDUINO > 22
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*
Library for Robokits on Arduino Mega2560
Written by GNB

Constructor requires pwmPin and two digital pins

*/

class Robokits
  {
	
	public:
	
	Robokits(int pwPin,int direcPin,int brkPin);
	void rampSpeed(int speed,int duration);
	void rampSpeed(int speed);
	void stopini();
	private:
	
	int prevSpeed;
	int pwmPin;
	int directionPin;
	};

#endif
