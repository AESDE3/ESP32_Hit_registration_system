#include <SoftwareSerial.h>

#include "common/shared_defaults.h"
#include "common/hc12_config.h"

#define TXP 26
#define RXP 27
#define SETP 28
#define LED 3
SoftwareSerial HC12(RXP, TXP); // RX, TX pins

static int setup_hc12(){
  digitalWrite(SETP, LOW); // AT mode
  delay(40);

  int ret;

  ret = hc12_change_baudrate(BAUDRATE);
  if (ret != 0){
    Serial.println("Failed to change baudrate")
    return -1;
  }
  ret = hc12_change_channel(CHANNEL);
  if (ret != 0){
    Serial.println("Failed to change channel")
    return -1;
  }
  ret = hc12_change_transmission_mode(TX_MODE);
  if (ret != 0){
    Serial.println("Failed to change transmission mode")
    return -1;
  }
  ret = hc12_change_tx_power(TX_POWER);
  if (ret != 0){
    Serial.println("Failed to change transmit power")
    return -1;
  }

  digitalWrite(SETP, HIGH); // AT mode
  delay(80);

  return 0
}

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12

  if (setup_hc12() != 0) {
    Serial.println("HC12 setup failed");
  } else {
    Serial.println("HC12 setup done");
  }
  //pinMode(LED,OUTPUT);
}
void loop() {
  if(HC12.available()) {        // If HC-12 has data
    String input = HC12.readStringUntil('\n');
    Serial.println(input);      // Send the data to Serial monitor
  }  
}