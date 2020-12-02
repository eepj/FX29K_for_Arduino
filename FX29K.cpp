#include "FX29K.h"
#include <Wire.h>

FX29K::FX29K(uint8_t addr, uint8_t range, TwoWire* i2cPtr) {
  _i2cAddr = addr;
  _range = range;
  _i2cPtr = i2cPtr;
}

FX29K::FX29K(void) {

}

FX29K::~FX29K(void) {

}

void FX29K::begin(void){
    Wire.begin(_i2cAddr);
}

void FX29K::requestMeasurement(void) {
  uint8_t temp = 0;
  write(_i2cPtr, _i2cAddr, &temp, 0);
}

uint16_t FX29K::getRawBridgeData(void) {
  uint8_t bridgeData[2] = {0};
  read(_i2cPtr, _i2cAddr, bridgeData, 2);
  return (bridgeData[0] << 8 | bridgeData[1]);
}

float FX29K::getPounds(void){
  uint16_t bridgeData = getRawBridgeData();
  return ((bridgeData - 1000) * _range / 14000.0); 
}

float FX29K::getKilograms(void){
  return getPounds() / 2.205; 
}

void FX29K:: write(TwoWire* i2cPtr, uint8_t i2cAddr, uint8_t* arr, uint8_t byteCount) {
  i2cPtr->beginTransmission(i2cAddr);
  for (uint8_t i = 0; i < byteCount; i++) {
    i2cPtr->write(*(arr + i));
  }
  i2cPtr->endTransmission();
}

void FX29K::read(TwoWire* i2cPtr, uint8_t i2cAddr, uint8_t* arr, uint8_t byteCount) {
  i2cPtr->requestFrom(i2cAddr, byteCount);
  for (uint8_t i = 0; i < byteCount; i++) {
    *arr = i2cPtr->read();
  }
}
