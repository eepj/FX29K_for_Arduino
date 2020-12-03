#include "FX29K.h"
#include <Arduino.h>
#include <Wire.h>

FX29K::FX29K(uint8_t addr, uint8_t range, TwoWire* i2cPtr) {
  _i2cAddr = addr;
  _range = range;
  _i2cPtr = i2cPtr;
}

FX29K::FX29K(uint8_t addr, uint8_t range) {
  _i2cAddr = addr;
  _range = range;
}

FX29K::FX29K(void) {}

FX29K::~FX29K(void) {}

void FX29K::begin(void) {
  Wire.begin(_i2cAddr);
  tare();
}

void FX29K::tare(void) {
  requestMeasurement();
  uint32_t sum = 0;
  for (uint8_t i = 0; i < 10; i++) {
    sum += getRawBridgeData();
    delay(10);
  }
  _tare = sum / 10;
}

void FX29K::tare(uint16_t samples) {
  requestMeasurement();
  uint32_t sum = 0;
  for (uint16_t i = 0; i < samples; i++) {
    sum += getRawBridgeData();
    delay(10);
  }
  _tare = sum / 10;
}

void FX29K::requestMeasurement(void) {
  uint8_t temp = 0;
  write(_i2cPtr, _i2cAddr, &temp, 0);
}

uint16_t FX29K::getRawBridgeData(void) {
  uint8_t bridgeData[2] = {0};
  read(_i2cPtr, _i2cAddr, bridgeData, 2);
  return (bridgeData[0] << 8 | bridgeData[1]) & 0x3fff;
}

double FX29K::getPounds(void) {
  uint16_t bridgeData = getRawBridgeData();
  uint16_t net = bridgeData - _tare;
  if (net < 1000)
    return 0.0;
  else
    return ((net - 1000) * _range / 14000.0);
}

double FX29K::getKilograms(void) {
  return getPounds() / 2.205;
}

uint16_t FX29K::getGrams(void) {
  return getPounds() * 2205;
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
    *(arr + i) = i2cPtr->read();
  }
  i2cPtr->endTransmission();
}
