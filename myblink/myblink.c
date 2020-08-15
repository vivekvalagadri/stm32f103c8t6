#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void gpio_setup(void){

	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO13);
	gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO14);
}
int main(){
	gpio_setup();
	while(1){
		gpio_clear(GPIOC,GPIO14);
		for(int i=0;i<1500000;i++)
			__asm__("nop");
		gpio_set(GPIOC,GPIO14);
		for(int i=0;i<1500000;i++)
			__asm__("NOP");
		gpio_clear(GPIOC,GPIO13);
		for(int i=0;i<15000000;i++)
			__asm__("nop");
		gpio_set(GPIOC,GPIO13);
		for(int i=0;i<15000000;i++)
			__asm__("NOP");
	}
	return 0;
}

