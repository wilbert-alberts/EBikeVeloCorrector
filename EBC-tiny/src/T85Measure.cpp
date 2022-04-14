
#include "T85Measure.hpp"


#include <avr/io.h>
#include <avr/interrupt.h>

// Measure in on PB4
// Measure (dbg) out on PB3

// Use Timer 0

static T85Measure *instance = nullptr;

T85Measure *T85Measure::getInstance()
{
    if (instance == nullptr)
        instance = new T85Measure();
    return instance;
}

T85Measure::~T85Measure()
{
}

ISR(TIM0_OVF_vect) {
    T85Measure::getInstance()->timerPeriod();
}

ISR(PCINT0_vect) {
    static bool oldValue = false;
    bool newValue= PINB & _BV(PINB3);
    if (newValue != oldValue && newValue)
        T85Measure::getInstance()->onPulseTrigger();
    oldValue = newValue;
}

void T85Measure::timerPeriod() {
    periodCtr++;

    if (periodCtr == 6000) 
    {
        onTimerOverflow();
    }
}

T85Measure::T85Measure()
{
    // Set PB3 to input
    DDRB &= ~(_BV(DDB3)); 

    // Enable pin change interrupt
    GIMSK |= _BV(PCIE);

}

void T85Measure::startPeriodTimer()
{
    periodCtr = 0;
    TCNT0 = 0;
    TCCR0B = (TCCR0B & ~(_BV(CS01))) | (_BV(CS02) | _BV(CS00)); 
}
void T85Measure::restartPeriodTimer()
{
    periodCtr = 0;
    TCNT0 = 0;
    GTCCR |= _BV(PSR0);
}

void T85Measure::stopPeriodTimer()
{
    TCCR0B = (TCCR0B & ~(_BV(CS02) | _BV(CS01) | _BV(CS00))); 
}

double T85Measure::capturePeriodTimer()
{
    double r = 1.024 * periodCtr;
    return r;
}
