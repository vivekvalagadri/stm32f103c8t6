/* Simple LED task demo, using timed delays:
 *
 * The LED on PC13 is toggled in task1.
 */
#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

extern void vApplicationStackOverflowHook(
	xTaskHandle *pxTask,
	signed portCHAR *pcTaskName);

void
vApplicationStackOverflowHook(
  xTaskHandle *pxTask __attribute((unused)),
  signed portCHAR *pcTaskName __attribute((unused))
) {
	for(;;);	// Loop forever here..
}

static void
task1(void *args __attribute((unused))) {

	for (;;) {
		gpio_toggle(GPIOC,GPIO13);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
static void
task2(void *args __attribute((unused))) {

	for (;;) {
		gpio_toggle(GPIOC,GPIO14);
		vTaskDelay(pdMS_TO_TICKS(50));
	}
}

int
main(void) {

	rcc_clock_setup_in_hse_8mhz_out_72mhz(); // For "blue pill"

	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(
		GPIOC,
		GPIO_MODE_OUTPUT_2_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL,
		GPIO13);
	gpio_set_mode(
		GPIOC,
		GPIO_MODE_OUTPUT_2_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL,
		GPIO14);

	xTaskCreate(task1,"LED",100,NULL,100,NULL);
	xTaskCreate(task2,"Led",100,NULL,1,NULL);
	vTaskStartScheduler();

	for (;;);
	return 0;
}

// End
