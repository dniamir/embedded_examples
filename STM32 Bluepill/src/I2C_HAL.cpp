#include "stm32f1xx_hal.h"

I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
static void MX_I2C1_Init(void);

#define DEVICE_ADDRESS 0b1110110 << 1  // Shifting left by 1 bit for 8-bit I2C address

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_I2C1_Init();

    uint8_t regAddr = 0xD0;
    uint8_t data;

    while (1) {
        HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDRESS, regAddr, 1, &data, 1, HAL_MAX_DELAY);
        HAL_Delay(1000);  // Wait for a second
    }
}

void SystemClock_Config(void) {
    // ... Clock configuration code (typically provided by STM32CubeMX or other tools)
}

static void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;  // 100kHz
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
        // Initialization Error
        while (1);
    }
}

