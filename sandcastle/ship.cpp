#include "ship.h"
#include "generators.h"



/*!************************************************************

**************************************************************/
Ship RandomShip()
{
  Ship ship;
  ship.SetName(RandomName()); //TODO: name isn't actually random atm

  return ship;
}

/*!************************************************************

**************************************************************/
ShipName Ship::GetName() const
{
  return m_name;
}

/*!************************************************************

**************************************************************/
void Ship::SetName(const ShipName& name)
{
  m_name = name;
}

/*!************************************************************

**************************************************************/
bool Ship::GetDestroyed() const
{
  return m_destroyed;
}

/*!************************************************************

**************************************************************/
void Ship::SetDestroyed(bool flag)
{
  m_destroyed = flag;
}

/*!************************************************************

**************************************************************/
void Ship::AddCondition(const Condition& condition)
{
  if (FindConditionIndex(condition) != m_conditions.size())
    return; //condition already present
  else
  {
    m_conditions.push_back(condition);
  }
}

/*!************************************************************

**************************************************************/
void Ship::RemoveCondition(const Condition& condition)
{
  size_t i = FindConditionIndex(condition);
  if (i == m_conditions.size())
    return; //condition not present
  else
  {
    //swap and pop
    std::swap(m_conditions[i], m_conditions.back());
    m_conditions.pop_back();
  }
}

/*!************************************************************

**************************************************************/
std::vector<Condition> Ship::GetConditions() const
{
  return m_conditions;
}

/*!************************************************************

**************************************************************/
size_t Ship::GetNumConditions() const
{
  return m_conditions.size();
}

/*!************************************************************
returns size (which is out of bounds) if condition DNE
**************************************************************/
size_t Ship::FindConditionIndex(const Condition& condition) const
{
  for (size_t i = 0; i < m_conditions.size(); ++i)
  {
    if (m_conditions[i] == condition)
    {
      return i;
    }
  }

  return m_conditions.size(); //should be out of bounds
}
