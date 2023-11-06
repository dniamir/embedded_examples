// 10/29/2023
#include "stm32f1xx_hal.h"

// Define the LED pin and port
#define LED_PIN        GPIO_PIN_13
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

void LED_Init();
void SystemClock_Config();
void Error_Handler();


int main(void) {

    SystemClock_Config();

    // This will configure the SysTick to interrupt every millisecond (1/1000th of a second)
    if (HAL_SYSTICK_Config(SystemCoreClock / 1000) != HAL_OK) {
        Error_Handler();
    }
    
    // Initialize the LED
    LED_Init();

    // __enable_irq();

    while (1) {

        // Toggle the LED
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
        
        // Wait for a short period (500ms)
        HAL_Delay(50);
    }
}

void LED_Init() {
    // Enable the GPIOC clock
    LED_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;

    // Configure the LED pin
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Initialize the RCC Oscillators
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    // Initialize the CPU, AHB, and APB bus clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler();
    }

    // Update SystemCoreClock after changing the clock configuration
    SystemCoreClockUpdate();
}

void Error_Handler(void) {
    while(1) {
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
        // HAL_Delay(100);
    }
}

// SysTick_Handler is called by the SystemTick ISR and increments a tick counter in HAL
extern "C" void SysTick_Handler(void) {
    HAL_IncTick();
}