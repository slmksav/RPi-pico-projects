#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"

#define PIR_PIN 0
#define LED_PIN 7
#define BUZZER_PIN 16
#define BUTTON_PIN 17

volatile bool pir_enabled = true;

void handle_button_irq() {
    pir_enabled = !pir_enabled;
}

int main() {
    stdio_init_all();

    gpio_init(PIR_PIN);
    gpio_set_dir(PIR_PIN, GPIO_IN);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    gpio_irq_callback(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true, &handle_button_irq);

    // wait time for the PIR sensor to stabilize after power has been turned on
    sleep_ms(2000);

    while (true) {
        if (pir_enabled) {
            int pir_value = gpio_get(PIR_PIN);
            if (pir_value == 1) {
                gpio_put(LED_PIN, 1);
                gpio_put(BUZZER_PIN, 1);
                sleep_ms(500);
                gpio_put(BUZZER_PIN, 0);
            } else {
                gpio_put(LED_PIN, 0);
            }
        } else {
            gpio_put(LED_PIN, 0);
            gpio_put(BUZZER_PIN, 0);
        }
        sleep_ms(100); //short delay to avoid any false positives
    }

    return 0;
}
