/* LoRaWAN Class A Hello World example
 *
 * Sends a message every 30 seconds
 *
 * This example code will just test the LoRaWAN stack STM32 using STM32LoRaWAN
 */
#include <Arduino.h>
#include <STM32RTC.h>
#include <STM32LoRaWAN.h>


// Blinky LED for now
//#define LED_BUILTIN PB5


void setup(void){
pinMode(PB5, OUTPUT);
}
void loop(void){
digitalWrite(PB5, HIGH);
delay(1000);
digitalWrite(PB5, LOW);
delay(1000);
}


