/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include "hello.h"

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec led_00 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led_01 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led_02 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led_03 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

LOG_MODULE_REGISTER(main,LOG_LEVEL_DBG);

int main(void)
{
	int ret;
	bool led_state = true;

	if(!gpio_is_ready_dt(&led_00) || !gpio_is_ready_dt(&led_01) || !gpio_is_ready_dt(&led_02) || !gpio_is_ready_dt(&led_03)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led_00,GPIO_OUTPUT_ACTIVE);
	if(ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led_01,GPIO_OUTPUT_ACTIVE);
	if(ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led_02,GPIO_OUTPUT_ACTIVE);
	if(ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led_03,GPIO_OUTPUT_ACTIVE);
	if(ret < 0) {
		return 0;
	}

	while(1)
	{
		LOG_DBG("Hiiii, this is from dbg");
		LOG_INF("Hiiii, this is from inf");
		LOG_WRN("Hiiii, this is from wrn");
		LOG_ERR("Hiiii, this is from err");

		printhello();

		ret = gpio_pin_toggle_dt(&led_00);
		if(ret < 0) {
			return 0;
		}

		ret = gpio_pin_toggle_dt(&led_01);
		if(ret < 0) {
			return 0;
		}

		ret = gpio_pin_toggle_dt(&led_02);
		if(ret < 0) {
			return 0;
		}

		ret = gpio_pin_toggle_dt(&led_03);
		if(ret < 0) {
			return 0;
		}
		led_state = !led_state;
		printk("LED %s\n",led_state ? "ON" : "OFF");

		k_msleep(5000);
	}

	return 0;
}
