#include <SoftwareSerial.h>

#define TXP 26
#define RXP 27
#define SETP 28 // tähän joku pinni
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
  pinMode(SETP, OUTPUT);

  
  if (setup_hc12() != 0) {
    Serial.println("HC12 setup failed");
  } else {
    Serial.println("HC12 setup done");
  }
}
void loop() {  
  HC12.println("sent");      // Send that data to HC-12
  delay(1000);  
}