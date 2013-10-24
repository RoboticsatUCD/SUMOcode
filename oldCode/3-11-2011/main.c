#include <pololu/orangutan.h>
#include <pololu/3pi.h>
#include <pololu/qtr.h>
#include <pololu/encoders.h>

int main(void){
  int strategy = 1;
  int status = 0;
  while(strategy){
    if(status = edge_status() && status != 0){
	  avoid_edge(status);
	}
    else if(status = push_status() && status != 0){
	  maneuver(status);
	}
	else{
      strategy = search_algorithm();
	  if (strategy == 2)
        strategy = stalemateAKAhide();
    }
	status = 0;
  }
  return 0;
}