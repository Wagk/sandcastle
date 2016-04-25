/*!************************************************************
	Created:	2016/02/11
	Intent:		
			
	Note:
			
**************************************************************/
#ifndef fleet_h__
#define fleet_h__

#include "ship.h"

class Fleet
{
public:

  bool GetDestroyed() const;
  Ship& RandomShip();

  void AddShip(const Ship& ship);

private:

  std::vector<Ship> m_ships;

};

using EngagementReport = std::vector<std::string>;

Fleet RandomFleet();
EngagementReport Engage(Fleet& fleet1, Fleet& fleet2);

#endif // fleet_h__
/*!************************************************************
	Todo:
			
**************************************************************/


