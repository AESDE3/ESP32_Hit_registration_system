#ifndef HC12_CONFIG_H
#define HC12_CONFIG_H

#include <SoftwareSerial.h>

int hc12_change_baudrate(SoftwareSerial*, int);
int hc12_change_channel(SoftwareSerial*, int);
int hc12_change_transmission_mode(SoftwareSerial*, int);
int hc12_change_tx_power(SoftwareSerial*, int);

#endif