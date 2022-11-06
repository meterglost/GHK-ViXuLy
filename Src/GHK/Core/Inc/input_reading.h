#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"

// we aim to work with more than one buttons
#define N0_OF_BUTTONS 3

enum Button
{
    BUTTON_RESET,
    BUTTON_INC,
    BUTTON_DEC,
};

enum ButtonState
{
    BUTTON_RELEASED,
    BUTTON_RELEASED_MORE_THAN_1_SECOND,
    BUTTON_PRESSED,
    BUTTON_PRESSED_MORE_THAN_3_SECOND,
};

void button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_3s(unsigned char index);
unsigned char is_button_released(unsigned char index);
unsigned char is_button_released_1s(unsigned char index);
unsigned char is_all_button_released();
unsigned char is_all_button_released_1s();

#endif /* INC_INPUT_READING_H_ */
