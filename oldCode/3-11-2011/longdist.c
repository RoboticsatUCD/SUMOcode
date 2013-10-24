#include <math.h>
#include <pololu/orangutan.h>
#include "longdist.h"

// Returns the distance in centimeters from a pin.
unsigned int long_range_distance(unsigned char pin) {
   unsigned int distVoltage = analog_read(pin);
   unsigned int distValue = convertToDistance(distVoltage);
}

// Converts the input voltage (10-bit unsigned int) to centimeters.
unsigned int convertToDistance(unsigned int distVoltage) {
   return (4034.6 * pow(distVoltage, -1.084));
}
