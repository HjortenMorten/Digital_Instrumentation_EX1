#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
GPIO_InitTypeDef GPIO_InitStructAll;



int main(void){
	uart_init(9600);
	uint8_t a = 10;
	char str[7];
	sprintf(str, "a = %2d", a);
	printf("%s\n",str);
}
