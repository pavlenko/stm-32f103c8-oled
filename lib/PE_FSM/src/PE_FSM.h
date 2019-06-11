#ifndef PE_FSM_H
#define PE_FSM_H

typedef struct {
    void (*onEnter) ();
    void (*onLeave) ();
    void (*onDispatch) ();
} PE_FSM_State_t;

class PE_FSM {
private:
    PE_FSM_State_t *_prevState;
    PE_FSM_State_t *_nextState;
public:
    /**
     * Default constructor
     */
    PE_FSM() = default;

    /**
     * Set initial state
     *
     * @param state
     */
    void initialize(PE_FSM_State_t *state);

    /**
     * Change state
     *
     * @param state
     */
    void transitionTo(PE_FSM_State_t *state);

    /**
     * Dispatch state change
     */
    void dispatch();
};


#endif //PE_FSM_H
