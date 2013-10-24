#include <stdio.h>
#include <stdlib.h>

#include "robot.h"
#include "simulator.h"

int main()
{
	srand(time(NULL));
	
	add_robot(robot1, NULL);
	add_robot(robot2, NULL);
	start_simulator();
	
	return 0;
}
