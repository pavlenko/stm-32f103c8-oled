#include "fsm.h"

#include "PE_FSM.h"
#include "servomotor.h"

PE_FSM_State_t SERVO_MID = {
    .onEnter = [](){ servo0.setDegree(90); },
};

PE_FSM_State_t SERVO_MIN = {
    .onEnter = [](){ servo0.setDegree(0); },
};

PE_FSM_State_t SERVO_MAX = {
    .onEnter = [](){ servo0.setDegree(180); },
};

PE_FSM fsm = PE_FSM();