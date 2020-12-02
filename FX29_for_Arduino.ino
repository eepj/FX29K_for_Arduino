#include "FX29K.h"

FX29K scale(FX29K0, 0010, &Wire);

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
