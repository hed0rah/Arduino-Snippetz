// OLED_Debug_Tool.ino
// Comprehensive debug for tiny 72x40 SSD1306 OLED (I2C)
// Tests scanner + Adafruit lib + U8g2 lib
// Use Serial Monitor at 115200 baud

#include <Wire.h>

// ────────────── Choose ONE display library to test at a time ──────────────
// Option A: Adafruit SSD1306 (your original, may need offset fix)
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH  72
#define SCREEN_HEIGHT 40
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C   // <── try 0x3D if this fails
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Option B: U8g2 ── usually works best on these tiny 72x40 screens
// Uncomment the include & constructor below when you want to switch
//#include <U8g2lib.h>
//U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  
// Alternative popular workaround if above constructor missing in your version:
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
// Then in setup after begin(): u8g2.setBufferPtrOffset(28, 12);  // rough center offset example

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);          // Wait for Serial (good for Leonardo/Micro/etc.)
  delay(500);
  Serial.println("\n=== OLED 72x40 DEBUG TOOL ===");
  Serial.println("Wiring reminder: 3.3V power/logic preferred, 4.7k pull-ups on SDA/SCL");

  Wire.begin();                       // SDA = A4, SCL = A5 on Uno; or your pins
  // Wire.setClock(100000);           // Uncomment to force 100 kHz if unstable

  // ────────────────────────────── I2C SCANNER ──────────────────────────────
  Serial.println("\nScanning I2C bus...");
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("→ Device found at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      Serial.print("→ Unknown error at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found → check wiring / voltage / pull-ups!");
  } else {
    Serial.print(nDevices);
    Serial.println(" device(s) found");
  }

  // ────────────────────── TEST ADAFRUIT SSD1306 ──────────────────────
  Serial.println("\nTrying Adafruit_SSD1306 init...");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("→ Adafruit init FAILED (wrong addr? bad wiring? lib incompatible?)");
  } else {
    Serial.println("→ Adafruit init OK!");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Adafruit test"));
    display.setCursor(0, 12);
    display.println(F("72x40 OLED"));
    display.setCursor(0, 24);
    display.println(F("If shifted/garbage → use U8g2"));
    display.display();
    Serial.println("→ Should show text now (if screen black → voltage/wiring)");
  }

  // ────────────────────── TEST U8G2 (uncomment when ready) ──────────────────────
  /*
  Serial.println("\nTrying U8g2 init...");
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);           // small readable font
  u8g2.drawStr(0, 10, "U8g2 test");
  u8g2.drawStr(0, 22, "72x40 should look");
  u8g2.drawStr(0, 34, "clean & centered");
  u8g2.sendBuffer();
  Serial.println("→ U8g2 should show clean text (best chance of success)");
  */

  Serial.println("\nDebug done. Re-upload with U8g2 section uncommented if Adafruit fails.");
  Serial.println("When breadboard ready, we can refine wiring & test live!\n");
}

void loop() {
  // Blink built-in LED as "alive" sign
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
