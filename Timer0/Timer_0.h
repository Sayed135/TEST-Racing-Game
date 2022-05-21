#ifndef TIMER_0_H
#define TIMER_0_H

typedef enum {

  Timer_16,
	Timer_32 =4
	


}Timer0_cfg;

typedef enum{
	count_down,
	count_up
	
}count_mode;

typedef enum{
	one_shot=1,
	periodic,
	capture

}T_mode;

typedef enum{
	
	LOW,
	HIGH
}enable;

void Timer0A_Handler(void);
void Timer0_Init(void(*task)(void), unsigned long period,Timer0_cfg mode, count_mode  count,T_mode TAMR_mode );




void Timer_Periodic_Function(void (*periodic));


#endif 