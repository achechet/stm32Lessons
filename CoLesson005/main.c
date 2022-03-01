typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;

#define F_CPU 72000000		// Тактовая частота от ST-LINK 8MHz, PLL:ON, PLLMUL:0111 input clock x9

//------------------------------------------------------------------------------------------------
#define RCC_AHBENR  (*(volatile unsigned long *)0x40021014)  // AHB peripheral clock enable register
#define GPIOE_MODER (*(volatile unsigned long *)0x48001000) // GPIO port mode register
#define GPIOE_ODR 	(*(volatile unsigned long *)0x48001014)     	// GPIO port output data register
//-------------------------------------------------------------------------------------------------
// Port A enable Включить clock to POrt A
// AHB peripheral clock enable register (RCC_AHBENR)
// Address offset: 0x14
// Bit 17 IOPAEN: I/O port A clock enable
// Set and cleared by software.
// 0: I/O port A clock disabled
// 1: I/O port A clock enabled
// 	RCC_AHBENR 	|= 1<<17;	//Port A clock enable
#define GPIOA_MODER 	(*(volatile unsigned long *)0x48000000)     	// GPIO port output data register
#define GPIOA_AFRH  (*(volatile unsigned long *)0x48000024)     	// GPIO alternate function high register
#define RCC_APB2ENR  (*(volatile unsigned long *)0x40021018) 		// APB2 peripheral clock enable register

// ---------------------------------------------------------------------------------------------------------

#define USART_CR1  (*(volatile unsigned long *)0x40013800) 		// Control register 1 (USART_CR1)
#define USART_BRR  (*(volatile unsigned long *)0x4001380C) 		// USART_BRR baud rate register
#define USART_ISR  (*(volatile unsigned long *)0x4001381C) 		// Interrupt and status register
#define USART1_TDR  (*(volatile unsigned long *)0x40013828) 		// Data transmit register

//----------------------------------------------------------------------------------------------------------
// Прототипы функций
void _delay(uint32_t);	// Задержка
uint8_t _strlen(const char* str);


//-------------------------------------------------------------------------------------------------

int main(void)
{
	RCC_AHBENR 	|= 1<<21;	//Port E clock enable
	RCC_AHBENR 	|= 1<<17;	//Port A clock enable

	GPIOE_MODER |= (0<<31|1<<30);	// Output mode
	GPIOE_MODER |= (0<<29|1<<28);	// Output mode

	// USART1_TX.PA9 Altenative function 7
	GPIOA_MODER |= (1<<19|0<<18);	// PA9 in alternative mode
	GPIOA_AFRH |= (0<<7|1<<6|1<<5|1<<4); // GPIO alternate function high register AF7 for PA9
	// USART1 init
	RCC_APB2ENR |= 1<<14; 		// Включить тактирование на USART1
	// Настроить регистры самого USART-a
	USART_BRR = 0x1D4C; // будет 9600
	// Bit 0 UE: USART enable
	USART_CR1 |= 1<<0; 	// USART1 enable
	USART_CR1 |= 1<<3;  // Transmitter enable

unsigned char txData[] = "Start program\n"; // Строка из 13 символов

	for (int i = 0; i < _strlen(txData);) {

		while(!(USART_ISR & (1<<7)));		// Ждем когда освобидится TDR
		USART1_TDR = txData[i];
		i++;
	}

    while(1)
    {
    	// if (USART_ISR & (1<<7)) USART1_TDR = 0x41;	// Передаем байт
    	GPIOE_ODR 	|= 1<<15;		// PE15 High level
    	GPIOE_ODR 	&= ~(1<<14);		// PE14 High level
    	_delay(2000000);
    	GPIOE_ODR 	|= 1<<14;		// PE14 High level
    	GPIOE_ODR 	&= ~(1<<15);		// PE15 High level
    	_delay(2000000);
    }
}
//--------------------------------------------------------------------------------------------------

// Задержка
void _delay(uint32_t index){
	while(index--);
}
/*
uint8_t _strlen(const char* str) {
	int lenght = 0;
	while(*str++) ++lenght;
	return lenght;
}
 */

uint8_t _strlen(const char* str) {
	return (*str) ? _strlen(++str) + 1:0;
}
