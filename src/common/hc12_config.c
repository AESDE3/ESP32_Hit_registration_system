#include <SoftwareSerial.h>
#include <string.h>
#include "hc12_config.h"

#define TIMEOUT_MILLIS 1000


/**
 * Runs commands into the serial. Remember to put SET pin to low and 
 * add delays before and after changing any settings (40ms before, 80ms after)
 */
static int run_command(SoftwareSerial *Serial, char *command){
    Serial->print("AT+");
    Serial->println(command);

    unsigned long start = millis();
    while (!serial->available()){
        if (millis() - start > TIMEOUT_MILLIS){
            return -1;
        }
    }

    char response Serial->readStringUntil('\n');
    return response.trim().startsWith("OK") ? 0 : -1;
}

/**
 * Change the UART baudrate. Acceptable options: 
 * 1200, 2400, 4800, 9600, 19200, 38400, 57600 and 115200
 */
int hc12_change_baudrate(SoftwareSerial *Serial, int baud){
    char cmd[10];
    snprintf(cmd, sizeof(cmd), "B%d", baud);
    return run_command(Serial, cmd);
}

/**
 * Change the wireless transmitting channel. Acceptable options:
 * 1 to 127 (433.4MHz to 473.0 MHz)
 */
int hc12_change_channel(SoftwareSerial *Serial, int channel){
    if (channel < 1 || channel > 127) return -1;

    char cmd[10];
    snprintf(cmd, sizeof(cmd), "C%03d", channel);
    return run_command(Serial, cmd);
}

/**
 * Change UART transmission mode. Acceptable options:
 * 1 to 4, lower for power saving, higher for more range
 * 
 * !! THIS ALSO CHANGES OTHER SETTINGS !!
 * 
 * Check out HC12 datasheet page 5 and 6.
 * https://statics3.seeedstudio.com/assets/file/bazaar/product/HC-12_english_datasheets.pdf
 * 
 */
int hc12_change_transmission_mode(SoftwareSerial *Serial, int mode){
    if (mode < 1 || mode > 4) return -1;

    char cmd[10];
    snprintf(cmd, sizeof(cmd), "FU%d", mode);
    return run_command(Serial, cmd);
}

/**
 * Change transmission power. Acceptable options:
 * 1 to 8, (-1dBm to 20dBm)
 */
int hc12_change_tx_power(SoftwareSerial *Serial, int power){
    if (power < 1 || power > 8) return -1;

    char cmd[10];
    snprintf(cmd, sizeof(cmd), "P%d", power);
    return run_command(Serial, cmd);
}
