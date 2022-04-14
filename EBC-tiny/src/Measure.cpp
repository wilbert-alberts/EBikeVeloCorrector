
#include "Measure.hpp"

Measure::Measure()
{
    state = STOPPED;
    pulseLengthInSeconds = 0;
    client = nullptr;
}
Measure::~Measure() {}

void Measure::setClient(IMeasureClient* cl)
{
    client = cl;
}

void Measure::onPulseTrigger()
{
    switch (state)
    {
    case STOPPED:
        startPeriodTimer();
        state = RUNNING;
        break;
    case RUNNING:
        pulseLengthInSeconds = capturePeriodTimer();
        sendPulseLength(pulseLengthInSeconds);
        restartPeriodTimer();
        break;
    default:
        // TODO? illegal state
        break;
    }
}

void Measure::onTimerOverflow()
{
    switch (state)
    {
    case STOPPED:
        // TODO: illegal state
        break;
    case RUNNING:
        stopPeriodTimer();
        pulseLengthInSeconds = 0.0;
        sendPulseLength(pulseLengthInSeconds);
        break;
    default:
        break;
    }
}

void Measure::sendPulseLength(double pulseLengthInSeconds)
{
    if (client != nullptr)
        client->measuredPulseLength(pulseLengthInSeconds);
}
