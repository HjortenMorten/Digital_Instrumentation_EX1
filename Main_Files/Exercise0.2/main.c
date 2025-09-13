#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
int main(void)
{
uart_init( 9600 ); // Initialize USB serial emulation at 9600 baud
printf("Hello World!\n"); // Show the world you are alive!
while(1){}
}
