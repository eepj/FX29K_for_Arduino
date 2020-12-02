#include "FX29K.h"

FX29 scale(FX29K0_I2C_ADDR, 10, &Wire);

void setup(){
  Serial.begin(115200);
  scale.begin();
  Serial.println("Kilograms\tPounds");
  Serial.println("-------------------------------");
}

void loop(){
  float kg = scale.getKilograms();
  float lb = scale.getPounds();
  Serial.print(kg);
  Serial.print("\t");
  Serial.println(lb);
  delay(1000);
}
