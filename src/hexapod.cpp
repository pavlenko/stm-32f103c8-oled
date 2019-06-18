#include "hexapod.h"

#define HP_C_LENGTH (20U)
#define HP_F_LENGTH (120U)
#define HP_T_LENGTH (120U)

HP_ConfigLeg_t configFL;
HP_ConfigLeg_t configFR;
HP_ConfigLeg_t configML;
HP_ConfigLeg_t configMR;
HP_ConfigLeg_t configRL;
HP_ConfigLeg_t configRR;

HP_Config_t hpConfig;

void MX_Hexapod_Init() {
    configFL.mountX  = -50;
    configFL.mountY  = 100;
    configFL.cLength = HP_C_LENGTH;
    configFL.fLength = HP_F_LENGTH;
    configFL.tLength = HP_T_LENGTH;

    configFR.mountX  = 50;
    configFR.mountY  = 100;
    configFR.cLength = HP_C_LENGTH;
    configFR.fLength = HP_F_LENGTH;
    configFR.tLength = HP_T_LENGTH;

    configML.mountX  = -50;
    configML.mountY  = 0;
    configML.cLength = HP_C_LENGTH;
    configML.fLength = HP_F_LENGTH;
    configML.tLength = HP_T_LENGTH;

    configMR.mountX  = 50;
    configMR.mountY  = 0;
    configMR.cLength = HP_C_LENGTH;
    configMR.fLength = HP_F_LENGTH;
    configMR.tLength = HP_T_LENGTH;

    configRL.mountX  = -50;
    configRL.mountY  = -100;
    configRL.cLength = HP_C_LENGTH;
    configRL.fLength = HP_F_LENGTH;
    configRL.tLength = HP_T_LENGTH;

    configRR.mountX  = 50;
    configRR.mountY  = -100;
    configRR.cLength = HP_C_LENGTH;
    configRR.fLength = HP_F_LENGTH;
    configRR.tLength = HP_T_LENGTH;

    hpConfig.legFL = &configFL;
    hpConfig.legFR = &configFR;
    hpConfig.legML = &configML;
    hpConfig.legMR = &configMR;
    hpConfig.legRL = &configRL;
    hpConfig.legRR = &configRR;
}

volatile uint8_t iteration = 0;

// frame center is: x=0, y=0, z=height
void calculate() {
    HP_Point_t targetFL, targetFR, targetML, targetMR, targetRL, targetRR;

    switch (iteration) {
        case 0:
            targetFL = {.x = -100, .y = 100, .z = 0};
            targetFR = {.x = 100, .y = 100, .z = 0};
            targetML = {.x = -100, .y = 0, .z = 0};
            targetMR = {.x = 100, .y = 0, .z = 0};
            targetRL = {.x = -100, .y = -100, .z = 0};
            targetRR = {.x = 100, .y = -100, .z = 0};
            break;

            //TODO change below
        case 1:
            targetFL = {.z = 0};
            targetFR = {.z = -hpConfig.height};
            targetML = {.z = 0};
            targetMR = {.z = -hpConfig.height};
            targetRL = {.z = 0};
            targetRR = {.z = -hpConfig.height};
            break;

        case 2:
            targetFL = {.z = 0};
            targetFR = {.z = -hpConfig.height};
            targetML = {.z = 0};
            targetMR = {.z = -hpConfig.height};
            targetRL = {.z = 0};
            targetRR = {.z = -hpConfig.height};
            break;

        case 3:
            targetFL = {.z = 0};
            targetFR = {.z = -hpConfig.height};
            targetML = {.z = 0};
            targetMR = {.z = -hpConfig.height};
            targetRL = {.z = 0};
            targetRR = {.z = -hpConfig.height};
            break;

        case 4:
            targetFL = {.z = -hpConfig.height};
            targetFR = {.z = -hpConfig.height};
            targetML = {.z = -hpConfig.height};
            targetMR = {.z = -hpConfig.height};
            targetRL = {.z = -hpConfig.height};
            targetRR = {.z = -hpConfig.height};
            break;

        case 5:
            targetFL = {.z = -hpConfig.height};
            targetFR = {.z = 0};
            targetML = {.z = -hpConfig.height};
            targetMR = {.z = 0};
            targetRL = {.z = -hpConfig.height};
            targetRR = {.z = 0};
            break;

        case 6:
            targetFL = {.z = -hpConfig.height};
            targetFR = {.z = 0};
            targetML = {.z = -hpConfig.height};
            targetMR = {.z = 0};
            targetRL = {.z = -hpConfig.height};
            targetRR = {.z = 0};
            break;

        case 7:
            targetFL = {.z = -hpConfig.height};
            targetFR = {.z = 0};
            targetML = {.z = -hpConfig.height};
            targetMR = {.z = 0};
            targetRL = {.z = -hpConfig.height};
            targetRR = {.z = 0};
            break;

        default:
            return;
    }

    //TODO make used:
    (void) &targetFL;
    (void) &targetFR;
    (void) &targetML;
    (void) &targetMR;
    (void) &targetRL;
    (void) &targetRR;
}