#include "main.h"

void app_main(void)
{
    gpio_config(&io_led);
    gpio_config(&io_button);
    gpio_config(&io_input);
    gpio_config(&io_output);
    esp_task_wdt_init(&twdt_config); // only init in main thread

    esp_task_wdt_add(NULL);

    int lastButtonState = LOW;
    while (1) {

        // pet watchdog
        esp_task_wdt_reset();

        // Turn all LEDs ON
        int buttonState = gpio_get_level(BUTTON_PIN_1);
        int inputState = gpio_get_level(SIGNAL_INPUT_1);

        gpio_set_level(SIGNAL_OUTPUT_1, buttonState)
        gpio_set_level(LED_PIN_1, inputState)
        
        vTaskDelay(pdMS_TO_TICKS(100)); // let other tasks run
};
}
