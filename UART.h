/*
Mostafa hessin ahmed qenawy
2000931
*/

#ifndef UART_H_
#define UART_H_

void UART5_init(void);           // Function to initialise UART5 and GPIO for PE4 and PE5
void SEND_BYTE(char c);
char RECEIVE_BYTE(void);
void RECEIVE_STRING(char* str, int length);
void SEND_STRING(char* str);

#endif
