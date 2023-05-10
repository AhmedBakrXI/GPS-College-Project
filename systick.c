/*
 *
 *@ Author: Muhammed ahmed abd-elgawad nassif 
 *  ID:2001771
 *  Username: Muhammed-nassif
 *
 */
 
#include "systick.h"

/******************************************* 
 * Function: SysTick timer initialization
 * Parameters : void
 * Return type: void
 *
 ******************************************/
void SYSTICK_ENABLE(void){
	NVIC_ST_CTRL_R = 0;					// Disable systick timer
	NVIC_ST_RELOAD_R = 80-1;		// Load 80 counts to reload register for 1 microsecond count
	NVIC_ST_CURRENT_R = 0;			// Clear the counter 
	NVIC_ST_CTRL_R = 5;					// Enable the counter and system CLK 
}

/******************************************/
/*
 * This function delays n microsecond by looping while count flag is not set
 * Parameters : void
 * Return type: void
 */
void DelayMicro(int count){
	int i = 0;
	while(i!=count){
		while((NVIC_ST_CTRL_R&0x10000)==0){}		// Loop while count flag is down
		i++;
	}
}

/******************************************/
/* 
 * This function loops for n milli second
 * Parameters : void
 * Return type: void
 */
void DelayMilli(int count){
	int i =0;
	while(i<(count*1000)){
		DelayMicro(1);								// loop for count milliseconds
		i++;
	}
}
/************** END OF FILE *****************/
