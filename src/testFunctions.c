#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include <stdint.h>

#include "testFunctions.h"

char switch_char(char c)
{
    // If c is uppercase, make it lowercase
    if (c <= 'z' && c >= 'a') return(c - 32);

    // If c is lowercase, "    "  uppercase
    else if (c >= 'A' && c <= 'Z') return(c + 32);

    // If it's not a letter, return same input
    else return c;
}