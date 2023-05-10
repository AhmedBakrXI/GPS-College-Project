/*
 *@ Author: Ahmed Eissa Mahfouz
 *  ID:2001725
 *  Username:AhmedEissaeng
 *@ Author: Karim Mostafa Mohamed Roshdy Nabhan 
 *  ID:2001563
 *  Username: karimnabhan
*/
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))  // Enable the clock for Port F
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))  // Unlock Port F
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))  // Allow changes to Port F pins
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))  // Disable/enable  analog mode for Port F pins
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))  // Set Port F pins as GPIO or if we will use it as UART , etc
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))  // Set Port F pins as outputs/inputs based on if its 1 (output )  or 0 (input)
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))  // alternate function for Port F pins
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))  // pull-up resistors for Port F pins
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))  // to define Port f as digital if they are set to 1 
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))  // Read or write the value of Port F pins
// Define LED color codes
#define RED     0x02  // Assign Red to value 0x02 i.e pin 1  which the the location of the pin connected to the red led 
#define BLUE    0x04  // Assign blue to value 0x04 i.e pin 2 which the the location of the pin connected to the blue led 
#define GREEN   0x08  // Assign Green to value 0x08 i.e pin 3 which the the location of the pin connected to the green led 
#define PINK    0X06  // Assign Pink to value 0x06 
#define YELLOW  0X0A  // Assign yellow to value 0x010 we got it by adding red and green
#define SKY     0X0C  // Assign Sky to value 0x0C
#define WHITE   0X0E  // Assign white to value 0x0E
//Prototypes
/* initializes Port F by enabling the clock, unlocking the port, configuring the pins as GPIO, disabling analog mode,
enabling pull-up resistors, and enabling digital functions. It does not take any arguments and does not return a value.
*/
void PortF_Init(void);
/* initializes Port B by enabling the clock, unlocking the port, configuring the pins as GPIO, disabling analog mode,
enabling pull-up resistors, and enabling digital functions. It does not take any arguments and does not return a value.
*/
void PortB_Init(void);
/*the RGB_ON function turns on an LED with the specified color by setting the appropriate bits in the GPIO_PORTF_DATA_R register. 
It takes one argument, color, which is an unsigned char representing the desired LED color. The function does not return a value.
*/

unsigned int PortF_Input(void);
void RGB_ON(unsigned char color);

