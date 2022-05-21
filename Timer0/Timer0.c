#include "../../../tm4c123gh6pm11.h"
#include "..//TM4C123GH6PM.h"
#include "Timer_0.h"

#define SYSCTL_RCGCTIMER_R      (*((volatile unsigned long *)0x400FE604))
#define NVIC_PRI4_R             (*((volatile unsigned long *)0xE000E410))
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))
#define TIMER_ICR_TBTOCINT      0x00000100  // GPTM Timer B Time-Out Interrupt
#define TIMER_ICR_TATOCINT      0x00000001  // GPTM Timer A Time-Out Raw

TIMER0_Type * TIMER0_cfg =(TIMER0_Type *) TIMER0_BASE;



void (*PeriodicTask)(void);   // user function

// ***************** Timer0_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer0_Init(void(*task)(void), unsigned long period,Timer0_cfg mode, count_mode  count,T_mode TAMR_mode ){
	
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
  PeriodicTask = task;          // user function
  TIMER0_cfg->CTL  |= LOW;    // 1) disable TIMER0A during setup	
	TIMER0_cfg->CFG =mode ;    // 2) configure for n-bit mode (32)
   
	TIMER0_cfg->TAMR |= (count<<4)|(TAMR_mode<<0); // 3) configure for periodic mode
  
	TIMER0_cfg->TAILR =period-1;  // 4) reload value
                                 	
	TIMER0_cfg->TAPR |=LOW;   // 5) bus clock resolution

	TIMER0_cfg->ICR |=HIGH;   // 6) clear TIMER0X timeout flag
    
	TIMER0_cfg->IMR |=HIGH;   // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized

  NVIC_EN0_R = HIGH<<19;           // 9) enable IRQ 19 in NVIC
   
	TIMER0_cfg->CTL |=HIGH;      // 10) enable TIMER0X


}


void Timer0A_Handler(void){
	
  TIMER0_cfg->ICR = TIMER_ICR_TATOCINT;
	// acknowledge TIMER0A timeout
  (*PeriodicTask)();                // execute user task
}
