#include "line.h"

int getLines()
{
	int result = 1;
	if(analog_read(TLLINE)<LINE_THRESHOLD)
		result *= 2;
	if(analog_read(TRLINE)<LINE_THRESHOLD)
		result *= 3;
	if(analog_read(BLLINE)<LINE_THRESHOLD)
		result *= 5;
	if(analog_read(BRLINE)<LINE_THRESHOLD)
		result *= 7;
	return result;
}
int avoid_edge()
{
	int status = getLines();
	if(status == 1)//no lines were sensed
		return 0;
	switch(status)
	{
		case 2://TL triggered
			set_speed(255,-255); //spin CW(from top view)
			//delayMicroseconds(20); //we'll see if we need this short delay
			break;
		case 3://TR triggered
			set_speed(-255,255); //spin CCW
			break;
		case 5://BL triggered
			set_speed(-255,255); //spin CCW
			break;
		case 7://BR triggered
			set_speed(255,-255); //spin CW
			break;
		case 6://Top triggered
			set_speed(-255,-255);//get the fuck back
			break;
		case 10://Left triggered
			set_speed(255,205);
			break;
		case 35://Bottom triggered
			set_speed(255,255); //get the fuck forward
			break;
		case 21://Right triggered
			set_speed(205,255);
			break;

	}
	return status;
}