#include "hexapod.h"

HP_ConfigLeg_t configFL;
HP_ConfigLeg_t configFR;
HP_ConfigLeg_t configML;
HP_ConfigLeg_t configMR;
HP_ConfigLeg_t configRL;
HP_ConfigLeg_t configRR;

void MX_Hexapod_Init() {
    configFL.mountX = -50;
    configFL.mountY = 100;

    configFR.mountX = 50;
    configFR.mountY = 100;

    configML.mountX = -50;
    configML.mountY = 0;

    configMR.mountX = 50;
    configMR.mountY = 0;

    configRL.mountX = -50;
    configRL.mountY = -100;

    configRR.mountX = 50;
    configRR.mountY = -100;
}