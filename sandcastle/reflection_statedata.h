/*!************************************************************
Created:	2016/04/20
Intent:

**************************************************************/
#ifndef reflection_statedata_h__
#define reflection_statedata_h__

#include "reflection_propertydata.h"

namespace Reflection
{

  class Statedata
  {
  public:

    Statedata(DataLayoutType layout = LEAF);
    Statedata(size_t array_count);

    //nested accessors
    Statedata& operator[](const String& name);
    const Statedata& operator[](const String& name) const;

    //array accessors
    Statedata& operator[](size_t index);
    const Statedata& operator[](size_t index) const;
    void Pushback(const Statedata& data);
    void Popback();

    size_t Size() const;
    DataLayoutType LayoutType() const;

    //"getters"
    template<typename T>
    void operator<<(const MirroredType<T>& value); //for types we can grab Propertydata from
    template<typename T>
    void operator<<(const NonMirroredType<T>& value); //for types we need to call extraction operators on

  private:

    DataLayoutType m_layout; //if true, we use `m_arrayfields`, false we use `m_subfields`

    String m_leaf_field;; //used only for leaf nodes to hold string data
    Vector<Statedata> m_array_field;
    Map<String, Statedata> m_struct_field;

  };

} //namespace Reflection

#include "reflection_statedata.inl"

#endif
/*!************************************************************
  Todo:

**************************************************************/

