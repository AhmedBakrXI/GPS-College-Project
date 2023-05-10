// Name :Ahmed Samir Tharwat 
// ID:2000217

#include "tm4c123gh6pm.h"
#include "UART.h"

//Function that Intialize UART5 of Port E
// It is Necessary to Send or Recieve Any Data of I/O ports
void UART5_init(void){
    SYSCTL_RCGCUART_R |= (1<<5); // Enable UART5 clock
    SYSCTL_RCGCGPIO_R |= (1<<4); // Enable GPIOE clock
    while((SYSCTL_PRGPIO_R & (1<<4)) == 0){}; // Wait for GPIOE clock to be ready

    UART5_CTL_R =0;     // Disable UART5

    UART5_IBRD_R = 520; // Set integer baud rate divisor = INT(80M/16*BAUD)
    UART5_FBRD_R = 53; // Set fractional baud rate divisor =(80M/16*BAUD- INT(16M/16*BAUD))*64+0.5

    UART5_LCRH_R = 0X0070; // Set line control (8 bits data, 1 stop bit, no parity)
    UART5_CTL_R = 0X0301; // Enable UART5 and its transmitter and receiver
    GPIO_PORTE_AFSEL_R |= (1<<4) | (1<<5); // Enable alternate function for PE4 and PE5
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) + 0x00110000; // Configure PE4 and PE5 for UART
    GPIO_PORTE_DEN_R |= 0X30; // Enable digital function for PE4 and PE5
    GPIO_PORTE_AMSEL_R &= ~0X30; // Disable analog function for PE4 and PE5

    GPIO_PORTE_DIR_R |= (1<<5); // Set PE5 as output
    GPIO_PORTE_DIR_R &= ~(1<<4); // Set PE4 as input
}


/*
Mohammed Magdy Mahrous
2000927
*/

// Function that send char
void SEND_BYTE(char c){
		// checking full Flag 
  	// while RXFF full , Busy wait 
		// Until Data Register is empty
    while((UART5_FR_R & 0x20) != 0);
		// put the character whish will be sent in the Data Register
	  UART5_DR_R = c;
}

// Function that Recieve char
char RECEIVE_BYTE(){
	  // checking Empty Flag 
	  // while RXFE Empty , Busy wait 
	  // Until recieving Data 
    while((UART5_FR_R&0x10)!=0);
	 // return the Recieved Data  
    return (char)(UART5_DR_R&0xFF);
}


/*
Mostafa hessin ahmed qenawy
2000931
*/


// Function that Recieve str
void RECEIVE_STRING(char* str, int length){
        char c;  	
				int i;	
        for ( i = 0; i < length; ++i) // looping on  the string
        {
            /* code */
            c = RECEIVE_BYTE();          // recieving each character from  the string 
																				 // put the recieved character at Char c
            str[i] = c;									 // put the recieved Character in the location of pointer to char 
				}
}

// Function that send str
void SEND_STRING(char* str){
			while(*str){											// checking the pointer to char not empty
					SEND_BYTE(*str);							// send the char which the pointer points to it
				str++;													// increasing the pointer to point to the next char of the string
				}																// then going to check the condition again
}
