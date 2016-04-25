/*!************************************************************
Created:	2016/04/15
Intent:


**************************************************************/
#ifndef reflection_metastruct_h__
#define reflection_metastruct_h__

#include "include_std.h"
#include "reflection_propertylist.h"
#include "reflection_modifydata.h"
#include "reflection_statedata.h"

namespace Reflection
{

  //abstract base class. NO MEMBERS TO BLOAT THE DERIVED SIZE. A VPTR IS BAD ENOUGH
  class Reflectable
  {
  public:

    virtual Propertylist Properties() const = 0; //populates the propertylist
    virtual Statedata State() const = 0;
    virtual bool Modify(const Modifydata& data) = 0; //extracts propertydata and manipulates it

  };

} //namespace Reflection

#include "reflection_reflectable.inl"

#endif
  /*!************************************************************
  Todo:

  **************************************************************/
