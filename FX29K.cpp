#include "FX29K.h"
#include <Wire.h>

FX29::FX29(uint8_t addr, uint8_t range, TwoWire* i2cPtr) {
  _i2cAddr = addr;
  _range = range;
  _i2cPtr = i2cPtr;
}

FX29::FX29(void) {

}

FX29::~FX29(void) {

}

void FX29::requestMeasurement(void) {
  uint8_t temp = 0;
  write(_i2cPtr, _i2cAddr, &temp, 0);
}

uint16_t FX29::getRawBridgeData(void) {
  uint8_t bridgeData[2] = {0};
  read(_i2cPtr, _i2cAddr, bridgeData, 2);
  return ((bridgeData[0] << 8) | bridgeData[1]);
}

void write(TwoWire* i2cPtr, uint8_t i2cAddr, uint8_t* arr, uint8_t byteCount) {
  i2cPtr->beginTransmission(i2cAddr);
  for (uint8_t i = 0; i < byteCount; i++) {
    i2cPtr->write(*(arr + i));
  }
  i2cPtr->endTransmission();
}

void read(TwoWire* i2cPtr, uint8_t i2cAddr, uint8_t* arr, uint8_t byteCount) {
  i2cPtr->requestFrom(i2cAddr, byteCount);
  for (uint8_t i = 0; i < byteCount; i++) {
    *arr = i2cPtr->read();
  }
}
