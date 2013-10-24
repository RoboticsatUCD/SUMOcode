#include <math.h>
#include <pololu/orangutan.h>

// Returns the distance in centimeters from a pin.
unsigned int longRangeDistance(unsigned char pin);

// Converts the input voltage (10-bit unsigned int) to centimeters.
unsigned int convertToDistance(unsigned int distVoltage);
