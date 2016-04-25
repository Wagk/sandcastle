#include "module.h"

/*!************************************************************
	FullName :	operator<<
	Returns  :	Utility::Serial::JsonFormat&
	Parameter:	Utility::Serial::JsonFormat & json
	Parameter:	const Module object
	Brief    :		
			
	Expect   :		
	Ensure   :
	Usage    :		
**************************************************************/
template<>
Utility::Serial::JsonFormat& operator<< (Utility::Serial::JsonFormat& json, const Module& object)
{
  using namespace Utility::Serial;

  //serialize name
  json["name"] = object.GetName();
  
  //serialize traits
  JsonFormat traitsarray(ARRAY);
  for (const auto& trait : object.GetTraits())
  {
    JsonFormat traitjson;

    traitjson << trait;
    traitsarray.append(traitjson);
  }
  json["traits"] = traitsarray;
  
  //serialize submodules
  JsonFormat submodulearray(ARRAY);
  for (const auto& submods : object.GetSubmodules())
  {
    JsonFormat submodjson;

    submodjson << submods;
    submodulearray.append(submodjson);
  }
  json["submodules"] = submodulearray;

  return json;
}

/*!************************************************************
	FullName :	operator>>
	Returns  :	Module&
	Parameter:	const Utility::Serial::JsonFormat & json
	Parameter:	Module & object
	Brief    :		
			
	Expect   :		
	Ensure   :
	Usage    :		
**************************************************************/
template<>
Module& operator>>(const Utility::Serial::JsonFormat& json, Module& object)
{
  //set name to json value or default
  if (json["name"].empty() == false)
  {
    object.SetName(json["name"].asString());
  }
  else
  {
    object.SetName("Default Module");
  }

  //set traits to json value or empty
  if (json["traits"].empty() == false)
  {
    Module::Traits traits;

    for (const auto& traitjson : json["traits"])
    {
      Trait trait;
      traitjson >> trait;
      traits.push_back(trait);
    }

    object.SetTraits(traits);
  }
  else
  {
    object.SetTraits(Module::Traits());
  }

  //set submodules to json values or empty
  if (json["submodules"].empty() == false)
  {
    Module::Submodules submodules;

    for (const auto& submodulejson : json["submodules"])
    {
      Module submodule;
      submodulejson >> submodule;
      submodules.push_back(submodule);
    }

    object.SetSubmodules(submodules);
  }
  else
  {
    object.SetSubmodules(Module::Submodules());
  }

  return object;
}

/*!************************************************************

**************************************************************/
Module::Name Module::GetName() const
{
  return m_name;
}

/*!************************************************************

**************************************************************/
void Module::SetName(const Name& name)
{
  m_name = name;
}

/*!************************************************************

**************************************************************/
Module::Traits Module::GetTraits() const
{
  return m_traits;
}

/*!************************************************************

**************************************************************/
void Module::SetTraits(const Traits& traits)
{
  m_traits = traits;
}

/*!************************************************************

**************************************************************/
Module::Submodules Module::GetSubmodules() const
{
  return m_submodules;
}

/*!************************************************************

**************************************************************/
void Module::SetSubmodules(const Submodules& submodules)
{
  m_submodules = submodules;
}
