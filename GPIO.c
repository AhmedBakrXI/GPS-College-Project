




















void PortF_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20;     // enable clock for Port F
    while((SYSCTL_PRGPIO_R&0x02)==0) {}; //delay 
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock GPIO Port F
    GPIO_PORTF_CR_R = 0x1F;        // allow changes to PF4-0
    GPIO_PORTF_AMSEL_R = 0x00;     // disable analog function
    GPIO_PORTF_PCTL_R = 0x00000000; // GPIO clear bit PCTL
    GPIO_PORTF_DIR_R = 0x0E;       // PF1,PF2,PF3 outputs, PF0 and PF4 inputs
    GPIO_PORTF_AFSEL_R = 0x00;     // disable alternate functions
    GPIO_PORTF_PUR_R = 0x11;       // enable pull-up resistors on PF0 and PF4
    GPIO_PORTF_DEN_R = 0x1F;       // enable digital�pins�PF4-PF0
}

unsigned int PortF_Input(void)
{
	return (GPIO_PORTF_DATA_R&0x11);        // read PF4,PF0 inputs 
}
void RGB_ON(unsigned char colour){
	GPIO_PORTF_DATA_R = colour;	// Set�LED�to colour i.e if color is red the red led turns on
}

