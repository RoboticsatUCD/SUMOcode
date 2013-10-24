void pulse(int pin, int duration)
{
  set_digital_output(pin, HIGH)
  delay_us(duration)
  set_digital_output(pin, LOW) 
}
