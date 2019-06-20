#ifndef __HP_H
#define __HP_H

/**
 * Movement steps 0...7 (8 == 0 on next iteration)
 *
 *     3---4---5
 *    / \     / \
 *   /   \   /   \
 *  /     \ /     \
 * 2---1--0,8--7---6
 *
 *     7---8---1
 *    / \     / \
 *   /   \   /   \
 *  /     \ /     \
 * 6---5--0,4--3---2
 */


//TODO geometry
//TODO initial state (prototype for modification)

#include <math.h>
#include <stdint.h>

#define PI_DIV_BY_180 0.01745329251
#define SIN_45        0.70710678118

typedef struct {
    int16_t x;
    int16_t y;
} HP_Point2D_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} HP_Point3D_t;

void test() {
    HP_Point3D_t center = {0, 0, 0};

    HP_Point2D_t mountFL = {-50, 100};
    HP_Point2D_t mountFR = {50, 100};
    HP_Point2D_t mountML = {-50, 0};
    HP_Point2D_t mountMR = {50, 0};
    HP_Point2D_t mountRL = {-50, -100};
    HP_Point2D_t mountRR = {50, -100};

    HP_Point3D_t targetFL = {-100, 100, -50};
    HP_Point3D_t targetFR = {100, 100, -50};
    HP_Point3D_t targetML = {-100, 0, -50};
    HP_Point3D_t targetMR = {100, 0, -50};
    HP_Point3D_t targetRL = {-100, -100, -50};
    HP_Point3D_t targetRR = {100, -100, -50};
}

#endif //__HP_H
