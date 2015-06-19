/*
 * UDOO board power off
 *
 * Copyright (C) 2014 Jasbir Matharu
 * Copyright (C) 2015 Peter Vicman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>

#define ARDUINO_MODE_STOPPED      1   /* does arduino starts at boot */
#define ARDUINO_MODE_LEAVE_POWER  2   /* leave 5V power on after shutdown (to keep arduino reset) */

static void (*pm_power_off_orig)(void) = NULL;
static int sam3x_rst_gpio = -EINVAL;
static int pwr_5v_gpio = -EINVAL;
static u32 arduino_mode = -EINVAL;
static int lcd_touch_reset_gpio = -EINVAL;  
static int lcd_panel_on_gpio = -EINVAL;
static int lcd_backlight_gpio = -EINVAL;  

static void udoo_set_gpio(unsigned gpio, int value) {
	int ret;

  if (! gpio_is_valid(gpio))
  	return;
  	
  ret = gpio_direction_output(gpio, value);
  if (ret)
    pr_err("%s: gpio %u/%d failed\n", __func__, gpio, value);
}

static void udoo_request_gpio(struct device *dev, unsigned gpio, unsigned long flags, const char *label) {
	int ret;

  if (! gpio_is_valid(gpio))
  	return;
  	
	ret = devm_gpio_request_one(dev, gpio, flags, label);
	if (ret)
		dev_err(dev, "request of gpio %s %u failed with %d\n", label, gpio, ret);
}
    
static void udoo_power_off(void) {
  pr_emerg("%s: powering off\n", __func__);
  
  if (pm_power_off_orig != NULL)
    pm_power_off_orig();
 
  udoo_set_gpio(lcd_touch_reset_gpio, 1);
  udoo_set_gpio(lcd_panel_on_gpio, 0);
  udoo_set_gpio(lcd_backlight_gpio, 0);
  
  udoo_set_gpio(sam3x_rst_gpio, 0);
  msleep(50);		/* stop sam3x safely */

  if (gpio_is_valid(pwr_5v_gpio) && (arduino_mode & ARDUINO_MODE_LEAVE_POWER) == 0) {
    pr_emerg("%s: 5V power down\n", __func__);
    udoo_set_gpio(pwr_5v_gpio, 1);
  } else
  	pr_emerg("%s: 5V power still on, sam3x reset\n", __func__);
}

static int udoo_power_off_probe(struct platform_device *pdev)
{
  struct device_node *pwr_off_np;
  int ret;

  dev_err(&pdev->dev, "%s: power-off probe\n", __func__);

  pwr_off_np = of_find_compatible_node(NULL, NULL, "sitronix,st1232");
  if (pwr_off_np) {
    lcd_touch_reset_gpio = of_get_named_gpio(pwr_off_np, "gpios", 0);
		lcd_panel_on_gpio = of_get_named_gpio(pwr_off_np, "lcd_panel_on_gpio", 0);
		lcd_backlight_gpio = of_get_named_gpio(pwr_off_np, "lcd_backlight_gpio", 0);
    of_node_put(pwr_off_np);

		udoo_request_gpio(&pdev->dev, lcd_panel_on_gpio, GPIOF_OUT_INIT_HIGH, "lcd_panel_on_gpio");
		udoo_request_gpio(&pdev->dev, lcd_backlight_gpio, GPIOF_OUT_INIT_HIGH, "lcd_backlight_gpio");
		
		ret = gpio_export(lcd_backlight_gpio, false);
  }
  
  pwr_off_np = of_find_compatible_node(NULL, NULL, "udoo,poweroff");
  if (pwr_off_np) {
    ret = of_property_read_u32(pwr_off_np, "arduino_mode", &arduino_mode);
    if (ret != 0) {
      dev_err(&pdev->dev, "%s: arduino mode not found in dtb\n", __func__);
      arduino_mode = 0;
    }

    sam3x_rst_gpio = of_get_named_gpio(pwr_off_np, "sam3x_rst_gpio", 0);
    pwr_5v_gpio = of_get_named_gpio(pwr_off_np, "pwr_5v_gpio", 0);
    of_node_put(pwr_off_np);

		udoo_request_gpio(&pdev->dev, pwr_5v_gpio, GPIOF_OUT_INIT_LOW, "pwr_5v_gpio");
	
  	if (gpio_is_valid(sam3x_rst_gpio)) {
  		ret = gpio_export(sam3x_rst_gpio, false);
		
  	  if (arduino_mode & ARDUINO_MODE_STOPPED) {
  	    dev_err(&pdev->dev, "%s: arduino stopped\n", __func__);
  	    udoo_set_gpio(sam3x_rst_gpio, 0);
  	  } else {
  	  	dev_err(&pdev->dev, "%s: arduino running\n", __func__);
  	    udoo_set_gpio(sam3x_rst_gpio, 1);
  	  }
  	}

    pm_power_off_orig = pm_power_off;
    pm_power_off = udoo_power_off;
    return 0;
  }

  /* If a pm_power_off function has already been added, leave it alone */
  if (pm_power_off != NULL) {
    dev_err(&pdev->dev, "%s: pm_power_off function already registered\n", __func__);
    return -EBUSY;
  }

  return -ENODEV;
}

static int udoo_power_off_remove(struct platform_device *pdev)
{
  return 0;
}

static const struct of_device_id power_off_dt_ids[] = {
  { .compatible = "udoo,poweroff", },
  { /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, power_off_dt_ids);

static struct platform_driver udoo_power_off_driver = {
  .driver = {
    .name = "udoo_power_off",
    .owner  = THIS_MODULE,
    .of_match_table = of_match_ptr(power_off_dt_ids),
  },
  .probe    = udoo_power_off_probe,
  .remove   = udoo_power_off_remove,
};
module_platform_driver(udoo_power_off_driver);

MODULE_AUTHOR("Jasbir Matharu, Peter Vicman");
MODULE_DESCRIPTION("UDOO Power off driver v3");
MODULE_LICENSE("GPL v2");
