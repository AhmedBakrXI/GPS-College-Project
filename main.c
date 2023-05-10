/*
 *
 * @author: Ahmed Mohammed Bakr Ahmed
 * ID: 2000037
 * UserName: AhmedBakrXI
 *
 */

#include "GPIO.h"
#include "systick.h"
#include "lcd.h"
#include "UART.h"
#include "gps.h"
extern volatile double latitude, longitude;
int main(){
	// Initialize all peripherals
    PortB_Init();
    PortF_Init();
    SYSTICK_ENABLE();
    UART5_init();
    InitializeLCD();
    Command(Clear);
    Command(HOME);
    DISPLAY_STRING("Welcome..");		// Display Welcome .. on lcd
    DelayMilli(500);					// Wait 500 ms
	while(1){
		Command(Clear);
		Command(HOME);
		GET_READINGS(); // get gps readings
		// if you reached end point diplay "Destination Reached!" & turn green led on
		if(latitude>=3003.84223&&longitude>=3116.74073){
			RGB_ON(GREEN);
			DISPLAY_STRING("Destination");
			Command(ROW_2);
			DISPLAY_STRING("Reached!");
			DelayMilli(500);
		// if you reached 5 meters before end point diplay "Continue .." & turn yellow led on
		}else if(latitude>=3003.8383&&longitude>=3116.73007){
			RGB_ON(YELLOW);
			DISPLAY_STRING("Continue ..");
			DelayMilli(500);
		// else diplay "Continue .." & turn red led on
		}else{
			RGB_ON(RED);
			DISPLAY_STRING("Continue ..");
			DelayMilli(500);
		}
	}
}
