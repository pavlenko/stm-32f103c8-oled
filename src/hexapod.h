#ifndef __HEXAPOD_H
#define __HEXAPOD_H

#include <stdint.h>
#include <PE_Servomotor.h>

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

extern void MX_Hexapod_Init();//TODO full init servo system with initial state

#endif //__HEXAPOD_H
