#define SHARP_L 6
#define SHARP_R 4
#define BAUD 115200
#define NUM_SAMPLES 10

#include <pololu/orangutan.h>

int distance_sharp() {
    char count;
    
    double sumLeft, sumRight, distance;
    
    distance = sumLeft = sumRight = 0.0;
    
    for (count = 0; count < NUM_SAMPLES; count++) {
        sumLeft += analog_read_millivolts(SHARP_L);
        delay_us(4);
        sumRight += analog_read_millivolts(SHARP_R);
        delay_us(4);
    }
    
    if (sumLeft > sumRight)
        distance = sumLeft / NUM_SAMPLES;
    else
        distance = sumRight / NUM_SAMPLES;
    
    distance = (12818.0 / (distance + 358.88)) + 1.0;
    
    return distance;
}

/*
	Function will print out character array, the first length amount of characters, without adding and newlines or carriage returns.
*/
void print_to_serial(char *arr, int length)
{
	serial_send_blocking(arr, length);
}

void print_new_line()
{
	char arr[2] = {'\n','\r'};
	serial_send_blocking(arr, 2);
}

/*
	Function will print positive and negative integers up to 4 digits
*/
void print_int(int i)
{
	char arr[5] = {'0','0','0','0','0'};
	if(i < 0)
	{
		arr[0] = '-';
		i = -i;
	}
	arr[4] = '0' + (i % 10);
	i /=10;
	arr[3] = '0' + (i % 10);
	i /=10;
	arr[2] = '0' + (i % 10);
	i /=10;
	arr[1] = '0' + (i % 10);
	print_to_serial(arr, 5);
}


int main() {
    serial_set_baud_rate(BAUD);
    
    int distanceRead;
    
    while(1) {
    	set_m1_speed(255/4);
	set_m2_speed(255/4);
	MOS2
	MOS4
    }
    return 0;
}
