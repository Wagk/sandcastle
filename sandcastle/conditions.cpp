#include "conditions.h"
#include "randomizer.h"

#include <array>

static std::vector<Condition> condition_table = 
{
  "On Fire",
  "Venting Gas",
  "Venting Fuel",
  "Venting Crew",
  "Losing Speed",
  "Lost Instrumentation",
  "Lost Life Support",
  "Lost Power",
};

/*!************************************************************

**************************************************************/
Condition RandomCondition()
{
  return condition_table[Random(size_t(0), condition_table.size() - 1)];
}
