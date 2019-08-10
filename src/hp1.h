#ifndef __HP1_H
#define __HP1_H

#include <math.h>
#include <stdint.h>

#define RAD_TO_DEG(x) ( 57.29577951308233 * (x) )

#define SQR(x) ((x) * (x))

#define S_THICKNESS 28
#define F_LENGTH 105
#define T_LENGTH 55

typedef struct {
    float x;
    float y;
    float z;
} HP1_Point3D_t;

typedef struct {
    float clearance;
} HP1_Frame_t;

void HP1_calculate_leg_angles(HP1_Frame_t *frame, HP1_Point3D_t *point, uint16_t *cDegree, uint16_t *fDegree, uint16_t *tDegree)
{
    /* Calculate horizontal distance in millimeters */
    float h_distance = hypotf((*point).x, (*point).y);

    /* Calculate coxa angle in radians */
    float c_angle = (float) (atanf((*point).y / (*point).x) + M_PI_2);

    /* Calculate vertical distance in millimeters */
    float v_distance = sqrtf(SQR(h_distance - S_THICKNESS) + SQR(frame->clearance - (*point).z));

    /* Calculate femur add angle from z to v_distance axis in radians */
    float f_add_angle = atanf((h_distance - S_THICKNESS) / (frame->clearance - (*point).z));

    /* Calculate femur angle in radians */
    float f_angle = acosf((SQR(F_LENGTH) + SQR(v_distance) - SQR(T_LENGTH)) / (2 * F_LENGTH * v_distance)) + f_add_angle;

    /* Calculate tiba angle in radians */
    float t_angle = acosf((SQR(T_LENGTH) + SQR(F_LENGTH) - SQR(v_distance)) / (2 * T_LENGTH * F_LENGTH));

    *cDegree = (uint16_t) RAD_TO_DEG(c_angle);
    *fDegree = (uint16_t) RAD_TO_DEG(f_angle);
    *tDegree = (uint16_t) RAD_TO_DEG(t_angle);
}

#endif //__HP1_H
