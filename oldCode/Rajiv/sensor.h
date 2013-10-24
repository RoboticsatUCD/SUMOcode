#include <pololu/orangutan.h>

#include "motor.h"

#define TLLINE 0	//pin IO_C0 //need to put in channels instead of pins for analog functions
#define TRLINE 1	//pin IO_C1
#define BLLINE 2	//pin IO_C2
#define BRLINE 3	//pin IO_C3
// Pins that the line sensors are attached to
// TR = Top Right, BR = Bottom Right etc...
#define SHARP_L 6	//ADC6
#define SHARP_R 4	//pc4, also connected to trimpot

#define THRESHOLD 600 //TODO: define this

#define NUM_SAMPLES 10
double distanceL, distanceR;

volatile int sensorCheck;


char getlines();
char avoid_edge();
char find_robot_sharp();

int sharp_distance();
int find_robot_sonar();

// abhinav 
// pin1 is TL
// pin2 is TR
// pin0 is BL
// pin3 is BR
