#include "motor.h"

void turn(int direction, int degrees, int speed) {
    int timerCount;
    float something; // something is just a variable to carry the 
                     // timer count calculations in
    
    stop();
    
    // initialize timer1
    cli();
    // set timer registers to 0
    TCCR1A = 0;
    TCCR1B = 0;
    
    // calculate desired timer count
    something = (float) degrees/360;
    something = (float) something * 0.13199;
    something = something / 0.0000128;
    timerCount = (int) something;
    
    // set compare match register to timer count
    OCR1A = timerCount;
    
    // turn on compare timer count (CTC) mode
    TCCR1B |= (1 << WGM12);
    // set CS12 bit for 256 prescaler
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    
    // enable global interrupts
    sei();
    
    if (direction == RIGHT) {
        set_speed(speed, -1*speed);
    }
    else if (direction == LEFT) {
        set_speed(-1*speed, speed);
    }
}

void set_speed(int speed, int speed2) {
    // stop() if speed is 0 for both motors
	if (speed == 0 && speed2 == 0)
		stop();
	else{
		// this section handles motor1
		if((speed > 0 && currentM1Speed > 0) || (speed < 0 && currentM1Speed < 0)) {
			set_m1_speed(speed);
			currentM1Speed = speed;
		}
		else {
			if(speed == 0)
				stop_m1();
			else if (speed > 0) {
				set_digital_output(MOS1, LOW);
				delayMicroseconds(2);
				set_digital_output(MOS2, HIGH);
				set_m1_speed(speed);
			}
			else { // speed has to be < 0
				set_digital_output(MOS2, LOW);
				delayMicroseconds(2);
				set_digital_output(MOS1, HIGH);
				set_m1_speed(speed);
			}
			currentM1Speed = speed;	
		}
		
		//this section is motor 2
		if((speed2 > 0 && currentM2Speed > 0) || (speed2 < 0 && currentM2Speed < 0)) {
			set_m2_speed(speed2);
			currentM2Speed = speed2;
		}
		else {
			if(speed2 == 0)
				stop_m2();
			else if (speed2 > 0) {
				set_digital_output(MOS3, LOW);
				delayMicroseconds(2);
				set_digital_output(MOS4, HIGH);
				set_m2_speed(speed2);
			}
			else { // speed has to be < 0
				set_digital_output(MOS4, LOW);
				delayMicroseconds(2);
				set_digital_output(MOS3, HIGH);
				set_m2_speed(speed2);
			}
			currentM2Speed = speed2;
		}
	}
}

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
