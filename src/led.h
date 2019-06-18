#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LED_OFF = 0U,
    LED_ON  = 1U,
} LED_State_t;

void MX_LED_Init();

void LED(LED_State_t state);

#ifdef __cplusplus
}
#endif

#endif //__LED_H
