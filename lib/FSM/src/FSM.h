#ifndef FSM_H
#define FSM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
    void (*onEnter) ();
    void (*onLeave) ();
    void (*onDispatch) ();
} FSM_State_t;

typedef struct {
    FSM_State_t *prevState;
    FSM_State_t *nextState;
} FSM_Handle_t;

void FSM_initialize(FSM_Handle_t *fsm, FSM_State_t *state);

void FSM_transition(FSM_Handle_t *fsm, FSM_State_t *state);

void FSM_dispatch(FSM_Handle_t *fsm);

#ifdef __cplusplus
}
#endif

#endif //FSM_H
