#include <pololu/orangutan.h>
#include <math.h>

#define REVERSE 1
#define FORWARD 0
#define RIGHT 0
#define LEFT 1

// Output pins of the motor control
#define MOS1 IO_B1
#define MOS2 IO_B0
#define MOS3 IO_D2
#define MOS4 IO_D7

// M1A is PD6, M1B is PD5 this will be the left motor
// M2B is PB3, M2B is PD3 this will be the right motor

void turn(int direction, int degrees, int speed);

void set_speed(int speed, int speed2);

void stop();
void stop_m1();
void stop_m2();

// global variables
int currentM1Speed;
int currentM2Speed;
