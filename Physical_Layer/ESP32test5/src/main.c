#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "sdkconfig.h"

#define HIGH 1
#define LOW 0

#define LED_PIN_1 39
#define BUTTON_PIN_1 45

void app_main(void)
{
    gpio_config_t io_led = {
        .pin_bit_mask = (1ULL << LED_PIN_1),
        .mode = GPIO_MODE_OUTPUT,              // Set as output
        .pull_up_en = GPIO_PULLUP_DISABLE,     // Disable pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // Disable pull-down
        .intr_type = GPIO_INTR_DISABLE         // Disable interrupts
    };
    gpio_config(&io_led);

    gpio_config_t io_button = {
        .pin_bit_mask = (1ULL << BUTTON_PIN_1),
        .mode = GPIO_MODE_INPUT,               // Set as input
        .pull_up_en = GPIO_PULLUP_DISABLE,     // Disable pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // Disable pull-down
        .intr_type = GPIO_INTR_DISABLE         // Disable interrupts
    };
    gpio_config(&io_button);

    while (1) {
        // Turn all LEDs ON
        int buttonState = gpio_get_level(BUTTON_PIN_1);

        if (buttonState == HIGH) {
            gpio_set_level(LED_PIN_1, HIGH);
        } else {
            gpio_set_level(LED_PIN_1, LOW);
        }
};
}
