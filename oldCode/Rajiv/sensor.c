#include "sensor.h"

char getLines() {
	char result = 1;
	
	if(analog_read(TLLINE)<THRESHOLD)
		result *= 2;
	if(analog_read(TRLINE)<THRESHOLD)
		result *= 3;
	if(analog_read(BLLINE)<THRESHOLD)
		result *= 5;
	if(analog_read(BRLINE)<THRESHOLD)
		result *= 7;
	return result;
}

char avoid_edge() {
    sensorCheck = 1;
	char status = getLines();
	
	if(status == 1)//no lines were sensed
		return 0;

	switch(status) {
		case 2://TL triggered
		    //spin CW(from top view)
            set_speed(255,-255);
			//delayMicroseconds(20); //we'll see if we need this short delay
			break;
		case 3://TR triggered
			//spin CCW
            set_speed(-255, 255);
			break;
		case 5://BL triggered
			//spin CCW
            set_speed(-255,255);
			break;
		case 7://BR triggered
			//spin CW
            set_speed(255,-255);
			break;
		case 6: //Top triggered
			//get the fuck back
            set_speed(-255,-255);
			break;
		case 10://Left triggered
            set_speed(255,205);
			break;
		case 35://Bottom triggered
			//get the fuck forward
            set_speed(255,255);
			break;
		case 21://Right triggered
            set_speed(205,255);
			break;
		default:
		set_speed(255,-255);
		return 0;
			break;
	}
	
    sensorCheck = 0;
	return status;
}

int sharp_distance() {
    int count;
    
    double sumLeft, sumRight, distance;
    
    distanceL = distanceR = sumLeft = sumRight = 0.0;
    
    for (count = 0; count < NUM_SAMPLES; count++) {
        sumLeft += analog_read_millivolts(SHARP_L);
        delay_us(4);
        sumRight += analog_read_millivolts(SHARP_R);
        delay_us(4);
    }
    
	distanceL = sumLeft / NUM_SAMPLES;
	distanceR = sumRight / NUM_SAMPLES;
    
    if(distanceL < distanceR)
    	distance = distanceL;
    else
    	distance = distanceR;
    
    distance = (12818.0 / (distance + 358.88)) + 1.0;
    
    return (int)distance;
}

char find_robot_sharp() {
    sensorCheck = 1;
	int result = sharp_distance();
	if(result > 18)
		return 0;
	if(distanceL < 15 && distanceR>18)
		turn(RIGHT, 10, 255);
	if(distanceR < 15 && distanceL>18)
		turn(LEFT, 10, 255);
	if(distanceL < 15 && distanceR < 15)
		set_speed(255,255);
	
    sensorCheck = 0;
	return 1;
}

int find_robot_sonar() {
    // set designated pin as output
    // send pulse to get
    return 0;
}
