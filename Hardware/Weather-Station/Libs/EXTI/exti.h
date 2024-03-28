#ifndef EXTI_H
#define EXTI_H


#include <stdint.h>

typedef void (* EXIT_CALLBACK_FUNCTION_t) (uint32_t gpio_pin);

typedef enum
{
    EXTI_EDGE_RISING = 1,
    EXTI_EDGE_FALLING = 2,
    EXTI_EDGE_ALL = 3,
}EXTI_EDGE_t;

void EXIT_Init(uint32_t gpio_pin, EXTI_EDGE_t edge);
void EXIT_SetCallBackFunction(EXIT_CALLBACK_FUNCTION_t callbackFunction);


#endif