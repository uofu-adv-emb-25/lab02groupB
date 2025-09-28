#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include <stdint.h>

#include "functions.h"

char switch_char(char c)
{
    // If c is uppercase, make it lowercase
    if (c <= 'z' && c >= 'a') return(c - 32);

    // If c is lowercase, "    "  uppercase
    else if (c >= 'A' && c <= 'Z') return(c + 32);

    // If it's not a letter, return same input
    else return c;
}

void blink_func(bool* on, int* count) {
    // Use count to toggle it every 12 ticks, delay by 500 ms
    // Expected delay = 6 seconds
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, (*on));
    if (++(*count) % 11) (*on) = !(*on);
}