#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define GPIO_ON 1
#define GPIO_OFF 0
#define LED_PIN 7

int main() {
    stdio_init_all();

    // Initialize the LED pin
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (1) {
        // Turn on the LED
        gpio_put(LED_PIN, GPIO_ON);
        sleep_ms(1000);
        // Turn off the LED
        gpio_put(LED_PIN, GPIO_OFF);
        sleep_ms(1000);
    }

    return 0;
}