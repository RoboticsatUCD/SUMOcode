#include "robot-api.h"

#if ROBOT_CODE_TYPE == SIMULATOR_CODE

#include <math.h>
#include <time.h>

void init_robot()
{
	sleep(2);
}

void set_active_wheels(uint8 wheels)
{
	robot_t * robot = get_robot();
	const double v = 10.0;
	const double rotv = 45.0;
	int num_active_wheels = (wheels & 1) + ((wheels & 2) >> 1) 
		+ ((wheels & 4) >> 2) + ((wheels & 8) >> 3);
	
	robot->rotv = robot->v = 0.0;
	if(wheels & FRONT_LEFT)
	{
		robot->v += v;
		robot->rotv -= rotv;
	}
	if(wheels & FRONT_RIGHT)
	{
		robot->v += v;
		robot->rotv += rotv;
	}
	if(wheels & BACK_LEFT)
	{
		robot->v += v;
		robot->rotv -= rotv;
	}
	if(wheels & BACK_RIGHT)
	{
		robot->v += v;
		robot->rotv += rotv;
	}
	robot->v *= num_active_wheels / 4.0;
}

void sleep_us(uint32 us)
{
	// note: this function relies on POSIX
	struct timespec t;
	t.tv_sec = us / 1000000;
	t.tv_nsec = 1000 * (us % 1000000);
	nanosleep(&t, &t);
}

inline double magnitude(double x, double y)
{
	return sqrt(x * x + y * y);
}

uint8 fake_line_sensor_reading(point_t pos)
{
	double d = magnitude(pos.x, pos.y);

	if(d <= RING_WIDTH / 2.0 && d >= RING_WIDTH / 2.0 - RING_BORDER_WIDTH)
		return 255;
	else
		return 0;
}

void read_line_sensors(line_sensor_readings_t * readings)
{
	robot_t * robot = get_robot();
	double half_width = robot->width / 2.0;
	
	// the sensors should (ideally) be 255 for white, 0 for black/brown
	readings->front_left = fake_line_sensor_reading(
		offset_from_robot(robot, -half_width, half_width));
	readings->front_right = fake_line_sensor_reading(
		offset_from_robot(robot, half_width, half_width));
	readings->back_left = fake_line_sensor_reading(
		offset_from_robot(robot, -half_width, -half_width));
	readings->back_right = fake_line_sensor_reading(
		offset_from_robot(robot, half_width, -half_width));
}
#elif ROBOT_CODE_TYPE == ROBOT_CODE
// This is where the robot code that actually runs on the robot goes
// (this is just code to call Pololu libraries)

#else
	#error Invalid ROBOT_CODE_TYPE
#endif
