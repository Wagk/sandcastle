#include "generators.h"

static size_t counter = 0;

/*!************************************************************
it's not really random, but I can't be assed to load from
a file atm
**************************************************************/
std::string RandomName()
{
  return "Ship " + std::to_string(counter++);
}
