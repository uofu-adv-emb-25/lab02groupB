#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"

#include "functions.h"

void setUp(void) {}

void tearDown(void) {}

void test_blink(void)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    int count = 0;
    bool on = 0;

    for (int i = 0; i < 120; i++) {
        int pin = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        int currentCount = count;
        bool notOn = on;

        blink_func(&on, &count);

        //printf("count: %d on: %d notOn: %d pin: %d \n", count, on, notOn, pin);
        TEST_ASSERT_EQUAL_MESSAGE(currentCount + 1, count, "Count did not increment by one");

        printf("count: %d on: %d notOn: %d pin: %d \n", count, on, notOn, pin);
        
        if (i > 1) {
            if ((!(count % 11) || (count % 11 == 1))) {
                TEST_ASSERT_EQUAL_MESSAGE(pin, !on, "Pin did not alternate when it should have");
            } else {
                TEST_ASSERT_EQUAL_MESSAGE(pin, on, "Pin alternated when it should not have");
            }
        }

        if ((i+1) % 11) {
            //printf("count: %d on: %d notOn: %d pin: %d \n", count, on, notOn, pin);
            TEST_ASSERT_EQUAL_MESSAGE(notOn, !on, "'on' alternated when count was divisible by 11");

        } else {
            //printf("count: %d on: %d notOn: %d pin: %d \n", count, on, notOn, pin);
            TEST_ASSERT_EQUAL_MESSAGE(notOn, on, "'On' did not alternate when count was not divisible by 11");
            
        }
            
    }
}

void test_switch_char(void) {
    char y = 'y';
    char X = 'X';
    char one = '1';
    char newLine = '\n';
    
    TEST_ASSERT_TRUE_MESSAGE(y   == switch_char('Y'), "Lowercasing did not return expected value");
    TEST_ASSERT_TRUE_MESSAGE(X   == switch_char('x'), "Uppercasing did not return expected value");
    TEST_ASSERT_TRUE_MESSAGE(one == switch_char('1'), "Switch_char for number did not return same number");

    TEST_ASSERT_TRUE_MESSAGE(newLine == switch_char('\n'), "Switch_char on newline did not return newline");
}

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    while(1) {
	    sleep_ms(5000); // Give time for TTY to attach.
	    printf("Start tests\n");
	    UNITY_BEGIN();
        RUN_TEST(test_blink);
        RUN_TEST(test_switch_char);
	    UNITY_END();
    }

    return 0;
}
