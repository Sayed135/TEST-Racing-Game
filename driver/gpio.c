#include "gpio.h"
#include "../TM4C123GH6PM.h"
#include "MATH_LIB.h"
extern gpio_Configurations_t portsCfgs;


GPIOA_Type * GPIO_PORTS_REGS [6]={(GPIOA_Type *)GPIOA_BASE, (GPIOA_Type *)GPIOB_BASE,(GPIOA_Type *)GPIOC_BASE,(GPIOA_Type *)GPIOD_BASE,(GPIOA_Type *)GPIOE_BASE,(GPIOA_Type *)GPIOF_BASE};
unsigned int pt[6]={1,0,0,0,1,0};
unsigned int pn[6][8]={
{0,0,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0}	
};
//Initializing all gpio ports with port valuse from gpio_cfg.c
gpio_Ret_t Gpio_Init( gpio_Configurations_t* gpioCfgs){
	
	int portNum=0; int pinNum=0;
	  for( portNum=0; portNum < MAX_PORT_NUM ;portNum++){
				if(!pt[portNum])continue;
			     
				GPIO_PORTS_REGS[portNum]->LOCK=0x4C4F434B;
				pinNum=0;
			for( pinNum=0; pinNum < MAX_PIN_NUM ;pinNum++){
				   if(!pn[portNum][pinNum])continue;
				   SET_BIT( GPIO_PORTS_REGS[portNum]->CR,pinNum);
				   					 GPIO_PORTS_REGS[portNum]->PCTL=0x00000000;		
					 
				   if(gpioCfgs->portsCfg[portNum].pinsCfg[pinNum].pinDir== GPIO_DIR_INPUT){
						 CLEAR_BIT( GPIO_PORTS_REGS[portNum]->DIR,pinNum);
					 }else if(gpioCfgs->portsCfg[portNum].pinsCfg[pinNum].pinDir== GPIO_DIR_OUTPUT){
						 SET_BIT( GPIO_PORTS_REGS[portNum]->DIR,pinNum);
					 }else{
						 return GPIO_RET_NOT_OK;}
					 
					 if(gpioCfgs->portsCfg[portNum].pinsCfg[pinNum].pinPullUp== GPIO_ENABLE){
							SET_BIT( GPIO_PORTS_REGS[portNum]->PUR,pinNum);
					 }else if(gpioCfgs->portsCfg[portNum].pinsCfg[pinNum].pinPullUp== GPIO_DISABLE){
						 	CLEAR_BIT( GPIO_PORTS_REGS[portNum]->PUR,pinNum);
					 }else{
						 return GPIO_RET_NOT_OK;}
						
						 if(gpioCfgs->portsCfg[portNum].pinsCfg[pinNum].pinPullDown== GPIO_ENABLE){
							SET_BIT( GPIO_PORTS_REGS[portNum]->PDR,pinNum);
					 }else if(gpioCfgs->portsCfg[portNum].pinsCfg[pinNum].pinPullDown== GPIO_DISABLE){
						 	 	CLEAR_BIT( GPIO_PORTS_REGS[portNum]->PDR,pinNum);
					 }else{
						 return GPIO_RET_NOT_OK;} 
					 
					  if(gpioCfgs->portsCfg[portNum].pinsCfg[pinNum].pinDigAngSel== GPIO_MODE_DIGITAL){
							SET_BIT( GPIO_PORTS_REGS[portNum]->DEN,pinNum);
							CLEAR_BIT( GPIO_PORTS_REGS[portNum]->AMSEL,pinNum);
					 }else if(gpioCfgs->portsCfg[portNum].pinsCfg[pinNum].pinDigAngSel== GPIO_MODE_ANALOG){
						 	CLEAR_BIT( GPIO_PORTS_REGS[portNum]->DEN,pinNum);
							SET_BIT( GPIO_PORTS_REGS[portNum]->AMSEL,pinNum);
					 }else{
						 return GPIO_RET_NOT_OK;}
					 
						 
		}
		}
	
	return GPIO_RET_OK;
}

gpio_Ret_t  Gpio_DigAngSel(gpio_Port_t portNum, gpio_Pin_t pinNum, gpio_DigAngSel_t digangsel){
	       GPIO_PORTS_REGS[portNum]->LOCK=0x4C4F434B;
	       SET_BIT(GPIO_PORTS_REGS[portNum]->CR,pinNum);
				 if(digangsel== GPIO_MODE_DIGITAL){
							SET_BIT(GPIO_PORTS_REGS[portNum]->DEN,pinNum);
							CLEAR_BIT(GPIO_PORTS_REGS[portNum]->AMSEL,pinNum);
					 }else if(digangsel== GPIO_MODE_ANALOG){
						 	CLEAR_BIT(GPIO_PORTS_REGS[portNum]->DEN,pinNum);
							SET_BIT(GPIO_PORTS_REGS[portNum]->AMSEL,pinNum);
					 }else{
						 return GPIO_RET_NOT_OK;}
					 
				 return GPIO_RET_OK;

}

gpio_Ret_t  Gpio_PullUp(gpio_Port_t portNum, gpio_Pin_t pinNum, gpio_Enable_t pur){
	
	         GPIO_PORTS_REGS[portNum]->LOCK=0x4C4F434B;
	       SET_BIT(GPIO_PORTS_REGS[portNum]->CR,pinNum);
	         if(pur== GPIO_ENABLE){
							SET_BIT(GPIO_PORTS_REGS[portNum]->PUR,pinNum);
					 }else if(pur== GPIO_DISABLE){
						 	CLEAR_BIT(GPIO_PORTS_REGS[portNum]->PUR,pinNum);
					 }else{
						 return GPIO_RET_NOT_OK;}
	
	
					 return GPIO_RET_OK;

}

gpio_Ret_t  Gpio_PullDown(gpio_Port_t portNum, gpio_Pin_t pinNum, gpio_Enable_t pdr){
	
	         GPIO_PORTS_REGS[portNum]->LOCK=0x4C4F434B;
	         SET_BIT(GPIO_PORTS_REGS[portNum]->CR,pinNum);
	         if(pdr== GPIO_ENABLE){
							SET_BIT(GPIO_PORTS_REGS[portNum]->PDR,pinNum);
					 }else if(pdr== GPIO_DISABLE){
						 	CLEAR_BIT(GPIO_PORTS_REGS[portNum]->PDR,pinNum);
					 }else{
						 return GPIO_RET_NOT_OK;}
	
	
					 return GPIO_RET_OK;

}
