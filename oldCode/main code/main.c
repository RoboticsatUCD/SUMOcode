//pin assignments
#define TLLINE 0	//pin IO_C0 //need to put in channels instead of pins for analog functions
#define TRLINE 1	//pin IO_C1
#define BLLINE 2	//pin IO_C2
#define BRLINE 3	//pin IO_C3
#define MOS1 IO_B0
#define MOS2 IO_B1
#define MOS3 IO_D7
#define MOS4 IO_D2
#define SHARP_1 6	//ADC6
#define SHARP_2 4	//pc4, also connected to trimpot
#define SONAR IO_B2
#define BAUD 115200
#define LINE_THRESHOLD 600 //TODO: define this
//unused: TODO: fill this line


#include <pololu/orangutan.h>
#include "motor.c"
#include "print.c"
#include "line.c"
/*
	TODO list
	sensors
		line
		IF sensors
		sonar
	motor control
		wrappers
		degree turn
	anything else
*/

void init()
{
	serial_set_baud_rate(BAUD);
	//delay_ms(5000);
}
int main()
{
	init();
	int pot;
	//char test_arr[6] = {'t','e','s','t','\n','\r'};
	while(1)
	{
		if(avoid_edge()==0)
			//if(find_robot_sharp()==0)
			//	if(find_robot_sonar==0)
					set_speed(255,-255);
		pot = analog_read(7)/2-256;
		print_int(pot);
		print_new_line();
		set_speed(pot, pot);
	}

	return 0;
}
