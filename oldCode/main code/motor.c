#include "motor.h"

void turn_right(int degrees) {
	stop();
}

void turn_left(int degrees){
	stop();
}

void set_speed(int speed, int speed2) {
	if (speed == 0 && speed2 == 0)//if command is to stop motors
		stop();
	else{
		//this section handles motor1
		if((speed > 0 && currentM1Speed > 0) || (speed < 0 && currentM1Speed < 0))
		{
			set_m1_speed(speed);
			currentM1Speed = speed;
		}
		else
		{//definitely switching direction
			if(speed == 0)
				stop_m1();
			else if (speed > 0) {
				set_digital_output(MOS2, HIGH);
				delayMicroseconds(2);
				set_digital_output(MOS1, LOW);
				set_m1_speed(speed);
			}
			else { // speed has to be < 0
				set_digital_output(MOS1, HIGH);
				delayMicroseconds(2);
				set_digital_output(MOS2, LOW);
				set_m1_speed(speed);
			}
			currentM1Speed = speed;	
		}
		
		//this section is motor 2
		if((speed2 > 0 && currentM2Speed > 0) || (speed2 < 0 && currentM2Speed < 0))
		{
			set_m2_speed(speed2);
			currentM2Speed = speed2;
		}
		else{
			if(speed2 == 0)
				stop_m2();
			else if (speed2 > 0) {
				set_digital_output(MOS4, HIGH);
				delayMicroseconds(2);
				set_digital_output(MOS3, LOW);
				set_m2_speed(speed2);
			}
			else { // speed has to be < 0
				set_digital_output(MOS3, HIGH);
				delayMicroseconds(2);
				set_digital_output(MOS4, LOW);
				set_m2_speed(speed2);
			}
			currentM2Speed = speed2;
		}
	}
}

// just needed for turning, might as well delete these and use turn_right turn_left

// may not need separate stop functions for each motor
void stop_m1() {
	set_m1_speed(0);
	currentM1Speed = 0;
	set_digital_output(MOS1, HIGH);
	set_digital_output(MOS2, HIGH);
}

void stop_m2() {
	set_m2_speed(0);
	currentM2Speed = 0;
	set_digital_output(MOS3, HIGH);
	set_digital_output(MOS4, HIGH);
}

void stop() {
	set_m1_speed(0);
		currentM1Speed = 0;
	set_m2_speed(0);
		currentM2Speed = 0;
	set_digital_output(MOS1, HIGH);
	set_digital_output(MOS2, HIGH);
	set_digital_output(MOS3, HIGH);
	set_digital_output(MOS4, HIGH);
}