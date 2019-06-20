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
    float x;
    float y;
    float z;
} HP_Point3D_t;

float clearance = 50;

typedef struct {
    HP_Point3D_t FL;
    HP_Point3D_t FR;
    HP_Point3D_t ML;
    HP_Point3D_t MR;
    HP_Point3D_t RL;
    HP_Point3D_t RR;
} HP_Targets_t;

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

//TODO initial points, default
void calculate0(HP_Targets_t *targets)
{
    float mul = sin(45 * PI_DIV_BY_180);

    targets->FL.x = -100 * mul;
    targets->FL.y = 100 * mul;
    targets->FL.z = -clearance;

    targets->FR.x = 100 * mul;
    targets->FR.y = 100 * mul;
    targets->FR.z = -clearance;

    targets->ML.x = -100;
    targets->ML.y = 0;
    targets->ML.z = -clearance;

    targets->MR.x = 100;
    targets->MR.y = 0;
    targets->MR.z = -clearance;

    targets->RL.x = -100 * mul;
    targets->RL.y = -100 * mul;
    targets->RL.z = -clearance;

    targets->RR.x = 100 * mul;
    targets->RR.y = -100 * mul;
    targets->RR.z = -clearance;
}

void calculate1(HP_Targets_t *targets)
{
    float mul = sin(45 * PI_DIV_BY_180);

    float diffX = 0;
    float diffY = 10;

    targets->FL.x = -100 * mul + diffX;
    targets->FL.y = 100 * mul + diffY;
    targets->FL.z = 0;

    targets->FR.x = 100 * mul + diffX;
    targets->FR.y = 100 * mul - diffY;
    targets->FR.z = -clearance;

    targets->ML.x = -100 + diffX;
    targets->ML.y = 0 - diffY;
    targets->ML.z = -clearance;

    targets->MR.x = 100 + diffX;
    targets->MR.y = 0 + diffY;
    targets->MR.z = 0;

    targets->RL.x = -100 * mul + diffX;
    targets->RL.y = -100 * mul + diffY;
    targets->RL.z = 0;

    targets->RR.x = 100 * mul + diffX;
    targets->RR.y = -100 * mul - diffY;
    targets->RR.z = -clearance;
}

#endif //__HP_H
