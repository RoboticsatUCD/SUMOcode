#pragma once

#include <pthread.h>
#include <GL/glut.h>

//#include "robot-api.h"

#define MAX_ROBOTS 20

#define RING_WIDTH 159.0 // battle-ring diameter in centimeters (including border)
#define RING_BORDER_WIDTH 5.0 // white border width in cm
#define RING_INNER_WIDTH (RING_WIDTH - RING_BORDER_WIDTH)

#define SQRT_2 1.4142135623730951

typedef struct
{
	double x, y;
} point_t;

typedef struct
{
	GLubyte r, g, b;
} color_t;

typedef struct
{
	point_t pos; // offset from robot center
	double rot; // offset angle from robots front (180 -> pointing backwards)
	double minViewDist;
	double maxViewDist;
	double viewAngle;
	//int delay_us; // microsecond delay to get a reading
} ir_ping_sensor_t;

typedef struct
{
	point_t pos; // position
	double v; // velocity
	double rot; // rotation
	double rotv; // rotational velocity
	double width; // width of the square robot (in cm)
	double mass; // mass in kilograms
	//double effective_mass;
	color_t color;
} robot_t;

extern volatile robot_t robots[MAX_ROBOTS];
extern pthread_t robot_threads[MAX_ROBOTS];
extern int robots_size;

int robot_id(); // index in the robots[] and robot_threads[] arrays
robot_t * get_robot(); // returns the pointer to the robot for the current thread
point_t offset_from_robot(robot_t * robot, double x, double y);

void start_simulator();
int add_robot(void (*robot_controller)(), robot_t * robot);

double cosd(double x);
double sind(double x);
