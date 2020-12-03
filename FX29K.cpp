#include "FX29K.h"
#include <Wire.h>

/**
 * @brief Construct a FX29K object instance.
 *
 * Check your load cell's part number:
 *
 *  FX29Kx-xxxx-xxxx-x
 *  |____|      |___|
 *	 addr       range
 *
 * @param addr FX29 I2C address. For simplicity, directly type the first 6 characters of your load cell part number as parameter.
 * @param range FX29 load range.
 * @param i2cPtr TwoWire object pointer.
 */
FX29K::FX29K(uint8_t addr, uint8_t range, TwoWire* i2cPtr) {
  _i2cAddr = addr;
  _range = range;
  _i2cPtr = i2cPtr;
}

/**
 * @brief Construct a FX29K object instance.
 *
 * Check your load cell's part number:
 *
 *  FX29Kx-xxxx-xxxx-x
 *  |____|      |___|
 *	 addr       range
 *
 * @param addr FX29 I2C address. For simplicity, directly type the first 6 characters of your load cell part number as parameter.
 * @param range FX29 load range.
 */
FX29K::FX29K(uint8_t addr, uint8_t range) {
  _i2cAddr = addr;
  _range = range;
}

/**
 * @brief Constructor, private by default.
 */
FX29K::FX29K(void) {}

/**
 * @brief Destructor.
 */
FX29K::~FX29K(void) {}

/**
 * @brief Initialization function. To be called once in setup().
 */
void FX29K::begin(void) {
  Wire.begin(_i2cAddr);
  tare();
}

/**
 * @brief Tare the scale with the average of 10 samples.
 */
void FX29K::tare(void) {
  requestMeasurement();
  uint32_t sum = 0;
  for (uint8_t i = 0; i < 10; i++) {
    sum += getRawBridgeData();
    delay(10);
  }
  _tare = sum / 10;
}

/**
 * @brief Tare the scale with the average of n samples.
 * @param samples Number of samples (n) to take while taring the scale.
 */
void FX29K::tare(uint16_t samples) {
  requestMeasurement();
  uint32_t sum = 0;
  for (uint16_t i = 0; i < samples; i++) {
    sum += getRawBridgeData();
    delay(10);
  }
  _tare = sum / 10;
}

/**
 * @brief Device to start a measuremnet.
 */
void FX29K::requestMeasurement(void) {
  uint8_t temp = 0;
  write(_i2cPtr, _i2cAddr, &temp, 0);
}

/**
 * @brief Device to return raw bridge data.
 * @return Bridge data as a 14-bit number.
 */
uint16_t FX29K::getRawBridgeData(void) {
  uint8_t bridgeData[2] = {0};
  read(_i2cPtr, _i2cAddr, bridgeData, 2);
  return (bridgeData[0] << 8 | bridgeData[1]) & 0x3fff;
}

/**
 * @brief Get weight in pounds (lbs).
 * @return Weight, in pounds.
 */
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

/**
 * @brief Get weight in kilograms (kgs).
 * @return Weight, in kilograms.
 */
uint16_t FX29K::getGrams(void) {
  return getPounds() * 2205;
}

/**
 * @brief I2C read function.
 * @param i2cPtr TwoWire object pointer.
 * @param i2cAddr I2C device address to read from.
 * @param arr Array to write fetched data bytes to.
 * @param byteCount Number of bytes to read.
 */
void FX29K:: write(TwoWire* i2cPtr, uint8_t i2cAddr, uint8_t* arr, uint8_t byteCount) {
  i2cPtr->beginTransmission(i2cAddr);
  for (uint8_t i = 0; i < byteCount; i++) {
    i2cPtr->write(*(arr + i));
  }
  i2cPtr->endTransmission();
}

/**
 * @brief I2C write function.
 * @param i2cPtr TwoWire object pointer.
 * @param i2cAddr I2C device address to write to.
 * @param arr Array containing data bytes to write.
 * @param byteCount Number of bytes to write.
 */
void FX29K::read(TwoWire* i2cPtr, uint8_t i2cAddr, uint8_t* arr, uint8_t byteCount) {
  i2cPtr->requestFrom(i2cAddr, byteCount);
  for (uint8_t i = 0; i < byteCount; i++) {
    *(arr + i) = i2cPtr->read();
  }
  i2cPtr->endTransmission();
}
