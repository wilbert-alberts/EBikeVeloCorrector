
#include "Controller.hpp"

Controller::Controller()
{
    state = STOPPED;
    pulseLengthInSeconds = 0.0;
}

Controller::~Controller()
{
}

void Controller::setPulseLength(double plis)
{
    switch (state)
    {
    case STOPPED:
        pulseLengthInSeconds = plis;
        generatePulse();
        startPeriodTimer(pulseLengthInSeconds);
        state = RUNNING;
        break;
    case RUNNING:
        pulseLengthInSeconds = plis;
        break;
    }
}

void Controller::onTimerCompare()
{
    switch (state)
    {
    case STOPPED:
        // TODO: illegal state
        break;
    case RUNNING:
        generatePulse();
        if (pulseLengthInSeconds > 0.0)
            startPeriodTimer(pulseLengthInSeconds);
        else
            stopPeriodTimer();
        state = STOPPED;
        break;
    default:
        // TODO: illegal state
        break;
    }
}
