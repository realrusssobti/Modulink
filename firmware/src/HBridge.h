//
// Created by Russ Sobti on 5/8/24.
//
#ifndef HBRIDGE_H
#define HBRIDGE_H

enum State {
	OFF = 0,
	ON = 1
};

class HBridge {
public:
	// Constructor
	HBridge(int pin1, int pin2);

	// Method to actuate the H-Bridge
	void actuate(int direction, int percentage);

private:
	int pin1;
	int pin2;
};

#endif // HBRIDGE_H