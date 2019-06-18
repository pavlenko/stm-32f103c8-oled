#ifndef __HEXAPOD_H
#define __HEXAPOD_H

#include <stdint.h>
#include <PE_Servomotor.h>

/**         _______
 *  /\    /         \    /\
 * /  \===|         |===/  \
 *        |    ^y   |
 *  /\    |    |  x |    /\
 * /  \===| <--*--> |===/  \
 *        |         |
 *  /\    |         |    /\
 * /  \===|         |===/  \
 *        \ _______ /
 */

typedef struct {
    int16_t mountX;  // Mount X distance
    int16_t mountY;  // Mount Y distance
    int16_t cLength; // Coxa length
    int16_t fLength; // Femur length
    int16_t tLength; // Tiba length
} HP_ConfigLeg_t;

typedef struct {
    float height;
    HP_ConfigLeg_t *legFL;
    HP_ConfigLeg_t *legFR;
    HP_ConfigLeg_t *legML;
    HP_ConfigLeg_t *legMR;
    HP_ConfigLeg_t *legRL;
    HP_ConfigLeg_t *legRR;
} HP_Config_t;

typedef struct {
    float x;
    float y;
    float z;
} HP_Point_t;

typedef struct {
    HP_Point_t *point;
    uint32_t cLength; // Coxa length
    uint32_t fLength; // Femur length
    uint32_t tLength; // Tiba length
    PE_Servomotor &cServo;
    PE_Servomotor &fServo;
    PE_Servomotor &tServo;
} HP_Leg_t;

typedef struct {
    HP_Leg_t *legFL; // front left
    HP_Leg_t *legFR; // front right
    HP_Leg_t *legML; // middle left
    HP_Leg_t *legMR; // middle right
    HP_Leg_t *legRL; // rear left
    HP_Leg_t *legRR; // rear right
} HP_Frame_t;

void MX_Hexapod_Init();//TODO full init servo system with initial state

#endif //__HEXAPOD_H
