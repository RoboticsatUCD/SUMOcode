/*
  -1________4_______ 1
   | pin1      pin2 |
   |                |
   |                |
 -2|                | 2
   |                |
   |                |
   |                |
  -3_pin0______pin3_ 3
          -4
 pin0
 pin1
 pin2
 pin3
 */
int edge_status(void){

 int pin0, pin1, pin2, pin3;
  pin0 = is_digital_input_high(pin_zero);
  pin1 = is_digital_input_high(pin_one);
  pin2 = is_digital_input_high(pin_two);
  pin3 = is_digital_input_high(pin_three);
  
  if (pin1 && pin2)
    return 4;
  if (pin2 && pin3)
    return 2;
  if (pin3 && pin0)
    return -4;
  if (pin0 && pin1)
    return -2;
  if (pin0)
    return -3;
  if (pin1)
    return -1;
  if (pin2)
    return 1;
  if (pin3)
    return 3;
}
