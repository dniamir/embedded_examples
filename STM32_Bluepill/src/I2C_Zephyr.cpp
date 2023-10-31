#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <drivers/i2c.h>
#include <sys/printk.h>

#define I2C_DEV DT_LABEL(DT_ALIAS(i2c0))
#define BME680_I2C_ADDRESS 0b1110110
#define WHO_AM_I_REGISTER 0xD0
#define LED_PORT DT_GPIO_LABEL(DT_ALIAS(led0), gpios)
#define LED_PIN DT_GPIO_PIN(DT_ALIAS(led0), gpios)

const struct device *i2c_dev;
const struct device *led_dev;

uint8_t readRegister(uint8_t address, uint8_t reg) {
    uint8_t value;
    int ret;

    ret = i2c_burst_read(i2c_dev, address, reg, &value, 1);
    if (ret) {
        printk("I2C read error: %d\n", ret);
        return 0xFF;
    }

    return value;
}

void main(void) {
    i2c_dev = device_get_binding(I2C_DEV);
    if (!i2c_dev) {
        printk("I2C: Device driver not found.\n");
        return;
    }

    led_dev = device_get_binding(LED_PORT);
    gpio_pin_configure(led_dev, LED_PIN, GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(DT_ALIAS(led0), gpios));

    while (1) {
        uint8_t sensorID = 5;
        sensorID = readRegister(BME680_I2C_ADDRESS, WHO_AM_I_REGISTER);
        printk("Sensor ID: 0x%02x\n", sensorID);

        gpio_pin_set(led_dev, LED_PIN, 0);
        k_sleep(K_MSEC(100));
        printk("Test1\n");
        gpio_pin_set(led_dev, LED_PIN, 1);
        k_sleep(K_MSEC(100));
    }
}
