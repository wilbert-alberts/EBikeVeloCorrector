#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller
{
public:
    Controller();

    virtual ~Controller();

    // Set new pulse length
    void setPulseLength(double plis);

    enum State
    {
        STOPPED,
        RUNNING
    };

protected:

    // Generate output pulse 
    virtual void generatePulse()=0;
    // Start timer to next pulse
    virtual void startPeriodTimer(double duration)=0;
    // Stop timer 
    virtual void stopPeriodTimer()=0;

    // And of pulse period, generate pulse
    void onTimerCompare();

private:
    State state;
    double pulseLengthInSeconds;

};

#endif