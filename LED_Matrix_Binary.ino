#include "Arduino_LED_Matrix.h"
// Arduino R4 Uno 12x8 LED Matrix used to display up to 12 8bit numbers in binary
// hed0rah ()
ArduinoLEDMatrix matrix;

uint8_t numbers[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};  // test array

void binaryMatrix(uint8_t numbers[], uint8_t size) {
  
  byte frame[8][12] = {0};  // init array with all pixels off

  for (int j = 0; j < size; j++) {
    for (int i = 0; i < 8; i++) {
      // calculate the bit position
      int bitPos = 7 - i;
      // check if the bit at current position is set
      bool isSet = numbers[j] & (1 << bitPos);
      // set the pixel at current position
      frame[i][j] = isSet;
    }
  }
  
  matrix.renderBitmap(frame, 8, 12);
}

void setup() {
  Serial.begin(115200);
  matrix.begin();
}

void loop() {
  binaryMatrix(numbers, 12);
}
