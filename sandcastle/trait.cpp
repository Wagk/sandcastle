#include "trait.h"

/*!************************************************************
	FullName :	operator<<
	Returns  :	Utility::Serial::JsonFormat&
	Parameter:	Utility::Serial::JsonFormat & json
	Parameter:	const Trait & object
	Brief    :		
			
	Expect   :		
	Ensure   :
	Usage    :		
**************************************************************/
template<>
Utility::Serial::JsonFormat& operator<< (Utility::Serial::JsonFormat& json, const Trait& object)
{
  json["name"] = object.GetName();

  return json;
}

/*!************************************************************
	FullName :	operator>>
	Returns  :	Trait&
	Parameter:	const Utility::Serial::JsonFormat & json
	Parameter:	Trait & object
	Brief    :		
			
	Expect   :		
	Ensure   :
	Usage    :		
**************************************************************/
template<>
Trait& operator>>(const Utility::Serial::JsonFormat& json, Trait& object)
{
  //set name to json value or default
  if (json["name"].empty() == false)
  {
    object.SetName(json["name"].asString());
  }
  else
  {
    object.SetName("Default Trait");
  }

  return object;
}

/*!************************************************************

**************************************************************/
Trait::Trait(const Traitname& name /*= "Default Trait"*/)
  : m_name(name)
{

}

/*!************************************************************

**************************************************************/
Traitname Trait::GetName() const
{
  return m_name;
}

/*!************************************************************

**************************************************************/
void Trait::SetName(const Traitname& name)
{
  m_name = name;
}
