#ifndef SOURCE_GPIO_H_
#define SOURCE_GPIO_H_

#include "gpio_cfg.h"

typedef enum gpio_ret_e{
	
	GPIO_RET_OK,
	GPIO_RET_NOT_OK
	
}gpio_Ret_t;


typedef enum gpio_Pin_e{
	
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7

} gpio_Pin_t;

typedef enum gpio_Port_e{
	
	
	GPIO_PORT_A,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_E,
	GPIO_PORT_F,
	
	
} gpio_Port_t;

typedef enum gpio_Dir_e{
	
	GPIO_DIR_INPUT,
	GPIO_DIR_OUTPUT
	
} gpio_Dir_t;

typedef enum gpio_DigAngSel_e{
	
	GPIO_MODE_DIGITAL,
	GPIO_MODE_ANALOG
	
} gpio_DigAngSel_t;

typedef enum gpio_Enable_e{
	
	GPIO_DISABLE,
	GPIO_ENABLE
	
}gpio_Enable_t;

typedef struct gpio_PinConfig_s{
	  gpio_DigAngSel_t pinDigAngSel;
	  gpio_Dir_t     pinDir;
	  gpio_Enable_t  pinPullUp; 
	  gpio_Enable_t  pinPullDown;
	 gpio_Enable_t   pinAFSEL;
}gpio_PinConfig_t;

typedef struct gpio_PortConfig_s{
	
	gpio_PinConfig_t pinsCfg[MAX_PIN_NUM];
	
}gpio_PortConfig_t;

typedef struct gpio_Configurations_s{
	
	gpio_PortConfig_t  portsCfg[MAX_PORT_NUM];
	
}gpio_Configurations_t;


gpio_Ret_t Gpio_Init( gpio_Configurations_t* gpioCfgs);
gpio_Ret_t Gpio_DigAngSel(gpio_Port_t portNum, gpio_Pin_t pinNum, gpio_DigAngSel_t digangsel);
gpio_Ret_t Gpio_PullUp(gpio_Port_t portNum, gpio_Pin_t pinNum, gpio_Enable_t pur);
gpio_Ret_t Gpio_PullDown(gpio_Port_t portNum, gpio_Pin_t pinNum, gpio_Enable_t pdr);
#endif
