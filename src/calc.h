#ifndef __CALC_H
#define __CALC_H

static inline long constrain(long amt, long low, long high) {
    return amt < low ? low : (amt > high ? high : amt);
}

static inline long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif //__CALC_H
