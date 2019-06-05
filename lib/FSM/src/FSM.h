#ifndef FSM_H
#define FSM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void (*enter) ();
    void (*leave) ();
} FSM_State_t;

typedef struct {
    FSM_State_t *(*handler) ();
} FSM_Transition_t;

typedef struct {
    FSM_State_t *state;
} FSM_Handle_t;

void FSM_initialize(FSM_Handle_t *fsm, FSM_State_t *state);

void FSM_transition(FSM_Handle_t *fsm, FSM_Transition_t *transition);

#ifdef __cplusplus
}
#endif

#endif //FSM_H
