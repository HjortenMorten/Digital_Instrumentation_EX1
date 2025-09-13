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

void initLed(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE); // Enable clock for GPIO Port C
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE); // Enable clock for GPIO Port A
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE); // Enable clock for GPIO Port B
	//Setup Red PB4 as output
	GPIO_StructInit(&GPIO_InitStructAll);
	GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as output
	GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP; // Set as Push-Pull
	GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_4; // Set so the configuration is on pin 0
	GPIO_Init(GPIOB, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen
	//Setup green PC7 as output
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_7; // Set so the configuration is on pin 4
	GPIO_Init(GPIOC, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen
	//Setup blue PA9 as output
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_9; // Set so the configuration is on pin 5
	GPIO_Init(GPIOA, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

}

void setLed(uint8_t joystick){
	if(joystick == 0){ //When no input from joystick no color
		GPIO_WriteBit(GPIOB,GPIO_Pin_4,1);
		GPIO_WriteBit(GPIOC,GPIO_Pin_7,1);
		GPIO_WriteBit(GPIOA,GPIO_Pin_9,1);
	}else if(joystick == 1){ //When up Red
		GPIO_WriteBit(GPIOB,GPIO_Pin_4,0);
	}else if(joystick == 2){ //When down Green
		GPIO_WriteBit(GPIOC,GPIO_Pin_7,0);
	}else if(joystick == 4){ //When left blue
		GPIO_WriteBit(GPIOA,GPIO_Pin_9,0);
	}else if(joystick == 8){ //When right white
		GPIO_WriteBit(GPIOB,GPIO_Pin_4,0);
		GPIO_WriteBit(GPIOC,GPIO_Pin_7,0);
		GPIO_WriteBit(GPIOA,GPIO_Pin_9,0);
	}
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
	data += GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) << 0; //Up 1
	data += GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) << 1; //Down 2
	data += GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) << 2; //Left 4
	data += GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0) << 3; //Right 8
	data += GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5) << 4; //Center 16
	return data;
}

int main(void){
	uart_init(9600);
	initJoystick();
	initLed();
	uint8_t A;
	while(1){
		A = readJoystick();
		setLed(A);
	}
}
