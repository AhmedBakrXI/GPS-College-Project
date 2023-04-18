/*
 *
 *@ Author: Muhammed ahmed abd-elgawad nassif 2001771
 *	ID:2001771
 * Username: Muhammed-nassif
 * Date: 18/4/2023
 *	Time: 6:00 PM
 *
 */
 
//*****************************************************************************
//
// NVIC used registers (NVIC)
//
//*****************************************************************************
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))		//Control register
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))		// Reload register
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))		// Current value register

// Prototypes
void SysTick_Init(void);
void delay_us(int count);
void delay_ms(int count);
