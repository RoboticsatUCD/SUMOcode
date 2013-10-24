#include "print.h"
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
