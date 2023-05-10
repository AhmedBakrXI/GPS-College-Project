/*
* Name: Mohaned Khaled Hassan Hassan
* ID : 2001372
* Username (GitHub) : MohanadKhh
*/

#ifndef LCD_H_
#define LCD_H_

#define Clear                0x01          // replace all characters with ASCII 'space'
#define HOME                 0x02          // return cursor to first position on first line
#define DisplayOn            0x0F          // display on & cursor blink
#define Set5x7FontSize    	 0x20		   // set font size to 5x7
#define four_bit_mode		 0x28	       // select 4-bit mode
#define ROW_1                0x80          // set cursor position in first row
#define ROW_2           	 0xC0          // set cursor position in second row
#define CURSOR_ON            0x0E		   // Cursor on
#define ENABLE			     0x04		   // lcd enable
#define REG_SEL				 0x01		   // register select
#define Entry                0x06          // shift cursor from left to right on read/write


void InitializeLCD(void);
void Command(unsigned char cmd);
void SEND_4BITS(unsigned char c, unsigned char ctrl);



//********************************
//************************************
//*****************************************





/* 
 Name: Abdelrahman Ahmed Abdelrahman Mahrous
 ID:2001760
 Username: Abdelrahman-Ahmed-Abdelrahman (GitHub)


*/
void DISPLAY_CHAR(unsigned char data, unsigned char ctrl);
void DISPLAY_STRING( char *str);
void LCD_intgerToString(double data);


#endif



