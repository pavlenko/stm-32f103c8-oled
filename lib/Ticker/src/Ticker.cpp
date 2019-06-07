#include "Ticker.h"

#include <malloc.h>

bool PE::Ticker::initialize(uint32_t time, uint8_t size) {
    _time = time;
    _size = size;

    _list = (Ticker_Handler_t **) malloc(_size * sizeof(Ticker_Handler_t *));

    return false;
}

uint32_t PE::Ticker::createHandlerSingular(uint32_t interval, void (*callable)()) {
    for (uint8_t i = 0; i < _size; ++i) {
        if ((*(_list + i)) == nullptr) {
            (*(_list + i)) = (Ticker_Handler_t *) malloc(sizeof(Ticker_Handler_t));

            if (!(*(_list + i))) {
                return 0;
            }

            _last++;

            (*(_list + i))->identity = _last;
            (*(_list + i))->interval = 0;
            (*(_list + i))->schedule = interval + _time;
            (*(_list + i))->callable = callable;

            return _last;
        }
    }

    return 0;
}

uint32_t PE::Ticker::createHandlerRepeated(uint32_t interval, void (*callable)()) {
    for (uint8_t i = 0; i < _size; ++i) {
        if ((*(_list + i)) == nullptr) {
            (*(_list + i)) = (Ticker_Handler_t *) malloc(sizeof(Ticker_Handler_t));

            if (!(*(_list + i))) {
                return 0;
            }

            _last++;

            (*(_list + i))->identity = _last;
            (*(_list + i))->interval = interval;
            (*(_list + i))->schedule = interval + _time;
            (*(_list + i))->callable = callable;

            return _last;
        }
    }

    return 0;
}

bool PE::Ticker::cancelHandler(uint32_t identity) {
    for (uint8_t i = 0; i < _size; ++i) {
        if ((*(_list + i)) != nullptr && (*(_list + i))->identity == identity) {
            free((*(_list + i)));
            (*(_list + i)) = nullptr;
            return true;
        }
    }

    return false;
}

void PE::Ticker::dispatch(uint32_t time) {
    _time = time;

    for (uint8_t i = 0; i < _size; ++i) {
        if ((*(_list + i)) == nullptr) {
            continue;
        }

        if ((*(_list + i))->schedule < time) {
            (*(_list + i))->callable();

            if ((*(_list + i))->interval > 0) {
                (*(_list + i))->schedule += (*(_list + i))->interval;
            } else {
                (*(_list + i)) = nullptr;
            }
        }
    }
}
