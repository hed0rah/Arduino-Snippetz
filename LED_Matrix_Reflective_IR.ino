#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int sensorPin=8;

unsigned long smiley[] = {
  	0x19819,
		0x80000002,
		0x43fc000
};


unsigned long frowny[] = {
	0x19819,
		0x80000003,
		0xfc204000
};

void setup() {
  Serial.begin(115200);
  matrix.begin();
}

void loop() {
  int val = digitalRead(sensorPin);
  Serial.println(val);
  if (val == HIGH) {
    matrix.loadFrame(smiley);
    delay(500);
  }
  else {
    matrix.loadFrame(frowny);
    delay(500);
  }
}
