
#define RCC_AHBENR  (*(volatile unsigned long *)0x40021014)  // AHB peripheral clock enable register
#define GPIOE_MODER (*(volatile unsigned long *)0x48001000) // GPIO port mode register
#define GPIOE_ODR 	(*(volatile unsigned long *)0x48001014)     	// GPIO port output data register




int main(void)
{
	RCC_AHBENR 	|= 1<<21;	//Port E clock enable

	GPIOE_MODER |= (0<<31|1<<30);	// Output mode
	GPIOE_ODR 	|= 1<<15;		// PE15 High level

	GPIOE_MODER |= (0<<29|1<<28);	// Output mode
	GPIOE_ODR 	|= 1<<14;		// PE15 High level
    while(1)
    {


    }
}
