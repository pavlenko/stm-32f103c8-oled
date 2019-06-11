#ifndef PE_SERVOMOTOR_H
#define PE_SERVOMOTOR_H

#include <stdint.h>

class PE_Servomotor {
private:
    uint16_t _min;
    uint16_t _max;
public:
    PE_Servomotor() = default;

    PE_Servomotor(uint16_t min, uint16_t max);

    uint16_t getMin() const;

    void setMin(uint16_t min);

    uint16_t getMax() const;

    void setMax(uint16_t max);
};


#endif //PE_SERVOMOTOR_H
