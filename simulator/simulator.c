#include "simulator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "robot-api.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define SCR_WIDTH 800 // default width/height
#define SCR_HEIGHT 600 


volatile robot_t robots[MAX_ROBOTS];
pthread_t robot_threads[MAX_ROBOTS];
int robots_size = 0;

double cosd(double x)
{
	return cos(x * M_PI / 180.0);
}

double sind(double x)
{
	return sin(x * M_PI / 180.0);
}


#define RGB(r, g, b) ((color_t){(r), (g), (b)})
color_t rainbowColor(int n)
{
	// red -> orange -> yellow
	if(n < 0x100) return RGB(255, n, 0);
	// yellow -> green
	if(n < 0x100 * 2) return RGB((0x100 * 2 - 1) - n, 255, 0);
	// green -> teal
	if(n < 0x100 * 3) return RGB(0, 255, n - (0x100 * 2 - 1));
	// teal -> blue
	if(n < 0x100 * 4) return RGB(0, (0x100 * 4 - 1) - n, 255);
	// blue -> purple
	if(n < 0x100 * 5) return RGB(n - (0x100 * 4 - 1), 0, 255);
	// purple -> red
	if(n < 0x100 * 6) return RGB(255, 0, (0x100 * 6 - 1) - n);
	// poop
	return rainbowColor(n % 1536);
}


GLfloat randFloat()
{
	return (GLfloat)rand() / RAND_MAX;
}

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitWindowPosition(50, 100);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutCreateWindow("UCD Robot Simulator");
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, RING_WIDTH, 0, RING_WIDTH);
}

void handle_mouse(int button, int state, int x, int y)
{

}

void handle_resize(int w, int h)
{
	double dispW, dispH;
	
	if(w < h)
	{
		dispW = 0.0;
		dispH = RING_WIDTH - RING_WIDTH * w / h ;
	}
	else
	{
		dispW = RING_WIDTH - RING_WIDTH * h / w ;
		dispH = 0.0;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-dispW - RING_WIDTH / 2.0, RING_WIDTH / 2.0 + dispW, 
		-dispH - RING_WIDTH / 2.0, RING_WIDTH / 2.0 + dispH);
	
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void draw()
{
	int j;
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	// draw white circle (large)
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0, 0.0);
		for(j = 0; j <= 360; j += 5)
		{
			glVertex2f(cosd(j) * RING_WIDTH / 2.0, sind(j) * RING_WIDTH / 2.0);
		}
	glEnd();
	
	// draw black circle
	glColor3f(0.05, 0.05, 0.05);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0, 0.0);
		for(j = 0; j <= 360; j += 5)
		{
			glVertex2f(cosd(j) * RING_INNER_WIDTH / 2.0, 
				sind(j) * RING_INNER_WIDTH / 2.0);
		}
	glEnd();
	
	// draw Shikiri Lines
	glColor3f(0.5, 0.164, 0.164);
	glBegin(GL_QUADS);
		glVertex2f(10.0, -10.0);
		glVertex2f(10.0, 10.0);
		glVertex2f(12.0, 10.0);
		glVertex2f(12.0, -10.0);
		glVertex2f(-10.0, -10.0);
		glVertex2f(-10.0, 10.0);
		glVertex2f(-12.0, 10.0);
		glVertex2f(-12.0, -10.0);
	glEnd();
	
	// draw robots
	for(j = 0; j < robots_size; j++)
	{
		glPushMatrix();
		glTranslatef(robots[j].pos.x, robots[j].pos.y, 0.0);
		glRotatef(robots[j].rot, 0.0, 0.0, 1.0);
		glColor3f(0.9, 0.9, 0.9);
		glBegin(GL_QUADS);
			glVertex2f(-robots[j].width / 2.0, -robots[j].width / 2.0);
			glVertex2f(-robots[j].width / 2.0, robots[j].width / 2.0);
			glVertex2f(robots[j].width / 2.0, robots[j].width / 2.0);
			glVertex2f(robots[j].width / 2.0, -robots[j].width / 2.0);
		glEnd();
		glColor3ubv(&robots[j].color.r);
		glBegin(GL_TRIANGLES);
			glVertex2f(-robots[j].width / 2.0, robots[j].width / 2.0);
			glVertex2f(robots[j].width / 2.0, 0.0);
			glVertex2f(-robots[j].width / 2.0, -robots[j].width / 2.0);
		glEnd();
		glPopMatrix();
	}
	
	glFlush();
}

// returns true (!0) if the point is "inside" the robot
// TODO: make this function accurate!
int point_in_robot(robot_t * robot, point_t * point)
{
	double radius = magnitude(robot->pos.x - point->x, robot->pos.y - point->y);
	return radius < robot->width * SQRT_2;
}

void iterate(int value)
{
	int j, k;
	// ITERATIONS_PER_SEC is used to divide
	const double ITERATIONS_PER_SEC = 1000.0 / value;
	
	// call this function again in value milliseconds
	glutTimerFunc(value, iterate, value);
	
	// detect and resolve collisions
	// note: for simplicity, we assume that there are only 2 robots in the ring
	for(j = 1; j < robots_size; j++)
	{
		for(k = 0; k < j; k++)
		{
			double avg_width = (robots[j].width + robots[k].width) / 2.0;
			// if there's a collision between robots[j] and robots[k]
			if(magnitude(robots[j].pos.x - robots[k].pos.x, robots[j].pos.y - robots[k].pos.y) < avg_width)
			{
				point_t robot_j_corner;
				double half_j_width = robots[j].width / 2.0;
				
				robot_j_corner = offset_from_robot(&robots[j], half_j_width, half_j_width);
				if(point_in_robot(&robots[k], &robot_j_corner))
				{
					// place code to figure out where the robots hit, now that we know there's a collision
				}
			}
		}
	}
	
	// update robots positions and angle (with the velocity and angular velocity)
	for(j = 0; j < robots_size; j++)
	{
		// If the robot's angular velocity is great enough, use a more accurate model
		if(fabs(robots[j].rotv) < 10.0)
		{
			robots[j].pos.x += robots[j].v * cosd(robots[j].rot) / ITERATIONS_PER_SEC;
			robots[j].pos.y += robots[j].v * sind(robots[j].rot) / ITERATIONS_PER_SEC;
		}
		else
		{
			robots[j].pos.x += robots[j].v * 180.0 / M_PI 
				* (sind(robots[j].rotv / ITERATIONS_PER_SEC + robots[j].rot) 
				- sind(robots[j].rot)) / robots[j].rotv;
			robots[j].pos.y += robots[j].v * 180.0 / M_PI 
				* (-cosd(robots[j].rotv / ITERATIONS_PER_SEC 
				+ robots[j].rot) + cosd(robots[j].rot)) / robots[j].rotv;
		}
		robots[j].rot += robots[j].rotv / ITERATIONS_PER_SEC;
	}
}

void redraw(int value)
{
	// call this function again in value milliseconds
	glutTimerFunc(value, redraw, value);
	draw();
}

void new_robot(robot_t * robot, int id)
{
	robot->v = 0.0;
	robot->rotv = 0.0;
	robot->width = 20.0; // 20 centimeters
	robot->mass = 3.0; // 3 kilograms
	
	if(id == 0)
	{
		robot->pos.x = -12.5 - robot->width / 2.0;
		robot->pos.y = 0.0;
		robot->rot = 0.0;
		robot->color = (color_t){255, 0, 0};
	}
	else if(id == 1)
	{
		robot->pos.x = 12.5 + robot->width / 2.0;
		robot->pos.y = 0.0;
		robot->rot = 180.0;
		robot->color = (color_t){0, 0, 255};
	}
	else
	{
		robot->pos.x = 0.0;
		robot->pos.y = 0.0;
		robot->rot = randFloat() * 360.0;//0.0;
		robot->color = rainbowColor(rand() % 1536);
	}
}

int robot_id()
{
	int j;
	pthread_t self;
	self = pthread_self();
	for(j = 0; j < robots_size; j++)
	{
		if(pthread_equal(self, robot_threads[j]))
			return j;
	}
	return -1;
}

robot_t * get_robot()
{
	int id = robot_id();
	if(id == -1)
		return NULL;
	return (robot_t *) &robots[id];
}

point_t offset_from_robot(robot_t * robot, double x, double y)
{
	point_t result;
	double rcosd = cosd(robot->rot);
	double rsind = sind(robot->rot);
	
	result.x = robot->pos.x + rcosd * y + rsind * x;
	result.y = robot->pos.y + -rcosd * x + rsind * y;
	
	return result;
}

void * run_simulator(void * ptr)
{
	srand(time(NULL));
	
	int dummy_argc = 0;
	glutInit(&dummy_argc, NULL);

	init();
	glutDisplayFunc(draw);
	glutMouseFunc(handle_mouse);
	glutReshapeFunc(handle_resize);
	iterate(1000 / 100);
	redraw(1000 / 30);
	
	glutMainLoop();
	
	return NULL;
}

void start_simulator()
{
	//pthread_t thread;
	//pthread_create(&thread, NULL, run_simulator, NULL);
	run_simulator(NULL);
}

// this actually starts the robot thread
void * start_robot(void * robot_controller_ptr)
{
	void (*robot_controller)() = (void (*)()) robot_controller_ptr;
	printf("Robot started\n");
	robot_controller();
	printf("ERR: robot_controller() exited\n");
	return NULL;
}

// this creates a thread for the robot that we're adding and starts it
int add_robot(void (*robot_controller)(), robot_t * robot)
{
	robot_t default_robot;
	
	if(robots_size >= MAX_ROBOTS || robot_controller == NULL)
		return 0;
	
	if(robot == NULL)
	{
		robot = &default_robot;
		new_robot(robot, robots_size);
	}
	robots[robots_size] = *robot;
	if(pthread_create(&robot_threads[robots_size], NULL, start_robot, robot_controller))
		return 0;
	robots_size++;
	
	return 1;
}
