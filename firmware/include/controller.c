#include "controller.h"

uint32_t get_controller_status(volatile uint32_t controller_status) {
	if(controller_status){
    	if(controller_status & 0x1){				//left
    		return a;
		}
    	if(controller_status & 0x2){			//up
    		return w;
		}
		if(controller_status & 0x4){		// down
			return x;
		}
		if(controller_status & 0x8){		//right
			return d;
		}
		if(controller_status & 0x10){				//left
			return u;
		}
		if(controller_status & 0x20){			//up
			return i;
		}
		if(controller_status & 0x40){		// down
			return j;
		}
		if(controller_status & 0x80){		//right
			return k;
		}
	}
	return NONE;
}




