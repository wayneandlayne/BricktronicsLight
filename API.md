# BricktronicsLight API

This library interfaces with LEGO NXT light sensors. It can be used with the [Bricktronics Shield](https://store.wayneandlayne.com/products/bricktronics-shield-kit.html), [Bricktronics Megashield](https://store.wayneandlayne.com/products/bricktronics-megashield-kit.html), or standalone with the [Bricktronics Breakout Board](https://store.wayneandlayne.com/products/bricktronics-breakout-board.html). For the shield/megashield, use the constructor below with the `BricktronicsSensorSettings` struct, otherwise use the constructor below that accepts the input pin number.

# Connection with [Bricktronics Shield](https://store.wayneandlayne.com/products/bricktronics-shield-kit.html)

Use the light sensor with any sensor port on the Bricktronics Shield. Use the jumpers to connect pins 2-3 and 4-5.

Constructor usage for Bricktronics Shield
```C++
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <BricktronicsShield.h>
#include <BricktronicsLight.h>
BricktronicsLight ls(BricktronicsShield::SENSOR_1);
```

# Connection with [Bricktronics Megashield](https://store.wayneandlayne.com/products/bricktronics-megashield-kit.html)

Use the light sensor with any sensor port on the Bricktronics Megashield. Use the jumpers to connect pins 2-3 and 4-5.

Constructor usage for Bricktronics Megashield
```C++
#include <BricktronicsMegashield.h>
#include <BricktronicsLight.h>
BricktronicsLight ls(BricktronicsMegashield::SENSOR_1);
```

# Connection with [Bricktronics Breakout Board](https://store.wayneandlayne.com/products/bricktronics-breakout-board.html)

* Pin 1 - Connect to any analog input pin (this is `inputPin` below)
* Pin 2 - Connect to Ground
* Pin 3 - Connect to Ground
* Pin 4 - Connect to 5V
* Pin 5 - Connect to any digital pin (this is `lightPin` below)
* Pin 6 - No connection

Constructor usage for Bricktronics Breakout Board:
```C++
#include <BricktronicsLight.h>
BricktronicsLight ls(A0, 12); // Constructor arguments: inputPin, lightPin
```

# Quick Example

```C++
#include <BricktronicsLight.h>

// Use one of the constructor options listed above.
BricktronicsLight ls(A0, 12);

void setup()
{
    Serial.begin(115200);
    // If using a Bricktronics Shield, you need to call
    // BricktronicsShield::begin();
    ls.begin();
}

void loop()
{
    Serial.print("Raw value: ");
    Serial.print(ls.value());
    Serial.print(" - scaled value: ");
    Serial.println(ls.scaledValue());

    // Flash the light sensor's built-in led, just for fun
    ls.setFloodlightAlways(true);
    delay(100);
    ls.setFloodlightAlways(false);

    delay(500);
}
```

# Constructors and begin()

#### `BricktronicsLight(uint8_t inputPin, uint8_t lightPin)`

Constructor - Simple constructor that accepts the data input and light control pins

**Parameters**

* `uint8_t inputPin` - The Arduino pin number where the sensor's pin 1 is connected. Must have analog input.
* `uint8_t lightPin` - The Arduino pin number where the sensor's pin 5 is connected.


#### `BricktronicsLight(const BricktronicsSensorSettings &settings)`

Constructor - Advanced constructor that accepts a SensorSettings struct to also override the low-level Arduino functions.

**Parameters**

* `const BricktronicsSensorSettings &settings` - A const reference to the struct containing all the sensor settings. Get these structs from the [BricktronicsShield](https://github.com/wayneandlayne/BricktronicsShield) or [BricktronicsMegashield](https://github.com/wayneandlayne/BricktronicsMegashield) library.

#### `void begin(void)`

Call this function once for each instance during your setup() function.


# Basic light sensor functions

#### `uint16_t value(void)`

Basic sensor read function. Scale is from 0 (very dark) to 1023 (very bright), but usually the actual range is about 550 to 990. If you have enabled the light, it will flash as part of the read process. It will turn on, delay for some time (default is 50ms), perform the analog read, then turn off the light.


#### `uint8_t scaledValue(void)`

Scales the raw brightness from `value()` above into an integer between 0 and 100. Uses the calibration low and high values (see below) for scaling range. Constrained to return a value between 0 and 100 inclusive.


# Automatic calibration functions

Point the light sensor at your bright/dark objects or surfaces, then call the corresponding function. Takes the average of 16 samples and updates the internal calibration values for use with `scaledValue()`. Both functions return true if the calibration passes a simple sanity check (that is, if `_calibrationLowValue < _calibrationHighValue`).

#### `bool calibrateLow(void)`

Use this function to calibrate the low value for your **dark** object or surface.

#### `bool calibrateHigh(void)`

Use this function to calibrate the low value for your **bright** object or surface.


# Manual calibration functions

These functions can be used to manually set the desired calibration low and high values.

#### `void setCalibrationLowValue(uint16_t value)`

#### `uint16_t getCalibrationLowValue(void)`

#### `void setCalibrationHighValue(uint16_t value)`

#### `uint16_t getCalibrationHighValue(void)`


# Sensor floodlight settings

The sensor has a small light that can be used to illuminate the sensor's target. There are two settings to control this light, and by default the light never turns on.

* If both are false, the light is never turned on (default).
* If `setFloodlight` is enabled, the light is turned on for each reading.
* If `setFloodlightAlways` in enabled, the light is always on, and the value of `setFloodlight` is ignored.

If you want to manually control the light, call `setFloodlight(false)` and use `setFloodlightAlways(true / false)` to turn it on and off.

#### `void setFloodlight(bool enable)`

#### `bool getFloodlight(void)`

#### `void setFloodlightAlways(bool enable)`

#### `bool getFloodlightAlways(void)`

You can also control the amount of time the floodlight is turned on before the analog reading is taken. Defaults to 50 ms. Light is pretty fast so you probably don't need to change this setting.

#### `void setFloodlightDelayInMs(uint16_t delayInMs)`

#### `uint16_t getFloodlightDelayInMs(void)`

