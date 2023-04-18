/*
 *
 *@ Author: Muhammed ahmed abd-elgawad nassif 
 *  ID:2001771
 *  Username: Muhammed-nassif
 *  Date: 18/4/2023
 *  Time: 6:00 PM
 *
 */
 
#include "systick.h"

/******************************************* 
 * Function: SysTick timer initialization
 * Parameters : void
 * Return type: void
 *
 ******************************************/
void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;					// Disable systick timer
	NVIC_ST_RELOAD_R = 80-1;		// Load 80 counts to reload register for 1 microsecond count
	NVIC_ST_CURRENT_R = 0;			// Clear the counter 
	NVIC_ST_CTRL_R = 5;					// Enable the counter and system CLK 
}

/******************************************/
/* Function: Delays n microsecond
 * Parameters : void
 * Return type: void
 */
void delay_us(int count){
	int i;
	for( i = 0; i<count; i++){
		while((NVIC_ST_CTRL_R&0x10000)==0){}		// Loop while count flag is down
	}
}

/******************************************/
/* Function: Delays n millisecond
 * Parameters : void
 * Return type: void
 */
void delay_ms(int count){
	int i ;
	for( i = 0; i<(count*1000); i++){
		delay_us(1);		// 1 us								// loop for count milliseconds
	}
}
/************** END OF FILE *****************/
