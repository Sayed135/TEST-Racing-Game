// This is your first program to run on the LaunchPad
// You will run this program without modification as your Lab 2
// If the left switch SW1 is 
//      not pressed the LED toggles blue-red
//      pressed the LED toggles blue-green

// 0.Documentation Section 
// main.c
// Runs on LM4F120 or TM4C123
// Lab2_HelloLaunchPad, Input from PF4, output to PF3,PF2,PF1 (LED)
// Authors: Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi
// Date: January 15, 2016

// LaunchPad built-in hardware
// SW1 left switch is negative logic PF4 on the Launchpad
// SW2 right switch is negative logic PF0 on the Launchpad
// red LED connected to PF1 on the Launchpad
// blue LED connected to PF2 on the Launchpad
// green LED connected to PF3 on the Launchpad

// 1. Pre-processor Directives Section
// Constant declarations to access port registers using 
// symbolic names instead of addresses
#include "TExaS.h"
 #include "../TM4C123GH6PM.h"
#include "MATH_LIB.h"

#include "gpio.h"
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
	
#define GPIO_PORTS_RE ((GPIOA_Type *) GPIOA_BASE)
extern gpio_Configurations_t portsCfgs;
	gpio_Ret_t x;
GPIOA_Type * GPIO_PORTS_REG [6]={(GPIOA_Type *)0x40004000, (GPIOA_Type *)0x40005000,(GPIOA_Type *)0x40006000,(GPIOA_Type *)0x40007000,(GPIOA_Type *)0x40024000,(GPIOA_Type *)0x40025000};

volatile unsigned long delay;
void PortE_Init(void);
int c;
/*
void Timer2_Init(unsigned long period){ 
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TimerCount = 0;
  Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}*/

int main(void){
	SYSCTL_RCGC2_R |= 0x000000FF;
	delay = SYSCTL_RCGC2_R;     
  GPIO_PORTE_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
	// delay   
  

 x= Gpio_Init(&portsCfgs);
//PortE_Init();
//	SET_BIT( GPIO_PORTS_REG[1].DIR,0);
//	SET_BIT( GPIO_PORTS_REG[1].DEN,0);
//	CLEAR_BIT( GPIO_PORTS_REG[1].AMSEL,0);
	while(1){
		
	//  (GPIO_PORTS_REG+ sizeof(GPIOA_Type) )->DATA= (1<<1);
		
		 GPIO_PORTE_DATA_R=(1<<3);
			
	}
}

void PortE_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTE_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTE_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTE_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R = 0x0f;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
 GPIO_PORTE_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTE_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTE_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}
// Color    LED(s) PortF

void Delay(void){unsigned long volatile time;
  time = 727240*200/91;  // 0.1sec
  while(time){
		time--;
  }
}

