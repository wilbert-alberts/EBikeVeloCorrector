#ifndef IMEASURECLIENT_HPP
#define IMEASURECLIENT_HPP

class IMeasureClient
{
public:
    virtual void measuredPulseLength(double pulseLengthInSeconds) = 0;
};

#endif