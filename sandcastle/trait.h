/*!************************************************************
	Created:	2016/02/23
	Intent:		
			traits are basically things that let us do stats and fite
	Note:
			
**************************************************************/
#ifndef trait_h__
#define trait_h__

#include <string>
#include "utility_serial.h"

using Traitname = std::string;

class Trait
{
public:

  Trait(const Traitname& name = "Default Trait");

  Traitname GetName() const;
  void SetName(const Traitname& name);

private:

  Traitname m_name;

};

#endif // trait_h__
/*!************************************************************
	Todo:
			
**************************************************************/


