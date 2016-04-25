/*!************************************************************
	Created:	2016/02/11
	Intent:		
			
	Note:
			
**************************************************************/
#ifndef ship_h__
#define ship_h__

#include <string>
#include "conditions.h"
#include <vector>
#include "module.h"

using ShipName = std::string;

class Ship
{
public:

  ShipName GetName() const;
  void SetName(const ShipName& name);

  bool GetDestroyed() const;
  void SetDestroyed(bool flag);

  void AddCondition(const Condition& condition);
  void RemoveCondition(const Condition& condition);
  std::vector<Condition> GetConditions() const;
  size_t GetNumConditions() const;

private:

  size_t FindConditionIndex(const Condition& condition) const;

  bool m_destroyed = false;
  ShipName m_name;
  std::vector<Condition> m_conditions;

};

Ship RandomShip();


#endif // ship_h__
/*!************************************************************
	Todo:

    Make the ship initialization format something like this:

    
			
**************************************************************/


