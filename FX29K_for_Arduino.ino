#include "FX29K.h"
#define MUX_ADDR 0x70
FX29K scale(FX29K0, 0010, &Wire);

void setup() {
  Wire.begin();
  Wire.begin(MUX_ADDR);
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(1 << 7);
  Wire.endTransmission();
  delay(100);
  Serial.begin(115200);
  scale.begin();
  scale.tare(1000);
  Serial.println("Grams\tPounds\tRaw");
  Serial.println("--------------------");
}

void loop() {
  uint16_t raw = scale.getRawBridgeData();
  float g = scale.getGrams(1000);
  float lb = scale.getPounds(1000);
  Serial.print(g, 1);
  Serial.print("\t");
  Serial.print(lb, 3);
  Serial.print("\t");
  Serial.println(raw);
  delay(1000);
}
