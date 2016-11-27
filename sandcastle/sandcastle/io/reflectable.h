/*!************************************************************
Created:	2016/04/15
Intent:


**************************************************************/
#ifndef reflection_metastruct_h__
#define reflection_metastruct_h__

#include "propertylist.h"
#include "modifydata.h"
#include "statedata.h"

namespace sandcastle::io::serial
{

  //abstract base class. NO MEMBERS TO BLOAT THE DERIVED SIZE. A VPTR IS BAD ENOUGH
  class serializable
  {
  public:

    virtual property_list properties() const = 0; //populates the propertylist
    virtual state_data state() const = 0;
    virtual bool modify(const modify_data& data) = 0; //extracts propertydata and manipulates it

  };

} //namespace sandcastle::io::serial

#include "reflectable.inl"

#endif
  /*!************************************************************
  Todo:

  **************************************************************/
