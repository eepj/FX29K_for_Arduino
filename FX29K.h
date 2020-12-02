#ifndef FX29K_H
#define FX29K_H
#include <Wire.h>

#define FX29K0_I2C_ADDR 0x28
#define FX29K1_I2C_ADDR 0x36
#define FX29K2_I2C_ADDR 0x46
#define FX29K3_I2C_ADDR 0x48
#define FX29K4_I2C_ADDR 0x51

class FX29{
  private:
    uint8_t _i2cAddr = FX29K0_I2C_ADDR;
    uint8_t _range = 0010;
    TwoWire* _i2cPtr = &Wire;
  public:
    FX29(void);
    FX29(uint8_t addr, uint8_t range, TwoWire* i2cPtr);
    ~FX29(void);
    void requestMeasurement(void);
    uint16_t getRawBridgeData(void);
    float getPounds(void);
    float getKilograms(void);
    void write(TwoWire* i2cPtr, uint8_t i2cAddr, uint8_t* arr, uint8_t byteCount);
    void read(TwoWire* i2cPtr, uint8_t i2cAddr, uint8_t* arr, uint8_t byteCount);
};

#endif
