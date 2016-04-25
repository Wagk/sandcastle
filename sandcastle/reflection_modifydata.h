/*!************************************************************
Created:	2016/04/20
Intent:

**************************************************************/
#ifndef reflection_updatedata_h__
#define reflection_updatedata_h__

#include "reflection_propertydata.h"

namespace Reflection
{

  class Modifydata
  {
  public:

    //nested accessors
    Modifydata& operator[](const String& name);
    const Modifydata& operator[](const String& name) const;
    //array accessors
    Modifydata& operator[](size_t index);
    const Modifydata& operator[](size_t index) const;

    //"setters"
    template<typename T>
    bool operator>>(MirroredType<T>& value); //for types we can pass Propertydata into
    template<typename T>
    bool operator>>(NonMirroredType<T>& value); //for types we want to call their insertion operator

    /*!************************************************************
    FullName	:Reflection::Propertydata::ToModify
    Returns		:bool, true if the member contains data to be modified
                     false otherwise
    Parameter	:const String & name
    Brief		:
     
    Use			:
    ```
      
    ```
    **************************************************************/
    bool ToModify(const String& name) const;

  private:

    bool m_is_array; //if true, we use `m_arrayfields`, false we use `m_subfields`\

    using Modifyinfo = Pair<bool, Modifydata>;

    String m_field; //used only for leaf nodes to restore data
    Vector<Pair<String, Modifyinfo>> m_arrayfields;
    Map<String, Modifyinfo> m_subfields;

  };

} //namespace Reflection

#include "reflection_modifydata.inl"

#endif
/*!************************************************************
  Todo:

**************************************************************/

