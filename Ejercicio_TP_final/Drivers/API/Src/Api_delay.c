
#include "Api_delay.h"
void delayInit( delay_t * delay, tick_t duration ){
	assert(delay!= NULL);
 delay->duration= duration;
 delay->running=false;
}

bool_t delayRead( delay_t * delay ){
	assert(delay!= NULL);
	if((delay->running)==false ){
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}

	if(delay->running){
		if((HAL_GetTick()-(delay->startTime))>=delay->duration){
			delay->running = false;
		}
	}
return delay->running;

}
void delayWrite( delay_t * delay, tick_t duration ){
	assert(delay!= NULL);
	delay->duration = duration;
}
void nueva_cuenta(delay_t * delay)
{
	delay->startTime = HAL_GetTick();
}
