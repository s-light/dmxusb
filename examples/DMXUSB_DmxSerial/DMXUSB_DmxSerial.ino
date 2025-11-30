/* DMXUSB_DmxSerial.ino
 * Originally created 11/25/2017 by Perry Naseck (DaAwesomeP)
 * This is an example sketch for the DMXUSB Arduino/Teensy library to create a
 * USB to DMX device. https://github.com/DaAwesomeP/dmxusb/
 *
 * Copyright 2017-present Perry Naseck (DaAwesomeP)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// converted DmxSimple to DmxSerial
// 30.11.2025 by Stefan Krüger (s-light.eu)
// This is tested on an Arduino Leonardo with QLC+ as host software

// More information about DmxSerial here:
// https://github.com/mathertel/DmxSerial
// https://github.com/mathertel/DMXSerial/blob/master/examples/DmxSerialSend/DmxSerialSend.ino

#include "DMXUSB.h"
#include <DMXSerial.h>

// DMXUSB should receive and transmit data at the highest,
// most reliable speed possible.
// Recommended / baud rate:
// Arduino UNO:  115200
// Teensy 3:    2000000 (2 Mb/s)
// DMX:          250000
// MIDI:          31250
//
// the Baudrate here has no effect on an Leonardo.
// https://forum.arduino.cc/t/leonardo-baud-rate-for-usb-cdc/106259/23
// i think it is the same as with the Teensy - both have native usb.
#define DMXUSB_BAUDRATE 2000000

// Pin that DMX port is on
// DmxSimple uses pin 3 by default.
#define DMX_PIN 3

// receive a DMX transmission
void sendDMX(int universe, char buffer[512]) {
    for (int index = 0; index < 512; index++) {
        // for each channel, 
        // universe starts at 0
        // channel starts at 0, 
        // so 
        // index 0 is DMX channel 1 and 
        // index 511 is DMX channel 512
        int channel = index + 1;

        // DMX value 0 to 255
        int value = buffer[index];

        if (universe == 0) {
            DMXSerial.write(channel, value);
        }
    }
}

DMXUSB DMXPC(
    // Stream serial,
    Serial,
    // int baudrate,
    DMXUSB_BAUDRATE,
    // int mode,
    0,
    // void (*dmxInCallback)(int universe, unsigned int index, char buffer[512])
    sendDMX);

void setup() {
    Serial.begin(DMXUSB_BAUDRATE);

    // DMX port
    DMXSerial.init(DMXController);
}

void loop() { DMXPC.listen(); }
