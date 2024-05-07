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

HardwareSerial mySerial {PB7, PB6};

STM32LoRaWAN modem; // get ready to set up the modem

//#include "arduino_secrets.h"
// Please enter your sensitive data in the Secret tab or arduino_secrets.h
String appEui = "B1C4E90005012038";
String appKey = "B1C4E90005012038";



// Blinky LED for now
//#define LED_BUILTIN PB5


void setup(void){
	// put your setup code here, to run once:
	mySerial.begin(115200);
	while (!Serial);
	// change this toyour regional band (eg. US915, AS923, ...)
	if (!modem.begin(US915)) {
		mySerial.println("Failed to start module");
		while (1) {}
	};
	mySerial.print("Your module version is: ");
	mySerial.println(modem.version());
	mySerial.print("Your device EUI is: ");
	mySerial.println(modem.deviceEUI());

	int connected = modem.joinOTAA(appEui, appKey);
	if (!connected) {
		mySerial.println("Something went wrong; are you indoor? Move near a window and retry");
		// get the last failure reason
		mySerial.print("Last Error: ");
		mySerial.println(modem.lastFailure);
		// print out the appEui and appKey that was used
		mySerial.print("AppEui: ");
		mySerial.println(appEui);
		mySerial.print("AppKey: ");
		mySerial.println(appKey);
// stay here
//		while (1) {}
	}

	// Set poll interval to 60 secs.
	modem.minPollInterval(60);
	// NOTE: independent of this setting, the modem will
	// not allow sending more than one message every 2 minutes,
	// this is enforced by firmware and can not be changed.
pinMode(PB5, OUTPUT);
}
void loop(void){
	// blink the LED
	

	mySerial.println();
	mySerial.println("Enter a message to send to network");
	mySerial.println("(make sure that end-of-line 'NL' is enabled)");

	while (!mySerial.available());
	String msg = mySerial.readStringUntil('###');

	mySerial.println();
	mySerial.print("Sending: " + msg + " - ");
	for (unsigned int i = 0; i < msg.length(); i++) {
		mySerial.print(msg[i] >> 4, HEX);
		mySerial.print(msg[i] & 0xF, HEX);
		mySerial.print(" ");
	}
	mySerial.println();

	int err;
	modem.beginPacket();
	modem.print(msg);
	err = modem.endPacket(true);
	if (err > 0) {
		mySerial.println("Message sent correctly!");
	} else {
		mySerial.println("Error sending message :(");
		mySerial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
		mySerial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
	}
	delay(1000);
	if (!modem.available()) {
		mySerial.println("No downlink message received at this time.");
		return;
	}
	char rcv[64];
	int i = 0;
	while (modem.available()) {
		rcv[i++] = (char)modem.read();
	}
	mySerial.print("Received: ");
	for (unsigned int j = 0; j < i; j++) {
		mySerial.print(rcv[j] >> 4, HEX);
		mySerial.print(rcv[j] & 0xF, HEX);
		mySerial.print(" ");
	}
	mySerial.println();


}


