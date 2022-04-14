#ifndef T85CONTROLLER_HPP
#define T85CONTROLLER_HPP

#include "Controller.hpp"

#include <stdint.h>

class T85Controller : public Controller
{
public:
    ~T85Controller();

    static T85Controller* getInstance();

    // Called when timer overflows indicating a period of 1.024 ms
    void timerOverflow();

protected:
    T85Controller();
    // Generaet pulse of 1 ms
    virtual void generatePulse();

    // start timer durationInMs [ 400,6000 ]
    virtual void startPeriodTimer(double durationInMs);

    // stop timer 
    virtual void stopPeriodTimer();

private:
    uint16_t periodCtr;
};

#endif
