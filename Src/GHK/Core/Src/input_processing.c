#include "input_processing.h"

enum ButtonState buttonState[N0_OF_BUTTONS] = {};

void fsm_for_input_processing()
{
    for (unsigned char i = 0; i < N0_OF_BUTTONS; i++)
    {
        switch (buttonState[i])
        {
        case BUTTON_RELEASED:
            if (is_button_pressed(i))
            {
                buttonState[i] = BUTTON_PRESSED;
                switch (i)
                {
                case BUTTON_RESET:
                    led_7segment_num = 0;
                    break;

                case BUTTON_INC:
                    led_7segment_num = (led_7segment_num + 1) % 10;
                    break;

                case BUTTON_DEC:
                    led_7segment_num = (led_7segment_num + 10 - 1) % 10;
                    break;
                }
            }
            else
            {
                if (is_button_released_1s(i))
                {
                    buttonState[i] = BUTTON_RELEASED_MORE_THAN_1_SECOND;
                }
            }
            break;
        case BUTTON_RELEASED_MORE_THAN_1_SECOND:
            if (is_button_pressed(i))
            {
                buttonState[i] = BUTTON_PRESSED;
            }
            break;
        case BUTTON_PRESSED:
            if (is_button_released(i))
            {
                buttonState[i] = BUTTON_RELEASED;
            }
            else
            {
                if (is_button_pressed_3s(i))
                {
                    buttonState[i] = BUTTON_PRESSED_MORE_THAN_3_SECOND;
                }
            }
            break;
        case BUTTON_PRESSED_MORE_THAN_3_SECOND:
            if (is_button_released(i))
            {
                buttonState[i] = BUTTON_RELEASED;
            }
            break;
        }
    }
}
