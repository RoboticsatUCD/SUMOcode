void forward(void)
{
  set_motor_speed(pin, 2000);
  set_motor_speed(pin2,2000);
}

void reverse(void)
{
  set_motor_speed(pin, 1000);
  set_motor_speed(pin2,1000);
} 

void turnright(int degrees)
{
  float coefficient = 1;
  set_motor_speed(pin, 2000);
  set_motor_speed(pin, 1000);
  delay(coefficient * degrees);
  set_motor_speed(pin, 1500);
  set_motor_speed(pin, 1500);
}
 
void turnleft(int degrees)
{
  float coefficient = 1.0;
  set_motor_speed(pin, 1000);
  set_motor_speed(pin, 2000);
  delay(coefficient * degrees);
  set_motor_speed(pin, 1500);
  set_motor_speed(pin, 1500);
}