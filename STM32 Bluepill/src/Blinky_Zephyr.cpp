// https://github.com/m3y54m/zephyr-os-bluepill-playground
// https://github.com/maksimdrachov/zephyr-rtos-tutorial

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

/* Get the device binding for the LED GPIO pin */
#define LED_NODE DT_ALIAS(led0)
#define LED_PIN DT_GPIO_PIN(LED_NODE, gpios)
#define LED_FLAGS DT_GPIO_FLAGS(LED_NODE, gpios)

void main(void)
{
    const struct device *dev = device_get_binding(DT_GPIO_LABEL(LED_NODE, gpios));
    gpio_pin_configure(dev, LED_PIN, GPIO_OUTPUT_ACTIVE | LED_FLAGS);

    while (1)
    {
        gpio_pin_set(dev, LED_PIN, 1); // Turn on the LED
        k_sleep(K_MSEC(200));         // Sleep for 200ms

        gpio_pin_set(dev, LED_PIN, 0); // Turn off the LED
        k_sleep(K_MSEC(200));         // Sleep for 200ms
    }
}