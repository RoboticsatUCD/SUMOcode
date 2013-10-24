//Turning functions for robot. Rotate causes the robot to rotate in place, while arc moves in an arc based on a given radius
//TODO get the setmotor function
//TODO add in proper while statements for being on the line.
//TODO add in the needed speed value in Arc.
//TODO calibrate const values as determined by the robot.
#include <pololu/3pi.h>
#define RIGHT 0
#define LEFT 1
#define RIGHT2 3
#define LEFT2 4
#define MINCHECKTIME 20
#define DESIREDTURNSPEED 100//adjust for more accurate turning

void Rotate(int direction,int degrees)//assumes direction given as 0,1,RIGHT,or LEFT
{
		const double needed_delay=degrees/360.0*1000000;  //change this as needed, I have no idea what the actual time should be. This assumes 1second=1 complete circle.
		if(direction){//turns left
			setmotor(RIGHT,DISEREDTURNSPEED);
			setmotor(LEFT,-DISEREDTURNSPEED);
			setmotor(RIGHT2,DISEREDTURNSPEED);
			setmotor(LEFT2,-DISEREDTURNSPEED);
			
			//while not on line and delay <neededDelay
			{
				delay_us(MINCHECKTIME);
			}
		}
		else{//turns right
			setmotor(RIGHT,-DISEREDTURNSPEED);
			setmotor(LEFT,DISEREDTURNSPEED);
			setmotor(RIGHT2,-DISEREDTURNSPEED);
			setmotor(LEFT2,DISEREDTURNSPEED);
			delay_us((int)needed_delay);//change this as needed, I have no idea what the actual time should be. This assumes 1second=1 complete circle.
		}
		//not sure if needed, just stops motors turning, may slow down bot, remove if unneccessary
		setmotor(RIGHT,0);
		setmotor(LEFT,0);
		setmotor(RIGHT2,0);
		setmotor(LEFT2,0);
	
}
 
void Arc(int direction,int radius, int degrees)//assumes radius given in cm and direction given as a 1 or 0 or right or left
{
		const double needed_speed=;//needs to be adjusted as necessary, as radius increases, the needed_speed should also increase, at radius=0,should be -DISEREDTURNSPEED, at radius->infinity should be DISEREDTURNSPEED
		const double needed_delay=radius+degrees/360.0*1000000;//change as needed
		if(direction){//turns left
			setmotor(RIGHT,DISEREDTURNSPEED);
			setmotor(LEFT,(int)needed_speed);//as the desired radius increases
			setmotor(RIGHT2,DISEREDTURNSPEED);
			setmotor(LEFT2,(int)needed_speed);//as the desired radius increases
			//while not on line and delay <neededDelay
			{
				delay_us(MINCHECKTIME);
			}
		}
		else{
			setmotor(RIGHT,(int)needed_speed);
			setmotor(LEFT, DISEREDTURNSPEED); 
			setmotor(RIGHT2,(int)needed_speed);
			setmotor(LEFT2,DISEREDTURNSPEED);
			//while not on line and delay <neededDelay
			{
				delay_us(MINCHECKTIME);
			}
		}
		//not sure if needed, just stops motors turning, may slow down bot, remove if unneccessary
		setmotor(RIGHT,0);
		setmotor(LEFT,0);
		setmotor(RIGHT2,0);
		setmotor(LEFT2,0);	
}