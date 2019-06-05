#include "FSM.h"

void FSM_initialize(FSM_Handle_t *fsm, FSM_State_t *state) {
    fsm->prevState = fsm->nextState = state;

    if (fsm->prevState->onEnter) {
        fsm->prevState->onEnter();
    }
}

void FSM_transition(FSM_Handle_t *fsm, FSM_State_t *state) {
    fsm->nextState = state;
}

void FSM_dispatch(FSM_Handle_t *fsm) {
    if (fsm->prevState != fsm->nextState) {
        if (fsm->prevState->onLeave) {
            fsm->prevState->onLeave();
        }

        fsm->prevState = fsm->nextState;

        if (fsm->prevState->onEnter) {
            fsm->prevState->onEnter();
        }
    }

    if (fsm->prevState->onDispatch) {
        fsm->prevState->onDispatch();
    }
}
