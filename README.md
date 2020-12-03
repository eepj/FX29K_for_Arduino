# FX29K_for_Arduino
An Arduino library written for the FX29K digital load cells.

## Compatibility
Supported models:
* `FX29Kx-xxxx-xxxx-L` (Tested)
* `FX29Jx-xxxx-xxxx-L` (Not tested)

FX292 and FX293 analog load cells are *NOT* supported.

## Quick start
### Minimal connections
```ruby
   RED ---------- VCC (2.7-5.5V)
YELLOW ---------- SCL
 WHITE ---------- SDA
 BLACK ---------- GND
```
### Main Program
#### Include
* In your `.ino` file, include [`FX29K.h`](./FX29K.h):
```ruby
#include "FX29K.h"
```
#### Declaration
* Declare your object globally, with constructors:
```ruby  
FX29K::FX29K(uint8_t addr, uint8_t range);
FX29K::FX29K(uint8_t addr, uint8_t range, TwoWire* i2cPtr);
```
* Check your load cell's part number and find the parameter for the constructors.
```ruby
FX29Kx-xxxx-xxxx-L
|____|      |__|
 addr       range
```
* For example, for `FX29K0-040B-0010-L`:
```ruby
FX29K fx29k(FX29K0, 0010, &Wire);
```
#### Initialization
* In `setup()`, initialize your object:
```ruby
void FX29K::begin(void);
```
* Tare your load cell with:
```ruby
void FX29K::tare(void);
void FX29K::tare(uint16_t samples);
```
#### Measurement
* Read raw wheatstone bridge data with:
```ruby
uint16_t FX29K::getRawBridgeData(void);
```
* Read weight with any of the following:
```ruby
double FX29K::getPounds(void);
double FX29K::getKilograms(void);
uint16_t FX29K::getGrams(void);
```
### Misc
* Refer to ./[`FX29K_for_Arduino.ino`](./FX29_for_Arduino.ino) and [datasheets](https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FFX29%7FA5%7Fpdf%7FEnglish%7FENG_DS_FX29_A5.pdf%7FCAT-FSE0006) for further information.
