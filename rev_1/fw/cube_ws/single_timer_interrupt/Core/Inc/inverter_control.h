#ifndef __INVERTER_CONTROL_H
#define __INVERTER_CONTROL_H
#include "main.h"

// Phase U
#define GPIO_PIN_U_NSD   GPIO_PIN_0
#define GPIO_PORT_U_NSD  GPIOB

#define GPIO_PIN_U_SW    GPIO_PIN_7
#define GPIO_PORT_U_SW   GPIOA

// Phase V
#define GPIO_PIN_V_NSD   GPIO_PIN_6
#define GPIO_PORT_V_NSD  GPIOB

#define GPIO_PIN_V_SW    GPIO_PIN_1
#define GPIO_PORT_V_SW   GPIOB

// Phase W
#define GPIO_PIN_W_NSD   GPIO_PIN_4
#define GPIO_PORT_W_NSD  GPIOB

#define GPIO_PIN_W_SW    GPIO_PIN_5
#define GPIO_PORT_W_SW   GPIOB

#endif /* __INVERTER_CONTROL_H */