/* LoRaWAN Class A Hello World example
 *
 * Sends a message every 30 seconds
 *
 * This example code will just test the LoRaWAN stack STM32 using STM32LoRaWAN
 */
#include <Arduino.h>
#include <STM32RTC.h>
#include <STM32LoRaWAN.h>
#include "HardwareSerial.h"
#include "HBridge.h"
HardwareSerial mySerial {PB7, PB6};

// Set up the H-Bridge
HBridge valve(PB10, PA9);
// LED is on PB5
#define LED_BUILTIN PB5
int valve_state = 0; // this is the state of the valve for now (0 = closed, 1 = open)


STM32LoRaWAN modem; // get ready to set up the modem

//#include "arduino_secrets.h"
// Please enter your sensitive data in the Secret tab or arduino_secrets.h



// LoRa OTAA Join Function
int joinOTAA() {
	if !modem.begin(US915) {
		mySerial.println("Failed to start module");
		return -1;
	}
	mySerial.print("Your device EUI is: ");
	mySerial.println(modem.deviceEUI());
	String appEui = "DEADBEEFDEADBEEF";
	String appKey = "BEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEF";
	int connected;
	appKey.trim();
	appEui.trim();
	connected = modem.joinOTAA(appEui, appKey);
	return connected;
}

// LoRa Send Message to Server
int sendMessage(String message) {
	modem.beginPacket();
	modem.write((uint8_t*)message.c_str(), message.length());
	int err = modem.endPacket(true); // true for confirmed packet
	if (err > 0) {
		mySerial.println("Message sent correctly!");
	} else {
		mySerial.println("Error sending message :(");
	}
	return err;
}

// Send a status message as a byte array - this should ideally be something per the Cayenne LPP format
int sendStatus(uint8_t* status, int length) {
	modem.beginPacket();
	modem.write(status, length);
	int err = modem.endPacket(true); // true for confirmed packet
	if (err > 0) {
		mySerial.println("Message sent correctly!");
	} else {
		mySerial.println("Error sending message :(");
	}
	return err;
}


void control_valve(bool state) {
	valve.actuate(state, 100); // 0 is closed, 1 is open per HBridge.cpp implementation
	digitalWrite(LED_BUILTIN, !state); // LED is active low!
	// wait before turning off current to the valve
	delay(5000);
	valve.actuate(state, 0); // same state, but 0% speed == latch it!
}


// Blinky LED for now
//#define LED_BUILTIN PB5
void setup() {

	// put your setup code here, to run once:
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	// make sure the valve is closed
	valve.actuate(0, 0);

	mySerial.begin(115200);

	while (!mySerial);

	// change this to your regional band (eg. US915, AS923, ...)

	// Set up the modem
	int connected =	joinOTAA();
	if (!connected) {

		mySerial.println("Uh-Oh, Connection failed. Check your keys and distance!");

		while (1) {}

	}

	mySerial.println("You're connected to the network");
	String message = "Hello World";
	sendMessage(message);
}

void loop() {
	// Set the builtin LED to the valve state
	control_valve(valve_state);

	sendMessage()

//
//	// Send "open" if the valve state is 1 and "closed" if the valve state is 0
//	String message = valve_state == 1 ? "open" : "closed";
//	modem.beginPacket();
//	modem.write((uint8_t*)message.c_str(), message.length());
//	int err = modem.endPacket(true); // true for confirmed packet
//
//	if (err > 0) {
//		mySerial.println("Message sent correctly!");
//	} else {
//		mySerial.println("Error sending message :(");
//	}
//
//	// Read a packet
//	int packetSize = modem.parsePacket();
//	// If there is a packet, read it
//	if (packetSize) {
//		mySerial.print("Received packet: ");
//		// Read the packet into a buffer
//		uint8_t  pkt[packetSize];
//		modem.read(pkt, packetSize);
//		// Convert to char array
//		char packet[packetSize];
//		for (int i = 0; i < packetSize; i++) {
//			packet[i] = (char)pkt[i];
//		}
//		// Print the packet
//		mySerial.println(packet);
//		// check the first part for "open" or "closed"
//		if (strncmp(packet, "open", 4) == 0) {
//			valve_state = 1;
//		} else if (strncmp(packet, "closed", 6) == 0) {
//			valve_state = 0;
//		}
//
//	}

	// Wait 10 seconds
	delay(1000);
	valve_state = !valve_state;
}