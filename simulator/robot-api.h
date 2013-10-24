#pragma once

// 0 -> simulator
// 1 -> real robot
#define SIMULATOR_CODE 0
#define ROBOT_CODE 1
#define ROBOT_CODE_TYPE SIMULATOR_CODE
// SIMULATOR
#if ROBOT_CODE_TYPE == SIMULATOR_CODE
#include "simulator.h"

// assumes common sizes for integral types
typedef signed char int8;
typedef short int16;
typedef int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
#endif

typedef enum
{
	FRONT_LEFT = 1,
	FRONT_RIGHT = 2,
	BACK_LEFT = 4,
	BACK_RIGHT = 8,

	NONE = 0,	
	FRONT = 3,
	BACK = 12,
	LEFT = 5,
	RIGHT = 10,
	ALL = 15,
} of_four_t;

typedef struct
{
	uint8 front_left;
	uint8 front_right;
	uint8 back_left;
	uint8 back_right;
} line_sensor_readings_t;


// initialize the robot! (this should always be called first)
// in the real robot, this should perform calibrations
void init_robot();
// turn wheels on/off (pass FRONT_LEFT or ALL, etc.)
void set_active_wheels(uint8 wheels);
// return clock ticks since program start (in units of 0.4us (microseconds))
//uint32 get_ticks();
// sleep a number of microseconds or milliseconds
void sleep_us(uint32 us);
// for a 32-bit unsigned number, it would take just over an hour
// to overflow the timer, we only actually implement sleep_us()
#define sleep_ms(ms) sleep_us((ms) * 1000);
#define sleep(s) sleep_us((s) * 1000000);
// fills readings with line-sensor values from 0 to 255
// read: unsigned char pololu_3pi_init(unsigned int line_sensor_timeout)
void read_line_sensors(line_sensor_readings_t * readings);

point_t offset_from_robot(robot_t * robot, double x, double y);

