

/* 1byte HC12 Receiver example.
/* Tutorial link: http://electronoobs.com/eng_arduino_tut96.php
 * Code: http://electronoobs.com/eng_arduino_tut96_code1.php
 * Scheamtic: http://electronoobs.com/eng_arduino_tut96_sch1.php
 * Youtube Channel: http://www.youtube/c/electronoobs   
 * 
  Module // Arduino UNO/NANO    
    GND    ->   GND
    Vcc    ->   3.3V
    Tx     ->   D10
    Rx     ->   D11      
 */
#include <SoftwareSerial.h>
#define TXP 26
#define RXP 27
#define LED 3
SoftwareSerial HC12(RXP, TXP); // RX, TX pins

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  //pinMode(LED,OUTPUT);
}
void loop() {
  if(HC12.available()) {        // If HC-12 has data
    String input = HC12.readStringUntil('\n');
    Serial.println(input);      // Send the data to Serial monitor
  }  
}