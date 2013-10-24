#define MOS1 IO_B1
#define MOS2 IO_B0
#define MOS3 IO_D2
#define MOS4 IO_D7
#define SONAR IO_B2
#define BAUD 115200
//unused: TODO: fill this line

#include <pololu/orangutan.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "motor.h"
#include "movements.h"
#include "sensor.h"

int main() {
    sensorCheck = 0;
    
	serial_set_baud_rate(BAUD);
	
	delay_ms(5000);
	
	while(1)
	{
		if(avoid_edge()==0)
			if(find_robot_sharp()==0)
				if(find_robot_sonar()==0)
					set_speed(255,-255);
	}

	return 0;
}

ISR(TIMER1_COMPA_vect) {
    if (sensorCheck != 0)
        stop();
}
