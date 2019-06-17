#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "PE_Button.h"

/**
 *
 *     ^ Y            [A]
 *     |   X
 * <-- o -->       [D]    [B]
 *     |
 *     v    [F] [E]   [C]
 *
 * Y - move front/rear
 * X - move left/right
 * A - increase height
 * B - rotate right
 * C - decrease height
 * D - rotate left
 * E - TODO
 * F - TODO
 */

uint8_t height = 0;

extern PE_Button buttonA;
extern PE_Button buttonB;
extern PE_Button buttonC;
extern PE_Button buttonD;

void MX_BTN_Init();

#endif //__CONTROLLER_H
