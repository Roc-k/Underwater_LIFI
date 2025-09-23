#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "sdkconfig.h"
#include "esp_task_wdt.h" // watchdog

#define HIGH 1
#define LOW 0

#define LED_PIN_1 12
#define BUTTON_PIN_1 16
#define SIGNAL_INPUT_1 39
#define SIGNAL_OUTPUT_1 6

gpio_config_t io_led = {
    .pin_bit_mask = (1ULL << LED_PIN_1),
    .mode = GPIO_MODE_OUTPUT,              
    .pull_up_en = GPIO_PULLUP_DISABLE,     
    .pull_down_en = GPIO_PULLDOWN_DISABLE, 
    .intr_type = GPIO_INTR_DISABLE         // Disable interrupts
};

gpio_config_t io_input = {
    .pin_bit_mask = (1ULL << SIGNAL_INPUT_1),
    .mode = GPIO_MODE_INPUT,              
    .pull_up_en = GPIO_PULLUP_DISABLE,     
    .pull_down_en = GPIO_PULLDOWN_DISABLE, 
    .intr_type = GPIO_INTR_DISABLE         // Disable interrupts
};

gpio_config_t io_output = {
    .pin_bit_mask = (1ULL << SIGNAL_OUTPUT_1),
    .mode = GPIO_MODE_OUTPUT,              
    .pull_up_en = GPIO_PULLUP_DISABLE,     
    .pull_down_en = GPIO_PULLDOWN_DISABLE, 
    .intr_type = GPIO_INTR_DISABLE         // Disable interrupts
};


gpio_config_t io_button = {
    .pin_bit_mask = (1ULL << BUTTON_PIN_1),
    .mode = GPIO_MODE_INPUT,               
    .pull_up_en = GPIO_PULLUP_DISABLE,     
    .pull_down_en = GPIO_PULLDOWN_DISABLE, 
    .intr_type = GPIO_INTR_DISABLE         // Disable interrupts
};


esp_task_wdt_config_t twdt_config = {
    .timeout_ms = 5000,          
    .idle_core_mask = (1 << 0),           // Mask for idle tasks (e.g., core 0 only)
    .trigger_panic = true,                // Trigger a panic handler on timeout
};
