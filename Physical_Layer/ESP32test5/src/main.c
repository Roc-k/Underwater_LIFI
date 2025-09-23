#include "main.h"

void app_main(void)
{
    gpio_config(&io_led);
    gpio_config(&io_button);
    esp_task_wdt_init(&twdt_config); // only init in main thread

    esp_task_wdt_add(NULL);

    int lastButtonState = LOW;
    while (1) {

        // pet watchdog
        esp_task_wdt_reset();

        // Turn all LEDs ON
        int buttonState = gpio_get_level(BUTTON_PIN_1);

        if (buttonState == HIGH) {
            gpio_set_level(LED_PIN_1, HIGH);
        } else {
            gpio_set_level(LED_PIN_1, LOW);
        }
        if (buttonState != lastButtonState) {
            printf("%d\n", buttonState);
            lastButtonState = buttonState;
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // let other tasks run
};
}
