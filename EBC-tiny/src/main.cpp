#include "Main.hpp"
#include "T85Controller.hpp"
#include "T85Measure.hpp"

#include <avr/interrupt.h>


int main(void)
{
  cli();
  Main *main = new Main();
  Controller *ctrl = T85Controller::getInstance();
  Measure *mea = T85Measure::getInstance();

  main->setController(ctrl);
  main->setMeasure(mea);
  main->setPulseFactor(1.0);

  sei();

  while (1)
    ;

  return 1;
}