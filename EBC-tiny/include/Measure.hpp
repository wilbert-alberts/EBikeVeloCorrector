#ifndef MEASURE_HPP
#define MEASURE_HPP

#include "IMeasureClient.hpp"

class Measure
{
public:
    Measure();
    virtual ~Measure();

    void setClient(IMeasureClient *cl);

    enum State
    {
        STOPPED,
        RUNNING
    };

    // Invoke when pulse is seen
    void onPulseTrigger();

protected:
    // Start timing measurement
    // Should be able to measure in range of [400,6000] ms;
    virtual void startPeriodTimer();
    // Set timer value to zero
    virtual void restartPeriodTimer();
    // Stop timer
    virtual void stopPeriodTimer();
    // Capture timer value and return in ms.
    virtual double capturePeriodTimer();

    // Invoke when max duration is measured (6000 ms)
    void onTimerOverflow();

private:
    IMeasureClient *client;
    State state;
    double pulseLengthInSeconds;
    void sendPulseLength(double pulseLengthInSeconds);
};

#endif