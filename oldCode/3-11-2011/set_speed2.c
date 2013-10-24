#include <pololu/orangutan.h>
#include <stdio.h>  //is this needed?

//define ports
#define wheel1   "some_port"
#define wheel2   "some_port2"
#define wheel3   "some_port3"
#define wheel4   "some_port4"

//function declaration
void mSpeed(char*, double);

int main()
{
	mspeed(wheel1, 100);	 //sample function calling
	
	return(0);
}

/*This function takes in "wheel1", "wheel2", "wheel3", or "wheel4"
 * and speed between -100 and 100; -100 full reverse, 100 full forward,
 * 0 for stop
 * as paramters and set motor speed as output
 */
void mSpeed(char* wheelnum, double speed)
{
	if(speed != 0) //wheels in forward or backward
	{
		speed = (speed * 5.0) + 1500.0; //convert -100 to 100 to								apporiate speed
	}
	else //speed = 0 -> stop
	{
		speed = 1500.0;
	}

	set_digital_output(wheelnum, HIGH);
	delay_us(speed);
	set_digitial_output(wheelnum, LOW);
} 
