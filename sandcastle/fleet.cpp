#include "fleet.h"
#include "randomizer.h"

const size_t min_fleet_size = 5;
const size_t max_fleet_size = 10;

/*!************************************************************

**************************************************************/
Fleet RandomFleet()
{
  size_t fleet_size = Random(min_fleet_size, max_fleet_size);

  Fleet fleet;

  for (size_t i = 0; i < fleet_size; ++i)
  {
    fleet.AddShip(RandomShip());
  }

  return fleet;
}

/*!************************************************************
TODO: FILL THIS IN
**************************************************************/
EngagementReport Engage(Fleet& fleet1, Fleet& fleet2)
{
  return EngagementReport();
}

/*!************************************************************
a fleet is only destroyed if all its component ships are destroyed
**************************************************************/
bool Fleet::GetDestroyed() const
{
  for (const auto& elem : m_ships)
  {
    if (elem.GetDestroyed() == false)
      return false;
  }

  return true;
}

/*!************************************************************

**************************************************************/
Ship& Fleet::RandomShip()
{
  return m_ships[Random(size_t(0), m_ships.size() - 1)];
}

/*!************************************************************
need to check if name exists, or shift to some UUID system
**************************************************************/
void Fleet::AddShip(const Ship& ship)
{
  m_ships.push_back(ship);
}
