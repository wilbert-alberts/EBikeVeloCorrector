#include "T85Controller.hpp"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Controller out: PB2, pin 7
// pulse length: 1ms

// Use timer 1

static T85Controller* instance = nullptr;

 T85Controller* T85Controller::getInstance() {
     if (instance == nullptr) {
         instance = new T85Controller();
     }
     return instance;
 }


T85Controller::T85Controller()
{
    // Set output direction for controller output, pb2
    DDRB |= _BV(DDB2);

    // Enable timer 1 overflow interrupt
    TIMSK |=  _BV(TOIE1);

}

ISR(TIM1_OVF_vect) {
    T85Controller::getInstance()->timerOverflow();
}

void T85Controller::timerOverflow()
{
    periodCtr--;
    if (periodCtr == 0) {
        onTimerCompare();
    }
}

T85Controller::~T85Controller()
{
}

void T85Controller::generatePulse()
{
    PORTB |= _BV(PORTB2);
    _delay_ms(1);
    PORTB &= ~(_BV(PORTB2));
}

void T85Controller::startPeriodTimer(double durationInMs)
{
    // Set prescaler to 1024 -> 1.024 ms per period
    periodCtr = (uint16_t)(durationInMs / 1.024);

    TCNT1 = 0;    
    TCCR1 = (TCCR1 & ~(_BV(CS12))) | (_BV(CS13)|_BV(CS11)| _BV(CS10)); 
}

void T85Controller::stopPeriodTimer()
{
    TCCR1 &= ~(_BV(CS13)| _BV(CS12)|_BV(CS11)| _BV(CS10)); 
}