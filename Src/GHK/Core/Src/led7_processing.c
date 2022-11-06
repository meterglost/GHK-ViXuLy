#include "led7_processing.h"

const uint16_t led_7segment_num_pin[10] = {
    // GFEDCBA
    0b1000000, // 0
    0b1111001, // 1
    0b0100100, // 2
    0b0110000, // 3
    0b0011001, // 4
    0b0010010, // 5
    0b0000010, // 6
    0b1111000, // 7
    0b0000000, // 8
    0b0010000, // 9
};

uint8_t led_7segment_num = 1;

void display_led_7segment(uint8_t num)
{
    GPIOA->BRR = ~led_7segment_num_pin[num] << 8; // Clear 7 pin for led7seg from GPIO port A pin 8 to pin 14
    GPIOA->BSRR = led_7segment_num_pin[num] << 8; // Output 7 pin for led7seg from GPIO port A pin 8 to pin 14
}
