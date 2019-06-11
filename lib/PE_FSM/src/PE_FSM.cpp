#include "PE_FSM.h"

void PE_FSM::initialize(PE_FSM_State_t *state) {
    _prevState = _nextState = state;

    if (_prevState->onEnter) {
        _prevState->onEnter();
    }
}

void PE_FSM::transitionTo(PE_FSM_State_t *state) {
    _nextState = state;
}

void PE_FSM::dispatch() {
    if (_prevState != _nextState) {
        if (_prevState->onLeave) {
            _prevState->onLeave();
        }

        _prevState = _nextState;

        if (_prevState->onEnter) {
            _prevState->onEnter();
        }
    }

    if (_prevState->onDispatch) {
        _prevState->onDispatch();
    }
}
