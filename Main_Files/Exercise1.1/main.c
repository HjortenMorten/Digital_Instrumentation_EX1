#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
GPIO_InitTypeDef GPIO_InitStructAll;

void initJoystick(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE); // Enable clock for GPIO Port C
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE); // Enable clock for GPIO Port A
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE); // Enable clock for GPIO Port B

	//Setup PC0 as input
	GPIO_StructInit(&GPIO_InitStructAll);
	GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_IN; // Set as input
	GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_DOWN; // Set as pull down
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_0; // Set so the configuration is on pin 0
	GPIO_Init(GPIOC, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	//Setup PA4 as input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_4; // Set so the configuration is on pin 4
	GPIO_Init(GPIOA, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	//Setup PB5 as input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_0; // Set so the configuration is on pin 5
	GPIO_Init(GPIOB, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	//Setup PC1 as input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_0; // Set so the configuration is on pin 1
	GPIO_Init(GPIOC, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	//Setup PB0 as input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_0; // Set so the configuration is on pin 0
	GPIO_Init(GPIOB, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen
}


//bit 0: 1 if the joystick is pressed up, 0 otherwise
//bit 1: 1 if the joystick is pressed down, 0 otherwise
//bit 2: 1 if the joystick is pressed left, 0 otherwise
//bit 3: 1 if the joystick is pressed right, 0 otherwise
//bit 4: 1 if the joystick is pressed center, 0 otherwise
//bit 5-7: 0
//PC0 (right), PA4 (up), PB5 (center), PC1 (left), and PB0 (down).
uint8_t readJoystick(){
	uint8_t data = 0;
	data += GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) << 0; //Up
	data += GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) << 1; //Down
	data += GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) << 2; //Left
	data += GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0) << 3; //Right
	data += GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5) << 4; //Center
	return data;
}

int main(void)
{
	uart_init(9600);
	initJoystick();
	uint8_t A;
	uint8_t B;
	while(1){
		A = readJoystick();
		if(A != B){
			printf("%8d",A);
		}
		B = A;
	}
}
