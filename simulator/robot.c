#include "robot.h"

// This is where the robot functions go!
// Robot functions are void functions like so: void robot() {...}
// Every function in this file should only call
//   functions defined in "robot-api.h" and "robot.h"!!!

void robot1()
{
	line_sensor_readings_t line_sensors;
	
	init_robot();
	for(;;)
	{
		read_line_sensors(&line_sensors);
		set_active_wheels(ALL);
		for(; line_sensors.front_left < 128; read_line_sensors(&line_sensors));
		set_active_wheels(RIGHT);
		sleep_us(1 * 1000 * 1000);
	}
}

void robot2()
{
	line_sensor_readings_t line_sensors;
	
	init_robot();
	for(;;)
	{
		read_line_sensors(&line_sensors);
		set_active_wheels(ALL);
		for(; line_sensors.front_left < 128; read_line_sensors(&line_sensors));
		set_active_wheels(LEFT);
		for(; line_sensors.front_left > 128; read_line_sensors(&line_sensors));
		for(; line_sensors.front_left < 128; read_line_sensors(&line_sensors));
		for(; line_sensors.front_left > 128; read_line_sensors(&line_sensors));
	}
}
