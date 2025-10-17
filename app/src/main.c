/*
 * main.c
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#define SW0NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0NODE, gpios);

int main(void) {
  printk("[Main]\tInit");

  if(!gpio_is_ready_dt(&button)) return 0;

  if(gpio_pin_configure_dt(&button, GPIO_INPUT)) return 0;
  while(1) {
    if(gpio_pin_get_dt(&button)) {
      printk("Button Poll Press");
      while(gpio_pin_get_dt(&button)) k_msleep(10);
    }
    k_msleep(10);
  }
	return 0;
}
