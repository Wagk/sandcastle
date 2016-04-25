/*!************************************************************
	Created:	2016/02/14
	Intent:		
			Ships are made out of modules. Modules are our building blocks

      Modules have conditions and modifiers
	Note:
			
**************************************************************/
#ifndef module_h__
#define module_h__

#include <string>

#include "conditions.h"
#include "trait.h"
#include "utility_serial.h"

/*
  It looks like modules will have a few things:
    - Typed. There will be crew modules, engine modules, FTL engine modules...
    - Traits. Modules can be dank, dusty, rusty, and more (not that important atm)
    - Conditions. Modules can be on fire, out of power, infected, etc
    - Requirements. Modules might need power, ammunition, crew
    - Limits. Modules might only allow 2 connections, or a module group might 
              only allow two modules of the same type
    - Others. When we throw this into the visualizer we might impose more
              restrictions

    Modules should be able to contain themselves. eg, engines should contain
    engines, ships might want to contain ships, etc.
*/

class Module
{
public:

  ~Module() = default;

  using Name = std::string;
  using Traits = std::vector<Trait>; //the name of a trait, not the definition
  using Submodules = std::vector<Module>; //parts, and number of parts

  Name GetName() const; //the type of the module, as a string 
  void SetName(const Name& name);
  Traits GetTraits() const; //the module traits
  void SetTraits(const Traits& traits);
  Submodules GetSubmodules() const; //the types of the parts of the module
  void SetSubmodules(const Submodules& submodules);

private:

  Name m_name;
  Traits m_traits;
  Submodules m_submodules;

};


/*
  Requirements should be verified using templates
*/

#endif // modules_h__
/*!************************************************************
	Todo:

    Since this is 
			
**************************************************************/


