# particle-hc-sr04

Firmware for reading ultrasonic measurements from an HC-SR04 on a Particle device.

The firmware assigns the readings to `inches` and `cm` variables.

## To build/deploy/test

1. Clone this repo

2. `cd particle-hc-sr04` 

3. `particle flash YOUR_DEVICE_NAME_OR_ID particle.ino`

4. `particle monitor YOUR_DEVICE_NAME_OR_ID inches`

## Note

* You'll need to power the HC-SR04 externally with 5V. Undervolting it by using the Particle's 3.3V pin will interrupt the Particle's WiFi while we wait for the HC's trigger pin.
* Make sure to share the ground wires between the Particle's GND pin and the 5V source for the HC-SR04

## Someday/maybe

* Publish threshold events to the Particle cloud
* Implement smart interrupts if the TRIG pin times out
