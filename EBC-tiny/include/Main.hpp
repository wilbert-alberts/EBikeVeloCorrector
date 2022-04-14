#ifndef MAIN_HPP
#define MAIN_HPP

#include "IMeasureClient.hpp"
#include "Measure.hpp"
#include "Controller.hpp"

class Main : public IMeasureClient
{
public:
    Main();
    virtual ~Main();

    void setMeasure(Measure *m);
    void setController(Controller *c);
    void setPulseFactor(double pf);

    virtual void measuredPulseLength(double pulseLengthInSeconds);

private:
    Measure *measure;
    Controller *controller;
    double pulseFactor;
};

#endif
