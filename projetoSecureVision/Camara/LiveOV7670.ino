




// change setup.h to switch between buffered and pixel-by-pixel processing
#include "setup.h"



void setup() {
  // This is not necessary and has no effect for ATMEGA based Arduinos.
  // WAVGAT Nano has slower clock rate by default. We want to reset it to maximum speed
  CLKPR = 0x80; // enter clock rate change mode
  CLKPR = 0; // set prescaler to 0. WAVGAT MCU has it 3 by default.
  Serial.begin(9600);
  Serial.println("SETUP");
  initializeScreenAndCamera();
}


void loop() {
  Serial.println("loop");
  delay(2000);
  processFrame();
}
