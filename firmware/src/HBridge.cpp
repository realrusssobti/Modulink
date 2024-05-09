//
// Created by Russ Sobti on 5/8/24.
//

#include "HBridge.h"
#include <Arduino.h>


//Input 1 (IN1 or IN3)
//
//Input 2 (IN2 or IN4)
//
//Spinning Direction
//
//Low//
//Low//
//Motor OFF
//
//High//
//Low//
//Forward
//
//Low//
//High//
//Backward
//
//High//
//High//
//Motor OFF


HBridge::HBridge(int pin1, int pin2) {
	this->pin1 = pin1;
	this->pin2 = pin2;
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
}

void HBridge::actuate(int direction, int percentage) {
	// cast the speed to a value between 0 and 255 (modulo 100 then scale to 255)
	int speed = (percentage % 101) * 255;
	if (direction == 0) {
		analogWrite(pin1, speed);
		analogWrite(pin2, 0);
	} else {
		analogWrite(pin1, 0);
		analogWrite(pin2, speed);
	}
}