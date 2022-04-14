#include "Main.hpp"


Main::Main()
    : measure(nullptr), controller(nullptr), pulseFactor(0.0)
{
}

 Main::~Main()
{
}

void Main::setMeasure(Measure *m)
{
    measure = m;
    measure->setClient(this);
}

void Main::setController(Controller *c)
{
    controller = c;
}

void Main::setPulseFactor(double pf)
{
    pulseFactor = pf;
}

void Main::measuredPulseLength(double pulseLengthInSeconds)
{
    if (controller != nullptr && pulseFactor > 0.0)
    {
        controller->setPulseLength(pulseFactor * pulseLengthInSeconds);
    }
}
