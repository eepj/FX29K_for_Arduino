#include "FX29K.h"

FX29K scale(FX29K0, 0010, &Wire);

void setup(){
  Serial.begin(115200);
  scale.begin();
  Serial.println("Kilograms\tPounds\tRaw");
  Serial.println("-------------------------------");
}

void loop(){
  uint16_t raw = scale.getRawBridgeData();
  float kg = scale.getKilograms();
  float lb = scale.getPounds();
  Serial.print(kg);
  Serial.print("\t");
  Serial.print(lb);
  Serial.print("\t");
  Serial.println(raw);
  delay(1000);
}
