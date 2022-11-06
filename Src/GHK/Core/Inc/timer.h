#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
#include "input_reading.h"
#include "led7_processing.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern const uint16_t led_blinking_cycle;
extern const uint16_t led_7segment_cycle;
extern uint16_t led_blinking_counter;
extern uint16_t led_7segment_counter;

#endif /* INC_TIMER_H_ */
