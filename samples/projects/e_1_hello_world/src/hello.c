#include <zephyr/kernel.h>

void  printhello(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD_TARGET);
}
