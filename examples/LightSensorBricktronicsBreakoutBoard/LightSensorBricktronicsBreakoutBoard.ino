// Bricktronics Example: LightSensorBricktronicsBreakoutBoard
// http://www.wayneandlayne.com/bricktronics
//
// Light sensor readings are taken every 100 milliseconds, and
// printed out over the serial console. Be sure to set your serial
// console to 115200 baud. The light sensor library reports the measured
// light value with a unitless value between 0 (very dim) and
// 1023 (very bright). We can also set a calibration range, and the
// library can scale the raw value to a range of 0-100 based on the
// calibration values. Both these values are printed to the serial console.
//
// We also flash the Light Sensor's LED between each sample. We've found
// that the light doesn't help much in distinguishing between light and dark
// surfaces, but your mileage may vary, so give it a try.
//
// Hardware used:
// * Wayne and Layne Bricktronics Breakout Board
//   https://store.wayneandlayne.com/products/bricktronics-breakout-board.html
// * LEGO NXT Light Sensor
//
// Software libraries used:
// * Wayne and Layne BricktronicsLight library
//   https://github.com/wayneandlayne/BricktronicsLight
//
// Written in 2016 by Matthew Beckler and Adam Wolf for Wayne and Layne, LLC
// To the extent possible under law, the author(s) have dedicated all
//   copyright and related and neighboring rights to this software to the
//   public domain worldwide. This software is distributed without any warranty.
// You should have received a copy of the CC0 Public Domain Dedication along
//   with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.


// Include the Bricktronics libraries
#include <BricktronicsLight.h>


// Connect these pins on the Bricktronics Breakout board:
//  Pin 1 - Connect to any analog input pin
//  Pin 2 - Connect to Ground
//  Pin 3 - Connect to Ground
//  Pin 4 - Connect to 5V
//  Pin 5 - Connect to any digital pin
//  Pin 6 - No connection
//
// The BricktronicsLight() arguments are: inputPin (pin 1), lightPin (pin 5)
// There is one consideration for pin assignments:
// A. inputPin needs to be an analog pin
//
BricktronicsLight ls(A0, 12);


void setup()
{
  // Be sure to set your serial console to 115200 baud
  Serial.begin(115200);

  // Initialize the light sensor connections
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

