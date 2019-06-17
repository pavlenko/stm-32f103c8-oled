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