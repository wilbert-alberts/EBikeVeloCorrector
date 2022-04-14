#ifndef T85MEASURE_HPP
#define T85MEASURE_HPP

#include "Measure.hpp"
#include <stdint.h>

class T85Measure : public Measure
{
public:
    static T85Measure* getInstance();
    ~T85Measure();
    void timerPeriod();

protected:
    uint16_t periodCtr;
    T85Measure();

    // Start timing measurement
    // Should be able to measure in range of [400,6000] ms;
    virtual void startPeriodTimer();
    // Set timer value to zero
    virtual void restartPeriodTimer();
    // Stop timer
    virtual void stopPeriodTimer();
    // Capture timer value and return in ms.
    virtual double capturePeriodTimer();
};

#endif