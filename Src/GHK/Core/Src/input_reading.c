#include "input_reading.h"

// timer interrupt duration is 10 ms, so to pass 3 second, we need to jump to the interrupt service routine 300 time
#define DURATION_FOR_LONG_PRESS 300
// timer interrupt duration is 10 ms, so to pass 1 second, we need to jump to the interrupt service routine 100 time
#define DURATION_FOR_LONG_RELEASE 100
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

const uint16_t button_pin[N0_OF_BUTTONS] = {
    RESET_Pin,
    INC_Pin,
    DEC_Pin,
};

// the buffer that the final result is stored after debouncing
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];
// we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];

// we define a flag for a button pressed more than 3 second.
static uint8_t flagForButtonPress3s[N0_OF_BUTTONS];
static uint16_t counterForButtonPress3s[N0_OF_BUTTONS];

// we define a flag for a button released more than 1 second.
static uint8_t flagForButtonRelease1s[N0_OF_BUTTONS];
static uint16_t counterForButtonRelease1s[N0_OF_BUTTONS];

void button_reading(void)
{
    for (unsigned char i = 0; i < N0_OF_BUTTONS; i++)
    {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOB, button_pin[i]);
        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
        {
            buttonBuffer[i] = debounceButtonBuffer1[i];
        }

        if (buttonBuffer[i] == BUTTON_IS_PRESSED)
        {
            counterForButtonRelease1s[i] = 0;
            flagForButtonRelease1s[i] = 0;

            if (counterForButtonPress3s[i] < DURATION_FOR_LONG_PRESS)
            {
                ++counterForButtonPress3s[i];
            }
            else
            {
                flagForButtonPress3s[i] = 1;
            }
        }
        else if (buttonBuffer[i] == BUTTON_IS_RELEASED)
        {
            counterForButtonPress3s[i] = 0;
            flagForButtonPress3s[i] = 0;

            if (counterForButtonRelease1s[i] < DURATION_FOR_LONG_RELEASE)
            {
                ++counterForButtonRelease1s[i];
            }
            else
            {
                flagForButtonRelease1s[i] = 1;
            }
        }
    }
}

unsigned char is_button_pressed(unsigned char index)
{
    if (index >= N0_OF_BUTTONS)
        return 0;
    return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_3s(unsigned char index)
{
    if (index >= N0_OF_BUTTONS)
        return 0;
    return (flagForButtonPress3s[index] == 1);
}

unsigned char is_button_released(unsigned char index)
{
    if (index >= N0_OF_BUTTONS)
        return 0;
    return (buttonBuffer[index] == BUTTON_IS_RELEASED);
}

unsigned char is_button_released_1s(unsigned char index)
{
    if (index >= N0_OF_BUTTONS)
        return 0;
    return (flagForButtonRelease1s[index] == 1);
}

unsigned char is_all_button_released()
{
    for (unsigned char i = 0; i < N0_OF_BUTTONS; ++i)
    {
        if (!is_button_released(i))
        {
            return 0;
        }
    }
    return 1;
}

unsigned char is_all_button_released_1s()
{
    for (unsigned char i = 0; i < N0_OF_BUTTONS; ++i)
    {
        if (!is_button_released_1s(i))
        {
            return 0;
        }
    }
    return 1;
}
