/*
* Name : Mohaned Khaled Hassan Hassan
* ID : 2001372
* Username (GitHub) : MohanadKhh
*/

#include "lcd.h"
#include "tm4c123gh6pm.h"
#include "systick.h"
#include "stdio.h"

/*This Method sets up the LCD display by sending a series of commands to it,
including setting the font size, communication protocol, entry mode, clearing the display,
and turning on the display. This function is typically called once at the beginning of a program
to initialize the LCD display before text is written to it.
*/
void InitializeLCD(void){ 			 //Method name "InitializeLCD" with no input parameter and no return value.
    Command(Set5x7FontSize);	//This command is used in setting font size to 5 pixels wide by 7 pixels tall.
    Command(four_bit_mode);
    Command(Entry);		//This line sends command to the LCD display. which determines the direction that text will be written to the screen that was from left to right
    Command(Clear);			//This command clears the display and sets the cursor position to the top-left corner.
    Command(DisplayOn);		//This line sends the "DisplayOn" command to the LCD display. This command turns on the display and enables the cursor to be displayed if desired.
}



/*
This Method sends commands to the LCD display in 4-bit mode by calling the "SEND_4BITS" function twice,
first with the four most significant bits of the command and then with the four least significant bits of the command.
The function also includes a delay to account for the longer processing times required for certain commands.
*/
void Command(unsigned char cmd){	//Method name "Command" with an input parameter "cmd" of unsigned character data type.
    
	SEND_4BITS(cmd & 0xF0, 0);
	/*
	This line calls a function "SEND_4BITS" with two input parameters "cmd & 0xF0" and "0".
	The first parameter is a bitwise AND operation of "cmd" with "0xF0", which sets the four least significant bits of "cmd" to 0.
	This is done because the LCD display is in 4-bit mode, and only the four most significant bits of the command need to be sent first.
	The second parameter "0" is used to indicate that the data being sent is a command, not data.
	*/
		
    SEND_4BITS(cmd<<4, 0);
	/*
	This line calls the same function "SEND_4BITS" with two input parameters "cmd<<4" and "0".
	The first parameter shifts the four most significant bits of "cmd" to the left by 4 bits,
	effectively discarding them and bringing the four least significant bits to the front.
	This is done because the LCD display is in 4-bit mode and expects the four most significant bits of a command to be sent first.
	The second parameter "0" is used to indicate that the data being sent is a command, not data.
	*/
	
    if(cmd < 4){
        DelayMilli(2);
    }
    else{
        DelayMicro(40);
    }
	/*
	The if statement block of code checks if the command being sent is one of four specific commands (0, 1, 2, or 3).
	If it is, the function waits for 2 milliseconds before continuing, otherwise it waits for 40 microseconds.
	This is because these four commands require longer processing times by the LCD display
	,so the function needs to wait longer before sending the next command.
	*/
}



/*
This Method writes data or commands to the LCD display in 4-bit mode
by sending the four most significant bits of the data or command followed by the four least significant bits.
The Method uses a delay to allow the LCD display to process the data or command and sets the "EN" bit to enable the LCD display to receive the data or command.
*/
void SEND_4BITS(unsigned char c, unsigned char ctrl){	//Method name "SEND_4BITS" with two input parameters "c" and "ctrl" of unsigned character data type.
	
    c &= 0XF0;
	/*
	This line performs a bitwise AND operation of "c" with the hexadecimal value "0xF0",
	which sets the four least significant bits of "c" to 0.
	This is done because the LCD display is in 4-bit mode,
	and only the four most significant bits of the data or command need to be sent first.
	*/
	
    ctrl &= 0x0F;
	/*
	This line performs a bitwise AND operation of "ctrl" with the hexadecimal value "0x0F",
	which sets the four most significant bits of "ctrl" to 0.
	This is done to ensure that the control bits are only the four least significant bits of the "GPIO_PORTB_DATA_R" variable,
	as the upper four bits may be used Data or command.
	*/
	
    GPIO_PORTB_DATA_R = c | ctrl;
	/*
	This line sets the "GPIO_PORTB_DATA_R" variable to the bitwise OR operation of "c" and "ctrl".
	This sends the four most significant bits of the data or command to the LCD display and raise the edge of data.
	*/
	
    GPIO_PORTB_DATA_R = c | ctrl | ENABLE;		//Raise the edge of enable
    DelayMicro(1);				//This line adds a 1 microsecond delay to the function. This is done to allow the LCD display to process the data or command.
    GPIO_PORTB_DATA_R = c;		//This sends the four least significant bits of the data or command to the LCD display.
    GPIO_PORTB_DATA_R = 0;		//This is done to disable the "EN" bit and signal the end of the data or command transmission.
}

******************************
**********************************
*************************************
****************************************

/*
* Name: Abdelrahman Ahmed Abdelrahman Mahrous
*ID: 2001760
*Username: Abdelrahman-Ahmed-Abdelrahman (GitHub)
*/
void DISPLAY_CHAR(unsigned char data, unsigned char ctrl){		//Method name "DISPLAY_CHAR" with two input parameters "data" and "ctrl" of unsigned character data type.
    
	SEND_4BITS(data&0xF0, REG_SEL);
	/*
	This line calls the "SEND_4BITS" function to write the four most significant bits of "data" to the LCD display.
	The "RS" parameter indicates that this is a data write operation, rather than a command write operation.
	*/
	
    SEND_4BITS(data<<4, REG_SEL);
	/*
	This line calls the "SEND_4BITS" function to write the four least significant bits of "data" to the LCD display.
	The "RS" parameter indicates that this is a data write operation, rather than a command write operation.
	*/
	
    DelayMicro(40);	//This line adds a 40 microsecond delay to the function. This is done to allow the LCD display to process the character data.
}



/*
This Method writes a string to the LCD display character-by-character by calling the "DISPLAY_CHAR" function in a loop.
The function uses a character pointer to iterate through the string,
and stops writing when it reaches the end of the string (indicated by the null terminator character '\0').
*/
void DISPLAY_STRING( char *str){	//Method name "DISPLAY_STRING" with one input parameter "str" of character pointer data type.
    int i;	//integer variable "i" which will be used as the loop counter.
	
    for( i = 0; *str!=0; i++){
        DISPLAY_CHAR(*(str++),REG_SEL);
    }
	/*
	for loop that initializes "i" to 0, and continues iterating while the value pointed to by "str" is not equal to 0.
	This means that the loop will continue as long as there are more characters in the string to be written.
	*/
}



/*
this function converts a double precision floating point number to a string using the sprintf function
and displays the resulting string on an LCD display using the "DISPLAY_STRING" function.
The resulting string is stored in a character array called "buff" which has a size of 16 characters.
*/
void LCD_intgerToString(double data)	//Method name "LCD_intgerToString" with one input parameter "data" of double data type.
{
    char buff[16];  //An array of characters called "buff" with a size of 16. This array will be used to hold the resulting string.
	
    sprintf(buff, "%f", data);
/*
This line converts the floating point number "data" to a string representation and stores in the "buff" array.
The "%f" format tells it to format the floating point number as a decimal number with six digits after the decimal point.
*/

    DISPLAY_STRING(buff);		// Display the resulting string on the LCD display.
}








