/**
 * @file main.c
 * @author Trevor Heyl trevor@planet3.co.za
 * @brief 
 * @version 0.1
 * @date 2022-06-20
 * 
 * MIT license
 * 
 * Sample Zephyr application using threads
 * 1) Create 2 threads,one statically and one dynamincally
 * 2) The one thread has as start delay but both run at the same rate to demonstrate the delayed start feature
 * 3) The tasks are created with kernel stacks due to  CONFIG_USERSPACE  not being enabled, the set of K_THREAD_STACK 
 * 			macros have an identical effect to the K_KERNEL_STACK macros.
 * 4) The threads run in supervisor mode (kernel space)
 * 
 */

#include <zephyr.h>
#include <drivers/gpio.h>


/**
 * @brief LED related definitions and declarations
 * 
 */
#define LEDRED_NODE 	DT_ALIAS(ledred)
#define LEDGREEN_NODE 	DT_ALIAS(ledgreen)

static const struct gpio_dt_spec ledred   = GPIO_DT_SPEC_GET(LEDRED_NODE, gpios);
static const struct gpio_dt_spec ledgreen = GPIO_DT_SPEC_GET(LEDGREEN_NODE, gpios);


/**
 * @brief Thread related declarations and definitions
 * 
 */
#define MY_STACK_SIZE 500
#define MY_PRIORITY 5

#define RED_LED_TASK_REPEAT		(1000)
#define GREEN_LED_TASK_REPEAT 	(1000)
#define TASK_START_DELAY		(3500)


void f_task_red_led(void *, void *, void *);

/**
 * @brief Create the red led task statically
 * 	 The task the same priority as any other task for this exmaple
 * 	the task is set to start delayed by TASK_START_DELAY_500ms
 */
K_THREAD_DEFINE(tid_red_led, MY_STACK_SIZE,
                f_task_red_led, NULL, NULL, NULL,
                MY_PRIORITY, 0, TASK_START_DELAY);

/**
 * @brief Construct a new thread stack
 * 	 The task will be created at run time dynamically
 */
K_THREAD_STACK_DEFINE(green_led_stack_area, MY_STACK_SIZE);
static struct k_thread tid_green_led;

/* the tasks/threads here.  */
void f_task_red_led(void * unused_1, void * unused_2, void * cunused_3) {

	while(1) {
			gpio_pin_toggle_dt(&ledred); /* */
			k_msleep(RED_LED_TASK_REPEAT); /* this also yields so other tasks can run */
	}

}

void f_task_green_led(void * unused_1, void * unused_2, void * cunused_3) {

	while(1) {
			gpio_pin_toggle_dt(&ledgreen); /* */
			k_msleep(GREEN_LED_TASK_REPEAT); /* this also yields so other tasks can run */
	}

}


/**
* init_failed()
* function called if there is any kind of zephyr initialisation problem
*/
void init_failed(void) {

	printk("Zephyr Init failed\n");
	while(1);  // Just a simple trap for errors
}

/**
 * @brief Check that all used hardware initialised ok
 * 
 */
void OS_checks( void) {
	int ret;

    /* Check if all devices initalised properly */
	if (!device_is_ready(ledred.port)) {
		init_failed();
	}
	if (!device_is_ready(ledgreen.port)) {
		init_failed();
	}

	/* make all led pins output */
	ret = gpio_pin_configure_dt(&ledred, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		init_failed();
	}

	ret = gpio_pin_configure_dt(&ledgreen, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		init_failed();
	}
}

/**
* main()
*/
void main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD);

	OS_checks();

	/* Create the green led task dynamically */
	k_thread_create(&tid_green_led, green_led_stack_area,
			K_THREAD_STACK_SIZEOF(green_led_stack_area),
			f_task_green_led, NULL, NULL, NULL,
			MY_PRIORITY, 0, K_FOREVER); /* k_FOREVER mean dont start the task yet */

	/* start the tasks */
	k_thread_start(tid_red_led);
	k_thread_start(&tid_green_led);

	/***** Main loop  ******/
	/* The OS is running but main is also a task so the code below also runs */
	/* If we dont have code after starting the tasks then it seems the OS is unaffected? */
	while(1) {
		k_msleep(500);
		printk("+");
	}
}
