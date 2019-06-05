#include "FSM.h"

void FSM_initialize(FSM_Handle_t *fsm, FSM_State_t *state) {
    fsm->state = state;

    fsm->state->enter();
}

void FSM_transition(FSM_Handle_t *fsm, FSM_Transition_t *transition) {
    fsm->state->leave();

    fsm->state = transition->handler();

    fsm->state->enter();
}
