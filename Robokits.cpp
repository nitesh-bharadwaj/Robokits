#include "Robokits.h"

Robokits :: Robokits(int pwPin, int direcPin, int brkPin) {
  pwmPin = pwPin;
	directionPin = direcPin;
	pinMode(pwmPin,OUTPUT);
	pinMode(directionPin,OUTPUT);
	pinMode(brkPin,OUTPUT);
	digitalWrite(brkPin,LOW);
	prevSpeed = 0;
}
void Robokits :: rampSpeed(int speed) {   //default delay of 3 milliseconds
	rampSpeed(speed,1500);
}
void Robokits :: rampSpeed(int speed,int duration) {	//speed from -255 to 255 and duration in microSeconds and > 480 milliseconds
	Serial.println(prevSpeed);
	int stepSize = duration/(speed-prevSpeed);
	if(speed>240)
	speed=240;
	else if(speed<-240)
	speed=-240;
	int count = 1;
	if (stepSize < 0) {
		stepSize = -stepSize;
	}
	if(speed<0) {                                     // direction Low -ve speed & direction High +ve speed
		speed=-speed;
		if (prevSpeed>0) {
			digitalWrite(directionPin,HIGH);
			for (int i=prevSpeed;i!=0;i--) {
				analogWrite(pwmPin,i);
				Serial.print(i);
				delay(stepSize);
			}
			analogWrite(pwmPin,0);
			prevSpeed = 0;
			Serial.print(0);
			delay(stepSize);
		}
		else if (prevSpeed<0) {
			prevSpeed = -prevSpeed;
		}
		digitalWrite(directionPin,LOW);
		if (speed-prevSpeed < 0) {
			count = -1;
		}
		for (int i=prevSpeed;i!=speed;i=i+count) {
			analogWrite(pwmPin,i);
			Serial.print(i);
			delay(stepSize);
		}
		analogWrite(pwmPin,speed);
		prevSpeed = -speed;
		Serial.println(speed);
	}	
	else if (speed>0) {                                           // direction Low -ve speed & direction High +ve speed
		if (prevSpeed<0) {
			prevSpeed = -prevSpeed;
			digitalWrite(directionPin,LOW);
			for (int i=prevSpeed;i!=0;i--) {
				analogWrite(pwmPin,i);
				Serial.print(i);
				delay(stepSize);
			}
			analogWrite(pwmPin,0);
			Serial.print(0);
			prevSpeed = 0;
			delay(stepSize);
		}
		digitalWrite(directionPin,HIGH);
		if (speed-prevSpeed < 0) {
			count = -1;
		}
		for (int i=prevSpeed;i!=speed;i=i+count) {
			analogWrite(pwmPin,i);
			Serial.print(i);
			delay(stepSize);
		}
		analogWrite(pwmPin,speed);
		Serial.println(speed);
		prevSpeed = speed;
	}
	else  {
		if (prevSpeed>0) {
			digitalWrite(directionPin,HIGH);
			for (int i=prevSpeed;i!=0;i--) {
				analogWrite(pwmPin,i);
				Serial.print(i);
				delay(stepSize);
			}
		}
		else if (prevSpeed<0) {
			digitalWrite(directionPin,LOW);	
			prevSpeed = -prevSpeed;
			for (int i=prevSpeed;i!=0;i--) {
				analogWrite(pwmPin,i);
				delay(stepSize);
			}
		}
		analogWrite(pwmPin,0);
		Serial.println(0);
		prevSpeed = 0;
	}
}
	
	
	
void Robokits :: stopini() {   //Use only when initializing
	analogWrite(pwmPin,0);
	prevSpeed = 0;
}
	
