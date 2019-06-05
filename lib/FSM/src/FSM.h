#ifndef FSM_H
#define FSM_H

#ifdef __cplusplus
extern "C" {
#endif

//TODO create finite state machine api for allow display state management and maybe something else

typedef struct {
    void (*handler) ();
} FSM_Transition_t;

typedef struct {
    void (*enter) ();
    void (*leave) ();
} FSM_State_t;

typedef struct {
    FSM_State_t *state;
} FSM_Handle_t;

void FSM_initialize();

#ifdef __cplusplus
}
#endif

#endif //FSM_H
