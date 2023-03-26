#include <stdio.h> //using serial port
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "header.h"

typedef enum
{
    GPIO_INPUT,
    GPIO_OUTPUT,
} gpio_direction_t;
typedef enum
{
    GPIO_PULL_NONE,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN,
} gpio_pull_mode_t;
typedef struct
{
    uint pin_number;
    gpio_direction_t pin_direction;
    gpio_pull_mode_t pin_pull_mode;
} PinConfig;

const uint PIR_PIN = 0;
const uint LED_PIN = 7;
const uint BUZZER_PIN = 16;
const uint BUTTON_PIN = 17;

const PinConfig pin_config[] = {
    {PIR_PIN, GPIO_INPUT, GPIO_PULL_NONE},     // PIR pin
    {LED_PIN, GPIO_OUTPUT, GPIO_PULL_NONE},    // LED pin
    {BUZZER_PIN, GPIO_OUTPUT, GPIO_PULL_NONE}, // Buzzer pin
    {BUTTON_PIN, GPIO_INPUT, GPIO_PULL_UP},    // Button pin
};

volatile bool pir_enabled = true;

void handle_button_irq(uint gpio, uint32_t events)
{
    pir_enabled = !pir_enabled;
}

int main()
{
    stdio_init_all();
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    lcd_init();
    lcd_set_cursor(0, 4);
    lcd_string("No motion");

    for (int i = 0; i < sizeof(pin_config) / sizeof(pin_config[0]); i++)
    {
        gpio_init(pin_config[i].pin_number); //initializes all pins to be used as I/Os
        gpio_set_dir(pin_config[i].pin_number, pin_config[i].pin_direction); //direction (output, input)
        gpio_set_pulls(pin_config[i].pin_number, pin_config[i].pin_pull_mode, pin_config[i].pin_pull_mode); //pull ups and pull downs
    }

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true, &handle_button_irq);

    // wait time for the PIR sensor to stabilize after power has been turned on
    sleep_ms(2000);

    while (true)
    {
        if (pir_enabled)
        {
            int pir_value = gpio_get(PIR_PIN);
            if (pir_value == 1)
            {
                gpio_put(LED_PIN, 1);
                gpio_put(BUZZER_PIN, 1);
                sleep_ms(500);
                gpio_put(BUZZER_PIN, 0);
                lcd_set_cursor(0, 4);
                lcd_string("Movement!");
            }
            else
            {
                gpio_put(LED_PIN, 0);
            }
        }
        else
        {
            gpio_put(LED_PIN, 0);
            gpio_put(BUZZER_PIN, 0);
        }
        sleep_ms(100); 
    }

    return 0;
}
