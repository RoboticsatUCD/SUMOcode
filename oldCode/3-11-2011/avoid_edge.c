void avoid_edge(int status)
{
  int response;
//  response = edge_status();
  response = status;
  if (4 == response)
    reverse();
  else if (-4 == response)
    forward();
  else if (response < 0)
    turn_right(135 * (-1 * response / 3));
  else if (response > 0)
    turn_left(135 * (response / 3));
}