#include "timer.h"

const uint16_t led_blinking_cycle = 100;
const uint16_t led_7segment_cycle = 100;
uint16_t led_blinking_counter = 0;
uint16_t led_7segment_counter = 0;

extern TIM_HandleTypeDef htim2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim2.Instance)
    {
        button_reading();
        display_led_7segment(led_7segment_num);

        if (led_blinking_counter == 0)
        {
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
        }
        led_blinking_counter = (led_blinking_counter + 1) % led_blinking_cycle;

        if (is_all_button_released())
        {
            led_7segment_counter = (led_7segment_counter + 1) % led_blinking_cycle;
            if (led_7segment_counter == 0)
            {
                led_7segment_num = (led_7segment_num > 0) ? (led_7segment_num - 1) : 0;
            }
        }
        else if (is_button_pressed_3s(BUTTON_INC))
        {
            if (led_7segment_counter == 0)
            {
                led_7segment_num = (led_7segment_num + 1) % 10;
            }
            led_7segment_counter = (led_7segment_counter + 1) % led_blinking_cycle;
        }
        else if (is_button_pressed_3s(BUTTON_DEC))
        {
            if (led_7segment_counter == 0)
            {
                led_7segment_num = (led_7segment_num + 10 - 1) % 10;
            }
            led_7segment_counter = (led_7segment_counter + 1) % led_blinking_cycle;
        }
        else
        {
            led_7segment_counter = 0;
        }
    }
}
